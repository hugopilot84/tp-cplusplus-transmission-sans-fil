#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <string>

class Communication {
protected:
    bool connecte;
public:
    Communication() : connecte(false) {}
    virtual ~Communication() {}

    virtual void envoyer(const std::string& message) = 0;
    virtual void recevoir(std::string& message) = 0;
    virtual bool estConnecte() const { return connecte; }
};

#endif
