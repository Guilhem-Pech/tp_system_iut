/**
 *
 * @File : exo_01_TuQuoqueFili_b.cxx 
 *
 * @Authors : D. Mathieu
 *            M. Laporte
 *
 * @Date : 2002
 *
 * @Version: petite adaptation A. B. Dragut 2011
 *
 * @Synopsis : Utilisation de kill()
 *
 **/
#include <string>
#include <exception>
#include <csignal>          // SIGKILL

#include <unistd.h>         // getppid(), sleep()
#include <sys/types.h>      // pid_t

#include "CExc.h"
#include "nsSysteme.h"      // Fork(), Kill()

using namespace nsSysteme;  // Fork(), Kill()
using namespace std;

int main(int argc, char * argv[])  
{ 
try {
   

    if (1 != argc)
        throw CExc("main()",string ("Usage : ") + argv [0]);

    ::pid_t n;
    if (!(n = Fork ())) 
         Kill (n, SIGKILL); 
     else 
     { 
         ::sleep (3); 
         Kill (::getppid (), SIGKILL); 
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
