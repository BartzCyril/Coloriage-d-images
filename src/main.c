#include "../includes/utils.h"
#include "../includes/liste.h"
#include "../includes/arbre.h"
#include "../includes/fonctions.h"

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        fprintf(stderr, "2 arguments attendu ! <mode> <fichier_type>\nmode : liste | arbre\n1 : pour un fichier généré\n2 : pour un fichier déjà existant\n");
        exit(EXIT_FAILURE);
    }
    if ((strcmp(argv[1], "liste") != 0) && (strcmp(argv[1], "arbre") != 0)) {
        fprintf(stderr, "ECHEC MODE !\nmode : liste | arbre\n");
        exit(EXIT_FAILURE);
    }
    if ((strcmp(argv[2], "1") != 0) && (strcmp(argv[2], "2") != 0)) {
        fprintf(stderr, "ECHEC TYPE FICHIER !\n1 : pour un fichier généré\n2 : pour un fichier déjà existant\n");
        exit(EXIT_FAILURE);
    }
    bool isGenerate = false;
    if (strcmp(argv[2], "1") == 0)
        isGenerate = true;
    // LISTES
    srand(time(NULL));
    Data data;
    PixelRGB PixelRGB;
    newPixelRGB(&PixelRGB);
    unsigned long millis = 0;
    clock_t begin = clock();
    if (strcmp(argv[1], "liste") == 0)
    {
        StructTabList stdTabList;
        newStructTabList(&stdTabList);
        AutomaticColoring(&stdTabList, &PixelRGB, &data, isGenerate);
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
    } else {
        StructTabNode stdTabTree;
        newStructTabNode(&stdTabTree);
        AutomaticColoringTree(&stdTabTree, &PixelRGB, &data, isGenerate);
        freeStructTabNode(&stdTabTree);
    }
    clock_t end = clock();
    millis = (end - begin) * 1e-6;
    printf("Tps d'execution du programme : %ld sec(s)\n", millis);
    freeArray(&data);
    free(PixelRGB.Colors);
    exit(EXIT_SUCCESS);
}
