#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <time.h>

//Declaracion de funciones
char ** reservatablero(int nFil,int nCol);
void creatablero(char ** tablero,int nFil,int nCol);
void imprimetablero(char ** tablero,int nFil,int nCol);
void poneminas(char ** tablero,int nFil,int nCol,int minas);
void cuentaminas(char ** tablero,int nFil,int nCol);
char pasanumeros(int minas);
void expande(char ** tablerofalso,char ** tableroreal,int nFil,int nCol,int i,int j);
void marcacasilla(char ** tablero,int nFil,int nCol);
void liberatablero(char ** tablero,int nFil);

int main(){
//Declaracion de variables
	char ** tablerofalso;
	char ** tableroreal;
	int nFil;
	int nCol;
	int minas;
	int x;
	int y;
	int victoria=0;
	int i;
	int j;
	int k;
	int marcaje;
	int cont;
	int sistema;
	int dificultad;

//Preguntamos al usuario en que sistema operativo esta jugando para la correcta funcionalidad del juego
	do{
		printf("Estas jugando en Linux o en Windows? (1=Linux 2=Windows): ");
		scanf("%d",&sistema);
		if(sistema!=1 && sistema!=2){
			printf("Error: respuesta no valida\n\n");
		}
	}while(sistema!=1 && sistema!=2);

//Preguntamos al usuario sobre la dificultad en la que quiere jugar y segun la opcion elegida ajustamos los parametros necesarios
	do{
		printf("Selecciona el nivel de dificultad (1=principiante 2=intermedio 3=experto 4=personalizado): ");
		scanf("%d",&dificultad);
		if(dificultad!=1 && dificultad!=2 && dificultad!=3 && dificultad!=4){
			printf("Error: respuesta no valida\n\n");
		}
	}while(dificultad!=1 && dificultad!=2 && dificultad!=3 && dificultad!=4);
	if(dificultad==1){
		nFil=8;
		nCol=8;
		minas=10;
	}
	if(dificultad==2){
		nFil=16;
		nCol=16;
		minas=40;
	}
	if(dificultad==3){
		nFil=16;
		nCol=30;
		minas=99;
	}
	if(dificultad==4){
		do{
			printf("Introduzca el numero de filas: ");
			scanf("%d",&nFil);
			if(nFil>100){
				printf("Demasiado grande, prueba de nuevo\n\n");
			}
			if(nFil<4){
				printf("Demasiado pequeno, prueba de nuevo\n\n");
			}
		}while(nFil>100 || nFil<4);
		do{
			printf("Introduzca el numero de columnas: ");
			scanf("%d",&nCol);
			if(nCol>100){
				printf("Demasiado grande, prueba de nuevo\n\n");
			}
			if(nCol<4){
				printf("Demasiado pequeno, prueba de nuevo\n\n");
			}
		}while(nCol>100 || nCol<4);
		do{
			printf("Introduzca el numero de minas: ");
			scanf("%d",&minas);
			if(minas>9990 || minas>(nFil*nCol)-10){
				printf("Demasiadas minas, prueba de nuevo\n\n");
			}
		}while(minas>9990 || minas>(nFil*nCol)-10);
	}

//Reservamos la memoria suficiente para dos tableros
	tableroreal=reservatablero(nFil,nCol);
	tablerofalso=reservatablero(nFil,nCol);

//Creamos un tablero que no se mostrara por pantalla y otro que si, estando en el primero los verdaderos datos del juego
	creatablero(tableroreal,nFil,nCol);
	creatablero(tablerofalso,nFil,nCol);

//Mostramos un tablero sin ningun dato por pantalla
	imprimetablero(tablerofalso,nFil,nCol);

//Colocamos las minas en el tablero y asignamos valores a las casillas que no tengan minas
	poneminas(tableroreal,nFil,nCol,minas);
	cuentaminas(tableroreal,nFil,nCol);

//Bucle del juego
	do{

//Preguntamos al usuario si quiere marcar una casilla hasta que de una respuesta valida
		do{
			printf("Quieres marcar alguna casilla? (si=1  no=0): ");
			scanf("%d",&marcaje);
			if(marcaje!=1 && marcaje!=0){
				printf("Error: respuesta no valida\n\n");
			}
		}while(marcaje!=1 && marcaje!=0);

//Si el usuario desea marcar una casilla, marcamos la casilla seleccionada y mostramos el resultado por pantalla
		if(marcaje==1){
			marcacasilla(tablerofalso,nFil,nCol);
			if(sistema==1){
				system("clear");
			}
			if(sistema==2){
				system("cls");
			}
			imprimetablero(tablerofalso,nFil,nCol);
		}

		else{
//Pedimos al usuario que seleccione una casilla
			do{
				printf("Selecciona una casilla\n");
				printf("Fila: ");
				scanf("%d",&x);
				printf("Columna: ");
				scanf("%d",&y);
				if(x>nFil || y>nCol){
					printf("No existe esa posicion, prueba de nuevo\n\n");
				}
			}while(x>nFil || y>nCol);
//Si la casilla seleccionada no tiene alrededor ninguna mina, mostramos por pantalla los valores de alrededor, hasta encontrar casillas que tengan minas alrededor
			tablerofalso[x-1][y-1]=tableroreal[x-1][y-1];
			for(k=0;k<10;k++){
				for(i=0;i<nFil;i++){
					for(j=0;j<nCol;j++){
						expande(tablerofalso,tableroreal,nFil,nCol,i,j);
					}
				}
			}

//Eliminamos de la pantalla los resultados anteriores para que estos no molesten al usuario
			if(sistema==1){
				system("clear");
			}
			if(sistema==2){
				system("cls");
			}

//Mostramos los resultados actuales por pantalla
			imprimetablero(tablerofalso,nFil,nCol);

//Si la casilla seleccionada por el usuario tenia una mina, se acaba el juego
			if(tablerofalso[x-1][y-1]=='M'){
				victoria=1;
				printf("Perdiste\n");
			}
			
			cont=0;
			for(i=0;i<nFil;i++){
				for(j=0;j<nCol;j++){
					if(tablerofalso[i][j]==tableroreal[i][j]){
						cont++;
					}
				}
			}

//Si todas las casillas de ambos tableros son iguales, exceptuando las minas, se acaba el juego
			if(cont==(nFil*nCol)-minas){
				victoria=1;
				printf("Enhorabuena, has ganado\n");
			}
		}
	}while(victoria==0);
	
	liberatablero(tableroreal,nFil);
	liberatablero(tablerofalso,nFil);
	
	if(sistema==2){
		system("pause");
	}

	return 0;
}

/*----------------------------------------------------------------
Nombre: reservatablero
Entrada: nFil, nCol
Salida: tablero
Cometido: reserva la memoria suficiente para crear un tablero
----------------------------------------------------------------*/
char ** reservatablero(int nFil,int nCol){
//Definicion de variables
	int i;
	int j;
	char ** tablero;

//Reservamos la memoria del tablero
	tablero=(char**)malloc(nFil*sizeof(char*));
	if(tablero==NULL){
		printf("No se pudo reservar memoria\n");
	}

	else{
		for(i=0;i<nFil;i++){
			tablero[i]=(char*)malloc(nCol*sizeof(char));
			if(tablero[i]==NULL){
				printf("No se pudo reservar memoria\n");
			}
		}
	}
	
	return (tablero);
}

/*------------------------------------------
Nombre: creatablero
Entrada: tablero, nFil, nCol
Cometido: crea un tablero para el juego
------------------------------------------*/
void creatablero(char ** tablero,int nFil,int nCol){
//Declaracion de variables
	int i;
	int j;

//Creamos un tablero de tamaÃ±o 8x8 sin ningun dato
	for(i=0;i<nFil;i++){
		for(j=0;j<nCol;j++){
			tablero[i][j]=' ';
		}
	}
}

/*--------------------------------------------
Nombre: imprimetablero
Entrada: tablero, nFil, nCol
Cometido: muestra un tablero por pantalla
--------------------------------------------*/
void imprimetablero(char ** tablero,int nFil,int nCol){
//Declaracion de variables
	int i;
	int j;

//Mostramos el tablero por pantalla, adjuntando a este un conjunto de coordenadas para una visualizacion mas sencilla de este
	printf("  ");
	for(i=0;i<nFil;i++){
		printf(" %d",i+1);
	}
	printf("\n");

	for(i=0;i<nFil;i++){
		if(i<9){
			printf(" %d",i+1);
			printf("|");
		}
		else{
			printf("%d",i+1);
			printf("|");
		}
		for(j=0;j<nCol;j++){
			printf("%c",tablero[i][j]);
			if(j>=9){
				printf(" |");
			}
			else{
				printf("|");
			}
		}
		printf("\n");
	}
}

/*-----------------------------------------------------------
Nombre: poneminas
Entrada: tablero, nFil, nCol, minas
Cometido: coloca minas en el tablero de manera aleatoria
-----------------------------------------------------------*/
void poneminas(char ** tablero,int nFil,int nCol,int minas){
//Declaracion de variables
	int i;
	int j;
	int ponedor;
	int cont=0;

	srand(time(NULL));

//Asignamos minas a casillas aleatorias del tablero, hasta que haya 10 minas
	do{
		for(i=0;i<nFil;i++){
			for(j=0;j<nCol;j++){
				ponedor=((rand()%999)+1);
				if(ponedor>=1 && ponedor<=10){
					if(cont<=minas){
						tablero[i][j]='M';
						cont++;
					}
				}
			}
		}
	}while(cont<minas);
}

/*--------------------------------------------------------------
Nombre: cuentaminas
Entrada: tablero, nFil, nCol
Cometido: cuenta las minas que tiene alrededor cada casilla
--------------------------------------------------------------*/
void cuentaminas(char ** tablero,int nFil,int nCol){
//Declaracion de variables
	int i;
	int j;
	int minas;
	char minaschar;

//Contamos las minas que tiene alrededor cada casilla que no tenga una mina
	for(i=0;i<nFil;i++){
		for(j=0;j<nCol;j++){
			minas=0;
			if(tablero[i][j]!='M'){

//Esquina de arriba a la izquierda
				if(i==0 && j==0){
					if(tablero[i+1][j]=='M'){
						minas++;
					}
					if(tablero[i][j+1]=='M'){
						minas++;
					}
					if(tablero[i+1][j+1]=='M'){
						minas++;
					}
					minaschar=pasanumeros(minas);
					tablero[i][j]=minaschar;
				}

//Esquina de arriba a la derecha
				if(i==0 && j==nCol-1){
					if(tablero[i+1][j]=='M'){
						minas++;
					}
					if(tablero[i][j-1]=='M'){
						minas++;
					}
					if(tablero[i+1][j-1]=='M'){
						minas++;
					}
					minaschar=pasanumeros(minas);
					tablero[i][j]=minaschar;
				}

//Esquina de abajo a la izquierda
				if(i==nFil-1 && j==0){
					if(tablero[i-1][j]=='M'){
						minas++;
					}
					if(tablero[i][j+1]=='M'){
						minas++;
					}
					if(tablero[i-1][j+1]=='M'){
						minas++;
					}
					minaschar=pasanumeros(minas);
					tablero[i][j]=minaschar;
				}

//Esquina de abajo a la derecha
				if(i==nFil-1 && j==nCol-1){
					if(tablero[i-1][j]=='M'){
						minas++;
					}
					if(tablero[i][j-1]=='M'){
						minas++;
					}
					if(tablero[i-1][j-1]=='M'){
						minas++;
					}
					minaschar=pasanumeros(minas);
					tablero[i][j]=minaschar;
				}

//Lado de arriba (sin contar las esquinas)
				if(i==0 && j!=0 && j!=nCol-1){
					if(tablero[i+1][j-1]=='M'){
						minas++;
						}
					if(tablero[i+1][j]=='M'){
						minas++;
					}
					if(tablero[i+1][j+1]=='M'){
						minas++;
					}
					if(tablero[i][j-1]=='M'){
						minas++;
					}
					if(tablero[i][j+1]=='M'){
						minas++;
					}
					minaschar=pasanumeros(minas);
					tablero[i][j]=minaschar;
				}

//Lado de la izquierda (sin contar las esquinas)
				if(j==0 && i!=0 && i!=nFil-1){
					if(tablero[i-1][j+1]=='M'){
						minas++;
					}
					if(tablero[i][j+1]=='M'){
						minas++;
					}
					if(tablero[i+1][j+1]=='M'){
						minas++;
					}
					if(tablero[i-1][j]=='M'){
						minas++;
					}
					if(tablero[i+1][j]=='M'){
						minas++;
					}
					minaschar=pasanumeros(minas);
					tablero[i][j]=minaschar;
				}

//Lado de abajo (sin contar las esquinas)
				if(i==nFil-1 && j!=0 && j!=nCol-1){
					if(tablero[i-1][j-1]=='M'){
						minas++;
					}
					if(tablero[i-1][j]=='M'){
						minas++;
					}
					if(tablero[i-1][j+1]=='M'){
						minas++;
					}
					if(tablero[i][j-1]=='M'){
						minas++;
					}
					if(tablero[i][j+1]=='M'){
						minas++;
					}
					minaschar=pasanumeros(minas);
					tablero[i][j]=minaschar;
				}

//Lado de la derecha (sin contar las esquinas)
				if(j==nCol-1 && i!=0 && i!=nFil-1){
					if(tablero[i-1][j-1]=='M'){
						minas++;
					}
					if(tablero[i][j-1]=='M'){
						minas++;
					}
					if(tablero[i+1][j-1]=='M'){
						minas++;
					}
					if(tablero[i-1][j]=='M'){
						minas++;
					}
					if(tablero[i+1][j]=='M'){
						minas++;
					}
					minaschar=pasanumeros(minas);
					tablero[i][j]=minaschar;
				}

//Resto del tablero
				if(i!=0 && j!=0 && i!=nFil-1 && j!=nCol-1){
					if(tablero[i-1][j-1]=='M'){
						minas++;
					}
					if(tablero[i-1][j]=='M'){
						minas++;
					}
					if(tablero[i-1][j+1]=='M'){
						minas++;
					}
					if(tablero[i][j-1]=='M'){
						minas++;
					}
					if(tablero[i][j+1]=='M'){
						minas++;
					}
					if(tablero[i+1][j-1]=='M'){
						minas++;
					}
					if(tablero[i+1][j]=='M'){
						minas++;
					}
					if(tablero[i+1][j+1]=='M'){
						minas++;
					}
					minaschar=pasanumeros(minas);
					tablero[i][j]=minaschar;
				}
			}
		}
	}
}

/*-------------------------------------------------------------------------
Nombre: pasanumeros
Entrada: minas
Salida: 0, 1, 2, 3, 4, 5, 6, 7 u 8 en formato char
Cometido: convierte un dato de tipo entero en un dato de tipo caracter
-------------------------------------------------------------------------*/
char pasanumeros(int minas){
//Convertimos los datos de tipo entero en datos de tipo caracter
	if(minas==0){
		return '0';
	}
	if(minas==1){
		return '1';
	}
	if(minas==2){
		return '2';
	}
	if(minas==3){
		return '3';
	}
	if(minas==4){
		return '4';
	}
	if(minas==5){
		return '5';
	}
	if(minas==6){
		return '6';
	}
	if(minas==7){
		return '7';
	}
	if(minas==8){
		return '8';
	}
}

/*------------------------------------------------------------------------------------------------------------------------------------------------------
Nombre: expande
Entrada: tablerofalso ,tableroreal, nFil, nCol, i, j
Cometido: asigna al tablero falso las casillas de alrededor de la casilla seleccionada por el usuario para que estas sean mostradas posteriormente,
teniendo en cuenta que las casillas que no tienen ninguna mina cerca también desbloquean automáticamente las casillas a su alrededor
------------------------------------------------------------------------------------------------------------------------------------------------------*/
void expande(char ** tablerofalso,char ** tableroreal,int nFil,int nCol,int i,int j){
//Declaracion de variables
	int x;
	int y;

//Asignamos las casillas de alrededor de la casilla seleccionada en el tablero real a las mismas casillas en el tablero falso
	for(x=0;x<nFil;x++){
		for(y=0;y<nCol;y++){
			if(tablerofalso[i][j]=='0'){

//Esquina de arriba a la izquierda
				if(i==0 && j==0){
					tablerofalso[i+1][j]=tableroreal[i+1][j];
					tablerofalso[i][j+1]=tableroreal[i][j+1];
					tablerofalso[i+1][j+1]=tableroreal[i+1][j+1];
				}

//Esquina de arriba a la derecha
				if(i==0 && j==nCol-1){
					tablerofalso[i+1][j]=tableroreal[i+1][j];
					tablerofalso[i][j-1]=tableroreal[i][j-1];
					tablerofalso[i+1][j-1]=tableroreal[i+1][j-1];
				}

//Esquina de abajo a la izquierda
				if(i==nFil-1 && j==0){
					tablerofalso[i-1][j]=tableroreal[i-1][j];
					tablerofalso[i][j+1]=tableroreal[i][j+1];
					tablerofalso[i][j+1]=tableroreal[i][j+1];
				}

//Esquina de abajo a la derecha
				if(i==nFil-1 && j==nCol-1){
					tablerofalso[i-1][j]=tableroreal[i-1][j];
					tablerofalso[i][j-1]=tableroreal[i][j-1];
					tablerofalso[i-1][j-1]=tableroreal[i-1][j-1];
				}

//Lado de arriba (sin contar las esquinas)
				if(i==0 && j!=0 && j!=nCol-1){
					tablerofalso[i+1][j-1]=tableroreal[i+1][j-1];
					tablerofalso[i+1][j]=tableroreal[i+1][j];
					tablerofalso[i+1][j+1]=tableroreal[i+1][j+1];
					tablerofalso[i][j-1]=tableroreal[i][j-1];
					tablerofalso[i][j+1]=tableroreal[i][j+1];
				}

//Lado de la izquierda (sin contar las esquinas)
				if(j==0 && i!=0 && i!=nFil-1){
					tablerofalso[i-1][j+1]=tableroreal[i-1][j+1];
					tablerofalso[i][j+1]=tableroreal[i][j+1];
					tablerofalso[i+1][j+1]=tableroreal[i+1][j+1];
					tablerofalso[i-1][j]=tableroreal[i-1][j];
					tablerofalso[i+1][j]=tableroreal[i+1][j];
				}

//Lado de abajo (sin contar las esquinas)
				if(i==nFil-1 && j!=0 && j!=nCol-1){
					tablerofalso[i-1][j-1]=tableroreal[i-1][j-1];
					tablerofalso[i-1][j]=tableroreal[i-1][j];
					tablerofalso[i-1][j+1]=tableroreal[i-1][j+1];
					tablerofalso[i][j-1]=tableroreal[i][j-1];	
					tablerofalso[i][j+1]=tableroreal[i][j+1];
				}

//Lado de la derecha (sin contar las esquinas)
				if(j==nCol-1 && i!=0 && i!=nFil-1){
					tablerofalso[i-1][j-1]=tableroreal[i-1][j-1];
					tablerofalso[i][j-1]=tableroreal[i][j-1];
					tablerofalso[i+1][j-1]=tableroreal[i+1][j-1];
					tablerofalso[i-1][j]=tableroreal[i-1][j];
					tablerofalso[i+1][j]=tableroreal[i+1][j];
				}

//Resto del tablero
				if(i!=0 && j!=0 && i!=nFil-1 && j!=nCol-1){
					tablerofalso[i-1][j-1]=tableroreal[i-1][j-1];
					tablerofalso[i-1][j]=tableroreal[i-1][j];
					tablerofalso[i-1][j+1]=tableroreal[i-1][j+1];
					tablerofalso[i][j-1]=tableroreal[i][j-1];
					tablerofalso[i][j+1]=tableroreal[i][j+1];
					tablerofalso[i+1][j-1]=tableroreal[i+1][j-1];
					tablerofalso[i+1][j]=tableroreal[i+1][j];
					tablerofalso[i+1][j+1]=tableroreal[i+1][j+1];
				}
			}
		}
	}
}

/*---------------------------------------------------------
Nombre: marcacasilla
Entrada: tablero
Cometido: marca la casilla seleccionada por el usuario
---------------------------------------------------------*/
void marcacasilla(char ** tablero,int nFil,int nCol){
//Declaracion de variables
	int x;
	int y;

//Marcamos con una X la casilla seleccionada por el usuario
	do{
		printf("Marca una casilla\n");
		printf("Fila: ");
		scanf("%d",&x);
		printf("Columna: ");
		scanf("%d",&y);
		if(x>nFil || y>nCol){
			printf("No existe esa posicion, prueba de nuevo\n\n");
		}
	}while(x>nFil || y>nCol);
	tablero[x-1][y-1]='X';
}

/*--------------------------------------------------------
Nombre: liberatablero
Entrada: tablero, nFil
Cometido: libera la memoria reservada para un tablero
--------------------------------------------------------*/
void liberatablero(char ** tablero,int nFil){
//Declaracion de variables
	int i;

//Liberamos la memoria del tablero
	for(i=0;i<nFil;i++){
		free(tablero[i]);
	}
	
	free(tablero);
	tablero=NULL;
}
