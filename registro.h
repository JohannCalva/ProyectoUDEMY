#ifndef REGISTRO_H_INCLUDED
#define REGISTRO_H_INCLUDED
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

FILE *registro;
FILE *eliminados;

struct datosEmpleado{
    int id;
    char nombre[20];
    float sueldo;
    int horas;
}empleado[20];


void menu(){
    printf("\n\nMENU DE REGISTRO DE EMPLEADOS:\n");
    printf("Seleccione la opcion que desea realizar:\n");
    printf("1. Alta empleado\n");
    printf("2. Baja empleado\n");
    printf("3. Lista de empleados\n");
    printf("4. Consultar datos de empleados\n");
    printf("5. Modificar salario\n");
    printf("6. Modificar horas\n");
    printf("7. Salir\n");
    printf("Opcion: ");
}

int cargarEmpleados(struct datosEmpleado empleado[20]){
    char addressFile[] = "registro.txt";
    int num_emp = 0;
    char delimitador[] = ";";
    char cadena[200];
    registro = fopen(addressFile, "rt");

    while(feof(registro) == 0){
        struct datosEmpleado e;
        fgets(cadena, 200, registro);
        char *token = strtok(cadena, delimitador);

        if(token != NULL){
            int campo = 1;
            while(token != NULL){
                switch(campo){
                case 1:
                    e.id = atoi(token);
                    break;
                case 2:
                    strcpy(e.nombre, token);
                    break;
                case 3:
                    e.sueldo = atof(token);
                    break;
                case 4:
                    e.horas = atoi(token);
                }
                campo++;
                token = strtok(NULL, delimitador);
            }
        }
        empleado[num_emp] = e;
        num_emp++;
    }

    fclose(registro);
    return num_emp;
}

void listarEmpleados(struct datosEmpleado empleado[20], int num_emp){
    printf("Listando los datos del empleado\n");
    for(int i = 0; i < num_emp; i++){
        printf("ID: %d\n", empleado[i].id);
        printf("Nombre: %s\n", empleado[i].nombre);
        printf("Sueldo: %.2f\n", empleado[i].sueldo);
        printf("Horas semanales: %d\n", empleado[i].horas);
        printf("\n");
    }
}

int verificarId(struct datosEmpleado empleado[20], int num_emp, int id){
    int resultado = 0;
    for(int i = 0; i < num_emp; i++){
        if(empleado[i].id == id){
            resultado = 1;
        }
    }
    return resultado;
}

int altaEmpleado(struct datosEmpleado empleado[20], int num_emp, int ultimo_id){
    int creado = 0;
    struct datosEmpleado emp;
    fflush(stdin);

    emp.id = ultimo_id+1;
    printf("Nombre: ");
    gets(emp.nombre);
    printf("Sueldo: ");
    scanf("%f", &emp.sueldo);
    printf("Horas semanales: ");
    scanf("%d", &emp.horas);

    int existe = verificarId(empleado, num_emp, emp.id);

    if(num_emp < 20){
        if(existe == 0){
            empleado[num_emp] = emp;
            creado = 1;
        }else{
            printf("No se puede dar de alta. ID duplicado\n");
        }
    }else{
        printf("No se puede dar de alta al empleado. No existe cupo.\n");
    }
    return creado;
}

int bajaEmpleado(struct datosEmpleado empleado[20], int num_emp){
    int eliminado = 0;
    int id, indice;
    
    printf("Introduzca el ID del empleado que quiere dar de baja: ");
    scanf("%d", &id);

    int existe = verificarId(empleado, num_emp, id);

    if(existe == 1){
        for(int i = 0; i < num_emp; i++){
            if(empleado[i].id == id){
                indice = i;
            }
        }

        FILE *eliminados;
        eliminados = fopen("eliminados.txt", "a");

        fprintf(eliminados, "%d,%s,%.2f,%d\n", empleado[indice].id, empleado[indice].nombre, empleado[indice].sueldo, empleado[indice].horas);
        fclose(eliminados);

        for(int j = indice; j < num_emp; j++){
            empleado[j] = empleado[j+1];
            struct datosEmpleado aux;
            empleado[j+1] = aux;
        }

        eliminado = 1;
    }else{
        printf("No se puede dar de baja al empleado. El ID no existe.");
    }
    return eliminado;
}

void consultarDatos(struct datosEmpleado empleado[20], int num_emp){
    int id;
    printf("\nIntroduzca ID del empleado para consultar datos\n");
    scanf("%d", &id);

    int existe = verificarId(empleado,num_emp,id);

    if(existe == 1){
        for(int i = 0; i < num_emp; i++){
            if(empleado[i].id == id){
                printf("Datos del empleado con ID: %d\n", empleado[i].id);
                printf("Nombre: %s\n", empleado[i].nombre);
                printf("Sueldo: %.2f\n", empleado[i].sueldo);
                printf("Horas semanales: %d\n", empleado[i].horas);
            }
        }
    }else{
        printf("No se puede consultar datos del empleado. ID no existe\n");
    }
}

void modificarSueldo(struct datosEmpleado empleado[20], int num_emp){
    int id;

    printf("Introduzca el ID del empleado para modificar su sueldo: ");
    scanf("%d", &id);

    int existe = verificarId(empleado,num_emp,id);

    if(existe == 1){
        float nuevo_sueldo;
        printf("Introducir nuevo sueldo: ");
        scanf("%f", &nuevo_sueldo);

        for(int i = 0; i < num_emp; i++){
            if(empleado[i].id == id){
                empleado[i].sueldo = nuevo_sueldo;
                printf("Sueldo actualizado\n");
            }
        }
    }else{
        printf("No se puede modificar el sueldo. ID no existente");
    }
}

void modificarHoras(struct datosEmpleado empleado[20], int num_emp){
    int id;

    printf("Introduzca el ID del empleado para modificar sus horas: ");
    scanf("%d", &id);

    int existe = verificarId(empleado,num_emp,id);

    if(existe == 1){
        float nuevas_horas;
        printf("Introducir nuevas horas: ");
        scanf("%f", &nuevas_horas);

        for(int i = 0; i < num_emp; i++){
            if(empleado[i].id == id){
                empleado[i].horas = nuevas_horas;
                printf("Horas actualizadas\n");
            }
        }
    }else{
        printf("No se puede modificar las horas. ID no existente");
    }
}

void guardarEmpleados(struct datosEmpleado empleado[20], int num_emp){
    FILE *registro;
    registro = fopen("registro.txt", "w");

    for(int i = 0; i < num_emp-1; i++){
        fprintf(registro, "%d;%s;%.2f;%d\n", empleado[i].id, empleado[i].nombre, empleado[i].sueldo, empleado[i].horas);
    }
    fprintf(registro, "%d;%s;%.2f;%d", empleado[num_emp-1].id, empleado[num_emp-1].nombre, empleado[num_emp-1].sueldo, empleado[num_emp-1].horas);
    fclose(registro);
}

#endif