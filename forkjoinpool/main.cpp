#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cassert>
#include <thread>
#include <queue>
#include <sstream>

#define MAX 100
#define MAX_SMALL 10
int numbers[MAX];
int numbers_2[MAX];
int numbers_small[MAX_SMALL];

#ifdef DEBUG
#define LOG(message) \
std::cout << message << std::endl
#else
#define LOG
#endif

int compare(const void *a, const void *b) {
  return (*(int *) a - *(int *) b);
}


void print_one() {
  std::cout << "11111111111111111111" << std::endl;
//  exit(0);
  std::cout << "11111111111111111111\n" << std::endl;
}

namespace parallel {

class logger {

 public:
  logger() {

  }

  class logger_factor {
   public:
    logger_factor() {

    }
  };
};
//auto dummy_executable = [&]() { };


template<size_t size>
class fork_join_pool {
 private:
 public:
  typedef void(*executable_t)(void);
 private:
  std::queue<size_t> available_indices;
  std::shared_ptr<std::thread> threads[size];
  
  executable_t executables[size];
  bool executed[size];
  bool on = true;
  bool is_idling = true;
  std::queue<executable_t> tasks_to_execute;
  bool idle = false;
 public:
  fork_join_pool() {
    for (size_t i = 0; i < size; ++i) {

      available_indices.push(i);
//        executables[i] = &dummy_executable;
      executables[i] = nullptr;

      executed[i] = true;
      threads[i] = nullptr;
    }
  }

  bool if_finished() {
//    std::ostringstream message;
//    message << "Available: ";
//    message << available_indices.size();
//    message << ", Tasks to execute: ";
//    message << tasks_to_execute.size();
//    std::cout << message.str() << std::endl;
    return (available_indices.size() == size) && tasks_to_execute.size() == 0;
  }

  void construct() {
    LOG("Constructing!\n");
    on = true;

    auto worker_dispatcher = std::thread([this] () {
      while(this->on) {
        /**
         * If there are tasks to execute, and there are indices available,
         * dispatch the top task.
         */
        if (!this->tasks_to_execute.empty() && !this->available_indices.empty()) {
          std::cout << "Executing tasks!" << std::endl;
          auto available_index = this->available_indices.front();
          this->available_indices.pop();

          this->set_task(this->tasks_to_execute.front(), available_index);
          this->tasks_to_execute.pop();
        }
      }
    });

    for (size_t i = 0; i < size; ++i) {
      /**
       * Creating the working threads.
       */
      threads[i] = std::make_shared<std::thread>([this, i]() {
        std::string message = "Executing task ";
        while (this->on) {
          if (!this->executed[i]) {
            message += '1';
            LOG(this->executed[i]);
            LOG(message);

            (*(this->executables[i]))();
            this->executed[i] = true;
            available_indices.push(i);
          }

        }
      });
    }

    LOG("Running!");
    worker_dispatcher.join();
    for (int i = 0; i < size; ++i) {
      this->threads[i]->join();
    }
  }

  void stop() {
    LOG("Stopping!");
    on = false;
  }

  void push_task(executable_t executable) {
    this->tasks_to_execute.push(executable);
  }

 private:

  void set_task(executable_t executable, size_t index) {
    LOG("Setting task!");
    assert(index < size);
    this->executed[index] = false;
    LOG(this->executed[index]);
    this->executables[index] = executable;
  }

};

}

namespace quicksort {
/**
 * Offset is the size
 */
int arrange(int *array, int offset) {
  /**
   * Determine the pivot.
   */
  int pivot_i = offset / 2;
  int pivot_v = array[pivot_i];
  int temp;
  int pivot_position = pivot_i;
  /**
   * Start to arrange.
   */
  int start_i = 0, end_i = offset - 1;
  while (start_i < end_i) {
    while (array[start_i] < pivot_v) start_i++;
    while (array[end_i] > pivot_v) end_i--;
    if (start_i < end_i) {
      temp = array[start_i];
      array[start_i] = array[end_i];
      array[end_i] = temp;
      if (start_i == pivot_position) pivot_position = end_i;
      else if (end_i == pivot_position) pivot_position = start_i;
    }
  }
  return pivot_position;
}


template<size_t size>
void sort(int *array) {

}

template<size_t size>
void parallel_sort(int *array) {

}

}

void print_array(int *array, size_t size) {
  assert(size > 0);
  for (int i = 0; i < size - 1; ++i) {
    std::cout << array[i] << ' ';
  }
  std::cout << array[size - 1];
}

template<size_t length>
void print_array(int (&array)[length]) {
  static_assert(length > 0, "The size must be at least 1.");
  for (int i = 0; i < length - 1; ++i) {
    std::cout << array[i] << ' ';
  }
  std::cout << array[length - 1] << '\n';
}

std::thread make_sort_thread(int *array, int size) {
  std::cout << "making " << array << ", " << size << '\n';
  if (size > 1) {
    std::thread sort_thread([&array, &size]() {
      auto split_position = quicksort::arrange(array, size);
      if (split_position > 1) {
        auto thread_1 = make_sort_thread(array, split_position);
        thread_1.join();
      }
      if (size - 1 - split_position > 1) {
        auto thread_2 = make_sort_thread(array + split_position + 1, size - 1 - split_position);
        thread_2.join();
      }
    });
    return sort_thread;
  } else {
    std::thread empty_thread([]() {
      return;
    });
    return empty_thread;
  }
}

int main() {
  srand(static_cast<unsigned>(time(0)));
  for (int i = 0; i < MAX; ++i) {
    numbers[i] = rand();
    numbers_2[i] = numbers[i];
  }

  for (int i = 0; i < MAX_SMALL; ++i) {
    numbers_small[i] = rand() % 512;
  }

  auto t0 = clock();
  qsort(numbers, MAX, sizeof(int), compare);
  auto t1 = clock();
  std::cout
      << "Time elapsed: " << static_cast<double>(t1 - t0) / CLOCKS_PER_SEC << '\n';

  print_array(numbers_small);



  t0 = clock();

  using pool_thousand = parallel::fork_join_pool<10>;
  pool_thousand my_pool;

//  pool_thousand::executable_t print_one = print_one;
  LOG("Pre setting task!\n");

//  auto setting_thread = std::thread([&]() {
  LOG("Setting task\n");
  my_pool.push_task(print_one);
  LOG("After Setting task\n");

  auto pool_thread = std::thread([&my_pool]() {
    my_pool.construct();
  });

  auto watching_thread = std::thread([&my_pool] () {
    while(!my_pool.if_finished()) {LOG("My pool is not finished!");};
    my_pool.stop();
  });

  pool_thread.join();
  watching_thread.join();

  std::cout << "Run ended!" << std::endl;


  t1 = clock();
  std::cout
      << "Thread pool test, time elapsed: "
      << static_cast<double>(t1 - t0) / CLOCKS_PER_SEC << '\n';


  return 0;
}