#include <gtk/gtk.h>
#include <assert.h>
#include <string.h>

#define AX_CAST(type, var) (*((type*)var))
#define AX_P_CAST(type, var) ((type*)var)
#define AX_P_DEREF(new_name, type, var) type* new_name = (((type*)var))


/**
   *
   */
typedef struct input_group {
  GtkWidget *input_group;
  GtkWidget *label;
  GtkWidget *input;
  char *name;
} input_group_t;


typedef struct form {
//  input_group_t* inputs;
  GHashTable *inputs;
  GHashTable *buttons;
} form_t;

typedef struct window {
  GtkWidget *window;

  GtkWidget *button;
  GtkWidget *another_button;
  GtkWidget *third_button;
  GtkWidget *button_box;

  GtkWidget *dialog_hbox;
  GtkWidget *total_vbox;

  /**
   * TODO: use prefixes to identify.
   */
  form_t *student_info_form;

  GtkWidget *student_form_buttons_group;
  GtkWidget *student_name_submit;
  GtkWidget *student_name_cancel;

  GtkWidget *entry;
} window_t;

gpointer student_inputs[2];

static void
print_hello(GtkWidget *widget,
            gpointer data) {
  AX_P_DEREF(pointer, int, data);
  if (pointer) {
    *pointer += 1;
    g_print("%p\n", pointer);
    g_print("Hello world! %d\n", AX_CAST(int, data));
  } else {
    g_print("NULL!\n");
  }
}

static void
print_each_input(gpointer key,
                 gpointer value,
                 gpointer user_data) {
  AX_P_DEREF(input, input_group_t, value);
  g_print("%s: %s\n", gtk_label_get_text(GTK_LABEL(input->label)), gtk_entry_get_text(GTK_ENTRY(input->input)));
}

static void
print_student(GtkWidget *widget,
              gpointer data) {
  AX_P_DEREF(pointer, GHashTable, data);
  assert(pointer != NULL);

  g_hash_table_foreach(pointer, print_each_input, NULL);
}

static void
activate(GtkApplication *app,
         gpointer user_data) {

  AX_P_DEREF(my_window, window_t, user_data);
  my_window->window = gtk_application_window_new(app);
  gtk_window_set_title(GTK_WINDOW(my_window->window), "Hello GNOME");

  my_window->total_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 1);
  my_window->dialog_hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);

  AX_P_DEREF(id_group, input_group_t, g_hash_table_lookup(my_window->student_info_form->inputs, "id"));
  assert(id_group != NULL);
  id_group->input = gtk_entry_new();
  id_group->label = gtk_label_new("Student ID: ");
  id_group->input_group = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
  gtk_container_add(GTK_CONTAINER(id_group->input_group), id_group->label);
  gtk_container_add(GTK_CONTAINER(id_group->input_group), id_group->input);

  AX_P_DEREF(name_group, input_group_t, g_hash_table_lookup(my_window->student_info_form->inputs, "name"));
  assert(name_group != NULL);
  name_group->input = gtk_entry_new();
  name_group->label = gtk_label_new("Student Name: ");
  name_group->input_group = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
  gtk_container_add(GTK_CONTAINER(name_group->input_group), name_group->label);
  gtk_container_add(GTK_CONTAINER(name_group->input_group), name_group->input);

  my_window->student_form_buttons_group = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);

  my_window->button_box = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
//  gtk_container_add(GTK_CONTAINER(window), button_box);
  gtk_container_add(GTK_CONTAINER(my_window->window), my_window->total_vbox);

  gtk_container_add(GTK_CONTAINER(my_window->total_vbox), my_window->dialog_hbox);
  gtk_container_add(GTK_CONTAINER(my_window->total_vbox), id_group->input_group);
  gtk_container_add(GTK_CONTAINER(my_window->total_vbox), name_group->input_group);
  gtk_container_add(GTK_CONTAINER(my_window->total_vbox), my_window->student_form_buttons_group);

  my_window->button = gtk_button_new_with_label("Hello!");
  my_window->another_button = gtk_button_new_with_label("Hello!");
  my_window->third_button = gtk_button_new_with_label("Hello2!");

  my_window->student_name_submit = gtk_button_new_with_label("Submit");
  my_window->student_name_cancel = gtk_button_new_with_label("Cancel");

  my_window->entry = gtk_entry_new();


  gtk_container_add(GTK_CONTAINER(my_window->dialog_hbox), my_window->button);
  gtk_container_add(GTK_CONTAINER(my_window->dialog_hbox), my_window->another_button);
  gtk_container_add(GTK_CONTAINER(my_window->dialog_hbox), my_window->third_button);
  gtk_container_add(GTK_CONTAINER(my_window->dialog_hbox), my_window->entry);


  gtk_container_add(GTK_CONTAINER(my_window->student_form_buttons_group), my_window->student_name_submit);
  gtk_container_add(GTK_CONTAINER(my_window->student_form_buttons_group), my_window->student_name_cancel);
  int n = 31;
  printf("%p\n", &n);
  g_signal_connect(my_window->button, "clicked", G_CALLBACK(print_hello), &n);
  g_signal_connect(my_window->another_button, "clicked", G_CALLBACK(print_hello), NULL);

//  student_inputs[0] = &my_window->student_id_input;
//  student_inputs[1] = &my_window->student_name_input;
  g_signal_connect(my_window->student_name_submit, "clicked", G_CALLBACK(print_student), my_window->student_info_form->inputs);
//  g_signal_connect_swapped(button, "clicked", G_CALLBACK(gtk_widget_destroy), window);
//  gtk_container_add(GTK_CONTAINER(button_box), button);
//  gtk_container_add(GTK_CONTAINER(window), another_button);

  gtk_widget_show_all(my_window->window);
}

guint hash_table_hash(gpointer a, gpointer b) {

}

gboolean hash_table_equal(gpointer a, gpointer b) {
  return strcmp(AX_P_CAST(char, a), AX_P_CAST(char, b));
}

int
main(int argc, char **argv) {
  GtkApplication *app;
  int status;
  /**
   *
   */
  app = gtk_application_new("org.gtk.example",
                            G_APPLICATION_FLAGS_NONE);
  /**
   * Initialize properties of the window components.
   */
  window_t window;
  window_t *p_window = &window;

  form_t form;
  form_t *p_form = &form;

  form.buttons = g_hash_table_new(g_str_hash, g_str_equal);
  form.inputs = g_hash_table_new(g_str_hash, g_str_equal);

  input_group_t id_group;
  input_group_t name_group;

  p_window->student_info_form = &form;
  GString* id_string = g_string_new("id");
  GString* name_string = g_string_new("name");
  /**
   * Initializing the hash table for groups of inputs
   */
  g_hash_table_insert(p_window->student_info_form->inputs, "id", &id_group);
  g_hash_table_insert(p_window->student_info_form->inputs, "name", &name_group);
  g_print("%p\n", g_hash_table_lookup(p_window->student_info_form->inputs, "id"));
  assert(g_hash_table_lookup(p_window->student_info_form->inputs, "id") != NULL);
  /**
   *
   */
  g_signal_connect(app, "activate",
                   G_CALLBACK(activate), p_window);
  status = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);
  char query[] = "INSERT INTO students VALUE(1, 2);";
  return (status);
}