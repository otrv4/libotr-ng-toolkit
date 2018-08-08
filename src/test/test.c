#include <glib.h>
#include <string.h>

#include "test_helpers.h"

#include "test_otrng_mackey.c"
#include "test_otrng_parse.c"
#include "test_otrng_readforge.c"

int main(int argc, char **argv) {

  if (!gcry_check_version(GCRYPT_VERSION))
    return 2;

  gcry_control(GCRYCTL_INIT_SECMEM, 0); // disable secure memory for tests
  gcry_control(GCRYCTL_RESUME_SECMEM_WARN);
  gcry_control(GCRYCTL_ENABLE_QUICK_RANDOM, 0);
  gcry_control(GCRYCTL_INITIALIZATION_FINISHED);

  g_test_init(&argc, &argv, NULL);
  g_test_add_func("/toolkit/parse_data_msg",
                  otrng_toolkit_test_parse_data_message);
  g_test_add_func("/toolkit/parse_identity_msg",
                  otrng_toolkit_test_parse_identity_message);
  g_test_add_func("/toolkit/parse_auth_r_msg",
                  otrng_toolkit_test_parse_auth_r_message);
  g_test_add_func("/toolkit/parse_auth_i_msg",
                  otrng_toolkit_test_parse_auth_i_message);

  g_test_add_func("/toolkit/calculate_mac",
                  otrng_toolkit_test_calculate_mac_key);

  g_test_add_func("/toolkit/read_and_forge", otrng_toolkit_test_read_and_forge);

  return g_test_run();
}
