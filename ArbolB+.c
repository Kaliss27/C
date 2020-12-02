/*
** Proyecto 1: Arbol-B+ **
** S17002346 Peralta Luna Karen Lisseth
*/
#include <stdio.h>
#include <stdlib.h>

#define D 2 

/*Estructuras*/

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

/* Declaracion de Funciones*/

int insercion(page **raiz,int id);
page *crear_pagina(int d);
page *crear_pagina_p(); 
clave *crear_clave(int d);
datos *crear_datos(int d);
void ver_claves_en_pag(clave *inicio);
void insertar_claves_en_pag(clave **raiz_p,int d);
int calcular_m(clave *raiz);
clave ** clave_centro(clave **raiz, int c);
clave *crear_pag_izq();
void modificar_clave(clave **clv,int aux);
void modificar_paginas(page **raiz,clave **centro,page **ant,page **abajo);
clave **buscar_clave(page  **raiz,int id_b);
clave **buscar_clave_en_pag(clave **inicio,int id_b);

int main(int argc, char const *argv[])
{
	page *raiz=NULL;
	insercion(&raiz,35);
	insercion(&raiz,30);
	insercion(&raiz,27);
	insercion(&raiz,18);
	insercion(&raiz,7);
	ver_claves_en_pag(raiz->ant->inicio);
    printf("\t");
    ver_claves_en_pag(raiz->inicio);
    printf("\t");
    clave *aux=raiz->inicio;
    ver_claves_en_pag(aux->abajo->inicio);
    printf("\n");
    int b=35;
    if(buscar_clave(&raiz,b))
    	printf("%i Encontrado\n",b);
    else
    	printf("# no encontrado\n");
	return 0;
}
/*Cuerpo de funciones*/

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

clave ** clave_centro(clave **raiz, int c) //Obtiene la clave que se encuentre al centro de una pagina
{
    if (!raiz)
        return NULL;
    if (c == D)
        return raiz;
    return clave_centro(&(*raiz)->sig,c+1);
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
page *crear_pagina_p( ) // Aloja espacio de memoria para cada pagina
{
	page *newe=(page*)malloc(sizeof(page));
	if(!newe)
		return NULL;
	newe->inicio=NULL;
	newe->ant=NULL;
	return newe;
}

int calcular_m(clave *raiz) // Cuenta los elementos alojados en una pagina
{
	if (!raiz) return 0;
    return 1 + calcular_m(raiz->sig);
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

clave *crear_pag_izq() // Aloja espacio de memoria para un elemento clave inicial, que podrà ser usado en nuevas paginas
{
	clave *newe=(clave*)malloc(sizeof(clave));
	if(!newe)
		return NULL;
	newe->clv=0;
	newe->datos_alm=NULL;
	newe->abajo=NULL;
	newe->sig=NULL;
	return newe;
}

clave **buscar_clave_en_pag(clave **inicio,int id_b)
{
	if(!(*inicio))
		return NULL;
	if((*inicio)->clv == id_b)
		return inicio;
	return buscar_clave_en_pag(&(*inicio)->sig,id_b);
}
clave **buscar_clave(page  **raiz,int id_b)
{
	if((*raiz))
	{
		clave **aux=buscar_clave_en_pag(&(*raiz)->inicio,id_b);
		if(aux)
			return aux;
		clave *aux_c=(*raiz)->inicio;
		if(id_b < aux_c->clv)
			return buscar_clave(&(*raiz)->ant,id_b);
		clave *aux_c1=aux_c->sig;
		if(aux_c->clv < id_b < aux_c1->clv)
			return buscar_clave(&(*raiz)->inicio->abajo,id_b);
		aux_c1=aux_c1->sig;
		if(id_b > aux_c1->clv)
			return buscar_clave(&aux_c1->abajo,id_b);
	}
	else
		return NULL;
}

void modificar_clave(clave **clv,int aux) //Modifica claves de una pagina raiz o no hoja
{
	(*clv)->clv=aux;
	(*clv)->sig=NULL;
	(*clv)->datos_alm=NULL;
	return;
}
void modificar_paginas(page **raiz,clave **centro,page **ant,page **abajo) // Partir pagina...
{        																	//Sube la clave central a la pagina antecesora
	clave *aux_c=crear_pag_izq();											//Acomoda en puntero anterior de la pagina, y 
	(*ant)->inicio=(*raiz)->inicio;											// el puntero "abajo" de cada elemento de la pagina
	(*raiz)->ant=(*ant);
	aux_c->abajo=(*abajo);
	modificar_clave(&aux_c,(*centro)->clv);
	(*abajo)->inicio=(*centro);
	(*raiz)->inicio=aux_c;
	(*raiz)->inicio->abajo=(*abajo);
	(*centro)=NULL;
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
	if(calcular_m((*raiz)->inicio) > 2*D)
	{
		clave **centro=clave_centro(&(*raiz)->inicio,0);
		page *n_ant=crear_pagina_p();
		page *n_abajo=crear_pagina_p();
		if(!(n_ant || n_abajo))
			return 0;
		modificar_paginas(raiz,centro,&n_ant,&n_abajo); //Modifica la estructura del arbol.
	return 1;
    }
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
