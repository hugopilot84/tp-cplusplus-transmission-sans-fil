#ifndef TRAME_H
#define TRAME_H

#include <stdio.h>
#include <string.h>

#define DEBUG_PANNEAU

#define LG_MAX_TRAME 128
#define LG_MAX 16

class Trame
{
public:
    Trame();

    void construire(const char *message);
    unsigned char calculerChecksum(char *trame);

    char *getTrame() { return trame; }

private:
    char trame[LG_MAX_TRAME];
    char protocole[LG_MAX_TRAME];
};

#endif