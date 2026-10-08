#ifndef PORTSERIE_H
#define PORTSERIE_H

#include <termios.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/signal.h>
#include <fcntl.h>

#define DEBUG_PANNEAU

class PortSerie
{
public:
    PortSerie();
    ~PortSerie();

    int ouvrir(char *nomPort);
    void fermer();
    int envoyer(char *trame, int nb);
    int recevoir(char *donnees, int nb);

    int getFd() const { return fd; }

private:
    int fd;
};

#endif