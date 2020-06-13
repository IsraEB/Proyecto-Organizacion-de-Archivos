#include <conio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <windows.h>

#include <ctime>
#include <iostream>
#include <string>

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

typedef struct
{
    char codigo[7];
    char marca[20];
    char modelo[20];
    char color[20];
    float costoComprado;
    float costoVendido;
    int existencia;
    char proveedor[20];
} tproducto;

struct node {
    tproducto product;
    struct node *next;
};
typedef struct node *Tlist;

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
            //printf("%i %s %0.2f\n", producto.codigo, producto.descripcion, producto.precio);

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
            //printf("%i %s %0.2f\n", producto.codigo, producto.descripcion, producto.precio);

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
            //printf("%i %s %0.2f\n", producto.codigo, producto.descripcion, producto.precio);

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
            //printf("%i %s %0.2f\n", producto.codigo, producto.descripcion, producto.precio);

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
            //printf("%i %s %0.2f\n", producto.codigo, producto.descripcion, producto.precio);

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
            //printf("%i %s %0.2f\n", producto.codigo, producto.descripcion, producto.precio);

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

// int sleepT = 100;
// void continuar() {
//     FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
//     cout << "Presione cualquier tecla para continuar\n";
//     fflush(stdin);
//     getch();
//     Sleep(sleepT);
// }

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
