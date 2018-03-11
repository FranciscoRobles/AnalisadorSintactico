/*
31 = '('
32 = ')'
33 = '['
34 = ']'
*/

int tipoDelimitacion(char c, int estado){
	int nuevoEstado = 0;
	switch(estado){
		case 0:
			if(c == '(')
			{
				nuevoEstado = 31;
			}
			else if(c == ')')
			{
				nuevoEstado = 32;
			}
			else if(c == '[')
			{
				nuevoEstado = 33;
			}
			else
			{
				nuevoEstado = 34;
			}
			break;
	}
	return nuevoEstado;
}