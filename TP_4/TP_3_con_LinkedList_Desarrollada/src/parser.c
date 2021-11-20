#include "parser.h"

#define ARCHIVO_VACIO_O_TERMINADO 1
#define LEN_NOMBRE 128
#define LEN_INT 10
#define LEN_FLOAT 20
#define OPERACION_EXITOSA 0
#define ERROR_PUNTERO_NULL -1
#define ERROR_NO_SE_PUDIERON_OBTENER_TODOS_LOS_DATOS -38
#define ERROR_NO_PUDO_CARGAR_EMPLEADO_A_LA_LISTA -41
#define ERROR_DATOS_INVALIDOS -43

/** \brief Parsea los datos de los empleados desde el archivo data.csv (modo texto).
 * \param FILE* pFile - puntero al archivo de texto
 * \param  LinkedList* pArrayListEmployee - puntero a la lista de empleados
 * \return int. Retorna 0 si la Operacion es exitosa
 * 				retorna 1 si es fin del archivo
 * 				retorna -1 si el puntero apunta a NULL.
 * 				retorna -41 si no se puede cargar empleado a la lista
 * 				retorna -43 si se detectan datos invalidos
 *
 */
int parser_EmployeeFromText(FILE* pFile, LinkedList* pArrayListEmployee)
{
	char id [LEN_INT];
	char horas [LEN_INT];
	char salario [LEN_FLOAT];
	char nombre [LEN_NOMBRE];
	Employee* pEmpleado;
	int retorno = ERROR_PUNTERO_NULL;

	if(pFile != NULL && pArrayListEmployee != NULL)
	{
		retorno = ARCHIVO_VACIO_O_TERMINADO;
		if(fscanf(pFile,"%[^,],%[^,],%[^,],%[^\n]\n", id, nombre, horas, salario) == 4)
		{
			retorno = ERROR_DATOS_INVALIDOS;
			pEmpleado = employee_newParametros(id, nombre, horas, salario);
			if(pEmpleado != NULL)
			{
				retorno = ERROR_NO_PUDO_CARGAR_EMPLEADO_A_LA_LISTA;
				if(!ll_add(pArrayListEmployee, pEmpleado))
				{
					retorno = OPERACION_EXITOSA;
				}
			}
		}
	}
    return retorno;
}

/** \brief Parsea los datos de los empleados desde el archivo data.csv (modo binario).
 * \param FILE* pFile - puntero al archivo binario
 * \param  LinkedList* pArrayListEmployee - puntero a la lista de empleados
 * \return int. Retorna 0 si la Operacion es exitosa
 * 				retorna 1 si es fin del archivo
 * 				retorna -1 si el puntero apunta a NULL.
 * 				retorna -38 si no se pudieron obtener todos los datos
 * 				retorna -41 si no se puede cargar empleado a la lista
 * 				retorna -43 si se detectan datos invalidos
 */
int parser_EmployeeFromBinary(FILE* pFile, LinkedList* pArrayListEmployee)
{
	int id;
	float salario;
	int horasTrabajadas;
	char nombre[LEN_NOMBRE];
	Employee* pEmpleado;
	int retorno = ERROR_PUNTERO_NULL;

	if(pFile != NULL && pArrayListEmployee != NULL)
	{
		retorno = ARCHIVO_VACIO_O_TERMINADO;
		if(fread(&id, sizeof(int), 1, pFile) == 1 &&
		   fread(nombre, sizeof(nombre), 1, pFile) == 1 &&
		   fread(&horasTrabajadas, sizeof(int), 1, pFile) == 1 &&
		   fread(&salario, sizeof(float), 1, pFile) == 1)
		{
			retorno = ERROR_DATOS_INVALIDOS;
			pEmpleado = employee_newParametrosDiferenciandoTiposDeDatos(id, nombre, salario, horasTrabajadas);
			if(pEmpleado != NULL)
			{
				retorno = ERROR_NO_PUDO_CARGAR_EMPLEADO_A_LA_LISTA;
				if(!ll_add(pArrayListEmployee, pEmpleado))
				{
					retorno = OPERACION_EXITOSA;
				}
			}
		}
	}
    return retorno;
}

/** \brief Carga los datos de un empleado desde la lista al archivo de texto.
 * \param FILE* pFile - puntero al archivo de texto
 * \param  Employee* pEmpleado - puntero al empleado
 * \return int. Retorna 0 si la Operacion es exitosa
 * 				retorna -1 si el puntero apunta a NULL.
 * 				retorna -38 si no se pudieron obtener todos los datos
 */
int parser_TextFromEmployee(FILE* pFile, Employee* pEmpleado)
{
	int id;
	float salario;
	int horasTrabajadas;
	char nombre[LEN_NOMBRE];
	int retorno = ERROR_PUNTERO_NULL;

	if(pEmpleado != NULL && pFile != NULL)
	{
		retorno = ERROR_NO_SE_PUDIERON_OBTENER_TODOS_LOS_DATOS;
		if(!employee_gettersFromEmployee(pEmpleado, &id, &horasTrabajadas, nombre, &salario))
		{
			fprintf(pFile,"%d,%s,%d,%f\n",id, nombre, horasTrabajadas, salario);
			retorno = OPERACION_EXITOSA;
		}
	}
	return retorno;
}


/** \brief Carga los datos de un empleado desde la lista al archivo Binario.
 * \param FILE* pFile - puntero al archivo de texto
 * \param  Employee* pEmpleado - puntero al empleado
 * \return int. Retorna 0 si la Operacion es exitosa
 * 				retorna -1 si el puntero apunta a NULL.
 * 				retorna -38 si no se pudieron obtener todos los datos
 */
int parser_BinaryFromEmployee(FILE* pFile, Employee* pEmpleado)
{
	int id;
	float salario;
	int horasTrabajadas;
	char nombre[LEN_NOMBRE];
	int retorno = ERROR_PUNTERO_NULL;

	if(pEmpleado != NULL && pFile != NULL)
	{
		retorno = ERROR_NO_SE_PUDIERON_OBTENER_TODOS_LOS_DATOS;
		if(!employee_gettersFromEmployee(pEmpleado, &id, &horasTrabajadas, nombre, &salario))
		{
			if(fwrite(&id, sizeof(int), 1, pFile) == 1 &&
			   fwrite(nombre, sizeof(nombre), 1, pFile) == 1 &&
			   fwrite(&horasTrabajadas, sizeof(int), 1, pFile) == 1 &&
			   fwrite(&salario, sizeof(float), 1, pFile) == 1)
			{
				retorno = OPERACION_EXITOSA;
			}
		}
	}
	return retorno;
}
