#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <string>

class Communication {
protected:
    bool ouvert;
public:
    Communication() : connecte(false) {}
    virtual ~Communication() {}
    virutal bool ouvrirPort() = 0;
    virtual void fermerPort() = 0;
    virtual void envoyer(const std::string& message) = 0;
    virtual std::string recevoir() = 0;
    virtual bool estOuvert() const { return connecte; }
};

#endif
