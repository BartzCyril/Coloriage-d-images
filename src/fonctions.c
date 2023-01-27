#include "../includes/fonctions.h"

void displayError(char *msg, unsigned int ErrorCode)
{
    if (ErrorCode > 0)
    {
        perror(msg);
        exit(ErrorCode);
    }
    else
    {
        fprintf(stderr, "%s\n", msg);
    }
}

void mallocArray(Data *data, unsigned int row_number, unsigned int column_number)
{
    data->column_number = column_number;
    data->row_number = row_number;
    data->array = (Pixel **)malloc(row_number * sizeof(Pixel *));
    for (unsigned int i = 0; i < row_number; i++)
    {
        data->array[i] = (Pixel *)malloc(column_number * sizeof(Pixel));
    }
    if (data->array == NULL)
        displayError("Erreur d'allocation du tableau", 0);
}

void Read(char *file, Data *data)
{
    char folder[100] = "tests/";
    strcat(folder, file);
    strcat(folder, ".pbm");
    FILE *file_img = fopen(folder, "r");
    if (file_img == NULL)
        displayError("Erreur ouverture du fichier", 0);
    char first_magic_number = ' ';
    int second_magic_number = 0;
    fscanf(file_img, "%c%d", &first_magic_number, &second_magic_number);
    if (first_magic_number != 'F' && second_magic_number != 1)
        displayError("Le format du fichier n'est pas le bon !", 0);
    unsigned int column_number = 0;
    unsigned int row_number = 0;
    fscanf(file_img, "%d %d", &column_number, &row_number);
    if (column_number == 0 && row_number == 0)
        displayError("Erreur lecture des dimensions", 0);
    mallocArray(data, row_number, column_number);
    char c;
    Pixel pixel;
    unsigned int value_pixel = 0;
    unsigned int count = 1;
    unsigned int j = 0;
    for (unsigned int i = 0; i < row_number; i++)
    {
        j = 0;
        while (j < column_number)
        {
            c = getc(file_img);
            if (c == 49)
            {
                value_pixel = BLACK;
                for (int k = 0; k < 3; k++)
                {
                    pixel.color[k] = value_pixel;
                }
                data->array[i][j] = pixel;
                j++;
            }
            else if (c == 48)
            {
                value_pixel = WHITE;
                pixel.index = count;
                count++;
                for (int k = 0; k < 3; k++)
                {
                    pixel.color[k] = value_pixel;
                }
                data->array[i][j] = pixel;
                j++;
            }
        }
    }
    fclose(file_img);
}

void Write(char *file, Data *data)
{
    if (data->array == NULL)
        displayError("Erreur génération impossible tableau vide", 0);
    char folder[100] = "tests/";
    strcat(folder, file);
    strcat(folder, ".ppm");
    FILE *img_generate_ppm = fopen(folder, "a+");
    if (img_generate_ppm == NULL)
        displayError("Erreur ouverture du fichier", 0);
    char magic_number[] = "P3";
    fputs(magic_number, img_generate_ppm);
    fprintf(img_generate_ppm, "\n%d %d", data->column_number, data->row_number);
    fputs("\n255", img_generate_ppm);
    fputc(10, img_generate_ppm);
    for (unsigned int i = 0; i < data->row_number; i++)
    {
        for (unsigned int j = 0; j < data->column_number; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                fprintf(img_generate_ppm, "%d ", data->array[i][j].color[k]);
            }
            fprintf(img_generate_ppm, "   ");
        }
    }
    fclose(img_generate_ppm);
}

void Generate(unsigned int row_number, unsigned int column_number, char *name)
{
    unsigned int Array[column_number][row_number];
    for (unsigned int i = 0; i < row_number; i++)
    {
        for (unsigned int j = 0; j < column_number; j++)
        {
            Array[i][j] = (rand() % 2);
        }
    }
    char folder[100] = "tests/";
    strcat(folder, name);
    strcat(folder, ".pbm");
    FILE *img_generate = fopen(folder, "a+");
    if (img_generate == NULL)
        displayError("Erreur ouverture du fichier", 0);
    char magic_number[] = "P1";
    fputs(magic_number, img_generate);
    fprintf(img_generate, "\n%d %d", column_number, row_number);
    fputc(10, img_generate);
    unsigned int count_row = 0;
    for (unsigned int i = 0; i < row_number; i++)
    {
        for (unsigned int j = 0; j < column_number; j++)
        {
            if (count_row == 70)
            {
                count_row = 0;
                fputc(10, img_generate);
            }
            count_row++;
            fputc(Array[i][j] + 48, img_generate);
        }
    }
    fclose(img_generate);
}

void freeArray(Data *data)
{
    for (unsigned int i = 0; i < data->row_number; i++)
    {
        free(data->array[i]);
    }
    free(data->array);
}

void newPixelRGB(PixelRGB *PixelRGB)
{
    PixelRGB->size = 0;
    PixelRGB->sizeMax = SIZE_ARRAY_RGB_MAX;
    PixelRGB->Colors = (Pixel *)malloc(sizeof(Pixel) * PixelRGB->sizeMax);
    if (PixelRGB->Colors == NULL)
        displayError("Erreur d'allocation du tableau", 0);
}

int count = 0;

Pixel newPixel()
{
    Pixel pixel;
    for (int i = 0; i < 3; i++)
    {
        pixel.color[i] = (rand() % 256);
    }
    pixel.key = count++;
    return pixel;
}

Pixel generateColors(PixelRGB *PixelRGB)
{
    if (PixelRGB->size == PixelRGB->sizeMax)
    {
        PixelRGB->sizeMax += SIZE_ARRAY_RGB_MAX;
        PixelRGB->Colors = (Pixel *)realloc(PixelRGB->Colors, PixelRGB->sizeMax * sizeof(Pixel));
        if (PixelRGB->Colors == NULL)
            displayError("Erreur de reallocation du tableau", 0);
    }
    unsigned int count_bis = 0;
    unsigned int different = 0;
    Pixel pixel;
    bool generate = true;
    bool validate = false;
    if (PixelRGB->size == 0)
        pixel = newPixel();
    else
    {
        while (generate)
        {
            validate = false;
            while (!validate)
            {
                pixel = newPixel();
                if ((pixel.color[0] == 255 && pixel.color[1] == 255 && pixel.color[2] == 255) ||
                    (pixel.color[0] == 0 && pixel.color[1] == 0 && pixel.color[2] == 0))
                {
                    validate = false;
                    count--;
                }
                else
                {
                    validate = true;
                }
            }
            different = 0;
            count_bis = 0;
            for (unsigned int i = 0; i < PixelRGB->size && count_bis != 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    if (pixel.color[j] == PixelRGB->Colors[i].color[j])
                        count_bis++;
                }
                if (count_bis != 3)
                {
                    different++;
                    count_bis = 0;
                }
            }
            if (different == PixelRGB->size)
                generate = false;
            else 
                count--;
        }
    }
    PixelRGB->Colors[PixelRGB->size] = pixel;
    PixelRGB->size++;
    return pixel;
}