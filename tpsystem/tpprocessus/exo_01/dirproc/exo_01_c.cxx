/**
 *
 *  @File : exo_01_c.cxx
 *
 *  @Authors  : A. Dragut
 *  @Synopsis : mise en evidence du partage de pointeur de fichier.
 *
 **/

#include <string>
#include <exception>
#include <iostream>   
#include <sys/types.h>      // pid_t 

#include <unistd.h>         // SEEK_SET
#include <fcntl.h>          // O_RDWR

#include "nsSysteme.h"
#include "CExc.h"

using namespace nsSysteme;
using namespace nsFctShell;
using namespace std;




int main(int argc, char * argv [])
{
  try {
    if (1 != argc)
        throw CExc ("main()",string ("Usage : ") + argv [0]);

    char c;

    const int fd = Open ("exo_01_c.txt", O_RDWR);

    if (Fork ()){   //pere
	  sleep(5);
        Lseek (fd,5, SEEK_SET);                         /* 01 */
        sleep(4);Read  (fd, &c, 1);                              /* 02 */
        cout << "lu par le pere : " << c << endl;       /* 03 */
	  sleep(10);
        Read  (fd, &c, 1);                              /* 04 */
        cout << "lu par le pere : " << c << endl;       /* 05 */
    }
    else{ //fils  
        Lseek (fd, 3, SEEK_SET);                        /* 01fils */
	  sleep(7);
        Read  (fd, &c, 1);                              /* 02fils */
        Write (fd, "ABCDE", 3);                         /* 03fils */
        cout << "lu par le fils : " << c << endl;       /* 04fils */
    }
    Close (fd);
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

