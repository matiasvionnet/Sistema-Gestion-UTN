/*-------------------------Listado de librerias-------------------------*/
#include <iostream>
#include <cstring>
#include <conio.h> //getch
#include <iomanip> //ayuda a organizar la informacion impresa en pantalla
#include <windows.h> //Permite cambiar de color el texto y la terminal
#include <vector>
using namespace std;
/*----------------------------------------------------------------------*/

/*-------------------------Estructuras-------------------------*/
struct Beneficio {
    char nombre[20]="";
    int costo;
};

struct Estudiante {
    char mail[50];
    char contraseña[50];
    int creditos;
};

bool salirConsumidor = false;
/*-------------------------------------------------------------*/

/*-------------------------------------------Listado de funciones-------------------------------------------*/
//primera parte en la que se inicia sesion y se verifica
void mostrarMenu();
void iniciarSesion();
int verificarMailYContraseña(const char* mailBuscado, const char* contraBuscada, int& creditosEstudiante);
Estudiante dameEstudianteLogin();

//segunda parte en la que se accede al menu para gastar los creditos
void mostrarMenu(int creditos, const char* mail);
int listarBeneficios(int& cantBeneficios);
void restarCreditos(int opcion, int& creditos);
void guardarCreditos(const char* mailBuscado, int creditos);
void Terminar_consumidor();
/*----------------------------------------------------------------------------------------------------------*/

/*-------------------------Main-------------------------*/
void ejecutar_consumidor() {
    salirConsumidor = false;
    mostrarMenu();
};
/*------------------------------------------------------*/

/*------------------------------------------Inicio de sesion y menues------------------------------------------*/
void mostrarMenu() {
    system("cls"); //limpia la pantalla cada vez que se inicia
    system("Color 02");
    int opcion;
    do{
        cout << "\n\t******************************************************" << endl;
        cout << "\t*              Consumidor de beneficios              *" << endl;
        cout << "\t******************************************************" << endl;
        cout << "\n\t   1. Iniciar sesion" << endl;
        cout << "\t   2. Salir" << endl;
        cout << "\n\t  Elija una opcion: ";
    
        if (cin >> opcion) {
            while (cin.get() != '\n'); // Limpia el búfer de entrada
            switch (opcion) {
                case 1:
                    iniciarSesion();
                    system("cls");
                    break;
                case 2:
                    Terminar_consumidor();
                    system("cls");
                    break;
                default:
                    cout << "Opcion no valida." << endl;
                    system("pause");
                    system("cls");
                    break;
            }
        } else {
            //esta parte elimina el error de poner letras en la opcion
            // Si la lectura de la opción falla, limpiar el estado de error y el búfer de entrada
            cin.clear();
            while (cin.get() != '\n'); // Limpia el búfer de entrada
            system("cls");
        }
    } while(opcion != 2 && !salirConsumidor); // Repetir el bucle hasta que el inicio de sesión sea exitoso o el usuario elija salir
}

void iniciarSesion() {
    system("Color 02");
    system("cls");
    Estudiante estudiante;
    int opcion;
    do {
        cout << "\n\t**********************************" << endl;
	    cout << "\t*         Iniciar sesion         *" << endl;
	    cout << "\t**********************************" << endl;
        estudiante = dameEstudianteLogin(); //se piden los datos on la función dameEstudiante y se guardan en la var estudiante
        int creditos;

        //Se realiza la verificación del mail
        if (verificarMailYContraseña(estudiante.mail, estudiante.contraseña, creditos)) {
            // Correo electrónico y contraseña coinciden
            cout << "\n\tInicio exitoso, presione enter." << endl;
            cin.get();
            system("cls");
            mostrarMenu(creditos, estudiante.mail); //si es todo correcto se muestra el menu
            break;
        } else {
            system("cls");
            cout << "\n\tLa contrasenia o mail son incorrectos" << endl;
            cout << "\t1. Volver a intentar" << endl;
            cout << "\t2. Salir" << endl;
            cin >> opcion;
            if(opcion == 2){
                Terminar_consumidor();
            }
            cin.ignore(); // Limpiar el búfer de entrada
            system("cls");
        }

        
    } while (opcion != 2); // Repetir el bucle hasta que el inicio de sesión sea exitoso o el usuario elija salir

}

Estudiante dameEstudianteLogin() {
    system("Color 02");
    Estudiante estudiante;

    cout << "\n\tIngrese su mail: ";
    cin.getline(estudiante.mail, sizeof(estudiante.mail));

    cout << "\n\tIngrese su contrasenia: ";
    cin.getline(estudiante.contraseña, sizeof(estudiante.contraseña));

    return estudiante;
}

int verificarMailYContraseña(const char* mailBuscado, const char* contraBuscada, int& creditosEstudiante) {
    system("Color 02");
    FILE* archivo = fopen("Estudiantes.dat", "rb");
    if (archivo != nullptr) {
        // que pasa si el archivo es distinto de NULL
        Estudiante estudiante;
        while (fread(&estudiante, sizeof(Estudiante), 1, archivo) == 1) {
            // lo que pasa mientras se esté leyendo
            if (strcmp(estudiante.mail, mailBuscado) == 0 && strcmp(estudiante.contraseña, contraBuscada) == 0) {
                creditosEstudiante = estudiante.creditos;
                fclose(archivo);
                return 1; // El mail y la contraseña coinciden
            }
        }
        fclose(archivo);
    } else {
        // que pasa si el archivo es igual a NULL
        cout << "\n\tNo se pudo abrir el archivo para lectura." << endl;
    }
    return 0; // El mail o la contraseña no coinciden
}

void mostrarMenu(int creditos, const char* mail){
    Beneficio beneficio;
    system("Color 02");
    int opcion;
    int cantBeneficios = 0;

     do {
        cout << "\n\t**********************************" << endl;
	    cout << "\t*              Menu              *" << endl;
	    cout << "\t**********************************" << endl;
        cout << "\n\tTus creditos son: " << creditos <<endl;
        cout << "\tElige tu beneficio:" <<endl;
        cantBeneficios = 0;

        listarBeneficios(cantBeneficios);
        cout << "\t" << cantBeneficios + 1 << ". Salir" << endl;
        cout<< "\n\tselecione una opcion: ";

        if (cin >> opcion) {
            while (cin.get() != '\n'); // Limpia el búfer de entrada
            system("cls");

            if (opcion >= 1 && opcion <= cantBeneficios) {
                //que pasa si elige una opcion valida
                restarCreditos(opcion, creditos);
                guardarCreditos(mail, creditos);

                // Mostrar el nombre del beneficio seleccionado
                FILE* archivo = fopen("Beneficios.dat", "rb");
                if (archivo != nullptr) {
                    for (int i = 0; i < opcion; i++) {
                        if (fread(&beneficio, sizeof(Beneficio), 1, archivo) != 1) {
                            break;
                        }
                    }
                    fclose(archivo);
                }
                cout << "\tElegiste el beneficio: " << beneficio.nombre << endl;
                cin.get();
                system("cls");
            } else if (opcion == cantBeneficios + 1) { 
            } else {
                //que pasa si elige una opcion invalida
                cout << "\n\tOpcion invalida. Por favor, elige una opcion valida." << endl;
                cin.get();
                system("cls");
            }
        } else {
            //esta parte elimina el error de poner letras en la opcion
            // Si la lectura de la opción falla, limpiar el estado de error y el búfer de entrada
            cin.clear();
            while (cin.get() != '\n'); // Limpia el búfer de entrada
            system("cls");
        }
        if(opcion == cantBeneficios + 1){
            Terminar_consumidor();
        }
    } while (opcion != cantBeneficios + 1 && !salirConsumidor);//el do se sigue repitiendo hasta que se elija salir
};
/*-------------------------------------------------------------------------------------------------------------*/

/*---------------------------------Funcion que muestra la lista de beneficios---------------------------------*/
int listarBeneficios(int& cantBeneficios){
    system("Color 02");
    FILE* archivo = fopen("Beneficios.dat", "rb");
    if (archivo != nullptr) {
        Beneficio beneficio;
        
        while (fread(&beneficio, sizeof(Beneficio), 1, archivo) == 1) {
            cantBeneficios++;
            cout << "\t" << cantBeneficios <<". " <<beneficio.nombre << ": " << beneficio.costo<< endl;
        }
        fclose(archivo);
    } else {
        cout << "\n\tNo se pudo abrir el archivo para lectura." << endl;
    }
    return 0;
};
/*------------------------------------------------------------------------------------------------------------*/

/*-------------------------Gestor de creditos-------------------------*/
void restarCreditos(int opcion, int& creditos){
    system("Color 02");
    vector <int> precios;
    
    FILE* archivo = fopen("Beneficios.dat", "rb");
    if (archivo != nullptr) {
        Beneficio beneficio;
        
        while (fread(&beneficio, sizeof(Beneficio), 1, archivo) == 1) {
            precios.push_back(beneficio.costo);
        }
        fclose(archivo);
    } else {
        cout << "\n\tNo se pudo abrir el archivo para lectura." << endl;
        return; //Corta aca si no hay archivo
    }

    if(opcion < 1 || opcion > (int) precios.size()){ //Chequeo por seguridad de corrupcion del archivo
        cout << "\n\tOpcion invalida." << endl;
        return;
    }
 
    creditos = creditos - precios[opcion-1]; //resta se creditos atuales - precio

    if(creditos < 0){ //vuelve a sumar los creditos en caso de que quede en negativo
        cout<<"\n\tno tienes creditos suficientes."<<endl;
        creditos = creditos + precios[opcion-1];
    }
};

void guardarCreditos(const char* mailBuscado, int creditos){
    system("Color 02");
    FILE* archivo = fopen("Estudiantes.dat", "rb+");
    if (archivo != nullptr) {
        Estudiante estudiante;
        bool encontrado = false;
        while (!encontrado && fread(&estudiante, sizeof(Estudiante), 1, archivo) == 1) {
            if (strcmp(estudiante.mail, mailBuscado) == 0) {
                encontrado = true;
                estudiante.creditos = creditos;
                fseek(archivo, -(long) sizeof(Estudiante), SEEK_CUR);
                fwrite(&estudiante, sizeof(Estudiante), 1, archivo);
            }
        }
        fclose(archivo);
    } else {
        cout << "\n\tNo se pudo abrir el archivo para lectura y escritura." << endl;
        cin.get();
    }
};
/*--------------------------------------------------------------------*/

/*---------------------------------Funcion cerrar programa---------------------------------*/
void Terminar_consumidor(){
	system("cls");
	system("Color 02");
	
	cout << "\n\t***********************************************************************" << endl;
	cout << "\t*   Gracias por utilizar el programa, regresando al menu principal!   *" << endl;
	cout << "\t***********************************************************************" << endl;
	
	system("pause");
    salirConsumidor = true;
    return; //regresa al menu principal
}
/*--------------------------------------------------------------------------------------*/