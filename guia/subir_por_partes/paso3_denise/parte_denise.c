//PUNTO 3: muestra SOLO las reservas pagadas con debito o efectivo (condicion elegida)
//y el descuento del 10% que les corresponde.
void mostrarPagos(T_RESERVA hotel){
	FILE *f;
	int tarjetaAux;      //fscanf no lee bool, uso un int auxiliar
	int cantidad = 0;    //cuantas reservas cumplen la condicion
	float descuento;

	f = fopen(ARCHIVO, "r");
	if (f == NULL){
		printf("\nTodavia no hay reservas cargadas.\n");
		return;
	}

	printf("\n--- RESERVAS PAGADAS CON DEBITO O EFECTIVO (10%% DE DESCUENTO) ---");
	printf("\n%-15s %-6s %-10s %12s %12s %12s", "CLIENTE", "HAB.", "PAGO", "MONTO", "DESC. 10%", "A PAGAR");
	printf("\n----------------------------------------------------------------------");

	while (fscanf(f, FORMATO_LECTURA, hotel.cliente, &tarjetaAux,
			&hotel.habitacion, &hotel.medio_de_pago, &hotel.monto) == CAMPOS){

		hotel.tarjeta = (tarjetaAux != 0);

		//condicion: solo se muestran las pagadas con debito o efectivo
		if (hotel.medio_de_pago == 'D' || hotel.medio_de_pago == 'E'){
			descuento = hotel.monto * DESCUENTO;
			printf("\n%-15s %-6d ", hotel.cliente, hotel.habitacion);
			switch (hotel.medio_de_pago){
				case 'D': printf("%-10s", "Debito");   break;
				case 'E': printf("%-10s", "Efectivo"); break;
			}
			printf(" %12.2f %12.2f %12.2f", hotel.monto, descuento, hotel.monto - descuento);
			cantidad++;
		}
	}

	fclose(f);

	if (cantidad == 0){
		printf("\n(ninguna reserva fue pagada con debito o efectivo)\n");
	} else {
		printf("\n\nCantidad de reservas con descuento: %d\n", cantidad);
	}
}

//PUNTO 4: busqueda secuencial de una habitacion en el archivo.
//Le pregunta al usuario que habitacion buscar y dice si esta ocupada o libre.
void buscarHabitacion(T_RESERVA hotel){
	FILE *f;
	int tarjetaAux;
	int buscada;                 //habitacion que ingresa el usuario
	bool encontrada = false;     //bandera de la busqueda

	f = fopen(ARCHIVO, "r");
	if (f == NULL){
		printf("\nTodavia no hay reservas cargadas: todas las habitaciones estan libres.\n");
		return;
	}

	printf("\nIngrese el numero de habitacion a buscar: ");
	buscada = leer_entero();     //si escriben letras lo vuelve a pedir

	while (!encontrada && fscanf(f, FORMATO_LECTURA, hotel.cliente, &tarjetaAux,
			&hotel.habitacion, &hotel.medio_de_pago, &hotel.monto) == CAMPOS){

		hotel.tarjeta = (tarjetaAux != 0);

		if (hotel.habitacion == buscada){
			encontrada = true;
		}
	}

	fclose(f);

	if (encontrada){
		printf("\nLa habitacion %d esta OCUPADA:", buscada);
		mostrar_encabezado();
		mostrar_reserva(hotel);
		printf("\n");
	} else {
		printf("\nLa habitacion %d esta LIBRE (no figura en el archivo).\n", buscada);
	}
}
