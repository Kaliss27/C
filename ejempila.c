#include "stdio.h"
#include "stdlib.h"

struct elemPila
{
	int dato;
	struct elemPila * sig;	/* data */
};
/************************
Funcion push: permite introducir un elemento a la pila
Parametros:
	dato: entero, informacion  que debe guardar un elemPila
	tope: struct elemPila , pila donde se va a almacenar el dato
Return:
	0: si no se pudo guardar el dato
	1: si se guardo con exito
**************************/
int push(int dato, struct elemPila ** tope)
{
	struct elemPila *nuevo = (struct elemPila*) malloc(sizeof(struct elemPila));
	if (!nuevo)
	{   //no se pudo reservar memoria
		return 0;
	}
	nuevo->dato = dato;
	nuevo->sig = (*tope);
	*tope = nuevo;
	return 1;
}

struct elemPila * pop(struct elemPila **tope)
{
	if (!(*tope))//pila vacía
		return NULL;
	
	struct elemPila *aux = (*tope); // el primer elemento 

	*tope = (*tope)->sig; // la pila solo estara constituida por el resto de los elementos 

	return aux; 
}

struct elemPila * buscar(int dato, struct elemPila** tope)
{
	struct elemPila * aux = pop(tope);
	if (!aux)
		return NULL;
	else
	{
		if (aux->dato == dato)
			return aux;
	}
	return buscar(dato,tope);
}



int main(int argc, char const *argv[])
{
	struct elemPila * tope=NULL;
	struct elemPila * tope2=NULL;
	struct elemPila * aux=NULL;

	push(7, &tope);
	push(4, &tope);
	push(27, &tope);
	push(9, &tope);

	/*
	aux = pop(&tope); //sacando al 9
	push (aux->dato, &tope2);
	printf("%i\n",aux->dato);
	aux = pop(&tope); //sacando al 27
	push (aux->dato, &tope2);
	printf("%i\n",aux->dato);
	aux = pop(&tope); //sacando al 4
	push (aux->dato, &tope2);
	printf("%i\n",aux->dato);
	aux = pop(&tope); //sacando al 7
	push (aux->dato, &tope2);
	printf("%i\n",aux->dato);
	*/
	while((aux = pop(&tope)))
	{
		push (aux->dato, &tope2);
		printf("%i\n",aux->dato);
		free(aux);
	}






	return 0;
}
