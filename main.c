#include "Editeur de text.h"


//main
int main() {
    //on va cr�er deux pile G "G contient les caract�res avant le curseur" et D "D contient les caract�res apr�s le curseur"
    TPileC *G=CreePile();
    TPileC *D=CreePile();
    // ici on a Cr�� une boucle infinie pour la r�p�tition du Menu
    while(1){
        system("cls");
        Menu(G,D);
    }

	return 0;
}

