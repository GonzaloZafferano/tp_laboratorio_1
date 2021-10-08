/*
 * ArrayEmployees.h
 *
 *  Created on: 5 oct 2021
 *      Author: GONZALO
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Inputs.h"
#include "ComprobarErrores.h"

#ifndef ARRAYEMPLOYEES_H_
#define ARRAYEMPLOYEES_H_

#define TAM 51

struct
{
	int id;
	char name[TAM];
	char lastName[TAM];
	float salary;
	int sector;
	int isEmpty;
}typedef Employee;

int initEmployees(Employee* list, int len);
int verificarSiHayEmpleados(Employee listaEmpleados[], int len);
int addEmployees(Employee* list, int len, int id, char name[],char lastName[],float salary,int sector);
int buscarIndiceLibre(Employee listaEmpleados[], int len);
int tomarDatosEmpleados(Employee listaEmpleados[], int len);
int findEmployeeById(Employee* list, int len,int id);
int campoAModificar(Employee* auxiliar, int opcion);
int modificarEmpleado(Employee* empleado, int opcion);
int removeEmployee(Employee* list, int len, int id);
int printOneEmployee(Employee empleado);
int imprimirIdsDisponibles(Employee listaEmpleados[], int len);
int printEmployees(Employee* list, int length);
int sortEmployees(Employee* list, int len, int order);
int imprimirDatosDeSalario(Employee listaEmpleados[], int len);
int calcularEImprimirEmpleadosQueSuperanSalarioPromedio(Employee listaEmpleados[], int len, float promedioSalario);
int calcularSalarios(Employee listaEmpleados[], int len, float* pTotalSalarios, float* pPromedioSalarios);

#endif /* ARRAYEMPLOYEES_H_ */