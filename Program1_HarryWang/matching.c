/******************************************************************************

Author: Harry Wang
Date: 2-19-23
Lab: lab01-extra_credit
Last modified: 2-20-23
Purpose: Suppose there are 5 Departments and 5 Programmers, each identified with an integer number between 1 and 5. You are to assign each Programmer to a Department according to the preferences given below. Each Department has a preference for the Programmers. For example, Department #1 preferences are as follows: 1 5 3 2 4, meaning that it would like to have programmer #1 as its first choice and programmer #4 as its last option. When there is a conflict, i.e., two Departments would like to have the same Programmer as their first choice, then consult with the Programmer in question, (that is, check his/her preferences) to determine which Department gets to hire him/her. When the program terminates, all Departments should have one programmer assigned to them.

How I implemented this problem:
p = programmer
d = department
starting from department 1
department 1 wants programmer 1
by ranking the index of the programmer's want for the departement
p1 index for d1 is 1 
p2 index for d1 is 2
p3 index for d1 is 3
p4 index for d1 is 3
p5 index for d1 is 2

it happends that p1 is the closets for d1 so now d1 is taken
for d2 inital want is p1 but p1 is taken so the next best is p3
p1 index for d2 is 2 (taken)
p2 index for d2 is 4
p3 index for d2 is 0
p4 index for d2 is 2
p5 index for d2 is 1

so d2 get p3 now we know p1 and p3 is taken
so for d3 first pick is p3 but now taken the next is p4

p1 index for d3 is 1 (taken)
p2 index for d3 is 2
p3 index for d3 is 4 (taken)
p4 index for d3 is 4
p5 index for d3 is 1
now the next closest is p5 
repeat untill all programmers are taken

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>

int main()
{
  //create a file pointer variable
  FILE *fp;
  // we need to pass in a filename pointer to get the entire string else if we pass in filename we will only be passing in singlr char.
  char filename[255], *filename_pointer = filename;
  //prompt the user
  printf("Enter your filename (example: sales_numbers.txt)(must be in the same directory): ");
  //get the filename from the user
  scanf("%s", filename);
  printf("\n");
  //open the file and have the file pointer point to this variable
  fp = fopen(filename_pointer, "r");
  //if the file does not exsist then prompt the user
  if (fp == NULL)
    {
      printf("cannot read 'matching-data.txt': No such file was found\n");
      exit(1);
    }
  //declare the index variables
  int i = 0, j, k;
  //declare the buffer for each text/int read from the file pointer
  char lines[255];
  //we know the file contains formated data for the programmer and department preference.
  // after the file is read line by line, it is then stored into an array
  int matching_data[10][5];
  //loop for each line until the end of file
  //deleminating each line by the new line charater
  while(EOF != fscanf(fp, "%[^\n]\n", lines))
    {
      // for each line store the individual charaters as an interger.
      for (j = 0; j < 5; j++)
	{ //the string notation of an interger is 49 when the string is 1
	  matching_data[i][j] = ((int)(lines[j * 2])) - 48;
	}
      // increment the row
      i++;
    }
  //close file when the file is read in
  fclose(fp);

  //split the array
  //the matching_data array contains both the programmers preference and the department preference.
  //so we can split their preference accordingly
  int programmer[5][5], department[5][5];

  //department
  //department starts from row 0 to row 4
  for (i = 0; i < 5; i++)
    {
      for (j = 0; j < 5; j++)
	{
	  department[i][j] = matching_data[i][j];
	}
    }
  //programmer
  //programmer starts from row 5 to row 9
  for (i = 5; i < 10; i++)
    {
      for (j = 0; j < 5; j++)
	{
	  programmer[i - 5][j] = matching_data[i][j];
	}
    }

  //by ranking the index of the programmer's want for the departement
  //we can rank how much the programmer want to be in the department based off of the department's index in
  //programmers preference; for example, programmer 1 wants 3 2 1 5 4 and we can rank that the programmer wants
  //department 1 at index 2. We store it as an array
  // index p1 p2 p3 p4 p5
  //  1    1  2  3  3  2
  //  2    2  4  0  2  1 
  //  3    *  *  *  *  *
  //  4
  //  5
  int index = 0;
  int val_index[25];
  for (k = 1; k < 6; k++)
    {
      for (i = 0; i < 5; i++)
	{
	  for (j = 0; j < 5; j++)
	    {
	      if (k == programmer[j][i])
		{
		  val_index[index] = j;
		  index++;
		}
	    }
	}
    }
  
  //uncompress val_index
  //we stored val_index in an 1d array because it was easier, although improvements can be made
  //we convert the val_index 1d array to an 2d array
  index = 0;
  int val_index_array[5][5];
  for (i = 0; i < 5; i++)
    {
      for (j = 0; j < 5; j++)
	{
	  val_index_array[i][j] = val_index[j + index];

	}
      index = index + 5;
    }

  //department is picking the programmers
  // reset the index variables to 0
  i = 0; j = 0; k = 0;
  //assuming the first col and row interger is the lowest
  //taken_programmer fills the colm with 6 when the programmer is taken therefore the programmer won't be taken again
  int lowest_val, taken_programmer;
  //run 5 time for each department
  for (i = 0; i < 5; i++)
    {
      //assume that the first index of each programmer is the lowest
      lowest_val = val_index_array[department[i][j] - 1][k];
      //iterate though the column and the programmer that wants the position the most or
      // has the lowest value is picked
      for(k = 0; k < 5; k++)
	{
	  if (val_index_array[i][k] < lowest_val)
	    {
	      lowest_val = val_index_array[i][k];
	    }
	}
      //iterate though the row at that index where the lowest value and the value in the index_array is the same
      //we know that column's index k is the programmer best fit for the department
      for(k = 0; k < 5; k++)
	{
	  if (val_index_array[i][k] == lowest_val)
	    {
	      taken_programmer = k;
	      printf("Department #%d will get Programmer #%d\n", i + 1, k + 1);
	      break;
	    }
	}
      // mark that programmer as taken
      for (k = 0; k < 5; k++)
	{ // when a programmer is taken the programmer will probably not leave their job so they would not choose any
      // other departments
	  val_index_array[k][taken_programmer] = 6;
	}
    }
}
