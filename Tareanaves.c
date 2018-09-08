//Instituto Tecnologico de Costa Rica
//Agosto 2015
//Josue David Rodriguez Alfaro
//carnet 2015033850

#include <stdlib.h>
#include <stdio.h>
#include "naves.h"
//~ 

// Creacion de un nodo 
	

struct lista* crear_lista_doble(){

	struct lista* nueva_lista = NULL;
	nueva_lista = calloc(1, sizeof(struct lista));

	return nueva_lista;
}
/////////////////////////////////////////////////////////////////////////
// Funcion en la cual se inserta una respectiva nave al final con todos 
// respectivos atributos

int contadornavesrojas;// se utilizan para verificar que equipo gana
int contadornavesverdes;



void insertar(struct lista* nueva_lista){
// se crea las naves con sus distintos atributos

	struct nodo* actual = nueva_lista->elementos;
	
	//Asignacion de nuevo nodo
	struct nodo* nuevo_nodo = calloc(1,sizeof(struct nodo));// pide memoria
	
	nuevo_nodo->vida=30;
	nuevo_nodo->poder=rand()%21;
	nuevo_nodo->nave = rand()%101;
	nuevo_nodo->color = rand()%2;
	
//	nuevo_nodo->siguiente = NULL;
//	nuevo_nodo->anterior = NULL;
	
    // En esta funcion se recorre la lista
    
	if(actual==NULL){
		nueva_lista->elementos = nuevo_nodo;
	} else {
		while(actual->siguiente != NULL)
			actual = actual->siguiente;
			actual->siguiente = nuevo_nodo;
			nuevo_nodo->anterior = actual;
			nuevo_nodo->siguiente = NULL;
			
	}

}
//////////////////////////////////////////////////////////////////
void juegoparejoequipos(struct lista* nueva_lista){
	
	struct nodo* actual = nueva_lista->elementos;
	struct nodo* temporals= actual;
	actual=temporals;
	temporals=temporals->siguiente;
	
	while(temporals!= NULL){
		if((actual->color == temporals->color)){
			temporals->color=rand()%2;
			actual=actual->siguiente;
			temporals=temporals->siguiente;
		}
		else{
			actual=actual->siguiente;
			temporals=temporals->siguiente;
		}
	}
		
		
}

//Funcion la cual tiene dos casos especiales: si la nave es la primera no
// tendra anterior y asi no tendra a quien atacar, y el otro caso especial 
// corresponde a la ultima nave ya que no  tiene un siguiente a quien atacar

void atacar(struct lista* nueva_lista, int nave)
{
	struct nodo* actual = nueva_lista->elementos;
	struct nodo*temporal=actual;
	
	
	while(temporal->nave != nave){
		actual=temporal;
		temporal=temporal->siguiente;
	}
		
		if(temporal->siguiente == NULL){
			(temporal->anterior)->vida -=  (temporal->poder);
		
		}if(temporal->anterior == NULL){
			(temporal->siguiente)->vida -= (temporal->poder);
		
		
		}if(temporal->siguiente != NULL && temporal->anterior != NULL){
			actual->vida -= (temporal->poder);
			(temporal->siguiente)->vida -=  (temporal->poder);
		}
	
	
}
		

///////////////////////////////////////////////////////////////

// Funcion encargada de recorrer la lista y verificar los que tienen en el 
// atributo vida "0" y eliminarlos usando punteros y el free para liberar memoria

void eliminarnaves(struct lista* nueva_lista){
	struct nodo* actual= nueva_lista->elementos;
	if (actual->anterior==NULL){
		if (actual->vida<=0){
			actual=actual->siguiente;
			actual->anterior=NULL;
			nueva_lista->elementos=actual;
		}
	}
	while (actual->siguiente!=NULL){
		if (actual->vida <=0){
			(actual->anterior)->siguiente=actual->siguiente;
		    (actual->siguiente)->anterior=actual->anterior;

		    actual=actual->siguiente;

		}else{
			actual=actual->siguiente;
		}
	}
	if (actual->vida<=0){
		(actual->anterior)->siguiente=actual->siguiente;
		actual=actual->siguiente;
	}
}

	
///////////////////////////////////////////////////////////////////
	
// Funcion encargada de recorrer la lista e imprimir el atributo  que posean 
// todas las naves en el campo de "nave" el cual indica el numero correspondiente
// a cada una
 
void imprimir_nave(struct lista* nueva_lista){
	
	struct nodo* actual = nueva_lista->elementos;
	while(actual != NULL){
		printf("Nave %d        \t", actual->nave);
		actual = actual->siguiente;
	}
	printf("\n");
}
/************************************************/
// Funcion encargada de recorrer la lista e imprimir el atributo  que posean 
// todas las naves en el campo de "color" el cual indica el equipo al que 
// pertenece cada una
 // Primero se valido con 0 y 1 para mayor facilidad luego en caso de que 
 // posean un "0" imprimira "equipo verde" y si tuviesen un "1" sera impreso
 // "equipo rojo".
void imprimir_equiponave(struct lista* nueva_lista){
	
	struct nodo* actual = nueva_lista->elementos;
	
	while(actual->siguiente != NULL){
		if(actual->color == 0){
			printf("Equipo Rojo\t");
		} else {
			printf("Equipo Verde\t");			
			}
		actual = actual->siguiente;	
	}
	if(actual->color == 0){
		printf("Equipo Rojo\t");
	} else {
		printf("Equipo Verde\t");
	}
	
	printf("\n");	
}
/************************************************/
	
void espacioentrelineas(struct lista* nueva_lista){
	struct nodo* actual = nueva_lista->elementos;
	
	while(actual->siguiente != NULL){
		printf("------------\t");
		actual = actual->siguiente;	
		}
	printf("------------\t");
	printf("\n");
	}
/************************************************/
// Funcion encargada de recorrer la lista e imprimir el atributo  que posean 
// todas las naves en el campo de "vida" el cual sera un numero que iniciara
// para todas las naves en "30"

void imprime_vida(struct lista* nueva_lista){
	//puntero a la nave inical
	struct nodo* actual = nueva_lista->elementos;
	
	while(actual->siguiente != NULL){
		printf("Vida %d \t", actual->vida);
		actual = actual->siguiente;
		}
		
	printf("Vida %d\t", actual->vida);
	printf("\n");
}
/************************************************/
// Funcion encargada de recorrer la lista e imprimir el atributo  que posean 
// todas las naves en el campo de "poder el cual sera un numero random 
// entre 1 y 20.

void imprime_poder(struct lista* nueva_lista){
	//puntero a la nave inical
	struct nodo* actual = nueva_lista->elementos;
	
	while(actual->siguiente != NULL){
		printf("Poder %d \t", actual->poder);
		actual = actual->siguiente;
		}
		
	printf("Poder %d \t", actual->poder);
	printf("\n");
}

/************************************************/	

////////////////////////////////////////////////////////////////
//Funcion en la cual se cuenta la cantidad de naves de  cada equipo
// sea rojo o verde (identificados con 1 y 0) y se iran almacenando 
// por separado en las variables contadornavesrojas o contadornavesverdes
// en caso de que algun contador sea 0 el juego se finalizara imprimiendo
// el respectivo ganador

int contadores(struct lista* nueva_lista){
	
	struct nodo* actual = nueva_lista->elementos;
	
	while(actual->siguiente != NULL){
		if(actual->color == 0){
			contadornavesrojas++;
		} else {
			contadornavesverdes++;			
			}
		actual = actual->siguiente;	
	}
	if(actual->color == 0){
		contadornavesrojas++;
		
	} else {
		contadornavesverdes++;
	}
	return contadornavesrojas;
	return contadornavesverdes;
	
}

////////////////////////////////////////////////////////////////
int turno=0;// se coloca una variable entera la cual se utiliza para
//saber que equipo va atacando

//Funcion la cual llama a las demas funciones para poder implementar el juego

void juegonaves(struct lista* nueva_lista){
	printf("\t▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒\n");

	printf("\t▒▓▓▓▓▓▓▓▓▓▓▒▓▓▓▓▓▓▓▓▓▓▒▓▓▓▓▒\n");

	printf("\t▒▓░░▓▓▓▓░░▓▒▓░░░░░░▓▓▓▒▓░░▓▒\n");

	printf("\t▒▓▓░░▓▓░░▓▓▒▓░░▓▓▓░░▓▓▒▓░░▓▒\n");

	printf("\t▒▓▓▓░░░░▓▓▓▒▓░░▓▓▓▓░░▓▒▓░░▓▒\n");

	printf("\t▒▓▓▓▓░░▓▓▓▓▒▓░░▓▓▓▓░░▓▒▓░░▓▒\n");

	printf("\t▒▓▓▓░░░░▓▓▓▒▓░░▓▓▓▓░░▓▒▓░░▓▒\n");

	printf("\t▒▓▓░░▓▓░░▓▓▒▓░░▓▓▓░░▓▓▒▓▓▓▓▒\n");

	printf("\t▒▓░░▓▓▓▓░░▓▒▓░░░░░░▓▓▓▒▓░░▓▒\n");

	printf("\t▒▓▓▓▓▓▓▓▓▓▓▒▓▓▓▓▓▓▓▓▓▓▒▓▓▓▓▒\n");

	printf("\t▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒\n\n");
	int parametro=1;
	while (parametro!=0){
		contadores(nueva_lista);
	    if (contadornavesrojas<=0){
			printf("\tEquipo verde gana \n\n");
			break;
		}
	    		
		if (contadornavesverdes<=0){
			printf("\tEquipo Rojo gana\n\n");
			break;
		}
	
		contadornavesrojas=0;
		contadornavesverdes=0;
		imprimir_nave(nueva_lista);
		imprimir_equiponave(nueva_lista);
		espacioentrelineas(nueva_lista);
		imprime_vida(nueva_lista);
		imprime_poder(nueva_lista);
		int nave;
		
		if (turno == 0){
			printf("\n<---------Equipo rojo---------->\n\n");
			turno+=1;
		}
		else if (turno == 1){
			printf("\n<---------Equipo verde--------->\n\n");
			turno-=1;
		}
		printf("Con cual nave planea atacar: \n");
		scanf("%d",&nave);
		atacar(nueva_lista, nave);
		eliminarnaves(nueva_lista);
		system("clear");
	}
}
/////////////////////////////////////////////////////////

////////////////////////////////////////////////////////

//MAIN: donde se llaman a las funciones para implementarlo

int main (int argc, char* argv[]){
	struct lista* nueva_lista = crear_lista_doble();
	int total= atoi(argv[1]);
	int i;
	for(i = 0; i < total;i++){
		insertar(nueva_lista);
	}

	juegoparejoequipos(nueva_lista);
	juegonaves(nueva_lista);
	
	return 0;
}


