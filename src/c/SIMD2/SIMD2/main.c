// References
//  https://zenodo.org/record/7594/files/CERN_openlab_report_Fumero.pdf
// Anger Fog Microarchitecture optimization manual
// Intel Intrinsics Guide
//  https://software.intel.com/sites/landingpage/IntrinsicsGuide/#expand=112,3118,3053,4645,3258,4645,4563,4645,3053,3118,3053,112&techs=AVX,AVX2&text=vaddps


//-----------------------------------------------------------------------
// Code to check if the CPU supports AVX and AVX2
//-----------------------------------------------------------------------

//#if defined(__INTEL_COMPILER) && (__INTEL_COMPILER >= 1300)
//#include <immintrin.h>
//int check_4th_gen_intel_core_features()
//{
//	const int the_4th_gen_features =
//		(_FEATURE_AVX2 | _FEATURE_FMA | _FEATURE_BMI | _FEATURE_LZCNT | _FEATURE_MOVBE);
//	return _may_i_use_cpu_feature(the_4th_gen_features);
//}
//#else /* non-Intel compiler */
//#include <stdint.h>
//#if defined(_MSC_VER)
//# include <intrin.h>
//#endif
//
//#if defined(_MSC_VER)
//void run_cpuid(uint32_t eax, uint32_t ecx, int32_t* abcd) {
//#else
//void run_cpuid(uint32_t eax, uint32_t ecx, uint32_t* abcd) {
//#endif
//
//#if defined(_MSC_VER)
//	__cpuidex(abcd, eax, ecx);
//#else
//	uint32_t ebx, edx;
//# if defined( __i386__ ) && defined ( __PIC__ )
//	/* in case of PIC under 32-bit EBX cannot be clobbered */
//	__asm__("movl %%ebx, %%edi \n\t cpuid \n\t xchgl %%ebx, %%edi" : "=D" (ebx),
//# else
//	__asm__("cpuid" : "+b" (ebx),
//# endif
//		"+a" (eax), "+c" (ecx), "=d" (edx));
//	abcd[0] = eax; abcd[1] = ebx; abcd[2] = ecx; abcd[3] = edx;
//#endif
//}
//
//int check_xcr0_ymm()
//{
//	uint32_t xcr0;
//#if defined(_MSC_VER)
//	xcr0 = (uint32_t)_xgetbv(0);  /* min VS2010 SP1 compiler is required */
//#else
//	__asm__("xgetbv" : "=a" (xcr0) : "c" (0) : "%edx");
//#endif
//	return ((xcr0 & 6) == 6); /* checking if xmm and ymm state are enabled in XCR0 */
//}
//
//int check_4th_gen_intel_core_features()
//{
//
//#if defined(_MSC_VER)
//	int32_t abcd[4];
//#else
//	uint32_t abcd[4];
//#endif
//
//	uint32_t fma_movbe_osxsave_mask = ((1 << 12) | (1 << 22) | (1 << 27));
//	uint32_t avx2_bmi12_mask = (1 << 5) | (1 << 3) | (1 << 8);
//
//	/* CPUID.(EAX=01H, ECX=0H):ECX.FMA[bit 12]==1   &&
//	CPUID.(EAX=01H, ECX=0H):ECX.MOVBE[bit 22]==1 &&
//	CPUID.(EAX=01H, ECX=0H):ECX.OSXSAVE[bit 27]==1 */
//	run_cpuid(1, 0, abcd);
//
//	if ((abcd[2] & fma_movbe_osxsave_mask) != fma_movbe_osxsave_mask)
//		return 0;
//
//	if (!check_xcr0_ymm())
//		return 0;
//
//	/*  CPUID.(EAX=07H, ECX=0H):EBX.AVX2[bit 5]==1  &&
//	CPUID.(EAX=07H, ECX=0H):EBX.BMI1[bit 3]==1  &&
//	CPUID.(EAX=07H, ECX=0H):EBX.BMI2[bit 8]==1  */
//	run_cpuid(7, 0, abcd);
//
//	if ((abcd[1] & avx2_bmi12_mask) != avx2_bmi12_mask)
//		return 0;
//
//	/* CPUID.(EAX=80000001H):ECX.LZCNT[bit 5]==1 */
//	run_cpuid(0x80000001, 0, abcd);
//
//	if ((abcd[2] & (1 << 5)) == 0)
//		return 0;
//
//	return 1;
//}
//#endif /* non-Intel compiler */
//
//static int can_use_intel_core_4th_gen_features()
//{
//	static int the_4th_gen_features_available = -1;
//
//	/* test is performed once */
//	if (the_4th_gen_features_available < 0)
//		the_4th_gen_features_available = check_4th_gen_intel_core_features();
//
//	return the_4th_gen_features_available;
//}
//
//#include <stdio.h>
//
//int main(int argc, char** argv) {
//	if (can_use_intel_core_4th_gen_features())
//		printf("This CPU supports ISA extensions introduced in Haswell\n");
//	else
//		printf("This CPU does not support all ISA extensions introduced in Haswell\n");
//
//	return 1;
//}


//-----------------------------------------------------------------------
//
//-----------------------------------------------------------------------
//#include <immintrin.h>
//#include <stdio.h>
//
//int main() {
//
//	int i;
//
//	int int_array[8] = { 100, 200, 300, 400, 500, 600, 700, 800 };
//
//	/* Initialize the mask vector */
//	__m256i mask = _mm256_setr_epi32(-20, -72, -48, -9, -100, 3, 5, 8);
//
//	/* Selectively load data into the vector */
//	__m256i result = _mm256_maskload_epi32(int_array, mask);
//
//	/* Display the elements of the result vector */
//	int* res = (int*)&result;
//	printf("%d %d %d %d %d %d %d %d\n",
//		res[0], res[1], res[2], res[3], res[4], res[5], res[6], res[7]);
//
//	return 0;
//}

//---------------------------------------------------------------------------
// Usage of _mm256_load_ps (AVX) lo load data from memory (must be ALIGNED)
//---------------------------------------------------------------------------
//#include <immintrin.h>
//#include <stdio.h>
//
//int main() {
//
//	float* data = (float*)_aligned_malloc(8 * sizeof(float), 32);
//	
//	data[0] = 0.f; 
//	data[1] = 1.f; 
//	data[2] = 2.f; 
//	data[3] = 3.f; 
//	data[4] = 4.f; 
//	data[5] = 5.f; 
//	data[6] = 6.f; 
//	data[7] = 7.f;
//
//	__m256 ymm0 = _mm256_load_ps(data); //vmovaps 
//
//	//float r0 = ymm0.m256_f32[0];
//	//float r4 = ymm0.m256_f32[4];
//
//	__m128 low  = _mm256_extractf128_ps(ymm0, 0); // extracts lower half
//	__m128 high = _mm256_extractf128_ps(ymm0, 1);// extracts upper half
//	float r0 = _mm_cvtss_f32(low);  // extracts lowest float
//	float r4 = _mm_cvtss_f32(high);  // extracts lowest float
//
//	printf("%f, %f\n", r0, r4);
//	system("pause");
//}

////-----------------------------------------------------------------------


//---------------------------------------------------------------------------
// Usage of _mm256_loadu_ps (AVX) lo load data from memory (does not need to be aligned )
//---------------------------------------------------------------------------
#include <immintrin.h>
#include <stdio.h>

int main() {


	float data[] = { 0.f, 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f };
	__m256 ymm0 = _mm256_loadu_ps(data);  // vmovups 

	//float r0 = ymm0.m256_f32[0];
	//float r4 = ymm0.m256_f32[4];

	__m128 low = _mm256_extractf128_ps(ymm0, 0); // extracts lower half
	__m128 high = _mm256_extractf128_ps(ymm0, 1);// extracts upper half
	float r0 = _mm_cvtss_f32(low);  // extracts lowest float
	float r4 = _mm_cvtss_f32(high);  // extracts lowest float

	printf("%f, %f\n", r0, r4);
	system("pause");
}

////-----------------------------------------------------------------------























////-----------------------------------------------------------------------
////-----------------------------------------------------------------------
////-----------------------------------------------------------------------



//#include <immintrin.h>
//
//#ifdef __cplusplus
//#include <cstdlib>
//#include <iostream>
//#else
//#include <stdio.h>
//#endif
//
//int main() {
//
//	int i;
//
//	int int_array[8] = { 100, 200, 300, 400, 500, 600, 700, 800 };
//
//	__m256i mask = _mm256_setr_epi32(-20, -72, -48, -9, -100, 3, 5, 8);
//	//__m256i mask = _mm256_set_epi32(8, 5, 3, -100, -9, -48, -72, -20);
//
//	__m256i result = _mm256_maskload_epi32(int_array, mask);
//
//	//int* res = (int*)&result;
//	//printf("%d %d %d %d %d %d %d %d\n", res[0], res[1], res[2], res[3], res[4], res[5], res[6], res[7]);
//
//	int* resMask = (int*)&mask;
//	printf("%d %d %d %d %d %d %d %d\n", resMask[0], resMask[1], resMask[2], resMask[3], resMask[4], resMask[5], resMask[6], resMask[7]);
//
//
//	//std::cin.get();
//	system("pause");
//
//	return 0;
//}