#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

/* Funcion agregarAmigos
Le solicita al usuario 3 datos
1- Nombre de usuario del amigo
2- IP del amigo
3- Puerto habilitado del amigo
Guarda los 3 datos solicitados en un struct para luego enviarlos al archivo
amigos.txt que funciona como la agenda de amigos
*/
void agregarAmigos(){
	char nombre, ip, puerto;
	printf("Indique el nombre de usuario ");
	scanf("%s",&nombre);
	printf("Indique la ip: ");
	scanf("%s",&ip);
	printf("Indique el puerto: ");
	scanf("%s",&puerto);

	FILE* fichero;
	
	fichero = fopen("amigos.txt","wt");
	fputs(nombre, fichero);
	
}

//Funcion que lee el dato ingresado por el usuario
void opciones(int opc){
	if(opc == 1)
		agregarAmigos();
	if(opc ==2)
		printf("Ingreso a enviar mensajes \n");
	if(opc ==3)
		exit(0);
	if(opc > 3){
		printf("Ingreso una opcion incorrecta \n");
		printf("Ingrese la opcion deseada: ");
		scanf("%d", &opc);
		opciones(opc);
	}
}

/*Funcion main
Funcion que solicita al usuario que accion desea realizar en el programa
Opcion 1 --> permite agregar amigos a su agenda de contactos
Opcion 2 --> permite enviar mensaje a un amigo determinado
Opcion 3 --> salir del programa
*/
void main(){
	int opcion;
	printf("---- Menu ---\n");
	printf("1. Agregar amigos\n");
	printf("2. Enviar mensaje\n");
	printf("3.Salir\n");
	printf("\n");
	printf("Ingrese la opcion deseada: ");
	scanf("%d",&opcion);
	opciones(opcion);
}


