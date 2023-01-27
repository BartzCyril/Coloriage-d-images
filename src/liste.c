#include "../includes/liste.h"

List *newList()
{
    List *l = malloc(sizeof *l);
    if (l == NULL)
        displayError("Erreur d'allocation mémoire", 0);
    l->head = 0;
    l->tail = 0;
    return l;
}

List *addElement(List *l, Pixel pixel)
{
    Object *new = malloc(sizeof *new);
    if (new == NULL)
        displayError("Erreur d'allocation mémoire", 0);
    new->pixel = pixel;
    new->next = NULL;
    if (isEmpty(l))
    {
        new->representative = new;
        l->head = new;
        l->tail = new;
    }
    else
    {
        l->tail->next = new;
        new->representative = l->head;
        l->tail = new;
    }
    return l;
}

void freeList(List *l, bool freeList)
{
    Object *temp;
    while (l->head)
    {
        temp = l->head->next;
        free(l->head);
        l->head = temp;
    }
    if (freeList)
        free(l);
}

void displayList(List *l)
{
    List temp = *l;
    while (temp.head != NULL)
    {
        for (int i = 0; i < 3; i++)
        {
            printf("Pixel RGB n°%d : {%d} | ", i + 1, temp.head->pixel.color[i]);
        }
        temp.head = temp.head->next;
        printf("\n");
    }
}

unsigned int sizeList(List *l)
{
    List temp = *l;
    unsigned int size = 0;
    while (temp.head)
    {
        temp.head = temp.head->next;
        size++;
    }
    return size;
}

bool isEmpty(List *l)
{
    return l->head == 0 || l->tail == 0;
}

void newStructTabList(StructTabList *stdTabList)
{
    stdTabList->size = 0;
    stdTabList->sizeMax = SIZE_ARRAY_RGB_MAX;
    stdTabList->array = (List **)malloc(sizeof(List *) * stdTabList->sizeMax);
    if (stdTabList->array == NULL)
        displayError("Erreur d'allocation du tableau", 0);
}

void freeStructTabList(StructTabList *stdTabList)
{
    free(stdTabList->array);
}

void MakeSetList(Pixel pixel, StructTabList *stdTabList)
{
    List *l = newList();
    l = addElement(l, pixel);
    if (stdTabList->size == stdTabList->sizeMax)
    {
        stdTabList->sizeMax += SIZE_ARRAY_RGB_MAX;
        stdTabList->array = (List **)realloc(stdTabList->array, sizeof(List *) * stdTabList->sizeMax);
        if (stdTabList->array == NULL)
            displayError("Erreur de reallocation du tableau", 0);
    }
    stdTabList->array[stdTabList->size] = l;
    stdTabList->size++;
}

Object *FindSetList(StructTabList *stdTabList, Pixel pixel)
{
    return stdTabList->array[pixel.key]->head;
}

void UnionList(StructTabList *stdTabList, Pixel p1, Pixel p2, PixelRGB *PixelRGB)
{
    Object *o1 = FindSetList(stdTabList, p1);
    if (o1 == NULL)
        displayError("Pixel introuvable ! ", 0);
    Object *o2 = FindSetList(stdTabList, p2);
    if (o2 == NULL)
        displayError("Pixel introuvable !", 0);
    if (o1 == o2)
    {
        return; // Ils ont le même représentant
    }
    List *new = newList();
    List *l1 = stdTabList->array[p1.key];
    List *l2 = stdTabList->array[p2.key];
    List l1_bis = *l1;
    List l2_bis = *l2;
    List l2_bis_find = *l2;
    int count = 0;
    while (l2_bis_find.head)
    {
        Pixel find = l2_bis_find.head->pixel;
        for (unsigned int i = 0; i < PixelRGB->size && count != 3; i++)
        {
            for (int k = 0; k < 3; k++)
            {
                if (find.color[k] == PixelRGB->Colors[i].color[k])
                    count++;
            }
            if (count == 3)
            {
                PixelRGB->Colors[i].key = p1.key;
                count = 0;
            }
            else
            {
                count = 0;
            }
        }
        l2_bis_find.head = l2_bis_find.head->next;
    }
    while (l1_bis.head)
    {
        new = addElement(new, l1_bis.head->pixel);
        l1_bis.head = l1_bis.head->next;
    }
    while (l2_bis.head)
    {
        new = addElement(new, l2_bis.head->pixel);
        l2_bis.head = l2_bis.head->next;
    }
    freeList(l1, true);
    freeList(l2, false);
    stdTabList->array[p1.key] = new;
}

void AutomaticColoring(StructTabList *stdTabList, PixelRGB *PixelRGB, Data *data, bool isGenerate)
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
    printf("a");
    Read(file, data);
    for (unsigned int i = 0; i < data->row_number; i++)
    {
        for (unsigned int j = 0; j < data->column_number; j++)
        {
            if (data->array[i][j].color[0] == WHITE)
            {
                MakeSetList(generateColors(PixelRGB), stdTabList); // Création des ensembles
            }
        }
    }
    // Union de toute les Lists
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
                        UnionList(stdTabList, PixelRGB->Colors[data->array[i][j].index - 1], PixelRGB->Colors[data->array[i][j_bis].index - 1], PixelRGB);
                    }
                }
                if (i_bis > 0)
                { // haut
                    if (data->array[i_bis][j].color[0] == WHITE)
                    {
                        UnionList(stdTabList, PixelRGB->Colors[data->array[i][j].index - 1], PixelRGB->Colors[data->array[i_bis][j].index - 1], PixelRGB);
                    }
                }
                if (j + 1 != data->column_number)
                { // droite
                    if (data->array[i][j + 1].color[0] == WHITE)
                    {
                        UnionList(stdTabList, PixelRGB->Colors[data->array[i][j].index - 1], PixelRGB->Colors[data->array[i][j + 1].index - 1], PixelRGB);
                    }
                }
                if (i + 1 != data->row_number)
                { // bas
                    if (data->array[i + 1][j].color[0] == WHITE)
                    {
                        UnionList(stdTabList, PixelRGB->Colors[data->array[i][j].index - 1], PixelRGB->Colors[data->array[i + 1][j].index - 1], PixelRGB);
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
                if (FindSetList(stdTabList, PixelRGB->Colors[data->array[i][j].index - 1]) != NULL)
                {
                    data->array[i][j] = FindSetList(stdTabList, PixelRGB->Colors[data->array[i][j].index - 1])->pixel;
                }
            }
        }
    }
    // Création et écriture de l'image au format ppm
    Write(file, data);
}
