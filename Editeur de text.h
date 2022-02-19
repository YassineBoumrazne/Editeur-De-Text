/*
    Auteurs : Yassine BOUMRAZNE
    Date : 9/8/2021
*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

// Ctrl + k nb on va passer le caractere k à la fonction CTRL_KEYPRESS(k)
#define CTRL_KEYPRESS(k) ((k)  & 0x1f)

// colors
#define COLOR_CYAN    "\x1b[36m"
#define COLOR_RESET   "\x1b[0m"
//
//
                    /*Debut D'exercice*/

struct maillon{
    char c;
    struct maillon *pSuivant;
};
typedef struct maillon Tmaillon;

struct pileC{
    Tmaillon *sommet;

};
typedef struct pileC TPileC;


//Fonction pour créer une pile
TPileC* CreePile(){
    TPileC *pile=malloc(sizeof(TPileC));
    pile->sommet=NULL;
    return pile;
}



//Fonction pour créer un nouveau Maillon et l'affecter le caractere c comme une valeur et la maillon suivant point sur NULL

Tmaillon *CreeMaillon(TPileC p,char c){
    Tmaillon *pm=malloc(sizeof(Tmaillon));
    pm->c=c;
    pm->pSuivant=NULL;
    return pm;
}



// Fonction pour Tester est ce que la pile est vide
int PileVide(TPileC pile){
    return (pile.sommet==NULL);
}



// Fonction pour Inserer un caractere avant le curseur   exp: H -> He|  'NB : on suppose que le caractere '|' est le curseur'
TPileC* InsererAvant(TPileC *G,char c){
    Tmaillon *pm=CreeMaillon(*G,c);
    if(pm==NULL) return NULL;
    pm->pSuivant=G->sommet;
    G->sommet=pm;
    return G;
}


//Fonction pour effacer le caractère suivant le curseur   exp: Hell|o -> Hell|
TPileC* EffacerCarSuit(TPileC *D){
    if(PileVide(*D))
        return NULL;
    Tmaillon *pT=D->sommet;

    D->sommet=D->sommet->pSuivant;
    free(pT);
    return D;
}



//Fonction pour effacer le caractère avant le curseur   exp: Hell|o -> Hel|o
TPileC* EffacerCarPrec(TPileC *G){
    if(PileVide(*G))
        return NULL;
    Tmaillon *pT=G->sommet;

    G->sommet=G->sommet->pSuivant;
    free(pT);
    return G;
}



//Fonction pour Avancer par curseur  exp: Hell|o -> Hello|
int Avancer (TPileC *G, TPileC *D){
    if(PileVide(*D)) return 0;
    if(InsererAvant(G,D->sommet->c)==NULL) return 0;
    EffacerCarSuit(D);
    return 1;
}



//Fonction pour Reculer par curseur    exp: Hell|o -> Hel|lo
int Reculer (TPileC *G, TPileC *D){
    if(PileVide(*G)) return 0;
    if(InsererAvant(D,G->sommet->c)==NULL) return 0;
    EffacerCarSuit(G);
    return 1;
}



// Fonction pour la recherche d'un caractere
//-exp1: on va rechercher sur 'u':  |Taroudant -> Tarou|dant
//-exp2: on va rechercher sur 'm':  |Taroudant -> Taroudant|
int Rechercher(TPileC *G, TPileC *D, char c){
    // ona va rechercher Aprés le curseur alor on va avancer jusqu'à on trouve le c si non le curseur va à la fin de text
    while(Avancer(G,D)){
        if(G->sommet->c==c){
            return 1;
        }
    }
    return 0;
}



// Procédur pour placer le curseur au début de la ligne où se trouve le curseur
void Debut(TPileC *G, TPileC *D){
    if(PileVide(*G)) return;
    while(Reculer(G,D) && !PileVide(*G)){
        if(G->sommet->c=='\n'){
            break;
        }
    }
}


// Procédur pour Afficher une pile donner comme parametre
void Afficher(TPileC pile){
    Tmaillon *pT=pile.sommet;
    while(pT!=NULL){
        printf("%c",pT->c);
        pT=pT->pSuivant;
    }
}

//Procédur pour Supprimer une pile donner comme parametre
void FreePile(TPileC *pile){
    Tmaillon *pT;
    while(!PileVide(*pile)){
        pT=pile->sommet;
        pile->sommet=pile->sommet->pSuivant;
        free(pT);
    }
}

// Procédur pour Afficher une pile en inverse
void AfficherInverse(TPileC pile){
    Tmaillon *pT=pile.sommet;
    TPileC *pileT=CreePile();
    while(pT!=NULL){
        InsererAvant(pileT,pT->c);
        pT=pT->pSuivant;
    }
    Afficher(*pileT);
    FreePile(pileT);
}



// Menu principale
void Menu(TPileC *G,TPileC *D){
    int choice;
    system("cls");
    printf("\n\n\t\t\t\tMenu");
    printf("\n\t\t\t1- Inserer une text");
    printf("\n\t\t\t2- Afficher");
    printf("\n\t\t\t0- Exit");
    printf("\n\n\t\t\t Votre Choix: ");
    fflush(stdin);
    scanf("%d",&choice);
    system("cls");
    int c,c3,c2;
    fflush(stdin);
    switch(choice){
    case 0:
        exit(1);
    case 1:
        //Alor dans le cas  d'insertion on permet à l'utilisateur de saissir le texte jusqu'à Press ctrl+s pour enregistrer le text
        printf("--------------------------------------------------------------------------------------------------------------------\n");
        printf(COLOR_CYAN "| Enregistrer:CTRL+S | Rechercher:CTRL+F | Debut:CTRL+D | Supprimer_Prec:BackSpace | Supprimer_Suiv:CTRL+BackSpace |" COLOR_RESET);
        printf("\n--------------------------------------------------------------------------------------------------------------------\n\n");
        AfficherInverse(*G);printf(COLOR_CYAN "|" COLOR_RESET);Afficher(*D);
        while((c=getch())!= CTRL_KEYPRESS('s')){
                c2 = 0;
                switch(c){
                case 0xE0:
                    // a scroll key was pressed
                    c2 = getch();
                    // determine what it was
                    //Flèche gauche Reculer
                    if(c2==75) Reculer(G,D);
                    //Flèche droite Avancer
                    else if(c2==77) Avancer(G,D);
                    break;
                case CTRL_KEYPRESS('f'):
                    // ctrl + r pour la recherche
                    system("cls");
                    printf("Saisissez le caract%cre %c rechercher: ",138,133);
                    fflush(stdin);
                    scanf("%c",&c3);
                    Rechercher(G,D,c3);
                    break;
                case CTRL_KEYPRESS('d'):
                    // ctrl + D placer le cureur au début de la ligne
                    Debut(G,D);
                    break;
                case 8:
                    //BackSpace code ASKII est 8
                    EffacerCarPrec(G);
                    break;
                case 127:
                    //ctrl + backspace code ASKII est 127
                    EffacerCarSuit(D);
                    break;
                case 13:
                    //Enter code askii est 13
                    InsererAvant(G,'\n');
                    break;
                default:
                    InsererAvant(G,c);
                    break;
                }
                system("cls"); //clean screen
                printf("--------------------------------------------------------------------------------------------------------------------\n");
                printf(COLOR_CYAN "| Enregistrer:CTRL+S | Rechercher:CTRL+F | Debut:CTRL+D | Supprimer_Prec:BackSpace | Supprimer_Suiv:CTRL+BackSpace |" COLOR_RESET);
                printf("\n--------------------------------------------------------------------------------------------------------------------\n\n");
                //chaque insertion d'un caractere on va afficher les pile G avant le curseur et D aprés le curseur
                AfficherInverse(*G);printf(COLOR_CYAN "|" COLOR_RESET);Afficher(*D);
            }
        printf("\n\nTexte enregistr%c",130);
        getch();
        break;
    case 2:
        AfficherInverse(*G);Afficher(*D);
        printf("\n\nPress any key");
        getch();
        break;
    default:
        printf("veuillez saisir un choix valide!!");
        getch();
        break;
    }
}


