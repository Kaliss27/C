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
	struct claves_en_paginas *ant; //Lista doble enlazada
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
clave *crear_pag_izq(); //*
void modificar_clave(clave **clv,int aux);
void modificar_paginas(page **raiz,clave **centro,page **ant,page **abajo);
clave **buscar_clave(page  **raiz,int id_b);
clave **buscar_clave_en_pag(clave **inicio,int id_b);
void subir_clave(clave **actual,clave *sig,page *abajo);
//****Fuciones para relizar el metodo bubblesort para ordenar las claves en una pagina
void bubble_sort(clave **inicio); 
void swap(clave **aux1,clave **aux2,clave **new_f);
int count_elem(clave *inicio,int c);
void ordenamiento(clave **inicio,int n_elem);

int main(int argc, char const *argv[])
{
	page *raiz=NULL;
	insercion(&raiz,10);
	insercion(&raiz,27);
	insercion(&raiz,53);
	insercion(&raiz,68);
	insercion(&raiz,80);
	insercion(&raiz,43);
	insercion(&raiz,21);
	insercion(&raiz,77);
	insercion(&raiz,58);
	insercion(&raiz,63);
	insercion(&raiz,15);
	insercion(&raiz,37);
	insercion(&raiz,41);
	insercion(&raiz,72);
	insercion(&raiz,39); 
	insercion(&raiz,95);
	insercion(&raiz,70);
	insercion(&raiz,38);
	insercion(&raiz,78);
	insercion(&raiz,82);//
    int b=50;
    if(buscar_clave(&raiz,b))
    	printf("%i Encontrado\n",b);
    else
    	printf("#%i no encontrado\n",b);
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
	newe->ant=NULL;
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
	if(!(*raiz_p))
		newe->ant=(*raiz_p);
	else
		(*raiz_p)->ant=newe;
	newe->sig=(*raiz_p);
	(*raiz_p)=newe;
	return;
}

void insertar_claves_en_pag_n(clave **raiz_p,clave *newe) // Interta claves en una pagina
{
	if(!(*raiz_p))
		return;
	if(!(*raiz_p))
		newe->ant=(*raiz_p);
	else
		(*raiz_p)->ant=newe;
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

clave **buscar_clave_mayor(clave **inicio,int id_b)
{
	if(!(*inicio))
		return NULL;
	clave *aux=(*inicio)->sig;
	if(!aux)
	{
		if((*inicio)->clv < id_b)
			return inicio;
		return  buscar_clave_en_pag(&(*inicio)->sig,id_b);
	}
	if(((*inicio)->clv < id_b) && (aux->clv > id_b))
		return inicio;
	return buscar_clave_mayor(&(*inicio)->sig,id_b);
}

clave **buscar_clave_en_pag(clave **inicio,int id_b) //Busca una clave dentro de una pagina dada
{
	if(!(*inicio))
		return NULL;
	if((*inicio)->clv == id_b)
		return inicio;
	return buscar_clave_en_pag(&(*inicio)->sig,id_b);
}
clave **buscar_clave(page  **raiz,int id_b) //Busca la clave en todo el arbol, de acuerdo a sus condiciones
{
	if((*raiz))
	{
		clave **aux=buscar_clave_en_pag(&(*raiz)->inicio,id_b);
		if(aux){
			if(!((*raiz)->ant) && !((*aux)->abajo))
				return aux;
			return buscar_clave(&(*aux)->abajo,id_b);
		}
		clave **aux_m=buscar_clave_mayor(&(*raiz)->inicio,id_b);
		if(aux_m && (*aux_m)->abajo)
			return buscar_clave(&(*aux_m)->abajo,id_b);
		return buscar_clave(&(*raiz)->ant,id_b);
	}
		return NULL;
}
void modificar_clave(clave **clv,int aux) //Modifica claves de una pagina raiz o no hoja
{
	(*clv)->clv=aux;
	(*clv)->sig=NULL;
	(*clv)->ant=NULL;
	(*clv)->datos_alm=NULL;
	return;
}
void modificar_paginas(page **raiz,clave **centro,page **ant,page **abajo) // Partir pagina...
{        																	//Sube la clave central a la pagina antecesora
	clave *aux_c=crear_pag_izq();	
	clave *aux_c1=(*centro)->sig;
	clave *aux_c2=(*centro)->ant;										//Acomoda en puntero anterior de la pagina, y 

	(*ant)->inicio=(*raiz)->inicio;
	if(!(*raiz)->ant)										// el puntero "abajo" de cada elemento de la pagina
		(*raiz)->ant=(*ant);
	else
	{
		(*ant)->ant=(*raiz)->ant;
		(*raiz)->ant=(*ant);
	}
	aux_c->abajo=(*abajo);
	(*centro)->ant=NULL;
	modificar_clave(&aux_c,(*centro)->clv);
	if(!(*centro)->abajo)
		(*abajo)->inicio=(*centro);
	else
		{
			(*abajo)->ant=(*centro)->abajo;
			(*abajo)->inicio=aux_c1;
			aux_c1->ant=NULL;
		}
	(*raiz)->inicio=aux_c;
	(*raiz)->inicio->abajo=(*abajo);
	(*centro)=NULL;
	return;
}
void acomodar_clave(clave **e_clave,page *e_page,clave **e_clnew)
{
	clave *aux=(*e_clave)->sig;
	if((aux) && (aux->ant))
	{
		(*e_clnew)->ant=(*e_clave);
		(*e_clnew)->sig=aux;
		aux->ant=(*e_clnew);
	}
	else
	{
		if((*e_clave)->ant)
			{
				(*e_clnew)->ant=(*e_clave);
			}
		else
			if((*e_clave)->sig)
				{
					(*e_clnew)->sig=aux;
				}
				else
				{
					(*e_clnew)->ant=(*e_clave);
				}
	}
	(*e_clave)->sig=e_page->inicio;
	(*e_clave)->abajo=e_page->ant;
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
	int bnd2;
	if((*raiz)->ant && id<(*raiz)->inicio->clv) //Verifica si existen paginas anteriores y corrobora que el numero a insertar sea menor
	{
		bnd2=insercion(&(*raiz)->ant,id);     //inicial de la pagina
		if((*raiz)->ant->ant && bnd2 == 2)
		{
			clave *axx1=(*raiz)->ant->inicio; 
			page *axx_a=(*raiz)->ant->ant; 

			(*raiz)->inicio->ant=axx1;
			axx1->sig=(*raiz)->inicio;
			(*raiz)->inicio=axx1;

			(*raiz)->ant=axx_a;
			return 1;

		}
		return 1;
	}
	clave **aux_mayor=buscar_clave_mayor(&(*raiz)->inicio,id);
	int bnd=0;
	if(aux_mayor && ((*aux_mayor)->abajo))
		{
			bnd2=insercion(&(*aux_mayor)->abajo,id); //Inserta sin llevarse arriba a otra clave..
			if((*aux_mayor)->abajo->ant && bnd2 == 2)
			{
				clave *aux_cl=(*aux_mayor);
				page *aux_pg1=aux_cl->abajo;
				acomodar_clave(&aux_cl,aux_cl->abajo,&aux_pg1->inicio); //Lleva arriba una clave
			}
			bnd=1;
		}
	if(bnd==0)
		insertar_claves_en_pag(&(*raiz)->inicio,id);
	ordenamiento(&(*raiz)->inicio,count_elem((*raiz)->inicio,0)+1);
	if(calcular_m((*raiz)->inicio) > 2*D)
	{
		clave **centro=clave_centro(&(*raiz)->inicio,0);
		page *n_ant=crear_pagina_p();
		page *n_abajo=crear_pagina_p();
		if(!(n_ant || n_abajo))
			return 0;
		modificar_paginas(raiz,centro,&n_ant,&n_abajo); //Modifica la estructura del arbol.
	return 2; //Pagina llena
    }
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
//******Ordena claves en una pagina
int count_elem(clave *inicio,int c)
{
	if(!inicio)
		return c;
	c++;
	return count_elem(inicio->sig,c);
}
void swap(clave **aux1,clave **aux2,clave **new_f)
{
	clave *aux=(*aux1);
	clave *auxx=(*aux1)->ant;

	(*aux1)=(*aux2);
	(*aux2)=aux;
	(*aux1)->ant=(*aux2)->ant;
	(*aux2)->ant=(*aux1);
	(*aux2)->sig=(*aux1)->sig;

	(*aux1)->sig=(*aux2);

	aux=(*aux2)->sig;
	if(aux)     //Verifica si se cambia con el ultimo elemento de la lista
		aux->ant=(*aux2);

	if(auxx)    //Verifica si se cambia con el primer elemento de la lista
	{
		auxx->sig=(*aux1);
	}

	if(!(*aux1)->ant)  //Modifica el puntero a inicio de la lista, en caso de que el primer elemento haya cambiado
		(*new_f)=(*aux1);

	return;
}

void bubble_sort(clave **inicio) 
{
	if (!(*inicio))
	{
		return;
	}
	clave *actual,*siguiente;
	actual=(*inicio);
	siguiente=(*inicio)->sig;
	
	while(siguiente)
	{
		if(actual->clv > siguiente->clv)
			swap(&actual,&siguiente,inicio);
		actual=siguiente;
	    siguiente=siguiente->sig;
	}
	bubble_sort(&(*inicio)->sig);
	return;
}
void ordenamiento(clave **inicio,int n_elem)
{
	for(int i=0;i<n_elem;i++)
	{
		bubble_sort(inicio);
	}
}
