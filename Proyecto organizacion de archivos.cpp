#include <conio.h>
#include <locale.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <windows.h>

#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

#define MAX 1000
#define NUMBER_OF_SLOTS 100

using namespace std;

/****************************************
 * Utilerías
 ***************************************/

//Función que espera a que presiones espacio
void escucharEspacio() {
    cout << "\t\tPresione espacio para continuar...";
    bool con = true;
    while (con) {
        //Solo si es la ventana activa
        if (GetConsoleWindow() == GetForegroundWindow()) {
            if (GetKeyState(' ') & 0x8000) {
                while (GetKeyState(' ') & 0x8000) {
                }
                con = false;
            }
        }
    }
}

void escucharEspacio(int i) {
    cout << "Presione espacio para continuar...";
    bool con = true;
    while (con) {
        //Solo si es la ventana activa
        if (GetConsoleWindow() == GetForegroundWindow()) {
            if (GetKeyState(' ') & 0x8000) {
                while (GetKeyState(' ') & 0x8000) {
                }
                con = false;
            }
        }
    }
}

//Función que valida el código de un producto
//Si es valida regresa true, y false si no
bool validarCodigo(char codigo[]) {
    char caracter;
    bool esNumero = false;
    bool esLetra = false;

    bool codigoValido = false;

    //Verifica su longitud
    string cadena = codigo;
    if (cadena.length() > 6 || cadena.length() == 0) {
        return false;
    }

    //Verifica que los primeros sean letras y los siguientes, números
    for (int i = 0; i < 6; i++) {
        caracter = codigo[i];
        for (int j = 48; j <= 57; j++) {
            if (caracter == j) {
                esNumero = true;
                esLetra = false;
            }
        }
        for (int j = 97; j <= 122; j++) {
            if (caracter == j) {
                esNumero = false;
                esLetra = true;
            }
        }
        for (int j = 65; j <= 90; j++) {
            if (caracter == j) {
                esNumero = false;
                esLetra = true;
            }
        }

        if (esNumero == false && esLetra == false) {
            return false;
        }
        if ((i == 0 || i == 1) && esNumero) {
            return false;
        }
        if ((i != 0 && i != 1) && esLetra) {
            return false;
        }

        esNumero = false;
        esLetra = false;
    }
    return true;
}

//Función que pide un número entero y ayuda a prevenir errores
int pedirEntero(string peticion) {
    string str;
    cout << peticion;

    fflush(stdin);
    cin >> str;
    fflush(stdin);

    //Se llama recursivamente hasta que el usuario digite una opción correcta
    try {
        return stoi(str);
    }
    catch (...) {
        cout << "\n\t\tDebe ingresar un entero!" << endl;
        return pedirEntero(peticion);
    }
}

//Función que pide un número long long sin signo y ayuda a prevenir errores
unsigned long long pedirUnsignedLongLong(string peticion) {
    string str;
    cout << peticion;

    fflush(stdin);
    cin >> str;
    fflush(stdin);

    //Se llama recursivamente hasta que el usuario digite una opción correcta
    try {
        return stoull(str);
    }
    catch (...) {
        cout << "\n\n\t\tDebe ingresar un entero!" << endl;
        return pedirUnsignedLongLong(peticion);
    }
}

//Función que pide un número flotante y ayuda a prevenir errores
float pedirFlotante(string peticion) {
    string str;
    cout << peticion;

    fflush(stdin);
    cin >> str;
    fflush(stdin);

    //Se llama recursivamente hasta que el usuario digite una opción correcta
    try {
        return stof(str);
    }
    catch (...) {
        cout << "\n\t\tDebe ingresar un flotante!" << endl;
        return pedirFlotante(peticion);
    }
}

//Función que escucha las teclas
int escucharTecla(int nOpciones) {
    char letras[] = {'U', 'N', 'E', 'I', 'F', 'A', 'Y', 'S'};
    //Entra a un bucle que se rompe cuando pulsas una tecla indicada
    while (true) {
        //Solo si es la ventana activa
        if (GetConsoleWindow() == GetForegroundWindow()) {
            //Verifiva las opciones que usan ctrl+KEY
            for (int i = 0; i < nOpciones; i++) {
                if ((GetKeyState(VK_CONTROL) & 0x8000) && (GetKeyState(letras[i]) & 0x8000)) {
                    while ((GetKeyState(VK_CONTROL) & 0x8000) && (GetKeyState(letras[i]) & 0x8000)) {
                    }
                    return i + 1;
                }
            }
            //Verifica las teclas numéricas
            for (int i = 49; i <= 49 + (nOpciones - 1); i++) {
                if (GetKeyState(i) & 0x8000) {
                    while (GetKeyState(i) & 0x8000) {
                    }
                    return i - 48;
                }
            }
        }
    }
}

//Ayuda para centrar el texto
void substring(char *cadena, char *subcadena, int inicio, int longitud) {
    int i;

    for (i = 0; i < longitud && inicio + i < strlen(cadena); i++)
        subcadena[i] = cadena[inicio + i];

    subcadena[i] = '\0';
}

void centrar_linea(char *linea, int ancho) {
    int i, espacios;
    espacios = (ancho - strlen(linea)) / 2;

    for (i = 0; i < espacios; i++)
        printf(" ");

    printf("%s", linea);
}

void centrar_cadena(char *cadena, int ancho) {
    char subcadena[MAX];
    int i, total;

    total = (int)ceil((float)strlen(cadena) / ancho);

    for (i = 0; i < total; i++) {
        substring(cadena, subcadena, i * ancho, ancho);
        centrar_linea(subcadena, ancho);
    }
}

void derecha_linea(char *linea, int ancho) {
    int i, espacios;
    espacios = ancho - strlen(linea);

    for (i = 0; i < espacios; i++)
        printf(" ");

    printf("%s", linea);
}

void derecha_cadena(char *cadena, int ancho) {
    char subcadena[MAX];
    int i, total;

    total = (int)ceil((float)strlen(cadena) / ancho);

    for (i = 0; i < total; i++) {
        substring(cadena, subcadena, i * ancho, ancho);
        derecha_linea(subcadena, ancho);
    }
}

/****************************************
 * Declaración de los struct
 ***************************************/
//Productos
typedef struct
{
    char codigo[7];
    char color[20];
    char marca[20];
    char modelo[20];
    char proveedor[20];
    float costoComprado;
    float costoVendido;
    int existencia;
    int unidadesCompradas;
} tproducto;

struct node {
    tproducto product;
    struct node *next;
};
typedef struct node *Tlist;

//Proveedores
typedef struct {
    char clave[20];
    char nombre[20];
    unsigned long long telefono;
} Proveedor;

//Vendedores
typedef struct {
    int clave;
    char nombre[20];
    float salario;
} Vendedor;

//Ventas
typedef struct {
    bool esVenta;  //Venta o reembolzo
    unsigned long long numero;
    unsigned int dia;
    unsigned int mes;
    unsigned int anho;
    char clave[7];
    int cantidad;
    int costo;
    int vendedor;
} Venta;

/****************************************
 * Productos
 ***************************************/

/************
 * Hash
 ************/

//Función hash
//Toma los primeros dos números del código que se le de
int hashFunction(string code) {
    try {
        string number = code.substr(2, 2);
        int n = atoi(number.c_str());
        return n;
    }
    catch (...) {
        cout << "Su productos.dat no corresponde con el que se maneja en este programa" << endl;
        cout << "Borrelo o cambielo de lugar" << endl;
        escucharEspacio();
        exit(0);
    }
    return 0;
}

//Variable arreglo que contendrá todos los productos
Tlist hashTable[NUMBER_OF_SLOTS];

//inicializa el arreglo con valores nulos
void initializeHashTable() {
    for (int i = 0; i < NUMBER_OF_SLOTS; i++) {
        hashTable[i] = NULL;
    }
}

//Llena el arreglo con los datos de productos.dat
//Si no existe simplemente lo deja con los valores nulos
void fillHashTable() {
    FILE *arch;

    arch = fopen("productos.dat", "rb");

    if (arch == NULL) {
        return;
    }

    tproducto producto;

    //Posiciona cada código en su lugar con la función hash
    fread(&producto, sizeof(tproducto), 1, arch);
    while (!feof(arch)) {
        int n = hashFunction(producto.codigo);

        //Usa la lógica de las listas dinámicas
        if (hashTable[n] == NULL) {
            Tlist q = new (struct node);
            q->product = producto;
            q->next = NULL;
            hashTable[n] = q;
        }
        else {
            Tlist t, q = new (struct node);
            q->product = producto;
            q->next = NULL;
            t = hashTable[n];
            while (t->next != NULL) {
                t = t->next;
            }
            t->next = q;
        }

        fread(&producto, sizeof(tproducto), 1, arch);
    }
    fclose(arch);
    return;
}

//Imprime el arreglo
//No es usado en este programa
//Pero es bueno tenerlo por si las moscas
void printHashTable() {
    for (int i = 0; i < NUMBER_OF_SLOTS; i++) {
        if (hashTable[i] == NULL) {
            cout << i << ".-" << endl;
        }
        else {
            Tlist t = hashTable[i];
            cout << i << ".- " << t->product.codigo;
            while (t->next != NULL) {
                t = t->next;
                cout << " -> " << t->product.codigo;
            }
            cout << endl;
        }
    }
}

//Escribe los cambios de el arreglo a productos.dat
void writeFile() {
    FILE *arch;
    arch = fopen("productos.dat", "w+b");
    if (arch == NULL) {
        cout << "Archivo productos.dat no se pudo generar" << endl;
        escucharEspacio();
        exit(1);
    }

    Tlist list;
    tproducto product;

    //Recorre todo el arreglo
    for (int i = 0; i < NUMBER_OF_SLOTS; i++) {
        if (hashTable[i] == NULL) {
        }
        else {
            Tlist t = hashTable[i];
            product = t->product;
            //Solo escribe el producto ya que escribir todo el nodo sería un caos con la memoria
            fwrite(&product, sizeof(tproducto), 1, arch);
            while (t->next != NULL) {
                t = t->next;
                product = t->product;
                fwrite(&product, sizeof(tproducto), 1, arch);
            }
        }
    }
    fclose(arch);
}

/************
 * Archivos de productos
 ************/

//Función que pide los datos de un producto y los escribe en productos.dat
void altaProducto() {
    tproducto producto;
    bool codigoValido = 0;

    /////////////////////////////////////////////////////////////////////////////////////
    //Petición de datos
    /////////////////////////////////////////////////////////////////////////////////////

    //Borra lo que escribimos escuchando las teclas
    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));

    while (!codigoValido) {
        printf("\n\n\t\tIngrese el código del producto: ");
        fflush(stdin);
        gets(producto.codigo);
        codigoValido = validarCodigo(producto.codigo);
        if (!codigoValido) {
            cout << "\n\n\t\tUsted ingreso un codigo invalido!!!" << endl;
            cout << "\n\t\tUn codigo correcto empieza con 2 letras y le siguen 4 numeros.\n"
                 << endl;
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////
    //Verifica que ese código no exista
    //Si no existe lo posiciona en el arreglo y lo escribe en el archivo
    /////////////////////////////////////////////////////////////////////////////////////

    int n = hashFunction(producto.codigo);
    Tlist t = new (struct node);
    t = hashTable[n];
    while (t != NULL) {
        int ret = strncmp(producto.codigo, t->product.codigo, 6);
        if (ret == 0) {
            cout << "\n\n\t\tUn producto con ese código ya existe." << endl;
            cout << "\n\t\tSe cancela todo.";
            return;
        }
        t = t->next;
    }

    fflush(stdin);
    cout << "\n\t\tIngrese el color del producto: ";
    cin.getline(producto.color, 20, '\n');

    fflush(stdin);
    cout << "\n\t\tIngrese la marca del producto: ";
    cin.getline(producto.marca, 20, '\n');

    fflush(stdin);
    cout << "\n\t\tIngrese el modelo del producto: ";
    cin.getline(producto.modelo, 20, '\n');

    fflush(stdin);
    cout << "\n\t\tIngrese el proveedor del producto: ";
    cin.getline(producto.proveedor, 20, '\n');

    /////////////////////////////////////////////////////////////////////////////////////
    //Verifica que exista el proveedor
    /////////////////////////////////////////////////////////////////////////////////////

    FILE *arch;
    arch = fopen("proveedores.dat", "r+b");
    if (arch == NULL) {
        cout << "\n\n\t\tArchivo proveedores.dat no encontrado." << endl;
        cout << "\n\t\tAgregue proveedores.\n"
             << endl;
        cout << "\t\tSe cancela todo.\n"
             << endl;
        return;
    }

    string cod = producto.proveedor;
    Proveedor proveedor;
    int existe = 0;
    fread(&proveedor, sizeof(Proveedor), 1, arch);
    while (!feof(arch)) {
        if (cod == proveedor.clave) {
            existe = 1;
            break;
        }
        fread(&proveedor, sizeof(Proveedor), 1, arch);
    }
    if (existe == 0) {
        printf("\n\n\t\tNo existe un proveedor con dicha clave.");
        cout << "\n\t\tSe cancela todo.\n"
             << endl;
        return;
    }

    fclose(arch);

    fflush(stdin);
    cout << "\n\t\tIngrese el precio al que se compró el producto: ";
    producto.costoComprado = pedirFlotante("");

    fflush(stdin);
    cout << "\n\t\tIngrese el precio al que se vende el producto: ";
    producto.costoVendido = pedirFlotante("");

    fflush(stdin);
    cout << "\n\t\tIngrese cuantas unidades se compraron: ";
    producto.existencia = pedirEntero("");

    producto.unidadesCompradas = producto.existencia;

    /////////////////////////////////////////////////////////////////////////////////////
    //Posiciona el producto en el arreglo
    /////////////////////////////////////////////////////////////////////////////////////

    if (hashTable[n] == NULL) {
        Tlist q = new (struct node);
        q->product = producto;
        q->next = NULL;
        hashTable[n] = q;
    }
    else {
        Tlist q = new (struct node);
        q->product = producto;
        q->next = NULL;
        t = hashTable[n];
        while (t->next != NULL) {
            t = t->next;
        }
        t->next = q;
    }
    cout << endl;

    writeFile();
}

//Función que da de baja un producto
void bajaProducto(string code) {
    //Lo busca en el arreglo y como es archivo directo se puede buscar directamente con la función hash

    //Verifica que esa posición del arreglo no esté vacía
    int n = hashFunction(code);
    if (hashTable[n] == NULL) {
        cout << "\n\t\tNo existe el producto con ese código." << endl;
    }
    else {
        //Si no busca en los nodos hijos
        bool existe = false;
        Tlist t = hashTable[n];
        int i = 1;
        if (t->next == NULL) {
            if (t->product.codigo == code) {
                cout << "\n\t\tCódigo: " << t->product.codigo << endl;
                cout << "\n\t\tColor: " << t->product.color << endl;
                cout << "\n\t\tPrecio al que se compró: " << t->product.costoComprado << endl;
                cout << "\n\t\tPrecio al que se vende: " << t->product.costoVendido << endl;
                cout << "\n\t\tExistencia: " << t->product.existencia << endl;
                cout << "\n\t\tUnidades compradas: " << t->product.unidadesCompradas << endl;
                cout << "\n\t\tMarca: " << t->product.marca << endl;
                cout << "\n\t\tModelo: " << t->product.modelo << endl;
                cout << "\n\t\tProveedor: " << t->product.proveedor << endl;
                cout << endl;

                hashTable[n] = NULL;
                cout << "\n\t\tProducto eliminado." << endl;
                writeFile();
            }
            else {
                cout << "\n\t\tEl producto con ese código no existe." << endl;
            }
        }
        else {
            while (t != NULL) {
                if (t->next->product.codigo == code) {
                    cout << "\n\t\tCódigo: " << t->product.codigo << endl;
                    cout << "\n\t\tColor: " << t->product.color << endl;
                    cout << "\n\t\tPrecio al que se compró: " << t->product.costoComprado << endl;
                    cout << "\n\t\tPrecio al que se vende: " << t->product.costoVendido << endl;
                    cout << "\n\t\tExistencia: " << t->product.existencia << endl;
                    cout << "\n\t\tUnidades compradas: " << t->product.unidadesCompradas << endl;
                    cout << "\n\t\tMarca: " << t->product.marca << endl;
                    cout << "\n\t\tModelo: " << t->product.modelo << endl;
                    cout << "\n\t\tProveedor: " << t->product.proveedor << endl;
                    cout << endl;

                    existe = true;
                    t->next = t->next->next;
                    cout << "\n\t\tProducto eliminado." << endl;
                    writeFile();
                }
                t = t->next;
                i++;
            }
            if (!existe) {
                cout << "\n\t\tEl producto con ese código no existe." << endl;
            }
            cout << endl;
        }
    }
}

//Función que cambia los datos de un producto
void cambioProducto(string code) {
    //Lo busca en el arreglo, píde los datos y como es archivo directo se puede buscar directamente con la función hash

    //Verifica que esa posición del arreglo no esté vacía
    int n = hashFunction(code);
    if (hashTable[n] == NULL) {
        cout << "\n\t\tNo existe el producto con ese código." << endl;
    }
    else {
        //Si no busca en los nodos hijos
        bool existe = false;
        Tlist t = hashTable[n];
        int i = 1;
        while (t != NULL) {
            if (t->product.codigo == code) {
                existe = true;

                //Borra lo que escribimos escuchando las teclas
                FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));

                cout << "\n\t\tCódigo: " << t->product.codigo << endl;
                cout << "\t\tColor: " << t->product.color << endl;
                cout << "\t\tPrecio al que se compró: " << t->product.costoComprado << endl;
                cout << "\t\tPrecio al que se vende: " << t->product.costoVendido << endl;
                cout << "\t\tExistencia: " << t->product.existencia << endl;
                cout << "\t\tUnidades compradas: " << t->product.unidadesCompradas << endl;
                cout << "\t\tMarca: " << t->product.marca << endl;
                cout << "\t\tModelo: " << t->product.modelo << endl;
                cout << "\t\tProveedor: " << t->product.proveedor << endl;
                cout << endl;

                fflush(stdin);
                cout << "\n\t\tIngrese el color del producto: ";
                cin.getline(t->product.color, 20, '\n');

                fflush(stdin);
                cout << "\n\t\tIngrese la marca del producto: ";
                cin.getline(t->product.marca, 20, '\n');

                fflush(stdin);
                cout << "\n\t\tIngrese el modelo del producto: ";
                cin.getline(t->product.modelo, 20, '\n');

                fflush(stdin);
                cout << "\n\t\tIngrese el proveedor del producto: ";
                cin.getline(t->product.proveedor, 20, '\n');

                FILE *arch;
                arch = fopen("proveedores.dat", "r+b");
                if (arch == NULL) {
                    cout << "\n\t\tArchivo proveedores.dat no encontrado." << endl;
                    cout << "\t\tAgregue proveedores" << endl;
                    cout << "\t\tSe cancela todo." << endl;
                    return;
                }

                string cod = t->product.proveedor;
                Proveedor proveedor;
                int existe = 0;
                fread(&proveedor, sizeof(Proveedor), 1, arch);
                while (!feof(arch)) {
                    if (cod == proveedor.clave) {
                        existe = 1;
                        break;
                    }
                    fread(&proveedor, sizeof(Proveedor), 1, arch);
                }
                if (existe == 0) {
                    printf("\n\n\t\tNo existe un proveedor con dicha clave\n");
                    cout << "\n\t\tSe cancela todo" << endl;
                    return;
                }

                fclose(arch);

                fflush(stdin);
                cout << "\n\t\tIngrese el precio al que se compró el producto: ";
                t->product.costoComprado = pedirFlotante("");

                fflush(stdin);
                cout << "\n\t\tIngrese el precio al que se vende el producto: ";
                t->product.costoVendido = pedirFlotante("");

                fflush(stdin);
                cout << "\n\t\tIngrese cuantas unidades se compraron: ";
                t->product.existencia = pedirEntero("");

                t->product.unidadesCompradas = t->product.existencia;

                writeFile();
            }
            t = t->next;
            i++;
        }
        if (!existe) {
            cout << "\n\t\tEl producto con ese código no existe." << endl;
        }
        cout << endl;
    }
}

//Función que busca un producto
void consultaProducto(string code) {
    //Lo busca en el arreglo y como es archivo directo se puede buscar directamente con la función hash

    //Verifica que esa posición del arreglo no esté vacía
    int n = hashFunction(code);
    if (hashTable[n] == NULL) {
        cout << "\n\t\tNo existe el producto con ese código." << endl;
    }
    else {
        //Si no busca en los nodos hijos
        bool existe = false;
        Tlist t = hashTable[n];
        int i = 1;
        while (t != NULL) {
            if (t->product.codigo == code) {
                existe = true;
                cout << "\n\t\tEl producto esta en el indice " << n << " de la tabla en la posicion " << i << endl;
                cout << "\t\tCódigo: " << t->product.codigo << endl;
                cout << "\t\tColor: " << t->product.color << endl;
                cout << "\t\tPrecio al que se compró: " << t->product.costoComprado << endl;
                cout << "\t\tPrecio al que se vende: " << t->product.costoVendido << endl;
                cout << "\t\tExistencia: " << t->product.existencia << endl;
                cout << "\t\tUnidades compradas: " << t->product.unidadesCompradas << endl;
                cout << "\t\tMarca: " << t->product.marca << endl;
                cout << "\t\tModelo: " << t->product.modelo << endl;
                cout << "\t\tProveedor: " << t->product.proveedor << endl;
                cout << endl;
            }
            t = t->next;
            i++;
        }
        if (!existe) {
            cout << "\n\t\tEl producto con ese código no existe." << endl;
        }
        cout << endl;
    }
}

/****************************************
 * Proveedores
 ***************************************/

//Función que da de alta a un proveedor
void altaProveedor() {
    FILE *arch;
    arch = fopen("proveedores.dat", "ab");
    if (arch == NULL) {
        cout << "\n\t\tArchivo proveedores.dat no se pudo generar." << endl;
        return;
    }

    Proveedor proveedor;

    //Borra lo que escribimos escuchando las teclas
    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));

    /////////////////////////////////////////////////////////////////////////////////////
    //Pide los datos
    /////////////////////////////////////////////////////////////////////////////////////

    bool codigoValido = 0;

    fflush(stdin);
    cout << "\n\n\t\tDigite la clave del proveedor: ";
    cin.getline(proveedor.clave, 20, '\n');

    fflush(stdin);
    cout << "\n\t\tDigite el nombre del proveedor: ";
    cin.getline(proveedor.nombre, 20, '\n');

    fflush(stdin);
    cout << "\n\t\tDigite el número telefónico del proveedor: ";
    proveedor.telefono = pedirUnsignedLongLong("");

    fwrite(&proveedor, sizeof(Proveedor), 1, arch);
    fclose(arch);
}

//Función que da de baja a un proveedor
void bajaProveedor() {
    FILE *arch;
    arch = fopen("proveedores.dat", "r+b");
    if (arch == NULL) {
        cout << "\n\n\t\tArchivo proveedores.dat no encontrado." << endl;
        cout << "\t\tAgregue proveedores." << endl;
        return;
    }
    //Borra lo que escribimos escuchando las teclas
    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));

    printf("\n\n\t\tIngrese la clave del proveedor a consultar: ");
    fflush(stdin);
    string cod;
    getline(cin, cod);
    Proveedor proveedor;
    int existe = 0;
    /////////////////////////////////////////////////////////////////////////////////////
    //Lo busca en el archivo secuencialmente
    /////////////////////////////////////////////////////////////////////////////////////
    fread(&proveedor, sizeof(Proveedor), 1, arch);
    while (!feof(arch)) {
        if (cod == proveedor.clave) {
            cout << "\n\t\tClave: " << proveedor.clave << endl;
            cout << "\t\tNombre: " << proveedor.nombre << endl;
            cout << "\t\tTeléfono: " << proveedor.telefono << endl;

            string cadenaVacia = "";

            strcpy(proveedor.clave, cadenaVacia.c_str());
            strcpy(proveedor.nombre, cadenaVacia.c_str());
            proveedor.telefono = 0;

            int pos = ftell(arch) - sizeof(Proveedor);
            fseek(arch, pos, SEEK_SET);
            fwrite(&proveedor, sizeof(Proveedor), 1, arch);
            printf("\n\n\t\tSe borro el proveedor.\n");
            existe = 1;
            break;
        }
        fread(&proveedor, sizeof(Proveedor), 1, arch);
    }
    if (existe == 0)
        printf("\n\n\t\tNo existe un proveedor con dicha clave.\n");
    fclose(arch);
}

//Función que cambia los datos de un proveedor
void cambioProveedor() {
    FILE *arch;
    arch = fopen("proveedores.dat", "r+b");
    if (arch == NULL) {
        cout << "n\n\t\tArchivo proveedores.dat no encontrado." << endl;
        cout << "\t\tAgregue proveedores." << endl;
        return;
    }
    //Borra lo que escribimos escuchando las teclas
    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));

    printf("\n\t\tIngrese la clave del proveedor a consultar: ");
    fflush(stdin);
    string cod;
    getline(cin, cod);
    Proveedor proveedor;
    int existe = 0;
    /////////////////////////////////////////////////////////////////////////////////////
    //Lo busca en el archivo secuencialmente
    /////////////////////////////////////////////////////////////////////////////////////
    fread(&proveedor, sizeof(Proveedor), 1, arch);
    while (!feof(arch)) {
        if (cod == proveedor.clave) {
            cout << "\n\t\tClave: " << proveedor.clave << endl;
            cout << "\t\tNombre: " << proveedor.nombre << endl;
            cout << "\t\tTeléfono: " << proveedor.telefono << endl;

            fflush(stdin);
            cout << "\n\t\tDigite el nombre del proveedor: ";
            cin.getline(proveedor.nombre, 20, '\n');

            fflush(stdin);
            cout << "\n\t\tDigite el número telefónico del proveedor: ";
            proveedor.telefono = pedirUnsignedLongLong("");

            int pos = ftell(arch) - sizeof(Proveedor);
            fseek(arch, pos, SEEK_SET);
            fwrite(&proveedor, sizeof(Proveedor), 1, arch);
            printf("\n\n\t\tSe modifico el proveedor.\n");
            existe = 1;
            break;
        }
        fread(&proveedor, sizeof(Proveedor), 1, arch);
    }
    if (existe == 0)
        printf("\n\n\t\tNo existe un proveedor con dicha clave.\n");
    fclose(arch);
}

//Función que consulta los datos de un proveedor
void consultaProveedor() {
    FILE *arch;
    arch = fopen("proveedores.dat", "r+b");
    if (arch == NULL) {
        cout << "\n\n\t\tArchivo proveedores.dat no encontrado." << endl;
        cout << "\t\tAgregue proveedores." << endl;
        return;
    }
    //Borra lo que escribimos escuchando las teclas
    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));

    printf("\n\t\tIngrese la clave del proveedor a consultar: ");
    fflush(stdin);
    string cod;
    getline(cin, cod);
    Proveedor proveedor;
    int existe = 0;
    /////////////////////////////////////////////////////////////////////////////////////
    //Lo busca en el archivo secuencialmente
    /////////////////////////////////////////////////////////////////////////////////////
    fread(&proveedor, sizeof(Proveedor), 1, arch);
    while (!feof(arch)) {
        if (cod == proveedor.clave) {
            cout << "\n\t\tClave: " << proveedor.clave << endl;
            cout << "\t\tNombre: " << proveedor.nombre << endl;
            cout << "\t\tTeléfono: " << proveedor.telefono << endl;

            existe = 1;
            break;
        }
        fread(&proveedor, sizeof(Proveedor), 1, arch);
    }
    if (existe == 0)
        printf("\n\t\tNo existe un proveedor con dicha clave.\n");
    fclose(arch);
}

/****************************************
 * Vendedores
 ***************************************/

//Función que da de alta a un vendedor
void altaVendedor() {
    FILE *arch;
    arch = fopen("vendedores.dat", "ab");
    if (arch == NULL) {
        cout << "\n\n\t\tArchivo vendedores.dat no pudo ser generado." << endl;
        return;
    }

    Vendedor vendedor;

    /////////////////////////////////////////////////////////////////////////////////////
    //Pide los datos
    /////////////////////////////////////////////////////////////////////////////////////

    //Borra lo que escribimos escuchando las teclas
    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));

    bool codigoValido = 0;

    fflush(stdin);
    vendedor.clave = pedirEntero("\n\n\t\tDigite la clave numérica del vendedor: ");

    fflush(stdin);
    cout << "\n\t\tDigite el nombre del vendedor: ";
    cin.getline(vendedor.nombre, 20, '\n');

    fflush(stdin);
    vendedor.salario = pedirFlotante("\n\t\tDigite el salario del vendedor: ");

    fwrite(&vendedor, sizeof(Vendedor), 1, arch);
    fclose(arch);
}

//Función que da de baja a un vendedor
void bajaVendedor() {
    FILE *arch;
    arch = fopen("vendedores.dat", "r+b");
    if (arch == NULL) {
        cout << "\n\n\t\tArchivo vendedores.dat no encontrado." << endl;
        cout << "\t\tAgregue vendedores." << endl;
        return;
    }
    //Borra lo que escribimos escuchando las teclas
    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));

    Vendedor vendedor;

    fflush(stdin);
    int cod = pedirEntero("\n\t\tIngrese la clave del vendedor a consultar: ");

    /////////////////////////////////////////////////////////////////////////////////////
    //Lo busca en el archivo secuencialmente
    /////////////////////////////////////////////////////////////////////////////////////

    int existe = 0;
    fread(&vendedor, sizeof(Vendedor), 1, arch);
    while (!feof(arch)) {
        if (cod == vendedor.clave) {
            cout << "\n\t\tClave: " << vendedor.clave << endl;
            cout << "\t\tNombre: " << vendedor.nombre << endl;
            cout << "\t\tSalario: " << vendedor.salario << endl;

            string cadenaVacia = "";

            vendedor.clave = 0;
            strcpy(vendedor.nombre, cadenaVacia.c_str());
            vendedor.salario = 0;

            int pos = ftell(arch) - sizeof(Vendedor);
            fseek(arch, pos, SEEK_SET);
            fwrite(&vendedor, sizeof(Vendedor), 1, arch);
            printf("\n\n\t\tSe borro el vendedor.\n");
            existe = 1;
            break;
        }
        fread(&vendedor, sizeof(Vendedor), 1, arch);
    }
    if (existe == 0)
        printf("\n\n\t\tNo existe un vendedor con dicha clave.\n");
    fclose(arch);
}

//Función que cambia los datos de un vendedor
void cambioVendedor() {
    FILE *arch;
    arch = fopen("vendedores.dat", "r+b");
    if (arch == NULL) {
        cout << "\n\n\t\tArchivo vendedores.dat no encontrado" << endl;
        cout << "\t\tAgregue vendedores" << endl;
        return;
    }
    //Borra lo que escribimos escuchando las teclas
    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
    Vendedor vendedor;

    fflush(stdin);
    int cod = pedirEntero("\n\n\t\tIngrese la clave del vendedor a consultar: ");

    /////////////////////////////////////////////////////////////////////////////////////
    //Lo busca en el archivo secuencialmente
    /////////////////////////////////////////////////////////////////////////////////////

    int existe = 0;
    fread(&vendedor, sizeof(Vendedor), 1, arch);
    while (!feof(arch)) {
        if (cod == vendedor.clave) {
            cout << "\n\t\tClave: " << vendedor.clave << endl;
            cout << "\t\tNombre: " << vendedor.nombre << endl;
            cout << "\t\tSalario: " << vendedor.salario << endl;

            fflush(stdin);
            cout << "\t\tDigite el nombre del vendedor: ";
            cin.getline(vendedor.nombre, 20, '\n');

            fflush(stdin);
            vendedor.salario = pedirFlotante("\n\t\tDigite el salario del vendedor: ");

            int pos = ftell(arch) - sizeof(Vendedor);
            fseek(arch, pos, SEEK_SET);
            fwrite(&vendedor, sizeof(Vendedor), 1, arch);
            printf("\n\t\tSe modifico el vendedor.\n");
            existe = 1;
            break;
        }
        fread(&vendedor, sizeof(Vendedor), 1, arch);
    }
    if (existe == 0)
        printf("\n\t\tNo existe un vendedor con dicha clave.\n");
    fclose(arch);
}

//Función que consulta los datos de un vendedor
void consultaVendedor() {
    FILE *arch;
    arch = fopen("vendedores.dat", "r+b");
    if (arch == NULL) {
        cout << "\n\t\tArchivo vendedores.dat no encontrado" << endl;
        cout << "\t\tAgregue vendedores" << endl;
        return;
    }
    //Borra lo que escribimos escuchando las teclas
    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
    Vendedor vendedor;

    fflush(stdin);
    int cod = pedirEntero("\n\n\t\tIngrese la clave del vendedor a consultar: ");

    /////////////////////////////////////////////////////////////////////////////////////
    //Lo busca en el archivo secuencialmente
    /////////////////////////////////////////////////////////////////////////////////////

    int existe = 0;
    fread(&vendedor, sizeof(Vendedor), 1, arch);
    while (!feof(arch)) {
        if (cod == vendedor.clave) {
            cout << "\n\t\tClave: " << vendedor.clave << endl;
            cout << "\t\tNombre: " << vendedor.nombre << endl;
            cout << "\t\tSalario: " << vendedor.salario << endl;

            existe = 1;
            break;
        }
        fread(&vendedor, sizeof(Vendedor), 1, arch);
    }
    if (existe == 0)
        printf("\n\t\tNo existe un vendedor con dicha clave.\n");
    fclose(arch);
}

/****************************************
 * Ventas
 ***************************************/
//Función que da de alta una venta
void altaVenta() {
    FILE *arch;
    arch = fopen("ventas.dat", "ab");
    if (arch == NULL) {
        cout << "\n\n\t\tArchivo ventas.dat no pudo ser generado." << endl;
        return;
    }

    Venta venta;

    /////////////////////////////////////////////////////////////////////////////////////
    //Pide los datos
    /////////////////////////////////////////////////////////////////////////////////////

    venta.esVenta = true;

    //Borra lo que escribimos escuchando las teclas
    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));

    bool codigoValido = 0;

    while (!codigoValido) {
        printf("\n\n\t\tIngrese el código del producto: ");
        fflush(stdin);
        cin.getline(venta.clave, 7, '\n');
        codigoValido = validarCodigo(venta.clave);
        if (!codigoValido) {
            cout << "\n\t\tUsted ingreso un codigo invalido!!!" << endl;
            cout << "\n\t\tUn codigo correcto empieza con 2 letras y le siguen 4 numeros.\n"
                 << endl;
        }
    }

    string code = venta.clave;

    Tlist t;

    /////////////////////////////////////////////////////////////////////////////////////
    //Verifica que exista el código
    /////////////////////////////////////////////////////////////////////////////////////

    int n = hashFunction(code);
    if (hashTable[n] == NULL) {
        cout << "\n\t\tNo existe el producto con ese código." << endl;
        cout << "\t\tSe cancela todo." << endl;
        return;
    }
    else {
        bool existe = false;
        t = hashTable[n];
        int i = 1;
        while (t != NULL) {
            if (t->product.codigo == code) {
                existe = true;
                break;
            }
            t = t->next;
            i++;
        }
        if (!existe) {
            cout << "\n\n\t\tEl producto con ese código no existe." << endl;
            cout << "\t\tSe cancela todo." << endl;
            return;
        }
    }

    fflush(stdin);
    cout << "\n\n\t\tDigite el código numerico del vendedor: ";
    venta.vendedor = pedirEntero("");

    /////////////////////////////////////////////////////////////////////////////////////
    //Verifica que el vendedor exista
    /////////////////////////////////////////////////////////////////////////////////////

    FILE *archV;
    archV = fopen("vendedores.dat", "r+b");
    if (archV == NULL) {
        cout << "\n\n\t\tArchivo vendedores.dat no encontrado." << endl;
        cout << "\t\tAgregue vendedores." << endl;
        cout << "\t\tSe cancela todo." << endl;
        return;
    }
    //Borra lo que escribimos escuchando las teclas
    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
    Vendedor vendedor;

    fflush(stdin);
    int cod = venta.vendedor;

    int existe = 0;
    fread(&vendedor, sizeof(Vendedor), 1, archV);
    while (!feof(archV)) {
        if (cod == vendedor.clave) {
            existe = 1;
            break;
        }
        fread(&vendedor, sizeof(Vendedor), 1, archV);
    }
    if (existe == 0) {
        printf("\n\n\t\tNo existe un vendedor con dicha clave.\n");
        cout << "\t\tSe cancela todo." << endl;
        return;
    }

    fclose(archV);

    bool band = true;

    /////////////////////////////////////////////////////////////////////////////////////
    //Verifica que las cantidades sean congruentes
    /////////////////////////////////////////////////////////////////////////////////////

    while (band) {
        fflush(stdin);
        venta.cantidad = pedirEntero("\n\n\t\tDigite la cantidad vendida: ");

        if (t->product.existencia < venta.cantidad) {
            cout << "\n\t\tSe están tratando de comprar" << venta.cantidad << "y solo hay " << t->product.existencia;
            return;
        }
        else if (venta.cantidad <= 0) {
            if (venta.cantidad == 0) {
                cout << "\n\n\t\tNo puede vender 0 productos." << endl;
                return;
            }
            if (venta.cantidad < 0) {
                cout << "\n\n\t\tNo puede ingresar un número negativo." << endl;
                return;
            }
        }
        else {
            band = false;
            t->product.existencia -= venta.cantidad;
            writeFile();
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////
    //Genera automáticamente la fecha y el número de la compra
    /////////////////////////////////////////////////////////////////////////////////////

    time_t now = time(0);

    tm *ltm = localtime(&now);

    venta.dia = ltm->tm_mday;
    venta.mes = 1 + ltm->tm_mon;
    venta.anho = 1900 + ltm->tm_year;

    string str = to_string(venta.anho - 2000) + to_string(venta.mes) + to_string(venta.dia) + to_string(1 + ltm->tm_hour) + to_string(1 + ltm->tm_min) + to_string(1 + ltm->tm_sec);

    venta.numero = stoull(str);

    fwrite(&venta, sizeof(Venta), 1, arch);
    fclose(arch);
}

//Función que da de alta una venta
void bajaVenta() {
    FILE *arch;
    arch = fopen("ventas.dat", "ab");
    if (arch == NULL) {
        cout << "\n\n\t\tArchivo ventas.dat no se pudo generar" << endl;
        return;
    }

    Venta venta;

    /////////////////////////////////////////////////////////////////////////////////////
    //Pide los datos
    /////////////////////////////////////////////////////////////////////////////////////

    venta.esVenta = false;

    //Borra lo que escribimos escuchando las teclas
    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));

    bool codigoValido = 0;

    while (!codigoValido) {
        printf("\n\n\t\tIngrese el código del producto: ");
        fflush(stdin);
        cin.getline(venta.clave, 7, '\n');
        codigoValido = validarCodigo(venta.clave);
        if (!codigoValido) {
            cout << "\n\n\t\tUsted ingreso un codigo invalido!!!" << endl;
            cout << "\n\t\tUn codigo correcto empieza con 2 letras y le siguen 4 numeros.\n"
                 << endl;
        }
    }

    string code = venta.clave;

    Tlist t;

    /////////////////////////////////////////////////////////////////////////////////////
    //Verifica que exista un producto con ese código
    /////////////////////////////////////////////////////////////////////////////////////

    int n = hashFunction(code);
    if (hashTable[n] == NULL) {
        cout << "\n\n\t\tNo existe el producto con ese código." << endl;
        cout << "\t\tSe cancela todo." << endl;
        return;
    }
    else {
        bool existe = false;
        t = hashTable[n];
        int i = 1;
        while (t != NULL) {
            if (t->product.codigo == code) {
                existe = true;
                break;
            }
            t = t->next;
            i++;
        }
        if (!existe) {
            cout << "\n\t\tEl producto con ese código no existe" << endl;
            cout << "\t\tSe cancela todo" << endl;
            return;
        }
    }

    fflush(stdin);
    cout << "\n\n\t\tDigite el código numerico del vendedor: ";
    venta.vendedor = pedirEntero("");

    /////////////////////////////////////////////////////////////////////////////////////
    //Verifica que el vendedor exista
    /////////////////////////////////////////////////////////////////////////////////////

    FILE *archV;
    archV = fopen("vendedores.dat", "r+b");
    if (archV == NULL) {
        cout << "\n\n\t\tArchivo vendedores.dat no encontrado." << endl;
        cout << "\t\tSe cancela todo." << endl;
        return;
    }
    //Borra lo que escribimos escuchando las teclas
    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
    Vendedor vendedor;

    fflush(stdin);
    int cod = venta.vendedor;

    int existe = 0;
    fread(&vendedor, sizeof(Vendedor), 1, archV);
    while (!feof(archV)) {
        if (cod == vendedor.clave) {
            existe = 1;
            break;
        }
        fread(&vendedor, sizeof(Vendedor), 1, archV);
    }
    if (existe == 0) {
        printf("\n\n\t\tNo existe un vendedor con dicha clave.\n");
        cout << "\t\tSe cancela todo." << endl;
        return;
    }

    fclose(archV);

    bool band = true;

    /////////////////////////////////////////////////////////////////////////////////////
    //Verifica que las cantidades sean congruentes
    /////////////////////////////////////////////////////////////////////////////////////

    while (band) {
        fflush(stdin);
        venta.cantidad = pedirEntero("\n\n\t\tDigite la cantidad de productos en el reembolzo: ");

        if (venta.cantidad <= 0 || venta.cantidad > t->product.unidadesCompradas) {
            if (venta.cantidad == 0) {
                cout << "\n\t\tNo puede reembolzar 0 productos" << endl;
                return;
            }
            if (venta.cantidad < 0) {
                cout << "\n\t\tNo puede ingresar un número negativo" << endl;
                return;
            }
            if (venta.cantidad > t->product.unidadesCompradas) {
                cout << "\n\t\tEstá tratando de reembolzar más de lo que se compró" << endl;
                return;
            }
        }
        else {
            band = false;
            t->product.existencia += venta.cantidad;
            writeFile();
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////
    //Genera automáticamente la fecha y el número de venta
    /////////////////////////////////////////////////////////////////////////////////////

    time_t now = time(0);

    tm *ltm = localtime(&now);

    venta.dia = ltm->tm_mday;
    venta.mes = 1 + ltm->tm_mon;
    venta.anho = 1900 + ltm->tm_year;

    string str = to_string(venta.anho - 2000) + to_string(venta.mes) + to_string(venta.dia) + to_string(1 + ltm->tm_hour) + to_string(1 + ltm->tm_min) + to_string(1 + ltm->tm_sec);

    venta.numero = stoull(str);

    fwrite(&venta, sizeof(Venta), 1, arch);
    fclose(arch);
}

//Función que consulta una venta
//No está implementado y no es usado
//Pero lo dejo por si las moscas
void consultaVenta() {
    FILE *arch;
    arch = fopen("ventas.dat", "r+b");
    if (arch == NULL) {
        cout << "Archivo ventas.dat no encontrado" << endl;
        return;
    }
    //Borra lo que escribimos escuchando las teclas
    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
    Vendedor vendedor;

    fflush(stdin);
    int cod = pedirEntero("Ingrese la clave del vendedor a consultar: ");

    int existe = 0;
    fread(&vendedor, sizeof(Vendedor), 1, arch);
    while (!feof(arch)) {
        if (cod == vendedor.clave) {
            cout << vendedor.clave;
            printf(": %s : ", vendedor.nombre);
            cout << vendedor.salario << endl;

            existe = 1;
            break;
        }
        fread(&vendedor, sizeof(Vendedor), 1, arch);
    }
    if (existe == 0)
        printf("No existe un vendedor con dicha clave\n");
    fclose(arch);
}

/****************************************
 * Reportes en pantalla
 ***************************************/
//Función que imprime el inventario
void inventarioPantalla() {
    cout << "Inventario" << endl;
    for (int i = 0; i < (10 + (20 * 8)); i++) {
        cout << "-";
    }
    cout << endl;

    cout << setw(10) << left << "Clave";
    cout << setw(20) << left << "Modelo";
    cout << setw(20) << left << "Marca";
    cout << setw(20) << left << "Color";
    cout << setw(20) << left << "Precio Venta";
    cout << setw(20) << left << "Precio Compra";
    cout << setw(20) << left << "Existencia";
    cout << setw(20) << left << "Unidades compradas";
    cout << setw(20) << left << "Proveedor";
    cout << endl;

    for (int i = 0; i < (10 + (20 * 8)); i++) {
        cout << "-";
    }
    cout << endl;

    /////////////////////////////////////////////////////////////////////////////////////
    //Imprime directamente
    /////////////////////////////////////////////////////////////////////////////////////

    for (int i = 0; i < NUMBER_OF_SLOTS; i++) {
        if (hashTable[i] == NULL) {
        }
        else {
            Tlist t = hashTable[i];
            cout << setw(10) << left << t->product.codigo;
            cout << setw(20) << left << t->product.modelo;
            cout << setw(20) << left << t->product.marca;
            cout << setw(20) << left << t->product.color;
            cout << setw(20) << left << t->product.costoVendido;
            cout << setw(20) << left << t->product.costoComprado;
            cout << setw(20) << left << t->product.existencia;
            cout << setw(20) << left << t->product.unidadesCompradas;
            cout << setw(20) << left << t->product.proveedor;
            cout << endl;
            while (t->next != NULL) {
                t = t->next;
                cout << setw(10) << left << t->product.codigo;
                cout << setw(20) << left << t->product.modelo;
                cout << setw(20) << left << t->product.marca;
                cout << setw(20) << left << t->product.color;
                cout << setw(20) << left << t->product.costoVendido;
                cout << setw(20) << left << t->product.costoComprado;
                cout << setw(20) << left << t->product.existencia;
                cout << setw(20) << left << t->product.unidadesCompradas;
                cout << setw(20) << left << t->product.proveedor;
                cout << endl;
            }
        }
    }
    for (int i = 0; i < (10 + (20 * 8)); i++) {
        cout << "-";
    }
    cout << endl;
}

//Función que imprime el reporte de ventas
void reporteDeVentasPantalla() {
    cout << "Reporte de ventas" << endl;
    FILE *arch;

    float pc = 0;
    float pv = 0;

    arch = fopen("ventas.dat", "r+b");
    if (arch == NULL) {
        cout << "Archivo ventas.dat no encontrado" << endl;
        return;
    }
    for (int i = 0; i < ((10 * 5) + 15 + (20 * 2)); i++) {
        cout << "-";
    }
    cout << endl;

    cout << setw(10) << left << "Tipo";
    cout << setw(13) << left << "No.";
    cout << setw(15) << left << "Fecha";
    cout << setw(10) << left << "Clave";
    cout << setw(10) << left << "Cantidad";
    cout << setw(20) << left << "Precio Comprado";
    cout << setw(20) << left << "Precio Vendido";
    cout << setw(10) << left << "Vendedor";
    cout << endl;

    for (int i = 0; i < ((10 * 5) + 15 + (20 * 2)); i++) {
        cout << "-";
    }
    cout << endl;

    /////////////////////////////////////////////////////////////////////////////////////
    //Imprime secuencialmente
    /////////////////////////////////////////////////////////////////////////////////////

    Venta venta;
    fread(&venta, sizeof(Venta), 1, arch);
    while (!feof(arch)) {
        if (venta.esVenta) {
            cout << setw(10) << left << "Venta";
        }
        else {
            cout << setw(10) << left << "Reembolzo";
        }

        string fecha = to_string(venta.dia) + "/" + to_string(venta.mes) + "/" + to_string(venta.anho);

        cout << setw(13) << left << venta.numero;
        cout << setw(15) << left << fecha;
        cout << setw(10) << left << venta.clave;
        cout << setw(10) << left << venta.cantidad;

        /////////////////////////////////////////////////////////////////////////////////////
        //Busca el producto con esa clave
        //Para obtener datos como el precio
        /////////////////////////////////////////////////////////////////////////////////////

        string code = venta.clave;
        Tlist t;
        int n = hashFunction(code);
        if (hashTable[n] == NULL) {
            cout << "No existe el producto con ese código" << endl;
        }
        else {
            bool existe = false;
            t = hashTable[n];
            int i = 1;
            while (t != NULL) {
                existe = true;
                if (t->product.codigo == code) {
                    break;
                }
                t = t->next;
                i++;
            }
            if (!existe) {
                cout << "El producto con ese código no existe" << endl;
            }
        }
        cout << setw(20) << left << t->product.costoComprado;

        cout << setw(20) << left << t->product.costoVendido;

        if (venta.esVenta) {
            pc += (t->product.costoComprado * venta.cantidad);
            pv += (t->product.costoVendido * venta.cantidad);
        }
        else {
            pc -= (t->product.costoComprado * venta.cantidad);
            pv -= (t->product.costoVendido * venta.cantidad);
        }
        cout << setw(10) << left << venta.vendedor;
        cout << endl;

        fread(&venta, sizeof(Venta), 1, arch);
    }
    fclose(arch);

    for (int i = 0; i < ((10 * 5) + 15 + (20 * 2)); i++) {
        cout << "-";
    }

    printf("\nInversión: %.2f \n", pc);
    printf("Dinero total recaudado de las ventas: %.2f \n", pv);
    printf("Ganancia: %.2f \n", pv - pc);
}

//Función que imprime el reporte de proveedores
void reporteDeProveedoresPantalla() {
    cout << "Reporte de proveedores" << endl;
    FILE *arch;
    arch = fopen("proveedores.dat", "r+b");
    if (arch == NULL) {
        cout << "Archivo proveedores.dat no encontrado" << endl;
        return;
    }
    for (int i = 0; i < ((20 * 3)); i++) {
        cout << "-";
    }
    cout << endl;

    cout << setw(20) << left << "Clave";
    cout << setw(20) << left << "Nombre";
    cout << setw(20) << left << "Teléfono";
    cout << endl;

    for (int i = 0; i < ((20 * 3)); i++) {
        cout << "-";
    }
    cout << endl;

    /////////////////////////////////////////////////////////////////////////////////////
    //Imprime secuencialmente
    /////////////////////////////////////////////////////////////////////////////////////

    Proveedor proveedor;
    fread(&proveedor, sizeof(Proveedor), 1, arch);
    while (!feof(arch)) {
        cout << setw(20) << left << proveedor.clave;
        cout << setw(20) << left << proveedor.nombre;
        cout << setw(20) << left << proveedor.telefono;

        fread(&proveedor, sizeof(Proveedor), 1, arch);
    }
    cout << endl;
    for (int i = 0; i < ((20 * 3)); i++) {
        cout << "-";
    }
    cout << endl;
    fclose(arch);
}

/****************************************
 * Reportes en archivo de texto
 ***************************************/
//Función que genera un archivo con el inventario
void inventarioArchivo() {
    FILE *arch;
    arch = fopen("Inventario.txt", "w");

    fprintf(arch, "Inventario \n");
    for (int i = 0; i < (10 + (20 * 8)); i++) {
        fprintf(arch, "-");
    }
    fprintf(arch, "\n");

    fprintf(arch, "%-10s %-20s %-20s %-20s %-20s %-20s %-20s %-20s %-20s\n", "Clave", "Modelo", "Marca", "Color", "Precio Venta", "Precio Compra", "Existencia", "Unidades compradas", "Proveedor");
    for (int i = 0; i < (10 + (20 * 8)); i++) {
        fprintf(arch, "-");
    }
    fprintf(arch, "\n");

    /////////////////////////////////////////////////////////////////////////////////////
    //Escribe directamente
    /////////////////////////////////////////////////////////////////////////////////////

    for (int i = 0; i < NUMBER_OF_SLOTS; i++) {
        if (hashTable[i] == NULL) {
        }
        else {
            Tlist t = hashTable[i];
            fprintf(arch, "%-10s %-20s %-20s %-20s %-20.2f %-20.2f %-20d %-20d %-20s\n", t->product.codigo, t->product.modelo, t->product.marca, t->product.color, t->product.costoVendido, t->product.costoComprado, t->product.existencia, t->product.unidadesCompradas, t->product.proveedor);

            while (t->next != NULL) {
                t = t->next;
                fprintf(arch, "%-10s %-20s %-20s %-20s %-20.2f %-20.2f %-20d %-20d %-20s\n", t->product.codigo, t->product.modelo, t->product.marca, t->product.color, t->product.costoVendido, t->product.costoComprado, t->product.existencia, t->product.unidadesCompradas, t->product.proveedor);
            }
        }
    }
    for (int i = 0; i < (10 + (20 * 8)); i++) {
        fprintf(arch, "-");
    }
    fprintf(arch, "\n");

    fclose(arch);
}

//Función que genera un archivo con el reporte de ventas
void reporteDeVentasArchivo() {
    FILE *archd, *archt;

    archt = fopen("Reporte de ventas.txt", "w");
    archd = fopen("ventas.dat", "r+b");

    fprintf(archt, "Reporte de ventas\n");

    float pc = 0;
    float pv = 0;

    if (archd == NULL) {
        fprintf(archt, "Archivo ventas.dat no encontrado\n");
        return;
    }
    for (int i = 0; i < ((10 * 5) + 15 + (20 * 2)); i++) {
        fprintf(archt, "-");
    }
    fprintf(archt, "\n");

    fprintf(archt, "%-10s %-13s %-15s %-10s %-10s %-20s %-20s %-10s\n", "Tipo", "No.", "Fecha", "Clave", "Cantidad", "Precio Comprado", "Precio Vendido", "Vendedor");

    for (int i = 0; i < ((10 * 5) + 15 + (20 * 2)); i++) {
        fprintf(archt, "-");
    }
    fprintf(archt, "\n");

    /////////////////////////////////////////////////////////////////////////////////////
    //Escribe secuencialmente
    /////////////////////////////////////////////////////////////////////////////////////

    Venta venta;
    fread(&venta, sizeof(Venta), 1, archd);
    while (!feof(archd)) {
        if (venta.esVenta) {
            fprintf(archt, "%-10s ", "Venta");
        }
        else {
            fprintf(archt, "%-10s ", "Reembolzo");
        }

        string fecha = to_string(venta.dia) + "/" + to_string(venta.mes) + "/" + to_string(venta.anho);
        int k = fecha.length();
        char fechav[k + 1];

        strcpy(fechav, fecha.c_str());

        fprintf(archt, "%-13d %-15s %-10s %-10d ", venta.numero, fechav, venta.clave, venta.cantidad);

        string code = venta.clave;
        Tlist t;
        int n = hashFunction(code);
        if (hashTable[n] == NULL) {
            fprintf(archt, "No existe el producto con ese código\n");
        }
        else {
            bool existe = false;
            t = hashTable[n];
            int i = 1;
            while (t != NULL) {
                existe = true;
                if (t->product.codigo == code) {
                    break;
                }
                t = t->next;
                i++;
            }
            if (!existe) {
                fprintf(archt, "El producto con ese código no existe\n");
            }
        }
        fprintf(archt, "%-20.2f %-20.2f ", t->product.costoComprado, t->product.costoVendido);

        if (venta.esVenta) {
            pc += (t->product.costoComprado * venta.cantidad);
            pv += (t->product.costoVendido * venta.cantidad);
        }
        else {
            pc -= (t->product.costoComprado * venta.cantidad);
            pv -= (t->product.costoVendido * venta.cantidad);
        }
        fprintf(archt, "%-10d\n", venta.vendedor);

        fread(&venta, sizeof(Venta), 1, archd);
    }

    fclose(archd);

    for (int i = 0; i < ((10 * 5) + 15 + (20 * 2)); i++) {
        fprintf(archt, "-");
    }

    fprintf(archt, "\nInversión: %.2f \n", pc);
    fprintf(archt, "Dinero total recaudado de las ventas: %.2f \n", pv);
    fprintf(archt, "Ganancia: %.2f \n", pv - pc);

    fclose(archt);
}

//Función que genera un archivo con el reporte de proveedores
void reporteDeProveedoresArchivo() {
    FILE *archd, *archt;

    archt = fopen("Reporte de proveedores.txt", "w");
    archd = fopen("proveedores.dat", "r+b");

    fprintf(archt, "Reporte de proveedores\n");

    if (archd == NULL) {
        fprintf(archt, "Archivo proveedores.dat no encontrado\n");
        return;
    }
    for (int i = 0; i < ((20 * 3)); i++) {
        fprintf(archt, "-");
    }
    fprintf(archt, "\n");

    fprintf(archt, "%-20s %-20s %-20s\n", "Clave", "Nombre", "Teléfono");

    for (int i = 0; i < ((20 * 3)); i++) {
        fprintf(archt, "-");
    }
    fprintf(archt, "\n");

    /////////////////////////////////////////////////////////////////////////////////////
    //Escribe secuencialmente
    /////////////////////////////////////////////////////////////////////////////////////

    Proveedor proveedor;
    fread(&proveedor, sizeof(Proveedor), 1, archd);
    while (!feof(archd)) {
        fprintf(archt, "%-20s %-20s %-20d\n", proveedor.clave, proveedor.nombre, proveedor.telefono);

        fread(&proveedor, sizeof(Proveedor), 1, archd);
    }
    for (int i = 0; i < ((20 * 3)); i++) {
        fprintf(archt, "-");
    }
    fprintf(archt, "\n");
    fclose(archd);
    fclose(archt);
}

/****************************************
 * Administración
 ***************************************/

//Función que crea un archivo
void crear() {
    string str;

    //Borra lo que escribimos escuchando las teclas
    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));

    cout << "Dijite el nombre del archivo que quiere crear, junto con su extensión: ";
    cin >> str;

    string comando = "type nul > " + str;

    system(comando.c_str());
}

//Función que respalda productos.dat, proveedores.dat, vendedores.dat y ventas.dat
void respaldar() {
    FILE *arch;

    //Genera el respaldo y copia los datos
    //Verifica que no exista antes un respaldo, si existe, lo borra
    arch = fopen("productos.dat", "r+b");
    if (arch == NULL) {
    }
    else {
        FILE *arch2;
        arch2 = fopen("productos respaldo.dat", "r+b");
        if (arch2 == NULL) {
            arch2 = fopen("productos respaldo.dat", "ab");
            if (arch2 == NULL) {
            }
            else {
                tproducto producto;
                fread(&producto, sizeof(tproducto), 1, arch);
                while (!feof(arch)) {
                    fwrite(&producto, sizeof(tproducto), 1, arch2);
                    fread(&producto, sizeof(tproducto), 1, arch);
                }
                fclose(arch2);
            }
        }
        else {
            fclose(arch2);
            system("del \"productos respaldo.dat\"");

            arch2 = fopen("productos respaldo.dat", "ab");
            if (arch2 == NULL) {
            }
            else {
                tproducto producto;
                fread(&producto, sizeof(tproducto), 1, arch);
                while (!feof(arch)) {
                    fwrite(&producto, sizeof(tproducto), 1, arch2);
                    fread(&producto, sizeof(tproducto), 1, arch);
                }
                fclose(arch2);
            }
        }
    }
    fclose(arch);

    //Genera el respaldo y copia los datos
    //Verifica que no exista antes un respaldo, si existe, lo borr
    arch = fopen("proveedores.dat", "r+b");
    if (arch == NULL) {
    }
    else {
        FILE *arch2;
        arch2 = fopen("proveedores respaldo.dat", "r+b");
        if (arch2 == NULL) {
            arch2 = fopen("proveedores respaldo.dat", "ab");
            if (arch2 == NULL) {
            }
            else {
                Proveedor proveedor;
                fread(&proveedor, sizeof(Proveedor), 1, arch);
                while (!feof(arch)) {
                    fwrite(&proveedor, sizeof(Proveedor), 1, arch2);
                    fread(&proveedor, sizeof(Proveedor), 1, arch);
                }
                fclose(arch2);
            }
        }
        else {
            fclose(arch2);
            system("del \"proveedores respaldo.dat\"");

            arch2 = fopen("proveedores respaldo.dat", "ab");
            if (arch2 == NULL) {
            }
            else {
                Proveedor proveedor;
                fread(&proveedor, sizeof(Proveedor), 1, arch);
                while (!feof(arch)) {
                    fwrite(&proveedor, sizeof(Proveedor), 1, arch2);
                    fread(&proveedor, sizeof(Proveedor), 1, arch);
                }
                fclose(arch2);
            }
        }
    }
    fclose(arch);

    //Genera el respaldo y copia los datos
    //Verifica que no exista antes un respaldo, si existe, lo borr
    arch = fopen("vendedores.dat", "r+b");
    if (arch == NULL) {
    }
    else {
        FILE *arch2;
        arch2 = fopen("vendedores respaldo.dat", "r+b");
        if (arch2 == NULL) {
            arch2 = fopen("vendedores respaldo.dat", "ab");
            if (arch2 == NULL) {
            }
            else {
                Vendedor vendedor;
                fread(&vendedor, sizeof(Vendedor), 1, arch);
                while (!feof(arch)) {
                    fwrite(&vendedor, sizeof(Vendedor), 1, arch2);
                    fread(&vendedor, sizeof(Vendedor), 1, arch);
                }
                fclose(arch2);
            }
        }
        else {
            fclose(arch2);
            system("del \"vendedores respaldo.dat\"");

            arch2 = fopen("vendedores respaldo.dat", "ab");
            if (arch2 == NULL) {
            }
            else {
                Vendedor vendedor;
                fread(&vendedor, sizeof(Vendedor), 1, arch);
                while (!feof(arch)) {
                    fwrite(&vendedor, sizeof(Vendedor), 1, arch2);
                    fread(&vendedor, sizeof(Vendedor), 1, arch);
                }
                fclose(arch2);
            }
        }
    }
    fclose(arch);

    //Genera el respaldo y copia los datos
    //Verifica que no exista antes un respaldo, si existe, lo borr
    arch = fopen("ventas.dat", "r+b");
    if (arch == NULL) {
    }
    else {
        FILE *arch2;
        arch2 = fopen("ventas respaldo.dat", "r+b");
        if (arch2 == NULL) {
            arch2 = fopen("ventas respaldo.dat", "ab");
            if (arch2 == NULL) {
            }
            else {
                Venta venta;
                fread(&venta, sizeof(Venta), 1, arch);
                while (!feof(arch)) {
                    fwrite(&venta, sizeof(Venta), 1, arch2);
                    fread(&venta, sizeof(Venta), 1, arch);
                }
                fclose(arch2);
            }
        }
        else {
            fclose(arch2);
            system("del \"ventas respaldo.dat\"");

            arch2 = fopen("ventas respaldo.dat", "ab");
            if (arch2 == NULL) {
            }
            else {
                Venta venta;
                fread(&venta, sizeof(Venta), 1, arch);
                while (!feof(arch)) {
                    fwrite(&venta, sizeof(Venta), 1, arch2);
                    fread(&venta, sizeof(Venta), 1, arch);
                }
                fclose(arch2);
            }
        }
    }
    fclose(arch);
}

//Función que recupera productos.dat, proveedores.dat, vendedores.dat y ventas.dat desde sus respaldos
//Básicamente es la función inversa del respaldar
void restaurar() {
    FILE *arch;

    //Copia los datos del respalo a otro archivo nuevo y luego lo renombra
    //Borra el archivo original si existe
    arch = fopen("productos respaldo.dat", "r+b");
    if (arch == NULL) {
    }
    else {
        FILE *arch2;
        arch2 = fopen("productos.dat", "r+b");
        if (arch2 == NULL) {
            arch2 = fopen("productos.dat", "ab");
            if (arch2 == NULL) {
            }
            else {
                tproducto producto;
                fread(&producto, sizeof(tproducto), 1, arch);
                while (!feof(arch)) {
                    fwrite(&producto, sizeof(tproducto), 1, arch2);
                    fread(&producto, sizeof(tproducto), 1, arch);
                }
                fclose(arch2);
            }
        }
        else {
            fclose(arch2);
            system("del \"productos.dat\"");

            arch2 = fopen("productos.dat", "ab");
            if (arch2 == NULL) {
            }
            else {
                tproducto producto;
                fread(&producto, sizeof(tproducto), 1, arch);
                while (!feof(arch)) {
                    fwrite(&producto, sizeof(tproducto), 1, arch2);
                    fread(&producto, sizeof(tproducto), 1, arch);
                }
                fclose(arch2);
            }
        }
    }
    fclose(arch);

    //Copia los datos del respalo a otro archivo nuevo y luego lo renombra
    //Borra el archivo original si existe
    arch = fopen("proveedores respaldo.dat", "r+b");
    if (arch == NULL) {
    }
    else {
        FILE *arch2;
        arch2 = fopen("proveedores.dat", "r+b");
        if (arch2 == NULL) {
            arch2 = fopen("proveedores.dat", "ab");
            if (arch2 == NULL) {
            }
            else {
                Proveedor proveedor;
                fread(&proveedor, sizeof(Proveedor), 1, arch);
                while (!feof(arch)) {
                    fwrite(&proveedor, sizeof(Proveedor), 1, arch2);
                    fread(&proveedor, sizeof(Proveedor), 1, arch);
                }
                fclose(arch2);
            }
        }
        else {
            fclose(arch2);
            system("del \"proveedores.dat\"");

            arch2 = fopen("proveedores.dat", "ab");
            if (arch2 == NULL) {
            }
            else {
                Proveedor proveedor;
                fread(&proveedor, sizeof(Proveedor), 1, arch);
                while (!feof(arch)) {
                    fwrite(&proveedor, sizeof(Proveedor), 1, arch2);
                    fread(&proveedor, sizeof(Proveedor), 1, arch);
                }
                fclose(arch2);
            }
        }
    }
    fclose(arch);

    //Copia los datos del respalo a otro archivo nuevo y luego lo renombra
    //Borra el archivo original si existe
    arch = fopen("vendedores respaldo.dat", "r+b");
    if (arch == NULL) {
    }
    else {
        FILE *arch2;
        arch2 = fopen("vendedores.dat", "r+b");
        if (arch2 == NULL) {
            arch2 = fopen("vendedores.dat", "ab");
            if (arch2 == NULL) {
            }
            else {
                Vendedor vendedor;
                fread(&vendedor, sizeof(Vendedor), 1, arch);
                while (!feof(arch)) {
                    fwrite(&vendedor, sizeof(Vendedor), 1, arch2);
                    fread(&vendedor, sizeof(Vendedor), 1, arch);
                }
                fclose(arch2);
            }
        }
        else {
            fclose(arch2);
            system("del \"vendedores.dat\"");

            arch2 = fopen("vendedores.dat", "ab");
            if (arch2 == NULL) {
            }
            else {
                Vendedor vendedor;
                fread(&vendedor, sizeof(Vendedor), 1, arch);
                while (!feof(arch)) {
                    fwrite(&vendedor, sizeof(Vendedor), 1, arch2);
                    fread(&vendedor, sizeof(Vendedor), 1, arch);
                }
                fclose(arch2);
            }
        }
    }
    fclose(arch);

    //Copia los datos del respalo a otro archivo nuevo y luego lo renombra
    //Borra el archivo original si existe
    arch = fopen("ventas respaldo.dat", "r+b");
    if (arch == NULL) {
    }
    else {
        FILE *arch2;
        arch2 = fopen("ventas.dat", "r+b");
        if (arch2 == NULL) {
            arch2 = fopen("ventas.dat", "ab");
            if (arch2 == NULL) {
            }
            else {
                Venta venta;
                fread(&venta, sizeof(Venta), 1, arch);
                while (!feof(arch)) {
                    fwrite(&venta, sizeof(Venta), 1, arch2);
                    fread(&venta, sizeof(Venta), 1, arch);
                }
                fclose(arch2);
            }
        }
        else {
            fclose(arch2);
            system("del \"ventas.dat\"");

            arch2 = fopen("ventas.dat", "ab");
            if (arch2 == NULL) {
            }
            else {
                Venta venta;
                fread(&venta, sizeof(Venta), 1, arch);
                while (!feof(arch)) {
                    fwrite(&venta, sizeof(Venta), 1, arch2);
                    fread(&venta, sizeof(Venta), 1, arch);
                }
                fclose(arch2);
            }
        }
    }
    fclose(arch);
}

//Función que elimina completamente los registros vacíos
void compactar() {
    FILE *arch;
    //Solo puede eliminar de proveedores.dat y vendedores.dat porque son secuenciales
    //Aunque ventas.dat también es secuencial, lsa bajas no se manejan de la misma manera
    //En ventas.dat se da un reembolzo y se tiene registro de ello, por eso no se borra

    //Funcionamiento
    //En el archivo busca los registros con clave=""
    arch = fopen("proveedores.dat", "r+b");
    if (arch == NULL) {
        fclose(arch);
    }
    else {
        FILE *arch2;
        arch2 = fopen("proveedores temporal.dat", "ab");
        Proveedor proveedor;
        fread(&proveedor, sizeof(Proveedor), 1, arch);
        while (!feof(arch)) {
            int ret = strncmp(proveedor.clave, "", 20);
            if (ret != 0) {
                fwrite(&proveedor, sizeof(Proveedor), 1, arch2);
            }
            fread(&proveedor, sizeof(Proveedor), 1, arch);
        }
        fclose(arch);
        fclose(arch2);
        system("del proveedores.dat");
        system("ren \"proveedores temporal.dat\" proveedores.dat");
    }

    arch = fopen("vendedores.dat", "r+b");
    if (arch == NULL) {
        fclose(arch);
    }
    else {
        FILE *arch2;
        arch2 = fopen("vendedores temporal.dat", "ab");
        Vendedor vendedor;
        fread(&vendedor, sizeof(Vendedor), 1, arch);
        while (!feof(arch)) {
            if (vendedor.clave != 0) {
                fwrite(&vendedor, sizeof(Vendedor), 1, arch2);
            }
            fread(&vendedor, sizeof(Vendedor), 1, arch);
        }
        fclose(arch);
        fclose(arch2);
        system("del vendedores.dat");
        system("ren \"vendedores temporal.dat\" vendedores.dat");
    }
}

/****************************************
 * Main
 ***************************************/
//El main solo se encarga del menú
int main() {
    // Establecer el idioma a español
    setlocale(LC_ALL, "es_ES");  // Cambiar locale - Suficiente para máquinas Linux
    SetConsoleCP(65001);         // Cambiar STDIN -  Para máquinas Windows
    SetConsoleOutputCP(65001);   // Cambiar STDOUT - Para máquinas Windows
    fflush(stdin);

    //Inicializa al arreglo en valores nulos
    initializeHashTable();
    //Rellena con productos.dat
    fillHashTable();

    //Variables para controlar los menús y submenús
    int opcion1,
        opcion2, opcion3;

    string objetivo;

    char c[] = "123";
    char intento[20];

    bool con = true;

    //Obtiene el número de columnas y filas de la consola
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int columns, rows;

    ////////////////////////////////////////////////////////
    //Primer mensaje
    ///////////////////////////////////////////////////////
    system("cls");
    //system("color 89");

    //Obtiene el número de columnas y filas de la consola
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

    centrar_cadena("UNIVERSIDAD AUTÓNOMA DEL ESTADO DE MÉXICO\n", columns);
    centrar_cadena("FACULTAD DE INGENIERÍA\n", columns);
    centrar_cadena("INGENIERÍA EN COMPUTACIÓN\n", columns);
    cout << endl;
    centrar_cadena("ORGANIZACIÓN DE ARCHIVOS\n", columns);
    cout << endl;
    centrar_cadena("PROYECTO FINAL\n", columns);
    cout << endl;

    cout << "\n\tGrupo: CO02" << endl
         << endl;
    cout << "\n\tEstudiantes: Ana Contreras Peralta";
    cout << "\n\t             Alejandro González Jiménez";
    cout << "\n\t             Cristian";
    cout << "\n\t             Daniel Sotelo";
    cout << "\n\t             Elizabeth García González";
    cout << "\n\t             Israel Enríquez Barreto";
    cout << "\n\t             María de Jesús Sánchez Suárez";

    cout << endl
         << endl;

    cout << "     SEMESTRE 2020-A";
    derecha_cadena("JUNIO DE 2020     \n", columns - 15 /*SEMESTRE 2020-A*/ - 5 /*Margen de 5 espacios*/);
    cout << endl;
    escucharEspacio(1);

    //Switch anidados dentro de whiles para navegar dentro del menú
    while (opcion1 != 8) {
        //Obtiene el número de columnas y filas de la consola
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

        system("cls");
        system("color 8B");
        cout << endl;
        centrar_cadena("MENÚ PRINCIPAL\n", columns);
        cout << endl;
        cout << "\t\t [1]. Accesorios\n"
             << endl;
        cout << "\t\t [2]. Proveedores\n"
             << endl;
        cout << "\t\t [3]. Vendedor\n"
             << endl;
        cout << "\t\t [4]. Ventas\n"
             << endl;
        cout << "\t\t [5]. Informes\n"
             << endl;
        cout << "\t\t [6]. Administración\n"
             << endl;
        cout << "\t\t [7]. Ayuda\n"
             << endl;
        cout << "\t\t [8]. Salir\n\n"
             << endl;
        cout << "\t\tPresione su opción: " << endl;
        opcion1 = escucharTecla(8);
        opcion2 = 0;
        switch (opcion1) {
            case 1: {
                while (opcion2 != 5) {
                    objetivo = "accesorio";

                    bool codigoValido;
                    string code;
                    char code_char[6 + 1];

                    system("cls");
                    system("color 0C");

                    //Obtiene el número de columnas y filas de la consola
                    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
                    columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
                    rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
                    cout << endl;
                    centrar_cadena("MENÚ DE ACCESORIOS\n", columns);

                    cout << "\t\t [1]. Agregar " + objetivo << endl;
                    cout << "\n\t\t [2]. Eliminar " + objetivo << endl;
                    cout << "\n\t\t [3]. Modificar " << endl;
                    cout << "\n\t\t [4]. Buscar " + objetivo << endl;
                    cout << "\n\t\t [5]. Regresar" << endl;
                    cout << "\n\n\t\tPresione su opción: " << endl;
                    opcion2 = escucharTecla(5);
                    switch (opcion2) {
                        case 1: {
                            system("color 0A");
                            altaProducto();
                            cout << endl;
                            break;
                        }
                        case 2: {
                            codigoValido = 0;
                            system("color 0A");
                            //Borra lo que escribimos escuchando las teclas
                            FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
                            while (!codigoValido) {
                                printf("\n\n\t\tIngrese el codigo del producto a eliminar: ");
                                fflush(stdin);
                                getline(cin, code);
                                strcpy(code_char, code.c_str());
                                codigoValido = validarCodigo(code_char);
                                if (!codigoValido) {
                                    cout << "\n\n\t\tUsted ingreso un codigo invalido!!!" << endl;
                                    cout << "\n\t\tUn codigo correcto empieza con 2 letras y le siguen 4 numeros.\n"
                                         << endl;
                                }
                            }
                            bajaProducto(code);
                            break;
                        }
                        case 3: {
                            system("color 0A");
                            //Borra lo que escribimos escuchando las teclas
                            FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
                            codigoValido = 0;
                            while (!codigoValido) {
                                system("color 0A");
                                printf("\n\n\t\tIngrese el codigo del producto a modificar: ");
                                fflush(stdin);
                                getline(cin, code);
                                strcpy(code_char, code.c_str());
                                codigoValido = validarCodigo(code_char);
                                if (!codigoValido) {
                                    cout << "\n\n\t\tUsted ingreso un codigo invalido!!!" << endl;
                                    cout << "\n\t\tUn codigo correcto empieza con 2 letras y le siguen 4 numeros.\n"
                                         << endl;
                                }
                            }
                            cambioProducto(code);
                            break;
                        }
                        case 4: {
                            system("color 0A");
                            //Borra lo que escribimos escuchando las teclas
                            FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
                            codigoValido = 0;
                            while (!codigoValido) {
                                printf("\n\n\t\tIngrese el codigo del producto a buscar: ");
                                fflush(stdin);
                                getline(cin, code);
                                strcpy(code_char, code.c_str());
                                codigoValido = validarCodigo(code_char);
                                if (!codigoValido) {
                                    cout << "\n\n\t\tUsted ingreso un codigo invalido!!!" << endl;
                                    cout << "\n\t\tUn codigo correcto empieza con 2 letras y le siguen 4 numeros.\n"
                                         << endl;
                                }
                            }
                            consultaProducto(code);
                            break;
                        }
                        case 5: {
                            system("color 8B");
                            cout << "\n\n\n\t\tRegresando al menú principal..." << endl;
                            cout << endl;
                            break;
                        }
                        default: {
                            system("color 0A");
                            cout << "\n\t\tDigite una opción correcta." << endl;
                            break;
                        }
                    }
                    escucharEspacio();
                }
                break;
            }
            case 2: {
                while (opcion2 != 5) {
                    objetivo = "proveedor";
                    system("cls");
                    system("color 0C");
                    //Obtiene el número de columnas y filas de la consola
                    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
                    columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
                    rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
                    cout << endl;
                    centrar_cadena("MENÚ DE PROVEEDORES\n", columns);
                    cout << "\t\t [1]. Agregar " + objetivo << endl;
                    cout << "\n\t\t [2]. Eliminar " + objetivo << endl;
                    cout << "\n\t\t [3]. Modificar " << endl;
                    cout << "\n\t\t [4]. Buscar " + objetivo << endl;
                    cout << "\n\t\t [5]. Regresar" << endl;
                    cout << "\n\n\t\tPresione su opción: " << endl;
                    opcion2 = escucharTecla(5);
                    switch (opcion2) {
                        case 1: {
                            system("color 0A");
                            altaProveedor();
                            break;
                        }
                        case 2: {
                            system("color 0A");
                            bajaProveedor();
                            break;
                        }
                        case 3: {
                            system("color 0A");
                            cambioProveedor();
                            break;
                        }
                        case 4: {
                            system("color 0A");
                            consultaProveedor();
                            break;
                        }
                        case 5: {
                            system("color 8B");
                            cout << "\n\n\n\t\tRegresando al menú principal..." << endl;
                            cout << endl;
                            break;
                        }
                        default: {
                            cout << "\n\t\tDigite una opción correcta" << endl;
                            break;
                        }
                    }
                    escucharEspacio();
                }
                break;
            }
            case 3: {
                while (opcion2 != 5) {
                    objetivo = "vendedor";
                    system("cls");
                    system("color 0C");
                    //Obtiene el número de columnas y filas de la consola
                    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
                    columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
                    rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
                    cout << endl;
                    centrar_cadena("MENÚ DE VENDEDOR\n", columns);
                    cout << "\t\t [1]. Agregar " + objetivo << endl;
                    cout << "\n\t\t [2]. Eliminar " + objetivo << endl;
                    cout << "\n\t\t [3]. Modificar " << endl;
                    cout << "\n\t\t [4]. Buscar " + objetivo << endl;
                    cout << "\n\t\t [5]. Regresar" << endl;
                    cout << "\n\n\t\tPresione su opción: " << endl;
                    opcion2 = escucharTecla(5);
                    switch (opcion2) {
                        case 1: {
                            system("color 0A");
                            altaVendedor();
                            break;
                        }
                        case 2: {
                            system("color 0A");
                            bajaVendedor();
                            break;
                        }
                        case 3: {
                            system("color 0A");
                            cambioVendedor();
                            break;
                        }
                        case 4: {
                            system("color 0A");
                            consultaVendedor();
                            break;
                        }
                        case 5: {
                            system("color 8B");
                            cout << "\n\n\n\t\tRegresando al menú principal..." << endl;
                            cout << endl;
                            break;
                        }
                        default: {
                            cout << "Digite una opción correcta" << endl;
                            break;
                        }
                    }
                    escucharEspacio();
                }
                break;
            }
            case 4: {
                while (opcion2 != 3) {
                    bool codigoValido;
                    string code;
                    char code_char[6 + 1];

                    system("cls");
                    system("color 0C");
                    //Obtiene el número de columnas y filas de la consola
                    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
                    columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
                    rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
                    cout << endl;
                    centrar_cadena("MENÚ DE VENTAS\n", columns);
                    cout << "\t\t [1]. Venta de un producto " << endl;
                    cout << "\n\t\t [2]. Reembolso de un producto " << endl;
                    cout << "\n\t\t [3]. Regresar" << endl;
                    cout << "\n\n\t\tPresione su opción: " << endl;
                    opcion2 = escucharTecla(3);
                    switch (opcion2) {
                        case 1: {
                            system("color 0A");
                            altaVenta();
                            break;
                        }
                        case 2: {
                            system("color 0A");
                            bajaVenta();
                            break;
                        }
                        case 3: {
                            system("color 8B");
                            cout << "\n\n\n\t\tRegresando al menú principal..." << endl;
                            cout << endl;
                            break;
                        }
                        default: {
                            cout << "Digite una opción correcta" << endl;
                            break;
                        }
                    }
                    escucharEspacio();
                }
                break;
            }
            case 5: {
                while (opcion2 != 4) {
                    system("cls");
                    system("color 0C");
                    //Obtiene el número de columnas y filas de la consola
                    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
                    columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
                    rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
                    cout << endl;
                    centrar_cadena("MENÚ DE INFORMES\n", columns);
                    cout << "\t\t [1]. Inventario" << endl;
                    cout << "\n\t\t [2]. Reporte de ventas" << endl;
                    cout << "\n\t\t [3]. Reporte de proveedores" << endl;
                    cout << "\n\t\t [4]. Regresar" << endl;
                    cout << "\n\n\t\tPresione su opción: " << endl;
                    opcion2 = escucharTecla(4);
                    opcion3 = 0;
                    switch (opcion2) {
                        case 1: {
                            while (opcion3 != 3) {
                                system("cls");
                                cout << "1. Reporte impreso en pantalla" << endl;
                                cout << "2. Reporte en archivo de texto" << endl;
                                cout << "3. Regresar" << endl;
                                cout << "Presione su opción: " << endl;
                                opcion3 = escucharTecla(3);
                                switch (opcion3) {
                                    case 1: {
                                        inventarioPantalla();
                                        break;
                                    }
                                    case 2: {
                                        inventarioArchivo();
                                        break;
                                    }
                                    case 3: {
                                        cout << "Regresando al menú de informes" << endl;
                                        break;
                                    }
                                    default: {
                                        cout << "Digite una opción correcta" << endl;
                                        break;
                                    }
                                }
                                escucharEspacio();
                            }
                            break;
                        }
                        case 2: {
                            while (opcion3 != 3) {
                                system("cls");
                                cout << "1. Reporte impreso en pantalla" << endl;
                                cout << "2. Reporte en archivo de texto" << endl;
                                cout << "3. Regresar" << endl;
                                cout << "Presione su opción: " << endl;
                                opcion3 = escucharTecla(3);
                                switch (opcion3) {
                                    case 1: {
                                        reporteDeVentasPantalla();
                                        break;
                                    }
                                    case 2: {
                                        reporteDeVentasArchivo();
                                        break;
                                    }
                                    case 3: {
                                        cout << "\n\n\n\t\tRegresando al menú de informes..." << endl;
                                        break;
                                    }
                                    default: {
                                        cout << "Digite una opción correcta" << endl;
                                        break;
                                    }
                                }
                                escucharEspacio();
                            }
                            break;
                        }
                        case 3: {
                            while (opcion3 != 3) {
                                system("cls");
                                cout << "1. Reporte impreso en pantalla" << endl;
                                cout << "2. Reporte en archivo de texto" << endl;
                                cout << "3. Regresar" << endl;
                                cout << "Presione su opción: " << endl;
                                opcion3 = escucharTecla(3);
                                switch (opcion3) {
                                    case 1: {
                                        reporteDeProveedoresPantalla();
                                        break;
                                    }
                                    case 2: {
                                        reporteDeProveedoresArchivo();
                                        break;
                                    }
                                    case 3: {
                                        cout << "\n\n\n\t\tRegresando al menú de informes..." << endl;
                                        break;
                                    }
                                    default: {
                                        cout << "Digite una opción correcta" << endl;
                                        break;
                                    }
                                }
                                escucharEspacio();
                            }
                            break;
                        }
                        case 4: {
                            cout << "\n\n\n\t\tRegresando al menú principal..." << endl;
                            cout << endl;
                            escucharEspacio();
                            break;
                        }
                        default: {
                            cout << "Digite una opción correcta" << endl;
                            escucharEspacio();
                            break;
                        }
                    }
                }
                break;
            }

            case 6: {
                //Borra lo que escribimos escuchando las teclas
                FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
                system("cls");
                system("color 0C");
                //Obtiene el número de columnas y filas de la consola
                GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
                columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
                rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
                cout << endl;
                centrar_cadena("MENÚ DE ADMINISTRACIÓN\n", columns);
                bool hayCaracterIncorrecto = false;
                fflush(stdin);
                cout << "\n\t\t Digite la contraseña: ";
                fflush(stdin);
                gets(intento);
                for (int j = 0; j <= strlen(intento); j++) {
                    if (c[j] != intento[j]) {
                        hayCaracterIncorrecto = true;
                    }
                }
                if (!hayCaracterIncorrecto) {
                    while (opcion2 != 5) {
                        system("cls");
                        cout << "1. Crear archivos" << endl;
                        cout << "2. Respaldar" << endl;
                        cout << "3. Restaurar" << endl;
                        cout << "4. Compactar archivos" << endl;
                        cout << "5. Regresar" << endl;
                        opcion2 = escucharTecla(5);
                        switch (opcion2) {
                            case 1: {
                                crear();
                                break;
                            }
                            case 2: {
                                respaldar();
                                break;
                            }
                            case 3: {
                                restaurar();
                                break;
                            }
                            case 4: {
                                compactar();
                                break;
                            }
                            case 5: {
                                cout << "\n\n\n\t\tRegresando al menú principal..." << endl;
                                cout << endl;
                                break;
                            }
                            default: {
                                cout << "Digite una opción correcta" << endl;
                                break;
                            }
                        }
                        escucharEspacio();
                    }
                }
                else {
                    cout << "Contraseña incorrecta" << endl;
                    cout << "\n\n\n\t\tRegresando al menú principal..." << endl;
                    cout << endl;
                    escucharEspacio();
                }
                break;
            }
            case 7: {
                break;
            }
            case 8: {
                system("color 0E");
                GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
                columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
                rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
                centrar_cadena("¡Hasta luego!\n", columns);
                cout << endl;
                escucharEspacio();
                break;
            }
            default: {
                cout << "\n\t\t¡Digite una opción correcta! " << endl;
                escucharEspacio();
                break;
            }
        }
    }
    return 0;
}
