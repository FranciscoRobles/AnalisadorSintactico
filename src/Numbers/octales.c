
int octal(char c, int estado){
	int nuevoEstado = 0;
	if((48<= (int)c) && ((int)c<=55))
	{
		nuevoEstado = 108;
	}
	else
	{
		nuevoEstado = -1;
	}
	return nuevoEstado;
}
