#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define  PORT_NUM 2018
#define  IP_ADDR "127.0.0.1"
int a=0;
int main()
{
    WORD wVersionRequested = MAKEWORD(1,1);
    WSADATA wsaData;
    unsigned int server_s;          /* Server socket descriptor*/
    struct sockaddr_in server_addr; /* Server1 Internet address*/
    struct sockaddr_in client_addr; /* Client1 Internet address*/
    int addr_len;                   /* Internet address length*/
    char out_buf[100];              /* 100-byte buffer for output data*/
    char in_buf[100];               /* 100-byte buffer for input data*/
    int addr_l;
    printf("Iniciando servidor\n");
    /*---Inicializacion de winsock---*/
    WSAStartup(wVersionRequested, &wsaData);

    /*---Creacion del socket---*/
    server_s = socket(AF_INET, SOCK_DGRAM, 0);
    printf("Socket creado\n");

    /*---Informacion de la direccion del socket---*/
    server_addr.sin_family = AF_INET;                   /* Address family to use*/
    server_addr.sin_port = htons(PORT_NUM);             /*Port number to use*/
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);    /* Listen on any IP address*/
    addr_l = sizeof(server_addr);
    a=bind(server_s, (struct sockaddr *)&server_addr, addr_l);

    printf("Retorno de bind: %d\n",a);

    /*---Informacion de la direccion del cliente---*/
    /*client_addr.sin_family = AF_INET;                   /* Address family to use*/
    /*client_addr.sin_port = htons(PORT_NUM);             /* Port num to use*/
    /*client_addr.sin_addr.s_addr = htonl(INADDR_ANY);    /* IP address to use*/

    /*listen(server_s,1);

    addr_l = sizeof(client_addr);

    a=accept(server_s, (struct sockaddr *)&client_addr, &addr_l);
    printf("Retorno de accept: %d\n",a);
    /*---Esperando recibir algo del cliente---*/
    addr_len = sizeof(client_addr);
    recvfrom(server_s, in_buf,sizeof(in_buf), 0,(struct sockaddr *)&client_addr, &addr_len); /*el mensaje se guarda en in_buf*/

printf("Message received is: '%s' \n", in_buf);
strcpy(out_buf, "Reply message from server1 to client1");

    /*---Enviando mensaje al cliente---*/
    sendto(server_s, out_buf,(strlen(out_buf) + 1), 0,(struct sockaddr *)&client_addr, sizeof(client_addr));

    /*---Cerrando el socket---*/
    closesocket(server_s);

    return 0;
}
