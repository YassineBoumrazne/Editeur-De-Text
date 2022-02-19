#include "Editeur de text.h"


//main
int main() {
    //on va créer deux pile G "G contient les caractères avant le curseur" et D "D contient les caractères aprés le curseur"
    TPileC *G=CreePile();
    TPileC *D=CreePile();
    // ici on a Créé une boucle infinie pour la répétition du Menu
    while(1){
        system("cls");
        Menu(G,D);
    }

	return 0;
}

