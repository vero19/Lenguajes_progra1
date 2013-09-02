#include <stdio.h>
#include <string.h>
#include <stdlib.h>


/*struct amigos
se define un struct para almacenar los datos
de contacto para luego enviarlos al archivo amigos.txt
*/
struct amigos{
	char usuario[100], ip[100], puerto[100];
	};

/* Funcion agregarAmigos
Le solicita al usuario 3 datos
1- Nombre de usuario del amigo
2- IP del amigo
3- Puerto habilitado del amigo
Guarda los 3 datos solicitados en un struct para luego enviarlos al archivo
amigos.txt que funciona como la agenda de amigos
*/
void agregarAmigos(){
	struct amigos amg;
	char nombre[100],ip[100],puerto[100];
	printf("\nIndique el nombre de usuario ");
	scanf("%s",nombre);
	strcpy(amg.usuario,nombre);
	printf("Indique la ip: ");
	scanf("%s",ip);
	strcpy(amg.ip,ip);
	printf("Indique el puerto: ");
	scanf("%s",puerto);
	strcpy(amg.puerto,puerto);

	FILE* fichero;
	
	fichero = fopen("amigos.txt","a");
	if(fichero!= NULL){
		fprintf(fichero,"%s; %s; %s\n",amg.usuario,amg.ip,amg.puerto);
		fclose(fichero);
	}
	
	char opcion;
	printf("\nDesea ingresar otro contacto: (s/n)");
	scanf("%s",&opcion);
	while(opcion != 'n' & opcion != 's'){
		printf("\nIngreso una opcion incorrecta\n");
		printf("Desea ingresar otro contacto: (s/n)");
		scanf("%s",&opcion);
	}
	if(opcion == 's')
		agregarAmigos();
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
void menu(){
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

//Funcion main
void main(){
	printf("\n-------------BIENVENIDO (A) AL PROGRAMA -------------\n\n");
	menu();
}
