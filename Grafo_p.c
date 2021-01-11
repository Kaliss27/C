/* Proyecto 2: EL predictor
s17002346 - Peralta Luna Karen Lisseth
*/
#include<GL/glut.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include<math.h>

#define l 30 //Longitud del nombre de archivo
#define wl 20 //Longitud de palabras


/**Estructuras*/

typedef struct nodo_vertice
{
	char palabra[l];  //Palabra
	float PA;  //Probabilidad de ocurrencia
	float d; //# de ocurrencia
	struct lista_adyacencia *lista_c; //inicio a lista de aristas
	struct nodo_vertice *enl_sig; //conexion con otros vertices sig
	struct nodo_vertice *enl_ant; // conexion con otros vertices ant
}vertice;

typedef struct lista_adyacencia
{
	vertice *destino; //Vertice con el que se conecta
	float peso; // Peso del arista
	struct lista_adyacencia *sig;
}arista;

typedef struct Cola
{
	vertice *frente;                  
	vertice *final;
}p_Cola;

/**Declaración de funciones para Grafos*/
vertice *alojar_vertice(char *palabra_a); //Crea espacio en memoria para un vertice del grafo, sin crear conexiones 
vertice **buscar_vertice(vertice **V,char *word_b);
int verificar_grafo(p_Cola *cola); // Verifica si existe un grafo o no
int insertar_vertice(p_Cola **grafo,char *w); //Inserta un vertice
int crear_conexiones(p_Cola **G,char *A,char *B); //Crea conexion entre dos grafos
void ver_vertices(vertice *vertices); //Visualiza vertices de un grafo
void crear_cola(p_Cola **cola); // Inicializa la cola que representa el grafo
void ver_arcos(arista *a); // Visualiza las conexiones por vertice
int leer_datos_archivo(FILE *archivo,char *p);// Lee datos de un archivo, para llenar un grafo
int cargar_grafo(p_Cola **G,char *n_file,int opc);//Crea y carga los datos en un grafo
void transformar(char *dato);
void probabilidad_ocurrencia(vertice **N); //Calcula la probabilidad de ocurrencia de una palabra
void eliminar_aristas(arista **A);
void eliminar_grafo(vertice **G);

int m; // Total de palabras contenidas en un texto

/**Función Main*/
int main (int argc, char **argv)
{
	p_Cola *G;
	crear_cola(&G);
	//cargar_grafo(&G,"don_quijote2.txt",0);
	//cargar_grafo(&G,"Lorem_ipsun.txt",0);
	//ver_vertices(G->frente);
	cargar_grafo(&G,"don_quijote2.txt",0);
	probabilidad_ocurrencia(&(G->frente));
	ver_vertices(G->frente);
	eliminar_grafo(&G->frente);
	ver_vertices(G->frente);
	//cargar_grafo(&G,"Lorem_ipsun.txt",1);
	return 0;
}
/**Definición de funciones para grafos*/
int leer_datos_archivo(FILE *file,char *p)
{
	if(feof(file))
	{
		*p='\0';
		return 2;
	}
	char c;
	fread(&c,sizeof(char),1,file);
	if(c==',' || c=='.' || c==';' || c==':' || c==0 || c==1 || c==-62 || c==-65 || c=='?' || c=='!' || c=='(' || c==')' || c==-85 || c==-69 || c=='-' || c==39 || c==34 || c=='\r' || c=='\n' || c=='\t')
	{
		if(c==-62)
			fread(&c,sizeof(char),1,file);
		*p='\0';
		return 1;
	}
	if(c==' '){
		*p='\0';
		return 0;
	}
	if(c!=-61)
	{
		transformar(&c);
		*p=tolower(c);
		p++;
	}
	return leer_datos_archivo(file,p);
}

vertice *alojar_vertice(char *palabra_a)
{
	vertice *newe=(vertice*)malloc(sizeof(vertice));
	if(!newe)
		return NULL;
	strcpy(newe->palabra,palabra_a);
	newe->lista_c=NULL;
	newe->PA=0;
	newe->d=1;
	newe->enl_sig=NULL;
	newe->enl_ant=NULL;
	return newe;
}

int verificar_grafo(p_Cola *cola)
{
	if(!(cola->frente) && !(cola->final))
		return 1;
	return 0;
}

int insertar_vertice(p_Cola **grafo,char *w)
{
	vertice **w_s=buscar_vertice(&(*grafo)->frente,w);
	if(!w_s)
		{
			vertice *newe=alojar_vertice(w);
	if(verificar_grafo((*grafo))==1)
	{
		(*grafo)->frente=newe;
		(*grafo)->final=newe;
		return 1;
	}else
	{
		(*grafo)->final->enl_sig=newe;
		newe->enl_ant=(*grafo)->final;
		(*grafo)->final=newe;
		return 1;
	}
	}
	(*w_s)->d++;
}

vertice **buscar_vertice(vertice **V,char *word_b)
{
	if((*V))
	{
		if((strcmp((*V)->palabra,word_b)==0))
			return V;
		else buscar_vertice(&(*V)->enl_sig,word_b);
	}
	else return NULL;
}

arista **buscar_arista(arista **A,vertice *V_d)
{
	if((*A))
	{
		if((*A)->destino == V_d)
			return A;
		else buscar_arista(&(*A)->sig,V_d);
	}
	else return NULL;
}

int crear_arco(vertice *V_d,arista **a)
{
	arista *newe=(arista*)malloc(sizeof(arista));
	if(!newe)
		return 0;
	newe->destino=V_d;
	newe->sig=(*a);
	newe->peso=1.0;
	(*a)=newe;
	return 1;
}

int crear_conexiones(p_Cola **G,char *A,char *B)
{
	vertice **V_o=buscar_vertice(&(*G)->frente,A);
	vertice **V_d=buscar_vertice(&(*G)->frente,B);

	arista **conexion=buscar_arista(&(*V_o)->lista_c,(*V_d));

	if(!conexion)
	{
		int bnd=crear_arco((*V_d),&(*V_o)->lista_c);
		if(bnd==1)
			return 1; // 1-> se creo nuevo arco
		else return 0;
	}
	else
	{
		(*conexion)->peso++;
		return 2; // 2-> Ya existia conexiòn, se agrego una unidad al peso
	}
	return 0;
}

int cargar_grafo(p_Cola **G,char *n_file,int opc)
{
	FILE *file_r;
	if(!(file_r=fopen(n_file,"r")))
	{
			printf("No existe el archivo\n");
			return 0;
		}
	if(feof(file_r))
		return 0;
	if(opc==1)
	{
		FILE *file_g;
		char c;
		//file_g=fopen("Grafo_completo.txt","a");
		if(!(file_g=fopen("Grafo_completo.txt","a")))
		{
			file_g=fopen("Grafo_completo.txt","w");
		}
		while(!feof(file_r))
		{
			fread(&c,sizeof(char),1,file_r);
			fwrite(&c,sizeof(char),1,file_g);
		}
		c='\n';
		fwrite(&c,sizeof(char),1,file_g);
		fwrite(&c,sizeof(char),1,file_g);
		fseek(file_r,0,SEEK_SET);
		fclose(file_g);
	}

	char word[20],A_word[20],B_word[20]; //datos->word,origen->A_word,destino->B_word
	memset(A_word,'\0',20);
	memset(B_word,'\0',20);
	int r=0; //resp->r;
	int s=0; // estado-> s
	while(r!=2){
		memset(word,'\0',20);
		r=leer_datos_archivo(file_r,word);
		if((word[0]>=97  && word[0]<=122) || (word[0]>=48 && word[0]<=57)  || (word[0]>=-96 && word[0]<=-92) || word[0]==-126 || word[0]!=0){
			m++;
			insertar_vertice(G,word);
			if(s==0){
				strcpy(A_word,word);
				s++;
			}else{
				strcpy(B_word,word);
				crear_conexiones(G,A_word,B_word);
				strcpy(A_word,B_word);
				memset(B_word,'\0',20);
			}
			if(r!=0)
				s=0;
		}
	}
	fclose(file_r);
	printf("\n\ntotal de palabras: %d\n",m);
	return 1;
}

void probabilidad_ocurrencia(vertice **N)
{
	if((*N))
	{
		(*N)->PA=(float)(((*N)->d)/m);
		return probabilidad_ocurrencia(&(*N)->enl_sig);
	}
	return;
}

void transformar(char *dato){
	int d=(int)(*dato);
	switch(d){
		case -95: case -127:
			d=160;
		break;
		case -87: case -119:
			d=130;
		break;
		case -83: case -115:
			d=161;
		break;
		case -77: case -109:
			d=162;
		break;
		case -70: case -102:
			d=163;
		break;
		case -79: case -111:
			d=164;
		break;

	}
	*dato=(char)(d);
}

void ver_vertices(vertice *vertices)
{
	if(vertices)
	{
		printf("|%s PA:%f|->",vertices->palabra,vertices->PA);
		ver_arcos(vertices->lista_c);
		printf("\n");
		ver_vertices(vertices->enl_sig);
	}
	return;
}

void ver_arcos(arista *a)
{
	if(a)
	{
	if(!a->sig)
	printf("[%s]",a->destino->palabra);
	else
	printf("[%s]-",a->destino->palabra);
	ver_arcos(a->sig);
}
	return;
	
}

void crear_cola(p_Cola **cola)
{
	(*cola)->frente=NULL;
	(*cola)->final=NULL;
	return;
}

//
void eliminar_aristas(arista **A)
{
	if(!(*A))
		return;
	arista *aux=(*A);
	(*A)=(*A)->sig;
	free(aux);
	eliminar_aristas(&(*A));
}
void eliminar_grafo(vertice **G)
{
	printf("entra a eliminar_grafo\n");
	if(!(*G))
		{
			FILE *d_file=fopen("Grafo_completo.txt","w");
			fclose(d_file);
			return;
		}
	eliminar_aristas(&(*G)->lista_c);
	vertice *aux=(*G);
	(*G)=(*G)->enl_sig;
	free(aux);
	eliminar_grafo(G);
}
