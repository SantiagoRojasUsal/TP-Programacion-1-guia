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
	float total = 0;

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
