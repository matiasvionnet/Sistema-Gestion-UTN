/*-------------------------Listado de librerias-------------------------*/
#include <iostream>
#include <cstring> //necesario para strcpy,strcmp
#include <conio.h> //utilizamos el getch
#include <iomanip> //ayuda a organizar la informacion impresa en pantalla
#include <windows.h> //Permite cambiar de color el texto y la terminal
using namespace std;
/*----------------------------------------------------------------------*/

/*-------------------------Estructuras-------------------------*/
struct Estudiante {
    char mail[50] = ""; // "" la usamos para limpiar la basura que pueda aparecer en la variable
    char contraseña[50] = "";
    int creditos;
};
/*-------------------------------------------------------------*/

/*-------------------------------Listado de funciones----------------------------------*/
void abrirArchivo();
Estudiante dameEstudiante();
void Menu_registro();
int verificarMail(const char* mailBuscado);
void Terminar_registro();
/*-------------------------------------------------------------------------------------*/

/*-------------------------Main-------------------------*/
void ejecutar_registro(){
    Menu_registro();
}
/*------------------------------------------------------*/

/*-------------------------------Funciones de registro----------------------------------*/
void Menu_registro() {
    system("cls"); //limpia la pantalla cada vez que se inicia
    system("Color 02");
    int opcion;
    do{
        cout << "\n\t**************************************" << endl;
        cout << "\t*              Registro              *" << endl;
        cout << "\t**************************************" << endl;
        cout << "\n\t   1. Registrarse" << endl;
        cout << "\t   2. Salir" << endl;
        cout << "\n\t  Elija una opcion: ";
    
        if (cin >> opcion) {
            while (cin.get() != '\n'); // Limpia el búfer de entrada
            switch (opcion) {
                case 1:
                    abrirArchivo();
                    system("cls");
                    break;
                case 2:
                    Terminar_registro();
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
    } while(opcion != 2); // Repetir el bucle hasta que el inicio de sesión sea exitoso o el usuario elija salir
}

//Funcion que le pide al usuario que ingrese su mail y su contrasenia para registrarlo en el sistema
//la funcion dameEstudiante hace lo dicho anteriormente y le asigna 1000 creditos de regalo
//verificar mail lee el archivo y se asegura de que no se haya ingresado un mail repetido

bool esmailValido(const char* mail) {
    int arrobas = 0;
    int puntos = 0;
    int longmail = strlen(mail);

    // Verifica que el mail no esté vacío
    if (longmail == 0)
        return false;

    // Verifica que el mail no comience con un punto o una arroba
    if (mail[0] == '.' || mail[0] == '@')
        return false;

    // Recorre el mail para validar caracteres
    for (int i = 0; i < longmail; i++) {
        char caracter = mail[i];

        // Verificar que el caracter sea alfanumérico o un punto o una arroba
        if (!((caracter >= 'A' && caracter <= 'Z') ||
              (caracter >= 'a' && caracter <= 'z') ||
              (caracter >= '0' && caracter <= '9') ||
              caracter == '.' || caracter == '@'))
            return false;

        // Contar arrobas y puntos
        if (caracter == '@')
            arrobas++;
        else if (caracter == '.')
            puntos++;
    }

    // Debe haber exactamente una arroba y al menos un punto
    if (arrobas != 1 || puntos < 1)
        return false;

    // El correo parece válido
    return true;
}

void abrirArchivo() {
    system("cls");
    system("Color 02");
    Estudiante estudiante;

    cout << "\n\t*******************************" << endl;
	cout << "\t*         Registrarse         *" << endl;
	cout << "\t*******************************" << endl;
    cout << "\n\t  Ingrese sus datos:" << endl;
    estudiante = dameEstudiante();

    if (verificarMail(estudiante.mail) == 1) {
        //lo que pasa cuando el mail ya ha sido ingresado (se devuelve 1)
        cout << "\n\tEste mail ya ha sido ingresado. Presione enter para volver al menu." << endl;
        cin.get(); // Espera a que el usuario presione Enter
    } else {
        //lo que pasa cuando el mail no ha sido ingresado (se devuelve 0)
        FILE* archivo = fopen("Estudiantes.dat", "ab"); //abrir en agregado binario
        if (archivo != nullptr) {
            fwrite(&estudiante, sizeof(Estudiante), 1, archivo);
            fclose(archivo);
            cout << "\n\tRegistro creado exitosamente." << endl;
            cout << "\tPresione enter para volver al menu." << endl;
            cin.get();
        } else {
            cout << "\n\tNo se pudo crear el archivo." << endl;
            cout << "\tPresione Enter para volver al menu." << endl;
            cin.get();
        }
    }
}

Estudiante dameEstudiante() {
    Estudiante estudiante;
    bool mailValido = false;

    do{
      cout << "\n\t  Ingrese su mail: ";
      cin.getline(estudiante.mail, sizeof(estudiante.mail));
      mailValido = esmailValido(estudiante.mail);
      if(!mailValido){
        cout << "\n\tEl mail es invalido, porfavor intente denuevo!" << endl;
      }
    } while(!mailValido);
    
    cout << "\n\t  Ingrese su contrasenia: ";
    cin.getline(estudiante.contraseña, sizeof(estudiante.contraseña));

    estudiante.creditos = 1000;

    return estudiante;
}

int verificarMail(const char* mailBuscado) {
    system("Color 02");
    Estudiante estudiante;
    FILE* archivo = fopen("Estudiantes.dat", "rb");
    
    if (archivo != nullptr) { // que pasa si el archivo es distinto de NULL
        bool archivoVacio = true;
        while (fread(&estudiante, sizeof(Estudiante), 1, archivo) == 1) { // lo que pasa mientras se esté leyendo
            archivoVacio = false;
            if (strcmp(estudiante.mail, mailBuscado) == 0) { //si estudiante.mail y mailBuscado son iguales devuelve 0 y pasa lo de abajo
                fclose(archivo);
                return 1; // El mail ya existe
            }
        }
        if(archivoVacio){
            fclose(archivo);
            return 0; //el archivo esta vacio
        }
        fclose(archivo);
    }
    return 0; // El mail no existe
}
/*--------------------------------------------------------------------------------------*/

/*---------------------------------Funcion cerrar programa---------------------------------*/
void Terminar_registro(){
	system("cls");
	system("Color 02");
	
    cout << "\n\t***********************************************************************" << endl;
	cout << "\t*   Gracias por utilizar el programa, regresando al menu principal!   *" << endl;
	cout << "\t***********************************************************************" << endl;
    
	system("pause");
    return; //regresa al menu principal
}
/*--------------------------------------------------------------------------------------*/