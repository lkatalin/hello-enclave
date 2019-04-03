#include <stdio.h>
#include <iostream>
#include "Enclave_u.h"
#include "sgx_urts.h"


/* Global EID for enclave */
sgx_enclave_id_t global_eid = 0;

int main(int argc, char const *argv[]) {

    // a string originating from within the untrusted App
    char app_secret_string[] = "App's secret string";
   
    // parameters to initialize enclave instance
    const std::string& enclave_name = "enclave.signed.so";
    sgx_launch_token_t token = {0};
    int updated = 0;
    sgx_status_t ret = SGX_ERROR_UNEXPECTED;

    // initialize an enclave instance (for debug support: set 2nd parameter to 1)
    ret = sgx_create_enclave(enclave_name.c_str(), SGX_DEBUG_FLAG, &token, &updated, &global_eid, NULL);
    if (ret != SGX_SUCCESS) {
        printf("Error: %s; Failed to initialize enclave", ret);
	return 1;
    }

    // ask enclave with ID 'global_eid' to reverse the string we pass from app_secret_string
    enclave_string_reverse(global_eid, app_secret_string);

    printf("App string after reverse_string called in enclave: %s\n\n", app_secret_string);

    return 0;
}
