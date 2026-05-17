#include <stdio.h>
#include <string.h>
#include "qcm.h"


void sauvegarder_QCM(QCM* qcm) {
    char nomFichier[TAILLE_MAX_NOM + 10];
    snprintf(nomFichier, sizeof(nomFichier), "%s.txt", qcm->nom);

    FILE* f = fopen(nomFichier, "w");
    if (f == NULL) {
        printf("Erreur d'ouverture fichier\n");
        return;
    }

    fprintf(f, "%s\n", qcm->nom);
    fprintf(f, "%s\n", qcm->categorie);
    fprintf(f, "%d;%d;%d\n", qcm->negatif, qcm->plsreponses, qcm->sequentiel);
    fprintf(f, "%d\n", qcm->num_questions);

    for (int j = 0; j < qcm->num_questions; j++) {
        Question* quest = &qcm->question[j];

        fprintf(f, "%s\n", quest->texte);
        fprintf(f, "%d\n", quest->num_options);

        for (int k = 0; k < quest->num_options; k++) {
            fprintf(f, "%s\n", quest->options[k]);
        }

        fprintf(f, "%d\n", quest->num_correct);
        for (int k = 0; k < quest->num_options; k++) {
            fprintf(f, "%d\n", quest->correct[k]);
        }
    }

    fclose(f);
    printf("QCM \"%s\" sauvegardé avec succès dans \"%s\"\n", qcm->nom, nomFichier);
}


