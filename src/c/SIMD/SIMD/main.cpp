#include <immintrin.h>

#ifdef __cplusplus
#include <cstdlib>
#include <iostream>
#else
#include <stdio.h>
#endif

int main() {

	int i;

	int int_array[8] = { 100, 200, 300, 400, 500, 600, 700, 800 };

	//__m256i mask = _mm256_setr_epi32(-20, -72, -48, -9, -100, 3, 5, 8);
	__m256i mask = _mm256_set_epi32(8, 5, 3, -100, -9, -48, -72, -20);

	__m256i result = _mm256_maskload_epi32(int_array, mask);

	//int* res = (int*)&result;
	//printf("%d %d %d %d %d %d %d %d\n", res[0], res[1], res[2], res[3], res[4], res[5], res[6], res[7]);

	int* resMask = (int*)&mask;
	printf("%d %d %d %d %d %d %d %d\n", resMask[0], resMask[1], resMask[2], resMask[3], resMask[4], resMask[5], resMask[6], resMask[7]);


	//std::cin.get();
	system("pause");

	return 0;
}