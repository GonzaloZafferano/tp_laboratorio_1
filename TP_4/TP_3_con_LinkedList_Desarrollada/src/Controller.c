#include "Controller.h"

#define VOLVER_ATRAS 1
#define ARCHIVO_VACIO_O_TERMINADO 1
#define MAXIMO_MENU_MOD 4
#define LEN_NOMBRE 128
#define SI 1
#define NO 2
#define MAXIMO_MENU_ORDEN 5
#define MOSTRAR_TODOS_LOS_DATOS 2
#define OPERACION_EXITOSA 0
#define ERROR_PUNTERO_NULL -1
#define ERROR_LEN_INVALIDO -2
#define ERROR_SIN_MAS_REINTENTOS -21
#define ERROR_NO_SE_PUDIERON_TOMAR_TODOS_LOS_DATOS -23
#define ERROR_NO_SE_OBTUVO_RESPUESTA_VALIDA -25
#define ERROR_NO_HAY_ELEMENTOS_CARGADOS_EN_LA_LISTA -30
#define ERROR_NO_SE_ENCONTRARON_DATOS_ASOCIADOS_AL_ID -32
#define ERROR_NO_SE_DIO_ALTA -34
#define ERROR_NO_SE_PUDO_IMPRIMIR -37
#define ERROR_AL_ORDENAR -39
#define ERROR_NO_SE_CARGARON_CORRECTAMENTE_LOS_DATOS_EN_ARCHIVO -40
#define ERROR_NO_SE_PUDO_CARGAR_ELEMENTO_A_LA_LISTA -41
#define ERROR_EN_LA_CARGA_DE_ARCHIVO_A_LISTA -42
#define ERROR_EN_CARGA_DE_ARCHIVO -44
#define ERROR_ARCHIVO_TEXTO_NO_EXISTE -45
#define ERROR_ARCHIVO_BINARIO_NO_EXISTE -47
#define ARCHIVO_NO_EXISTE -48
#define SALIR_APLICACION 15
#define NINGUN_ARCHIVO_CARGADO 3
#define ARCHIVO_TEXTO_CARGADO 1
#define ARCHIVO_BINARIO_CARGADO 2
#define ERROR_NO_SE_PUEDE_ORDENAR_UN_SOLO_EMPLEADO -31
#define CRITERIO 1
#define ORDEN 2
#define DAR_BAJA 1
#define CONFIRMAR_BAJA 2
#define MODIFICAR 1
#define MODIFICAR_CAMPOS 2
#define SALIR 1
#define CONFIRMAR_SALIR 2
#define MOSTRAR_LISTA 1
#define GUARDAR_LISTA 2
#define OBTENER_NUEVO_ULTIMO_ID 2
#define LEN_ARCHIVO 50

static int cargarArchivo(char* path, LinkedList* pArrayList, int tipoArchivo, int* contadorCargas);
static int cargarListaEnArchivo(char* path , LinkedList* pArrayListEmployee, int* contadorCargas, int tipoArchivo);
static int agregarElementoDeListaDeArchivoAListaDeSistema(LinkedList* pArrayListaOriginal, LinkedList* pListaClon);
static int evaluarUnificacionDeListas(LinkedList* pArrayListaOriginal, LinkedList* pListaClon, int operacion);
static int guardarListaEnModoBinario(char* path , LinkedList* pArrayListEmployee);
static int guardarListaEnModoTexto(char* path, LinkedList* pArrayListEmployee);
static int imprimirListaDeEmpleados(LinkedList* pArrayListEmployee);

/** \brief Carga los datos de los empleados a la LinkedList
 * \param char* path - Ruta absoluta o relativa del archivo
 * \param LinkedList* pArrayListEmployee - puntero a la lista de empleados
 * \param int tipoArchivo - tipo de archivo que se desea trabajar, texto o binario
 * \param int* contadorCargas - puntero a variable que cuenta la cantidad de cargas realizadas desde el archivo
 * \return int - retorna 0 si opero correctamente o
 *               retorna -1 si el puntero es NULL o
 *               retorna -42 si ocurrio un error en la carga del archivo a la lista o
 *               retorna -48 si el archivo no exite
 */
static int cargarArchivo(char* path, LinkedList* pArrayList, int tipoArchivo, int* pContadorCargas)
{
	int estadoOperacion;
	FILE* fpArchivo;
	char encabezado[LEN_NOMBRE];
	int (*pFuncion)(FILE*, LinkedList*);
	int retorno = ERROR_PUNTERO_NULL;

	if(path != NULL && pArrayList != NULL && pContadorCargas != NULL)
	{
		retorno = ARCHIVO_NO_EXISTE;

		switch(tipoArchivo)
		{
			case ARCHIVO_TEXTO_CARGADO:
				fpArchivo = fopen(path, "r");
				pFuncion = parser_EmployeeFromText;
				break;
			case ARCHIVO_BINARIO_CARGADO:
				fpArchivo = fopen (path, "rb");
				pFuncion = parser_EmployeeFromBinary;
				break;
		}

		if(fpArchivo != NULL)
		{
			if(tipoArchivo == ARCHIVO_TEXTO_CARGADO)
			{
				fgets(encabezado, sizeof(encabezado), fpArchivo);
			}

			do
			{
				retorno = OPERACION_EXITOSA;
				estadoOperacion = pFuncion(fpArchivo, pArrayList);
				if(utn_comprobarEstadoDeOperacion(estadoOperacion) && !estadoOperacion)
				{
					*pContadorCargas = *pContadorCargas +1;
				}
				else
				{
					if(estadoOperacion != ARCHIVO_VACIO_O_TERMINADO)
					{
						retorno = ERROR_EN_LA_CARGA_DE_ARCHIVO_A_LISTA;
						break;
					}
				}
			}while(!feof(fpArchivo));
			fclose(fpArchivo);
		}
	}
	return retorno;
}

/** \brief Evalua si la lista obtenida del archivo puede guardarse en el sistema
 *         o (ante un error) debe consultar con el usuario
 * \param  LinkedList* pArrayListEmployee - puntero a la lista de empleados
 * \param  LinkedList* pListaArchivo - puntero a la lista con los datos descargados del archivo
 * \return int - retorna 0 si opero correctamente o
 * 				 retorna 1 si decide NO guardar la lista
 *               retorna -1 si el puntero es NULL o
 *               retorna -42 si no se obtuvo una respuesta valida del usuario
 */
static int evaluarUnificacionDeListas(LinkedList* pArrayListaOriginal, LinkedList* pListaArchivo, int operacion)
{
	int respuesta = NO;
	int retorno = ERROR_PUNTERO_NULL;
	int estadoOperacion;
	if(pArrayListaOriginal != NULL && pListaArchivo != NULL)
	{
		if(operacion == ERROR_EN_LA_CARGA_DE_ARCHIVO_A_LISTA)
		{
			retorno = VOLVER_ATRAS;
			estadoOperacion = menu_ImprimirMenuGuardarListaArchivo(MOSTRAR_LISTA, &respuesta);
			if(utn_comprobarEstadoDeOperacion(estadoOperacion) && respuesta == SI)
			{
				imprimirListaDeEmpleados(pListaArchivo);
			}

			estadoOperacion = menu_ImprimirMenuGuardarListaArchivo(GUARDAR_LISTA, &respuesta);
			if(!utn_comprobarEstadoDeOperacion(estadoOperacion))
			{
				printf("\n\t\t<--Se descartara la lista descargada del archivo!-->");
			}

			if(estadoOperacion < 0)
			{
				retorno = ERROR_NO_SE_OBTUVO_RESPUESTA_VALIDA;
			}
		}

		if(operacion == OPERACION_EXITOSA || (estadoOperacion == OPERACION_EXITOSA && respuesta == SI))
		{
			estadoOperacion = agregarElementoDeListaDeArchivoAListaDeSistema(pArrayListaOriginal, pListaArchivo);
			if(utn_comprobarEstadoDeOperacion(estadoOperacion))
			{
				printf("\n\t\t<--Carga completada exitosamente!-->\n");
				retorno = OPERACION_EXITOSA;
			}
		}
	}
	return retorno;
}

/** \brief Carga los elementos que estan en la lista del archivo a la lista del sistema
 * \param  LinkedList* pArrayListEmployee - puntero a la lista de empleados
 * \param  LinkedList* pListaArchivo - puntero a la lista con los datos descargados del archivo
 * \return int - retorna 0 si opero correctamente o
 *               retorna -1 si el puntero es NULL o
 *               retorna -41 si no se pudo cargar el elemento a la lista
 */
static int agregarElementoDeListaDeArchivoAListaDeSistema(LinkedList* pArrayListaOriginal, LinkedList* pListaArchivo)
{
	int i;
	int len;
	Employee* pEmpleado;
	int retorno = ERROR_PUNTERO_NULL;
	if(pArrayListaOriginal != NULL && pListaArchivo != NULL)
	{
		len = ll_len(pListaArchivo);
		if(len >=0)
		{
			for(i = 0; i < len; i++)
			{
				pEmpleado = ll_get(pListaArchivo, i);
				if(pEmpleado != NULL)
				{
					retorno = OPERACION_EXITOSA;
					ll_add(pArrayListaOriginal, pEmpleado);
				}
				else
				{
					retorno = ERROR_NO_SE_PUDO_CARGAR_ELEMENTO_A_LA_LISTA;
					break;
				}
			}
		}
	}
	return retorno;
}

/** \brief imprime la lista de empleados
 * \param LinkedList* pArrayListEmployee - puntero a la lista de empleados
 * \return int 0 si la operacion resulto exitosa
 * 	       retorna -1 si el puntero apunta a NULL
 * 	       retorna -2 si el len es invalido
 * 	       retorna -30 si no hay elementos en la lista
 * 	       retorna -37 si no se pudo imprimir
 */
static int imprimirListaDeEmpleados(LinkedList* pArrayListEmployee)
{
	int i;
	int len;
	int retorno = ERROR_PUNTERO_NULL;
	Employee* pEmpleado;
	if(pArrayListEmployee != NULL)
	{
		retorno = ERROR_NO_HAY_ELEMENTOS_CARGADOS_EN_LA_LISTA;
		if(!ll_isEmpty(pArrayListEmployee))
		{
			retorno = ERROR_LEN_INVALIDO;
			len = ll_len(pArrayListEmployee);
			if(len > 0)
			{
				printf("\n\t\t<--Lista de empleados-->");
				employee_ImprimirEncabezadoDeDatos(MOSTRAR_TODOS_LOS_DATOS);
				for(i = 0; i < len; i++)
				{
					retorno = ERROR_NO_SE_PUDO_IMPRIMIR;
					pEmpleado = ll_get(pArrayListEmployee, i);
					if(pEmpleado != NULL)
					{
						employee_ImprimirFilaDeDatos(pEmpleado, MOSTRAR_TODOS_LOS_DATOS);
						retorno = OPERACION_EXITOSA;
					}
				}
				if(retorno)
				{
					employee_ImprimirFilaVaciaDeDatos(MOSTRAR_TODOS_LOS_DATOS);
					printf("\n\t\t<--No hay empleados cargados en el sistema-->");
				}
			}
		}
	}
	return retorno;
}

/** \brief Guarda los datos de los empleados en la ruta y el tipo de archivo especificado.
 * \param char* path - Ruta absoluta o relativa del archivo
 * \param  LinkedList* pArrayListEmployee - puntero a la lista de empleados
 * \param int* contadorCargas - puntero a variable que cuenta la cantidad de cargas realizadas desde la lista al archivo
* \param int tipoArchivo - tipo de archivo que se desea trabajar, texto o binario
 * \return int - Retorna   0 si opero correctamente o
 *   			 retorna  -1 si el puntero es NULL
 *   			 retorna -40 si no se cargaron correctamente todos los datos en el archivo
 *   			 retorna -44 si hay un error en la carga del archivo
 */
static int cargarListaEnArchivo(char* path , LinkedList* pArrayListEmployee, int* contadorCargas, int tipoArchivo)
{
	int i;
	int len;
	FILE* fpArchivo;
	Employee* pEmpleado;
	int (*pFuncion)(FILE*, Employee*);
	int retorno = ERROR_PUNTERO_NULL;

	if(path != NULL && pArrayListEmployee != NULL && contadorCargas != NULL)
	{
		len = ll_len(pArrayListEmployee);
		retorno = OPERACION_EXITOSA;
		if(len >= 0)
		{
			switch(tipoArchivo)
			{
				case ARCHIVO_TEXTO_CARGADO:
					fpArchivo = fopen(path, "w");
					pFuncion = parser_TextFromEmployee;
					break;
				case ARCHIVO_BINARIO_CARGADO:
					fpArchivo = fopen(path, "wb");
					pFuncion = parser_BinaryFromEmployee;
					break;
			}

			if(fpArchivo != NULL)
			{
				if(tipoArchivo == ARCHIVO_TEXTO_CARGADO)
				{
					fprintf(fpArchivo, "Id,Nombre,Horas trabajadas,Salario\n");
				}

				for(i = 0; i < len ; i++)
				{
					retorno = ERROR_PUNTERO_NULL;
					pEmpleado = ll_get(pArrayListEmployee, i);
					if(pEmpleado != NULL)
					{
						retorno = ERROR_EN_CARGA_DE_ARCHIVO;
						if(!pFuncion(fpArchivo, pEmpleado))
						{
							*contadorCargas = *contadorCargas + 1;
							retorno = OPERACION_EXITOSA;
						}
					}

					if(!utn_comprobarEstadoDeOperacion(retorno))
					{
						retorno = ERROR_NO_SE_CARGARON_CORRECTAMENTE_LOS_DATOS_EN_ARCHIVO;
						break;
					}
				}
				fclose(fpArchivo);
			}
		}
	}
	return retorno;
}

/** \brief Guarda los datos de los empleados en el archivo .csv (modo texto).
 * \param char* path - Ruta absoluta o relativa del archivo
 * \param  LinkedList* pArrayListEmployee - puntero a la lista de empleados
 * \return int - Retorna 0 si opero correctamente o
 *   			 retorna -1 si el puntero es NULL
 *   			 retorna -40 si no se cargaron correctamente todos los datos en el archivo
 *   			 retorna -44 si hay un error en la carga del archivo
 */
static int guardarListaEnModoTexto(char* path, LinkedList* pArrayListEmployee)
{
	int estadoOperacion;
	int contador = 0;
	int len = ll_len(pArrayListEmployee);
	int retorno = ERROR_PUNTERO_NULL;

	if(path != NULL && pArrayListEmployee != NULL)
	{
		estadoOperacion =  cargarListaEnArchivo(path, pArrayListEmployee, &contador, ARCHIVO_TEXTO_CARGADO);
		retorno = estadoOperacion;

		if(contador > 0)
		{
			printf("\n\t\t<--Se cargaron en el archivo de Texto %d / %d empleados en lista-->\n", contador, len);
		}
		else
		{
			if(retorno == OPERACION_EXITOSA)
			{
				printf("\n\t<--Se completo el guardado de la lista en el archivo de Texto, pero la lista estaba vacia!-->\n");
			}
		}
	}
	return retorno;
}


/** \brief Guarda los datos de los empleados en el archivo .bin (modo binario).
 * \param char* path - Ruta absoluta o relativa del archivo
 * \param  LinkedList* pArrayListEmployee - puntero a la lista de empleados
 * \return int - Retorna 0 si opero correctamente o
 *   			 retorna -1 si el puntero es NULL
 *   			 retorna -40 si no se cargaron correctamente todos los datos en el archivo
 *   			 retorna -44 si hay un error en la carga del archivo
 */
static int guardarListaEnModoBinario(char* path, LinkedList* pArrayListEmployee)
{
	int estadoOperacion;
	int contador = 0;
	int len = ll_len(pArrayListEmployee);
	int retorno = ERROR_PUNTERO_NULL;

	if(path != NULL && pArrayListEmployee != NULL)
	{
		estadoOperacion = cargarListaEnArchivo(path, pArrayListEmployee, &contador, ARCHIVO_BINARIO_CARGADO);
		retorno = estadoOperacion;

		if(contador > 0)
		{
			printf("\n\t\t<--Se cargaron en el archivo Binario %d / %d empleados en lista-->\n", contador, len);
		}
		else
		{
			if(retorno == OPERACION_EXITOSA)
			{
				printf("\n\t<--Se completo el guardado de la lista en el archivo Binario, pero la lista estaba vacia!-->\n");
			}
		}
	}
	return retorno;
}

/** \brief Carga los datos de los empleados desde el archivo data.csv (modo texto).
 * \param char* path - Ruta absoluta o relativa del archivo
 * \param  LinkedList* pArrayListEmployee - puntero a la lista de empleados
 * \return int - retorna 0 si opero correctamente o
 * 				 retorna 1 si cancela la carga
 *               retorna -1 si el puntero es NULL o
 *               retorna -45 si el archivo no exite
 */
int controller_loadFromText(char* path, LinkedList* pArrayListEmployee)
{
	int estadoOperacion;
	int contadorCargas = 0;
	LinkedList* pListaArchivo = ll_newLinkedList();
	int retorno = ERROR_PUNTERO_NULL;

	if(path != NULL && pArrayListEmployee != NULL && pListaArchivo != NULL)
	{
		retorno = OPERACION_EXITOSA;
		estadoOperacion = cargarArchivo(path, pListaArchivo, ARCHIVO_TEXTO_CARGADO, &contadorCargas);
		if(!utn_comprobarEstadoDeOperacion(estadoOperacion) && (estadoOperacion == ARCHIVO_NO_EXISTE || estadoOperacion == ERROR_PUNTERO_NULL))
		{
			retorno = ERROR_ARCHIVO_TEXTO_NO_EXISTE;
		}
		else
		{
			if(estadoOperacion == ERROR_EN_LA_CARGA_DE_ARCHIVO_A_LISTA || estadoOperacion ==  OPERACION_EXITOSA)
			{
				menu_imprimirCantidadCargasDesdeArchivo(contadorCargas, estadoOperacion);
				if(contadorCargas >0)
				{
					estadoOperacion = evaluarUnificacionDeListas(pArrayListEmployee, pListaArchivo, estadoOperacion);
					if(estadoOperacion != OPERACION_EXITOSA)
					{
						retorno = NO;
					}
				}
			}
		}

		if(!ll_clear(pListaArchivo))
		{
			ll_deleteLinkedList(pListaArchivo);
		}
	}
    return retorno;
}

/** \brief Carga los datos de los empleados desde el archivo data.csv (modo binario).
 * \param char* path - Ruta absoluta o relativa del archivo
 * \param  LinkedList* pArrayListEmployee - puntero a la lista de empleados
 * \return int - retorna 0 si opero correctamente o
 * 				 retorna 1 si se cancela la carga
 *               retorna -1 si el puntero es NULL o
 *               retorna -47 si el archivo no exite
 *
 */
int controller_loadFromBinary(char* path , LinkedList* pArrayListEmployee)
{
	int estadoOperacion;
	int contadorCargas = 0;
	LinkedList* pListaArchivo = ll_newLinkedList();
	int retorno = ERROR_PUNTERO_NULL;

	if(path != NULL && pArrayListEmployee != NULL && pListaArchivo != NULL)
	{
		retorno = OPERACION_EXITOSA;
		estadoOperacion = cargarArchivo(path, pListaArchivo, ARCHIVO_BINARIO_CARGADO, &contadorCargas);
		if(!utn_comprobarEstadoDeOperacion(estadoOperacion) && (estadoOperacion == ARCHIVO_NO_EXISTE || estadoOperacion == ERROR_PUNTERO_NULL))
		{
			retorno = ERROR_ARCHIVO_BINARIO_NO_EXISTE;
		}
		else
		{
			if(estadoOperacion == ERROR_EN_LA_CARGA_DE_ARCHIVO_A_LISTA || estadoOperacion ==  OPERACION_EXITOSA)
			{
				menu_imprimirCantidadCargasDesdeArchivo(contadorCargas, estadoOperacion);
				if(contadorCargas >0)
				{
					estadoOperacion = evaluarUnificacionDeListas(pArrayListEmployee, pListaArchivo, estadoOperacion);
					if(estadoOperacion != OPERACION_EXITOSA)
					{
						retorno = NO;
					}
				}
			}
		}

		if(!ll_clear(pListaArchivo))
		{
			ll_deleteLinkedList(pListaArchivo);
		}
	}
    return retorno;
}

/** \brief Controlador para las altas de empleados
 * \param  LinkedList* pArrayListEmployee - puntero a la lista de empleados
 * \return int 0 si la operacion resulto exitosa o
 * 	       retorna  1 si el usuario decide volver atras o
 * 	       retorna -1 si el puntero apunta a NULL o
 * 	       retorna -23 si no se pudieron tomar todos los datos del empleado o
 * 	       retorna -25 si no se obtuvo una respuesta valida del usuario o
 * 	       retorna -34 si no se dio el alta
 */
int controller_addEmployee(LinkedList* pArrayListEmployee)
{
	int id;
	float salario;
	int horasTrabajadas;
	char nombre[LEN_NOMBRE];
	int opcionElegida;
	int estadoOperacion;
	Employee* pEmpleado = NULL;
	int retorno = ERROR_PUNTERO_NULL;

	if(pArrayListEmployee != NULL)
	{
		retorno = VOLVER_ATRAS;
		estadoOperacion = menu_ImprimirMenuAltas(&opcionElegida);

		if(utn_comprobarEstadoDeOperacion(estadoOperacion) && opcionElegida == SI)
		{
			retorno = ERROR_NO_SE_PUDIERON_TOMAR_TODOS_LOS_DATOS;
			estadoOperacion = employee_getDataToAddANewEmployee(nombre, sizeof(nombre), &horasTrabajadas, &salario);

			if(!estadoOperacion)
			{
				retorno = ERROR_NO_SE_DIO_ALTA;
				estadoOperacion = employee_getLastOrNextId(OBTENER_NUEVO_ULTIMO_ID);
				if(utn_comprobarEstadoDeOperacion(estadoOperacion))
				{
					id = estadoOperacion;
					pEmpleado = employee_newParametrosDiferenciandoTiposDeDatos(id , nombre, salario, horasTrabajadas);

					if(pEmpleado != NULL && !ll_add(pArrayListEmployee, pEmpleado))
					{
						printf("\n\t\t<--Alta Exitosa!-->");
						employee_imprimirUnSoloEmpleado(pEmpleado);
						retorno = OPERACION_EXITOSA;
					}
				}
			}
		}
		else
		{
			if(estadoOperacion == ERROR_SIN_MAS_REINTENTOS)
			{
				retorno = ERROR_NO_SE_OBTUVO_RESPUESTA_VALIDA;
			}
		}
	}
    return retorno;
}

/** \brief Controlador para las modificaciones de un empleado
 * \param  LinkedList* pArrayListEmployee - puntero a la lista de empleados
 * \return int 0 si la operacion resulto exitosa o
 * 	       retorna  1 si el usuario decide volver atras o
 * 	       retorna -1 si el puntero apunta a NULL o
 * 	       retorna -25 si no se obtuvo una respuesta valida del usuario o
 * 	       retorna -30 si no hay elementos en la lista o
 * 	       retorna -32 si el id no fue encontrado o
 */
int controller_editEmployee(LinkedList* pArrayListEmployee)
{
	int idElegido;
	int opcionElegida;
	int estadoOperacion;
	Employee* pEmpleado;
	int retorno = ERROR_PUNTERO_NULL;

	if(pArrayListEmployee != NULL)
	{
		retorno = ERROR_NO_HAY_ELEMENTOS_CARGADOS_EN_LA_LISTA;
		if(!ll_isEmpty(pArrayListEmployee))
		{
			retorno = VOLVER_ATRAS;
			estadoOperacion = menu_ImprimirMenuModificacion(MODIFICAR, &opcionElegida);

			if(utn_comprobarEstadoDeOperacion(estadoOperacion) && opcionElegida == SI)
			{
				imprimirListaDeEmpleados(pArrayListEmployee);
				estadoOperacion = menu_imprimirMenuTomaDeId();

				if(utn_comprobarEstadoDeOperacion(estadoOperacion) && estadoOperacion)
				{
					idElegido = estadoOperacion;
					retorno = ERROR_NO_SE_ENCONTRARON_DATOS_ASOCIADOS_AL_ID;
					pEmpleado = employee_findPointerToEmployeeById(pArrayListEmployee, idElegido);

					if(pEmpleado != NULL)
					{
						retorno = VOLVER_ATRAS;
						printf("\n\t\t<--Empleado a modificar-->");
						employee_imprimirUnSoloEmpleado(pEmpleado);
						estadoOperacion = menu_ImprimirMenuModificacion(MODIFICAR_CAMPOS, &opcionElegida);

						if(utn_comprobarEstadoDeOperacion(estadoOperacion) && opcionElegida != MAXIMO_MENU_MOD)
						{
							estadoOperacion = employee_getDataFromUserToEditAFiel(pEmpleado, opcionElegida);

							if(utn_comprobarEstadoDeOperacion(estadoOperacion))
							{
								printf("\n\t\t<--Modificacion Exitosa!-->");
								employee_imprimirUnSoloEmpleado(pEmpleado);
								retorno = OPERACION_EXITOSA;
							}
						}
					}
				}
			}

			if(estadoOperacion == ERROR_SIN_MAS_REINTENTOS)
			{
				retorno = ERROR_NO_SE_OBTUVO_RESPUESTA_VALIDA;
			}
		}
	}
    return retorno;
}

/** \brief Controlador que se encarga de operar toda la baja de un empledo
 * \param  LinkedList* pArrayListEmployee - puntero a la lista de empleados
 * \return int 0 si la operacion resulto exitosa o
 * 	       retorna 1 si el usuario decide volver atras o
 * 	       retorna -1 si el puntero apunta a NULL o
 * 	       retorna -25 si no se obtuvo una respuesta valida del usuario o
 * 	       retorna -30 si no hay elementos en la lista o
 * 	       retorna -32 si el id no fue encontrado
 */
int controller_removeEmployee(LinkedList* pArrayListEmployee)
{
	int indice;
	int idElegido;
	int estadoOperacion;
	int opcionElegida;
	Employee* pAuxiliar;
	int retorno = ERROR_PUNTERO_NULL;

	if(pArrayListEmployee != NULL)
	{
		retorno = ERROR_NO_HAY_ELEMENTOS_CARGADOS_EN_LA_LISTA;
		if(!ll_isEmpty(pArrayListEmployee))
		{
			retorno = VOLVER_ATRAS;
			estadoOperacion = menu_ImprimirMenuBajas(DAR_BAJA, &opcionElegida);

			if(utn_comprobarEstadoDeOperacion(estadoOperacion) && opcionElegida == SI)
			{
				imprimirListaDeEmpleados(pArrayListEmployee);
				estadoOperacion = menu_imprimirMenuTomaDeId();

				if(utn_comprobarEstadoDeOperacion(estadoOperacion) && estadoOperacion)
				{
					idElegido = estadoOperacion;
					pAuxiliar = employee_findPointerToEmployeeById(pArrayListEmployee, idElegido);
					retorno = ERROR_NO_SE_ENCONTRARON_DATOS_ASOCIADOS_AL_ID;

					if(pAuxiliar != NULL)
					{
						printf("\n\t\t<--Empleado a eliminar-->");
						employee_imprimirUnSoloEmpleado(pAuxiliar);
						estadoOperacion = menu_ImprimirMenuBajas(CONFIRMAR_BAJA, &opcionElegida);

						if(utn_comprobarEstadoDeOperacion(estadoOperacion) && opcionElegida == SI)
						{
							indice = ll_indexOf(pArrayListEmployee, pAuxiliar);
							if(indice >= 0)
							{
								if(!ll_remove(pArrayListEmployee, indice))
								{
									printf("\n\t\t<--Eliminacion Exitosa!-->");
									employee_delete(pAuxiliar);
									retorno = OPERACION_EXITOSA;

									if(ll_isEmpty(pArrayListEmployee))
									{
										printf("\n\t\t<--No hay mas empleados en la lista!-->");
									}
								}
							}
						}
					}
				}
			}

			if(estadoOperacion == ERROR_SIN_MAS_REINTENTOS)
			{
				retorno = ERROR_NO_SE_OBTUVO_RESPUESTA_VALIDA;
			}
		}
	}
    return retorno;
}

/** \brief Controlador que se encarga de listar los empleados disponibles
 * \param LinkedList* pArrayListEmployee - puntero a la lista de empleados
 * \return int 0 si la operacion resulto exitosa
 * 	       retorna -1 si el puntero apunta a NULL
 * 	       retorna -2 si el len es invalido
 * 	       retorna -30 si no hay elementos en la lista
 * 	       retorna -37 si no se pudo imprimir
 */
int controller_ListEmployee(LinkedList* pArrayListEmployee)
{
	int retorno = ERROR_PUNTERO_NULL;
	if(pArrayListEmployee != NULL)
	{
		retorno = imprimirListaDeEmpleados(pArrayListEmployee);
	}
	return retorno;
}

/** \brief Controlador que se encarga de operar todo lo referente a ordernar empleados
 * \param pArrayListEmployee LinkedList* - puntero a la lista de empleados
 * \return int - retorna 0 si la operacion fue exitosa
 *               retorna 1 si el usuario decide volver atras
 *               retorna -1 si el puntero es NULL
 *               retorna -25 si no se obtuvo una respuesta valida del usuario
 *               retorna -30 si no hay elementos cargados en la lista
 *               retorna -39 si ocurrio un error al intentar ordenar la lista
 */
int controller_sortEmployee(LinkedList* pArrayListEmployee)
{
	int estadoOperacion;
	int opcionOrden;
	int opcionCriterio;
    int retorno = ERROR_PUNTERO_NULL;

    if(pArrayListEmployee != NULL)
    {
		retorno = ERROR_NO_HAY_ELEMENTOS_CARGADOS_EN_LA_LISTA;
    	if(!ll_isEmpty(pArrayListEmployee))
    	{
    		if(ll_len(pArrayListEmployee) > 1)
    		{
				retorno = VOLVER_ATRAS;
				estadoOperacion = menu_ImprimirMenuOrdenamiento(CRITERIO, &opcionCriterio);

				if(utn_comprobarEstadoDeOperacion(estadoOperacion) && opcionCriterio != MAXIMO_MENU_ORDEN)
				{
					estadoOperacion = menu_ImprimirMenuOrdenamiento(ORDEN, &opcionOrden);

					if(utn_comprobarEstadoDeOperacion(estadoOperacion))
					{
						retorno = ERROR_AL_ORDENAR;
						printf("\n\t\t<--Ordenando lista de empleados. Esto puede demorar unos instantes...-->");
						switch(opcionCriterio)
						{
							case 1:
								estadoOperacion = ll_sort(pArrayListEmployee, employee_orderById, opcionOrden);
								break;
							case 2:
								estadoOperacion = ll_sort(pArrayListEmployee, employee_orderByName, opcionOrden);
								break;
							case 3:
								estadoOperacion = ll_sort(pArrayListEmployee, employee_orderBySalary, opcionOrden);
								break;
							case 4:
								estadoOperacion = ll_sort(pArrayListEmployee, employee_orderByHoursWorked, opcionOrden);
								break;
						}

						if(!estadoOperacion && !imprimirListaDeEmpleados(pArrayListEmployee))
						{
							retorno = OPERACION_EXITOSA;
						}
					}
				}
				if(estadoOperacion == ERROR_SIN_MAS_REINTENTOS)
				{
					retorno = ERROR_NO_SE_OBTUVO_RESPUESTA_VALIDA;
				}
    		}
    		else
    		{
    			retorno = ERROR_NO_SE_PUEDE_ORDENAR_UN_SOLO_EMPLEADO;
    		}
    	}
    }
    return retorno;
}

/** \brief Controlador que se encarga de iniciar el proceso de guardado de la lista de los empleados en el archivo .csv (modo texto).
 * \param char* path - Ruta absoluta o relativa del archivo
 * \param  LinkedList* pArrayListEmployee - puntero a la lista de empleados
 * \return int - Retorna el estado recibido de la carga del archivo
 *   			 retorna -1 si el puntero es NULL
 *   			 retorna -40 si no se cargaron correctamente todos los datos en el archivo
 *   			 retorna -44 si hay un error en la carga del archivo
 */
int controller_saveAsText(char* path , LinkedList* pArrayListEmployee)
{
	int retorno = ERROR_PUNTERO_NULL;
	if(path != NULL && pArrayListEmployee != NULL)
	{
		retorno = guardarListaEnModoTexto(path, pArrayListEmployee);
	}
    return retorno;
}

/** \brief Controlador que se encarga de iniciar el proceso de guardado de la lista de los empleados en el archivo .bin (modo binario).
 * \param char* path - Ruta absoluta o relativa del archivo
 * \param  LinkedList* pArrayListEmployee - puntero a la lista de empleados
 * \return int - Retorna 0 si opero correctamente o
 *   			 retorna -1 si el puntero es NULL
 *   			 retorna -40 si no se cargaron correctamente todos los datos en el archivo
 *   			 retorna -44 si hay un error en la carga del archivo
 */
int controller_saveAsBinary(char* path, LinkedList* pArrayListEmployee)
{
	int retorno = ERROR_PUNTERO_NULL;
	if(path != NULL && pArrayListEmployee != NULL)
	{
		retorno = guardarListaEnModoBinario(path, pArrayListEmployee);
	}
    return retorno;
}

/** \brief Controlador que evalua el estado de los archivos antes de salir de la aplicacion
 * \param LinkedList* pArrayListEmployee - puntero a la lista de empleados
 * \param int banderaArchivoTexto - bandera que contiene el estado actual de carga del archivo de texto
 * \param int banderaArchivoBinario - bandera que contiene el estado actual de carga del archivo binario
 * \param int banderaModificacion - bandera que indica si hay una modificacion sin guardar
 * \return int - retorna 15 si el usuario decide Salir de la aplicacion
 *               retorna 1 si el usuario decide volver atras
 *               Retorna -1 si el puntero es NULL
 *               retorna -25 si el usuario no ingresa una respuesta valida
 */
int controller_exitApp(LinkedList* pArraylist, int banderaArchivoTexto, int banderaArchivoBinario, int banderaModificacion)
{
	int estadoOperacion;
	int opcionElegida;
	char pathArchivoTexto [LEN_ARCHIVO] = "data.csv";
	char pathArchivoBinario [LEN_ARCHIVO] = "data.bin";
	int retorno = ERROR_PUNTERO_NULL;

	if(pArraylist != NULL)
	{
		retorno = VOLVER_ATRAS;
		estadoOperacion = menu_ImprimirMenuSalir(SALIR, &opcionElegida);
		if(utn_comprobarEstadoDeOperacion(estadoOperacion) && opcionElegida == SI)
		{
			if(banderaModificacion)
			{
				estadoOperacion = menu_VerificarCargasDeArchivosParaSalir(banderaArchivoTexto, banderaArchivoBinario);

				switch(estadoOperacion)
				{
					case ARCHIVO_TEXTO_CARGADO:
						estadoOperacion = guardarListaEnModoBinario(pathArchivoBinario, pArraylist);
						break;
					case ARCHIVO_BINARIO_CARGADO:
						estadoOperacion = guardarListaEnModoTexto(pathArchivoTexto, pArraylist);
						break;
					case NINGUN_ARCHIVO_CARGADO:
						estadoOperacion = menu_ImprimirMenuSalir(CONFIRMAR_SALIR, &opcionElegida);
						break;
				}
				utn_comprobarEstadoDeOperacion(estadoOperacion);
			}
			if(!estadoOperacion && opcionElegida == SI)
			{
				retorno = SALIR_APLICACION;
			}
		}

		if(estadoOperacion == ERROR_SIN_MAS_REINTENTOS)
		{
			retorno = ERROR_NO_SE_OBTUVO_RESPUESTA_VALIDA;
		}
	}
	return retorno;
}
