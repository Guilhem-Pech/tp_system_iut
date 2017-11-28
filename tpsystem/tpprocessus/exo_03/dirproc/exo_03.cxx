/**
 *
 * @File : 
 *
 * @Author : A. B. Dragut
 *
 * @Synopsis : modelmain
 **/

#include <string>
#include <exception>
#include <iostream>    

#include <unistd.h>     // getdtablesize()
#include <sys/time.h>   // fd_set

#include "nsSysteme.h"
#include "CExc.h"

#define GETSTATUS(status) (((status) >> 8) & 0xff)

using namespace nsSysteme;
using namespace std;
namespace{
    void Derout(int numSignal){
        cout <<" Fils arrété , Init récupère son status" << endl;
    }//Derout
}//Namespace anonyme


int main(int argc, char * argv [])
{
  try {
    if (argc <= 1)
        return 1;
      
    struct sigaction Act;
    Act.sa_flags = SA_NOCLDWAIT;
    sigemptyset(&Act.sa_mask);
    Act.sa_handler = Derout;

    Sigaction (SIGCHLD,&Act,NULL);
    
    int NbreFils = atoi(argv[1]);
    for (int i = NbreFils; i >= 0 ; --i ){
        if (!Fork()){
            cout << "Le fils "<< ::getpid() <<" va dormir pendant  " << i << " secondes"<< endl;
            ::sleep (i);
            return i;
         }
    }
    for(;;);

    return 0;
  }
  catch (const CExc & Exc) {
        cerr <<Exc<< endl;
        return errno;
  }
  catch (const exception & Exc) {
        cerr << "Exception : " << Exc.what () << endl;
        return 1;
  }
  catch (...) {
        cerr << "Exception inconnue recue dans la fonction main()" 
             << endl;
        return 1;
  }


}  //  main()
