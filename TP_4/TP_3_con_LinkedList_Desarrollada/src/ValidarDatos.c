/*
 * ValidarDatos.c
 *
 *  Created on: 3 nov 2021
 *      Author: GONZALO
 */

#include "ValidarDatos.h"

#define LEN_TEXTO 150
#define LEN_NOMBRE 128
#define LEN_DIRECCION 51
#define LEN_ALFANUMERICO 51
#define LEN_NOMBRE_ALFANUMERICO 51
#define LEN_TEXTO_CUIT 15
#define LEN_CUIT 13
#define LEN_BUFFER_FLOAT 10
#define LEN_BUFFER_INT 10
#define TRUE 1
#define FALSE 0
#define OPERACION_EXITOSA 0
#define ERROR_PUNTERO_NULL -1
#define ERROR_LEN_INVALIDO -2
#define ERROR_PARAMETRO_I_ES_IGUAL_A_J -5
#define ERROR_PARAMETRO_I_O_J_FUERA_DE_RANGO -6
#define ERROR_FUNCION_INTERNA_FALLO -20
#define ERROR_NO_SE_INGRESARON_CARACTERES_O_SE_PERDIO_FIN_DE_CADENA -22

static int esSigno(char caracter);
static int esNumero(char caracter);
static int esLetra(char caracter);
static int esNumeroEntero(char cadena[], int largo);
static int esNumeroFloat(char cadena[], int largo);
static int esNombreOApellido(char cadena[], int largo);
static int swapCaracteres(char plistaCaracteres[], int i, int j);
static int darFormatoMayusculaMinuscula(char pNombre[], int len);
static int borrarEspacios(char pCadena[], int len);
static int cambiarTabsPorEspacios(char pCadena[], int len);
static int borrarEspaciosIzquierda(char pCadena[], int len, int indiceInicial);
static int borrarEspaciosExtrasIntermedios(char pCadena[], int len);
static int borrarEspaciosFinales(char pCadena[], int len);
static int esDireccion(char pCadena[], int len);
static int esCaracterValidoParaDireccion(char caracter);
static int esCaracterAlfanumerico(char caracter);
static int esCuit(char pCadena[], int len);
static int esAlfanumerico(char pCadena[], int len);
static int convertirUnCaracterEnMayuscula(char* pCaracter);
static int esNombreAlfanumerico(char pCadena[], int len);

/**
* \brief Evalua si el caracter recibido por parametro corresponde a un numero o no.
* \param char caracter - Caracter recibido para evaluar.
* \return retorna un INT, 1 (para verdadero) si el caracter corresponde a un numero.
*         retorna 0 (para falso) si el caracter NO corresponde a un numero.
*/
static int esNumero (char caracter)
{
	int retorno = TRUE;

	if(caracter < 48 || caracter > 57) //48 ASCII para el caracter '0' y 57 para '9'
	{
		retorno = FALSE;
	}
	return retorno;
}

/**
* \brief Evalua si el caracter recibido por parametro corresponde a un signo ('+' o '-') o no.
* \param char caracter - Caracter recibido para evaluar.
* \return retorna un INT, 1 (para verdadero) si el caracter corresponde a un signo ('+' o '-').
*         retorna 0 (para falso) si el caracter NO corresponde a un signo.
*/
static int esSigno (char caracter)
{
	int retorno = TRUE;

	if(caracter != 43 && caracter != 45) //43 ASCII para el caracter '+' y 45 para '-'
	{
		retorno = FALSE;
	}
	return retorno;
}

/**
* \brief Evalua si el caracter recibido por parametro corresponde a una letra o no.
* \param char caracter - Caracter recibido para evaluar.
* \return retorna un INT, 1 (para verdadero) si el caracter corresponde a una letra.
*         retorna 0 (para falso) si el caracter NO corresponde a una letra.
*/
static int esLetra (char caracter)
{
	int retorno = TRUE; //Asumo que es letra. 1 para verdadero

	if((caracter > 122 || caracter < 97) && (caracter > 90 || caracter < 65))
	{
		retorno = FALSE; //0 para Falso. No es una letra
	}
	return retorno;
}

/**
* \brief Verifica si un caracter es un caracter alfanumerico.
* \param char caracter - caracter que se evaluara
* \return retorna INT. 1 si el caracter es valido
*         retorna  0 es si el caracter no es valido
*/
static int esCaracterAlfanumerico(char caracter)
{
	int retorno = TRUE;

	if(esLetra(caracter) == FALSE && esNumero(caracter) == FALSE)
	{
		return FALSE;
	}
	return retorno;
}

/**
* \brief Verifica si un caracter es un caracter valido para una direccion.
* \param char caracter - caracter que se evaluara
* \return retorna INT. 1 si el caracter es valido
*         retorna  0 es si el caracter no es valido
*/
static int esCaracterValidoParaDireccion(char caracter)
{
	int retorno = TRUE;

	if(caracter != '.' && caracter != ',' && caracter != ' ')
	{
		return FALSE;
	}
	return retorno;
}

/**
* \brief Verifica si una cadena representa una direccion VALIDA (numeros, letras y algunos caracteres permitidos).
* \param char pCadena [] - Cadena que se evaluara, para determinar si es una direccion valida.
* \param int largo - Largo del array de caracteres.
* \return retorna INT. 1 si el dato es valido
*         retorna  0 es si el dato no es valido
*         retorna -1 si el puntero apunta a NULL
*         retorna -2 si el len es invalido
*         retorna -22 si no se ingresaron caracteres o la cadena perdio el '\0'
*/
static int esDireccion(char pCadena[], int len)
{
	int i;
	int largo;
	int retorno = ERROR_PUNTERO_NULL;

	if(pCadena != NULL)
	{
		retorno = ERROR_LEN_INVALIDO;
		if(len >0)
		{
			largo = strnlen(pCadena, len);
			retorno = ERROR_NO_SE_INGRESARON_CARACTERES_O_SE_PERDIO_FIN_DE_CADENA;
			if(largo > 0 && largo < len)
			{
				retorno = TRUE;
				for(i = 0; i < largo ; i++)
				{
					if(esLetra(pCadena[i]) == FALSE && esCaracterValidoParaDireccion(pCadena[i]) == FALSE && esNumero(pCadena[i]) == FALSE)
					{
						retorno = FALSE;
					}
				}
			}
		}
	}
	return retorno;
}

/**
* \brief Evalua si el caracter recibido por parametro corresponde a una letra o un numero.
* \param char pCadena [] - Cadena que se evaluara para determinar si es alfanumerico.
* \param int largo - Largo del array recibido por parametro.
* \return retorna un INT, 1 (para verdadero) si el caracter corresponde a una letra o numero.
*         retorna 0 (para falso) si el caracter NO corresponde a una letra ni un numero.
*         retorna -1 si el puntero apunta a NULL
*         retorna -2 si el len es invalido
*         retorna -22 si no se ingresaron caracteres  o la cadena perdio el '\0'
*/
static int esAlfanumerico(char pCadena[], int len)
{
	int i;
	int largo;
	int retorno = ERROR_PUNTERO_NULL;

	if(pCadena != NULL)
	{
		retorno = ERROR_LEN_INVALIDO;
		if(len > 0)
		{
			largo = strnlen(pCadena, len);
			retorno = ERROR_NO_SE_INGRESARON_CARACTERES_O_SE_PERDIO_FIN_DE_CADENA;
			if(largo >0 && largo < len)
			{
				retorno = TRUE;
				for(i = 0; i < largo; i++)
				{
					if(esCaracterAlfanumerico(pCadena[i])==FALSE)
					{
						retorno = FALSE;
						break;
					}
				}
			}
		}
	}
	return retorno;
}

/**
* \brief Evalua si la cadena de texto recibida representa un CUIT
* \param char pCadena[] - Direccion de memoria de la variable que almacena el CUIT.
* \param int largo - Largo de la cadena de caracteres.
* \return retorna INT. 1 si es CUIL
* 		  retorna 0 si NO es CUIL
*         retorna -1 si el puntero apunta a NULL
*         retorna -2 si el len es invalido
*         retorna -22 si no se ingresaron caracteres
*/
static int esCuit(char pCadena[], int len)
{
	int i;
	int retorno = ERROR_PUNTERO_NULL;
	int largo;
	if(pCadena != NULL)
	{
		retorno = ERROR_LEN_INVALIDO;
		if(len >= LEN_TEXTO_CUIT)
		{
			retorno = FALSE;
			largo = strnlen(pCadena, len);
			if(largo == LEN_CUIT)
			{
				retorno = TRUE;
				for(i = 0; i < largo; i ++)
				{
					//En posicion 2 y 11 va un guion medio '-'
					if((i != 2 && i != 11 && esNumero(pCadena[i])==FALSE) || ((i == 2 || i == 11) && pCadena[i] != 45))
					{
						retorno = FALSE;
						break;
					}
				}
			}
		}
	}
	return retorno;
}

/**
* \brief Verifica si una cadena representa un numero ENTERO VALIDO.
* \param char pCadena [] - Cadena que se evaluara, para determinar si contiene un ENTERO valido.
* \param int largo - Largo del array recibido por parametro.
* \return retorna INT. 1 si el dato es Entero
*         retorna  0 es si el dato es invalido
*         retorna -1 si el puntero apunta a NULL
*         retorna -2 si el len es invalido
*         retorna -22 si no se ingresaron caracteres o la cadena perdio el '\0'
*/
static int esNumeroEntero (char pCadena [], int len)
{
	int longitudActual;
	int i=0;
	int retorno = ERROR_PUNTERO_NULL;

	if(pCadena != NULL)
	{
		retorno = ERROR_LEN_INVALIDO;
		if(len > 0 && len <= LEN_BUFFER_INT)
		{
			retorno = ERROR_NO_SE_INGRESARON_CARACTERES_O_SE_PERDIO_FIN_DE_CADENA; //Dato invalido (no tiene caracteres).
			longitudActual = strnlen(pCadena, len); //No cuenta el \0

			//mygets() borra el ENTER, por lo que si el ENTER fue la unica
			//tecla apretada, entonces la cadena tiene un largo actual de 0 (seria un error).
			if(longitudActual > 0 && longitudActual < len)
			{
				retorno = TRUE;

				//Si el indice 0 es un signo, entonces la cadena debe tener mas de 1 elemento.
				//La cadena no puede tener un unico elemento, y ese unico elemento ser un signo.
				if(esSigno(pCadena[0]) == TRUE && longitudActual > 1)
				{
					i++;
				}

				for(	; i < longitudActual; i++)
				{
					if(esNumero(pCadena[i]) == FALSE)
					{
						retorno = FALSE;//Dato invalido, no es numero.
						break;
					}
				}
			}
		}
	}
	return retorno;
}

/**
* \brief Verifica si una cadena representa un numero FLOAT VALIDO.
* \param char pCadena [] - Cadena que se evaluara, para determinar si contiene un FLOAT valido.
* \param int largo - Largo del array recibido por parametro.
* \return retorna INT. 1 si el dato es FLOAT
*         retorna  0 es si el dato es invalido
*         retorna -1 si el puntero apunta a NULL
*         retorna -2 si el len es invalido
*         retorna -22 si no se ingresaron caracteres o la cadena perdio el '\0'
*/
static int esNumeroFloat (char pCadena [], int len)
{
	int longitudActual;
	int i=0;
	int contadorPuntos = 0;
	int retorno = ERROR_PUNTERO_NULL;

	if(pCadena != NULL)
	{
		retorno = ERROR_LEN_INVALIDO;
		if(len > 0 && len <= LEN_BUFFER_FLOAT)
		{
			retorno = ERROR_NO_SE_INGRESARON_CARACTERES_O_SE_PERDIO_FIN_DE_CADENA; //Dato invalido (no tiene caracteres).
			longitudActual = strnlen(pCadena, len);
			//mygets() borra el ENTER, por lo que si el ENTER fue la unica
			//tecla apretada, entonces la cadena tiene un largo actual de 0 (seria un error).
			//Por otro lado, si la longitud actual es igual al len, entonces se perdio el '\0'
			if(longitudActual > 0 && longitudActual < len)
			{
				retorno = TRUE; //todo OK.

				//Para validar un signo '-' o '+', la longitud debe ser necesariamente mayor a 1.
				//Esto es porque el signo ocupa 1 caracter, por lo que la cadena NO PUEDE TENER
				//ESE UNICO CARACTER, debe tener por lo menos 2 (1 ocupado por el signo, y el otro por un digito).
				if(esSigno(pCadena[0]) == 1 && longitudActual > 1 )
				{
					i++;
				}

				for(	;i < longitudActual; i++)
				{
					if(esNumero(pCadena[i]) == FALSE)
					{
						if(pCadena[i] == 46 && contadorPuntos == 0)//46 para '.'
						{
							contadorPuntos++;
						}
						else
						{
							retorno = FALSE; //Dato invalido.
							break;
						}
					}
				}
			}
		}
	}
	return retorno;
}

/**
* \brief Obtiene una cadena y verifica si es un nombre o un apellido valido.
* \param char pCadena[] - array de tipo CHAR a evaluar.
* \param int largo - Largo del array de caracteres recibido.
* \return retorna INT. 1 si el dato es valido.
*         retorna  0 si el dato es invalido
*         retorna -1 si el puntero apunta a NULL
*         retorna -2 si el len es invalido
*         retorna -22 si no se ingresaron caracteres o la cadena perdio el '\0'
*/
static int esNombreOApellido (char pCadena[], int len)
{
	int i;
	int longitudActual;
	int retorno = ERROR_PUNTERO_NULL;

	if(pCadena != NULL)
	{
		retorno = ERROR_LEN_INVALIDO;
		if(len > 0)
		{
			retorno = ERROR_NO_SE_INGRESARON_CARACTERES_O_SE_PERDIO_FIN_DE_CADENA;
			longitudActual = strnlen(pCadena, len);
			//mygets() borra el ENTER, por lo que si el ENTER fue la unica
			//tecla apretada, entonces la cadena tiene un largo actual de 0 (seria un error).
			if(longitudActual > 0 && longitudActual < len)
			{
				retorno = TRUE;//Asumo que esta todo OK.

				for(i = 0; i < longitudActual; i++)
				{
					//Si no es letra, ni un espacio en blanco (validado) es un caracter INVALIDO.
					if(esLetra(pCadena[i]) == FALSE && pCadena[i] != 32)
					{
						retorno = FALSE;
						break;
					}
				}
			}
		}
	}
	return retorno;
}

/**
* \brief Verifica si una cadena representa un nombre Alfanumerico VALIDO (numeros, letras y espacios).
* \param char pCadena [] - Cadena que se evaluara, para determinar si es una cadena alfanumerica valida.
* \param int largo - Largo del array de caracteres.
* \return retorna INT. 1 si el dato es valido
*         retorna  0 es si el dato no es valido
*         retorna -1 si el puntero apunta a NULL
*         retorna -2 si el len es invalido
*         retorna -22 si no se ingresaron caracteres o la cadena perdio el '\0'
*/
static int esNombreAlfanumerico(char pCadena[], int len)
{
	int i;
	int largo;
	int retorno = ERROR_PUNTERO_NULL;

	if(pCadena != NULL)
	{
		retorno = ERROR_LEN_INVALIDO;
		if(len >0)
		{
			retorno = ERROR_NO_SE_INGRESARON_CARACTERES_O_SE_PERDIO_FIN_DE_CADENA;
			largo = strnlen(pCadena, len);
			if(largo > 0 && largo < len)
			{
				retorno = TRUE;
				for(i = 0; i < largo ; i++)
				{
					if(esLetra(pCadena[i]) == FALSE && pCadena[i] != 32 && esNumero(pCadena[i]) == FALSE)
					{
						retorno = FALSE;
					}
				}
			}
		}
	}
	return retorno;
}

/**
* \brief Recibe un caracter ya validado como letra, y lo convierte en mayuscula
* \param char* pCaracter - puntero al caracter
* \return retorna INT. 0 si pudo operar correctamente
*         retorna -1 si el puntero apunta a NULL
*/
static int convertirUnCaracterEnMayuscula(char* pCaracter)
{
	int retorno = ERROR_PUNTERO_NULL;
	if(pCaracter != NULL)
	{
		retorno = OPERACION_EXITOSA;
		if(*pCaracter >= 97 && *pCaracter <=122)
		{
			*pCaracter = *pCaracter - 32;
		}
	}
	return retorno;
}

/**
* \brief Recibe una cadena de caracteres y coloca una mayuscula en la primer letra de cada palabra (si corresponde)
*        Convierte la primer letra de cada palabra en Mayuscula y el resto en minusculas.
* \param char pNombre[] - Array de caracteres
* \param int len - largo del Array
* \return retorna INT. 0 si pudo operar correctamente
*         retorna -1 si el puntero apunta a NULL
*         retorna -2 si el len es invalido
*         retorna -22 si no se ingresaron caracteres o la cadena perdio el '\0'
*/
static int darFormatoMayusculaMinuscula(char pNombre[], int len)
{
	int largo;
	int i = 0;
	int retorno = ERROR_PUNTERO_NULL;

	if(pNombre != NULL)
	{
		retorno = ERROR_LEN_INVALIDO;
		if(len >0)
		{
			largo = strnlen(pNombre, len);
			retorno = ERROR_NO_SE_INGRESARON_CARACTERES_O_SE_PERDIO_FIN_DE_CADENA;
			if(largo >0 && largo < len)
			{
				retorno = OPERACION_EXITOSA;
				if(pNombre[i] <= 122 && pNombre[i] >= 97)
				{
					pNombre[i] = pNombre[i] - 32;
				}

				for(i = 1; i < largo; i++)
				{
					if(pNombre[i] != 32)
					{
						if(pNombre[i] >= 65 && pNombre[i]<= 90)
						{
							pNombre[i] = pNombre[i] + 32;
						}
					}
					else
					{
						if(pNombre[i+1] <= 122 && pNombre[i+1] >= 97)
						{
							pNombre[i+1] = pNombre[i+1] - 32;
						}
						i++;
					}
				}
			}
		}
	}
	return retorno;
}

/*
* \brief Reemplaza los tabs que se encuentre por espacios en blanco.
* \param cha pCadena[] - Array de caracteres que contiene la cadena.
* \param int len - largo del array
* \return retorna INT. 0 si pudo operar correctamente
*         retorna -1 si el puntero apunta a NULL
*         retorna -2 si el len es invalido
*         retorna -22 si no se ingresaron caracteres  o la cadena perdio el '\0'
*/
static int cambiarTabsPorEspacios(char pCadena[], int len)
{
	int i;
	int largo;
	int retorno = ERROR_PUNTERO_NULL;

	if(pCadena != NULL)
	{
		retorno = ERROR_LEN_INVALIDO;
		if(len > 0)
		{
			largo = strnlen(pCadena, len);
			retorno = ERROR_NO_SE_INGRESARON_CARACTERES_O_SE_PERDIO_FIN_DE_CADENA;
			if(largo > 0 && largo < len)
			{
				retorno = OPERACION_EXITOSA;

				for(i=0;i < largo; i++)
				{
					 if(pCadena[i] == '\t')
					 {
						 pCadena[i] = 32; //32 para ' ' (espacio en blanco)
					 }
				}
			}
		}
	}
	return retorno;
}

/*
* \brief Borra los espacios en blanco (al inicio de la cadena, al final y los extras en el medio)
* 		 Se apoya en 4 funciones para operar correctamente.
* \param cha pCadena[] - Array de caracteres que contiene la cadena.
* \param int len - largo del array
* \return retorna INT. 0 si pudo operar correctamente
*         retorna -1 si el puntero apunta a NULL
*         retorna -2 si el len es invalido
*         retorna -20 si fallo alguna funcion interna

*/
static int borrarEspacios(char pCadena[], int len)
{
	int i = 0;
	int retorno = ERROR_PUNTERO_NULL;
	if(pCadena != NULL)
	{
		retorno = ERROR_LEN_INVALIDO;
		if(len > 0)
		{
			retorno = ERROR_FUNCION_INTERNA_FALLO;
			if(cambiarTabsPorEspacios(pCadena, len) == OPERACION_EXITOSA)
			{
				if(borrarEspaciosIzquierda(pCadena, len,i) == OPERACION_EXITOSA)
				{
					if(borrarEspaciosExtrasIntermedios(pCadena, len) == OPERACION_EXITOSA)
					{
						if(borrarEspaciosFinales(pCadena, len) == OPERACION_EXITOSA)
						{
							retorno = OPERACION_EXITOSA;
						}
					}
				}
			}
		}
	}
	return retorno;
}

/*
* \brief Borra los espacios en blanco a partir de la posicion especificada, hasta que detecta una letra
* \param cha pCadena[] - Array de caracteres que contiene la cadena.
* \param int len - largo del array
* \param int indiceInicial - Indice a partir del cual empieza a borrar espacios.
* \return retorna INT. 0 si pudo operar correctamente
*         retorna -1 si el puntero apunta a NULL
*         retorna -2 si el len es invalido
*         retorna -22 si no se ingresaron caracteres  o la cadena perdio el '\0'
*/
static int borrarEspaciosIzquierda(char pCadena[], int len, int indiceInicial)
{
	int largo;
	int i = indiceInicial;
	int j = indiceInicial;
	int banderaHayLetras = FALSE;
	int retorno = ERROR_PUNTERO_NULL;

	if(pCadena != NULL)
	{
		retorno = ERROR_LEN_INVALIDO;
		if(len > 0)
		{
			largo = strnlen(pCadena, len);
			retorno = ERROR_NO_SE_INGRESARON_CARACTERES_O_SE_PERDIO_FIN_DE_CADENA;
			if(largo > 0 && largo < len)
			{
				retorno = OPERACION_EXITOSA;
				for(	;i < largo; i++)
				{
					 if(pCadena[i] != 32)
					 {
						 banderaHayLetras = TRUE; //En cuanto encuentre una letra, activo la bandera
						 swapCaracteres(pCadena, i, j);//Cambio de lugar el espacio con la letra.
						 j++;
					 }
					 else
					 {
					  //Si la posicion [i] es igual al caracter 32 (espacio), y ademas ya detecte una letra previamente,
					  //ROMPO EL BUCLE, porque ya habria acomodado todas las letras a la izquierda.
					  //Ese espacio "intermedio" se deja, porque se interpreta que se coloco para
					  //separar palabras o nombres.
						 if(banderaHayLetras == TRUE)
						 {
							 break;
						 }
					 }
				}
			}
		}
	}
	return retorno;
}

/*
* \brief Borra los espacios en blanco EXTRAS (mas de 1) que esten en medio de la cadena, hasta que detecta una letra
* \param char pCadena[] - Array de caracteres que contiene la cadena.
* \param int len - largo del array
* \return retorna INT. 0 si pudo operar correctamente
*         retorna -1 si el puntero apunta a NULL
*         retorna -2 si el len es invalido
*         retorna -22 si no se ingresaron caracteres  o la cadena perdio el '\0'
*/
static int borrarEspaciosExtrasIntermedios(char pCadena[], int len)
{
	int largo;
	int i=0;
	int j=1;
	int retorno = ERROR_PUNTERO_NULL;

	if(pCadena != NULL)
	{
		retorno = ERROR_LEN_INVALIDO;
		if(len > 0)
		{
			retorno = ERROR_NO_SE_INGRESARON_CARACTERES_O_SE_PERDIO_FIN_DE_CADENA;
			largo = strnlen(pCadena, len);
			if(largo > 0 && largo < len)
			{
				retorno = OPERACION_EXITOSA;
				largo =	largo-1;
				//i debe llegar a la Anteultima posicion, mientras que j sera quien llegara a la ultima posicion.
				while(i < largo)
				{
					if(pCadena[i] == 32 && pCadena[j] == 32)//Si ambos son espacios en blanco, borro el segundo.
					{
						borrarEspaciosIzquierda(pCadena, len, j);//Paso el indice j, para que sea borrado, y salvar el espacio en i.
					}
					i++;
					j++;
				}
			}
		}
	}
	return retorno;
}

/*
* \brief Borra los espacios en blanco que esten al final de la cadena, hasta que detecta una letra
* \param cha pCadena[] - Array de caracteres que contiene la cadena.
* \param int len - largo del array
* \return retorna INT. 0 si pudo operar correctamente
*         retorna -1 si el puntero apunta a NULL
*         retorna -2 si el len es invalido
*         retorna -22 si no se ingresaron caracteres o la cadena perdio el '\0'
*/
static int borrarEspaciosFinales(char pCadena[], int len)
{
	int i;
	int retorno = ERROR_PUNTERO_NULL;

	if(pCadena != NULL)
	{
		retorno = ERROR_LEN_INVALIDO;
		if(len > 0)
		{
			retorno = ERROR_NO_SE_INGRESARON_CARACTERES_O_SE_PERDIO_FIN_DE_CADENA;
			i = strnlen(pCadena, len);
			if(i >0 && i < len)
			{
				i = i-1;
				retorno = OPERACION_EXITOSA;
				while (i >= 0)
				{
					if(pCadena[i] == 32) //32 es para el espacio en blanco ' '
					{
						pCadena[i] = '\0';
					}
					else
					{
						break;
					}
					i--;
				}
			}
		}
	}
	return retorno;
}

/*
* \brief intercambia 2 caracteres de posicion en un array de caracteres especificado.
* \param char pCadena[] - Array de caracteres que contiene la cadena.
* \param int i - Indice uno que se intercambiara con el Indice dos
* \param int j - Indice dos que se intercambiara con el indice uno
* \return retorna INT. 0 si pudo operar correctamente
*         retorna -1 si el puntero apunta a NULL
*         retorna -5 si el parametro 'i' es igual al 'j'
*         retorna -6 si el parametro 'i' o 'j' esta fuera de rango

*/
static int swapCaracteres(char plistaCaracteres[], int i, int j)
{
	char auxiliar;
	int retorno = ERROR_PUNTERO_NULL;
	if(plistaCaracteres != NULL)
	{
		retorno = ERROR_PARAMETRO_I_O_J_FUERA_DE_RANGO;
		if(i >= 0 && j >= 0)
		{
			retorno = ERROR_PARAMETRO_I_ES_IGUAL_A_J;
			if(i != j)
			{
				auxiliar = plistaCaracteres[i];
				plistaCaracteres[i] = plistaCaracteres[j];
				plistaCaracteres[j] = auxiliar;
				retorno = OPERACION_EXITOSA;
			}
		}
	}
	return retorno;
}

/**
* \brief Valida un texto, eliminando espacios.
* \param char pCadena[] - Direccion de memoria de la variable CHAR que contiene el texto
* \param int largo - Largo de la cadena de caracteres.
* \return retorna INT. 1 si es texto
*         retorna 0 si no es un texto
*         retorno -1 si el puntero es NULL
*         retorno -2 si el len es invalido
*/
int validar_texto(char pCadena[], int len)
{
	char auxiliar[LEN_TEXTO];
	int retorno = ERROR_PUNTERO_NULL;

	if(pCadena != NULL)
	{
		retorno = ERROR_LEN_INVALIDO;
		if(len > 0 && len <= LEN_TEXTO)
		{
			retorno = FALSE;
			strncpy(auxiliar, pCadena, len);
			if(borrarEspacios(auxiliar, len) == OPERACION_EXITOSA)
			{
				strncpy(pCadena, auxiliar, len);
				retorno = TRUE;
			}
		}
	}
	return retorno;
}

/**
* \brief Valida una letra.
* \param char pCadena[] - Direccion de memoria de la variable CHAR que contiene la letra
* \param int largo - Largo de la cadena de caracteres.
* \return retorna INT. 1 si es letra
*         retorna 0 si no es una letra
*         retorno -1 si el puntero es NULL
*/
int validar_letra(char* pCaracter)
{
	int retorno = ERROR_PUNTERO_NULL;
	if(pCaracter != NULL)
	{
		retorno = FALSE;
		if(esLetra(*pCaracter) && convertirUnCaracterEnMayuscula(pCaracter) == OPERACION_EXITOSA)
		{
			retorno = TRUE;
		}
	}
	return retorno;
}

/**
* \brief Valida un nombre, eliminando espacios y colocando las mayusculas correspondientes
* \param char pCadena[] - Direccion de memoria de la variable CHAR que contiene el nombre
* \param int largo - Largo de la cadena de caracteres.
* \return retorna INT. 1 si es nombre
*         retorna 0 si no es un nombre
*         retorno -1 si el puntero es NULL
*         retorno -2 si el len es invalido
*/
int validar_nombre(char pCadena[], int len)
{
	char auxiliar[LEN_NOMBRE];
	int retorno = ERROR_PUNTERO_NULL;
	if(pCadena != NULL)
	{
		retorno = ERROR_LEN_INVALIDO;
		if(len > 0 && len <= LEN_NOMBRE)
		{
			retorno = FALSE;
			strncpy(auxiliar, pCadena, len);
			if(!borrarEspacios(auxiliar, len))
			{
				if(esNombreOApellido(auxiliar, len)== TRUE)
				{
					if(!darFormatoMayusculaMinuscula(auxiliar, len))
					{
						strncpy(pCadena, auxiliar, len);
						retorno = TRUE;
					}
				}
			}
		}
	}
	return retorno;
}

/**
* \brief Valida una direccion, eliminando espacios y colocando las mayusculas correspondientes
* \param char pCadena[] - Direccion de memoria de la variable CHAR que contiene la direccion
* \param int largo - Largo de la cadena de caracteres.
* \return retorna INT. 1 si es direccion
*         retorna 0 si no es una direccion
*         retorno -1 si el puntero es NULL
*         retorno -2 si el len es invalido
*/
int validar_direccion(char pCadena[], int len)
{
	char auxiliar[LEN_DIRECCION];
	int retorno = ERROR_PUNTERO_NULL;

	if(pCadena != NULL)
	{
		retorno = ERROR_LEN_INVALIDO;
		if(len > 0 && len <= LEN_DIRECCION)
		{
			retorno = FALSE;
			strncpy(auxiliar, pCadena, len);
			if(borrarEspacios(auxiliar, len)== OPERACION_EXITOSA)
			{
				if(esDireccion(auxiliar, len) == TRUE)
				{
					if(darFormatoMayusculaMinuscula(auxiliar, len)== OPERACION_EXITOSA)
					{
						strncpy(pCadena, auxiliar, len);
						retorno = TRUE;
					}
				}
			}
		}
	}
	return retorno;
}

/**
* \brief Valida si una cadena pertenece al formato alfanumerico
* \param char pCadena[] - Direccion de memoria de la variable CHAR que contiene el texto alfanumerico
* \param int largo - Largo de la cadena de caracteres.
* \return retorna INT. 1 si es alfanumerico
*         retorna 0 si no es un altanumerico
*         retorno -1 si el puntero es NULL
*         retorno -2 si el len es invalido
*/
int validar_alfanumerico(char pCadena[], int len)
{
	int retorno = ERROR_PUNTERO_NULL;
	if(pCadena != NULL)
	{
		retorno = ERROR_LEN_INVALIDO;
		if(len > 0 && len <= LEN_ALFANUMERICO)
		{
			retorno = FALSE;
			if(esAlfanumerico(pCadena, len) == TRUE)
			{
				retorno = TRUE;
			}
		}
	}
	return retorno;
}

/**
* \brief Valida un nombre Alfanumerico, eliminando espacios y colocando las mayusculas correspondientes
* \param char pCadena[] - Direccion de memoria de la variable CHAR que contiene el nombre alfanumerico
* \param int largo - Largo de la cadena de caracteres.
* \return retorna INT. 1 si es nombre alfanumerico
*         retorna 0 si no es un nombre alfanumerico
*         retorno -1 si el puntero es NULL
*         retorno -2 si el len es invalido
*/
int validar_nombreAlfanumerico(char pCadena[], int len)
{
	char auxiliar[LEN_NOMBRE_ALFANUMERICO];
	int retorno = ERROR_PUNTERO_NULL;

	if(pCadena != NULL)
	{
		retorno = ERROR_LEN_INVALIDO;
		if(len > 0 && len <= LEN_NOMBRE_ALFANUMERICO)
		{
			retorno = FALSE;
			strncpy(auxiliar, pCadena, len);
			if(borrarEspacios(auxiliar, len)== OPERACION_EXITOSA)
			{
				if(esNombreAlfanumerico(auxiliar, len) == TRUE)
				{
					if(darFormatoMayusculaMinuscula(auxiliar, len)== OPERACION_EXITOSA)
					{
						strncpy(pCadena, auxiliar, len);
						retorno = TRUE;
					}
				}
			}
		}
	}
	return retorno;
}

/**
* \brief Valida si una cadena pertenece al formato de un cuit
* \param char pCadena[] - Direccion de memoria de la variable CHAR que contiene el cuit
* \param int largo - Largo de la cadena de caracteres.
* \return retorna INT. 1 si es cuit
*         retorna 0 si no es un cuit
*         retorno -1 si el puntero es NULL
*         retorno -2 si el len es invalido
*/
int validar_cuit(char pCadena[], int len)
{
	int retorno = ERROR_PUNTERO_NULL;
	if(pCadena != NULL)
	{
		retorno = ERROR_LEN_INVALIDO;
		if(len > 0 && len <= LEN_TEXTO_CUIT)
		{
			retorno = FALSE;
			if(esCuit(pCadena, len) == TRUE)
			{
				retorno = TRUE;
			}
		}
	}
	return retorno;
}

/**
* \brief Valida un numero entero
* \param char pCadena[] - Direccion de memoria de la variable CHAR que contiene el numero
* \param int largo - Largo de la cadena de caracteres.
* \return retorna INT. 1 si es numero entero
*         retorna 0 si no es un numero entero
*         retorno -1 si el puntero es NULL
*         retorno -2 si el len es invalido
*/
int validar_numeroEntero(char pNumero[], int len)
{
	int retorno = ERROR_PUNTERO_NULL;
	if(pNumero != NULL)
	{
		retorno = ERROR_LEN_INVALIDO;
        if( len > 0 && len <= LEN_BUFFER_INT)
        {
        	retorno = FALSE;
			if(esNumeroEntero(pNumero, len) == TRUE)
			{
				retorno = TRUE;
			}
        }
	}
	return retorno;
}

/**
* \brief Valida un numero float
* \param char pNumero[] - Direccion de memoria de la variable CHAR que contiene el numero
* \param int largo - Largo de la cadena de caracteres.
* \return retorna INT. 1 si es numero float
*         retorna 0 si no es un numero float
*         retorno -1 si el puntero es NULL
*         retorno -2 si el len es invalido
*/
int validar_numeroFloat(char pNumero[], int len)
{
	int retorno = ERROR_PUNTERO_NULL;
	if(pNumero != NULL)
	{
		retorno = ERROR_LEN_INVALIDO;
		if(len > 0 && len <= LEN_BUFFER_FLOAT)
		{
			retorno = FALSE;
			if(esNumeroFloat(pNumero, len) == TRUE)
			{
				retorno = TRUE;
			}
		}
	}
	return retorno;
}
