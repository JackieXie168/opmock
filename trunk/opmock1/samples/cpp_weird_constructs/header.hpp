#ifndef _TRUC_H
#define _TRUC_H

#include <stdio.h>
#include <iostream>

// some template and template inheritance
template <class T>
class opmock_Mother
{
public:
  int method1(const T & param) {
    printf("opmock_mother::method1\n");
    return 1;
  }
  char method2(const T & param2) {
    printf("opmock_mother::method2\n");
    return 'x';
  }
};

template <class T>
class Mother : public opmock_Mother<T>
{

public:
  int machin;

  int method1(const T & param) {
    printf("appel template Mother::method1\n");

    // If I want to call the super class template
    // (call original impl)
    int res = opmock_Mother<T>::method1(param);
    printf("resultat appel classe mere %d\n", res);
    return res;
  }
  char method2(const T & param2) {
     printf("appel template Mother::method2\n");
     return 'z';
  }

  // call a templated callback function
  void template_callback(int param1, T param2)
  {
    callback2(param1, param2, this, 1);
  }
};

// callback est aussi fonction template pour recevoir les
// arguments. Probleme : normalement il doit etre défini dans le même fichier
// que le template pour que je puisse l'utiliser... Dans pas dans le corps du test.
// la classe peut stocker un pointeur sur la fonction template
// via un typedef?
template <typename T>
static void callback2(int param1, T param2, Mother<T> *ptr, int calls)
{
  ptr->machin = 77;
  std::cout << "param1 " << param1 << " param2 " << param2 << std::endl;
}


class Truc;

static void callback_1(int param, Truc * ref);

class Truc
{
public:
  int attrib;

  // can't use static here as I work with an instance
  // which means of course that I need first to have a pointer
  // on the class instance... Not always possible!
  void methode1_callbackWithInstance(int param) {
    callback_1(param, this);
  }

  static void methode1_callback(int param) {
  }
};

static void callback_1(int param, Truc * ref)
{
  ref->attrib = 1;//side effect

  // let's see if I can get a pointer on an instance attribute
  // yes I can. So I should be able to get a pointer
  // even on an attribute allocated "on the stack"
  // like MyClass class;
  // then set it's callback, provided that the class is stubbed.
  int * ptr = &(ref->attrib);
  *ptr = 2;//change the value!
}

//static void callback_noRef(int param)
//{
  // do something, return a value, but no side effect
  // on the class
//}


// doit etre ds le meme fichier header
// pose pb car je dois modifier le fichier header original dans ce cas?

//TODO en fait pour les classes il vaut peut etre mieux
//ne faire que des methodes d'instance et laisser tomber les méthodes statiques
//mais ds ce cas ca n'affecte pas toutes les instances... Ca peut etre utile pour
//des operations ou l'effet de bord sur la classe ne nous intéresse pas.
#endif
