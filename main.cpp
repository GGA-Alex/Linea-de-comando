#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <limits>
#include <dirent.h>

using namespace std;

void copiar(string nombreArchivo, string estado);
void eliminar(string nombreArchivo, string codigoPostal);
void renombrar(string nombreArchivo, string nuevoNombre);
void combinar(string nombreArchivo1, string nombreArchivo2);
void Agrupar(int num, vector<string> archivos);

string nombreEstado(string estado); // Acomoda el nombre del estado cuando tenga espacios
vector<string> lineasArchivo(string nombreArchivo); // Obtiene el contenido del archivo JSON
vector<string> lineasEliminarArchivo(string nombreArchivo,string cp); // Elimina del archivo los estados que tenga el CP buscado


int main()
{
    string comando_input, comando;
    cout << "------------------------------------------" << endl;
    cout << endl;
    do{
        cin >> comando_input;

        stringstream input_stringstream(comando_input);
        getline(input_stringstream, comando, ';');

        if(comando == "copiar"){
            string nombreArchivo,estado;
            getline(input_stringstream, nombreArchivo, ';');
            getline(input_stringstream, estado, ';');
            nombreArchivo = nombreEstado(nombreArchivo);
            estado = nombreEstado(estado);
            copiar(nombreArchivo, estado);
        }else if(comando == "eliminar"){
            string nombreArchivo,codigoPostal;
            getline(input_stringstream, nombreArchivo, ';');
            getline(input_stringstream, codigoPostal, ';');
            nombreArchivo = nombreEstado(nombreArchivo);
            eliminar(nombreArchivo,codigoPostal);
        }else if(comando == "renombrar"){
            string nombreArchivo,nuevoNombre;
            getline(input_stringstream, nombreArchivo, ';');
            getline(input_stringstream, nuevoNombre, ';');
            nombreArchivo = nombreEstado(nombreArchivo);
            renombrar(nombreArchivo, nuevoNombre);
        }else if(comando == "combinar"){
            string nombreArchivo1,nombreArchivo2;
            getline(input_stringstream, nombreArchivo1, ';');
            getline(input_stringstream, nombreArchivo2, ';');
            nombreArchivo1 = nombreEstado(nombreArchivo1);
            nombreArchivo2 = nombreEstado(nombreArchivo2);
            combinar(nombreArchivo1, nombreArchivo2);
        }else if(comando == "agrupar"){
            string estado;
            vector<string> estados;
            while(getline(input_stringstream, estado, ';')){
                estado = nombreEstado(estado);
                estados.push_back(estado);
            }
            if(estados.size() <= 5){
                Agrupar(0,estados);
            }else{
                cout << "\nERROR SOLO SE PERMITE AGRUPAR HASTA 5 ARCHIVOS" << endl;
            }

        }else {
            cout << "\nCOMANDO NO RECONOCIDO" << endl;
        }
        cout << "------------------------------------------" << endl;
        cout << endl;
    }while(comando_input != "0");

    return 0;
}


void copiar(string nombreArchivo, string estado){
    fstream archivo("Estados/" + nombreArchivo + ".json"); // Abrimos el archivo al que le vamos a insertar el contenido

    vector<string> lineasArchivo1 = lineasArchivo(nombreArchivo); // Obtenemos todas las lineas del archivo1
    vector<string> lineasArchivo2 = lineasArchivo(estado); // Obtenemos todas las lineas del archivo2

    // Guardamos todas las lineas del archivo1 primero y despues todas las lineas del archivo 2
    archivo << '{' << endl;
    for(int i = 0; i < lineasArchivo1.size()-4; i++){
        archivo << lineasArchivo1[i] << endl;
    }
    for(int i = 0; i < lineasArchivo2.size()-4; i++){
        archivo << lineasArchivo2[i] << endl;
    }
    archivo << '}' << endl;
    archivo.close();
}

void eliminar(string nombreArchivo, string codigoPostal){
    // Abrimos el archivo al que le vamos a eliminar los estados con el código postal
    fstream archivo("Estados/" + nombreArchivo + ".json");

    string codigoPostalEliminar = "\t" + codigoPostal + "{"; // Inicialiamos el codigo postal

    // Obtenemos todos los estados, menos los que sean del codigo postal que queremos eliminar
    vector<string> lineasArchivo1 = lineasEliminarArchivo(nombreArchivo,codigoPostalEliminar);

    // Guardamos en el archivo las lineas actualizadas
    archivo << '{' << endl;
    for(int i = 0; i < lineasArchivo1.size()-4; i++){
        archivo << lineasArchivo1[i] << endl;
    }
    archivo << '}' << endl;
    archivo.close();
}

void renombrar(string nombreArchivo, string nuevoNombre){
    string ruta = "Estados/" + nombreArchivo + ".json"; // Obtenemos la ruta del archivo original
    string ruta2 = "Estados/" + nuevoNombre + ".json"; // Creamos la ruta del archivo con el cambio de nombre

    // Las convertimos a tipo char las dos rutas
    char const* ptr1 = ruta.c_str();
    char const* ptr2 = ruta2.c_str();

    // Renombramos el archivo
    rename(ptr1,ptr2);
}

void combinar(string nombreArchivo1, string nombreArchivo2){
    ofstream archivo("Estados/" + nombreArchivo1 + "_" + nombreArchivo2 +".json"); // Creamos el archivo
    vector<string> lineaArchivo1 = lineasArchivo(nombreArchivo1); // Obtenemos todas las lineas del primer archivo
    vector<string> lineaArchivo2 = lineasArchivo(nombreArchivo2); // Obtenemos todas las lineas del segundo archivo

    // Escribimos los datos actualizados 1 y 1
    archivo << '{' << endl;
    for(int i = 0; i < lineaArchivo1.size() + lineaArchivo2.size(); i = i +4){
        if(i < lineaArchivo1.size()-4){
            archivo << lineaArchivo1[i] << endl;
            archivo << lineaArchivo1[i+1] << endl;
            archivo << lineaArchivo1[i+2] << endl;
            archivo << lineaArchivo1[i+3] << endl;
        }
        if(i < lineaArchivo2.size()-4){
            archivo << lineaArchivo2[i] << endl;
            archivo << lineaArchivo2[i+1] << endl;
            archivo << lineaArchivo2[i+2] << endl;
            archivo << lineaArchivo2[i+3] << endl;
        }
    }
    archivo << '}' << endl;
    archivo.close();
}

void Agrupar(int num,vector<string> archivos){
    string id, ruta;
    char const* rutaCarpeta;
    DIR * directorio;

    if(num == 0){
        id = "Agrupacion";
    }else{
        id = "Agrupacion" + to_string(num);
    }

    ruta = "Estados/" + id;
    rutaCarpeta = ruta.c_str();

    if(directorio = opendir(rutaCarpeta)){
        closedir(directorio);
        Agrupar(num+1, archivos); // Volvemos a llamar a la función ya que existe una carpeta con el mismo nombre
    }else{
        mkdir(rutaCarpeta); // Creamos las carpeta

        string nombreArchivo;
        char const* rutaDestinoArchivo;
        char const* nombreArchivoChar;

        // Movemos los archivos seleccionados dentro de la carpeta creada
        for(int i = 0; i < archivos.size(); i++){
            nombreArchivo = "Estados/" + archivos[i] + ".json";
            ruta = "Estados/" + id + "/" + archivos[i] + ".json";
            rutaDestinoArchivo = ruta.c_str();
            nombreArchivoChar = nombreArchivo.c_str();

            rename(nombreArchivoChar,rutaDestinoArchivo);
        }
    }
}

vector<string> lineasArchivo(string nombreArchivo){
    fstream archivo("Estados/" + nombreArchivo + ".json"); // Abrimos el archivo
    vector<string> lineasArchivo;
    string linea;
    // Obtenemos todas las lineas
    getline(archivo, linea);
    while (getline(archivo, linea))
    {
        lineasArchivo.push_back(linea);
        getline(archivo, linea);
        lineasArchivo.push_back(linea);
        getline(archivo, linea);
        lineasArchivo.push_back(linea);
        getline(archivo, linea);
        lineasArchivo.push_back(linea);
    }
    return lineasArchivo;
}

vector<string> lineasEliminarArchivo(string nombreArchivo,string cp){
    fstream archivo("Estados/" + nombreArchivo + ".json"); // Abrimos el archivo
    vector<string> lineasArchivo,lineasEliminar;
    string linea;
    // Obtenemos todas las lineas menos los estados que tengan el codigo postal buscado
    getline(archivo, linea);
    while (getline(archivo, linea))
    {
        if(linea != cp){
            lineasArchivo.push_back(linea);
            getline(archivo, linea);
            lineasArchivo.push_back(linea);
            getline(archivo, linea);
            lineasArchivo.push_back(linea);
            getline(archivo, linea);
            lineasArchivo.push_back(linea);
        }else{
            getline(archivo, linea);
            getline(archivo, linea);
            getline(archivo, linea);
        }
    }
    return lineasArchivo;
}

string nombreEstado(string estado){
    if (estado == "BajaCaliforniaSur")
        return "Baja California Sur";
    if (estado == "BajaCalifornia")
        return "Baja California";
    if (estado == "CiudaddeMexico")
        return "Ciudad de Mexico";
    if (estado == "CoahuiladeZaragoza")
        return "Coahuila de Zaragoza";
    if (estado == "MichoacandeOcampo")
        return "Michoacan de Ocampo";
    if (estado == "NuevoLeon")
        return "Nuevo Leon";
    if (estado == "QuintanaRoo")
        return "Quintana Roo";
    if (estado == "SanLuisPotosi")
        return "San Luis Potosi";
    if (estado == "VeracruzdeIgnaciodelaLlave")
        return "Veracruz de Ignacio de la Llave";
    return estado;
}
