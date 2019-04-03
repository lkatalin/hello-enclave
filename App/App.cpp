#include <stdio.h>
#include <iostream>
#include "Enclave_u.h"
#include "sgx_urts.h"
#include "sgx_utils/sgx_utils.h"

#define MAX_BUF_LEN 100

/* Global EID shared by multiple threads */
sgx_enclave_id_t global_eid = 0;

int main(int argc, char const *argv[]) {

    // a string originating from within the untrusted App
    char app_secret_string[MAX_BUF_LEN] = "App's secret string";

    // a char array in the untrusted App that will store strings returned 
    // from trusted Enclave
    char string_from_enclave[MAX_BUF_LEN] = "";
    
    if (initialize_enclave(&global_eid, "enclave.token", "enclave.signed.so") < 0) {
        std::cout << "Fail to initialize enclave." << std::endl;
        return 1;
    }

    // initialize testing
    printf("\n\nInitializing Enarx testing.... \n\n");

    // ask enclave with ID 'global_eid' to emit its default stored string into 
    // App's char array 
    enclave_output_saved_string(global_eid, string_from_enclave, MAX_BUF_LEN);
    printf("App: Received Enclave's default stored string: %s\n", string_from_enclave);

    // ask enclave with ID 'global_eid' to reverse its default string
    enclave_reverse_string(global_eid);
    printf("App: Enclave has been asked to reverse its default string....\n");

    // ask enclave with ID 'global_eid' to re-emit its default stored string
    enclave_output_saved_string(global_eid, string_from_enclave, MAX_BUF_LEN);
    printf("App: Received Enclave's reversed stored string: %s\n\n", string_from_enclave);


    // print App's string for user
    printf("App: The App's Secret String we will ask the Enclave to save is: %s\n", app_secret_string);

    // save a string into enclave with ID 'global_eid'
    enclave_string_save(global_eid, app_secret_string);
    printf("App: Sent App's secret string (from above) to Enclave.\n");


    // ask enclave with ID 'global_eid' to re-emit its stored string
    enclave_output_saved_string(global_eid, string_from_enclave, MAX_BUF_LEN);
    printf("App: Received Enclave's current stored string (should be same as App's Secret String (above)): %s\n\n", string_from_enclave);

    // ask enclave with ID 'global_eid' to reverse its stored string
    enclave_reverse_string(global_eid);
    printf("App: Enclave has been asked to reverse its current stored string....\n");

    // ask enclave to emit its stored string
    enclave_output_saved_string(global_eid, string_from_enclave, MAX_BUF_LEN);
    printf("App: Received reversed stored string from Enclave: %s\n\n", string_from_enclave);

    return 0;

}
