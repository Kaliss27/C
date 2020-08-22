//Biblioteca---Peralta Luna Karen Lisseth
#include <stdlib.h>
#include<stdio.h>
//Estructuras
typedef struct elemento{
	int d;
	struct elemento *sig;
}e_gral;

typedef struct elemento_Cola
{
	e_gral *fre;
	e_gral *fin;
}ptrs_cola;

//Funciones listas
int insertar_elemento_ent(e_gral **inicio,int d)
{
	e_gral *newe=(e_gral*)malloc(sizeof(e_gral));
	if(!newe)
		return 0;
	newe->d=d;
	if((*inicio)==NULL)
	{
			newe->sig=NULL;
	}else{
	        newe->sig=(*inicio);
	}
	(*inicio)=newe;
	return 1;
}

void ver_lista_ent(e_gral *inicio)
{
	if(inicio!=NULL)
	{
		printf("%i,", inicio->d);
		ver_lista_ent(inicio->sig);
	}
	return;
}


int eliminar_elemento_l(e_gral **inicio_l, int d,int bnd){

	if((*inicio_l) == NULL){
		if(bnd==0)
			return 0;
		return 1;
	}

	if ((*inicio_l)->d == d){
		e_gral *aux = (*inicio_l);
		(*inicio_l) = (*inicio_l)->sig;
		free(aux); 
		bnd=1;
		if((*inicio_l) == NULL){
			return 1;
		}
	}
	return eliminar_elemento_l(&(*inicio_l)->sig,d,bnd);
}


////Funciones colas
int insertar_elemento_c(ptrs_cola **ptrs){
	e_gral *newe=(e_gral*)malloc(sizeof(e_gral));
	if(!newe)
		return 0;
	printf("Ingrese un n%cmero entero:",163);
	scanf("%i",&newe->d);
	newe->sig=NULL;
	if((*ptrs)->fre==NULL)
		{
			(*ptrs)->fre=newe;

		}else{
			(*ptrs)->fin->sig=newe;
		}	
	(*ptrs)->fin=newe;
	return 1;
}

int buscar_elemento_c(ptrs_cola *ver,int d){
	if(ver->fre!=NULL){
		if(d==ver->fre->d)
			return 1;
		buscar_elemento_l(ver->fre->sig,d);
    }
    return 0;
}

void eliminacion(ptrs_cola **ptrs, int d,e_gral **act, e_gral **ant){
	if ((*act) == NULL)
		return;
	
	if ((*act)->d == d){

		if ((*ptrs)->fre == (*ptrs)->fin){
			(*ptrs)->fre = NULL;
			(*ptrs)->fin = NULL;
			free(ant);
			return;
		}

		else if ((*act) == (*ptrs)->fre)
			(*ptrs)->fre = (*ptrs)->fre->sig;

		else if ((*act) == (*ptrs)->fin){
			(*ant)->sig = NULL;
			(*ptrs)->fin = (*ant);
		}

		else
			(*ant)->sig = (*act)->sig;
		free(ant);
		return;
	}

	(*ant) = (*act);
	(*act) = (*act)->sig;
	eliminacion(&(*ptrs),d, &(*act), &(*ant));
}

//funciones pila
e_gral* pop(e_gral **tope)
{
	e_gral *aux=(*tope);
	(*tope)=(*tope)->sig;
	return aux;
}

int push(int d,e_gral **tope)
{
	e_gral *newe=(e_gral*)malloc(sizeof(e_gral));
	if(!newe)
		return 0;
	newe->d=d;
	newe->sig=(*tope);
	(*tope)=newe;
}
