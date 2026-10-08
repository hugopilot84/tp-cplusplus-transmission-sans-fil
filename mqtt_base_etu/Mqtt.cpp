#include "Mqtt.h"
#include <iostream>

Mqtt::Mqtt(const std::string& ipBroker, int portBroker, const std::string& identifiant)
    : client("tcp://" + ipBroker + ":" + std::to_string(portBroker), identifiant)
{
    options.set_clean_session(true);
    options.set_keep_alive_interval(20);
    client.set_callback(*this);
}

Mqtt::~Mqtt()
{
    deconnecter();
}

bool Mqtt::connecter()
{
    try {
        client.connect(options)->wait();
        return true;
    } catch (const mqtt::exception& erreur) {
        std::cerr << "ERREUR : connexion broker : " << erreur.what() << std::endl;
        return false;
    }
}

void Mqtt::deconnecter()
{
    try {
        if (client.is_connected()) {
            client.disconnect()->wait();
        }
    } catch (const mqtt::exception& erreur) {
        std::cerr << "ERREUR : deconnexion : " << erreur.what() << std::endl;
    }
}

bool Mqtt::estConnecte()
{
    return client.is_connected();
}

bool Mqtt::publier(const std::string& topic, const std::string& message)
{
    try {
        client.publish(topic, message.c_str(), message.size(), 1, false)->wait();
        return true;
    } catch (const mqtt::exception& erreur) {
        std::cerr << "ERREUR : publication sur " << topic << " : " << erreur.what() << std::endl;
        return false;
    }
}

bool Mqtt::abonner(const std::string& topic)
{
    try {
        client.subscribe(topic, 1)->wait();
        return true;
    } catch (const mqtt::exception& erreur) {
        std::cerr << "ERREUR : abonnement a " << topic << " : " << erreur.what() << std::endl;
        return false;
    }
}

void Mqtt::connection_lost(const std::string& cause)
{
    std::cerr << "ERREUR : connexion perdue : " << cause << std::endl;
}

void Mqtt::message_arrived(mqtt::const_message_ptr message)
{
    std::cout << "Recu sur " << message->get_topic() << " : " << message->to_string() << std::endl;
}
