#include <stdio.h>
#include <stdlib.h>
#include "numeros.c"
#include "relacion.c"
#include "delimitacion.c"
#include "aritmetico.c"
#include "puntuacion.c"

FILE *inicio, *avance;
char palabra[100];
int linea = 1;
int ident = 1;

/*
Estados:
error = -1, 57, 106, 111, 113, or ident = -1
comentarios = 100
*/

void aceptar(){
	long inicioPalabra = ftell(inicio);
	long finPalabra = ftell(avance);

	fread(palabra, finPalabra - inicioPalabra, 1, inicio);

	fseek(inicio, finPalabra, SEEK_SET);
}

void rechazar(){
	fseek(avance, ftell(inicio), SEEK_SET);
}

char obtenerCaracter(){
	return fgetc(avance);
}

int isfeof(){
	char c = obtenerCaracter();
	rechazar();
	return c == EOF;
}

int identificar(){
	int estado = 0;
	char c = obtenerCaracter();
	if(c == '/' && estado != -1)
	{
		estado = 44;
		c = obtenerCaracter();
		if( c == '/')
		{
			c = obtenerCaracter();
			while(c!= '\n'){
				c = obtenerCaracter();
				estado = 100;
			}
		}
		else if(c == ' ' || c == '\n' || c =='\t')
		{
			estado = 44;
		}
		else
		{
			return estado = -1;
		}
	}
	else
	{
		while(c != ' ' && c != '\n' && c != '\t' && c != EOF && estado != -1){
			if(48<=(int)c && (int)c<=57)
			{
				if(estado == 20)
				{
					estado = 20;
				}
				else
				{
					estado = tipoNumero(c, estado);
				}
			}
			else if((65 <= (int)c && (int)c <= 90) || (97<= (int)c && (int)c <=122) || c=='_')
			{
				if(estado!=20 && estado != 0)
				{
					estado = tipoNumero(c, estado);
				}
				else if(estado == 0 || estado == 20)
				{
					if(c=='_' && estado == 0)
					{
						ident = -1;
						estado = 20;
					}
					else
					{
						ident = 1;
						estado = 20;
					}
				}
			}
			else if(c == '.' || c == ',' || c == ';' || c == ':')
			{
				if((estado == 10 || estado == 11)&& c == '.')
				{
					estado = tipoNumero(c, estado);
				}
				else if((c==','||c==';')&&(estado==11||estado==108||estado==112||estado==114||estado==115||estado==116))
				{
					estado = estado;
					break;
				}
				else if(estado == 0)
				{
					estado = tipoPuntuacion(c, estado);
					break;
				}
				else if(estado == 20)
				{
					estado = 20;
					break;
				}
				else
				{
					estado = -1;
				}
			}
			else if(c == '+' || c == '-' || c == '*' || c=='/')
			{
				if(estado == 113)
				{
					estado = tipoNumero(c, estado);
				}
				else if(estado == 0)
				{
					estado = tipoAritmetico(c,estado);
				}
				else
				{
					estado = -1;
				}
			}
			else if(c == '=' || c == '<' || c == '>' || c == '!')
			{
				if(estado == 0 || estado == 51 || estado == 53 || estado == 55 || estado == 57)
				{
					estado = tipoRelacion(c, estado);
				}
				else
				{
					estado = -1;
				}
			}
			else if(c == '(' || c == ')' || c == '[' || c == ']')
			{
				if(estado == 0)
				{
					estado = tipoDelimitacion(c, estado);
					break;
				}
				else if(estado == 20)
				{
					estado = 20;
					break;
				}
				else
				{
					estado = -1;
				}
			}
			c = obtenerCaracter();
		}
	}
	if(c == '\n')
	{
		linea = linea+1;
	}
	return estado;
}

void token(){
	int posicion = 0;
	inicio = fopen("AnalizadorLexico/lectura.txt", "r");
	avance = fopen("AnalizadorLexico/lectura.txt", "r");
	extern tokensArray t;
	t.tk[0] = 1;
	int estadoFinal = 0;
	while(!isfeof()){
		estadoFinal = identificar();
		if((estadoFinal != -1 && estadoFinal != 57 && estadoFinal != 106 && estadoFinal != 111 && estadoFinal != 113) && ident != -1)
		{
			if(estadoFinal != 100)
			{
				aceptar();
				if(estadoFinal == 20){
					if(palabra[0]=='i'&& palabra[1]=='f'&& (palabra[2]==' '||palabra[2]=='\n'||palabra[2]=='\t'||palabra[2] == (char)0))
					{
						estadoFinal = 21;
					}
					else if(palabra[0]=='t'&& palabra[1]=='h'&& palabra[2]=='e'&& palabra[3]=='n'&& (palabra[4]==' '||palabra[4]=='\n'||palabra[4]=='\t'||palabra[4] == (char)0))
					{
						estadoFinal = 22;
					}
					else if(palabra[0]=='e'&& palabra[1]=='l'&& palabra[2]=='s'&& palabra[3]=='e'&& (palabra[4]==' '||palabra[4]=='\n'||palabra[4]=='\t'||palabra[4] == (char)0))
					{
						estadoFinal = 23;
					}
					else if(palabra[0]=='e'&& palabra[1]=='n'&& palabra[2]=='d'&& (palabra[3]==' '||palabra[3]=='\n'||palabra[3]=='\t'||palabra[3] == (char)0))
					{
						estadoFinal = 24;
					}
					else if(palabra[0]=='r'&& palabra[1]=='e'&& palabra[2]=='p'&& palabra[3]=='e'&& palabra[4]=='a'&& palabra[5]=='t'&& (palabra[6]==' '||palabra[6]=='\n'||palabra[6]=='\t'||palabra[6]==(char)0))
					{
						estadoFinal = 25;
					}
					else if(palabra[0]=='u'&& palabra[1]=='n'&& palabra[2]=='t'&& palabra[3]=='i'&& palabra[4]=='l'&& (palabra[5]==' '||palabra[5]=='\n'||palabra[5]=='\t'||palabra[5]==(char)0))
					{
						estadoFinal = 26;
					}
					else if(palabra[0]=='r'&& palabra[1]=='e'&& palabra[2]=='a'&& palabra[3]=='d'&& (palabra[4]==' '||palabra[4]=='\n'||palabra[4]=='\t'||palabra[4]==(char)0))
					{
						estadoFinal = 27;
					}
					else if(palabra[0]=='w'&& palabra[1]=='r'&& palabra[2]=='i'&& palabra[3]=='t'&& palabra[4]=='e'&& (palabra[5]==' '||palabra[5]=='\n'||palabra[5]=='\t'||palabra[5]==(char)0))
					{
						estadoFinal = 28;
					}
					else
					{
						estadoFinal = 20;
					}
				}
				if(estadoFinal == 11 || estadoFinal == 108 || estadoFinal == 112 || estadoFinal == 114 || estadoFinal == 115 || estadoFinal ==116){
				estadoFinal = 10;
				}
				for(int i = 0;i<100;i++){
					palabra[i] = (char)0;
				}
				t.tk[posicion] = estadoFinal;
				posicion++;
			}
			aceptar();
				for(int i = 0;i<100;i++){
				palabra[i] = (char)0;
			}
		}
		else
		{
			rechazar();
			printf("Error en el input! (Línea %d)\n", linea);
			break;
		}
	}
	fclose(inicio);
	fclose(avance);
}