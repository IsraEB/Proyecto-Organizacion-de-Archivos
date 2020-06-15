#include <conio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <windows.h>

#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

#define NUMBER_OF_SLOTS 100

using namespace std;

/****************************************
 * Utilerías
 ***************************************/

void escucharEspacio() {
    bool con = true;
    while (con) {
        if (GetKeyState(' ') & 0x8000) {
            while (GetKeyState(' ') & 0x8000) {
            }
            con = false;
        }
    }
}

void continuar() {
    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
    cout << "Presione espacio para continuar\n";
    fflush(stdin);
    escucharEspacio();
}

bool validarCodigo(char codigo[]) {
    char caracter;
    bool esNumero = false;
    bool esLetra = false;

    bool codigoValido = false;

    string cadena = codigo;
    if (cadena.length() > 6 || cadena.length() == 0) {
        return false;
    }

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

int pedirEntero(string peticion) {
    string str;
    cout << peticion;

    fflush(stdin);
    cin >> str;
    fflush(stdin);

    try {
        return stoi(str);
    }
    catch (...) {
        cout << "Debe ingresar un entero!" << endl;
        return pedirEntero(peticion);
    }
}

unsigned long long pedirUnsignedLongLong(string peticion) {
    string str;
    cout << peticion;

    fflush(stdin);
    cin >> str;
    fflush(stdin);

    try {
        return stoull(str);
    }
    catch (...) {
        cout << "Debe ingresar un entero!" << endl;
        return pedirEntero(peticion);
    }
}

float pedirFlotante(string peticion) {
    string str;
    cout << peticion;

    fflush(stdin);
    cin >> str;
    fflush(stdin);

    try {
        return stof(str);
    }
    catch (...) {
        cout << "Debe ingresar un flotante!" << endl;
        return pedirEntero(peticion);
    }
}

int escucharTecla(int nOpciones) {
    char letras[] = {'U', 'N', 'E', 'I', 'F', 'A', 'Y', 'S'};
    while (true) {
        for (int i = 0; i < nOpciones; i++) {
            if ((GetKeyState(VK_CONTROL) & 0x8000) && (GetKeyState(letras[i]) & 0x8000)) {
                while ((GetKeyState(VK_CONTROL) & 0x8000) && (GetKeyState(letras[i]) & 0x8000)) {
                }
                return i + 1;
            }
        }
        for (int i = 49; i <= 49 + (nOpciones - 1); i++) {
            if (GetKeyState(i) & 0x8000) {
                while (GetKeyState(i) & 0x8000) {
                }
                return i - 48;
            }
        }
    }
}

/****************************************
 * Productos
 ***************************************/

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

} tproducto;

struct node {
    tproducto product;
    struct node *next;
};
typedef struct node *Tlist;

typedef struct {
    char clave[20];
    char nombre[20];
    unsigned long long telefono;
} Proveedor;

/************
 * Hash
 ************/

int hashFunction(string code) {
    string number = code.substr(2, 2);
    int n = atoi(number.c_str());
    return n;
}

Tlist hashTable[NUMBER_OF_SLOTS];

void initializeHashTable() {
    for (int i = 0; i < NUMBER_OF_SLOTS; i++) {
        hashTable[i] = NULL;
    }
}

void fillHashTable() {
    FILE *arch;

    arch = fopen("productos.dat", "rb");

    if (arch == NULL) {
        return;
    }

    tproducto producto;

    fread(&producto, sizeof(tproducto), 1, arch);
    while (!feof(arch)) {
        int n = hashFunction(producto.codigo);

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

void writeFile() {
    FILE *arch;
    arch = fopen("productos.dat", "w+b");
    if (arch == NULL) {
        cout << "Archivo no encontrado" << endl;
        continuar();
        exit(1);
    }

    Tlist list;
    tproducto product;

    for (int i = 0; i < NUMBER_OF_SLOTS; i++) {
        if (hashTable[i] == NULL) {
        }
        else {
            Tlist t = hashTable[i];
            product = t->product;
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

void altaProducto() {
    tproducto producto;
    bool codigoValido = 0;

    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));

    while (!codigoValido) {
        printf("Ingrese el codigo del producto: ");
        fflush(stdin);
        cin.getline(producto.codigo, 7, '\n');
        codigoValido = validarCodigo(producto.codigo);
        if (!codigoValido) {
            cout << "Usted ingreso un codigo invalido!!!" << endl;
            cout << "Un codigo correcto empieza con 2 letras y le siguen 4 numeros" << endl;
        }
    }

    fflush(stdin);
    cout << "Ingrese el color del producto: ";
    cin.getline(producto.color, 20, '\n');

    fflush(stdin);
    cout << "Ingrese la marca del producto: ";
    cin.getline(producto.marca, 20, '\n');

    fflush(stdin);
    cout << "Ingrese el modelo del producto: ";
    cin.getline(producto.modelo, 20, '\n');

    fflush(stdin);
    cout << "Ingrese el proveedor del producto: ";
    cin.getline(producto.proveedor, 20, '\n');

    FILE *arch;
    arch = fopen("proveedores.dat", "r+b");
    if (arch == NULL) {
        cout << "Archivo no encontrado" << endl;
        cout << "Se cancela todo" << endl;
        return;
    }
    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));

    string cod = producto.proveedor;
    Proveedor proveedor;
    int existe = 0;
    fread(&proveedor, sizeof(Proveedor), 1, arch);
    while (!feof(arch)) {
        if (cod == proveedor.clave) {
            printf("%s : ", proveedor.clave);
            printf("%s : ", proveedor.nombre);
            cout << proveedor.telefono << endl;

            existe = 1;
            break;
        }
        fread(&proveedor, sizeof(Proveedor), 1, arch);
    }
    if (existe == 0) {
        printf("No existe un proveedor con dicha clave\n");
        cout << "Se cancela todo" << endl;
        return;
    }

    fclose(arch);

    fflush(stdin);
    cout << "Ingrese el precio al que se compró el producto: ";
    producto.costoComprado = pedirFlotante("");

    fflush(stdin);
    cout << "Ingrese el precio al que se vende el producto: ";
    producto.costoVendido = pedirFlotante("");

    fflush(stdin);
    cout << "Ingrese cuantas unidades se compraron: ";
    producto.existencia = pedirEntero("");

    int n = hashFunction(producto.codigo);

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
    writeFile();
}

void bajaProducto(string code) {
    int n = hashFunction(code);
    if (hashTable[n] == NULL) {
        cout << "No existe el producto con ese codigo";
    }
    else {
        bool existe = false;
        Tlist t = hashTable[n];
        int i = 1;
        if (t->next == NULL) {
            if (t->product.codigo == code) {
                cout << "Código: " << t->product.codigo << endl;
                cout << "Color: " << t->product.color << endl;
                cout << "Precio al que se compró: " << t->product.costoComprado << endl;
                cout << "Precio al que se vende: " << t->product.costoVendido << endl;
                cout << "Existencia: " << t->product.existencia << endl;
                cout << "Marca: " << t->product.marca << endl;
                cout << "Modelo: " << t->product.modelo << endl;
                cout << "Proveedor: " << t->product.proveedor << endl;
                cout << endl;

                hashTable[n] = NULL;
                cout << "Producto eliminado" << endl;
            }
            else {
                cout << "El producto con ese codigo no existe" << endl;
            }
        }
        else {
            while (t != NULL) {
                if (t->next->product.codigo == code) {
                    cout << "Código: " << t->product.codigo << endl;
                    cout << "Color: " << t->product.color << endl;
                    cout << "Precio al que se compró: " << t->product.costoComprado << endl;
                    cout << "Precio al que se vende: " << t->product.costoVendido << endl;
                    cout << "Existencia: " << t->product.existencia << endl;
                    cout << "Marca: " << t->product.marca << endl;
                    cout << "Modelo: " << t->product.modelo << endl;
                    cout << "Proveedor: " << t->product.proveedor << endl;
                    cout << endl;

                    existe = true;
                    t->next = t->next->next;
                    cout << "Producto eliminado" << endl;
                }
                t = t->next;
                i++;
            }
            if (!existe) {
                cout << "El producto con ese codigo no existe" << endl;
            }
            cout << endl;
        }
    }
    writeFile();
}

void cambioProducto(string code) {
    int n = hashFunction(code);
    if (hashTable[n] == NULL) {
        cout << "No existe el producto con ese codigo";
    }
    else {
        bool existe = false;
        Tlist t = hashTable[n];
        int i = 1;
        while (t != NULL) {
            if (t->product.codigo == code) {
                existe = true;

                cout << "Código: " << t->product.codigo << endl;
                cout << "Color: " << t->product.color << endl;
                cout << "Precio al que se compró: " << t->product.costoComprado << endl;
                cout << "Precio al que se vende: " << t->product.costoVendido << endl;
                cout << "Existencia: " << t->product.existencia << endl;
                cout << "Marca: " << t->product.marca << endl;
                cout << "Modelo: " << t->product.modelo << endl;
                cout << "Proveedor: " << t->product.proveedor << endl;
                cout << endl;

                fflush(stdin);
                cout << "Ingrese el color del producto: ";
                cin.getline(t->product.color, 20, '\n');

                fflush(stdin);
                cout << "Ingrese la marca del producto: ";
                cin.getline(t->product.marca, 20, '\n');

                fflush(stdin);
                cout << "Ingrese el modelo del producto: ";
                cin.getline(t->product.modelo, 20, '\n');

                fflush(stdin);
                cout << "Ingrese el proveedor del producto: ";
                cin.getline(t->product.proveedor, 20, '\n');

                fflush(stdin);
                cout << "Ingrese el precio al que se compró el producto: ";
                t->product.costoComprado = pedirFlotante("");

                fflush(stdin);
                cout << "Ingrese el precio al que se vende el producto: ";
                t->product.costoVendido = pedirFlotante("");

                fflush(stdin);
                cout << "Ingrese cuantas unidades se compraron: ";
                t->product.existencia = pedirEntero("");
            }
            t = t->next;
            i++;
        }
        if (!existe) {
            cout << "El producto con ese codigo no existe" << endl;
        }
        cout << endl;
    }
    writeFile();
}

void consultaProducto(string code) {
    int n = hashFunction(code);
    if (hashTable[n] == NULL) {
        cout << "No existe el producto con ese codigo";
    }
    else {
        bool existe = false;
        Tlist t = hashTable[n];
        int i = 1;
        while (t != NULL) {
            if (t->product.codigo == code) {
                existe = true;
                cout << "El producto esta en el indice " << n << " de la tabla en la posicion " << i << endl;
                cout << "Código: " << t->product.codigo << endl;
                cout << "Color: " << t->product.color << endl;
                cout << "Precio al que se compró: " << t->product.costoComprado << endl;
                cout << "Precio al que se vende: " << t->product.costoVendido << endl;
                cout << "Existencia: " << t->product.existencia << endl;
                cout << "Marca: " << t->product.marca << endl;
                cout << "Modelo: " << t->product.modelo << endl;
                cout << "Proveedor: " << t->product.proveedor << endl;
                cout << endl;
            }
            t = t->next;
            i++;
        }
        if (!existe) {
            cout << "El producto con ese codigo no existe" << endl;
        }
        cout << endl;
    }
}

/****************************************
 * Proveedores
 ***************************************/

void altaProveedor() {
    FILE *arch;
    arch = fopen("proveedores.dat", "ab");
    if (arch == NULL) {
        cout << "Archivo no encontrado" << endl;
        return;
    }

    Proveedor proveedor;

    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));

    bool codigoValido = 0;

    fflush(stdin);
    cout << "Digite la clave del proveedor: ";
    cin.getline(proveedor.clave, 20, '\n');

    fflush(stdin);
    cout << "Digite el nombre del proveedor: ";
    cin.getline(proveedor.nombre, 20, '\n');

    fflush(stdin);
    cout << "Digite el número telefónico del proveedor: ";
    proveedor.telefono = pedirUnsignedLongLong("");

    fwrite(&proveedor, sizeof(Proveedor), 1, arch);
    fclose(arch);
}

void bajaProveedor() {
    FILE *arch;
    arch = fopen("proveedores.dat", "r+b");
    if (arch == NULL) {
        cout << "Archivo no encontrado" << endl;
        return;
    }
    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));

    printf("Ingrese la clave del proveedor a consultar:");
    fflush(stdin);
    string cod;
    getline(cin, cod);
    Proveedor proveedor;
    int existe = 0;
    fread(&proveedor, sizeof(Proveedor), 1, arch);
    while (!feof(arch)) {
        if (cod == proveedor.clave) {
            printf("%s : ", proveedor.clave);
            printf("%s : ", proveedor.nombre);
            cout << proveedor.telefono << endl;

            string cadenaVacia = "";

            strcpy(proveedor.clave, cadenaVacia.c_str());
            strcpy(proveedor.nombre, cadenaVacia.c_str());
            proveedor.telefono = 0;

            int pos = ftell(arch) - sizeof(Proveedor);
            fseek(arch, pos, SEEK_SET);
            fwrite(&proveedor, sizeof(Proveedor), 1, arch);
            printf("Se borro el proveedor.\n");
            existe = 1;
            break;
        }
        fread(&proveedor, sizeof(Proveedor), 1, arch);
    }
    if (existe == 0)
        printf("No existe un proveedor con dicha clave\n");
    fclose(arch);
}

void cambioProveedor() {
    FILE *arch;
    arch = fopen("proveedores.dat", "r+b");
    if (arch == NULL) {
        cout << "Archivo no encontrado" << endl;
        return;
    }
    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));

    printf("Ingrese la clave del proveedor a consultar:");
    fflush(stdin);
    string cod;
    getline(cin, cod);
    Proveedor proveedor;
    int existe = 0;
    fread(&proveedor, sizeof(Proveedor), 1, arch);
    while (!feof(arch)) {
        if (cod == proveedor.clave) {
            printf("%s : ", proveedor.clave);
            printf("%s : ", proveedor.nombre);
            cout << proveedor.telefono << endl;

            fflush(stdin);
            cout << "Digite el nombre del proveedor: ";
            cin.getline(proveedor.nombre, 20, '\n');

            fflush(stdin);
            cout << "Digite el número telefónico del proveedor: ";
            proveedor.telefono = pedirUnsignedLongLong("");

            int pos = ftell(arch) - sizeof(Proveedor);
            fseek(arch, pos, SEEK_SET);
            fwrite(&proveedor, sizeof(Proveedor), 1, arch);
            printf("Se modifico el proveedor.\n");
            existe = 1;
            break;
        }
        fread(&proveedor, sizeof(Proveedor), 1, arch);
    }
    if (existe == 0)
        printf("No existe un proveedor con dicha clave\n");
    fclose(arch);
}

void consultaProveedor() {
    FILE *arch;
    arch = fopen("proveedores.dat", "r+b");
    if (arch == NULL) {
        cout << "Archivo no encontrado" << endl;
        return;
    }
    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));

    printf("Ingrese la clave del proveedor a consultar:");
    fflush(stdin);
    string cod;
    getline(cin, cod);
    Proveedor proveedor;
    int existe = 0;
    fread(&proveedor, sizeof(Proveedor), 1, arch);
    while (!feof(arch)) {
        if (cod == proveedor.clave) {
            printf("%s : ", proveedor.clave);
            printf("%s : ", proveedor.nombre);
            cout << proveedor.telefono << endl;

            existe = 1;
            break;
        }
        fread(&proveedor, sizeof(Proveedor), 1, arch);
    }
    if (existe == 0)
        printf("No existe un proveedor con dicha clave\n");
    fclose(arch);
}

/****************************************
 * Vendedores
 ***************************************/

typedef struct {
    int clave;
    char nombre[20];
    float salario;
} Vendedor;

void altaVendedor() {
    FILE *arch;
    arch = fopen("vendedores.dat", "ab");
    if (arch == NULL) {
        cout << "Archivo no encontrado" << endl;
        return;
    }

    Vendedor vendedor;

    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));

    bool codigoValido = 0;

    fflush(stdin);
    vendedor.clave = pedirEntero("Digite la clave numérica del vendedor: ");

    fflush(stdin);
    cout << "Digite el nombre del vendedor: ";
    cin.getline(vendedor.nombre, 20, '\n');

    fflush(stdin);
    vendedor.salario = pedirFlotante("Digite el salario del vendedor: ");

    fwrite(&vendedor, sizeof(Vendedor), 1, arch);
    fclose(arch);
}

void bajaVendedor() {
    FILE *arch;
    arch = fopen("vendedores.dat", "r+b");
    if (arch == NULL) {
        cout << "Archivo no encontrado" << endl;
        return;
    }
    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));

    Vendedor vendedor;

    fflush(stdin);
    int cod = pedirEntero("Ingrese la clave del vendedor a consultar: ");
    ;

    int existe = 0;
    fread(&vendedor, sizeof(Vendedor), 1, arch);
    while (!feof(arch)) {
        if (cod == vendedor.clave) {
            cout << vendedor.clave;
            printf(": %s : ", vendedor.nombre);
            cout << vendedor.salario << endl;

            string cadenaVacia = "";

            vendedor.clave = 0;
            strcpy(vendedor.nombre, cadenaVacia.c_str());
            vendedor.salario = 0;

            int pos = ftell(arch) - sizeof(Vendedor);
            fseek(arch, pos, SEEK_SET);
            fwrite(&vendedor, sizeof(Vendedor), 1, arch);
            printf("Se borro el vendedor.\n");
            existe = 1;
            break;
        }
        fread(&vendedor, sizeof(Vendedor), 1, arch);
    }
    if (existe == 0)
        printf("No existe un vendedor con dicha clave\n");
    fclose(arch);
}

void cambioVendedor() {
    FILE *arch;
    arch = fopen("vendedores.dat", "r+b");
    if (arch == NULL) {
        cout << "Archivo no encontrado" << endl;
        return;
    }
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

            fflush(stdin);
            cout << "Digite el nombre del vendedor: ";
            cin.getline(vendedor.nombre, 20, '\n');

            fflush(stdin);
            vendedor.salario = pedirFlotante("Digite el salario del vendedor: ");

            int pos = ftell(arch) - sizeof(Vendedor);
            fseek(arch, pos, SEEK_SET);
            fwrite(&vendedor, sizeof(Vendedor), 1, arch);
            printf("Se modifico el vendedor.\n");
            existe = 1;
            break;
        }
        fread(&vendedor, sizeof(Vendedor), 1, arch);
    }
    if (existe == 0)
        printf("No existe un vendedor con dicha clave\n");
    fclose(arch);
}

void consultaVendedor() {
    FILE *arch;
    arch = fopen("vendedores.dat", "r+b");
    if (arch == NULL) {
        cout << "Archivo no encontrado" << endl;
        return;
    }
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
 * Vendedores
 ***************************************/

typedef struct {
    bool esVenta;
    int numero;
    unsigned int dia;
    unsigned int mes;
    unsigned int anho;
    char clave[7];
    int cantidad;
    int costo;
    int vendedor;
} Venta;

void altaVenta() {
    FILE *arch;
    arch = fopen("ventas.dat", "ab");
    if (arch == NULL) {
        cout << "Archivo no encontrado" << endl;
        return;
    }

    Venta venta;

    venta.esVenta = true;

    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));

    // int numero;
    // unsigned int dia;
    // unsigned int mes;
    // unsigned int anho;
    // char clave[20];
    // int cantidad;
    // int costo;
    // int vendedor;

    fflush(stdin);
    venta.numero = pedirEntero("Digite el numero de venta: ");

    fflush(stdin);
    venta.dia = pedirEntero("Digite el día de la venta: ");

    fflush(stdin);
    venta.mes = pedirEntero("Digite el mes de la venta: ");

    fflush(stdin);
    venta.anho = pedirEntero("Digite el año de la venta: ");

    bool codigoValido = 0;

    while (!codigoValido) {
        printf("Ingrese el codigo del producto: ");
        fflush(stdin);
        cin.getline(venta.clave, 7, '\n');
        codigoValido = validarCodigo(venta.clave);
        if (!codigoValido) {
            cout << "Usted ingreso un codigo invalido!!!" << endl;
            cout << "Un codigo correcto empieza con 2 letras y le siguen 4 numeros" << endl;
        }
    }

    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));

    string code = venta.clave;

    Tlist t;

    int n = hashFunction(code);
    if (hashTable[n] == NULL) {
        cout << "No existe el producto con ese codigo";
        cout << "Se cancela todo" << endl;
        return;
    }
    else {
        bool existe = false;
        t = hashTable[n];
        int i = 1;
        while (t != NULL) {
            if (t->product.codigo == code) {
                existe = true;
                cout << "El producto esta en el indice " << n << " de la tabla en la posicion " << i << endl;

                cout << "Código: " << t->product.codigo << endl;
                cout << "Color: " << t->product.color << endl;
                cout << "Precio al que se compró: " << t->product.costoComprado << endl;
                cout << "Precio al que se vende: " << t->product.costoVendido << endl;
                cout << "Existencia: " << t->product.existencia << endl;
                cout << "Marca: " << t->product.marca << endl;
                cout << "Modelo: " << t->product.modelo << endl;
                cout << "Proveedor: " << t->product.proveedor << endl;
                cout << endl;

                break;
            }
            t = t->next;
            i++;
        }
        if (!existe) {
            cout << "El producto con ese codigo no existe" << endl;
            cout << "Se cancela todo" << endl;
            return;
        }
        cout << endl;
    }

    fflush(stdin);
    venta.cantidad = pedirEntero("Digite la cantidad vendida: ");

    if (t->product.existencia < venta.cantidad) {
        cout << "Se están tratando de comprar" << venta.cantidad << "y solo hay " << t->product.existencia;
        cout << "Se cancela todo" << endl;
        return;
    }
    else if (venta.cantidad <= 0) {
        if (venta.cantidad == 0) {
            cout << "No puede vender 0 productos" << endl;
            cout << "Se cancela todo" << endl;
            return;
        }
        if (venta.cantidad < 0) {
            cout << "No puede ingresar un número negativo" << endl;
            cout << "Se cancela todo" << endl;
            return;
        }
    }
    else {
        t->product.existencia -= venta.cantidad;
        writeFile();
    }

    fflush(stdin);
    cout << "Digite el codigo numerico del vendedor: ";
    venta.vendedor = pedirEntero("");

    FILE *archV;
    archV = fopen("vendedores.dat", "r+b");
    if (archV == NULL) {
        cout << "Archivo vendedores.dat no encontrado" << endl;
        cout << "Se cancela todo" << endl;
        return;
    }
    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
    Vendedor vendedor;

    fflush(stdin);
    int cod = venta.vendedor;

    int existe = 0;
    fread(&vendedor, sizeof(Vendedor), 1, archV);
    while (!feof(archV)) {
        if (cod == vendedor.clave) {
            cout << vendedor.clave;
            printf(": %s : ", vendedor.nombre);
            cout << vendedor.salario << endl;

            existe = 1;
            break;
        }
        fread(&vendedor, sizeof(Vendedor), 1, archV);
    }
    if (existe == 0) {
        printf("No existe un vendedor con dicha clave\n");
        cout << "Se cancela todo" << endl;
        return;
    }

    fclose(archV);

    fwrite(&venta, sizeof(Venta), 1, arch);
    fclose(arch);
}

void bajaVenta() {
    FILE *arch;
    arch = fopen("ventas.dat", "ab");
    if (arch == NULL) {
        cout << "Archivo no encontrado" << endl;
        return;
    }

    Venta venta;

    venta.esVenta = false;

    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));

    // int numero;
    // unsigned int dia;
    // unsigned int mes;
    // unsigned int anho;
    // char clave[20];
    // int cantidad;
    // int costo;
    // int vendedor;

    fflush(stdin);
    venta.numero = pedirEntero("Digite el numero del reembolzo: ");

    fflush(stdin);
    venta.dia = pedirEntero("Digite el día del reembolzo: ");

    fflush(stdin);
    venta.mes = pedirEntero("Digite el mes del reembolzo ");

    fflush(stdin);
    venta.anho = pedirEntero("Digite el año del reembolzo: ");

    bool codigoValido = 0;

    while (!codigoValido) {
        printf("Ingrese el codigo del producto: ");
        fflush(stdin);
        cin.getline(venta.clave, 7, '\n');
        codigoValido = validarCodigo(venta.clave);
        if (!codigoValido) {
            cout << "Usted ingreso un codigo invalido!!!" << endl;
            cout << "Un codigo correcto empieza con 2 letras y le siguen 4 numeros" << endl;
        }
    }

    string code = venta.clave;

    Tlist t;

    int n = hashFunction(code);
    if (hashTable[n] == NULL) {
        cout << "No existe el producto con ese codigo";
        cout << "Se cancela todo" << endl;
        return;
    }
    else {
        bool existe = false;
        t = hashTable[n];
        int i = 1;
        while (t != NULL) {
            existe = true;
            cout << "El producto esta en el indice " << n << " de la tabla en la posicion " << i << endl;
            if (t->product.codigo == code) {
                cout << "Código: " << t->product.codigo << endl;
                cout << "Color: " << t->product.color << endl;
                cout << "Precio al que se compró: " << t->product.costoComprado << endl;
                cout << "Precio al que se vende: " << t->product.costoVendido << endl;
                cout << "Existencia: " << t->product.existencia << endl;
                cout << "Marca: " << t->product.marca << endl;
                cout << "Modelo: " << t->product.modelo << endl;
                cout << "Proveedor: " << t->product.proveedor << endl;
                cout << endl;
                break;
            }
            t = t->next;
            i++;
        }
        if (!existe) {
            cout << "El producto con ese codigo no existe" << endl;
            cout << "Se cancela todo" << endl;
            return;
        }
        cout << endl;
    }

    fflush(stdin);
    venta.cantidad = pedirEntero("Digite la cantidad de productos en el reembolzo: ");

    if (venta.cantidad <= 0) {
        if (venta.cantidad == 0) {
            cout << "No puede reembolzar 0 productos" << endl;
            cout << "Se cancela todo" << endl;
            return;
        }
        if (venta.cantidad < 0) {
            cout << "No puede ingresar un número negativo" << endl;
            cout << "Se cancela todo" << endl;
            return;
        }
    }
    else {
        t->product.existencia += venta.cantidad;
        writeFile();
    }

    fflush(stdin);
    cout << "Digite el codigo numerico del vendedor: ";
    venta.vendedor = pedirEntero("");

    FILE *archV;
    archV = fopen("vendedores.dat", "r+b");
    if (archV == NULL) {
        cout << "Archivo vendedores.dat no encontrado" << endl;
        cout << "Se cancela todo" << endl;
        return;
    }
    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
    Vendedor vendedor;

    fflush(stdin);
    int cod = venta.vendedor;

    int existe = 0;
    fread(&vendedor, sizeof(Vendedor), 1, archV);
    while (!feof(archV)) {
        if (cod == vendedor.clave) {
            cout << vendedor.clave;
            printf(": %s : ", vendedor.nombre);
            cout << vendedor.salario << endl;

            existe = 1;
            break;
        }
        fread(&vendedor, sizeof(Vendedor), 1, archV);
    }
    if (existe == 0) {
        printf("No existe un vendedor con dicha clave\n");
        cout << "Se cancela todo" << endl;
        return;
    }

    fclose(archV);

    fwrite(&venta, sizeof(Venta), 1, arch);
    fclose(arch);
}

void consultaVenta() {
    FILE *arch;
    arch = fopen("ventas.dat", "r+b");
    if (arch == NULL) {
        cout << "Archivo no encontrado" << endl;
        return;
    }
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

void inventarioPantalla() {
    cout << "Inventario" << endl;
    for (int i = 0; i < (10 + (20 * 7)); i++) {
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
    cout << setw(20) << left << "Proveedor";
    cout << endl;

    for (int i = 0; i < (10 + (20 * 7)); i++) {
        cout << "-";
    }
    cout << endl;

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
                cout << setw(20) << left << t->product.proveedor;
                cout << endl;
            }
        }
    }
}

void reporteDeVentasPantalla() {
    cout << "Reporte de ventas" << endl;
    FILE *arch;

    int pc = 0;
    int pv = 0;

    arch = fopen("ventas.dat", "r+b");
    if (arch == NULL) {
        cout << "Archivo no encontrado" << endl;
        return;
    }
    for (int i = 0; i < ((10 * 7) + 15); i++) {
        cout << "-";
    }
    cout << endl;

    cout << setw(10) << left << "Tipo";
    cout << setw(10) << left << "No.";
    cout << setw(15) << left << "Fecha";
    cout << setw(10) << left << "Clave";
    cout << setw(10) << left << "Cantidad";
    cout << setw(10) << left << "Precio Comprado";
    cout << setw(10) << left << "Precio Vendido";
    cout << setw(10) << left << "Vendedor";
    cout << endl;

    for (int i = 0; i < ((10 * 7) + 15); i++) {
        cout << "-";
    }
    cout << endl;

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

        cout << setw(10) << left << venta.numero;
        cout << setw(15) << left << fecha;
        cout << setw(10) << left << venta.clave;
        cout << setw(10) << left << venta.cantidad;

        string code = venta.clave;
        Tlist t;
        int n = hashFunction(code);
        if (hashTable[n] == NULL) {
            cout << "No existe el producto con ese codigo" << endl;
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
                cout << "El producto con ese codigo no existe" << endl;
            }
        }
        cout << setw(10) << left << t->product.costoComprado;

        cout << setw(10) << left << t->product.costoVendido;

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
    cout << endl;
    fclose(arch);

    cout << endl;
    cout << "Inversión: " << pc << endl;
    cout << "Dinero total recaudado de las ventas: " << pv << endl;
    cout << "Ganancia: " << pv - pc << endl;
}

void reporteDeProveedoresPantalla() {
    cout << "Reporte de proveedores" << endl;
    FILE *arch;
    arch = fopen("proveedores.dat", "r+b");
    if (arch == NULL) {
        cout << "Archivo no encontrado" << endl;
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

    Proveedor proveedor;
    fread(&proveedor, sizeof(Proveedor), 1, arch);
    while (!feof(arch)) {
        cout << setw(20) << left << proveedor.clave;
        cout << setw(20) << left << proveedor.nombre;
        cout << setw(20) << left << proveedor.telefono;

        fread(&proveedor, sizeof(Proveedor), 1, arch);
    }
    cout << endl;
    fclose(arch);
}

/****************************************
 * Reportes en archivo de texto
 ***************************************/

void inventarioArchivo() {
    ofstream arch;
    arch.open("Inventario.txt");

    arch << "Inventario" << endl;
    for (int i = 0; i < (10 + (20 * 7)); i++) {
        arch << "-";
    }
    arch << endl;

    arch << setw(10) << left << "Clave";
    arch << setw(20) << left << "Modelo";
    arch << setw(20) << left << "Marca";
    arch << setw(20) << left << "Color";
    arch << setw(20) << left << "Precio Venta";
    arch << setw(20) << left << "Precio Compra";
    arch << setw(20) << left << "Existencia";
    arch << setw(20) << left << "Proveedor";
    arch << endl;

    for (int i = 0; i < (10 + (20 * 7)); i++) {
        arch << "-";
    }
    arch << endl;

    for (int i = 0; i < NUMBER_OF_SLOTS; i++) {
        if (hashTable[i] == NULL) {
        }
        else {
            Tlist t = hashTable[i];
            arch << setw(10) << left << t->product.codigo;
            arch << setw(20) << left << t->product.modelo;
            arch << setw(20) << left << t->product.marca;
            arch << setw(20) << left << t->product.color;
            arch << setw(20) << left << t->product.costoVendido;
            arch << setw(20) << left << t->product.costoComprado;
            arch << setw(20) << left << t->product.existencia;
            arch << setw(20) << left << t->product.proveedor;
            arch << endl;
            while (t->next != NULL) {
                t = t->next;
                arch << setw(10) << left << t->product.codigo;
                arch << setw(20) << left << t->product.modelo;
                arch << setw(20) << left << t->product.marca;
                arch << setw(20) << left << t->product.color;
                arch << setw(20) << left << t->product.costoVendido;
                arch << setw(20) << left << t->product.costoComprado;
                arch << setw(20) << left << t->product.existencia;
                arch << setw(20) << left << t->product.proveedor;
                arch << endl;
            }
        }
    }
    arch.close();
}

void reporteDeVentasArchivo() {
    ofstream archivo;
    archivo.open("Reporte de ventas.txt");

    archivo << "Reporte de ventas" << endl;
    FILE *arch;

    int pc = 0;
    int pv = 0;

    arch = fopen("ventas.dat", "r+b");
    if (arch == NULL) {
        archivo << "Archivo no encontrado" << endl;
        return;
    }
    for (int i = 0; i < ((10 * 7) + 15); i++) {
        archivo << "-";
    }
    archivo << endl;

    archivo << setw(10) << left << "Tipo";
    archivo << setw(10) << left << "No.";
    archivo << setw(15) << left << "Fecha";
    archivo << setw(10) << left << "Clave";
    archivo << setw(10) << left << "Cantidad";
    archivo << setw(10) << left << "Precio Comprado";
    archivo << setw(10) << left << "Precio Vendido";
    archivo << setw(10) << left << "Vendedor";
    archivo << endl;

    for (int i = 0; i < ((10 * 7) + 15); i++) {
        archivo << "-";
    }
    archivo << endl;

    Venta venta;
    fread(&venta, sizeof(Venta), 1, arch);
    while (!feof(arch)) {
        if (venta.esVenta) {
            archivo << setw(10) << left << "Venta";
        }
        else {
            archivo << setw(10) << left << "Reembolzo";
        }

        string fecha = to_string(venta.dia) + "/" + to_string(venta.mes) + "/" + to_string(venta.anho);

        archivo << setw(10) << left << venta.numero;
        archivo << setw(15) << left << fecha;
        archivo << setw(10) << left << venta.clave;
        archivo << setw(10) << left << venta.cantidad;

        string code = venta.clave;
        Tlist t;
        int n = hashFunction(code);
        if (hashTable[n] == NULL) {
            archivo << "No existe el producto con ese codigo" << endl;
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
                archivo << "El producto con ese codigo no existe" << endl;
            }
        }
        archivo << setw(10) << left << t->product.costoComprado;

        archivo << setw(10) << left << t->product.costoVendido;

        if (venta.esVenta) {
            pc += (t->product.costoComprado * venta.cantidad);
            pv += (t->product.costoVendido * venta.cantidad);
        }
        else {
            pc -= (t->product.costoComprado * venta.cantidad);
            pv -= (t->product.costoVendido * venta.cantidad);
        }
        archivo << setw(10) << left << venta.vendedor;
        archivo << endl;

        fread(&venta, sizeof(Venta), 1, arch);
    }
    archivo << endl;
    fclose(arch);

    archivo << endl;
    archivo << "Inversión: " << pc << endl;
    archivo << "Dinero total recaudado de las ventas: " << pv << endl;
    archivo << "Ganancia: " << pv - pc << endl;
    archivo.close();
}

void reporteDeProveedoresArchivo() {
    ofstream archivo;
    archivo.open("Reporte de proveedores.txt");

    archivo << "Reporte de proveedores" << endl;
    FILE *arch;
    arch = fopen("proveedores.dat", "r+b");
    if (arch == NULL) {
        archivo << "Archivo no encontrado" << endl;
        return;
    }
    for (int i = 0; i < ((20 * 3)); i++) {
        archivo << "-";
    }
    archivo << endl;

    archivo << setw(20) << left << "Clave";
    archivo << setw(20) << left << "Nombre";
    archivo << setw(20) << left << "Teléfono";
    archivo << endl;

    for (int i = 0; i < ((20 * 3)); i++) {
        archivo << "-";
    }
    archivo << endl;

    Proveedor proveedor;
    fread(&proveedor, sizeof(Proveedor), 1, arch);
    while (!feof(arch)) {
        archivo << setw(20) << left << proveedor.clave;
        archivo << setw(20) << left << proveedor.nombre;
        archivo << setw(20) << left << proveedor.telefono;

        fread(&proveedor, sizeof(Proveedor), 1, arch);
    }
    archivo << endl;
    fclose(arch);
    archivo.close();
}

/****************************************
 * Administración
 ***************************************/

void crear() {
    string str;

    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));

    cout << "Dijite el nombre del archivo que quiere crear, junto con su extensión: ";
    cin >> str;

    string comando = "type nul > " + str;

    system(comando.c_str());
}

void respaldar() {
    FILE *arch;

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

void restaurar() {
    FILE *arch;

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

void compactar() {
    FILE *arch;

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

int main() {
    // Establecer el idioma a español
    setlocale(LC_ALL, "es_ES");  // Cambiar locale - Suficiente para máquinas Linux
    SetConsoleCP(65001);         // Cambiar STDIN -  Para máquinas Windows
    SetConsoleOutputCP(65001);   // Cambiar STDOUT - Para máquinas Windows

    fflush(stdin);

    initializeHashTable();
    fillHashTable();

    int opcion1,
        opcion2, opcion3;

    string objetivo;

    char c[] = "123";
    char intento[20];

    bool con = true;

    while (opcion1 != 8) {
        system("cls");
        cout << "1. Accesorios" << endl;
        cout << "2. Proveedores" << endl;
        cout << "3. Vendedor" << endl;
        cout << "4. Ventas" << endl;
        cout << "5. Informes" << endl;
        cout << "6. Administración" << endl;
        cout << "7. Ayuda" << endl;
        cout << "8. Salir" << endl;
        cout << "Presione su opción: " << endl;
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
                    cout << "1. Agregar " + objetivo << endl;
                    cout << "2. Eliminar " + objetivo << endl;
                    cout << "3. Modificar " << endl;
                    cout << "4. Buscar " + objetivo << endl;
                    cout << "5. Regresar" << endl;
                    cout << "Presione su opción: " << endl;
                    opcion2 = escucharTecla(5);
                    switch (opcion2) {
                        case 1: {
                            altaProducto();
                            break;
                        }
                        case 2: {
                            FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
                            while (!codigoValido) {
                                printf("Ingrese el codigo del producto a eliminar: ");
                                fflush(stdin);
                                getline(cin, code);
                                strcpy(code_char, code.c_str());
                                codigoValido = validarCodigo(code_char);
                                if (!codigoValido) {
                                    cout << "Usted ingreso un codigo invalido!!!" << endl;
                                    cout << "Un codigo correcto empieza con 2 letras y le siguen 4 numeros" << endl;
                                }
                            }
                            bajaProducto(code);
                            break;
                        }
                        case 3: {
                            FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
                            codigoValido = 0;
                            while (!codigoValido) {
                                printf("Ingrese el codigo del producto a modificar: ");
                                fflush(stdin);
                                getline(cin, code);
                                strcpy(code_char, code.c_str());
                                codigoValido = validarCodigo(code_char);
                                if (!codigoValido) {
                                    cout << "Usted ingreso un codigo invalido!!!" << endl;
                                    cout << "Un codigo correcto empieza con 2 letras y le siguen 4 numeros" << endl;
                                }
                            }
                            cambioProducto(code);
                            break;
                        }
                        case 4: {
                            FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
                            codigoValido = 0;
                            while (!codigoValido) {
                                printf("Ingrese el codigo del producto a buscar: ");
                                fflush(stdin);
                                getline(cin, code);
                                strcpy(code_char, code.c_str());
                                codigoValido = validarCodigo(code_char);
                                if (!codigoValido) {
                                    cout << "Usted ingreso un codigo invalido!!!" << endl;
                                    cout << "Un codigo correcto empieza con 2 letras y le siguen 4 numeros" << endl;
                                }
                            }
                            consultaProducto(code);
                            break;
                        }
                        case 5: {
                            cout << "Regresando al menú principal" << endl;
                            break;
                        }
                        default: {
                            cout << "Digite una opción correcta" << endl;
                            break;
                        }
                    }
                    continuar();
                }
                break;
            }
            case 2: {
                while (opcion2 != 5) {
                    objetivo = "proveedor";
                    system("cls");
                    cout << "1. Agregar " + objetivo << endl;
                    cout << "2. Eliminar " + objetivo << endl;
                    cout << "3. Modificar " << endl;
                    cout << "4. Buscar " + objetivo << endl;
                    cout << "5. Regresar" << endl;
                    cout << "Presione su opción: " << endl;
                    opcion2 = escucharTecla(5);
                    switch (opcion2) {
                        case 1: {
                            altaProveedor();
                            break;
                        }
                        case 2: {
                            bajaProveedor();
                            break;
                        }
                        case 3: {
                            cambioProveedor();
                            break;
                        }
                        case 4: {
                            consultaProveedor();
                            break;
                        }
                        case 5: {
                            cout << "Regresando al menú principal" << endl;
                            break;
                        }
                        default: {
                            cout << "Digite una opción correcta" << endl;
                            break;
                        }
                    }
                    continuar();
                }
                break;
            }
            case 3: {
                while (opcion2 != 5) {
                    objetivo = "vendedor";
                    system("cls");
                    cout << "1. Agregar " + objetivo << endl;
                    cout << "2. Eliminar " + objetivo << endl;
                    cout << "3. Modificar " << endl;
                    cout << "4. Buscar " + objetivo << endl;
                    cout << "5. Regresar" << endl;
                    cout << "Presione su opción: " << endl;
                    opcion2 = escucharTecla(5);
                    switch (opcion2) {
                        case 1: {
                            altaVendedor();
                            break;
                        }
                        case 2: {
                            bajaVendedor();
                            break;
                        }
                        case 3: {
                            cambioVendedor();
                            break;
                        }
                        case 4: {
                            consultaVendedor();
                            break;
                        }
                        case 5: {
                            cout << "Regresando al menú principal" << endl;
                            break;
                        }
                        default: {
                            cout << "Digite una opción correcta" << endl;
                            break;
                        }
                    }
                    continuar();
                }
                break;
            }
            case 4: {
                while (opcion2 != 3) {
                    bool codigoValido;
                    string code;
                    char code_char[6 + 1];

                    system("cls");
                    cout << "1. Venta de un producto " << endl;
                    cout << "2. Reembolso de un producto " << endl;
                    cout << "3. Regresar" << endl;
                    cout << "Presione su opción: " << endl;
                    opcion2 = escucharTecla(3);
                    switch (opcion2) {
                        case 1: {
                            altaVenta();
                            break;
                        }
                        case 2: {
                            bajaVenta();
                            break;
                        }
                        case 3: {
                            cout << "Regresando al menú principal" << endl;
                            break;
                        }
                        default: {
                            cout << "Digite una opción correcta" << endl;
                            break;
                        }
                    }
                    continuar();
                }
                break;
            }
            case 5: {
                while (opcion2 != 4) {
                    system("cls");
                    cout << "1. Inventario" << endl;
                    cout << "2. Reporte de ventas" << endl;
                    cout << "3. Reporte de proveedores" << endl;
                    cout << "4. Regresar" << endl;
                    cout << "Presione su opción: " << endl;
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
                                continuar();
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
                                        cout << "Regresando al menú de informes" << endl;
                                        break;
                                    }
                                    default: {
                                        cout << "Digite una opción correcta" << endl;
                                        break;
                                    }
                                }
                                continuar();
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
                                        cout << "Regresando al menú de informes" << endl;
                                        break;
                                    }
                                    default: {
                                        cout << "Digite una opción correcta" << endl;
                                        break;
                                    }
                                }
                                continuar();
                            }
                            break;
                        }
                        case 4: {
                            cout << "Regresando al menú principal" << endl;
                            continuar();
                            break;
                        }
                        default: {
                            cout << "Digite una opción correcta" << endl;
                            continuar();
                            break;
                        }
                    }
                }
                break;
            }

            case 6: {
                FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
                system("cls");
                bool hayCaracterIncorrecto = false;
                fflush(stdin);
                cout << "Digite la contraseña: ";
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
                                cout << "Regresando al menú principal" << endl;
                                break;
                            }
                            default: {
                                cout << "Digite una opción correcta" << endl;
                                break;
                            }
                        }
                        continuar();
                    }
                }
                else {
                    cout << "Contraseña incorrecta" << endl;
                    cout << "Regresando al menú principal" << endl;
                    continuar();
                }
                break;
            }
            case 7: {
                break;
            }
            case 8: {
                cout << "Hasta luego! " << endl;
                continuar();
                break;
            }
            default: {
                cout << "Digite una opción correcta! " << endl;
                continuar();
                break;
            }
        }
    }
    return 0;
}
