// See LICENSE for license details.

#include "stdlib.h"
#include "dataset.h"

//--------------------------------------------------------------------------
// vvadd function

void __attribute__((noinline)) vvadd(int coreid, int ncores, size_t n, const data_t* x, const data_t* y, data_t* z)
{
   size_t i;

   // interleave accesses
   for (i = coreid; i < n; i+=ncores)
   {
      z[i] = x[i] + y[i];
   }
}

void __attribute__((noinline)) vvadd_opt(int coreid, int ncores, size_t n, const data_t* x, const data_t* y, data_t* z)
{
	int chunkSize = n / ncores;
	int start = coreid * chunkSize;
	for(int i = 0; i<chunkSize; i++) {
		z[i + start] = x[i + start] + y[i + start];
	}
	if (coreid == 1) {
		for(int i = n / ncores * ncores; i < n; i++)
		z[i] = x[i] + y[i];
	}
}
