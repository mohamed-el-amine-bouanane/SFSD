#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "conio.h"
#include "Interfaces.h"

void acceuil (){
  system("mode con LINES=40 COLS=120");
    int x,y;
    gotoxy(40,15);
    textcolor(15);
    system ("pause ");
    gotoxy(1,2);
    x=wherex();
    y=wherey();
    gotoxy(x,y);
    printf(" ______  _____  __ ");
    gotoxy(x,y+1);
    printf("|  ____|/ ____||__|");
    gotoxy(x,y+2);
    printf("| |__  | (___   __ ");
    gotoxy(x,y+3);
    printf("|  __|  \\___ \\ |  |");
    gotoxy(x,y+4);
    printf("| |____ ____) ||  |");
    gotoxy(x,y+5);
    printf("|______|_____/ |__|");
    textcolor(9);
    gotoxy(x+15,y);
    printf(" __");
    gotoxy(x+15,y+1);
    printf("|__|");
    textcolor(15);
    gotoxy(x+21,y+1);
    printf("%ccole nationale",144);
    gotoxy(x+21,y+3);
    printf("Sup%crieure",130);
    gotoxy(x+21,y+5);
    printf("d'Informatique");

    gotoxy(25,11);
    printf("   TP du module structure de fichier et structure de donn%cs",130);

      textcolor(9);
    gotoxy(4,12);
    x=wherex();
    y=wherey();
    gotoxy(x,y);
    printf("                      _ _           _   _                   _                        _   _              ");
    gotoxy(x,y+1);
    printf("    /\\               | (_)         | | (_)                 | |                      | | (_)             ");
    gotoxy(x,y+2);
    printf("   /  \\   _ __  _ __ | |_  ___ __ _| |_ _  ___  _ __     __| | ___    __ _  ___  ___| |_ _  ___  _ __   ");
    gotoxy(x,y+3);
    printf("  / /\\ \\ | '_ \\| '_ \\| | |/ __/ _` | __| |/ _ \\| '_ \\   / _` |/ _ \\  / _` |/ _ \\/ __| __| |/ _ \\| '_ \\");
    gotoxy(x,y+4);
    printf(" / ____ \\| |_) | |_) | | | (_| (_| | |_| | (_) | | | | | (_| |  __/ | (_| |  __/\\__ \\ |_| | (_) | | | |");
    gotoxy(x,y+5);
    printf("/_/    \\_\\ .__/| .__/|_|_|\\___\\__,_|\\__|_|\\___/|_| |_|  \\__,_|\\___|  \\__, |\\___||___/\\__|_|\\___/|_| |_| ");
    gotoxy(x,y+6);
    printf("         | |   | |                                                    __/ |                     ");
    gotoxy(x,y+7);
    printf("         |_|   |_|                                                   |___/                              ");
    textcolor(15);
    textcolor(9);
    gotoxy(9,20);
    x=wherex();
    y=wherey();
    gotoxy(x,y);
    printf("\t\t\t     _        _ _                                                                                     ");
    gotoxy(x,y+1);
    printf("\t\t\t    | |      | (_)                                                                                              ");
    gotoxy(x,y+2);
    printf("\t\t\t  __| | ___  | |_ _    _ _ __ ___  ___" ) ;
    gotoxy(x,y+3);
    printf("\t\t\t / _` |/ _ \\ | | | \\  / | '_// _ \\/ __|");
    gotoxy(x,y+4);
    printf("\t\t\t| (_| || __/ | | |\\ \\/ /| |  | __/\\__ \\ ");
    gotoxy(x,y+5);
    printf("\t\t\t \\__,_|\\___| |_|_| \\__/ |_|  \\___||___/");
    gotoxy(x,y+6);
    printf("                         ");
    gotoxy(x,y+7);
    printf("                     ");
    textcolor(15);

    gotoxy(5,32);
    textcolor(15);
    printf("Projet supervise par Mme EL ALLIA NADIA");
    gotoxy(45,32);
    x=wherex();
    y=wherey();
    printf("|");
    gotoxy(x,y+1);
    printf("|");
    gotoxy(x,y+2);
    printf("|");
    gotoxy(x,y+3);
    printf("|");
    gotoxy(x,y+4);
    printf("|");
    gotoxy(50,34);
    printf("realis%c par BOUANANE MOHAMMED & FALEK MEHDI ",130);
    gotoxy(50,35);
    printf("Ann%ce scolaire 2020/2021",130);
    gotoxy(35,30);
    printf("appuyer sur une touche pour continuer...");
    getch();
}
 void menu1 ()
{
    textbackground(7);
    system("CLS");
    gotoxy(35,5);
    textcolor(2);
    textbackground(7);
    printf("_______________________________________________");
         printf("\n");
    gotoxy(35,6);
    textbackground(14);
    printf("|   MENU POUR GERER LES LIVRES DE LA BIB      |");
    gotoxy(35,7);
    printf("|_____________________________________________|");
    gotoxy(15,12);
    textcolor(14);
    textbackground(12);
    printf("Les choix  :");
    gotoxy(20,15);
    textcolor(2);
    textbackground(15);
    printf("1_--------------> Cr%cation du fichier Ouvrages.bin.",130);
    gotoxy(20,17);
    textcolor(2);
    textbackground(15);
   printf("2_--------------> Recherche d'un ouvrage .");
    gotoxy(20,19);
    textcolor(2);
    textbackground(15);
    printf("3_--------------> Insertion de l\'arrivage d'un nouvel ouvrage.");
    gotoxy(20,21);
    textcolor(2);
    textbackground(15);
    printf("4_--------------> Modification de l\'%ctat d'un ouvrage donn%c.",130,130);
    gotoxy(20,23);
    textcolor(2);
    textbackground(15);
    printf("5_--------------> Cr%cation de : Livres.bin , Memoire.bin , Articles.bin , Periodiques.bin.",130);
    gotoxy(20,25);
    textcolor(2);
    textbackground(15);
    printf("6_--------------> Recherche d\'un p%criodique donn%c.",130,130);
      gotoxy(20,27);
    textcolor(2);
    textbackground(15);
    printf("7_--------------> Cr%cation de la table d\'index primaire.",130);
     gotoxy(20,29);
    textcolor(2);
    textbackground(15);
    printf("8_--------------> Recherche d'un p?riodique donn? ? partir de l'index et affichage de tous ces champs",130);
     gotoxy(20,31);
    textcolor(2);
    textbackground(15);
      printf("9_--------------> Affichage de l\'en-t%cte d\'un fichier donn%c en param%ctre.",131,130,129);
     gotoxy(20,33);
    textcolor(2);
    textbackground(15);
   printf("10_--------------> Affichage du contenu d\'un bloc donn%c d\'un fichier donn%c.",130,130);
     gotoxy(20,35);
    textcolor(2);
    textbackground(15);
    printf("11_--------------> Affichage du contenu de tout le fichier bloc par bloc pour un fichier donn%c.",130);
     gotoxy(20,37);
    textcolor(2);
    textbackground(15);
    printf("0_--------------> Quiter.");

    }
