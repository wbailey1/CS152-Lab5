// See LICENSE for license details.

#include "dataset.h"
#include "util.h"
#include <stddef.h>

void matmul(const size_t coreid, const size_t ncores, const size_t lda,  const data_t A[], const data_t B[], data_t C[])
{
  size_t i, j, k;

  for (i = 0; i < lda; i++) {
    for (j = coreid; j < lda; j += ncores) {
      data_t sum = 0;
      for (k = 0; k < lda; k++)
        sum += A[j*lda + k] * B[k*lda + i];
      C[i + j*lda] = sum;
    }
  }
}

void matmul_opt(const size_t coreid, const size_t ncores, const size_t lda,  const data_t A[], const data_t B[], data_t C[])
{
	size_t i, j, k, kblock, jblock;
	data_t sum;
	for (kblock = 0; kblock < lda; kblock += 8) {
		for (jblock = 8*coreid; jblock < lda; jblock += 8*ncores) {
			for (i = 0; i < lda; i++) {
				for (j = jblock; j < jblock + 8; j++) {
					sum = C[i*lda + j];
					for (k = kblock; k < kblock + 8; k++) {
						sum += A[i*lda + k] * B[k*lda + j];
					}
					C[i*lda + j] = sum;
				}
			}
		}
	}

    /*for (i = coreid; i < lda; i += ncores) {
        for (k = 0; k < lda; k++) {
            for (j = 0; j < lda; j++) {
                C[i*lda + j] += A[i*lda + k] * B[k*lda + j];
            }
        }
    }*/
}


