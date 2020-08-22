//Tarea 3-Peralta Luna Karen Lisseth
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
void ver_Arbol(nodoB *raiz,int c,int i);

int main(int argc, char const *argv[])
{
	nodoB *raiz=NULL;
	int d,bnd;
	do{
		printf("Ingrese un n%cmero entero:",163);
		scanf("%i",&d);
		insertar(&raiz,d);
		printf("1->Otro n%cmero\n0->Terminar\t:",163);
		scanf("%i",&bnd);
	}while(bnd==1);
	printf("====Arbol binario====\n");
	ver_Arbol(raiz,0,0);
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
void ver_Arbol(nodoB *raiz,int c,int i){
	if(raiz==NULL){
		return;
	}
	else{
		ver_Arbol(raiz->der,c+1,0);
		for(i=0;i<c;i++){
			printf("   ");
		}
		printf("%i\n",raiz->dato);
		ver_Arbol(raiz->izq,c+1,0);
	}
	
}

