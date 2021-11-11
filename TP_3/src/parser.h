/*
 * parser.h
 *
 *  Created on: 5 nov 2021
 *      Author: GONZALO
 */

#ifndef PARSER_H_
#define PARSER_H_

#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Employee.h"

int parser_EmployeeFromText(FILE* pFile, LinkedList* pArrayListEmployee);
int parser_EmployeeFromBinary(FILE* pFile, LinkedList* pArrayListEmployee);
int parser_TextFromEmployee(FILE* pFile, Employee* pEmpleado);
int parser_BinaryFromEmployee(FILE* pFile, Employee* pEmpleado);

#endif /* PARSER_H_ */
