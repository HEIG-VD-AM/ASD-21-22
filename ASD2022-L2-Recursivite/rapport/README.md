# Rapport 

## Nombre de permutations

9 pièces et 4 orientations possibles, il y a donc au départ 9 × 4 = 36 possibilités de commencer le puzzle. Les possibilités diminuent de 4 à chaque profondeur.

<img  src="https://render.githubusercontent.com/render/math?math={\displaystyle \color{white}\prod_{k=0}^{8} (36 - 4k) = 36 \times 32 \times 28 \times \cdots \times 4 = 9.512681472 \times 10^{10}}#gh-dark-mode-only">

<img  src="https://render.githubusercontent.com/render/math?math={\displaystyle \prod_{k=0}^{8} (36 - 4k) = 36 \times 32 \times 28 \times \cdots \times 4 = 9.512681472 \times 10^{10}}#gh-light-mode-only">

(en cas de problème d'affichage la formule est la suivante : les 36-4k pour les k allant de 0 a 8, ce qui donne environ 95 milliards de permutations)

## Nombre d'appels récursifs
Notre algorithme a été fait de façon à élaguer les branches de l'arbre qui ne sont pas des solutions. C'est-à-dire que l'on place une pièce et on vérifie sa compatibilité avec le reste du jeu, s'il y a une erreur alors le plateau actuel n'est pas retenu comme solution viable.

De cette manière, nous avons réussi à créer un algorithme qui réalise extrêmement peu d'appels récursifs. Pour trouver toutes les solutions possibles, nous devons faire 3767 appels. Nous convergeons alors très rapidement vers les solutions en comparaison du nombre de permutations possibles.


## Slogan commercial vs réalité
Le slogan de Djeco est le suivant : "des millions de possibilités et une seule solution". Cependant, comme l'a prouvé le calcul du nombre de permutations possibles, il se trouve qu'il y a un peu plus de possibilités que ce qu'annonce Djeco.
Il y a en réalité 95 milliards de possibilités et non des millions, ce qui est tout de même une différence assez considérable.

Et pour le nombre de solutions possibles, la marque annonce une seule solution. La réalité étant qu'il en existe deux distinctes. Ce qui en fait huit en tout si l'on prend en compte la possibilité de faire tourner le jeu sur lui-même.
On peut retrouver l'ensemble des dispositions/solutions dans les listes ci-dessous.

- Première disposition : 
  - 1b 5d 4a 7a 6a 2a 8a 3a 9d
  - 8d 7d 1a 3d 6d 5c 9c 2d 4d
  - 9b 3c 8c 2c 6c 7c 4c 5b 1d
  - 4b 2b 9a 5a 6b 3b 1c 7b 8b


- Seconde disposition :
  - 1c 9a 6b 2a 4b 8b 7a 3a 5a
  - 6c 8c 5b 9b 4c 3b 1d 2b 7b
  - 5c 3c 7c 8d 4d 2c 6d 9c 1a
  - 7d 2d 1b 3d 4a 9d 5d 8a 6a

