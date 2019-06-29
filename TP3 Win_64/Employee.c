#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Employee.h"
#include "utn_string.h"


Employee* employee_new()
{
    return (Employee*) malloc(sizeof(Employee));
}

Employee* employee_newParametros(char* idStr,char* nombreStr,char* horasTrabajadasStr,char* sueldo)
{

    Employee* employee=employee_new();
    if(employee!=NULL)
    {
        employee_setId(employee,idStr);
        employee_setNombre(employee,nombreStr);
        employee_setHorasTrabajadas(employee,horasTrabajadasStr);
        employee_setSueldo(employee,sueldo);
    }
    return employee;
}

int employee_delete(Employee* this)
{
    int ret=-1;
    if(this!=NULL)
    {
        free(this);
        ret=0;
    }
    return ret;
}

int employee_setId(Employee* this,char* value)
{
    int auxId;
    int ret=-1;

    if(this!=NULL&& value!=NULL &&isNum(value))
    {
        auxId=atoi(value);
        if(auxId>=0)
        {
            this->id=auxId;
            ret=0;
        }
    }
    return ret;
}


int employee_setSueldo(Employee* this,char* value)
{
    int auxSueldo;
    int ret=-1;
    if(this!=NULL&& value!=NULL &&isNum(value))
    {
        auxSueldo=atoi(value);
        if(auxSueldo>=0)
        {
            this->sueldo=auxSueldo;
            ret=0;
        }
    }
    return ret;
}

int employee_setNombre(Employee* this,char* value)
{
    int ret=-1;
    if(this!=NULL&& value!=NULL &&validarLetra(value))
    {
        if(strlen(value)>0)
        {
            strncpy(this->nombre,value,sizeof(this->nombre));
            ret=0;
        }
    }
    return ret;
}


int employee_setHorasTrabajadas(Employee* this,char* value)
{
    int auxHoras;
    int ret=-1;
    if(this!=NULL&& value!=NULL &&isNum(value))
    {
        auxHoras=atoi(value);
        if(auxHoras>=0)
        {
            this->horasTrabajadas=auxHoras;
            ret=0;
        }
    }
    return ret;
}


int employee_getNombre(Employee* this,char* value)
{
    int ret=-1;
    if(this!=NULL&&value!=NULL)
    {
        strncpy(value,this->nombre,sizeof(this->nombre));
        ret=0;
    }
    return ret;
}

int employee_getSueldo(Employee* this,int* value)
{
    int ret=-1;
    if(this!=NULL&&value!=NULL)
    {
        *value=this->sueldo;
        ret=0;
    }
    return ret;
}

int employee_getHorasTrabajadas(Employee* this,int* value)
{
    int ret=-1;
    if(this!=NULL&&value!=NULL)
    {
        *value=this->horasTrabajadas;
        ret=0;
    }
    return ret;
}

int employee_getId(Employee* this,int* value)
{
    int ret=-1;
    if(this!=NULL&&value!=NULL)
    {
        *value=this->id;
        ret=0;
    }
    return ret;
}


int employee_initArray(Employee* arrayEmpleado[],int lenEmpleado)
{
    int i;
    int ret=-1;
    if(arrayEmpleado!=NULL&&lenEmpleado>0)
    {
        for(i=0;i<lenEmpleado;i++)
        {
            arrayEmpleado[i]=NULL;
        }
        ret=0;

    }
    return ret;
}

int employee_findFree(Employee* arrayEmployee[],int lenEmployee)
{
    int i;
    int ret=-1;
    if(arrayEmployee!=NULL&&lenEmployee>0)
    {
        for(i=0;i<lenEmployee;i++)
        {
            if(arrayEmployee[i]==NULL)
            {
                ret=i;
                printf("\nHay un lugar libre\n");
                break;
            }
        }
    }
    return ret;
}

int employee_sortByName(void* pFirstEmployee,void* pSecondEmployee)
{
    int ret;
    Employee* pEmployeeA;
    Employee* pEmployeeB;

    pEmployeeA=(Employee*) pFirstEmployee;
    pEmployeeB=(Employee*) pSecondEmployee;

    if(strcmp(pEmployeeA->nombre,pEmployeeB->nombre)>0)
    {
        ret=1;
    }
    else if(strcmp(pEmployeeA->nombre,pEmployeeB->nombre)<0)
    {
        ret=-1;
    }
    else if(strcmp(pEmployeeA->nombre,pEmployeeB->nombre)==0)
    {
        ret=0;
    }
    return ret;
}




