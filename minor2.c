/* Author: Jorge Moreno
   Instructor: Mark Thompson
   Date: 2/5/18
   Description: This program reads in a file with variables for a person's bank account. These variables are then stored in a dynamic array. Afterwords i read in a second file
   that contains either an account number of account name and a transaction amount either positive or negative. My program checks if the given number or name is in the array,
   if so then it adjusts the account balance. When the adjustments are complete i write the new variables over the old ones in the original file.*/

#include<stdio.h>
#include<stdlib.h>

typedef struct Account  //each account will contain 4 variables
{
  long accNum;    //holds the account number
  char accName[20];  //holds the account name
  char dollar;   //holds the account dollar sign
  float accBal;  //holds the account balance
}account; 

int main(int argc, char *argv[])  //arguments in main for parsing
{ 
  long tempNum;  //holds a temp number for reading in the file and finding the size
  char tempName[20];  //holds a temp name for reading in the file and finding the size
  char tempDollar;  //holds a temp dollar for reading in the file and finding the size
  float tempBal;  ////holds a temp number for reading in the file and finding the size
  int size =0;  //counter
  int size2=0;  //counter
  int count=0;  //counter
  int count2=0;  //counter
  int check;  //check counter
  float transNumT;  //holds the transaction file number
  int i;  //used for for loop
  int a;  //used for for loop
  char ch[20];  //make a char to check the first char in the transaction file
  char next;  //next line in the file
  int test=-1;  //test to check a value
  FILE *fp;  //first file pointer
  FILE *fp2;  //second file pointer
  FILE *fp3;  //another first file pointer
  if(argc != 3)  //if the user entered too few command arguments
  {
    printf("Command line should be in the format: \n");
    printf("usage: ./a.out <account file> <transact file>");
    return 0;
  }
  fp = fopen(argv[1], "r+");  //open the first file which will be in argv[1]
  if(fp == NULL)
  {
    printf("File not opened\n");
    exit(EXIT_FAILURE);
  }
  else
  {
    printf("File has been opened and is ready for use.\n");
  }
  while(!feof(fp))  //while not the end of the file read in temp values to find the lines in the file which will be the size for the array of structs
  {
    fscanf(fp,"%ld %s %c %f", &tempNum, tempName, &tempDollar, &tempBal); //read in each thing in the file line by line
  //  printf("\n%.8ld %s %c %.2f", tempNum, tempName, tempDollar, tempBal);
    count++;
  }
 // printf("\n");
  account *acc = malloc(count * sizeof(account));  //allocate memory dynamically using the counter
  fseek(fp,0,SEEK_SET);  //restart the pointer to the beginning

  while(!feof(fp))  //while not the end of the first file now we insert the information into my struct variables
  {
    fscanf(fp,"%ld %s %c %f", &acc[size].accNum, acc[size].accName, &acc[size].dollar, &acc[size].accBal);
 //   printf("\n%.8ld %s %c %.2f", acc[size].accNum, acc[size].accName, acc[size].dollar, acc[size].accBal);
    size++;
  }
  //printf("\nThe size is: %d\n",count);
  printf("Printing out array\n"); //Print the array of initial values
  for(i=0;i<count;i++)
  {
    printf("Account #%d : %.8ld %s %c %.2f\n", i+1,acc[i].accNum,acc[i].accName,acc[i].dollar,acc[i].accBal);
    printf("\n");
  }
 printf("Now opening the second file and adjusting balances.\n"); 
  fp2 =fopen(argv[2],"r+"); //open the second file
  if(fp2 == NULL)
  {
    printf("File 2 not opened.\n");
    exit(EXIT_FAILURE);
  }
  else
  {
    printf("File 2 has been opened and is ready for use.\n");
  }
 
  while(!feof(fp2)) //while not the end of file2
  {
    int exist; //will hold to see if the string encountered matched to an account name or number
    fscanf(fp2,"%s %f",ch,&transNumT);  //read in the first thing in file as a string then the float number
    int at=atoi(ch);  //at holds the string converted into an int
     for(check=0;check<count;check++)
     {
      if(strcmp(acc[check].accName,ch) == 0) //if the two account names are the same
      {
        acc[check].accBal += transNumT;  //adjust the users balance
        exist++;
      }
      else if(acc[check].accNum == at)  //if the account number is the same as the string converted to an int
      {
        acc[check].accBal += transNumT;  //adjust the users balance
        exist++;
      }
     }
  }
  printf("\n");
  printf("\nPrinting out updated first array\n");
  for(i=0;i<count;i++)
  {
    printf("Account #%d : %.8ld %s %c%.2f\n", i+1,acc[i].accNum,acc[i].accName,acc[i].dollar,acc[i].accBal);
    printf("\n");
  }
  printf("Now overwriting original file with updated balances.\n");
  
  fp3 = fopen(argv[1], "w"); //open the same first file with a new pointer
  if(fp3 == NULL)
  {
    printf("File not opened\n");
    exit(EXIT_FAILURE);
  }
  else
  {
    printf("File has been opened and is ready for writing.\n");
  }
  fseek(fp3,0,SEEK_CUR);  //rest the file pointer to the beginning
  for(i=0;i<count;i++)
  {
    if(acc[i].accNum != 00000000)  //semi fixed an issue where it would print to the file extra accounts but still prints 1 extra
    {
    fprintf(fp3,"%.8ld %s %c %.2f\n",acc[i].accNum,acc[i].accName,acc[i].dollar,acc[i].accBal);
    }
   
  }
  printf("Finished overwriting.\n");
  free(acc); //free the memory
  fclose(fp); //close the files
  fclose(fp2);
  return 0;
}
