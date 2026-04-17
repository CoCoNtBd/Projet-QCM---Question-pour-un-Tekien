#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "teacher.h"

void teacher_login() {
    char password[128];
    printf("   Mot de passe : ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0'; 

    if (strcmp(password, TEACHER_PASSWORD) == 0) {
        printf("Vous entrez dans le mode enseignant\n");
    } else {
        printf("Mot de passe incorrect\n");
    }
}

void teacher_menu(){
    int choix;
    char buffer[50];
    printf("MENU ENSEIGNANT");
    printf("\n");
    printf("1 : Créer un nouveau QCM\n");
    printf("2 : Lister les QCM existants\n");
    printf("3 : Quitter le mode enseignant\n");
    printf("\n");
    printf("Votre choix : ");
    do {
        fgets(buffer, sizeof(buffer), stdin);
        choix = atoi(buffer);
        if (choix < 1 || choix > 3)
            printf("Mode invalide, réessayez : ");
    } while (choix < 1 || choix > 3);
    
    switch(choix){
        case 1:
            //créer une fonction pour créer un QCM
            break;
        case 2:
            //créer une fonction pour lister les QCM existants
            break;
        case 3:
            printf("Au revoir !");
            break;
    }
}








