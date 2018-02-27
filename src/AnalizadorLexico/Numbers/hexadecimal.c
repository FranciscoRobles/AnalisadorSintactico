
int hex(char c, int estado){
	int nuevoEstado = 0;
	if((48<=(int)c && (int)c<=57) || (65<=(int)c && (int)c<=70) || (97<=(int)c && (int)c<=102))
	{
		nuevoEstado = 116;
	}
	else
	{
		nuevoEstado = -1;
	}
	return nuevoEstado;
}
