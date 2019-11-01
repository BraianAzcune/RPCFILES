//para hacer funcionar al servidor
#include "rpc/server.h"
#include <string>


//para manejadorArchivo y cache.
#include "ManejadoresArchivoCache/ManejadorArchivos.h"


//prueba de envio de archivos.
#include <fstream>
#include <iostream>
#include <sstream> //std::stringstream

//prueba para dormir durante un tiempo un hilo dentro de mutex.
    //#include <chrono>
    //#include <thread>
#include <mutex>


using namespace std;

//MANEJADOR ARCHIVOS (es un puntero para que pueda ser accedido por cualquier hilo)
ManejadorArchivos* manejadorArchivos;




string adquirir_archivo(string path){



    cout<<"ID thread: "<<pthread_self();
    ARCHIVO archivoRespuesta=manejadorArchivos->obtenerArchivo(path);

    return archivoRespuesta.puntero;
}

void liberar_archivo(string nombreArchivo){

    manejadorArchivos->me->mapaDeMutex[nombreArchivo].unlock();
}


int main() {



    //INICIALIZAMOS MANEJADORARCHVIO.
    manejadorArchivos= new ManejadorArchivos();

    rpc::server srv(8080);


    srv.bind("adquirir_archivo",&adquirir_archivo);

    srv.bind("liberar_archivo",&liberar_archivo);

    constexpr size_t thread_count = 8;
    srv.async_run(thread_count);
    cin.ignore();

    //llamamos al destructor para borrar todos los archivos.
    manejadorArchivos->~ManejadorArchivos();
    return 0;
}



//CODIGO DE PRUEBAS


//mutex mtx; // mutex for critical section
//string entregar_archivo_generico(string noLouso){
//
//    cout<<"ID thread: "<<pthread_self();
//
//    //etrar mutex.
//    mtx.lock();
//    //std::this_thread::sleep_for(std::chrono::milliseconds(6000));
//
//    cout<<"Se pidio el archivo "<<noLouso<<" se ignora\n";
//
//    ifstream inFile;
//    inFile.open("prueba.txt"); //open the input file
//
//    stringstream strStream;
//    strStream << inFile.rdbuf(); //read the file
//    string str = strStream.str(); //str holds the content of the file
//
//    //cout << str << "\n"; //you can do anything with the string!!!
//
//    inFile.close();
//
//    mtx.unlock();
//    //salir mutex
//
//    return str;
//}
