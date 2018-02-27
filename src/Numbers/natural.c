
int natural(char* word, int length){

    int tipoNumero = 0;
    int i=1;
    for(i;i<length;i++){
        if(word[i] == '.')
        {
            tipoNumero = real2(word, length, i);
            break;
        }
        else if(0<=(word[i]-'0')<=9)
        {
            tipoNumero = 1;
        }
        else
        {
            tipoNumero = 13;
            break;
        }
    }

    return tipoNumero;
}