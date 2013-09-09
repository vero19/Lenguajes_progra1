//Inclucion de librerias necesarias para el programa
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAX 500

int prueba(int argc, char*argv[]){
	int socket_propio; // ID del socket de conexio 
	int conexion, recvLen, SERVER_PORT;
	char buffer[256]; //Variable para almacenar las escrituras en socket
	struct sockaddr_in servAddr; // Estructura que almacena la direccion del amigo
	struct sockaddr_in localAddr;  // Estructura para la direccion local del mensaje
	socket_propio = socket(AF_INET, SOCK_STREAM, 0); //Pide el socket tcp/ip
	//struct hostent *h;
	
	servAddr.sin_family = AF_INET; // Construccion de direccion del receptor
	
	//Transforma la direccion IP de un tip char ej: "127.0.0.1" en tipo direccion para ser guardada en la 		estructura
	inet_pton(AF_INET,argv[1],&(servAddr.sin_addr.s_addr));
	servAddr.sin_port= htons(atoi(argv[2])); //conversion del char* a int y de int a bytes de red

//-----------------------------------------------------------------------------------
//Conexion con el socket 
	conexion = connect(socket_propio, (struct sockaddr *) &servAddr, sizeof(servAddr));
	if(conexion <0){
		perror("No se puede realizar la conexion" );
		exit(1);
	}

	
	char mensaje[MAX]; //Variable que guardara el mensaje ingresado por el usuario
	printf("Ingrese el mensaje deseado: ");	//Solicita al usuario el mensaje que desea enviar
	scanf("%[^\n]",mensaje);	//Lee el mensaje ingresado y lo guarda en la variable mensaje

	//Proceso para enviar el mensaje
	conexion  = send(socket_propio,&mensaje,strlen(mensaje)+1,0);
	//Si conexion es igual a 1
	if(conexion <0){ 
		perror("Fallo en la conexion. Mensaje no enviado"); 
		close(socket_propio);
		exit(1);
	}
	else{
		printf("Mensaje enviado exitosamente\n");
	}
} 

void main(){
	char* datos[3];
	datos[0] = "vero";
	datos[1] = "192.168.1.109";
	datos[2] = "62105";
	
	prueba(3,datos);
	
}
