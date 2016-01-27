////#include <boost/interprocess/file_mapping.hpp>
////#include <boost/interprocess/mapped_region.hpp>
////#include <iostream>
////#include <fstream>
////#include <string>
////#include <vector>
////#include <cstring>
////#include <cstddef>
////#include <cstdlib>
////
////int main(int argc, char *argv[])
////{
////	using namespace boost::interprocess;
////
////	//Define file names
////	const char *FileName = "file.bin";
////	const std::size_t FileSize = 60651 * 1024; // 10000;
////
////	{  //Create a file
////		file_mapping::remove(FileName);
////		std::filebuf fbuf;
////		fbuf.open(FileName, std::ios_base::in | std::ios_base::out
////			| std::ios_base::trunc | std::ios_base::binary);
////		//Set the size
////		fbuf.pubseekoff(FileSize - 1, std::ios_base::beg);
////		fbuf.sputc(0);
////	}
////
////	////Remove on exit
////	//struct file_remove
////	//{
////	//	file_remove(const char *FileName)
////	//		: FileName_(FileName) {}
////	//	~file_remove() { file_mapping::remove(FileName_); }
////	//	const char *FileName_;
////	//} remover(FileName);
////
////	//Create a file mapping
////	file_mapping m_file(FileName, read_write);
////
////	//Map the whole file with read-write permissions in this process
////	mapped_region region(m_file, read_write);
////
////	//Get the address of the mapped region
////	void * addr = region.get_address();
////	std::size_t size = region.get_size();
////
////	//Write all the memory to 1
////	std::memset(addr, 1, size);
////
////
////
////	return 0;
////}
//
////-----------------------------------------
//
////#include <boost/iostreams/device/mapped_file.hpp>
////#include <boost/iostreams/stream.hpp>
////#include <vector>
////
////namespace bio = boost::iostreams;
////
////int main() {
////	using namespace std;
////	vector<string> strArray(2000000);
////
////	bio::mapped_file_params params;
////	params.path = "text.txt";
////	params.new_file_size = 30ul << 30;
////	params.flags = bio::mapped_file::mapmode::readwrite;
////
////	bio::stream<bio::mapped_file_sink> out(params);
////
////	copy(strArray.begin(), strArray.end(), ostream_iterator<string>(out, "\n"));
////}
//
////-----------------------------------------
//
//
//// Clang: clang++ -O3 -std=c++1y cod_masreal.cpp
//// GCC:   g++ -Wall -Wextra -pedantic -O3 -std=c++1y cod_masreal.cpp
//// MSVC:  
//
//#include "cod_realbig.hpp"
//#include <iostream>
//
//using namespace std;
//
//int main(int /*argc*/, char const * /*argv*/[]) {
//
//	//mult_files_big_buffer_with_copy();
//	mult_files_big_buffer_without_copy();
//
//	return 0;
//}
