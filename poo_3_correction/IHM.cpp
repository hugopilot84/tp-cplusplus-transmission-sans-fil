#include "IHM.h"

#define NUL 0x00

IHM::IHM()
{
    strcpy(nomPort, PORT_DEFAUT);
    quitter = false;
}

IHM::~IHM()
{
}

// Lit une ligne au clavier et supprime le '\n' final
void IHM::saisirLigne(char *buffer, int taille)
{
    if (fgets(buffer, taille, stdin) == NULL)
    {
        buffer[0] = NUL;
        return;
    }

    // suppression du '\n' final
    int lg = strlen(buffer);
    if (lg > 0 && buffer[lg - 1] == '\n')
        buffer[lg - 1] = NUL;
    else
    {
        // la ligne était trop longue : on vide le tampon clavier
        int c;
        while ((c = getchar()) != '\n' && c != EOF)
            ;
    }
}

void IHM::afficherMenu()
{
    printf("\n");
    printf("========================================\n");
    printf("   Panneau Mc Crypte-590996 - BTS CIEL\n");
    printf("========================================\n");
    printf(" Port courant : %s\n", nomPort);
    printf("----------------------------------------\n");
    printf(" 1. Envoyer un message\n");
    printf(" 2. Modifier le port de communication\n");
    printf(" 3. Quitter\n");
    printf("----------------------------------------\n");
    printf(" Votre choix : ");
    fflush(stdout);
}

int IHM::lireChoix()
{
    char saisie[LG_MAX_PORT] = {NUL};

    saisirLigne(saisie, LG_MAX_PORT);

    if (saisie[0] == NUL)
        return -1;

    return atoi(saisie);
}

void IHM::envoyerMessage()
{
    char message[LG_MAX_MESSAGE] = {NUL};
    char reponse[LG_MAX_MESSAGE] = {NUL};
    char saisie[LG_MAX_PORT] = {NUL};
    int fd = -1;
    int retour;

    printf("\nMessage a afficher (%d caracteres max) : ", LG_MAX_MESSAGE - 1);
    fflush(stdout);
    saisirLigne(saisie, LG_MAX_PORT);

    if (saisie[0] == NUL)
    {
        printf("Message vide : envoi annule.\n");
        return;
    }

    if ((int)strlen(saisie) > LG_MAX_MESSAGE - 1)
    {
        printf("Message trop long : il sera tronque a %d caracteres.\n",
               LG_MAX_MESSAGE - 1);
    }

    strncpy(message, saisie, LG_MAX_MESSAGE - 1);
    message[LG_MAX_MESSAGE - 1] = NUL;

    // 0, 1, 2 : construction de la trame (message + protocole + checksum)
    // Remarque : un nouvel objet Trame est cree a chaque envoi car
    // construire() concatene le message a l'en-tete du protocole.
    Trame trame;
    PortSerie port;

    trame.construire(message);

    // 3.1 on ouvre le port
    fd = port.ouvrir(nomPort);
    if (fd == -1)
    {
        fprintf(stderr, "Erreur ouverture du port %s !\n", nomPort);
        return;
    }

    // 3.2 on envoie la trame
    retour = port.envoyer(trame.getTrame(), strlen(trame.getTrame()));
    if (retour == -1)
    {
        fprintf(stderr, "Erreur transmission !\n");
        port.fermer();
        return;
    }

    usleep(DELAI);

    // 3.3 on receptionne l'acquittement
    retour = port.recevoir(reponse, LG_REPONSE);
    if (retour < 1)
        fprintf(stderr, "Erreur reception : pas d'acquittement !\n");
    else
        printf("Reponse : %s\n", reponse);

    // 3.4 on ferme le port
    port.fermer();

    printf("Message \"%s\" envoye.\n", message);
}

void IHM::modifierPort()
{
    char saisie[LG_MAX_PORT] = {NUL};

    printf("\nPort actuel : %s\n", nomPort);
    printf("Nouveau port (Entree pour conserver) : ");
    fflush(stdout);
    saisirLigne(saisie, LG_MAX_PORT);

    if (saisie[0] == NUL)
    {
        printf("Port inchange : %s\n", nomPort);
        return;
    }

    strncpy(nomPort, saisie, LG_MAX_PORT - 1);
    nomPort[LG_MAX_PORT - 1] = NUL;

    printf("Nouveau port : %s\n", nomPort);
}

void IHM::executer()
{
    int choix;

    while (!quitter)
    {
        afficherMenu();
        choix = lireChoix();

        switch (choix)
        {
        case 1:
            envoyerMessage();
            break;

        case 2:
            modifierPort();
            break;

        case 3:
            quitter = true;
            printf("\nAu revoir.\n");
            break;

        default:
            printf("\nChoix invalide : saisir 1, 2 ou 3.\n");
            break;
        }
    }
}