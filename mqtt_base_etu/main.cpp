#include "Mqtt.h"
#include <iostream>

// Compilation : g++ -std=c++11 -pthread main.cpp Mqtt.cpp -lpaho-mqttpp3 -lpaho-mqtt3a -o monPublisher

int main(int argc, char** argv)
{
    if (argc < 3) {
        std::cerr << "Usage : " << argv[0] << " <topic> <message>" << std::endl;
        return 1;
    }

    std::string topic = argv[1];
    std::string message = argv[2];

    Mqtt mqtt("127.0.0.1", 1883, "publisher");

    if (!mqtt.connecter()) {
        return 1;
    }

    if (!mqtt.publier(topic, message)) {
        return 1;
    }

    std::cout << "Publie sur " << topic << " : " << message << std::endl;
    return 0;
}
