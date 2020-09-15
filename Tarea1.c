//*Tarea 1. * Peralta Luna Karen Lisseth  S17002346//
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
int buscar_id_lista(e_lista1 *inicio_l);
int insertar_elemento_ent(e_lista **inicio,int d);
int insertar_elemento_lista(e_lista1 **inicio,int idl,int num);
void ver_listas(e_lista1 *inicio);
void ver_elementos(e_lista *inicio);
int crear_lista(e_lista1 **inicio,int *idl);
void lista_ejm(e_lista1 **inicio,int bnd);
void menu();
int num_listas(e_lista1 *inicio,int cl);
int eliminar_elemento_l(e_lista **inicio_l, int d,int bnd);
void eliminar_elemento_de_lista(e_lista1 **lista,int nl,int eb);
int eliminar_elemento_lp(e_lista1 **inicio_l,int d,int bnd);

int main(int argc, char const *argv[])
{
    e_lista1 *inicio_l=NULL;
	int d,bnd,dd,opc;
	lista_ejm(&inicio_l,0);
	int cnid=buscar_id_lista(inicio_l);
	do{
		menu();
		scanf("%i",&opc);
		switch(opc){
			case 1:
			if (!inicio_l)
				printf("¡Lista Vacia!\nFavor de crear una nueva lista\n");
			else
			{
				ver_listas(inicio_l);	
			    printf("Ingrese el numero de la lista a usar:\n");
			    scanf("%i",&dd);
			    printf("Ingrese un numero a almacenar:\n");
			    scanf("%i",&d);
			    insertar_elemento_lista(&inicio_l,dd,d);
			}		    
			break;
			case 2:
			crear_lista(&inicio_l,&cnid);
			break;
			case 3:
			printf("Lista de Listas\n");
			ver_listas(inicio_l);
			printf("Ingrese el numero de la lista a usar:\n");
			scanf("%i",&dd);
			printf("Ingrese un numero a eliminar:\n");
			scanf("%i",&d);
			eliminar_elemento_de_lista(&inicio_l,dd,d);
			break;
			case 4:
			printf("Lista de Listas\n");
			ver_listas(inicio_l);
			printf("Ingrese el id de la lista a eliminar:\n");
			scanf("%i",&d);
			eliminar_elemento_lp(&inicio_l,d,0);
			break;
			case 5:
			free(inicio_l);
			inicio_l=NULL;
		}
		system("clear");
		printf("Lista de Listas\n");
		ver_listas(inicio_l);
		printf("1->Continuar\n2->Terminar\t:");
		scanf("%i",&bnd);
		system("clear");
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
int buscar_id_lista(e_lista1 *inicio_l)
{
	if(!inicio_l->sig)
		return inicio_l->id;
	buscar_id_lista(inicio_l->sig);
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
int crear_lista(e_lista1 **inicio,int *idl){
	if(!(*inicio)){
	    e_lista1 *newe=(e_lista1*)malloc(sizeof(e_lista1));
	    if(!newe)
	        return 0;
	    printf("%i\n",*idl);
	    system("pause");
	    (*idl)++;
	    newe->id=*idl;
	    newe->lista_datos=NULL;
	    newe->sig=NULL;
	    (*inicio)=newe;
	return 1;  
	}else{
		crear_lista(&(*inicio)->sig,idl);
	}
}
void menu(){
	printf("===MENU DE OPCIONES===\n1->Insertar nuevo elemento a una lista\n2->Crear nueva lista\n");
	printf("3->Eliminar elemento de una lista\n4->Eliminar lista\n5->Eliminar lista de listas:\n6->Salir\n");
	printf("Opcion:");
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
/*IMPRIMIR LISTA DE LISTAS*/
//IMPRIME ELEMENTOS DE UNA LISTA 
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
//IMPRIME ELEMENTOS DE LA LISTA PRINCIPAL
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
/*-------------------------------------------------------*/
/*ELIMINAR ELEMENTOS DE LISTAS*/
int eliminar_elemento_l(e_lista **inicio_l, int d,int bnd)
{
	if((*inicio_l) == NULL){
		if(bnd==0)
			return 0;
		return 1;
	}
	if ((*inicio_l)->dato == d){
		e_lista *aux = (*inicio_l);
		(*inicio_l) = (*inicio_l)->sig;
		free(aux); 
		bnd=1;
		if((*inicio_l) == NULL){
			return 1;
		}
    return eliminar_elemento_l(&(*inicio_l)->sig,d,bnd);
}
return eliminar_elemento_l(&(*inicio_l)->sig,d,bnd);
}

void eliminar_elemento_de_lista(e_lista1 **lista,int nl,int eb){
	if((*lista)){
		e_lista1 *g_lista=buscar_lista((*lista),nl);
		eliminar_elemento_l(&g_lista->lista_datos,eb,0);
		return;
	}
}
//ELIMINA ELEMENTO DE LA LISTA PRINCIPAL
int eliminar_elemento_lp(e_lista1 **inicio_l,int d,int bnd){
	if((*inicio_l) == NULL){
		if(bnd==0)
			return 0;
		return 1;
	}
	if ((*inicio_l)->id == d){
		e_lista1 *aux = (*inicio_l);
		(*inicio_l) = (*inicio_l)->sig;
		free(aux); 
		bnd=1;
		if((*inicio_l) == NULL){
			return 1;
		}
    return eliminar_elemento_lp(&(*inicio_l)->sig,d,bnd);
}
return eliminar_elemento_lp(&(*inicio_l)->sig,d,bnd);
}
