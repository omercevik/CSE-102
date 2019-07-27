/*
											CSE 102 Homework Assignment 2 

												OMER_CEVIK_161044004

					# 	We are trying to read from an input text file and write to an output text file.	 #
					# 	And we make some rules while writing it to output file. That's what we did.  	 # 

																														*/
#include <stdio.h>	/* We use FILE pointers, if, else, for and while loops etc. */
#include <stdlib.h>	/* We use calloc.  */

#define MAX_SIZE 1000	/* That's our maximum size of variables.  */
#define STOP_VALUE -99.9	/* That's our lines' stopping points.   */

void ReadAndWriteToFileFunction(char *filenameRead, char *filenameWrite);	/* We make read, write and average calculating functions in here.  */
void InitializeSumArray(double *ArrayOfSum);								/* We just initialize the SumArray. */
void InsertionSort(double *ArrayOfSum, int *NewIndexedSum);										/* We sort the averages.   */
void SwapLines(double *SummedArray, double CoppiedArray[][MAX_SIZE], char *filenameLast, int *NewIndexedSum);	/* We are sorting the lines.  */

int main(int argc, char const *argv[])	/* We call our functions in here.  */
{
	ReadAndWriteToFileFunction("input.txt","output.txt");	/* We call our function with input and output text files.  */

	return 0;	/* Ending our story truely.	*/
}

void ReadAndWriteToFileFunction(char *filenameRead, char *filenameWrite)	/* Our reading and writing functions are here. */
{
	FILE *fpointerReader;	/* File pointer for to read.  */

	int NewIndexedSum[MAX_SIZE/3],CounterOfZeros = 0, index = 0, indexCopy = 0, line = 0, CounterOfNumber = 0;	/* Initialing zero counter, index of ReadArray, line number and how many number have a line. */

	
	double *ReadArray, *Sum, CopyArray[MAX_SIZE/3][MAX_SIZE];	/* Declaring ReadArray and Sum array.  */

	ReadArray = calloc(sizeof(double),MAX_SIZE);/* Getting place from memory for ReadArray. */
	Sum = calloc(sizeof(double),MAX_SIZE/3);	/* Getting place from memory for Sum Array. */

	InitializeSumArray(Sum);	/* Initialize the Sum array.  */

	if ( (fpointerReader = fopen(filenameRead,"r")) == NULL )	/* We are checking if couldn't open the files.  */
	{
		printf("Reader File can not open!\n");	/* If we couldn't open the files then we report it to user.  */
		return;			/*  Failed function report. */
	}
	else	/* If we are success about opening the file then we continue in our way.  */
		while( fscanf(fpointerReader,"%lf",&ReadArray[index]) != EOF )	/* We save all numbers at an array from file.  */
		{
			++index;		/* Counting in array.  */
		}

		ReadArray[index] = EOF; /* Stop point of array.  */
		index = 0;				/* Re-initializasion of read array's index.  */

		while( ReadArray[index] != EOF )	/* We check if it's not end of file.  */
		{
			CopyArray[line][indexCopy] = ReadArray[index]; /* We are copying our readed values in 2D array.  */
			Sum[line] += CopyArray[line][indexCopy];	/* We are getting sum of each lines' numbers.  */
			
			if ( (ReadArray[index] == 0.0) && (ReadArray[index+1] == 0.0) && (ReadArray[index+2] == 0.0) )	/* We are checking out if we catch three zeros.  */
			{	
				CopyArray[line][indexCopy] = STOP_VALUE;	/* We are ending our line with a variable that we defined before.  */
				Sum[line] /= CounterOfNumber;				/* We are calculating our averages of each lines.   */

				CounterOfNumber = 0;						/* We are making a new line so we will count new line's numbers.  */
				index += 3;			/* We are jumping on 3 zeros.  */
				indexCopy = 0;		/* We are going on in our copy array. */
				++line;				/* A new line.  */
				continue;			/* We continue about reading on array. */
			}
			++CounterOfNumber;		/* We count a line's numbers.  */
			++index;			/* Counter index of ReadArray.  */
			++indexCopy;		/* Counter index of CopyArray.  */
		}
		Sum[line] /= CounterOfNumber;	/* Last line's average.  */
		CopyArray[line][indexCopy] = STOP_VALUE; /* We assign the last value of copy array.  */
		
		InsertionSort(Sum,NewIndexedSum);	/* We are making a sort for SumArray. It sorts the averages smaller to bigger.  */
		SwapLines(Sum,CopyArray,filenameWrite,NewIndexedSum);	/* We are sorting the lines in here.  */

	free(Sum);			/* We leave the memory of SumArray free.  */
	free(ReadArray);	/* We leave the memory of ReadArray free. */
	fclose(fpointerReader);	/* We are closing our reader file pointer. */
}

void InitializeSumArray(double *ArrayOfSum)	/* We just initialize the SumArray. Because we will make summing. It has junk values. We make it with zeros.  */
{
	int i;	/* It's just a counter. */

	for (i = 0; i < MAX_SIZE/3; ++i)	/* For loop to initialize SumArray. Size is MAX_SIZE/10. Because we won't have too much sum variables. */
	{
		ArrayOfSum[i] = 0.0;	/* Initialize with zeros. */
	}
}

void InsertionSort(double *ArrayOfSum, int *NewIndexedSum)	/* It sorts the averages in that function.  */
{
	double temp,tempIndex;	/* We save the variable with temp for to change their position.  */
	int i, j;		/* They are just counter. */

	for (i = 0; i < MAX_SIZE/3; ++i)	/* We are creating our index. We will change our lines.  */
	{
		NewIndexedSum[i] = i;	/* We initialize sorted array.  */
	}

	for (i = 1; ArrayOfSum[i] != 0.0; ++i)	/* We are starting to loop for to sort.  */
	{
		temp = ArrayOfSum[i];	/* We save the second variable of Sum array.  */
		tempIndex = NewIndexedSum[i];	/* We swap indexes.  */
		j = i - 1;				/* We are getting first variable's index of Sum array. */

		while( temp < ArrayOfSum[j] && j >= 0 )	/* We check which is bigger and is first variable's index is valuable.  */
		{	
			ArrayOfSum[j+1] = ArrayOfSum[j];	/* We change first and second variables positions.  */
			NewIndexedSum[j+1] = NewIndexedSum[j];	/* We swap indexes.  */
			--j;	/* We are decreasing the index of array.  */
		}

		ArrayOfSum[j+1] = temp;	/* We are completing the sorting story.  */
		NewIndexedSum[j+1] = tempIndex;	/* We swap indexes.  */
	}
}

void SwapLines(double SummedArray[MAX_SIZE/3], double CoppiedArray[][MAX_SIZE], char *filenameLast, int NewIndexedSum[MAX_SIZE/3])	/* That function swaps the each lines about which is smaller it is first line.  */
{
	FILE *fpointerWriter;	/* We create a new file pointer.  */
	int i, j;	/* In here i and j are just for to count.  */

	fpointerWriter = fopen(filenameLast,"w");	/* We are opening the file.  */

	if ( !fpointerWriter )	/* If we can not open the file we check out about it.  */
	{
		printf("We can not open the file.\n");	/* We inform the user that it didn't open the file.  */
		return;	/* It returns because we failed.  */
	}
	else	/* We continue in our way if we opened the file truely.  */

		for (i = 0; SummedArray[i] != 0.0; ++i)	/* We are getting a loop for to print into the file.  */
		{
			for (j = 0; CoppiedArray[NewIndexedSum[i]][j] != STOP_VALUE; ++j)	/* We are getting a loop for to check in swapped array.  */
			{
				fprintf(fpointerWriter,"%.4f ",CoppiedArray[NewIndexedSum[i]][j] );	/* We print swapped array into the file.  */
			}
			fprintf(fpointerWriter,"\n");			/* We make a new line in the file.  */
		}

	fclose(fpointerWriter);	/* We are closing our file.  */
}