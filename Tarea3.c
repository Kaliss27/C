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
hijo *buscar_entre_hermanos(hijo *hermanos,int padre);
int insertar_nuevo_hermano(hijo *nhijo,hijo **fin);

int main(int argc, char const *argv[])
{
	n_padre *raiz=NULL;
	//raiz=crear_nodo_p(65);
	insertar_nuevo_nodo(&raiz,65,0);//A
	insertar_nuevo_nodo(&raiz,66,65);//B
	insertar_nuevo_nodo(&raiz,67,65);//C
	insertar_nuevo_nodo(&raiz,68,66);//D
	insertar_nuevo_nodo(&raiz,69,66);//E
	insertar_nuevo_nodo(&raiz,70,66);//F
	insertar_nuevo_nodo(&raiz,71,67);//H
	insertar_nuevo_nodo(&raiz,72,67);//H
	insertar_nuevo_nodo(&raiz,73,68);//I
    insertar_nuevo_nodo(&raiz,74,70);//J
	insertar_nuevo_nodo(&raiz,75,70);//K
	insertar_nuevo_nodo(&raiz,76,72);//L
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
int insertar_nuevo_hermano(hijo *nhijo,hijo **fin)
{
	(*fin)->hermano=nhijo;
	(*fin)=nhijo;
	return 1;
}
hijo *buscar_entre_hermanos(hijo *hermanos,int padre)
{
	if(!hermanos)
		return NULL;
	if(hermanos->raiz->dato==padre)
		return hermanos;
	buscar_entre_hermanos(hermanos->hermano,padre);
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
		insertar_nuevo_hermano(aux_h,&(*raiz)->final);
		return 1;
	}
	hijo *aux=(*raiz)->frente;
	if(aux){
		hijo *pb=buscar_entre_hermanos(aux,p);
		if(pb){
			insertar_nuevo_nodo(&pb->raiz,d,p);
			return 1;
		}
		if(aux->hermano)
			insertar_nuevo_nodo(&aux->hermano->raiz,d,p);
		insertar_nuevo_nodo(&aux->raiz,d,p);
	}
	return 0;
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
