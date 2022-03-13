/**
* @file yams.c
*
* @author MICHELO Axel (axel.mch@outlook.fr)
*
* @brief  Programme du jeu yams
*
* @version 1.0
*
* @date 2021-11-28
*
* Ce programme vous permet de jouer au jeu du yams ici codé en c :
* Le Yams se joue avec 5 dés et se finit une fois toutes les cases de la feuille de marque
* remplies (il y a 13 combinaisons à réaliser). Les joueurs jouent à tour de rôle et chaque
* joueur dispose de 3 lancers à chaque coup. Le joueur a le choix de reprendre tous ou
* une partie des dés à chaque lancer, selon son gré, pour tenter d’obtenir la combinaison
* voulue. À chaque tour, le joueur doit obligatoirement inscrire son score dans une des
* cases de la feuille de marque que ce soit par les points qu’il a obtenus ou par un X. Il
* peut en effet arriver lors d’un tour que lfe résultat ne convienne pas au joueur et qu’il se
* dise qu’il pourrait faire un plus grand score sur un autre tour. Il peut alors choisir de
* barrer une autre case à la place. Bien entendu, il ne pourra plus faire cette combinaison
* par la suite.
* Le gagnant d’une partie de Yams est le joueur qui comptabilise le plus de points à la fin
* des 13 coups.
*/

/**************************************
 * APPEL DES BIBLIOTHÈQUES A UTILISER *
**************************************/

#include <stdlib.h> 
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>  

/*******************************************
 * DÉCLARATION DES TYPES ET DES CONSTANTES *
*******************************************/

#define N 14 // pour faciliter l'accès la manipulation et le parcours des tableau de type values_thimble
#define T 5 // pour faciliter l'accès la manipulation et le parcours des tableau de type total
#define TO 6 // pour faciliter l'accès la manipulation et le parcours des tableau de type thimble

typedef int values_table[N]; //déclaration de nouveaux type tableaux
typedef int total[TO]; //déclaration de nouveaux type tableaux
typedef int thimble[T]; //déclaration de nouveaux type tableaux
typedef char caracteres[N]; //déclaration de nouveaux type tableaux

/***************************
 * FONCTION INITIALISATION *
***************************/

/**
 * @fn initialiser_table_values (values_table table_sup, values_table table_inf)
 * 
 * @brief Cette procédure initialise la valeur -1 pour chaque élément des tableaux inf et sup pour chaque joueur.
 * 
 * @param table_sup tableau des scores inf 
 * @param table_inf tableau des scores sup
 */
void initialiser_table_values (values_table table_sup, values_table table_inf){ 
    int i;
    for (i=0; i<N; i++){
        table_sup[i] = -1; 
        table_inf[i] = -1;
    }
}

/*************************
 * FONCTIONS SUR LES DÉS *
*************************/

/**
 * @fn random_one_thimble()
 * 
 * @brief cette procédure permet de créer un dé pour pouvoir le réutiliser plus tard (pour relancer les dés)
 * 
 * @return un dé d'une valeur allant de 1 à 6
 */
int random_one_thimble(){
  int thimble;
  srand(time(NULL)); //initialisation du générateur à partir de l'heure machine
  thimble = rand() % 6; //récupération d'un nombre aléatoire entre 0 et 6 exclus
  thimble++; 
  return thimble;
}

/**
 * @fn void random_thimble(thimble table_thimble)
 * 
 * @brief cette procédure passe les valeur de 5 dé allant de 1 à 6, qu'elle genère dans un tableau passé en paramètres.
 * 
 * @param table_thimble tableau des dés
 */
void random_thimble(thimble table_thimble){
  int i, nbAleatoire;
  srand(time(NULL)); //initialisation du générateur à partir de l'heure machine
  for (i=0; i<T; i++){
    nbAleatoire = rand() % 6; //récupération d'un nombre aléatoire entre 0 et 6 exclus
    nbAleatoire++;
    table_thimble[i] = nbAleatoire;
  }
  printf("voici la valeur des dés %d, %d, %d, %d, %d\n", table_thimble[0], table_thimble[1], table_thimble[2], table_thimble[3], table_thimble[4]);
}

/**
 * @fn lancer(thimble table_thimble, int joueur, char J1[8], char J2[8])
 * 
 * @brief Cette procédure demande à l'utilisateur si il souhaite lancer les dés et tant qu'il ne veut pas on lui redemande. 
 * 
 * @param table_thimble tableau des dés
 * @param joueur sert a savoir si c'est le tour de joueur 1 ou joueur 2.
 * @param J1 nom du joueur 1
 * @param J2 nom du joueur 2
 */
void lancer(thimble table_thimble, int joueur, char J1[8], char J2[8]){
    char reponse[4];
    int value;
    if (joueur == 2){ // pour définir quel joueur joue et donc afficher son nom.
      printf("Voulez-vous lancez les dés %s ( oui / non ) ?", J1);
    }
    else{
      printf("Voulez-vous lancez les dés %s ( oui / non ) ?", J2);
    }
    scanf("%s", reponse);
    value = strcmp (reponse, "oui");
    while (value != 0){// pour définir quel joueur joue et donc afficher son nom.
            if (joueur == 2){
              printf("Voulez-vous lancez les dés %s ( oui / non ) ?", J1);
            }
            else{
              printf("Voulez-vous lancez les dés %s ( oui / non ) ?", J2);
            }
            scanf("%s", reponse);
            value = strcmp (reponse, "oui");
        }
    if (value == 0){
      random_thimble(table_thimble);
    }
}

/**
 * @fn add_total (total table_total, values_table table_sup, values_table table_inf)
 * 
 * @brief Cette procédure permet de faire le calcul des points de chaque joueur pour leurs tableaux inf et sup et ensuite, avec le résultat calcule 
 *        le total inf et sup, calcul le total de point de chaque joueur.
 * 
 * @param table_total tableau des totaux (de tableau sup et tableau inf)
 * @param table_sup tableau des scores sup
 * @param table_inf tabelau des scores inf
 */
void add_total (total table_total, values_table table_sup, values_table table_inf){
    int i;
    table_total[0] = 0; // initialise les valeurs du tableau à 0 
    table_total[1] = 0;
    table_total[2] = 0;
    table_total[3] = 0;
    for (i=0; i<7; i++){
      if (table_sup[i] != -1){ // on ajoute seulement les valeurs que le joueur a rempli à l'instant c'est à dire toutes sauf -1.
        table_total[0] = table_total[0] + table_sup[i];
      }
      if (table_sup[i+7] != -1){
        table_total[1] = table_total[1] + table_sup[i+7];
      }
      if (table_inf[i] != -1){
        table_total[2] = table_total[2] + table_inf[i];
      }
      if (table_inf[i+7] != -1){
        table_total[3] = table_total[3] + table_inf[i+7];
      }
    }
    table_total[4] = table_total[0] + table_total[2];
    table_total[5] = table_total[1] + table_total[3];
}

/**
 * @fn exchange(thimble table_thimble, int i, int j)
 * 
 * @brief Cette procédure permet d'échanger deux valeur entre elles en en stockant une pour ne pas la perdre.
 * 
 * @param table_thimble tableau des dés
 * @param i indice du tableau qui vient de la 1ème boucle de la fonction sort_thimble 
 * @param j indice du tableau qui vient de la 2ème boucle de la fonction sort_thimble 
 */
void exchange(thimble table_thimble, int i, int j){
    int tmp; // valeur temporaire
    tmp = table_thimble[i];
    table_thimble[i] = table_thimble[j];
    table_thimble[j] = tmp;
}

/**
 * @fn sort_thimble(thimble table_thimble)
 * 
 * @brief cette procédure permet de faire le tri d'un tableau donnée en paramètres grâce a la procédure échange.
 * 
 * @param table_thimble tableau des dés
 */

void sort_thimble(thimble table_thimble){
    int i, j, min, imin;
    for (i=0; i<6-1; i++){
        min=table_thimble[i]; // définissions du minimum de base 
        imin = i; // indice du minimum
        for (j=i+1; j<T; j++){
            if (table_thimble[j] < min){
                min = table_thimble[j];
                imin = j;
            }
        }
        exchange(table_thimble, i, imin); // appel de la fonction échange qui échange l'élèment avec celui qui le précède dans le tableau
    }
    printf("voici la valeur des dés %d, %d, %d, %d, %d\n", table_thimble[0], table_thimble[1], table_thimble[2], table_thimble[3], table_thimble[4]);
}

/**
 * @fn relancer(thimble table_thimble)
 * 
 * @brief Cete procédure permet aux joueurs de pouvoir relancer les dés si ils le souhaitent ou non. Si le joueur veut relancer les dés alors il a trois essaies
 *        pour essayer de récuperer les dés qu'il souhaite sinon conserve ceux qu'il a. 
 * 
 * @param table_thimble tableau des dés
 */
void relancer(thimble table_thimble){
    int i, value, max;
    char reponse_1[4];
    char reponse_2[4];
    bool arret;
    arret = false;
    max = 0;
    while(max < 3 && !arret){ // conditions d'arrêt (soit on a fait 3 fois la demande soit il à arrêter de vouloir relancer les dés)
      printf("voulez vous gardez ces dés ( oui / non )?\n");
      scanf("%s", reponse_1);
      value = strcmp (reponse_1, "oui");
      while ( strcmp (reponse_1, "oui") != 0 && strcmp (reponse_1, "non") != 0){ // vérifie bien que la réponse est soit "oui", soit "non"
        printf("voulez vous gardez ces dés ( oui / non )?\n");
        scanf("%s", reponse_1);
        value = strcmp (reponse_1, "oui"); 
      }
      if (value != 0){
        for (i=0; i<T; i++){
          printf("voulez vous relancez le dé %d : ( oui / non)", i+1);
          scanf("%s", reponse_2);
          while ( strcmp (reponse_2, "oui") != 0 && strcmp (reponse_2, "non") != 0){
              printf("voulez vous relancez le dé %d : ( oui / non)", i+1);
              scanf("%s", reponse_2);
          }
          if ( strcmp (reponse_2, "oui") == 0){
              table_thimble[i] = random_one_thimble(); // fait appel a la procédure et remplace le dé qu'il a choisi par un autre
          }
        }
      }
      else{
        arret = true; // définition d'arrêt de la fin de la boucle 
      }
      printf("les dés %d, %d, %d, %d, %d\n", table_thimble[0], table_thimble[1], table_thimble[2], table_thimble[3], table_thimble[4]);
      max++;
    }
}

/****************************************
 * FONCTIONS DE COMPTAGE DU TABLEAU SUP *
****************************************/

/**
 * @fn count_1(thimble table_thimble){
 *
 * @brief compte le nombre de dé égaux à 1 dans le tableaux
 * 
 * @param table_thimble tableau des dés
 * @return nombre de 1  
 */
int count_1(thimble table_thimble){
    int i, value, res_1;
    res_1 = 0;
    value = 1;
    for (i=0; i<T; i++){
        if(table_thimble[i] == value){
            res_1++;
        }
    }
    return res_1;
}

/**
 * @fn count_2(thimble table_thimble)
 * 
 * @brief compte le nombre de dé égaux à 2 dans le tableaux
 * 
 * @param table_thimble tableau des dés
 * @return nombre de 2  
 */
int count_2(thimble table_thimble){
    int i, value, res_2;
    res_2 = 0;
    value = 2;
    for (i=0; i<T; i++){
        if(table_thimble[i] == value){
            res_2++;
        }
    }
    return res_2;
}

/**
 * @fn count_3(thimble table_thimble)
 * 
 * @brief compte le nombre de dé égaux à 3 dans le tableaux
 * 
 * @param table_thimble tableau des dés
 * @return nombre de 3  
 */
int count_3(thimble table_thimble){
    int i, value, res_3;
    res_3 = 0;
    value = 3;
    for (i=0; i<T; i++){
        if(table_thimble[i] == value){
            res_3++;
        }
    }
    return res_3;
}

/**
 * @fn count_4(thimble table_thimble)
 * 
 * @brief compte le nombre de dé égaux à 4 dans le tableaux
 * 
 * @param table_thimble tableau des dés
 * @return nombre de 4  
 */
int count_4(thimble table_thimble){
    int i, value, res_4;
    res_4 = 0;
    value = 4;
    for (i=0; i<T; i++){
        if(table_thimble[i] == value){
            res_4++;
        }
    }
    return res_4;
}

/**
 * @fn count_5(thimble table_thimble)
 * 
 * @brief compte le nombre de dé égaux à 5 dans le tableaux
 * 
 * @param table_thimble tableau des dés
 * @return nombre de 5  
 */
int count_5(thimble table_thimble){
    int i, value, res_5;
    res_5 = 0;
    value = 5;
    for (i=0; i<T; i++){
        if(table_thimble[i] == value){
            res_5++;
        }
    }
    return res_5;
}

/**
 * @fn count_6(thimble table_thimble)
 * 
 * @brief compte le nombre de dé égaux à 6 dans le tableaux
 * 
 * @param table_thimble tableau des dés
 * @return nombre de 6 
 */
int count_6(thimble table_thimble){
    int i, value, res_6;
    res_6 = 0;
    value = 6;
    for (i=0; i<T; i++){
        if(table_thimble[i] == value){
            res_6++;
        }
    }
    return res_6;
}

/**
 * @fn bonus(values_table table_sup, int joueur)
 * 
 * @brief cette procédure calcule le bonus c'est à dire si la somme des points de la somme des 1,2,3,4,5,6 du joueurs est supérieur 
 *        à 65 alors il ajoute 35 à la case respective .
 * 
 * @param table_sup tableau des scores sup
 * @param joueur sert a savoir si c'est le tour de joueur 1 ou joueur 2.
 * @return le bonus (35 ou 0).
 */
void bonus(values_table table_sup, int joueur){
    int i, bonus;
    bonus = 0;
    if (joueur == 2){ //vérifie qel joueur est en train de jouer
      for (i=0; i<7; i++){
        if (table_sup[i] != -1){
            bonus = bonus + table_sup[i];
            }
        }
        if (bonus > 10){
            table_sup[6] = 35; // ajoute 35 dans la case BONUS de J1
        }
        else{
            table_sup[6] = 0;
        }
    }
    if (joueur == 1){
      for (i=7; i<N-1; i++){
        if (table_sup[i] != -1){
            bonus = bonus + table_sup[i];
            }
        }
        if (bonus > 10){
            table_sup[13] = 35; // ajoute 35 dans la case BONUS de J1
        }
        else{
            table_sup[13] = 0;
        }
    }
}

/**
 * @fn somme(thimble table_thimble)
 * 
 * @brief  fait la somme de tous les dé du tableau.
 * 
 * @param table_thimble tableau des dés
 * @return la somme des dés du tableau.
 */
int somme(thimble table_thimble){
    int i, res;
    res = 0;
    for (i=0; i<T;i++){
        res = res + table_thimble[i];
    }
    return res;
}

/****************************************
 * FONCTIONS DE COMPTAGE DU TABLEAU INF *
****************************************/

/**
 * @fn brelan(thimble table_thimble, int point_1, int point_2, int point_3, int point_4, int point_5, int point_6)
 * 
 * @brief calcule le brelan grâce au calcul des points des fonctions count. retourne la valeur de la somme des dés 
 *        (avec la fonction somme) si jamais 3 dé sont de la même valeur. 
 * 
 * @param table_thimble tableau des dés
 * @param point_1 le nombre de fois où le 1 est présent dans le tableau des dés
 * @param point_2 le nombre de fois où le 2 est présent dans le tableau des dés
 * @param point_3 le nombre de fois où le 3 est présent dans le tableau des dés
 * @param point_4 le nombre de fois où le 4 est présent dans le tableau des dés
 * @param point_5 le nombre de fois où le 5 est présent dans le tableau des dés
 * @param point_6 le nombre de fois où le 6 est présent dans le tableau des dés
 * @return (0, si il n'y a pas de brelan / la somme de tous les dés tirés, si il y a un brelan). 
 */
int brelan(thimble table_thimble, int point_1, int point_2, int point_3, int point_4, int point_5, int point_6){
  int res;
  res = 0;
  if (point_1 >= 3){
    res = somme(table_thimble); // fait appel a la fonction somme pour additionner la valeur de tous les dés.
  }
  if (point_2 >= 3){
    res = somme(table_thimble);
  }
  if (point_3 >= 3){
    res = somme(table_thimble);
  }
  if (point_4 >= 3){
    res = somme(table_thimble);
  }
  if (point_5 >= 3){
    res = somme(table_thimble);
  }
  if (point_6 >= 3){
    res = somme(table_thimble);
  }
  return res;
}

/**
 * @fn square(thimble table_thimble, int point_1, int point_2, int point_3, int point_4, int point_5, int point_6)
 * 
 * @brief calcule le carré grâce au calcul des points des fonctions count. retourne la valeur de la somme des dés 
 *        (avec la fonction somme) si jamais 4 dé sont de la même valeur. 
 * 
 * @param table_thimble tableau des dés
 * @param point_1 le nombre de fois où le 1 est présent dans le tableau des dés
 * @param point_2 le nombre de fois où le 2 est présent dans le tableau des dés
 * @param point_3 le nombre de fois où le 3 est présent dans le tableau des dés
 * @param point_4 le nombre de fois où le 4 est présent dans le tableau des dés
 * @param point_5 le nombre de fois où le 5 est présent dans le tableau des dés
 * @param point_6 le nombre de fois où le 6 est présent dans le tableau des dés
 * @return (0, si il n'y a pas de carré / la somme de tous les dés tirés, si il y a un carré).  
 */
int square(thimble table_thimble, int point_1, int point_2, int point_3, int point_4, int point_5, int point_6){
  int res;
  res = 0;
  if (point_1 >= 4){
    res = somme(table_thimble); // fait appel a la fonction somme pour additionner la valeur de tous les dés.
  }
  if (point_2 >= 4){
    res = somme(table_thimble);
  }
  if (point_3 >= 4){
    res = somme(table_thimble);
  }
  if (point_4 >= 4){
    res = somme(table_thimble);
  }
  if (point_5 >= 4){
    res = somme(table_thimble);
  }
  if (point_6 >= 4){
    res = somme(table_thimble);
  }
  return res;
}

/**
 * @fn full(thimble table_thimble, int point_1, int point_2, int point_3, int point_4, int point_5, int point_6)
 * 
 * @brief calcule le carré grâce au calcul des points des fonctions count. retourne la valeur de la somme des dés 
 *        (avec la fonction somme) si jamais 3 dé sont de la même valeur et les 2 autres sont aussi entre eux de la même valeur.
 * 
 * @param table_thimble tableau des dés
 * @param point_1 le nombre de fois où le 1 est présent dans le tableau des dés
 * @param point_2 le nombre de fois où le 2 est présent dans le tableau des dés
 * @param point_3 le nombre de fois où le 3 est présent dans le tableau des dés
 * @param point_4 le nombre de fois où le 4 est présent dans le tableau des dés
 * @param point_5 le nombre de fois où le 5 est présent dans le tableau des dés
 * @param point_6 le nombre de fois où le 6 est présent dans le tableau des dés
 * @return (0 si il n'y en a pas / 25 si il y en a un).
 */
int full(thimble table_thimble, int point_1, int point_2, int point_3, int point_4, int point_5, int point_6){
  int res;
  res = 0;
  if (((point_1 == 3 ) && ( point_2 == 2  ||  point_3 == 2  ||  point_4 == 2  ||  point_5 == 2  ||  point_6 == 2))){
    res = 25;
  }
  if (((point_2 == 3 ) &&  ( point_1 == 2  ||  point_3 == 2  ||  point_4 == 2  ||  point_5 == 2  ||  point_6 == 2))){
    res = 25;
  }
  if (((point_3 == 3 ) &&  ( point_1 == 2  ||  point_2 == 2  ||  point_4 == 2  ||  point_5 == 2  ||  point_6 == 2))){
    res = 25;
  }
  if (((point_4 == 3 ) &&  ( point_1 == 2  ||  point_2 == 2  ||  point_3 == 2  ||  point_5 == 2  ||  point_6 == 2))){
    res = 25;
  }
  if (((point_5 == 3 ) &&  ( point_1 == 2  ||  point_2 == 2  ||  point_3 == 2  ||  point_4 == 2  ||  point_6 == 2))){
    res = 25;
  }
  if (((point_6 == 3 ) &&  ( point_1 == 2  ||  point_2 == 2  ||  point_3 == 2  ||  point_4 == 2  ||  point_5 == 2))){
    res = 25;
  }
  return res;
}

/**
 * @fn petite_suite(thimble table_thimble)
 * 
 * @brief Cette fonction cherche a partir d'une liste trié si jamais il y a une suit de valeur dans les dés, c'est à dire par exemple si
 *        on a 1-2-3-4-6 alors la fonction va retourner 25.
 * 
 * @param table_thimble tableau des dés
 * @return (0 si il n'y a pas  de petite suite / 25 si il y en a une).
 */
int petite_suite(thimble table_thimble){
    int i, res, j;
    res = 0;
    j = 1;
    for (i=0; i<T; i++){
        if (table_thimble[i+1] == table_thimble[i]+1){// si le dé d'indice i est égal au dé d'indice i(+ 1)
            j = j + 1;
        }
    if (j == 4){ // si il a 4 dé de valeur consécutive
      res = 25;
    }
    }
    return res;
}

/**
 * @fn grande_suite(thimble table_thimble) 
 * 
 * @brief Cette fonction cherche a partir d'une liste trié si jamais il y a une suite de valeur dans les dés, c'est à dire par exemple si
 *        on a 1-2-3-4-5 alors la fonction va retourner 50.
 * 
 * @param table_thimble tableau des dés
 * @return (0 si il n' a pas de grande suite / 40 si il y en a une).
 */
int grande_suite(thimble table_thimble){
    int i, res, j;
    res = 0;
    j = 1;
    for (i=0; i<T; i++){
        if (table_thimble[i+1] == table_thimble[i]+1){// si le dé d'indice i est égal au dé d'indice i(+ 1)
            j = j + 1;
        }
    if (j == 5){// si il a 5 dé de valeur consécutive
      res = 40;
    }
    }
    return res;
}

/**
 * @fn yams(thimble table_thimble)
 * 
 * @brief Cette fonction cherche dans un tableau si jamais il y a les 5 dé de même valeur alors la fonction va retourner 50.
 * 
 * @param table_thimble tableau des dés
 * @return (0 si les 5 dé ne sont pas égaux / 50 si les 5 désont égaux). 
 */
int yams(thimble table_thimble){
  int i, res, j;
  j = 0;
  res = 0;
  for (i=0; i<4; i++){
    if (table_thimble[i+1] == table_thimble[i]){ // si le dé est égal au prochain dé
      j = j + 1;
    }
  if(j == 4){
    res = 50;
  }
  }
  return res;
}

/**
 * @fn chance(int point_1, int point_2, int point_3, int point_4, int point_5, int point_6)
 * 
 * @brief Cette fonction retourne le somme des resultats des dés multiplié par leur valeur respective.
 * 
 * @param point_1 le nombre de fois où le 1 est présent dans le tableau des dés
 * @param point_2 le nombre de fois où le 2 est présent dans le tableau des dés
 * @param point_3 le nombre de fois où le 3 est présent dans le tableau des dés
 * @param point_4 le nombre de fois où le 4 est présent dans le tableau des dés
 * @param point_5 le nombre de fois où le 5 est présent dans le tableau des dés
 * @param point_6 le nombre de fois où le 6 est présent dans le tableau des dés
 * @return nombre de 6 à 36 
 */
int chance(int point_1, int point_2, int point_3, int point_4, int point_5, int point_6){
    int res; 
    res = 0;
    res = (point_1 * 1 + point_2 * 2 + point_3 * 3 + point_4 * 4 + point_5 * 5 + point_6 * 6);
    return res;
}

/*******************************************
* FONCTIONS POUR LE REMPLISSAGE DU TABLEAU *
*******************************************/

/**
 * @fn void affiche_point(thimble table_thimble)
 * 
 * @brief Cette procédure retourne les valeurs de toutes fonctions qui permettent de calculer les point si elles retourne autre chose que 0 sauf bonus.
 * 
 * @param table_thimble tableau des dés
 */
void affiche_point(thimble table_thimble){
    int res_1, res_2, res_3, res_4, res_5, res_6,
           res_brelan, res_square, res_full, res_petite_suite, 
           res_grande_suite, res_yams, res_chance;
    // appel de toutes les fonctions pour calculer les points sauf bonus que l'on n'affichera jamais 
    res_1 = count_1(table_thimble);
    res_2 = count_2(table_thimble);
    res_3 = count_3(table_thimble);
    res_4 = count_4(table_thimble);
    res_5 = count_5(table_thimble);
    res_6 = count_6(table_thimble);
    res_chance = chance(res_1, res_2, res_3, res_4, res_5, res_6);
    res_brelan = brelan(table_thimble, res_1, res_2, res_3, res_4, res_5, res_6);
    res_square = square(table_thimble, res_1, res_2, res_3, res_4, res_5, res_6);
    res_full = full(table_thimble, res_1, res_2, res_3, res_4, res_5, res_6);
    res_petite_suite = petite_suite(table_thimble);
    res_grande_suite = grande_suite(table_thimble);
    res_yams = yams(table_thimble); 
    if (res_1 != 0){ 
        printf("1 : %d\n", res_1);
    }
    if (res_2 != 0){
        printf("2 : %d\n", res_2 * 2);
    }
    if (res_3 != 0){
        printf("3 : %d\n", res_3 * 3);
    }
    if (res_4 != 0){
        printf("4 : %d\n", res_4 * 4);
    }
    if (res_5 != 0){
        printf("5 : %d\n", res_5 * 5);
    }
    if (res_6 != 0){
        printf("6 : %d\n", res_6 * 6);
    }
    if (res_brelan != 0){
        printf("B : %d\n", res_brelan);
    }
    if (res_square != 0){
      printf("C : %d\n", res_square);
    }
    if (res_full != 0){
      printf("F : %d\n", res_full);
    }
    if (res_petite_suite != 0){
      printf("P : %d\n", res_petite_suite);
    }
    if (res_grande_suite != 0){
      printf("G : %d\n", res_grande_suite);
    }
    if (res_yams != 0){
      printf("Y : %d\n", res_yams);
    }
    if (res_chance != 0){
      printf("c : %d\n", res_chance);
    }

}

/**
 * @fn doublon(char choix, values_table table_sup, values_table table_inf, int joueur)
 * 
 * @brief cette fonction permet de d'incrémenter 1 à une variable après qu'on est choix une case du tanleau pour 
 *        ensuite la réutiliser dans la fonction permettant de remplir le tableau (pour ne pas remplir 2  fois la même case)
 * 
 * @param choix correspond à la case que le joueur veut remplir, proviens de remplir_tableau == reponse
 * @param table_sup tableau des scores sup
 * @param table_inf tableau des scores inf
 * @param joueur sert a savoir a quel joueur est le tour
 * @return possibilité en fonction de la cas que ke joueur a voulu remplir 
 */
int doublon(char choix, values_table table_sup, values_table table_inf, int joueur){
  int possible, n;
  possible = 0;
  if(joueur == 2){ // on définit quel joueur joue pour accèder a ses tableaux
      n = 0;
  }
    else{
      n = 7;
  }

  if (choix == '1'){
        if (table_sup[n] != -1){
          possible = 1;
      }
    }
    if (choix == '2'){
        if (table_sup[n+1] != -1){
          possible = 1;
        }
    }
    if (choix == '3'){
        if (table_sup[n+2] != -1){
          possible = 1;
        }
    }
    if (choix == '4'){
        if (table_sup[n+3] != -1){
          possible = 1;
        }
    }
    if (choix == '5'){
        if (table_sup[n+4] != -1){
          possible = 1;
        }
    }
    if (choix == '6'){
        if (table_sup[n+5] != -1){
          possible = 1;
        }
    }
    if (choix == 'B'){
        if (table_inf[n] != -1){
          possible = 1;
        }
    }
    if (choix == 'C'){
        if (table_inf[n+1] != -1){
          possible = 1;
        }
    }
    if (choix == 'F'){
        if (table_inf[n+2] != -1){
          possible = 1;
        }
    }
    if (choix == 'P'){
        if (table_inf[n+3] != -1){
          possible = 1;
        }
    }
    if (choix == 'G'){
        if (table_inf[n+4] != -1){
          possible = 1;
        }
    }
    if (choix == 'Y'){
        if (table_inf[n+5] != -1){
          possible = 1;
        }
    }
    if (choix == 'c'){
        if (table_inf[n+6] != -1){
          possible = 1;
        }
    }
  return possible;
}


/**
 * @fn remplir_tableau(values_table table_sup, values_table table_inf, thimble table_thimble, int joueur, char J1[8], char J2[8])
 * 
 * @brief  Cette fonction permet de rentrer une valeur dans le tableau en appelant les fonctions permettant de calculer les points.
 * 
 * @param table_sup tableau des scores sup
 * @param table_inf tableau des scores inf
 * @param table_thimble tableau des dés
 * @param joueur sert a savoir a quel joueur est le tour
 * @param J1 nom du joueur 1
 * @param J2 nom du joueur 2
 */
void remplir_tableau(values_table table_sup, values_table table_inf, thimble table_thimble, int joueur, char J1[8], char J2[8]){
    int n, possible,
        point_1, point_2, point_3, point_4, point_5, point_6;
    char reponse;
    char enter;
    point_1 = count_1(table_thimble);
    point_2 = count_2(table_thimble);
    point_3 = count_3(table_thimble);
    point_4 = count_4(table_thimble);
    point_5 = count_5(table_thimble);
    point_6 = count_6(table_thimble);
    if (joueur == 2){
      printf("quel valeur du tableau valide voulez vous remplir : %s (saisissez la lettre maj présente dans le tableau (CHANCE = c)) ?\n", J1);
    }
    else{
      printf("quel valeur du tableau valide voulez vous remplir : %s (saisissez la lettre maj présente dans le tableau (CHANCE = c)) ?\n", J2);
    }
    scanf("%c", &enter);
    scanf("%c", &reponse);
    possible = doublon(reponse, table_sup, table_inf, joueur);
    /*
    la condition ici regarde tout d'abords si la lettre que le joueur entre est bien dans la liste proposé et regarde
    aussi la lettre n'a pas déjà été utilisé pour ce joueur (avec possible).
    */
    while (((reponse != '1' ) && (reponse != '2' ) && (reponse != '3' ) && (reponse != '4' ) && (reponse != '5' ) && (reponse != '6' ) && (reponse != 'B' ) 
          && (reponse != 'C' ) && (reponse != 'F' ) && (reponse != 'P' ) && (reponse != 'G' ) && (reponse != 'Y' ) && (reponse != 'c')) || (possible == 1)){
            if (joueur == 2){
              printf("quel valeur du tableau valide voulez vous remplir : %s (saisissez la lettre maj présente dans le tableau (CHANCE = c)) ?\n", J1);
            }
            else{
              printf("quel valeur du tableau valide voulez vous remplir : %s (saisissez la lettre maj présente dans le tableau (CHANCE = c)) ?\n", J2);
            }
              scanf("%c", &enter);
              scanf("%c", &reponse);
              possible = doublon(reponse, table_sup, table_inf, joueur);
    }
        
    if(joueur == 2){ 
      n = 0;
    }
    else{
      n = 7;
    }
    /*
    ces conditions affichent le resultat dans la case respective du choix en appelant leur fonction
    */
    if (reponse == '1'){
        table_sup[n] =  count_1(table_thimble);
    }
    if (reponse == '2'){
        table_sup[n+1] =  count_2(table_thimble) * 2;
    }
    if (reponse == '3'){
        table_sup[n+2] =  count_3(table_thimble) * 3;
    }
    if (reponse == '4'){
        table_sup[n+3] =  count_4(table_thimble) * 4;
    }
    if (reponse == '5'){
        table_sup[n+4] =  count_5(table_thimble) * 5;
    }
    if (reponse == '6'){
        table_sup[n+5] =  count_6(table_thimble) * 6;
    }
    if (reponse == 'B'){
        table_inf[n] =  brelan(table_thimble, point_1, point_2, point_3, point_4, point_5, point_6);
    }
    if (reponse == 'C'){
        table_inf[n+1] =  square(table_thimble, point_1, point_2, point_3, point_4, point_5, point_6);
    }
    if (reponse == 'F'){
        table_inf[n+2] =  full(table_thimble, point_1, point_2, point_3, point_4, point_5, point_6);
    }
    if (reponse == 'P'){
        table_inf[n+3] =  petite_suite(table_thimble);
    }
    if (reponse == 'G'){
        table_inf[n+4] =  grande_suite(table_thimble);
    }
    if (reponse == 'Y'){
        table_inf[n+5] =  yams(table_thimble);
    }
    if (reponse == 'c'){
        table_inf[n+6] =  chance(point_1, point_2, point_3, point_4, point_5, point_6);
    }
     
}

/*************************************************
 * FONCTIONS D'AFFICHAGE DES ELEMENTS PRINCIPAUX *
*************************************************/

/**
 * @fn print_thimble(thimble table_thimble)
 * 
 * @brief cette procédure affiche les dés.
 * 
 * @param table_thimble tableau des dés
 */
void print_thimble(thimble table_thimble){  
  printf("voici vos dés : %d, %d, %d, %d, %d\n", table_thimble[0],  table_thimble[1],  table_thimble[2],  table_thimble[3],  table_thimble[4]);
}

/**
 * @fn gagnant(char nomj1[20], char nomj2[20], total table_total)
 * 
 * @brief cette procédure affiche le gagnants ainsi que son score
 * 
 * @param nomj1 nom du joueur 1
 * @param nomj2 nom du joueur 1
 * @param table_total tableau des scores totaux 
 */
void gagnant(char nomj1[20], char nomj2[20], total table_total){
  if (table_total[4] == table_total[5]){
    printf("Bien joué %s et %s vous êtes ex æquo avec un score de %d à %d\n", nomj1, nomj2, table_total[4], table_total[5]);
  }
  else if (table_total[4] > table_total[5]){
    printf("Félicitaitons %s pour votre victoire de %d à %d\n", nomj1, table_total[4], table_total[5]);
  }
  else{
    printf("Félicitaitons %s pour votre victoire de %d à %d\n", nomj2, table_total[5], table_total[4]);
  }
}

/**
 * @fn print_table (char nomj1[20],char nomj2[20], values_table table_sup, values_table table_inf, total table_total,thimble table_thimble)
 * 
 * @brief Cette procédure affiche le tableau du jeu de yams avec dans ses cases les prénoms des joueurs, leur points inf/sup,
 *        leurs totaux et la valeur des dés.
 * 
 * @param nomj1 nom du joueur 1
 * @param nomj2 nom du joueur 2
 * @param table_sup tableau des scores sup
 * @param table_inf tableau des scores inf
 * @param table_total tableau des scores totaux
 * @param table_thimble tableau des dés
 */
void print_table (char nomj1[20],char nomj2[20],
                      values_table table_sup,
                      values_table table_inf,
                      total table_total,
                      thimble table_thimble)
{
  
    /* 
    * le %<nombre>(d/s) permettent de définir le nombre de caractère que va utiliser la variable pour améliorer la lisibilité du tableau
    */

    printf("┏━━━━━━━━┳━━━┳━━━┳━━━┳━━━┳━━━┳━━━┳━━━━━┓\n");
    printf("┃sup     ┃ 1 ┃ 2 ┃ 3 ┃ 4 ┃ 5 ┃ 6 ┃BONUS┃\n");
    printf("┃%-7s ┃%2d ┃%2d ┃%2d ┃%2d ┃%2d ┃%2d ┃%3d  ┃\n", nomj1, table_sup[0], table_sup[1], table_sup[2], table_sup[3], table_sup[4], table_sup[5], table_sup[6]);
    printf("┃%-7s ┃%2d ┃%2d ┃%2d ┃%2d ┃%2d ┃%2d ┃%3d  ┃\n", nomj2, table_sup[7], table_sup[8], table_sup[9], table_sup[10], table_sup[11], table_sup[12], table_sup[13]);
    printf("┗━━━━━━━━┻━━━┻━━━┻━━━┻━━━┻━━━┻━━━┻━━━━━┛\n");
    printf("\n");
    printf("┏━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━┓\n");
    printf("┃ TOTAL sup %-7s┃%10d         ┃\n", nomj1, table_total[0]);
    printf("┃ TOTAL sup %-7s┃%10d         ┃\n", nomj2, table_total[1]);
    printf("┗━━━━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━━━━┛\n");
    printf("\n");
    printf("┏━━━━━━━┳━━━┳━━━┳━━━┳━━━┳━━━┳━━━┳━━━━━━┓\n");
    printf("┃inf    ┃ B ┃ C ┃ F ┃ P ┃ G ┃ Y ┃CHANCE┃\n");
    printf("┃%-7s┃%2d ┃%2d ┃%2d ┃%2d ┃%2d ┃%2d ┃%3d   ┃\n", nomj1, table_inf[0], table_inf[1], table_inf[2], table_inf[3], table_inf[4], table_inf[5], table_inf[6]);
    printf("┃%-7s┃%2d ┃%2d ┃%2d ┃%2d ┃%2d ┃%2d ┃%3d   ┃\n", nomj2, table_inf[7], table_inf[8], table_inf[9], table_inf[10], table_inf[11], table_inf[12], table_inf[13]);
    printf("┗━━━━━━━┻━━━┻━━━┻━━━┻━━━┻━━━┻━━━┻━━━━━━┛\n");
    printf("\n");
    printf("┏━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━┓\n");
    printf("┃ TOTAL inf %-7s┃%10d         ┃\n", nomj1, table_total[2]);
    printf("┃ TOTAL inf %-7s┃%10d         ┃\n", nomj2, table_total[3]);
    printf("┗━━━━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━━━━┛\n");
    printf("\n");
    printf("  dé1   dé2   dé3   dé4   dé5 \n");
    printf(" ┏━━━┓ ┏━━━┓ ┏━━━┓ ┏━━━┓ ┏━━━┓\n");
    printf(" ┃%2d ┃ ┃%2d ┃ ┃%2d ┃ ┃%2d ┃ ┃%2d ┃\n", table_thimble[0], table_thimble[1], table_thimble[2], table_thimble[3], table_thimble[4]);
    printf(" ┗━━━┛ ┗━━━┛ ┗━━━┛ ┗━━━┛ ┗━━━┛\n");
    printf("\n");   
    printf("┏━━━━━━━┳━━━━━━━┳━━━━━━━┓\n");
    printf("┃       ┃%-7s┃%-7s┃\n", nomj1, nomj2);
    printf("┃ TOTAL ┃%4d   ┃%4d   ┃\n", table_total[4], table_total[5]);
    printf("┗━━━━━━━┻━━━━━━━┻━━━━━━━┛\n");
}

/***********************
 * PROGRAMME PRINCIPAL *
***********************/

int main(){
    int nbtours, tour_joueur,  joueur,
        taillej1, taillej2;
    char nomj1[20];
    char nomj2[20];
    char enter;
    /*
    définisions des tableaux à utiliser pour l'affichage
    */
    thimble table_thimble = {}; 
    values_table table_sup = {};
    values_table table_inf = {};
    total table_total = {};

    system("clear"); // pour effacer les anciens affichage, quesyion esthétisme

    printf("quel est votre nom joueur 1 (maximum 7 lettres) ?\n");
    scanf(" %s", nomj1);
    printf("quel est votre nom joueur 2 (maximum 7 lettres) ?\n");
    scanf(" %s", nomj2);
    taillej1 =  strlen(nomj1); // récupere la taille de la longueur des chaines de caractères
    taillej2 = strlen(nomj2); // récupere la taille de la longueur des chaines de caractères
    while (taillej1 > 7){
        printf("quel est votre nom joueur 1 (maximum 7 lettres) ?\n");
        scanf(" %s", nomj1);
        taillej1 =  strlen(nomj1);
    }
    while (taillej2 > 7){
        printf("quel est votre nom joueur 2 (maximum 7 lettres) ?\n");
        scanf(" %s", nomj2);
        taillej2 = strlen(nomj2);
    }

    initialiser_table_values(table_sup, table_inf);
  
    for(nbtours=0; nbtours<26;nbtours++){
      tour_joueur = (nbtours % 2);
      if(tour_joueur == 1){
        joueur = 1;
      }
      else{
        joueur = 2;
      }

      system("clear");

      lancer(table_thimble, joueur, nomj1, nomj2);

      relancer(table_thimble);

      sort_thimble(table_thimble);

      affiche_point(table_thimble);

      system("clear");

      affiche_point(table_thimble);

      printf("\n");

      print_table(nomj1, nomj2, table_sup, table_inf, table_total, table_thimble);

      printf("\n");

      remplir_tableau(table_sup, table_inf, table_thimble, joueur, nomj1, nomj2);

      print_table(nomj1, nomj2, table_sup, table_inf, table_total, table_thimble);


      system("clear");

      bonus(table_sup, joueur);

      add_total(table_total, table_sup, table_inf);

      print_table(nomj1, nomj2, table_sup, table_inf, table_total, table_thimble);

      printf("\n");
      printf("appuyez sur entrée pour continuer\n");
      scanf("%c", &enter);
      scanf("%c", &enter);
    }

    system("clear");

    gagnant(nomj1, nomj2, table_total);

    printf("\n");
    printf("appuyez sur entrée pour quitter\n");
    scanf("%c", &enter);
return EXIT_SUCCESS;
}