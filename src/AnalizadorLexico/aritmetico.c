/*
41 = '+'
42 = '-'
43 = '*'
44 = '/'
*/

int tipoAritmetico(char c, int estado){
    int nuevoEstado = 0;
    switch(estado){
        case 0:
            if(c=='+')
            {
                nuevoEstado = 41;
            }
            else if(c=='-')
            {
                nuevoEstado = 42;
            }
            else if(c=='*')
            {
                nuevoEstado = 43;
            }
            else
            {
                nuevoEstado = 44;
            }
            break;
    }
    return nuevoEstado;
}