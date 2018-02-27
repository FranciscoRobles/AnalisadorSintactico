#include "Numbers/hexadecimal.c"
#include "Numbers/hexadecimal.h"
#include "Numbers/octales.c"
#include "Numbers/octales.h"
#include "Numbers/reales.c"
#include "Numbers/reales.h"

/*
10 = '0' (octal porque es el único que empieza con 0)
11 = natural
108 = octal
112 = real
114 = real con exponente
115 = real con exponente y signo
116 = hexadecimal
*/

int tipoNumero(char c, int estado){
	int nuevoEstado = 0;
	switch (estado){
        case 0:
			if(c == '0')
			{
				nuevoEstado = 10;
			}
			else
			{
				nuevoEstado = 11;
			}
			break;
		case 10:
			if(c == '.')
			{
				nuevoEstado = 112;
			}
			else if(c == 'x' || c == 'X')
			{
				nuevoEstado = 106;
			}
			else if(48 <= (int)c && (int)c <= 55)
			{
				nuevoEstado = 108;
			}
			else
			{
				nuevoEstado = -1;
			}
			break;
		case 11:
			if(c == '.')
			{
				nuevoEstado = 112;
			}
			else if(48 <= (int)c && (int)c <= 57)
			{
				nuevoEstado = 11;
			}
			else
			{
				nuevoEstado = -1;
			}
			break;
		case 106:
			nuevoEstado = hex(c, estado);
			break;
		case 108:
			nuevoEstado = octal(c, estado);
			break;
		case 111:	//estado intermedio de punto '1.'
			nuevoEstado = primerReal(c, estado);
		case 112:
			nuevoEstado = siguienteReal(c, estado);
			break;
		case 113:	//estado intermedio de exponente '1.2e'
			nuevoEstado = realExponente(c, estado);
			break;
		case 114:
			nuevoEstado = realExponente(c, estado);
			break;
		case 115:
			nuevoEstado = realExponenteConSigno(c, estado);
			break;
		case 116:
			nuevoEstado = hex(c, estado);
			break;
	}
    return nuevoEstado;
}