#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "conio.h"
#include "FONCTIONS.c"
int main()
{


    int choix;
    srand(time(0));
    acceuil();
    TOF *f2;
    FILE *f3;
    ind d;
    int i,j,cle,cle2,cle3,chek;
    char chaine[6]="";
    TOVC *f1;
    int trouv;
    LOV *f,*Fm;
home:
    menu1();
    gotoxy(50,39);
    cprintf("votre choix:");
    scanf("%i",&choix);
    switch (choix)
    {
    case 1:
        textbackground(15);
        system("CLS");
        printf("Initialisation du fichier Ouverage.bin ...\n");
        /**Creation de fichier Ouverages.bin**/
        initialisation("Ouvrages.bin",&f);
        printf("Fichier Ouverages.bin cr%ce.\n",130);
        gotoxy(35,20);
        textcolor(5);
        textbackground(7);
        printf("Appuyer sur une touche pour revenir au menu ");
        getch();
        goto home;

        break;
    case 2:
        textbackground(15);
        system("CLS");
        gotoxy(10,8);
        printf("Affichage du fichier Ouverages.bin: \n");
        /**Affichage de fichier Ouverages.bin**/
        printf_Block(&f);
        getch();
        goto home;


        break;
    case 3:
        textbackground(15);
        system("CLS");
        gotoxy(35,20);
        printf("insertion reussite");
        textcolor(5);
        textbackground(7);
        printf("Appuyer sur une touche pour revenir au menu ");
        getch();
        goto home;
        break;
    case 4:
        textbackground(15);
        system("CLS");
        gotoxy(10,8);
        printf("\n entrere la valeur du cle 2 a modifier: ");
        scanf("%d",&cle2);
        modification(&f,cle2);
        gotoxy(35,20);
        textcolor(5);
        textbackground(7);
        printf("Appuyer sur une touche pour revenir au menu ");
        getch();
        goto home;


        break;
    case 5:
        textbackground(15);
        system("CLS");
        gotoxy(10,8);
        Memoire(&Fm);
        creation_TOVC_Livre("Ouvrages.bin",&f,"Livres.bin",&f1);
        creation_TOVC_Article("Ouvrages.bin",&f,"Articles.bin",&f1);
        creation_ind(&f3);
        gotoxy(35,20);
        textcolor(5);
        textbackground(7);
        printf("Appuyer sur une touche pour revenir au menu ");
        getch();
        goto home;
        break;
    case 6:
        textbackground(15);
        system("CLS");
        gotoxy(10,8);
        printf("donner le cle a recherche: ");
        scanf("%s",chaine);
        recherche_dicho(&f2,chaine,&trouv,&i,&j);
        gotoxy(35,20);
        textcolor(5);
        textbackground(7);
        printf("Appuyer sur une touche pour revenir au menu ");
        getch();
        goto home;
        break;

    case 7:
        textbackground(15);
        system("CLS");
        gotoxy(10,8);
        creation_ind(&f2);
        gotoxy(35,20);
        textcolor(5);
        textbackground(7);
        printf("Appuyer sur une touche pour revenir au menu ");
        getch();
        goto home;
        break;

    case 8:
        textbackground(15);
        system("CLS");
        gotoxy(10,8);
        printf("\n entrer votre chaine  : \n");
        scanf("%d",&cle3);
        Recherche_index(f2,cle3,&trouv,&d);
        affich_ind(f2);
        gotoxy(35,20);
        textcolor(5);
        textbackground(7);
        printf("Appuyer sur une touche pour revenir au menu ");
        getch();
        goto home;
        break;

    case 9:
        textbackground(15);
        system("CLS");
        gotoxy(10,8);
        printf("\n entrer votre chaine  : \n");
        scanf("%s",chaine);
        affich_entet(chaine);
        gotoxy(35,20);
        textcolor(5);
        textbackground(7);
        printf("Appuyer sur une touche pour revenir au menu ");
        getch();
        goto home;
        break;

    case 10:
        textbackground(15);
        system("CLS");
        gotoxy(10,8);
        printf_Block(&f);
        gotoxy(35,20);
        textcolor(5);
        textbackground(7);
        printf("Appuyer sur une touche pour revenir au menu ");
        getch();
        goto home;
        break;

    case 11:
        textbackground(15);
        system("CLS");
        gotoxy(10,8);
        printf_Block(&f);
        gotoxy(35,20);
        textcolor(5);
        textbackground(7);
        printf("Appuyer sur une touche pour revenir au menu ");
        getch();
        goto home;
        break;
    case 0:
        textbackground(15);
        system("CLS");
        gotoxy(10,8);
        textcolor(12);
        textbackground(15);
        gotoxy(40,10);
        printf("____________________________________________");
        gotoxy(40,11);
        printf("| Merci pour l'utilisation de ce programme |");
        gotoxy(40,12);
        printf("|__________________________________________|");
        Sleep(3000);
        exit(EXIT_SUCCESS);
        break;

    default:
        textbackground(15);
        system("CLS");
        gotoxy(43,15);
        textcolor(12);
        textbackground(15);
        printf("donner une valeur entre 1 et 8");
        gotoxy(70,24);
        textcolor(5);
        textbackground(7);
        printf("Appuyer sur une touche pour revenir au menu ");
        getch();
        break;


    }

    initialisation("Ouvrages.bin",&f);
    //scanf("\n %d",&cle);
    //recherche_LOV(&f,cle,&trouv,&i,&j);
    //printf("trouver : %d   le  i  : %d   le j est : %d ",trouv,i,j);
    printf("\n entrere la valeur du cle 2 : \n");
    //  scanf("%d",&cle2);
    //modification(&f,cle2);
    Memoire(&Fm);
    creation_TOVC_Livre("Ouvrages.bin",&f,"Livres.bin",&f1);
    creation_TOVC_Article("Ouvrages.bin",&f,"Articles.bin",&f1);
    return 0;

    return 0;
}
