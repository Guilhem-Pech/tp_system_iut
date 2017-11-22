/**
 *
 * @File : exo_04.cxx
 *
 * @Author : A. B. Dragut
 *
 * @Synopsis : 
 *
 **/
#include <iostream> 
#include <exception>
#include <string>
#include <iomanip>
#include <vector>
#include <algorithm>       // sort()
#include <csignal>         // sigemptyset(), sigaddset(),
                           // SIG_BLOCK, SIG_UNBLOCK, SIGINT

#include <unistd.h>        // sleep()

#include "CExc.h"
#include "nsSysteme.h"

using namespace std;
using namespace nsSysteme;

namespace 
{
    typedef vector <int> CVInt;
    CVInt V;

    void Affich (void)
    {
        /** /

        cout << "Vecteur trié : " << endl;
        for (CVInt::size_type i = 0; i < V.size(); ++i)
        {
            cout << setw (5) << V [i] << flush;
            ::sleep (1); 
        }

        */   //  autre version

        for (CVInt::const_iterator i = V.begin(); i < V.end(); ++i)
        {
            cout << setw (5) << *i << flush;
            ::sleep (1);
        }
        /**/

        cout << endl;

    } // Affich()

    void Derout (int)
    { 
        cout << "Tapez un entier : ";
        int IntLu;
        cin >> IntLu;
        V.push_back (IntLu);
        sort (V.begin(), V.end());

    } //  Derout()

} // namespace anonyme

int main(int argc, char * argv []) 
{
  try {
   if (argc != 1)
        throw CExc("main()",string ("Usage : ") + argv [0]);

    V.push_back ( 0);
    V.push_back (10);
    V.push_back (20);

    Signal (SIGINT, Derout);

    sigset_t Masque; 
    sigemptyset (&Masque);
    sigaddset   (&Masque, SIGINT);

    for (;;)
    {
        ::sleep (10);

	Sigprocmask (SIG_BLOCK,   & Masque, 0);
        Affich();
        Sigprocmask (SIG_UNBLOCK, & Masque, 0);
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



}  //  main ()


