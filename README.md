# Trading Card Game : Yu-Gi-Oh!

Implémentation du jeu de carte Yu-Gi-Oh!

[Lien vers le cahier des charges](https://docs.google.com/document/d/1OeF_gmBVjo56tAUFRijaNlVDgjEvVVLkMJVCUVTZqDc/edit?usp=sharing), à completer.

:warning: Les descriptifs des fichiers .set et .deck ont été ajoutés ici.


## Actuellement en Zone Critique

 - [x] Création du type carte
 - [ ] Elaboration du système de "commandes de jeu" (ex: pour que la carte X attaque la carte Y ou que la carte X active son effet Y), avec code. En lien avec le tranzit de ces commandes sur le réseau.



## TODO List

#### Projet Général

 - [ ] Cahier des charges
 - [ ] Rapport


#### Interface Générale

 - [ ] Yu-Gi-Oh style qss
 - [ ] Contraste-full style
 - [ ] Dyschromatopsia style (http://jfly.iam.u-tokyo.ac.jp/color/#pallet)
 - [ ] Traduction FR - EN
 - [x] Indications Bar (Where-Am-I) dans les menus


#### Menu Principal

 - [x] Écran de chargement
 - [x] Menu Principal
   - [x] Menu de Selection du Mode de Jeu
   
 - [ ] Affichage des Paramètres (decks courrant + règles courrantes)


#### Zone Duels

 - [ ] Interface Generale
    - [ ] Slots de Cartes
       - [ ] Normaux
       - [ ] Monstres (atk/def)
       - [ ] Deck
    - [ ] Rotation Partie adverse
    - [ ] Zone Indications
       - [ ] Tour
       - [ ] Phase
       - [ ] Indication
       - [ ] Bouton "Passer la phase"
    - [ ] Zone "Carte en grand"
    - [ ] Popup sur certains élements
        - [ ] Confirmation lors de l'abandon
	- [ ] Affichage du cimetière
    
 - [ ] Chargement des Decks
 - [ ] Chargement des cartes
 
 - [ ] Communication/Slots Moteur - Terrain
 - [ ] Communication/Slots Terrain - Cartes
 
 - [ ] Gestion des parties
    - [ ] Solo
       - [ ] AI Random
       - [ ] AI Optimisation
       - [ ] Trained AI
    - [ ] Private Server
       - [ ] Créer
       - [ ] Rejoindre
    - [ ] Online MatchMaking


#### Zone DeckBuild

 - [ ] DeckBuild
    - [ ] Liste des decks
      - [ ] Choix du deck courrant
      - [ ] Choix du deck adverse (a placer dans la zone de duel ?)
      
 - [ ] Liste des cartes custom
    - [ ] Lien vers CarteBuild si liste vide
    
 - [ ] CarteBuild
    - [ ] Edition des cartes déjà créées


#### Zone Règles

 - [x] Sous-Zone Edition
    - [ ] Listage des règles modifiables
       - [ ] Main il/limitée
       - ... 
    - [ ] Création des règles modifiables
    
 - [x] Sous-Zone "Lire les règles officielles"


#### Zone Paramètres

 - [x] Enlever "A Propos"
 - [ ] Zone "Raccourcis"


#### Zone Aide

   - [x] Rajout "A Propos"
   - [ ] Création de l'aide (help.text)



## Elements de GUI réimplémentés

Nom de la classe | Remplace/Améliore | Descriptif
---------------- | ----------------- | ----------
ShadowButt | QPushButton | Rajoute des effets d'ombrage



## Description des fichiers 

#### Extensions de cartes .set 

Autant de cartes que l'on veut dans un fichier

```
##YGO (separe 2 cartes)
ID_CARTE (custom negatif) INTEGER
(SET) (extention) (set custom) INTEGER //plus necessaire 
GENRE_CARTE (0 monstre / 1 magie / 2 piege) INTEGER
SOUS_TYPE (FUSION / RITUEL / EQUIPEMENT... numero par ordre alphabetique ) INTEGER
NOM_CARTE STRING
ATTRIBUT terre / lumiere.. INTEGER
NIVEAUX (1 - 12) (que les cartes monstres, les petites étoiles) INTEGER
(IMAGE) ====> inutile car nr SET + ID identifie de manière unique l'image
	(set = repertoire, ID = nom, ex: ./pic/set/id.png)
TYPE (rocher, démon, elfe...) INTEGER
DESCRIPTION (texte purement visuel) STRING
EFFET effet separé par {{ , fin d'effet}} INTEGER
	exemple : {{effet 1 {{ effet 2 {{ effet 3 
ATK (min: 0) INTEGER
DEF (min: 0) INTEGER
HASH (anti corruption) STRING
##YGO
```

#### Decks de cartes .deck

```
NOM_DU_DECK
#main_deck
ID_CARD1 INTEGER
ID_CARD2
....
minimum 40 Cartes max 60
....
#extra_deck
....
minimum 0 Cartes max 15
....
```

## Description du Terrain (field)

```
89 ---- 149 : main adverse
82 - 88     : magie adverse
75 - 81     : monstre adverse
-------------
00 - 06     : monstre self
07 - 13     : magie self
14 ---- 074 : main self
```


## Elements Optionnels Interessants/WTF

:information_source: Ces élements ne sont à prendre en compte qu'une fois les fonctionnalités principales implémentées.

 - [ ] Environnement sonore
    - [ ] Option de désactivation des élements sonores
 - [ ] Remplacement des tooltips
 - [ ] Chats lors des parties Online
 
 

