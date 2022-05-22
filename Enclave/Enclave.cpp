#include "Enclave_t.h"

#include "sgx_trts.h"

void calculate_xpos(int32_t seqNumber, int32_t* xpos)
{
    *xpos = 80 + (100 * (seqNumber % 5));
}