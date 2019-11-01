/**
 * Project TP1EJ2SERVIDOR
 */


#include "ManejadorCache.h"

/**
 * ManejadorCache implementation
 *
 * Esta cache hace uso de std::map
 * mantiene una cola, con las claves mas usadas.
 * cuando se acabe la memoria, comenzara a borrar las menos usadas de la lista. hasta que pueda guardar el nuevo dato.
 */


/**
 * retorna el archivo si esta, si no esta sera null.
 * actualiza la cola poniendo el archivo al principio si es que existe
 *
 * @param direccionArchivo
 * @return ARCHIVO
 */
ARCHIVO ManejadorCache::consultaArchivo(string direccionArchivo) {
    //perror("\nSoy ManejadorCache, siempre retorno archivos nulos, no tengo implementado mi cache LRU\n");
    struct ARCHIVO file;
    file.puntero=NULL;
    file.size=0;

    auto itr=cache.find(direccionArchivo);
    if( itr == cache.end() ){
        //cout<<"no esta en la cache\n";
        //no ta en cache
    }
    else {
        file.puntero=itr->second.puntero;
        file.size=itr->second.size;
        cola.remove(direccionArchivo);
        cola.push_front(direccionArchivo);
    }




    return file;
}

/**
 * lo mismo que en consultarArchivo, hay que ver de que forma, se implementa en memoria ram un archivo.
 *
 * @param file
 */
void ManejadorCache::agregarArchivo(ARCHIVO file, string direccionArchivo) {
    //cout<<"Soy agregar archivo, actualmente no agrego nada.\n";
    if(this->maxSizeCache - file.size > 0){
       if(this->maxSizeCache - this->sizeCache - file.size > 0){
       //entra insertamos el archivo a cache , modificamos la cola LRU.
        cache.insert(std::pair<string,struct ARCHIVO>(direccionArchivo,file));
        cola.push_front(direccionArchivo);
        cout<<"Agrege  sin liberar espacio";
       }
       else{
         liberarEspacio(file.size);//ya se realizaron los pop_back necesarios en esta funcion
         cola.push_front(direccionArchivo);// Se lo ingresa en la cola y en el cache
         cache.insert(std::pair<string,struct ARCHIVO>(direccionArchivo,file));
         cout<<"Agrege liberando espacio\n";
       }
     }
     else
       perror("El archivo es demasiado grande para la cache");

    }





/**
 *Constructor
 **/
ManejadorCache::ManejadorCache() {
    cout<<"Constructor manejador cache\n";
   // map<string, struct ARCHIVO> cache = new map<string, struct ARCHIVO>();
    cache.clear(); //por las dudas
    this->sizeCache=0;

    this->maxSizeCache=Utilidades::MAX_SIZE512M;

}

/**
 * Destructor
 */
ManejadorCache::~ManejadorCache()
{
    cout<<"Se llama a librar espacio para liberar todo\n";
    this->liberarEspacio(this->maxSizeCache);

}


/**
 * eliminara espacio hasta cumplir con la cantidad de bytes que se necesitan guardar. Si este numero es mayor a lo que deberia guardar la cache ERROR.
 *
 * Si
 * maxSizeCache-sizeCache-size>0
 * no se hace nada.
 * en caso contrario se liberara espacio hasta cumplir.
 *
 *
 * @param size
 * @return bool
 */
bool ManejadorCache::liberarEspacio(int size) {

    bool rta=false;
    struct ARCHIVO file;

    while(this->maxSizeCache-this->sizeCache<size){  //mientras no haya espacio para almacenar el tamaño size en cache libera (teniendo en cuenta que previamente se intuyo que entra en cache)

        auto itr=cache.find(cola.back());
        file.puntero=itr->second.puntero;
        file.size=itr->second.size;

        delete file.puntero;

        this->sizeCache-=file.size;

        cache.erase(itr);    //libera espacio
        cola.pop_back();     //quita de la lista LRU
        rta=true;            //por que si
    }

    return rta;
}
