/*
 ============================================================================
 Name        : TP_2.c
 Author      : Gonzalo Zafferano
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "Inputs.h"
#include "ComprobarErrores.h"
#include "ArrayEmployees.h"
#include "Menus.h"

#define CERRAR_APLICACION 5
#define VOLVER_ATRAS 2
#define TAM_LISTA_EMPLEADOS 1000
#define NO_SE_CARGARON_TODOS_LOS_CAMPOS -14

int main(void)
{
	setbuf(stdout, NULL);
	Employee listaEmpleados[TAM_LISTA_EMPLEADOS];
	int opcionElegida;
	int estadoOperacion;
	int opcionMinimo;
	int opcionMaximo;
	int banderaMenuSecundarioTitulo = 0;
	int banderaMenuSecundarioOpcion = 0;
	int banderaModificarBajaInformar = 0;

	estadoOperacion = initEmployees(listaEmpleados, TAM_LISTA_EMPLEADOS);
	if(utn_comprobarEstadoDeOperacion(estadoOperacion))
	{
		do
		{
			imprimirMenuPrincipal();

			opcionMinimo = 1;
			opcionMaximo = 5;
			estadoOperacion = ingreseUnaOpcion(&opcionElegida, opcionMinimo,opcionMaximo);

			if(utn_comprobarEstadoDeOperacion(estadoOperacion))
			{
				switch(opcionElegida)
				{
					case 1:
						banderaMenuSecundarioTitulo = 0;
						banderaMenuSecundarioOpcion = 0;
						imprimirMenuSecundario(banderaMenuSecundarioTitulo, banderaMenuSecundarioOpcion);
						estadoOperacion = tomarDatosEmpleados(listaEmpleados, TAM_LISTA_EMPLEADOS);
						utn_comprobarEstadoDeOperacion(estadoOperacion);

						if(estadoOperacion == 0)
						{
							printf("\n\t\t<-Empleado cargado exitosamente!->\n");
							banderaModificarBajaInformar = 1;
						}
						else
						{
							//El error -14 indica que no se cargaron correctamente los datos, por
							//lo que puede continuar reintentando y operando el menu.
							//Otro tipo de error, como memoria NULL, len invalido o ID fuera de limite,
							//no permitiran operar los distintos menu, por lo que no tiene sentido continuar.
							if(estadoOperacion != NO_SE_CARGARON_TODOS_LOS_CAMPOS)
							{
								opcionElegida = CERRAR_APLICACION;
							}
						}
						break;
					case 2:
						if(esPosibleOperar(banderaModificarBajaInformar))
						{
							estadoOperacion = operarMenuModificacion(listaEmpleados, TAM_LISTA_EMPLEADOS);
							utn_comprobarEstadoDeOperacion(estadoOperacion);
						}
						break;
					case 3:
						if(esPosibleOperar(banderaModificarBajaInformar))
						{
							do
							{
								opcionElegida = VOLVER_ATRAS;
								estadoOperacion = operarMenuBajas(listaEmpleados, TAM_LISTA_EMPLEADOS);
								utn_comprobarEstadoDeOperacion(estadoOperacion);

								if(estadoOperacion == 0) //Si es 0, se realizo una eliminacion exitosa.
								{
									//Despues de haber eliminado al empleado, verifico que aun existan empleados en la lista.
									estadoOperacion = verificarSiHayEmpleados(listaEmpleados, TAM_LISTA_EMPLEADOS);
									if(utn_comprobarEstadoDeOperacion(estadoOperacion))
									{
										if(estadoOperacion == 0) //Si es 0, ya no quedan empleados
										{
											printf("\n\t\t<-No hay mas empleados en el sistema!->\n");
											banderaModificarBajaInformar = 0;
										}
										else
										{
											banderaMenuSecundarioTitulo = 2;
											banderaMenuSecundarioOpcion = 5;
											imprimirMenuSecundario(banderaMenuSecundarioTitulo, banderaMenuSecundarioOpcion);
											opcionMinimo = 1;
											opcionMaximo = 2;
											estadoOperacion = ingreseUnaOpcion(&opcionElegida, opcionMinimo, opcionMaximo);
										}
									}
								}
							}while(opcionElegida != VOLVER_ATRAS);
						}
						break;
					case 4:
						if(esPosibleOperar(banderaModificarBajaInformar))
						{
							banderaMenuSecundarioTitulo = 3;
							banderaMenuSecundarioOpcion = 6;
							imprimirMenuSecundario(banderaMenuSecundarioTitulo, banderaMenuSecundarioOpcion);

							opcionMinimo = 0;
							opcionMaximo = 2;
							estadoOperacion = ingreseUnaOpcion(&opcionElegida, opcionMinimo, opcionMaximo);

							if(utn_comprobarEstadoDeOperacion(estadoOperacion) && opcionElegida < VOLVER_ATRAS)
							{
								estadoOperacion = sortEmployees(listaEmpleados, TAM_LISTA_EMPLEADOS, opcionElegida);
								if(utn_comprobarEstadoDeOperacion(estadoOperacion))
								{
									estadoOperacion = printEmployees(listaEmpleados, TAM_LISTA_EMPLEADOS);
									if(utn_comprobarEstadoDeOperacion(estadoOperacion))
									{
										estadoOperacion = imprimirDatosDeSalario(listaEmpleados, TAM_LISTA_EMPLEADOS);
										utn_comprobarEstadoDeOperacion(estadoOperacion);
									}
								}
							}
						}
						break;
				}
			}
			else
			{
				opcionElegida = CERRAR_APLICACION;
			}

		}while(opcionElegida != CERRAR_APLICACION);
	}

	printf("\n\t\t<--Fin del programa-->");

	return EXIT_SUCCESS;
}
