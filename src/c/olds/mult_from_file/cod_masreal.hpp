#ifndef COD_MASREAL_HPP_
#define COD_MASREAL_HPP_

#include <cstdio>
#include <cstdlib>

// MAX uint64_t (20 chars in base10)
// 18446744073709551616

void mult_files_fscanf() {
    FILE* in = fopen("src_masreal.txt", "r");
    FILE* out = fopen("out_masreal.txt", "w");

    for (size_t i {0}; i < 1000000; ++i) {
        int uno, dos;
        fscanf(in, "%i %i\n", &uno, &dos);
        auto resultado = uno * dos;
        fprintf(out, "%i\n", resultado);
    }

    fclose(out);
    fclose(in);
}

#endif // COD_MASREAL_HPP_



