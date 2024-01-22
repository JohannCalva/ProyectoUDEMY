#include "registro.h"

FILE *registro;
FILE *eliminados;

int main(void){
    int op;
    int num_emp = 0;
    struct datosEmpleado empleado[20];
    int ultimo_id;

    num_emp = cargarEmpleados(empleado);
    printf("Numero de empleados en el sistema: %d\n", num_emp);
    do{
        menu();
        scanf("%d", &op);

        switch(op){
        case 1:
            if(num_emp == 0){
                ultimo_id = 0;
            }else{

                for(int i = 0; i < num_emp; i++){
                    ultimo_id = empleado[i].id;
                }
            }
            int creado = altaEmpleado(empleado, num_emp, ultimo_id);
            if(creado == 1){
                num_emp++;
            }
            break;
        case 2:
            int eliminado = bajaEmpleado(empleado, num_emp);
            if(eliminado == 1){
                num_emp--;
            }
            break;
        case 3:
            listarEmpleados(empleado, num_emp);
            break;
        case 4:
            consultarDatos(empleado, num_emp);
            break;
        case 5:
            modificarSueldo(empleado, num_emp);
            break;
        case 6:
            modificarHoras(empleado, num_emp);
            break;
        case 7:
            printf("\nSaliendo del programa. Gracias por usar\n");
            break;
        default:
            printf("\nOpcion no valida\n");
            break;
        }
    }while(op != 7);
    guardarEmpleados(empleado, num_emp);
    return 0;
}