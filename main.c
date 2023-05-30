#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define TAILLE_TITRE 100
#define TAILLE_AUTEUR 100

/* Structure d'un livre */
typedef struct Livre {
    int id;
    char titre[TAILLE_TITRE];
    char auteur[TAILLE_AUTEUR];
    bool reserve;
} Livre;

/* Structure d'un nœud de la liste chaînée */
typedef struct Noeud {
    Livre livre;
    struct Noeud* suivant;
} Noeud;

/* Structure de la liste de livres */
typedef struct ListeLivres {
    Noeud* debut;
    Noeud* fin;
} ListeLivres;

/* Initialiser une liste de livres vide */
ListeLivres* initialiserListe() {
    ListeLivres* liste = (ListeLivres*)malloc(sizeof(ListeLivres));
    liste->debut = NULL;
    liste->fin = NULL;
    return liste;
}

/* Ajouter un livre à la liste */
void ajouterLivre(ListeLivres* liste, int id, int n , const char* titre, const char* auteur) {
    /*le parametre n pour afficher un message dans les cas d'ajouter un livre*/
    Livre* livre = (Livre*)malloc(sizeof(Livre));
    livre->id = id;
    strncpy(livre->titre, titre, TAILLE_TITRE - 1);
    livre->titre[TAILLE_TITRE - 1] = '\0'; /* Ajouter le caractère nul de fin de chaîne */
    strncpy(livre->auteur, auteur, TAILLE_TITRE - 1);
    livre->auteur[TAILLE_AUTEUR - 1] = '\0'; /* Ajouter le caractère nul de fin de chaîne */
    livre->reserve = false;

    Noeud* nouveauNoeud = (Noeud*)malloc(sizeof(Noeud));
    nouveauNoeud->livre = *livre;
    nouveauNoeud->suivant = NULL;

    if (liste->debut == NULL) {
        liste->debut = nouveauNoeud;
        liste->fin = nouveauNoeud;
    } else {
        liste->fin->suivant = nouveauNoeud;
        liste->fin = nouveauNoeud;
    }
    if(n==1)
        printf("Le livre avec le titre : '%s' a ete ajoute.\n", titre);
    else
        return;
}

/* Supprimer un livre de la liste */
void supprimerLivre(ListeLivres* liste, int id) {
    Noeud* courant = liste->debut;
    Noeud* precedent = NULL;

    while (courant != NULL) {
        if (courant->livre.id == id) {
            if (precedent == NULL) {
                liste->debut = courant->suivant;
                if (liste->debut == NULL) {
                    liste->fin = NULL;
                }
            } else {
                precedent->suivant = courant->suivant;
                if (courant == liste->fin) {
                    liste->fin = precedent;
                }
            }

            free(courant);
            printf("Le livre avec l'ID %d a ete supprime.\n", id);
            return;
        }

        precedent = courant;
        courant = courant->suivant;
    }

    printf("Aucun livre trouve avec l'ID %d.\n", id);
}

/* Rechercher un livre dans la liste */
Livre* rechercherLivre(ListeLivres* liste, int id) {
    Noeud* courant = liste->debut;

    while (courant != NULL) {
        if (courant->livre.id == id) {
            return &(courant->livre);
        }
        courant = courant->suivant;
    }

    return NULL;
}

/* Afficher tous les livres de la liste */
void afficherLivres(ListeLivres* liste) {
    Noeud* courant = liste->debut;

    if (courant == NULL) {
        printf("Aucun livre dans la liste.\n");
        return;
    }

    printf("Liste des livres :\n");

    while (courant != NULL) {
        printf("ID : %d\n", courant->livre.id);
        printf("Titre : %s\n", courant->livre.titre);
        printf("Auteur : %s\n", courant->livre.auteur);
        printf("Reserve : %s\n", courant->livre.reserve ? "Oui" : "Non");
        printf("--------------------\n");
        courant = courant->suivant;
    }
}

/* Réserver un livre */
void reserverLivre(ListeLivres* liste, int id) {
    Livre* livre = rechercherLivre(liste, id);

    if (livre != NULL) {
        if (!livre->reserve) {
            livre->reserve = true;
            printf("Le livre avec l'ID %d a ete reserve.\n", id);
        } else {
            printf("Le livre avec l'ID %d est deje reserve.\n", id);
        }
    } else {
        printf("Aucun livre trouve avec l'ID %d.\n", id);
    }
}

int main() {
    ListeLivres* liste = initialiserListe();
    int choixUtilisateur;
    printf("Bonjour!!\n");
    printf("********** Systeme de gestion de Bibliotheque **********\n");
    /* Ajouter des livres par défaut */
    ajouterLivre(liste, 1,0, "Data structures and algorithm in C++", "Mark Allen Weiss");
    ajouterLivre(liste, 2,0,"Algorithmes et structures de donnees", "Michel Divay");
    ajouterLivre(liste, 3,0, "C Programming For Dummies", "Dan Gookin");
    ajouterLivre(liste, 4,0,"The Compound Effect", "Darren_Hardy");
    debut:
    printf("\nEtes-vous un utilisateur regulier ou un Administrateur: \n");
    printf("1- Utilisateur regulier\n");
    printf("2- Administrateur\n");
    printf("votre choix : ");
    scanf("%d", &choixUtilisateur);
    if (choixUtilisateur == 1) {
        int choixNormal;
        do {
            printf("\nMenu utilisateur normal\n");
            printf("1. Afficher les livres\n");
            printf("2. Rechercher un livre\n");
            printf("3. Reserver un livre\n");
            printf("4.Retour a zero\n");
            printf("0. Quitter\n");
            printf("Choisissez une option : ");
            scanf("%d", &choixNormal);

            switch (choixNormal) {
                case 1:
                    afficherLivres(liste);
                    break;
                case 2:
                    {
                        int idRecherche;
                        printf("Entrez l'ID du livre à rechercher : ");
                        scanf("%d", &idRecherche);

                        Livre* livreRecherche = rechercherLivre(liste, idRecherche);
                        if (livreRecherche != NULL) {
                            printf("Livre trouve :\n");
                            printf("ID : %d\n", livreRecherche->id);
                            printf("Titre : %s\n", livreRecherche->titre);
                            printf("Auteur : %s\n", livreRecherche->auteur);
                            printf("Reserve : %s\n", livreRecherche->reserve ? "Oui" : "Non");
                        } else {
                            printf("Aucun livre trouve avec l'ID %d.\n", idRecherche);
                        }
                    }
                    break;
                case 3:
                    {
                        int idReservation;
                        printf("Entrez l'ID du livre a reserver : ");
                        scanf("%d", &idReservation);
                        reserverLivre(liste, idReservation);
                    }
                    break;
                case 4:
                    {
                        goto debut;
                    }
                    break;
                case 0:
                    printf("Au revoir !\n");
                    break;
                default:
                    printf("Option invalide. Veuillez reessayer.\n");
                    break;
            }
        } while (choixNormal != 0);
    } else if (choixUtilisateur == 2) {
        char motDePasse[100];
        printf("Entrez le mot de passe de l'administrateur : ");
        scanf("%s", motDePasse);

        /* Vérifier le mot de passe de l'administrateur
         Remplacez 'votre_mot_de_passe' par le mot de passe réel */
        if (strcmp(motDePasse, "password") == 0) {
            int choixAdmin;
            do {
                printf("\nMenu administrateur\n");
                printf("1. Afficher les livres\n");
                printf("2. Rechercher un livre\n");
                printf("3. Reserver un livre\n");
                printf("4. Ajouter un livre\n");
                printf("5. Supprimer un livre\n");
                printf("6.Retour a zero\n");
                printf("0. Quitter\n");
                printf("Choisissez une option : ");
                scanf("%d", &choixAdmin);

                switch (choixAdmin) {
                    case 1:
                        afficherLivres(liste);
                        break;
                    case 2:
                        {
                            int idRecherche;
                            printf("Entrez l'ID du livre a rechercher : ");
                            scanf("%d", &idRecherche);

                            Livre* livreRecherche = rechercherLivre(liste, idRecherche);
                            if (livreRecherche != NULL) {
                                printf("Livre trouve :\n");
                                printf("ID : %d\n", livreRecherche->id);
                                printf("Titre : %s\n", livreRecherche->titre);
                                printf("Auteur : %s\n", livreRecherche->auteur);
                                printf("Reserve : %s\n", livreRecherche->reserve ? "Oui" : "Non");
                            } else {
                                printf("Aucun livre trouve avec l'ID %d.\n", idRecherche);
                            }
                        }
                        break;
                    case 3:
                        {
                            int idReservation;
                            printf("Entrez l'ID du livre a reserver : ");
                            scanf("%d", &idReservation);
                            reserverLivre(liste, idReservation);
                        }
                        break;
                    case 4:

                        {
                            int id, choix;
                            char titre[TAILLE_TITRE];
                            char auteur[TAILLE_AUTEUR];
                            printf("Veuillez entrer l'ID du livre : ");
                            scanf("%d", &id);
                            printf("Veuillez entrer le titre du livre : ");
                            getchar();  /* Pour consommer le caractère de nouvelle ligne restant dans le flux d'entrée */
                            fgets(titre, TAILLE_TITRE, stdin);
                            titre[strcspn(titre, "\n")] = '\0';  /* Supprimer le caractère de nouvelle ligne */
                            printf("Veuillez entrer l'auteur du livre : ");
                            fgets(auteur, TAILLE_AUTEUR, stdin);
                            auteur[strcspn(auteur, "\n")] = '\0';  /* Supprimer le caractère de nouvelle ligne */
                            ajouterLivre(liste, id,1, titre, auteur);
                        }
                        break;

                    case 5:
                        {
                            int idSuppression;
                            printf("Entrez l'ID du livre a supprimer : ");
                            scanf("%d", &idSuppression);
                            supprimerLivre(liste, idSuppression);
                        }
                        break;
                    case 6:
                        {
                            goto debut;
                        }
                        break;
                    case 0:
                        printf("Au revoir !\n");
                        break;
                    default:
                        printf("Option invalide. Veuillez reessayer.\n");
                        break;
                }
            } while (choixAdmin != 0);
        } else {
            printf("Mot de passe incorrect. Acces refuse.\n");
        }
    } else {
        printf("Option invalide. Veuillez reessayer.\n");
    }

    return 0;
}
