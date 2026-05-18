#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "qcm.h"

char** qcm_list(int* choix) {
	FILE* f = fopen("qcm_list.txt", "r");
	if (f == NULL) {
		printf("Impossible d'ouvrir le fichier.\n");
		return NULL;
	}
	char ligne[256];
	int compteur = 0;
	while (fgets(ligne, sizeof(ligne), f) != NULL) {
		compteur++;
	}

	rewind(f);
	char** list = malloc(compteur * sizeof(char *));
	*choix = compteur;
	int num = 0;
	while (fgets(ligne, sizeof(ligne), f) != NULL) {
		printf("%d : %s", num+1, ligne);
		*(list+num) = malloc(sizeof(char)*256);
		strcpy(*(list+num),ligne);
		num ++;
	}

	fclose(f);
	return list;
}


void sauvegarder_QCM(QCM* qcm) {
    qcm->nom[strcspn(qcm->nom, "\n")] = '\0';
    
	FILE* fi = fopen("qcm_list.txt", "a");
	fprintf(fi, "%s.txt\n", qcm->nom);
	fclose(fi);
    
    char nomFichier[TAILLE_MAX_NOM + 10];
    snprintf(nomFichier, sizeof(nomFichier), "%s.txt", qcm->nom);

    FILE* f = fopen(nomFichier, "w");
    if (f == NULL) {
        printf("Erreur d'ouverture fichier\n");
        return;
    }
    
    fprintf(f, "%s\n", qcm->nom);
    qcm->categorie[strcspn(qcm->nom, "\n")] = '\0';
    fprintf(f, "%s\n", qcm->categorie);
    fprintf(f, "%d;%d;%d\n", qcm->negatif, qcm->plsreponses, qcm->sequentiel);
    fprintf(f, "%d\n", qcm->num_questions);

    for (int j = 0; j < qcm->num_questions; j++) {
        Question* quest = &qcm->question[j];

        quest->texte[strcspn(quest->texte, "\n")] = '\0';
        fprintf(f, "%s\n", quest->texte);
        fprintf(f, "%d\n", quest->num_options);

        for (int k = 0; k < quest->num_options; k++) {
            quest->options[k][strcspn(quest->options[k], "\n")] = '\0';
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


void charger_QCM(char* f, QCM* qcm) {
	FILE* fi = fopen(f, "r");
	if (fi == NULL) {
		printf("Impossible d'ouvrir le fichier\n");
		return;
	}

	fgets(qcm->nom, TAILLE_MAX_NOM, fi);
    qcm->nom[strcspn(qcm->nom, "\n")] = '\0';
    
	fgets(qcm->categorie, TAILLE_MAX_NOM, fi);
    qcm->categorie[strcspn(qcm->categorie, "\n")] = '\0';
	
	fscanf(fi, "%d;%d;%d\n", &qcm->negatif, &qcm->plsreponses, &qcm->sequentiel);
	fscanf(fi, "%d\n", &qcm->num_questions);

	for (int i = 0; i < qcm->num_questions; i++) {
		Question* quest = &qcm->question[i];

		fgets(quest->texte, TAILLE_MAX_NOM, fi);
        quest->texte[strcspn(quest->texte, "\n")] = '\0';
        
		fscanf(fi, "%d\n", &quest->num_options);
		
		for (int j = 0; j < quest->num_options; j++) {
			fgets(quest->options[j], TAILLE_MAX_OPTIONS, fi);
            quest->options[j][strcspn(quest->options[j], "\n")] = '\0';
		}
		
	    fscanf(fi, "%d\n", &quest->num_correct);
	    
	    for (int j = 0; j < quest->num_options; j++) {
	        fscanf(fi, "%d\n", &quest->correct[j]);
		}
	}

	fclose(fi);
}