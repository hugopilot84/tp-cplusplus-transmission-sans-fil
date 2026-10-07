# tp-cplusplus-transmission-sans-fil
Séquence 1 - Mise en oeuvre d’un panneau lumineux   Séance 4 - Communication sur IP


Compétences développés et activités réalisés : 

C06 - Valider un système informatique
D2 - Développement et validation de solution logicielle
C08 - Coder
R3 - Exploitation et maintien en condition opérationnelle
C10 - Exploiter un réseau informatique
T6 - Intégration de nouveaux équipements


Ressources : 
Cours UML
Cours POO
Cours POO en C++
Diagramme de classes à utiliser
Programme de contrôle du panneau en langage C

Mise en situation : 
En magasin de composants informatique a acheté un panneau lumineux pour afficher dynamiquement des informations en vitrine. Vous êtes chargé de sa mise en œuvre et du développement d’un logiciel de commande. Le développement orienté objet à été réalisé avec un contrôle filaire.
Pour plus de flexibilité, il est demandé de passer à une commande sans fil. N’importe quel protocole IP pourra être utilisé pour exploiter la liaison Wi-Fi. Il est décidé d’utiliser le protocole MQTT, flexible et pensé pour les objets connectés.

Le but de cette séance est de développer un programme de contrôle du panneau lumineux en C++ via MQTT. Le panneau est abonné via un broker MQTT à un topic sur lequel peut être publié du texte et à un topic sur lequel peut être publié des trames brutes : 
panneau/texte;
panneau/trame.

Une proposition de correction pour la séance 3 est proposée en fichier joint.


Généralisation et spécialisation

Il existe déjà dans votre code une classe permettant de communiquer avec l’extérieur de la machine : PortSerie. 

Plusieurs membres de PortSerie peuvent servir à la communication de manière générale sans être spécifique au port série.
