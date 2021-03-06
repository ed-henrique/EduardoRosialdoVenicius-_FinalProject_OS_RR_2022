#include <stdio.h>
#include <string.h>
#include "io_related.h"
#include "log_related.h"
#include "socket_related.h"

void test_if_options_passed(int argc, char* argv[], char** LOG_NAME, int* PORT, char** HOST, int* COMPRESS, int* LOG_SAVE) {
    for (int i = 1; i < argc; i++) {
        if (strstr(argv[i], "--help") != NULL) print_help(argv);
        else if (strstr(argv[i], "--log") != NULL) {
            *LOG_SAVE = 1;
            *LOG_NAME = create_log(argv[i], *PORT, *HOST, *COMPRESS, *LOG_SAVE);
        }
        else if (strstr(argv[i], "--compress") != NULL) *COMPRESS = 1;
        else if (strstr(argv[i], "--port") != NULL) *PORT = change_port(argv[i]);
        else if (strstr(argv[i], "--host") != NULL) *HOST = change_host(argv[i]);
        else printf("No options passed\n");
    }
}