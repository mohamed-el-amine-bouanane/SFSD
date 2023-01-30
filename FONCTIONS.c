#define max_tab 1024
#define max_resume 100
#define max_caractere 80
#define max_tab_TOF 4

/**Livres(L),mémoire(M),Article(A),Périodique(P)*/

/***********************************************************************************************************/

/**************************************LES STRUCTURES*****************************************************/

/*******************************************************************************************************/

/**************************************LOV(C/~C)******************************************************/
typedef struct Tbloc
{
    char tab[max_tab];
    int suivant;
    int nb_char;

} Tbloc;

typedef struct Tbloc Buffer;
typedef struct maillon
{
    char num_livre[5];
    char titre[11];///le 11 eme est pour '\0'
    char auteur[11];///le 11 eme est pour '\0'
    char type;
    int annee_de_pub;
    char dispo;
    char cote[7];///le 7 eme est pour '\0'
    char resume[max_resume];
} Article;


typedef struct Entete
{
    int nbbloc;
    int tete;
    int queue;
    int car_inseree;
    int car_supr;
} Entete;

typedef struct LOV
{
    FILE *fich;
    Entete entete;
} LOV;
/*******************************************************************************************************/

/**************************************TOV(C/~C)******************************************************/

typedef struct Tbloc_TOVC
{
    char tableau[max_caractere];  /// puisque taille variable => (bloc = tableau de caractère)
} Tbloc_TOVC ;
typedef struct Tbloc_TOVC Buffer_TOVC;
typedef struct maillon_TOVC
{
    char num_livre[5];
    char titre[11];///le 11 eme est pour '\0'
    char auteur[11];///le 11 eme est pour '\0'
    int annee_de_pub;
    char dispo;
    char cote[7];///le 7 eme est pour '\0'
    char resume[max_resume];
} Article_TOVC;
typedef struct Entete_TOVC
{
    int adr_dernier_bloc ;       /// @ du dernier bloc, pas besoin du 1er bloc puisque la structure est un tableau => contigûe
    int pos_libre_dernier_bloc; /// nécessaire aux décalages pour l'insertion ordonnée
    int nbr_caract_insert ;      /// nécessaire pour la comparaison avec nbr caractères supprimés
    int nbr_caract_supp ;        /// si > 50% => réorganisation du fichier
} Entete_TOVC ;
typedef struct TOVC
{
    FILE * f ;
    Entete_TOVC entete_TOVC ;
}   TOVC ;
/*************************************************************************************************/

/**************************************TOF******************************************************/
typedef struct maillon_TOF
{
    char num_livre[5];///le 5 eme est pour '\0'
    char titre[11];///le 11 eme est pour '\0'
    char auteur[11];///le 11 eme est pour '\0'
    int annee_de_pub;
    char dispo;
} Article_TOF;
typedef struct Tbloc_TOF
{
    Article_TOF T[max_tab_TOF];
    int nb_enreg;

} Tbloc_TOF;
typedef struct Tbloc_TOF Buffer_TOF;
typedef struct Entete_TOF
{
    int nb_bloc;
    int nb_article;
} Entete_TOF;

typedef struct TOF
{
    FILE *fich;
    Entete_TOF entete_TOF;
} TOF;
/*************************************************************************************************/

/**************************************TOF******************************************************/

typedef struct ind
{
    int cle ;
    int bloc ;
    int indice ;
} ind;
/************************************************************************************************/

/**********************************************************************************************/

/**************************           LES MACHINES ABSTRAITES          **********************/

/**********************************************************************************************************/

/********************************************************************************************************/

/**************************          **TOF**           ************************************************/
int entete_TOF(TOF *f,int i)
{
    if(i == 1)
        return (f->entete_TOF).nb_bloc;
    else if(i == 2)
        return (f->entete_TOF).nb_article;
    else
        return -1;
}
void aff_entete_TOF(TOF *f, int i, int val)
{
    if(i == 1)
        (f->entete_TOF).nb_bloc = val;
    else if(i == 2)
        (f->entete_TOF).nb_article = val;
}
int ouvrir_TOF(TOF **f,char *chemin,char mode)
{
    *f = malloc(sizeof(TOF));
    char s[4];

    if((mode == 'A') || (mode == 'a'))
        sprintf(s,"rb+");
    else if ((mode == 'N') || (mode == 'n'))
        sprintf(s,"wb+");
    else
        return 0;

    (*f)->fich = fopen(chemin, s);
    if((*f)->fich == NULL)
        return 0;

    if((mode == 'A') || (mode == 'a'))
    {
        fread(&((*f)->entete_TOF), sizeof(Entete_TOF), 1, (*f)->fich);
    }
    else if ((mode == 'N') || (mode == 'n'))
    {
        (*f)->entete_TOF.nb_bloc = 0;
        (*f)->entete_TOF.nb_article = 0;
        fwrite(&((*f)->entete_TOF), sizeof(Entete_TOF),1, (*f)->fich);
    }
    return 1;
}
void fermer_TOF(TOF *f)
{
    rewind(f->fich);
    fwrite(&(f->entete_TOF), sizeof(Entete_TOF), 1, f->fich);
    fclose(f->fich);
    free(f);
}
void lireDir_TOF(TOF *f,int N_Bloc,Tbloc_TOF *buffer)
{
    if(N_Bloc <= (f->entete_TOF).nb_bloc)
    {
        fseek(f->fich, sizeof(Entete_TOF) + (N_Bloc-1) * sizeof(Tbloc_TOF),SEEK_SET);
        fread(buffer, 1, sizeof(Tbloc_TOF), f->fich);
    }
}
void ecrireDir_TOF(TOF *f,int N_Bloc,Tbloc_TOF *buffer)
{
    fseek(f->fich, sizeof(Entete_TOF) + (N_Bloc-1) * sizeof(Tbloc_TOF),SEEK_SET);
    fwrite(buffer, 1, sizeof(Tbloc_TOF), f->fich);
}
int alloc_bloc_TOF(TOF *f)
{
    aff_entete_TOF(f,1,entete_TOF(f,1)+1);
    return entete_TOF(f,1);
}

/**************************************LOV(C/~C)******************************************************/

void aff_entete(LOV *fichier,int i, int valeur)
{

    switch(i)
    {
    case 1:
    {
        /// nb bloc alloués dans le fichier
        fichier->entete.nbbloc=valeur;
    }
    break;
    case 2:
    {
        /// nb bloc representatnt la tete du fichier
        fichier->entete.tete=valeur;
    }
    break;
    case 3:
    {
        /// nb bloc representatnt la queue du ficheir
        fichier->entete.queue=valeur;
    }
    break;
    case 4:
    {

        /// nombre de caractères suprimé depuis la création du ficher
        fichier->entete.car_inseree=valeur;

    }
    break;
    case 5:
    {

        /// nombre de caractères suprimé depuis la création du ficher
        fichier->entete.car_supr=valeur;
    }
    break;
    };
}
int entete(LOV *fichier, int i)
{

    switch(i)
    {
    case 1:
    {
        return(fichier->entete.nbbloc);
    }
    break;
    case 2:
    {
        return(fichier->entete.tete);
    }
    break;
    case 3:
    {
        return(fichier->entete.queue);
    }
    break;
    case 4:
    {
        return(fichier->entete.car_inseree);
    }
    break;
    case 5:
    {
        return(fichier->entete.car_supr);
    }
    break;
    };
    return 0;
}
void liredir(LOV *fichier, int i, Buffer *buf)
{
    fseek(fichier->fich,(sizeof(Entete)+sizeof(Tbloc)*(i-1)),SEEK_SET);
    fread(buf,sizeof(Buffer),1,fichier->fich);
    rewind(fichier->fich);
}
void ecriredir(LOV *fichier, int i, Buffer buf)
{
    fseek(fichier->fich,sizeof(Entete)+sizeof(Tbloc)*(i-1),SEEK_SET);
    fwrite(&buf,sizeof(Buffer),1,fichier->fich);
}
LOV *ouvrir(char nom_physique[], char mode)
{
    LOV *fichier=malloc(sizeof(LOV));
    Buffer buf;
    /// mode ancien
    if( (mode=='A') ||  (mode == 'a') )
    {
        fichier->fich=fopen(nom_physique,"rb+");
        fread(&(fichier->entete),sizeof(Entete),1,fichier->fich);
    }
    else
    {
        /// mode nouveau
        if( (mode=='N') ||  (mode == 'n') )
        {
            fichier->fich=fopen(nom_physique,"wb+");
            aff_entete(fichier,1,0);
            aff_entete(fichier,2,1);
            aff_entete(fichier,3,1);
            aff_entete(fichier,4,0);
            aff_entete(fichier,5,0);
            fwrite(&(fichier->entete),sizeof(Entete),1,fichier->fich);
            buf.suivant=-1;
            sprintf(buf.tab,"%s","");
            ecriredir(fichier,1,buf);
        }
        else
        {
            printf("format d'ouverture impossible");
        }
    }
    return(fichier);
}
void fermer(LOV *fichier)
{
    rewind(fichier->fich);
    fwrite(&(fichier->entete),sizeof(Entete),1,fichier->fich);                                                                  //dans le fichier
    rewind(fichier->fich);
    fclose(fichier->fich);
}
void  alloc_bloc(LOV *fichier)
{
    /// allocation du Buffer
    Buffer *buf=malloc(sizeof(Buffer));
    /// lecture du bloc correspondant a la queue
    liredir(fichier,entete(fichier,3),buf);
    /// mise a jour du suiv
    buf->suivant=entete(fichier,1)+1;
    /// ecriture du bloc de queue dans le fichier
    ecriredir(fichier,entete(fichier,3),*buf);
    aff_entete(fichier,3,entete(fichier,1)+1);
    buf->suivant=-1;
    buf->nb_char=0;
    /// vider la chaine du buffer
    sprintf(buf->tab,"%s","");
    /// ecriture du buffer dans le bloc representatnt la nouvelle queue
    ecriredir(fichier,entete(fichier,3),*buf);
    /// incrémentation
    aff_entete(fichier,1,entete(fichier,1)+1);
}

/**************************************TOV(C/~C)******************************************************/

int entete_TOVC(TOVC * fichier, int i)
{
    if (i ==1)
    {
        return(fichier->entete_TOVC.adr_dernier_bloc);
    }
    else if (i == 2)
    {
        return(fichier->entete_TOVC.pos_libre_dernier_bloc);
    }
    else if (i== 3)
    {
        return(fichier->entete_TOVC.nbr_caract_insert);
    }
    else
    {
        return(fichier->entete_TOVC.nbr_caract_supp);
    }
}
void Aff_Entete_TOVC(TOVC * fichier, int i, int val)
{
    if (i == 1)
    {
        fichier->entete_TOVC.adr_dernier_bloc = val;
    }
    else if (i == 2)
    {
        fichier->entete_TOVC.pos_libre_dernier_bloc = val;
    }
    else if (i == 3)
    {
        fichier->entete_TOVC.nbr_caract_insert = val;
    }
    else
    {
        fichier->entete_TOVC.nbr_caract_supp = val;
    }
}
TOVC * Ouvrir_TOVC (char nom_fichier[30], char mode_ouverture)
{
    TOVC * fichier = malloc(sizeof(TOVC));
    if ((mode_ouverture == 'n')||(mode_ouverture == 'N'))
    {
        fichier->f = fopen(nom_fichier,"wb+") ;
        if (fichier->f != NULL)
        {
            printf(" ouverture du fichier reussie\n\n");
            fichier->entete_TOVC.adr_dernier_bloc = 0;
            fichier->entete_TOVC.pos_libre_dernier_bloc = 0 ;
            fichier->entete_TOVC.nbr_caract_insert = 0 ;
            fichier->entete_TOVC.nbr_caract_supp = 0;
            rewind(fichier->f);
            fwrite(&(fichier->entete_TOVC),sizeof(Entete_TOVC),1,fichier->f);///pourqoui il n'a pas fait directement size_of(entete)
        }
        else
        {
            printf("fichier mal cree\n");
        }
    }
    else
    {
        if ((mode_ouverture == 'a')||(mode_ouverture == 'A'))
        {
            fichier->f = fopen(nom_fichier,"rb+");
            if (fichier->f!= NULL)
            {
                printf("\nouverture du fichier reussie\n");
                rewind(fichier->f);
                fread(&(fichier->entete_TOVC),sizeof(Entete_TOVC),1,fichier->f);
            }
            else
            {
                printf("\n fichier mal ouvert,vous devez le cree\n");
            }
        }
    }
    return(fichier);
}
void Fermer_TOVC(TOVC * fichier)
{
    rewind(fichier->f);
    fwrite(&(fichier->entete_TOVC),sizeof(Entete_TOVC),1,fichier->f);
    fclose(fichier->f);
    free(fichier);
}
void Ecriredir_TOVC(TOVC * fichier, int i, Tbloc_TOVC buf)
{
    fseek(fichier->f,sizeof(Entete_TOVC)+(sizeof(Tbloc_TOVC)*(i-1)),SEEK_SET);
    fwrite(&buf,sizeof(Tbloc_TOVC),1,fichier->f);
}
void Liredir_TOVC(TOVC * fichier, int i, Tbloc_TOVC * buf)
{
    fseek(fichier->f,sizeof(Entete_TOVC)+(sizeof(Tbloc_TOVC)*(i-1)),SEEK_SET);
    fread(buf,sizeof(Tbloc_TOVC),1,fichier->f);
}
void Alloc_bloc_TOVC(TOVC * fichier)
{
    Aff_Entete_TOVC(fichier,1,entete_TOVC(fichier,1)+1);
}
/**********************************************************************************************************/

/**************************************LES FONCTIONS******************************************************/

/**********************************************************************************************************/


void turn_to_string(char chaine[], int n, int longueur)
{
    ///transformer un entier vers une chaine de taille precese
    int k;
    for(k=longueur-1; k>=0; k--)
    {
        chaine[k]=(n%10)+'0';
        n=n/10;
    }
    chaine[longueur]='\0';
}

char  *Aleachaine ( int N )
{
    int k;
    char  * Chaine = malloc(N+1);

    char Chr1[26] = "abcdefghijklmnopqrstuvwxyz";
    char Chr2[26] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    for (k=0; k<N; k++)
        switch ( rand() % 2 )
        {
        case 0 :
            *(Chaine+k) = Chr1[rand() % 26] ;
            break ;
        case 1 :
            *(Chaine+k) = Chr2[rand() % 26] ;
            break ;
        }
    Chaine[k] =  '\0' ;

    return (Chaine);
}

int Aleanombre( int N )
{
    return ( rand() % N );
}

/**************************************LOV(C/~C)******************************************************/
void printf_Block(LOV *(*f))
{
    int i;
    Buffer *Buf=malloc(sizeof(Buffer));
    *f=ouvrir("Ouvrages.bin",'A');
    for (i=1;i<entete(*f,1);i++)
    {
        liredir(*f,i,Buf);
        printf("\nle nb char:\n%d",Buf->nb_char);
        printf("\nle suiv:\n%d",Buf->suivant);
        printf("\nle tableau: %d\n%s",i,Buf->tab);
    }

}

char *identif(void)
{
    ///pour generer un identifiant pour un livre aleatoirement
    int i=0,a;
    char l[1]="";
    char *id= malloc(5*sizeof(char));
    strcpy(id,"");
    while(i<4)
    {
        a=rand()%10;
        itoa(a,l,10);
        strcat(id,l);
        i++;
    }
    return (id);
}
/// pour remplire une chaine de caractere par des champs de valeur random
char *remplirArticle()
{
    Article Livre;
    /**
    initialisation par des chaines vides
    */
    strcpy(Livre.titre,"");
    strcpy(Livre.auteur,"");
    strcpy(Livre.num_livre,"");
    strcpy(Livre.cote,"");
    strcpy(Livre.resume,"");
    ///_________________________
    int taille,alea;
    char tai[5]="";
    char year[5]="";
    char *Book=calloc(145,sizeof(char));
    /**
    initialisation par des chaine vides et apres des valeur random
    */
    strcpy(Book,"");
    sprintf(Livre.num_livre,"%s","");
    strcpy(Livre.num_livre,identif());///num livre
    strcpy(Livre.titre,Aleachaine(10));/// titre
    strcpy(Livre.auteur,Aleachaine(10));/// auteur
    /**
    pour choisir un type aleatoirement
    */
    alea=Aleanombre(4)+1;
    switch(alea)
    {
    case 1:
        Livre.type='L';
        break;
    case 2:
        Livre.type='M';
        break;
    case 3:
        Livre.type='A';
        break;
    case 4:
        Livre.type='P';
        break;
    default:
        printf("\nerror\n");
        break;
    }
    /**
    une annee entre 1950 & 2021
    */
    Livre.annee_de_pub=Aleanombre(72)+1950;
    alea=Aleanombre(2);
    if (alea)
        Livre.dispo='D';
    else
        Livre.dispo='N';
    strcpy(Livre.cote,Aleachaine(6));/// la cote
    alea=Aleanombre(50)+50;/// nombre aleatoire de caractere du resume
    strcpy(Livre.resume,Aleachaine(alea));
    taille=40+strlen(Livre.resume);/// la taille du resume + du autres champs
    turn_to_string(tai,taille,4);
    /**
    Remplissage dans les champs du livre
    */
    strcpy(Book,tai);
    Book[strlen(Book)]=Livre.dispo;
    strcat(Book,Livre.num_livre);
    strcat(Book,Livre.titre);
    strcat(Book,Livre.auteur);
    Book[strlen(Book)]=Livre.type;
    sprintf(year,"%d",Livre.annee_de_pub);
    strcat(Book,year);
    strcat(Book,Livre.cote);
    strcat(Book,Livre.resume);
    return(Book);
}
///--------------------------------------------------------------------------------------////
///--------------------------------------------------------------------------------------////
///--------------------------------------------------------------------------------------////
///--------------------------------------------------------------------------------------////
///--------------------------------------------------------------------------------------////
///--------------------------------------------------------------------------------------////
void affich_entet(char affichage[])
{
    TOF *f2;
    ind d;
    FILE *f3;
    TOVC *f1;
    LOV *f,*Fm;
    if(strcpy(affichage,"Ouvrages.bin")==0)
    {
        f=ouvrir("Ouvrages.bin",'A');
        printf("\nnbbloc: %d",entete(f,1));
        printf("\ntete: %d\n",entete(f,2));
        printf("\nqueue: %d\n",entete(f,3));
        printf("\ncar_inseree: %d\n",entete(f,4));
        printf("\ncar_inseree: %d\n",entete(f,4));
        printf("\ncar_supr: %d\n",entete(f,5));
        fermer(f);
    }
    else if(strcpy(affichage,"Livres.bin")==0)
    {
        f1=Ouvrir_TOVC("Ouvrages.bin",'A');
        printf("\nnbbloc: %d",entete_TOVC(f1,1));
        printf("\ntete: %d\n",entete_TOVC(f1,2));
        printf("\nqueue: %d\n",entete_TOVC(f1,3));
        printf("\ncar_inseree: %d\n",entete_TOVC(f1,4));
        printf("\ncar_inseree: %d\n",entete_TOVC(f1,4));
        printf("\ncar_supr: %d\n",entete_TOVC(f1,5));
        Fermer_TOVC(f1);
    }
    else if(strcpy(affichage,"Memoire.bin")==0)
    {
        f=ouvrir("Ouvrages.bin",'A');
        printf("\nnbbloc: %d",entete(f,1));
        printf("\ntete: %d\n",entete(f,2));
        printf("\nqueue: %d\n",entete(f,3));
        printf("\ncar_inseree: %d\n",entete(f,4));
        printf("\ncar_inseree: %d\n",entete(f,4));
        printf("\ncar_supr: %d\n",entete(f,5));
        fermer(f);
    }
    else if(strcpy(affichage,"Articles.bin")==0)
    {
        f1=Ouvrir_TOVC("Ouvrages.bin",'A');
        printf("\nnbbloc: %d",entete_TOVC(f1,1));
        printf("\ntete: %d\n",entete_TOVC(f1,2));
        printf("\nqueue: %d\n",entete_TOVC(f1,3));
        printf("\ncar_inseree: %d\n",entete_TOVC(f1,4));
        printf("\ncar_inseree: %d\n",entete_TOVC(f1,4));
        printf("\ncar_supr: %d\n",entete_TOVC(f1,5));
        Fermer_TOVC(f1);
    }
    else if(strcpy(affichage,"Periodiques.bin")==0)
    {
        ouvrir_TOF(f2,"Ouvrages.bin",'A');
        printf("\nnbbloc: %d",entete_TOF(f2,1));
        printf("\ntete: %d\n",entete_TOF(f2,2));
        printf("\nqueue: %d\n",entete_TOF(f2,3));
        printf("\ncar_inseree: %d\n",entete_TOF(f2,4));
        printf("\ncar_inseree: %d\n",entete_TOF(f2,4));
        printf("\ncar_supr: %d\n",entete_TOF(f2,5));
        fermer_TOF(f2);

    }
    else
        printf("\nerror nom introuvable!\n");
}
///--------------------------------------------------------------------------------------////
///--------------------------------------------------------------------------------------////
///--------------------------------------------------------------------------------------////
///--------------------------------------------------------------------------------------////
void initialisation(char NomFichier[30], LOV *(*f) )
{
    /***************************************/
    Buffer Buf;
    int T=max_tab,C1=0;
    char *Book=calloc(145,sizeof(char));
    int k = 0;
    int i=1;
    int j = 0;
    int len=0;
    char num[5];
    int nb,_nb=0;/// pour reserver les identifiant a l ordre
    int n=Aleanombre(50)+1;/// nombre de structures aleatoire
    /**
    ouverture du fichier
    */
    *f=ouvrir(NomFichier,'N');
    C1++;
    alloc_bloc(*f);
    C1++;
    strcpy(Buf.tab,"");
    while(k < n)/// repeter le travaile n fois ''' n est random '''-------------------!
    {
        strcpy(Book,remplirArticle());/// remplire
        for (j=5; j<9; j++)
        {
            num[j-5]=Book[j];/// extraction de l'id.
        }
        nb=atoi(num);
        if(nb>_nb)/// pour sauvegarder l ordre L'O'V
        {
            if ( nb==9999) /// if random goes with 9999 le dernier cas
                break;
            if (strlen(Book)<=T)/// place suffisant pour placer la chaine
            {
                strcat(Buf.tab,Book);
                len+=strlen(Book);
                T=T-strlen(Book);
            }
            else/// alloc block 'place insuff'
            {
                Buf.nb_char=len;
                ecriredir(*f,i,Buf);
                C1++;
                i++;
                len=0;
                T=max_tab;
                strcpy(Buf.tab,"");
                alloc_bloc(*f);
            }
            _nb=nb;/// l'ordre encore une fois
            k++;/// nombre de structure
        }
    }
    Buf.nb_char=len;
    ecriredir(*f,i,Buf);
    C1++;
    printf("\n Creation du fichier Ouvrages.bin ressite!\n");
    printf("\n||----------- Le cout de cette operation est: %d\n",C1);
    fermer(*f);
    //printf_Block(&*f);
}
/**
fonctions dtandard pour recupere une chaine apartire d une autre chaine du BUFFER
*/
void recuperer_chaine(LOV *fichier,int n , int *i, int *j, char chaine[],Buffer buf) //
   {

    int k=0;
    sprintf(chaine,"%s","");
    for(k=0;k<n;k++)                    // boucle de n itérations correspondant a la longueur de la chaine
    {
        if((*j)==strlen(buf.tab))       // indice de parcours de la chaine resultata et j celui du tableau
        {
        }
        if((*j)<buf.nb_char)                    // si le kièmem caractère de la chaine correspondant au j ime car du buffer  est toujour dans le bloc i
        {                               // le caractère 99 correspond a la fin de la chaine dans le tableau
            chaine[k]=buf.tab[(*j)];   // recuperation du caractère dans la position k de la chaine
            (*j)++;                      // deplacement d'une position dans le buffer
        }
        else                             // si le k ièeme caractère a recuperer sort du buffer
        {

            if((*i)!=1)
            {

                (*i)=buf.suivant;           // on passe au suivant du bloc i dans la liste
                liredir(fichier,(*i),&buf);   // lecture
                chaine[k]=buf.tab[0];       // recuperation du premier caractère du tableau de carractère correspondant au ka ième car de la chaine
                (*j)=1;
            }

            /// 7r7r                      //positionnement eu second caractère dans le nouveau buffer
        }
    }
   chaine[k]='\0';                        // fin de la chaine obtenue
}


///--------------------------------------------------------------------------------------////
///--------------------------------------------------------------------------------------////
///--------------------------------------------------------------------------------------////


void recherche_LOV(LOV  **fichier,int cle,int *trouv,int *i, int *j )
{
    Buffer buf;
    strcpy(buf.tab,"");
    char *ch1=malloc(sizeof(char)*5); // chaine pour recevoir la taille de l'info
    char *ch2=malloc(sizeof(char)*2);   // chaine pour recevoir le champ effacé
    char *ch3=malloc(sizeof(char)*5);   // chaine pour recevoir la cle
    char *chaine=malloc(sizeof(char)*1024); //chaine pour recevoir l'info'*/
    int stop=0;                          // booleen pour l'arret de la recherche
    int bloc,pos;
    (*trouv)=0;                          // initialisdation de trouv a 0
    (*i)=1;//entete(fichier,2);              // positionnement au bloc entete pour une recherche sequentielle
    (*j)=0;
    *fichier=ouvrir("Ouvrages.bin",'A');                              // première position
    if(entete(*fichier,1)!=0)             // si le fichier nest pas vide
    {
     liredir(*fichier,*i,&buf);     // lecture du premier bloc afin d'entammer le parcours
        //printf("\nla taille est: %c%c%c%c\n",buf.tab[0],buf.tab[1],buf.tab[2],buf.tab[3]);
        //printf("\n la tab 3 est :%s \n",buf.tab);
        //printf("\n la tab 3 est :%d \n",strlen(buf.tab));
        while((stop==0) && ((*trouv)==0)) // tant qu'on pas trouvé ou qu'on est pas a la fin du ficher
        {
            if((*j)==buf.nb_char){
                (*i)=buf.suivant;
                liredir(*fichier,*i,&buf);
                (*j)=0;
            }
            bloc=(*i);   // sauvegarde du bloc a partir duquel on a commencé l'extraction de l'enregistrement
            pos=(*j);    //sauvegarde de la position
            recuperer_chaine(*fichier,4,i,j,ch1,buf);    // recuperation des champs
            recuperer_chaine(*fichier,1,i,j,ch2,buf);    // recuperation des champs
            recuperer_chaine(*fichier,4,i,j,ch3,buf);
            (*j)-=9;
            recuperer_chaine(*fichier,atoi(ch1),i,j,chaine,buf); // longueur de l'info est le nombre equivalent a ch1
            //printf("\n  j  : %d \n",(*j));
            int resultat=strcmp(ch2,"N");
            int comp=atoi(ch3);
            //printf("\n le i  est : %d le j  est : %d\n",(*i),*j);
             if(comp==cle)             // si l'info est troiuvée
             {
                    (*trouv)=1;   // arret de la recherche
             }
            else
            {
                if(((*i)==entete(*fichier,3))&& ((*j)== strlen(buf.tab))) // si on est a la fin du fichier on arrete
                {
                     stop=1;
                }
            }
        }
        (*i)=bloc; // renvoi du bloc et de la position aux quels no n a trouvé l'info si elle existe
        (*j)=pos;
    }
    fermer(*fichier);
}

///--------------------------------------------------------------------------------------////
///--------------------------------------------------------------------------------------////
///--------------------------------------------------------------------------------------////
void modification(LOV **fichier, int cle)
{
    int i,j,trouv,C4=0;
    Buffer buf;
    strcpy(buf.tab,"");
    char *chaine=malloc(sizeof(char)*4);
    recherche_LOV(fichier,cle,&trouv,&i,&j); /// recherche de la cle f dans le fichihre
    *fichier=ouvrir("Ouvrages.bin",'A');
    if(trouv==1)
    {
        liredir(*fichier,i,&buf);
        C4++;/// lecture du  bloc afin d'entammer le parcours
        /// recuperation de la chaine correpondant a la taille de l'info
        recuperer_chaine(*fichier,4,&i,&j,chaine,buf);
        if (buf.tab[j]=='D')
        {
            buf.tab[j]='N';
        }
        else if(buf.tab[j]=='N')
        {
            buf.tab[j]='D';
        }
        ecriredir(*fichier,1,buf);
        C4++;
        printf("\nModification reissue\n");
    }
    else
    {
        printf("\nle cle n existe pas!\n");
    }
    fermer(*fichier);
    printf("\n||----------- Le cout de cette operation est: sans le cout du recherche%d\n",C4);
}
/**
autre fonction de recpiration du chaine ms cette fois est particulier
*/
void recuperer_chaine2(int n,int j, char chaine[],Buffer buf)  //
{

    int k=0;
    sprintf(chaine,"%s","");
    for(k=0; k<n; k++)
    {
        chaine[k]=buf.tab[(j)];
        (j)++;
    }
    chaine[k]='\0';
}
///--------------------------------------------------------------------------------------////
///--------------------------------------------------------------------------------------////
///--------------------------------------------------------------------------------------////
int rec_taille(Buffer *B,int offset)
{
    char taille[5]="";
    int j=0;
    for(int i=offset; i<offset+4; i++)
    {
        taille[j]=B->tab[i];
        j++;
    }
    return atoi(taille);
}
///--------------------------------------------------------------------------------------////
///--------------------------------------------------------------------------------------////
///--------------------------------------------------------------------------------------////
void Memoire(LOV *(*f))
{
    LOV *fd =ouvrir("Ouvrages.bin",'A');
    int j=29,lenn=0;
    int nb_blockC=1,C52=0;
    int T=max_tab;
    *f=ouvrir("Memoire.bin",'N');
    C52++;
    Buffer B,B2;
    char *ch1=malloc(sizeof(char)*140);
    strcpy(ch1,"");
    sprintf(B.tab,"%s","");
    sprintf(B2.tab,"%s","");
    /**
    parcoure du 1 fichier
    */
    for(int i=1; i<entete(fd,1); i++)
    {
        liredir(fd,i,&B);
        C52++;
        int t=0;
        while(t<strlen(B.tab))
        {
            if(B.tab[j]=='M')/// si le type est Memoire
            {
                recuperer_chaine2(rec_taille(&B,t),j-29,ch1,B);/// on recupere la chiane
                /**
                on modifier la taile par -1 car on onleve le type
                */
                char taille[5]="";
                for(int i=0; i<4; i++)
                {
                    taille[i]=ch1[i];
                }
                int taille_int=atoi(taille)-1;
                turn_to_string(taille,taille_int,4);
                for(int i=0; i<4; i++)
                {
                    ch1[i]=taille[i];
                }
                for(int i=29; i<strlen(ch1); i++)/// supp du type
                {
                    ch1[i]=ch1[i+1];
                }
                if (strlen(ch1)<=T)/// si il ya enaugh space to place it
                {
                    lenn+=strlen(ch1);
                    T-=strlen(ch1);
                    strcat(B2.tab,ch1);
                }
                else/// or on va la chauvocher
                {
                    int c=0;
                    for (int cpt=lenn; cpt<max_tab; cpt++)
                    {
                        B2.tab[cpt]=ch1[cpt-lenn];
                        c++;
                    }
                    B2.nb_char=lenn;
                    ecriredir(*f,nb_blockC,B2);
                    C52++;/// ecriture du block et alocation d un nouveau
                    alloc_bloc(*f);
                    C52++;
                    nb_blockC++;
                    T=max_tab;
                    lenn=strlen(ch1)-c;
                    strcpy(B2.tab,"");
                    int cc=c;
                    for (int cpt=0; cpt<c; cpt++)/// placement du reste de la chiane en chauvochement
                    {
                        B2.tab[cpt]=ch1[cc];
                        cc++;
                    }

                }

            }
            j=j+rec_taille(&B,t);///pour sauter vers l enreg suivant
            t=t+rec_taille(&B,t);
        }
    }
    B2.nb_char=lenn;
    ecriredir(*f,nb_blockC,B2);
    C52++;/// ecriture finale
    fermer(*f);
    fermer(fd);
    printf("\n||----------- Le cout de cette operation est: %d\n",C52);
}
///--------------------------------------------------------------------------------------////
///--------------------------------------------------------------------------------------////
///--------------------------------------------------------------------------------------////

/*************************              **TOF**            ******************************************/
///--------------------------------------------------------------------------------------////
///--------------------------------------------------------------------------------------////
///--------------------------------------------------------------------------------------////
void creation_TOF(char NomFichier[30], LOV *(*f),char NomFichier2[30],TOF *(*f1))
{
    int chek,C51=0;
    Buffer buf_LOV;
    Buffer_TOF *buf_TOF=malloc(sizeof(Buffer_TOF)),*buf_TOF2=malloc(sizeof(Buffer_TOF));
    ///Buffer_TOF *buf_TOF2=malloc(sizeof(Buffer_TOF));
    char *c=calloc(4,sizeof(char)),*taille1=calloc(4,sizeof(char));
    int tai=0,x;
    strcpy(c,"");
    strcpy(taille1,"");
    *f=ouvrir(NomFichier,'A');
    C51++;
    Article_TOF *art=malloc(sizeof(Article_TOF));
    chek=ouvrir_TOF(f1,NomFichier2,'N');
    C51++;
    printf("check est: %d",chek);
    int k = 0,o=1;
    int i=1,z=0;
    int j = 0;
    liredir(*f,i,&buf_LOV);
    C51++;
    printf("\n le tab est : %s \n",buf_LOV.tab);
    strcpy(taille1,"");
    strcpy(art->auteur,"");
    strcpy(art->num_livre,"");
    strcpy(art->titre,"");
    alloc_bloc_TOF(*f1);
    C51++;
    while((i!=-1) && j!=strlen(buf_LOV.tab))
    {
        tai=strlen(buf_LOV.tab);
        k=j;
        for(k=j; k<j+4; k++)
        {
            taille1[k-j]=buf_LOV.tab[k];
        }
        if ((buf_LOV.tab[j+29])=='P')
        {
            aff_entete_TOF(*f1,2,entete_TOF(*f1,2)+1);
            j=j+4;
            buf_TOF->T[z].dispo=buf_LOV.tab[j]; ///dispo
            j=j+1;
            k=j;
            strcpy(buf_TOF->T[z].num_livre,"");
            for(k=j; k<j+4; k++)          /// num de livre
            {
                buf_TOF->T[z].num_livre[k-j]=buf_LOV.tab[k];
            }
            j=j+4;
            k=j;
            for(k=j; k<j+10; k++)         /// num de titre
            {
                buf_TOF->T[z].titre[k-j]=buf_LOV.tab[k];
            }
            j=j+10;
            k=j;
            for(k=j; k<j+11; k++)         /// nom de l auteur
            {
                buf_TOF->T[z].auteur[k-j]=buf_LOV.tab[k];
            }
            j=j+11;
            for(k=j; k<j+4; k++)         /// nom de l anne de pub
            {
                c[k-j]=buf_LOV.tab[k];
            }
            buf_TOF->T[z].annee_de_pub=atoi(c);
            buf_TOF->nb_enreg+=1;
            z=z+1;
            if (z==max_tab_TOF)
            {
                ecrireDir_TOF(*f1,o,buf_TOF);
                C51++;
                aff_entete_TOF(*f1,1,entete_TOF(*f1,1)+1);
                o+=1;
                alloc_bloc_TOF(*f1);
                C51++;
                buf_TOF->nb_enreg=0;
                z=0;
            }
            j+=atoi(taille1)-30;
        }
        else
        {
            j+=atoi(taille1);
        }

        if (j==tai)
        {
            (i)=buf_LOV.suivant;
        }
    }
    ecrireDir_TOF(*f1,o,buf_TOF);
    C51++;
    fermer_TOF(*f1);
    fermer(*f);
    chek=ouvrir_TOF(f1,NomFichier2,'A');
    lireDir_TOF(*f1,1,buf_TOF2);
    for(x=0; x<3; x++)
    {
        printf("\n ********************************************");
        printf(" \n buf :%s",buf_TOF2->T[x].num_livre);
        printf("\n ********************************************");
    }
    fermer_TOF(*f1);
    printf("\n||----------- Le cout de cette operation est: %d\n",C51);
}
///--------------------------------------------------------------------------------------////
///--------------------------------------------------------------------------------------////
///--------------------------------------------------------------------------------------////
void recherche_dicho(TOF **f,char matricule[256],int* trv,int* i,int* j)
{

    int v = atoi(matricule),chek,C6=0;
    chek=ouvrir_TOF(f,"Periodiques.bin",'a');
    C6++;
    Tbloc_TOF buf;
    int bs=entete_TOF(*f,1),bi=1,inf,sup;
    int stop=0 ;
    *trv = 0;
    while (bi <= bs && (*trv==0 && stop == 0))
    {
        *i = (bi + bs)/2;
        lireDir_TOF(*f,*i,&buf);
        C6++;
        if (v >= atoi(buf.T[0].num_livre) && v <= atoi(buf.T[buf.nb_enreg-1].num_livre))
        {
            inf = 0;
            sup = buf.nb_enreg -1;
            while (inf <= sup && (*trv==0))
            {
                *j = (inf + sup)/2;
                if (v == atoi(buf.T[*j].num_livre))
                    *trv =1;
                else
                {
                    if ( v < atoi(buf.T[*j].num_livre))
                        sup = *j-1;
                    else
                        inf = *j+1;
                }
            }
            if ( inf > sup)
                *j = inf;
            stop = 1;
        }
        else
        {
            if (v < atoi(buf.T[0].num_livre))
                bs = *i-1;
            else
                bi = *i+1;
        }
    }
    if (bi > bs)
    {
        if (v> atoi(buf.T[buf.nb_enreg -1].num_livre) && buf.nb_enreg < 20)
            *j=buf.nb_enreg;
        else if (v < atoi(buf.T[0].num_livre))
            *j = 0;
        else
        {
            *i = bi;
            *j=0;
        }
    }
    fermer_TOF(*f);
    printf("\n||----------- Le cout de cette operation est: %d\n",C6);
}
///--------------------------------------------------------------------------------------////
///--------------------------------------------------------------------------------------////
///--------------------------------------------------------------------------------------////
/**************************************TOV(C/~C)******************************************************/
///--------------------------------------------------------------------------------------////
///--------------------------------------------------------------------------------------////
///--------------------------------------------------------------------------------------////
void creation_TOVC_Livre(char NomFichier[30], LOV *(*f),char NomFichier2[30],TOVC *(*f1))
{
    Buffer buf_LOV;
    strcpy(buf_LOV.tab,"");
    Buffer_TOVC *buf_TOVC=malloc(sizeof(Buffer_TOVC));
    strcpy(buf_TOVC->tableau,"");
    char *taille1=calloc(4,sizeof(char));
    int i=1,j=0,tai,i1=0,j1=0,z=0,k=0,len=0,cpt=0;///pour parcourire lrs 2 fichiers
    *f=ouvrir(NomFichier,'A');
    *f1=Ouvrir_TOVC(NomFichier2,'N');
    liredir(*f,i,&buf_LOV);

    while ((i!=-1) && j!=strlen(buf_LOV.tab))
    {
        char *Book=calloc(145,sizeof(char));
        cpt=0;
        strcpy(Book,"");
        tai=strlen(buf_LOV.tab);
        for(k=j; k<j+4; k++) /// la taille
        {
            taille1[k-j]=buf_LOV.tab[k];
        }
        len=atoi(taille1);
        if(buf_LOV.tab[j+29]=='L')/// l enreg  voulu
        {
            int taille_int=atoi(taille1)-1;/// decrimenter la taille
            turn_to_string(taille1,taille_int,4);
            for(k=j; k<j+4; k++)
            {
                Book[k-j]=taille1[k-j];/// affect du nv taille
            }
            for(k=j+4; k<j+len; k++)
            {
                cpt+=1;
                Book[k-j]=buf_LOV.tab[k];/// le reste de l enreg
            }
            k=j;
            for(k=j+29; k<j+len; k++)
            {
                cpt+=1;
                Book[k]=Book[k+1];/// suat du case 'type'
            }
            z=0;
            j=j+len;
            strcpy(buf_TOVC->tableau,"");
            while(z<len)/// affec dans le block
            {
                if(j1<max_caractere)
                {
                    buf_TOVC->tableau[j1]=Book[z];

                }
                else
                {
                    Ecriredir_TOVC(*f1,i1,*buf_TOVC);
                    i1+=1;
                    Alloc_bloc_TOVC(*f1);

                    j1=0;
                }
                z=z+1;
                j1=j1+1;
            }
        }
        else
            j+=len;
        if (j==tai)
        {
            (i)=buf_LOV.suivant;
            liredir(*f,i,&buf_LOV);
            j=0;
        }
    }
    Ecriredir_TOVC(*f1,i1,*buf_TOVC);
    fermer(*f);
    Fermer_TOVC(*f1);
}


///--------------------------------------------------------------------------------------////
///--------------------------------------------------------------------------------------////
///--------------------------------------------------------------------------------------////

/**
c est le meme sauf qu'on doit sauter la cote aussi
*/
void creation_TOVC_Article(char NomFichier[30], LOV *(*f),char NomFichier2[30],TOVC *(*f1))
{
    Buffer buf_LOV;
    strcpy(buf_LOV.tab,"");
    Buffer_TOVC *buf_TOVC=malloc(sizeof(Buffer_TOVC));
    strcpy(buf_TOVC->tableau,"");
    char *taille1=calloc(4,sizeof(char));
    int i=1,j=0,tai,i1=0,j1=0,z=0,k=0,len=0,cpt=0;
    *f=ouvrir(NomFichier,'A');
    *f1=Ouvrir_TOVC(NomFichier2,'N');
    liredir(*f,i,&buf_LOV);

    while ((i!=-1) && j!=strlen(buf_LOV.tab))
    {
        char *Book=calloc(145,sizeof(char));
        cpt=0;
        strcpy(Book,"");
        tai=strlen(buf_LOV.tab);
        for(k=j; k<j+4; k++)
        {
            taille1[k-j]=buf_LOV.tab[k];
        }
        len=atoi(taille1);
        if(buf_LOV.tab[j+29]=='A')
        {
            int taille_int=atoi(taille1)-7;
            turn_to_string(taille1,taille_int,4);
            for(k=j; k<j+4; k++)
            {
                Book[k-j]=taille1[k-j];
            }
            for(k=j+4; k<j+len; k++)
            {
                cpt+=1;
                Book[k-j]=buf_LOV.tab[k];
            }
            k=j;
            for(k=j+29; k<j+len; k++)
            {
                cpt+=1;
                Book[k]=Book[k+1];
            }
            for(k=j+33; k<j+len; k++) ///saut de la cote
            {
                cpt+=1;
                Book[k]=Book[k+6];
            }
            z=0;
            j=j+len;
            strcpy(buf_TOVC->tableau,"");
            while(z<len)
            {
                if(j1<max_caractere)
                {
                    buf_TOVC->tableau[j1]=Book[z];

                }
                else
                {
                    Ecriredir_TOVC(*f1,i1,*buf_TOVC);
                    i1+=1;
                    Alloc_bloc_TOVC(*f1);

                    j1=0;
                }
                z=z+1;
                j1=j1+1;
            }
        }
        else
            j+=len;
        if (j==tai)
        {
            (i)=buf_LOV.suivant;
            liredir(*f,i,&buf_LOV);
            j=0;
        }
    }
    Ecriredir_TOVC(*f1,i1,*buf_TOVC);
    fermer(*f);
    Fermer_TOVC(*f1);
}
///--------------------------------------------------------------------------------------////
///--------------------------------------------------------------------------------------////
///--------------------------------------------------------------------------------------////
/**************************************Index************************************************/
///--------------------------------------------------------------------------------------////
///--------------------------------------------------------------------------------------////
///--------------------------------------------------------------------------------------////

//------------------------------Fonction qui fait la creation du tab d index------------------------------------------------------
void creation_ind(FILE **f2)
{
    ind tab[20];
    *f2 = fopen("Index_Periodiques.bin","wb+");
    Buffer_TOF buf;
    TOF *fichier_TOF;
    int chek=ouvrir_TOF(&fichier_TOF,"Periodiques.bin",'a');
    int i,j,cout = 0;
    int k = 0;
    for (i = 1 ; i<=entete_TOF(fichier_TOF,1) ; i++)   //on parcour  les bloks  jusqu'a nb de blok final
    {
        lireDir_TOF(fichier_TOF,i,&buf);
        cout ++;
        for ( j=0 ; j< buf.nb_enreg ; j++)         // on parcour les enreg dans chaque bloks
        {
            tab[k].cle=atoi(buf.T[j].num_livre);
            tab[k].bloc = i;
            tab[k].indice =j;
            k++;
        }
    }
    fwrite(&tab,sizeof(tab),1,*f2);                // on ecrit dans le tab
    fermer_TOF(fichier_TOF);
    fclose(*f2);
}
//***********************************Fonction qui fait l affichage du tableau d index
void affich_ind(FILE *f2)
{
    TOF *fichier_TOF;
    int chek=ouvrir_TOF(&fichier_TOF,"Periodiques.bin",'a');
    ind tab[20];
    f2 = fopen("Index_Periodiques.bin","rb+");
    fread(&tab,sizeof(tab),1,f2);         // on lit le tableau
    printf("\n k azd : %d  ",entete_TOF(fichier_TOF,2));
    for ( int k = 0 ; k<entete_TOF(fichier_TOF,2) ; k++)      // a chaque fois on affiche la cle bloc et indice
    {
        printf("\nident = %d |",tab[k].cle);
        printf("bloc    = %d |",tab[k].bloc);
        printf("indice  = %d |\n",tab[k].indice);
    }
    fermer_TOF(fichier_TOF);
    fclose(f2);
}
// *************************** Procedure qui fait la recherche sur un tableau d index
void Recherche_index(FILE *f2, int cle, int *trouv, ind *d)
{
    TOF *fichier_TOF;
    int chek=ouvrir_TOF(&fichier_TOF,"Periodiques.bin",'a');
    ind tab[20];
    int pos,bs,bi;
    *trouv = 0 ;
    f2 = fopen("Index_Periodiques.bin","rb+");
    fread(&tab,sizeof(tab),1,f2);
    bs = entete_TOF(fichier_TOF,2);
    bi = 0;

    while ( (bi<=bs) && (*trouv=0)) // on fait la recherche dichotomique
    {
        pos=(bs+bi)/2;
        if ( cle == tab[pos].cle)
        {
            (*trouv)= 1;
        }
        else
        {
            if (cle < tab[pos].cle)
                bs = pos-1;
            else
            {
                bi = pos+1 ;
            }
        }
    }
    (*d).cle=tab[pos].cle;            // on affecte a d la cle et cloc
    (*d).bloc=tab[pos].bloc;
    (*d).indice=tab[pos].indice;
    fermer_TOF(fichier_TOF);
    fclose(f2);
}
