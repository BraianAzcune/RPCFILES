
#include "rpc/server.h"
#include <string>

//prueba de envio de archivos.
#include <fstream>
#include <iostream>
#include <sstream> //std::stringstream


#include <unistd.h>

using namespace std;


string entregar_archivo_generico(string noLouso){

    cout<<"ID thread: "<<pthread_self();

    usleep(500000);

    cout<<"Se pidio el archivo "<<noLouso<<" se ignora\n";

    ifstream inFile;
    inFile.open("prueba.txt"); //open the input file

    stringstream strStream;
    strStream << inFile.rdbuf(); //read the file
    string str = strStream.str(); //str holds the content of the file

    cout << str << "\n"; //you can do anything with the string!!!

    inFile.close();
    return str;
}


int main() {
  rpc::server srv(8080);

  srv.bind("echo", [](string const& s) {
    return string("> ") + s;
  });

  srv.bind("adquirir_archivo",&entregar_archivo_generico);

  srv.run();
  return 0;
}
