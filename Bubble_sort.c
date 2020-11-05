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
void bubble_sort(e_lista **inicio,int n_elem); 
void swap(e_lista *aux1,e_lista *aux2,e_lista *new_f);
int count_elem(e_lista *inicio,int c);

int main(int argc, char const *argv[])
{
	e_lista *inicio_l1=NULL;
	agregar_inicio(&inicio_l1,27);
	agregar_inicio(&inicio_l1,7);
	agregar_inicio(&inicio_l1,18);
	//agregar_inicio(&inicio_l1,24);
	//agregar_inicio(&inicio_l1,4);
	ver_lista(inicio_l1);
	bubble_sort(&inicio_l1,count_elem(inicio_l1,0)+1);
	printf("\n");
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
void swap(e_lista *aux1,e_lista *aux2,e_lista *new_f)
{
	printf("aux1:%i\naux2:%i\n",aux1->dato,aux2->dato);
	e_lista *aux_a=aux1->ant;
	aux_a->sig=aux2;
	aux1->sig=aux2->sig;
	aux1->ant=aux_a->sig;
	aux2->ant=aux_a;
	aux2->sig=aux1;
	aux2=aux1;
	aux1=aux_a->sig;
	printf("aux1:%i\naux2:%i\n",aux1->dato,aux2->dato);
	if(!aux1->ant)
		new_f=aux1;
	return;
}

void bubble_sort(e_lista **inicio,int n_elem) 
{
	if (!(*inicio))
	{
		return;
	}
	printf("\nebubble\n");
	printf("inicio:%i\nn_e:%i\n",(*inicio)->dato,n_elem);
	int bnd;
	e_lista *actual,*siguiente;
	actual=(*inicio);
	siguiente=(*inicio)->sig;
	while(siguiente)
	{
		if(actual->dato > siguiente->dato)
			swap(actual,siguiente,(*inicio));
		printf("hii\n");
		actual=siguiente;
		siguiente=siguiente->sig;
	}
	bubble_sort(&(*inicio)->sig,n_elem);
	return;
}
