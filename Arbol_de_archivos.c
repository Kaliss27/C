/*Tarea: Arbol de archivos
-Peralta Luna Karen Lisseth
-S17002346
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct nodo_archivo
{
	char nombre[20];
}n_archivo;
typedef struct nodo_folder
{
	char nombre[20];
	struct punteros_hijos *frente;
	struct punteros_hijos *final;
}n_folder;

typedef struct nodo_padre
{
    n_archivo *archivo;
    n_folder *folder;
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
n_padre *crear_nodo_p(char *d,int t);
n_padre *crear_nodo_a(char *d);//
int insertar_nuevo_nodo(n_padre **raiz,char *d,char *p,int ty);
void imprimir_hojas(hijo *frente,int c,int i);
void imprimir_arbol(n_padre *raiz,int c,int i);
hijo *buscar_entre_hermanos(hijo *hermanos,char *padre);
int insertar_nuevo_hermano(hijo *nhijo,hijo **fin);
void eliminar(n_padre **cola,char *padre);
void eliminar_x(hijo **cola,hijo *x,hijo **final);
void menu();
int main(int argc, char const *argv[])
{
	n_padre *raiz=NULL;
	int opc,id_asg=0;
	char name[10],namep[10];
	insertar_nuevo_nodo(&raiz,"Escritorio",NULL,0);
	do
	{
		printf("**ARBOL DE ARCHIVOS**\n");
		menu();
		scanf("%i",&opc);
		printf("*************************************\n");
		switch(opc)
		{
			case 1:
			imprimir_arbol(raiz,0,0);
			printf("Ingrese el nombre del folder padre\n");
			scanf("%19s",namep);
			printf("Ingrese el nombre de su nuevo folder\n");
			scanf("%19s",name);
			insertar_nuevo_nodo(&raiz,name,namep,0);
			break;
			case 2:
			imprimir_arbol(raiz,0,0);
			printf("Ingrese el nombre del folder padre en que se guardara su archivo\n");
			scanf("%19s",namep);
			printf("Ingrese el nombre de su archivo:\n");
			scanf("%19s",name);
			insertar_nuevo_nodo(&raiz,name,namep,1);
			break;
			case 3:
			imprimir_arbol(raiz,0,0);
			printf("Ingrese el nombre del archivo a eliminar:");
			scanf("%s",name);
			eliminar(&raiz,name);
			printf("Eliminado\n");
			break;
			case 4:break;
			case 5:
			imprimir_arbol(raiz,0,0);
			sleep(5);
		}
		system("clear");
	}while(opc!=6);
	printf("**ARBOL DE ARCHIVOS**\n");
	imprimir_arbol(raiz,0,0);
	return 0;
}

void menu()
{
	printf("1->Crear un nuevo folder\n");
	printf("2->Agregar un archivo\n");
	printf("3->Borrar Archivo\n");
	printf("4->Borrar Folder\n");
	printf("5->Ver Arbol\n");
	printf("6->Salir\n");
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
n_folder *crear_n_folder(char *n){
	n_folder *newe=(n_folder*)malloc(sizeof(n_folder));
	if (!newe)
		return NULL;
	strcpy(newe->nombre,n);
	newe->frente=NULL;
	newe->final=NULL;
	return newe;
}

n_archivo *crear_n_archivo(char *n){
	n_archivo *newe=(n_archivo*)malloc(sizeof(n_archivo));
	if(!newe)
		return NULL;
	strcpy(newe->nombre,n);
	return newe;
}
n_padre *crear_nodo_p(char *d,int t)
{
	n_padre *newe=(n_padre*)malloc(sizeof(n_padre));
	if(!newe)
		return NULL;
	if(t==0){
		newe->folder=crear_n_folder(d);
		newe->archivo=NULL;
	}else{
		newe->archivo=crear_n_archivo(d);
		newe->folder=NULL;
	}
	newe->frente=NULL;
	newe->final=NULL;
	return newe;
}

n_padre *crear_nodo_a(char *d)
{
	n_padre *newe=(n_padre*)malloc(sizeof(n_padre));
	if(!newe)
		return NULL;
	strcpy(newe->archivo->nombre,d);
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
	if(strcmp(hermanos->raiz->folder->nombre,padre)==0)
		return hermanos;
	buscar_entre_hermanos(hermanos->hermano,padre);
}

int insertar_nuevo_nodo(n_padre **raiz,char *d,char *p,int ty)
{
	if(!(*raiz)){
		(*raiz)=crear_nodo_p(d,ty);
		return 1;
	}
	if(strcmp((*raiz)->folder->nombre,p)==0)
	{
		n_padre *aux_n=crear_nodo_p(d,ty);
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
			insertar_nuevo_nodo(&pb->raiz,d,p,ty);
			return 1;
		}
		if(aux->hermano)
			insertar_nuevo_nodo(&aux->hermano->raiz,d,p,ty);
		insertar_nuevo_nodo(&aux->raiz,d,p,ty);
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
		if(raiz->folder)
			printf("|-%s --F\n",raiz->folder->nombre);
		if(raiz->archivo)
			printf("|-%s --A\n",raiz->archivo->nombre);
		imprimir_hojas(raiz->frente,c+1,0);
	}
	return;
}
void eliminar(n_padre **cola,char *padre)
{
	if(!(*cola))
	{
		printf("Cola vacia. No existen elementos a eliminar\n");
		return;
	}
	hijo *buq=buscar_entre_hermanos((*cola)->frente,padre);
	printf("%p\n",buq);
	if(!buq)
	{
		printf("No existe tal elemento en la cola\n");
		return;
	}
	if((*cola)->frente==(*cola)->final)
	{
		free(buq);
		(*cola)->frente=NULL;
		(*cola)->final=NULL;
		return;
	}
	if((*cola)->frente==buq){
		(*cola)->frente=buq->hermano;
		free(buq);
		return;
	}
	eliminar_x(&(*cola)->frente,buq,&(*cola)->final);
	return;
}

void eliminar_x(hijo **cola,hijo *x,hijo **final)
{
	if((*cola)->hermano==x)
	{
		hijo *aux=x->hermano;
		(*cola)->hermano=aux;
		if(!x->hermano)
		    (*final)=aux;
		free(x);
		return;
	}
	eliminar_x(&(*cola)->hermano,x,final);
}
