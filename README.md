# Trading Card Game : Yu-Gi-Oh!

Implémentation du jeu de carte Yu-Gi-Oh!

[Lien vers le cahier des charges](https://docs.google.com/document/d/1OeF_gmBVjo56tAUFRijaNlVDgjEvVVLkMJVCUVTZqDc/edit?usp=sharing), à completer.

:information_source: Libre à chacun d'éditer les fichiers

:information_source: Vous pouvez utiliser [GitKraken](https://www.gitkraken.com) pour suivre facilement les commits.

:warning: Mettez des commits à minima clairs

:warning: La cohérence du design sera mise en place progressivement, une fois les élements développés et stables. Attention toutefois à réutiliser les élements de GUI déjà réimplémentés le plus souvent possible, par soucis de cohérence (voir tableau ci-dessous).


## TODO List

#### Projet Général

 - [ ] Cahier des charges


#### Interface Générale

 - [ ] Yu-Gi-Oh style qss
 - [ ] Contraste-full style
 - [ ] Dyschromatopsia style
 - [ ] Traduction FR - EN


#### Menu Principal

 - [x] Écran de chargement
 - [x] Menu Principal
   - [ ] Menu Selection Jeu (Solo / Local / Online)
 - [ ] Indications (replace tooltip, everywhere)


#### Zone Duels

 - [ ] Interface Generale
    - [ ] Rotation Partie adverse + inversion
 - [ ] Gestion des parties
    - [ ] Solo
       - [ ] IA 1
    - [ ] Local
    - [ ] Online
 - [ ] Chargement des Decks
 - [ ] Chargement des cartes


#### Zone DeckBuild

 - [ ] DeckBuild
    - [ ] Liste des decks
      - [ ] Choix du deck courrant
      - [ ] Choix du deck adverse (a placer dans la zone de duel ?)
 - [ ] CarteBuild


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

