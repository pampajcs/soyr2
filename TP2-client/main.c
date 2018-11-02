#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define  PORT_NUM 2018
#define  IP_ADDR "127.0.0.1"

int main()
{
    WORD wVersionRequested = MAKEWORD(1,1);
    WSADATA wsaData;
    unsigned int client_s;          /* Client socket descriptor*/
    struct sockaddr_in server_addr; /* Server1 Internet address*/
    int addr_len;                   /* Internet address length*/
    char out_buf[100];              /* 100-byte buffer for output data*/
    char in_buf[100];               /* 100-byte buffer for input data*/
    int c;
    printf("Iniciando cliente\n");
    /*---Inicializacion de winsock---*/
    WSAStartup(wVersionRequested, &wsaData);

    /*---Creacion del socket---*/
    client_s = socket(AF_INET, SOCK_DGRAM, 0);

    /*---Informacion de la direccion del socket---*/
    server_addr.sin_family = AF_INET;                   /* Address family to use*/
    server_addr.sin_port = htons(PORT_NUM);             /* Port number to use*/
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);    /* Listen on any IP address*/

    c=connect(client_s, (struct sockaddr *)&server_addr, sizeof(server_addr));

    printf("Retorno de conect: %d",c);

    /*---Asignacion de mensaje al buffer de salida---*/
    strcpy(out_buf, "Test message from client1 to server1");

    /*---Enviando mensaje al servidor---*/
    sendto(client_s, out_buf, (strlen(out_buf) + 1), 0,(struct sockaddr *)&server_addr, sizeof(server_addr));

    /*---Esperando recibir aldo del servidor---*/
    addr_len = sizeof(server_addr);
    recvfrom(client_s, in_buf, sizeof(in_buf), 0,(struct sockaddr *)&server_addr, &addr_len);

    printf("Message received is: '%s' \n", in_buf);

    closesocket(client_s);
    c=getchar();
    return 0;
}
