# Trading Card Game : Yu-Gi-Oh!

Implémentation du jeu de carte Yu-Gi-Oh!

[Lien vers le cahier des charges](https://docs.google.com/document/d/1OeF_gmBVjo56tAUFRijaNlVDgjEvVVLkMJVCUVTZqDc/edit?usp=sharing), à completer.

:warning: Dernière semaine avant rendu !


## TODO List

#### 4rk

 - [ ] Cahier des charges -> Rapport
 - [ ] QSS Polishing
 - [ ] Contraste-full style
 - [ ] Dyschromatopsia style (http://jfly.iam.u-tokyo.ac.jp/color/#pallet)
 - [ ] Popups 1 & 2
 - [ ] Bouton deck edit
 - [ ] Création de l'aide (help.text)


#### Vect

 - [ ] Fin Noyau de base (combat)
 - [ ] Click Cimetiere / Fusion deck --> popup si non vide


#### Chop1

 - [ ] Fin card + deck Editor
 - [ ] Set du Deck courrant
 - [ ] Liste des cartes (customs)


#### Lucas

 - [ ] Connexion IA / Noyau
 - [ ] Lancement des parties IA


#### Mathieu

 - [ ] Fin racc. clavier
 - [ ] Fin traduction
 - [ ] Compile .exe windows
 - [ ] Compile .desktop Linux


## Description des fichiers 

#### Extensions de cartes .set 

Autant de cartes que l'on veut dans un fichier

```
##YGO (separe 2 cartes)
ID_CARTE (custom negatif) INTEGER
GENRE_CARTE (0 monstre / 1 magie / 2 piege) INTEGER
SOUS_TYPE (FUSION / RITUEL / EQUIPEMENT... numero par ordre alphabetique ) INTEGER
NOM_CARTE STRING
ATTRIBUT terre / lumiere.. INTEGER
NIVEAUX (1 - 12) (que les cartes monstres, les petites étoiles) INTEGER
TYPE (rocher, démon, elfe...) INTEGER
DESCRIPTION (texte purement visuel) STRING
EFFET effet separé par {{ , fin d'effet}} INTEGER
    exemple : {{effet 1 {{ effet 2 {{ effet 3 
ATK (min: 0) INTEGER
DEF (min: 0) INTEGER
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
 - [ ] Remplacement des tooltips par zone dédiée
 - [ ] Modification du jeu pour profiter de l'aspect dématérialisé
 
 

