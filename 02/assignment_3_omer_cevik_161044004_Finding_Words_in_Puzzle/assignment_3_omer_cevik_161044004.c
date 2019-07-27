/*
											CSE 102 Homework Assignment 3 

												OMER_CEVIK_161044004

					# 	We are trying to read from an input text file and print to terminal what we found.	 #
					# 	And we make searches vertically and horizontally. We print it that and locations.  	 # 

																															*/
#include <stdio.h>	/* We use printf, fscanf, if, else, for, while etc.   */
#include <string.h> /* We use strlen.  */

#define MAX_ROW_NUMBER 100	/* It's our maximum rows.  		*/
#define MAX_LENGTH_ROW 250	/* It's our maximum columns.  	*/

int SearchXantosHorizontal(char *name1, char CopyName1[][MAX_LENGTH_ROW]);	/* It searches Xantos horizontally.  */
int SearchXantosVertical(char *name1, char CopyName1[][MAX_LENGTH_ROW]);	/* It searches Xantos vertically. 	 */

int SearchPataraHorizontal(char *name2, char CopyName2[][MAX_LENGTH_ROW]);	/* It searches Patara horizontally.  */
int SearchPataraVertical(char *name2, char CopyName2[][MAX_LENGTH_ROW]);	/* It searches Patara vertically.  	 */

int SearchMyraHorizontal(char *name3, char CopyName3[][MAX_LENGTH_ROW]);	/* It searches Myra horizontally.  	*/
int SearchMyraVertical(char *name3, char CopyName3[][MAX_LENGTH_ROW]);		/* It searches Myra vertically.  	*/	

int SearchArycandaHorizontal(char *name4, char CopyName4[][MAX_LENGTH_ROW]);/* It searches Arycanda horizontally.   */
int SearchArycandaVertical(char *name4, char CopyName4[][MAX_LENGTH_ROW]);	/* It searches Arycanda vertically.		*/

int SearchPhaselisHorizontal(char *name5, char CopyName4[][MAX_LENGTH_ROW]);/* It searches Phaselis horizontally.   */
int SearchPhaselisVertical(char *name5, char CopyName4[][MAX_LENGTH_ROW]);	/* It searches Phaselis vertically.  	*/

int main(int argc, char const *argv[])	/* Our main function that we call our functions.  */
{
	FILE *fp;	/* Creating our file pointer.  */

	char nameXantos[] = "Xanthos";		/* Our 1.name initializing.  */
	char namePatara[] = "Patara";		/* Our 2.name initializing.  */
	char nameMyra[] = "Myra";			/* Our 3.name initializing.  */	
	char nameArycanda[] = "Arycanda";	/* Our 4.name initializing.  */
	char namePhaselis[] = "Phaselis";	/* Our 5.name initializing.  */

	char CopyName[MAX_ROW_NUMBER][MAX_LENGTH_ROW];	/* We read into that 2D character array.  */

	int index = 0, row = 0, LastIndex;	/* Our rows and columns in array.  */

	if ( (fp = fopen("input.txt","r")) == NULL )	/* We open the text file and check it we could open or not.  */
	{
		printf("File can not open.\n");	/* We inform the user about it.  */
		return -1;	/* Something wrong so we return -1, not 0.  */
	}
	else	/* So we opened the file.   */
		while( fscanf(fp,"%s",CopyName[row]) != EOF )	/* We read as string into our 2D array till end of line.  */
		{	
			++row;	/* We save it on rows.  */
		}

		LastIndex = strlen(CopyName[row-1]);	/* We are finding our last index about 2D array.  */
		CopyName[row-1][LastIndex] = '\n';		/* We are initializing last index with \n. */
		
		for (index = 0; index < LastIndex; ++index)	/* We initializing our array's boundary.  */
		{
			CopyName[row][index] = '\0';	/* We make boundary with NULL characters.  */
		}

	if ( SearchXantosHorizontal(nameXantos,CopyName) == 1 )		/* We check if it is horizontal. */
	{
	 	SearchXantosVertical(nameXantos,CopyName);		/* If it is not horizontally then it is vertically.  */
	} 
	
	if ( SearchPataraHorizontal(namePatara,CopyName) == 1 )		/* We check if it is horizontal. */
	{
		SearchPataraVertical(namePatara,CopyName);		/* If it is not horizontally then it is vertically.  */
	}
	
	if ( SearchMyraHorizontal(nameMyra,CopyName) == 1 )			/* We check if it is horizontal. */
	{
		SearchMyraVertical(nameMyra,CopyName);			/* If it is not horizontally then it is vertically.  */
	}

	if ( SearchArycandaHorizontal(nameArycanda,CopyName) == 1 ) /* We check if it is horizontal. */
	{
		SearchArycandaVertical(nameArycanda,CopyName);	/* If it is not horizontally then it is vertically.  */
	}

	if ( SearchPhaselisHorizontal(namePhaselis,CopyName) == 1 ) /* We check if it is horizontal. */
	{
		SearchPhaselisVertical(namePhaselis,CopyName);	/* If it is not horizontally then it is vertically.  */
	}

	fclose(fp);	/* Closing our file pointer.  */

	return 0;	/* Ending programme truely.  */
}

int SearchXantosHorizontal(char *name1, char CopyName1[][MAX_LENGTH_ROW])	/* It searchs horizontally. 	 */
{
	int i, LengthOfXantos = 0, j = 0, flag = 1;		/* Our counters and flag.  */

	for (i = 0; CopyName1[i][j] != '\n' && flag; ++i)		/* 	Loop for columns.  */
	{
		for (j = 0; CopyName1[i][j] != '\0' && flag; ++j)	/* Loop for rows.   */
		{
			if ( CopyName1[i][j] == name1[LengthOfXantos] )	/* We check if it gets the first same character.   */ 
			{
				++LengthOfXantos;		/* We check for other character of name.   */
				if ( CopyName1[i][j+1] != name1[LengthOfXantos] && name1[LengthOfXantos] != '\0')	/* We check if it is moving horizontally or not.  */
				{
					flag = 1;	/* If it is not horizontally then it is vertically.  */
					return flag;	/* Return to vertical function.  */
				}
				if ( LengthOfXantos == strlen(name1) )	/* We check if we are end of the name's characters.  */
				{
					printf("Xanthos (%d,%d) Horizontal\n", i+1, j-LengthOfXantos+2 ); /* We print location and our name.  */
					flag = 0;	/* We make flag zero because it means we don't have to check for vertical search we found it.  */
					return flag;	/* We are finishing our loop.  */
				}
			}
		}
	}
}

int SearchXantosVertical(char *name1, char CopyName1[][MAX_LENGTH_ROW])		/* It searches vertically.  	 */
{
	int i, LengthOfXantos = 0, j = 0, flag = 1;		/* Our counters and flag.  */

	for (i = 0; CopyName1[j][i] != '\n' && flag; ++i)			/* Loop for rows.   */
	{
		for (j = 0; CopyName1[j][i] != '\0' && flag; ++j)		/* 	Loop for columns.  */
		{
			if ( CopyName1[j][i] == name1[LengthOfXantos] )		/* We check if it gets the first same character.   */
			{
				++LengthOfXantos;		/* We check for other character of name.   */
				if ( LengthOfXantos == strlen(name1) )	/* We check if we are end of the name's characters.  */
				{
					printf("Xanthos (%d,%d) Vertical\n", j-LengthOfXantos, i+1 );	/* We print location and our name.  */
					flag = 0;	/* We make flag zero so we found it vertically.  */
					return flag;	/* We are finishing our loop.  */
				}
			}
		}
	}
}

int SearchPataraHorizontal(char *name2, char CopyName2[][MAX_LENGTH_ROW]) 	/* It searchs horizontally. 	 */
{
	int i, LengthOfPatara = 0, j = 0, flag = 1;		/* Our counters and flag.  */

	for (i = 0; CopyName2[i][j] != '\n' && flag; ++i)		/* 	Loop for columns.  */
	{
		for(j = 0; CopyName2[i][j] != '\0' && flag; ++j)	/* Loop for rows.   */
		{
			if ( CopyName2[i][j] == name2[LengthOfPatara] )	/* We check if it gets the first same character.   */ 
			{
				++LengthOfPatara;		/* We check for other character of name.   */
				if ( CopyName2[i][j+1] != name2[LengthOfPatara] && name2[LengthOfPatara] != '\0')	/* We check if it is moving horizontally or not.  */
				{
					flag = 1;	/* If it is not horizontally then it is vertically.  */
					return flag;	/* Return to vertical function.  */
				}
				if ( LengthOfPatara == strlen(name2) )	/* We check if we are end of the name's characters.  */
				{
					printf("Patara (%d,%d) Horizontal\n", i+1, j-LengthOfPatara+2 ); /* We print location and our name.  */
					flag = 0;	/* We make flag zero because it means we don't have to check for vertical search we found it.  */
					return flag;	/* We are finishing our loop.  */
				}
			}
		}
	}
}

int SearchPataraVertical(char *name2, char CopyName2[][MAX_LENGTH_ROW])		/* It searches vertically. 		 */
{
	int i, LengthOfPatara = 0, j = 0, flag = 1;		/* Our counters and flag.  */

	for (i = 0; CopyName2[j][i] != '\n' && flag; ++i)		/* Loop for rows.   */
	{
		for(j = 0; CopyName2[j][i] != '\0' && flag; ++j )	/* 	Loop for columns.  */
		{
			if ( CopyName2[j][i] == name2[LengthOfPatara] )	/* We check if it gets the first same character.   */
			{
				++LengthOfPatara;		/* We check for other character of name.   */
				if ( LengthOfPatara == strlen(name2) )	/* We check if we are end of the name's characters.  */
				{
					printf("Patara (%d,%d) Vertical\n", j-LengthOfPatara+2 , i+1 ); 	/* We print location and our name.  */
					flag = 0;	/* We make flag zero so we found it vertically.  */
					return flag;	/* We are finishing our loop.  */
				}
			}
		}
	}
}

int SearchMyraHorizontal(char *name3, char CopyName3[][MAX_LENGTH_ROW])		/* It searchs horizontally.  	 */
{
	int i, LengthOfMyra = 0, j = 0, flag = 1;	/* Our counters and flag.  */

	for (i = 0; CopyName3[i][j] != '\n' && flag; ++i)		/* 	Loop for columns.  */	
	{
		for (j = 0; CopyName3[i][j] != '\0' && flag; ++j)	/* Loop for rows.   */
		{
			if ( CopyName3[i][j] == name3[LengthOfMyra] )	/* We check if it gets the first same character.   */
			{
				++LengthOfMyra;			/* We check for other character of name.   */
				if ( CopyName3[i][j+1] != name3[LengthOfMyra] && name3[LengthOfMyra] != '\0')	/* We check if it is moving horizontally or not.  */
				{
					flag = 1;	/* If it is not horizontally then it is vertically.  */
					return flag;	/* Return to vertical function.  */
				}
				if ( LengthOfMyra == strlen(name3) )	/* We check if we are end of the name's characters.  */
				{
					printf("Myra (%d,%d) Horizontal\n", i+1, j-LengthOfMyra+2 );	/* We print location and our name.  */
					flag = 0;	/* We make flag zero because it means we don't have to check for vertical search we found it.  */
					return flag;	/* We are finishing our loop.  */
				}
			}
		}
	}
}

int SearchMyraVertical(char *name3, char CopyName3[][MAX_LENGTH_ROW]) 		/* It searches vertically.  	 */
{
	int i, LengthOfMyra = 0, j = 0, flag = 1;	/* Our counters and flag.  */

	for (i = 0; CopyName3[j][i] != '\n' && flag; ++i)		/* Loop for rows.   */
	{
		for (j = 0; CopyName3[j][i] != '\0' && flag; ++j)	/* 	Loop for columns.  */
		{
			if ( CopyName3[j][i] == name3[LengthOfMyra] )	/* We check if it gets the first same character.   */
			{
				++LengthOfMyra;			/* We check for other character of name.   */
				if ( LengthOfMyra == strlen(name3) )	/* We check if we are end of the name's characters.  */
				{
					printf("Myra (%d,%d) Vertical\n", j-LengthOfMyra+2 , i+1 );	/* We print location and our name.  */
					flag = 0;	/* We make flag zero so we found it vertically.  */
					return flag;	/* We are finishing our loop.  */
				}
			}
		}
	}	
}

int SearchArycandaHorizontal(char *name4, char CopyName4[][MAX_LENGTH_ROW])	/* It searchs horizontally. 	 */
{
	int i, LengthOfArycanda = 0, j = 0, flag = 1;	/* Our counters and flag.  */

	for (i = 0; CopyName4[i][j] != '\n' && flag; ++i)			/* 	Loop for columns.  */
	{
		for(j = 0; CopyName4[i][j] != '\0' && flag; ++j)		/* Loop for rows.   */
		{
			if ( CopyName4[i][j] == name4[LengthOfArycanda] )	/* We check if it gets the first same character.   */
			{
				++LengthOfArycanda;		/* We check for other character of name.   */
				if ( CopyName4[i][j+1] != name4[LengthOfArycanda] && name4[LengthOfArycanda] != '\0')	/* We check if it is moving horizontally or not.  */
				{
					flag = 1;	/* If it is not horizontally then it is vertically.  */
					return flag;	/* Return to vertical function.  */
				}
				if ( LengthOfArycanda == strlen(name4) )	/* We check if we are end of the name's characters.  */
				{
					printf("Arycanda (%d,%d) Horizontal\n", i+1, j-LengthOfArycanda+2 );	/* We print location and our name.  */
					flag = 0;	/* We make flag zero because it means we don't have to check for vertical search we found it.  */
					return flag;	/* We are finishing our loop.  */
				}
			}
		}
	}
}

int SearchArycandaVertical(char *name4, char CopyName4[][MAX_LENGTH_ROW]) 	/* It searches vertically. 		 */
{
	int i, LengthOfArycanda = 0, j = 0, flag = 1;	/* Our counters and flag.  */

	for (i = 0; CopyName4[j][i] != '\n' && flag; ++i)			/* Loop for rows.   */
	{
		for(j = 0; CopyName4[j][i] != '\0' && flag; ++j )		/* 	Loop for columns.  */
		{
			if ( CopyName4[j][i] == name4[LengthOfArycanda] )	/* We check if it gets the first same character.   */
			{
				++LengthOfArycanda;		/* We check for other character of name.   */
				if ( LengthOfArycanda == strlen(name4) )	/* We check if we are end of the name's characters.  */
				{
					printf("Arycanda (%d,%d) Vertical\n", j-LengthOfArycanda+2 , i+1 );	/* We print location and our name.  */
					flag = 0;	/* We make flag zero so we found it vertically.  */
					return flag;	/* We are finishing our loop.  */
				}
			}
		}
	}	
}

int SearchPhaselisHorizontal(char *name5, char CopyName5[][MAX_LENGTH_ROW])	/* It searchs horizontally.		 */
{
	int i, LengthOfPhaselis = 0, j = 0, flag = 1;	/* Our counters and flag.  */

	for (i = 0; CopyName5[i][j] != '\n' && flag; ++i)			/* 	Loop for columns.  */	
	{
		for (j = 0; CopyName5[i][j] != '\0' && flag; ++j)		/* Loop for rows.   */
		{
			if ( CopyName5[i][j] == name5[LengthOfPhaselis] )	/* We check if it gets the first same character.   */
			{
				++LengthOfPhaselis;		/* We check for other character of name.   */
				if ( CopyName5[i][j+1] != name5[LengthOfPhaselis] && name5[LengthOfPhaselis] != '\0' )	/* We check if it is moving horizontally or not.  */
				{
					flag = 1;	/* If it is not horizontally then it is vertically.  */
					break;		/* Return to vertical function. So break it.  */
				}
				if ( LengthOfPhaselis == strlen(name5) )	/* We check if we are end of the name's characters.  */
				{
					printf("Phaselis (%d,%d) Horizontal\n", i+1, j-LengthOfPhaselis+2 );	/* We print location and our name.  */
					flag = 0;	/* We make flag zero because it means we don't have to check for vertical search we found it.  */
					return flag;	/* We are finishing our loop.  */
				}
			}
		}
	}
	return flag;	/* Returning our flag.  */
}

int SearchPhaselisVertical(char *name5, char CopyName5[][MAX_LENGTH_ROW]) 	/* It searches vertically. 		 */
{
	int i, LengthOfPhaselis = 0, j = 0, flag = 1;	/* Our counters and flag.  */

	for (i = 0; CopyName5[j][i] != '\n' && flag; ++i)			/* Loop for rows.   */
	{
		for (j = 0; CopyName5[j][i] != '\0' && flag; ++j)		/* 	Loop for columns.  */
		{
			if ( CopyName5[j][i] == name5[LengthOfPhaselis] )	/* We check if it gets the first same character.   */
			{
				++LengthOfPhaselis;			/* We check for other character of name.   */
				if ( LengthOfPhaselis == strlen(name5) )	/* We check if we are end of the name's characters.  */
				{
					printf("Phaselis (%d,%d) Vertical\n", j-LengthOfPhaselis+2 , i+1 );	/* We print location and our name.  */
					flag = 0;	/* We make flag zero so we found it vertically.  */
					return flag;	/* We are finishing our loop. Returning. */
				}
			}
		}
	}
}