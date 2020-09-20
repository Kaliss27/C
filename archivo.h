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

typedef struct elemento_cola
{
	int dato;                        /*ELEMENTO COLA SIMPLE*/
	struct elemento_cola *sig;
}e_Cola;

typedef struct Cola
{
	e_Cola *frente;                  /*COLA*/
	e_Cola *final;
}p_Cola;
/*
  FUNCIONES PARA LISTAS, PILAS Y COLAS
*/
//FUNCIONES LISTAS SIMPLES
/*Agrega un elemento al inicio de la lista
** e_lista1 **inicio: Doble apuntador para modificar el * de inicio de la lista
** int num :Entero que se almacenara en el elemento lista
** retorna 1 si se logro agregar, y 0 si existio algun problema    
*/
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
/*Visualiza todos los elementos de una lista
** e_lista1 *inicio: Apuntador que indica el inicio de la lista, con el cual se hara
** el recorrido de forma recursiva   
*/
void ver_lista(e_lista1 *inicio)
{
	if(inicio){
		printf("|%i|",inicio->dato);
		ver_lista(inicio->sig);
	}
	return;
}
/*Busca un elemento en especifico de la lista
** e_lista1 *inicio: Apuntador que indica el inicio de la lista, con el cual se hara
** el recorrido de forma recursiva   
** int d :Entero que se buscara
** devuelve la posiciòn en memoria de la estructura que almacena a el numero buscado
*/
e_lista1* buscar_elemento_x(e_lista1 *actual,int d){
	if(actual && actual->dato==d)
		return actual;
	if(!actual)
		return NULL;
	buscar_elemento_x(actual->sig,d);
	
}
/*Elimina un elemento de la lista
** e_lista1 **inicio: Doble apuntador para modificar el * de inicio de la lista
** int d :Entero que determinara el elemento a eliminar de la lista
** int bnd: variable que permite determinar si se realizo la operacion (1) o no (0) 
*/
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
/*Determina si una pila esta vacia o no
** e_Pila *pila: Apuntador que permite recorrer la pila
   retorna un entero que indica si esta vacia la pila (1) o no (0)
*/
int pila_vacia(e_Pila *pila)
{
	if(!pila)
		return 1;
	return 0;	 
}
/* Asigna el espacio en memoria del nuevo elemento Pila
** retorna el puntero creado, o NULL si existiese algun problema al reservar memoria
*/
e_Pila *crear_ePila()
{
	e_Pila *newe=(e_Pila*)malloc(sizeof(e_Pila));
	if(!newe)
		return NULL;
	return newe;

}
/* Agrega un nuevo elemento a la pila y determina el nuevo tope de esta
** e_Pila **pila: Doble apuntador para modificar la pila
** int d: dato a almacenar en el nuevo elemento pila
*/
void push(e_Pila **pila,int d)
{
	e_Pila *newe=crear_ePila();
	newe->dato=d;
	newe->sig=(*pila);
	(*pila)=newe;
	return;
}
/* Saca el elemento ubicado en la cima de la pila y determina el nuevo tope de esta
** e_Pila **tope: Doble apuntador para modificar la pila
** retorna el puntero del elemento retirado de la pila
*/
e_Pila *pop(e_Pila **tope)
{
	e_Pila *aux=(*tope);
	(*tope)=(*tope)->sig;
	return aux;
}
/* Visualiza todos los elementos de la pila
** e_Pila *tope: apuntador que permite recorrer la pila
*/
void ver_pila(e_Pila *tope)
{
	if(tope)
	{
		printf("%i\n",tope->dato);
		ver_pila(tope->sig);
	}
	return;
}
//FUNCIONES COLAS SIMPLES
/* Inserta un nuevo elemento a la cola
** p_Cola **cola: Doble puntero para modificar los apuntadores frente y final de la cola
** int d: numero a almacenar en el nuevo elemento cola
** retorna 1 si se llevo a cabo la insercion
*/
int insertar_elemento(p_Cola **cola,int d)
{
	e_Cola *newe=crear_elemento();
	newe->dato=d;
	newe->sig=NULL;
	if(cola_vacia((*cola))==1)
	{
		(*cola)->frente=newe;
		(*cola)->final=newe;
		return 1;
	}else
	{
		(*cola)->final->sig=newe;
		(*cola)->final=newe;
		return 1;
	}
}
/*Crea el espacio en memoria del nuevo elemento cola
** devuelve el puntero creado, o NULL si existiese algun problema al reservar memoria
*/
e_Cola *crear_elemento()
{
	e_Cola *newe=(e_Cola*)malloc(sizeof(e_Cola));
	if(!newe)
		return NULL;
	return newe;
}
int cola_vacia(p_Cola *cola)
{
	if(!(cola->frente) && !(cola->final))
		return 1;
	return 0;
}
void crear_cola(p_Cola **cola)
{
	(*cola)->frente=NULL;
	(*cola)->final=NULL;
	return;
}
void ver_cola(e_Cola *cola)
{
	if(cola)
	{
		printf("|%i|",cola->dato);
		ver_cola(cola->sig);
	}
	return;
}
e_Cola *buscar_x(e_Cola *cola,int b)
{
    if(cola)
    {
    	if(cola->dato==b)
    		return cola;
    	else
    		buscar_x(cola->sig,b);
    }else{
    	return NULL;
    }
}
void eliminar(p_Cola **cola,int e)
{
	if(cola_vacia(*cola)==1)
	{
		printf("Cola vacia. No existen elementos a eliminar\n");
		return;
	}
	e_Cola *buq=buscar_x((*cola)->frente,e);
	if(!buq)
	{
		printf("No existe tal elemento en la cola\n");
		return;
	}
	if((*cola)->frente==(*cola)->final)
	{
		free(buq);
		(*cola)->frente=NULL;
		(*cola)->final=NULL;
		return;
	}
	if((*cola)->frente==buq){
		(*cola)->frente=buq->sig;
		free(buq);
		return;
	}
	eliminar_x(&(*cola)->frente,buq,&(*cola)->final);
	return;
}

void eliminar_x(e_Cola **cola,e_Cola *x,e_Cola **final)
{
	if((*cola)->sig==x)
	{
		e_Cola *aux=x->sig;
		(*cola)->sig=aux;
		if(!x->sig)
		    (*final)=aux;
		free(x);
		return;
	}
	eliminar_x(&(*cola)->sig,x,final);
}
