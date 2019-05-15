#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

/*****FUNCIONES*****/

void barajar(void);
void interprete_carta(int card);
void manos(void);

/*****VARIABLES*****/

int cartas_valores[4][10];
int maso[40];
int maso2[40];
int carta=0;
int i=0;
int j=0;
int cant_jug=4;
int cant_manos=0;

struct Jugador{
	int mano[18][3];	//primer indice= n° de mano, segundo indice= cartas de cada mano
	int pila[40];
};

struct Flop{
	int cartas_mesa[40];
};

struct Jugador P1;
struct Jugador P2;
struct Jugador P3;
struct Jugador P4;
struct Flop flop;


int main(){
	printf("ESCOBA DE 15\n");  
	printf("\n");
	cant_manos=12/(cant_jug);
	barajar();
	manos();
	for(i=0;i<cant_manos;i++){
		for(j=0;j<3;j++){
			interprete_carta(P1.mano[i][j]);
		}
		printf("\n");	
	}
	printf("\n");
	for(i=0;i<cant_manos;i++){
		for(j=0;j<3;j++){
			interprete_carta(P2.mano[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	for(i=0;i<cant_manos;i++){
		for(j=0;j<3;j++){
			interprete_carta(P3.mano[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	for(i=0;i<cant_manos;i++){
		for(j=0;j<3;j++){
			interprete_carta(P4.mano[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	while(1){
	
	}
}

void barajar(void){				/*uso un valor aleatorio entre 0 y 40 para posicionar las cartas */
	time_t t;
    	srand((unsigned) time(&t));
	for(i=0; i<40;i++){
		maso[i]=i+1;
		/*printf("%d ",maso[i]);*/
	}
	for(j=0;j<40;j++){
		carta=rand()%40;
		while(maso[carta]==0){
			carta=rand()%40;
		}
		maso2[j]=maso[carta]-1;
		maso[carta]=0;
	}
	/*for(i=0;i<40;i++){
		printf("%d ",maso2[i]);
	}
	printf("\n");
	printf("\n");*/
}

void interprete_carta(int card){		/*a cada posicion del maso lo interpreto como un valor y un palo para mostrar en pantalla*/
	//for(i=0;i<40;i++){
		int palo=card/10;
		int valor=1+card%10;
		switch(valor){
			case 8:
				printf("10");
				break;
			case 9:
				printf("11");
				break;
			case 10:
				printf("12");
				break;
			default:
				printf("%d",valor);
				break;
		
		}
		switch(palo){
			case 0:
				printf("O ");
				break;
			case 1:
				printf("C ");
				break;
			case 2:
				printf("E ");
				break;
			case 3:
				printf("B ");
				break;
			case 4:
				printf("B ");
				break;
		}
	//}
}

void manos(void){
	printf("FLOP\n");
	for(i=0;i<4;i++){
		flop.cartas_mesa[i]=maso2[i];
		interprete_carta(flop.cartas_mesa[i]);
		//printf("	");
	}	
	printf("\n");
	printf("\n");
	for(i=0;i<cant_manos;i++){
		/*switch(cant_jug){
			case 2:
				printf("P1	P2	P1	P2	P1	P2	Mano %d\n",i+1);
				break;
			case 3:
				printf("P1	P2	P3	P1	P2	P3	P1	P2	P3	Mano %d\n",i+1);
				break;
			case 4:
				printf("P1	P2	P3	P4	P1	P2	P3	P4	P1	P2	P3	P4	Mano %d\n",i+1);
				break;
		}*/
		//printf("P1	P2	P1	P2	P1	P2	Mano %d\n",i+1);
		for(j=0;j<3;j++){//3*cant_jug;j++){
			P1.mano[i][j]=maso2[j+4+3*cant_jug*i];
			P2.mano[i][j]=maso2[j+5+3*cant_jug*i];
			P3.mano[i][j]=maso2[j+6+3*cant_jug*i];
			//P4.mano[i][j]=maso2[j+7+3*cant_jug*i];

			switch(cant_jug){
				case 2:
					P1.mano[i][j]=maso2[j+4+3*cant_jug*i];
					P2.mano[i][j]=maso2[j+5+3*cant_jug*i];
					break;
				case 3:
					P1.mano[i][j]=maso2[j+4+3*cant_jug*i];
					P2.mano[i][j]=maso2[j+5+3*cant_jug*i];
					P3.mano[i][j]=maso2[j+6+3*cant_jug*i];
					break;
				case 4:
					P1.mano[i][j]=maso2[j+4+3*cant_jug*i];
					P2.mano[i][j]=maso2[j+5+3*cant_jug*i];
					P3.mano[i][j]=maso2[j+6+3*cant_jug*i];
					P4.mano[i][j]=maso2[j+7+3*cant_jug*i];
				break;
			}
			/*if(j%cant_jug==0){
				P1.mano[j]=maso2[j+4+3*cant_jug*i];
				interprete_carta(P1.mano[j]);
				//printf("%d	",P1.mano[j]);
			}
			if(j%2==1){
				printf("	");
				P2.mano[j]=maso2[j+4+3*cant_jug*i];
				interprete_carta(P2.mano[j]);
				printf("	");
				//printf("%d ",P2.mano[j+4]);
			}*/
		}
		//printf("\n");
		//printf("\n");
	}
}
