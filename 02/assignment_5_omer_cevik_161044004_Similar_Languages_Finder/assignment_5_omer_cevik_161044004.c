/*
											CSE 102 Homework Assignment 5 

												OMER_CEVIK_161044004


					# 		In here we are reading files. And we compare the unknown language			 #
					# 			with known language. And we check out which language is					 #
					#			 	more similar to our unknown language.								 # 


																															*/
#include <stdio.h>	/* We use FILE pointers, if, else, for loops etc. */
#include <stdlib.h>	/* We use realloc function.						  */

#define MAX_SIZE 27*27	/* We define our maximum size of arrays.	  */

int* FrequencyOfLanguage(char *LangX, int *FreqLan, int *CounterFreq, char *filenameLan);	/* We calculate the frequencies here.		*/
double TotalBigramCalculateLanguage(int *FrequencyX, int *FrequencyLanguage, int *SizeCounter, int *SizeCounterX);	/* We calculate the result here.	*/
void ReadLanguage(char **Language, char *filename);		/* We read into char array the language.*/
void dissimilarity(char *filename1, char *filename2);	/* We calculate the dissimilarity here.	*/

int main()						/* We call our functions in here.  */
{
	dissimilarity("language_x.txt","language_1.txt");			/* We calculate the dissimilarity of language x and language 1. 	*/
	dissimilarity("language_x.txt","language_2.txt");			/* We calculate the dissimilarity of language x and language 2. 	*/
	dissimilarity("language_x.txt","language_3.txt");			/* We calculate the dissimilarity of language x and language 3. 	*/
	dissimilarity("language_x.txt","language_4.txt");			/* We calculate the dissimilarity of language x and language 4. 	*/
	dissimilarity("language_x.txt","language_5.txt");			/* We calculate the dissimilarity of language x and language 5. 	*/

	return 0;	/* Ending our story truely.	*/
}

void ReadLanguage(char **Language, char *filename)			/* We read into char array the language.*/
{
	FILE *f = fopen(filename,"r");							/* We open to read our file.			*/

	int i = 0;												/* It's just a counter.					*/

	do{														/* We start a loop to read language into an array.		*/
		++i;														/* We count for to read.		*/
		*Language = (char*)realloc(*Language,i*sizeof(char));		/* We get dynamic memory.		*/
		fscanf(f,"%c",&((*Language)[i-1]));							/* We read file into the array.	*/
		
	}while(!feof(f));												/* We check loop about if it is end of line.	*/

	*Language = (char*) realloc(*Language,(i+1)*sizeof(char));		/* We get dynamic memory for to last character.	*/

	(*Language)[i] = '\0'; 		/* We assign the last character.	*/

	fclose(f);					/* We close our file.				*/
}

int* FrequencyOfLanguage(char *Lang, int *FreqLan, int *CounterFreq, char *filenameLan)	/* We calculate each bi-gram's frequency of languages.		*/
{
	FILE *fp = fopen(filenameLan,"r");			/* We open the file to read.					*/

	char mychar1, mychar2;						/* We use them to read the languages bi-grams.	*/
	int i, counterStartBigram = 0;				/* i is just counter. CounterStartBigram counts for to fseek function. */ 

	*CounterFreq = 0;							/* It counts for our bigram.					*/

	for (i = 0; i < MAX_SIZE; ++i)				/* We are making a loop to initialize our frequency array.		*/
	{
		FreqLan[i] = 0;							/* We initialize our frequency array.			*/
	}

	fscanf(fp,"%c%c",&mychar1,&mychar2);		/* We read bigrams from languages texts.		*/

	for (i = 0;	Lang[i] != '\0' && mychar2 != EOF; ++i)	/* We are making loop in our language x array.			*/
	{
		if ( mychar1 == ' ' && mychar2 == ' ' )								/* We check if our bigrams of all equal to spaces.		*/
		{
			fseek(fp,-1,SEEK_CUR);											/* If it equals then we move our file pointer.			*/
			++counterStartBigram;											/* We count our Bigramcounter.							*/
		}
		else if ( mychar1 == Lang[i] && mychar2 == Lang[i+1] )				/* We check if our bigrams equals to language x array.	*/
		{
			fseek(fp,-1,SEEK_CUR);											/* If it equals then we move our file pointer.			*/
			++FreqLan[*CounterFreq];										/* We count our frequency array.						*/
		}
		else if ( Lang[i+1] == '\0' )										/* We check if we are end of the language x array.		*/
		{
			++(*CounterFreq);												/* If it is, then we count for to check another bigram.	*/
			++counterStartBigram;											/* We count our Bigramcounter.							*/
			i = 0;															/* We initialize again our counter.						*/
			fseek(fp,counterStartBigram,SEEK_SET);							/* We are coming start position of our file.			*/	
			fscanf(fp,"%c%c",&mychar1,&mychar2);							/* We read another bigram.								*/
		}
		
	}

	fclose(fp);									/*		 We close our file.								*/

	return FreqLan;								/* We return our frequencies of languages bigrams.		*/
}

double TotalBigramCalculateLanguage(int *FrequencyX, int *FrequencyLanguage, int *SizeCounter, int *SizeCounterX)	/* We calculate the total bigram's frequencies and dissimilarity.		*/
{
	int i, TotalX = 0, TotalLanguage = 0, Border;				/* TotalX saves Frequency of language x, TotalLanguage saves frequency of other languages, Border represents which size is smaller.	*/
	double Frequency = 0.0, Result = 0.0;						/* We assign to frequency and our result.					*/

	if ( *SizeCounter < *SizeCounterX )							/* We check which size is more.								*/
	{
		Border = *SizeCounterX;									/* If language x' size is bigger then it is our border.		*/
	}
	else														/* If language x' size is not bigger.						*/
	{
		Border = *SizeCounter;									/* Then we assign to border our language's size.			*/			
	}

	for (i = 0; *SizeCounter > i; ++i)							/* We are making loop for to sum total language's bigrams.	*/
	{
		TotalLanguage += FrequencyLanguage[i];					/* We sum frequencies into our variable.					*/
	}	

	for (i = 0; *SizeCounterX > i; ++i)							/* We are making loop for to sum total language x' bigrams.	*/
	{
		TotalX += FrequencyX[i];								/* We sum language x' frequencies into our variable.		*/
	}

	for (i = 0; Border > i ; ++i)								/* We make a loop to calculate the result.					*/
	{
		Frequency = ((double)FrequencyX[i]/TotalX - (double)FrequencyLanguage[i]/TotalLanguage);	/* We calculate the dissimilarity.			*/

		if ( Frequency < 0 )									/* We check our if our frequency is negative.				*/
		{
			Frequency *= -1;									/* If it is negative then we make it positive.				*/
		}

		Result += Frequency;									/* We sum it into our result.								*/
	}

	return Result;												/* We return our result.									*/
}

void dissimilarity(char *filename1, char *filename2)	/* We read and calculate the files and their frequencies.			*/
{
	int FrequencyX[MAX_SIZE], FrequencyLanguage[MAX_SIZE], counter[1], counterX[1],i;			/* We declare our frequency arrays and our counters.	*/
	char *LanguageX = NULL;																	/* We declare the array that we store the language x. 	*/

	ReadLanguage(&LanguageX,filename1);														/* We read language x into our character array.			*/

	int *FrequencyOfX = FrequencyOfLanguage(LanguageX,FrequencyX,counterX,filename1);		/* We calculate the frequency of language x.			*/

	int *FreqLanguage = FrequencyOfLanguage(LanguageX,FrequencyLanguage,counter,filename2);	/* We calculate the frequency of other language.		*/

	printf("%lf\n",TotalBigramCalculateLanguage(FrequencyX,FreqLanguage,counter,counterX));	/* We calculate the dissimilarity and print the result.	*/

	free(LanguageX);		/* We free our dynamic memory of language x array.		*/
}
