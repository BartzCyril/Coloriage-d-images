#include "../includes/arbre.h"

Node *newNode(Pixel pixel)
{
    Node *n = malloc(sizeof *n);
    n->parent = n;
    n->pixel = pixel;
    n->rank = 0;
    return n;
}

void newStructTabNode(StructTabNode *stdTabNode)
{
    stdTabNode->size = 0;
    stdTabNode->sizeMax = SIZE_ARRAY_RGB_MAX;
    stdTabNode->array = (Node **)malloc(sizeof(Node *) * stdTabNode->sizeMax);
    if (stdTabNode->array == NULL)
        displayError("Erreur d'allocation du tableau", 0);
}

void freeStructTabNode(StructTabNode *stdTabNode)
{
    for (unsigned int i = 0; i < stdTabNode->size; i++)
    {
        free(stdTabNode->array[i]);
    }
    free(stdTabNode->array);
}

void MakeSet(Pixel pixel, StructTabNode *stdTabNode)
{
    Node *n = newNode(pixel);
    if (stdTabNode->size == stdTabNode->sizeMax)
    {
        stdTabNode->sizeMax += SIZE_ARRAY_RGB_MAX;
        stdTabNode->array = (Node **)realloc(stdTabNode->array, sizeof(Node *) * stdTabNode->sizeMax);
        if (stdTabNode->array == NULL)
            displayError("Erreur de reallocation du tableau", 0);
    }
    stdTabNode->array[stdTabNode->size] = n;
    stdTabNode->size++;
}

Node *FindSet(Pixel pixel, StructTabNode *stdTabNode)
{
    Node *n = stdTabNode->array[pixel.key];
    while (n->parent != n) {
        n = n->parent;
    }
    return n;
}

void Union(StructTabNode *stdTabNode, Pixel p1, Pixel p2) {
    Node* n1 = FindSet(p1, stdTabNode);
    Node* n2 = FindSet(p2, stdTabNode);
    if(n1 == n2) 
        return; // Ils ont le même représentant
    if (n1->rank > n2->rank)
        n2->parent = n1;
    else {
        n1->parent = n2;
        if (n1->rank == n2->rank)
            n2->rank++;
    }
}

void AutomaticColoringTree(StructTabNode *stdTabNode, PixelRGB *PixelRGB, Data *data, bool isGenerate)
{
    char file[100];
    printf("Entrez le nom du fichier (sans l'extension) : ");
    scanf("%s", file);
    if (isGenerate)
    {
        unsigned int column = 0;
        unsigned int row = 0;
        printf("Entrez le nombre de colonnes : ");
        scanf("%d", &column);
        printf("Entrez le nombre de lignes : ");
        scanf("%d", &row);
        // Génération du fichier
        Generate(row, column, file);
    }
    // Lecture du fichier
    Read(file, data);
    for (unsigned int i = 0; i < data->row_number; i++)
    {
        for (unsigned int j = 0; j < data->column_number; j++)
        {
            if (data->array[i][j].color[0] == WHITE)
            {
                MakeSet(generateColors(PixelRGB), stdTabNode); // Création des ensembles
            }
        }
    }
    // Union
    int i_bis;
    int j_bis;
    for (unsigned int i = 0; i < data->row_number; i++)
    {
        for (unsigned int j = 0; j < data->column_number; j++)
        {
            if (data->array[i][j].color[0] == WHITE)
            {
                i_bis = i - 1;
                j_bis = j - 1;
                if (j_bis > 0)
                { // gauche
                    if (data->array[i][j_bis].color[0] == WHITE)
                    {
                        Union(stdTabNode, PixelRGB->Colors[data->array[i][j].index - 1], PixelRGB->Colors[data->array[i][j_bis].index - 1]);
                    }
                }
                if (i_bis > 0)
                { // haut
                    if (data->array[i_bis][j].color[0] == WHITE)
                    {
                        Union(stdTabNode, PixelRGB->Colors[data->array[i][j].index - 1], PixelRGB->Colors[data->array[i_bis][j].index - 1]);
                    }
                }
                if (j + 1 != data->column_number)
                { // droite
                    if (data->array[i][j + 1].color[0] == WHITE)
                    {
                        Union(stdTabNode, PixelRGB->Colors[data->array[i][j].index - 1], PixelRGB->Colors[data->array[i][j + 1].index - 1]);
                    }
                }
                if (i + 1 != data->row_number)
                { // bas
                    if (data->array[i + 1][j].color[0] == WHITE)
                    {
                        Union(stdTabNode, PixelRGB->Colors[data->array[i][j].index - 1], PixelRGB->Colors[data->array[i + 1][j].index - 1]);
                    }
                }
            }
        }
    }

    // Coloriage de l'image
    for (unsigned int i = 0; i < data->row_number; i++)
    {
        for (unsigned int j = 0; j < data->column_number; j++)
        {
            if (data->array[i][j].color[0] == WHITE)
            {
                data->array[i][j] = FindSet(PixelRGB->Colors[data->array[i][j].index - 1], stdTabNode)->pixel;
            }
        }
    }
    // Création et écriture de l'image au format ppm
    Write(file, data);
}