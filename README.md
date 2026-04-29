🤖 PROJET DE ROBOTIQUE : THE SHOW MUST GO ON
Ce dépôt contient le code source complet d'un robot mobile piloté par une manette PS2, équipé d'un système de pinces motorisées et d'un affichage de score en temps réel.


📋 Présentation du projet
Le robot est piloté par un Arduino qui fait l'interface entre plusieurs composants critiques :
Déplacement : Un contrôleur de moteur Sabertooth gérant deux moteurs en mode différentiel.  
Contrôle : Une manette PlayStation 2 via le shield Cytron PS2.  
Affichage : Un écran Grove Alphanumeric pour le suivi des points. 
Mécanismes : Des pinces motorisées avec capteurs de fin de course pour la sécurité.  


🛠️ Matériel Requis
Microcontrôleur : Arduino (ou CT-UNO).  
Shield PS2 : Cytron PS2 Shield.  
Driver Moteur : Sabertooth (en mode Simplified Serial). 
Affichage : Grove Quad Alphanumeric Display (HT16K33).  
Manette : DualShock 2 sans fil ou filaire.  


🎮 Commandes de la manette
Le robot réagit aux commandes suivantes :


🚀 Déplacement (Joystick Gauche)
Haut / Bas : Avancer ou reculer.  
Gauche / Droite : Rotation sur place.  
Bouton R1 : Modificateur de vitesse (permet un contrôle plus précis).  


🏗️ Mécanismes (Pinces & Levage)
Joystick Droit (Axe Y) : Faire monter ou descendre les pinces.  
Bouton L2 / R2 : Ouverture et fermeture des pinces.  
Sécurité : Le mouvement vertical s'arrête automatiquement via des interruptions matérielles dès que les capteurs de fin de course sont activés.  


🔢 Gestion du Score
Triangle / Croix : Ajouter ou retirer 10 points. 
Rond / Carré : Ajouter ou retirer 1 point.  
Le score est instantanément mis à jour sur l'afficheur numérique.  


📂 Structure du programe
CodeRobot_V4_orange.ino : Le script principal (cerveau du robot) qui contient la boucle de contrôle et la gestion des interruptions. 
Cytron_PS2Shield : Bibliothèque pour la communication avec la manette.  
SabertoothSimplified : Bibliothèque simplifiée pour l'envoi de commandes aux moteurs.  
grove_alphanumeric_display : Pilote pour l'affichage LED I2C.  

