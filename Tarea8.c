/* S17002346
   Peralta Luna Karen Lisseth
   Tarea 8.
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

int insertar(nodoB **axraiz,char d);
nodoB* crearNodo(char d);
void ver_Arbol(nodoB *raiz,int c,int i);
int buscar_dato(nodoB *raiz,int d);
void postorden(nodoB *raiz);
void preorden(nodoB *raiz);
void inorden(nodoB *raiz);
int separar(char *cadena,char *cad_izq,char *cad_der,nodoB **raiz);

int main(int argc, char const *argv[])
{
	nodoB *raiz=NULL;
	//char formula[]="a*(b+c)";
	char formula[]="(b+c)*a";
	//char formula[]="a+b";	
	int t_cad=strlen(formula);
	char temp,ax[t_cad],axi[t_cad];
	//printf("\nIntroduce ecuacion:");
	//scanf("%s",formula);
	//temp='*';
	//strstr(formula,&temp);
	separar(formula,axi,ax,&raiz);
	ver_Arbol(raiz,0,0);
	/*printf("\n\n preorden :");
	preorden(raiz);
	printf("\n\n inorden :");
	inorden(raiz);
	printf("\n\n postorden :");
	postorden(raiz);*/
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
char seleccionar_operador(char *cadena)
{
	char c;
	printf("%s\n\n",cadena);
	if(strchr(cadena,'+'))
		c='+';
	else
	    if(strchr(cadena,'-'))
		    c='-';
	    else
			if(strchr(cadena,'*'))
			    c='*';
		    else
			    if(strchr(cadena,'/'))
		   		    c='/';
		   	    else
	     	    	c='0';
	printf("so:%c\n",c);     	    
	return c;	     	 
}
char seleccionar_operador_f(char *cadena,int *bnd)
{
	printf("entro sof\n%s\n",cadena);
	if(!cadena)
		return '0';
	int loc,locc,len;
	len=strlen(cadena);
	char c,aux[len];
	strcpy(aux,cadena);
	printf("aux:%s\n",aux);
	if(strchr(cadena,'(') && strchr(cadena,')') ) 
	{
		locc=strcspn(cadena,"(");
		loc=strcspn(cadena,")");
		printf("%i\n",loc);
		printf("%s\n\n",cadena);
		if(loc==len-1 && locc!=0) // los signos de agrupaciòn son los ultimos en la cadena 
			{
				c=seleccionar_operador(strtok(aux,"("));
		}else{
			if(locc==0) // los signos de agrupaciòn son los primeros en la cadena 
			{
				c=seleccionar_operador(strstr(cadena,")")+1);
				return c;
			}
		printf("ax2:%s\n",strcpy(aux,cadena));
		c=seleccionar_operador(strtok(aux+1,")"));	
		*bnd=1;
		printf("sef:%c\n",c);   
		return c;
	}
    }
    printf("%s\n",cadena);
	c=seleccionar_operador(cadena);   	    
	printf("c:%c\n",c);
	return c;	     	    
}
void separar_cadenas(char *cad_i,char *cad_d,char *cad,char *c)
{
	char *temp,cc;
	cc=*c;
	strcpy(cad_d,cad);
	strcpy(cad_i,cad);
	cad_i=strtok(cad_i,c);
	printf("%s\n",cad_i);
	strcpy(cad_d,strstr(cad_d,&cc)+1);
	printf("%s\n",cad_d);
	return;
}

int separar(char *cadena,char *cad_izq,char *cad_der,nodoB **raiz)
{
	if(!cadena)
	{
		printf("%s\n",cadena);
		return 0;
	}
	printf("entro sep\nraiz:%p\n",(*raiz));
	int bnd=0,bnd_o=0,len_c;
	len_c=strlen(cadena);
	char c,temp,axi[len_c],auxd[len_c],aux_i[len_c];
	//printf("%c\n",c);
	c=seleccionar_operador_f(cadena,&bnd_o);
	//printf("hii\n");
	printf("sep:%c\nlen:%i",c,len_c);
	//insertar(raiz,c);
	if(bnd_o==1)
		{
			printf("si ()\n");
			insertar(raiz,c);
			//printf("c:%c\ncadena izq:%s\ncadena der:%s\n",c,cad_izq,cad_der);
			separar_cadenas(cad_izq,cad_der,cadena,&c);
			printf("cadena izq:%s\ncadena der:%s\n",cad_izq,cad_der);
		}else{
			if(c=='0')
	        {
	        	//insertar(raiz,*cadena);
		        printf("no hay operadores\n");
	            insertar(raiz,*cadena);
 		        return 0;
	        }
			insertar(raiz,c);
			separar_cadenas(cad_izq,cad_der,cadena,&c);
			printf("c:%c\ncadena izq:%s\ncadena der:%s\n",c,cad_izq,cad_der);
		}/*
	if(bnd_o==1)
	{
		strcpy(aux_i,cadena);
		strcpy(aux_i,strtok(aux_i+1,")"));
		bnd=1;
		printf("Cadena 1:%s\n",aux_i);
		c=seleccionar_operador_f(strstr(cadena,")"),&bnd_o);
		strcpy(cad_der,strstr(cadena,")")+1);
	}else{
		strcpy(cad_der,cadena);
        cad_der=strstr(cad_der,&c);
	    strcpy(cad_der,cad_der+1);
	}
    printf("c:%c\nvuelta\n",c);
	insertar(raiz,c);
	if(bnd==1)
		strcpy(cad_izq,aux_i);
	else
	{
		strcpy(cad_izq,cadena);
		strtok(cad_izq,&c);
	}
	printf("cadena izq:%s\ncadena der:%s\n",cad_izq,cad_der);*/
	//printf("c:%c\ncadena izq:%p\ncadena derii:%p\n",c,cad_izq,cad_der);
	//printf("raiz->izq:%p\nraiz->der:%p\n",(*raiz)->izq,(*raiz)->der);
	if(!(*raiz)->izq)
		{
			printf("%p\ncadena:%s\n",(*raiz)->izq,cad_izq);
			separar(cad_izq,axi,auxd,&(*raiz)->izq);
			printf("%p\n",(*raiz)->izq);
	}if(!(*raiz)->der){
		//printf("%s\n",cad_der+1);
		printf("%p\n",(*raiz)->der);
		separar(cad_der,axi,auxd,&(*raiz)->der);
	}
	return 0;        		
}
///////////INSERTAR NODO A ARBOL BINARIO////////////////////////
int insertar(nodoB **axraiz,char d)
{
	if(!(*axraiz)){
		(*axraiz)=crearNodo(d);
		return 1;
	}
	return 0;
	/*if(d>(*axraiz)->dato){
	    insertar(&(*axraiz)->der,d);
	}else{
		if((*axraiz)->dato==d) return 2;
		insertar(&(*axraiz)->izq,d); 
	}*/
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
