#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>

using namespace std;

/*
===========================================================
    ESTRUCTURA PRINCIPAL
    Representa un equipo del torneo
===========================================================
*/
struct Equipo {
    string nombre;
    int partidosJugados;
    int partidosGanados;
    int partidosEmpatados;
    int partidosPerdidos;
    int puntos;
};

const int MAX_EQUIPOS = 20;
int totalEquipos = 16;

/*
===========================================================
    FUNCION AUXILIAR: CONVERTIR TEXTO A MINUSCULAS
    Permite realizar busquedas sin importar mayusculas
    o minusculas ingresadas por el usuario
===========================================================
*/
string convertirMinusculas(string texto) {
    for (char& letra : texto) {
        letra = tolower(letra);
    }
    return texto;
}

/*
===========================================================
    FUNCION AUXILIAR: VALIDAR NUMEROS NEGATIVOS
    Verifica que los datos numericos del equipo sean validos
===========================================================
*/
bool datosNoNegativos(Equipo equipo) {
    return equipo.partidosJugados >= 0 &&
        equipo.partidosGanados >= 0 &&
        equipo.partidosEmpatados >= 0 &&
        equipo.partidosPerdidos >= 0 &&
        equipo.puntos >= 0;
}

/*
===========================================================
    FUNCION AUXILIAR: VERIFICAR SI UN EQUIPO EXISTE
    Evita registrar equipos repetidos dentro del torneo
===========================================================
*/
bool equipoExiste(Equipo equipos[], string nombre) {
    string nombreNuevo = convertirMinusculas(nombre);

    for (int i = 0; i < totalEquipos; i++) {
        if (convertirMinusculas(equipos[i].nombre) == nombreNuevo) {
            return true;
        }
    }

    return false;
}

/*
===========================================================
    RECONSTRUCCION DE DATOS INICIALES
    Calcula los partidos empatados y perdidos, debido a que
    inicialmente estos datos aparecen en cero por un error
    de lectura
===========================================================
*/
void reconstruirDatos(Equipo equipos[]) {
    for (int i = 0; i < totalEquipos; i++) {

        int empates = equipos[i].puntos - (3 * equipos[i].partidosGanados);

        if (empates < 0) {
            empates = 0;
        }

        int perdidos = equipos[i].partidosJugados -
            equipos[i].partidosGanados -
            empates;

        if (perdidos < 0) {
            perdidos = 0;
        }

        equipos[i].partidosEmpatados = empates;
        equipos[i].partidosPerdidos = perdidos;
    }
}

/*
===========================================================
    MOSTRAR TABLA DE POSICIONES
    Presenta toda la informacion de los equipos en formato
    tabulado y organizado
===========================================================
*/
void mostrarTabla(Equipo equipos[]) {
    cout << "\n====================== TABLA DE POSICIONES ======================\n";

    cout << left << setw(28) << "Equipo"
        << setw(6) << "PJ"
        << setw(6) << "PG"
        << setw(6) << "PE"
        << setw(6) << "PP"
        << setw(6) << "Pts" << endl;

    cout << "-----------------------------------------------------------------\n";

    for (int i = 0; i < totalEquipos; i++) {
        cout << left << setw(28) << equipos[i].nombre
            << setw(6) << equipos[i].partidosJugados
            << setw(6) << equipos[i].partidosGanados
            << setw(6) << equipos[i].partidosEmpatados
            << setw(6) << equipos[i].partidosPerdidos
            << setw(6) << equipos[i].puntos << endl;
    }
}

/*
===========================================================
    ORDENAMIENTO Y VISUALIZACION DE EQUIPOS
    Ordena una copia de los equipos para no modificar el
    arreglo original
===========================================================
*/
void ordenarYMostrar(Equipo equipos[], bool descendente) {
    Equipo copia[MAX_EQUIPOS];

    for (int i = 0; i < totalEquipos; i++) {
        copia[i] = equipos[i];
    }

    for (int i = 0; i < totalEquipos - 1; i++) {
        for (int j = 0; j < totalEquipos - i - 1; j++) {

            bool condicionOrdenamiento =
                (descendente && copia[j].puntos < copia[j + 1].puntos) ||
                (!descendente && copia[j].puntos > copia[j + 1].puntos);

            if (condicionOrdenamiento) {
                swap(copia[j], copia[j + 1]);
            }
        }
    }

    mostrarTabla(copia);
}

/*
===========================================================
    EQUIPOS CON MAS PARTIDOS EMPATADOS
    Identifica el mayor numero de empates y muestra todos
    los equipos que cumplen con esa condicion
===========================================================
*/
void mostrarEquiposConMasEmpates(Equipo equipos[]) {
    int mayorEmpates = equipos[0].partidosEmpatados;

    for (int i = 1; i < totalEquipos; i++) {
        if (equipos[i].partidosEmpatados > mayorEmpates) {
            mayorEmpates = equipos[i].partidosEmpatados;
        }
    }

    cout << "\nEquipos con mas partidos empatados (" << mayorEmpates << "):\n";

    for (int i = 0; i < totalEquipos; i++) {
        if (equipos[i].partidosEmpatados == mayorEmpates) {
            cout << "- " << equipos[i].nombre << endl;
        }
    }
}

/*
===========================================================
    BUSQUEDA DE EQUIPO
    Permite encontrar toda la informacion de un equipo
    especifico ingresado por el usuario
===========================================================
*/
void buscarEquipo(Equipo equipos[]) {
    string nombreBuscado;

    cout << "\nIngrese el nombre del equipo que desea buscar: ";
    cin.ignore();
    getline(cin, nombreBuscado);

    string busqueda = convertirMinusculas(nombreBuscado);

    for (int i = 0; i < totalEquipos; i++) {
        if (convertirMinusculas(equipos[i].nombre) == busqueda) {

            cout << "\nEquipo encontrado:\n";
            cout << "Nombre: " << equipos[i].nombre << endl;
            cout << "Partidos jugados: " << equipos[i].partidosJugados << endl;
            cout << "Partidos ganados: " << equipos[i].partidosGanados << endl;
            cout << "Partidos empatados: " << equipos[i].partidosEmpatados << endl;
            cout << "Partidos perdidos: " << equipos[i].partidosPerdidos << endl;
            cout << "Puntos: " << equipos[i].puntos << endl;

            return;
        }
    }

    cout << "\nNo se encontro ningun equipo con ese nombre.\n";
}

/*
===========================================================
    VALIDACION DE CONSISTENCIA DE DATOS
    Verifica que los puntos y partidos jugados cumplan con
    las reglas matematicas del torneo
===========================================================
*/
bool validarEquipo(Equipo equipo) {
    if (!datosNoNegativos(equipo)) {
        cout << "\nAdvertencia: no se permiten valores negativos.\n";
        return false;
    }

    int puntosCalculados = (3 * equipo.partidosGanados) +
        equipo.partidosEmpatados;

    int partidosCalculados = equipo.partidosGanados +
        equipo.partidosEmpatados +
        equipo.partidosPerdidos;

    if (equipo.puntos != puntosCalculados) {
        cout << "\nAdvertencia: los puntos no coinciden con la formula.\n";
        cout << "Puntos esperados: " << puntosCalculados << endl;
        return false;
    }

    if (equipo.partidosJugados != partidosCalculados) {
        cout << "\nAdvertencia: los partidos jugados no coinciden.\n";
        cout << "Partidos esperados: " << partidosCalculados << endl;
        return false;
    }

    return true;
}

/*
===========================================================
    AGREGAR NUEVO EQUIPO
    Permite registrar un equipo adicional, verificando que
    sus datos sean consistentes y que no se supere el limite
    de cuatro equipos nuevos
===========================================================
*/
void agregarEquipo(Equipo equipos[]) {
    if (totalEquipos >= MAX_EQUIPOS) {
        cout << "\nNo se pueden agregar mas equipos. Limite maximo alcanzado.\n";
        return;
    }

    Equipo nuevoEquipo;

    cout << "\nIngrese el nombre del nuevo equipo: ";
    cin.ignore();
    getline(cin, nuevoEquipo.nombre);

    if (equipoExiste(equipos, nuevoEquipo.nombre)) {
        cout << "\nAdvertencia: este equipo ya se encuentra registrado.\n";
        return;
    }

    cout << "Partidos jugados: ";
    cin >> nuevoEquipo.partidosJugados;

    cout << "Partidos ganados: ";
    cin >> nuevoEquipo.partidosGanados;

    cout << "Partidos empatados: ";
    cin >> nuevoEquipo.partidosEmpatados;

    cout << "Partidos perdidos: ";
    cin >> nuevoEquipo.partidosPerdidos;

    cout << "Puntos: ";
    cin >> nuevoEquipo.puntos;

    if (validarEquipo(nuevoEquipo)) {
        equipos[totalEquipos] = nuevoEquipo;
        totalEquipos++;

        cout << "\nEquipo agregado correctamente.\n";
    }
    else {
        cout << "\nEl equipo no fue guardado porque los datos son inconsistentes.\n";
    }
}

/*
===========================================================
    MENU PRINCIPAL
    Presenta las opciones disponibles y llama a la funcion
    correspondiente segun la eleccion del usuario
===========================================================
*/
void menu(Equipo equipos[]) {
    int opcion;

    do {
        cout << "\n================ MENU ================\n";
        cout << "1. Mostrar tabla de posiciones de mayor a menor\n";
        cout << "2. Mostrar tabla de posiciones de menor a mayor\n";
        cout << "3. Mostrar equipos con mas partidos empatados\n";
        cout << "4. Buscar informacion de un equipo especifico\n";
        cout << "5. Agregar nuevo equipo\n";
        cout << "0. Salir\n";
        cout << "Seleccione una opcion: ";

        cin >> opcion;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "\nEntrada invalida. Debe ingresar un numero.\n";
            continue;
        }

        switch (opcion) {
        case 1:
            ordenarYMostrar(equipos, true);
            break;

        case 2:
            ordenarYMostrar(equipos, false);
            break;

        case 3:
            mostrarEquiposConMasEmpates(equipos);
            break;

        case 4:
            buscarEquipo(equipos);
            break;

        case 5:
            agregarEquipo(equipos);
            break;

        case 0:
            cout << "\nPrograma finalizado correctamente.\n";
            break;

        default:
            cout << "\nOpcion no valida. Intente nuevamente.\n";
            break;
        }

    } while (opcion != 0);
}

/*
===========================================================
    FUNCION PRINCIPAL
    Inicializa los datos, reconstruye la informacion faltante
    y ejecuta el menu del programa
===========================================================
*/
int main() {
    Equipo equipos[MAX_EQUIPOS] = {
        {"Andromeda FC",12,4,0,0,13},
        {"Vulcano Academia",11,2,0,0,10},
        {"Orion Confederacion",11,4,0,0,14},
        {"Sirio Estrellas",10,6,0,0,20},
        {"Caronte Titanes",11,1,0,0,6},
        {"Quiron Cometas",10,5,0,0,17},
        {"Pegaso Pulsares",11,7,0,0,24},
        {"Osos Cosmicos",11,5,0,0,18},
        {"Via Lactea Nomadas",11,6,0,0,20},
        {"Leonidas FC",11,5,0,0,16},
        {"Cangrejo Fortaleza",11,4,0,0,16},
        {"Cefeo Cumulo",11,3,0,0,14},
        {"Atletico Interestelar",11,4,0,0,16},
        {"Deportivo Galactico",11,2,0,0,8},
        {"Estrella Estelar",11,5,0,0,17},
        {"Inter Galaxia",10,2,0,0,10}
    };

    reconstruirDatos(equipos);
    menu(equipos);

    return 0;
}