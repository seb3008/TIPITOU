/*
* Module utilitaire de sous-programmes fournis
* dans le cadre du tp3 inf1145 A16 (voir �nonc�)
*
* Auteur : Pierre B�lisle (Copyright 2016).
*/

// Votre module du tp2.
#include "t_boite.h"

// D�clenche l'ajout d'un disjoncteur dans la bo�te.
void ajouter_disjoncteur(t_boite* boite);

// D�clenche la sauvegarde d'une bo�te dans un fichier binaire.
void sauvegarder_boite(const t_boite* boite);

// D�clenche la r�cup�ration d'une bo�te d'un fichier binaire
// et remplit la boite re�u en param�tre, par r�f�rence.
void recuperer_boite(t_boite* boite);

// Permet l'utilisateur de retirer un disjoncteur de la bo�te.
void retirer_disjoncteur(t_boite* boite);