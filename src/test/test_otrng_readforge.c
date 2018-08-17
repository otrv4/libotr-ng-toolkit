#include "../helper.c"
#include "../readforge.c"
#include "test_helpers.h"

void otrng_toolkit_test_read_and_forge_ratchet_key() {
  return;
  //  char *ratchet_key =
  //      "7b8efb2c7f8172a4d867d16290d34ed317726414513cb1a4999939839d026f34916b11a1"
  //      "1e2b04e934fbecc0c8e84eec8826a7e0c50d6eed428cb74336af5418";
  //  char *msg =
  //      "?OTR:AAQDAAABAgAAAQEAAAAAAAAAAAIAAAACNtSQZqzaA4gWxznsjmnQLP9yhtmyAU5IR+"
  //      "Y0FKGCfmLoQ1ooKdee8t9vlIOyoPUoxuYSluV5g8cAAAABgOZazW61heHpiPH5zLZgsA+"
  //      "Qfk26wA9xVEGf+eFGz5uyD+Mcc17X1IvLY8iB9q3Kfmhy42iod/"
  //      "CWWMNueTadffnw6d3168hmQe6P8fVG9H5f1V++YnDs2nSBVg8+ldCDIfdW6nMd/"
  //      "rmDlrEHMeTurIRyZGu+gitdIKj/"
  //      "EU16snHQM5pWp2I57lRQVUYmYPBYId+"
  //      "rXyLWNMSvEcSKX31ESpX8su9aUVp87mmQe1hRRVsfOYNhzTnAus3wAPWG05+"
  //      "CgrZZHLdVq44bl3wIpIfhKL5aQ5grZpbbzehrACpBfxqolr1xQwdhfapYyGVG3T+"
  //      "MzcdGGwZ2CXRBMR53KvzRJ6oPEs2H31Sf+l8cquS0E/"
  //      "n5xlzuokIbzu6vFNgzPdNDebl1MZ+MU40sXxHmZiHqv4+"
  //      "xLD606SNaO24FFIVsW0NR973hocWJjmSbNN2MI5ddrmDK8d0L4pyN8RoHF3LVsViZY+"
  //      "7dWrNo77+yhk6OI4eesJPgK4VfODj00VLIw+aUycb1fOqjogqiewBB+oxzdCSh8Wd+"
  //      "ZbrUKgAAAP/dXlGg2Xkm/eG0vGexMPuxvHhpV+yOr4o9Qw2G7XTMj4hlkLsYndf3zQoQVFX/"
  //      "kj4qjuHJN4bUL1MBfsNbqBnvj8QhxivUz3xMgXN0ihsmn4Nppm8sx4K5wBoUJl+"
  //      "0n8viTzGb1Wr76xway0NhznqFFdDzPD9Fr35sL+2ZteBlLkTZnk/9pVnOvT/"
  //      "I2raW9ywpGLWomxxZR2S3xrsUZMPPznwKgCPDnPuKRj6whcZhi6C9647xbTz+"
  //      "Kqa75gHigXH7Hjgne8VQaiQMyd3TkoR6V9dM0NccrH+JrtINbShYlPjLrjfXxvnnsdmuv++"
  //      "J3ALmT6PoDcKrCsRwStf/"
  //      "LdLlIT1i1NbVtQpASk7ZmSJsGr3SolbAh8GTl2W9xh78kEUbgjqhZpCGO6n7dJ7S4gKpsZwF"
  //      "wnLJLjXtNT/8m20R.";
  //  char *encoded_data_msg = NULL;
  //  char *plain_text = NULL;
  //
  //  readforge(&plain_text, &encoded_data_msg, ratchet_key, msg, NULL);
  //  otrng_toolkit_assert_cmpmem(plain_text, "hello", strlen(plain_text));
  //  otrng_toolkit_assert(encoded_data_msg == NULL);
  //  free(plain_text);
  //  free(encoded_data_msg);
}

void otrng_toolkit_test_read_and_forge_ratchet_key_new_msg() {
  //  char *ratchet_key =
  //      "7b8efb2c7f8172a4d867d16290d34ed317726414513cb1a4999939839d026f34916b11a1"
  //      "1e2b04e934fbecc0c8e84eec8826a7e0c50d6eed428cb74336af5418";
  //  char *msg =
  //      "?OTR:AAQDAAABAgAAAQEAAAAAAAAAAAIAAAACNtSQZqzaA4gWxznsjmnQLP9yhtmyAU5IR+"
  //      "Y0FKGCfmLoQ1ooKdee8t9vlIOyoPUoxuYSluV5g8cAAAABgOZazW61heHpiPH5zLZgsA+"
  //      "Qfk26wA9xVEGf+eFGz5uyD+Mcc17X1IvLY8iB9q3Kfmhy42iod/"
  //      "CWWMNueTadffnw6d3168hmQe6P8fVG9H5f1V++YnDs2nSBVg8+ldCDIfdW6nMd/"
  //      "rmDlrEHMeTurIRyZGu+gitdIKj/"
  //      "EU16snHQM5pWp2I57lRQVUYmYPBYId+"
  //      "rXyLWNMSvEcSKX31ESpX8su9aUVp87mmQe1hRRVsfOYNhzTnAus3wAPWG05+"
  //      "CgrZZHLdVq44bl3wIpIfhKL5aQ5grZpbbzehrACpBfxqolr1xQwdhfapYyGVG3T+"
  //      "MzcdGGwZ2CXRBMR53KvzRJ6oPEs2H31Sf+l8cquS0E/"
  //      "n5xlzuokIbzu6vFNgzPdNDebl1MZ+MU40sXxHmZiHqv4+"
  //      "xLD606SNaO24FFIVsW0NR973hocWJjmSbNN2MI5ddrmDK8d0L4pyN8RoHF3LVsViZY+"
  //      "7dWrNo77+yhk6OI4eesJPgK4VfODj00VLIw+aUycb1fOqjogqiewBB+oxzdCSh8Wd+"
  //      "ZbrUKgAAAP/dXlGg2Xkm/eG0vGexMPuxvHhpV+yOr4o9Qw2G7XTMj4hlkLsYndf3zQoQVFX/"
  //      "kj4qjuHJN4bUL1MBfsNbqBnvj8QhxivUz3xMgXN0ihsmn4Nppm8sx4K5wBoUJl+"
  //      "0n8viTzGb1Wr76xway0NhznqFFdDzPD9Fr35sL+2ZteBlLkTZnk/9pVnOvT/"
  //      "I2raW9ywpGLWomxxZR2S3xrsUZMPPznwKgCPDnPuKRj6whcZhi6C9647xbTz+"
  //      "Kqa75gHigXH7Hjgne8VQaiQMyd3TkoR6V9dM0NccrH+JrtINbShYlPjLrjfXxvnnsdmuv++"
  //      "J3ALmT6PoDcKrCsRwStf/"
  //      "LdLlIT1i1NbVtQpASk7ZmSJsGr3SolbAh8GTl2W9xh78kEUbgjqhZpCGO6n7dJ7S4gKpsZwF"
  //      "wnLJLjXtNT/8m20R.";
  //  /*char *expected_new_data_msg =
  //      "?OTR:AAQDAAABAgAAAQEAAAAAAAAAAAIAAAACNtSQZqzaA4gWxznsjmnQLP9yhtmyAU5IR+"
  //      "Y0FKGCfmLoQ1ooKdee8t9vlIOyoPUoxuYSluV5g8cAAAABgOZazW61heHpiPH5zLZgsA+"
  //      "Qfk26wA9xVEGf+eFGz5uyD+Mcc17X1IvLY8iB9q3Kfmhy42iod/"
  //      "CWWMNueTadffnw6d3168hmQe6P8fVG9H5f1V++YnDs2nSBVg8+ldCDIfdW6nMd/"
  //      "rmDlrEHMeTurIRyZGu+gitdIKj/"
  //      "EU16snHQM5pWp2I57lRQVUYmYPBYId+"
  //      "rXyLWNMSvEcSKX31ESpX8su9aUVp87mmQe1hRRVsfOYNhzTnAus3wAPWG05+"
  //      "CgrZZHLdVq44bl3wIpIfhKL5aQ5grZpbbzehrACpBfxqolr1xQwdhfapYyGVG3T+"
  //      "MzcdGGwZ2CXRBMR53KvzRJ6oPEs2H31Sf+l8cquS0E/"
  //      "n5xlzuokIbzu6vFNgzPdNDebl1MZ+MU40sXxHmZiHqv4+"
  //      "xLD606SNaO24FFIVsW0NR973hocWJjmSbNN2MI5ddrmDK8d0L4pyN8RoHF3LVsViZY+"
  //      "7dWrNo77+yhk6OI4eesJPgK4VfODj00VLIw+aUycb1fOqjogqiewBB+oxzdCSh8Wd+"
  //      "ZbrUKgAAAAjQVk24z3km/X7Ji9TNcLHr82ZVQAiVgd3iNpC5iK3uwy/"
  //      "q+3KkvkK9UakDgI72fyh7UZEd2qnIFEuLa8oLg8bdLyd2dgCosAI=."; */
  //  char *encoded_data_msg = NULL;
  //  char *new_msg = "empty";
  //  char *plain_text;
  //  g_assert_cmpint(
  //      readforge(&plain_text, &encoded_data_msg, ratchet_key, msg, new_msg),
  //      ==, 0);
  //  otrng_toolkit_assert_cmpmem(plain_text, "hello", strlen(plain_text));
  //  // g_assert_cmpstr(encoded_data_msg, ==, expected_new_data_msg);
  //  free(plain_text);
  //  free(encoded_data_msg);
}
//
void otrng_toolkit_test_read_and_forge_encryption_key() {
  return;
  //  char *encryption_key =
  //      "599a91343bd3b586afcbc65c374a3ba08e364814d54437fb353d429213238115";
  //  char *msg =
  //      "?OTR:AAQDAAABAgAAAQEAAAAAAAAAAAIAAAACNtSQZqzaA4gWxznsjmnQLP9yhtmyAU5IR+"
  //      "Y0FKGCfmLoQ1ooKdee8t9vlIOyoPUoxuYSluV5g8cAAAABgOZazW61heHpiPH5zLZgsA+"
  //      "Qfk26wA9xVEGf+eFGz5uyD+Mcc17X1IvLY8iB9q3Kfmhy42iod/"
  //      "CWWMNueTadffnw6d3168hmQe6P8fVG9H5f1V++YnDs2nSBVg8+ldCDIfdW6nMd/"
  //      "rmDlrEHMeTurIRyZGu+gitdIKj/"
  //      "EU16snHQM5pWp2I57lRQVUYmYPBYId+"
  //      "rXyLWNMSvEcSKX31ESpX8su9aUVp87mmQe1hRRVsfOYNhzTnAus3wAPWG05+"
  //      "CgrZZHLdVq44bl3wIpIfhKL5aQ5grZpbbzehrACpBfxqolr1xQwdhfapYyGVG3T+"
  //      "MzcdGGwZ2CXRBMR53KvzRJ6oPEs2H31Sf+l8cquS0E/"
  //      "n5xlzuokIbzu6vFNgzPdNDebl1MZ+MU40sXxHmZiHqv4+"
  //      "xLD606SNaO24FFIVsW0NR973hocWJjmSbNN2MI5ddrmDK8d0L4pyN8RoHF3LVsViZY+"
  //      "7dWrNo77+yhk6OI4eesJPgK4VfODj00VLIw+aUycb1fOqjogqiewBB+oxzdCSh8Wd+"
  //      "ZbrUKgAAAP/dXlGg2Xkm/eG0vGexMPuxvHhpV+yOr4o9Qw2G7XTMj4hlkLsYndf3zQoQVFX/"
  //      "kj4qjuHJN4bUL1MBfsNbqBnvj8QhxivUz3xMgXN0ihsmn4Nppm8sx4K5wBoUJl+"
  //      "0n8viTzGb1Wr76xway0NhznqFFdDzPD9Fr35sL+2ZteBlLkTZnk/9pVnOvT/"
  //      "I2raW9ywpGLWomxxZR2S3xrsUZMPPznwKgCPDnPuKRj6whcZhi6C9647xbTz+"
  //      "Kqa75gHigXH7Hjgne8VQaiQMyd3TkoR6V9dM0NccrH+JrtINbShYlPjLrjfXxvnnsdmuv++"
  //      "J3ALmT6PoDcKrCsRwStf/"
  //      "LdLlIT1i1NbVtQpASk7ZmSJsGr3SolbAh8GTl2W9xh78kEUbgjqhZpCGO6n7dJ7S4gKpsZwF"
  //      "wnLJLjXtNT/8m20R.";
  //  char *encoded_data_msg = NULL;
  //  char *plain_text;
  //  readforge(&plain_text, &encoded_data_msg, encryption_key, msg, NULL);
  //  otrng_toolkit_assert_cmpmem(plain_text, "hello", strlen(plain_text));
  //  otrng_toolkit_assert(encoded_data_msg == NULL);
  //  free(plain_text);
  //  free(encoded_data_msg);
}

void otrng_toolkit_test_read_and_forge_encryption_key_new_msg() {
  return;
  //  char *encryption_key =
  //      "599a91343bd3b586afcbc65c374a3ba08e364814d54437fb353d429213238115";
  //  char *msg =
  //      "?OTR:AAQDAAABAgAAAQEAAAAAAAAAAAIAAAACNtSQZqzaA4gWxznsjmnQLP9yhtmyAU5IR+"
  //      "Y0FKGCfmLoQ1ooKdee8t9vlIOyoPUoxuYSluV5g8cAAAABgOZazW61heHpiPH5zLZgsA+"
  //      "Qfk26wA9xVEGf+eFGz5uyD+Mcc17X1IvLY8iB9q3Kfmhy42iod/"
  //      "CWWMNueTadffnw6d3168hmQe6P8fVG9H5f1V++YnDs2nSBVg8+ldCDIfdW6nMd/"
  //      "rmDlrEHMeTurIRyZGu+gitdIKj/"
  //      "EU16snHQM5pWp2I57lRQVUYmYPBYId+"
  //      "rXyLWNMSvEcSKX31ESpX8su9aUVp87mmQe1hRRVsfOYNhzTnAus3wAPWG05+"
  //      "CgrZZHLdVq44bl3wIpIfhKL5aQ5grZpbbzehrACpBfxqolr1xQwdhfapYyGVG3T+"
  //      "MzcdGGwZ2CXRBMR53KvzRJ6oPEs2H31Sf+l8cquS0E/"
  //      "n5xlzuokIbzu6vFNgzPdNDebl1MZ+MU40sXxHmZiHqv4+"
  //      "xLD606SNaO24FFIVsW0NR973hocWJjmSbNN2MI5ddrmDK8d0L4pyN8RoHF3LVsViZY+"
  //      "7dWrNo77+yhk6OI4eesJPgK4VfODj00VLIw+aUycb1fOqjogqiewBB+oxzdCSh8Wd+"
  //      "ZbrUKgAAAP/dXlGg2Xkm/eG0vGexMPuxvHhpV+yOr4o9Qw2G7XTMj4hlkLsYndf3zQoQVFX/"
  //      "kj4qjuHJN4bUL1MBfsNbqBnvj8QhxivUz3xMgXN0ihsmn4Nppm8sx4K5wBoUJl+"
  //      "0n8viTzGb1Wr76xway0NhznqFFdDzPD9Fr35sL+2ZteBlLkTZnk/9pVnOvT/"
  //      "I2raW9ywpGLWomxxZR2S3xrsUZMPPznwKgCPDnPuKRj6whcZhi6C9647xbTz+"
  //      "Kqa75gHigXH7Hjgne8VQaiQMyd3TkoR6V9dM0NccrH+JrtINbShYlPjLrjfXxvnnsdmuv++"
  //      "J3ALmT6PoDcKrCsRwStf/"
  //      "LdLlIT1i1NbVtQpASk7ZmSJsGr3SolbAh8GTl2W9xh78kEUbgjqhZpCGO6n7dJ7S4gKpsZwF"
  //      "wnLJLjXtNT/8m20R.";
  //  /*char *expected_new_data_msg =
  //      "?OTR:AAQDAAABAgAAAQEAAAAAAAAAAAIAAAACNtSQZqzaA4gWxznsjmnQLP9yhtmyAU5IR+"
  //      "Y0FKGCfmLoQ1ooKdee8t9vlIOyoPUoxuYSluV5g8cAAAABgOZazW61heHpiPH5zLZgsA+"
  //      "Qfk26wA9xVEGf+eFGz5uyD+Mcc17X1IvLY8iB9q3Kfmhy42iod/"
  //      "CWWMNueTadffnw6d3168hmQe6P8fVG9H5f1V++YnDs2nSBVg8+ldCDIfdW6nMd/"
  //      "rmDlrEHMeTurIRyZGu+gitdIKj/"
  //      "EU16snHQM5pWp2I57lRQVUYmYPBYId+"
  //      "rXyLWNMSvEcSKX31ESpX8su9aUVp87mmQe1hRRVsfOYNhzTnAus3wAPWG05+"
  //      "CgrZZHLdVq44bl3wIpIfhKL5aQ5grZpbbzehrACpBfxqolr1xQwdhfapYyGVG3T+"
  //      "MzcdGGwZ2CXRBMR53KvzRJ6oPEs2H31Sf+l8cquS0E/"
  //      "n5xlzuokIbzu6vFNgzPdNDebl1MZ+MU40sXxHmZiHqv4+"
  //      "xLD606SNaO24FFIVsW0NR973hocWJjmSbNN2MI5ddrmDK8d0L4pyN8RoHF3LVsViZY+"
  //      "7dWrNo77+yhk6OI4eesJPgK4VfODj00VLIw+aUycb1fOqjogqiewBB+oxzdCSh8Wd+"
  //      "ZbrUKgAAAAjQVk24z3km/X7Ji9TNcLHr82ZVQAiVgd3iNpC5iK3uwy/"
  //      "q+3KkvkK9UakDgI72fyh7UZEd2qnIFEuLa8oLg8bdLyd2dgCosAI=."; */
  //  char *encoded_data_msg = NULL;
  //  char *plain_text;
  //  char *new_msg = "empty";
  //  readforge(&plain_text, &encoded_data_msg, encryption_key, msg, new_msg);
  //  otrng_toolkit_assert_cmpmem(plain_text, "hello", strlen(plain_text));
  //  // g_assert_cmpstr(encoded_data_msg, ==, expected_new_data_msg);
  //  free(plain_text);
  //  free(encoded_data_msg);
}
