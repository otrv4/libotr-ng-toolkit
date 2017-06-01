#include <glib.h>
#include <string.h>

#include "test_otrv4_parse.c"

int main(int argc, char **argv) {
  g_test_init(&argc, &argv, NULL);
  g_test_add_func("/toolkit/parse", otrv4_toolkit_test_parse_data_message);

  return g_test_run();
}
