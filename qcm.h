#ifndef QCM_H
#define QCM_H

#define TAILLE_MAX_TEXTE 256
#define MAX_QUESTIONS 40
#define MAX_OPTIONS 5
#define TAILLE_MAX_OPTIONS 256
#define TAILLE_MAX_NOM 64


typedef struct{
    char texte[TAILLE_MAX_TEXTE];
    char options[MAX_OPTIONS][TAILLE_MAX_OPTIONS];
    int num_options;
    int correct[MAX_OPTIONS];
    int num_correct;
}Question;

typedef struct{
    char nom[TAILLE_MAX_NOM];
    int negatif;
    int plsreponses;
    int sequentiel;
    int num_questions;
    Question question[MAX_QUESTIONS];
}QCM;

#endif
