/*
 * Menus.c
 *
 *  Created on: 5 oct 2021
 *      Author: GONZALO
 */

#include "Menus.h"

#define TRUE 1
#define FALSE 0
#define MENU_BAJAS_VOLVER 2
#define MENU_MODIFICACION_ATRAS 5
#define OPERACION_EXITOSA 0
#define PUNTERO_NULL -1
#define LEN_INVALIDO -2
#define PRESIONO_ATRAS 1
#define NO_SE_APLICARON_BAJAS -19
#define NO_SE_ENCONTRARON_DATOS_ASOCIADOS_AL_ID_INDICADO -20
#define TAM_LISTA_EMPLEADOS 1000

/*
* \brief Imprime el menu principal.
* \param int banderaMenu - Bandera que indica el titulo que debe imprimir el menu.
* \return Retorna VOID.
*/
void imprimirMenuPrincipal(void)
{
	char* pMensaje;
	static int banderaMenu = 0;

	if(banderaMenu)
	{
		pMensaje = "\n\t\t<--Volviendo al Menu Principal-->\n\n";
	}
	else
	{
		pMensaje = "\n\t<--Bienvenido al sistema de carga de datos de Empleados-->\n\n"
				"\t\t<--Menu Principal-->";
		banderaMenu = 1;
	}

	printf("%s", pMensaje);

	printf("\n1 >>Alta de personal\n2 >>Modificar\n3 >>Baja de personal\n4 >>Informar\n5 <<Salir");
}

/*
* \brief Imprime un menu secundario, segun la opcion recibida por parametro.
* \param int opcion - opcion que indica que fragmento del menu imprimir
* \return retorna VOID.
*/
void imprimirMenuSecundario(int opcionUno, int opcionDos)
{
	char* pMensaje;
	char* pMensajeDos;

	switch(opcionUno)
	{
		case 0:
			pMensaje ="\n\n\t\t<--Menu de Alta de datos-->";
			break;
		case 1:
			pMensaje ="\n\n\t\t<--Menu de modificacion de datos-->";
			break;
		case 2:
			pMensaje ="\n\n\t\t<--Menu de Baja de Ids-->";
			break;
		case 3:
			pMensaje ="\n\n\t\t<--Menu para muestra de informacion-->";
			break;
	}

	switch(opcionDos)
	{
		case 0:
			pMensajeDos="\n\n>>A continuacion, complete los campos con los datos solicitados\n";
			break;
		case 1:
			//Los Id arrancan en 1, por lo que se puede usar el '0' para volver atras.
			pMensajeDos ="\n\n>>A continuacion, ingrese el Id del empleado que desee modificar\n<<o pulse '0' para volver atras";
			break;
		case 2:
			pMensajeDos ="\n\n>>A continuacion indique el campo que desea modificar\n\t1 >>Nombre\n\t2 >>Apellido\n\t3 >>Salario \n\t4 >>Sector \n\t5 <<Atras";
			break;
		case 3:
			pMensajeDos ="\n>>A continuacion ingrese el Id que desee dar de baja\n<<o pulse '0' para volver atras";
			break;
		case 4:
			pMensajeDos ="\nSeguro desea eliminar la informacion asociada a ese Id? \n\t1 >>Si\n\t2 <<Volver\n";
			break;
		case 5:
			pMensajeDos = "\nDesea continuar dando de baja otros Id?\n\t1 >>Si\n\t2 <<Atras";
			break;
		case 6:
			pMensajeDos = "\nPor favor, indique como desea mostrar el listado\n\t0 >>De forma Descendete (Z-A)\n\t1 >>De forma Ascendente(A-Z)\n\t2 <<Atras";
			break;
		case 7:
			pMensajeDos = "\nDesea continuar modificando al empleado seleccionado?\n\t1 >>Si\n\t2 <<Atras";
			break;
	}
	printf("%s %s", pMensaje, pMensajeDos);
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
		printf("\n\t\t<--Un momento! no hay empleados cargados para operar\n\t\tIngrese un empleado con la opcion 1.-->\n");
		retorno = FALSE;
	}
	return retorno;
}

/*
* \brief Opera el menu de modificaciones (opcion 2)
* \param Employee listaEmpleados - Lista de empleados
* \param int len - largo del array
* \return retorna INT. 0 si esta todo OK.
* 		  retorna  1 si se decide volver <<atras, cancelando la modificacion.
*         retorna -1 si la direccion de memoria del array es NULL.
*         retorna -2 si el len es invalido.
*/
int operarMenuModificacion(Employee listaEmpleados[], int len)
{
	int opcionElegida;
	int banderaMenuOpciones;
	int estadoOperacion;
	int idIngresado;
	int indiceDelId;
	int retorno = PUNTERO_NULL;
	int banderaMenuTitulo = 1;

	if(listaEmpleados != NULL)
	{
		retorno = LEN_INVALIDO;
		if(len >0 && len <= TAM_LISTA_EMPLEADOS)
		{
			retorno = PRESIONO_ATRAS;
			do
			{
				banderaMenuOpciones = 1;
				opcionElegida = 0;
				imprimirMenuSecundario(banderaMenuTitulo, banderaMenuOpciones);
				imprimirIdsDisponibles(listaEmpleados, len);
				//Puede ingresar un numero entre 0 (atras) hasta 9999 (ids)
				estadoOperacion = tomarID();
				if(utn_comprobarEstadoDeOperacion(estadoOperacion))
				{
					opcionElegida = estadoOperacion;
					if(opcionElegida > 0)
					{
						idIngresado = opcionElegida;
						//Rescato el ID dentro de "opcionElegida",
						//porque la variable "opcionElegida" se continuara reutilizando y perdera el ID
						estadoOperacion = findEmployeeById(listaEmpleados, len, idIngresado);
						if(utn_comprobarEstadoDeOperacion(estadoOperacion))
						{
							indiceDelId = estadoOperacion;
							//Rescato el Indice del Id, porque "estadoOperacion" se continuara reutilizando,
							//y perdera el indice, y el indice lo necesito mantener para otras operaciones.
							do
							{
								banderaMenuOpciones = 2;
								printOneEmployee(listaEmpleados[indiceDelId]);
								imprimirMenuSecundario(banderaMenuTitulo, banderaMenuOpciones);
								estadoOperacion = ingreseUnaOpcion(&opcionElegida, 1,5);
								if(utn_comprobarEstadoDeOperacion(estadoOperacion) && opcionElegida != MENU_MODIFICACION_ATRAS)
								{
									estadoOperacion = modificarEmpleado(&listaEmpleados[indiceDelId], opcionElegida);

									if(utn_comprobarEstadoDeOperacion(estadoOperacion))
									{
										estadoOperacion = printOneEmployee(listaEmpleados[indiceDelId]);
										if(utn_comprobarEstadoDeOperacion(estadoOperacion))
										{
											printf("\n\n\t\t<-Modificacion exitosa!->\n");
											banderaMenuOpciones = 1;
											retorno = OPERACION_EXITOSA;
										}
									}
								}
								if(estadoOperacion == 0 && opcionElegida != MENU_MODIFICACION_ATRAS)
								{
									banderaMenuOpciones = 7;
									imprimirMenuSecundario(banderaMenuTitulo, banderaMenuOpciones);
									estadoOperacion = ingreseUnaOpcion(&opcionElegida, 1,2);
									utn_comprobarEstadoDeOperacion(estadoOperacion);
								}
								if(estadoOperacion<0)
								{
									opcionElegida = 2;
								}
							}while(opcionElegida == 1);
						}
					}
				}
			}while(opcionElegida > 0);
		}
	}
	return retorno;
}

/*
* \brief Opera el menu de bajas (opcion 3)
* \param Employee listaEmpleados - Lista de empleados
* \param int len - largo del array
* \return retorna INT. 0 si se completo la baja de forma correcta.
* 		  retorna  1 si se decidio volver <<atras, cancelando la baja.
*         retorna -1 si la direccion de memoria del array es NULL.
*         retorna -2 si el len es invalido.
*         retorna-19 si no se aplicaron bajas en el sistema
*/
int operarMenuBajas(Employee listaEmpleados[], int len)
{
	int estadoOperacion;
	int idIngresado;
	int indiceId;
	int banderaTituloMenu;
	int banderaOpcionesMenu;
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
				banderaTituloMenu = 2;
				banderaOpcionesMenu = 3;
				imprimirMenuSecundario(banderaTituloMenu, banderaOpcionesMenu);
				imprimirIdsDisponibles(listaEmpleados, len);

				estadoOperacion = tomarID();
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
						banderaTituloMenu = 2;
						banderaOpcionesMenu = 4;
						imprimirMenuSecundario(banderaTituloMenu, banderaOpcionesMenu);
						estadoOperacion = ingreseUnaOpcion(&opcionElegida, 1,2);

						if(utn_comprobarEstadoDeOperacion(estadoOperacion) && opcionElegida == 1)
						{
							estadoOperacion = removeEmployee(listaEmpleados, TAM_LISTA_EMPLEADOS, idIngresado);
							if(utn_comprobarEstadoDeOperacion(estadoOperacion))
							{
								printf("\n\t\t<-ID eliminado exitosamente!->\n");
								retorno = OPERACION_EXITOSA;
							}
						}
					}
				}
			}while(opcionElegida == MENU_BAJAS_VOLVER || estadoOperacion == NO_SE_ENCONTRARON_DATOS_ASOCIADOS_AL_ID_INDICADO);
		}
	}
	return retorno;
}
