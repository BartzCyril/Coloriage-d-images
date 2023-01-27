#include "../includes/utils.h"
#include "../includes/liste.h"
#include "../includes/fonctions.h"
#include "../includes/arbre.h"

void test1Question4(PixelRGB *PixelRGB, Data *data, StructTabList *stdTabList, char *name)
{
    // Lecture de l'image
    Read(name, data);
    // Compteur de pixels blancs
    unsigned int count_pix_white = 0;
    // MakeSetList
    for (unsigned int i = 0; i < data->row_number; i++)
    {
        for (unsigned int j = 0; j < data->column_number; j++)
        {
            if (data->array[i][j].color[0] == WHITE)
            {
                count_pix_white++;
                MakeSetList(generateColors(PixelRGB), stdTabList); // Création des ensembles
            }
        }
    }
    printf("Pixel blanc = %d\n", count_pix_white);
    // Taille du tableau de liste est égal au nombre de pixels blancs
    if (stdTabList->size == count_pix_white)
        printf("TEST REUSSI : la taille du tableau de liste est égal au nombre de pixels blancs !\n");
    else
        printf("ECHEC : la taille du tableau de liste est différente au nombre de pixels blancs !\n");
    // Aucun doublon
    unsigned int k = 0;
    unsigned int count = 0;
    while (k < PixelRGB->size && count != 3)
    {
        Pixel current = PixelRGB->Colors[k];
        for (unsigned int i = 0; i < PixelRGB->size && count != 3; i++)
        {
            if (k != i)
            {
                for (unsigned int j = 0; j < 3; j++)
                {
                    if (current.color[j] == PixelRGB->Colors[i].color[j])
                        count++;
                }
                if (count != 3)
                {
                    count = 0;
                }
                else
                {
                    printf("k = %d, i = %d\n", k, i);
                    for (int a = 0; a < 3; a++)
                    {
                        printf("%d | %d\n", PixelRGB->Colors[k].color[a], PixelRGB->Colors[i].color[a]);
                    }
                }
            }
        }
        k++;
    }
    if (count != 3)
        printf("TEST REUSSI : il n'y a aucun doublon !\n");
    else
        printf("ECHEC : Il y a des doublons !\n");

    // Comparaison entre le tableau de couleurs aléatoires et le représantant de chaque élément du tableau de liste
    unsigned int nb_test_successful = 0;
    for (unsigned int i = 0; i < stdTabList->size; i++)
    {
        unsigned int count = 0;
        for (unsigned int k = 0; k < 3; k++)
        {
            if (stdTabList->array[i]->head->representative->pixel.color[k] == PixelRGB->Colors[i].color[k])
                count++;
        }
        if (count == 3)
        {
            nb_test_successful++;
            count = 0;
        }
        else
            count = 0;
    }
    if (count_pix_white == nb_test_successful)
        printf("TEST REUSSI : tous les représentants correspondent avec le tableau de couleurs aléatoires \n!");
    else
        printf("ECHEC : tous les représentants ne correspondent pas avec le tableau de couleurs aléatoires \n!");
    freeArray(data);
}

void test2Question4()
{
    // Création de la liste
    List *test = newList();
    Pixel head = newPixel();
    test = addElement(test, head);
    test = addElement(test, newPixel());
    test = addElement(test, newPixel());
    test = addElement(test, newPixel());
    test = addElement(test, newPixel());
    test = addElement(test, newPixel());
    test = addElement(test, newPixel());
    // On regarde si le représentant de chaque élement correspond à la tête
    unsigned int count = 0;
    unsigned int length = sizeList(test);
    List temp = *test;
    while (temp.head)
    {
        for (int i = 0; i < 3; i++)
        {
            if (temp.head->representative->pixel.color[i] == head.color[i])
                count++;
        }
        if (count == 3)
        {
            length--;
            count = 0;
        }
        else
        {
            count = 0;
        }
        temp.head = temp.head->next;
    }
    if (length == 0)
        printf("TEST REUSSI : Le représantant de chaque élément correspond à la tête de la liste !\n");
    else
        printf("ECHEC : Le représentant d'un ou de plusieurs éléments ne correspond(ent) pas à la tête de la liste !\n");
    freeList(test, true);
}

void test1Question8(StructTabList *stdTabList, PixelRGB *PixelRGB)
{
    List *l1 = newList();
    l1 = addElement(l1, newPixel());
    l1 = addElement(l1, newPixel());
    l1->head->next->pixel.key = l1->head->pixel.key;
    stdTabList->array[stdTabList->size] = l1;
    stdTabList->size++;
    List *l2 = newList();
    l2 = addElement(l2, newPixel());
    l2 = addElement(l2, newPixel());
    l2->head->pixel.key = 1;
    l2->head->next->pixel.key = l2->head->pixel.key;
    stdTabList->array[stdTabList->size] = l2;
    stdTabList->size++;
    // UnionList des deux listes
    UnionList(stdTabList, l1->head->pixel, l2->head->pixel, PixelRGB);
    // On affiche la liste
    displayList(stdTabList->array[0]);
    // On regarde si chaque élément de la liste a commme représentant la tête de la nouvelle liste
    unsigned int length = 4;
    unsigned int count = 0;
    List temp = *stdTabList->array[0];
    while (temp.head)
    {
        for (int i = 0; i < 3; i++)
        {
            if (temp.head->representative->pixel.color[i] == stdTabList->array[0]->head->pixel.color[i])
                count++;
        }
        if (count == 3)
        {
            length--;
            count = 0;
        }
        else
        {
            count = 0;
        }
        temp.head = temp.head->next;
    }
    if (length == 0)
        printf("TEST REUSSI : Le représantant de chaque élément correspond à la tête de la liste !\n");
    else
        printf("ECHEC : Le représentant d'un ou de plusieurs éléments ne correspond(ent) pas à la tête de la liste !\n");
}

void test2Question8(StructTabList *stdTabList, PixelRGB *PixelRGB, Data *data, bool freeArrayData)
{
    // On lit l'image de test
    Read("test2Question8", data);
    /**
    Cette image contient 6 pixels blancs donc nous devons obtenir 6 Listes avec MakeSetList
    et cette image est composée de 3 zones, une avec 4 pixels et deux autres avec 1 pixel
    donc nous devons obtenir 3 listes à la fin des UnionLists
    **/
    // Pour chaque pixel blanc => MakeSetList
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
    // Test si la taille du tableau de liste est égal à 6 et affiche les listes si oui
    if (stdTabList->size == 6)
    {
        printf("TEST REUSSI : La taille du tableau est égal à 6 !\n");
        for (unsigned int i = 0; i < stdTabList->size; i++)
        {
            displayList(stdTabList->array[i]);
            printf("\n");
        }
    }
    else
        printf("ECHEC : La taille du tableau n'est pas égal à 6 !\n");
    // UnionList
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
    unsigned int count_nb_list = 0;
    for (unsigned int i = 0; i < stdTabList->size; i++)
    {
        if (!isEmpty(stdTabList->array[i]))
            count_nb_list++;
    }
    // On test si le nombre de liste est égal à 3 et on les affiche
    if (count_nb_list == 3)
    {
        printf("TEST REUSSI : La taille de la liste est égal à 3 !\n");
        for (unsigned int i = 0; i < stdTabList->size; i++)
        {
            if (!isEmpty(stdTabList->array[i]))
            {
                displayList(stdTabList->array[i]);
                printf("\n");
            }
        }
    }
    else
    {
        printf("ECHEC : La taille de la liste n'est pas égal à 3 !\n");
    }
    if (freeArrayData)
        freeArray(data);
}

void test3Question8(StructTabList *stdTabList, PixelRGB *PixelRGB, Data *data)
{
    // Read + MakeSetList + FindSetList + UnionList avec test2Question8
    test2Question8(stdTabList, PixelRGB, data, false);
    // On parcourt les pixels blancs pour leur attribué la bonne couleur
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
    // Après la mise à jour du tableau qui contenait les pixels noir et blanc
    // On génère la nouvelle image au format ppm avec Write et si le test est OK
    // L'image sera coloriée avec 3 couleurs différentes
    Write("test2Question8", data);
    freeArray(data);
}

void test1Question11(PixelRGB *PixelRGB, Data *data, StructTabNode *stdTabNode, char *name)
{
    // Lecture de l'image
    Read(name, data);
    // Compteur de pixels blancs
    unsigned int count_pix_white = 0;
    // MakeSet
    for (unsigned int i = 0; i < data->row_number; i++)
    {
        for (unsigned int j = 0; j < data->column_number; j++)
        {
            if (data->array[i][j].color[0] == WHITE)
            {
                count_pix_white++;
                MakeSet(generateColors(PixelRGB), stdTabNode); // Création des ensembles
            }
        }
    }
    // Taille du tableau de liste est égal au nombre de pixels blancs
    if (stdTabNode->size == count_pix_white)
        printf("TEST REUSSI : la taille du tableau de noeud est égal au nombre de pixels blancs !\n");
    else
        printf("ECHEC : la taille du tableau de noeud est différente au nombre de pixels blancs !\n");
    freeArray(data);
}

void test2Question11(Data *data, StructTabNode *stdTabNode, PixelRGB *PixelRGB)
{
    // Lecture de l'image
    Read("test2Question11", data);
    // MakeSet
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
    stdTabNode->array[3]->parent = stdTabNode->array[2]->parent;
    stdTabNode->array[2]->parent = stdTabNode->array[1]->parent;
    stdTabNode->array[1]->parent = stdTabNode->array[0]->parent;
    // On regarde si le représantant du pixel n°4 correspond au pixel n°1
    if (FindSet(stdTabNode->array[3]->pixel, stdTabNode) == stdTabNode->array[0])
        printf("TEST REUSSI : FindSet fonctionne\n");
    else
        printf("ECHEC : FindSet ne fonctionne pas\n");
    freeArray(data);
}

void test1Question15(StructTabNode *stdTabNode) {
    Node* n1_parent = newNode(newPixel());
    stdTabNode->array[stdTabNode->size++] = n1_parent;
    Node* n1_children = newNode(newPixel());
    stdTabNode->array[stdTabNode->size++] = n1_children;
    Node* n2_parent = newNode(newPixel());
    stdTabNode->array[stdTabNode->size++] = n2_parent;
    Node* n2_children = newNode(newPixel());
    stdTabNode->array[stdTabNode->size++] = n2_children;
    n1_children->parent = n1_parent;
    n1_parent->rank++;
    n2_children->parent = n2_parent;
    n2_parent->rank++;
    // Union 
    Union(stdTabNode, n1_parent->pixel, n2_children->pixel);
    // On regarde si le rang de n2->parent = 2 ; n1->parent = 1 ; n1&n2->children = 0
    if (n1_parent->rank == 1 && n2_parent->rank == 2 && n1_children->rank == 0 && n2_children->rank == 0)
        printf("TEST REUSSI : Tous les rangs sont corrects !\n");
    else 
        printf("ECHEC : Les rangs ne correspondent pas !\n");
    // On regarde si tous les éléments ont comme parent n2->parent
    if (FindSet(n1_children->pixel, stdTabNode) == n2_parent && 
        FindSet(n2_parent->pixel, stdTabNode) == n2_parent &&
        FindSet(n2_children->pixel, stdTabNode) == n2_parent &&
        FindSet(n2_parent->pixel, stdTabNode) == n2_parent) 
        printf("TEST REUSSI : Tous les éléments ont comme parent n2->parent !\n");
    else
        printf("ECHEC : Tous les éléments n'ont pas comme parent n2->parent !\n");
}

void test2Question15(StructTabNode *stdTabNode, PixelRGB *PixelRGB, Data *data, bool freeArrayData)
{
    // On lit l'image de test
    Read("test2Question8", data);
    /**
    Cette image contient 6 pixels blancs donc nous devons obtenir 6 Noeuds avec MakeSet
    et cette image est composée de 3 zones, une avec 4 pixels et deux autres avec 1 pixel
    donc nous devons obtenir 3 listes à la fin des Union
    **/
    // Pour chaque pixel blanc => MakeSet
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
    // Test si la taille du tableau de noeud est égal à 6 et on affiche les noeuds si oui
    if (stdTabNode->size == 6)
    {
        printf("TEST REUSSI : La taille du tableau est égal à 6 !\n");
        for (unsigned int i = 0; i < stdTabNode->size; i++)
        {
            printf("Pixel RGB : {%d,%d,%d}", stdTabNode->array[i]->pixel.color[0], stdTabNode->array[i]->pixel.color[1], stdTabNode->array[i]->pixel.color[2]);
            printf("\n");
        }
    }
    else
        printf("ECHEC : La taille du tableau n'est pas égal à 6 !\n");
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
    // On regarde si les 4 premiers éléments ont le même père, et que les deux derniers éléments ont le même père
    if (FindSet(stdTabNode->array[0]->pixel, stdTabNode) == stdTabNode->array[1] &&
        FindSet(stdTabNode->array[1]->pixel, stdTabNode) == stdTabNode->array[1] &&
        FindSet(stdTabNode->array[2]->pixel, stdTabNode) == stdTabNode->array[1] &&
        FindSet(stdTabNode->array[3]->pixel, stdTabNode) == stdTabNode->array[1] &&
        FindSet(stdTabNode->array[4]->pixel, stdTabNode) == stdTabNode->array[4] &&
        FindSet(stdTabNode->array[5]->pixel, stdTabNode) == stdTabNode->array[5]
    )
        printf("TEST REUSSI : Il y a 3 arbres !\n");
    else 
        printf("ECHEC : Il n'y a pas 3 arbres !\n");
    if (freeArrayData)
        freeArray(data);
}

void test3Question15(StructTabNode *stdTabNode, PixelRGB *PixelRGB, Data *data) {
    // Read + MakeSetList + FindSetList + UnionList avec test2Question8
    test2Question15(stdTabNode, PixelRGB, data, false);
    // On parcourt les pixels blancs pour leur attribué la bonne couleur
    for (unsigned int i = 0; i < data->row_number; i++)
    {
        for (unsigned int j = 0; j < data->column_number; j++)
        {
            if (data->array[i][j].color[0] == WHITE)
            {
                if (FindSet(PixelRGB->Colors[data->array[i][j].index - 1], stdTabNode) != NULL)
                {
                    data->array[i][j] = FindSet(PixelRGB->Colors[data->array[i][j].index - 1], stdTabNode)->pixel;
                }
            }
        }
    }
    // Après la mise à jour du tableau qui contenait les pixels noir et blanc
    // On génère la nouvelle image au format ppm avec Write et si le test est OK
    // L'image sera coloriée avec 3 couleurs différentes
    Write("test2Question8", data);
    freeArray(data);
}

int main(int argc, char const *argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "2 arguments attendu !\n<mode> <n°test>\nmode : liste | arbre\n");
        exit(EXIT_FAILURE);
    }
    if ((strcmp(argv[1], "liste") != 0) && (strcmp(argv[1], "arbre") != 0))
    {
        fprintf(stderr, "ECHEC MODE !\nmode : liste | arbre\n");
        exit(EXIT_FAILURE);
    }
    srand(time(NULL));
    Data data;
    PixelRGB PixelRGB;
    newPixelRGB(&PixelRGB);
    if (strcmp("liste", argv[1]) == 0)
    {
        StructTabList stdTabList;
        newStructTabList(&stdTabList);
        if (strcmp(argv[2], "Q4_1") == 0)
        {
            char file[100];
            printf("Entrez le nom du fichier (sans l'extension) : ");
            scanf("%s", file);
            test1Question4(&PixelRGB, &data, &stdTabList, file);
        }
        else if (strcmp(argv[2], "Q4_2") == 0)
        {
            test2Question4();
        }
        else if (strcmp(argv[2], "Q8_1") == 0)
        {
            test1Question8(&stdTabList, &PixelRGB);
        }
        else if (strcmp(argv[2], "Q8_2") == 0)
        {
            test2Question8(&stdTabList, &PixelRGB, &data, true);
        }
        else if (strcmp(argv[2], "Q8_3") == 0)
        {
            test3Question8(&stdTabList, &PixelRGB, &data);
        }
        else {
            printf("AUCUN TEST DISPONIBLE\n");
        }
        for (unsigned int i = 0; i < stdTabList.size; i++)
        {
            if (stdTabList.array[i]->head != 0)
            {
                freeList(stdTabList.array[i], true);
            }
            else
            {
                free(stdTabList.array[i]);
            }
        }
        freeStructTabList(&stdTabList);
    }
    else
    {
        StructTabNode stdTabNode;
        newStructTabNode(&stdTabNode);
        if (strcmp(argv[2], "Q11_1") == 0)
        {
            char file[100];
            printf("Entrez le nom du fichier (sans l'extension) : ");
            scanf("%s", file);
            test1Question11(&PixelRGB, &data, &stdTabNode, file);
        }
        else if (strcmp(argv[2], "Q11_2") == 0) {
            test2Question11(&data, &stdTabNode, &PixelRGB);
        }
        else if (strcmp(argv[2], "Q15_1") == 0) {
            test1Question15(&stdTabNode);
        }
        else if (strcmp(argv[2], "Q15_2") == 0) {
            test2Question15(&stdTabNode, &PixelRGB, &data, true);
        }
        else if (strcmp(argv[2], "Q15_3") == 0) {
            test3Question15(&stdTabNode, &PixelRGB, &data);
        } else {
            printf("AUCUN TEST DISPONIBLE\n");
        }
        freeStructTabNode(&stdTabNode);
    }
    free(PixelRGB.Colors);
    return 0;
}
