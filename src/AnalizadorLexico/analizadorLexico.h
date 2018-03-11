#ifndef __ANALIZADORLEXICOH__
#define __ANALIZADORLEXICOH__
typedef struct tokensArray{
    int tk[100];
} tokensArray;
void token();
void acepta();
void rechazar();
char obtenerCaracter();
int isfeof();
int identificar();
#endif