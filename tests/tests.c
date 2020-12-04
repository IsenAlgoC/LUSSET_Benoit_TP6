#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#define MAX_NOM 20

bool est_sup(char* enr1, char* enr2)					//On v�rifie si la premi�re chaine est apr�s ou non dans l'alphabet
{
	// code � compl�ter ici
	for (int i = 0; i < MAX_NOM; i++) {
		if (tolower(enr2[i]) < tolower(enr1[i])) return (true);   //on v�rifie si la 1ere lettre du deuxi�me contact est plus bas que l'autre, si oui c'est bon
		if (tolower(enr2[i]) > tolower(enr1[i])) return (false);  //sinon on v�rifie si elle est plus haut, si c'est le cas on return false
	}                                                                      //si les lettres sont les m�mes on refait un test sur la lettre suivante jusqu'� une diff�rence

	return(false);																//dans le cas o� les 2 sont les m�mes, on renvoie false par d�faut

}

main() {

	char* nom1[MAX_NOM] = { 'J', 'O', 'H', 'N' };
	char* nom2[MAX_NOM] = { 'B','E','N' };
	if (est_sup(nom2,nom1) == true) { printf("oui"); }
	else { printf("non"); }

}