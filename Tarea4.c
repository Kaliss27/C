//Tarea 4 Peralta Luna Karen Lisseth
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
int borrar_dato(nodoB **raiz,int d);
void avance(nodoB **aux,nodoB **aux1,int *bo);
int buscar_dato(nodoB *raiz,int d);

int main(int argc, char const *argv[])
{
	nodoB *raiz=NULL;
	int d,opc,n;
	do{
		printf("1->Ingresar datos al arbol\n2->Ver arbol\n3->Eliminar datos del arbol\n4->Buscar dato en el arbol\n5->Salir\nOpci%cn:",162);
		scanf("%i",&opc);
		switch(opc){
			case 1: 
			printf("Ingresar un n%cmero entero:",163);
			scanf("%i",&d);
			insertar(&raiz,d);
			break;
			case 2:
			printf("==Arbol binario==\n");
			ver_Arbol(raiz,0,0);
			system("pause");
			break;
			case 3:
			printf("==Arbol binario==\n");
            ver_Arbol(raiz,0,0);
			printf("Ingresar un n%cmero entero:",163);
			scanf("%i",&d);
			borrar_dato(&raiz,d);
			break;
			case 4:
			printf("Ingrese un n%cmero entero a buscar:",163);
			scanf("%i",&d);
			n=buscar_dato(raiz,d);
			if(n==1)
				printf("Se encontr%c el valor en el arbol\n",162);
			if(n==0)
				printf("No se encontr%c el valor en el arbol\n",162);
			system("pause");
		}	
	system("cls");
	}while(opc!=5);
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
//////////Imprime arbol//////////////
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

//////////////////Eliminar nodo de arbol/////////////////////////////////
int borrar_dato(nodoB **raiz,int d){
	nodoB *aux,*aux1,*otro;
	int bo;
	if((*raiz)!=NULL){
		if(d<(*raiz)->dato){
			borrar_dato(&(*raiz)->izq,d);
		}else{
			if(d>(*raiz)->dato){
				borrar_dato(&(*raiz)->der,d);
			}else{
				otro=(*raiz);
				if(otro->der==NULL){
					(*raiz)=otro->izq;
				}else{
					if(otro->izq==NULL){
						(*raiz)=otro->der;
					}else{
						aux=(*raiz)->izq;
						bo=0;
						avance(&aux,&aux1,&bo);
						(*raiz)->dato=aux->dato;
						otro=aux;
						if(bo==1){
							aux1->der=aux->izq;
						}else{
							(*raiz)->izq=aux->izq;
						}
					}
				}
				free(otro);
				return 1;
			}
		}
	}
	return 0;
}

void avance(nodoB **aux,nodoB **aux1,int *bo){
	if((*aux)->der!=NULL){
		(*aux1)=(*aux);
		(*aux)=(*aux)->der;
		*bo=1;
		avance(&(*aux),&(*aux1),bo);
	}
	return;
}
//Buscar arbol
int buscar_dato(nodoB *raiz,int d){
	if(raiz==NULL)
		return 0;
	if(raiz->dato==d)
		return 1;
	buscar_dato(raiz->der,d);
	if(raiz->dato==d)
		return 1;
	buscar_dato(raiz->izq,d);
}