#include <stdio.h>
#include <stdlib.h>
#define ESTADO_INIT 0
#define ESTADO_CERRADO 1
#define ESTADO_ABIERTO 2
#define ESTADO_CERRANDO 3
#define ESTADO_ABRIENDO 4
#define ESTADO_ERROR 5
#define TRUE 1
#define FALSE 0
#define RT_MAX 180
#define ERROR_OK 0
#define ERROR_LS 1
#define ERROR_RT 2

int ESTADO_SIGUIENTE    = ESTADO_INIT;
int ESTADO_ACTUAL       = ESTADO_INIT;
int ESTADO_ANTERIOR     = ESTADO_INIT;

struct DATA_IO
{
    unsigned int LSC:1;
    unsigned int LSA:1;
    unsigned int SPP:1;     //comando pulso pulso
    unsigned int MA:1;      //enciende el motor para abrir
    unsigned int MC:1;      //enciende el motor para cerrar
    unsigned int Cont_RT;   //contador de run time en segundos
    unsigned int Led_A:1;   //Indicador puerta abierta
    unsigned int Led_C:1;   //Indicador puerta cerrada
    unsigned int Led_ER:1;
    unsigned int COD_ERR;
    unsigned int DATOS_READY:1;

} data_io;

int main()
{
    for(;;)
    {
        if(ESTADO_SIGUIENTE == ESTADO_INIT)
        {
            ESTADO_SIGUIENTE = Func_Init();
        }

        if(ESTADO_SIGUIENTE == ESTADO_CERRADO)
        {
            ESTADO_SIGUIENTE = Func_CERRADO();
        }

        if(ESTADO_SIGUIENTE == ESTADO_CERRADO)
        {
            ESTADO_SIGUIENTE = Func_CERRADO();
        }

        if(ESTADO_SIGUIENTE == ESTADO_ABIERTO)
        {
            ESTADO_SIGUIENTE = Func_ABRIENDO();
        }

        if(ESTADO_SIGUIENTE == ESTADO_ABIERTO)
        {
            ESTADO_SIGUIENTE = FuncABIERTO();
        }

        if(ESTADO_SIGUIENTE == ESTADO_ERROR)
        {
            ESTADO_SIGUIENTE = Func_ERROR();
        }
    }

    return 0;
}

int Func_INIT(void)
{
    ESTADO_ANTERIOR = ESTADO_INIT;
    ESTADO_ACTUAL = ESTADO_INIT;

    data_io.MC = FALSE;
    data_io.MA = FALSE;
    data_io.SPP = FALSE;
    data_io.Led_C = TRUE;
    data_io.Led_A = TRUE;
    data_io.Led_ER = TRUE;
    delay();
    data_io.Led_C = FALSE;
    data_io.Led_A = FALSE;
    data_io.Led_ER = FALSE;
    data_io.COD_ERR = FALSE;
    data_io.Cont_RT = 0;
    data_io.DATOS_READY = FALSE;

    //Posiblemente necesitamos esperar que se lean
    //Posiblemente podemos llamar la funcion que lea las entradas
    //Antes de que el codigo continue

    while(!DATOS_READY); //Espero entrada de datos

    for(;;)
    {
        if(data_io.LSC == TRUE && data_io.LSA == FALSE)
        {
            return ESTADO_CERRADO;
        }

        if(data_io.LSC == TRUE && data_io.LSA == TRUE)
        {
            return ESTADO_ERROR;
        }

        if(data_io.LSC == FALSE && data_io.LSA == FALSE)
        {
            return ESTADO_CERRANDO;
        }

        if(data_io.LSC == FALSE && data_io.LSA == TRUE)
        {
            return ESTADO_CERRANDO;
        }
    }
}
int Fun_ABIERTO(void)
{
    for(;;)
    {

    }
}

int Func_CERRADO(void)
{
    ESTADO_ANTERIOR = ESTADO_ACTUAL;
    ESTADO_ACTUAL = ESTADO_CERRADO;
    data_io.MC = FALSE;
    data_io.SPP = FALSE;
    data_io.Led_C = TRUE;
    data_io.Led_A = FALSE;
    data_io.Led_ER = FALSE;

    for(;;)
    {
        //espera comando PP
        if(data_io.SPP == TRUE)
        {
            data_io.SPP = FALSE;
            return ESTADO_ABIERTO;
        }
    }
}

int Func_CERRADO(void)
{
    ESTADO_ANTERIOR = ESTADO_ACTUAL;
    ESTADO_ACTUAL = ESTADO_CERRADO;
    data_io.MC = TRUE;
    data_io.Cont_RT = 0;

    data_io.Led_C = TRUE;
    data_io.Led_A = FALSE;
    data_io.Led_ER = FALSE;

    for(;;)
    {
        if(data_io.LSC == TRUE)
        {
            return ESTADO_CERRADO;
        }

        if(data_io.Cont_RT > RT_MAX)
        {
            return ESTADO_ERROR;
        }
    }
}

int Fun_ABRIENDO(void)
{

}

int Func_ERROR(void)
{

}

