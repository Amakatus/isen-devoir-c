C-search est un projet développé en langage C, permettant de réaliser des recherches dans des fichiers texte en utilisant différentes méthodes de recherche telles que la recherche exacte, la recherche insensible à la casse, et la recherche avec joker. Il a été fait dans le cadre d'un devoir-maison pour le cours d'algorithmie-C.

**Fonctionnalités principales**

* Recherche exacte : Recherche d'un mot dans un fichier (attention aux majuscules !).
* Recherche insensible à la casse : Recherche d'un mot, sans tenir compte des majuscules.
* Recherche avec joker (un peu buggé) : Recherche d'un mot partiel, en utilisant le caractère générique `*`, ce qui permets de rechercher des mots dont une partie est inconnu.

**Bugs connus** 

* Recherche avec joker devant le mot : la wildcard `*`, ne marche pas bien dans le cas où l'on met par exemple "*Bon", cela renvoie tous les mots du texte. Je ne sais pas trop pourquoi et je n'arrive pas à trouver la solution.

**Installation**

Clonez ce projet dans un répertoire de votre choix :

```bash
git clone https://github.com/Amakatus/isen-devoir-c.git
cd isen-devoir-c
```

Installer les dépendances et préparer le projet avec Meson  :dizzy: :

Si vous n'avez pas encore installé Meson et Ninja, vous pouvez les installer via pacman ou en suivant la documentation officielle de Meson :

```bash 
sudo pacman -S meson
sudo pacman -S ninja-build
```

Construire le projet :

Créez un répertoire de construction et compilez le projet :

```bash
meson setup build
meson compile -C build
```

Exécuter le programme :

Après la compilation, vous pouvez exécuter l'application avec la commande suivante (sans oublier le dossier):

```bash
./build/c-search dossier_de_votre_choix
```