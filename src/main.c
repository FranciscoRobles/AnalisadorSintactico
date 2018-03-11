#include <stdio.h>
#include <stdlib.h>
#include "AnalizadorLexico/analizadorLexico.h"
#include "AnalizadorLexico/analizadorLexico.c"

int value;
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

*/

int programa(){
	root = create(0, NULL);
	return 1;
}

int secuenciaSent(){
	root = append(root, 1);
	return 1;
}

int sentencia(){
	root = append(root, 2);
	return 1;
}

int sentIf(){
	root = append(root, 4);
	return 1;
}

int main(){
	int estado = programa();
	estado = secuenciaSent();
	estado = sentencia();
	extern tokensArray t;
	printf("%d\n", t.tk[0]);
	token();
	printf("%d\n", t.tk[0]);
	printf("%d\n", t.tk[1]);
	printf("%d\n", t.tk[2]);
	dispose(root);
	return 0;
}

