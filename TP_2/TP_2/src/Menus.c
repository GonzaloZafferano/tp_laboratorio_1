/*
 * Menus.c
 *
 *  Created on: 5 oct 2021
 *      Author: GONZALO
 */

#include "Menus.h"

#define TRUE 1
#define FALSE 0
#define MENU_ALTAS 0
#define MENU_ALTAS_COMPLETAR_CAMPOS 0
#define SE_PUEDE_OPERAR_BAJA_MOD_MUESTRA 1
#define MENU_ALTAS_DAR_UNA_ALTA 1
#define MENU_ALTAS_MINIMO 1
#define MENU_ALTAS_MAXIMO 2
#define MENU_ALTAS_ATRAS 2
#define MENU_ALTAS_DESEA_OTRA_ALTA_MAS 9
#define MENU_ALTAS_DESEA_DAR_ALTA 10
#define MENU_MODIFICACION_SALIR 0
#define MENU_MODIFICACION 1
#define	MENU_MODIFICACION_INGRESE_ID_EMPLEADO 1
#define MENU_MODIFICACION_CONTINUAR 1
#define MENU_MODIFICACION_CAMPOS_A_MODIFICAR 2
#define MENU_MODIFICACION_CONTINUAR_ATRAS 2
#define MENU_MODIFICACION_CAMPOS_ATRAS 5
#define MENU_MODIFICACION_CONTINUAR_MODIFICANDO_AL_EMPLEADO 7
#define MENU_CAMPOS_MINIMO 1
#define MENU_CAMPOS_MAXIMO 5
#define MENU_BAJAS 2
#define MENU_BAJAS_INGRESE_ID 3
#define MENU_BAJAS_ELIMINAR 1
#define MENU_BAJAS_SEGURO_DESEA_ELIMINAR 4
#define MENU_BAJAS_NO_ELIMINAR_Y_VOLVER 2
#define MENU_MOSTRAR_ATRAS 3
#define MENU_MOSTRAR_SALARIOS 2
#define MENU_INFORMACION 3
#define MENU_INFORMACION_MINIMO 0
#define MENU_INFORMACION_MAXIMO 3
#define MENU_INFORMACION_COMO_DESEA_VER_LISTADO 6
#define PRESIONO_ATRAS 1
#define OPERACION_EXITOSA 0
#define PUNTERO_NULL -1
#define LEN_INVALIDO -2
#define NO_HAY_EMPLEADOS_CARGADOS_CON_ESE_ID -12
#define NO_SE_PUDIERON_TOMAR_DATOS_CORRECTAMENTE -14
#define NO_SE_APLICARON_BAJAS -19
#define NO_SE_PUDO_TOMAR_UN_DATO_VALIDO -22
#define TAM_LISTA_EMPLEADOS 1000

/*
* \brief Imprime el menu principal.
* \param int banderaMenu - Bandera que indica el titulo que debe imprimir el menu.
* \return Retorna VOID.
*/
void imprimirMenuPrincipal(void)
{
	static int banderaMenu = 0;

	if(banderaMenu)
	{
		printf("\n\t\t<--Volviendo al Menu Principal-->\n\n");
	}
	else
	{
		printf("\n\t<--Bienvenido al sistema de carga de datos de Empleados-->\n\n");
		banderaMenu = 1;
	}

	printf("\t\t<--Menu Principal-->\n1 >>Alta de personal\n2 >>Modificar\n3 >>Baja de personal\n4 >>Informar\n5 <<Salir");
}

/*
* \brief Imprime un menu secundario, segun la opcion recibida por parametro.
* \param int opcion - entero que indica el titulo del menu a imprimir
* \param int opcionDos - entero que indica el listado de opciones a imprimir
* \return retorna VOID.
*/
void imprimirMenuSecundario(int opcionUno, int opcionDos)
{
	switch(opcionUno)
	{
		case 0:
			printf("\n\n\t\t<--Menu de Alta de datos-->");
			break;
		case 1:
			printf("\n\n\t\t<--Menu de modificacion de datos-->");
			break;
		case 2:
			printf("\n\n\t\t<--Menu de Baja de Ids-->");
			break;
		case 3:
			printf("\n\n\t\t<--Menu para muestra de informacion-->");
			break;
		case 4:
			printf("\n\n\t\t<--Menu salida de programa-->");
			break;
	}

	switch(opcionDos)
	{
		case 0:
			printf("\n>>A continuacion, complete los campos con los datos solicitados\n");
			break;
		case 1:
			printf("\n>>A continuacion, ingrese el Id del empleado que desee modificar\n<<o pulse '0' para volver atras");
			break;
		case 2:
			printf("\n>>A continuacion indique el campo que desea modificar\n\t1 >>Nombre\n\t2 >>Apellido\n\t3 >>Salario \n\t4 >>Sector \n\t5 <<Atras");
			break;
		case 3:
			printf("\n>>A continuacion ingrese el Id que desee dar de baja\n<<o pulse '0' para volver atras");
			break;
		case 4:
			printf("\nSeguro desea eliminar la informacion asociada a ese Id? \n\t1 >>Si\n\t2 <<Volver\n");
			break;
		case 5:
			printf("\nDesea continuar dando de baja otros Id?\n\t1 >>Si\n\t2 <<Atras");
			break;
		case 6:
			printf("\n>>A continuacion seleccione la informacion que desea mostrar"
							"\n\t0 >>Listado de empleados, ordenado de forma Descendete (Z-A)"
							"\n\t1 >>Listado de empleados, ordenado de forma Ascendente(A-Z)"
							"\n\t2 >>Informacion relacionada con los salarios\n\t3 <<Atras");
			break;
		case 7:
			printf("\nDesea continuar modificando al empleado seleccionado?\n\t1 >>Si\n\t2 <<Atras");
			break;
		case 8:
			printf("\nDesea salir del programa?\n\t1 >>Si\n\t2 <<Atras");
			break;
		case 9:
			printf("\nDesea continuar con otra alta?\n\t1 >>Si\n\t2 <<Atras");
			break;
		case 10:
			printf("\nDesea dar una alta?\n\t1 >>Si\n\t2 <<Atras");
			break;
	}
}

/*
* \brief Evalua si es posible realizar una operacion. Si es posible, no realiza acciones.
*        Si no es posible, informa el motivo.
* \param int bandera - Valor que identifica la posibilidad de realizar una operacion.
* \return retorna un INT. 1 si es posible realizar la operacion en base a la bandera recibida.
* 		  retorna 0 si la operacion no puede ser realizada.
*/
int esPosibleOperar(int bandera)
{
	int retorno = TRUE;

	if(bandera == 0)
	{
		printf("\n\t\t<--Un momento! No hay empleados cargados para operar.\n\t\tIngrese un empleado con la opcion 1.-->\n");
		retorno = FALSE;
	}
	return retorno;
}

/*
* \brief Opera el menu de Altas de empleados (opcion 1)
* \param Employee listaEmpleados - Lista de empleados
* \param int len - largo del array
* \param int* idMaximo - Id maximo hasta el momento
* \param int* banderaAltas - puntero a bandera de altas, para retornar que se cargo un empleado
* \return retorna INT. 0 si esta todo OK.
* 		  retorna  1 si presiona <<atras, cancelando el alta.
*         retorna -1 si la direccion de memoria del array es NULL.
*         retorna -2 si el len es invalido.
*         retorna -14 si No se pudieron tomar los datos correctamente
*/
int operarMenuAltas(Employee listaEmpleados[], int len, int* idMaximo, int* banderaAltas)
{
	int estadoOperacion;
	int opcionElegidaPrimerSubMenu;
	int opcionElegidaSegundoSubMenu;
	int retorno = PUNTERO_NULL;

	if(listaEmpleados != NULL && idMaximo != NULL && banderaAltas != NULL)
	{
		retorno = LEN_INVALIDO;
		if(len >0 && len <= TAM_LISTA_EMPLEADOS)
		{
			retorno = PRESIONO_ATRAS;
			do
			{
				opcionElegidaPrimerSubMenu = MENU_ALTAS_ATRAS;
			    imprimirMenuSecundario(MENU_ALTAS, MENU_ALTAS_DESEA_DAR_ALTA);
				estadoOperacion=ingreseUnaOpcion(&opcionElegidaPrimerSubMenu, MENU_ALTAS_MINIMO, MENU_ALTAS_MAXIMO);

				if(opcionElegidaPrimerSubMenu == MENU_ALTAS_DAR_UNA_ALTA)
				{
					do
					{
						retorno = NO_SE_PUDIERON_TOMAR_DATOS_CORRECTAMENTE;
						opcionElegidaSegundoSubMenu = MENU_ALTAS_ATRAS;
						imprimirMenuSecundario(MENU_ALTAS, MENU_ALTAS_COMPLETAR_CAMPOS);
						estadoOperacion = tomarDatosEmpleados(listaEmpleados, TAM_LISTA_EMPLEADOS, idMaximo);
						if(utn_comprobarEstadoDeOperacion(estadoOperacion))
						{
							printf("\n\t\t<-Empleado cargado exitosamente!->\n");
							retorno = OPERACION_EXITOSA;
							*banderaAltas = SE_PUEDE_OPERAR_BAJA_MOD_MUESTRA;

							imprimirMenuSecundario(MENU_ALTAS, MENU_ALTAS_DESEA_OTRA_ALTA_MAS);
							estadoOperacion = ingreseUnaOpcion(&opcionElegidaSegundoSubMenu, MENU_ALTAS_MINIMO,MENU_ALTAS_MAXIMO);
							utn_comprobarEstadoDeOperacion(estadoOperacion);
						}
					}while(opcionElegidaSegundoSubMenu == MENU_ALTAS_DAR_UNA_ALTA);

					if(opcionElegidaSegundoSubMenu == MENU_ALTAS_ATRAS && estadoOperacion == OPERACION_EXITOSA)
					{
						break;
					}
				}
			}while(opcionElegidaPrimerSubMenu == MENU_ALTAS_DAR_UNA_ALTA && estadoOperacion != NO_SE_PUDO_TOMAR_UN_DATO_VALIDO);
		}
	}
	return retorno;
}

/*
* \brief Opera el menu de modificaciones (opcion 2)
* \param Employee listaEmpleados - Lista de empleados
* \param int len - largo del array
* \param int idMaximo - id mas alto generado hasta el momento
* \return retorna INT. 0 si esta todo OK.
* 		  retorna  1 si se decide volver <<atras, cancelando la modificacion.
*         retorna -1 si la direccion de memoria del array es NULL.
*         retorna -2 si el len es invalido.
*/
int operarMenuModificacion(Employee listaEmpleados[], int len, int idMaximo)
{
	int opcionElegida;
	int estadoOperacion;
	int idIngresado;
	int indiceDelId;
	int retorno = PUNTERO_NULL;

	if(listaEmpleados != NULL)
	{
		retorno = LEN_INVALIDO;
		if(len > 0 && len <= TAM_LISTA_EMPLEADOS)
		{
			retorno = PRESIONO_ATRAS;
			do
			{
				opcionElegida = MENU_MODIFICACION_SALIR;
				imprimirMenuSecundario(MENU_MODIFICACION, MENU_MODIFICACION_INGRESE_ID_EMPLEADO);
				imprimirIdsDisponibles(listaEmpleados, len);

				estadoOperacion = tomarID(idMaximo);
				if(utn_comprobarEstadoDeOperacion(estadoOperacion))
				{
					opcionElegida = estadoOperacion;
					if(opcionElegida > MENU_MODIFICACION_SALIR)
					{
						idIngresado = opcionElegida;

						estadoOperacion = findEmployeeById(listaEmpleados, len, idIngresado);
						if(utn_comprobarEstadoDeOperacion(estadoOperacion))
						{
							indiceDelId = estadoOperacion;

							do
							{
								printOneEmployee(listaEmpleados[indiceDelId]);
								imprimirMenuSecundario(MENU_MODIFICACION, MENU_MODIFICACION_CAMPOS_A_MODIFICAR);
								estadoOperacion = ingreseUnaOpcion(&opcionElegida, MENU_CAMPOS_MINIMO,MENU_CAMPOS_MAXIMO);
								if(utn_comprobarEstadoDeOperacion(estadoOperacion) && opcionElegida != MENU_MODIFICACION_CAMPOS_ATRAS)
								{
									estadoOperacion = modificarEmpleado(&listaEmpleados[indiceDelId], opcionElegida);

									if(utn_comprobarEstadoDeOperacion(estadoOperacion))
									{
										estadoOperacion = printOneEmployee(listaEmpleados[indiceDelId]);
										if(utn_comprobarEstadoDeOperacion(estadoOperacion))
										{
											printf("\n\n\t\t<-Modificacion exitosa!->\n");
											retorno = OPERACION_EXITOSA;
										}
									}
								}
								if(estadoOperacion == 0 && opcionElegida != MENU_MODIFICACION_CAMPOS_ATRAS)
								{
									opcionElegida = MENU_MODIFICACION_CONTINUAR_ATRAS;//Lo seteo en 2 (volver atras), en caso de que no ingrese nunca una opcion valida
									imprimirMenuSecundario(MENU_MODIFICACION, MENU_MODIFICACION_CONTINUAR_MODIFICANDO_AL_EMPLEADO);
									estadoOperacion = ingreseUnaOpcion(&opcionElegida, MENU_MODIFICACION_CONTINUAR,MENU_MODIFICACION_CONTINUAR_ATRAS);
									utn_comprobarEstadoDeOperacion(estadoOperacion);
								}
								else
								{
									if(estadoOperacion < 0)
									{
										opcionElegida = MENU_MODIFICACION_CONTINUAR_ATRAS;
									}
								}
							}while(opcionElegida == MENU_MODIFICACION_CONTINUAR);
						}
					}
				}
			}while(opcionElegida > MENU_MODIFICACION_SALIR);
		}
	}
	return retorno;
}

/*
* \brief Opera el menu de bajas (opcion 3)
* \param Employee listaEmpleados - Lista de empleados
* \param int len - largo del array
* \param int idMaximo - id mas alto generado hasta el momento
* \return retorna INT. 0 si se completo la baja de forma correcta.
* 		  retorna  1 si se decidio volver <<atras, cancelando la baja.
*         retorna -1 si la direccion de memoria del array es NULL.
*         retorna -2 si el len es invalido.
*         retorna-19 si no se aplicaron bajas en el sistema
*/
int operarMenuBajas(Employee listaEmpleados[], int len, int idMaximo)
{
	int estadoOperacion;
	int idIngresado;
	int indiceId;
	int opcionElegida;
	int retorno = PUNTERO_NULL;

	if(listaEmpleados != NULL)
	{
		retorno = LEN_INVALIDO;
		if(len > 0 && len <= TAM_LISTA_EMPLEADOS)
		{
			do
			{
				retorno = PRESIONO_ATRAS;//Retorna 1 si decide volver <<atras
				imprimirMenuSecundario(MENU_BAJAS, MENU_BAJAS_INGRESE_ID);
				imprimirIdsDisponibles(listaEmpleados, len);

				estadoOperacion = tomarID(idMaximo);
				opcionElegida = estadoOperacion;
				if(utn_comprobarEstadoDeOperacion(estadoOperacion) && estadoOperacion != 0)
				{
					retorno = NO_SE_APLICARON_BAJAS;
					idIngresado = estadoOperacion;
					estadoOperacion = findEmployeeById(listaEmpleados, len, idIngresado);
					if(utn_comprobarEstadoDeOperacion(estadoOperacion))
					{
						indiceId = estadoOperacion;

						printOneEmployee(listaEmpleados[indiceId]);
						imprimirMenuSecundario(MENU_BAJAS, MENU_BAJAS_SEGURO_DESEA_ELIMINAR);
						estadoOperacion = ingreseUnaOpcion(&opcionElegida, MENU_BAJAS_ELIMINAR,MENU_BAJAS_NO_ELIMINAR_Y_VOLVER);

						if(utn_comprobarEstadoDeOperacion(estadoOperacion) && opcionElegida == MENU_BAJAS_ELIMINAR)
						{
							estadoOperacion = removeEmployee(listaEmpleados, TAM_LISTA_EMPLEADOS, idIngresado);
							if(utn_comprobarEstadoDeOperacion(estadoOperacion))
							{
								printf("\n\t\t<-ID eliminado exitosamente!->\n");
								retorno = OPERACION_EXITOSA;
							}
						}
						else
						{
							if(opcionElegida == MENU_BAJAS_NO_ELIMINAR_Y_VOLVER)
							{
								printf("\n\t\t<-No se realizo la baja->");
							}
						}
					}
				}
			}while(opcionElegida == MENU_BAJAS_NO_ELIMINAR_Y_VOLVER || estadoOperacion == NO_HAY_EMPLEADOS_CARGADOS_CON_ESE_ID || estadoOperacion == NO_SE_PUDO_TOMAR_UN_DATO_VALIDO);
		}
	}
	return retorno;
}

/*
* \brief Opera el menu de muestra de informacion (opcion 4)
* \param Employee listaEmpleados - Lista de empleados
* \param int len - largo del array
* \return retorna INT. 0 si esta todo OK.
* 		  retorna  1 si se decide volver <<atras.
*         retorna -1 si la direccion de memoria del array es NULL.
*         retorna -2 si el len es invalido.
*/
int operarMenuMostrarInformacion(Employee listaEmpleados[], int len)
{
	int estadoOperacion;
	int opcionElegida;
	int retorno = PUNTERO_NULL;
	if(listaEmpleados != NULL)
	{
		retorno = LEN_INVALIDO;
		if(len > 0 && len <= TAM_LISTA_EMPLEADOS)
		{
			retorno = PRESIONO_ATRAS;
			do
			{
				imprimirMenuSecundario(MENU_INFORMACION, MENU_INFORMACION_COMO_DESEA_VER_LISTADO);

				estadoOperacion = ingreseUnaOpcion(&opcionElegida, MENU_INFORMACION_MINIMO, MENU_INFORMACION_MAXIMO);

				if(utn_comprobarEstadoDeOperacion(estadoOperacion) && opcionElegida != MENU_MOSTRAR_ATRAS)
				{
					retorno = OPERACION_EXITOSA;
					if(opcionElegida != MENU_MOSTRAR_SALARIOS)
					{
						estadoOperacion = sortEmployees(listaEmpleados, len, opcionElegida);
						if(utn_comprobarEstadoDeOperacion(estadoOperacion))
						{
							estadoOperacion = printEmployees(listaEmpleados, len);
							utn_comprobarEstadoDeOperacion(estadoOperacion);
						}
					}
					else
					{
						estadoOperacion = imprimirDatosDeSalario(listaEmpleados, len);
						utn_comprobarEstadoDeOperacion(estadoOperacion);
					}
				}
			}while(opcionElegida != MENU_MOSTRAR_ATRAS && estadoOperacion == OPERACION_EXITOSA);
		}
	}
	return retorno;
}
