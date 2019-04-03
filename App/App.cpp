#include <stdio.h>
#include <iostream>
#include "Enclave_u.h"
#include "sgx_urts.h"
#include "sgx_utils/sgx_utils.h"

/* Global EID for enclave */
sgx_enclave_id_t global_eid = 0;

int main(int argc, char const *argv[]) {

    // a string originating from within the untrusted App
    char app_secret_string[] = "App's secret string";
 
    if (initialize_enclave(&global_eid, "enclave.token", "enclave.signed.so") < 0) {
        std::cout << "Fail to initialize enclave." << std::endl;
        return 1;
    }

    // ask enclave with ID 'global_eid' to reverse the string we pass from app_secret_string
    enclave_string_reverse(global_eid, app_secret_string);

    printf("App string after reverse_string called in enclave: %s\n\n", app_secret_string);

    return 0;
}
