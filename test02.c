/*test*/
/* Author: Jorge Moreno
   Instructor: Mark Thompson
   Date: 2/5/18
   Description: */

#include<stdio.h>
#include<stdlib.h>


typedef struct Account
{
  long accNum;
  char accName[20];
  char dollar;
  char neg;
  float accBal;
  //float transNum;
  //char transName[20];
  
}account; 

int main(int argc, char *argv[])
{ 
  long tempNum;
  char tempName[20];
  char tempDollar;
  char tempNeg;
  float tempBal;
  int size =0;
  int size2=0;
  int count=0;
  int count2=0;
  int check;
  float transNumT;
  long transAcc;
  char transNameT[20];
  int i;
  int a;
  FILE *fp;
  FILE *fp2;
  FILE *fp3;
  if(argc != 3)
  {
    printf("Command line should be in the format: \n");
    printf("usage: ./a.out <account file> <transact file>");
    return 0;
  }
  fp = fopen(argv[1], "r+");
  if(fp == NULL)
  {
    printf("File not opened\n");
    exit(EXIT_FAILURE);
  }
  else
  {
    printf("File has been opened and is ready for use.\n");
  }
  fp2 =fopen(argv[2],"r+");
  if(fp2 == NULL)
  {
    printf("File 2 not opened.\n");
    exit(EXIT_FAILURE);
  }
  else
  {
    printf("File 2 has been opened and is ready for use.\n");
  }
 
  while(!feof(fp))
  {
    fscanf(fp,"%ld %s%c%c%f", &tempNum, tempName,&tempNeg, &tempDollar, &tempBal);
    printf("\n%ld %s%c%c%.2f", tempNum, tempName, tempNeg,tempDollar, tempBal);
    count++;
  }
  printf("\n");
  account *acc = malloc(count * sizeof(account));
  fseek(fp,0,SEEK_SET);

  while(!feof(fp))
  {
    fscanf(fp,"%ld %s%c%c%f", &acc[size].accNum, acc[size].accName, &acc[size].neg, &acc[size].dollar, &acc[size].accBal);
    printf("\n%ld %s%c%c%.2f", acc[size].accNum, acc[size].accName, acc[size].neg, acc[size].dollar, acc[size].accBal);
    size++;
  }
  printf("\nThe size is: %d\n",count);
  printf("Printing out array\n");
 // int i;
  for(i=0;i<count;i++)
  {
    printf("Account #%d : %ld %s%c%c%.2f\n", i+1,acc[i].accNum,acc[i].accName,acc[i].neg,acc[i].dollar,acc[i].accBal);
    printf("\n");
  }
 printf("Now opening the second file and adjusting balances.\n");
  
  char ch;
  char next;
  int test;
  fseek(fp2,0,SEEK_CUR);
  while(!feof(fp2))
  {
    fscanf(fp2,"%c",&ch);
    fseek(fp2,-1,SEEK_CUR);
    if(isalpha(ch))
    {
      test = 1;
    }
    else if(isdigit(ch))
    {
      test =0;
    }
    else
    {
      test=-1;
    }
    if(test == 1)
    {
      fscanf(fp2, "%s %f",transNameT,&transNumT);
      fscanf(fp2, "%c", &next);
     for(check=0;check<count;check++)
     {
      // printf("%s\n",acc[check].accName);
       //printf("%s\n",transNameT);
      if(strcmp(acc[check].accName,transNameT) == 0) //if the two account names are the same
      {
       // printf("The two strings are equal.\n");
        acc[check].accBal += transNumT;
       // printf("Worked #1\n");
      }
    /*  else
      {
        printf("The two string are NOT equal?!\n");
      } */
     }
    // break;
    }
    else if(test == 0)
    {
     fscanf(fp2,"%ld %f\n",&transAcc,&transNumT);
     for(check=0;check<count;check++)
     {
      if(acc[check].accNum == transAcc)
      {
       acc[check].accBal += transNumT;
      }
     }
    // break;
    }
    else
    {
      printf("The given account number/name does not match any account in our records.\n");
      exit(EXIT_FAILURE);
    }
   }
  printf("Printing out updated first array\n");
  for(i=0;i<count;i++)
  {
    printf("Account #%d : %ld %s %c%.2f\n", i+1,acc[i].accNum,acc[i].accName,acc[i].dollar,acc[i].accBal);
    printf("\n");
  }
  printf("Now overwriting original file with updated balances.\n");
  //fseek(fp,0,SEEK_CUR);
  fp3 = fopen(argv[1], "w");
  if(fp3 == NULL)
  {
    printf("File not opened\n");
    exit(EXIT_FAILURE);
  }
  else
  {
    printf("File has been opened and is ready for writing.\n");
  }
  for(i=0;i<count;i++)
  {
    if(acc[i].accBal < 0)
    {
      float positive;
      positive = (acc[i].accBal * -1);
      char neg = '-';
      fprintf(fp3,"%.8ld %s %c%c%.2f\n",acc[i].accNum,acc[i].accName,neg,acc[i].dollar,positive);
    }
    else
    {
    fprintf(fp3,"%.8ld %s %c %.2f\n",acc[i].accNum,acc[i].accName,acc[i].dollar,acc[i].accBal);
    }
  }
  printf("Finished overwriting.\n");
  free(acc);
  //free(trans);
  fclose(fp);
  fclose(fp2);
  return 0;
}

