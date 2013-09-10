//Inclucion de librerias necesarias para el programa
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define MAX 500

/*Funcion servidor
Recibe como parametro el puerto
Se encarga de mantener el puerto en escucha
Una vez identificado un mensaje de entrada lo muestra en pantalla
*/
int servidor (int argc, char *argv[]){
	int socket_propio; //ID del socket de conexion
	/*conexion -> int que verifica la conexion con el socket
	  cliAddr -> indica el largo de la direccion del cliente
	  recvLen -> int que verifica si ha recibido un mensaje */
	int conexion, cliLen, recvLen; 
	/* cliAddr --> Estructura para la direccion del cliente
	   servAddr --> Estructura para la direccion del servidor(local)*/
	struct sockaddr_in cliAddr, servAddr;
	char line[MAX];

	socket_propio = socket(AF_INET, SOCK_STREAM, 0); //Pide el socket TCP/IP
	
	servAddr.sin_family = AF_INET; // Construccion de direccion
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY); 
	servAddr.sin_port = htons(atoi(argv[0])); // convierte el dato de puerto en bits de red

	//Union del socket con esta direccion
	if(bind(socket_propio, (struct sockaddr *) &servAddr, sizeof(servAddr))<0){
		perror("No se puede conectar al puerto");
		exit(1);
	}

	//Ciclo donde el puerto se matiene escuchando
	while(1){
		listen(socket_propio,10); //Le indica al socket que espere conexiones
		cliLen=sizeof(cliAddr); // Determina el largo de la direccion del cliente
		//verifica si la conexion con el socket es correcta
		conexion= accept(socket_propio, (struct sockaddr *) &cliAddr, &cliLen);
		if(conexion <0){
			perror("Error. Conexion no aceptada");
			exit(1);
		}
		
		memset(line,0x0,MAX); //inicia la linea de escucha

		recvLen = recv(conexion, line, MAX, 0); // Espera que lleguen todos los datos
		//Si el numero de datos es menor que 0 envia error
		if(recvLen < 0){
			perror("Error en la recepcion de datos");
			exit(1); // sale del programa
		}
		// Cuando ya tiene todos los datos recibidos, los muestra en pantalla
		printf("\033[01;32m\n\nMensaje recibido de: %s",line);
		// ----------------

		//Recibe los mensajes enviados
		recvLen = recv(conexion, line, MAX, 0); // Espera que lleguen todos los datos
		//Si el numero de datos es menor que 0 envia error
		if(recvLen < 0){
			perror("Error en la recepcion de datos");
			exit(1); // sale del programa
		}
		// Cuando ya tiene todos los datos recibidos, los muestra en pantalla
		printf("\n%s\n\033[01;37m", line);
	}
	return 0;
}

/*Funcion cliente
Recibe como parametros los datos del amigo a enviar mensaje
Se encarga de enviar los mensajes a los amigos
*/
int cliente(int argc, char*argv[]){
	char *puerto, *ip;
	puerto = argv[2];
	ip = argv[1];
	int socket_propio; // ID del socket de conexio 
	int conexion; /*conexion -> int que verifica la conexion con el socket*/
	char buffer[MAX]; //Variable para almacenar las escrituras en socket
	struct sockaddr_in servAddr; // Estructura para la direccion del amigo
	struct sockaddr_in localAddr;  // Estructura para la direccion local del mensaje
	socket_propio = socket(AF_INET, SOCK_STREAM, 0); //Pide el socket tcp/ip
	//struct hostent *h;
	
	servAddr.sin_family = AF_INET; // Construccion de direccion del receptor
	
	//Transforma la direccion IP de un tip char ej: "127.0.0.1" en tipo direccion para ser guardada en la 		estructura
	inet_pton(AF_INET,ip,&(servAddr.sin_addr.s_addr));
	servAddr.sin_port= htons(atoi(puerto)); //conversion del char* a int y de int a bytes de red

	//-----------------------------------------------------------------------------------
	//Conexion con el socket 
	conexion = connect(socket_propio, (struct sockaddr *) &servAddr, sizeof(servAddr));
	if(conexion <0){ //Si conexion es menor que cero, indica que exites error en la conexion
		perror("No se puede realizar la conexion" );
		exit(1);
	}

	conexion = send(socket_propio,argv[0],strlen(argv[0])+1,0); //Verifica la conexion con el socket, para el envio de mensajes
	
	//Si conexion es igual a 1
	if(conexion <0){  // Indica que el mensaje no se pudo enviar correctamente
		perror("Fallo en la conexion. Mensaje no enviado"); 
		close(socket_propio);
		exit(1);
	}

	char mensaje[MAX]; //Variable que guardara el mensaje ingresado por el usuario
	printf("\033[01;33mIngrese el mensaje deseado: ");//Solicita al usuario el mensaje que desea enviar
	scanf(" %[^\n]",mensaje);	//Lee el mensaje ingresado y lo guarda en la variable mensaje
	
	//Proceso para enviar el mensaje
	conexion = send(socket_propio,mensaje,strlen(mensaje)+1,0);
	
	//Si conexion es igual a 1
	if(conexion <0){ 
		perror("\033[01;37mFallo en la conexion. Mensaje no enviado"); 
		close(socket_propio);
		exit(1);
	}
	else{
		printf("\033[01;37m\nMensaje enviado exitosamente\n");
	}
} 

void main(){
	char* datos[3];
	datos[0] = "vero";
	datos[1] = "192.168.1.109";
	datos[2] = "62105";
	
	cliente(3,datos);
	
}
