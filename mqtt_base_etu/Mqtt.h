#ifndef MQTT_H
#define MQTT_H

#include <string>
#include <mqtt/async_client.h>

class Mqtt : public virtual mqtt::callback {
public:
    Mqtt(const std::string& ipBroker, int portBroker, const std::string& identifiant);
    ~Mqtt();

    bool connecter();
    void deconnecter();
    bool estConnecte();

    bool publier(const std::string& topic, const std::string& message);
    bool abonner(const std::string& topic);

private:
    void connection_lost(const std::string& cause);
    void message_arrived(mqtt::const_message_ptr message);

    mqtt::async_client client;
    mqtt::connect_options options;
};

#endif
