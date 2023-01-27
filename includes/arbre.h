/**
 * @file arbre.h
 * @author BARTZ Cyril
 * @brief 
 * @version final
 * @date 2022-11-18
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef __ARBRE_H
#define __ARBRE_H

#include "utils.h"
#include "../includes/fonctions.h"

/*******************************************************/
/**********************Arbre****************************/
/*******************************************************/

/**
 * @struct Node
 * @brief Cette structure représente un noeud 
 */
typedef struct strnode {
    Pixel pixel; ///< Pixel RGB
    unsigned int rank; ///< rang qui correspond à la borne supérieur de la hauteur du noeud dans l'arbre
    struct strnode* parent; ///< pointeur vers son parent
}Node;  

/**
 * @brief Créer un nouveau noeud
 * @post @code le noeud contient le pixel, avec comme rang 0 et comme parent lui même
 * @param pixel -> Pixel
 * @return Node* 
 */
Node* newNode(Pixel pixel);

/*******************************************************/
/**********************StructTabNode*********************/
/*******************************************************/

/**
 * @struct StructTabNode
 * @brief Cette structure permet de stocker les noeuds
**/
typedef struct {
    Node **array; ///< Tableau de Noeud
    unsigned int size; ///< Taille courante du tableau
    unsigned int sizeMax; ///< Taille max du tableau (utilise pour realloc)
}StructTabNode;

/**
 * @brief Allocation mémoire du tableau
 * @post @code Mémoire du tableau alouée
 * @param stdTabNode -> StructTabNode
 */
void newStructTabNode(StructTabNode *stdTabNode);

/**
 * @brief Libération de la mémoire du tableau
 * @pre @code !isEmpty(stdTabNode->array)
 * @post @code Mémoire du tableau libérée
 * @param stdTabNode -> StructTabNode
 */
void freeStructTabNode(StructTabNode *stdTabNode);

/*******************************************************/
/****************FONCTIONS PRINCIPALES******************/
/*******************************************************/

/**
 * @brief Créé un nouvel ensemble Sx , ne contenant que l'élément x. x est donc le
représentant de Sx
 * @pre @code pixel ∉ ∀ Tableau de noeud
 * @post @code Noeud crée avec l'élement pixel puis ajouter dans le tableau de la structure StructTabNode
 * @param pixel -> Pixel
 * @param stdTabNode -> StructTabNode
 */
void MakeSet(Pixel pixel, StructTabNode *stdTabNode);

/**
 * @brief Retourne un pointeur vers le représentant de l'ensemble contenant l'élément
 * @pre @code ∃ pixel && !isEmpty(stdTabNode->array)
 * @post @code On obtient le représentant du pixel
 * @param stdTabNode -> StructTabNode
 * @param pixel -> Pixel
 * @return Node* 
 */
Node* FindSet(Pixel pixel, StructTabNode *stdTabNode);

/**
 * @brief Créé un nouvel ensemble Sxy , qui contient à la fois les éléments de l'ensemble
Sx dont le représentant est x et les éléments de l'ensemble Sy dont le représentant est y ,
et supprime les ensembles Sx et Sy . Précondition : les deux ensembles Sx et Sy doivent
être disjoints.
 * @pre @code !isEmpty(stdTabNode->array) && (∃ p1 && ∃ p2)
 * @post @code Changement du pointeur d'un des parents
 * @param stdTabNode -> StructTabNode
 * @param p1 -> Pixel
 * @param p2 -> Pixel
 */
void Union(StructTabNode *stdTabNode, Pixel p1, Pixel p2);

/**
 * @brief Codez l'algorithme de coloriage automatique décrit en Section 3, pour une image
au format P BM ASCII. Cet algorithme doit générer une image au format P P M ASCII, et utiliser
les fonctions Read(), Write(), MakeSet(), FindSet() et Union() précédemment codées
 * @pre @code !isEmpty(stdTabNode->array) && !isEmpty(PixelRGB->array) && !isEmpty(data->array) && le nom du fichier ∉ au reportoire /tests
 * @post @code Image au format ppm coloriée
 * @param stdTabNode -> StructTabNode
 * @param PixelRGB -> PixelRGB
 * @param data -> Data
 * @param file -> nom du fichier
 * @param isGenerate -> -> si faux image existe
 */
void AutomaticColoringTree(StructTabNode *stdTabNode, PixelRGB *PixelRGB, Data *data, bool isGenerate);

#endif

