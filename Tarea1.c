//*Tarea 1. *//
#include <stdio.h>
#include <stdlib.h>

typedef struct elemento_lista
{
	int dato;
	struct elemento_lista *sig;
}e_lista;

typedef struct elemento_lista1
{
	int id;
	e_lista *lista_datos;
	struct elemento_lista1 *sig;
}e_lista1;

/*------------------Funciones-------------------*/
e_lista1* buscar_lista(e_lista1 *actual,int d);
int insertar_elemento_ent(e_lista **inicio,int d);
int insertar_elemento_lista(e_lista1 **inicio,int idl,int num);
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
			printf("Ingrese un numero:\n");
			scanf("%i",&d);
			insertar_elemento_lista(&inicio_l,0,d);
			printf("------\n");
			ver_listas(inicio_l);			    
			break;
		}

	}while(bnd==1);
	printf("\n");
	do{
		
	}while(bnd==1);
	return 0;
}

/*------------------Cuerpo de Funciones-------------------*/
e_lista1* buscar_lista(e_lista1 *actual,int d){
	if(actual && actual->id==d)
		return actual;
	if(!actual)
		return NULL;
	buscar_lista(actual->sig,d);
	
}

void menu(){
	printf("===MENU DE OPCIONES===\n1->Insertar nuevo elemento a una lista\n2->Eliminar elemento de una lista\n3->Ver lista\n:");
}
int insertar_elemento_ent(e_lista **inicio,int d)
{
	e_lista *newe=(e_lista*)malloc(sizeof(e_lista));
	if(!newe)
		return 0;
	newe->dato=d;
    newe->sig=(*inicio);
    //printf("%p\n",newe->sig);
	(*inicio)=newe;
	//printf("%p\n",(*inicio));
	return 1;
}
int insertar_elemento_lista(e_lista1 **inicio,int idl,int num){
	if((*inicio)){
		e_lista1 *g_lista=buscar_lista((*inicio),idl);
		insertar_elemento_ent(&g_lista->lista_datos,num);
		return 1;
	}else{
		e_lista1 *newe=(e_lista1*)malloc(sizeof(e_lista1));
		if(!newe)
			return 0;
		//printf("%p\n",(*inicio));
		newe->lista_datos=NULL;
		//printf("%p\n",newe->lista_datos);
		insertar_elemento_ent(&newe->lista_datos,num);
		newe->sig=NULL;
		//printf("%p\n",newe->lista_datos);
		//printf("%p\n",newe->sig);
		(*inicio)=newe;
		//printf("%p\n",(*inicio));
		return 1;
	}
}
/*Imprimir lista de listas*/
void ver_elementos(e_lista *inicio)
{
	if(inicio)
	{
		printf("%i,", inicio->dato);
		//printf("%p\n",inicio->sig);
		ver_elementos(inicio->sig);
	}else{
		return;
	}
}

void ver_listas(e_lista1 *inicio)
{
	if(inicio)
	{
		//printf("%p\n",inicio);
		//printf("%p\n",inicio->lista_datos);
		ver_elementos(inicio->lista_datos);
		//printf("%p\n",inicio->sig);
		ver_listas(inicio->sig);
	}else{
		return;
	}
}
//------------------
/*int eliminar_elemento_l(e_lista1 **inicio_l, int d,int bnd){

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
}*/


