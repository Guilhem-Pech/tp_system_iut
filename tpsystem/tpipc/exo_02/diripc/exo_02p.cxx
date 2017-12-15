/**
 *
 * @File : exo_02p.cxx
 *
 *
 * @Author : A. Dragut
 *
 * @Synopsis : Producteur-Consommateur communiquant
 *             a travers une FIFO  -- mkfifo()
 *
 **/
#include <iostream>
#include <string>
#include <exception>
#include <unistd.h>      // getpid()
#include <cerrno>        // ENOENT, EEXIST
#include <fcntl.h>       // O_WRONLY

#include "CExc.h"	  // exceptions fonctions systemes
#include "nsSysteme.h"    //appels systemes

using namespace std;
using namespace nsSysteme; //utilisation de la bibliotheque nsSysteme




int main(int argc, char * argv [])
{
	try {

		if (argc < 3)
			throw CExc("main()",string ("Usage : ") + argv [0] +
					   " <FIFO> <Il faut donner des chaines a transmettre au consommateur>");


		//on essaye de creer la FIFO si le consommateur ne l'as pas deja fait
		//si elle est creee, l'erreur systeme sera EEXIST
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

		const int fdFIFO = Open(argv[1], O_WRONLY);


		//protocole de communication

		//chaque message de taille variable est precede d'un entier contenant
		//sa taille en octets. Ca nous aide a savoir combien il faut  lire
		//(un entier est code toujours sur sizeof(int))

		size_t TailleMessage; //en octets

		//protocole de communication

		//chaque message de taille variable est precede d'un entier contenant
		//sa taille en octets. Ca nous aide a savoir combien il faut  lire
		//(un entier est code toujours sur sizeof(int))

		for (int i = 2; i < argc; ++i)
		{

			//la taille du message ecrit dans le pipe
			TailleMessage = strlen (argv [i]);
			//ecriture de la taille en octets
			Write (fdFIFO, &TailleMessage, sizeof (int));
			Write (fdFIFO, argv [i], TailleMessage);
		}

		//le producteur connait le nombre de messages a envoyer
		//mais le consommateur ne va pas savoir quand il doit s'arreter
		//si on ne lui annonce pas la fin

		//protocole de fin de communication
		//fin annoncee par '#' de taille 1

		TailleMessage = 1;
		char Fin='#';
		Write (fdFIFO, &TailleMessage, sizeof (int));
		Write (fdFIFO, &Fin, TailleMessage);

		//fermeture complete de pipe
		//fin effective
		//le producteur ne doit plus ecrire apres que le
		//consommateur a ferme son bout de pipe, sinon
		//le producteur recoit un SIGPIPE

		// mais le producteur peut fermer son bout de pipe
		// a tout moment, independamment du consommateur


		//Sans un protocole de fin on ne peut pas differencier
		//entre une fin attendue et une par erreur

		/* Si le consommateur fait un read() apres que
                 le pipe/tuyau est ferme en ecriture
		 par le producteur (celui qui fait write()), alors
		 le read() du consommateur renvoie 0
		 */

		/* Si le producteur est ferme a cause d'un incident:
		 segmentation fault, arrivee de signal,.., etc.
		 le read() du consommateur renvoie 0 aussi
		 */


		//Fin de communication du cote processus consommateur
		Close (fdFIFO);

		//on essaye d'effacer la FIFO si le consommateur ne l'as pas deja fait
		//si elle est effacee l'erreur sera ENOENT
		//dans ce cas on va simplement finir le producteur avec un return 0;

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
