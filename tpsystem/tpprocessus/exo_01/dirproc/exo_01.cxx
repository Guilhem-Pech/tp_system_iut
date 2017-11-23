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

using namespace nsSysteme;
using namespace std;

namespace{
	bool pere;
	void Derout (int numSig){
		cout << " PID du processus ayant reçu le signal: " << ::getpid() << '\n' 
		     << "Signal reçu :" << ::strsignal(numSig) << '\n';  
	}
}

int main(int argc, char * argv [])
{
  try {
	nsFctShell::DerouterSignaux(Derout);
	pid_t pidFils;  
	
	if((pidFils = fork())){ // On est donc dans le processus père
		pere = true;
		Signal(SIGINT,SIG_DFL); // Remettre par default sigint
		std::cout << "PID du père : " << ::getpid() 
		          << " PID du fils : " << pidFils << std::endl;
	}
	else { // On est donc dans le processus fils
		pere=false;
		Signal(SIGTSTP, SIG_DFL); // Par default sigstop
		cout << "PID (Fils): " << ::getpid() <<
			" fils de :" << ::getppid() << endl;
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
