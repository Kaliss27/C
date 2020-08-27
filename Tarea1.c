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
int crear_lista(e_lista1 **inicio,int idl);
void lista_ejm(e_lista1 **inicio,int bnd);
void menu();
int num_listas(e_lista1 *inicio,int cl);

int main(int argc, char const *argv[])
{
    e_lista1 *inicio_l=NULL;
	int d,bnd,dd,opc;
	lista_ejm(&inicio_l,0);
	do{
		menu();
		scanf("%i",&opc);
		switch(opc){
			case 1:
			ver_listas(inicio_l);	
			printf("Ingrese el numero de la lista a usar:\n");
			scanf("%i",&dd);
			printf("Ingrese un numero a almacenar:\n");
			scanf("%i",&d);
			insertar_elemento_lista(&inicio_l,dd,d);		    
			break;
			case 2:
			crear_lista(&inicio_l,num_listas(inicio_l,1));
			break;
		}
		printf("Lista de Listas\n");
		ver_listas(inicio_l);
		printf("1->Continuar\n2->Stop\t:");
		scanf("%i",&bnd);
	}while(bnd==1);
	ver_listas(inicio_l);	
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
int num_listas(e_lista1 *inicio,int cl){
	if(inicio){
		cl++;
		num_listas(inicio->sig,cl);
	}else{
		return cl;
	}
}
void lista_ejm(e_lista1 **inicio,int bnd){
	if(bnd<3){
	    e_lista1 *newe=(e_lista1*)malloc(sizeof(e_lista1));
	    if(!newe)
	        return;
	    bnd++;
	    newe->id=bnd;
	    newe->lista_datos=NULL;
	    newe->sig=NULL;
	    (*inicio)=newe;
	    lista_ejm(&(*inicio)->sig,bnd);  
	}else{
		return;
	}
}
int crear_lista(e_lista1 **inicio,int idl){
	if(!(*inicio)){
	    e_lista1 *newe=(e_lista1*)malloc(sizeof(e_lista1));
	    if(!newe)
	        return 0;
	    newe->id=idl;
	    newe->lista_datos=NULL;
	    newe->sig=NULL;
	    (*inicio)=newe;
	return 1;  
	}else{
		crear_lista(&(*inicio)->sig,idl);
	}
}
void menu(){
	printf("===MENU DE OPCIONES===\n1->Insertar nuevo elemento a una lista\n2->Crear nueva lista\n3->Eliminar elemento de una lista\n4->Ver lista\n:");
}
int insertar_elemento_ent(e_lista **inicio,int d)
{
	e_lista *newe=(e_lista*)malloc(sizeof(e_lista));
	if(!newe)
		return 0;
	newe->dato=d;
    newe->sig=(*inicio);
	(*inicio)=newe;
	return 1;
}
int insertar_elemento_lista(e_lista1 **inicio,int idl,int num){
	if((*inicio)){
		e_lista1 *g_lista=buscar_lista((*inicio),idl);
		insertar_elemento_ent(&g_lista->lista_datos,num);
		return 1;
	}
}
/*Imprimir lista de listas*/
void ver_elementos(e_lista *inicio)
{
	if(inicio)
	{
		printf("| %i |", inicio->dato);
		ver_elementos(inicio->sig);
	}else{
		return;
	}
}

void ver_listas(e_lista1 *inicio)
{
	if(inicio)
	{
		printf("Lista:%i\n",inicio->id);
		ver_elementos(inicio->lista_datos);
		printf("\n");
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
