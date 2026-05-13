
void sauvegarder_QCM(QCM* qcm){
    char nomFichier[100];
    FILE* f = fopen(nomFichier, "w");
    if(f == NULL){
        printf("Erreur d'ouverture fichier");
        return;
    }
    fprintf(f,"%s\n", qcm->nom);
    fprintf(f,"%s\n", qcm->categorie);
    fprintf(f,"%d;%d;%d\n", q.negatif, q.plsreponses, q.sequentiel);
    fprintf(f,"%d\n", q.num_questions);
    for(int j = 0; j<q.num_questions; j++){
        
    }
}


void sauvegarder_question(Question* q){
    fprintf(f,"%s\n", q->texte);
    fprintf(f,"%d\n", q->num_correct);
    for(int k = 0; k<q->num_correct; k++){
        fprintf(f,"%c:%s", 'A'+k, q->correct[i]);
    }
}
