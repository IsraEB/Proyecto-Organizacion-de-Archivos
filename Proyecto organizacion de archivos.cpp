#include <conio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <windows.h>

#include <ctime>
#include <iostream>
#include <string>

#define NUMBER_OF_SLOTS 100

using namespace std;

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

bool fillHashTable() {
    FILE *arch;

    arch = fopen("productos.dat", "rb");

    if (arch == NULL) {
        return false;
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
    return true;
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

void altaProducto() {
    tproducto producto;
    bool codigoValido = 0;

    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));

    while (!codigoValido) {
        printf("Ingrese el codigo del producto: ");
        fflush(stdin);
        gets(producto.codigo);
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

    fflush(stdin);
    cout << "Ingrese el precio al que se compró el producto: ";
    cin >> producto.costoComprado;

    fflush(stdin);
    cout << "Ingrese el precio al que se vende el producto: ";
    cin >> producto.costoVendido;

    fflush(stdin);
    cout << "Ingrese cuantas unidades se compraron: ";
    cin >> producto.existencia;

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
                cin >> t->product.costoComprado;

                fflush(stdin);
                cout << "Ingrese el precio al que se vende el producto: ";
                cin >> t->product.costoVendido;

                fflush(stdin);
                cout << "Ingrese cuantas unidades se compraron: ";
                cin >> t->product.existencia;
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

typedef struct {
    char clave[20];
    char nombre[20];
    unsigned int telefono;
} Proveedor;

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
    cin >> proveedor.telefono;

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
            cin >> proveedor.telefono;

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

typedef struct {
    char clave[20];
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
    cout << "Digite la clave del vendedor: ";
    cin.getline(vendedor.clave, 20, '\n');

    fflush(stdin);
    cout << "Digite el nombre del vendedor: ";
    cin.getline(vendedor.nombre, 20, '\n');

    fflush(stdin);
    cout << "Digite el número telefónico del vendedor: ";
    cin >> vendedor.salario;

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

    printf("Ingrese la clave del vendedor a consultar:");
    fflush(stdin);
    string cod;
    getline(cin, cod);
    Vendedor vendedor;
    int existe = 0;
    fread(&vendedor, sizeof(Vendedor), 1, arch);
    while (!feof(arch)) {
        if (cod == vendedor.clave) {
            printf("%s : ", vendedor.clave);
            printf("%s : ", vendedor.nombre);
            cout << vendedor.salario << endl;

            string cadenaVacia = "";

            strcpy(vendedor.clave, cadenaVacia.c_str());
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

    printf("Ingrese la clave del vendedor a consultar:");
    fflush(stdin);
    string cod;
    getline(cin, cod);
    Vendedor vendedor;
    int existe = 0;
    fread(&vendedor, sizeof(Vendedor), 1, arch);
    while (!feof(arch)) {
        if (cod == vendedor.clave) {
            printf("%s : ", vendedor.clave);
            printf("%s : ", vendedor.nombre);
            cout << vendedor.salario << endl;

            fflush(stdin);
            cout << "Digite el nombre del vendedor: ";
            cin.getline(vendedor.nombre, 20, '\n');

            fflush(stdin);
            cout << "Digite el número telefónico del vendedor: ";
            cin >> vendedor.salario;

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

    printf("Ingrese la clave del vendedor a consultar:");
    fflush(stdin);
    string cod;
    getline(cin, cod);
    Vendedor vendedor;
    int existe = 0;
    fread(&vendedor, sizeof(Vendedor), 1, arch);
    while (!feof(arch)) {
        if (cod == vendedor.clave) {
            printf("%s : ", vendedor.clave);
            printf("%s : ", vendedor.nombre);
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
        cout << "Intentemoslo de nuevo" << endl;
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

int main() {
    setlocale(LC_ALL, "");
    fflush(stdin);

    initializeHashTable();
    if (!fillHashTable()) {
        system("cls");
        cout << "Error al abrir productos.dat" << endl;
        exit(1);
    }

    int opcion1, opcion2, opcion3;

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
                                        break;
                                    }
                                    case 2: {
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
                                        break;
                                    }
                                    case 2: {
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
                                        break;
                                    }
                                    case 2: {
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
                                break;
                            }
                            case 2: {
                                break;
                            }
                            case 3: {
                                break;
                            }
                            case 4: {
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
