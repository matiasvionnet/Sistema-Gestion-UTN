/*-------------------------Listado de librerias-------------------------*/
#include <iostream>
#include <iomanip> //ayuda a organizar la informacion impresa en pantalla
#include <windows.h> //Permite cambiar de color el texto y la terminal
#include "Beneficios Final.h"
#include "Registro v2.h"
#include "Consumidor.h"

using namespace std;
/*----------------------------------------------------------------------*/

/*-------------------------Main-------------------------*/
int main() {
    int opcion;
    system("cls");
    system("color 02");
    do {
        cout << "\n\t******************************************" << endl;
		cout << "\t*                  Menu                  *" << endl;
		cout << "\t******************************************" << endl;
        cout << "\n\t1. Gestor de beneficios" << endl;
        cout << "\t2. Registro" << endl;
        cout << "\t3. Consumidor de beneficios" << endl;
        cout << "\t4. Salir" << endl;
        cout << "\tElija una opcion: ";
        cin >> opcion;

        switch(opcion) {
            case 1: ejecutar_gestor(); break;
            case 2: ejecutar_registro(); break;
            case 3: ejecutar_consumidor(); break;
            case 4: cout << "Hasta la proxima!" << endl; break;
            default: cout << "Opcion invalida" << endl;
        }
    } while(opcion != 4);
    return 0;
}
/*------------------------------------------------------*/