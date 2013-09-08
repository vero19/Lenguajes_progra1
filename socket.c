//Inclusiones de las librerias que se van a utilizar
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

//Envia un mensaje de error y termina el programa
void error(char *mensaje_error){
	printf("%s\nIntente de nuevo!\n",mensaje_error);
	exit(0);
}

/*Comandos que se utilizaran:
033[2J Limpia la pantalla
033[1;1H Se coloca en la esquina superior irzq de la misma
033[01;33m Color Amarillo
033[01;37m Color Blanco
033[01;32m Color Verde
033[2K\r Limpia la linea en caso de que se este escribiendo
033[01;31m Color Rojo
033[01;37m Color Blanco(Normal)
*/

int main (int c,  char *arg[]){ 

	if (c!=3){
		error("Ingrese los 3 argumentos necesarios");
	}

	pid_t inicioPID=fork();//Inicia el fork y guarda el identificador del proceso
	if (inicioPID==0){
		int socket_propio;//ID del socket de conexion
		struct sockaddr_in direc_servidor;//Estructura para la direccion del receptor del mensaje
		char buffer[256];//Variable para almacenar las escrituras en socket
		socket_propio = socket(AF_INET, SOCK_STREAM, 0);//Pide el socket tcp/ip

		//Construccion de direccion del receptor
		direc_servidor.sin_family = AF_INET;

		//transforma la direccion IP de un tipo char ej: "127.0.0.1" en tipo direccion para ser guardado en la estructura
		inet_pton(AF_INET, arg[3], &(direc_servidor.sin_addr.s_addr));
		//esta linea es la que establece el puerto a utilizar por parte del usuario
		direc_servidor.sin_port = htons(atoi(arg[2])); // conversion de char* a int y el htons convierte un int a bytes de red  

		//Inicia el proceso de conexion
		printf("Iniciando conexion\n");
		printf("Espere un momento...\n");
		int conecxion=-1;//Identificador de conexion 
		int veces = 0;
		while(conecxion<0){
			//Intenta conectarse (max 20 intentos en 20 segundos)
			conecxion = connect(socket_propio,
			(struct sockaddr *) &direc_servidor,
			sizeof(direc_servidor));
			veces++;
			if (veces > 20){
				close(socket_propio);
				kill(getppid(),9);
				error("No se logro realizar la conexion en los 20 intentos");
			}//Cierre del if (veces)
			sleep(1);//Pausa de 1 segundo
		}//Cierre del while

		//Una vez realizada la conexion imprime lo siguiente

		printf(	"\033[2J\033[1;1H"
		"---------------------------------------\n"
		"||||| \033[01;33mBienvenido!!!\033[01;37m |||||\n"
		"---------------------------------------\n"
		"\033[01;32mConexion Establecida!!!!\n"
		"Ingrese los mensajes\033[01;37m\n");

		//Separacion de procesos envio de mensajes y cierre de socket
		pid_t envio = fork();//Inicia el fork 
	
		//Proceso que la entrada del stdout y envia el mensaje
		if (envio == 0) {
			pid_t proceso2 = (getppid()-1);//Devuelve el PID
			int estado = 1;
			while(estado == 1){
				if (getppid()==1){ //Revisa estado del proceso padre para cerrar sockets
					close(socket_propio);
					int cerrar = kill(proceso2,8); //Kill es para enviar señales a un proceso pid_t
					sleep(2);
					estado = 0;
					//Lineas que le ponen color a los mensajes impresos
					char *color = "";
					if(cerrar==0) {
						color ="\033[A\033[2K";}
					printf(	"\033[2K\r"
					"\033[01;32m%s"
					"Conexion Finalizada..."
					"\nPresione Enter para salir"
					"\033[01;37m!!!",color);
				}//Fin de if (getppid)
			}//Fin del while	
		}//Fin del if(envio)
		else {	
			int estado = 1;
			while(estado == 1){
				bzero(buffer,256);//Limpia la variable buffer
				//Recibe texto por parte del usuario y lo guarda en la variable buffer
				//la funcion fgets es una funcion que lee los caracteres de un file
				fgets(buffer,255,stdin);
				if(strcmp(buffer,"\n") != 0){ //Compara el mensaje a enviar con un salto de linea para verificar que se vaya a enviar algo
					printf(	"\033[A\033[2K\033[01;36m"
					"Mensaje Enviado:\033[01;37m %s",buffer);
				}//Fin de if(strcmp)
				//Escribe en el socket para enviar
				write(socket_propio,buffer,strlen(buffer));//Escribe el socket con el mensaje a enviar
				estado = 0;
			}//Fin del while
		}//Fin del else
	}//Fin del if principal

	// Proceso padre: Aca ejecuta el codigo servidor
	else {
		int socket_Servidor, socket_serv_conectado;
		char buffer[256];//Variable para almacenar lecturas del socket

		struct sockaddr_in direc_servidor, direc_cliente;//Estructura para guardar las direcciones en el socket

		//Pide el socket
		//Tipo internet tcp/ip
		socket_Servidor = socket(AF_INET, SOCK_STREAM, 0);//Pide el socket tcp/ip
	
		//Construccion de direccion de este servidor
		direc_servidor.sin_family = AF_INET;
		direc_servidor.sin_addr.s_addr = INADDR_ANY;//Su propio IP
		direc_servidor.sin_port = htons(atoi(arg[1])); // conversion de char* a int y el htons convierte un int a bytes de red
	
		//Union del socket con esta direccion
		bind(socket_Servidor, (struct sockaddr *) &direc_servidor, sizeof(direc_servidor));

		//Le indica al socket que espere conexiones
		listen(socket_Servidor,5);

		//Inicial el proceso de aceptar conexiones y almacenarla en un nuevo
		//identificador de socket
		socklen_t largo_dir_cliente = sizeof(direc_cliente);
		socket_serv_conectado = accept(socket_Servidor, (struct sockaddr *) &direc_cliente, &largo_dir_cliente);
		
		//Inicia recepcion del mensaje y el cierre del socket
		pid_t recepcion=fork();//Inicia el fork 

		if (recepcion == 0) {
			pid_t proceso3 = (getppid()+1);
			int ciclo = 1;
			while(ciclo == 1){
				if(getppid()==1){//Revisa estado del proceso padre para cerrar sockets
					close(socket_Servidor);
					close(socket_serv_conectado);
					kill(proceso3,8);
					ciclo = 0;
				}//Fin del if(getppid)
			}//Fin del while
		}//Fin del if(recepcion)
		else {
			int ciclo = 1;
			while(ciclo == 1){
				//Lectura del socket
				bzero(buffer,256);//Limpia el buffer
				read(socket_serv_conectado,buffer,255); //Lee los datos que se encuentran en el socket
				if(strcmp(buffer,"\n") != 0){ //Compara los escrito en buffer con con el salto de linea
					printf(	"\033[2K\r\033[01;31m"
					"Mensaje Recibido:\033[01;37m %s",buffer); //Imprime el mensaje recibido
				}//Fin del if(strcmp)
				ciclo = 0;
			}//fin del while
		}//Fin del primer else
	}//Fin del else principal
return 1;
}//Fin del main
