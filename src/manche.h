/**
* @file 
* Header del modulo manche.
*/

//Inizio Interfaccia modulo manche


/**
* Funzione che inizializza l'array ::p di tipo ::puntatore.
*
* Questo array viene usato per conoscere puntatore ad ::elemento, dimensione e nome di ogni categoria.
*/
void riempi();



/**
* Funzione che prepara la schermata della manche tramite valori passati da partita.cc.
* Vengono chiamate le funzioni ::inizializza e ::aggiorna_punteggio_parziale.
*
* A questo punto saranno le due funzioni ::handler_button_V e ::handler_button_stop a controllare il modulo. 
* In particolar modo la prima delle due chiamerà la ::min_dist nel modulo distance.cc per verificare la correttezza della
* parola inserita dal giocatore. La seconda funzione invece si occuperà di ritornare al modulo per la gestione della partita.
*
* @param[in] x Indice della categoria chiamata da ::handler_play_manche
* @param[in] player Nome del giocatore che disputa la manche chiamata
* @param[in] num_manche Contatore delle manches
*/
void manche(const int x,const char *player,int &num_manche);


//Fine Interfaccia modulo manche


