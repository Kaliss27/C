/*
  S17002346 - Peralta Luna Karen Lisseth
  Ordenamiento: Bubble Sort 
*/
#include <stdio.h>
#include <stdlib.h>
//Estructuras
typedef struct elemento_lista
{
	int dato;
	struct elemento_lista *sig;
	struct elemento_lista *ant;
}e_lista;
//Funciones
int agregar_inicio(e_lista **inicio,int num);
void ver_lista(e_lista *inicio);
void bubble_sort(e_lista **inicio); 
void swap(e_lista **aux1,e_lista **aux2,e_lista **new_f);
int count_elem(e_lista *inicio,int c);
void ordenamiento(e_lista **inicio,int n_elem);
int main(int argc, char const *argv[])
{
	e_lista *inicio_l1=NULL;
	// Ejemplo del video
	agregar_inicio(&inicio_l1,9);
	agregar_inicio(&inicio_l1,6);
	agregar_inicio(&inicio_l1,4);
	agregar_inicio(&inicio_l1,5);
	agregar_inicio(&inicio_l1,2);
	agregar_inicio(&inicio_l1,7);
	agregar_inicio(&inicio_l1,8);
	agregar_inicio(&inicio_l1,1);
	agregar_inicio(&inicio_l1,0);
	agregar_inicio(&inicio_l1,3);
	ver_lista(inicio_l1);
	ordenamiento(&inicio_l1,count_elem(inicio_l1,0)+1);
	printf("\nBubble Sort\n");
	ver_lista(inicio_l1);
	return 0;
}

//Cuerpo de funciones
int agregar_inicio(e_lista **inicio,int num)
{
	e_lista *newe=(e_lista*)malloc(sizeof(e_lista));
	if(!newe)
		return 0;
	newe->dato=num;
	if(!(*inicio))
		newe->ant=(*inicio);
	else
		(*inicio)->ant=newe;
    newe->sig=(*inicio);
	(*inicio)=newe;
	return 1;
}

void ver_lista(e_lista *inicio)
{
	if(inicio){
		printf("|%i|",inicio->dato);
		ver_lista(inicio->sig);
	}
	return;
}
int count_elem(e_lista *inicio,int c)
{
	if(!inicio)
		return c;
	c++;
	return count_elem(inicio->sig,c);
}
void swap(e_lista **aux1,e_lista **aux2,e_lista **new_f)
{
	e_lista *aux=(*aux1);
	e_lista *auxx=(*aux1)->ant;

	(*aux1)=(*aux2);
	(*aux2)=aux;
	(*aux1)->ant=(*aux2)->ant;
	(*aux2)->ant=(*aux1);
	(*aux2)->sig=(*aux1)->sig;

	(*aux1)->sig=(*aux2);

	aux=(*aux2)->sig;
	if(aux)     //Verifica si se cambia con el ultimo elemento de la lista
		aux->ant=(*aux2);

	if(auxx)    //Verifica si se cambia con el primer elemento de la lista
	{
		auxx->sig=(*aux1);
	}

	if(!(*aux1)->ant)  //Modifica el puntero a inicio de la lista, en caso de que el primer elemento haya cambiado
		(*new_f)=(*aux1);

	return;
}

void bubble_sort(e_lista **inicio) 
{
	if (!(*inicio))
	{
		return;
	}
	e_lista *actual,*siguiente;
	actual=(*inicio);
	siguiente=(*inicio)->sig;
	
	while(siguiente)
	{
		if(actual->dato > siguiente->dato)
			swap(&actual,&siguiente,inicio);
		actual=siguiente;
	    siguiente=siguiente->sig;
	}
	bubble_sort(&(*inicio)->sig);
	return;
}
void ordenamiento(e_lista **inicio,int n_elem)
{
	for(int i=0;i<n_elem;i++)
	{
		bubble_sort(inicio);
	}
}
