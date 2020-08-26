//*Tarea 1. *//
#include <stdio.h>
#include <stdlib.h>

typedef struct elemento_lista
{
	int dato;
	struct elemento_lista2 *sig;
}e_lista;

typedef struct elemento_lista1
{
	int id;
	e_lista2 *lista_datos;
	struct elemento_lista1 *sig;
}e_lista1;

/*------------------Funciones-------------------*/

int insertar_elemento_ent(e_lista **inicio,int d);
int insertar_elemento_lista(e_lista1 **inicio,int idl);
void ver_listas(e_lista1 *inicio);
void ver_elementos(e_lista *inicio);
int eliminar_elemento_l(e_lista1 **inicio,int d,int bnd);
void menu();

int main(int argc, char const *argv[])
{
    e_lista1 *inicio_l=NULL;
	int d,bnd,dd,opc;
	do{
		menu();
		scanf("%i",&opc);
		switch(opc){
			case 1:
			    
			break;
		}

	}while(bnd==1);
	ver_lista_ent(inicio_l);
	printf("\n");
	do{
		
	}while(bnd==1);
	return 0;
}

/*------------------Cuerpo de Funciones-------------------*/
void menu(){
	printf("===MENU DE OPCIONES===\n1->Insertar nuevo elemento a una lista\n2->Eliminar elemento de una lista\n3->Ver lista\n:");
}
int insertar_elemento_ent(e_lista **inicio,int d)
{
	e_lista *newe=(e_lista*)malloc(sizeof(e_lista));
	if(!newe)
		return 0;
	newe->dato=d;
	if((*inicio)==NULL)
	{
			newe->sig=NULL;
	}else{
	        newe->sig=(*inicio);
	}
	(*inicio)=newe;
	return 1;
}

void ver_elementos(e_lista *inicio)
{
	if(inicio!=NULL)
	{
		if()
		printf("%i,", inicio->dato);
		ver_lista_ent(inicio->sig);
	}
	return;
}

void ver_listas(e_lista1 *inicio)
{
	if(inicio!=NULL)
	{
		ver_elementos(inicio->lista_datos);
		ver_listas(inicio->sig);
	}
	return;
}

e_lista1* buscar_lista(e_lista1 *inicio_l,int d)
{
	if(inicio_l==NULL)
		return NULL;
	if(inicio_l->dato==d)
		return inicio_l;
	return buscar_lista(inicio_l->sig,d);
}

int eliminar_elemento_l(e_lista1 **inicio_l, int d,int bnd){

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
    //return eliminar_elemento_l(&(*inicio_l)->sig,d,bnd);
}
return eliminar_elemento_l(&(*inicio_l)->sig,d,bnd);
}


