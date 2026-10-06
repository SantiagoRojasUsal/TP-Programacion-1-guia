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
void menu(void);
int leer_entero(void);
float leer_float(void);
char leer_letra(void);
void limpiar_buffer(void);
void pasar_a_mayusculas(char texto[]);
bool habitacion_ocupada(int numero);
void mostrar_encabezado(void);
void mostrar_reserva(T_RESERVA hotel);
//opciones 1 y 2 (Ornella)
void cargar_reserva(void);
void listar_reservas(void);
//opciones 3 y 4 (Denise)
void listar_debito_efectivo(void);
void buscar_reserva(void);
//opciones 5 y 6 (Santiago)
void dividir_por_tarjeta(void);
void salir_del_sistema(void);

//INT MAIN
int main(){
	menu();
	return 0;
}

//FUNCIONES

//==================== MENU Y FUNCIONES GENERALES ====================

void menu(void){
	int opcion;
	do {
		printf("\n========== HOTEL - MENU ==========");
		printf("\n1) Cargar una reserva nueva");
		printf("\n2) Mostrar todas las reservas");
		printf("\n3) Mostrar reservas pagadas con debito o efectivo (10%% de descuento)");
		printf("\n4) Buscar una reserva (por habitacion o por cliente)");
		printf("\n5) Dividir el archivo segun tarjeta de cliente regular");
		printf("\n6) Salir del sistema");
		printf("\nOpcion: ");
		opcion = leer_entero();
		switch (opcion){
			case 1: cargar_reserva(); break;
			case 2: listar_reservas(); break;
			case 3: listar_debito_efectivo(); break;
			case 4: buscar_reserva(); break;
			case 5: dividir_por_tarjeta(); break;
			case 6: salir_del_sistema(); break;
			default: printf("\nERROR: opcion invalida, elija un numero del 1 al 6.\n"); break;
		}
	} while (opcion != 6);
}

//Lee un numero entero. Si el usuario escribe letras, lo vuelve a pedir.
//Si se termina la entrada (Ctrl+Z / Ctrl+D) devuelve 6 para salir del sistema.
int leer_entero(void){
	int numero, leidos;
	leidos = scanf("%d", &numero);
	while (leidos != 1){
		if (leidos == EOF){
			return 6;
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
	while (leidos != 1 && leidos != EOF){
		limpiar_buffer();
		printf("Debe ingresar un numero: ");
		leidos = scanf("%f", &numero);
	}
	if (leidos == EOF){
		return 0;
	}
	limpiar_buffer();
	return numero;
}

//Lee una sola letra (salteando espacios) y la devuelve en mayuscula.
char leer_letra(void){
	char letra = ' ';
	if (scanf(" %c", &letra) == 1){
		limpiar_buffer();
	}
	return toupper((unsigned char)letra);
}

//Descarta lo que haya quedado escrito en la linea.
void limpiar_buffer(void){
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
}

//Pasa un texto a mayusculas para poder compararlo sin importar como se escribio.
void pasar_a_mayusculas(char texto[]){
	int i;
	for (i = 0; texto[i] != '\0'; i++){
		texto[i] = toupper((unsigned char)texto[i]);
	}
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

void cargar_reserva(void){
	printf("\nOpcion en desarrollo (Ornella).\n");
}

void listar_reservas(void){
	printf("\nOpcion en desarrollo (Ornella).\n");
}

//==================== OPCIONES 3 Y 4 - DENISE ====================

void listar_debito_efectivo(void){
	printf("\nOpcion en desarrollo (Denise).\n");
}

void buscar_reserva(void){
	printf("\nOpcion en desarrollo (Denise).\n");
}

//==================== OPCIONES 5 Y 6 - SANTIAGO ====================

//OPCION 5: divide el archivo de reservas en dos archivos de texto nuevos
//segun el campo booleano tarjeta (tarjeta de cliente regular).
//Lee una reserva por vez, no guarda todo el archivo en memoria.
void dividir_por_tarjeta(void){
	FILE *origen, *con_tarjeta, *sin_tarjeta;
	T_RESERVA hotel;
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
