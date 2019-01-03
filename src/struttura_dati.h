/**
* @file 
* File contenente dichiarazioni di strutture e variabili condivise a tutti i file.
*/


//STRUTTURA DATI DEL GIOCO
const int liste=21;		/**< Variabile contenente il numero di categorie, per creare un array di ::puntatore. */

const int max_nome=45;		/**< Variabile contenente la massima lunghezza di un campo nome nella struct ::elemento. */

/**
* Struttura elememto, contenente tutti i nomi e valori di ogni categoria.
*
* La struct elemento viene chiamata durante l'esecuzione del programma
* tramite il puntatore punt della struct ::puntatore. In questo modo viene controllata la
* correttezza delle parole inserite tramite la funzione ::min_dist.
*/
struct elemento {char nome[max_nome];
		 int valore; };

extern elemento auto_italiane[];

extern elemento auto_giapponesi[];

extern elemento tipi_cottura[];

extern elemento sport_palla[];

extern elemento materie_scuola[];

extern elemento stati_sudamerica[];

extern elemento stati_eurozona[];

extern elemento citta_10milioni[];

extern elemento citta_italiane15[];

extern elemento vincitrici_serieA[];

extern elemento citta_usa[];

extern elemento vincitrici_mondiali[];

extern elemento ambienti_casa[];

extern elemento muscoli_principali[];

extern elemento pianeti_sistema_solare[];

extern elemento harry_potter[];

extern elemento personaggi_simpson[];

extern elemento i25_atleti[];

extern elemento oscar_miglior_film[];

extern elemento serietv_piu_viste[];

extern elemento aziende_piu_grandi[];

/*
elemento []=
{"",,"",,"",,"",,"",,"",,"",,"",,"",,"",,"",,"",,"",,"",,"",};
*/

/**
* Struttura puntatore, contenente indirizzo, dimensione e nome di una data categoria.
*
* Con la struct puntatore verrà creato un array di puntatori,
* uno per ogni categoria. Questo viene usato nella funzione ::handler_button_V per visualizzare
* un certo elemento di una certa categoria.
*/
struct puntatore {elemento *punt; 
		  int dim;
		  char nome[55]; };
extern puntatore p[liste];


