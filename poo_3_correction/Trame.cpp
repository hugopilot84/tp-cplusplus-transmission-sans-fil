#include "Trame.h"

#define NUL 0x00

Trame::Trame()
{
    trame[0] = NUL;
    strcpy(protocole, "<L1><PA><FE><MA><WC><FE>");
}

unsigned char Trame::calculerChecksum(char *trame)
{
    unsigned char checksum = 0;
    int i = 0;

#ifdef DEBUG_PANNEAU
    printf("data packet :\t");
    for (i = 0; i < (int)strlen(trame); i++)
        printf("0x%02X ", trame[i]);
    printf("\n");
#endif

    for (i = 0; i < (int)strlen(trame); i++)
        checksum ^= trame[i];
#ifdef DEBUG_PANNEAU
    printf("checksum :\t0x%02X\n", checksum);
#endif

    return checksum;
}

void Trame::construire(const char *message)
{
    unsigned char checksum;

    // 0. on ajoute le message dans l'en-tête du protocole
    sprintf(protocole, "%s%s", protocole, message);

    // 1. on calcule le checksum de la trame
    checksum = calculerChecksum(protocole);

    // 2. on fabrique la trame
    sprintf(trame, "<ID01>%s%02X<E>", protocole, checksum);
}