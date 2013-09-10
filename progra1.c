//Inclucion de librerias necesarias para el programa
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define MAX 500

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

/*Funcion enviarMensajes
Es la funcion encargada de solicitar la funcion
*/
int enviarMensajes(){
	FILE *archivo=NULL;
	char* nombre = "amigos.txt";
	char lectura[MAX], nom_amigo[MAX];
	char *datos[3];
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
			datos[0] = nom_amigo;
			fscanf(archivo,"%s",lectura); //lee el dato del archivo
			char ip[MAX]; // crea la cadena para guarda la ip
			strcpy(ip,lectura); // copia lo que se leyo del archivo a la cadena ip
			datos[1] = ip; // envia el dato de la cadena ip al arreglo datos
			fscanf(archivo,"%s",lectura); // lee el segundo dato del archivo
			datos[2] = lectura; // envia el dato leido en el archivo al arreglo de datos
			cliente(3,datos); // cuando tiene los datos del amigo llama a cliente() para enviar el mensaje
			break; // se sale del ciclo
		}
		// Si se llega al final del archivo y no se encontro el nombre indicado para enviar el mensaje
		// Indica que no se tiene la informacion del contacto
		if(feof(archivo)){
			printf("\nNo se tiene informacion del contacto indicado\n");
		}
	}
	fclose(archivo); // Cierra el archivo
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
	char datos[MAX];
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
	fclose(fichero);
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
	if(opc == 1){
		agregarAmigos();
	}
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


/* Funcion configuracion
Verifica si el archivo config esta vacio y solicita los datos al usuario
1- Nombre de usuario
2- IP del usuario
3- Puerto del usuario
*/
void datoInicio(){
	FILE *archivo=NULL;
	char* nombre = "config.txt";
	char lectura[MAX],usuario[MAX],ip[MAX],puerto[MAX];
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
	fclose(archivo);
}

/* Verifica el archivo config.txt
recorre el archivo y guarda cada datos en su respectiva variable para ser 
enviados a la funcion servidor*/
void configuracion(){
	FILE *archivo=NULL;
	char* nombre = "config.txt";
	char lectura[MAX],usuario[MAX],ip[MAX],puerto[MAX];
	int tamanno;
	
	archivo = fopen(nombre, "r"); //abre el archivo config.txt

	while(!feof(archivo)){
		fscanf(archivo,"%s",lectura); // lee cada linea del archivo
		strcpy(usuario,lectura);
		fscanf(archivo,"%s",lectura); // lee cada linea del archivo
		strcpy(ip,lectura);
		fscanf(archivo,"%s",lectura); // lee cada linea del archivo
		strcpy(puerto,lectura);
		tamanno = ftell(archivo); // determina el tamanno del archivo
	}

	char *nom[1];
	nom[0] = puerto;
	servidor(3,nom);
	fclose(archivo);
}

/*Funcion *conf
asigna una accion del hilo que ejecuta el programa
El programa se mantiene oyendo el puerto para detectar un mensaje entrante*/
void *conf(void *var){
	int salir = 0;
	while(salir ==0)
		configuracion();
}
/*Funcio *men
asigna otra accion al hilo que ejecuta el programa
El programa permite al usuario ingresar distintas opciones
1 - Agregar amigos
2 - Enviar mensaje
3- Salir del programa */
void *men(void *var){
	int salir = 0;
	while(salir ==0)
		menu();
}

/*Funcion main
incia el programa llamando a la funcion datoInicio --> verifica los datos de configuracion del usuario
Luego ejecuta los hijos, hasta que el usuario le de salir al programa */
int main(){
	datoInicio();
	printf("------------- BIENVENIDO (A) ------------- \n\n");
	pthread_t thread1, thread2;
	char *mensaje1 = "muesta el menu";
	char *mensaje2 = "muesta el menu";
	pthread_create(&thread2,NULL,conf,(void*)mensaje2);
	pthread_create(&thread1,NULL,men,(void*)mensaje1);	
	pthread_join(thread2,NULL);
	pthread_join(thread1,NULL);
	return 0;
}
