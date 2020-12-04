#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#define MAX_NOM 20

bool est_sup(char* enr1, char* enr2)					//On vérifie si la première chaine est après ou non dans l'alphabet
{
	// code à compléter ici
	for (int i = 0; i < MAX_NOM; i++) {
		if (tolower(enr2[i]) < tolower(enr1[i])) return (true);   //on vérifie si la 1ere lettre du deuxième contact est plus bas que l'autre, si oui c'est bon
		if (tolower(enr2[i]) > tolower(enr1[i])) return (false);  //sinon on vérifie si elle est plus haut, si c'est le cas on return false
	}                                                                      //si les lettres sont les mêmes on refait un test sur la lettre suivante jusqu'à une différence

	return(false);																//dans le cas où les 2 sont les mêmes, on renvoie false par défaut

}

main() {

	char* nom1[MAX_NOM] = { 'J', 'O', 'H', 'N' };
	char* nom2[MAX_NOM] = { 'B','E','N' };
	if (est_sup(nom2,nom1) == true) { printf("oui"); }
	else { printf("non"); }

}