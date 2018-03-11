/*
51 = '='
52 = '=='
53 = '<'
54 = '<='
55 = '>'
56 = '>='
57 = '!'
58 = '!='
*/
int tipoRelacion(char c, int estado){
	int nuevoEstado = 0;
	switch(estado)
	{
		case 0:
			if(c == '=')
			{
				nuevoEstado = 51;
			}
			else if(c == '<')
			{
				nuevoEstado = 53;
			}
			else if(c == '>')
			{
				nuevoEstado = 55;
			}
			else
			{
				nuevoEstado = 57;
			}
			break;
		case 51:
			if(c == '=')
			{
				nuevoEstado = 52;
			}
			else
			{
				nuevoEstado = -1;
			}
			break;
		case 53:
			if(c == '=')
			{
				nuevoEstado = 54;
			}
			else
			{
				nuevoEstado = -1;
			}
			break;
		case 55:
			if(c == '=')
			{
				nuevoEstado = 56;
			}
			else
			{
				nuevoEstado = -1;
			}
			break;
		case 57:
			if(c == '=')
			{
				nuevoEstado = 58;
			}
			else
			{
				nuevoEstado = -1;
			}
			break;
	}
	return nuevoEstado;
}