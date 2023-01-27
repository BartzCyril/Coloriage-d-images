/**
 * @file liste.h
 * @author BARTZ Cyril
 * @brief 
 * @version final
 * @date 2022-11-18
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef __List_H
#define __List_H

#define WHITE 0xFF

#include "utils.h"
#include "fonctions.h"

/*******************************************************/
/**********************List***************************/
/*******************************************************/

/**
 * @struct Object
 * @brief Cette structure représente un élément de la List
 */
typedef struct object {
    struct object *next; ///< pointeur sur le suivant de la List (le dernier pointe sur NULL)
    struct object *representative; ///< pointeur sur le représentant de la List 
    Pixel pixel; ///< Pixel RGB
}Object;

/**
 * @struct List
 * @brief Cette structure représente la List 
 */
typedef struct {
    Object *head; ///< pointeur tête qui représente le représentant
    Object *tail; ///< pointeur sur le dernier élement de la List
}List;

/**
 * @brief Créer une List vide
 * @return List* 
 */
List* newList();

/**
 * @brief Vacuité d'une List
 * 
 * @param l -> List
 * @return true 
 * @return false 
 */
bool isEmpty(List *l);

/**
 * @brief Cette fonction permet d'ajouter un élement à une List
 * @pre @code !isEmpty(l) && pixel ∉ ∀ List
 * @param l -> List
 * @param pixel -> Pixel
 * @return List* 
 */
List* addElement(List *l, Pixel pixel);

/**
 * @brief Retourne la taille de la List
 * @param l -> List
 * @return unsigned int 
 */
unsigned int sizeList(List *l);

/**
 * @brief Affiche une List
 * @pre @code !isEmpty(l)
 * @param l -> List
 */
void displayList(List *l);

/**
 * @brief Libère la mémoire de la List
 * @pre @code !isEmpty(l)
 * @param l -> List
 * @param freeListe -> si faux ne free que les objets de la liste
 */
void freeList(List *l, bool freeListe);

/*******************************************************/
/**********************StructTabList*********************/
/*******************************************************/

/**
 * @struct StructTabList
 * @brief Cette structure permet de stocker les Lists 
 */
typedef struct {
    List **array; ///< Tableau de List
    unsigned int size; ///< Taille courante du tableau
    unsigned int sizeMax; ///< Taille max du tableau (utilise pour realloc)
}StructTabList;

/**
 * @brief Allocation mémoire du tableau
 * @post @code Mémoire du tableau alouée
 * @param stdTabList -> StructTabList
 */
void newStructTabList(StructTabList *stdTabList);

/**
 * @brief Libération de la mémoire du tableau
 * @pre @code !isEmpty(stdTabList->array)
 * @post @code Mémoire du tableau libérée
 * @param stdTabList stdTabList -> StructTabList
 */
void freeStructTabList(StructTabList *stdTabList);

/*******************************************************/
/****************FONCTIONS PRINCIPALES******************/
/*******************************************************/

/**
 * @brief Créé un nouvel ensemble Sx , ne contenant que l'élément x. x est donc le
représentant de Sx
 * @pre @code pixel ∉ ∀ Tableau de List
 * @post @code Liste crée avec l'élement pixel puis ajouter dans le tableau de la structure StructTabList
 * @param pixel -> Pixel
 * @param stdTabList stdTabList -> StructTabList
 */
void MakeSetList(Pixel pixel, StructTabList*stdTabList);

/**
 * @brief Retourne un pointeur vers le représentant de l'ensemble contenant l'élément
 * @pre @code ∃ pixel && !isEmpty(stdTabList->array)
 * @post @code On obtient le représentant du pixel
 * @param stdTabList stdTabList -> StructTabList
 * @param pixel -> Pixel
 * @return Object* 
 */
Object* FindSetList(StructTabList*stdTabList, Pixel pixel);

/**
 * @brief Créé un nouvel ensemble Sxy , qui contient à la fois les éléments de l'ensemble
Sx dont le représentant est x et les éléments de l'ensemble Sy dont le représentant est y ,
et supprime les ensembles Sx et Sy . Précondition : les deux ensembles Sx et Sy doivent
être disjoints.
 * @pre @code !isEmpty(stdTabList->array) && (∃ p1 && ∃ p2) && !isEmpty(PixelRGB->array)
 * @post @code Création d'un nouvel ensemble avec la concaténation de l'ensemble qui contient l'élément p1 avec 
 * l'ensemble qui contient l'élément p2 et liberation de la mémoire.
 * @param stdTabList stdTabList -> StructTabList
 * @param p1 -> Pixel
 * @param p2 -> Pixel
 * @param PixelRGB -> PixelRGB
 */
void UnionList(StructTabList *stdTabList, Pixel p1, Pixel p2, PixelRGB *PixelRGB)  ;

/**
 * @brief Codez l'algorithme de coloriage automatique décrit en Section 3, pour une image
au format P BM ASCII. Cet algorithme doit générer une image au format P P M ASCII, et utiliser
les fonctions Read(), Write(), MakeSet(), FindSet() et Union() précédemment codées
 * @pre @code !isEmpty(stdTabList->array) && !isEmpty(PixelRGB->array) && !isEmpty(data->array) && le nom du fichier ∉ au reportoire /tests
 * @post @code Image au format ppm coloriée
 * @param stdTabList -> StructTabList
 * @param PixelRGB -> PixelRGB
 * @param data -> Data
 * @param file -> nom de l'image
 * @param isGenerate -> si faux image existe
 */
void AutomaticColoring(StructTabList *stdTabList, PixelRGB *PixelRGB, Data *data, bool isGenerate);

#endif