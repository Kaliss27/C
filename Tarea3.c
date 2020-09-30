/*Tarea 3
-Peralta Luna Karen Lisseth
-S17002346
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct nodo_padre
{
	int dato;
	struct punteros_hijos *frente;
	struct punteros_hijos *final;
}n_padre;

typedef struct punteros_hijos
{
	n_padre * raiz;
	struct punteros_hijos *hermano;
}hijo;

/*--------------------------------------*/
hijo *crear_cola(n_padre *nhijo);
n_padre *crear_nodo_p(int d);
int insertar_nuevo_nodo(n_padre **raiz,int d,int p);
void imprimir_hojas(hijo *frente);
void imprimir_arbol(n_padre *raiz);

int main(int argc, char const *argv[])
{
	n_padre *raiz=NULL;
	insertar_nuevo_nodo(&raiz,65,0);
	printf("%c\n",raiz->dato);
	insertar_nuevo_nodo(&raiz,66,65);
	insertar_nuevo_nodo(&raiz,67,65);
	insertar_nuevo_nodo(&raiz,68,66);
	insertar_nuevo_nodo(&raiz,69,66);
	insertar_nuevo_nodo(&raiz,70,66);
	insertar_nuevo_nodo(&raiz,71,67);
	insertar_nuevo_nodo(&raiz,72,67);
	insertar_nuevo_nodo(&raiz,73,68);
	insertar_nuevo_nodo(&raiz,74,70);
	//insertar_nuevo_nodo(&raiz,75,70);
	//insertar_nuevo_nodo(&raiz,76,72);
	imprimir_arbol(raiz);
	return 0;
}
hijo *crear_cola(n_padre *nhijo)
{
	hijo *neweh=(hijo*) malloc(sizeof(hijo));
	if(!neweh)
		return NULL;
	neweh->raiz=nhijo;
	neweh->hermano=NULL;
	return neweh;
}
n_padre *crear_nodo_p(int d)
{
	n_padre *newe=(n_padre*)malloc(sizeof(n_padre));
	if(!newe)
		return NULL;
	newe->dato=d;
	newe->frente=NULL;
	newe->final=NULL;
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
		n_padre *aux_n=crear_nodo_p(d);
		if(!(*raiz)->frente)
		{
			(*raiz)->frente=crear_cola(aux_n);
			(*raiz)->final=(*raiz)->frente;
			return 1;
		}
		hijo *aux_h=crear_cola(aux_n);
		(*raiz)->final->hermano=aux_h;
		(*raiz)->final=aux_h;
		return 1;
	}
	printf("no father\n");
	hijo *aux=(*raiz)->frente;
	if(!aux)
	{
		return 0;
	}else{
		insertar_nuevo_nodo(&aux->hermano->raiz,d,p);
	}
	printf("aux 1\n");
	insertar_nuevo_nodo(&aux->raiz,d,p);
}
void imprimir_hojas(hijo *frente)
{
	if(frente)
	{
		imprimir_arbol(frente->raiz);
		//printf("hijo: %c\n",frente->raiz->dato);
		imprimir_hojas(frente->hermano);
	}
	return;

}
void imprimir_arbol(n_padre *raiz)
{
	if(raiz)
	{
		printf("Padre:%c\n",raiz->dato);
		imprimir_hojas(raiz->frente);
	}
	return;
}

