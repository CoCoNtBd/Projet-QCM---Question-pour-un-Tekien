#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "teacher.h"
#include "qcm.h"
#include "main.h"


void lire_mot_de_passe(char *mdp, int taille) {
    FILE *f = fopen("password.txt", "r");
    if (f == NULL) {
        strncpy(mdp, MDP_DEFAUT, taille);
        return;
    }
    if(fgets(mdp, taille, f) == NULL){
        printf("Erreur lecture");
        return;
    }
    mdp[strcspn(mdp, "\n")] = '\0';
    fclose(f);
}


void sauvegarder_mot_de_passe(char *mdp) {
    FILE *f = fopen("password.txt", "w");
    if (f == NULL) {
        printf("Erreur : impossible de sauvegarder le mot de passe\n");
        return;
    }
    fprintf(f, "%s\n", mdp);
    fclose(f);
}

void changer_mot_de_passe() {
    char mdp_actuel[128], ancien[128], nouveau[128], confirmation[128];

    lire_mot_de_passe(mdp_actuel, sizeof(mdp_actuel));

    printf("Mot de passe actuel : ");
    if (fgets(ancien, sizeof(ancien), stdin) == NULL){
        printf("Erreur lecture");
        return;
    }
    ancien[strcspn(ancien, "\n")] = '\0';

    if (strcmp(ancien, mdp_actuel) != 0) {
        printf("Mot de passe incorrect\n");
        return;
    }

    printf("Nouveau mot de passe : ");
    if (fgets(nouveau, sizeof(nouveau), stdin) == NULL) return;
    nouveau[strcspn(nouveau, "\n")] = '\0';

    printf("Confirmez le nouveau mot de passe : ");
    if (fgets(confirmation, sizeof(confirmation), stdin) == NULL) return;
    confirmation[strcspn(confirmation, "\n")] = '\0';

    if (strcmp(nouveau, confirmation) != 0) {
        printf("Les mots de passe ne correspondent pas\n");
        return;
    }

    sauvegarder_mot_de_passe(nouveau);
    printf("Mot de passe changé avec succès !\n");
}

void teacher_menu() {
    int choix;
    char buffer[50];
    printf("============= MENU ENSEIGNANT =============\n");
    printf("1 : Créer un nouveau QCM\n");
    printf("2 : Lister les QCM existants\n");
    printf("3 : Changer le mot de passe\n");
    printf("4 : Revenir au menu principal\n\n");
    printf("Votre choix : ");

    do {
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            printf("Erreur de lecture\n");
            return;
        }
        choix = atoi(buffer);
        if (choix < 1 || choix > 4)
            printf("Mode invalide, réessayez : ");
    } while (choix < 1 || choix > 4);

    switch (choix) {
        case 1: creer_qcm();                        break;
        case 2: liste_qcm();                        break;
        case 3: changer_mot_de_passe(); teacher_menu(); break;
        case 4: afficher_menu();                    break;
    }
}

void teacher_login() {
    char mdp_actuel[128];
    lire_mot_de_passe(mdp_actuel, sizeof(mdp_actuel));

    char password[128];
    printf("   Mot de passe : ");
    if (fgets(password, sizeof(password), stdin) == NULL) {
        printf("Erreur lecture\n");
        return;
    }
    password[strcspn(password, "\n")] = '\0';

    if (strcmp(password, mdp_actuel) == 0) {
        printf("Vous entrez dans le mode enseignant\n");
        teacher_menu();
    } else {
        printf("Mot de passe incorrect\n");
        teacher_login();
    }
}

void creer_qcm() {
    QCM q = {0};
    printf("CREATION D'UN NOUVEAU QCM\n");
    printf("Nom du nouveau qcm : ");
    fgets(q.nom, TAILLE_MAX_NOM, stdin);
}

void liste_qcm() {
}
