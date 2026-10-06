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
