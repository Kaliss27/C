/*
** Proyecto 1: Arbol-B+ **
** S17002346 Peralta Luna Karen Lisseth
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/time.h>

#define D 2 
#define tn 20

/*Estructuras*/

typedef struct datos_almacenados   //Estructura que almacenara los datos pertenecientes a cada clave
{
	int id;
	char nombre_p[tn];
	char apellido_pp[tn];
	char apellido_pm[tn];
	int edad;
	char piso[tn];
	int cama;
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
void ver_claves_en_pag(clave *inicio,int c,int i); 
void insertar_claves_en_pag(clave **raiz_p,int d);
void ver_paginas(page *inicio_p,int c,int i);
int calcular_m(clave *raiz);
clave ** clave_centro(clave **raiz, int c);
clave *crear_pag_izq(); //*
void modificar_clave(clave **clv,int aux);
void modificar_paginas(page **raiz,clave **centro,page **ant,page **abajo);
clave **buscar_clave(page  **raiz,int id_b);
clave **buscar_clave_en_pag(clave **inicio,int id_b);
void tiempo_busqueda(page **raiz,int b); 
void subir_clave(clave **actual,clave *sig,page *abajo);
void eliminar(page **raiz,int id_b);
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
	insercion(&raiz,29);
	insercion(&raiz,17);
	insercion(&raiz,25);
	insercion(&raiz,21);
	insercion(&raiz,15);
	insercion(&raiz,31);
	insercion(&raiz,13);
	insercion(&raiz,51);
	insercion(&raiz,20);
	insercion(&raiz,24);
	insercion(&raiz,48);
	insercion(&raiz,19);
	insercion(&raiz,60); 
	insercion(&raiz,45);
	insercion(&raiz,66);
	/*insercion(&raiz,38);
	insercion(&raiz,78);
	insercion(&raiz,82);/*/
/*
	eliminar(&raiz,15);
	eliminar(&raiz,51);
	eliminar(&raiz,48);
	eliminar(&raiz,60);
	eliminar(&raiz,31);
	eliminar(&raiz,17);
	eliminar(&raiz,21);*/
	//eliminar(&raiz,19);
	//eliminar(&raiz,13);

    int b=27;
    tiempo_busqueda(&raiz,b);

    ver_paginas(raiz,0,0);
	return 0;
}
/*Cuerpo de funciones*/

datos *crear_datos(int d)  //Aloja espacio de memoria para los datos a almacenar
{
	datos *newe=(datos*)malloc(sizeof(datos));
	if(!newe)
		return NULL;
	//fflush(stdin);
	newe->id=d;
	newe->nombre_p[0]='s';
	/*printf("\nNombre del paciente:");
	scanf("%s",newe->nombre_p);
	printf("\nApellido Paterno:");
	scanf("%s",newe->apellido_pp);
	printf("\nApellido Materno:");
	scanf("%s",newe->apellido_pm);
	printf("\nEdad:");
	scanf("%i",&newe->edad);
	printf("\nPiso:");
	scanf("%s",newe->piso);
	printf("\nCama:");
	scanf("%i",&newe->cama);*/
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
/**/
long long cronomsec(int startstop)
{
  static long long pre_time;
  struct timeval tv;

  if (startstop)
    {
      gettimeofday(&tv, NULL);      
      pre_time=tv.tv_sec*1000+tv.tv_usec/1000;
    }
  else
    {      
      gettimeofday(&tv, NULL);      
      return tv.tv_sec*1000+tv.tv_usec/1000 - pre_time;
    }
    return 0;
}

void tiempo_busqueda(page **raiz,int b) //REaliza la busqueda de una clave y mide el tiempo que se tarda en realizarla
{
	time_t start_t, end_t;
	double total_t;
	time(&start_t);
	clave **aux=buscar_clave(raiz,b);
	time(&end_t);
	if(aux)
    	printf("#%i Encontrado\n",b);
    else
    	printf("#%i no encontrado\n",b);
    printf("Tiempo de busqueda:%lld mls\n",cronomsec(end_t-start_t));
    return;
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

clave **mas_der_rama_izq(clave **claves) //Busca clave mas a la derecha de una rama
{
	if(!(*claves)->sig)
		return claves;
	return mas_der_rama_izq(&(*claves)->sig);
}

clave **mas_izq_rama_der(clave **claves) //Busca clave mas a la izquierda de una rama
{
	if(!(*claves)->ant)
		return claves;
	//return mas_izq_rama_der(&(*claves)->sig);
}

clave **localizar_rama(clave **e_clave,int *m) // Localiza rama con m<d
{
	if(!(*e_clave))
		return NULL;
	*m=calcular_m((*e_clave)->abajo->inicio);
	if(*m < D)
	{
		return e_clave;
	}
	return localizar_rama(&(*e_clave)->sig,m);
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

int eliminar_clave_p(clave **e_clvp,int id_b,int bnd) //Elimina x clave de una pag
{
	if(!(*e_clvp))
		return 0;
	clave *aux1;
	if((*e_clvp)->clv == id_b)
	{
		if(!(*e_clvp)->ant)
		{
			aux1=(*e_clvp)->sig;
			aux1->ant=NULL;
		}
		clave *aux2 = (*e_clvp);
		(*e_clvp) = (*e_clvp)->sig;
		free(aux2); 
		bnd=1;
		if((*e_clvp) == NULL){
			return 1;
		}
    return eliminar_clave_p(&(*e_clvp)->sig,id_b,bnd);
}
return eliminar_clave_p(&(*e_clvp)->sig,id_b,bnd);
}

int eliminar_camino(page **raiz,int id_b)
{
	if((*raiz))
	{
		clave **aux=buscar_clave_en_pag(&(*raiz)->inicio,id_b);
		if(aux){
			if(!((*raiz)->ant) && !((*aux)->abajo))
				{
					int d=eliminar_clave_p(&(*raiz)->inicio,id_b,0);
					return 1;

				}
			return eliminar_camino(&(*aux)->abajo,id_b);
		}
		clave **aux_m=buscar_clave_mayor(&(*raiz)->inicio,id_b);
		if(aux_m && (*aux_m)->abajo)
			{
				eliminar_camino(&(*aux_m)->abajo,id_b);
				int m=0;
				clave **aux_m=localizar_rama(&(*raiz)->inicio,&m);
				if(m<D)
				{
					clave **aux_c1;
					if(!(*aux_m)->sig)
					{
						aux_c1=mas_der_rama_izq(&(*aux_m)->ant->abajo->inicio);
						clave *aux_a1=(*aux_c1)->ant;
						(*aux_c1)->sig=(*aux_m)->abajo->inicio;
						(*aux_m)->abajo->inicio->ant=(*aux_c1);
						(*aux_c1)->ant=NULL;
						(*aux_m)->abajo->inicio=(*aux_c1);
						(*aux_m)->clv=(*aux_m)->abajo->inicio->clv;
						aux_a1->sig=NULL;
					    return 1;
				    }
				    aux_c1=NULL;
				    if((*aux_m)->sig)
				    {
				    	aux_c1=mas_izq_rama_der(&(*aux_m)->sig->abajo->inicio);
				    	return 1;
				    }
				}
				return 1;
			}
		return eliminar_camino(&(*raiz)->ant,id_b);
	}
		return 0;
}

void eliminar(page **raiz,int id_b)
{
	clave **clv_b=buscar_clave(raiz,id_b);
	if(clv_b)
	{
		eliminar_camino(raiz,id_b);
	}
}


//*****Ver Arbol B+*******
void ver_claves_en_pag(clave *inicio,int c,int i) // VIsualiza las claves contenidas en una pagina
{
	if(inicio)
	{
		for(i=0;i<c;i++)
			printf(" ");
		datos *data_p=inicio->datos_alm;
		printf("|%i - %s\n",inicio->clv,data_p->nombre_p);
		ver_claves_en_pag(inicio->sig,c,i);
	}
	return;
}

void ver_ramas(page *rama,int c,int i)
{
	if(rama)
		if(rama->ant)
		{
			printf("|-");
			ver_paginas(rama,c,0);
		}
		else
		{
			ver_claves_en_pag(rama->inicio,c+1,0);
		}
		ver_paginas(rama->inicio->abajo,c+1,0);
		clave *aux=rama->inicio->sig;
		if(aux)
			ver_paginas(aux->abajo,c,0);
		return;
}

void ver_paginas(page *inicio_p,int c,int i)
{
	if(inicio_p)
	{
		for(i=0;i<c;i++)
		{
			printf(" ");
		}
		printf("|\n");
		if(inicio_p->ant)
			ver_ramas(inicio_p->ant,c+1,0);
		else
			return ver_claves_en_pag(inicio_p->inicio,c+1,0);
		if(i==0)
			ver_ramas(inicio_p->inicio->abajo,c,0);
	}
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