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

namespace
{
  void Derout(int sigInt)
  {
    cout<< sigInt << " :" << strsignal(sigInt) << " ;" << endl;
  }
  
}

int main(int argc, char * argv [])
{
  try {
	if (1 != argc) 
	      throw CExc ("main()",string ("Usage : ") + argv [0]);


	for (int NumSig = 1; NumSig < CstSigMax; ++NumSig) {
	      	if(NumSig != SIGKILL && NumSig != SIGSTOP) {
		struct sigaction Action;
	
		Action.sa_flags   = SA_RESETHAND;
		Action.sa_handler = Derout;
		sigemptyset (& Action.sa_mask);
	
		Sigaction (NumSig, &Action, 0);
		cout <<  _sys_siglist [NumSig] << " (" << NumSig  << ") deroute, traitement Particulier,"
		     << " et restoration automatique au traitement par defaut" << endl;
	      	}
      else {
	cout << "Signal non déroutable " << _sys_siglist [NumSig] << "\n";
      }
    }
    cout << "Deroutement acheve.\n";
      
      
    for (;;);
    
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
