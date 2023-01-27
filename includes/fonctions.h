/**
 * @file fonctions.h
 * @author BARTZ Cyril
 * @brief 
 * @version final
 * @date 2022-10-25
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef __FONCTIONS_H
#define __FONCTIONS_H

#include "utils.h"

#define SIZE_ARRAY_RGB_MAX 800
#define WHITE 0xFF
#define BLACK 0x00
/**
 * @brief Fonction qui renvoie un message d'erreur
 *
 * @param msg -> le message d'erreur
 * @param ErrorCode -> code d'erreur
 */
void displayError(char *msg, unsigned int ErrorCode);

/**
 * @struct Pixel
 * @brief Cette structure contient un tableau contenant un pixel de couleur RGB
 *
 */
typedef struct
{
    unsigned int color[3]; ///< Tableau contenant un pixel de couleur RGB
    unsigned int index; ///< indice dans le tableau PixelRGB
    unsigned int key; ///< indice dans le tableau de listes
}Pixel;

/**
 * @struct Data
 * @brief Cette structure permet de stocker les pixels
 * de l'image dans un tableau bidimensionnel
 *
 */
typedef struct
{
    unsigned int row_number;    ///< nombre de lignes
    unsigned int column_number; ///< nombre de colonnes
    Pixel **array;              ///< tableau contenant les pixels noir et blanc d'une image
    char *name_file;            ///< nom du fichier d'une image
}Data;

/**
 * @struct PixelRGB
 * @brief Cette structure permet de stocker les couleurs
 * qui sont déjà utilisé par la fonction MakeSet
 *
 */
typedef struct
{
    Pixel *Colors; ///< Tableau contenant les pixels de couleurs
    unsigned int size; ///< Le nombre d'éléments dans le tableau
    unsigned int sizeMax; ///< Taille max définit pour l'instant sur 800 mais évolue en fonction du nombre de pixels blanc de l'image
}PixelRGB;

/**
 * @brief Cette fonction permet d'allouer dynamiquement la mémoire du tableau bidimensionnel
 *
 * @param data -> Data 
 * @param row_number
 * @param column_number
 */
void mallocArray(Data *data, unsigned int row_number, unsigned int column_number);

/**
 * @brief Question 1
 * Cette fonction lit une image au format PBM et
 * stocke ses pixels dans un tableau bidimensionnel
 * @pre @code le fichier qu'on lit ne doit pas être présent au format ppm
 * @post @code Tableau à 2 dimensions contenant les pixels de l'image au format PBM
 * @param file l'image au format pbm
 * @param data -> Data
 */
void Read(char *file, Data *data);

/**
 * @brief Question 2
 * Cette fonction génère une image au format PPM à partir d'un tableau
 * bidimensionnel de pixels de couleurs
 * @pre @code !vide(data->array)
 * @post @code Genere une image au format ppm
 * @param data -> Data
 * @param file -> nom du fichier
 */
void Write(char* file, Data *data);

/**
 * @brief Question 3
 * Cette fonction permet de génerer une image
 * aléatoire au format PBM
 * @pre @code (row_number && column_number > 0) && !∃ nom du fichier
 * @post @code Créer une image au format pbm aléatoirement
 * @param row_number
 * @param column_number
 * @param name nom du fichier à générer
 */
void Generate(unsigned int row_number, unsigned int column_number, char *name);

/**
 * @brief Cette fonction libère la mémoire du tableau bidimensionnel
 *
 * @param data -> Data
 */
void freeArray(Data *data);

/**
 * @brief Cette fonction alloue la mémoire du tableau contenant toutes les couleurs utilisées
 *
 * @param PixelRGB -> PixelRGB
 */
void newPixelRGB(PixelRGB *PixelRGB);

/**
 * @brief Cette fonction renvoie un pixel RGB aléatoirement
 * @code @post Obtenir un nouveau pixel
 * @return Pixel
 */
Pixel newPixel();

/**
 * @brief Cette fonction permet de générer une couleur qui n'est pas présente dans le tableau
 * @code @pre !vide(data->array)
 * @code @post Ajout d'un pixel RGB non présent dans le tableau
 * @param PixelRGB -> PixelRGB
 * @return Pixel
 */
Pixel generateColors(PixelRGB *PixelRGB);

#endif