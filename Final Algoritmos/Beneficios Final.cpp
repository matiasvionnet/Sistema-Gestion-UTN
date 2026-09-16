/*-------------------------Listado de librerias-------------------------*/
#include <iostream>
#include <cstring> //necesario para strcpy,strcmp
#include <iomanip> //ayuda a organizar la informacion impresa en pantalla
#include <windows.h> //Permite cambiar de color el texto y la terminal
#include <cctype> //Permite utilizar tolower()

using namespace std;
/*----------------------------------------------------------------------*/

/*-------------------------Listado de funciones-------------------------*/
void Menu();
void Menu_Agregar();
void Menu_Modificar();
void Menu_Eliminar();
void Menu_Listar();
void Agregar_beneficios();
void Listar_beneficios();
void Modificar_beneficios();
void Eliminar_beneficios();
void Terminar();
/*----------------------------------------------------------------------*/

/*-------------------------Estructuras-------------------------*/
struct Beneficios {
    char nombre[20]=""; // "" la usamos para limpiar la basura que pueda aparecer en la variable
    int costo;
};

bool salirGestor = false; // Bandera compartida por todo el modulo

bool compMayMin(const char* a, const char* b){ //Compara dos beneficios para saber si son el mismo escrito en mayuscula o minuscula
	while (*a && *b){
		if(tolower((unsigned char)*a) != tolower((unsigned char)*b)){
			return false;
		}
		a++;
		b++;
	}
	return *a == *b; //ambos deben tener el mismo largo
}
/*-------------------------------------------------------------*/

/*-------------------------Main-------------------------*/
void ejecutar_gestor() {
	salirGestor = false;
	Menu();
}
/*------------------------------------------------------*/

/*---------------------------------Menues---------------------------------*/
//Creamos distintos menues para facilitar la comprension del usuario a la hora de utilizar el programa
//y aumentar la comodidad mientras se ejecuta el mismo

void Menu() {
	system("cls"); //limpia la pantalla cada vez que se inicia
	system("Color 0a");
	int opcion;
	
	do{
		cout << "\n\t**********************************************************" << endl;
		cout << "\t*                  Gestor de beneficios                  *" << endl;
		cout << "\t**********************************************************" << endl;
		cout << "\n\tBienvenido! Que vamos a hacer hoy?" << endl;
		cout << "\n\t  1. Agregar beneficios" << endl;
		cout << "\t  2. Listar beneficios" << endl;
		cout << "\t  3. Modificar el costo de un beneficio" << endl;
		cout << "\t  4. Eliminar beneficios" << endl;
		cout << "\t  5. Salir del programa" << endl;
		cout << "\n\t  Elija una opcion: ";

		if(cin >> opcion){
			while (cin.get() != '\n'); // Limpia el búfer de entrada
			switch (opcion){
				case 1:
					Agregar_beneficios();
					system("pause"); //pausa el recorrido del programa hasta que el usuario elija seguir
					break;
				case 2:
					Listar_beneficios();
					system("pause");
					break;
				case 3:
					Modificar_beneficios();
					system("pause");
					break;
				case 4:
					Eliminar_beneficios();
					system("pause");
					break;
				case 5:
					Terminar();
					break;
				default:
					cout << "\n\tOpcion no valida" << endl;
					system("pause");
					system("cls");
					break;
			}
		} else {
			//esta parte elimina el error de poner letras en la opcion
			// Si la lectura de la opción falla, limpiar el estado de error y el búfer de entrada
			cin.clear();
			while (cin.get() != '\n'); // Limpia el búfer de entrada
		}
	} while(opcion != 5 && !salirGestor); // Repetir el bucle hasta que el inicio de sesión sea exitoso o el usuario elija salir
}

void Menu_Agregar(){
	system("cls");
	system("Color 02");
	int opcion;

	do{
		cout << "\n\t*************************************" << endl;
		cout << "\t*   Desea agregar otro beneficio?   *" << endl;
		cout << "\t*************************************" << endl;
		cout << "\t   1. Si                           " << endl;
		cout << "\t   2. No, ir al menu principal     " << endl;
		cout << "\n\t  Elija una opcion: ";

		if(cin >> opcion){
			while (cin.get() != '\n');
			if(opcion == 1){
				Agregar_beneficios();
			} else{
				Menu();
			}
		} else {
			cin.clear();
			while (cin.get() != '\n'); 
		}
	} while(opcion != 2);
}

void Menu_Modificar(){
	system("cls");
	system("Color 02");
	int opcion;

	do{
		cout << "\n\t***************************************************" << endl;
		cout << "\t*   Desea modificar el costo de otro beneficio?   *" << endl;
		cout << "\t***************************************************" << endl;
		cout << "\t    1. Si                             " << endl;
		cout << "\t    2. No, ir al menu principal       " << endl;
		cout << "\n\t  Elija una opcion: ";

		if(cin >> opcion){
			while (cin.get() != '\n');
			if(opcion == 1){
				Modificar_beneficios();
			} else{
				Menu();
			} 
		} else {
			cin.clear();
			while (cin.get() != '\n'); 
		}
	} while(opcion != 2);
}

void Menu_Eliminar(){
	system("cls");
	system("Color 02");
	int opcion;

	do{
		cout << "\n\t**************************************" << endl;
		cout << "\t*   Desea eliminar otro beneficio?   *" << endl;
		cout << "\t**************************************" << endl;
		cout << "\t   1. Si                            " << endl;
		cout << "\t   2. No, ir al menu principal      " << endl;
		cout << "\n\t  Elija una opcion: ";
		
		if(cin >> opcion){
			while (cin.get() != '\n');
			if(opcion == 1){
				Eliminar_beneficios();
			} else{
				Menu();
			}
		} else {
			cin.clear();
			while (cin.get() != '\n'); 
		}
	} while(opcion != 2);
}

void Menu_Listar(){
	system("cls");
	system("Color 02");
	int opcion;

	do{
		cout << "\n\t***********************************************" << endl;
		cout << "\t*   Desea continuar utilizando el programa?   *" << endl;
		cout << "\t***********************************************" << endl;
		cout << "\t    1. ir al menu" << endl;
		cout << "\t    2. Agregar beneficio" << endl;
		cout << "\t    3. Modificar el costo de un beneficio" << endl;
		cout << "\t    4. Eliminar beneficio" << endl;
		cout << "\t    5. No, salir" << endl;
		cout << "\n\t  Elija una opcion: ";

		if(cin >> opcion){
			while (cin.get() != '\n');
			if(opcion == 1){
				Menu();
			} else if(opcion == 2){
				Agregar_beneficios();
			} else if(opcion == 3){
				Modificar_beneficios();
			} else if(opcion == 4){
				Eliminar_beneficios();
			} else if(opcion == 5){
				Terminar();
			} else {
				cout << "\n\tOpcion invalida" << endl;
				system("pause");
			}
		} else {
			cin.clear();
			while (cin.get() != '\n'); 
		}
	} while(opcion != 5 && !salirGestor);
}
/*------------------------------------------------------------------------*/

/*---------------------------------Funciones que agregan beneficios---------------------------------*/
//La funcion agregar beneficio le pide al usuario que ingrese los datos relacionados al beneficio y luego llama a la funcion verificarBeneficio
//para que lea el archivo en busca de un beneficio que sea exactamente igual al ingresado por el usuario y en caso de no existir
//escribe los datos del beneficio en el archivo fisico, de lo contrario no lo hace

int verificarBeneficio(const char* beneficioBuscado){
	system("Color 02");
	FILE* archivo = fopen ("Beneficios.dat","rb");
	
	if (archivo != nullptr) {
        Beneficios beneficio;
        bool archivoVacio = true;
        while (fread(&beneficio, sizeof(Beneficios), 1, archivo) == 1) {
            archivoVacio = false;
            if (compMayMin(beneficio.nombre, beneficioBuscado)) {
                fclose(archivo);
                return 1;
            }
        }
        if(archivoVacio){
            fclose(archivo);
            return 0;
        }
        fclose(archivo);
    }
    return 0;
}

void Agregar_beneficios(){
	system("cls");
	system("Color 02");
    Beneficios beneficio;

	cout << "\n\t******************************" << endl;
	cout << "\t*     Agregar Beneficios     *" << endl;
	cout << "\t******************************" << endl;
	
	cout << "\n\tIngrese el nombre del beneficio: ";
	cin.getline(beneficio.nombre,20);
	cout << "\n\tIngrese el costo del beneficio: ";
	cin >> beneficio.costo;

	if(verificarBeneficio(beneficio.nombre)){
		cout << "\n\tEl beneficio ya existe! Presione cualquier boton para continuar" << endl;
		system("pause");
		cin.get();// Espera a que el usuario presione Enter
	} else {
		FILE* archivoEscribir = fopen("Beneficios.dat","ab");
		if(archivoEscribir != nullptr){
			fwrite(&beneficio, sizeof(Beneficios), 1, archivoEscribir);
			fclose(archivoEscribir);
			cout << "\n\tBeneficio ingresado correctamente!" << endl;
			system("pause");
		} else {
			cout << "\n\tNo se pudo cargar el archivo" << endl;
			system("pause");
		}
	}
	Menu_Agregar();
}
/*--------------------------------------------------------------------------------------------------*/

/*---------------------------------Funcion que muestra la lista de beneficios---------------------------------*/
//La funcion abre el archivo en modo lectura y lee el archivo e imprime por pantalla cada uno en orden en forma de lista

void Listar_beneficios(){
	system("cls"); 
	system("Color 02");
	Beneficios beneficio;
	FILE* archivoMostrar = fopen("Beneficios.dat","rb");

	if(archivoMostrar != nullptr){
		cout << "\n\t---------------------------------------" << endl;
		cout << "\t|       Beneficio       |    Costo    |" << endl;
		while(fread(&beneficio, sizeof(Beneficios),1,archivoMostrar) == 1){
			cout << "\t|" << left << setw(20) << beneficio.nombre << "         " << left << setw(5) << beneficio.costo << "   |" << endl;
			//los comandos left setw son comandos que ayudan con la organizacion de la informacion
		}
		fclose(archivoMostrar);
	} else{
		cout << "\n\tEl archivo esta vacio o no se pudo abrir :_(" << endl;
	}
	system("pause");
	Menu_Listar();
}
/*------------------------------------------------------------------------------------------------------------*/

/*---------------------------------Funcion que modifica los beneficios---------------------------------*/
//La funcion utiliza el mismo algoritmo anterior para imprimir por pantalla la lista de beneficios
//para facilitar la eleccion de beneficios
//Se utiliza una variable Booleana para definir el momento en el que se encuentra el beneficio que se 
//quiere modificar, cuando se encuentra se le pide al usuario que ingrese un nuevo costo y se reemplaza
//el costo antiguo. En caso de no hayar el beneficio se le informa al usuario de su eleccion y el caso que corresponda

void Modificar_beneficios(){
	system("cls");
	system("Color 02");
	Beneficios beneficio;
	FILE* archivoMostrar = fopen("Beneficios.dat","rb");

	if(archivoMostrar !=nullptr){
		cout << "\n\t---------------------------------------" << endl;
		cout << "\t|       Beneficio       |    Costo    |" << endl;
		while(fread(&beneficio, sizeof(Beneficios),1,archivoMostrar) == 1){
			cout << "\t|" << left << setw(20) << beneficio.nombre << "         " << left << setw(5) << beneficio.costo << "   |" << endl;
		}
		fclose(archivoMostrar);
	} 

	cout << "\n\t*************************************************" << endl;
	cout << "\t*        Modificar costo de un beneficio        *" << endl;
	cout << "\t*************************************************" << endl;

	char nombre[20];
	FILE* archivo = fopen("Beneficios.dat","rb+");

	cout << "\n\tIndique el beneficio que desea modificar: ";
	cin.getline(nombre,20);

	if(archivo != nullptr){
		bool modificado = false;
		while(!modificado && fread(&beneficio,sizeof(Beneficios),1,archivo) == 1){
			if(compMayMin(beneficio.nombre,nombre)){
				int nuevoCosto;
				modificado = true;
			
				cout << "\n\tIngrese el nuevo costo del beneficio: ";
				cin >> nuevoCosto;
			
				beneficio.costo = nuevoCosto;

				fseek(archivo, -(long) sizeof(Beneficios), SEEK_CUR); //(long) es para evitar el overflow ocacionado por el uso de variables
				fwrite(&beneficio, sizeof(Beneficios), 1, archivo);
				
				cout << "\n\tSe ha modificado el beneficio con exito!" << endl;
				
				system("pause");
			}
		}
		if(!modificado) {
			cout << "\n\tNo se ha encontrado el beneficio: " << nombre << endl;
			system("pause");
		}
		fclose(archivo);
	} else{
		cout << "\n\tNo se ha podido abrir el archivo!" << endl;
		system("pause");
	}
	Menu_Modificar();
}
/*-----------------------------------------------------------------------------------------------------*/

/*---------------------------------Funcion que elimina los beneficios---------------------------------*/
//La funcion utiliza el mismo algoritmo anterior para imprimir por pantalla la lista de beneficios
//para facilitar la eleccion de beneficios
//La funcion crea un archivo temporal en memoria en el que escribe todos los beneficios menos el que desea borrar 
//el usuario, luego cierra el archivo original y lo vuelve a abrir en modo escritura para borrar el contenido
//lo reabre en modo escritura y pasa todos los datos del archivo temporal al archivo fisico

void Eliminar_beneficios() {
    system("cls");
    Beneficios beneficio;
    FILE* archivoMostrar = fopen("Beneficios.dat", "rb");

    if (archivoMostrar != NULL) {
        cout << "\n\t---------------------------------------" << endl;
        cout << "\t|       Beneficio       |    Costo    |" << endl;
        while (fread(&beneficio, sizeof(Beneficios), 1, archivoMostrar) == 1) {
            cout << "\t|" << left << setw(20) << beneficio.nombre << "         " << left << setw(5) << beneficio.costo << "   |" << endl;
        }
        fclose(archivoMostrar);
    }
    else {
        cout << "El archivo está vacío o no se pudo abrir :_(" << endl;
    }

    cout << "\n\t***************************************" << endl;
    cout << "\t*         Eliminar Beneficios         *" << endl;
    cout << "\t***************************************" << endl;

    char buscador[20];
    cout << "\n\tIngrese el beneficio que desea eliminar: ";
    cin.getline(buscador, 20);

    FILE* archivo = fopen("Beneficios.dat", "r+b");

    if (archivo != nullptr) {
        bool eliminado = false;

        // Creamos un archivo temporal en memoria
        FILE* archivoTemporal = tmpfile();

        while (fread(&beneficio, sizeof(Beneficios), 1, archivo) == 1) {
            if (!compMayMin(beneficio.nombre, buscador)) {
                // Si el nombre no coincide, escribimos el beneficio en el archivo temporal
                fwrite(&beneficio, sizeof(Beneficios), 1, archivoTemporal);
            }
            else {
                eliminado = true;
            }
        }

        // Cierra el archivo original
        fclose(archivo);

        if (eliminado) {
            // Abre el archivo original en modo escritura y elimina su contenido
            archivo = fopen("Beneficios.dat", "wb");
            fclose(archivo);

            // Reabre el archivo original y escribe los datos del archivo temporal en él
            archivo = fopen("Beneficios.dat", "r+b");
            fseek(archivoTemporal, 0, SEEK_SET);

            while (fread(&beneficio, sizeof(Beneficios), 1, archivoTemporal) == 1) {
                fwrite(&beneficio, sizeof(Beneficios), 1, archivo);
            }

            fclose(archivoTemporal);
            fclose(archivo);

            cout << "\tSe ha eliminado el beneficio :)" << endl;
        }
        else {
            cout << "\n\tNo se ha encontrado el beneficio: " << buscador << endl;
        }
    }
    else {
        cout << "\tNo se ha podido eliminar el beneficio: " << buscador << endl;
    }

    system("pause");
    Menu_Eliminar();
}
/*----------------------------------------------------------------------------------------------------*/

/*---------------------------------Funcion cerrar programa---------------------------------*/
void Terminar(){
	system("cls");
	
	cout << "\n\t***********************************************************************" << endl;
	cout << "\t*   Gracias por utilizar el programa, regresando al menu principal!   *" << endl;
	cout << "\t***********************************************************************" << endl;

	system("pause");
	salirGestor = true;
    return; //regresa al main.cpp
}
/*-----------------------------------------------------------------------------------------*/