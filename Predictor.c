/* Proyecto 2: EL predictor
s17002346 - Peralta Luna Karen Lisseth
*/
#include<GL/glut.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include<math.h>

#define l 30

/**Estructuras*/

typedef struct nodo_vertice
{
	char palabra[l];
	float PA;
	float num_oc;
	struct lista_adyacencia *lista_c;
	struct nodo_vertice *enl_sig;
	struct nodo_vertice *enl_ant;
}vertice;

typedef struct lista_adyacencia
{
	vertice *destino;
	float peso;
	struct lista_adyacencia *sig;
}arista;

typedef struct Cola
{
	vertice *frente;                  
	vertice *final;
}p_Cola;

/**Declaración de funciones para Grafos*/
vertice *alojar_vertice(int clv_d); //Crea espacio en memoria para un vertice del grafo, sin crear conexiones 
int verificar_grafo(p_Cola *cola); // Verifica si existe un grafo o no
int insertar_vertice(p_Cola **grafo,int clv_d); //Inserta un vertice
int crear_conexiones(p_Cola **G,int clv_o,int clv_d); //Crea conexion entre dos grafos
void ver_vertices(vertice *vertices); //Visualiza vertices de un grafo
void crear_cola(p_Cola **cola); // Inicializa la cola que representa el grafo
void ver_arcos(arista *a); // Visualiza las conexiones por vertice
int leer_datos_archivo(FILE *archivo,char *p);


/**Declaración de funciones para dibujar*/
void reshape_cb (int w, int h);
void display_cb();
void initialize();
void dibujar_letras_encabezado(char *s);

/**Declaración de variables globales*/
char encabezado[100],nombre_archivo[100];

/**Función Main*/
int main (int argc, char **argv) {
	glutInit (&argc, argv);
	initialize();
	//glutIdleFunc(refresh);
	glutMainLoop();
	return 0;
}
/**Definición de funciones para grafos*/
int leer_datos_archivo(FILE *archivo,char *p)
{
	return 0;
}

vertice *alojar_vertice(int clv_d)
{
	vertice *newe=(vertice*)malloc(sizeof(vertice));
	if(!newe)
		return NULL;
	//newe->clv=clv_d;
	newe->lista_c=NULL;
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

int insertar_vertice(p_Cola **grafo,int clv_d)
{
	vertice *newe=alojar_vertice(clv_d);
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

vertice **buscar_vertice(vertice **V,int clv_b)
{
	/*if((*V))
	{
	if((*V)->clv==clv_b)
	return V;
	else
	buscar_vertice(&(*V)->enl_sig,clv_b);
}
	else
	return NULL;*/
	return NULL;
}

int crear_arco(vertice *V_d,arista **a)
{
	arista *newe=(arista*)malloc(sizeof(arista));
	if(!newe)
		return 0;
	newe->destino=V_d;
	newe->sig=(*a);
	(*a)=newe;
	return 1;
}

int crear_conexiones(p_Cola **G,int clv_o,int clv_d)
{
	vertice **V_o=buscar_vertice(&(*G)->frente,clv_o);
	vertice **V_d=buscar_vertice(&(*G)->frente,clv_d);
	if(V_o)
	{
		int bnd=crear_arco((*V_d),&(*V_o)->lista_c);
		if(bnd==1)
			return 1;
		else return 0;
	}
	return 0;
}

void ver_vertices(vertice *vertices)
{
	if(vertices)
	{
		//printf("|%c|->",vertices->clv);
		ver_arcos(vertices->lista_c);
		printf("\n");
		ver_vertices(vertices->enl_sig);
	}
	return;
}

void ver_arcos(arista *a)
{
	/*if(a)
	{
	if(!a->sig)
	printf("[%c]",a->destino->clv);
	else
	printf("[%c]-",a->destino->clv);
	ver_arcos(a->sig);
}*/
	return;
	
}

void crear_cola(p_Cola **cola)
{
	(*cola)->frente=NULL;
	(*cola)->final=NULL;
	return;
}
/**Definición de funciones para dibujar*/
void reshape_cb (int w, int h) {
	if (w==0||h==0) return;
	glViewport(0,0,w,h);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluOrtho2D(0,w,0,h);
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity ();
}

void display_cb() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3d(1,1,1);
	glPushMatrix();
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluOrtho2D (0,1000,1000,0);
	
	//contar_nodos(raiz);
	//asignar_posiciones(raiz,x,y,1);
	//dibujar_conexiones(raiz);
	//dibujar_vertices(raiz);
	//intervalo=0;
	
	glColor3d(0.372549,0.623529,0.623529);	//CadetBlue
	glBegin (GL_QUADS);
	glVertex2f(0,0);
	glVertex2f(1000,0);
	glVertex2f(1000,100);
	glVertex2f(0,100);	
	glEnd();
	
	
	glColor3d(1,1,1);
	glRasterPos2f(491.0f,20.0f);
	sprintf(encabezado,"Controles");
	dibujar_letras_encabezado(encabezado);
	
	
	glColor3d(1,1,1);
	glRasterPos2f(30.0f,30.0f);
	sprintf(encabezado,"Menu de funciones -> Click izquierdo ");
	dibujar_letras_encabezado(encabezado);
	
	glColor3d(1,1,1);
	glRasterPos2f(30.0f,50.0f);
	sprintf(encabezado,"Moverse -> Teclas de direccion");
	dibujar_letras_encabezado(encabezado);

	
	glPopMatrix();
	glutSwapBuffers();
}

void initialize() {
	glutInitDisplayMode (GLUT_RGBA|GLUT_DOUBLE);
	glutInitWindowSize (1000,1000);
	glutInitWindowPosition (0,0);
	glutCreateWindow ("Proyecto 2- El predictor");
	glutDisplayFunc (display_cb);
	glutReshapeFunc (reshape_cb);
	glClearColor(0.0,0.0,0.0,0.0);
	/*glutCreateMenu(0);
	glutAddMenuEntry("Anexar nuevo archivo de texto",1);
	glutAddMenuEntry("Insertar nueva frase",2);
	glutAddMenuEntry("Frases frecuentes",3);
	glutAddMenuEntry("Eliminar grafo",4);
	glutAttachMenu(GLUT_LEFT_BUTTON);*/
	
	glutCreateMenu(0);
	glutAddMenuEntry("Anexar nuevo archivo de texto",1);
	glutAddMenuEntry("Insertar nueva frase",2);
	glutAddMenuEntry("Frases frecuentes",3);
	glutAddMenuEntry("Eliminar grafo",4);
	glutAttachMenu(GLUT_LEFT_BUTTON);

}


void dibujar_letras_encabezado(char *s){
	glColor3f(0.0f,0.0f,1.0f);
	for(unsigned int i=0;i<strlen(s);i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,s[i]);
}
