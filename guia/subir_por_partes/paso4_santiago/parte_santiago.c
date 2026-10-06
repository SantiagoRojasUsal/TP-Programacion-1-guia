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
