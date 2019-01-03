/**
* @file 
* Header del modulo distance.
*/

//Inizio Interfaccia

/**
* Funzione per calcolare la distanza minima.
* Chiama ::LevenshteinDistance passando iterativamente la parola inserita con tutte quelle della categoria.
*
* Una volta calcolata la distanza minima ritorna al modulo manche.cc.
*
* @param[in] parola Stringa inserita dall'utente
* @param[in] x Indice categoria
* @param[in] y Posizione della parola con distanza minima, passata per riferimento
* @return Distanza intera minima trovata
*/
int min_dist (const char * parola, int x, int &y) ;

//Fine Interfaccia




