/**
* @mainpage The List Game
*
* Gioco basato su parole e categorie, un giocatore contro un altro. Per ogni categoria il giocatore
* deve inserire più parole possibili per quella categoria. Ogni partita si basa su tre Manches, una
* per giocatore. Alla fine vince il giocatore con il punteggio piu alto.
*
* Il programma è diviso in 4 moduli:
*
* - Il modulo main.cc che contiene la funzione ::main e gli handler della prima schermata. 
*
* - Il modulo partita.cc si occupa della gestione dell'intera partita dall'inizio alla fine. Tramite la
* funzione ::handler_play_manche si passa al modulo manche.
*
* - Il modulo manche.cc gestisce una singola manche con tutti i controlli sulle parole inserite e attribuisce i
* punteggi, oltre che inizializzare l'array di puntatori ::p. 
*
* - Infine c'è il modulo distance.cc che viene chiamato dal modulo manche ed è responsabile di calcolare la distanza
* minima tra la parola inserita dall'utente e tutte quelle della categoria.
*
* @author Giorgio Martino
*/

/**
* @file 
* File contenente la funzione ::main.
*/

#include <iostream>	
#include <stdlib.h>	
#include <cstring>
#include <gtk/gtk.h>

using namespace std;

#include "struttura_dati.h"
#include "partita.h"
#include "manche.h"



#ifdef DEBUG_MODE

unsigned int MASK;
#define DBG(A, B) {if ((A) & MASK) {B; } }

#else

#define DBG(A, B)

#endif



#define D1(a) DBG(1, a)		//Livello di debug per il modulo main



elemento auto_italiane[8]=
{"Alfa Romeo",1,"Ferrari",1,"Abarth",3,"Maserati",2,"Fiat",1,"Lamborghini",2,"Dr",3,"Lancia",2};

elemento auto_giapponesi[11]= 
{"Infiniti",2,"Nissan",1,"Toyota",1,"Isuzu",3,"Honda",1,"Suzuki",2,"Mazda",2,"Mitsubishi",2,"Subaru",1,"Daihatsu",3,"Lexus",1};

elemento tipi_cottura[12]={"Fritto",1,"Forno",1,"Vapore",2,"Bollito",1,"Piastra",1,"Arrosto",1,"Lessa",2,"Bagnomaria",3,"Brasato",2,"Irraggiato",3,
"Stufato",1,"Affumicato",2};

elemento sport_palla[15]=
{"Pallamano",2,"Baseball",1,"Golf",1,"Cricket",2,"Hockey su prato",3,"Ping Pong",1,"Squash",3,"Tennis",1,
"Basket",1,"Football",2,"Calcio",1,"Pallavolo",1,"Beach Volley",2,"Rugby",1,"Pallanuoto",3};

elemento materie_scuola[15]=
{"Italiano",1,"Storia",1,"Geografia",2,"Matematica",1,"Scienze",1,"Inglese",1,"Francese",2,"Spagnolo",2,"Tedesco",3,"Arte",1,
"Educazione Fisica",1,"Tecnologia",3,"Musica",2,"Religione",1,"Geometria",2};

elemento stati_sudamerica[12]=
{"Argentina",1,"Bolivia",1,"Brasile",1,"Cile",1,"Colombia",1,"Ecuador",2,"Guyana",3,"Paraguay",2,"Perù",1,"Suriname",3,"Uruguay",1,
"Venezuela",1};

elemento stati_eurozona[19]=
{"Austria",1,"Belgio",1,"Finlandia",1,"Francia",1,"Germania",1,"Irlanda",1,"Italia",1,"Lussemburgo",2,"Paesi Bassi",1,"Portogallo",1,
"Spagna",1,"Grecia",1,"Slovenia",2,"Cipro",2,"Malta",2,"Slovacchia",3,"Estonia",3,"Lettonia",3,"Lituania",3};

elemento citta_10milioni[15]=
{"Shangai",1,"Karachi",3,"Pechino",1,"Lagos",2,"Città del Messico",1,"Delhi",2,"Tientsin",3,"Istanbul",1,"Tokyo",1,
"Canton",3,"Mumbai",2,"Mosca",1,"San Paolo",1,"Giacarta",3,"Kinshasa",3};

elemento citta_italiane15[15]=
{"Roma",1,"Milano",1,"Napoli",1,"Torino",1,"Palermo",1,"Genova",1,"Bologna",1,"Firenze",1,"Bari",2,"Catania",2,
"Venezia",1,"Verona",2,"Messina",3,"Padova",2,"Trieste",3};

elemento vincitrici_serieA[16]=
{"Juventus",1,"Milan",1,"Inter",1,"Roma",1,"Lazio",1,"Sampdoria",2,"Napoli",1,"Hellas Verona",2,"Torino",2,"Cagliari",2,
"Fiorentina",1,"Bologna",1,"Genoa",2,"Novese",3,"Pro Vercelli",3,"Casale",3};

elemento citta_usa[20]=
{"New York",1,"Los Angeles",1,"Chicago",1,"Houston",1,"Filadelfia",2,"Phoenix",2,"San Antonio",2,"San Diego",1,"Dallas",1,"San Jose",2,
"Austin",1,"Jacksonville",3,"Indianapolis",2,"San Francisco",1,"Columbus",1,"Fort Worth",3,"Charlotte",3,"Detroit",1,"El Paso",2,
"Memphis",2};

elemento vincitrici_mondiali[8]=
{"Brasile",1,"Germania",1,"Italia",1,"Francia",2,"Inghilterra",2,"Uruguay",3,"Spagna",1,"Argentina",2};

elemento ambienti_casa[15]=
{"Camera da letto",1,"Cucina",1,"Sala da pranzo",2,"Bagno",1,"Ingresso",1,"Corridoio",1,"Disimpegno",3,"Balcone",1,"Terrazzo",2,
"Scala",1,"Garage",1,"Cantina",1,"Soggiorno",2,"Taverna",2,"Soffitta",3};

elemento muscoli_principali[20]=
{"Bicipite",1,"Tricipite",1,"Deltoide",1,"Trapezio",1,"Pettorale",1,"Dorsale",1,"Addominali",1,"Quadricipite Femorale",1,"Bicipite Femorale",2,"Adduttori",2,"Abduttori",2,"Gluteo",1,"Sternocleidomastoideo",1,"Facciali",1,"Sartorio",3,"Gastrocnemio",3,"Tibiale anteriore",3,"Estensore",3,"Ileopsas",3,"Obliquo esterno",3};

elemento pianeti_sistema_solare[13]=
{"Terra",1,"Marte",1,"Marcurio",1,"Saturno",1,"Giove",1,"Venere",1,"Urano",2,"Nettuno",2,"Cerere",3,"Plutone",2,"Haumea",3,
"Makemake",3,"Eris",3};

elemento harry_potter[28]=
{"Harry Potter",1,"Lily Potter",2,"James Potter",2,"Ron Weasley",1,"Hermione Granger",1,"Hagrid",1,"Fred Weasley",2,"George Weasley",2,
"Ginny Weasley",2,"Albus Silente",1,"Minerva McGrannit",2,"Severus Piton",1,"Remus Lupin",2," Neville Paciock",1,"Draco Malfoy",1,
"Cho Chang",2,"Cedric Diggory",2,"Sirius Black",1,"Peter Minus",2,"Lucius Malfoy",2,"Bellatrix",2,"Lord Voldemort",1,"Dobby",2,"Luna Lovegood",3,"Nagini",3,"Edvige",3,"Viktor Krum",3,"Tom Riddle",2};

elemento personaggi_simpson[30]=
{"Homer Simpson",1,"Bart Simpson",1,"Marge Simpson",1,"Montgomery Burns",1,"Lisa Simpson",1,"Apu Nahasapeemapetilon",3,"Ned Flanders",1,"Milhouse Van Houten",2,"Boe Szyslak",2,"Krusty il Clown",2,"Waylon Smithers",1,"Barney Gumble",1,"Edna Caprapall",1,"Patty Bouvier",1,"Selma Bouvier",1,"Seymour Skinner",1,"Ralph Winchester",1,"Clancy Winchester",2,"Martin Prince",1,"Abraham Simpson",1,"Lenny Leonard",1,"Maggie Simpson",1,"Kent Brockman",2,"Joe Quimby",2,"Timothy Lovejoy",3,"Tony Ciccione",2,"Julius Hibbert",2,"Carl Carlson",1,
"Nelson Muntz",1,"Telespalla Bob",2};

elemento i25_atleti[25]=
{"Cristiano Ronaldo",1,"Le Bron James",1,"Lionel Messi",1,"Roger Federer",1,"Kevin Durant",2,"Andrew Luck",3,"Rory McIlroy",3,"Stephen Curry",2,"James Harden",2,"Lewis Hamilton",1,"Drew Brees",3,"Phil Mickelson",3,"Russell Westbrook",3,"Sebastian Vettel",1,"Damian Lillard",3,"Novak Djokovic",2,"Tiger Woods",1,"Neymar",1,"Dwayne Wade",2,"Fernando Alonso",1,"Jordan Spieth",3,"Derrick Rose",3,"Usain Bolt",1,"Gareth Bale",2,"Conor McGregor",1};

elemento oscar_miglior_film[29]=
{"A spasso con Daisy",1,"Balla coi lupi",1,"Il silenzio degli innocenti",1,"Gli spietati",2,"Schindler's list",3,"Forrest Gump",1,
"Braveheart",2,"Il paziente inglese",2,"Titanic",1,"Shakespeare in Love",2,"American Beauty",1,"Il gladiatore",1,"A Beautiful Mind",1,
"Chicago",3,"Il Signore degli Anelli - Il ritorno del re",3,"Million Dollar Baby",2,"Crash",2,"The Departed",1,"Non è un paese per vecchi",1,
"The Millionaire",1,"The Hurt Locker",2,"Il discorso del re",2,"The Artist",2,"Argo",1,"12 anni schiavo",1,"Birdman",1,
"Il caso Spotlight",1,"Moonlight",2};

elemento serietv_piu_viste[20]=
{"Sex and the City",1,"Modern Family",1,"Downton Abbey",2,"Game of Thrones",1,"Friends",1,"Six Feet Under",3,"The Walking Dead",1,
"The Americans",2,"Star Trek",1,"Ai confini della realtà",3,"Battlestar Galactica",3,"Homeland",1,"Mad Men",1,"Boardwalk Empire",2,
"Twin Peaks",2,"Buffy",2,"Lost",1,"Breaking Bad",1,"I Soprano",2,"X-Files",2,};

elemento aziende_piu_grandi[20]=
{"Apple",1,"Alphabet",2,"Microsoft",1,"Berkshire Hathaway",2,"Amazon",1,"Facebook",1,"ExxonMobil",3,"Johnson & Johnson",2,
"JPMorgan Chase",2,"General Electric",1,"Wells Fargo",3,"AT&T",1,"Tencent Holdings",2,"Alibaba",1,"ICBC",3,"Royal Dutch Shell",1,
"Bank of America",1,"Nestle",2,"China Mobile",2,"Procter & Gamble",3};


puntatore p[liste];	/**< Array di tipo ::puntatore ad ogni categoria. Viene inizializzato con la funzione ::riempi */

GtkBuilder *builder;	/**< Oggetto GTkBuilder, creato tramite gtk_builder_new nel ::main */




/**
* Handler per terminare il programma.
*/
extern "C" void handler_delete_event(GtkWidget *widget,GdkEvent  *event,gpointer   user_data)
{
	D1(cout<<"\n\tProgramma terminato"<<endl);
	gtk_main_quit() ;
}




/**
* Handler per nascondere la finestra di errore.
*
* La finestra può essere generata dall'inserimento dei nomi 
* dei Player 1 e Player 2.
*/
extern "C" void close_current_window(GtkButton *button, gpointer user_data)
{
GtkWidget * dialog1 = GTK_WIDGET(gtk_builder_get_object(builder, "dialog1"));
GtkWidget * window1 = GTK_WIDGET(gtk_builder_get_object(builder, "window1"));

widget_hide_show(dialog1,window1);
}



/**
* Funzione che imposta un messaggio e mostra la relativa finestra d'errore.
*
* @param[in] error_string Messaggio d'errore per la finestra
*/
void show_error_dialog (const char *error_string)
{
GtkLabel * label_error = GTK_LABEL(gtk_builder_get_object(builder, "label4"));
gtk_label_set_text(label_error, error_string);

GtkWidget * dialog1 = GTK_WIDGET(gtk_builder_get_object(builder, "dialog1"));
GtkWidget * window1 = GTK_WIDGET(gtk_builder_get_object(builder, "window1"));

widget_hide_show(window1,dialog1);
}




/**
* Handler del pulsante PLAY nella prima finestra.
*
* Dopo aver inserito i nomi dei giocatori, esegue un controllo sulle due stringhe
* e se va tutto bene chiama la funzione ::gestione_partita,
* altrimenti chiama ::show_error_dialog.
*/
extern "C" void handler_button_play(GtkButton *button, gpointer user_data)
{
//Seleziono la prima GtkEntry e metto il testo in una stringa
GtkEntry * entry1 = GTK_ENTRY(gtk_builder_get_object(builder, "entry1"));
const char * player1 = gtk_entry_get_text(entry1);

//Ripeto la stessa operazione per la seconda GtkEntry
GtkEntry * entry2 = GTK_ENTRY(gtk_builder_get_object(builder, "entry2"));
const char * player2 = gtk_entry_get_text(entry2);

if ((strlen(player1)==0)||(strlen(player1)>20))
	show_error_dialog("Nome Player 1 non valido.");
else
	{
	if ((strlen(player2)==0)||(strlen(player2)>20))
		show_error_dialog("Nome Player 2 non valido.");
	else
		{
		if (strcmp(player1,player2)==0)
			show_error_dialog("I nomi dei due giocatori devono essere diversi.");
		else
			gestione_partita(player1,player2);
		}
	}
}





/**
* Funzione main.
*
* Chiama la funzione ::riempi, carica l'interfaccia grafica e connette tutti i segnali delle gtk,
* infine chiama gtk_main() che genera l'inizio degli eventi.
* Dopo l'inserimento corretto dei nomi dei giocatori si passa al madulo partita.cc chiamando la funzione ::gestione_partita.
*/
int main(int argc, char *argv[])

{

#ifdef DEBUG_MODE
	cout<<"Inserire valore della Mask, ricordando che esistono 4 livelli di debug."<<endl
	<<"Livello 1 = 1, Livello 2 = 2, Livello 3 = 4, Livello 4 = 8"<<endl
	<<"Per attivarli tutti settare mask=15"<<"\n\nMask: ";
	cin>>MASK;
#endif


riempi();

	D1(cout<<"\nFunzione riempi eseguita"<<endl
	<<"test: "<<endl
	<<"Prima auto italiana: "<<p[0].punt[0].nome<<endl
	<<"Dimensione regioni italiane: "<<p[10].dim<<endl
	<<"Nome ultima cat. atleti: "<<p[17].nome<<endl);

//Inizializzazioni Gtk
gtk_init(&argc, &argv);
builder = gtk_builder_new();
gtk_builder_add_from_file(builder,"grafica.glade", NULL);
gtk_builder_connect_signals(builder, NULL);

//Inizio eventi
gtk_main();
	

return 0;
}






