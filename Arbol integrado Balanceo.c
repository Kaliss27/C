#include <stdio.h>
#include <stdlib.h>

typedef struct nodoBinario
{
	int dato;
	struct nodoBinario *izq;
	struct nodoBinario *der;	
}nodoB;

int insertar(nodoB **axraiz,int d);
nodoB* crearNodo(int d);
int altura_arbol(nodoB *raiz);
int equilibrio_arbol(nodoB *raiz);

int main(int argc, char const *argv[])
{
	nodoB *raiz=NULL;
	int d,bnd,eq,h;
	do{
		printf("Ingrese un n%cmero entero:",163);
		scanf("%i",&d);
		insertar(&raiz,d);
		printf("1->Otro n%cmero\n0->Terminar\t:",163);
		scanf("%i",&bnd);
	}while(bnd==1);
	h=altura_arbol(raiz);
	eq=equilibrio_arbol(raiz);
	printf("Altura arbol:%i\nFactor de equilibrio del arbol:%i",h,eq);
	return 0;
}
nodoB* crearNodo(int d){
	nodoB *newe=(nodoB*)malloc(sizeof(nodoB));
	newe->dato=d;
	newe->der=NULL;
    newe->izq=NULL;		
	return newe;	
}
///////////INSERTAR NODO A ARBOL BINARIO////////////////////////
int insertar(nodoB **axraiz,int d){
	if((*axraiz)==NULL){
		nodoB *nnuevo=crearNodo(d);
		if(!nnuevo){
			return 0;
		}
		(*axraiz)=nnuevo;
		return 1;
	}
	if(d>(*axraiz)->dato){
		return insertar(&(*axraiz)->der,d);
	}else{
		if((*axraiz)->dato==d) return 2;
		return insertar(&(*axraiz)->izq,d);
	}	
}
///////////////CONTAR NIVELES DEL ARBOL///////////////////////
int altura_arbol(nodoB *raiz){
	int h1,h2;
	if(!raiz)
		return 0;
	h1=altura_arbol(raiz->izq);
	h2=altura_arbol(raiz->der);

	if(h1>h2)
		return h1+1;
	return h2+1;
}
/////////EQUILIBRIO DEL ARBOL/////////////////////
int equilibrio_arbol(nodoB *raiz){
	int h1,h2;
	if(!raiz)
		return 0;
	h1=altura_arbol(raiz->izq);
	h2=altura_arbol(raiz->der);
	return h2-h1;
}
//BALANCEO DE ARBOL
int balanceo_DD(nodoB **raiz)
{
	if(!(*raiz))
		return 0;
	nodoB *aux=(*raiz)->der;
	(*raiz)->der=aux->izq;
	aux->izq=*raiz;
	*raiz=aux;
	return 1;
}

int balanceo_II(nodoB **raiz)
{
	if(!(*raiz))
		return 0;
	nodoB *aux=(*raiz)->izq;
	(*raiz)->izq=aux->der;
	aux->der=(*raiz);
	*raiz=aux;
	return 1;

}
int balanceo_DI(nodoB **raiz)
{
	if(!(*raiz)==NULL)
		return 0;
	balanceo_DD(&(*raiz)->izq);
	
}
