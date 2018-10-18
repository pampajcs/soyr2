//----Programa TP1----
//Descripcion: Simulacion de funcionamiento
//             de un router de cuatro bocas,
//             cada una de ellas conectadas
//             a una subred distinta
//Materia: Sistemas operativos y redes
//Profesor: Gerardo Sager
//Autores: Scatuerchio Juan Cruz
//         Aparicio Facundo

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

/*----VARIABLES----*/
    struct boca{
        char ip[16];
        char subnet[16];
        char mask[16];
    };

    struct boca bocaA;
    struct boca bocaB;
    struct boca bocaC;
    struct boca bocaD;
    char def_gateway[16];

    struct pack{
        char ip_origen[16];
        char ip_destino[16];
        char boca_in[16];
        char boca_out[16];
        char default_gateway[3];
    };
    struct pack packA;
    struct pack packB;
    struct pack packC;
    struct pack packD;

/*----FUNCIONES----*/
int get_config(FILE * archivo);
int ip_mask_verif(struct boca boca_n);
struct pack read_pack(FILE * pack_boca);

/*----PROGRAMA----*/
int main()
{
    FILE * archivo;
    archivo = fopen("routerconfig.txt","r");
    FILE * pack_bocaA;
    pack_bocaA = fopen("bocaA.txt","r");
    FILE * pack_bocaB;
    pack_bocaB = fopen("bocaB.txt","r");
    FILE * pack_bocaC;
    pack_bocaC = fopen("bocaC.txt","r");
    FILE * pack_bocaD;
    pack_bocaD = fopen("bocaD.txt","r");
    if( archivo == NULL ) {
        printf("No se encontro el archivo.");
    }
    get_config(archivo);
    packA = read_pack(pack_bocaA);
    packB = read_pack(pack_bocaB);
    packC = read_pack(pack_bocaC);
    packD = read_pack(pack_bocaD);
    return 0;
}

int get_config(FILE * file){
    int error=0;
    fscanf(file,"%s",bocaA.ip);
    fscanf(file,"%s",bocaA.subnet);
    fscanf(file,"%s",bocaA.mask);
    fscanf(file,"%s",bocaB.ip);
    fscanf(file,"%s",bocaB.subnet);
    fscanf(file,"%s",bocaB.mask);
    fscanf(file,"%s",bocaC.ip);
    fscanf(file,"%s",bocaC.subnet);
    fscanf(file,"%s",bocaC.mask);
    fscanf(file,"%s",bocaD.ip);
    fscanf(file,"%s",bocaD.subnet);
    fscanf(file,"%s",bocaD.mask);
    fscanf(file,"%s",def_gateway);


   /* printf("%s\n",bocaA.ip);
    printf("%s\n",bocaA.mask);
    printf("%s\n",bocaB.ip);inet_addr(bocaA.ip)
    printf("%s\n",bocaB.mask);
    printf("%s\n",bocaC.ip);
    printf("%s\n",bocaC.mask);
    printf("%s\n",bocaD.ip);
    printf("%s\n",bocaD.mask);
    printf("%s\n",def_gateway);*/
    return error;
}

int ip_mask_verif(struct boca boca_n){
    //hacer comparacion de la salida de la and entre ip y mask con subred
    return 0;
}

struct pack read_pack(FILE * pack_boca ){
    struct pack salida;
    fscanf(pack_boca,"%s",salida.ip_origen);
    fscanf(pack_boca,"%s",salida.ip_destino);
    fscanf(pack_boca,"%s",salida.boca_in);
    fscanf(pack_boca,"%s",salida.boca_out);
    fscanf(pack_boca,"%s",salida.default_gateway);
    return salida;
}
