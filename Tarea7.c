/* S17002346
   Peralta Luna Karen Lisseth
   Tarea 7.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct nodoBinario
{
	char dato;
	struct nodoBinario *izq;
	struct nodoBinario *der;	
}nodoB;

int insertar(nodoB **axraiz,int d);
nodoB* crearNodo(char d);
void ver_Arbol(nodoB *raiz,int c,int i);
int buscar_dato(nodoB *raiz,int d);
void postorden(nodoB *raiz);
void preorden(nodoB *raiz);
void inorden(nodoB *raiz);


int main(int argc, char const *argv[])
{
	nodoB *raiz=NULL;
	char temp,formula[300];
	printf("\nIntroduce ecuacion:");
	scanf("%s",formula);
	printf("%s\n",formula);
		for(int i=0;i<=strlen(formula);i++)
	{
		temp = formula[i-1];
		insertar(&raiz,temp);
	}	
	ver_Arbol(raiz,0,0);
	printf("\n\n preorden :");
	preorden(raiz);
	printf("\n\n inorden :");
	inorden(raiz);
	printf("\n\n postorden :");
	postorden(raiz);
	return 0;
}
nodoB* crearNodo(char d){
	nodoB *newe=(nodoB*)malloc(sizeof(nodoB));
	if(!newe)
		return NULL;
	newe->dato=d;
	newe->der=NULL;
    newe->izq=NULL;		
	return newe;	
}
///////////INSERTAR NODO A ARBOL BINARIO////////////////////////
int insertar(nodoB **axraiz,int d)
{
	if(!(*axraiz)){
		(*axraiz)=crearNodo(d);
		return 1;
	}
	if(d>(*axraiz)->dato){
	    insertar(&(*axraiz)->der,d);
	}else{
		if((*axraiz)->dato==d) return 2;
		insertar(&(*axraiz)->izq,d); 
	}
}
//////////Imprime arbol//////////////
void ver_Arbol(nodoB *raiz,int c,int i){
	if(!raiz){
		return;
	}
	else{
		ver_Arbol(raiz->der,c+1,0);
		for(i=0;i<c;i++){
			printf("   ");
		}
		printf("%c\n",raiz->dato);
		ver_Arbol(raiz->izq,c+1,0);
	}
	
}
////////Buscar dato en el arbol//////////////////
int buscar_dato(nodoB *raiz,int d){
	if(!raiz)
		return 0;
	if(raiz->dato==d)
		return 1;
	if(d<raiz->dato)
		return buscar_dato(raiz->izq,d);
	return buscar_dato(raiz->der,d);
}
void inorden(nodoB *raiz)
{
	if(raiz)
	{
	   	if(raiz->izq)
			inorden(raiz->izq); 
		printf("%c ",(*raiz).dato);
		if(raiz->der)   
	    	inorden(raiz->der);
	}
	return;
}         
void preorden(nodoB *raiz)
{
	if(raiz)
	{
		printf("%c ",(*raiz).dato);
		if(raiz->izq)
	    	preorden(raiz->izq);
	   	if(raiz->der) 
		    preorden(raiz->der);
	}
	return;
}
void postorden(nodoB *raiz)
{
	if(raiz)
	{
		if(raiz->izq)    
	    	postorden(raiz->izq);
		if(raiz->der) 
	    	postorden(raiz->der); 
		printf("%c ",(*raiz).dato);
	}
	return;
} 