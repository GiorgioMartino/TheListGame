/**
* @file 
* Header del modulo partita.
*/


//Inizio Interfaccia modulo partita



/**
*Funzione per nascondere un widget ed aprirne un altro.
*
* @param[in] hide Widget da nascondere
* @param[in] hide Widget da aprire
*/
void widget_hide_show(GtkWidget * hide, GtkWidget * show);



/**
*Funzione che aggiorna la label "punteggio".
*
* Chiamata da manche.cc e da partita.cc.
*/
void aggiorna_punteggio();



/**
* Funzione che imposta correttamente la finestra vincitore.
*
* Calcola chi è il vincitore oppure se si ha un pareggio, inizilizza poi
* tutte le label correttamente.
*
* @param[in] player1 Nome del giocatore 1
* @param[in] player1 Nome del giocatore 2
*/
void inizializza_window4(const char * player1, const char * player2);



/**
* Funzione che viene chiamata da main.cc
*
* Inizializza l'array ::m[6], le label contenenti in nomi dei giocatori e tutte le
* altre tramite ::aggiorna_label e ::aggiorna_punteggio.
*
* Dopo questa funzione sarà il turno di ::handler_play_manche, che passerà al modulo manche.cc chiamando la funzione ::manche
* per la gestione di uno specifico turno di gioco.
*
* @param[in] player1 Nome del giocatore 1
* @param[in] player1 Nome del giocatore 2
*/
void gestione_partita (const char * player1, const char * player2);



//Fine Interfaccia modulo partita


