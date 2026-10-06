/*
 * TP Programacion 1 - Sistema de reservas de hotel
 * Integrantes: Denise Muzica, Santiago Rojas, Ornella Sansalone Rodriguez
 *
 * Programa con menu de opciones que trabaja con una ESTRUCTURA (T_RESERVA)
 * y un ARCHIVO DE TEXTO (reservas.txt).
 * No usa memoria dinamica (malloc/calloc/realloc) ni variables globales.
 * El unico puntero es FILE *, que C exige para trabajar con archivos.
 */

//BIBLIOTECAS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

//CONSTANTES
#define STRING 15
#define ARCHIVO "reservas.txt"
#define ARCHIVO_CON_TARJETA "reservas_con_tarjeta.txt"
#define ARCHIVO_SIN_TARJETA "reservas_sin_tarjeta.txt"
#define DESCUENTO 0.10
//Formato de cada linea del archivo: cliente tarjeta habitacion medio_de_pago monto
//ejemplo: PEREZ 1 101 D 15000.00
#define FORMATO_LECTURA "%14s %d %d %c %f"
#define FORMATO_ESCRITURA "%s %d %d %c %.2f\n"
#define CAMPOS 5

//ESTRUCTURA RESERVA
typedef struct{
	char cliente[STRING];   //apellido del cliente (una palabra)
	bool tarjeta;           //true si tiene tarjeta de cliente regular
	int habitacion;         //numero de habitacion
	char medio_de_pago;     //'D' debito, 'E' efectivo, 'C' credito
	float monto;            //monto de la reserva
}T_RESERVA;

//DECLARACIONES DE FUNCIONES
//menu y funciones generales (de todo el grupo)
void mostrar(T_RESERVA hotel);
int leer_entero(void);
float leer_float(void);
char leer_letra(void);
void leer_apellido(char texto[]);
void limpiar_buffer(void);
void fin_de_entrada(void);
bool habitacion_ocupada(int numero);
void mostrar_encabezado(void);
void mostrar_reserva(T_RESERVA hotel);
//opciones 1 y 2 (Ornella)
void cargar_reserva(T_RESERVA hotel);
void listar_reservas(T_RESERVA hotel);
//opciones 3 y 4 (Denise)
void listar_debito_efectivo(T_RESERVA hotel);
void buscar_reserva(T_RESERVA hotel);
//opciones 5 y 6 (Santiago)
void dividir_por_tarjeta(T_RESERVA hotel);
void salir_del_sistema(void);

//INT MAIN
int main(){
	T_RESERVA hotel = {"", false, 0, ' ', 0};
	mostrar(hotel);
	return 0;
}

//FUNCIONES

//==================== MENU Y FUNCIONES GENERALES ====================

//Menu principal: se repite hasta elegir la opcion 6.
//Recibe la reserva "hotel" y se la pasa a cada opcion para usarla como variable de trabajo.
void mostrar(T_RESERVA hotel){
	int opcion;
	do {
		puts("\n================ MENU ================");
		printf("1) cargar una reserva nueva");
		printf("\n2) mostrar lista de todas las reservas");
		printf("\n3) mostrar solo los que pagaron con debito o efectivo (10%% de descuento)");
		printf("\n4) buscar una reserva (habitacion ocupada o por cliente)");
		printf("\n5) dividir en dos archivos segun tarjeta de cliente regular");
		printf("\n6) salir del sistema");
		printf("\nopcion= ");
		opcion = leer_entero();
		switch (opcion){
			case 1: cargar_reserva(hotel); break;
			case 2: listar_reservas(hotel); break;
			case 3: listar_debito_efectivo(hotel); break;
			case 4: buscar_reserva(hotel); break;
			case 5: dividir_por_tarjeta(hotel); break;
			case 6: salir_del_sistema(); break;
			default: printf("\nERROR... opcion invalida, elija un numero del 1 al 6.\n"); break;
		}
	} while (opcion != 6);
}

//Lee un numero entero. Si el usuario escribe letras, lo vuelve a pedir.
int leer_entero(void){
	int numero, leidos;
	leidos = scanf("%d", &numero);
	while (leidos != 1){
		if (leidos == EOF){
			fin_de_entrada();
		}
		limpiar_buffer();
		printf("Debe ingresar un numero entero: ");
		leidos = scanf("%d", &numero);
	}
	limpiar_buffer();
	return numero;
}

//Lee un numero con decimales. Si el usuario escribe letras, lo vuelve a pedir.
float leer_float(void){
	float numero;
	int leidos;
	leidos = scanf("%f", &numero);
	while (leidos != 1){
		if (leidos == EOF){
			fin_de_entrada();
		}
		limpiar_buffer();
		printf("Debe ingresar un numero: ");
		leidos = scanf("%f", &numero);
	}
	limpiar_buffer();
	return numero;
}

//Lee una sola letra (salteando espacios) y la devuelve en mayuscula.
char leer_letra(void){
	char letra;
	if (scanf(" %c", &letra) != 1){
		fin_de_entrada();
	}
	limpiar_buffer();
	return toupper((unsigned char)letra);
}

//Lee un apellido (una palabra, maximo STRING-1 letras) y lo pasa a mayusculas,
//asi las busquedas no dependen de como se escribio.
void leer_apellido(char texto[]){
	int i;
	if (scanf("%14s", texto) != 1){
		fin_de_entrada();
	}
	limpiar_buffer();
	for (i = 0; texto[i] != '\0'; i++){
		texto[i] = toupper((unsigned char)texto[i]);
	}
}

//Descarta lo que haya quedado escrito en la linea.
void limpiar_buffer(void){
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
}

//Si se termina la entrada del teclado (Ctrl+Z en Windows, Ctrl+D en Linux)
//el programa termina para no quedar en un loop infinito.
void fin_de_entrada(void){
	printf("\nFin de la entrada. Fuera del sistema.\n");
	exit(0);
}

//Devuelve true si la habitacion ya tiene una reserva en el archivo.
bool habitacion_ocupada(int numero){
	FILE *archivo;
	T_RESERVA hotel;
	int tarjeta;
	bool ocupada = false;
	archivo = fopen(ARCHIVO, "r");
	if (archivo == NULL){
		return false;
	}
	while (!ocupada && fscanf(archivo, FORMATO_LECTURA, hotel.cliente, &tarjeta,
			&hotel.habitacion, &hotel.medio_de_pago, &hotel.monto) == CAMPOS){
		if (hotel.habitacion == numero){
			ocupada = true;
		}
	}
	fclose(archivo);
	return ocupada;
}

void mostrar_encabezado(void){
	printf("\n%-15s %-10s %-8s %-10s %12s", "CLIENTE", "HABITACION", "TARJETA", "PAGO", "MONTO");
	printf("\n---------------------------------------------------------");
}

void mostrar_reserva(T_RESERVA hotel){
	char medio[STRING];
	switch (hotel.medio_de_pago){
		case 'D': strcpy(medio, "Debito"); break;
		case 'E': strcpy(medio, "Efectivo"); break;
		case 'C': strcpy(medio, "Credito"); break;
		default: strcpy(medio, "?"); break;
	}
	printf("\n%-15s %-10d %-8s %-10s %12.2f", hotel.cliente, hotel.habitacion,
		hotel.tarjeta ? "SI" : "NO", medio, hotel.monto);
}

//==================== OPCIONES 1 Y 2 - ORNELLA ====================

//OPCION 1: pide los datos de una reserva, los valida y la agrega al final del archivo.
void cargar_reserva(T_RESERVA hotel){
	FILE *archivo;
	char respuesta;

	printf("\n--- CARGAR RESERVA NUEVA ---");
	printf("\nApellido del cliente (una palabra, max %d letras): ", STRING - 1);
	leer_apellido(hotel.cliente);

	printf("Numero de habitacion: ");
	hotel.habitacion = leer_entero();
	while (hotel.habitacion <= 0 || habitacion_ocupada(hotel.habitacion)){
		if (hotel.habitacion <= 0){
			printf("El numero debe ser mayor a 0. Numero de habitacion: ");
		} else {
			printf("La habitacion %d ya esta ocupada. Elija otra: ", hotel.habitacion);
		}
		hotel.habitacion = leer_entero();
	}

	printf("Tiene tarjeta de cliente regular? (S/N): ");
	respuesta = leer_letra();
	while (respuesta != 'S' && respuesta != 'N'){
		printf("Responda S o N: ");
		respuesta = leer_letra();
	}
	hotel.tarjeta = (respuesta == 'S');

	printf("Medio de pago (D=debito, E=efectivo, C=credito): ");
	hotel.medio_de_pago = leer_letra();
	while (hotel.medio_de_pago != 'D' && hotel.medio_de_pago != 'E' && hotel.medio_de_pago != 'C'){
		printf("Ingrese D, E o C: ");
		hotel.medio_de_pago = leer_letra();
	}

	printf("Monto: ");
	hotel.monto = leer_float();
	while (hotel.monto <= 0){
		printf("El monto debe ser mayor a 0. Monto: ");
		hotel.monto = leer_float();
	}

	archivo = fopen(ARCHIVO, "a");
	if (archivo == NULL){
		printf("\nERROR: no se pudo abrir el archivo %s.\n", ARCHIVO);
		return;
	}
	fprintf(archivo, FORMATO_ESCRITURA, hotel.cliente, hotel.tarjeta ? 1 : 0,
		hotel.habitacion, hotel.medio_de_pago, hotel.monto);
	fclose(archivo);
	printf("\nReserva guardada correctamente.\n");
}

//OPCION 2: muestra todas las reservas del archivo, la cantidad y el total facturado.
void listar_reservas(T_RESERVA hotel){
	FILE *archivo;
	int tarjeta, cantidad = 0;
	double total = 0;   //double: mas precision para acumular muchos montos

	archivo = fopen(ARCHIVO, "r");
	if (archivo == NULL){
		printf("\nTodavia no hay reservas cargadas.\n");
		return;
	}
	printf("\n--- TODAS LAS RESERVAS ---");
	mostrar_encabezado();
	while (fscanf(archivo, FORMATO_LECTURA, hotel.cliente, &tarjeta,
			&hotel.habitacion, &hotel.medio_de_pago, &hotel.monto) == CAMPOS){
		hotel.tarjeta = (tarjeta != 0);
		mostrar_reserva(hotel);
		cantidad++;
		total += hotel.monto;
	}
	fclose(archivo);
	if (cantidad == 0){
		printf("\n(no hay reservas en el archivo)\n");
	} else {
		printf("\n\nCantidad de reservas: %d", cantidad);
		printf("\nTotal facturado: $%.2f\n", total);
	}
}

//==================== OPCIONES 3 Y 4 - DENISE ====================

//OPCION 3: muestra solo las reservas pagadas con debito o efectivo,
//con el monto final aplicando un 10% de descuento.
void listar_debito_efectivo(T_RESERVA hotel){
	FILE *archivo;
	int tarjeta, cantidad = 0;

	archivo = fopen(ARCHIVO, "r");
	if (archivo == NULL){
		printf("\nTodavia no hay reservas cargadas.\n");
		return;
	}
	printf("\n--- RESERVAS PAGADAS CON DEBITO O EFECTIVO (10%% DE DESCUENTO) ---");
	printf("\n%-15s %-10s %-8s %-10s %12s %14s", "CLIENTE", "HABITACION", "TARJETA", "PAGO", "MONTO", "CON DESCUENTO");
	printf("\n------------------------------------------------------------------------");
	while (fscanf(archivo, FORMATO_LECTURA, hotel.cliente, &tarjeta,
			&hotel.habitacion, &hotel.medio_de_pago, &hotel.monto) == CAMPOS){
		hotel.tarjeta = (tarjeta != 0);
		if (hotel.medio_de_pago == 'D' || hotel.medio_de_pago == 'E'){
			mostrar_reserva(hotel);
			printf("%15.2f", hotel.monto * (1 - DESCUENTO));
			cantidad++;
		}
	}
	fclose(archivo);
	if (cantidad == 0){
		printf("\n(ninguna reserva fue pagada con debito o efectivo)\n");
	} else {
		printf("\n\nCantidad de reservas con descuento: %d\n", cantidad);
	}
}

//OPCION 4: pregunta al usuario por que dato buscar (habitacion o cliente)
//y muestra las reservas que coinciden.
void buscar_reserva(T_RESERVA hotel){
	FILE *archivo;
	int tarjeta, criterio, habitacion_buscada = 0, encontradas = 0;
	char cliente_buscado[STRING] = "";

	printf("\n--- BUSCAR RESERVA ---");
	printf("\n1) buscar por numero de habitacion (ver si esta ocupada)");
	printf("\n2) buscar por apellido del cliente");
	printf("\nopcion= ");
	criterio = leer_entero();
	while (criterio != 1 && criterio != 2){
		printf("Elija 1 o 2: ");
		criterio = leer_entero();
	}
	if (criterio == 1){
		printf("Numero de habitacion a buscar: ");
		habitacion_buscada = leer_entero();
	} else {
		printf("Apellido del cliente a buscar: ");
		leer_apellido(cliente_buscado);
	}

	archivo = fopen(ARCHIVO, "r");
	if (archivo == NULL){
		printf("\nTodavia no hay reservas cargadas.\n");
		return;
	}
	while (fscanf(archivo, FORMATO_LECTURA, hotel.cliente, &tarjeta,
			&hotel.habitacion, &hotel.medio_de_pago, &hotel.monto) == CAMPOS){
		hotel.tarjeta = (tarjeta != 0);
		if ((criterio == 1 && hotel.habitacion == habitacion_buscada) ||
			(criterio == 2 && strcmp(hotel.cliente, cliente_buscado) == 0)){
			if (encontradas == 0){
				mostrar_encabezado();
			}
			mostrar_reserva(hotel);
			encontradas++;
		}
	}
	fclose(archivo);

	if (criterio == 1){
		if (encontradas > 0){
			printf("\n\nLa habitacion %d esta OCUPADA.\n", habitacion_buscada);
		} else {
			printf("\nLa habitacion %d esta LIBRE.\n", habitacion_buscada);
		}
	} else {
		if (encontradas > 0){
			printf("\n\nSe encontraron %d reserva(s) a nombre de %s.\n", encontradas, cliente_buscado);
		} else {
			printf("\nNo hay reservas a nombre de %s.\n", cliente_buscado);
		}
	}
}

//==================== OPCIONES 5 Y 6 - SANTIAGO ====================

//OPCION 5: divide el archivo de reservas en dos archivos de texto nuevos
//segun el campo booleano tarjeta (tarjeta de cliente regular).
//Lee una reserva por vez, no guarda todo el archivo en memoria.
void dividir_por_tarjeta(T_RESERVA hotel){
	FILE *origen, *con_tarjeta, *sin_tarjeta;
	int tarjeta, cant_con = 0, cant_sin = 0;

	origen = fopen(ARCHIVO, "r");
	if (origen == NULL){
		printf("\nTodavia no hay reservas cargadas.\n");
		return;
	}
	con_tarjeta = fopen(ARCHIVO_CON_TARJETA, "w");
	sin_tarjeta = fopen(ARCHIVO_SIN_TARJETA, "w");
	if (con_tarjeta == NULL || sin_tarjeta == NULL){
		printf("\nERROR: no se pudieron crear los archivos nuevos.\n");
		if (con_tarjeta != NULL) fclose(con_tarjeta);
		if (sin_tarjeta != NULL) fclose(sin_tarjeta);
		fclose(origen);
		return;
	}
	while (fscanf(origen, FORMATO_LECTURA, hotel.cliente, &tarjeta,
			&hotel.habitacion, &hotel.medio_de_pago, &hotel.monto) == CAMPOS){
		hotel.tarjeta = (tarjeta != 0);
		if (hotel.tarjeta){
			fprintf(con_tarjeta, FORMATO_ESCRITURA, hotel.cliente, 1,
				hotel.habitacion, hotel.medio_de_pago, hotel.monto);
			cant_con++;
		} else {
			fprintf(sin_tarjeta, FORMATO_ESCRITURA, hotel.cliente, 0,
				hotel.habitacion, hotel.medio_de_pago, hotel.monto);
			cant_sin++;
		}
	}
	fclose(origen);
	fclose(con_tarjeta);
	fclose(sin_tarjeta);
	printf("\n--- ARCHIVO DIVIDIDO ---");
	printf("\n%d reserva(s) CON tarjeta de cliente regular -> %s", cant_con, ARCHIVO_CON_TARJETA);
	printf("\n%d reserva(s) SIN tarjeta de cliente regular -> %s\n", cant_sin, ARCHIVO_SIN_TARJETA);
}

//OPCION 6: mensaje de salida (el do-while del menu termina con la opcion 6).
void salir_del_sistema(void){
	printf("\nFuera del sistema. Hasta luego!\n");
}
