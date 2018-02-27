
int realExponenteConSigno(char c, int estado){
	int nuevoEstado = 0;
	if(48<=(int)c && (int)c<=57)
	{
		nuevoEstado = 115;
	}
	else
	{
		nuevoEstado = -1;
	}
	return nuevoEstado;
}

int realExponente(char c, int estado){
	int nuevoEstado = 0;
	if(48<= (int)c && (int)c<=57)
	{
		nuevoEstado = 114;
	}
	else if(c == '+' || c == '-')
	{
		nuevoEstado = 115;
	}
	else
	{
		nuevoEstado = -1;
	}
	return nuevoEstado;
}

int siguienteReal(char c, int estado){
	int nuevoEstado = 0;
	if(48<= (int)c && (int)c<=57)
	{
		nuevoEstado = 112;
	}
	else if(c == 'e' || c == 'E')
	{
		nuevoEstado = 113;
	}
	else
	{
		nuevoEstado = -1;
	}
	return nuevoEstado;
}

int primerReal(char c, int estado){
	int nuevoEstado = 0;
	if((48<= (int)c) && ((int)c<=57)){
		nuevoEstado = 112;
	}
	else
	{
		nuevoEstado = -1;
	}
	return nuevoEstado;
}