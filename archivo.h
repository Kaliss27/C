/*TAREA 2
Biblioteca---Peralta Luna Karen Lisseth*/
#include <stdlib.h>
#include<stdio.h>
//ESTRUCTURAS
typedef struct elemento_lista1     /*ELEMENTO LISTA SIMPLE*/
{
	int dato;
	struct elemento_lista1 *sig;
}e_lista1;

typedef struct pila{              /*ELEMENTO PILA*/
	int dato;
	struct pila *sig;
}e_Pila;
/*
  FUNCIONES PARA LISTAS, PILAS Y COLAS
*/
//FUNCIONES LISTAS SIMPLES
int agregar_inicio(e_lista1 **inicio,int num)
{
	e_lista1 *newe=(e_lista1*)malloc(sizeof(e_lista1));
	if(!newe)
		return 0;
	newe->dato=num;
    newe->sig=(*inicio);
	(*inicio)=newe;
	return 1;
}
void ver_lista(e_lista1 *inicio)
{
	if(inicio){
		printf("|%i|",inicio->dato);
		ver_lista(inicio->sig);
	}
	return;
}
e_lista1* buscar_elemento_x(e_lista1 *actual,int d){
	if(actual && actual->dato==d)
		return actual;
	if(!actual)
		return NULL;
	buscar_elemento_x(actual->sig,d);
	
}
int eliminar_elemento_x(e_lista1 **inicio_l,int d,int bnd){
	if((*inicio_l) == NULL){
		if(bnd==0)
			return 0;
		return 1;
	}
	if ((*inicio_l)->dato == d){
		e_lista1 *aux = (*inicio_l);
		(*inicio_l) = (*inicio_l)->sig;
		free(aux); 
		bnd=1;
		if((*inicio_l) == NULL){
			return 1;
		}
    return eliminar_elemento_x(&(*inicio_l)->sig,d,bnd);
}
return eliminar_elemento_x(&(*inicio_l)->sig,d,bnd);
}
//FUNCIONES PILAS
int pila_vacia(e_Pila *pila)
{
	if(!pila)
		return 1;
	return 0;	 
}
e_Pila *crear_ePila()
{
	e_Pila *newe=(e_Pila*)malloc(sizeof(e_Pila));
	if(!newe)
		return NULL;
	return newe;

}
void push(e_Pila **pila,int d)
{
	e_Pila *newe=crear_ePila();
	newe->dato=d;
	newe->sig=(*pila);
	(*pila)=newe;
	return;
}
e_Pila *pop(e_Pila **tope)
{
	e_Pila *aux=(*tope);
	(*tope)=(*tope)->sig;
	return aux;
}
void ver_pila(e_Pila *tope)
{
	if(tope)
	{
		printf("%i\n",tope->dato);
		ver_pila(tope->sig);
	}
	return;
}
