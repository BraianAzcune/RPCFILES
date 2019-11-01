
#include "rpc/server.h"
#include <string>

//prueba de envio de archivos.
#include <fstream>
#include <iostream>
#include <sstream> //std::stringstream

//prueba para dormir durante un tiempo un hilo dentro de mutex.
#include <chrono>
#include <thread>
#include <mutex>
std::mutex mtx; // mutex for critical section

using namespace std;


string entregar_archivo_generico(string noLouso){

    cout<<"ID thread: "<<pthread_self();

    //etrar mutex.
    mtx.lock();
    std::this_thread::sleep_for(std::chrono::milliseconds(6000));

    cout<<"Se pidio el archivo "<<noLouso<<" se ignora\n";

    ifstream inFile;
    inFile.open("prueba.txt"); //open the input file

    stringstream strStream;
    strStream << inFile.rdbuf(); //read the file
    string str = strStream.str(); //str holds the content of the file

    //cout << str << "\n"; //you can do anything with the string!!!

    inFile.close();

    mtx.unlock();
    //salir mutex

    return str;
}


int main() {
  rpc::server srv(8080);

  srv.bind("echo", [](string const& s) {
    return string("> ") + s;
  });

  srv.bind("adquirir_archivo",&entregar_archivo_generico);


  constexpr size_t thread_count = 2;
  srv.async_run(thread_count);
  cin.ignore();

  return 0;
}
