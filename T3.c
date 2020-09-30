/*Tarea 3
-Peralta Luna Karen Lisseth
-S17002346
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct nodo_padre
{
	int dato;
	struct punteros_hijos *hijos;
}n_padre;

typedef struct punteros_hijos
{
	n_padre * raiz;
	struct punteros_hijos *hermano;
}hijo;
typedef struct cola_hijos
{
	hijo *frente;
	hijo *final;
}c_hijos;
/*--------------------------------------*/
int crear_cola(c_hijos **cola,n_padre *nhijo);
n_padre *crear_nodo_p(int d);
int insertar_nuevo_nodo(n_padre **raiz,int d,int p);
void imprimir_hojas(hijo *frente);
void imprimir_arbol(n_padre *raiz);

int main(int argc, char const *argv[])
{
	n_padre *raiz=NULL;
	insertar_nuevo_nodo(&raiz,65,0);
	printf("%c\n",raiz->dato);
	printf("insertar_nuevo_nodo\n");
	insertar_nuevo_nodo(&raiz,66,65);
	printf("desp\n");
	imprimir_arbol(raiz);
	return 0;
}
int crear_cola(c_hijos **cola,n_padre *nhijo)
{
	hijo *neweh=(hijo*) malloc(sizeof(hijo));
	if(!neweh)
		return 0;
	neweh->raiz=nhijo;
	neweh->hermano=NULL;
	(*cola)->frente=neweh;
	(*cola)->final=neweh;
	return 1;
}
n_padre *crear_nodo_p(int d)
{
	n_padre *newe=(n_padre*)malloc(sizeof(n_padre));
	if(!newe)
		return NULL;
	newe->dato=d;
	newe->hijos=NULL;
	return newe;
}
int insertar_nuevo_nodo(n_padre **raiz,int d,int p)
{
	if(!(*raiz)){
		(*raiz)=crear_nodo_p(d);
		return 1;
	}
	if((*raiz)->dato==p)
	{
		n_padre *aux=crear_nodo_p(d);
		c_hijos *p;
		crear_cola(&p,aux);
		(*raiz)->hijos=p->final;
		//printf("inserto :%i\n",aux->dato);
		return 1;
	}
}
void imprimir_hojas(hijo *frente)
{
	if(frente)
	{
		imprimir_arbol(frente->raiz);
		imprimir_hojas(frente->hermano);
	}
	return;

}
void imprimir_arbol(n_padre *raiz)
{
	printf("iarbol\n");
	if(raiz)
	{
		printf("Padre %p\n Hijo:%p\n",raiz,raiz->hijos);
		printf("Padre:%c",raiz->dato);
		imprimir_hojas(raiz->hijos);
	}
	return;
}
