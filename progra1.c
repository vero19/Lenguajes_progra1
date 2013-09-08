#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*Funcion enviarMensajes
Es la funcion encargada de solicitar la funcion
*/
int enviarMensajes(){
	FILE *archivo=NULL;
	char* nombre = "amigos.txt";
	char lectura[80],nom_amigo[80],ip_amigo[80],puerto_amigo[80];
	int tamanno;

	printf("\nMensaje para: "); // Solicita el usuario el nombre del amigo al cual le desea enviar msj
	scanf("%s",nom_amigo); //Lee el dato ingresado y lo guarda en nom_amigo
	
	archivo = fopen(nombre, "r"); //Abre el archivo para leerlo

	//Lectura del archivo linea por linea
	while(!feof(archivo)){
		fscanf(archivo,"%s",lectura);
		int n;
		n = strcmp(nom_amigo,lectura); // Funcion que compara las cadenas nom_amigo y lectura
		// lectura hace referencia al dato que esta leyendo
		// nom_amigo es el dato que el usuario ingreso anteriormente
		// si n es igual a 0, se refiere que ambas cadenas son iguales
		if(n==0){ //si los datos son iguales ingresa el if
			fscanf(archivo,"%s",lectura); // lee el segundo dato del archivo
			strcpy(lectura,ip_amigo);	// guarda el dato en ip_amigo
			fscanf(archivo,"%s",lectura);	// lee el tercer dato del archivo
			strcpy(lectura,puerto_amigo);  // guarda el dato en puerto_amigo
			break;
		}
		if(feof(archivo)){
			printf("\nNo se tiene informacion del contacto indicado\n");
			}
	}
	fclose(archivo);
}

/* Funcion agregarAmigos
Le solicita al usuario 3 datos
1- Nombre de usuario del amigo
2- IP del amigo
3- Puerto habilitado del amigo
Guarda los 3 datos solicitados en un struct para luego enviarlos al archivo
amigos.txt que funciona como la agenda de amigos
*/
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
	while(opcion != 'n' & opcion != 's'){
		printf("\nIngreso una opcion incorrecta\n");
		printf("Desea ingresar otro contacto: (s/n)");
		scanf("%s",&opcion);
	}

	// Si ingreso la opcion 's', vuelve llamar a la funcion agregarAmigos()
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
		enviarMensajes(); // se dirige a enviarMensajes()
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

/* Funcion configuracion
Verifica si el archivo config tiene los 3 datos del usuario
1- Nombre de usuario
2- IP del usuario
3- Puerto del usuario
Si el archivo tiene los datos anteriores los envia para ser usados en la funcion servidor()
Sino se los solicita al usuario y una vez ingresados se los envia a la funcion servidor()
*/
void configuracion(){
	FILE *archivo=NULL;
	char* nombre = "config.txt";
	char lectura[80],usuario[80],ip[80],puerto[80];
	int tamanno;
	
	archivo = fopen(nombre, "r"); //abre el archivo config.txt

	while(!feof(archivo)){
		fscanf(archivo,"%s",lectura); // lee cada linea del archivo
		tamanno = ftell(archivo); // determina el tamanno del archivo
	}

	// Si el tamnanno es igual a 0
	// solicita al usuario los datos requeridos
	if(tamanno == 0){
		archivo = fopen(nombre,"a"); //abre el archivo para escribir en el
		printf("\n ----- Configuracion del programa ----- \n");
		printf("Indique su nombre de usuario: ");
		scanf("%s",usuario);	//lee el dato ingresado por el usuario y lo guarda en usuario
		fprintf(archivo, "%s",usuario);	// escribi lo que esta en usuario en el archivo
		printf("Indique su ip de usuario: ");
		scanf("%s",ip);	//lee el dato ingresado por el usuario y lo guarda en ip
		fprintf(archivo, " %s ",ip); // escribi lo que esta en ip en el archivo
		printf("Indique su puerto de usuario: "); 
		scanf("%s",puerto); //lee el dato ingresado por el usuario y lo guarda en puerto
		fprintf(archivo, "%s\n",puerto); // escribi lo que esta en puerto en el archivo
	}
}

void main(){
	configuracion();
	printf("-------------BIENVENIDO (A) AL PROGRAMA -------------\n\n");
	int salir = 0;
	while(salir==0)
		menu();
}

