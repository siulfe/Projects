#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Pequeño programa de muestra, sobre el uso de los arboles de datos y la recursividad en lenguaje C
siendo el hijo1 en caso de que la palara sea mayor, y hijo 2 en caso de que sea menor
*/

typedef struct palabra{
	palabra *padre;
	palabra *hijo1;
	palabra *hijo2;
	char palabra[120];
	char significado[255]; 
}*p;

p inicio=NULL;

void menu();
void agregar();
void eliminar();
void buscar();
void listar(p puntero);

//subFunciones
void insertar(p puntero,p *padre,p *abuelo);
void eliminarPuntero(char palab[120],p *puntero);
void agregarPuntero(p *puntero,p *padre);
void conseguir(char palab[120],p puntero);
int verificar();
int encontrar(char palab[120],p puntero);
p nuevoPuntero();


int main(){
	int respuesta=0,salir=5;
	
	do{
		menu();
		scanf("%d",&respuesta);
	
		switch(respuesta){
			case 1: agregar(); break;
			case 2: eliminar(); break;
			case 3: buscar(); break;
			case 4: system("cls");
					if(verificar()==1)
						break;
					printf("Listado: \n\n"); 
					listar(inicio);  
					system("pause"); 
					break;
		}
		
		 system("cls");
		 
	}while(respuesta!=salir);
	
	
	printf("\n ADIOS, QUE TENGA UN BUEN DIA");
	
	return 0;
	
}


void menu(){
	printf("BIENVENIDO, ESTE ES UN PROGRAMA DE PRUEBA CREADO POR EL GOCHO, ESPERO SEA DE SU AGRADO\n\n");
	printf("1-AGREGAR\n2-ELIMINAR\n3-BUSCAR\n4-LISTAR\n5-SALIR\n\n-");
	fflush(stdin);
}

void agregar(){
	system("cls");
	
	p puntero=nuevoPuntero();
	fflush(stdin);
	printf("Ingrese una palabra\n-");
	gets(puntero->palabra);
	
	fflush(stdin);
	printf("Ingrese el significado de la palabra\n-");
	gets(puntero->significado);
	
	if(encontrar(puntero->palabra,inicio)==0)
		return;
	
	insertar(puntero,&inicio,NULL);
	
}

void eliminar(){
	char palab[120];
	
	system("cls");
	
	if(verificar()==1)
		return;

	fflush(stdin);
	printf("Ingrese palabra a eliminar: "); gets(palab);
	
	eliminarPuntero(palab,&inicio);
	
}

void buscar(){
	char palab[120];
	system("cls");
	
	if(verificar()==1)
		return;
	
	fflush(stdin);
	printf("Ingrese palabra a buscar: ");
	gets(palab);
	
	conseguir(palab,inicio);
	
	
}

void listar(p puntero){
	if(puntero==NULL)
		return;
	
	fflush(stdin);	
	printf("Palabra: '%s'\nSignificado: %s\n\n",puntero->palabra,puntero->significado);
	
	if(puntero->hijo1!=NULL)
		listar(puntero->hijo1);
		
	if(puntero->hijo2!=NULL)
		listar(puntero->hijo2);
		
}

void insertar(p puntero,p *padre,p *abuelo){
	
	if(*padre==NULL){
		if(abuelo!=NULL)
			puntero->padre=*abuelo;
		*padre=puntero;
		return;
	}
	
	p ayudante=*padre;
	
	if(ayudante->palabra[0]<puntero->palabra[0]){
		return insertar(puntero,&ayudante->hijo1,&ayudante);
	}else{
		return insertar(puntero,&ayudante->hijo2,&ayudante);
	}
	
}

void eliminarPuntero(char palab[120],p *puntero){
	char respuesta[120];
	
	
	if(*puntero==NULL){
		fflush(stdin);
		printf("NO SE ENCONTRO LA PALABRA EN LA LISTA\n");
		system("pause");
		return;
	}
	
	p ayudante=*puntero;
	
	if(strcmp(ayudante->palabra,palab)==0){
		printf("PALABRA ENCONTRADA EN LA LISTA, SEGURO DE QUERER ELIMINARLA s/n \n");
		gets(respuesta);
		
		if(respuesta[0]!='s')
			return;
		
		if(ayudante->padre==NULL){
			p ayudante2=NULL;
			
			if(ayudante->hijo2!=NULL && ayudante->hijo1!=NULL){
				agregarPuntero(&ayudante->hijo2,&ayudante->hijo1);
				ayudante2=ayudante->hijo1;
			}else if(ayudante->hijo1!=NULL){
				ayudante2=ayudante->hijo1;
			}else if(ayudante->hijo2!=NULL){
				ayudante2=ayudante->hijo2;
			}
			
			ayudante->hijo1=NULL;
			ayudante->hijo2=NULL;
			
			free(ayudante);
			
			inicio=ayudante2;
			
			return;
		}
		
		if(ayudante->padre->palabra[0]<ayudante->palabra[0])
			ayudante->padre->hijo1=NULL;
		else
			ayudante->padre->hijo2=NULL;
			
		if(ayudante->hijo1!=NULL)
			agregarPuntero(&ayudante->hijo1,&inicio);
		
		if(ayudante->hijo2!=NULL)
			agregarPuntero(&ayudante->hijo2,&inicio);
			
		ayudante->hijo1=NULL;
		ayudante->hijo2=NULL;
			
		free(ayudante);
		
		return;
		
	}
	
	
	if(ayudante->palabra[0]<palab[0]){
		eliminarPuntero(palab,&ayudante->hijo1);
	}else{
		eliminarPuntero(palab,&ayudante->hijo2);
	}
		
	
}

void agregarPuntero(p *puntero,p *padre){
	
	if(*padre==NULL){
		*padre=*puntero;
		return;
	}
	
	p ayudante1=*puntero, ayudante2=*padre;
	
	if(ayudante2->palabra[0]<ayudante1->palabra[0])
		agregarPuntero(&ayudante1,&ayudante2->hijo1);
	else
		agregarPuntero(&ayudante1,&ayudante2->hijo2);
}

void conseguir(char palab[120],p puntero){
	
	if(puntero==NULL){
		printf("NO SE ENCONTRO LA PALABRA EN LA LISTA GUARDADA\n");
		system("pause");
		return;
	}
	
	
	
	if(strcmp(puntero->palabra,palab)!=0){
		if(puntero->palabra[0]<palab[0])
			return conseguir(palab,puntero->hijo1);
		else
			return conseguir(palab,puntero->hijo2);
	}
	
	printf("PALABRA CONSEGUIDA\nPalabra: %s\nSignificado: %s\n",puntero->palabra,puntero->significado);
	system("pause");
	
}

int verificar(){
	
	if(inicio==NULL){
		printf("SIN DATOS EN LA LISTA\n");
		system("pause");
		return 1;
	}
	
	return 0;	
}

int encontrar(char palab[120],p puntero){
	
	if(puntero==NULL){
		return 1;
	}
	
	if(strcmp(palab,puntero->palabra)==0){
		fflush(stdin);
		printf("\nPALABRA EXISTENTE\n");
		system("pause");
		return 0;
	}
	
	if(puntero->palabra[0]<palab[0])
		return encontrar(palab,puntero->hijo1);
	else
		return encontrar(palab,puntero->hijo2);
	
}

p nuevoPuntero(){
	p puntero=(p)malloc(sizeof(palabra));
	
	puntero->hijo1=NULL;
	puntero->hijo2=NULL;
	puntero->padre=NULL;
	
	return puntero;
}



