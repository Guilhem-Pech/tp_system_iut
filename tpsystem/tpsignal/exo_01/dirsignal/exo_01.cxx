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
#include <string.h>

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
    if (2 != argc || 
       (argv[1][0] != 'D' && argv[1][0] != 'I' && argv[1][0] != 'P')) 
       throw CExc ("main()",string ("Usage : ") + argv [0] + " {P|I|D} ");
    
    for(int NumSig(1) ; NumSig < 31 ; ++NumSig) {
      if (NumSig != SIGKILL && NumSig != SIGSTOP && NumSig != SIGCONT) {
	switch (argv[1][0]){
	case 'P':
	  Signal(NumSig,Derout);
	  cout << "Signal  " << strsignal(NumSig) << "(" << NumSig << ") mise en place du déroutement du signal" << endl;
	  break;
	case 'I':
	  Signal(NumSig,SIG_IGN);
	  cout << "Signal  " << strsignal(NumSig) << "(" << NumSig << ") le signal sera ignoré" << endl;
	  break;
	case 'D':
	  Signal(NumSig,SIG_DFL);
	  cout << "Signal  " << strsignal(NumSig) << "(" << NumSig << ") traitement par défault" << endl;
	  break;
	default:
	  throw CExc ("main()",string ("Usage : ") + argv [0] + " {P|I|D} ");
	  break;
	}
      } else{
	cout << "Signal non déroutable " << _sys_siglist [NumSig] << "\n";
      } 
    }
     cout << "Deroutement acheve.\n";
     for(;;);      
///code
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
	return 0;
}  //  main()
