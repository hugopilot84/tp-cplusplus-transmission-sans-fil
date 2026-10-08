#include "PortSerie.h"

PortSerie::PortSerie()
{
    fd = -1;
}

PortSerie::~PortSerie()
{
    // Le port est fermé dans la fonction main(). On aurait pu le fermer ici, à la destruction de l'objet.
}

// Lire: http://ftp.lip6.fr/pub/linux/french/echo-linux/html/ports-series/ports_series.html
int PortSerie::ouvrir(char *nomPort)
{
    struct termios termios_p;

#ifdef DEBUG_PANNEAU
    fprintf(stderr, "Ouverture du port %s\n", nomPort);
#endif

    // cf. man 2 open
    if ((fd = open(nomPort, O_RDWR | O_NONBLOCK)) == -1)
    {
        perror("open");
        return fd;
    }

    // cf. man tcgetattr
    tcgetattr(fd, &termios_p);

    // configuration du port série : 9600 bits/s, 8 bits, pas de parité
    // remarque : les caractères BREAK et ceux qui comportent une erreur de parité sont ignorés
    termios_p.c_iflag = IGNBRK | IGNPAR;
    // rien de particulier à faire pour l'envoi des caractères
    termios_p.c_oflag = 0;
    // 9600 bits/s, 8 bits, pas de parité
    termios_p.c_cflag = B9600 | CS8;
    termios_p.c_cflag &= ~PARENB;

    // pas d'écho des caractères reçus
    termios_p.c_lflag = ~ECHO;
    // spécifie le nombre de caractéres que doit contenir le tampon pour être accessible à la lecture
    // En général, on fixe cette valeur à 1
    termios_p.c_cc[VMIN] = 1;
    // spécifie en dixièmes de seconde le temps au bout duquel un caractère devient accessible,
    // même si le tampon ne contient pas [VMIN] caractères
    // Une valeur de 0 représente un temps infini.
    termios_p.c_cc[VTIME] = 0;

    // cf. man tcsetattr
    tcsetattr(fd, TCSANOW, &termios_p);

    // cf. man 2 fcntl
    // mode bloquant ?
    // fcntl(fd, F_SETFL, fcntl(fd,F_GETFL)&~O_NONBLOCK);

    return fd;
}

void PortSerie::fermer()
{
    // cf. man 2 close
    close(fd);
}

int PortSerie::envoyer(char *trame, int nb)
{
    int retour = -1;

    if (fd > 0)
    {
        // cf. man 2 write
        retour = write(fd, trame, nb);

#ifdef DEBUG_PANNEAU
        // debug : affichage
        fprintf(stderr, "-> envoyer (%d/%d) : ", nb, retour);
        // fprintf(stderr, "trame : ");
        /*int i;
        for(i=0;i<nb;i++)
        {
            fprintf(stderr, "0x%02X ", *(trame+i));
        }
        fprintf(stderr, "\n");*/
        fprintf(stderr, "%s\n", trame);
#endif
        if (retour == -1)
        {
            perror("write");
        }
    }
    else
    {
#ifdef DEBUG_PANNEAU
        // debug : affichage
        fprintf(stderr, "-> envoyer (%d) : ERREUR port !\n", nb);
        fprintf(stderr, "trame : ");
        /*int i;
        for(i=0;i<nb;i++)
        {
            fprintf(stderr, "0x%02X ", *(trame+i));
        }
        fprintf(stderr, "\n");*/
        fprintf(stderr, "%s\n", trame);
#endif
        retour = fd;
    }

    return retour;
}

int PortSerie::recevoir(char *donnees, int nb)
{
    int retour;
    char donnee;
    int lus = 0;

    if (fd > 0 && donnees != (char *)NULL)
    {
        if (nb > 0)
        {
            for (lus = 0; lus < nb; lus++)
            {
                // cf. man 2 read
                retour = read(fd, &donnee, 1);
                if (retour > 0)
                    *(donnees + lus) = donnee;
                else
                {
                    /*if (retour == -1)
                    {
                        perror("read");
                    }*/
                    break;
                }
            }
            if (nb == lus && nb > 1)
                *(donnees + lus) = 0x00; // fin de chaine
            retour = lus;
#ifdef DEBUG_PANNEAU
            int i;
            fprintf(stderr, "<- recevoir (%d/%d) : ", nb, lus);
            // fprintf(stderr, "trame : ");
            for (i = 0; i < lus; i++)
                fprintf(stderr, "0x%02X ", *(donnees + i));
            fprintf(stderr, "\n");
#endif
        }
        else
        {
        }
    }
    else
        retour = fd;

    return retour;
}