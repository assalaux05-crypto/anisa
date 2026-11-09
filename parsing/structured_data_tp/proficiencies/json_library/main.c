#include <stdio.h>
#include <stdlib.h>

// Déclaration de la fonction à tester
int json_library_export_top(const char *input, const char *output, int minimum);

// Fonction utilitaire pour générer un fichier input de test
static int create_dummy_input(const char *path)
{
    FILE *f = fopen(path, "w");
    if (!f) return -1;

    const char *content =
        "{\n"
        "  \"courses\": [\n"
        "    {\n"
        "      \"id\": 10,\n"
        "      \"title\": \"C Programming\",\n"
        "      \"room\": \"A101\",\n"
        "      \"students\": [\n"
        "        {\"name\": \"Ada\", \"grade\": 18},\n"
        "        {\"name\": \"Bob\", \"grade\": 12}\n"
        "      ]\n"
        "    },\n"
        "    {\n"
        "      \"id\": 20,\n"
        "      \"title\": \"Structured Data\",\n"
        "      \"room\": \"B204\",\n"
        "      \"students\": [\n"
        "        {\"name\": \"Chihiro\", \"grade\": 17},\n"
        "        {\"name\": \"Dora\", \"grade\": 9}\n"
        "      ]\n"
        "    }\n"
        "  ]\n"
        "}\n";

    fputs(content, f);
    fclose(f);
    return 0;
}

// Fonction utilitaire pour afficher le contenu d'un fichier dans le terminal
static void print_file_content(const char *path)
{
    FILE *f = fopen(path, "r");
    if (!f)
    {
        printf("Impossible d'ouvrir %s pour la lecture.\n", path);
        return;
    }

    char ch;
    while ((ch = fgetc(f)) != EOF)
    {
        putchar(ch);
    }
    putchar('\n');
    fclose(f);
}

int main(void)
{
    const char *input_file = "test_input.json";
    const char *output_file = "test_output.json";
    int seuil = 15;

    // 1. Création automatique du fichier source
    if (create_dummy_input(input_file) != 0)
    {
        fprintf(stderr, "Erreur : echec de creation de %s\n", input_file);
        return 1;
    }
    printf("1. Fichier source '%s' cree avec succes.\n", input_file);

    // 2. Appel de ta fonction
    printf("2. Exportation des etudiants ayant au moins %d/20...\n", seuil);
    int res = json_library_export_top(input_file, output_file, seuil);

    if (res != 0)
    {
        printf("Echec : la fonction a retourne une erreur (%d).\n", res);
        return 1;
    }

    // 3. Affichage du fichier de sortie généré
    printf("3. Succes ! Contenu de '%s' :\n", output_file);
    printf("----------------------------------------\n");
    print_file_content(output_file);
    printf("----------------------------------------\n");
    printf("Resultat attendu : un tableau contenant Ada (18) et Chihiro (17).\n");

    return 0;
}