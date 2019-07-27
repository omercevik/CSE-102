/*
											CSE 102 Homework Assignment 4 

												OMER_CEVIK_161044004


					# 			We read a polynomial text and we read values from a text.				 #
					# 				Then we try to calculate that values in the polynom. 				 #
					#			  And we write the results into the evalutions text file. 				 # 


																														*/
#include <stdio.h>	/* We use printf, fscanf, fprintf, fgets etc.  */
#include <math.h>	/* We use pow() function.   */

#define MAX_SIZE_VALUE 100			/* Maximum size of values' numbers. 	*/
#define MAX_SIZE_CHARACTER 1000		/* Maximum size of polynom characters.  */

int ReadValues(double *ValueArray, char *FileOfValue);					/* It reads values from the text file.  */
void ReadPolynom(char *PolyArray, char *FileOfPoly);					/* It reads polynom from the text file. */
double CalculateAndWrite(double *Value, char *Poly, int SizeOfValues);	/* We calculate the results and write into the text file.  */

int main()		/* It's our main function. We call our functions.   */
{
	FILE *fp;	/* For to write into the file we use it.   */

	fp = fopen("evaluations.txt","w");		/* We open the file to write.   */

	int i, SizeOfValues = 0;				/* Counter of values and we use i for to do a work with it.   */
	double ArrayValue[MAX_SIZE_VALUE];		/* We save values in that array.  							  */
	char ArrayPoly[MAX_SIZE_CHARACTER];		/* We save polynon in that array.    						  */

	SizeOfValues = ReadValues(ArrayValue,"values.txt");	/* We call function to read values and saving the count of values.   */

	ReadPolynom(ArrayPoly,"polynomial.txt");			/* We call function to read polynom.  */

	if ( !fp )	/* We check if we openned the file.  */
	{
		printf("Write File can not open.\n");	/* We couldn't open the file.  */
		return -1;	  /* We failed so we return.  */
	}
	else	/* We openned the file.   */
		
		for (i = 0; i < SizeOfValues; ++i)	/* Counting the values.	*/
		{
			fprintf(fp,"%.2f\n", CalculateAndWrite(&ArrayValue[i],ArrayPoly,SizeOfValues));	/* We calculate polynom for each value.  	  */
		}

	fclose(fp);	/* We close the file.       */
	return 0;	/* Ending our story truely.	*/
}

int ReadValues(double *ValueArray,char *FileOfValue)	/* It reads values from the text file.   */
{
	FILE *fp;	/* For to read a file we use it.   */

	int i;		/* Just a counter.   */

	fp = fopen(FileOfValue,"r");	/* We open the file to read.   */

	if ( !fp )	/* We check if we openned the file.  */
	{
		printf("Value file can not open.\n");	/* We couldn't open the file.  */
		return -1;	/* We failed so we return.  */
	}
	else	/* We openned the file.   */

		for (i = 0; fscanf(fp,"%lf",&ValueArray[i]) != EOF; ++i);	/* We read values into our array.   */

	fclose(fp);	/* We close our file.   		 */
	return i;	/* We return to size of values.  */
}

void ReadPolynom(char *PolyArray,char *FileOfPoly)		/* It reads polynom from the text file.  */
{
	FILE *fp;	/* For to read a file we use it.   */

	fp = fopen(FileOfPoly,"r");		/* We open the file to read.   */

	if ( !fp )	/* We check if we openned the file.  */
	{
		printf("Poly file can not open.\n");	/* We couldn't open the file.  */
		return;   /* We failed so we return.  */
	}
	else	/* We openned the file.   */

		fgets(PolyArray,MAX_SIZE_CHARACTER,fp);	/* We read polynom into polynom array. 	*/

	fclose(fp);	/* We close the file.  */
}


double CalculateAndWrite(double *Value, char *Poly, int SizeOfValues)
{
	int i = 0, j = 0, k = 0, counterFloat = 0, counterInt = 0;					/* They are our counters.   */
	double SumOfNumber[MAX_SIZE_CHARACTER], Result = 0.0, ResultSum = 0.0, SumFloat = 0.0;	/* We initialize our result, integers and doubles sum (ResultSum), double's float sum and sum of numbers.   */

	for (i = 0; Poly[i] != '\0'; ++i)	/* We start a loop for to calculate result in the polynom.  */
	{
		if ( Poly[i] <= '9' && Poly[i] >= '0' )	/* It checks if we get a number.  */
		{
			++counterInt;							/* We get a number so we count it.  	   */
			SumOfNumber[k] = (Poly[i]-'0');			/* We sum it into our sum array. 	       */
			++k;									/* We are going on about our sum array.    */
			continue;								/* We continue for to check other numbers. */
		}

		if ( Poly[i] == 'x' && Poly[i+1] == '\0' )	/* We control if we have only one variable. */
		{
			if ( Poly[i-1] == '-')					/* We control if it is negative or not.		*/
			{
				Result = -(*Value);					/* If it is negative we make it negative. 	*/
			}
			else									/* If it is positive we check it.			*/
				Result = *Value;					/* If it is positive we make it positive.	*/
		}

		if ( Poly[i] == '.' )		/* We check if we get a floating point number.   */
		{
			counterFloat = 0;		/* We start a counter.   						 */

			for (j = 1; Poly[i+j] != 'x'; ++j)	/* We make a loop to check if there are more numbers after floating point.   */
			{
				SumFloat += (Poly[i+j]-'0')/pow(10,j);	/* We sum floating points into sum variable.   						 */
				++counterFloat;							/* We count the floating points.									 */
			}

			i += j;										/* For to go on in polynom we need to re-initialize our pointer.	 */ 
		}

		if ( Poly[i] == '^' && (Poly[i-2] >= '0' && Poly[i-2] <= '9') )		/* We check if we got a power function and does it have a factor.  */
		{
			for (j = counterInt; 0 < j; --j)								/* We have a power function and we calculate that the factor. 	   */ 
			{
				ResultSum += SumOfNumber[j-1]*pow(10,counterInt-j);			/* We sum that factor into ResultSum.   						   */
			}
			
			ResultSum += SumFloat;											/* If we have floating point then we sum it too.				   */

			ResultSum *= pow(*Value,Poly[i+1]-'0');							/* We calculate the power function.								   */ 

			Result += ResultSum;											/* We sum it into our result.									   */

			counterInt = 0;													/* We zeroize the integer counter.								   */
			k = 0;															/* We zeroize our counter of sum array.							   */
		}

		if ( Poly[i] == '^' && (Poly[i-2] == '-' || Poly[i-2] == '+') )		/* We check if we got a power function without any factor variable.*/ 
		{
			ResultSum = pow(*Value,Poly[i+1]-'0');							/* We calculate the power function.								   */

			if ( Poly[i-2] == '+' )											/* We check if our calculated function is positive.				   */
			{
				Result += ResultSum;										/* We sum it into our result.									   */
			}
			else if ( Poly[i-2] == '-' )									/* We check if our calculated function is negative.				   */
			{
				Result -= ResultSum;										/* We take away from it into our result.						   */
			}

			ResultSum = 0;													/* We zeroize our ResultSum.									   */	
			counterInt = 0;													/* We zeroize our counter of integers.							   */
			k = 0;															/* We zeroize our counter of sum array.							   */
		}

		else if ( Poly[i] == '^' && Poly[i-1] == 'x' && ((Poly[i-2] < '0' || Poly[i-2] > '9'))) /* We check if there is no factor to variable. */
		{
			ResultSum = pow(*Value,Poly[i+1]-'0');							/* We calculate the power function.								   */

			Result += ResultSum;											/* We sum it into our result.									   */

			ResultSum = 0;													/* We zeroize our ResultSum.									   */	
			counterInt = 0;													/* We zeroize our counter of integers.							   */
			k = 0;															/* We zeroize our counter of sum array.							   */
		}

		if ( Poly[i] == '+' || Poly[i] == '-' || Poly[i+1] == '\0' )		/* We check if we are at end of the line and we calculate float.    */
		{	
			if ( Poly[i] == '+' && Poly[i-1] == 'x' )						/* We check if we have summing function and we have a factor to it. */
			{
				for (j = counterInt; 0 < j; --j)							/* We have a factor and we are making loop to calculate it.		    */
				{
					ResultSum += SumOfNumber[j-1]*pow(10,counterInt-counterFloat-j);	/* We sum it into our ResultSum variable.			    */
				}
				
				ResultSum += SumFloat;										/* If we have floating point variable then we sum it into ResultSum.*/
				Result += ResultSum*(*Value);								/* We sum the calculated variable into Result.						*/

			}
			else if ( Poly[i] == '-' && Poly[i-1] == 'x')					/* We check if we have a negative function and we have a factor.	*/
			{
				for (j = counterInt; 0 < j; --j)							/* We have a factor and we are making loop to calculate it.		    */
				{
					ResultSum += SumOfNumber[j-1]*pow(10,counterInt-counterFloat-j);	/* We sum it into our ResultSum variable.			    */

				}

				ResultSum -= SumFloat;										/* If we have floating point variable then we take away from.		*/

				Result -= ResultSum*(*Value);								/* We take away from the calculated variable.						*/
			}

			ResultSum = 0;													/* We re-initialize our ResultSum.									*/
			counterFloat = 0;												/* We re-initialize our float counter.								*/
			counterInt = 0;													/* We re-initialize our integer counter.							*/
			SumFloat = 0;													/* We re-initialize our float variable.								*/
			k = 0;															/* We re-initialize our sum array counter.							*/
		}
	}
	return Result;	/* We return the result.   */
}
