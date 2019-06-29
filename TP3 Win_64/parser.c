#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Employee.h"


/** \brief Parsea los datos de los empleados del archivo data.csv (texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int parser_EmployeeFromText(FILE* pFile , LinkedList* pArrayListEmployee)
{
    char bufferId[4096];
    char bufferNombre[4096];
    char bufferHorasTrabajadas[4096];
    char bufferSueldo[4096];
    int cantidadDatos;
    int ret=1;
    Employee *pEmpleado;


    if(pFile!=NULL && pArrayListEmployee!=NULL)
    {
        fscanf(pFile,"%[^,],%[^,],%[^,],%[^\n]\n",bufferId
                                                 ,bufferNombre
                                                 ,bufferHorasTrabajadas
                                                 ,bufferSueldo);

        do
        {
            cantidadDatos=fscanf(pFile,"%[^,],%[^,],%[^,],%[^\n]\n",bufferId
                                                                   ,bufferNombre
                                                                   ,bufferHorasTrabajadas
                                                                   ,bufferSueldo);

            if(cantidadDatos==4)
            {
                pEmpleado=employee_newParametros( bufferId
                                                 ,bufferNombre
                                                 ,bufferHorasTrabajadas
                                                 ,bufferSueldo);

                if(pEmpleado != NULL)
                {
                    if(ll_add(pArrayListEmployee,pEmpleado)==0)
                    {
                        ret=0;
                    }
                }
            }
        }while(!feof(pFile));
    }
    return ret;
}

/** \brief Parsea los datos de los empleados del archivo data.csv (binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int parser_EmployeeFromBinary(FILE* pFile,LinkedList* pArrayListEmployee)
{
    int ret=-1;
    Employee* pEmpleado;

    do
    {
        pEmpleado=employee_new();
        if(pEmpleado!=NULL&&pFile!=NULL&&pArrayListEmployee!=NULL)
        {
            if(fread(pEmpleado,sizeof(Employee),1,pFile)==1)
            {
                ll_add(pArrayListEmployee,pEmpleado);
                ret=0;
            }
            else
            {
                employee_delete(pEmpleado);
            }
        }
    }while(!feof(pFile));
    return ret;
}
