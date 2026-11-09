#include <stdio.h>

int json_update_semester(const char *filename, int semester);

int main(void)
{
    const char *fichier = "course.json";

    printf("Mise a jour du semestre a 2 dans %s...\n", fichier);

    int res = json_update_semester(fichier, 2);

    if (res == 0)
    {
        printf("Succes ! Le fichier %s a bien ete modifie.\n", fichier);
    }
    else
    {
        printf("Erreur : la fonction a renvoye %d. Verifie le nom du fichier ou son contenu.\n", res);
    }

    return 0;
}