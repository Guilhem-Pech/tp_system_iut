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

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


using namespace nsSysteme;
using namespace std;

int main(int argc, char * argv []){
    try {
        Open("ecriture",O_WRONLY | O_CREAT,0700);
        Open("lecture",O_RDONLY | O_CREAT,0700);
        Open("lecture", O_RDWR | O_CLOEXEC );
        ::execl("exo_05_x.run","Edouard", static_cast<char *>(0));


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
