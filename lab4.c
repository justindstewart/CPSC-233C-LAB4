/*
  CPSC 223C
  Spring 2015
  CSU Fullerton

  Lab 4: variable arguments

  Authors: Justin Stewart (scubastew@csu.fullerton.edu)

*/ 

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

/* num is the number of variable arguments, all of type int. Compute
   and return the median of the variable arguments. Recall that in the
   case of an even number of arguments, you need to take the mean of
   the two arguments closest to the middle, which is why the return
   type is double. */
double median(int num, ...);

/* num is the number of variable arguments, all of type int. Compute
   and return the mode of the variable arguments. Recall that the mode
   is the most frequently-ocurring value. If there are multiple values
   tied for the same number of occurences, return the lesser of the
   tied values.
 */
int mode(int num, ...);

//compare is used to sort arrays
int compare (const void * a, const void * b);

double median(int num, ...) {
  //Start variable argument list
  va_list myList;
  va_start (myList, num);
  
  //Create array of size num(size of argument list)
  int *array = malloc(num * sizeof(int));
  
  //Loop through argument list adding each element to array
  for(int i = 0; i < num; i++) {
    int number = va_arg (myList, int);
    array[i] = number;
  }
  
  //End variable argument list
  va_end (myList);

  //Sort array
  qsort(array, num, sizeof(int), compare);
  
  //Checks for even array, does appropriate calculation
  if (num%2 == 0) {
    return ((array[num/2] + array[num/2 - 1]) / 2.0);
  }
  else {
    return array[num/2];
  }
}

int mode(int num, ...) {
  //Start argument list
  va_list myList;
  va_start (myList, num);

  //Create array of size num(size of argument list)
  int *array = malloc(num * sizeof(int));

  //Variables and arrays initialized to 0
  int countModes[11] = {0};
  int maxModes = 0;
  int maxIndex = 0;
  int minIndex = 0;

  //Loop through argument list adding each element to array and counting modes
  for (int i = 0; i < num; i++) {
    int number = va_arg (myList, int);
    array[i] = number;
    countModes[array[i]]++;
  }

  //End variable argument list
  va_end (myList);

  //Loops through countModes array and finds the max value and index
  for (int i = 0; i < 11; i++) {
    //Checks if current array value is greater than the set max
    if (countModes[i] > maxModes) {
      maxModes = countModes[i];
      maxIndex = i;
    }
  }

  //Loops through countModes and outputs first instance of maxModes;
  for (int i = 0; i < 11; i++) {
    if(countModes[i] == maxModes) {
      minIndex = i;
      break;
    }
  }
  return minIndex;
}


int compare (const void * a, const void * b) {
  return ( *(int*)a - *(int*)b );
}

int main() {

  /* MEDIAN */

  /* one argument */
  assert(median(1, 1) == 1);

  /* special case: even number of arguments */
  assert(median(2, 1, 2) == 1.5);

  /* straightforward three-argument cases */
  assert(median(3, 1, 2, 3) == 2);
  assert(median(3, 3, 2, 1) == 2);
  assert(median(3, 3, 3, 3) == 3);

  /* straightforward four-argument cases */
  assert(median(6, 9, -10, -1, 8, 3, 5) == 4);
  assert(median(7, 5, 6, 4, 1, 2, 3, 7) == 4);

  /* TODO: you should add at least two more test cases for your
     median() function here. */

  assert(median(9, 32, 76, 21, 83, 81, 80, 100, 91, 95) == 81);
  assert(median(10, 32, 76, 21, 83, 81, 80, 100, 91, 95, 15) == 80.5);

  /* MODE */

  /* straightforward cases */
  assert(mode(1, 1) == 1);
  assert(mode(3, 2, 1, 1) == 1);
  assert(mode(7, 1, 1, 1, 2, 2, 2, 2) == 2);

  /* special case: tie */
  assert(mode(6, 3, 3, 3, 2, 2, 2) == 2);
  assert(mode(6, 2, 3, 2, 3, 2, 3) == 2);

  /* TODO: you should add at least two more test cases for your mode()
     function here. */
  
  assert(mode(10, 2, 1, 3, 3, 1, 5, 4, 6, 7, 3) == 3);
  assert(mode(11, 2, 1, 3, 3, 1, 5, 4, 6, 7, 3, 1) == 1);

  return 0;
}
