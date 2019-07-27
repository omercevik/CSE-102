/*
											CSE 102 Homework Assignment 6

												OMER_CEVIK_161044004


					# 				In that programme, we read a text file.					 #
					# 				And we check the letters recursively.					 #
					#			Then we print them into the screen with minuses. 			 # 


																															*/
#include <stdio.h>				/* We use printf, return, if, else...	*/
#include <string.h>				/* We use strlen function.				*/

#define MAX 100					/* Our files maximum size.				*/

void Recursion(char *String, int length, int counter);	/* We print recursively our letters.		*/
void RecursionMinus(int minus);							/* We print minus signature.				*/
void ReadFunction(char *ReadArray);						/* We read our file into character array.	*/

int main()						/* We call our functions.	*/
{
	char Input[MAX];			/* Our character array.		*/
	int count = 0;				/* It counts minus sign.	*/
		
	ReadFunction(Input);		/* We call to read file.	*/
	
	Recursion(Input,strlen(Input),count);	/* We call to make recursively print letters.	*/

	return 0;	/* Ending our story truely.	*/
}

void Recursion(char *String, int length, int counter)		/* It checks letters and parentheses,then prints the letters.		*/
{
	if( length == 0 )		/* Our base case.		*/
	{
		return;				/* We finish the loop.	*/
	}
	else					/* We check we are not at the last element of array.	*/	

		if( String[0] == ',' )							/* We check if we have a comma.							*/
		{
			Recursion(&String[1],length-1,counter);		/* Then we keep going in our array.						*/
		}
		else if( String[0] == '(' )						/* We check if we have an open parenthese.				*/ 
		{
			Recursion(&String[1],length-1,counter+1);	/* Then we count it and keep going in array.			*/
		}
		else if( String[0] == ')' )						/* We check if we have an close paranthese.				*/
		{
			Recursion(&String[1],length-1,counter-1);	/* Then we decrease count and keep going in array.		*/
		}
		if( (String[0] >= 'A' && String[0] <= 'Z') || (String[0] >= 'a' && String[0] <= 'z') )		/* We check if we have a letter.		*/
		{
			RecursionMinus(counter);					/* Then we call our minus recursion function and we print minus signs.		*/
			printf("%c\n",String[0]);					/* Then we print our letter.												*/
			Recursion(&String[1],length-1,counter);		/* Then we keep going in our array.											*/
		}  
}

void RecursionMinus(int minus)			/* It prints the minus recursively.			*/
{
	if ( minus == 0 )					/* Our base case.							*/
	{
		return;							/* If our minus is zero then we return it.	*/
	}
	else								/* If our minus is not zero then we go.		*/

		printf("-");					/* We print our minus sign.					*/

		RecursionMinus(minus-1);		/* We decrease our minus and keep going.	*/
}

void ReadFunction(char *ReadArray)		/* It reads a text file into our character array.		*/ 
{
	FILE *fp = fopen("input.txt","r");	/* We open to read our text file.						*/
	
	fgets(ReadArray,MAX,fp);			/* We get the file as a string into our array.			*/

	fclose(fp);							/* We close our file.									*/
}
