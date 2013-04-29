#include "header.hpp"
#include <stdio.h>


// ne marche pas : il me faudrait un type paramétré?
// créer une instance paramétrée de la classe d'abord
// donc le code peut uniquement être inline?
// et je suppose que je peux juste utiliser un callback ou alors
// impl originale (mais il n'y en a pas si c'est un template...)
// et en plus il faut que je fasse un template de fonction static
//int Mother::method1(const T & param)
//{
//  printf("Mother::method1 appelée\n");
//}


// voyons si on peut repartir le template ds un fichier d'implementation separe
//ben non. En fait je dois donner ici le body de mes fonctions template
//et je ne peux pas me référer à l'

// imaginons que c'est le code généré par opmock pour un template

