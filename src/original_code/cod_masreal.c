/* 
un error bobo (uno/in, dos/out)
otro error bobo, no se comenta con # :)
tiempo de codeo 10 minutos
- checkeo de manpage de fscanf y fopen
*/
#include "stdio.h"

int main(void) {
    FILE *in, *out;
    int uno, dos, resultado, i;
    
    in = fopen("src_masreal.txt", "r");
    out = fopen("out_masreal.txt", "w");
    for (i = 0; i < 1000000 ; i++ ) {
        fscanf(in, "%i %i\n", &uno, &dos);
        resultado = uno * dos;
        fprintf(out, "%i\n", resultado);
    }
    fclose(in);
    fclose(out);
}
