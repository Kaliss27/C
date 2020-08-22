////////////////////////////////TAREA 1
#include <stdio.h>
#include <stdlib.h>
//#include <archivo.h>
#define l 3

typedef struct elemento_lista1
{
	int dato;
	struct elemento_lista1 *sig;
}e_lista1;

/*typedef struct elemento_lista0
{
	int id;
	e_lista1 *elemento;
	struct elemento_lista0 *sig;
}e_lista0;*/
/*------------------Funciones-------------------*/
int insertar_elemento_ent(e_lista1 **inicio,int d);
void ver_lista_ent(e_lista1 *inicio);
int eliminar_elemento_l(e_lista1 **inicio,int d,int bnd);

int main(int argc, char const *argv[])
{
    e_lista1 *inicio_l=NULL;
	int d,bnd,dd;
	do{
		printf("Ingrese un n%cmero entero:",163);
		scanf("%i",&d);
		dd=insertar_elemento_ent(&inicio_l,d);
		/*if(dd==1)
			printf("Se agreg%c correctamente\n",162);*/
		if(dd==0)
			printf("No se agreg%c correctamente\n",162);
		ver_lista_ent(inicio_l);
		printf("1->Otro\n0->Fin\t:");
		scanf("%i",&bnd);
	}while(bnd==1);
	ver_lista_ent(inicio_l);
	printf("\n");
	do{
		printf("Ingrese un n%cmero entero a eliminar:",163);
		scanf("%i",&d);
		dd=eliminar_elemento_l(&inicio_l,d,0);
		if(dd==1)
			printf("Se elimin%c correctamente\n",162);
		if(dd==0)
			printf("No se elimin%c correctamente\n",162);
		ver_lista_ent(inicio_l);
		printf("\n");
		printf("1->Otro\n0->Fin\t:");
		scanf("%i",&bnd);
	}while(bnd==1);
	return 0;
}

/*------------------Cuerpo de Funciones-------------------*/
int insertar_elemento_ent(e_lista1 **inicio,int d)
{
	e_lista1 *newe=(e_lista1*)malloc(sizeof(e_lista1));
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

void ver_lista_ent(e_lista1 *inicio)
{
	if(inicio!=NULL)
	{
		printf("%i,", inicio->dato);
		ver_lista_ent(inicio->sig);
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


