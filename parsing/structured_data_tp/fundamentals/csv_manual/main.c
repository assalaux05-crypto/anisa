#include "exercise.h"
#include <stdio.h>
/*
int main(void)
{
    char name[64];

    // 1. Nombre de lignes avant l'ajout
    printf("Rows avant ajout: %d\n", csv_count_rows("students.csv"));

    // 2. Recherche avant l'ajout
    if (csv_find_student("students.csv", 2, name, sizeof(name)) == 0)
        printf("Student 2: %s\n", name);
    else
        puts("Student 2: not found");

    // 3. Test de l'ajout (append)
    if (csv_add_student("students.csv", 99, "Charlie", 17) == 0)
        printf("Ajout de Charlie (id 99) reussi !\n");
    else
        puts("Erreur lors de l'ajout de l'etudiant");

    // 4. Verification : le nombre de lignes doit avoir augmente de 1
    printf("Rows apres ajout: %d\n", csv_count_rows("students.csv"));

    // 5. Verification : on cherche le nouvel etudiant
    if (csv_find_student("students.csv", 99, name, sizeof(name)) == 0)
        printf("Student 99 retrouve: %s\n", name);
    else
        puts("Student 99: non trouve");

    return 0;
}

#include "exercise.h"
#include <stdio.h>

static void afficher_fichier(const char *filename)
{
    FILE *f = fopen(filename, "r");
    if (!f) {
        perror("Erreur lors de l'ouverture du fichier");
        return;
    }

    printf("\n--- Contenu actuel de %s ---\n", filename);
    char buf[256];
    while (fgets(buf, sizeof(buf), f)) {
        printf("%s", buf);
    }
    printf("------------------------------------\n\n");

    fclose(f);
}

int main(void)
{
    const char *csv_file = "students.csv";

    // 1. État initial
    printf("1. Etat avant modification :");
    afficher_fichier(csv_file);

    // 2. Test 1 : Modifier la note de l'étudiant avec l'id 2 (ex: mettre 20)
    int target_id = 2;
    int new_grade = 20;
    printf("2. Tentative de mise a jour : ID %d -> nouvelle note %d\n", target_id, new_grade);

    int res = csv_update_grade(csv_file, target_id, new_grade);
    if (res == 0) {
        printf("-> Succes : csv_update_grade a renvoye 0.\n");
    } else {
        printf("-> Echec : la fonction a renvoye %d.\n", res);
    }

    afficher_fichier(csv_file);

    // 3. Test 2 : Tenter de modifier un ID inexistant (ex: 9999)
    int bad_id = 9999;
    printf("3. Tentative de mise a jour d'un ID inexistant (%d)...\n", bad_id);

    res = csv_update_grade(csv_file, bad_id, 10);
    if (res == -1) {
        printf("-> Succes : la fonction a bien renvoye -1 pour un ID introuvable.\n");
    } else {
        printf("-> Erreur : la fonction aurait du renvoyer -1, mais a renvoye %d.\n", res);
    }

    return 0;
}
    */
#include "exercise.h"
#include <stdio.h>

static void afficher_fichier(const char *filename)
{
    FILE *f = fopen(filename, "r");
    if (!f) {
        perror("Erreur lecture fichier");
        return;
    }

    printf("\n--- Contenu de %s ---\n", filename);
    char buf[256];
    while (fgets(buf, sizeof(buf), f)) {
        printf("%s", buf);
    }
    printf("---------------------------\n\n");

    fclose(f);
}

int main(void)
{
    const char *csv_file = "students.csv";

    // 1. État initial
    printf("1. Fichier initial :");
    afficher_fichier(csv_file);

    // 2. Test 1 : Supprimer un étudiant qui existe (ex: ID 2 - Bob)
    int target_id = 2;
    printf("2. Suppression de l'etudiant avec l'ID %d...\n", target_id);
    int res = csv_delete_student(csv_file, target_id);

    if (res == 0) {
        printf("-> Succes : etudiant %d supprime.\n", target_id);
    } else {
        printf("-> Echec : csv_delete_student a renvoye %d.\n", res);
    }

    // Affichage après la première suppression
    afficher_fichier(csv_file);

    // 3. Test 2 : Tenter de supprimer un ID inexistant (ex: 9999)
    int bad_id = 9999;
    printf("3. Tentative de suppression d'un ID inexistant (%d)...\n", bad_id);
    res = csv_delete_student(csv_file, bad_id);

    if (res == -1) {
        printf("-> Succes : la fonction a bien echoue (-1) et preserve le fichier.\n");
    } else {
        printf("-> Erreur : la fonction aurait du renvoyer -1, mais a renvoye %d.\n", res);
    }

    // Affichage final pour vérifier qu'aucune ligne n'a disparu par erreur
    afficher_fichier(csv_file);

    return 0;
}