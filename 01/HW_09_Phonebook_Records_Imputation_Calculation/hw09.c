/*
    CSE 102 C Programming
    OMER CEVIK
    161044004
    Homework 9
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NAMELEN 50
#define MAXRECORD 500

typedef struct record_s
{
    int id;
    char number[NAMELEN];
    struct record_s *next;
} Record;

typedef struct person_s
{
    int id;
    char name[NAMELEN];
    double expenditure;
    Record *numbers;
} Person;

typedef struct people_s
{
    Person data[MAXRECORD];
    int size;
} People;


/*
 Write People.data array to the filename.
*/
void writePeople(People people, char* filename)
{
    FILE* fp = fopen(filename,"wb");
    if (fp)
    {
        fwrite(&people, sizeof(People), 1, fp);
        fclose(fp);
    }
    else
    {
        printf("File can not be openned!\n");
    }
}

/*
 Reads Person structs from file and places them to People.data array.
 Note that the number of Person structs in the file is unkown.
*/
void readPeople(People *people, char* filename)
{
    FILE* fp = fopen(filename,"rb");
    if (fp)
    {
        int i = 0;
        while(!feof(fp))
        {
            fread(&(people->data[i++]), sizeof(Person), 1, fp);
        }
        fread(&(people->size),sizeof(int),1,fp);
        fclose(fp);
    }
    else
    {
        printf("File can not be openned!\n");
    }
}

/*
 Calculates the expected expenditure for the person with unknown expenditure.
 Persons' expenditure is -1 if their expenditure is unknown.
 You should calculate average bill amount for a phone number and multiply it by
 the phone number count for the person.
*/
void imputation(People *people)
{
    People temp = *people;
    double E = 0.0;
    int N = 0, K = 0;

    for (int i = 0; i < temp.size; ++i)
    {
        if (temp.data[i].expenditure != -1.0)
        {
            E += temp.data[i].expenditure;
            while(temp.data[i].numbers->next != NULL)
            {
                ++N;
                temp.data[i].numbers = temp.data[i].numbers->next;
            }
        }
        else
        {
            while(temp.data[i].numbers->next != NULL)
            {
                ++K;
                temp.data[i].numbers = temp.data[i].numbers->next;
            }
        }
    }

    for (int i = 0; i < temp.size; ++i)
    {
        if (temp.data[i].expenditure == -1.0)
        {
            people->data[i].expenditure = (E / N) * K;
        }
    }
}

/*
 Reads the input file and constructs People struct.
 Note that the number of phone numbers in file is unknown unlike your
 previous homework. You should keep phone numbers in the linked list
 (numbers field)
*/
void read(char* filename, People *people)
{
    FILE *fp1 = fopen(filename,"r");

    if( !fp1 )
    {
        printf("File can not be openned!\n");
    }
    else
    {
        while(!feof(fp1))
        {
            int readId = 0;
            double exp = 0.0;
            char readName1[NAMELEN], readName2[NAMELEN];
            fscanf(fp1,"%d %s %s %lf",&readId,readName1,readName2,&exp);
            strcat(readName1," ");
            char* fullName = strcat(readName1,readName2);

            people->data[people->size].id = readId;
            people->data[people->size].expenditure = exp;

            strcpy(people->data[people->size].name,fullName);
            Record* head = (Record*)malloc(sizeof(Record));

            people->data[people->size].numbers = head;

            char readPhoneNumbers[12];
            for (int i = 0; ; ++i)
            {
                fscanf(fp1,"%s",readPhoneNumbers);
                if (readPhoneNumbers[0] != '0' || feof(fp1))
                {
                    head = NULL;
                    if (!feof(fp1))
                        fseek(fp1,-(strlen(readPhoneNumbers)+1),SEEK_CUR);
                    break;
                }
                head->id = readId;
                strcpy(head->number,readPhoneNumbers);
                head->next = (Record*)malloc(sizeof(Record));
                head = head->next;
            }
            free(head);
            ++(people->size);
        }
        fclose(fp1);
    }
}

void print(People people)
{
    int i,found = 0;
    Record *rec;
    /* header */
    printf("%-5s %-30s %-20s %-20s\n", "ID","NAME","EXPENDITURE","NUMBER(s)");
    /* line */
    for (i = 0; i < 78; ++i)
        printf("-");
    printf("\n");

    for (i = 0; i < people.size; ++i) {
        found = 0;
        printf("%-5d %-30s %-20.4f", people.data[i].id, people.data[i].name, people.data[i].expenditure);
        rec = people.data[i].numbers;
        while(rec) {
            if(found)
                printf("%57s", "");
            else
                found = 1;
            printf("%-20s\n", rec->number);
            rec = rec->next;
        }
        printf("\n");
    }
}

int isPeopleEq(People ppl1, People ppl2)
{
    Record *rec1,*rec2;
    int i,found = 0;
    int p1size = 0, p2size = 0;
    if(ppl1.size != ppl2.size)
        return 0;
    for (i = 0; i < ppl1.size; ++i)
        if(strcmp(ppl1.data[i].name,ppl2.data[i].name))
            return 0;
        if(ppl1.data[i].id != ppl2.data[i].id)
            return 0;

        p1size = p2size = 0;
        rec1 = ppl1.data[i].numbers;
        while(rec1) {
            ++p1size;
            rec1 = rec1->next;
        }

        rec2 = ppl2.data[i].numbers;
        while(rec2) {
            ++p2size;
            rec2 = rec2->next;
        }

        if(p1size != p2size) {
            return 0;
        }

        rec1 = ppl1.data[i].numbers;
        while(rec1) {
            rec2 = ppl2.data[i].numbers;
            found = 0;
            while(!found && rec2) {
                if(strcmp(rec1->number,rec2->number) == 0) {
                    found = 1;
                    break;
                }
                rec2 = rec2->next;
            }
            if(!found) {
                return 0;
            }
            rec1 = rec1->next;
        }
    return 1;
}

void freeRecords(Record* record)
{
    if (record->next != NULL)
        freeRecords(record->next);
    free(record);
}

void freeAll(People people)
{
    for (int i = 0; i < people.size; ++i)
    {
        freeRecords(people.data[i].numbers);
    }
}

int main(int argc, char** argv)
{
    People people1,people2;
    people1.size = 0;
    read("input.txt",&people1);
    print(people1);
    writePeople(people1,"people.bin");
    readPeople(&people2,"people.bin");
    print(people2);
    printf("%s\n", isPeopleEq(people1,people2) ? "PEOPLE ARE SAME" : "PEOPLE ARE DIFFERENT!");
    printf("Making imputation\n");
    imputation(&people1);
    print(people1);
    freeAll(people1);
    return 0;
}
