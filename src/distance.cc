/**
* @file 
* File per il calcolo della distanza minima tra una parola e la sua categoria.
*/

#include <iostream>	
#include <stdlib.h>	
#include <cstring>

using namespace std;

#include "struttura_dati.h"
#include "distance.h"


#ifdef DEBUG_MODE

extern unsigned int MASK;	
#define DBG(A, B) {if ((A) & MASK) {B; } }

#else

#define DBG(A, B)

#endif



#define D4(a) DBG(8, a)		//Livello di debug per il modulo distance



//--------------------------------------------------INIZIO DEFINIZIONE FUNZIONI DISTANCE--------------------------------------------------------

/**
* Funzione che calcola la distanza tra due stringhe.
* 
* @param[in] s Prima stringa
* @param[in] t Seconda stringa
* @return Valore intero della distanza tra le due stringhe
*/
int LevenshteinDistance(const char * s, const char * t) 
{
    int n = strlen(s);
    int m = strlen(t);
    int d[n+1][m+1];
    if (n == 0) {
        return m;
    }
    if (m == 0) {
        return n;
    }
    for (int i = 0; i <= n; i++) {
        d[i][0] = i;
    }
    for (int j = 0; j <= m; j++) {
        d[0][j] = j;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            int cost = (t[j-1] == s[i-1])?0:1;
            d[i][j] = min(min(d[i-1][j]+1,d[i][j-1]+1),d[i-1][j-1]+cost);
        }
    }
    return d[n][m];
}




int min_dist (const char * parola, int x, int &y)
{
int min=1000;
int a;
	for(int i=0; i<(p[x].dim); i++)
		{
		a=LevenshteinDistance(parola,p[x].punt[i].nome);
		if (a<min)
			{
			min=a;
			y=i;
			}
		}
D4(cout<<"\nDistanza minima calcolata: "<<min<<endl);	
return min;
}

//-------------------------------------------------FINE DEFINIZIONE FUNZIONI DISTANCE--------------------------------------------------------






