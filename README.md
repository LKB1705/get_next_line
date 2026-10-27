<p align="center">
  <img src="https://img.shields.io/badge/42-Lausanne-black?style=for-the-badge&logo=42&logoColor=white" alt="42 Lausanne"/>
  <img src="https://img.shields.io/badge/langage-C-blue?style=for-the-badge&logo=c" alt="C"/>
  <img src="https://img.shields.io/badge/norminette-OK-success?style=for-the-badge" alt="Norminette"/>
</p>

*Ce projet a été créé dans le cadre du cursus de l'école 42 Lausanne par obohbot.*

# get_next_line

## Description

**get_next_line** est une fonction qui lit un descripteur de fichier et retourne **une ligne à chaque appel**, terminée par `\n` (sauf pour la dernière ligne si le fichier ne se termine pas par un retour à la ligne). Appelée en boucle, elle permet de lire un fichier ou l'entrée standard ligne par ligne, quelle que soit la taille des lignes.

Le projet fait découvrir les **variables statiques**, la **gestion de la mémoire dynamique** et la lecture bufferisée avec `read`.

```c
char *get_next_line(int fd);
```

**Valeur de retour :**

| Cas                                   | Retour                        |
|---------------------------------------|-------------------------------|
| Une ligne a été lue                   | La ligne, `\n` inclus         |
| Fin du fichier atteinte               | `NULL`                        |
| Erreur (fd invalide, échec de `read`, échec de `malloc`) | `NULL` |

## Instructions

### Prérequis

- Un compilateur `cc` (gcc ou clang)
- Les fichiers du projet : `get_next_line.c`, `get_next_line_utils.c`, `get_next_line.h`

### Compilation

La taille du buffer de lecture se définit à la compilation avec `BUFFER_SIZE` :

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c -o gnl
```

Le code doit fonctionner avec n'importe quelle valeur de `BUFFER_SIZE` (1, 42, 9999, 10000000…).

### Utilisation

```c
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "get_next_line.h"

int main(void)
{
    int     fd;
    char    *line;

    fd = open("fichier.txt", O_RDONLY);
    if (fd < 0)
        return (1);
    line = get_next_line(fd);
    while (line)
    {
        printf("%s", line);
        free(line);
        line = get_next_line(fd);
    }
    close(fd);
    return (0);
}
```

> La ligne retournée est allouée avec `malloc` : c'est à l'appelant de la libérer avec `free`.

### Structure du projet

```
get_next_line/
├── get_next_line.c
├── get_next_line_utils.c
├── get_next_line.h
└── README.md
```

> Si tu as fait la partie bonus, ajoute `get_next_line_bonus.c`, `get_next_line_utils_bonus.c` et `get_next_line_bonus.h`.

## Algorithme et choix techniques

### Principe général

1. Une **variable statique** (`static char *stash`) conserve entre deux appels les données déjà lues mais pas encore retournées.
2. À chaque appel, tant que le stash ne contient pas de `\n`, on lit `BUFFER_SIZE` octets avec `read` et on les ajoute au stash.
3. Dès qu'un `\n` est trouvé (ou que `read` retourne 0), on **extrait la ligne** du stash.
4. Le stash est **mis à jour** : on ne garde que ce qui suit la ligne extraite, pour l'appel suivant.
5. Quand il n'y a plus rien à lire ni à retourner, le stash est libéré et la fonction retourne `NULL`.

### Choix de conception

- **Variable statique** : seule façon (avec les contraintes du sujet, sans variable globale) de mémoriser l'état de lecture entre deux appels.
- **Lecture par blocs** : un seul `read` par itération, avec un buffer de taille `BUFFER_SIZE`, pour limiter les appels système sans lire tout le fichier d'un coup.
- **Aucune fuite mémoire** : chaque `malloc` est libéré dans tous les chemins, y compris en cas d'erreur de `read` ou d'allocation.
- **Fonctions utilitaires maison** : `ft_strlen`, `ft_strchr`, `ft_strjoin`, `ft_substr`/`ft_strdup` réécrites dans `get_next_line_utils.c`, car la `libft` n'est pas autorisée dans ce projet.
- **Cas limites gérés** : fichier vide, fichier sans `\n` final, lignes très longues, `BUFFER_SIZE` égal à 1, `fd` invalide (`-1`), lecture sur l'entrée standard.

### Bonus

La version bonus gère **plusieurs descripteurs de fichiers en parallèle** avec une seule variable statique : un tableau de stashs indexé par `fd` (`static char *stash[FD_MAX]`), ce qui permet d'alterner les lectures entre plusieurs fichiers sans perdre l'état de chacun.

## Tests

```bash
# Différentes tailles de buffer
cc -Wall -Wextra -Werror -D BUFFER_SIZE=1     *.c -o gnl && ./gnl
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42    *.c -o gnl && ./gnl
cc -Wall -Wextra -Werror -D BUFFER_SIZE=10000 *.c -o gnl && ./gnl

# Fuites mémoire
valgrind --leak-check=full ./gnl
```

Pistes de tests :

- Fichier vide, fichier d'une seule ligne, fichier sans `\n` final.
- Lignes vides consécutives (`\n\n\n`).
- Très longue ligne (plusieurs Mo).
- Lecture sur `stdin` (`./gnl < fichier.txt` ou saisie au clavier).
- `fd` invalide (`-1`, fd fermé).
- Bonus : alternance de lectures entre plusieurs fichiers.

Testeurs communautaires utiles : [Tripouille/gnlTester](https://github.com/Tripouille/gnlTester), [xicodomingues/francinette](https://github.com/xicodomingues/francinette).

## Ressources

### Documentation

- `man 2 read`, `man 2 open`, `man 3 malloc`, `man 3 free`
- [Variables statiques en C — cppreference](https://en.cppreference.com/w/c/language/storage_duration)
- [Norme de 42](https://github.com/42School/norminette)
- [Valgrind — documentation](https://valgrind.org/docs/manual/manual.html)

### Utilisation de l'IA

L'IA a été utilisée comme aide à la rédaction de ce README (structure et mise en forme). Le code, la conception et la logique du projet ont été réalisés et compris par l'auteur, conformément aux règles de l'école.

## Auteur

- **<votre_login>** — 42 Lausanne
