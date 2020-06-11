#include <conio.h>
#include <locale.h>
#include <stdlib.h>
#include <wchar.h>
#include <windows.h>

#include <ctime>
#include <iostream>
#include <string>

using namespace std;

void continuar() {
    cout << "Presione una tecla para continuar\n";
    getch();
}

int pedirEntero(string peticion) {
    string str;
    cout << peticion;

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

int main() {
    setlocale(LC_ALL, "");
    fflush(stdin);

    int opcion1, opcion2, opcion3;
    char c[] = "123";
    char intento[20];

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
        opcion1 = pedirEntero("Digite su opción: ");
        opcion2 = 0;
        switch (opcion1) {
            case 1: {
                while (opcion2 != 5) {
                    system("cls");
                    cout << "1. Agregar accesorio" << endl;
                    cout << "2. Eliminar accesorio" << endl;
                    cout << "3. Modificar accesorio" << endl;
                    cout << "4. Buscar accesorio" << endl;
                    cout << "5. Regresar" << endl;
                    opcion2 = pedirEntero("Digite su opción: ");
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
                    system("cls");
                    cout << "1. Agregar proveedor" << endl;
                    cout << "2. Eliminar proveedor" << endl;
                    cout << "3. Modificar proveedor" << endl;
                    cout << "4. Buscar proveedor" << endl;
                    cout << "5. Regresar" << endl;
                    opcion2 = pedirEntero("Digite su opción: ");
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
                    system("cls");
                    cout << "1. Agregar vendedor" << endl;
                    cout << "2. Eliminar vendedor" << endl;
                    cout << "3. Modificar vendedor" << endl;
                    cout << "4. Buscar vendedor" << endl;
                    cout << "5. Regresar" << endl;
                    opcion2 = pedirEntero("Digite su opción: ");
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
                    opcion2 = pedirEntero("Digite su opción: ");
                    opcion3 = 0;
                    switch (opcion2) {
                        case 1: {
                            while (opcion3 != 3) {
                                system("cls");
                                cout << "1. Reporte impreso en pantalla" << endl;
                                cout << "2. Reporte en archivo de texto" << endl;
                                cout << "3. Regresar" << endl;
                                opcion3 = pedirEntero("Digite su opción: ");
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
                                opcion3 = pedirEntero("Digite su opción: ");
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
                                opcion3 = pedirEntero("Digite su opción: ");
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
                break;
            }

            case 6: {
                system("cls");
                bool hayCaracterIncorrecto = false;
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
                        opcion2 = pedirEntero("Digite su opción: ");
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
