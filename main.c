#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

#include <time.h>
#include <locale.h>
#include "pila.h"

#define  archClientes "perfilesclientes.dat"
#define ArchProductos "productos.dat"
#define ArchCompras "compras.dat"

#define MAX 80
#define ESC 27


typedef struct
{
    char localidad[30];
    char calle[30];
    char altura[30];
    char piso[30];
    char departamento[30];
} stDireccion;

typedef struct
{
    int idCliente;
    char nombre[30];
    char apellido[30];
    char mail[30];
    char telefono[30];
    stDireccion dire;
} stCliente;

typedef struct
{
    int codigo;
    char nombre[30];
    int precio;
} stProducto;

typedef struct
{
    int idAsociado;
    int numCompra;
    char descripcion[MAX];
    int cantItems;
    float precioUnidad;
    float precioTotalxUnidad;
    float totalCompra;
} stCompra;

/* **************************************************************************************************/


/*PROTOTIPADOS*/
int buscarMenorAlumno(stCompra A[ ], int pos, int validos);


/* *********************************PROTOTIPADOS DE CLIENTES******************************************/
/*CASE 1 INSERTAR CLIENTE*/
int buscaUltimoIdCliente();
void cargarcliente();
char existeCliente(int idC, stCliente *client);
char insertarCliente(stCliente c);
/*CASE 2 MOSTRAR LISTADO DE CLIENTES*/
void opcionMostrar();
void datosCliente(stCliente client);
/*CASE 3 MOSTRAR LISTADO DE CLIENTES*/
void buscarPorApellido();
/*CASE 4 MOSTRAR LISTADO DE CLIENTES*/
void modificarUnCliente();
char modificarCliente(stCliente c);
/*CASE 6 ELIMINAR UN CLIENTE*/
void opcionEliminar();
char eliminarCliente(int idC);
/* **************************************FIN PROTOTIPADOS DE CLIENTES**********************************/
stCliente buscaMayorConsumoArchivo();

/* ************************************PROTOTIPADOS DE PRODUCTOS*************************************/
void cargarNuevoProducto();
int existeProducto(int codigoProducto, stProducto * producto);
int insertarProducto(stProducto product);
void opcionMostrarProductos();
void datosProductos(stProducto product);
void buscarProducto();
void modificarUnProducto();
int modificarProducto(stProducto product);
void opcionEliminarProducto();
char eliminarProducto(int codigoProduct);
/* ************************************FIN PROTOTIPADOS DE PRODUCTOS************************************/

/* *************************************PROTOTIPADOS DE COMPRAS****************************************/
int todosLosProductos();
int nuevaCompra();
stCompra CompraTotal(stCompra * compra, int v);
int insertarCompra(stCompra compra[], int  validos);
stCompra listadoCompras(stCompra compra);
int buscaNumUltimaCompra();
void opcionMostrarCompras();
int NumRegistros();
void muestraPedidos(stCompra c[], int v);
/* *************************************FIN PROTOTIPADOS DE COMPRAS************************************/
int leecad(char *cad, int n);
void tituloPrincipal();
/* ******************************************************************************************************/
char linea[MAX];


int main()
{

    setlocale(LC_ALL, "spanish"); /* Permite imprimir caracteres con tilde */
    menuPrincipal();




    return 0;
}

void menuPrincipal()
{
    char repite = 1;
    int opcion = -1;
    system("color f1");
    int validos;
     int mayo=0;
    /* Cuando el usuario ingresa texto en lugar de ingresar una opción. El programa no modifica
    el valor de opcion. En ese caso, no se debe de ingresar a ninguno de los case, por eso se está
    inicializando la variable opcion con un valor que no permita ejecutar ningún case. Simplemente,
    volver a interar y pedir nuevamente la opción. */

    do
    {
        system("cls");

        tituloPrincipal();

        printf("\n\t\t\t\tMENU PRINCIPAL\n");
        printf("\n\t\t\tOPCIONES DE USUARIO\n\n");
        printf("\t\t[1]. Crear nuevo usuario\n");
        printf("\t\t[2]. Mostrar listado de todos los clientes\n");
        printf("\t\t[3]. Buscar un cliente por apellido\n");
        printf("\t\t[4]. Modificar datos de un cliente\n");
        printf("\t\t[5]. Mejores clientes\n");
        printf("\t\t[6]. Eliminar un cliente\n");

        printf("\n\n\t\t\t OPCIONES DE PRODUCTOS\n\n ");
        printf("\t\t[7]. Crear nuevo producto\n");
        printf("\t\t[8]. Mostrar listado de productos\n");
        printf("\t\t[9]. Buscar un producto\n");
        printf("\t\t[10]. Modificar un producto\n");
        printf("\t\t[11]. Eliminar un producto\n");

        printf("\n\n\t\t\t OPCIONES DE COMPRAS\n\n ");
        printf("\t\t[12]. Nueva Compra\n");
        printf("\t\t[13]. Historial de compras\n");
        printf("\t\t[14]. Ver compras de un cliente especifico\n");
        printf("\t\t[15] Para salir\n");

        printf("\n\t\tIngrese su opción: [   ]\b\b\b");

        /* Lectura segura de un entero */
        leecad(linea, MAX);
        sscanf(linea, "%d", &opcion);

        switch (opcion)
        {

        case 1:
            system("cls");
            cargarcliente();

            break;

        case 2:
            system("cls");
            opcionMostrar();
            system("pause");
            break;

        case 3:
            system("cls");
            buscarPorApellido();
            system("pause");
            break;

        case 4:
            modificarUnCliente();
            break;

        case 5:


            break;

        case 6:
            opcionEliminar();
            break;

        case 7:
            cargarNuevoProducto();
            break;
        case 8:
            system("cls");
            opcionMostrarProductos();
            system("pause");
            break;
        case 9:
            system("cls");
            buscarProducto();
            system("pause");
            break;
        case 10:
            modificarUnProducto();
            break;
        case 11:
            opcionEliminarProducto();
            break;
        case 12:
            validos=nuevaCompra();
            break;
        case 13:
            mostrarTodasLasCompras();
            system("pause");
            break;
        case 14:
            repite = 0;
            break;
        case 15:
            repite = 0;
            break;

        }

    }
    while (repite);
}


/************************ CASE 1 - CARGAR UN NUEVO CLIENTE**********************************/
int buscaUltimoIdCliente()
{
    stCliente c;
    int id;

    FILE * pArchCliente = fopen(archClientes,"rb");

    if(pArchCliente)
    {
        fseek(pArchCliente, sizeof(stCliente)*(-1),SEEK_END);
        if(fread(&c,sizeof(stCliente),1,pArchCliente) > 0)
        {
            id=c.idCliente+1;
        }
        fclose(pArchCliente);
    }
    return id;
}

void cargarcliente()
{
    stCliente client;
    int IdClient = 0;
    char repite = 1;
    char respuesta[MAX];

    do
    {
        system("cls");
        tituloPrincipal();

        IdClient=buscaUltimoIdCliente();
        //IdClient=1;

        if (!existeCliente(IdClient, &client))
        {

            client.idCliente = IdClient;
            printf("\n\nID del cliente: %d\n ", client.idCliente);

            printf("Ingrese su nombre:\n");
            gets(client.nombre);

            printf("Ingrese su Apellido:\n");
            gets(client.apellido);

            printf("Ingrese su numero de celular:\n");
            gets(client.telefono);

            printf("Ingrese su e-mail:\n");
            gets(client.mail);
            printf("Ingrese su localidad:\n");
            gets(client.dire.localidad);

            printf("Ingrese su calle:\n");
            gets(client.dire.calle);

            printf("Ingrese su numero de calle:\n");
            gets(client.dire.altura);

            printf("Ingrese su piso:\n");
            gets(client.dire.piso);

            printf("Ingrese su Departamento:\n");
            gets(client.dire.departamento);

            /* Se inserta el producto en el archivo */
            datosCliente(client);
            if (insertarCliente(client))
            {
                printf("\n\tEl cliente fue insertado correctamente\n");

            }
            else
            {
                printf("\n\tOcurrió un error al intentar insertar el producto\n");
                printf("\tInténtelo mas tarde\n");
            }
        }
        else
        {
            printf("\n\tEl cliente de código %d ya existe.\n", IdClient);
            printf("\tNo puede ingresar dos clientes distintos con el mismo código.\n");
        }

        printf("\n\tDesea seguir ingresando productos? [S/N]: ");
        leecad(respuesta, MAX);

        if (!(strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0))
        {
            repite = 0;
        }

    }
    while (repite);
}


char existeCliente(int idC, stCliente *client)
{
    FILE * pArchCliente;
    char existe;

    /* Abre el archivo en modo lectura */
    pArchCliente = fopen(archClientes, "rb");

    if (pArchCliente == NULL)   /* Si no se pudo abrir el archivo, el valor de archivo es NULL */
    {
        existe = 0;

    }
    else
    {
        existe = 0;
        //printf("eNTRA1");
        /* Se busca el producto cuyo código coincida con codigoProducto */
        fread(&(*client), sizeof(*client), 1, pArchCliente);

        while (!feof(pArchCliente))
        {
            //  printf("eNTRA2-");
            if ((*client).idCliente == idC)
            {
                existe = 1;
                break;
            }
            fread(&(*client), sizeof(*client), 1, pArchCliente);
        }

        /* Cierra el archivo */
        fclose(pArchCliente);
    }

    return existe;
}

char insertarCliente(stCliente client)
{
    FILE * pArchCliente=NULL;
    char insercion;

    /* Abre el archivo para agregar datos al final */
    pArchCliente = fopen(archClientes, "ab");	/* Añade datos al final. Si el archivo no existe, es creado */

    if (pArchCliente == NULL)   /* Si no se pudo abrir el archivo, el valor de archivo es NULL */
    {
        insercion = 0;

    }
    else
    {
        fwrite(&client, sizeof(client), 1, pArchCliente);
        insercion = 1;

        /* Cierra el archivo */
        fclose(pArchCliente);
    }

    return insercion;
}

/********************************CASE 2 - MOSTRAR LISTADO DE CLIENTES*********************************/

void opcionMostrar()
{

    FILE * pArchCliente;
    pArchCliente=fopen(archClientes,"rb");
    stCliente aux;

    if(pArchCliente!=NULL)
    {
        printf("\nContenido del archivo:\n\n");
        fseek(pArchCliente,0,SEEK_SET);/* pone el curso al inicio del archivo para mostrar todos los datos*/

        while(!feof(pArchCliente))
        {
            if(fread(&aux, sizeof(stCliente),1,pArchCliente)>0)
            {
                datosCliente(aux);
            }
        }
        fclose(pArchCliente);
    }
}

void datosCliente(stCliente client)
{

    if(client.idCliente>0)
    {

        printf("\n-------------------------------------------\n");

        printf("Id Cliente:");
        printf("%d",client.idCliente);
        printf("\nNombre: ");
        printf("%s",client.nombre);

        printf("\nApellido: ");
        printf("%s", client.apellido);

        printf("\ncelular: ");
        printf("%s", client.telefono);

        printf("\nmail: ");
        printf("%s", client.mail);

        printf("\nLocalidad: ");
        printf("%s", client.dire.localidad);

        printf("\nDireccion: ");
        printf("%s", client.dire.calle);

        printf("\nnumero de calle: ");
        printf("%s", client.dire.altura);

        printf("\nPiso: ");
        printf("%s", client.dire.piso);

        printf("\nDepartamento: ");
        printf("%s", client.dire.departamento);


        printf("\n-------------------------------------------\n");
    }
}

/**************************************FIN CASE 2*****************************************************/

/**************************************CASE 3 - MUESTRA 1 CLIENTE*************************************/

void buscarPorApellido()
{
    stCliente client;
    FILE * pArchCliente;
    char auxApellido[MAX];
    int flag=0;
    tituloPrincipal();
    pArchCliente=fopen(archClientes, "rb");

    if(pArchCliente ==NULL)
    {
        printf("ocurrio un error, no se pudo modificar el archivo \n");

    }
    else
    {

        printf("\n\t\t\tIngrese el Apeliido\n");
        leecad(linea, MAX);
        scanf(linea, "%s", &auxApellido);
        printf("apellido %s\n",auxApellido);

        fseek(pArchCliente,0,SEEK_SET);/* posiciono el curso al inicio*/
        fread(&client, sizeof(client), 1, pArchCliente);

        while ( flag==0&&!feof(pArchCliente))
        {
            //printf("entra al while\n");
            if (strcmp(client.apellido, auxApellido)==0)
            {
                //printf("entra al if\n");
                flag = 1;
                fseek(pArchCliente, (-1)*sizeof(stCliente), SEEK_CUR);
            }
            fread(&client, sizeof(client),1, pArchCliente);
        }

        if(flag==1)
        {
            printf("Datos del Cliente\n");

            datosCliente(client);
        }
        else
        {
            printf("Apellido no encontrado\n");
        }

        fclose(pArchCliente);

    }
}

/*********************************************FIN CASE 3***********************************************/

/**********************************CASE 4 - MODIFICAR DATOS DE UN CLIENTE*********************************/

void modificarUnCliente()
{
    stCliente client;
    int idClient;
    char repite = 1;
    char respuesta[MAX];

    do
    {
        system("cls");
        tituloPrincipal();
        printf("\n\t\t\t==> MODIFICAR PRODUCTO POR CÓDIGO <==\n");


        printf("\n\tIngrese el Id del cliente que desea modificar: ");
        leecad(linea, MAX);
        sscanf(linea, "%d", &idClient);

        if (existeCliente(idClient, &client))
        {
            printf("\n\tID del cliente: %d \n", client.idCliente);
            printf("\tNombre del cliente: %s %s \n", client.nombre, client.apellido);
            printf("\t Telefono: %s \n", client.telefono);
            printf("\tLocalidad:  %s \n", client.dire.localidad);
            printf("\tCalle: %s \n", client.dire.calle);
            printf("\tAltura: %s \n", client.dire.altura);
            printf("\tPiso: %s \n",client.dire.piso);
            printf("\tDepartamento: %s \n",client.dire.departamento);
            printf("\n\tElija los datos a modificar\n");


            printf("\n\tNombre: %s\n", client.nombre);
            printf("\tDesea modificar el nombre del producto? [S/N]: ");
            leecad(respuesta, MAX);
            if (strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0)
            {
                printf("\tNuevo nombre: ");
                leecad(linea, MAX);
                sscanf(linea, "%s", &client.nombre);
            }


            printf("\n\tApellido:%s\n", client.apellido);
            printf("\tDesea modificar el apellido del cliente? [S/N]: ");
            leecad(respuesta, MAX);
            if (strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0)
            {
                printf("\tIngrese nuevo Apellido: ");
                leecad(linea, MAX);
                sscanf(linea, "%s", &client.apellido);
            }

            printf("\n\tMail: %s\n", client.mail);
            printf("\tDesea modificar el Mail? [S/N]: ");
            leecad(respuesta, MAX);
            if (strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0)
            {
                printf("\tIngrese el nuevo mail: ");
                leecad(linea, MAX);
                sscanf(linea, "%s", &client.mail);
            }

            printf("\n\tTelefono: %s\n", client.telefono);
            printf("\tDesea modificar el telefono? [S/N]: ");
            leecad(respuesta, MAX);
            if (strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0)
            {
                printf("\tIngrese nuevo telefono: ");
                leecad(linea, MAX);
                sscanf(linea, "%s", &client.telefono);
            }

            printf("\n\t Localidad: %s\n", client.dire.localidad);
            printf("\tDesea modificar la localdiad? [S/N]: ");
            leecad(respuesta, MAX);
            if (strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0)
            {
                printf("\tIngrese nueva localidad: ");
                leecad(linea, MAX);
                sscanf(linea, "%s", &client.dire.localidad);
            }

            printf("\n\tDireccion: %s\n", client.dire.calle);
            printf("\tDesea modificar la direccion? [S/N]: ");
            leecad(respuesta, MAX);
            if (strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0)
            {
                printf("\tIngrese nueva direccion: ");
                leecad(linea, MAX);
                sscanf(linea, "%s", &client.dire.calle);

            }

            printf("\n\tAltura: %s\n", client.dire.altura);
            printf("\tDesea modificar la Altura? [S/N]: ");
            leecad(respuesta, MAX);
            if (strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0)
            {
                printf("\tIngrese nueva altura: ");
                leecad(linea, MAX);
                sscanf(linea, "%s", &client.dire.altura);
            }

            printf("\n\tPiso: %s\n", client.dire.piso);
            printf("\tDesea modificar la piso? [S/N]: ");
            leecad(respuesta, MAX);
            if (strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0)
            {
                printf("\tIngrese nueva piso: ");
                leecad(linea, MAX);
                sscanf(linea, "%s", &client.dire.piso);
            }

            printf("\n\t Departamento: %s\n", client.dire.departamento);
            printf("\tDesea modificar el departamento? [S/N]: ");
            leecad(respuesta, MAX);
            if (strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0)
            {
                printf("\tIngrese nueva departamento: ");
                leecad(linea, MAX);
                sscanf(linea, "%s", &client.dire.departamento);
            }

            printf("\n\tEstá seguro que desea modificar los datos del cliente [S/N]: ");
            leecad(respuesta, MAX);

            if (strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0)
            {
                /* Se modifica el producto en el archivo */
                if (modificarCliente(client))
                {
                    printf("\n\tEl cliente fue modificado correctamente\n");

                }
                else
                {
                    printf("\n\tOcurrió un error al intentar modificar el cliente\n");
                    printf("\tInténtelo mas tarde\n");
                }
            }
        }
        else
        {
            /* El producto no existe */
            printf("\n\tEl cliente de código %d no existe.\n", idClient);
        }

        printf("\n\tDesea modificar algún otro producto? [S/N]: ");
        leecad(respuesta, MAX);

        if (!(strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0))
        {
            repite = 0;
        }

    }
    while (repite);
}

char modificarCliente(stCliente c)
{
    FILE * pArchCliente;
    char modifica;
    stCliente cliente;

    /* Abre el archivo para lectura/escritura */
    pArchCliente = fopen(archClientes, "r+b");

    if (pArchCliente == NULL)   /* Si no se pudo abrir el archivo, el valor de archivo es NULL */
    {
        modifica = 0;
    }
    else
    {
        modifica = 0;
        fread(&cliente, sizeof(cliente), 1, pArchCliente);
        while (!feof(pArchCliente))
        {
            if (cliente.idCliente == c.idCliente)
            {
                fseek(pArchCliente, ftell(pArchCliente) - sizeof(c), SEEK_SET);
                fwrite(&c, sizeof(c), 1, pArchCliente);
                modifica = 1;
                break;
            }
            fread(&cliente, sizeof(cliente), 1, pArchCliente);
        }

        fclose(pArchCliente);
    }
    return modifica;
}
/****************************************FIN CASE 4**************************************************/

/******************************* CASE 6 - ELIMINAR UN CLIENTE *****************************************/


void opcionEliminar()
{
    stCliente c;
    int idClient;
    char repite=1;
    char respuesta[MAX];

    do
    {
        system("cls");
        tituloPrincipal();
        printf("\n\t\t\t==> ELIMINAR UN CLIENTE <==\n");

        /* Se pide el código del producto a eliminar */
        printf("\n\t Ingrese el Id del cliente que quiere eliminar\n ");
        leecad(linea,MAX);
        sscanf(linea, "%d",&idClient);

        /* Se verifica que el producto a buscar, exista */
        if (existeCliente(idClient, &c))
        {

            /* Se muestran los datos del producto */
            printf("\n\tID del cliente: %d \n", c.idCliente);
            printf("\tNombre del cliente: %s %s \n", c.nombre, c.apellido);
            printf("\t Telefono: %s \n", c.telefono);
            printf("\tLocalidad:  %s \n", c.dire.localidad);
            printf("\tCalle: %s \n", c.dire.calle);
            printf("\tAltura: %s \n", c.dire.altura);
            printf("\tPiso: %s \n",c.dire.piso);
            printf("\tDepartamento: %s \n",c.dire.departamento);
            printf("\n\tSeguro que desea eliminar el producto? [S/N]: ");
            leecad(respuesta, MAX);

            if (strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0)
            {
                if (eliminarCliente(idClient))
                {
                    printf("\n\tCliente eliminado satisfactoriamente.\n");
                }
                else
                {
                    printf("\n\tEl cliente no pudo ser eliminado\n");
                }
            }

        }
        else
        {
            /* El producto no existe */
            printf("\n\tEl cliente  %d no existe.\n", idClient);
        }

        printf("\n\tDesea eliminar otro cliente? [S/N]: ");
        leecad(respuesta, MAX);

        if (!(strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0))
        {
            repite = 0;
        }

    }
    while (repite=1);
}

/* ELiminación lógica de un registro */
char eliminarCliente(int idClient)/* id cliente */
{
    FILE * pArchCliente;
    FILE *auxiliar;
    stCliente client;
    char elimina;

    /* Abre el archivo para leer */
    pArchCliente = fopen(archClientes, "r+b");	/* Modo lectura/escritura. Si el archivo no existe, es creado */

    if (pArchCliente == NULL)   /* Si no se pudo abrir el archivo, el valor de archivo es NULL */
    {
        elimina = 0;
        printf("Error al abrir el archivo\n");

    }
    else
    {
        /* Se busca el registro que se quiere borrar. Cuando se encuentra, se sitúa en esa posición mediante la
        función fseek y luego se modifica el campo clave de ese registro mediante algún valor centinela, eso se logra
        con fwrite. Hasta allí se ha logrado una eliminación LÓGICA. Porque el registro sigue ocupando espacio en el archivo físico */

        fread(&client, sizeof(stCliente), 1, pArchCliente);
        //printf("LLego al else\n");

        while (!feof(pArchCliente))
        {
            //  printf("Entra en nel while!!\n");
            if (client.idCliente == idClient)
            {
                //    printf("entra en el id\n");
                fseek(pArchCliente, ftell(pArchCliente) - sizeof(client), SEEK_SET);
                client.idCliente = -1;
                fwrite(&client, sizeof(stCliente), 1, pArchCliente);
                elimina = 1;
                break;

            }
            fread(&client, sizeof(stCliente), 1, pArchCliente);
        }

        /* Cierra el archivo */
        fclose(pArchCliente);
    }

    return elimina;
}


/**************************FIN CASE 6******************************/


/**---------------------------------------------------------------------------------------------------------------------------------------------------------------**/

/*****************************************FUNCIONES DE PRODUCTOS*******************************************/

void cargarNuevoProducto()
{
    stProducto producto;

    int codigo = 0;
    char repite = 1;
    char respuesta[MAX];
    int aux=0;


    do
    {
        system("cls");
        tituloPrincipal();

        printf("\n\t\t\t==> CREAR NUEVO PRODUCTO <==\n");

        /* Se pide el código del producto a insertar */
        printf("\n\t Codigo del producto: ");
        leecad(linea, MAX);
        sscanf(linea, "%d", &codigo);

        /* Se verifica que el producto no haya sido almacenado anteriormente */
        if (!existeProducto(codigo, &producto))
        {

            producto.codigo= codigo;

            /* Se piden los demás datos del producto a insertar */
            printf("Ingrese nombre del producto:\n");
            gets(producto.nombre);

            printf("Ingrese precio:\n");
            scanf("%d", &producto.precio);


            printf("aca1!\n");
            /* Se inserta el producto en el archivo */
            aux=insertarProducto(producto);

            if (aux==1)
            {
                printf("\n\tEl producto fue insertado correctamente\n");

            }
            else
            {
                printf("\n\tOcurrió un error al intentar insertar el producto\n");
                printf("\tInténtelo mas tarde\n");
            }
        }
        else
        {
            /* El producto ya existe, no puede ser insertado. */
            printf("\n\tEl producto con código %d ya existe.\n", codigo);
            printf("\tNo puede ingresar dos productos distintos con el mismo código.\n");
        }

        printf("\n\tDesea seguir ingresando productos? [S/N]: ");
        leecad(respuesta, MAX);

        if (!(strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0))
        {
            repite = 0;
        }

    }
    while (repite);
}


int existeProducto(int codigoProducto, stProducto * producto)
{
    FILE * pArchProducto;
    char existe;

    /* Abre el archivo en modo lectura */
    pArchProducto = fopen(ArchProductos, "rb");

    if (pArchProducto == NULL)   /* Si no se pudo abrir el archivo, el valor de archivo es NULL */
    {
        printf("Ocurrio un error al intentar abir el archivo!!!!\n");
        existe = 0;

    }
    else
    {
        existe = 0;

        /* Se busca el producto cuyo código coincida con codigoProducto */
        fread(&(*producto), sizeof(*producto), 1, pArchProducto);

        while (!feof(pArchProducto))
        {

            if ((*producto).codigo == codigoProducto)
            {
                existe = 1;
                break;
            }
            fread(&(*producto), sizeof(*producto), 1, pArchProducto);
        }

        /* Cierra el archivo */
        fclose(pArchProducto);
    }

    return existe;
}

int insertarProducto(stProducto product)///char nombrearchivo
{
    FILE * pArchProducto;
    char insercion;

    /* Abre el archivo para agregar datos al final */
    pArchProducto = fopen(ArchProductos, "ab");	/* Añade datos al final. Si el archivo no existe, es creado */
    if (pArchProducto == NULL)   /* Si no se pudo abrir el archivo, el valor de archivo es NULL */
    {
        insercion = 0;
        printf("Ocurrio un error al intentar abiri el archivo\n");
    }
    else
    {
        fwrite(&product, sizeof(stProducto), 1, pArchProducto);
        insercion = 1;

        /* Cierra el archivo */
        fclose(pArchProducto);
    }

    return insercion;
}

/* MOSTRAR TODOS LOS PRODUCTOS EN UNA LISTA*/
void opcionMostrarProductos()
{

    FILE * pArchProductos;
    pArchProductos=fopen(ArchProductos,"rb");
    stProducto aux;
    tituloPrincipal();

    if(pArchProductos!=NULL)
    {
        printf("\nContenido del archivo:\n\n");
        fseek(pArchProductos,0,SEEK_SET);/*situo al inicio del archivo*/

        while(!feof(pArchProductos))
        {
            if(fread(&aux, sizeof(stProducto),1,pArchProductos)>0)
            {
                datosProductos(aux);
            }
        }
        fclose(pArchProductos);
    }
    else
    {
        printf("Ocurrio un error al intentar abrir el archivo\n");
    }
}

void datosProductos(stProducto product)
{

    if(product.codigo>0)
    {

        printf("\n------------------------------------------------------------------\n");

        printf("\t\tCodigo del producto:");
        printf("\t%d", product.codigo);
        printf("\n\t\tNombre: ");
        printf("\t\t%s", product.nombre);

        printf("\n\t\tPrecio: ");
        printf("\t\t%d", product.precio);

        printf("\n------------------------------------------------------------------\n");
    }
}

void buscarProducto()
{
    stProducto product;
    FILE * pArchProducto;
    char auxProducto[MAX];
    int flag=0;
    tituloPrincipal();
    pArchProducto=fopen(ArchProductos, "rb");

    if(pArchProducto ==NULL)
    {
        printf("ocurrio un error, no se pudo modificar el archivo \n");

    }
    else
    {

        printf("\n\t\t\tIngrese el nombre del producto\n");
        leecad(linea, MAX);
        sscanf(linea, "%s", &auxProducto);
        printf("Producto: %s\n",auxProducto);

        fseek(pArchProducto,0,SEEK_SET);/* posiciono el curso al inicio*/
        fread(&product, sizeof(stProducto), 1, pArchProducto);

        while ( flag==0&&!feof(pArchProducto))
        {
            //printf("entra al while\n");
            if (strcmp(product.nombre, auxProducto)==0)
            {
                //  printf("entra al if\n");
                flag = 1;
                fseek(pArchProducto, (-1)*sizeof(stProducto), SEEK_CUR);
            }
            fread(&product, sizeof(stProducto),1, pArchProducto);
        }

        if(flag==1)
        {
            printf("Datos del Cliente\n");

            datosProductos(product);
        }
        else
        {
            printf("Producto no encontrado\n");
        }
        /* Cierra el archivo */
        fclose(pArchProducto);

    }
}

void modificarUnProducto()
{
    stProducto product;
    int codigoProducto;
    char repite = 1;
    char respuesta[MAX];
    int aux, auxModifica;

    do
    {
        system("cls");
        tituloPrincipal();
        printf("\n\t\t\t==> MODIFICAR PRODUCTO POR CÓDIGO <==\n");


        printf("\n\tIngrese el codigo del producto que desea modificar: ");
        leecad(linea, MAX);
        sscanf(linea, "%d", &codigoProducto);

        if (existeProducto(codigoProducto, &product))
        {
            printf("\n\t\t\tCodigo del producto: %d \n", product.codigo);
            printf("\t\t\tNombre del producto: %s\n", product.nombre);
            printf("\t\t\tPrecio %d \n", product.precio);

            printf("\n\tElija los datos a modificar\n");


            printf("\n\tNombre: %s\n", product.nombre);
            printf("\tDesea modificar el nombre del producto? [S/N]: ");
            leecad(respuesta, MAX);
            if (strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0)
            {
                printf("\tNuevo nombre: ");
                gets(product.nombre);
            }

            printf("\n\tPrecio:%d\n", product.precio);
            printf("\tDesea modificar el precio del producto? [S/N]: ");
            leecad(respuesta, MAX);
            if (strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0)
            {
                printf("\tIngrese el nuevo precio: ");
                leecad(linea, MAX);
                sscanf(linea, "%d", &product.precio);
            }


            printf("\n\tEstá seguro que desea modificar los datos del producto [S/N]: ");
            leecad(respuesta, MAX);

            if (strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0)
            {
                /* Se modifica el producto en el archivo */
                //auxModifica=modificarProducto(product);
                if (modificarProducto(product))
                {
                    printf("\n\tEl producto fue modificado correctamente\n");

                }
                else
                {
                    printf("\n\tOcurrió un error al intentar modificar el producto\n");
                    printf("\tInténtelo mas tarde\n");
                }
            }
        }
        else
        {
            /* El producto no existe */
            printf("\n\tEl producto de código %d no existe.\n", product);
        }

        printf("\n\tDesea modificar algún otro producto? [S/N]: ");
        leecad(respuesta, MAX);

        if (!(strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0))
        {
            repite = 0;
        }

    }
    while (repite);
}

int modificarProducto(stProducto product)
{
    FILE * pArchProducto;
    char modifica;
    int flag=0;
    stProducto auxProduct;

    /* Abre el archivo para lectura/escritura */
    pArchProducto = fopen(ArchProductos, "r+b");

    if (pArchProducto == NULL)   /* Si no se pudo abrir el archivo, el valor de archivo es NULL */
    {
        modifica = 0;


    }
    else
    {
        modifica = 0;
        fread(&auxProduct, sizeof(stProducto), 1, pArchProducto);
        while (!feof(pArchProducto))
        {

            if (auxProduct.codigo == product.codigo)
            {
                fseek(pArchProducto, ftell(pArchProducto) - sizeof(product), SEEK_SET);
                fwrite(&product, sizeof(stProducto), 1, pArchProducto);
                modifica = 1;
                break;

            }
            fread(&auxProduct, sizeof(stProducto), 1, pArchProducto);

        }

        fclose(pArchProducto);
    }

    return modifica;
}

void opcionEliminarProducto()
{
    stProducto product;
    int codigoProducto;
    char repite=1;
    char respuesta[MAX];

    do
    {
        system("cls");
        tituloPrincipal();
        printf("\n\t\t\t==> ELIMINAR UN PRODUCTO <==\n");

        /* Se pide el código del producto a eliminar */
        printf("\n\t Ingrese el codigo del producto que quiere eliminar\n ");
        leecad(linea,MAX);
        sscanf(linea, "%d",&codigoProducto);

        /* Se verifica que el producto a buscar, exista */
        if (existeProducto(codigoProducto, &product))
        {

            /* Se muestran los datos del producto */
            printf("\n\tCodigo del producto: %d \n", product.codigo);
            printf("\tNombre del producto: %s %s \n", product.nombre);
            printf("\t Precio: %s \n", product.precio);
            printf("\n\tSeguro que desea eliminar el producto? [S/N]: ");
            leecad(respuesta, MAX);

            if (strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0)
            {
                if (eliminarProducto(codigoProducto))
                {
                    printf("\n\tProducto eliminado satisfactoriamente.\n");
                }
                else
                {
                    printf("\n\tEl producto no pudo ser eliminado\n");
                }
            }

        }
        else
        {
            /* El producto no existe */
            printf("\n\tEl producto codigo %d no existe.\n", product);
        }

        printf("\n\tDesea eliminar otro producto? [S/N]: ");
        leecad(respuesta, MAX);

        if (!(strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0))
        {
            repite = 0;
        }

    }
    while (repite);
}

/* ELiminación lógica de un registro */
char eliminarProducto(int codigoProduct)/* id producto */
{
    FILE * pArchProducto;
    FILE *auxiliar;
    stProducto product;
    char elimina;

    /* Abre el archivo para leer */
    pArchProducto = fopen(ArchProductos, "r+b");	/* Modo lectura/escritura. Si el archivo no existe, es creado */

    if (pArchProducto == NULL)   /* Si no se pudo abrir el archivo, el valor de archivo es NULL */
    {
        elimina = 0;
        printf("Error al abrir el archivo\n");

    }
    else
    {

        fread(&product, sizeof(stProducto), 1, pArchProducto);

        while (!feof(pArchProducto))
        {
            if (product.codigo == codigoProduct)
            {
                fseek(pArchProducto, ftell(pArchProducto) - sizeof(product), SEEK_SET);
                product.codigo = -1;
                fwrite(&product, sizeof(stProducto), 1, pArchProducto);
                elimina = 1;
                break;

            }
            fread(&product, sizeof(stProducto), 1, pArchProducto);
        }

        /* Cierra el archivo */
        fclose(pArchProducto);
    }

    return elimina;
}

/******************************************FIN FUNCIONES PRODUCTOS******************************************/

/********************************************FUNCIONES DE COMPRAS********************************************/
int buscaNumUltimaCompra()
{
    stCompra c[MAX];
    int num=-1,i=0;

    FILE * pArchCompra= fopen(ArchCompras,"rb");

    if(pArchCompra)
    {
        fseek(pArchCompra, sizeof(stCompra)*(-1),SEEK_END);
        if(fread(&c[i],sizeof(stCompra),1,pArchCompra) > 0)
        {
            printf("ENTRA\n");
            num=c[i].numCompra+1;
        }
        fclose(pArchCompra);
    }
    return num;
}

int nuevaCompra()
{
    stCompra nuevaCom[MAX];

    stProducto nuevoPro;
    stCliente client;


    int existe=1, idCliente, numCompra,opcion, i=0,j=0, numProductos=0, items, continua=1, aux=0;
    char control, control2;
    float contTotalCompra=0,pXunidad=0, totalXproducto=0;

    do
    {
        printf("\t\t Ingrese el Id del cliente\n");
        scanf("%d",&idCliente);

        if(existeCliente(idCliente, &client))
        {
            datosCliente(client);
            existe=0;
            nuevaCom[i].idAsociado=idCliente;
            system("pause");
        }
        else
        {
            printf("El ID %d no existe\n",idCliente);
            printf("Desea volver a intentarlo?s/n\n");
            scanf("%c",&control);
        }
    }
    while(existe==1 && control=='s');

    numCompra=buscaNumUltimaCompra();

    nuevaCom[j].numCompra=numCompra;
    /* *******************************************************************/
    do
    {
        printf("Numero de compra %d: !!!!!!!", nuevaCom[j].numCompra);
        opcion=todosLosProductos();



        switch(opcion)
        {
        case 1:///producto 101
            nuevaCom[i].precioUnidad=50;
            printf("\rIngrese la cantidad de CAFE :");
            scanf("%d", &items);
            totalXproducto=items*50;
            nuevaCom[i].cantItems=items;

            strcpy(nuevaCom[i].descripcion, "CAFE");
            nuevaCom[i].precioTotalxUnidad=(float)items*50;
            printf("\n %d \t  %s \t\t\t | %.2f | \t | %.2f | ", nuevaCom[i].cantItems, nuevaCom[i].descripcion, nuevaCom[i].precioUnidad,nuevaCom[i].precioTotalxUnidad);
            contTotalCompra+=nuevaCom[i].precioTotalxUnidad;
            break;

        case 2:
            nuevaCom[i].precioUnidad=55;
            printf("\rIngrese la cantidad de CAFE DOBLE:");
            scanf("%d", &items);
            totalXproducto=items*55;
            nuevaCom[i].cantItems=items;

            strcpy(nuevaCom[i].descripcion, "CAFE DOBLE");
            nuevaCom[i].precioTotalxUnidad=(float)items*55;
            printf("\n %d \t  %s \t\t\t | %.2f | \t | %.2f | ", nuevaCom[i].cantItems, nuevaCom[i].descripcion, nuevaCom[i].precioUnidad,nuevaCom[i].precioTotalxUnidad);
            contTotalCompra+=nuevaCom[i].precioTotalxUnidad;

            break;

        case 3:
            nuevaCom[i].precioUnidad=60;
            printf("\rIngrese la cantidad de MOKA :");
            scanf("%d", &items);
            totalXproducto=items*60;
            nuevaCom[i].cantItems=items;

            strcpy(nuevaCom[i].descripcion, "MOKA");
            nuevaCom[i].precioTotalxUnidad=(float)items*60;
            printf("\n %d \t  %s \t\t\t | %.2f | \t | %.2f | ", nuevaCom[i].cantItems, nuevaCom[i].descripcion, nuevaCom[i].precioUnidad,nuevaCom[i].precioTotalxUnidad);
            contTotalCompra+=nuevaCom[i].precioTotalxUnidad;
            break;

        case 4:
            nuevaCom[i].precioUnidad=65;
            printf("\rIngrese la cantidad de DESCAFEINADO :");
            scanf("%d", &items);
            totalXproducto=items*65;
            nuevaCom[i].cantItems=items;

            strcpy(nuevaCom[i].descripcion, "DESCAFEINADO");
            nuevaCom[i].precioTotalxUnidad=(float)items*65;
            printf("\n %d \t  %s \t\t\t | %.2f | \t | %.2f | ", nuevaCom[i].cantItems, nuevaCom[i].descripcion, nuevaCom[i].precioUnidad,nuevaCom[i].precioTotalxUnidad);
            contTotalCompra+=nuevaCom[i].precioTotalxUnidad;
            break;
        case 5:
            nuevaCom[i].precioUnidad=65;
            printf("\rIngrese la cantidad de CAFE CON LECHE :");
            scanf("%d", &items);
            totalXproducto=items*65;
            nuevaCom[i].cantItems=items;

            strcpy(nuevaCom[i].descripcion, "CAFE CON LECHE");
            nuevaCom[i].precioTotalxUnidad=(float)items*65;
            printf("\n %d \t  %s \t\t\t | %.2f | \t | %.2f | ", nuevaCom[i].cantItems, nuevaCom[i].descripcion, nuevaCom[i].precioUnidad,nuevaCom[i].precioTotalxUnidad);
            contTotalCompra+=nuevaCom[i].precioTotalxUnidad;
            break;

        case 6:
            nuevaCom[i].precioUnidad=65;
            printf("\rIngrese la cantidad de CAFE CON CREMA :");
            scanf("%d", &items);
            totalXproducto=items*65;
            nuevaCom[i].cantItems=items;

            strcpy(nuevaCom[i].descripcion, "CAFE CON CREMA");
            nuevaCom[i].precioTotalxUnidad=(float)items*65;
            printf("\n %d \t  %s \t\t\t | %.2f | \t | %.2f | ", nuevaCom[i].cantItems, nuevaCom[i].descripcion, nuevaCom[i].precioUnidad,nuevaCom[i].precioTotalxUnidad);
            contTotalCompra+=nuevaCom[i].precioTotalxUnidad;
            break;

        case 7:
            nuevaCom[i].precioUnidad=70;
            printf("\rIngrese la cantidad de CAPPUCCINO :");
            scanf("%d", &items);
            totalXproducto=items*70;
            nuevaCom[i].cantItems=items;

            strcpy(nuevaCom[i].descripcion, "CAPPUCCINO");
            nuevaCom[i].precioTotalxUnidad=(float)items*70;
            printf("\n %d \t  %s \t\t\t | %.2f | \t | %.2f | ", nuevaCom[i].cantItems, nuevaCom[i].descripcion, nuevaCom[i].precioUnidad,nuevaCom[i].precioTotalxUnidad);
            contTotalCompra+=nuevaCom[i].precioTotalxUnidad;
            break;

        case 8:
            nuevaCom[i].precioUnidad=65;
            printf("\rIngrese la cantidad de CAFE IRLANDES :");
            scanf("%d", &items);
            totalXproducto=items*65;
            nuevaCom[i].cantItems=items;

            strcpy(nuevaCom[i].descripcion, "CAFE IRLANDES");
            nuevaCom[i].precioTotalxUnidad=(float)items*65;
            printf("\n %d \t  %s \t\t\t | %.2f | \t | %.2f | ", nuevaCom[i].cantItems, nuevaCom[i].descripcion, nuevaCom[i].precioUnidad,nuevaCom[i].precioTotalxUnidad);
            contTotalCompra+=nuevaCom[i].precioTotalxUnidad;
            break;

        case 9:
            nuevaCom[i].precioUnidad=62;
            printf("\rIngrese la cantidad de TE :");
            scanf("%d", &items);
            totalXproducto=items*62;
            nuevaCom[i].cantItems=items;

            strcpy(nuevaCom[i].descripcion, "TE");
            nuevaCom[i].precioTotalxUnidad=(float)items*62;
            printf("\n %d \t  %s \t\t\t | %.2f | \t | %.2f | ", nuevaCom[i].cantItems, nuevaCom[i].descripcion, nuevaCom[i].precioUnidad,nuevaCom[i].precioTotalxUnidad);
            contTotalCompra+=nuevaCom[i].precioTotalxUnidad;
            break;

        case 10:
            nuevaCom[i].precioUnidad=70;
            printf("\rIngrese la cantidad de TE SABORIZADO :");
            scanf("%d", &items);
            totalXproducto=items*70;
            nuevaCom[i].cantItems=items;

            strcpy(nuevaCom[i].descripcion, "TE SABORIZADO");
            nuevaCom[i].precioTotalxUnidad=(float)items*70;
            printf("\n %d \t  %s \t\t\t | %.2f | \t | %.2f | ", nuevaCom[i].cantItems, nuevaCom[i].descripcion, nuevaCom[i].precioUnidad,nuevaCom[i].precioTotalxUnidad);
            contTotalCompra+=nuevaCom[i].precioTotalxUnidad;
            break;

        case 11:
            nuevaCom[i].precioUnidad=75;
            printf("\rIngrese la cantidad de TE CON LIMON :");
            scanf("%d", &items);
            totalXproducto=items*75;
            nuevaCom[i].cantItems=items;

            strcpy(nuevaCom[i].descripcion, "TE CON LIMON");
            nuevaCom[i].precioTotalxUnidad=(float)items*75;
            printf("\n %d \t  %s \t\t\t | %.2f | \t | %.2f | ", nuevaCom[i].cantItems, nuevaCom[i].descripcion, nuevaCom[i].precioUnidad,nuevaCom[i].precioTotalxUnidad);
            contTotalCompra+=nuevaCom[i].precioTotalxUnidad;
            break;

        case 12:
            nuevaCom[i].precioUnidad=75;
            printf("\rIngrese la cantidad de TE CON LECHE :");
            scanf("%d", &items);
            totalXproducto=items*75;
            nuevaCom[i].cantItems=items;

            strcpy(nuevaCom[i].descripcion, "TE CON LECHE");
            nuevaCom[i].precioTotalxUnidad=(float)items*75;
            printf("\n %d \t  %s \t\t\t | %.2f | \t | %.2f | ", nuevaCom[i].cantItems, nuevaCom[i].descripcion, nuevaCom[i].precioUnidad,nuevaCom[i].precioTotalxUnidad);
            contTotalCompra+=nuevaCom[i].precioTotalxUnidad;
            break;
        case 13:
            nuevaCom[i].precioUnidad=140;
            printf("\rIngrese la cantidad de SUBMARINO :");
            scanf("%d", &items);
            totalXproducto=items*140;
            nuevaCom[i].cantItems=items;

            strcpy(nuevaCom[i].descripcion, "SUBMARINO");
            nuevaCom[i].precioTotalxUnidad=(float)items*140;
            printf("\n %d \t  %s \t\t\t | %.2f | \t | %.2f | ", nuevaCom[i].cantItems, nuevaCom[i].descripcion, nuevaCom[i].precioUnidad,nuevaCom[i].precioTotalxUnidad);
            contTotalCompra+=nuevaCom[i].precioTotalxUnidad;
            break;

        case 14:
            nuevaCom[i].precioUnidad=80;
            printf("\rIngrese la cantidad de CHCOLATADA :");
            scanf("%d", &items);
            totalXproducto=items*80;
            nuevaCom[i].cantItems=items;

            strcpy(nuevaCom[i].descripcion, "CHOCOLATADA");
            nuevaCom[i].precioTotalxUnidad=(float)items*80;
            printf("\n %d \t  %s \t\t\t | %.2f | \t | %.2f | ", nuevaCom[i].cantItems, nuevaCom[i].descripcion, nuevaCom[i].precioUnidad,nuevaCom[i].precioTotalxUnidad);
            contTotalCompra+=nuevaCom[i].precioTotalxUnidad;
            break;

        case 15:
            nuevaCom[i].precioUnidad=115;
            printf("\rIngrese la cantidad de EXPRIMIDO :");
            scanf("%d", &items);
            totalXproducto=items*115;
            nuevaCom[i].cantItems=items;

            strcpy(nuevaCom[i].descripcion, "EXPRIMIDO");
            nuevaCom[i].precioTotalxUnidad=(float)items*115;
            printf("\n %d \t  %s \t\t\t | %.2f | \t | %.2f | ", nuevaCom[i].cantItems, nuevaCom[i].descripcion, nuevaCom[i].precioUnidad,nuevaCom[i].precioTotalxUnidad);
            contTotalCompra+=nuevaCom[i].precioTotalxUnidad;
            break;

        case 16:
            nuevaCom[i].precioUnidad=150;
            printf("\rIngrese la cantidad de LICUADOS :");
            scanf("%d", &items);
            totalXproducto=items*150;
            nuevaCom[i].cantItems=items;

            strcpy(nuevaCom[i].descripcion, "LICUADOS");
            nuevaCom[i].precioTotalxUnidad=(float)items*150;
            printf("\n %d \t  %s \t\t\t | %.2f | \t | %.2f | ", nuevaCom[i].cantItems, nuevaCom[i].descripcion, nuevaCom[i].precioUnidad,nuevaCom[i].precioTotalxUnidad);
            contTotalCompra+=nuevaCom[i].precioTotalxUnidad;
            break;

        case 17:
            nuevaCom[i].precioUnidad=150;
            printf("\rIngrese la cantidad de mil  MILK SHAKE :");
            scanf("%d", &items);
            totalXproducto=items*150;
            nuevaCom[i].cantItems=items;

            strcpy(nuevaCom[i].descripcion, "MILK SHAKE");
            nuevaCom[i].precioTotalxUnidad=(float)items*150;
            printf("\n %d \t  %s \t\t\t | %.2f | \t | %.2f | ", nuevaCom[i].cantItems, nuevaCom[i].descripcion, nuevaCom[i].precioUnidad,nuevaCom[i].precioTotalxUnidad);
            contTotalCompra+=nuevaCom[i].precioTotalxUnidad;
            break;

        case 18:
            nuevaCom[i].precioUnidad=50;
            printf("\rIngrese la cantidad de MEDIA LUNA :");
            scanf("%d", &items);
            totalXproducto=items*50;
            nuevaCom[i].cantItems=items;

            strcpy(nuevaCom[i].descripcion, "MEDIA LUNA");
            nuevaCom[i].precioTotalxUnidad=(float)items*50;
            printf("\n %d \t  %s \t\t\t | %.2f | \t | %.2f | ", nuevaCom[i].cantItems, nuevaCom[i].descripcion, nuevaCom[i].precioUnidad,nuevaCom[i].precioTotalxUnidad);
            contTotalCompra+=nuevaCom[i].precioTotalxUnidad;
            break;

        case 19:
            nuevaCom[i].precioUnidad=150;
            printf("\rIngrese la cantidad de TORTA  DE CHOCOLATE :");
            scanf("%d", &items);
            totalXproducto=items*150;
            nuevaCom[i].cantItems=items;

            strcpy(nuevaCom[i].descripcion, "TORTA DE CHOCOLATE");
            nuevaCom[i].precioTotalxUnidad=(float)items*50;
            printf("\n %d \t  %s \t\t\t | %.2f | \t | %.2f | ", nuevaCom[i].cantItems, nuevaCom[i].descripcion, nuevaCom[i].precioUnidad,nuevaCom[i].precioTotalxUnidad);
            contTotalCompra+=nuevaCom[i].precioTotalxUnidad;
            break;
        case 20:
            nuevaCom[i].precioUnidad=130;
            printf("\rIngrese la cantidad de PASTA FROLA :");
            scanf("%d", &items);
            totalXproducto=items*130;
            nuevaCom[i].cantItems=items;

            strcpy(nuevaCom[i].descripcion, "PASTA FROLA");
            nuevaCom[i].precioTotalxUnidad=(float)items*130;
            printf("\n %d \t  %s \t\t\t | %.2f | \t | %.2f | ", nuevaCom[i].cantItems, nuevaCom[i].descripcion, nuevaCom[i].precioUnidad,nuevaCom[i].precioTotalxUnidad);
            contTotalCompra+=nuevaCom[i].precioTotalxUnidad;
            break;
        case 21:
            nuevaCom[i].precioUnidad=150;
            printf("\rIngrese la cantidad de TOSTADOS :");
            scanf("%d", &items);
            totalXproducto=items*150;
            nuevaCom[i].cantItems=items;

            strcpy(nuevaCom[i].descripcion, "TOSTADOS");
            nuevaCom[i].precioTotalxUnidad=(float)items*150;
            printf("\n %d \t  %s \t\t\t | %.2f | \t | %.2f | ", nuevaCom[i].cantItems, nuevaCom[i].descripcion, nuevaCom[i].precioUnidad,nuevaCom[i].precioTotalxUnidad);
            contTotalCompra+=nuevaCom[i].precioTotalxUnidad;
            break;

        }

        printf("\n\t\t DESEA CONTINUAR? s/n\n");
        scanf("%s", &control2);
        i++;

    }
    while(control2=='s' && control2 !='S');

    nuevaCom[j].totalCompra = contTotalCompra;

    CompraTotal(nuevaCom,i);

    aux=insertarCompra(nuevaCom, i);
    if (aux==1)
    {
        printf("\n\tEl producto fue insertado correctamente\n");
        system("pause");

    }
    else
    {
        printf("\n\tOcurrió un error al intentar insertar el producto\n");
        printf("\tInténtelo mas tarde\n");
    }

    return i;
}

stCompra CompraTotal(stCompra * compra, int v)
{
    int i, j=0;
    printf("\n\n \t\t\t FACTURA C\n");
    printf("\n| Cantidad  | \t    Descripcion    \t\t| valor x unidad |\t valor total |\n");

    for(i=0; i<v; i++)
    {
        printf("\n|    %d    ", compra[i].cantItems);
        printf("|%s \t\t\t", compra[i].descripcion);
        printf("|\t %.2f", compra[i].precioUnidad);
        printf("|\t %.2f", compra[i].precioTotalxUnidad);
    }

    printf("\n\n\nTotal de la Compra \t\t\t\t\t %.2f\n", compra[j].totalCompra);
    system("pause");
}

int insertarCompra(stCompra compra[], int validos)///char nombrearchivo
{
    FILE * pArchcompra;
    char insercion;

    /* Abre el archivo para agregar datos al final */
    pArchcompra = fopen(ArchCompras, "ab");	/* Añade datos al final. Si el archivo no existe, es creado */
    if (pArchcompra == NULL)   /* Si no se pudo abrir el archivo, el valor de archivo es NULL */
    {
        insercion = 0;
        printf("Ocurrio un error al intentar abiri el archivo\n");
    }
    else
    {
        fwrite(compra, sizeof(compra), 1, pArchcompra);
        insercion = 1;

        /* Cierra el archivo */
        fclose(pArchcompra);
    }

    return insercion;
}
/* ***** para que ingrese el ide del usuario****/

void mostrarTodasLasCompras()
{
    stCompra aux;
    FILE * archCompra = fopen(ArchCompras, "rb");

    int i, cont=0, j;

    if(archCompra!=NULL)
    {
        while(fread(&aux, sizeof(stCompra),1,archCompra)>0);
        {

        }

    }



}

//void MostrarComprasUnCliente()
//{
//    stCompra compra;
//    int i=0, idCliente;
//
//    FILE * pArchCompras=fopen(ArchCompras,"rb");
//
//    if(pArchCompras)
//    {
//        if(compra.idAsociado == idCliente)
//        {
//            while(fread(&compra,sizeof(stCompra),1,pArchCompras)>0 &&compra.idAsociado==idCliente)
//            {
//                printf("ID cliente : %d",compra.idAsociado);
//                printf("numero de pedido : %d",compra.cantItems);
//                printf("\n|    %d    ", compra.cantItems);
//                printf("|%s \t\t\t", compra.descripcion);
//                printf("|\t %.2f", compra.precioUnidad);
//                printf("|\t %.2f", compra.precioTotalxUnidad);
//                printf("\n\n\nTotal de la Compra \t\t\t\t\t %.2f\n", compra.totalCompra);
//            }
//        }
//    }
//    fclose(pArchCompras);
//}

int NumRegistros()
{
    FILE * pArchCompra;
    int numeroRegistros;

    /* Se abre para lectura el fichero */
    pArchCompra = fopen(ArchCompras, "rb");

    /* Nos situamos al final del mismo */
    fseek(pArchCompra, 0, SEEK_END);

    /* ftell devuelve el numero de bytes desde el principio del fichero
       hasta la posicion actual que es el final del fichero */
    numeroRegistros = ftell(pArchCompra)/sizeof(stCompra);
    fclose(pArchCompra);
    return numeroRegistros;
}

int todosLosProductos()
{
    int i=0;
    printf("\t\t\t\t ELIJA EL PRODUCTO\n");
    printf("\t 1- Cafe Jarrito $50  \t\t 2-Cafe doble $55 \t\t 3- Moka $60\n");
    printf("\t 4- Descafeinado $65 \t\t 5-Cafe con leche $65 \t\t 6 - Cafe con crema\n");
    printf("\t 7- Capuccino 70 \t\t 8- Cafe irlandes $65 \t\t 9- Te $ 62\n");
    printf("\t 10- Te saborizado $80 \t\t 11- Te con limon $85 \t\t 12- Te con leche $95\n");
    printf("\t 13- Submarino $140 \t\t 14- Chocolatada $80 \t\t 15 Exprimidos $125\n");
    printf("\t 15- Licuado $150 \t\t 17 Medialunas $50  \t\t 18- Milk Shake $150\n");
    printf("\t 19- Tota de chocoolate $ 150\t 20- Pasta frula $130  \t\t 21- Tostados\n");
    scanf("%d",&i);
    return i;
}

/******************************************FIN FUNCIONES COMPRAS******************************************/


int leecad(char *cad, int n)
{
    int i, c;

    /* Hay que verificar si el buffer está limpio o si hay un '\n'
      dejado por scanf y, en ese caso, limpiarlo:
    */

    /* 1 COMPROBACIÓN DE DATOS INICIALES EN EL BUFFER */

    /* Empezamos leyendo el primer caracter que haya en la entrada. Si es
      EOF, significa que no hay nada por leer, así que cerramos la cadena,
      dejándola "vacía" y salimos de la función retornando un valor de 0
      o falso, para indicar que hubo un error */
    c = getchar();
    if (c == EOF)
    {
        cad[0] = '\0';
        return 0;
    }

    /* Si el valor leído es '\n', significa que había un caracter de nueva línea
    dejado por un scanf o función similar. Simplemente inicializamos i a 0,
    para indicar que los siguientes caracteres que leamos iremos asignando a
    partir del primer caracter de la cadena. */
    if (c == '\n')
    {
        i = 0;
    }
    else
    {
        /* Si no había un '\n', significa que el caracter que leímos es el primer
          caracter de la cadena introducida. En este caso, lo guardamos en la
          posición 0 de cad, e inicializamos i a 1, porque en este caso, como ya
          tenemos el primer caracter de la cadena, continuaremos agregando
          caracteres a partir del segundo.

        */
        cad[0] = c;
        i = 1;
    }

    /* 2. LECTURA DE LA CADENA */

    /* El for empieza con un ; porque estamos omitiendo la inicialización del contador,
    ya que fue inicializado en el punto anterior.
    Este código lee un caracter a la vez,lo agrega a cad, y se repite hasta que
    se encuentre un fin de línea, fin de archivo, o haya leído la cantidad máxima
    de caracteres que se le indicó. Luego, cierra la cadena agregando un '\0'
    al final. Todo esto es muy similar a la forma en que los compiladores suelen
    implementar la función fgets, sólo que en lugar de getchar usan getc o fgetc
    */
    for (; i < n - 1 && (c = getchar()) != EOF && c != '\n'; i++)
    {
        cad[i] = c;
    }
    cad[i] = '\0';

    /*3. LIMPIEZA DEL BUFFER */

    /* Finalmente limpiamos el buffer si es necesario */
    if (c != '\n' && c != EOF) /* es un caracter */
        while ((c = getchar()) != '\n' && c != EOF);

    /* La variable c contiene el último caracter leído. Recordemos que había 3 formas
    de salir del for: que hayamos encontrando un '\n', un EOF, o que hayamos llegado
    al máximo de caracteres que debemos leer. Si se da cualquiera de los dos
    primeros casos, significa que leímos todo lo que había en el buffer, por lo que
    no hay nada que limpiar. En el tercer caso, el usuario escribió más caracteres
    de los debidos, que aún están en el buffer, por lo que hay que quitarlos, para
    lo cual usamos el método que vimos poco más arriba
    */

    return 1;
}

/* TITULO DE TODOS LAS PANTALLAS*/
void tituloPrincipal()
{
    int i;
    printf("\n     ======================================================================\n");
    printf("\t\t\t     PROJECTO DE LABORATORIO COMISION 8\n");
    printf("\t\t\t\t Profesor Sonvico, Gustavo\n");
    printf("\t\t    Vermu con Papas Fritas | Jaime - Suarez - Miranda \n");
    printf("     ======================================================================\n");

    i = 0;
    putchar('\n');
    for (; i < 80; i++)
    {
        putchar('_');
    }
}




int buscarMenorAlumno(stCompra A[ ], int pos, int validos)
{
    int posMenor = pos;
    stCompra menor = A[pos];

    for(int i=pos+1; i<validos; i++) {
        if( A[i].totalCompra< menor.totalCompra) {
            posMenor = i;
            menor = A[i];
        }
    }
    return posMenor;
}





