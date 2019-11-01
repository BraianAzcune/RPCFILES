/**
 * Project TP1EJ2SERVIDOR
 */


#ifndef _ARCHIVO_H
#define _ARCHIVO_H
#include <sys/types.h>
#include "rpc/this_session.h"
using namespace std;

struct ARCHIVO
{
    char* puntero;
    size_t size;
    rpc::session_id_t idSession;
};




#endif //_ARCHIVO_H
