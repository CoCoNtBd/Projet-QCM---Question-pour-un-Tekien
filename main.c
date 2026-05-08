#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include "teacher.h"
#include "student.h"
#include "qcm.h"


void afficher_menu(){
    int mode;
    char buffer[50];
    
    printf("================== Modes ==================\n\n");
    printf("1 : Mode ENSEIGNANT\n2 : Mode ETUDIANT\n3 : Quitter\n");
    printf("Votre choix : ");
    
    do {
        if(fgets(buffer, sizeof(buffer), stdin) == NULL){
            printf("Erreur de lecture");
            return;
        }
        mode = atoi(buffer);
        if (mode < 1 || mode > 3)
            printf("Mode invalide, réessayez : ");
    } while (mode < 1 || mode > 3);
    
    switch(mode){
        case 1:
            teacher_login();
            break;
        case 2:
            printf("Vous entrez dans le mode ETUDIANT\n");
            printf("Chargement ...");
            break;
        case 3:
            printf("Au revoir !");
            break;
    }
}



int main(){
    afficher_menu();
    
    return 0;
}
