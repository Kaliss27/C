/*
** Proyecto 1: Arbol-B+ **
** S17002346 Peralta Luna Karen Lisseth
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct datos_almacenados   //Estructura que almacenara los datos pertenecientes a cada clave
{
	int id;
}datos;

typedef struct claves_en_paginas // Estructura para almacenar los datos contenidos por un elemento pagina
{
	int clv;
	datos *datos_alm;
	struct claves_en_paginas *sig;
	struct pagina *abajo;
}clave;

typedef struct pagina // Estructura para almacenar los distintos elementos pagina
{
	clave *inicio;
	struct pagina *ant;
}page;

int insercion(page **raiz,int id);
page *crear_pagina(int d);
clave *crear_clave(int d);
void ver_claves_en_pag(clave *inicio);
void insertar_claves_en_pag(clave **raiz_p,int d);

int main(int argc, char const *argv[])
{
	page *raiz=NULL;
	insercion(&raiz,35);
	insercion(&raiz,30);
	insercion(&raiz,27);
	insercion(&raiz,18);
	insercion(&raiz,7);
	ver_claves_en_pag(raiz->inicio);
    printf("\n");
	return 0;
}

datos *crear_datos(int d)  //Aloja espacio de memoria para los datos a almacenar
{
	datos *newe=(datos*)malloc(sizeof(datos));
	if(!newe)
		return NULL;
	newe->id=d;
	return newe;
}

clave *crear_clave(int d) //Aloja espacio de memoria para almacenar las claves a alojar en una pagina
{
	clave *newe=(clave*)malloc(sizeof(clave));
	if(!newe)
		return NULL;
	newe->clv=d;
	newe->datos_alm=crear_datos(d);
	newe->abajo=NULL;
	newe->sig=NULL;
	return newe;
}

page *crear_pagina(int d) // Aloja espacio de memoria para cada pagina
{
	page *newe=(page*)malloc(sizeof(page));
	if(!newe)
		return NULL;
	newe->inicio=crear_clave(d);
	newe->ant=NULL;
	return newe;
}

void insertar_claves_en_pag(clave **raiz_p,int d) // Interta claves en una pagina
{
	if(!(*raiz_p))
		return;
	clave *newe=crear_clave(d);
	newe->sig=(*raiz_p);
	(*raiz_p)=newe;
	return;
}
int insercion(page **raiz,int id) // Operacion general de insercion
{
	if(!(*raiz))
	{
		(*raiz)=crear_pagina(id);
		if(raiz)
			return 1;
	}
	insertar_claves_en_pag(&(*raiz)->inicio,id);
	/*clave *newe=crear_clave(id);
	newe->sig=(*raiz)->inicio;
	(*raiz)->inicio=newe;*/
	return 1;

}
void ver_claves_en_pag(clave *inicio) // VIsualiza las claves contenidas en una pagina
{
	if(inicio)
	{
		printf("|%i",inicio->clv);
		ver_claves_en_pag(inicio->sig);
	}
	return;
}