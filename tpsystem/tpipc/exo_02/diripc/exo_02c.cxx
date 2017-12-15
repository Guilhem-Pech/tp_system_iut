/**
 *
 * @File : exo_02c.cxx
 *
 *
 * @Author : A. Dragut
 *
 * @Synopsis : Producteur-Consommateur communicant
 *             a travers une FIFO  -- mkfifo()
 *
 **/
#include <iostream>
#include <string>
#include <exception>
#include <unistd.h>      // getpid()
#include <cerrno>        // ENOENT, EEXIST
#include <fcntl.h>       // O_RDONLY


#include "CExc.h"	  // exceptions fonctions systemes
#include "nsSysteme.h"    //appels systemes

using namespace std;
using namespace nsSysteme; //utilisation de la bibliotheque nsSysteme




int main(int argc, char * argv [])
{
	try {

		if (argc != 2)
			throw CExc("main()",string ("Usage : ") + argv [0] +
					   " <FIFO>");


		//on essaye de creer la FIFO si le producteur ne l'as pas deja fait
		//si elle est creee l'erreur systeme sera EEXIST
		//dans ce cas on va simplement continuer en l'utilisant

		//creation d'un fichier de type FIFO

		try { Mkfifo (argv [1], 0700); }

		catch (const CExc & Exc) {
			cerr <<Exc<< endl;
			if (errno != EEXIST) throw;
			cerr << "Ce n'est pas grave, on continue.\n";
		}

		//Un fichier FIFO peut etre ouvert en ecriture dans le producteur
		//ou en lecture dans le consommateur
		//mais pas en O_RDWR

		const int fdFIFO = Open(argv[1], O_RDONLY);


		//protocole de communication

		//chaque message de taille variable est precede d'un entier contenant
		//sa taille en octets. Ca nous aide a savoir combien il faut  lire
		//(un entier est code toujours sur sizeof(int))

		size_t TailleMessage; //en octets
		int VraieFinPasRecue = 1;

		while (VraieFinPasRecue) { //tant que on n'as pas recu  '#' on continue
		    int OctetsLus = Read (fdFIFO, &TailleMessage, sizeof (int));
		    char Message [TailleMessage + 1];
		    if(OctetsLus) {
			int TailleMessageReelle = Read (fdFIFO, Message, TailleMessage);
			Message[TailleMessageReelle] = '\0';
			if((1 == TailleMessage) && ('#' == Message[0])) {
			    VraieFinPasRecue = 0;
			    cout << "Fin de communication annoncee par '#'" << endl;
			}
			else {
			    cout << "Le Consommateur fils id : " << ::getpid() << " a lu : "
				 << Message << endl;
			}
		    }
		    else {
			VraieFinPasRecue = 0;
			cout << "Fin de communication imprevue. "     << endl;
			cout << "Le pere producteur a ferme son pipe" << endl;

			//le producteur a deja ferme son pipe/tuyau
			//donc on peut fermer tout de suite
		    }
		}
		//Fin de communication du cote processus consommateur
		Close (fdFIFO);

		//on essaye d'effacer la FIFO si le producteur ne l'as pas deja fait
		//si elle est effacee l'erreur sera ENOENT
		//dans ce cas on va simplement finir le consommateur avec un return 0;

		try { Unlink (argv [1]); }
		catch (const CExc & Exc) {
			cerr <<Exc<< endl;
			if (errno != ENOENT) throw;
			cerr << "Ce n'est pas tres grave.\n";
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
