#ifndef IHM_H
#define IHM_H

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <cstdlib>

#include "PortSerie.h"
#include "Trame.h"

#define PORT_DEFAUT "/dev/ttyUSB0"

#define LG_MAX_MESSAGE 16 // 15 caractères utiles + '\0'
#define LG_MAX_PORT 64
#define LG_REPONSE 4 // au maximum 4 caractères pour NACK

#define DELAI 1000000 // en micro secondes

class IHM
{
public:
    IHM();
    ~IHM();

    void executer(); // boucle principale du menu

private:
    // affichage
    void afficherMenu();
    int lireChoix();
    void saisirLigne(char *buffer, int taille);

    // actions du menu
    void envoyerMessage();
    void modifierPort();

    char nomPort[LG_MAX_PORT];
    bool quitter;
};

#endif
