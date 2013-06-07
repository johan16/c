//
//  main.c
//  prueba
//
//  Created by Mauro on 06-06-13.
//  Copyright (c) 2013 Mauro. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <monetary.h>
#define TAMANO_LINEA 50
#define NUMERO_REGISTROS 1000
#define NUMERO_PRODUCTOS 15
#define TRUE  1
#define FALSE 0

typedef struct registro
{
    int		dia;
    int		mes;
    int		anio;
    int		id_local;
    int		id_producto;
    int		cantidad;
} transaccion;

typedef struct prod
{
    int		id_producto;
    char	nombre_producto[40];
    int		precio_unitario;
} producto;

typedef struct loc
{
    int		id_local;
    char	nombre_local[40];
} local;

typedef struct reg
{
    char transaccion[100];
} trans_1, trans_2, trans_3;

//DECLARARACION DE FUNCIONES
char menu ();
int ventas_mes(transaccion list[], producto prod[], int mes);
int precio_prod_buscado( producto  prod[], int id_prod);
void substring(char st_salida[], char st_entrada[], int po, int n);
int Buscar_String( char cad[], char c, int pos_ini);
void buscar_sucursal(local loc[], int cod_buscado);
int date_is_valid(int day, int month);
void transacciones_buscadas(transaccion trans[], local loc[], producto  prod[], int dia,int mes, int id_local);
int existe_local(local loc[], int cod_buscado);
void nombre_producto(producto  prod[],int id_prod);
void clearScreen();

int main(int argc, const char * argv[])
{
    //arrays de meses
    const char *meses[12] = { "Enero", "Febrero", "Marzo", "Abril", "Mayo", "Junio", "Julio", "Agosto", "Septiembre", "Octubre", "Nomviembre", "Diciembre" };
    //instacio a File para abrir archivos como "archivo"
    FILE *archivo,*archivo1,*archivo2;
    //declaro a fila y un iterador
    int fila, i, pos_ini, pos_fin, cantidad_caracteres;
    //guardo la linea con un array de string
    char caracteres[TAMANO_LINEA];
    //guardo la linea con un array de string
    char variable_destino[TAMANO_LINEA];
    //declaro el separador de lineas
    char caracter_buscado = '*';
    
    //Se define el nombre del archivo
    /*FILES EN MAC*//*
    char transacciones[1240]="/Applications/MAMP/htdocs/C/prueba/prueba/TRANSACCIONES.txt";
    char productos[1250] = "/Applications/MAMP/htdocs/C/prueba/prueba/PRODUCTOS.txt";
    char locales[1250] = "/Applications/MAMP/htdocs/C/prueba/prueba/LOCALES.txt";
    */
    /*FILES EN PC*/
    char transacciones[1240]="C:/xampp/htdocs/c/TRANSACCIONES.txt";
    char productos[1250] = "C:/xampp/htdocs/c/PRODUCTOS.txt";
    char locales[1250] = "C:/xampp/htdocs/c/LOCALES.txt";
    
    // Permite abrir archivo.
    archivo = fopen(transacciones,"r");
    archivo1 = fopen(productos,"r");
    archivo2 = fopen(locales,"r");
    
    // Si el archivo no se encuentra o se esta dañado, no se puede leer.
    if (archivo == NULL || archivo1 == NULL || archivo2 == NULL)
    {
        printf("Archivo no puede ser leido\n\n");
        system("pause");
        exit(1);
    }
    
    /**
     * Estructura Transaccion
     * *<dia>*<mes>*<anio>*<id_local>*<id_producto>*<cantidad>*
     *
     */
    
    // Definimos vector de largo NUMERO_REGISTROS de tipo de datos "linea"
    trans_1 var_transaccion[NUMERO_REGISTROS];
    //Almacenamos las transacciones en el vector de estructura "var_transaccion"
    fila = 0;
    
    while (feof(archivo) == 0)
    {
        //Funcion que lee linea por linea e imprime por pantalla su resultado.
        fgets(caracteres,TAMANO_LINEA,archivo);
        strcpy(var_transaccion[fila].transaccion,caracteres);
        fila++;
    }
    
    trans_2 var_transaccion2[NUMERO_REGISTROS];
    fila = 0;
    
    while (feof(archivo1) == 0)
    {
        //Funcion que lee linea por linea e imprime por pantalla su resultado.
        fgets(caracteres,TAMANO_LINEA,archivo1);
        strcpy(var_transaccion2[fila].transaccion,caracteres);
        fila++;
    }
    
    trans_3 var_transaccion3[NUMERO_REGISTROS];
    fila = 0;
    
    while (feof(archivo2) == 0)
    {
        //Funcion que lee linea por linea e imprime por pantalla su resultado.
        fgets(caracteres,TAMANO_LINEA,archivo2);
        strcpy(var_transaccion3[fila].transaccion,caracteres);
        fila++;
    }
    
    // Se definen vectores de estructura
    transaccion ventas[NUMERO_REGISTROS];
    producto prods[NUMERO_PRODUCTOS];
    local loc[10];
    
    //Proceso de extraccion
    for( i = 0; i < NUMERO_REGISTROS ; i++)
    {
        //Extraer dia
        pos_ini =  1;
        pos_fin =  Buscar_String( var_transaccion[i].transaccion, caracter_buscado, pos_ini+1 );
        cantidad_caracteres = ((pos_fin - pos_ini) - 1);
        substring(variable_destino,var_transaccion[i].transaccion,pos_ini+1,cantidad_caracteres);
        //Almacenamos el variable extraida a la estructura
        ventas[i].dia = atoi(variable_destino);
        
        //Extraer mes
        pos_ini =  pos_fin;
        pos_fin =  Buscar_String( var_transaccion[i].transaccion, caracter_buscado, pos_ini+1 );
        cantidad_caracteres = ((pos_fin - pos_ini) - 1);
        substring(variable_destino,var_transaccion[i].transaccion,pos_ini+1,cantidad_caracteres);
        //Almacenamos el variable extraida a la estructura
        ventas[i].mes = atoi(variable_destino);
        
        //Extraer año
        pos_ini =  pos_fin;
        pos_fin =  Buscar_String( var_transaccion[i].transaccion, caracter_buscado, pos_ini+1 );
        cantidad_caracteres = ((pos_fin - pos_ini) - 1);
        substring(variable_destino,var_transaccion[i].transaccion,pos_ini+1,cantidad_caracteres);
        //Almacenamos el variable extraida a la estructura
        ventas[i].anio = atoi(variable_destino);
        
        //Extraer id local
        pos_ini =  pos_fin;
        pos_fin =  Buscar_String( var_transaccion[i].transaccion, caracter_buscado, pos_ini+1 );
        cantidad_caracteres = ((pos_fin - pos_ini) - 1);
        substring(variable_destino,var_transaccion[i].transaccion,pos_ini+1,cantidad_caracteres);
        //Almacenamos el variable extraida a la estructura
        ventas[i].id_local = atoi(variable_destino);
        
        //Extraer id producto
        pos_ini =  pos_fin;
        pos_fin =  Buscar_String( var_transaccion[i].transaccion, caracter_buscado, pos_ini+1 );
        cantidad_caracteres = ((pos_fin - pos_ini) - 1);
        substring(variable_destino,var_transaccion[i].transaccion,pos_ini+1,cantidad_caracteres);
        //Almacenamos el variable extraida a la estructura
        ventas[i].id_producto = atoi(variable_destino);
        
        //Extraer cantidad
        pos_ini =  pos_fin;
        pos_fin =  Buscar_String( var_transaccion[i].transaccion, caracter_buscado, pos_ini+1 );
        cantidad_caracteres = ((pos_fin - pos_ini) - 1);
        substring(variable_destino,var_transaccion[i].transaccion,pos_ini+1,cantidad_caracteres);
        //Almacenamos el variable extraida a la estructura
        ventas[i].cantidad = atoi(variable_destino);
    }
    //CERRAMOS EL ARCHIVO
    fclose(archivo);
    
    //Proceso de extraccion
    for(i=0;i<NUMERO_PRODUCTOS;i++)
    {
        
        //Extraer id producto
        pos_ini =  1;
        pos_fin =  Buscar_String( var_transaccion2[i].transaccion, caracter_buscado, pos_ini+1 );
        cantidad_caracteres = ((pos_fin - pos_ini) - 1);
        substring(variable_destino,var_transaccion2[i].transaccion,pos_ini+1,cantidad_caracteres);
        //Almacenamos el variable extraida a la estructura
        prods[i].id_producto = atoi(variable_destino);
        
        
        //Extraer nombre producto
        pos_ini =  pos_fin;
        pos_fin =  Buscar_String( var_transaccion2[i].transaccion, caracter_buscado, pos_ini+1 );
        cantidad_caracteres = ((pos_fin - pos_ini) - 1);
        substring(variable_destino,var_transaccion2[i].transaccion,pos_ini+1,cantidad_caracteres);
        //Almacenamos el variable extraida a la estructura
        strcpy(prods[i].nombre_producto,variable_destino);
        
        //Extraer precio unitario
        pos_ini =  pos_fin;
        pos_fin =  Buscar_String( var_transaccion2[i].transaccion, caracter_buscado, pos_ini+1 );
        cantidad_caracteres = ((pos_fin - pos_ini) - 1);
        substring(variable_destino,var_transaccion2[i].transaccion,pos_ini+1,cantidad_caracteres);
        //Almacenamos el variable extraida a la estructura
        prods[i].precio_unitario = atoi(variable_destino);
        
    }
    //CERRAMOS EL FILE
    fclose(archivo1);
    
    //Proceso de extraccion
    for( i = 0 ; i < 10 ; i++)
    {
        
        //Extraer id local
        pos_ini =  1;
        pos_fin =  Buscar_String( var_transaccion3[i].transaccion, caracter_buscado, pos_ini+1 );
        cantidad_caracteres = ((pos_fin - pos_ini) - 1);
        substring(variable_destino,var_transaccion3[i].transaccion,pos_ini+1,cantidad_caracteres);
        //Almacenamos el variable extraida a la estructura
        loc[i].id_local = atoi(variable_destino);
        
        
        //Extraer nombre local
        pos_ini =  pos_fin;
        pos_fin =  Buscar_String( var_transaccion3[i].transaccion, caracter_buscado, pos_ini+1 );
        cantidad_caracteres = ((pos_fin - pos_ini) - 1);
        substring(variable_destino,var_transaccion3[i].transaccion,pos_ini+1,cantidad_caracteres);
        //Almacenamos el variable extraida a la estructura
        strcpy(loc[i].nombre_local,variable_destino);
        
    }
    //CERRAMOS EL ARCHIVO
    fclose(archivo2);
    
    
    char option;
   
   while(tolower((option=menu()))!='x'){
        
        switch (option){
                
            case 'a':
                //caso1
                clearScreen();
                int mes;
                printf("Ingrese un mes entre 1-12 \n");
                scanf("%d", &mes);
                printf("\n");
                if(mes>0 && mes<13)
                    printf("MES: %s\nTOTAL: $%d\n",  meses[mes-1], ventas_mes(ventas, prods, mes));
                printf("\n");
                break;
                
            case 'b':
                //caso2
                printf("");
                int cod_buscado;
                printf("Buscar Sucursal, Ingrese Cod sucursal \n");
                scanf("%d", &cod_buscado);
                printf("\n");
                buscar_sucursal(loc, cod_buscado);
                printf("\n");
                break;
                
            case 'c':
                //caso3
                printf("");
                int dia_b, mes_b, cod_b;//cod local
                printf("Ingresar dia \n");
                scanf("%d", &dia_b);
                
                printf("Ingresar mes \n");
                scanf("%d", &mes_b);
                
                printf("Ingresar cod local \n");
                scanf("%d", &cod_b);
                printf("\n");
                
                if(date_is_valid(dia_b, mes_b)){
                    //existe local?
                    if(!existe_local(loc, cod_b))
                        transacciones_buscadas(ventas, loc, prods, dia_b, mes_b, cod_b);
                    else
                        printf("Hey el codigo local -> %d, no es valido\n", cod_b);
                }else{
                    printf("FECHA INVALIDA, INGRESASTE %d-%d\n", dia_b, mes_b);
                    
                }
                break;
                
            default:
                break;
        }
    }
    
    return 0;
  
    
}

char menu (){
   
    char option;
    printf("Ingresa una opcion, porfa :\n" );
    printf("===========================\n" );
    
    printf("\nA. Venta Total Mes  :" );
    printf("\nB. Nombre Sucursal :" );
    printf("\nC. Listado Dia :" );
    printf("\nX. Salir. >");
    
    scanf(" %c", &option);
    while(fgetc(stdin)!='\n');
    clearScreen(); 
    return option;
}

void transacciones_buscadas(transaccion trans[], local loc[], producto  prod[], int dia,int mes, int id_local){
    int valid = TRUE, i;
    
    for( i = 0 ; i < NUMERO_REGISTROS ; i++)
    {
        if(trans[i].dia == dia && trans[i].mes == mes && trans[i].id_local == id_local ){
            printf("FECHA : %d-%d\n", trans[i].dia, trans[i].mes);
            printf("SUCURSAL : ");
            buscar_sucursal(loc, id_local);
            
            /**
             
             Formato de despliegue de la transaccion.
             ----------------------------------------------------------------
             | NOMBRE PRODUCTO | CANTIDAD | PRECIO UNITARIO | TOTAL VENDIDO |
             ----------------------------------------------------------------
             
             */
            printf("----------------------------------------------------------------\n");
            printf("| NOMBRE PRODUCTO | CANTIDAD | PRECIO UNITARIO | TOTAL VENDIDO |\n");
            printf("----------------------------------------------------------------\n");
            nombre_producto(prod, trans[i].id_producto);
            printf(" %d |", trans[i].cantidad);
            printf(" %d |", precio_prod_buscado( prod, trans[i].id_producto));
            printf(" %d |", precio_prod_buscado( prod, trans[i].id_producto) * trans[i].cantidad);

            printf("\n\n");
            valid = FALSE;
        }
    }
    if(valid){
        printf("NO SE ENCONTRARON RESULTADOS COINCIDENTES\n");
    }
}


int existe_local(local loc[], int cod_buscado)
{
    int valid = TRUE, i;
    
    for( i=0; i<10; i++)
    {
        if(loc[i].id_local == cod_buscado){
            valid = FALSE;
        }
    }
    
    return ( valid );
}

int date_is_valid(int day, int month)
{
    int valid = TRUE;
    
    int month_length[13] =
    { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    
    if ( month < 1 || month > 12 )
        valid = FALSE;
    else if ( day < 1 || day > month_length[month] )
        valid = FALSE;
    
    return ( valid );
}

void buscar_sucursal(local loc[], int cod_buscado){
    int boleano = 0, i;
    for( i=0; i<10; i++)
    {
        if(loc[i].id_local == cod_buscado){
            boleano = 1;
            printf("Sucursal %s\n", loc[i].nombre_local);
        }
    }
    if(boleano == 0)
        printf("Codigo no es valido\n");
}

int ventas_mes(transaccion trans[], producto prod[],int mes){
    int ventas_total_mes = 0, i;
    if(mes > 0 && mes < 13 ){
        for(i = 0 ; i < NUMERO_REGISTROS ; i++)
        {
            if(trans[i].mes == mes){
                ventas_total_mes+= trans[i].cantidad * precio_prod_buscado(prod, trans[i].id_producto);
            }
        }
        return ventas_total_mes;
    }
    return ventas_total_mes;
    
}

int precio_prod_buscado( producto  prod[],int id_prod){
    int i;
    for(i = 0 ; i < NUMERO_PRODUCTOS; i++)
    {
        if(prod[i].id_producto == id_prod )
            return prod[i].precio_unitario;
    }
    return 0;
}

void nombre_producto(producto  prod[],int id_prod){
    int i;
    for( i = 0 ; i < NUMERO_PRODUCTOS; i++)
    {
        if(prod[i].id_producto == id_prod )
            printf("| %s |", prod[i].nombre_producto);
    }

}

//Permite cortar string
void substring(char st_salida[], char st_entrada[], int po, int n) {
    int i=0;   /* contador de caracteres copiados */
    int pos;
    pos=po-1;
    
    if (pos < strlen(st_entrada)) {
        /* Ciclo en el que se lleva a cabo la extraccion. Se detiene cuando se copiaron */
        /* todos los caracteres, o cuando se termina el string de origen.               */
        while (i<n && st_entrada[pos+i]!=0) {
            /* Copia un caracter e incrementa el puntero de posicion */
            st_salida[i] = st_entrada[pos+i];
            i++;
        }
    }
    
    /* Al terminar la copia delimita el string de salida con ASCII(0) */
    st_salida[i] = 0;
    
}
int Buscar_String( char cad[], char c, int pos_ini)
{
    int pos = -1;
    int len = strlen( cad), i;
    for( i = (pos_ini-1); pos == -1 && i < len; i++){ // si quitas la condición pos == -1
        // te devuelve la última posición encontrada (si es que hay más de 1)
        if(*(cad+i) == c)
            pos = i+1;
    }
    return pos;
}

void clearScreen()
{
  system("cls");
}
