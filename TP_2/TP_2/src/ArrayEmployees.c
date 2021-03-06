/*
 * ArrayEmployees.c
 *
 *  Created on: 5 oct 2021
 *      Author: GONZALO
 */

#include "ArrayEmployees.h"

#define VACIO 1
#define OCUPADO 0
#define ORDENADO 1
#define DESORDENADO 0
#define ORDEN_ASCENDENTE 1
#define MAXIMO_LEN 1000
#define SECTOR_MINIMO 1
#define SECTOR_MAXIMO 10
#define SALARIO_MINIMO 1
#define SALARIO_MAXIMO 500000
#define MOSTRAR_TODOS_LOS_DATOS_DEL_EMPLEADO 1
#define MOSTRAR_ID_NOMBRE_EMPLEADOS_DISPONIBLES 2
#define REINTENTOS 2
#define HAY_EMPLEADOS 1
#define OPERACION_EXITOSA 0
#define NO_HAY_EMPLEADOS 0
#define NINGUN_EMPLEADO_SUPERA_SALARIO_PROMEDIO 0
#define PUNTERO_NULL -1
#define LEN_INVALIDO -2
#define ID_FUERA_DE_RANGO -11
#define NO_HAY_EMPLEADOS_CARGADOS_CON_ESE_ID -12
#define PARAMETRO_I_NO_ES_DISTINTO_DE_J -13
#define NO_SE_CARGARON_TODOS_LOS_CAMPOS -14
#define NO_SE_APLICARON_CAMBIOS_SOBRE_EL_EMPLEADO -15
#define NO_HAY_EMPLEADOSCARGADOS_EN_EL_SISTEMA -16
#define NO_SE_CALCULO_EL_PROMEDIO_DE_SALARIOS -17
#define NO_SE_PUDO_IMPRIMIR_DATOS_RELACIONADOS_CON_SALARIOS -18
#define NO_SE_APLICARON_BAJAS -19
#define NO_SE_ENCONTRARON_DATOS_ASOCIADOS_AL_ID_INDICADO -20
#define ARRAY_COMPLETO -21
#define I_O_J_ESTA_FUERA_DE_RANGO -23
#define NO_SE_CARGO_NINGUN_ALTA -25

static int generadorDeIds(void);
static void imprimirEncabezadoDeTablaEmpleados(int opcion);
static void imprimirFilaDeEmpleado(Employee empleado, int opcion);
static int swapEmpleados(Employee listaEmpleados[], int i, int j);

/**
* \brief Genera un ID, que es acumulativo.
* \param VOID -
* \return retorna INT. Un entero positivo que es el ID generado
*/
static int generadorDeIds(void)
{
	static int id = 0;
	id++;
	return id;
}

/** \brief Imprime los encabezados de la tabla de datos.
* \param int opcion - opcion que determina el encabezado que se imprime
* \return VOID
*/
static void imprimirEncabezadoDeTablaEmpleados(int opcion)
{
	switch(opcion)
	{
		case 1:
			printf("\n%5s  %-15s %-15s %18s %12s", "Id", "Nombre", "Apellido", "Salario", "Sector");
			break;
		case 2:
			printf("\n\n\t\t<--Lista de Ids disponibles-->\n%5s  %-15s %-15s", "Id", "Nombre", "Apellido");
			break;
	}
}

/** \brief Imprime los datos de un empleado ya validado previamente.
 * 		   (Id, nombre, apellido, salario, sector).
* \param Employee empleado - Empleado cuyos datos se quieren imprimir
* \param int opcion - opcion que determina los datos que se imprimen del empleado
* \return VOID
*/
static void imprimirFilaDeEmpleado(Employee empleado, int opcion)
{
	switch(opcion)
	{
		case 1:
			printf("\n%5d  %-15.15s %-15.15s   $%15.4f %12d", empleado.id, empleado.name, empleado.lastName, empleado.salary, empleado.sector);
			break;
		case 2:
			printf("\n%5d  %-15.15s %-15.15s", empleado.id, empleado.name, empleado.lastName);
			break;
	}
}

/** \brief Cambia la posicion de 2 empleados
* \param Employee listaEmpleados [] - Lista de empleados
* \param int i - Indice en el array, del empleado A
* \param int i - Indice en el array, del empleado B
* \return INT. 0 Si pudo operar correctamente
* 			  -1 si la direccion de memoria del array es NULL
* 			  -13 si el parametro i no es distinto del parametro j.
* 			  -23 si el indice de i o j estan fuera del rango.
*/
static int swapEmpleados(Employee listaEmpleados[], int i, int j)
{
	int retorno = PUNTERO_NULL;
	Employee auxiliar;

	if(listaEmpleados != NULL)
	{
		retorno = I_O_J_ESTA_FUERA_DE_RANGO;
		if((i >= 0 && i < MAXIMO_LEN) && (j >= 0 && j < MAXIMO_LEN))// i y j son indices, por eso van de 0 a < maximo
		{
			retorno = PARAMETRO_I_NO_ES_DISTINTO_DE_J;
			if(i != j)
			{
				auxiliar = listaEmpleados[i];
				listaEmpleados[i] = listaEmpleados[j];
				listaEmpleados[j] = auxiliar;
				retorno = OPERACION_EXITOSA;
			}
		}
	}
	return retorno;
}

/**
* \brief Inicializa la bandera 'IsEmpty' en 1 en todas las posiciones,
*          indicando que todas las posiciones del array estan vacias.
* \param Employee* list - Array de tipo Employee
* \param int len - largo del Array
* \return retorna INT. 0 si esta todo OK.
*         retorna -1 si la direccion de memoria del array es NULL.
*         retorna -2 si el len es invalido.
*/
int initEmployees(Employee* list, int len)
{
	int i;
	int retorno = PUNTERO_NULL;

	if(list != NULL)
	{
		retorno = LEN_INVALIDO;
		if(len > 0 && len <= MAXIMO_LEN)
		{
			for(i = 0; i < len; i++)
			{
				list[i].isEmpty = VACIO;
			}
			retorno = OPERACION_EXITOSA;
		}
	}
	return retorno;
}

/*
* \brief Evalua si hay empleados en la lista (ante una eliminacion o falta de carga).
* \param Employee listaEmpleados[] - lista de todos los empleados
* \param int len - largo del array
* \return Retorna INT. 1 si hay empleados.
* 		  Retorna  0 Si no hay empleados.
* 		  Retorna -1 si la direccion de memoria es NULL.
* 		  Retorna -2 si hay el largo del array es invalido
*/
int verificarSiHayEmpleados(Employee listaEmpleados[], int len)
{
	int i;
	int retorno = PUNTERO_NULL;

	if(listaEmpleados != NULL)
	{
		retorno = LEN_INVALIDO;
		if(len >0 && len <= MAXIMO_LEN)
		{
			retorno = NO_HAY_EMPLEADOS;
			for(i = 0; i < len; i++)
			{
				if(listaEmpleados[i].isEmpty == OCUPADO)
				{
					retorno = HAY_EMPLEADOS;
					break;
				}
			}
		}
	}
	return retorno;
}

/** \brief Agrega en un elemento de la lista existente de tipo Employees los valores recibidos por parametro,
 *         en la primer posicion vacia que este disponible.
* \param Employee* list - Array de tipo Employee
* \param int len - largo del array
* \param int id - id del empleado
* \param char name[] - Nombre del empleado
* \param char lastName[] - Apellido del empleado
* \param float salary - Salario del empleado
* \param int sector - Sector del empleado
* \return Retorna INT. 0 Si se opero correctamente,
*          retorna -1 si la direccion de memoria del array es NULL,
*          retorna -2 si el len es invalido
*          retorna -11 si el ID esta fuera de rango
*          retorno -25 si no se pudo dar el alta.
*/
int addEmployees(Employee* list, int len, int id, char name[],char lastName[],float salary,int sector)
{
	int indiceLibre;
	int retorno = PUNTERO_NULL;

	if(list != NULL && name != NULL && lastName != NULL)
	{
		retorno = LEN_INVALIDO;
		if(len > 0 && len <= MAXIMO_LEN)
		{
			retorno = ID_FUERA_DE_RANGO;
			if(id > 0)
			{
				retorno = NO_SE_CARGO_NINGUN_ALTA;
				indiceLibre = buscarIndiceLibre(list, len);
				if(utn_comprobarEstadoDeOperacion(indiceLibre))
				{
					list[indiceLibre].id = id;
					list[indiceLibre].salary = salary;
					list[indiceLibre].sector = sector;
					strncpy(list[indiceLibre].name, name, sizeof(list[indiceLibre].name));
					strncpy(list[indiceLibre].lastName, lastName, sizeof(list[indiceLibre].name));
					list[indiceLibre].isEmpty = OCUPADO;
					retorno = OPERACION_EXITOSA;
				}
			}
		}
	}
	return retorno;
}

/** \brief Busca un indice libre que pueda ser cargado de datos.
* \param Employee listaEmpleados[] - Array de tipo Employee
* \param int len - largo del array
* \return Retorna INT. 0 o un numero positivo, que es el indice libre encontrado
*          retorna -1 si la direccion de memoria del array es NULL,
*          retorna -2 si el len es invalido
*          retorno -21 si todos los espacios estan ocupados.
*/
int buscarIndiceLibre(Employee listaEmpleados[], int len)
{
	int i;
	int retorno = PUNTERO_NULL;

	if(listaEmpleados != NULL)
	{
		retorno = LEN_INVALIDO;
		if(len > 0  && len <= MAXIMO_LEN)
		{
			retorno = ARRAY_COMPLETO;
			for(i = 0; i < len; i++)
			{
				if(listaEmpleados[i].isEmpty == VACIO)
				{
					retorno = i;
					break;
				}
			}
		}
	}
	return retorno;
}

/** \brief Toma los datos de un empleado para posteriormente enviarselos a
 * 			la funcion addEmployee() quien se encargara de cargarlo en el sistema.
* \param Employee listadoEmpleados[] - Array de tipo Employee
* \param int len - largo del array
* \param int* idMaximo - puntero a variable idMaximo, para cargar en ella el ultimo ID generado
* \return Retorna INT. 0 Si se opero correctamente,
*          retorna -1 si la direccion de memoria del array es NULL,
*          retorna -2 si el len es invalido
*          retorna -14 si no se pudieron cargar correctamente todos los campos.
*/
int tomarDatosEmpleados(Employee listaEmpleados[], int len, int* idMaximo)
{
	Employee auxiliar;
	int estadoOperacion;
	int iDGenerado;
	int retorno = PUNTERO_NULL;

	if(listaEmpleados != NULL && idMaximo != NULL)
	{
		retorno = LEN_INVALIDO;
		if(len > 0 && len <= MAXIMO_LEN)
		{
			retorno = NO_SE_CARGARON_TODOS_LOS_CAMPOS;
			estadoOperacion = utn_getNombreOApellido(auxiliar.name, sizeof(auxiliar.name), "Ingrese el nombre", "Error, dato invalido!", REINTENTOS);
			if(utn_comprobarEstadoDeOperacion(estadoOperacion))
			{
				estadoOperacion = utn_getNombreOApellido(auxiliar.lastName, sizeof(auxiliar.lastName), "Ingrese el apellido", "Error, dato invalido!", REINTENTOS);
				if(utn_comprobarEstadoDeOperacion(estadoOperacion))
				{
					estadoOperacion = utn_getFloat(&auxiliar.salary, "Ingrese el salario (1 - 500000)", "Error, dato invalido!", SALARIO_MINIMO, SALARIO_MAXIMO, REINTENTOS);
					if(utn_comprobarEstadoDeOperacion(estadoOperacion))
					{
						estadoOperacion = utn_getInt(&auxiliar.sector, "Ingrese el sector (1 - 10)", "Error, dato invalido!", SECTOR_MINIMO, SECTOR_MAXIMO, REINTENTOS);
						if(utn_comprobarEstadoDeOperacion(estadoOperacion))
						{
							iDGenerado = generadorDeIds();
							*idMaximo = iDGenerado;
							estadoOperacion = addEmployees(listaEmpleados, len, iDGenerado, auxiliar.name, auxiliar.lastName, auxiliar.salary, auxiliar.sector);
							if(utn_comprobarEstadoDeOperacion(estadoOperacion))
							{
								retorno = OPERACION_EXITOSA;
							}
						}
					}
				}
			}
		}
	}
	return retorno;
}

/** \brief Encuentra un empleado por su Id, y retorna el indice del array donde se encuentra.
* \param Employee* list - lista de todos los empleados
* \param int len - largo del array
* \param int Id - Id del empleado que se desea encontrar
* \return Retorna INT. Retorna el indice del empleado (0 a 999)
* 		  Retorna -1 si la direccion de memoria es NULL.
* 		  Retorna -2 si hay el largo del array es invalido
* 		  Retorna -11 si el ID es invalido
* 		  retorna -12 si el Id es valido, pero no tiene ningun empleado cargado.
*/
int findEmployeeById(Employee* list, int len,int id)
{
	int i;
	int retorno = PUNTERO_NULL;

	if(list != NULL)
	{
		retorno = LEN_INVALIDO;
		if(len > 0 && len <= MAXIMO_LEN)
		{
			retorno = ID_FUERA_DE_RANGO;

			if(id >0)
			{
				retorno = NO_HAY_EMPLEADOS_CARGADOS_CON_ESE_ID;
				for(i = 0; i< len ; i++)
				{
					if(list[i].id == id && list[i].isEmpty == OCUPADO)
					{
						retorno = i;
						break;
					}
				}
			}
		}
	}
	return retorno;
}

/*
* \brief Toma el nuevo dato que se le quiere otorgar a un campo elegido que recibe por parametro.
* \param Employee* pAuxiliar - auxiliar donde se cargara el dato
* \param int opcion - opcion que se cargara
* \return Retorna INT. 0 Si se opero correctamente,
*         retorna -14 si no se pudieron tomar los datos correctamente.
*/
int campoAModificar(Employee* pAuxiliar, int opcion)
{
	int estadoOperacion;
	int retorno = NO_SE_CARGARON_TODOS_LOS_CAMPOS;
	switch(opcion)
	{
		case 1:
			estadoOperacion = utn_getNombreOApellido(pAuxiliar->name, sizeof(pAuxiliar->name), "Ingrese el nuevo nombre", "Dato invalido!", REINTENTOS);
			break;
		case 2:
			estadoOperacion = utn_getNombreOApellido(pAuxiliar->lastName, sizeof(pAuxiliar->lastName), "Ingrese el nuevo apellido", "Dato invalido!", REINTENTOS);
			break;
		case 3:
			estadoOperacion = utn_getFloat(&pAuxiliar->salary, "Ingrese el nuevo salario (1 - 500000)", "Error, dato invalido!", SALARIO_MINIMO, SALARIO_MAXIMO, REINTENTOS);
			break;
		case 4:
			estadoOperacion = utn_getInt(&pAuxiliar->sector, "Ingrese el nuevo sector (1 - 10)", "Error, dato invalido!", SECTOR_MINIMO, SECTOR_MAXIMO, REINTENTOS);
			break;
	}

	if(utn_comprobarEstadoDeOperacion(estadoOperacion))
	{
		retorno = OPERACION_EXITOSA;
	}
	return retorno;
}

/*
* \brief Modifica al empleado indicado por Id.
* \param Employee* pEmpleado - Empleado que se quiere modificar
* \param int opcion - Opcion que indica que elemento se modificara.
* \return Retorna INT. 0 Si se opero correctamente,
*          retorna -1 si la direccion de memoria del array es NULL,
*          retorna -15 si no se pudo realizar la modificacion del empleado.
*/
int modificarEmpleado(Employee* pEmpleado, int opcion)
{
	Employee auxiliar;
	int estadoOperacion;
	int retorno = PUNTERO_NULL;

	if(pEmpleado != NULL)
	{
		retorno = NO_SE_APLICARON_CAMBIOS_SOBRE_EL_EMPLEADO;
		estadoOperacion = campoAModificar(&auxiliar, opcion);
		if(utn_comprobarEstadoDeOperacion(estadoOperacion))
		{
			switch(opcion)
			{
				case 1:
					strncpy(pEmpleado->name, auxiliar.name, sizeof(pEmpleado->name));
					break;
				case 2:
					strncpy(pEmpleado->lastName, auxiliar.lastName, sizeof(pEmpleado->lastName));
					break;
				case 3:
					pEmpleado->salary = auxiliar.salary;
					break;
				case 4:
					pEmpleado->sector = auxiliar.sector;
					break;
			}
			retorno = OPERACION_EXITOSA;
		}
	}
	return retorno;
}

/** \brief Elimina a un empleado por su Id (se setea la bandera "isEmpty" en 1)
* \param Employee* list - Lista de empleados
* \param int len - largo del array
* \param int id - Id del empleado que se eliminara
* \return Retorna INT. Retorna 0 si la eliminacion fue exitosa.
* 		  Retorna -1 si la direccion de memoria es NULL.
* 		  Retorna -2 si hay el largo del array es invalido
* 		  Retorna -11 si el ID es invalido
* 		  retorna -19 si no se aplicaron bajas en el sistema (porque el ID no tiene datos).
*/
int removeEmployee(Employee* list, int len, int id)
{
	int indiceRecibido;
	int retorno = PUNTERO_NULL;

	if(list != NULL)
	{
		retorno = LEN_INVALIDO;
		if(len > 0 && len <= MAXIMO_LEN)
		{
			retorno = ID_FUERA_DE_RANGO;
			if(id >0)
			{
				retorno = NO_SE_APLICARON_BAJAS;

				indiceRecibido = findEmployeeById(list, len, id);
				if(utn_comprobarEstadoDeOperacion(indiceRecibido))
				{
					list[indiceRecibido].isEmpty = VACIO;
					retorno = OPERACION_EXITOSA;
				}
			}
		}
	}
	return retorno;
}

/** \brief Imprime los campos Id, nombre y apellido del array listaEmpleados[] recibido por parametro
* \param Employee  listaEmpleados[] - lista para imprimir
* \param int len - largo del array
* \return INT. 0 Si pudo operar correctamente
* 			  -1 si la direccion de memoria del array es NULL
* 			  -2 si el largo del array es invalido
*/
int imprimirIdsDisponibles(Employee listaEmpleados[], int len)
{
	int i;
	int retorno = PUNTERO_NULL;
	if(listaEmpleados!= NULL)
	{
		retorno = LEN_INVALIDO;
		if(len >0 && len <= MAXIMO_LEN)
		{
			retorno = OPERACION_EXITOSA;
			imprimirEncabezadoDeTablaEmpleados(MOSTRAR_ID_NOMBRE_EMPLEADOS_DISPONIBLES);
			for(i = 0; i < len; i++)
			{
				if(listaEmpleados[i].isEmpty == OCUPADO)
				{
					imprimirFilaDeEmpleado(listaEmpleados[i], MOSTRAR_ID_NOMBRE_EMPLEADOS_DISPONIBLES);
				}
			}
		}
	}
	return retorno;
}

/** \brief Imprime el contenido del empleado recibido por parametro
* \param Employee empleado - empleado que se imprime
* \return INT. 0 Si pudo operar correctamente
* 			 -20 si no se encontraron datos asociados al ID indicado
*/
int printOneEmployee(Employee empleado)
{
	int retorno = NO_SE_ENCONTRARON_DATOS_ASOCIADOS_AL_ID_INDICADO;

	if(empleado.isEmpty == OCUPADO)
	{
		printf("\n\t\t<--Datos asociados al ID: < %d >-->\n", empleado.id);
		imprimirEncabezadoDeTablaEmpleados(MOSTRAR_TODOS_LOS_DATOS_DEL_EMPLEADO);
		imprimirFilaDeEmpleado(empleado, MOSTRAR_TODOS_LOS_DATOS_DEL_EMPLEADO);
		retorno = OPERACION_EXITOSA;
	}
	return retorno;
}

/** \brief Imprime todo el contenido de un array listaEmpleados[] recibido por parametro
* \param Employee* list - lista para imprimir
* \param int len - largo del array
* \return INT. 0 Si pudo operar correctamente
* 			  -1 si la direccion de memoria del array es NULL
* 			  -2 si el largo del array es invalido
*/
int printEmployees(Employee* list, int length)
{
	int i;
	int retorno = PUNTERO_NULL;

	if(list != NULL)
	{
		retorno = LEN_INVALIDO;
		if(length > 0 && length <= MAXIMO_LEN)
		{
			retorno = OPERACION_EXITOSA;

			printf("\n\t\t<--Mostrando lista con informacion de los empleados-->");
			imprimirEncabezadoDeTablaEmpleados(MOSTRAR_TODOS_LOS_DATOS_DEL_EMPLEADO);
			for(i = 0; i < length; i++)
			{
				if(list[i].isEmpty == OCUPADO)
				{
					imprimirFilaDeEmpleado(list[i], MOSTRAR_TODOS_LOS_DATOS_DEL_EMPLEADO);
				}
			}
		}
	}
	return retorno;
}

/** \brief Ordena los elementos del array de empleados por apellido y sector.
 *         El argumento Orden se utiliza para indica orden Ascendente (1) o descendente (0)
* \param Employee* list - Lista de empleados
* \param int len - largo del array
* \param int order - [1] Orden Ascendente - [0] orden Descendente
* \return INT. 0 Si pudo operar correctamente
* 			  -1 si la direccion de memoria del array es NULL
* 			  -2 si el largo del array es invalido
*/
int sortEmployees(Employee* list, int len, int order)
{
	int retornoApellido;
	int banderaOrdenado;
	int i = 0;
	int limite = len;
	int retorno = PUNTERO_NULL;
	int largoCadenaApellido = sizeof(list[i].lastName);

	if(list != NULL)
	{
		retorno = LEN_INVALIDO;
		if(len > 0 && len <= MAXIMO_LEN)
		{
			retorno = OPERACION_EXITOSA;
			do
			{
				banderaOrdenado = ORDENADO;
				limite = limite - 1;

				for(i = 0; i < limite; i++)
				{
					retornoApellido = strncmp(list[i].lastName, list[i+1].lastName, largoCadenaApellido);

					if(order == ORDEN_ASCENDENTE)
					{
						if((retornoApellido > 0) || (retornoApellido == 0 && (list[i].sector > list[i+1].sector)))
						{
							banderaOrdenado = swapEmpleados(list, i, i+1);//Si el swap opera, quiere decir que esta desordenado
							utn_comprobarEstadoDeOperacion(banderaOrdenado);
						}
					}
					else
					{
						if((retornoApellido < 0) || (retornoApellido == 0 && (list[i].sector < list[i+1].sector)))
						{
							banderaOrdenado = swapEmpleados(list, i, i+1);//Si el swap opera, quiere decir que esta desordenado
							utn_comprobarEstadoDeOperacion(banderaOrdenado);
						}
					}
				}
			}while(banderaOrdenado == DESORDENADO);
		}
	}
	return retorno;
}

/*
* \brief Imprime los datos relacionados con los salarios. Se apoya en 2 funciones.
* \param Employee listaEmpleados[] - lista de todos los empleados
* \param int len - largo del array
* \return Retorna 0 Si Ok.
* 		  Retorna -1 si la direccion de memoria es NULL.
* 		  Retorna -2 si hay el largo del array es invalido
* 		  retorna -18 si por un error no pudo imprimir los datos relacionados con los salarios
*/
int imprimirDatosDeSalario(Employee listaEmpleados[], int len)
{
	int retorno = PUNTERO_NULL;
	float totalSalarios;
	float promedioSalarios;
	int estadoOperacion;
	int cantidadEmpleadosQueSuperanSalarioPromedio;
	if(listaEmpleados != NULL)
	{
		retorno = LEN_INVALIDO;
		if(len > 0 && len <= MAXIMO_LEN)
		{
			estadoOperacion = calcularSalarios(listaEmpleados, len, &totalSalarios, &promedioSalarios);
			if(utn_comprobarEstadoDeOperacion(estadoOperacion))
			{
				printf("\n\n\t\t<--Mostrando datos relacionados con salarios-->\n%20s %21s","Total de salarios", "Promedio Salarios");
				printf("\n$%19.4f  $%19.4f\n", totalSalarios, promedioSalarios);

				printf("\n\t\t<--Mostrando lista de empleados que <superan> el salario promedio-->");
				imprimirEncabezadoDeTablaEmpleados(MOSTRAR_TODOS_LOS_DATOS_DEL_EMPLEADO);

				estadoOperacion = calcularEImprimirEmpleadosQueSuperanSalarioPromedio(listaEmpleados,len, promedioSalarios);
				if(utn_comprobarEstadoDeOperacion(estadoOperacion))
				{
					cantidadEmpleadosQueSuperanSalarioPromedio = estadoOperacion;
					printf("\n\n Cantidad de empleados que <superan> el salario promedio: %d\n", cantidadEmpleadosQueSuperanSalarioPromedio);
					retorno = OPERACION_EXITOSA;
				}
			}

			if(retorno < 0)
			{
				retorno = NO_SE_PUDO_IMPRIMIR_DATOS_RELACIONADOS_CON_SALARIOS;
			}
		}
	}
	return retorno;
}

/*
* \brief Calcula, imprime y retorna la cantidad de empleados que superan el salario promedio.
* \param Employee listaEmpleados[] - lista de todos los empleados
* \param int len - largo del array
* \param float promedioSalario - Puntero a variable promedio
* \return Retorna  Numero positivo que representa la cantidad de empleados que superan el salario promedio.
* 		  Retorna 0 si ningun empleado supera el salario promedio
* 		  (porque se eliminaron los empleados que lo superaban o solo hay un empleado cargado)
* 		  Retorna -1 si la direccion de memoria es NULL.
* 		  Retorna -2 si hay el largo del array es invalido
* 		  retorna -16 si no hay empleados cargados en el sistema
* 		  retorna -17 si no se ha calculado el promedio de los salarios.
*/
int calcularEImprimirEmpleadosQueSuperanSalarioPromedio(Employee listaEmpleados[], int len, float promedioSalario)
{
	int i;
	int contador=0;
	int retorno = PUNTERO_NULL;

	if(listaEmpleados != NULL)
	{
		retorno = LEN_INVALIDO;
		if(len >0 && len <=MAXIMO_LEN)
		{
			retorno = NO_SE_CALCULO_EL_PROMEDIO_DE_SALARIOS;
			if(promedioSalario >0)
			{
				retorno = NO_HAY_EMPLEADOSCARGADOS_EN_EL_SISTEMA;
				for(i = 0; i < len; i++)
				{
					if(listaEmpleados[i].isEmpty == OCUPADO)
					{
						retorno = NINGUN_EMPLEADO_SUPERA_SALARIO_PROMEDIO;

						if(listaEmpleados[i].salary > promedioSalario)
						{
							imprimirFilaDeEmpleado(listaEmpleados[i], MOSTRAR_TODOS_LOS_DATOS_DEL_EMPLEADO);
							contador++;
						}
					}
				}

				if(contador > 0)
				{
					retorno = contador;
				}
				else
				{
					printf("\n%5s %7s %17s %25s %12s","-","-","-","-","-");
				}
			}
		}
	}
	return retorno;
}

/*
* \brief Calcula el total de los salarios y el promedio de salarios
* \param Employee listaEmpleados[] - lista de todos los empleados
* \param int len - largo del array
* \param float* pTotalSalarios - Puntero a variable totalSalarios
* \param float* pPromedioSalarios - Puntero a variable promedio
* \return Retorna  0 Si esta OK.
* 		  Retorna -1 si la direccion de memoria es NULL.
* 		  Retorna -2 si hay el largo del array es invalido
* 		  retorna -16 si no hay empleados cargados en el sistema
*/
int calcularSalarios(Employee listaEmpleados[], int len, float* pTotalSalarios, float* pPromedioSalarios)
{
	int i;
	float promedio;
	int contador = 0;
	float acumuladorSalarios = 0.0;
	int retorno = PUNTERO_NULL;
	if(listaEmpleados != NULL && pTotalSalarios != NULL && pPromedioSalarios != NULL)
	{
		retorno = LEN_INVALIDO;
		if(len > 0 && len <= MAXIMO_LEN)
		{
			retorno = NO_HAY_EMPLEADOSCARGADOS_EN_EL_SISTEMA;
			for(i = 0; i< len; i++)
			{
				if(listaEmpleados[i].isEmpty == OCUPADO)
				{
					acumuladorSalarios = acumuladorSalarios + listaEmpleados[i].salary;
					contador++;
				}
			}

			if(contador > 0)
			{
				promedio = acumuladorSalarios / contador;
				*pPromedioSalarios = promedio;
				*pTotalSalarios = acumuladorSalarios;
				retorno = OPERACION_EXITOSA;
			}
		}
	}
	return retorno;
}
