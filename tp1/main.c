/*----Programa TP1----
//Descripcion: Simulacion de funcionamiento
//             de un router de cuatro bocas,
//             cada una de ellas conectadas
//             a una subred distinta
//Materia: Sistemas operativos y redes
//Profesor: Gerardo Sager
//Autores: Scatuerchio Juan Cruz
//         Aparicio Facundo*/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
/*-----Defines-----*/

    #define cpriv 0XEA000000 /*mascara para ver si ip es clase C "privada"*/
    #define clasec 0XC0000000 /*ip provada clase c */

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
struct in_addr conv_ip1;
struct in_addr conv_ip2;
struct in_addr conv_ip3;
char def_gateway[16];
char ip_privada[]="192.168.0.255";
unsigned long boca_def_gat=0;

struct pack{
    char ip_origen[16];
    char ip_destino[16];
    int fin_archivo;
};

struct pack packA;
struct pack packB;
struct pack packC;
struct pack packD;
struct in_addr *addr;

FILE *config,*pack_bocaA,*pack_bocaB,*pack_bocaC,*pack_bocaD,*rechazados,*decisiones_qd,*decisiones_hexa;

unsigned long dir;
char default_gateway[]="no";
char default_gateway2[]="no";
int verif[4];
int i;

/*----FUNCIONES----*/

int get_config(FILE * archivo); /*obntiene la configuracion del router */
int verificacion(struct boca boca_n); /*verifica si el archivo de configuracion tiene errores o no, SI NO HAY ERROR ENTREGA 0 */
void imp_error(int verif);/* imprime los errores*/
struct pack read_pack(FILE * pack_boca); /*lee los paquetes de cada boca*/
void out(struct pack paquetes); /*escribe en el archivo de decisiones y los paquetes rechazados */
unsigned long identif_boca(unsigned long ip_origen_); /* identifica la boca de entrada y de salida*/

/*----PROGRAMA----*/

int main(){
    config = fopen("routerconfig.txt","r");
    pack_bocaA = fopen("BocaA.txt","r");
    pack_bocaB = fopen("BocaB.txt","r");
    pack_bocaC = fopen("BocaC.txt","r");
    pack_bocaD = fopen("BocaD.txt","r");
    rechazados = fopen("rechazados.txt","w");
    decisiones_qd = fopen("decisiones_qd.txt","w");
    decisiones_hexa = fopen("decisiones_hexa.txt","w");
    if( config == NULL ) {
        printf("No se encontro el archivo de configuracion");
    }
    get_config(config);     /*llamado a la funcion que determiona la configuracion de las bocas*/
    verif[0]=verificacion(bocaA);
    verif[1]=verificacion(bocaB);
    verif[2]=verificacion(bocaC);
    verif[3]=verificacion(bocaD);
    if(verif[0]==0 && verif[1]==0 && verif[2]==0 && verif[3]==0){
        printf("\nConfiguracion consistente\n");
        fprintf(decisiones_qd,"IP origen        IP destino      Boca IN     Boca OUT        DG\n");
        boca_def_gat=identif_boca(ntohl(inet_addr(def_gateway)));
        while(packA.fin_archivo==0){
            packA = read_pack(pack_bocaA);  /*leo el archivo de paquetes de la boca A hasta llegar al fin de archivo*/
            out(packA);                     /*escribo en los archivos de salida */
        }
        while(packB.fin_archivo==0){
            packB = read_pack(pack_bocaB);
            out(packB);
        }
        while(packC.fin_archivo==0){
            packC = read_pack(pack_bocaC);
            out(packC);
        }
        while(packD.fin_archivo==0){
            packD = read_pack(pack_bocaD);
            out(packD);
        }
        printf("\nEl programa se ejecuto correctamente\n");
    }
    else{
        printf("Se encontraron los siguientes errores: \n");
        printf("\nBoca A\n");
        imp_error(verif[0]);
        printf("Boca B\n");
        imp_error(verif[1]);
        printf("Boca C\n");
        imp_error(verif[2]);
        printf("Boca D\n");
        imp_error(verif[3]);
        printf("\n\nEl programa se cerro a causa de errores\n\n");
    }
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
    return error;
}

int verificacion(struct boca boca_n){
    unsigned long ipv;
    unsigned long maskv;
    unsigned long subnetv;
    unsigned long red;
    int a=0;
    int b=0;
    int c=0;
    int d=0;
    int i=0;
    int sum=0;
    int aux=0;
    /*IP*/
    for (i=0;i<=14;i++){ /*corroboro si hay dos puntos seguidos y si hay 4 puntos */
        if (boca_n.ip[i]=='.'){
            sum++;
            if (aux==(i-1)){
                a=1;
            }
            aux=i;
        }
    }
    if (sum!=3){
        a=1;
    }
    sum=0;
    i=0;
    if (strlen(boca_n.ip)<7){  /*compruebo si hay el minimo de valores posibles (ejemplo = pongo 1.1.1 hay error falta un numero)*/
        a=1;
    }
    ipv=inet_addr(boca_n.ip);/* el valor lo convierte a un unsigned int en binario e invertido*/
    if (ipv==0xffffffff){ /*error si no corresponde a una ip , o puede ser si el valor es 255.255.255.255*/
        if (strcmp(boca_n.ip,"255.255.255.255"))/* si el valor es distinto a 255.255.255.255 que corresponde a ffffffff como tambien al error si el numero no es valido*/
            a=1;
    }
   /*MASCARA*/
    for (i=0;i<=14;i++){ /*corroboro si hay dos puntos seguidos y si hay 4 puntos */
        if (boca_n.mask[i]=='.'){
            sum++;
            if (aux==(i-1)){
                b=10;
            }
            aux=i;
        }
    }
    if (sum!=3){
        b=10;
    }
    sum=0;
    i=0;
    if (strlen(boca_n.mask)<7){
        b=10;
    }
    maskv=inet_addr(boca_n.mask);
    if (maskv==0xffffffff){
        if (strcmp(boca_n.mask,"255.255.255.255"))
            b=10;
    }
    /*SUBRED*/
    for (i=0;i<=14;i++){ /*corroboro si hay dos puntos seguidos y si hay 4 puntos */
        if (boca_n.subnet[i]=='.'){
            sum++;
            if (aux==(i-1)){
                c=100;
            }
            aux=i;
        }
    }
    if (sum!=3){
        c=100;
    }
    sum=0;
    i=0;
    if (strlen(boca_n.subnet)<7){
        c=100;
    }
    subnetv=inet_addr(boca_n.subnet);
    if (subnetv==0xffffffff){
        if (strcmp(boca_n.subnet,"255.255.255.255"))
            c=100;
    }
    /*AND*/
    if (a==0 && b==0 && c==0){
        red=ntohl(ipv) & ntohl(maskv);
        if (red!=ntohl(subnetv)){
            d=1000;
        }
    }
    return (a+b+c+d);
}

void imp_error(int validacion){
    switch (validacion){
        case 0:
            printf("No hay error\n");
            break;
        case 1:
            printf("Error Ip\n");
            break;
        case 10:
            printf("Error Mascara\n");
            break;
        case 100:
            printf("Error Subred\n");
            break;
        case 1000:
            printf("Error la ip no pertenece a la Subred\n");
            break;
        default:
            printf("Error, mas de un error de configuracion\n");
            break;
    }
}

struct pack read_pack(FILE * pack_boca ){           /*funcion que lee el archivo de paquetes*/
    struct pack salida;
    if(!feof(pack_boca)){           /*si no se llego al fin de archivo, guardo la informacion en una estructura*/
        fscanf(pack_boca,"%s",salida.ip_origen);
        fscanf(pack_boca,"%s",salida.ip_destino);
        salida.fin_archivo=0;
    }
    else{
        salida.fin_archivo=1;
    }
    return salida;
}

void out(struct pack paquetes){             /*funcion que escribe en el archivo de decisiones*/
    if(paquetes.fin_archivo==0){
        unsigned long ip_or=ntohl(inet_addr(paquetes.ip_origen));
        unsigned long ip_des=ntohl(inet_addr(paquetes.ip_destino));
        unsigned long boca_en;
        unsigned long boca_sal;
        char aux_ip1[16];
        char aux_ip2[16];
        int i=0;
        int sum=0;
        int aux=0;
        int aux2=0;
        char default_gateway_out[3];
        boca_en=identif_boca(ip_or);
        strcpy(default_gateway2,default_gateway);
        boca_sal=identif_boca(ip_des);
        if (ip_or==0xffffffff){ /*error si no corresponde a una ip , o puede ser si el valor es 255.255.255.255*/
            if (strcmp(paquetes.ip_origen,"255.255.255.255")){/* si el valor es distinto a 255.255.255.255 que corresponde a ffffffff como tambien al error si el numero no es valido*/
                boca_en=0;
            }
        }
        if (ip_des==0xffffffff){ /*error si no corresponde a una ip , o puede ser si el valor es 255.255.255.255*/
            if (strcmp(paquetes.ip_destino,"255.255.255.255")){/* si el valor es distinto a 255.255.255.255 que corresponde a ffffffff como tambien al error si el numero no es valido*/
                boca_sal=0;
            }
        }
        for (i=0;i<=14;i++){ /*corroboro si hay dos puntos seguidos y si hay 4 puntos */
            if (paquetes.ip_origen[i]=='.'){
                sum++;
                if (aux==(i-1)){
                    boca_en=0;
                }
                aux=i;
            }
        }
        if (sum!=3){
            boca_en=0;
        }
        sum=0;
        aux=0;
        i=0;
        for (i=0;i<=14;i++){ /*corroboro si hay dos puntos seguidos y si hay 4 puntos */
            if (paquetes.ip_destino[i]=='.'){
                sum++;
                if (aux==(i-1)){
                    boca_sal=0;
                }
                aux=i;
            }
        }
        if (sum!=3){
            boca_sal=0;
        }
        sum=0;
        aux=0;
        i=0;
        conv_ip1.s_addr=ntohl(boca_en);
        conv_ip2.s_addr=ntohl(boca_sal);
        strcpy(aux_ip1,inet_ntoa(conv_ip1));
        strcpy(aux_ip2,inet_ntoa(conv_ip2));
        if(!strcmp(default_gateway,"si") || !strcmp(default_gateway2,"si")){
            strcpy(default_gateway_out,"si");
        }
        else{
            strcpy(default_gateway_out,"no");
        }
        if(boca_en == 0 || boca_sal==0){
            fprintf(rechazados,"%X  %X  %s  %s\n",ip_or,ip_des,paquetes.ip_origen,paquetes.ip_destino);
        }
        else{
            fprintf(decisiones_hexa,"%X %X  %X  %X  %s\n", ip_or,ip_des,boca_en, boca_sal,default_gateway);
            fprintf(decisiones_qd,"%s   %s      %s   %s   %s\n", paquetes.ip_origen,paquetes.ip_destino,aux_ip1,aux_ip2,default_gateway_out);
        }
    }
}

unsigned long identif_boca(unsigned long ip_origen_dest){       /*funcion que identifica la boca de ip de origen o destino*/
    unsigned long identif_boca_sal;
    int pertenece=0;
        if(ip_origen_dest == ntohl(inet_addr(def_gateway))){
            strcpy(default_gateway,"si");
        }
        if((ip_origen_dest & cpriv)==clasec){
            identif_boca_sal=0;
            pertenece=0;
        }
        else{
            if((ip_origen_dest & ntohl(inet_addr(bocaA.mask))) == ntohl(inet_addr(bocaA.subnet))){
                identif_boca_sal=ntohl(inet_addr(bocaA.ip));
                pertenece=0;
            }
            else{
                if((ip_origen_dest & ntohl(inet_addr(bocaB.mask))) == ntohl(inet_addr(bocaB.subnet))){
                    identif_boca_sal=ntohl(inet_addr(bocaB.ip));
                    pertenece=0;
                }
                else{
                    if((ip_origen_dest & ntohl(inet_addr(bocaC.mask))) == ntohl(inet_addr(bocaC.subnet))){
                        identif_boca_sal=ntohl(inet_addr(bocaC.ip));
                        pertenece=0;
                    }
                    else{
                        if((ip_origen_dest & ntohl(inet_addr(bocaD.mask))) == ntohl(inet_addr(bocaD.subnet))){
                            identif_boca_sal=ntohl(inet_addr(bocaD.ip));
                            pertenece=0;
                        }
                        else{
                            identif_boca_sal=boca_def_gat;
                            pertenece=1;
                        }
                    }
                }
            }
        }
        if(pertenece == 1){
            strcpy(default_gateway,"si");
        }
        if(pertenece == 0){
            strcpy(default_gateway,"no");
        }
    return identif_boca_sal;
}

