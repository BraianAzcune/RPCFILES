/**
 * Project TP1EJ2SERVIDOR
 */



#include "ManejadorArchivos.h"

/**
 * ManejadorArchivos implementation
 *
 * se encargara del acceso al directorio, en caso de que no este en cache.
 */

/**
 * Devuelve un struct ARCHIVO.
 * si el archivo no se encontro, sera NULL.
 *
 * @param path
 * @return ARCHIVO
 */
ARCHIVO ManejadorArchivos::obtenerArchivo(string path)//CUALQUIER COSA QUE IMPOSIBILITE EL ENVIO, SE TRADUCIRA, ENVIAR UN FICHERO PREDEFINDO, CON EL ERROR.
{
    struct ARCHIVO file= this->me->consultaArchivo(path);

    if(file.puntero==NULL){//El archivo no existe en cache
        cout<<"El archivo no esta en cache, Buscando en disco\n";

        Utilidades::RESPUESTA respuesta= Utilidades::esValido(path);

        if(respuesta==Utilidades::RESPUESTA::NO_VALIDO){//EL ARCHIVO NO EXISTE, O ES UN ARCHIVO QUE NO SE PUEDE ENVIAR.
            cout<<"Aqui hay que responder que no existe el archivo y cortar conexion";
        }else if(respuesta==Utilidades::RESPUESTA::ENCONTRADO_MENOR512M){//EL ARCHIVO EXISTE Y ES MENOR A 512 MB
            //cout<<"Aqui hay que traer el archivo a ram y luego enviarlo";
            file= this->cargarArchivo(path);//cargamos el archivo a ram
            this->me->agregarArchivo(file,path);//lo agregamos a la cache



        }else{//ES MAYOR A 512 MB
            cout<<"ARCHIVO MAYOR A 512MB--manejadorArchivo";
        }

    }else{//EL ARCHIVO EXISTE EN CACHE
       cout<<"el archivo esta en cache.";

    }

    return file;
}

/**
 * Constructor, crea ManejadorCache
 */
ManejadorArchivos::ManejadorArchivos()
{
    cout<<"Constructor manejador archivos\n";
    this->me= new ManejadorCache();
}

/**
 * Destructor
 */
ManejadorArchivos::~ManejadorArchivos()
{
    cout<<"Eliminamos Manejador Cache\n";
    delete this->me;
}



/**
 * carga el archivo en ram
 * @param path
 * @return ARCHIVO
 */
ARCHIVO ManejadorArchivos::cargarArchivo(string path)
{
    struct ARCHIVO archivo;

    archivo.size=Utilidades::obtenerSize(path);//obtenemos cuanto pesa el archivo en bytes

    ifstream manejadorArchivo(path.c_str(),ifstream::binary);

    if(manejadorArchivo.is_open()){

        this->me->mapaDeMutex[path].lock();

        archivo.idSession=rpc::this_session().id();

        archivo.puntero= new char[archivo.size];//pedimos de forma dinamica la cantidad de memoria, justa para almacenar el archivo.

        manejadorArchivo.read(archivo.puntero,archivo.size);//Leemos de a bloques, hasta llenar el tamaño




        //NOTIFICACION DE ERRORES
        if(manejadorArchivo.eof()){
            perror("Se alcanzo el final del archivo antes de que se llenera el buffer");
            delete archivo.puntero;
            archivo.puntero=NULL;
            archivo.size=0;
        }
        if(manejadorArchivo.fail()){
            perror("no se pudo leer la cantidad asignada en el buffer");
            if(manejadorArchivo.bad()){
                perror("La transmicion fallo, errores de bits.");
            }
            delete archivo.puntero;
            archivo.puntero=NULL;
            archivo.size=0;
        }
        //FIN NOTIFICAR ERRORES

        manejadorArchivo.close();//cerramos el archivo.

    }else{
        perror("No se puede abrir el archivo");
        archivo.puntero=NULL;
        archivo.size=0;
    }

    return archivo;
}
