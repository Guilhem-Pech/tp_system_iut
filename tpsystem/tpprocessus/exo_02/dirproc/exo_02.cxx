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
        cout << "Processus dérouté" << endl;
    }//Derout
}//Namespace anonyme


int main(int argc, char * argv [])
{
  try {
    int NbrFils = atoi(argv[1]); // Prend le premier argument et le converti en integer.
    Signal(SIGCHLD,Derout); // Déroutement du signal SIGCHLD vers la fonction Derout.
    ::pid_t TabDesPID[NbrFils];
    for (int i(NbrFils); i ;--i){
        if (!(TabDesPID[i] = Fork())){
            cout << "Le processus "<< ::getpid() << " va  dormir pendant " << i << " secondes" << endl; 
            ::sleep(i); // Fait dormir le processus pour i secondes
            return i; 
        }
    }
    int status;
    ::pid_t Fils;
    for (int i = NbrFils;i;--i ) {
        Fils=TabDesPID [i];
        Waitpid(TabDesPID[i],&status,0);
        cout << "Le fils de pid " << Fils << " est termine " << endl;
        if (WIFEXITED(status))
            cout << "Statut exit : " << WEXITSTATUS(status) << endl;

        if (WIFEXITED(status)) 
             cout << "Statut exit (avec macro): " << GETSTATUS (status) << endl;


    }


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
