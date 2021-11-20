
#include "Employee.h"

#define ERROR -50
#define LEN_INT 10
#define LEN_FLOAT 10
#define TRUE 1
#define MOSTRAR_ID_NOMBRE 1
#define REINTENTOS 2
#define MOSTRAR_TODOS_LOS_DATOS 2
#define LEN_NOMBRE 128
#define LEN_ARCHIVO 50
#define LEN_TEXTO 200
#define ERROR_PUNTERO_NULL_AL_COMPARAR -10
#define MAXIMO_HORAS_TRABAJADAS 500
#define MINIMO_HORAS_TRABAJADAS 1
#define MINIMO_SALARIO 1
#define MAXIMO_SALARIO 500000
#define OPERACION_EXITOSA 0
#define ERROR_PUNTERO_NULL -1
#define ERROR_DATO_FUERA_DE_RANGO -9
#define ERROR_DATO_INVALIDO -11
#define ERROR_NO_SE_PUDIERON_TOMAR_TODOS_LOS_DATOS -23
#define ERROR_ID_INVALIDO -24
#define ERROR_NO_SE_ENCONTRARON_DATOS_ASOCIADOS_AL_ID -32
#define ERROR_NO_SE_DIO_MODIFICACION -35
#define ERROR_NO_SE_PUDO_IMPRIMIR -37
#define ERROR_NO_SE_PUDIERON_OBTENER_TODOS_LOS_DATOS -38
#define ERROR_NO_SE_PUDO_GUARDAR_ULTIMO_ID_EN_ARCHIVO -49
#define IGUALDAD 0
#define PRIMERO_ES_MAYOR 1
#define SEGUNDO_ES_MAYOR -1
#define OBTENER_ACTUAL_ULTIMO_ID 1
#define OBTENER_NUEVO_ULTIMO_ID 2
#define SIN_INGRESOS 0
#define PRIMER_INGRESO_OK 1
#define NO_SE_ENCONTRO_ARCHIVO_DE_ID 2
#define ARCHIVO_ID_CREADO_O_ACTUALIZADO 3

static int employee_abrirArchivoConUltimoId(char* path, int* pUltimoId);
static int employee_guardarUltimoIdEnArchivo(char* path, int ultimoId);
static int employee_buscarUltimoId(char* pPathListado, int* pUltimoId);

/**
* \brief Obtiene una direccion de memoria con espacio suficiente para colocar un nuevo empleado
* \param void -
* \return retorna un eEmpleado* (direccion de memoria disponible con espacio suficiente para el nuevo empleado)
*/
Employee* employee_new()
{
	Employee* pEmpleado;
	pEmpleado = (Employee*)malloc(sizeof(Employee));

	return pEmpleado;
}

/**
* \brief Obtiene la direccion de memoria de un nuevo empleado, cargando todos sus campos con los parametros recibidos
* 		 Recibe todos los campos en tipo char.
* \param char* pIdStr - string del id
* \param char* pNombreStr - string nombre
* \param char* pHorasTrabajadasStr - string con las hs trabajadas
* \param char* pSalario - Salario del empleado
* \return retorna un eEmpleado* (direccion de memoria disponible con espacio suficiente para el nuevo empleado)
* 		  retorna NULL si hubo un error.
*/
Employee* employee_newParametros(char* pIdStr,char* pNombreStr,char* pHorasTrabajadasStr, char* pSalarioStr)
{
	Employee* pEmpleado = NULL;
	if(pIdStr != NULL && pNombreStr != NULL && pHorasTrabajadasStr != NULL && pSalarioStr != NULL)
	{
		pEmpleado = employee_new();
		if(pEmpleado != NULL)
		{
			if(employee_setHorasTrabajadasTexto(pEmpleado, pHorasTrabajadasStr) ||
			   employee_setIdTexto(pEmpleado, pIdStr) ||
			   employee_setSueldoTexto(pEmpleado, pSalarioStr)  ||
			   employee_setNombre(pEmpleado, pNombreStr))
			{
				employee_delete(pEmpleado);
				pEmpleado = NULL;
			}
		}
	}
	return pEmpleado;
}

/**
* \brief Obtiene la direccion de memoria de un nuevo empleado, cargando todos sus campos con los parametros recibidos
* \param int id - id empleado
* \param char nombre[] -  nombre del empleado
* \param int horasTrabajadas - hs trabajadas
* \param  int salario - Salario del empleado
* \return retorna un eEmpleado* (direccion de memoria disponible con espacio suficiente para el nuevo empleado)
* 		  o retorna NULL en caso de ERROR
*/
Employee* employee_newParametrosDiferenciandoTiposDeDatos(int id, char pNombre[],  float salario, int horasTrabajadas)
{
	Employee* pEmpleado = NULL;
	if(pNombre != NULL)
	{
		pEmpleado = employee_new();
		if(pEmpleado != NULL)
		{
			if(employee_setHorasTrabajadas(pEmpleado, horasTrabajadas) ||
			   employee_setId(pEmpleado, id) ||
			   employee_setSueldo(pEmpleado, salario) ||
			   employee_setNombre(pEmpleado, pNombre))
			{
				employee_delete(pEmpleado);
				pEmpleado = NULL;
			}
		}
	}
	return pEmpleado;
}

/*
* \brief Libera los datos que se hayan cargado en una direccion de memoria.
* \param Employee* pEmpleado - direccion de memoria de empleado, a la cual se le liberaran los datos cargados
* \return VOID
* */
void employee_delete(Employee* pEmpleado)
{
	if(pEmpleado != NULL)
	{
		free(pEmpleado);
	}
}

/*
* \brief Toma los datos de la modificacion, y los carga en una direccion de memoria recibida por parametro
* \param Employee* pEmpleado - direccion de memoria del empleado, al cual se le realizaran las modificaciones
* \param int opcion - opcion que representa el campo que se desea modificar
* \return retorna INT. 0 si opero correctamente
* 	      retorna -1 si algun puntero apunta a NULL
* 	      retorna -23 si no se pudieron tomar todos los datos correctamente
* 	      retorna -35 si no se pudo aplicar la modificacion

* */
int employee_getDataFromUserToEditAFiel(Employee* pEmpleado, int opcion)
{
	int estadoOperacion;
	char nombre[LEN_NOMBRE];
	int horasTrabajadas;
	int salario;
	int retorno = ERROR_PUNTERO_NULL;
	if(pEmpleado != NULL)
	{
		retorno = ERROR_NO_SE_PUDIERON_TOMAR_TODOS_LOS_DATOS;
		switch(opcion)
		{
			case 1:
				estadoOperacion = utn_getNombreOApellido(nombre, sizeof(nombre), "\nIngrese el nombre completo", "\nError. Dato invalido", REINTENTOS);
				break;
			case 2:
				estadoOperacion = utn_getInt(&horasTrabajadas, "Ingrese las horas trabajadas (1 - 500)", "Error. Dato invalido", MINIMO_HORAS_TRABAJADAS, MAXIMO_HORAS_TRABAJADAS, REINTENTOS);
				break;
			case 3:
				estadoOperacion = utn_getInt(&salario, "Ingrese el salario $(1 - 500000)", "Error. Dato invalido", MINIMO_SALARIO, MAXIMO_SALARIO, REINTENTOS);
				break;
		}

		if(utn_comprobarEstadoDeOperacion(estadoOperacion))
		{
			retorno = ERROR_NO_SE_DIO_MODIFICACION;
			switch(opcion)
			{
				case 1:
					estadoOperacion = employee_setNombre(pEmpleado, nombre);
					break;
				case 2:
					estadoOperacion = employee_setHorasTrabajadas(pEmpleado, horasTrabajadas);
					break;
				case 3:
					estadoOperacion = employee_setSueldo(pEmpleado, salario);
					break;
			}
			if(utn_comprobarEstadoDeOperacion(estadoOperacion))
			{
				retorno = OPERACION_EXITOSA;
			}
		}
	}
	return retorno;
}

///////////////////////////////////FUNCIONES IMPRIMIR/////////////////////////////////////////////////////////

/**
* \brief Imprime los encabezados para la tabla de datos de empleados
* \param int opcion - opcion que determina el encabezado que se va a imprimir
* \return retorna VOID
*/
void employee_ImprimirEncabezadoDeDatos(int opcion)
{
	switch(opcion)
	{
		case MOSTRAR_ID_NOMBRE:
			printf("\n%5s   %-30s","Id", "Nombre y apellido");
			break;
		case MOSTRAR_TODOS_LOS_DATOS:
			printf("\n%5s   %-30s    %5s   %15s","Id", "Nombre y apellido", "Horas trabajadas", "Salario");
			break;
	}
}

/**
* \brief Imprime una fila vacia.
* \param int opcion - opcion que determina el formato de fila vacia que se va a imprimir
* \return retorna VOID
*/
void employee_ImprimirFilaVaciaDeDatos(int opcion)
{
	switch(opcion)
	{
		case MOSTRAR_ID_NOMBRE:
			printf("\n%5s   %-30s","-", "-");
			break;
		case MOSTRAR_TODOS_LOS_DATOS:
			printf("\n%5s   %-30s    %16s    %14s","-", "-", "-", "-");
			break;
	}
}

/**
* \brief Imprime los datos de un empleado
* \param Employee* empleado - puntero del empleado que se quiere imprimir
* \param int opcion - opcion que determina los datos que se quieren imprimir
* \return retorna INT. 0 si opero correctamente
* 	      retorna -1 si algun puntero apunta a NULL
* 	      retorna -37 si no se pudieron obtener todos los datos para imprimir la fila de datos
*/
int employee_ImprimirFilaDeDatos(Employee* this, int opcion)
{
	float sueldo;
	int id;
	int horasTrabajadas;
	char nombre[LEN_NOMBRE];
	int retorno = ERROR_PUNTERO_NULL;

	if(this != NULL)
	{
		retorno = ERROR_NO_SE_PUDO_IMPRIMIR;
		if(!employee_getHorasTrabajadas(this, &horasTrabajadas))
		{
			if(!employee_getId(this, &id))
			{
				if(!employee_getSueldo(this, &sueldo))
				{
					if(!employee_getNombre(this, nombre))
					{
						retorno = OPERACION_EXITOSA;
						switch(opcion)
						{
							case MOSTRAR_ID_NOMBRE:
								printf("\n%5d   %-30s ",id , nombre);
								break;
							case MOSTRAR_TODOS_LOS_DATOS:
								printf("\n%5d   %-30.30s    %16d    $%13f", id, nombre, horasTrabajadas, sueldo);
								break;
						}
					}
				}
			}
		}
	}
	return retorno;
}

int employee_imprimirUnSoloEmpleado(Employee* this)
{
	int retorno = ERROR_PUNTERO_NULL;
	if(this != NULL)
	{
		retorno = ERROR_NO_SE_PUDO_IMPRIMIR;
		employee_ImprimirEncabezadoDeDatos(MOSTRAR_TODOS_LOS_DATOS);
		if(!employee_ImprimirFilaDeDatos(this, MOSTRAR_TODOS_LOS_DATOS))
		{
			retorno = OPERACION_EXITOSA;
		}
	}
	return retorno;
}

///////////////////////////////////GETTERS Y SETTERS/////////////////////////////////////////////////////////

/**
* \brief setea el sueldo del employee
* \param Employee* pElemento - puntero al elemento employee
* \param float sueldo - sueldo que se quiere setear
* \return Retorna INT. Retorna 0 si seteo el dato correctamente
* 		  Retorna -1 si la direccion de memoria es NULL.
* 	      retorna -9 si el dato esta fuera de rango
*/
int employee_setSueldo(Employee* this, float sueldo)
{
	int retorno = ERROR_PUNTERO_NULL;
	if(this != NULL)
	{
		retorno = ERROR_DATO_FUERA_DE_RANGO;
		if(sueldo >= MINIMO_SALARIO && sueldo <= MAXIMO_SALARIO)
		{
			this->sueldo = sueldo;
			retorno = OPERACION_EXITOSA;
		}
	}
	return retorno;
}

/**
* \brief Obtiene el sueldo del employee
* \param Employee* pElemento - puntero al elemento employee
* \param int* sueldo - puntero (direccion de memoria) donde se guardara el tipo de employee
* \return Retorna INT. Retorna 0 si obtuvo el dato correctamente
* 		  Retorna -1 si la direccion de memoria es NULL.
*/
int employee_getSueldo(Employee* this, float* pSueldo)
{
	int retorno = ERROR_PUNTERO_NULL;
	if(this != NULL && pSueldo != NULL)
	{
		*pSueldo = this->sueldo;
		retorno = OPERACION_EXITOSA;
	}
	return retorno;
}

/**
* \brief setea las horas trabajadas del employee
* \param Employee* pElemento - puntero al elemento employee
* \param int horasTrabajadas - horas Trabajadas que se quiere setear
* \return Retorna INT. Retorna 0 si seteo el dato correctamente
* 		  Retorna -1 si la direccion de memoria es NULL.
* 	      retorna -9 si el dato esta fuera de rango
*/
int employee_setHorasTrabajadas(Employee* this, int horasTrabajadas)
{
	int retorno = ERROR_PUNTERO_NULL;
	if(this != NULL)
	{
		retorno = ERROR_DATO_FUERA_DE_RANGO;
		if(horasTrabajadas >= MINIMO_HORAS_TRABAJADAS && horasTrabajadas <= MAXIMO_HORAS_TRABAJADAS)
		{
			this->horasTrabajadas = horasTrabajadas;
			retorno = OPERACION_EXITOSA;
		}
	}
	return retorno;
}

/**
* \brief Obtiene las horas Trabajadas del employee
* \param Employee* pElemento - puntero al elemento employee
* \param int* horasTrabajadas - puntero (direccion de memoria) donde se guardara las horas Trabajadas del employee
* \return Retorna INT. Retorna 0 si obtuvo el dato correctamente
* 		  Retorna -1 si la direccion de memoria es NULL.
*/
int employee_getHorasTrabajadas(Employee* this, int* pHorasTrabajadas)
{
	int retorno = ERROR_PUNTERO_NULL;
	if(this != NULL && pHorasTrabajadas != NULL)
	{
		*pHorasTrabajadas = this->horasTrabajadas;
		retorno = OPERACION_EXITOSA;
	}
	return retorno;
}

/**
* \brief setea el id del employee
* \param Employee* pElemento - puntero al elemento employee
* \param int id - id que se seteara
* \return Retorna INT. Retorna 0 si seteo el dato correctamente
* 		  Retorna -1 si la direccion de memoria es NULL.
* 		  retorna -24 si el id es invalido
*/
int employee_setId(Employee* this, int id)
{
	int retorno = ERROR_PUNTERO_NULL;
	if(this != NULL)
	{
		retorno = ERROR_ID_INVALIDO;
		if(id > 0)
		{
			this->id = id;
			retorno = OPERACION_EXITOSA;
		}
	}
	return retorno;
}

/**
* \brief Obtiene el id del employee
* \param Employee* pElemento - puntero al elemento employee
* \param int* id - puntero (direccion de memoria) donde se guardara el id de employee
* \return Retorna INT. Retorna 0 si obtuvo el dato correctamente
* 		  Retorna -1 si la direccion de memoria es NULL.
*/
int employee_getId(Employee* this, int* pId)
{
	int retorno = ERROR_PUNTERO_NULL;
	if(this != NULL && pId != NULL)
	{
		*pId = this->id;
		retorno = OPERACION_EXITOSA;
	}
	return retorno;
}

/**
* \brief setea el nombre del employee
* \param Employee* pElemento - puntero al elemento employee
* \param char pNombre[] - nombre que se quiere setear
* \return Retorna INT. Retorna 0 si seteo el dato correctamente
* 		  Retorna -1 si la direccion de memoria es NULL.
* 	      retorna -11 si el dato es invalido y no se puede setear
*/
int employee_setNombre(Employee* this, char* pNombre)
{
	int lenCadena;
	char auxiliar[LEN_NOMBRE];
	int retorno = ERROR_PUNTERO_NULL;

	if(this != NULL && pNombre != NULL)
	{
		retorno = ERROR_DATO_INVALIDO;
		lenCadena = strnlen(pNombre, sizeof(auxiliar));
		if(lenCadena > 0)
		{
			strncpy(auxiliar, pNombre, sizeof(auxiliar));

			if(lenCadena == sizeof(auxiliar))
			{
				utn_cortarCadena(auxiliar, lenCadena);
			}

			if(validar_nombre(auxiliar, sizeof(auxiliar))==TRUE)
			{
				strncpy(this->nombre, auxiliar, sizeof(this->nombre));
				retorno = OPERACION_EXITOSA;
			}
		}
	}
	return retorno;
}

/**
* \brief Obtiene el nombre del employee
* \param Employee* pElemento - puntero al elemento employee
* \return Retorna INT. Retorna 0 si obtuvo el dato correctamente
* 		  Retorna -1 si la direccion de memoria es NULL.
* 		  Retorna -2 si hay el tam del array es invalido
*/
int employee_getNombre(Employee* this, char* pNombre)
{
	int lenCadena = sizeof(this->nombre);
	int retorno = ERROR_PUNTERO_NULL;
	if(this != NULL && pNombre != NULL)
	{
		strncpy(pNombre, this->nombre, lenCadena);
		retorno = OPERACION_EXITOSA;
	}
	return retorno;
}

/**
* \brief setea el id del employee
* \param Employee* pElemento - puntero al elemento employee
* \param char* pId - id que se quiere setear
* \return Retorna INT. Retorna 0 si seteo el dato correctamente
* 		  Retorna -1 si la direccion de memoria es NULL.
* 	      retorna -11 si el dato no se pudo cargar
* 		  retorna -24 si el id es invalido
*/
int employee_setIdTexto(Employee* pElemento, char* pId)
{
	int lenCadena;
	int auxiliarEntero;
	char cadenaAuxiliarEntero[LEN_INT];
	int retorno = ERROR_PUNTERO_NULL;
	if(pElemento != NULL && pId != NULL)
	{
		retorno = ERROR_DATO_INVALIDO;
		lenCadena = strnlen(pId, sizeof(cadenaAuxiliarEntero));
		if(lenCadena > 0)
		{
			strncpy(cadenaAuxiliarEntero, pId, sizeof(cadenaAuxiliarEntero));
			if(lenCadena == sizeof(cadenaAuxiliarEntero))
			{
				utn_cortarCadena(cadenaAuxiliarEntero, lenCadena);
			}

			if(validar_numeroEntero(cadenaAuxiliarEntero, sizeof(cadenaAuxiliarEntero)) == TRUE)
			{
				retorno = ERROR_ID_INVALIDO;
				auxiliarEntero = atoi(cadenaAuxiliarEntero);
				if(auxiliarEntero > 0)
				{
					pElemento->id = auxiliarEntero;
					retorno = OPERACION_EXITOSA;
				}
			}
		}
	}
	return retorno;
}

/**
* \brief setea las horas trabajadas del employee
* \param Employee* pElemento - puntero al elemento employee
* \param char* pHorasTrabajadas - Horas Trabajadas que se quiere setear
* \return Retorna INT. Retorna 0 si seteo el dato correctamente
* 		  Retorna -1 si la direccion de memoria es NULL.
* 		  retorna -9 si el dato esta fuera de rango
* 	      retorna -11 si el dato no se pudo cargar
*/
int employee_setHorasTrabajadasTexto(Employee* pElemento, char* pHorasTrabajadas)
{
	int lenCadena;
	int auxiliarEntero;
	char cadenaAuxiliarEntero[LEN_INT];
	int retorno = ERROR_PUNTERO_NULL;
	if(pElemento != NULL && pHorasTrabajadas != NULL)
	{
		retorno = ERROR_DATO_INVALIDO;
		lenCadena = strnlen(pHorasTrabajadas, sizeof(cadenaAuxiliarEntero));
		if(lenCadena > 0)
		{
			strncpy(cadenaAuxiliarEntero, pHorasTrabajadas, sizeof(cadenaAuxiliarEntero));
			if(lenCadena == sizeof(cadenaAuxiliarEntero))
			{
				utn_cortarCadena(cadenaAuxiliarEntero, lenCadena);
			}

			if(validar_numeroEntero(cadenaAuxiliarEntero, sizeof(cadenaAuxiliarEntero)) == TRUE)
			{
				retorno = ERROR_DATO_FUERA_DE_RANGO;
				auxiliarEntero = atoi(cadenaAuxiliarEntero);
				if(auxiliarEntero >= MINIMO_HORAS_TRABAJADAS && auxiliarEntero <=MAXIMO_HORAS_TRABAJADAS)
				{
					pElemento->horasTrabajadas = auxiliarEntero;
					retorno = OPERACION_EXITOSA;
				}
			}
		}
	}
	return retorno;
}

/**
* \brief setea el salario del employee
* \param Employee* pElemento - puntero al elemento employee
* \param char* pSalario - salario que se quiere setear
* \return Retorna INT. Retorna 0 si seteo el dato correctamente
* 		  Retorna -1 si la direccion de memoria es NULL.
* 		  retorna -9 si el dato esta fuera de rango
* 	      retorna -11 si el dato no se pudo cargar
*/
int employee_setSueldoTexto(Employee* pElemento, char* pSalario)
{
	int lenCadena;
	float auxiliarFloat;
	char cadenaAuxiliarFloat[LEN_FLOAT];
	int retorno = ERROR_PUNTERO_NULL;
	if(pElemento != NULL && pSalario != NULL)
	{
		retorno = ERROR_DATO_INVALIDO;
		lenCadena = strnlen(pSalario, sizeof(cadenaAuxiliarFloat));
		if(lenCadena > 0)
		{
			strncpy(cadenaAuxiliarFloat, pSalario, sizeof(cadenaAuxiliarFloat));
			if(lenCadena == sizeof(cadenaAuxiliarFloat))
			{
				utn_cortarCadena(cadenaAuxiliarFloat, lenCadena);
			}

			if(validar_numeroFloat(cadenaAuxiliarFloat, sizeof(cadenaAuxiliarFloat)) == TRUE)
			{
				retorno = ERROR_DATO_FUERA_DE_RANGO;
				auxiliarFloat = atof(cadenaAuxiliarFloat);
				if(auxiliarFloat >= MINIMO_SALARIO && auxiliarFloat <=MAXIMO_SALARIO)
				{
					pElemento->sueldo = auxiliarFloat;
					retorno = OPERACION_EXITOSA;
				}
			}
		}
	}
	return retorno;
}

///////////////////////////////////FUNCIONES DE ORDENAR/////////////////////////////////////////////////////////

/**
* \brief determina si un elemento es mayor que otro por el nombre
* \param void* pElementoUno - puntero a un empleado
* \param void* pElementoDos - puntero a un segundo empleado
* \return Retorna INT. Retorna 1 si el primer elemento es mayor que el segundo
* 	      retorna 0 si ambos elementos son iguales
* 		  Retorna -1 si el segundo elemento es mayor que el primero
* 		  retorna -10 si la direccion de memoria es NULL.
*/
int employee_orderByName(void* pElementoUno, void* pElementoDos)
{
	int respuesta;
	char cadenaUno[LEN_NOMBRE];
	char cadenaDos[LEN_NOMBRE];
	int retorno = ERROR_PUNTERO_NULL_AL_COMPARAR;
	if(pElementoUno != NULL && pElementoDos != NULL)
	{
		if(!employee_getNombre(pElementoUno, cadenaUno) &&
		   !employee_getNombre(pElementoDos, cadenaDos))
		{
			retorno = IGUALDAD;
			respuesta = strncmp(cadenaUno, cadenaDos, sizeof(cadenaUno));
			if(respuesta > 0)
			{
				retorno = PRIMERO_ES_MAYOR;
			}
			else
			{
				if(respuesta < 0)
				{
					retorno = SEGUNDO_ES_MAYOR;
				}
			}
		}
	}
	return retorno;
}

/**
* \brief determina si un elemento es mayor que otro por el id
* \param void* pElementoUno - puntero a un empleado
* \param void* pElementoDos - puntero a un segundo empleado
* \return Retorna INT. Retorna 1 si el primer elemento es mayor que el segundo
* 	      retorna 0 si ambos elementos son iguales
* 		  Retorna -1 si el segundo elemento es mayor que el primero
* 		  retorna -10 si la direccion de memoria es NULL.
*/
int employee_orderById(void* pElementoUno, void* pElementoDos)
{
	int idUno;
	int idDos;
	int retorno = ERROR_PUNTERO_NULL_AL_COMPARAR;
	if(pElementoUno != NULL && pElementoDos != NULL)
	{
		if(!employee_getId(pElementoUno, &idUno) &&
		   !employee_getId(pElementoDos, &idDos))
		{
			retorno = IGUALDAD;
			if(idUno > idDos)
			{
				retorno = PRIMERO_ES_MAYOR;
			}
			else
			{
				if(idDos > idUno)
				{
					retorno = SEGUNDO_ES_MAYOR;
				}
			}
		}
	}
	return retorno;
}

/**
* \brief determina si un elemento es mayor que otro por el salario
* \param void* pElementoUno - puntero a un empleado
* \param void* pElementoDos - puntero a un segundo empleado
* \return Retorna INT. Retorna 1 si el primer elemento es mayor que el segundo
* 	      retorna 0 si ambos elementos son iguales
* 		  Retorna -1 si el segundo elemento es mayor que el primero
* 		  retorna -10 si la direccion de memoria es NULL.
*/
int employee_orderBySalary(void* pElementoUno, void* pElementoDos)
{
	float salarioUno;
	float salarioDos;
	int retorno = ERROR_PUNTERO_NULL_AL_COMPARAR;
	if(pElementoUno != NULL && pElementoDos != NULL)
	{
		if(!employee_getSueldo(pElementoUno, &salarioUno) &&
		   !employee_getSueldo(pElementoDos, &salarioDos))
		{
			retorno = IGUALDAD;
			if(salarioUno > salarioDos)
			{
				retorno = PRIMERO_ES_MAYOR;
			}
			else
			{
				if(salarioDos > salarioUno)
				{
					retorno = SEGUNDO_ES_MAYOR;
				}
			}
		}
	}
	return retorno;
}

/**
* \brief determina si un elemento es mayor que otro por las horas trabajadas
* \param void* pElementoUno - puntero a un empleado
* \param void* pElementoDos - puntero a un segundo empleado
* \return Retorna INT. Retorna 1 si el primer elemento es mayor que el segundo
* 	      retorna 0 si ambos elementos son iguales
* 		  Retorna -1 si el segundo elemento es mayor que el primero
* 		  retorna -10 si la direccion de memoria es NULL.
*/
int employee_orderByHoursWorked(void* pElementoUno, void* pElementoDos)
{
	int horasTrabajadasUno;
	int horasTrabajadasDos;
	int retorno = ERROR_PUNTERO_NULL_AL_COMPARAR;
	if(pElementoUno != NULL && pElementoDos != NULL)
	{
		if(!employee_getHorasTrabajadas(pElementoUno, &horasTrabajadasUno) &&
		   !employee_getHorasTrabajadas(pElementoDos, &horasTrabajadasDos))
		{
			retorno = IGUALDAD;
			if(horasTrabajadasUno > horasTrabajadasDos)
			{
				retorno = PRIMERO_ES_MAYOR;
			}
			else
			{
				if(horasTrabajadasDos > horasTrabajadasUno)
				{
					retorno = SEGUNDO_ES_MAYOR;
				}
			}
		}
	}
	return retorno;
}

/**
* \brief Obtiene el nodo en el que se encuentra un empleado segun su id
* \param LinkedList* pArrayListEmployee - puntero a lista de empleados
* \param int id - id del empleado
* \return Retorna INT. Retorna 0 o positivo, que es el indice del empleado
* 		  Retorna -1 si el segundo elemento es mayor que el primero
* 		  retorna -32 si no se encontraron datos asociados al id
*/
int employee_findEmployeeById(LinkedList* pArrayListEmployee, int id)
{
	int i;
	int len;
	int idObtenido;
	Employee* pAuxiliar;
	int retorno = ERROR_PUNTERO_NULL;
	if(pArrayListEmployee != NULL)
	{
		retorno =  ERROR_NO_SE_ENCONTRARON_DATOS_ASOCIADOS_AL_ID;
		len = ll_len(pArrayListEmployee);
		for(i = 0; i < len; i++)
		{
			pAuxiliar = (Employee*)ll_get(pArrayListEmployee, i);
			if(pAuxiliar != NULL)
			{
				if(!employee_getId(pAuxiliar, &idObtenido))
				{
					if(idObtenido == id)
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

/**
* \brief Obtiene el puntero en el que se encuentra un empleado segun su id
* \param LinkedList* pArrayListEmployee - puntero a lista de empleados
* \param int id - id del empleado
* \return Retorna Employee*. Retorna la direccion de memoria del empleado,
*                 o NULL si no lo encontro o hubo un error.
*/
Employee* employee_findPointerToEmployeeById(LinkedList* pArrayListEmployee, int id)
{
	int i;
	int len;
	int idObtenido;
	Employee* pAuxiliar;
	Employee* retorno = NULL;
	if(pArrayListEmployee != NULL)
	{
		len = ll_len(pArrayListEmployee);
		for(i = 0; i < len; i++)
		{
			pAuxiliar = (Employee*)ll_get(pArrayListEmployee, i);
			if(pAuxiliar != NULL)
			{
				if(!employee_getId(pAuxiliar, &idObtenido))
				{
					if(idObtenido == id)
					{
						retorno = pAuxiliar;
						break;
					}
				}
			}
		}
	}
	return retorno;
}

/**
* \brief Obtiene los datos de un empleado
* \param char nombre [] - nombre del empleado
* \param int lenNombre - len del array nombre
* \param int* pHorasTrabajadas - puntero a variable horas trabajadas
* \param float* pSalario - puntero a variable salario
* \return Retorna Int. Retorna -1 si alguno de los punteros es NULL o
*                  	   Retorna el estado de la ultima operacion realizada de toma de datos,
*                  	   Si el retorno es 0, opero correctamente. Si es negativo, ocurrio un error.
*/
int employee_getDataToAddANewEmployee(char nombre[], int lenNombre, int* pHorasTrabajadas, float* pSalario)
{
	int estadoOperacion;
	int retorno = ERROR_PUNTERO_NULL;
	if(nombre != NULL && pHorasTrabajadas != NULL && pSalario != NULL)
	{
		estadoOperacion = utn_getNombreOApellido(nombre, lenNombre, "\nIngrese el nombre completo", "\nError. Dato invalido", REINTENTOS);
		if(utn_comprobarEstadoDeOperacion(estadoOperacion))
		{
			estadoOperacion = utn_getInt(pHorasTrabajadas, "Ingrese las horas trabajadas (1 - 500)", "Error. Dato invalido", MINIMO_HORAS_TRABAJADAS, MAXIMO_HORAS_TRABAJADAS, REINTENTOS);
			if(utn_comprobarEstadoDeOperacion(estadoOperacion))
			{
				estadoOperacion = utn_getFloat(pSalario, "Ingrese el salario $(1 - 500000)", "Error. Dato invalido", MINIMO_SALARIO, MAXIMO_SALARIO, REINTENTOS);
				utn_comprobarEstadoDeOperacion(estadoOperacion);
			}
		}
		retorno = estadoOperacion;
	}
	return retorno;
}

/** \brief Obtiene los datos de un empleado, y los carga en variables.
 * \param  Employee* pEmpleado - puntero al empleado
 * \param  int* pId - puntero a variable que espera guardar el id
 * \param  int* pHorasTrabajadas - puntero a variable que espera guardar las horas trabajadas
 * \param  char* nombre - puntero a variable que espera guardar el nombre
 * \param  float *pSalario - puntero a variable que espera guardar el salario
 * \return int. Retorna 0 si la Operacion es exitosa
 * 				retorna -1 si el puntero apunta a NULL.
 * 				retorna -38 si no se pudieron obtener todos los datos
 */
int employee_gettersFromEmployee(Employee* pEmpleado, int* pId, int* pHorasTrabajadas, char* nombre, float *pSalario)
{
	int retorno = ERROR_PUNTERO_NULL;
	if(pEmpleado != NULL && pId != NULL && pHorasTrabajadas != NULL && nombre != NULL && pSalario != NULL)
	{
		retorno = ERROR_NO_SE_PUDIERON_OBTENER_TODOS_LOS_DATOS;
		if(!employee_getNombre(pEmpleado, nombre) &&
		   !employee_getId(pEmpleado, pId) &&
		   !employee_getHorasTrabajadas(pEmpleado, pHorasTrabajadas) &&
		   !employee_getSueldo(pEmpleado, pSalario))
		{
			retorno = OPERACION_EXITOSA;
		}
	}
	return retorno;
}

/** \brief obtiene el ultimo ID o el proximo, segun el parametro recibido
* \param  int opcion - opcion que determina si se obtiene el ultimo ID (1) o el proximo ID (2)
* \return int. Retorna 0 o positivo, que es el ID obtenido o
* 			   retorna -49 si hay un error y no se pudo guardar ultimo ID en archivo de Ids.
* 			   retorna -50 si hay un error general.
*/
int employee_getLastOrNextId(int opcion)
{
	int estadoOperacion;
	int auxiliarUltimoId;
	static int banderaPrimerIngreso = SIN_INGRESOS;
	static int ultimoIdActual = 0;
	char pathArchivoTexto [LEN_ARCHIVO] = "data.csv";
	char pathArchivoUltimoId [LEN_ARCHIVO] = "ArchivoUltimoId.csv";
	int retorno = ERROR;

	if(!banderaPrimerIngreso)
	{
		banderaPrimerIngreso = PRIMER_INGRESO_OK;
		estadoOperacion = employee_abrirArchivoConUltimoId(pathArchivoUltimoId, &auxiliarUltimoId);
		if(estadoOperacion)//Si no encontro el archivo "ArchivoUltimoId.csv" (no existe), entro al IF
		{
			banderaPrimerIngreso = NO_SE_ENCONTRO_ARCHIVO_DE_ID;
			estadoOperacion = employee_buscarUltimoId(pathArchivoTexto, &auxiliarUltimoId);
			if(estadoOperacion)//Si tambien FALLO la busqueda del mayor ID en el archivo "data.csv", entro al IF
			{
				//Aca es el peor caso, fallaron todas las opciones que me obtienen el ID mayor,
				//entonces como ultimo recurso Hardcodeo el ultimo Id a 1000.
				auxiliarUltimoId = 1000;
			}
		}
		ultimoIdActual = auxiliarUltimoId;
	}

	switch(opcion)
	{
		case OBTENER_ACTUAL_ULTIMO_ID:
			retorno = ultimoIdActual;
			break;
		case OBTENER_NUEVO_ULTIMO_ID:
			ultimoIdActual++;
			break;
	}

	if(banderaPrimerIngreso == NO_SE_ENCONTRO_ARCHIVO_DE_ID || opcion == OBTENER_NUEVO_ULTIMO_ID)
	{
		retorno = ERROR_NO_SE_PUDO_GUARDAR_ULTIMO_ID_EN_ARCHIVO;
		if(!employee_guardarUltimoIdEnArchivo(pathArchivoUltimoId, ultimoIdActual))
		{
			banderaPrimerIngreso = ARCHIVO_ID_CREADO_O_ACTUALIZADO;
			retorno = ultimoIdActual;
		}
	}
	return retorno;
}

/** \brief abre el archivo que contiene el ultimo ID
* \param  char* pathArchivoUltimoId - ruta absoluta o relativa del archivo
* \param  int* pUltimoId - puntero a variable que espera guardar el ultimo id
* \return int. Retorna 0 si opero exitosamente
* 			   retorna -50 si hay un error.
*/
static int employee_abrirArchivoConUltimoId(char* pathArchivoUltimoId, int* pUltimoId)
{
	FILE* fpArchivoId;
	int auxiliarUltimoIdEntero;
	char auxiliarUltimoIdChar[LEN_INT];
	int retorno = ERROR;
	if(pathArchivoUltimoId != NULL && pUltimoId != NULL)
	{
		fpArchivoId = fopen(pathArchivoUltimoId, "r");
		if(fpArchivoId != NULL)
		{
			if(fscanf(fpArchivoId, "%[^\n]\n", auxiliarUltimoIdChar) == 1)
			{
				if(validar_numeroEntero(auxiliarUltimoIdChar, sizeof(auxiliarUltimoIdChar)) == TRUE)
				{
					auxiliarUltimoIdEntero = atoi(auxiliarUltimoIdChar);
					if(auxiliarUltimoIdEntero >= 0)
					{
						*pUltimoId = auxiliarUltimoIdEntero;
						retorno = OPERACION_EXITOSA;
					}
				}
			}
			fclose(fpArchivoId);
		}
	}
	return retorno;
}

/** \brief Busca el ID mas grande en el Archivo con la lista de datos, y lo guarda en el puntero pUltimoId
* \param  char* pPathListado - ruta absoluta o relativa del archivo donde buscara el id mas grande.
* \param  int* pUltimoId - puntero a variable que espera guardar el ultimo id
* \return int. Retorna 0 si opero exitosamente o
* 			   retorna -50 si hay un error.
*/
static int employee_buscarUltimoId(char* pPathListado, int* pUltimoId)
{
	int idEntero;
	int idMasGrande;
	FILE* fpAuxiliar;
	char idTexto[LEN_INT];
	char texto[LEN_TEXTO];
	int banderaPrimerIngreso = 0;
	int retorno = ERROR;

	if(pPathListado != NULL && pUltimoId != NULL)
	{
		fpAuxiliar = fopen(pPathListado, "r");
		if(fpAuxiliar != NULL)
		{
			do
			{
				if(fscanf(fpAuxiliar,"%[^,],%[^\n]\n", idTexto, texto) == 2)
				{
					if(validar_numeroEntero(idTexto, sizeof(idTexto)) == TRUE)
					{
						idEntero = atoi(idTexto);
						if(banderaPrimerIngreso == 0 || idEntero > idMasGrande)
						{
							idMasGrande = idEntero;
							banderaPrimerIngreso = 1;
						}
					}
				}

			}while(!feof(fpAuxiliar));
			fclose(fpAuxiliar);
			if(banderaPrimerIngreso)
			{
				*pUltimoId = idMasGrande;
				retorno = OPERACION_EXITOSA;
			}
		}
	}
	return retorno;
}

/** \brief guarda el ultimo ID en el archivo de IDs
* \param  char* pPathArchivoId - ruta absoluta o relativa del archivo.
* \param  int ultimoId - ultimo id hasta el momento
* \return int. Retorna 0 si opero exitosamente
* 			   retorna -50 si hay un error.
*/
static int employee_guardarUltimoIdEnArchivo(char* pPathArchivoId, int ultimoId)
{
	FILE* fpArchivoId;
	int retorno = ERROR;
	if(pPathArchivoId != NULL)
	{
		fpArchivoId = fopen(pPathArchivoId, "w");
		if(fpArchivoId != NULL)
		{
			fprintf(fpArchivoId, "%d\n", ultimoId);
			fclose(fpArchivoId);
			retorno = OPERACION_EXITOSA;
		}
	}
	return retorno;
}
