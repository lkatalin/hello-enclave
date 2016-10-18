#include <cstring>
#include <string.h>
#include "Enclave_t.h"

// save a string in the enclave
char saved_string[100] = "Default Enclave Saved Text";

// save a string passed in from the outside world
void enclave_string_save(char *input) {
        if ((strlen(input) + 1) < 100)
        {
                memcpy(saved_string, input, strlen(input) + 1);
        } else {
                memcpy(input, "false", strlen("false") + 1);
        }
}

// reverse the string in saved_string
void enclave_reverse_string(void) {
        char* str = saved_string;
        size_t len = strlen(str);
        size_t i = 0;
        while (len > i) {
                char tmp = str[--len];
                str[len] = str[i];
                str[i++] = tmp;
        }
}

// send saved string to outside world
void enclave_output_saved_string(char *output, size_t len) {
        if (len > strlen(saved_string)) {
                memcpy(output, saved_string, strlen(saved_string) + 1);
        }
        else {
                memcpy(output, "false", strlen("false") + 1);
        }
}
