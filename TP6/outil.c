#include <stdio.h>   /* pour les entrées-sorties */
#include <string.h>  /* pour les manipulations de chaînes de caractères */
#include <conio.h>
#include <ctype.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>
#include "rep.h"

#define VERSION 3.0
#define SQUELET
/**************************************************************************/
/* Compléter votre nom ici                                                */
/*   Nom : Lusset                        Prénom :  Benoît                 */
/**************************************************************************/

extern bool modif;


/**********************************************************************/
/*  Ajout d'un contact dans le répertoire stocké en mémoire           */
/**********************************************************************/

int ajouter_un_contact_dans_rep(Repertoire *rep, Enregistrement enr)
{
#ifdef IMPL_TAB
	// compléter code ici pour tableau
	int idx;

	if (rep->nb_elts < MAX_ENREG)
	{
		*(rep->tab + rep->nb_elts) = enr;
		rep->nb_elts += 1;
		modif = true;
	}
	else {
		return(ERROR);
	}

	
#else
#ifdef IMPL_LIST
		
			// compléter code ici pour Liste
			
	bool inserted = false;
	SingleLinkedListElem* tmp = rep->liste->head;
	if (rep->nb_elts == 0) {                                   // regarde si la liste est vide
		InsertElementAt(rep->liste, rep->liste->size, enr);    // insère le premier élément de liste grâce à la fonction InsertElementAt
		rep->nb_elts += 1;
		modif = true;
		rep->est_trie = true;              //modifie les paramètres pour bien assigner la modification au programme
		inserted = true;
		return(OK);
	}
	else {
		for (int i = 0; i < rep->liste->size; i++) {					//parcours l'ensemble de la liste chaînée pour
			if (est_sup(enr, tmp->pers) == false) {						//comparer si l'enregistrement est plus petit que le maillon avec la fonction est_sup
				if (InsertElementAt(rep->liste, i, enr) != 0) {			//et s'il se situe avant l'élément suivant dans l'alphabet, place le nom à ce maillon
					rep->nb_elts += 1;
					modif = true;
					rep->est_trie = true;
					inserted = true;
					return(OK);
				}
				else {
					return(ERROR);
				}
			}
			else {
				tmp = tmp->next;									// décale le pointeur de la liste au maillon suivant afin de refaire une comparaison avec est_sup
			}
			if (i == rep->liste->size - 1) {
				if (InsertElementAt(rep->liste, i + 1, enr) != 0) {    //vérifie que l'insertion est possible dans la liste chaînée sinon renvoie une erreur
					rep->nb_elts += 1;
					modif = true;
					rep->est_trie = true;
					inserted = true;
					return(OK);
				}
				else {
					return(ERROR);
				}
			}
		}
		return(ERROR);
	}

#endif
	
#endif


	return(OK);

} /* fin ajout */
  /**********************************************************************/
  /* supprime du répertoire l'enregistrement dont l'indice est donné en */
  /*   paramètre       et place modif = true                            */
  /**********************************************************************/
#ifdef IMPL_TAB
void supprimer_un_contact_dans_rep(Repertoire *rep, int indice) {

	// compléter code ici pour tableau
	if (rep->nb_elts >= 1)		// s'il y a au moins un element ds le tableau 
	{						// et que l'indice pointe a l'interieur 
		
		for (int i = indice; i < rep->nb_elts; i++) {
			*(rep->tab + i) = *(rep->tab + i + 1);
		}

		rep->nb_elts -= 1;		// dans tous les cas, il y a un element en moins 
		modif = true;
	}

	return;
} /* fin supprimer */

#else
#ifdef IMPL_LIST
  /************************************************************************/
  /* supprime du répertoire l'enregistrement contenu dans le maillon elem */
  /*                   et fixe modif à vrai                              */
  /************************************************************************/
  // complet

	int supprimer_un_contact_dans_rep_liste(Repertoire *rep, SingleLinkedListElem *elem) {
	
	int ret=DeleteLinkedListElem(rep->liste, elem);
	if (ret == 1) {
		rep->nb_elts--;
		modif = true;
	}

	return (0); 
	}
#endif
#endif


  /**********************************************************************/
  /*  fonction d'affichage d'un enregistrement sur une ligne à l'écran  */
  /* ex Dupont, Jean                 0320304050                         */
  /**********************************************************************/
void affichage_enreg(Enregistrement enr)
{
	// code à compléter ici
	printf("%s, %s                      %s\n", enr.nom, enr.prenom, enr.tel);

} /* fin affichage_enreg */
  /**********************************************************************/
  /*  fonction d'affichage d'un enregistrement avec alignement des mots */
  /* pour les listes                                                    */
  /* ex | Dupont                |Jean                  |0320304050      */
  /**********************************************************************/
void affichage_enreg_frmt(Enregistrement enr)
{
	// code à compléter ici
	// comme fonction affichage_enreg, mais avec présentation alignées des infos
	printf("|%-20s  |%-20s  |%-30s\n", enr.nom, enr.prenom, enr.tel);

} /* fin affichage_enreg */


  /**********************************************************************/
  /* test si dans l'ordre alphabetique, un enregistrement est apres     */
  /* un autre                                                           */
  /**********************************************************************/
bool est_sup(Enregistrement enr1, Enregistrement enr2)					//On vérifie si la première chaine est après ou non dans l'alphabet (true si après)
{
	// code à compléter ici
	for (int i = 0; i < MAX_NOM; i++) {
		if (tolower(enr2.nom[i]) < tolower(enr1.nom[i])) return (true);   //on vérifie si la 1ere lettre du deuxième contact est plus bas que l'autre, si oui c'est bon
		if (tolower(enr2.nom[i]) > tolower(enr1.nom[i])) return (false);  //sinon on vérifie si elle est plus haut, si c'est le cas on return false
	}                                                                      //si les lettres sont les mêmes on refait un test sur la lettre suivante jusqu'à une différence
	for (int i = 0; i < MAX_NOM; i++) {
		if (tolower(enr2.prenom[i]) < tolower(enr1.prenom[i])) return (true);   //on refait pareil avec les prénoms au cas où les noms sont les mêmes
		if (tolower(enr2.prenom[i]) > tolower(enr1.prenom[i])) return (false);
	}
	return(false);																//dans le cas où les 2 sont les mêmes, on renvoie false par défaut

}
 
/*********************************************************************/
/*   Tri Alphabetique du tableau d'enregistrements                   */
/*********************************************************************/

void trier(Repertoire *rep)
{

#ifdef IMPL_TAB
	
	for (int j = 0; j < rep->nb_elts; j++) {
		for (int i = 0; i < rep->nb_elts; i++) {
			if (est_sup(*((rep->tab) + i), *((rep->tab) + i + 1)) == true) {
				Enregistrement tmp;
				tmp = *((rep->tab) + i);
				*((rep->tab) + i) = *((rep->tab) + i + 1);
				*((rep->tab) + i + 1) = tmp;
			}
		}
	}


	
#else
#ifdef IMPL_LIST
	// ajouter code ici pour Liste
	// rien à faire !
	// la liste est toujours triée dès ajouter_un_contact_dans_rep
#endif
#endif


	rep->est_trie = true;

} /* fin trier */

  /**********************************************************************/
  /* recherche dans le répertoire d'un enregistrement correspondant au  */
  /*   nom à partir de l'indice ind                                     */
  /*   retourne l'indice de l'enregistrement correspondant au critère ou*/
  /*   un entier négatif si la recherche est négative				    */
  /**********************************************************************/

int rechercher_nom(Repertoire *rep, char nom[], int ind)
{
	int i = ind;		    /* position (indice) de début de recherche dans tableau/liste rep */
	int ind_fin;			/* position (indice) de fin de tableau/liste rep */

	char tmp_nom[MAX_NOM];	/* 2 variables temporaires dans lesquelles */
	char tmp_nom2[MAX_NOM];	/* on place la chaine recherchee et la chaine lue dans le */
							/* tableau, afin de les convertir en majuscules et les comparer */
	bool trouve = false;		


#ifdef IMPL_TAB
							// ajouter code ici pour tableau
	ind_fin = rep->nb_elts - 1;
	strcpy_s(tmp_nom, _countof(tmp_nom), nom);    //on copie le nom dans tmp_nom, et on le passe en majuscule avec strupr
	_strupr_s(tmp_nom, _countof(tmp_nom));
	while (trouve == false) {  //on va comparer tmp_nom a chaque élément du répertoire 
		strcpy_s(tmp_nom2, _countof(tmp_nom2), rep->tab[i].nom);   //on copie dans tmp_nom2 le nom du répertoire et on le passe en majuscule pour comparer dans le même format
		_strupr_s(tmp_nom2, _countof(tmp_nom2));
		if (strcmp(tmp_nom, tmp_nom2)==0) {				 //on compare
			trouve = true;								//si ce sont les mêmes trouve devient true 
		}
		else if (i == ind_fin) {
			return -1;  //si on est arrivé à la fin, et qu'on a pas trouvé on return -1
		}
		i++; 
	}
	return i-1; //on return l'indice du nom trouvé
	
#else
#ifdef IMPL_LIST
							// ajouter code ici pour Liste

	SingleLinkedListElem* tmp = rep->liste->head;		// positionne un pointeur sur la tête de la liste chaînée
	for (i = 0; i < rep->liste->size; i++) {
		if (_stricmp(nom, tmp->pers.nom) == 0) {		// compare le nom tapé avec le nom du maillon choisi
			trouve = true;
			return i - 1;
			break;										// sort de la boucle si le nom a été trouvé
		}
		tmp = tmp->next;								//positionne le pointeur sur le maillon suivant 
	}
	return -1;
	
#endif
#endif

	return((trouve) ? i : -1);
} /* fin rechercher_nom */

  /*********************************************************************/
  /* Supprimer tous les caracteres non numériques de la chaines        */
  /*********************************************************************/

void supprime_caractere(char* chaine, int rang) {					//on créé une fonction pour supprimer un caractère d'un chaine pour la fonction compact
	int j = rang;
	while (*(chaine + j + 1) != '\0') {
		*(chaine + j) = *(chaine + j + 1);
		j++;
	}
	chaine--;
	return;
}

void compact(char *s)
{
	// compléter code ici
	
	int k = 0;

	while (*(s + k) != '\0') {
		if (isdigit(*(s + k)) == 0) {
			supprime_caractere(&s,k);
		}
	}

	return;
}

/**********************************************************************/
/* sauvegarde le répertoire dans le fichier dont le nom est passé en  */
/* argument                                                           */
/* retourne OK si la sauvegarde a fonctionné ou ERROR sinon           */
/**********************************************************************/
int sauvegarder(Repertoire *rep, char nom_fichier[])
{
	FILE *fic_rep;					/* le fichier */
#ifdef IMPL_TAB
	
	errno_t err = fopen_s(&fic_rep, nom_fichier, "w");
	if (fic_rep == NULL) return ERROR;

	for (int i = 0; i < rep->nb_elts; i++) {

		int nbDeCar = 4 + strlen(rep->tab[i].nom) + strlen(rep->tab[i].prenom) + strlen(rep->tab[i].tel);  // 4 pour 2*";" et "\n" et "\0"
		char* buffer = (char*)malloc(nbDeCar * sizeof(char));
		if (buffer == NULL) {
			printf("Memoire insuffisante.");
			return ERROR;
		}
		strcpy_s(buffer, nbDeCar, rep->tab[i].nom);
		strcat_s(buffer, nbDeCar, ";");
		strcat_s(buffer, nbDeCar, rep->tab[i].prenom);
		strcat_s(buffer, nbDeCar, ";");
		strcat_s(buffer, nbDeCar, rep->tab[i].tel);
		strcat_s(buffer, nbDeCar, "\n");
		fputs(buffer, fic_rep);
		free(buffer);
	}
	fclose(fic_rep);
	return OK;
	
#else
#ifdef IMPL_LIST
	// ajouter code ici pour Liste

	errno_t err = fopen_s(&fic_rep, nom_fichier, "w");

	if ((err = fopen_s(&fic_rep, nom_fichier, "w")) != 0) {
		return(err);
	}
	else {
		LinkedList* liste = rep->liste;
		if (fic_rep != 0) {
			for (size_t i = 0; i < liste->size; i++) {
				fprintf(fic_rep, "%s%c%s%c%s\n", GetElementAt(liste, i)->pers.nom, SEPARATEUR, GetElementAt(liste, i)->pers.prenom, SEPARATEUR, GetElementAt(liste, i)->pers.tel);
			}
			fclose(fic_rep);
			return OK;
		}
		else { return ERROR; }
	}



#endif
#endif

	return(OK);
} /* fin sauvegarder */


  /**********************************************************************/
  /*   charge dans le répertoire le contenu du fichier dont le nom est  */
  /*   passé en argument                                                */
  /*   retourne OK si le chargement a fonctionné et ERROR sinon         */
  /**********************************************************************/

int charger(Repertoire *rep, char nom_fichier[])
{
	FILE *fic_rep;					/* le fichier */
	errno_t err;
	int num_rec = 0;						/* index sur enregistrements */
	int long_max_rec = sizeof(Enregistrement);
	char buffer[sizeof(Enregistrement) + 1];
	int idx = 0;

	char *char_nw_line;
	
	_set_errno(0);
	if ( ((err = fopen_s(&fic_rep, nom_fichier, "r")) != 0) || (fic_rep == NULL) )
	{
		return(err);
	}
	else
	{
		while (!feof(fic_rep) && (rep->nb_elts < MAX_ENREG))
		{
			if (fgets(buffer, long_max_rec, fic_rep) != NULL)
			{
				/* memorisation de l'enregistrement lu dans le tableau */
				buffer[long_max_rec] = 0;			/* en principe il y a deja un fin_de_chaine, cf fgets */

				if ((char_nw_line = strchr(buffer, '\n')) != NULL)
					*char_nw_line = '\0';			/* suppression du fin_de_ligne eventuel */

				idx = 0;								/* analyse depuis le debut de la ligne */
#ifdef IMPL_TAB
				if (lire_champ_suivant(buffer, &idx, rep->tab[num_rec].nom, MAX_NOM, SEPARATEUR) == OK)
				{
					idx++;							/* on saute le separateur */
					if (lire_champ_suivant(buffer, &idx, rep->tab[num_rec].prenom, MAX_NOM, SEPARATEUR) == OK)
					{
						idx++;
						if (lire_champ_suivant(buffer, &idx, rep->tab[num_rec].tel, MAX_TEL, SEPARATEUR) == OK)
							num_rec++;		/* element à priori correct, on le comptabilise */
					}
				}
#else
#ifdef IMPL_LIST
														// ajouter code implemention liste

				SingleLinkedListElem* temp = rep->liste->head;
				if (lire_champ_suivant(buffer, &idx, temp->pers.nom, MAX_NOM, SEPARATEUR) == OK)
				{
					idx++;							/* on saute le separateur */
					if (lire_champ_suivant(buffer, &idx, temp->pers.prenom, MAX_NOM, SEPARATEUR) == OK)
					{
						idx++;
						if (lire_champ_suivant(buffer, &idx, temp->pers.tel, MAX_TEL, SEPARATEUR) == OK)
							temp = temp->next;	/* element à priori correct, on le comptabilise */
						/*num_rec++;*/
					}
				}
#endif
#endif




			}

		}
		rep->nb_elts = num_rec;
		fclose(fic_rep);
		return(OK);
	}


} /* fin charger */