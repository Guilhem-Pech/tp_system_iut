/**
 *
 * @File :
 *
 * @Author : Guilhem PECH (# Le plus beau)
 *
 * @Synopsis : Exercice 1
 **/

#include <string>
#include <exception>
#include <iostream>

#include <unistd.h>     // getdtablesize()
#include <sys/time.h>   // fd_set

#include "nsSysteme.h"
#include "CExc.h"

using namespace nsSysteme;
using namespace std;

int main(int argc, char * argv [])
{
  try {
    int pipe[2];
    Pipe(pipe);
    int fils = Fork();
    int TailleMessage;
    if (fils == 0){
        Close(pipe[1]);
        int VraieFinPasRecue = 1 ;
        while (VraieFinPasRecue) { //tant que on n'as pas recu  '#' on continue
            int OctetsLus = Read (pipe[0], &TailleMessage, sizeof (int));
            char Message [TailleMessage + 1];
            if(OctetsLus) {
                int TailleMessageReelle = Read (pipe[0], Message, TailleMessage);
                Message[TailleMessageReelle] = '\0';
                if((1 == TailleMessage) && ('#' == Message[0])) {
                    VraieFinPasRecue = 0;
                    cout << "Fin de la communication" << endl;
                 }
                else {
                    cout << "Message reçu par: " << ::getpid() << " est: "
                        << Message << endl;
                }
            }
            else {
                VraieFinPasRecue = 0;
                cout << "La communication est interrompue "     << endl;
                cout << "Fermeture du Pipe" << endl;
            }
        }
    }
    else {
        Close(pipe[0]);
        for (int i = 1; i < argc ; ++i ){
            int messageLength = strlen(argv[i]);
            Write(pipe[1],&messageLength,sizeof(int));
            Write(pipe[1],argv[i],messageLength);
         }
        char endCommunication = '#';
        int messageLength = 1;
        Write (pipe[1],&messageLength,sizeof(int));
        Write (pipe[1],&endCommunication,1);

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
