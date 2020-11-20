/*Tarea: Arbol Genealogico
-Peralta Luna Karen Lisseth
-S17002346
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct nodo_padre
{
	char nombre[10];
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
n_padre *crear_nodo_p(char *d);
int insertar_nuevo_nodo(n_padre **raiz,char *d,char *p);
void imprimir_hojas(hijo *frente,int c,int i);
void imprimir_arbol(n_padre *raiz,int c,int i);
hijo *buscar_entre_hermanos(hijo *hermanos,char *padre);
int insertar_nuevo_hermano(hijo *nhijo,hijo **fin);
void menu();
int main(int argc, char const *argv[])
{
	n_padre *raiz=NULL;
	int opc,id_asg=0;
	char name[10],namep[10];
	do
	{
		printf("**ARBOL GENEALOGICO**\n");
		menu();
		scanf("%i",&opc);
		printf("*************************************\n");
		switch(opc)
		{
			case 1:
			if(!raiz)
			{
				printf("No existen aun registro de familiares\nPor favor ingresa el nombre del padre o madre:\n");
				scanf("%9s",name);
				insertar_nuevo_nodo(&raiz,name,NULL);
				break;
			}
			imprimir_arbol(raiz,0,0);
			printf("Ingrese el nombre del padre o madre:\n");
			scanf("%9s",namep);
			printf("Ingrese el nombre del hijo o hija:\n");
			scanf("%9s",name);
			insertar_nuevo_nodo(&raiz,name,namep);
			break;
			case 2:
			imprimir_arbol(raiz,0,0);
			sleep(5);
			break;
		}
		system("clear");
	}while(opc!=3);
	printf("**ARBOL GENEALOGICO**\n");
	imprimir_arbol(raiz,0,0);
	return 0;
}

void menu()
{
	printf("1->Insertar nuevo hijo\n");
	printf("2->Ver Arbol Genealogico\n");
	printf("3->Salir\n");
	printf("Opcion:");
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
n_padre *crear_nodo_p(char *d)
{
	n_padre *newe=(n_padre*)malloc(sizeof(n_padre));
	if(!newe)
		return NULL;
	strcpy(newe->nombre,d);
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
hijo *buscar_entre_hermanos(hijo *hermanos,char *padre)
{
	if(!hermanos)
		return NULL;
	if(strcmp(hermanos->raiz->nombre,padre)==0)
		return hermanos;
	buscar_entre_hermanos(hermanos->hermano,padre);
}

int insertar_nuevo_nodo(n_padre **raiz,char *d,char *p)
{
	if(!(*raiz)){
		(*raiz)=crear_nodo_p(d);
		return 1;
	}
	if(strcmp((*raiz)->nombre,p)==0)
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

void imprimir_hojas(hijo *frente,int c,int i)
{
	if(frente)
	{
		imprimir_arbol(frente->raiz,c,0);
		imprimir_hojas(frente->hermano,c,0);
	}
	return;

}

void imprimir_arbol(n_padre *raiz,int c,int i)
{
	if(raiz)
	{
		for(i=0;i<c;i++)
		{
			printf(" ");
		}
		printf("|-%s\n",raiz->nombre);
		imprimir_hojas(raiz->frente,c+1,0);
	}
	return;
}
