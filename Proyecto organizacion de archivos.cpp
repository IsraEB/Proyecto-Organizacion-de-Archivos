#include <conio.h>
#include <locale.h>
#include <stdlib.h>
#include <wchar.h>
#include <windows.h>

#include <ctime>
#include <iostream>
#include <string>

int sleepT = 100;

using namespace std;

void continuar() {
    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
    cout << "Presione cualquier tecla para continuar\n";
    fflush(stdin);
    getch();

    Sleep(sleepT);
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
    if (nOpciones >= 8) {
        while (true) {
            for (int i = 0; i < 8; i++) {
                if ((GetKeyState(VK_CONTROL) & 0x8000) && (GetKeyState(letras[i]) & 0x8000)) {
                    Sleep(sleepT);
                    return i + 1;
                }
            }
            for (int i = 49; i <= 49 + (nOpciones - 1); i++) {
                if (GetKeyState(i) & 0x8000) {
                    Sleep(sleepT);
                    return i - 48;
                }
            }
        }
    }
    else {
        while (true) {
            for (int i = 0; i < nOpciones; i++) {
                if ((GetKeyState(VK_CONTROL) & 0x8000) && (GetKeyState(letras[i]) & 0x8000)) {
                    Sleep(sleepT);
                    return i + 1;
                }
            }
            for (int i = 49; i <= 49 + (nOpciones - 1); i++) {
                if (GetKeyState(i) & 0x8000) {
                    Sleep(sleepT);
                    return i - 48;
                }
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
    getch();
    return 0;
}
