#include "t_disjoncteur.h"
#include <stdlib.h>

// Retourne un disjoncteur cr�er en allocation dynamique et initialis�.
t_disjoncteur* nouveau_disjoncteur(int ampere, int tension) {

	t_disjoncteur* nouveau_disjoncteur = (t_disjoncteur*)malloc(sizeof(t_disjoncteur));

	nouveau_disjoncteur->ampere = ampere;

	nouveau_disjoncteur->tension = tension;

	nouveau_disjoncteur->demande_du_circuit = 0;

	tester_etat_disjoncteur(nouveau_disjoncteur);

	init_liste(nouveau_disjoncteur->ref_appareils, MAX_APPAREILS);

	return nouveau_disjoncteur;
}


// Retourne la puissance maximum possible pour ce disjoncteur.
int puissance_max(const t_disjoncteur* disjoncteur){

	return (disjoncteur->tension*disjoncteur->ampere*COEFF_PUISSANCE);
}


// Change l'�tat du disjoncteur � sa bonne valeur
void tester_etat_disjoncteur(t_disjoncteur* disjoncteur)
{
	disjoncteur->etat = 
		((disjoncteur->demande_du_circuit) < disjoncteur->ampere) ? 
		ALLUME : ETEINT;
}



/*Calcule la demande totale en amp�res de tous les appareils branch�s 
* sur un disjoncteur, et met le r�sultat dans disjoncteur.demande_du_circuit
*/
void calculer_demande_totale(t_disjoncteur* disjoncteur) {
	
	if (!liste_est_vide(disjoncteur->ref_appareils)) {

		do {

			disjoncteur->demande_du_circuit += lire_appareil(disjoncteur->ref_appareils).ampere;

		}while (!pc_a_la_fin(disjoncteur->ref_appareils));		

		disjoncteur->demande_du_circuit += lire_appareil(disjoncteur->ref_appareils).ampere;

	}	
}




//sous programme qui lit un �l�ment dans la liste, le convertit en appareil
//et met la position courante � la case suivante
static t_appareil lire_appareil(t_liste* liste) {


	//permet d'aller lire un �l�ment de la liste
	t_element* element;
	

	//Lecture de l'�l�ment � la position courante
	obtenir_element(liste, element);

	//incr�mentation de la position
	set_pc_suivant(liste);

	//conversion de l'�l�ment en t_appareil*
	return *((t_appareil*)element);
}




/*permet d'ajouter un appareil dans la liste d'appareils
* n�cessite de fournir toutes les caract�ristiques de l'appareil
* 
* s'occupe aussi d'actualiser la consommation sur le disjoncteur
* ET son �tat
*/

void ajouter_un_appareil(t_disjoncteur* disjoncteur, 
	t_chaine categorie, t_chaine emplacement,
	double ampere, double tension) {

	/*Strat�gie : 
	* On appelle le sous-programme de cr�ation d'un appareil avec les 
	* bons param�tres, puis on l'ins�re dans la liste d'appareils
	* � la position courante.
	* 
	* On actualise ensuite les champs du disjoncteur
	*/
	
	if (tension == disjoncteur->tension) {

		//cr�ation et insertion du disjoncteur dans la liste
		inserer(disjoncteur->ref_appareils,
			nouvel_appareil(categorie, emplacement, ampere, tension));

		//actualisation de la demande totale
		calculer_demande_totale(disjoncteur);

		//actualisation de l'�tat du disjoncteur
		tester_etat_disjoncteur(disjoncteur);
	}
}



/*permet de retirer un appareil dans la liste d'appareils---------------------------------A TERMINER-------------
* n�cessite de fournir toutes les caract�ristiques de l'appareil
*
* s'occupe aussi d'actualiser la consommation sur le disjoncteur
* ET son �tat
*/

void retirer_un_appareil(t_disjoncteur* disjoncteur,
	t_chaine categorie, t_chaine emplacement,
	double ampere, double tension) {

	/*Strat�gie :
	* On compare si
	* On appelle le sous-programme de cr�ation d'un appareil avec les
	* bons param�tres, puis on l'ins�re dans la liste d'appareils
	* � la position courante.
	*/

	t_element* element;

	t_appareil* appareil_1 = 
		nouvel_appareil(categorie, emplacement, ampere, tension);

	set_pc_debut(disjoncteur->ref_appareils);



	while (!pc_a_la_fin(disjoncteur->ref_appareils)) {

		obtenir_element(disjoncteur->ref_appareils, element);

		if (appareils_sont_pareils(appareil_1, 
			(t_appareil*) element)) {

			//cr�ation et insertion du disjoncteur dans la liste
			inserer(disjoncteur->ref_appareils,
				nouvel_appareil(categorie, emplacement, ampere, tension));

			//actualisation de la demande totale
			calculer_demande_totale(disjoncteur);

			//actualisation de l'�tat du disjoncteur
			tester_etat_disjoncteur(disjoncteur);
		}
	}
}