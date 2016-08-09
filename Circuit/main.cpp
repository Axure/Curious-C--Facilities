#include <iostream>

#include <boost/signals2.hpp>
#include <vector>
#include <memory>
#include <string>

//enum class State: bool {
//  ON = true, OFF = false
//};

using State = bool;
const State ON = true;
const State OFF = false;

typedef boost::signals2::signal<void(State)> ElectronSignal;
typedef ElectronSignal::slot_type ElectronSlot;

struct Gate {
  std::string name_;

  Gate(std::string &name) : name_(name) {}
  Gate(std::string &&name) : name_(name) {}

  virtual State checkValue() = 0;

  virtual void check() = 0;

};

struct TwoOneGate: public Gate {

  State firstState = OFF, secondState = OFF;


  std::shared_ptr<ElectronSignal> output = std::make_shared<ElectronSignal>();

  TwoOneGate(std::string &name) : Gate(name) {}
  TwoOneGate(std::string &&name) : Gate(name) {}

  virtual State checkValue() = 0;
  virtual State getValue() = 0;
  virtual void setValue(State value) = 0;

  virtual void check() {
    auto value = this->checkValue();
    if (this->getValue() != value) {
      std::cout << "Automatically output of Gate " << name_ << " turns to " << value << '\n';
      this->setValue(value);
      (*output)(value);
    }
  }

  void FirstInput(State value) {
    std::cout << "Automatically input 1 of Gate " << name_ << " turns to " << value << '\n';
    setFirst(value);
  }

  void SecondInput(State value) {
    std::cout << "Automatically input 2 of Gate " << name_ << " turns to " << value << '\n';
    setSecond(value);
  }

 private:

  void setFirst(State value) {
    firstState = value;
    check();
  }

  void setSecond(State value) {
    secondState = value;
    check();
  }

 public:

  void ManualFirstInput(State value) {
    std::cout << "\nManually setting 1st input of Gate " << name_ << " to " << value << "\n\n";
    setFirst(value);
  }

  void ManualSecondInput(State value) {
    std::cout << "\nManually setting 2nd input of Gate " << name_ << " to " << value << "\n\n";
    setSecond(value);
  }

};

struct AndGate: public TwoOneGate {

  State value = checkValue();

  AndGate(std::string &name) : TwoOneGate(name) {}
  AndGate(std::string &&name) : TwoOneGate(name) {}

  State getValue() {
    return this->value;
  }

  void setValue(State value) {
    this->value = value;
  }

  State checkValue() {
    return this->firstState && this->secondState;
  }

};


struct OrGate: public TwoOneGate {

  State value = checkValue();

  OrGate(std::string &name) : TwoOneGate(name) {}
  OrGate(std::string &&name) : TwoOneGate(name) {}

  State getValue() {
    return this->value;
  }

  void setValue(State value) {
    this->value = value;
  }

  State checkValue() {
    return this->firstState || this->secondState;
  }

};

int main() {
  AndGate b1("B1"), b2("B2"), f1("F1");
  OrGate f2("F2");
  b1.output->connect(ElectronSlot(&AndGate::FirstInput, f1, _1));
  b1.output->connect(ElectronSlot(&OrGate::FirstInput, f2, _1));
  b2.output->connect(ElectronSlot(&AndGate::SecondInput, f1, _1));
  b2.output->connect(ElectronSlot(&OrGate::SecondInput, f2, _1));

  b1.ManualFirstInput(true);
  b2.ManualFirstInput(true);
  b1.ManualSecondInput(true);
  b2.ManualSecondInput(true);
}