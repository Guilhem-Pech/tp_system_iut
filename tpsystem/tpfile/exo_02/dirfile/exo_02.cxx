#include <string>
#include <exception>
#include <sys/stat.h>       // struct stat
#include "CExc.h"
#include "nsSysteme.h"      // Stat()

using namespace nsSysteme;  // Stat()
using namespace std;


int main (int argc, char * argv [])
{
    try
      {
      // Si pas d'argument renvoyer une erreur
      if (2 != argc)
	throw CExc (string ("main()"),string("Usage ") +
		    argv [0] + " <nomFic>");

      // Remplissage de la struct:
      struct stat S;
      Stat (argv[1], & S);
      
      // Affichage des informations contenu dans la struct
      cout << "Nom fichier: " << argv[0] << endl
	   << "Poid fichier: " << S.st_size << endl
	   << "Nombre de lien en dur: " << S.st_nlink << endl
	   << "Derniere modif " << ctime(&(S.st_mtime)) << endl;
      
      return 0;
      }
    
    catch (const CExc & Exc)
    {
        cerr <<Exc<< endl;
        return errno;
    }
    catch (const exception & Exc)
    {
        cerr << "Exception : " << Exc.what () << endl;
        return 1;
    }
    catch (...)
    {
        cerr << "Exception inconnue recue dans la fonction main()" 
             << endl;
        return 1;
    }

}  // main()

