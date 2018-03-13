#include <stdio.h>
#include <stdlib.h>
#include "AnalizadorLexico/analizadorLexico.h"
#include "AnalizadorLexico/analizadorLexico.c"

int posicion = 0;
tokensArray t;

typedef struct node{
	int data;
	struct node* next;
} node;

node* root;

typedef void (*callback)(node* data);
/*
	create a new node
	initialize the data and next field

	return the newly created node
*/
node* create(int data,node* next){
	node* new_node = (node*)malloc(sizeof(node));
	if(new_node == NULL)
	{
		printf("Error creating a new node.\n");
		exit(0);
	}
	new_node->data = data;
	new_node->next = next;

	return new_node;
}

/*
	add a new node at the end of the list
*/
node* append(node* head, int data){
	if(head == NULL)
		return NULL;
	/* go to the last node */
	node *cursor = head;
	while(cursor->next != NULL)
		cursor = cursor->next;

	/* create a new node */
	node* new_node =  create(data,NULL);
	cursor->next = new_node;

	return head;
}

/*
	remove node from the back of the list
*/
node* remove_back(node* head){
	if(head == NULL)
		return NULL;

	node *cursor = head;
	node *back = NULL;
	while(cursor->next != NULL)
	{
		back = cursor;
		cursor = cursor->next;
	}

	if(back != NULL)
		back->next = NULL;

	/* if this is the last node in the list*/
	if(cursor == head)
		head = NULL;

	free(cursor);

	return head;
}

/*
	remove all element of the list
*/
void dispose(node *head){
	node *cursor, *tmp;
	if(head != NULL)
	{
		cursor = head->next;
		head->next = NULL;
		while(cursor != NULL)
		{
			tmp = cursor->next;
			free(cursor);
			cursor = tmp;
		}
	}
	printf("Eliminación completa.\n");
}

/*
    display a node
*/
void display(node* n)
{
    if(n != NULL)
        printf("%d\n", n->data);
	else
	{
		printf("no existe\n");
	}
}

/*
programa = 0;
secuenciaSent = 1;
sentencia = 2;
sentIf = 3;
sentRepeat = 4;
sentAssign = 5;
sentRead = 6;
sentWrite = 7;
expr = 8;
opComparacion = 9;
expSimple = 10;
opSuma = 11;
term = 12;
opMult = 13;
factor = 14;

print de debug: printf("x %d - %d", t.tk[posicion], posicion);
*/

int factor(){
	printf("Factor - 14 (%d)\n", posicion);
	if(t.tk[posicion] == 31)
	{
		printf("'(' - 31 (%d)\n", posicion);
		posicion++;
		if(expr()!=1)
		{
			return -1;
		}
		if(t.tk[posicion] == 32)
		{
			printf("')' - 32 (%d)\n", posicion);
			posicion++;
			return 1;
		}
		else
		{
			return -1;
		}
	}
	else if(t.tk[posicion] == 15)
	{
		printf("Numero - 15 (%d)\n", posicion);
		posicion++;
		return 1;
	}
	else if(t.tk[posicion] == 20)
	{
		printf("Identificador - 20 (%d)\n", posicion);
		posicion++;
		return 1;
	}
	return -1;
}

int opMult(){
	if((t.tk[posicion] != 43 && t.tk[posicion] != 44) || posicion >= 99)
	{
		return -1;
	}
	else
	{
		printf("OpMult - 13 (%d)\n", posicion);
		if(t.tk[posicion] == 43)
		{
			printf("'*' - 43 (%d)\n", posicion);
		}
		if(t.tk[posicion] == 44)
		{
			printf("'/' - 44 (%d)\n", posicion);
		}
	}
	return 1;
}

int term(){
	printf("Term - 12 (%d)\n", posicion);
	if(factor()!=1)
	{
		return -1;
	}
	if(opMult() == 1)
	{
		posicion++;
		if(factor() != -1)
		{
			return -1;
		}
	}
	return 1;
}

int opSuma(){
	if((t.tk[posicion] != 41 && t.tk[posicion] != 42) || posicion >= 99)
	{
		return -1;
	}
	else
	{
		printf("OpSuma - 11 (%d)\n", posicion);
		if(t.tk[posicion] == 41)
		{
			printf("'+' - 41 (%d)\n", posicion);
		}
		if(t.tk[posicion] == 42)
		{
			printf("'-' - 42 (%d)\n", posicion);
		}
	}
	return 1;
}

int expSimple(){
	printf("ExpSimple - 10 (%d)\n", posicion);
	if(term()!=1)
	{
		return -1;
	}
	if(opSuma() == 1)
	{
		posicion++;
		if(term() != 1)
		{
			return -1;
		}
	}
	return 1;
}

int opComparacion(){
	if((t.tk[posicion] != 51 && t.tk[posicion] != 53) || posicion >= 99)
	{
		return -1;
	}
	else
	{
		printf("OpComparacion - 9 (%d)\n", posicion);
		if(t.tk[posicion] == 51)
		{
			printf("'=' - 51 (%d)\n", posicion);
		}
		if(t.tk[posicion] == 53)
		{
			printf("'<' - 53 (%d)\n", posicion);
		}
	}
	return 1;
}

int expr(){
	printf("Expr - 8 (%d)\n", posicion);
	if(expSimple()!=1)
	{
		return -1;
	}
	if(opComparacion() == 1)
	{
		posicion++;
		if(expSimple() != 1)
		{
			return -1;
		}
	}
	return 1;
}

int sentWrite(){
	if(t.tk[posicion] != 28 || posicion >= 99)
	{
		return -1;
	}
	printf("Sent Write - 7 (%d)\n", posicion);
	printf("Write - 28 (%d)\n", posicion);
	posicion++;
	if(expr()!=1)
	{
		return -1;
	}
	return 1;
}

int sentRead(){
	if(t.tk[posicion] != 27 || posicion >= 99)
	{
		return -1;
	}
	printf("Sent Read - 6 (%d)\n", posicion);
	printf("Read - 27 (%d)\n", posicion);
	posicion++;
	if(t.tk[posicion] != 20 || posicion >= 90)
	{
		return -1;
	}
	printf("Identificador - 20 (%d)\n", posicion);
	posicion++;
	return 1;
}

int sentAssign(){
	if(t.tk[posicion] != 20 || posicion >= 99)
	{
		return -1;
	}
	printf("Sent Assign- 5 (%d)\n", posicion);
	printf("Identificador - 20 (%d)\n", posicion);
	posicion++;
	if(t.tk[posicion] != 64 || posicion >= 99)
	{
		return -1;
	}
	printf("':' - 64 (%d)\n", posicion);
	posicion++;
	if(t.tk[posicion] != 51 || posicion >= 99)
	{
		return -1;
	}
	printf("'=' - 51 (%d)\n", posicion);
	posicion++;
	if(expr() != 1)
	{
		return -1;
	}
	return 1;
}

int sentRepeat(){
	if(t.tk[posicion] != 25 || posicion >= 99)
	{
		return -1;
	}
	printf("Sent Repeat - 4 (%d)\n", posicion);
	printf("Repeat - 25 (%d)\n", posicion);
	posicion++;
	if(secuenciaSent()!=1)
	{
		return -1;
	}
	if(t.tk[posicion] != 26|| posicion >= 99)
	{
		return -1;
	}
	printf("Until - 26 (%d)\n", posicion);
	posicion++;
	if(expr()!=1)
	{
		return -1;
	}
	return 1;
}

int sentIf(){
	if(t.tk[posicion] != 21 || posicion >= 99)
	{
		return -1;
	}
	printf("Sent If - 3 (%d)\n", posicion);
	printf("If - 21 (%d)\n", posicion);
	posicion++;
	if(expr()!=1)
	{
		return -1;
	}
	if(t.tk[posicion] != 22 || posicion >= 99)
	{
		return -1;
	}
	printf("Then - 22 (%d)\n", posicion);
	posicion++;
	if(secuenciaSent()!=1)
	{
		return -1;
	}
	if(t.tk[posicion] == 23)
	{
		printf("Else - 23 (%d)\n", posicion);
		posicion++;
		if(secuenciaSent() != 1)
		{
			return -1;
		}
		if(t.tk[posicion] != 24 || posicion >= 99)
		{
			return -1;
		}
	}
	else
	{
		if(t.tk[posicion] != 24 || posicion >= 99)
		{
			return -1;
		}
	}
	printf("End - 24 (%d)\n", posicion);
	return 1;
}

int sentencia(){
	printf("Sentencia - 2 (%d)\n", posicion);
	if(sentIf() == 1)
	{
		return 1;
	}
	else if(sentRepeat() == 1)
	{
		return 1;
	}
	else if(sentAssign() == 1)
	{
		return 1;
	}
	else if(sentRead() == 1)
	{
		return 1;
	}
	else if(sentWrite() == 1)
	{
		return 1;
	}
	return -1;
}

int secuenciaSent(){
	printf("Secuencia Sent - 1 (%d)\n", posicion);
	if(sentencia()!=1)
	{
		return -1;
	}
	while(posicion>=99 || t.tk[posicion] == 63){
		printf("';' - 63 (%d)\n", posicion);
		posicion++;
		if(sentencia()!=1)
		{
			return -1;
		}
	}
	return 1;
}

int programa(){
	printf("Programa - 0 (%d)\n", posicion);
	return secuenciaSent();
}

int main(){
	extern tokensArray t;
	token();
	/*for(int i = 0; i< 50;i++)
	{
		printf("%d: %d\n", i, t.tk[i]);
	}*/
	if(programa() == 1)
	{
		printf("Genial! No hubo errores sintácticos\n");
	}
	else
	{
		printf("Hubo un error sintáctico\n");
	}
	dispose(root);
	return 0;
}

