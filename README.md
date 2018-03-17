# Trading Card Game : Yu-Gi-Oh!

Implémentation du jeu de carte Yu-Gi-Oh!

[Lien vers le cahier des charges](https://docs.google.com/document/d/1OeF_gmBVjo56tAUFRijaNlVDgjEvVVLkMJVCUVTZqDc/edit?usp=sharing), à completer.

:information_source: Vous pouvez utiliser [GitKraken](https://www.gitkraken.com) pour suivre facilement les commits.

:warning: La cohérence du design sera mise en place progressivement, une fois les élements développés et stables. Attention toutefois à réutiliser les élements de GUI déjà réimplémentés le plus souvent possible, par soucis de cohérence (voir tableau ci-dessous).


## Actuellement en Zone Critique

 - [x] Création du type carte
 - [ ] Elaboration du système de "commandes de jeu" (ex: pour que la carte X attaque la carte Y ou que la carte X active son effet Y), avec code. En lien avec le tranzit de ces commandes sur le réseau.



## TODO List

#### Projet Général

 - [ ] Cahier des charges


#### Interface Générale

 - [ ] Yu-Gi-Oh style qss
 - [ ] Contraste-full style
 - [ ] Dyschromatopsia style
 - [ ] Traduction FR - EN
 - [ ] Indications Bar (Where-Am-I) dans les menus
 - [ ] Replace tooltip ?


#### Menu Principal

 - [x] Écran de chargement
 - [x] Menu Principal
   - [ ] Menu de Selection du Mode de Jeu
 - [ ] Affichage des Paramètres (decks courrant + règles courrantes)


#### Zone Duels

 - [ ] Interface Generale
    - [ ] Rotation Partie adverse
    - [ ] Confirmation lors de l'abandon
 - [ ] Gestion des parties
    - [ ] Solo
       - [ ] IA Random
       - [ ] IA Optimisation
       - [ ] Trained IA
    - [ ] Private Server
       - [ ] Créer
       - [ ] Réjoindre
    - [ ] Online MatchMaking
 - [ ] Chargement des Decks
 - [ ] Chargement des cartes


#### Zone DeckBuild

 - [ ] DeckBuild
    - [ ] Liste des decks
      - [ ] Choix du deck courrant
      - [ ] Choix du deck adverse (a placer dans la zone de duel ?)
 - [ ] Liste des cartes custom
 - [ ] CarteBuild
    - [ ] Edition des cartes déjà créées


#### Zone Règles

 - [x] Sous-Zone Edition
    - [ ] Listage des règles modifiables
    - [ ] Création des règles modifiables
 - [x] Sous-Zone "Lire les règles officielles"


#### Zone Paramètres

 - [x] Enlever "A Propos"
 - [ ] Deplacement "Raccourcis"


#### Zone Aide

   - [x] Rajout "A Propos"
   - [ ] Création de l'aide (help.text)



## Elements de GUI réimplémentés

Nom de la classe | Remplace/Améliore | Descriptif
---------------- | ----------------- | ----------
ShadowButt | QPushButton | Rajoute des effets d'ombrage



## Elements Optionnels Interessants/WTF

:information_source: Ces élements ne sont à prendre en compte qu'une fois les fonctionnalités principales implémentées.

 - [ ] Environnement sonore
    - [ ] Option de désactivation des élements sonores
 

