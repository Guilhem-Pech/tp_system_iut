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
namespace {
  std::size_t donnerTailleMorceau(const string & comment, const string & nomFic){
  
    if(comment == "char") return 1;
    if(comment == "all") {
      struct stat S;
      Stat (nomFic . c_str(), & S);
      return S.st_size;
    }
    if(comment == "block") {
      struct stat S;
      Stat (nomFic . c_str(), & S);
      return S.st_blksize;
    }
    throw CExc("donneTaille()", string("argument invalide ") + comment);
  }
}

int main(int argc, char * argv [])
{
  try {
    cout << argv[1] << " " << argv[2];
    std::size_t size = donnerTailleMorceau("all",argv[1]);
    cout << "Taille tampon: " + size << endl;
    nsFctShell::FileCopy(argv[2],argv[1],size);


///code
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
