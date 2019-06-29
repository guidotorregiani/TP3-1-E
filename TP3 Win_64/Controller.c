#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Employee.h"
#include "Controller.h"
#include "parser.h"
#include "utn_string.h"

/** \brief Carga los datos de los empleados del archivo data.csv (txt).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_loadFromText(char* path,LinkedList* pArrayListEmployee)
{
    int ret=-1;
    FILE* pFile;

    if(pArrayListEmployee!=NULL)
    {
        pFile=fopen(path,"r");
        if(pFile!=NULL)
        {
            parser_EmployeeFromText(pFile,pArrayListEmployee);
            fclose(pFile);
            ret=0;
        }
    }
    return ret;
}

/** \brief Carga los datos de los empleados del archivo data.csv (bin).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_loadFromBinary(char* path,LinkedList* pArrayListEmployee)
{
    int ret=-1;
    FILE* pFile;

    if(pArrayListEmployee!=NULL)
    {
        pFile=fopen(path,"rb");
        if(pFile!=NULL)
        {
            parser_EmployeeFromBinary(pFile,pArrayListEmployee);
            fclose(pFile);
            ret=0;
        }
    }
    return ret;
}

/** \brief Alta de empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_addEmployee(LinkedList* pArrayListEmployee)
{
    char bufferId[4096];
    char bufferNombre[4096];
    char bufferHorasTrabajadas[4096];
    char bufferSueldo[4096];
    int ret=-1;
    Employee* pEmployee;

    if(pArrayListEmployee!=NULL)
    {
        if((!getStringNumeros(bufferId,"Ingrese ID:","campo ingresado de manera incorrecta\n",3))
         &&(!getString(bufferNombre,"Ingrese Nombre: ","campo ingresado de manera incorrecta",1,128,2))
         &&(!getStringNumeros(bufferHorasTrabajadas,"Ingrese Horas Trabajadas(int): ","campo ingresado de manera incorrecta",3))
         &&(!getStringNumeros(bufferSueldo,"Ingrese Sueldo(int): ","campo ingresado de manera incorrecta",3)))
        {
            pEmployee=employee_newParametros(bufferId,bufferNombre,bufferHorasTrabajadas,bufferSueldo);
            if(pEmployee!=NULL)
            {
                ll_add(pArrayListEmployee,pEmployee);
                ret=0;
            }
        }
    }
    return ret;
}

/** \brief Modifica los datos de x empleado
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_editEmployee(LinkedList* pArrayListEmployee)
{
    int ret=-1;
    int auxId;
    int i;
    int option;
    char bufferId[4096];
    char bufferNombre [4096];
    char bufferHorasTrabajadas [4096];
    char bufferSueldo [4096];
    Employee* pEmployee;


    if (pArrayListEmployee != NULL)
    {
        if(!getStringNumeros(bufferId,"Ingrese ID del empleado a modificar: ","ERROR\n",3))
        {
            auxId=atoi(bufferId);
            for (i=0;i<ll_len(pArrayListEmployee);i++)
            {
                pEmployee=ll_get(pArrayListEmployee,i);
                if(auxId==pEmployee->id)
                {
                    do
                    {
                        printf("Elija el campo a modificar: \n1Nombre\n2Horas trabajadas\n3Sueldo\n4Salir\n");
                        getValidInt(&option,"Ingrese Opcion: ","ERROR\n",1,4,3);
                        switch(option)
                        {
                            case 1:
                                if(!getString(bufferNombre,"Ingrese Nuevo Nombre: ","campo ingresado de manera incorrecta\n",1,128,2))
                                {
                                    employee_setNombre(pEmployee,bufferNombre);
                                    ret=0;
                                }
                                break;
                            case 2:
                                if(!getStringNumeros(bufferHorasTrabajadas,"Ingrese Horas Trabajadas: ","campo ingresado de manera incorrecta\n",3))
                                {
                                    employee_setHorasTrabajadas(pEmployee,bufferHorasTrabajadas);
                                    ret=0;
                                }
                                break;
                            case 3:
                                if(!getStringNumeros(bufferSueldo,"Ingrese Nuevo Sueldo: ","campo ingresado de manera incorrecta\n",3))
                                {
                                    employee_setSueldo(pEmployee,bufferSueldo);
                                    ret=0;
                                }
                                break;
                        }
                    }while(option != 4);
                }
            }
        }
    }
    return ret;
}

/** \brief Baja de x empleado
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_removeEmployee(LinkedList* pArrayListEmployee)
{
    char bufferId[4096];
    int auxId;
    int i;
    int ret=-1;
    Employee* pEmployee;

    if(pArrayListEmployee!=NULL)
    {
        if(!getStringNumeros(bufferId,"Ingrese ID empleado a eliminar: ","campo ingresado de manera incorrecta\n",3))
        {
            auxId=atoi(bufferId);
            if(auxId>=0&&ll_len(pArrayListEmployee)>0)
            {
                for(i=0;i<ll_len(pArrayListEmployee);i++)
                {
                    pEmployee=ll_get(pArrayListEmployee,i);
                    if(pEmployee->id==auxId)
                    {
                        ll_remove(pArrayListEmployee, i);
                        employee_delete(pEmployee);
                        ret=0;
                        break;
                    }
                }
            }
        }
    }
    return ret;
}

/** \brief Lista todos los empleados de la ll
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_ListEmployee(LinkedList* pArrayListEmployee)
{
    int ret=-1;
    int auxId;
    int auxSueldo;
    int auxHoras;
    char auxNombre[4096];
    int i;
    Employee* pEmployee;

    if(pArrayListEmployee!=NULL)
    {
        for(i=0;i<ll_len(pArrayListEmployee);i++)
        {
            pEmployee=ll_get(pArrayListEmployee,i);
            employee_getId(pEmployee,&auxId);
            employee_getNombre(pEmployee,auxNombre);
            employee_getHorasTrabajadas(pEmployee,&auxHoras);
            employee_getSueldo(pEmployee,&auxSueldo);

            if(pEmployee!=NULL)
            {
                printf("%d,%s,%d,%d\n",auxId
                                      ,auxNombre
                                      ,auxHoras
                                      ,auxSueldo);
                ret=0;
            }
        }
    }
   return ret;
}


/** \brief Ordenar empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_sortEmployee(LinkedList* pArrayListEmployee)
{
    int ret=-1;
    if(pArrayListEmployee!=NULL)
    {
        ll_sort(pArrayListEmployee,employee_sortByName,1);
        ret=0;
    }
    return ret;
}


/** \brief Guarda los datos de los empleados en el archivo data.csv (txt).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_saveAsText(char* path,LinkedList* pArrayListEmployee)
{
    int ret=1;
    int auxId;
    int auxSueldo;
    int auxHoras;
    char auxNombre[4096];
    int i;
    Employee* pEmployee;

    FILE* fp=fopen(path,"w+");
    if(fp!=NULL&&pArrayListEmployee!=NULL)
    {
        fprintf(fp,"id,nombre,horasTrabajadas,sueldo\n");

        for(i=0;i<ll_len(pArrayListEmployee);i++)
        {
            pEmployee=ll_get(pArrayListEmployee,i);
            employee_getId(pEmployee,&auxId);
            employee_getNombre(pEmployee,auxNombre);
            employee_getHorasTrabajadas(pEmployee,&auxHoras);
            employee_getSueldo(pEmployee,&auxSueldo);

            if(pEmployee!=NULL)
            {
                fprintf(fp,"%d,%s,%d,%d\n",auxId
                                          ,auxNombre
                                          ,auxHoras
                                          ,auxSueldo);
            }
        }
        fclose(fp);
        ret=0;
    }
    return ret;
}

/** \brief Guarda los datos de los empleados en el archivo data.csv (bin).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_saveAsBinary(char* path,LinkedList* pArrayListEmployee)
{
    int ret=1;
    int i;
    Employee* pEmployee;

    FILE* fp=fopen(path,"w+b");
    if(fp!=NULL)
    {
        for(i=0;i<ll_len(pArrayListEmployee);i++)
        {
            pEmployee=ll_get(pArrayListEmployee,i);
            fwrite(pEmployee,sizeof(Employee),1,fp);
        }
        fclose(fp);
        ret=0;
    }
    return ret;
}
