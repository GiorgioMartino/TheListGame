/**
* @file 
* File per la gestione di una singola manche.
*/


#include <iostream>	
#include <stdlib.h>	
#include <cstring>	
#include <gtk/gtk.h>
#include <sstream>

using namespace std;

#include "struttura_dati.h"
#include "partita.h"
#include "manche.h"
#include "distance.h"


#ifdef DEBUG_MODE

extern unsigned int MASK;	
#define DBG(A, B) {if ((A) & MASK) {B; } }

#else

#define DBG(A, B)

#endif



#define D3(a) DBG(4, a)		//Livello di debug per il modulo manche



//--------------------------------------------------------INIZIO DEFINIZIONE FUNZIONI MANCHE---------------------------------------------------

int tot;		/**<Totale parziale di ogni manche.*/

int * visited;		/**<
			* Puntatore ad array dinamico per tenere traccia di quali parole sono già state inserite correttamente.
			* Questo controllo viene effettuato da ::handler_button_V.
			*/

int category;		/**<Indice della cateogoria da passare a ::min_dist.*/

int y;			/**<Indice della parola all'interno di ::category.*/

int errori;		/**<Contatore degli errori per ogni manche.*/

int ripetizioni;	/**<Contatore delle ripetizioni per ogni manche.*/

extern GtkBuilder *builder;

extern ostringstream oss;

extern int tot1;

extern int tot2;

extern bool scherzetto;




void riempi()
{
p[0].punt=auto_italiane;
p[0].dim=8;
strcpy(p[0].nome,"Case Automobilistiche Italiane");

p[1].punt=auto_giapponesi;
p[1].dim=11;
strcpy(p[1].nome,"Case Automobilistiche Giapponesi");

p[2].punt=tipi_cottura;
p[2].dim=12;
strcpy(p[2].nome,"Tipi di Cottura del Cibo");

p[3].punt=sport_palla;
p[3].dim=15;
strcpy(p[3].nome,"Sport in cui si usa la Palla");

p[4].punt=materie_scuola;
p[4].dim=15;
strcpy(p[4].nome,"Materie Scolastiche Medie");

p[5].punt=stati_sudamerica;
p[5].dim=12;
strcpy(p[5].nome,"Stati che fanno parte del Sud America");

p[6].punt=stati_eurozona;
p[6].dim=19;
strcpy(p[6].nome,"Stati dell'UE che usano l'Euro");

p[7].punt=citta_10milioni;
p[7].dim=15;
strcpy(p[7].nome,"Città con oltre 10 milioni di abitanti");

p[8].punt=citta_italiane15;
p[8].dim=15;
strcpy(p[8].nome,"Le 15 città italiane con più abitanti");

p[9].punt=vincitrici_serieA;
p[9].dim=16;
strcpy(p[9].nome,"Squadre che hanno vinto la serie A");

p[10].punt=citta_usa;
p[10].dim=20;
strcpy(p[10].nome,"20 città più importanti degli USA");

p[11].punt=vincitrici_mondiali;
p[11].dim=8;
strcpy(p[11].nome,"Nazionali che hanno vinto i mondiali");

p[12].punt=ambienti_casa;
p[12].dim=15;
strcpy(p[12].nome,"Ambienti che fanno parte della casa");

p[13].punt=muscoli_principali;
p[13].dim=20;
strcpy(p[13].nome,"Muscoli principali");

p[14].punt=pianeti_sistema_solare;
p[14].dim=13;
strcpy(p[14].nome,"Pianeti, pianeti nani e plutoidi del sistema solare");

p[15].punt=harry_potter;
p[15].dim=28;
strcpy(p[15].nome,"Personaggi principali di Harry Potter");

p[16].punt=personaggi_simpson;
p[16].dim=30;
strcpy(p[16].nome,"Personaggi principali dei Simpson");

p[17].punt=i25_atleti;
p[17].dim=25;
strcpy(p[17].nome,"I 25 atleti più pagati al mondo");

p[18].punt=oscar_miglior_film;
p[18].dim=29;
strcpy(p[18].nome,"Oscar miglior film dal 1990 ad oggi");

p[19].punt=serietv_piu_viste;
p[19].dim=20;
strcpy(p[19].nome,"Le 20 serie tv più viste");

p[20].punt=aziende_piu_grandi;
p[20].dim=20;
strcpy(p[20].nome,"Le 20 aziende piu grandi per capitalizzazione di borsa");
}



/**
* Funzione che inizializza l'array visited e le variabili errori, ripetizioni e tot all'inizio di ogni manche.
*
* @param[in] x Indice della categoria per allocare array dinamico ::visited
*/
void inizializza(const int &x)
{
errori=1;
ripetizioni=0;
tot=0;
category=x;

	D3(cout<<"\nErrori inizializzati: "<<errori<<endl
	<<"Ripetizioni inizilizzate: "<<ripetizioni<<endl
	<<"Totale parziale: "<<tot<<endl
	<<"Nome categoria: "<<p[category].nome<<endl);

visited = new int [p[x].dim];

for(int i=0; i<p[x].dim; i++)
	visited[i]=0;
}




/**
* Funzione che aggiorna la label punteggio parziale della manche.
*/
void aggiorna_punteggio_parziale()
{
//svuoto oss e riempio con il punteggio
oss.str("");
oss.clear();
oss<<tot;

GtkLabel * punt_parziale = GTK_LABEL(gtk_builder_get_object(builder, "label8"));
gtk_label_set_text(punt_parziale, oss.str().c_str() );

}




/**
* Funzione che mostra la finestra d'errore relativa ad un punteggio troppo basso.
*/
void dialog_wanna_lose()
{
GtkWidget * dialog4 = GTK_WIDGET(gtk_builder_get_object(builder, "dialog4"));
gtk_widget_show_all(dialog4);
}




/**
*Handler che chiude la finestra d'errore relativa ad un punteggio troppo basso.
*/
extern "C" void dialog_wanna_lose_close(GtkButton *button, gpointer user_data)
{
GtkWidget * dialog4 = GTK_WIDGET(gtk_builder_get_object(builder, "dialog4"));
GtkWidget * window3 = GTK_WIDGET(gtk_builder_get_object(builder, "window3"));

widget_hide_show(dialog4,window3);
}




/**
* Handler del bottone STOP per terminare una manche.
*
* Aggiorna il punteggio del giocatore che ha appena disputato la manche,
* poi controlla se la partita è finita o no e apre la relativa finestra.
*/
extern "C" void handler_button_stop(GtkButton *button, gpointer user_data)
{
GtkLabel * label6 = GTK_LABEL(gtk_builder_get_object(builder, "label6"));
const char * player = gtk_label_get_text(label6);

GtkLabel * label12 = GTK_LABEL(gtk_builder_get_object(builder, "label12"));
const char * player1 = gtk_label_get_text(label12);

GtkLabel * label13 = GTK_LABEL(gtk_builder_get_object(builder, "label13"));
const char * player2 = gtk_label_get_text(label13);

	if (strcmp(player,player1)==0)
		tot1+=tot;
	else
		tot2+=tot;

aggiorna_punteggio();

GtkLabel * label19 = GTK_LABEL(gtk_builder_get_object(builder, "label19"));
const char * turno = gtk_label_get_text(label19);

//Nascondo window3
GtkWidget * window3 = GTK_WIDGET(gtk_builder_get_object(builder, "window3"));
gtk_widget_hide(window3);

//Se la partita è finita apro window4, altrimenti torno a window2
if (strcmp(turno,"-")==0)
	{
	inizializza_window4(player1,player2);
	
	//Apro window4
	GtkWidget * window4 = GTK_WIDGET(gtk_builder_get_object(builder, "window4"));
	gtk_widget_show_all(window4);
	}
else
	{
	//Apro window2
	GtkWidget * window2 = GTK_WIDGET(gtk_builder_get_object(builder, "window2"));
	gtk_widget_show_all(window2);
	}

//Svuoto la textview
GtkTextView * textview1 = GTK_TEXT_VIEW(gtk_builder_get_object(builder, "textview1"));
GtkTextBuffer *buffer = gtk_text_view_get_buffer(textview1);
gtk_text_buffer_set_text(buffer,"",-1);

//Svuoto la gtkentry
GtkEntry * entry3 = GTK_ENTRY(gtk_builder_get_object(builder, "entry3"));
gtk_entry_set_text(entry3, "");

//Dealloco l'array dinamico in visited
delete [] visited;

D3(cout<<"\nHandler button stop terminato -> fine manche."<<endl);
}




/**
* Handler del bottone che invia la parola scritta nella gtkentry.
*
* Viene chiamata la funzione ::min_dist, calcolata la lunghezza della stringa inserita e in base
* a questi paramentri si controlla che la parola sia giusta, un errore oppure una ripetizione
* di una parola già inserita.
* In ogni caso viene mandato il buffer con l'esito di quella stringa alla textview, viene fatto scorrere 
* il cursore della scrolled window e viene chiamata ::aggiorna_punteggio_parziale.
* Viene inoltre controllato che il punteggio non sia troppo basso, in tale caso viene chiamata la funzione
* ::dialog_wanna_lose.
* Infine viene "pulita" la gtkentry, pronta per una nuova parola.
*/
extern "C" void handler_button_V (GtkButton *button, gpointer user_data)
{
GtkEntry * entry3 = GTK_ENTRY(gtk_builder_get_object(builder, "entry3"));
const char * parola = gtk_entry_get_text(entry3);

int dist=min_dist(parola,category,y);

const int len=strlen(parola);

//Seleziono il buffer della textview
GtkTextView *textview1 = GTK_TEXT_VIEW(gtk_builder_get_object(builder, "textview1"));
GtkTextBuffer *buffer = gtk_text_view_get_buffer(textview1);

//Svuoto oss, che mi servirà per aggiornare la textview
oss.str("");
oss.clear();

if ( (visited[y]==0) && (((len<=6) && (dist<2)) || ((len<=9) && (len>6) && (dist<3)) || ((len<=13) && (len>9) && (dist<4)) || ((len<=20) && (len>13) && (dist<5)) || ((len<=30) && (len>20) && (dist<6)) || ((len>30) && (dist<7))) )
	{
	oss<<parola<<"\n\t\t\t\t\tSI\t\t+"<<p[category].punt[y].valore<<"\t\t"<<p[category].punt[y].nome<<endl;

	tot+=p[category].punt[y].valore;
	visited[y]=1;

	if((scherzetto) && (strcmp(p[category].punt[y].nome , "Tom Riddle")==0))
			{		
			GtkWidget * window3 = GTK_WIDGET(gtk_builder_get_object(builder, "window3"));
			GtkWidget * window5 = GTK_WIDGET(gtk_builder_get_object(builder, "window5"));

			widget_hide_show(window3,window5);
			}
	}
else
	{
	if ( (visited[y]!=0) && (((len<=6) && (dist<2)) || ((len<=9) && (len>6) && (dist<3)) || ((len<=13) && (len>9) && (dist<4)) || ((len<=20) && (len>13) && (dist<5)) || ((len<=30) && (len>20) && (dist<6)) || ((len>30) && (dist<7))) )
		{
		ripetizioni++;
		
		oss<<parola<<"\n\t\t\t\t\tRIPETIZIONE\t\t-"<<(ripetizioni*2)<<endl;

		tot-=(ripetizioni*2);
		
		if (tot<=(-50))
			dialog_wanna_lose();			
		}
	else
		{
		errori++;

		oss<<parola<<"\n\t\t\t\t\tERRORE\t\t-"<<(errori/2)<<endl;

		tot-=(errori/2);
		if (tot<=(-50))
			dialog_wanna_lose();
		}
	}

//Inserisco la nuova parola in fondo al buffer
gtk_text_buffer_insert_at_cursor(buffer, oss.str().c_str(), -1);

//Faccio scorrere la scrolled window fino al Mark posto in fondo al buffer
GtkTextMark * mark = gtk_text_buffer_get_insert(buffer);
gtk_text_view_scroll_to_mark(textview1, mark, 0.0, TRUE, 0.0, 1.0);

D3(cout<<"\nNuova stringa inserita!"<<endl);

aggiorna_punteggio_parziale();

gtk_entry_set_text(entry3, "");

}




void manche(const int x,const char * player, int &num_manche)
{

//Nascondo window2 e apro window2
GtkWidget * window2 = GTK_WIDGET(gtk_builder_get_object(builder, "window2"));
GtkWidget * window3 = GTK_WIDGET(gtk_builder_get_object(builder, "window3"));

widget_hide_show(window2,window3);

//Svuoto oss e aggiorno il titolo della window3
oss.str("");
oss.clear();
oss<<"MANCHE "<<(num_manche/2)+1;
	GtkLabel * title_manche = GTK_LABEL(gtk_builder_get_object(builder, "label5"));
	gtk_label_set_text(title_manche, oss.str().c_str() );

//Aggiorno il sottotitolo con il nome del giocatore
GtkLabel * player_manche = GTK_LABEL(gtk_builder_get_object(builder, "label6"));
gtk_label_set_text(player_manche, player );

//Aggiorno tramite oss il nome della categoria
oss.str("");
oss.clear();
oss<<p[x].nome;
	GtkLabel * category_manche = GTK_LABEL(gtk_builder_get_object(builder, "label7"));
	gtk_label_set_text(category_manche, oss.str().c_str() );


inizializza(x);

aggiorna_punteggio_parziale();

return;
}

//--------------------------------------------------------FINE DEFINIZIONE FUNZIONI MANCHE---------------------------------------------------


