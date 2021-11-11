/****************************************************
    Menu:
     1. Cargar los datos de los empleados desde el archivo data.csv (modo texto).
     2. Cargar los datos de los empleados desde el archivo data.csv (modo binario).
     3. Alta de empleado
     4. Modificar datos de empleado
     5. Baja de empleado
     6. Listar empleados
     7. Ordenar empleados
     8. Guardar los datos de los empleados en el archivo data.csv (modo texto).
     9. Guardar los datos de los empleados en el archivo data.csv (modo binario).
    10. Salir
*****************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Controller.h"
#include "Employee.h"
#include "Menu_mensajes.h"

#define SALIR 15
#define SI 1
#define NO 2
#define ERROR_ARCHIVO_TEXTO_NO_EXISTE -45
#define ERROR_ARCHIVO_BINARIO_NO_EXISTE -47
#define FALTA_CARGAR_ARCHIVOS 1
#define ARCHIVOS_INEXISTENTES 2
#define ARCHIVO_CARGADO_EN_SISTEMA 3
#define ARCHIVO_CARGADO 1
#define ARCHIVO_SIN_CARGAR 0
#define SE_PUEDE_CARGAR 10
#define MODIFICACION_REALIZADA_EN_LISTA 1
#define SIN_MODIFICACIONES_EN_LISTA 0
#define NO_SE_PUEDE_GUARDAR_ARCHIVO_SIN_CARGAR 0
#define SE_HABILITA_CREACION_ARCHIVOS 1
#define ARCHIVO_TEXTO_CARGADO 1
#define ARCHIVO_BINARIO_CARGADO 2
#define LEN_ARCHIVO 50

int main()
{
	setbuf(stdout, NULL);
	int estadoOperacion;
    int opcionElegida = 0;
	int sePuedeGuardar = NO;
	int respuestaPrimeraCargaTexto;
	int respuestaPrimeraCargaBinario;
	int banderaTexto = SE_PUEDE_CARGAR;
	int banderaBinario = SE_PUEDE_CARGAR;
	int banderaCargarTexto = ARCHIVO_SIN_CARGAR;
	int banderaCargarBinario = ARCHIVO_SIN_CARGAR;
	int banderaRealizoUnaModificacionEnSistema = SIN_MODIFICACIONES_EN_LISTA;
	int banderaHabilitarCreacionDeArchivos = NO_SE_PUEDE_GUARDAR_ARCHIVO_SIN_CARGAR;
	char pathArchivoBinario [LEN_ARCHIVO] = "data.bin";
	char pathArchivoTexto [LEN_ARCHIVO] = "data.csv";
    LinkedList* listaEmpleados = ll_newLinkedList();

    do{
    	estadoOperacion = menu_ImprimirMenuPrincipal(&opcionElegida);
    	if(utn_comprobarEstadoDeOperacion(estadoOperacion))
    	{
			switch(opcionElegida)
			{
				case 1:
					if(menu_EsPosibleOperarMenu(banderaTexto))
					{
						respuestaPrimeraCargaTexto = controller_loadFromText(pathArchivoTexto, listaEmpleados);
						if(utn_comprobarEstadoDeOperacion(respuestaPrimeraCargaTexto) && !respuestaPrimeraCargaTexto)
						{
							banderaTexto = ARCHIVO_TEXTO_CARGADO;
							banderaBinario = ARCHIVO_TEXTO_CARGADO;
						}

						if(respuestaPrimeraCargaTexto == ERROR_ARCHIVO_TEXTO_NO_EXISTE && respuestaPrimeraCargaBinario == ERROR_ARCHIVO_BINARIO_NO_EXISTE)
						{
							menu_mensajesAlerta(ARCHIVOS_INEXISTENTES);
							banderaHabilitarCreacionDeArchivos = SE_HABILITA_CREACION_ARCHIVOS;
						}
					}
					break;
				case 2:
					if(menu_EsPosibleOperarMenu(banderaBinario))
					{
						respuestaPrimeraCargaBinario = controller_loadFromBinary(pathArchivoBinario, listaEmpleados);
						if(utn_comprobarEstadoDeOperacion(respuestaPrimeraCargaBinario) && !respuestaPrimeraCargaBinario)
						{
							banderaBinario = ARCHIVO_BINARIO_CARGADO;
							banderaTexto = ARCHIVO_BINARIO_CARGADO;
						}

						if(respuestaPrimeraCargaTexto == ERROR_ARCHIVO_TEXTO_NO_EXISTE && respuestaPrimeraCargaBinario == ERROR_ARCHIVO_BINARIO_NO_EXISTE)
						{
							menu_mensajesAlerta(ARCHIVOS_INEXISTENTES);
							banderaHabilitarCreacionDeArchivos = SE_HABILITA_CREACION_ARCHIVOS;
						}
					}
					break;
				case 3:
					estadoOperacion = controller_addEmployee(listaEmpleados);
					if(utn_comprobarEstadoDeOperacion(estadoOperacion))
					{
						banderaRealizoUnaModificacionEnSistema = MODIFICACION_REALIZADA_EN_LISTA;
						banderaCargarTexto = ARCHIVO_SIN_CARGAR;
						banderaCargarBinario = ARCHIVO_SIN_CARGAR;
					}
					break;
				case 4:
					estadoOperacion= controller_editEmployee(listaEmpleados);
					if(utn_comprobarEstadoDeOperacion(estadoOperacion))
					{
						banderaRealizoUnaModificacionEnSistema = MODIFICACION_REALIZADA_EN_LISTA;
						banderaCargarTexto = ARCHIVO_SIN_CARGAR;
						banderaCargarBinario = ARCHIVO_SIN_CARGAR;
					}
					break;
				case 5:
					estadoOperacion = controller_removeEmployee(listaEmpleados);
					if(utn_comprobarEstadoDeOperacion(estadoOperacion))
					{
						banderaRealizoUnaModificacionEnSistema = MODIFICACION_REALIZADA_EN_LISTA;
						banderaCargarTexto = ARCHIVO_SIN_CARGAR;
						banderaCargarBinario = ARCHIVO_SIN_CARGAR;
					}
					break;
				case 6:
					estadoOperacion = controller_ListEmployee(listaEmpleados);
					utn_comprobarEstadoDeOperacion(estadoOperacion);
					break;
				case 7:
					estadoOperacion =  controller_sortEmployee(listaEmpleados);
					if(utn_comprobarEstadoDeOperacion(estadoOperacion) && !estadoOperacion)
					{
						banderaRealizoUnaModificacionEnSistema = MODIFICACION_REALIZADA_EN_LISTA;
						banderaCargarTexto = ARCHIVO_SIN_CARGAR;
						banderaCargarBinario = ARCHIVO_SIN_CARGAR;
					}
					break;
				case 8:
					if((banderaBinario == ARCHIVO_BINARIO_CARGADO || banderaTexto == ARCHIVO_TEXTO_CARGADO) || banderaHabilitarCreacionDeArchivos)
					{
						sePuedeGuardar = controller_sePuedeGuardarEnArchivo(listaEmpleados);
						if(sePuedeGuardar == SI)
						{
							estadoOperacion = controller_saveAsText(pathArchivoTexto, listaEmpleados);
							if(utn_comprobarEstadoDeOperacion(estadoOperacion))
							{
								banderaCargarTexto = ARCHIVO_CARGADO;
								banderaHabilitarCreacionDeArchivos = SE_HABILITA_CREACION_ARCHIVOS;

								banderaRealizoUnaModificacionEnSistema = MODIFICACION_REALIZADA_EN_LISTA;
								banderaBinario = ARCHIVO_CARGADO_EN_SISTEMA;
								banderaTexto = ARCHIVO_CARGADO_EN_SISTEMA;
							}
						}
					}
					else
					{
						menu_mensajesAlerta(FALTA_CARGAR_ARCHIVOS);
					}
						break;
				case 9:
					if((banderaBinario == ARCHIVO_BINARIO_CARGADO || banderaTexto == ARCHIVO_TEXTO_CARGADO) || banderaHabilitarCreacionDeArchivos)
					{
						sePuedeGuardar = controller_sePuedeGuardarEnArchivo(listaEmpleados);
						if(sePuedeGuardar == SI)
						{
							estadoOperacion = controller_saveAsBinary(pathArchivoBinario, listaEmpleados);
							if(utn_comprobarEstadoDeOperacion(estadoOperacion))
							{
								banderaCargarBinario = ARCHIVO_CARGADO;
								banderaHabilitarCreacionDeArchivos = SE_HABILITA_CREACION_ARCHIVOS;
								banderaRealizoUnaModificacionEnSistema = MODIFICACION_REALIZADA_EN_LISTA;
								banderaBinario = ARCHIVO_CARGADO_EN_SISTEMA;
								banderaTexto = ARCHIVO_CARGADO_EN_SISTEMA;
							}
						}
					}
					else
					{
						menu_mensajesAlerta(FALTA_CARGAR_ARCHIVOS);
					}
					break;
				case 10:
					estadoOperacion = controller_exitApp(listaEmpleados, banderaCargarTexto, banderaCargarBinario, banderaRealizoUnaModificacionEnSistema);
					if(utn_comprobarEstadoDeOperacion(estadoOperacion))
					{
						opcionElegida = estadoOperacion;
						if(opcionElegida == SALIR)
						{
					    	if(!ll_clear(listaEmpleados))
					    	{
					    		ll_deleteLinkedList(listaEmpleados);
					    	}
						}
					}
					break;
			}
    	}
    }while(opcionElegida != SALIR);

    printf("\n\t\t<--Fin del Programa-->");
    return 0;
}
