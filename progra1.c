#include <stdio.h>
#include <string.h>
#include <stdlib.h>
<<<<<<< HEAD
=======


/*struct amigos
se define un struct para almacenar los datos
de contacto para luego enviarlos al archivo amigos.txt
*/
struct amigos{
	char usuario[100], ip[100], puerto[100];
	};
>>>>>>> 132a5ed605890b0b9a71fdeace145f89ed07cf22

/* Funcion agregarAmigos
Le solicita al usuario 3 datos
1- Nombre de usuario del amigo
2- IP del amigo
3- Puerto habilitado del amigo
Guarda los 3 datos solicitados en un struct para luego enviarlos al archivo
amigos.txt que funciona como la agenda de amigos
*/
<<<<<<< HEAD
int agregarAmigos(){
	FILE* fichero;
	fichero = fopen("amigos.txt","a"); // Abre el archivo amigos.txt
	char datos[80];
	int cantidad;

	if (fichero ==NULL) 
		return -1;

	// ---------------------------------------------------
	// Solicita los datos del amigo al usuario
	printf("\n -- Agregar amigos --");
	printf("\nIngrese el nombre del amigo: "); // Solicita el nombre del amigo
	scanf("%s",datos);	// Lee el dato ingresado y lo guarda en la variable datos
	fprintf(fichero, "%s",datos);	// Escribe el valor de la variable datos en el archivo amigos.txt
	printf("Ingrese la ip del amigo: ");	// Solicita la ip del amigo
	scanf("%s",datos);	// Lee el dato ingresado y lo guarda en la variable datos
	fprintf(fichero, " %s ",datos); // Escribe el valor de la variable datos en el archivo amigos.txt
	printf("Ingrese el puerto del amigo: ");  // Solicita el puerto del amigo
	scanf("%s",datos);	// Lee el dato ingresado y lo guarda en la variable datos
	fprintf(fichero, "%s\n",datos); // Escribe el valor de la variable datos en el archivo amigos.txt
	// ----------------------------------------------------

	char opcion;
	printf("\nDesea ingresar otro contacto: (s/n)"); // Consulta al usuario si desea ingresar otro contacto
	scanf("%s",&opcion); // Lee la opcion ingresada por el usuario y la guarda en la variable opcion

	// Si el usuario ingreso una opcion distina a 'n' o 's'
	// Le indica que la opcion es incorrecta y que vuelva a intentar
=======
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
>>>>>>> 132a5ed605890b0b9a71fdeace145f89ed07cf22
	while(opcion != 'n' & opcion != 's'){
		printf("\nIngreso una opcion incorrecta\n");
		printf("Desea ingresar otro contacto: (s/n)");
		scanf("%s",&opcion);
	}
<<<<<<< HEAD
	// Si ingreso la opcion 's', vuelve llamar a la funcion agregarAmigos()
=======
>>>>>>> 132a5ed605890b0b9a71fdeace145f89ed07cf22
	if(opcion == 's')
		agregarAmigos();
}

/* Funcion opciones
Determina que debe ser el programa segun el dato que ingreso el usuario
Si ingresa 1 --> se dirige a la funcion agregarAmigos()
Si ingresa 2 --> se dirige a la funcion enviarMensajes()
Si ingresa 3 --> cierra el programa
Si ingresa otra opcion --> Indica que ingreso una opcion incorrecta y le solicita la opcion de nuevo
*/
void opciones(int opc){
	if(opc == 1)
		agregarAmigos(); // se dirige a agregarAmigos()
	if(opc ==2)
		printf("Ingreso a enviar"); // se dirige a enviarMensajes()
	if(opc ==3)
		exit(0);	// cierra el programa
	if(opc > 3){
		printf("Ingreso una opcion incorrecta \n"); //Indica que ingreso una opcion incorrecta
		printf("Ingrese la opcion deseada: ");	//Solicita de nuevo la opcion
		scanf("%d", &opc); //Lee la opcion que ingreso el usuario
		opciones(opc);	// vuelve a llamar a la funcion opciones
	}
}

/*Funcion menu
Funcion que solicita al usuario que accion desea realizar en el programa
Opcion 1 --> permite agregar amigos a su agenda de contactos
Opcion 2 --> permite enviar mensaje a un amigo determinado
Opcion 3 --> salir del programa
*/
void menu(){
	int opcion;
	printf("\n---- Menu ---\n");
	printf("1. Agregar amigos\n");
	printf("2. Enviar mensaje\n");
	printf("3.Salir\n");
	printf("\n");
	printf("Ingrese la opcion deseada: ");
	scanf("%d",&opcion); // lee la opcion que el usuario ingreso y lo guarda en la variable opcion
	opciones(opcion); // se dirige a la funcion opciones
}


void main(){
	printf("-------------BIENVENIDO (A) AL PROGRAMA -------------\n\n");
	int salir = 0;
	while(salir==0)
		menu();
}

//Funcion main
void main(){
	printf("\n-------------BIENVENIDO (A) AL PROGRAMA -------------\n\n");
	menu();
}
