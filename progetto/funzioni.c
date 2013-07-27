#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "funzioni.h"
#define MAX 1000


/*	Derivate fondamentali	*/
char *D_Principali(char *primo_operando)
{
	if ( strcmp( primo_operando, "x" ) != 0 ) { 	return "0";	}
	else	
	return "1";
}
char *Pow(char *funzione_1,char *funzione_2, char *potenza)
{	
	potenza = (char *)malloc(sizeof(char)*(7+strlen(funzione_1)+strlen(funzione_2)));
	sprintf(potenza, "Mul(%s,(Pow(%s,Sot(%s,1)))", funzione_2,funzione_1,funzione_2);		
	return potenza;				
}
char *Sum(char *funzione_1,char *funzione_2, char *somma)
{

	somma = (char *)malloc(sizeof(char)*(7+strlen(funzione_1)+strlen(funzione_2)));
	if(funzione_1[0]=='m' || funzione_1[0]=='s' || funzione_1[0]=='p' || funzione_1[0] == 'c')
			funzione_1=split(funzione_1);
	else
		 funzione_1 = D_Principali(funzione_1);
	if(funzione_2[0]=='m' || funzione_2[0]=='s' || funzione_2[0]=='p' || funzione_2[0] == 'c' )
			funzione_2=split(funzione_2);	
	else 
		 funzione_2=D_Principali(funzione_2);

	
	printf("funzione_1 = %s\n", funzione_1);
	printf("funzione_2 = %s\n\n", funzione_2);
	

	sprintf(somma, "Plus(%s,%s)",funzione_1, funzione_2);		
	return somma;				

}
char *Sot(char *funzione_1,char *funzione_2, char *sottrazione)
{
	sottrazione = (char *)malloc(sizeof(char)*(7+strlen(funzione_1)+strlen(funzione_2)));
	if(funzione_1[0]=='m' || funzione_1[0]=='s' || funzione_1[0]=='p' || funzione_1[0] == 'c')
		{	funzione_1=split(funzione_1);	}
	else
		{ funzione_1=D_Principali(funzione_1);}
	if(funzione_2[0]=='m' || funzione_2[0]=='s' || funzione_2[0]=='p' || funzione_1[0] == 'c')
		{	funzione_2=split(funzione_2);	}
	else 
		{ funzione_2=D_Principali(funzione_2);}

	sprintf(sottrazione, "Sot(%s,%s) ",funzione_1, funzione_2);		
	return sottrazione;				
}
/*------------------------------------------------------*
*		    Funizione Prodotto			*
* 							*
*	        questa funzione calcola			*
*   	        la derivata del prodotto		*
*							*
*     D(f(x) * g(x)) = f'(x) * g(x) + f(x) * g'(x)	*
*-------------------------------------------------------*/
char *Mul(char *funzione_1, char *funzione_2, char *prodotto)
	{
		char *d_funzione_2;	
		char *d_funzione_1;   // d_funzione_* corrisponde alla derivata di quella funzione
		
	prodotto = (char *)malloc(sizeof(char)*(7+sizeof(funzione_1)+sizeof(funzione_2)));
	if(funzione_1[0]=='m' || funzione_1[0]=='s' || funzione_1[0]=='p')
		{	d_funzione_1=split(funzione_1);	}
	else
		{	d_funzione_1=D_Principali(funzione_1);}
	if(funzione_2[0]=='m' || funzione_2[0]=='s' || funzione_2[0]=='p')
		{	d_funzione_2=split(funzione_2);	}
	else 
		{	d_funzione_2=D_Principali(funzione_2);}

	sprintf(prodotto,"Plus(Mul(%s,%s),Mul(%s,%s))",d_funzione_1,funzione_2,funzione_1,d_funzione_2);
	return prodotto;
	}
char *Cos(char *funzione_1, char *derivata_1, char *coseno)
	{

		coseno = (char *)malloc(sizeof(char)*(7+strlen(funzione_1)));
		if(funzione_1[0]=='m' || funzione_1[0]=='s' || funzione_1[0]=='p')
			{	derivata_1 = split(funzione_1);	}
		else
			{	derivata_1 = D_Principali(funzione_1);}

		sprintf(coseno, "Mul(-Sin(%s),%s)",funzione_1, derivata_1);		
	
		return coseno;
	}
char *Sin(char *funzione_1, char *derivata_1, char *seno)
	{

		seno = (char *)malloc(sizeof(char)*(7+strlen(funzione_1)));
		if(funzione_1[0]=='m' || funzione_1[0]=='s' || funzione_1[0]=='p')
			{	derivata_1 = split(funzione_1);	}
		else
			{	derivata_1 = D_Principali(funzione_1);}

		sprintf(seno, "Mul(Cos(%s),%s)",funzione_1, derivata_1);		
	
		return seno;
	}
/*------------------------------------------------------*
*		Funzione Ricerca_e_deriva		*
*							*
*	questa funzione ci permette di entrare nella	*
*      funzione corrispondente all'operatore in esame,	*
*     la quale successivamente calcolerà la derivata.	*
*							*
*-------------------------------------------------------*/

char *Ricerca_e_deriva(char *funzione_1, char *funzione_2, char *primo_operando, char *output)
{
	output = (char *)malloc(sizeof(char)*10000);
	if ( strcmp(primo_operando,"x") == 0 || ( strcmp(primo_operando,"plus") != 0 && strcmp(primo_operando,"mul") != 0 && strcmp(primo_operando,"sot") != 0 && strcmp(primo_operando,"pow") != 0 ))
	D_Principali(primo_operando); // Se il primo operando è una x oppure non è nessuna delle funzioni previste allora chiama D_Principali 	

	if(strcmp(primo_operando,"pow")==0)  //---------------------------------------- POW
		{
			output=Pow(funzione_1,funzione_2, output);
		}
	else if(strcmp(primo_operando,"mul")== 0)	 //------------------------------------------- Mul
		{	
			output=Mul(funzione_1 ,funzione_2, output);	
		}
	else if(strcmp(primo_operando,"plus") == 0)	//------------------------------------------- Add
		{ 
			output=Sum(funzione_1,funzione_2, output);
		}
	else if(strcmp(primo_operando,"sot") == 0)	//------------------------------------------- Sot
		{ 	output=Sot(funzione_1,funzione_2, output);}
	else if(strcmp(primo_operando,"sin") == 0)	//------------------------------------------- Sot
		{	output = Sin(funzione_1, "", output);}
	else if(strcmp(primo_operando,"cos") == 0)	//------------------------------------------- Sot
		{	output = Cos(funzione_1, "", output);}
/*	if(strcmp(primo_operando,"div")== 0)	//------------------------------------------- Div
	{ 
		//Div();
	}*/
	return output;	
}
char *split(char *str)
{
	int x = 0,y = 0,yy=0, pt = 0,max,flag_primo=1, contatore_aperta = 1;
	char parte_tok[MAX]="", funzione_1[MAX]="", funzione_2[MAX]="",primo_operando[MAX]="";	


	max=strlen(str);
	printf("stringa principale = %s\n", str);	// stampa vett originale
	while(x <= max )							//ciclo per scorrere il vett
	{
		if(flag_primo==1)
		{
			primo_operando[x]=str[x];
			if(str[x+1]=='(' )
			flag_primo=0;
		}

		if(str[x-1]=='(')					// inizia a copiare 
		{	
			while(contatore_aperta>0)		// copia fino a quando 
			{	
				if(str[x]=='(')	contatore_aperta++;
				if(str[x+1]==',')	contatore_aperta--;
				if(str[x-1]=='(' && str[x+1]==')')	contatore_aperta--;
				parte_tok[y]=str[x];	//copia cella per cella nel vett di out
				x++,y++;
			}
			strcpy(funzione_1,parte_tok);
			x++;
			for(pt=0;pt<MAX;pt++) {	parte_tok[pt]=0;}
		}
		else if(contatore_aperta==0)
		{
			while(x <= max-1 )
			{	parte_tok[yy]=str[x-1];
				yy++,x++;
			}
			strcpy(funzione_2,parte_tok);
			for( pt=0; pt<MAX;pt++) { parte_tok[pt]=0;	}
			
		}
		x++;
	}
	printf("funzione_1 %s\n",funzione_1);
	printf("funzione_2 %s\n",funzione_2);
	printf("primo_operando = %s\n", primo_operando);
	return Ricerca_e_deriva(funzione_1,funzione_2,primo_operando, NULL);
}

