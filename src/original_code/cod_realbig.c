#include <stdio.h>
#include <openssl/bn.h>
#include <openssl/crypto.h>

int main(void) {
    FILE *in, *out;
    BIGNUM *uno=NULL, *dos=NULL, *resultado;
    int i;
    BN_CTX *bnctx;
    char line[70], *num, *p;
    bnctx = BN_CTX_new();
    BN_CTX_init( bnctx );
    resultado = BN_new( );
    uno = BN_new();
    dos = BN_new();
    in = fopen("src_realbig.txt", "r");
    out = fopen("out_realbig.txt", "w");
    
    for (i = 0; i < 1000000 ; i++ ) {
        fread(line, 1, 66, in);
        line[32]=0;
        p = line;
        while (*p == ' ') p++;
        BN_dec2bn( &uno, p );
        line[66]=0;
        p = line+34;
        while (*p == ' ') p++;
        BN_dec2bn( &dos, p );        
        BN_mul( resultado, uno, dos, bnctx);
        num = BN_bn2dec( resultado );
        fprintf(out, "%s\n", num);
    }
    fclose(in);
    fclose(out);
}
