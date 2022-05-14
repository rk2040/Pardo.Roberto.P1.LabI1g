#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "trabajo.h"
#include "auto.h"
#include "marca.h"
#include "color.h"
#include "servicio.h"
#include "fecha.h"
#include "utn.h"
#include "pardo.h"


int inicializarTrabajos(eTrabajo trabajos[], int tamTrabajo)
{
    int exito = 0;

    if(trabajos != NULL && tamTrabajo > 0){
        for(int i=0; i<tamTrabajo; i++)
        {
            trabajos[i].isEmpty = 1;
        }
        exito = 1;
    }
    return exito;
}


int buscarLibreTrabajo(eTrabajo trabajos[], int tamTrabajo)     // -1 si no hay lugar libre, sino devuelve el indice de la primer estructura vacia
{
    int indice = -1;

    if(trabajos != NULL && tamTrabajo > 0)
    {
        for(int i=0; i<tamTrabajo; i++)
        {
            if( trabajos[i].isEmpty )
            {
                indice = i;
                break;
            }
        }
    }
    return indice;
}



int altaTrabajo(eTrabajo trabajos[], int tamTrabajo, eAuto autos[], int tamAuto, eMarca marcas[], int tamMarca, eColor colores[], int tamColor, eServicio servicios[], int tamServicio, int* pNextId)
{
    int exito = 0;
    int indice;
    eTrabajo auxTrabajo;

    if(trabajos != NULL && tamTrabajo > 0 && autos != NULL && tamAuto >0 && servicios != NULL && tamServicio > 0)
    {
        system("cls");

        printf("-------------------------------------\n");
        printf("      *** Alta de trabajo ***        \n");
        printf("-------------------------------------\n");

        indice = buscarLibreTrabajo(trabajos, tamTrabajo);

        if(indice == -1)
        {
            printf("No hay Trabajos cargados en el sistema.\n");
        }
        else{
            auxTrabajo.id = *pNextId;

            (*pNextId)++;

            mostrarAutos(autos, tamAuto, marcas, tamMarca, colores, tamColor);
            //utn_getNumero(&auxTrabajo.idAuto, "Ingrese id Auto: \n", "Error. Reingrese id Auto: \n", 1, 1000, 5);
            printf("Ingrese id del auto: ");
            fflush(stdin);
            scanf("%d", &auxTrabajo.idAuto);
            while( !validarAuto(autos, tamAuto, auxTrabajo.idAuto))
            {
                printf("Error. Reingrese id del Auto: ");
                fflush(stdin);
                scanf("%d", &auxTrabajo.idAuto);
            }

            mostrarServicios(servicios, tamServicio);
            printf("Ingrese id del Servicio: ");
            fflush(stdin);
            scanf("%d", &auxTrabajo.idServicio);
            while( !validarServicio(servicios, tamServicio, auxTrabajo.idServicio))
            {
                printf("Error. Reingrese id del Servicio: ");
                fflush(stdin);
                scanf("%d", &auxTrabajo.idServicio);
            }
        //Fecha a�o
            utn_getNumero(&auxTrabajo.fecha.anio, "Ingrese anio: aaaa ", "\nError. Reingrese anio: aaaa", 1990, 2022,5);
        //Fecha mes
            utn_getNumero(&auxTrabajo.fecha.mes, "Ingrese mes: mm ", "\nError. Reingrese mes: mm", 1, 12, 5);
            if(auxTrabajo.fecha.mes == 1 || auxTrabajo.fecha.mes == 3 || auxTrabajo.fecha.mes == 5 || auxTrabajo.fecha.mes == 7 ||
               auxTrabajo.fecha.mes == 8 || auxTrabajo.fecha.mes == 10 || auxTrabajo.fecha.mes == 12)
            {
                utn_getNumero(&auxTrabajo.fecha.dia, "Ingrese dia: dd ", "\nError. Reingrese dia: dd", 1, 31, 5);
            }
            else if(auxTrabajo.fecha.mes == 4 || auxTrabajo.fecha.mes == 6 || auxTrabajo.fecha.mes == 9 || auxTrabajo.fecha.mes == 11)
            {
                utn_getNumero(&auxTrabajo.fecha.dia, "Ingrese dia: dd ", "\nError. Reingrese dia: dd", 1, 30, 5);
            }
            else{
                utn_getNumero(&auxTrabajo.fecha.dia, "Ingrese dia: dd ", "\nError. Reingrese dia: dd", 1, 28, 5);
            }

            auxTrabajo.isEmpty = 0;

            trabajos[indice] = auxTrabajo;

            exito = 1;
        }
    }
    return exito;
}


void mostrarTrabajoFila(eTrabajo unTrabajo, eAuto autos[], int tamAuto, eMarca marcas[], int tamMarca, eColor colores[], int tamColor, eServicio servicios[], int tamServicio)
{
    char descMarca[20];
    char descColor[20];
    char descServicio[25];
    float precioServicio;
    int indice;

    for(int i=0; i<tamAuto; i++)
    {
        if(unTrabajo.idAuto == autos[i].id)
        {
            indice = i;

            if( cargarDescripcionMarca(marcas, tamMarca, autos[indice].idMarca, descMarca) &&
                cargarDescripcionColor(colores, tamColor, autos[indice].idColor, descColor) &&
                cargarDescripcionServicios(servicios, tamServicio, unTrabajo.idServicio, descServicio) &&
                cargarPrecioServicio(servicios, tamServicio, unTrabajo.idServicio, &precioServicio) )
            {
                printf(" %2d       %-15s %-15s%-15s $%7.2f         %02d/%02d/%d\n",
                       unTrabajo.id,
                       descMarca,
                       descColor,
                       descServicio,
                       precioServicio,
                       unTrabajo.fecha.dia,
                       unTrabajo.fecha.mes,
                       unTrabajo.fecha.anio
                       );
           }
        }
    }
}


int mostrarTrabajos(eTrabajo trabajos[], int tamTrabajo, eAuto autos[], int tamAuto, eMarca marcas[], int tamMarca, eColor colores[], int tamColor, eServicio servicios[], int tamServicio)
{
    int exito = 0;
    int flag = 1;

    if(trabajos != NULL && tamTrabajo > 0){
        //system("cls");
        printf("---------------------------------------------------------------------------------------------------\n");
        printf("                                *** Lista de Trabajos ***                                             \n");
        printf("  Id      Marca Auto          Color          Servicio         Precio       Fecha Trabajo\n");
        printf("---------------------------------------------------------------------------------------------------\n");
        for(int i=0; i<tamTrabajo; i++){
            if( !trabajos[i].isEmpty ){
                mostrarTrabajoFila(trabajos[i], autos, tamAuto, marcas, tamMarca, colores, tamColor, servicios, tamServicio);
                flag = 0;
            }
        }
        if(flag){
            printf("No hay trabajos para mostrar \n");
        }
        exito = 1;
    }
    return exito;
}