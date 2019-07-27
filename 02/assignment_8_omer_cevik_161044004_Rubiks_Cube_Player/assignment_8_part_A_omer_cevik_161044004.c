/*
											CSE 102 Homework Assignment 8
													  PART   A
												OMER_CEVIK_161044004


					# 				In that programme, we read a text file.						 #
					# 				In that text file we have commands to move.				     #
					#				   We create a cube like Rubik's cube. 				     	 # 
					#			      We rotate on that cube with commands.				    	 #


																															*/
#include <stdio.h>			/*  We use fprintf, sscanf, for, if, else etc.   	*/
#include <stdlib.h>			/*  We use dynamic allocation functions.			*/ 
#include <string.h>			/*  We use strcmp, strncmp.							*/

void InitializeFaces(int **face0, int **face1, int **face2, int **face3, int **face4, int **face5, int *n);			/*  We initialize the faces of cube.		*/
void AllocateF(int ***F, int *n);		/*  We allocate to our faces.			*/
void FreeAll(int **face0, int **face1, int **face2, int **face3, int **face4, int **face5, int *n, char **Command, int CommandColumn);	/*  We free what we allocated.		*/
void printResult(int **F0, int **F1, int **F2, int **F3, int **F4, int **F5, int *n);			/*  We print the results into our text file.		*/ 
void RotateCube(char **Command, int **face0, int **face1, int **face2, int **face3, int **face4, int **face5, int *n, int CommandColumn);	/*  We make rotates.		*/
int ReadFunction(char ***Read, int *n);			/*  We read commands from text file.		*/

int main()		/*  We call our functions.	*/
{
	int i, j, *n, size;								/*  i and j are just counters. size is commands counts.		*/
	char **ReadArray = NULL;						/*  We initialize our character array to read.				*/
	int **F0 = NULL, **F1 = NULL, **F2 = NULL,		/*  We initialize our faces.								*/
	**F3 = NULL, **F4 = NULL, **F5 = NULL;

	size = ReadFunction(&ReadArray,n);				/*  We read our commands.								*/

	AllocateF(&F0,n);								/*  We allocate memmory for face 0.						*/
	AllocateF(&F1,n);								/*  We allocate memmory for face 1.						*/
	AllocateF(&F2,n);								/*  We allocate memmory for face 2.						*/
	AllocateF(&F3,n);								/*  We allocate memmory for face 3.						*/
	AllocateF(&F4,n);								/*  We allocate memmory for face 4.						*/
	AllocateF(&F5,n);								/*  We allocate memmory for face 5.						*/

	InitializeFaces(F0,F1,F2,F3,F4,F5,n);			/*  We initialize our faces.							*/

	RotateCube(ReadArray,F0,F1,F2,F3,F4,F5,n,size); /*  We makes rotates.									*/

	printResult(F0,F1,F2,F3,F4,F5,n);				/*  We print the results.								*/

	FreeAll(F0,F1,F2,F3,F4,F5,n,ReadArray,size);	/*  We free allocated memmories.						*/

	return 0;			/*  Ending our story truely.	*/
}

void RotateCube(char **Command, int **face0, int **face1, int **face2, int **face3, int **face4, int **face5, int *n, int CommandColumn)	/* We make moves on cube.		*/
{
	int i = 0, j = 0, k = *n, face = 0, row = 0;						/*	We initialize our counters and our face and row/column.		*/
	char ColumnOrRow[7], Way[6], rotate[7];						/*  We initialize our columns/row, which way and rotate.		*/

	int *temp = malloc((*n)*sizeof(int));						/*  We initialize our temp array.								*/ 

	for (i = 0; i < CommandColumn; ++i)							/* 	We start a loop in the commands.							*/
	{
		if ( strncmp(Command[i],"rotate",6) == 0 )				/*	We check if we have a rotate.								*/
		{
			sscanf(Command[i],"%s %d %s %d %s",rotate,&face,ColumnOrRow,&row,Way);	/*  If we have rotate then we save our commands into our arrays and variables.		*/

			if ( strcmp(ColumnOrRow,"row") == 0 )					/*	We check if we rotate on row.			*/
			{
				if ( face == 0 )								/*	We check if we rotate on face 0.		*/
				{
					if ( strcmp(Way,"right") == 0 )				/*  We check if we rotate to right.			*/ 
					{
						for (j = 0; j < *n; ++j)				/*  We start a loop to rotate.				*/
						{
							temp[j] = face0[row][j];			/*  We save our starting face.				*/
							face0[row][j] = face3[row][j];		/*	Then we move to other face.				*/
							face3[row][j] = face2[row][j];		/*	Then we move to other face.				*/
							face2[row][j] = face1[row][j];		/*	Then we move to other face.				*/
							face1[row][j] = temp[j];			/*  We move saved face.						*/
						}
					}
					else if ( strcmp(Way,"left") == 0 )			/*  We check if we rotate to left.			*/
					{
						for (j = 0; j < *n; ++j)				/*  We start a loop to rotate.				*/
						{
							temp[j] = face0[row][j];			/*  We save our starting face.				*/
							face0[row][j] = face1[row][j];		/*	Then we move to other face.				*/
							face1[row][j] = face2[row][j];		/*	Then we move to other face.				*/
							face2[row][j] = face3[row][j];		/*	Then we move to other face.				*/
							face3[row][j] = temp[j];			/*  We move saved face.						*/
						}	
					}
				}
				else if ( face == 1 )							/*	We check if we rotate on face 1.		*/
				{
					if ( strcmp(Way,"right") == 0 )				/*  We check if we rotate to right.			*/
					{
						for (j = 0; j < *n; ++j)				/*  We start a loop to rotate.				*/
						{
							temp[j] = face0[row][j];			/*  We save our starting face.				*/
							face0[row][j] = face3[row][j];		/*	Then we move to other face.				*/
							face3[row][j] = face2[row][j];		/*	Then we move to other face.				*/
							face2[row][j] = face1[row][j];		/*	Then we move to other face.				*/
							face1[row][j] = temp[j];			/*  We move saved face.						*/
						}
					}
					else if ( strcmp(Way,"left") == 0 )			/*  We check if we rotate to left.			*/
					{
						for (j = 0; j < *n; ++j)				/*  We start a loop to rotate.				*/
						{
							temp[j] = face0[row][j];			/*  We save our starting face.				*/
							face0[row][j] = face1[row][j];		/*	Then we move to other face.				*/
							face1[row][j] = face2[row][j];		/*	Then we move to other face.				*/
							face2[row][j] = face3[row][j];		/*	Then we move to other face.				*/
							face3[row][j] = temp[j];			/*  We move saved face.						*/
						}	
					}
				}
				else if ( face == 2 )							/*	We check if we rotate on face 2.		*/
				{
					if ( strcmp(Way,"right") == 0 )				/*  We check if we rotate to right.			*/
					{
						for (j = 0; j < *n; ++j)				/*  We start a loop to rotate.				*/
						{
							temp[j] = face0[row][j];			/*  We save our starting face.				*/
							face0[row][j] = face3[row][j];		/*	Then we move to other face.				*/
							face3[row][j] = face2[row][j];		/*	Then we move to other face.				*/
							face2[row][j] = face1[row][j];		/*	Then we move to other face.				*/
							face1[row][j] = temp[j];			/*  We move saved face.						*/
						}
					}
					else if ( strcmp(Way,"left") == 0 )			/*  We check if we rotate to left.			*/
					{
						for (j = 0; j < *n; ++j)				/*  We start a loop to rotate.				*/
						{
							temp[j] = face0[row][j];			/*  We save our starting face.				*/
							face0[row][j] = face1[row][j];		/*	Then we move to other face.				*/
							face1[row][j] = face2[row][j];		/*	Then we move to other face.				*/
							face2[row][j] = face3[row][j];		/*	Then we move to other face.				*/
							face3[row][j] = temp[j];			/*  We move saved face.						*/
						}	
					}
				}
				else if ( face == 3 )							/*	We check if we rotate on face 3.		*/
				{
					if ( strcmp(Way,"right") == 0 )				/*  We check if we rotate to right.			*/
					{
						for (j = 0; j < *n; ++j)				/*  We start a loop to rotate.				*/
						{
							temp[j] = face0[row][j];			/*  We save our starting face.				*/
							face0[row][j] = face3[row][j];		/*	Then we move to other face.				*/
							face3[row][j] = face2[row][j];		/*	Then we move to other face.				*/
							face2[row][j] = face1[row][j];		/*	Then we move to other face.				*/
							face1[row][j] = temp[j];			/*  We move saved face.						*/
						}
					}
					else if ( strcmp(Way,"left") == 0 )			/*  We check if we rotate to left.			*/
					{
						for (j = 0; j < *n; ++j)				/*  We start a loop to rotate.				*/
						{
							temp[j] = face0[row][j];			/*  We save our starting face.				*/
							face0[row][j] = face1[row][j];		/*	Then we move to other face.				*/
							face1[row][j] = face2[row][j];		/*	Then we move to other face.				*/
							face2[row][j] = face3[row][j];		/*	Then we move to other face.				*/
							face3[row][j] = temp[j];			/*  We move saved face.						*/
						}	
					}
				}
				else if ( face == 4 )							/*	We check if we rotate on face 4.		*/
				{
					if ( strcmp(Way,"right") == 0 )				/*  We check if we rotate to right.			*/
					{
						for (j = 0; j < *n; ++j)				/*  We start a loop to rotate.				*/
						{
							temp[j] = face4[row][j];			/*  We save our starting face.				*/
							face4[row][j] = face3[row][j];		/*	Then we move to other face.				*/
							face3[row][j] = face5[row][j];		/*	Then we move to other face.				*/
							face5[row][j] = face1[row][j];		/*	Then we move to other face.				*/
							face1[row][j] = temp[j];			/*  We move saved face.						*/
						}
					}
					else if ( strcmp(Way,"left") == 0 )			/*  We check if we rotate to left.			*/
					{
						for (j = 0; j < *n; ++j)				/*  We start a loop to rotate.				*/
						{
							temp[j] = face4[row][j];			/*  We save our starting face.				*/
							face4[row][j] = face1[row][j];		/*	Then we move to other face.				*/
							face1[row][j] = face5[row][j];		/*	Then we move to other face.				*/
							face5[row][j] = face3[row][j];		/*	Then we move to other face.				*/
							face3[row][j] = temp[j];			/*  We move saved face.						*/
						}	
					}
				}
				else if ( face == 5 )							/*	We check if we rotate on face 5.		*/
				{
					if ( strcmp(Way,"right") == 0 )				/*  We check if we rotate to right.			*/
					{
						for (j = 0; j < *n; ++j)				/*  We start a loop to rotate.				*/
						{
							temp[j] = face5[row][j];			/*  We save our starting face.				*/
							face5[row][j] = face3[row][j];		/*	Then we move to other face.				*/
							face3[row][j] = face4[row][j];		/*	Then we move to other face.				*/
							face4[row][j] = face1[row][j];		/*	Then we move to other face.				*/
							face1[row][j] = temp[j];			/*  We move saved face.						*/
						}
					}
					else if ( strcmp(Way,"left") == 0 )			/*  We check if we rotate to left.			*/
					{
						for (j = 0; j < *n; ++j)				/*  We start a loop to rotate.				*/
						{
							temp[j] = face5[row][j];			/*  We save our starting face.				*/
							face5[row][j] = face1[row][j];		/*	Then we move to other face.				*/
							face1[row][j] = face4[row][j];		/*	Then we move to other face.				*/
							face4[row][j] = face3[row][j];		/*	Then we move to other face.				*/
							face3[row][j] = temp[j];			/*  We move saved face.						*/
						}	
					}
				}
			}
			else if ( strcmp(ColumnOrRow,"column") == 0 )			/*	We check if we rotate on column.			*/
			{
				if ( face == 0 )								/*	We check if we rotate on face 0.		*/
				{
					if ( strcmp(Way,"up") == 0 )				/*  We check if we rotate to up.			*/
					{
						for (j = 0; j < *n; ++j)				/*  We start a loop to rotate.				*/
						{
							temp[j] = face0[j][row];			/*  We save our starting face.				*/
							face0[j][row] = face5[j][row];		/*	Then we move to other face.				*/
							face5[j][row] = face2[k-1][*n-row-1];		/*	Then we move to other face.				*/
							face2[k-1][*n-row-1] = face4[j][row];		/*	Then we move to other face.				*/
							face4[j][row] = temp[j];			/*  We move saved face.						*/
							--k;
						}
					}
					else if ( strcmp(Way,"down") == 0 )			/*  We check if we rotate to down.			*/
					{
						for (j = 0; j < *n; ++j)				/*  We start a loop to rotate.				*/
						{
							temp[j] = face0[j][row];			/*  We save our starting face.				*/
							face0[j][row] = face4[j][row];		/*	Then we move to other face.				*/
							face4[j][row] = face2[k-1][*n-row-1];		/*	Then we move to other face.				*/
							face2[k-1][*n-row-1] = face5[j][row];		/*	Then we move to other face.				*/
							face5[j][row] = temp[j];			/*  We move saved face.						*/
							--k;
						}	
					}
				}
				else if ( face == 1 )							/*	We check if we rotate on face 1.		*/
				{
					if ( strcmp(Way,"up") == 0 )				/*  We check if we rotate to up.			*/
					{
						for (j = 0; j < *n; ++j)				/*  We start a loop to rotate.				*/
						{
							temp[j] = face1[j][row];			/*  We save our starting face.				*/
							face1[j][row] = face5[j][row];		/*	Then we move to other face.				*/
							face5[j][row] = face3[k-1][*n-row-1];		/*	Then we move to other face.				*/
							face3[k-1][*n-row-1] = face4[j][row];		/*	Then we move to other face.				*/
							face4[j][row] = temp[j];			/*  We move saved face.						*/
							--k;
						}
					}
					else if ( strcmp(Way,"down") == 0 )			/*  We check if we rotate to down.			*/
					{
						for (j = 0; j < *n; ++j)				/*  We start a loop to rotate.				*/
						{
							temp[j] = face1[j][row];			/*  We save our starting face.				*/
							face1[j][row] = face4[j][row];		/*	Then we move to other face.				*/
							face4[j][row] = face3[k-1][*n-row-1];		/*	Then we move to other face.				*/
							face3[k-1][*n-row-1] = face5[j][row];		/*	Then we move to other face.				*/
							face5[j][row] = temp[j];			/*  We move saved face.						*/
							--k;
						}	
					}
				}
				else if ( face == 2 )							/*	We check if we rotate on face 2.		*/
				{
					if ( strcmp(Way,"up") == 0 )				/*  We check if we rotate to up.			*/
					{
						for (j = 0; j < *n; ++j)				/*  We start a loop to rotate.				*/
						{
							temp[j] = face2[j][row];			/*  We save our starting face.				*/
							face2[j][row] = face5[j][row];		/*	Then we move to other face.				*/
							face5[j][row] = face0[k-1][*n-row-1];		/*	Then we move to other face.				*/
							face0[k-1][*n-row-1] = face4[j][row];		/*	Then we move to other face.				*/
							face4[j][row] = temp[j];			/*  We move saved face.						*/
							--k;
						}
					}
					else if ( strcmp(Way,"down") == 0 )			/*  We check if we rotate to down.			*/
					{
						for (j = 0; j < *n; ++j)				/*  We start a loop to rotate.				*/
						{
							temp[j] = face2[j][row];			/*  We save our starting face.				*/
							face2[j][row] = face4[j][row];		/*	Then we move to other face.				*/
							face4[j][row] = face0[k-1][*n-row-1];		/*	Then we move to other face.				*/
							face0[k-1][*n-row-1] = face5[j][row];		/*	Then we move to other face.				*/
							face5[j][row] = temp[j];			/*  We move saved face.						*/
							--k;
						}	
					}
				}
				else if ( face == 3 )							/*	We check if we rotate on face 3.		*/
				{
					if ( strcmp(Way,"up") == 0 )				/*  We check if we rotate to up.			*/
					{
						for (j = 0; j < *n; ++j)				/*  We start a loop to rotate.				*/
						{
							temp[j] = face3[j][row];			/*  We save our starting face.				*/
							face3[j][row] = face5[j][row];		/*	Then we move to other face.				*/
							face5[j][row] = face1[k-j-1][*n-row-1];		/*	Then we move to other face.				*/
							face1[k-j-1][*n-row-1] = face4[j][row];		/*	Then we move to other face.				*/
							face4[j][row] = temp[j];			/*  We move saved face.						*/
							--k;
						}
					}
					else if ( strcmp(Way,"down") == 0 )			/*  We check if we rotate to down.			*/
					{
						for (j = 0; j < *n; ++j)				/*  We start a loop to rotate.				*/
						{
							temp[j] = face3[j][row];			/*  We save our starting face.				*/
							face3[j][row] = face4[j][row];		/*	Then we move to other face.				*/
							face4[j][row] = face1[k-1][*n-row-1];		/*	Then we move to other face.				*/
							face1[k-1][*n-row-1] = face5[j][row];		/*	Then we move to other face.				*/
							face5[j][row] = temp[j];			/*  We move saved face.						*/
							--k;
						}	
					}
				}
				else if ( face == 4 )							/*	We check if we rotate on face 4.		*/
				{
					if ( strcmp(Way,"up") == 0 )				/*  We check if we rotate to up.			*/
					{
						for (j = 0; j < *n; ++j)				/*  We start a loop to rotate.				*/
						{
							temp[j] = face4[j][row];			/*  We save our starting face.				*/
							face4[j][row] = face0[j][row];		/*	Then we move to other face.				*/
							face0[j][row] = face5[k-1][*n-row-1];		/*	Then we move to other face.				*/
							face5[k-1][*n-row-1] = face2[j][row];		/*	Then we move to other face.				*/
							face2[j][row] = temp[j];			/*  We move saved face.						*/
							--k;
						}
					}
					else if ( strcmp(Way,"down") == 0 )			/*  We check if we rotate to down.			*/
					{
						for (j = 0; j < *n; ++j)				/*  We start a loop to rotate.				*/
						{
							temp[j] = face4[j][row];			/*  We save our starting face.				*/
							face4[j][row] = face2[j][row];		/*	Then we move to other face.				*/
							face2[j][row] = face5[k-1][*n-row-1];		/*	Then we move to other face.				*/
							face5[k-1][*n-row-1] = face0[j][row];		/*	Then we move to other face.				*/
							face0[j][row] = temp[j];			/*  We move saved face.						*/
							--k;
						}	
					}
				}
				else if ( face == 5 )							/*	We check if we rotate on face 5.		*/
				{
					if ( strcmp(Way,"up") == 0 )				/*  We check if we rotate to up.			*/
					{
						for (j = 0; j < *n; ++j)				/*  We start a loop to rotate.				*/
						{
							temp[j] = face5[j][row];			/*  We save our starting face.				*/
							face5[j][row] = face2[j][row];		/*	Then we move to other face.				*/
							face2[j][row] = face4[k-1][*n-row-1];		/*	Then we move to other face.				*/
							face4[k-1][*n-row-1] = face0[j][row];		/*	Then we move to other face.				*/
							face0[j][row] = temp[j];			/*  We move saved face.						*/
							--k;
						}
					}
					else if ( strcmp(Way,"down") == 0 )			/*  We check if we rotate to down.			*/
					{
						for (j = 0; j < *n; ++j)				/*  We start a loop to rotate.				*/
						{
							temp[j] = face5[j][row];			/*  We save our starting face.				*/
							face5[j][row] = face0[j][row];		/*	Then we move to other face.				*/
							face0[j][row] = face4[k-1][*n-row-1];		/*	Then we move to other face.				*/
							face4[k-1][*n-row-1] = face2[j][row];		/*	Then we move to other face.				*/
							face2[j][row] = temp[j];			/*  We move saved face.						*/
							--k;								
						}	
					}
				}
				k = *n;
			}
		}
	}

	free(temp);				/* We free our temp array.			*/
}

void FreeAll(int **F0, int **F1, int **F2, int **F3, int **F4, int **F5, int *n, char **Command, int CommandColumn)		/*  We free that whatever we allocated dynamically.	*/	
{
	int i;			/*  It is just a counter.	*/

	for (i = 0; i < CommandColumn; ++i)		/*  We start a loop to free read array.		*/
	{
		free(Command[i]);					/*  We free char* of read array.			*/
	}
	free(Command);							/*  We free char** of read array.			*/

	for (i = 0; i < *n; ++i)				/*  We start a loop to free faces.			*/
	{
		free(F0[i]);						/*  We free int* of face 0.					*/
		free(F1[i]);						/*  We free int* of face 1.					*/
		free(F2[i]);						/*  We free int* of face 2.					*/
		free(F3[i]);						/*  We free int* of face 3.					*/
		free(F4[i]);						/*  We free int* of face 4.					*/
		free(F5[i]);						/*  We free int* of face 5.					*/
	}
	free(F0);						/*  We free int** of face 0.					*/
	free(F1);						/*  We free int** of face 1.					*/
	free(F2);						/*  We free int** of face 2.					*/
	free(F3);						/*  We free int** of face 3.					*/
	free(F4);						/*  We free int** of face 4.					*/
	free(F5);						/*  We free int** of face 5.					*/
}

int ReadFunction(char ***Read, int *n)			/*  We read commands text file into the character array.		*/
{
	int i = 0, j = 0;						/*  They are just counters.				*/
	char c;									/*  We use it just to read.				*/

	FILE *fp = fopen("commands.txt","r");	/*  We open our text file to read.		*/

	fscanf(fp,"%d",n);						/*  We read our size.					*/

	fseek(fp,2,SEEK_CUR);					/*  We rotate our file pointer to read characters.	*/

	while( fscanf(fp,"%c",&c) != EOF )		/*  We start a loop to read all till end of line.	*/
	{	
		*Read = (char**)realloc(*Read,sizeof(char*)*(j+1));				/*  We allocate char** dynamically.		*/

		(*Read)[j] = (char*)realloc((*Read)[j],sizeof(char)*(i+1));		/*  We allocate char* dynamically.		*/

		if ( c == '\n' )				/*  We check if we have a new line.					*/ 
		{	
			(*Read)[j][i] = '\0';		/*  If we have a new line then we make a string.	*/
			++j;						/*  We start a new array.							*/
			i = 0;						/*  We re-initialize our counter.					*/

			continue;					/*  We keep reading.								*/
		}

		(*Read)[j][i] = c;				/*  We assign that readed characters to array.		*/
		++i;							/*  We count characters.							*/
	}

	(*Read)[j] = (char*)realloc((*Read)[j],sizeof(char)*(i+1));		/*  We allocate for to last character of string.		*/

	(*Read)[j][i] = '\0';			/*  We assign null character to finish our string.		*/

	fclose(fp);						/*  We close our file.				*/

	return j+1;				/*  We return our counter of commands.		*/
}

void AllocateF(int*** F, int *n)			/*  We allocate dynamically to faces.		*/
{
	int i = 0;		/*  It's just a counter.		*/

	*F = malloc((*n)*sizeof(int*));				/*  We allocate to our int** array.			*/

	for (i = 0; i < *n; ++i)					/*  We start a loop to allocate int*.		*/
	{
		(*F)[i] = malloc((*n)*sizeof(int));		/*  We allocate to our int* array.			*/
	}
}

void InitializeFaces(int **face0, int **face1, int **face2, int **face3, int **face4, int **face5, int *n)		/*  We initialize our faces.		*/
{
	int i = 0, j = 0;				/* 	They are just counters.				*/ 

	for (i = 0; i < *n; ++i)		/*  We start a loop to int** array.		*/
	{	
		for (j = 0; j < *n; ++j)	/*  We start a loop to int* array.		*/
		{
			face0[i][j] = 0;		/*  We initialize our face 0 with 0.	*/
			face1[i][j] = 1;		/*  We initialize our face 1 with 1.	*/
			face2[i][j] = 2;		/*  We initialize our face 2 with 2.	*/
			face3[i][j] = 3;		/*  We initialize our face 3 with 3.	*/
			face4[i][j] = 4;		/*  We initialize our face 4 with 4.	*/
			face5[i][j] = 5;		/*  We initialize our face 5 with 5.	*/
		}
	}
}

void printResult(int **F0, int **F1, int **F2, int **F3, int **F4, int **F5, int *n)		/*  We print the results into the result text file.		*/
{
	int i, j;		/*  They are just counters.		*/

	FILE *fp = fopen("result.txt","w");			/*  We open our file to write.			*/

	for (i = 0; i < *n; ++i)					/*  We start a loop to int** array.		*/
	{	
		for (j = 0; j < *n; ++j)				/*  We start a loop to int* array.		*/
		{
			fprintf(fp,"%d ",F0[i][j]);			/*  We print the results of face 0.		*/
		}

		fprintf(fp,"\n");						/*  We print a new line.				*/
	}

	fprintf(fp,"\n");							/*  We print a new line.				*/

	for (i = 0; i < *n; ++i)					/*  We start a loop to int** array.		*/
	{	
		for (j = 0; j < *n; ++j)				/*  We start a loop to int* array.		*/
		{
			fprintf(fp,"%d ",F1[i][j]);			/*  We print the results of face 1.		*/
		}

		fprintf(fp,"\n");						/*  We print a new line.				*/
	}

	fprintf(fp,"\n");							/*  We print a new line.				*/

	for (i = 0; i < *n; ++i)					/*  We start a loop to int** array.		*/
	{	
		for (j = 0; j < *n; ++j)				/*  We start a loop to int* array.		*/
		{
			fprintf(fp,"%d ",F2[i][j]);			/*  We print the results of face 2.		*/
		}

		fprintf(fp,"\n");						/*  We print a new line.				*/
	}

	fprintf(fp,"\n");							/*  We print a new line.				*/

	for (i = 0; i < *n; ++i)					/*  We start a loop to int** array.		*/
	{	
		for (j = 0; j < *n; ++j)				/*  We start a loop to int* array.		*/
		{
			fprintf(fp,"%d ",F3[i][j]);			/*  We print the results of face 3.		*/
		}

		fprintf(fp,"\n");						/*  We print a new line.				*/
	}

	fprintf(fp,"\n");							/*  We print a new line.				*/

	for (i = 0; i < *n; ++i)					/*  We start a loop to int** array.		*/
	{	
		for (j = 0; j < *n; ++j)				/*  We start a loop to int* array.		*/
		{
			fprintf(fp,"%d ",F4[i][j]);			/*  We print the results of face 4.		*/
		}

		fprintf(fp,"\n");						/*  We print a new line.				*/
	}

	fprintf(fp,"\n");							/*  We print a new line.				*/

	for (i = 0; i < *n; ++i)					/*  We start a loop to int** array.		*/
	{	
		for (j = 0; j < *n; ++j)				/*  We start a loop to int* array.		*/
		{
			fprintf(fp,"%d ",F5[i][j]);			/*  We print the results of face 5.		*/
		}

		fprintf(fp,"\n");						/*  We print a new line.				*/
	}

	fclose(fp);				/*	We close our file.		*/
}