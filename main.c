#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>








int main(){
    int mode;
    char buffer[50];
    
    printf("================== Modes ==================\n\n");
    printf("1 : Mode ENSEIGNANT\n2 : Mode ETUDIANT\n3 : Quitter\n");
    printf("Votre choix : ");
    
    do {
        fgets(buffer, sizeof(buffer), stdin);
        mode = atoi(buffer);
        if (mode < 1 || mode > 3)
            printf("Mode invalide, réessayez : ");
    } while (mode < 1 || mode > 3);
    
    switch(mode){
        case 1:
            printf("Vous entrez dans le mode ENSEIGNANT ");
            printf("Chargement ...");
            break;
        case 2:
            printf("Vous entrez dans le mode ETUDIANT\n");
            printf("Chargement ...");
            break;
        case 3:
            printf("Au revoir !");
            break;
    }
    
    return 0;
}
