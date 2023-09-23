#!/bin/bash
set -e

make SGX_MODE=HW SGX_DEBUG=0 SGX_PRERELEASE=1
# ~/SGXSan/Tool/GetLayout.sh Enclave/Enclave_t.o Enclave/Enclave.o Enclave/sqlite3.o Enclave/ocall_interface.o /opt/intel/sgxsdk/lib64/libsgx_trts.a /opt/intel/sgxsdk/lib64/libsgx_tstdc.a /opt/intel/sgxsdk/lib64/libsgx_tcxx.a /opt/intel/sgxsdk/lib64/libsgx_tcrypto.a /opt/intel/sgxsdk/lib64/libsgx_tservice.a
