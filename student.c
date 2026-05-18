#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "student.h"
#include "qcm.h"


int rep_pls(Question q, int seq, int neg){ // demande la réponse si plusieurs choix sont possible
    char buffer[50];
    int reps[10];
    int count = 0;
    
    printf("Entrez %d réponses :\n", q.num_correct);
    while (count < q.num_correct) {
        int rep, valid;
        printf("Réponse %d/%d : ", count + 1, q.num_correct);
        
        do {
            valid = 1;
            if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
                printf("Erreur de lecture\n");
                return 0;
            }
            rep = buffer[0];
            if (seq == 1 && count == 0 && rep == 'A' + q.num_options) {
                printf("\nVous avez passé la réponse\n");
                return 0;
            }
            if (rep < 'A' || rep > 'A' + q.num_options + seq - 1) {
                printf("Choix invalide, réessayez : ");
                valid = 0;
            }
            for (int i = 0; i < count; i++) {
                if (reps[i] == rep) {
                    printf("Déjà choisi, réessayez : ");
                    valid = 0;
                    break;
                }
            }
        } while (valid == 0);
        reps[count] = rep;
        count ++;
    }
    
    int correct_count = 0;
    for (int j = 0; j < count; j++) {
        if (1 == q.correct[reps[j]-'A']) {
            correct_count++;
        }
    }

    if (correct_count == q.num_correct) {
        printf("\nBonne réponse!\n");
        return correct_count;
    }
    printf("\nMauvaise réponse!\n");
    printf("Les bonnes réponses étaient :\n");
    for(int i = 0; i<q.num_options; i++){
        if(1 == q.correct[i]){printf("\"%c\"\n", i+'A');}
    }
    return 0 - neg;
}


int rep_one(Question q, int seq, int neg){ // demande la réponse si un choix est possible
    char buffer[50];
    int rep = 0;
    
    printf("Votre réponse : ");
    do {
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            printf("Erreur de lecture\n");
            return 0;
        }
        rep = buffer[0];
        if (rep < 'A' || rep > 'A' + q.num_options + seq - 1)
            printf("Choix invalide, réessayez : ");
    } while (rep < 'A' || rep > 'A' + q.num_options + seq - 1);
    
    if(seq == 1 && rep == 'A' + q.num_options){
        printf("\nVous avez passé la réponse\n");
        return 0;
    }
    
    if(1 == q.correct[rep-'A']){
        printf("\nBonne réponse!\n");
        return 1;
    }
    
    for(int i = 0; i<q.num_options; i++){
        if(1 == q.correct[i]){printf("\nMauvaise réponse!\n\"%c\" était la bonne réponse\n", i+'A');}
    }
    return 0 - neg;
}


void student_menu() {
    char buffer[50]; // choix du qcm
    int num = 0;
    int* choix = malloc(sizeof(int));
    char** liste_qcm = qcm_list(choix);
    printf("Choisir un qcm : ");
    do {
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            printf("Erreur de lecture\n");
            return;
        }
        num = atoi(buffer);
        if (num < 1 || num > *choix)
            printf("QCM invalide, réessayez : ");
    } while (num < 1 || num > *choix);
    
    QCM* qcm_actuel = malloc(sizeof(QCM)); // chargement du qcm
    liste_qcm[num-1][strcspn(liste_qcm[num-1],"\n")] = '\0';
    charger_QCM(liste_qcm[num-1], qcm_actuel);
    
    printf("%s\n%d questions\n", qcm_actuel->nom, qcm_actuel->num_questions); // affichage des informations du qcm
    if (qcm_actuel->negatif == 1) {printf("Points négatifs\n");};
    if (qcm_actuel->plsreponses == 1) {printf("Réponses multiples\n");};
    if (qcm_actuel->sequentiel == 1) {printf("Questions séquentielles\n");};
    
    float score = 0; // initialisation du score et du score_max
    float score_max = 0;
    for (int i = 0; i < qcm_actuel->num_questions; i++){
        score_max += qcm_actuel->question[i].num_correct;
    }
    
    for (int i = 0; i < qcm_actuel->num_questions; i++){ // boucle pour chaque question du qcm
        Question quest = qcm_actuel->question[i];
        
        printf("\n------%d------\n\n", i+1);
        printf("%s\n\n", quest.texte);
        
        int j = 0;
        for (j = 0; j < quest.num_options; j++){
            printf("%c : %s\n", j+'A', quest.options[j]);
        }
        if (qcm_actuel->sequentiel == 1) {printf("%c : Passer\n", j+'A');};
        
        if (qcm_actuel->plsreponses == 0) { // demande la réponse de l'étudiant
            score += rep_one(quest, qcm_actuel->sequentiel, qcm_actuel->negatif);
        }
        else {
            score += rep_pls(quest, qcm_actuel->sequentiel, qcm_actuel->negatif);
        }
    }
    if(score<0){score = 0;}
    printf("\n------Fin du QCM------\n\nVotre note : %.2f/20\n", score/score_max*20);
}