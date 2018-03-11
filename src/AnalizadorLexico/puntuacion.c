/*
61 = '.'
62 = ','
63 = ';'
64  = ':'
*/

int tipoPuntuacion(char c, int estado){
	int nuevoEstado = 0;
	switch(estado){
		case 0:
			if(c == '.')
			{
				nuevoEstado = 61;
			}
			else if(c == ',')
			{
				nuevoEstado = 62;
			}
			else if (c == ';')
			{
				nuevoEstado = 63;
			}
			else
			{
				nuevoEstado = 64;
			}
			break;
	}
	return nuevoEstado;
}