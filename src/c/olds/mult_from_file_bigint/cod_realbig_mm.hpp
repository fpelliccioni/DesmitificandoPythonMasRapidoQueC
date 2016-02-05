#ifndef COD_MASREAL_MM_HPP_
#define COD_MASREAL_MM_HPP_

//#include <cctype>
//#include <cstddef>

#include <boost/interprocess/file_mapping.hpp>
#include <boost/interprocess/mapped_region.hpp>

using namespace std;
using namespace boost::interprocess;

void mult_files_buffer() {

	file_mapping f_mapped("src_masreal.txt", read_only);
	mapped_region f_region(f_mapped, read_only);

	const char* buffer = (const char*)(f_region.get_address());
	const char* end = buffer + f_region.get_size();
	FILE* out = fopen("out_masreal.txt", "w");

	while (buffer != end) {
		int uno = atoi(buffer); 
		buffer += 6;
		int dos = atoi(buffer);
		buffer += 7;

		auto resultado = uno * dos;
		fprintf(out, "%i\n", resultado);
	}

	fclose(out);
}

#endif // COD_MASREAL_MM_HPP_



