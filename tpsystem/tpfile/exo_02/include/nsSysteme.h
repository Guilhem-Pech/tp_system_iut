/**
 *
 * @File : nsSysteme.h
 *
 * @Synopsis : espace de noms qui contient les prototypes des wrappers
 *             des fonctions systeme
 *
 *
 **/
#if !defined __NSSYSTEME_H__
#define      __NSSYSTEME_H__

#include <cstddef>        // size_t

#include <sys/types.h>    // ssize_t
                                                    
#include <sys/stat.h>     // struct stat, stat(), fstat()


#include "string.h"

#include "CExc.h"

//  Declarations des fonctions concernant les fichiers
//  =========================================================

namespace nsSysteme
{
   void        Stat    (const char * file_name, struct stat * buf)
                             throw (CExc);

      
} // nsSysteme




//  Definitions courtes des fonctions concernant les fichiers
//  =========================================================

inline
void nsSysteme::Stat (const char * file_name, struct stat * buf)
    throw (CExc)
{
    if (::stat (file_name, buf))
        throw CExc ("stat()", std::string("fichier :")+ file_name);

} // Stat()



#endif    /* __NSSYSTEME_H__ */
