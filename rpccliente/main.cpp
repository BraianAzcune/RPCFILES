#include "rpc/client.h"
#include <iostream>
#include <string>
using namespace std;




int main() {

    bool ejecutar=true;

    rpc::client c("127.0.0.1", 8080);
    int opcion=0;
    string nombre_archivo;
    while(ejecutar){

        cout<<"eliga la opcion que quiere tomar\n";
        cout<<"1-Listado de archivos ocupados y quien lo posee\n";
        cout<<"2-Adquirir un archivo\n";
        cout<<"3-Liberar archivo\n";
        cout<<"9-salir\n";
        cin>>opcion;

        switch(opcion){
            case 1 ... 3:
                cout<<"Ingrese nombre del archivo:\n";
                cin>>nombre_archivo;
        }

        switch(opcion){

            case 1:
                cout<<"no implementado";
                break;
            case 2:
                {//Esto es para decirle al codigo que la variable archivo, se limita a este alcance.
                auto archivo= c.call("adquirir_archivo",nombre_archivo).as<string>();
                cout<<"Recibimos=\n";
                cout<<archivo<<"\n";
                }
                break;
            case 3:
                cout<<"no implementado";
                break;
            case 9:
                //hay que llamar al servidor, para liberar cualquier archivo que tengamos.
                ejecutar=false;
                break;
            default:
                cout<<"Opcion invalida";
                break;
        }

    }




    //string rta;
    //rta = c.call("echo","Hola").as<string>();

    //printf("llego: %s",rta.c_str());

    return 0;
}
