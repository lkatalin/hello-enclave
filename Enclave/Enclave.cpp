#include <cstring>
#include <string.h>
#include "Enclave_t.h"

// reverse a string in place
void enclave_string_reverse(char *string) {
	size_t len = strlen(string);
	size_t i = 0;
	while (len > i) {
		char tmp = string[--len];
		string[len] = string[i];
		string[i++] = tmp;
	}
}
