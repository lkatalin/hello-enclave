## To run
This code relies on the linux-sgx-driver from: https://github.com/intel/linux-sgx-driver
It also assumes you have the SGX SDK installed from: https://github.com/intel/linux-sgx

Once the latter is installed, it will print output indicating where your SGXSDK lives. This will be used as the environment variable for the Makefile.


To make the executable install the driver and SDK (see above), then run:

make SGX_SDK={your SGXSDK path}

Example: make SGX_SDK=/home/user/linux-sgx/linux/installer/bin/sgxsdk



## What this code does
This code launches one SGX enclave containing a default string. An application outside the enclave calls enclave functions to: 

1) have the enclave emit its default string, 
2) have the enclave reverse its default string, 
3) have the enclave emit its default string again, 
4) ask the enclave to save a new string passed in from the application, 
5) ask the enclave to emit this new string, 
6) ask the enclave to reverse this new string, 
7) ask the enclave to emit the new reversed string.

## Details
The untrusted application's functions are specified in ./App/App.cpp.
The enclave's functions are specified in ./Enclave/Enclave.cpp.
The enclave's interface to the application is specified in ./Enclave/Enclave.edl.

The enclave contains:
- One char array to store strings (saved_string[]), which reads "Default enclave saved text" by default.
- One function to read in a string from the application (enclave_string_save) and store it into saved_string[]. 
- One function to emit whatever is stored in saved_string[] to the untrusted application.
- One function to reverse (in place) the string in saved_string[].

## Thanks to:
- https://github.com/digawp/hello-enclave
- https://ayeks.de/2016/01/Create-and-Execute-an-Intel-SGX-Enclave/

## Other resources:
- https://software.intel.com/en-us/articles/intel-software-guard-extensions-tutorial-part-7-refining-the-enclave
- https://software.intel.com/en-us/sgx-sdk-dev-reference-the-edger8r-tool
- https://software.intel.com/en-us/sgx-sdk-dev-reference-calling-functions-outside-the-enclave
