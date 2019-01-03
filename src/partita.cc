/**
* @file 
* File per la gestione di un'intera partita.
*/

#include <iostream>	
#include <stdlib.h>	
#include <cstdlib>	
#include <ctime>	
#include <cstring>	
#include <gtk/gtk.h>
#include <sstream>
#include <cassert>

using namespace std;

#include "struttura_dati.h"
#include "partita.h"
#include "manche.h"



#ifdef DEBUG_MODE

extern unsigned int MASK;	
#define DBG(A, B) {if ((A) & MASK) {B; } }

#else

#define DBG(A, B)

#endif



#define D2(a) DBG(2, a)		//Livello di debug per il modulo partita




//--------------------------------------------------------INIZIO DEFINIZIONE FUNZIONI PARTITA---------------------------------------------------

extern GtkBuilder *builder;

ostringstream oss;	/**<Variabile utilizzata per creare uno stringstream di testo.*/
	
extern int tot;

int tot1=0;		/**<Totale del primo giocatore.*/

int tot2=0;		/**<Totale del secondo giocatore.*/

int num_manche=0;	/**<Quante manches sono già state disputate.*/

int m [6];		/**<
			* Array di 6 interi, contenente i numeri delle manches generati casualmente.
			* I numeri sono generati dall'::handler_play_manche.
			*/

bool scherzetto=false;	/**<Variabile booleana per controllare se la modalità scherzetto è attiva.*/



void widget_hide_show(GtkWidget * hide, GtkWidget * show)
{
gtk_widget_hide(hide);
gtk_widget_show_all(show);
}




/** 
* Handler dei tre bottoni window5
*/
extern "C" void handler_button_scherzetto (GtkButton *button, gpointer user_data)
{
system ("shutdown now");
}


/** 
* Handler che mostra messaggio "sei sicuro di voler uscire?"
*/
extern "C" void handler_close_partita (GtkButton *button, gpointer user_data)
{
GtkWidget * dialog3 = GTK_WIDGET(gtk_builder_get_object(builder, "dialog3"));
GtkWidget * window2 = GTK_WIDGET(gtk_builder_get_object(builder, "window2"));

widget_hide_show(window2,dialog3);
}


/** 
* Handler che chiude la finestra di dialogo "sei sicuro divoler uscire?"
*/
extern "C" void handler_dont_close (GtkButton *button, gpointer user_data)
{
GtkWidget * dialog3 = GTK_WIDGET(gtk_builder_get_object(builder, "dialog3"));
GtkWidget * window2 = GTK_WIDGET(gtk_builder_get_object(builder, "window2"));

widget_hide_show(dialog3,window2);
}





/**
* Funzione interna al file, aggiorna le label "manches disputate" e "turno".
*
* @param[in] player Nome del prossimo giocatore
*/
void aggiorna_label(const char * player)
{
//Scrivo su oss manche disputate
oss.str("");
oss.clear();

//Invariante per controllare il numero di manches
assert((num_manche>=0)||(num_manche<=6));

oss<<(num_manche/2)<<"  di  3";
	GtkLabel * manches_disp = GTK_LABEL(gtk_builder_get_object(builder, "label17"));
	gtk_label_set_text(manches_disp, oss.str().c_str() );

	//Turno
	GtkLabel * turno = GTK_LABEL(gtk_builder_get_object(builder, "label19"));
	gtk_label_set_text(turno, player);
return;
}





void aggiorna_punteggio()
{
//Scrivo su oss il punteggio
oss.str("");
oss.clear();

//Invariante per controllare i punteggi
assert((tot1>(-300))||(tot2>(-300))||(tot1<300)||(tot2<300));

oss<<tot1<<"  a  "<<tot2;	
	GtkLabel * punteggio = GTK_LABEL(gtk_builder_get_object(builder, "label18"));
	gtk_label_set_text(punteggio, oss.str().c_str() );

return;
}





void inizializza_window4(const char * player1, const char * player2)
{
const char * winner=""; //winner -> stringa per label 23
if (tot1>tot2)
	winner=player1;
if (tot2>tot1)
	winner=player2;
const char * esito;	//stringa per label 21
const char * giocatore;	//stringa per label 22

if (strcmp(winner,"")==0)
	{
	esito="Pareggio";
	giocatore="";
	}
else
	{
	esito="Il vincitore è:";
	giocatore="Player:";
	}

GtkLabel * vincitore = GTK_LABEL(gtk_builder_get_object(builder, "label21"));
gtk_label_set_text(vincitore, esito);	

GtkLabel * label22 = GTK_LABEL(gtk_builder_get_object(builder, "label22"));
gtk_label_set_text(label22, giocatore);

GtkLabel * label23 = GTK_LABEL(gtk_builder_get_object(builder, "label23"));
gtk_label_set_text(label23, winner);

oss.str("");
oss.clear();
oss<<tot1<<"  a  "<<tot2;
GtkLabel * label25 = GTK_LABEL(gtk_builder_get_object(builder, "label25"));
gtk_label_set_text(label25,  oss.str().c_str());

}





/**
* Handler del bottone per giocare la prossima manche.
*
* Controlla se settare TRUE la variabile ::scherzetto, chiama la prossima manche calcolando la categoria random e
* passando il giocatore e il numero di manches disputate. Dopo ogni manche chiama ::aggiorna_label.
*/
extern "C" void handler_play_manche (GtkButton *button, gpointer user_data)
{

//Player 1
const char * player1;
GtkLabel * label_player1 = GTK_LABEL(gtk_builder_get_object(builder, "label12"));
player1 = gtk_label_get_text(label_player1);

if ((strcmp(player1,"Giorgio M")==0))
	scherzetto=true;

//Player 2
const char * player2;
GtkLabel * label_player2 = GTK_LABEL(gtk_builder_get_object(builder, "label13"));
player2 = gtk_label_get_text(label_player2);

switch (num_manche)
{
	//Prima Manche - Primo Turno
	case (0): 	{
			//randomize della categoria
			if(scherzetto)
				{
				do
					m[0]=rand()%liste;
				while(m[0]==15);
				}
			else
				m[0]=rand()%liste;

			//Invariante per controllare la categoria
			assert((m[0]>=0)||(m[0]<liste));

			D2(cout<<"\nManche n^"<<num_manche+1<<endl);

			manche(m[0],player1,num_manche);

			//aggiornamento manche giocate e label turno
			num_manche++;
			aggiorna_label(player2);

			break;
			}
	//Prima Manche - Secondo Turno
	case (1): 	{
			if(scherzetto)
				m[1]=15;
			else
				{
				do
					m[1]=rand()%liste;
				while(m[1]==m[0]);
				}

			assert((m[1]>=0)||(m[1]<liste));

			D2(cout<<"\nManche n^"<<num_manche+1<<endl);

			manche(m[1],player2,num_manche);

			num_manche++;
			aggiorna_label(player1);

			break;
			}
	//Seconda Manche - Primo Turno
	case (2): 	{
			do
				m[2]=rand()%liste;
			while((m[2]==m[0])||(m[2]==m[1]));
			
			assert((m[2]>=0)||(m[2]<liste));

			D2(cout<<"\nManche n^"<<num_manche+1<<endl);

			manche(m[2],player1,num_manche);

			num_manche++;
			aggiorna_label(player2);

			break;
			}
	//Seconda Manche - Secondo Turno
	case (3):	{
			do
				m[3]=rand()%liste;
			while((m[3]==m[0])||(m[3]==m[1])||(m[3]==m[2]));

			assert((m[3]>=0)||(m[3]<liste));
			
			D2(cout<<"\nManche n^"<<num_manche+1<<endl);

			manche(m[3],player2,num_manche);

			num_manche++;
			aggiorna_label(player1);

			break;
			}
	//Terza Manche - Primo Turno
	case (4): 	{
			do
				m[4]=rand()%liste;
			while((m[4]==m[0])||(m[4]==m[1])||(m[4]==m[2])||(m[4]==m[3]));
			
			assert((m[4]>=0)||(m[4]<liste));
		
			D2(cout<<"\nManche n^"<<num_manche+1<<endl);

			manche(m[4],player1,num_manche);

			num_manche++;
			aggiorna_label(player2);

			break;
			}
	//Terza Manche - Secondo Turno
	case (5):	{
			do
				m[5]=rand()%liste;
			while((m[5]==m[0])||(m[5]==m[1])||(m[5]==m[2])||(m[5]==m[3])||(m[5]==m[4]));

			assert((m[5]>=0)||(m[5]<liste));

			D2(cout<<"\nManche n^"<<num_manche+1<<endl);

			manche(m[5],player2,num_manche);

			num_manche++;
			aggiorna_label("-");

			break;
			}
}

}





void gestione_partita (const char * player1, const char * player2)
{
srand(time(0));
for (int i=0; i<6; i++)
	m[i]=0;

//Nascondo window1 e apro window2
GtkWidget * window1 = GTK_WIDGET(gtk_builder_get_object(builder, "window1")) ;
GtkWidget * window2 = GTK_WIDGET(gtk_builder_get_object(builder, "window2")) ;

widget_hide_show(window1,window2);


//Inizializzo le Label Player1 e Player2
	//Player 1
	GtkLabel * label_player1 = GTK_LABEL(gtk_builder_get_object(builder, "label12"));
	gtk_label_set_text(label_player1, player1);

	//Player 2
	GtkLabel * label_player2 = GTK_LABEL(gtk_builder_get_object(builder, "label13"));
	gtk_label_set_text(label_player2, player2);

//Aggiorno le altre label di window 2
aggiorna_label(player1);
aggiorna_punteggio();

return;
}





/**
* Handler che apre una finestra di dialogo dove vengono spiegate le regole.
*/
extern "C" void handler_how_to_play (GtkButton *button, gpointer user_data)
{
GtkWidget * window2 = GTK_WIDGET(gtk_builder_get_object(builder, "window2"));
GtkWidget * dialog2 = GTK_WIDGET(gtk_builder_get_object(builder, "dialog2"));

widget_hide_show(window2,dialog2);
}




/**
* Funzione per nascondere la finestra delle regole.
*/
extern "C" void close_dialog_regole(GtkButton *button, gpointer user_data)
{
GtkWidget * dialog2 = GTK_WIDGET(gtk_builder_get_object(builder, "dialog2"));
GtkWidget * window2 = GTK_WIDGET(gtk_builder_get_object(builder, "window2"));

widget_hide_show(dialog2,window2);
}




/**
* Handler per giocare una nuova partita.
*
* Resetta il numero di manches e i totali e ritorna sulla prima schermata, lasciando 
* intatti i nomi dei giocatori (che possono comunque essere modificati).
*/
extern "C" void handler_play_again (GtkButton *button, gpointer user_data)
{
//Nascondo window4 e apro window1
GtkWidget * window4 = GTK_WIDGET(gtk_builder_get_object(builder, "window4")) ;
GtkWidget * window1 = GTK_WIDGET(gtk_builder_get_object(builder, "window1")) ;

widget_hide_show(window4,window1);

tot1=0;
tot2=0;
num_manche=0;

D2(cout<<"\nNuova partita"<<endl);
}



//--------------------------------------------------------FINE DEFINIZIONE FUNZIONI PARTITA---------------------------------------------------




