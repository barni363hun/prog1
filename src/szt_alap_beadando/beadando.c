/******************************************************************************

Készítsen programot amely alkalmas BCD kód formájában tárolt egész
számokkal való alapm¶veletek elvégzésére
M¶veletek:
Összeadás
Kivonás
Szorzás
Osztás
Feltételek
A feladat során maximum 32 bites aritmetikát alkalmazhat
A m¶veletek megvalósításához csak összeadás, kivonás, negálás, eltolás
és logikai muveleteket használhat.
A file-ból karakterenként kell beolvasni az adatokat és string m¶veletek
nem használhatók
Nem lehet semmilyen hiba a m¶velet elvégzése közben.
A megoldásnak tartalmaznia kell a program megfelel® dokumentációját.
Az els® 15 helyes megoldást tudjuk csak értékelni.

A bemeneti adatsor egy szöveges file-ban található (input.txt)
1002
-
502
A program irja ki egy TXT file-ba (output.txt) a m¶velet eredményét.
1002 (0x3EA)
-
502 (0x1F6)
=
500 (0x1F4)
Mellékeljen műveletenként 1-2 darab bemeneti minta file-t.
Dr. Fodor Attila, Dr. Görbe Péter (Pannon Egyetem)A számítástechnika alapjai
2022. 3 / 3

*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
// result array and its lenght as a struct
struct MyResult {
  int *res_arr;
  int res_arr_size;
};

struct MyResult sum(int *arr1, int *arr2, int arr1_size, int arr2_size) {
  // init
  int *res_arr;
  int res_arr_size = (arr1_size > arr2_size) ? arr1_size : arr2_size;
  res_arr = calloc(res_arr_size, sizeof(int));
  int arr1_i = arr1_size - 1;
  int arr2_i = arr2_size - 1;
  int res_arr_i = res_arr_size - 1;
  int leftover = 0;
  int current_sum = 0;
  int *tmp_arr = calloc(res_arr_size, sizeof(int));
  int i;

  // left padding the shorter input array with 0's
  if (arr1_size < res_arr_size) {
    for (i = 0; i <= arr1_i; i++) {
      tmp_arr[res_arr_i - i] = arr1[arr1_i - i];
    }

    arr1_size = res_arr_size;
    arr1 = realloc(tmp_arr, arr1_size * sizeof(int));
    if (arr1 == NULL) {
      fprintf(stderr, "Array not reallocated");
    }

  } else if (arr2_size < res_arr_size) {
    for (i = 0; i <= arr2_i; i++) {
      tmp_arr[res_arr_i - i] = arr2[arr2_i - i];
    }

    arr2_size = res_arr_size;
    arr2 = realloc(tmp_arr, arr2_size * sizeof(int));
    if (arr2 == NULL) {
      fprintf(stderr, "Array not reallocated");
    }
  }

  // add the two arrays like you would on paper
  while (res_arr_i >= 0) {
    current_sum = arr1[res_arr_i] + arr2[res_arr_i] + leftover;
    if (current_sum >= 10) {
      leftover = 1;
      current_sum = current_sum - 10;
    } else {
      leftover = 0;
    }
    res_arr[res_arr_i] = current_sum;
    // printf("%d+%d=%d\n", arr1[res_arr_i], arr2[res_arr_i],
    // res_arr[res_arr_i]);
    res_arr_i = res_arr_i - 1;
  }
  // return result array and its lenght as a struct
  struct MyResult res;
  res.res_arr = res_arr;
  res.res_arr_size = res_arr_size;
  return res;
}
struct MyResult subtract(int *arr1, int *arr2, int arr1_size, int arr2_size) {

  // return result array and its lenght as a struct
  struct MyResult res;
  res.res_arr = arr1;
  res.res_arr_size = arr1_size;
  return res;
}
struct MyResult multiply(int *arr1, int *arr2, int arr1_size, int arr2_size) {

  // return result array and its lenght as a struct
  struct MyResult res;
  res.res_arr = arr1;
  res.res_arr_size = arr1_size;
  return res;
}
struct MyResult divide(int *arr1, int *arr2, int arr1_size, int arr2_size) {

  // return result array and its lenght as a struct
  struct MyResult res;
  res.res_arr = arr1;
  res.res_arr_size = arr1_size;
  return res;
}

int main() {
  // init
  int *arr1; // first input number
  int *arr2; // second input number
  char c;
  int i;
  char operator;
  unsigned int arr1_size = 0;
  unsigned int arr2_size = 0;
  arr1 = calloc(arr1_size, sizeof(int));
  arr2 = calloc(arr2_size, sizeof(int));
  struct MyResult result;

  // open files
  FILE *ofp = fopen("output.txt", "w");
  FILE *ifp = fopen("input.txt", "r");
  int file_end = 0;
  // Return if could not open file
  if (ofp == NULL)
    return 0;
  // Return if could not open file
  if (ifp == NULL) {
    fprintf(stderr, "input.txt not found!");
    return 0;
  }

  if (arr1 == NULL) {
    fprintf(stderr, "Array 1 not allocated");
  }
  if (arr2 == NULL) {
    fprintf(stderr, "Array 2 not allocated");
  }
  c = fgetc(ifp); // read in first character of first number
  // read numbers until we foud '\n' character
  while ((int)(c)-48 >= 0) {
    arr1_size++;
    arr1 = realloc(arr1, arr1_size * sizeof(int));
    if (arr1 == NULL) {
      fprintf(stderr, "Array not reallocated");
    }
    arr1[arr1_size - 1] = (int)(c)-48;
    c = fgetc(ifp);
  }
  // write out first number
  for (i = 0; i < arr1_size; i++) {
    fputc((arr1[i]) + '0', ofp);
  }
  // read and write out operator
  operator= fgetc(ifp);
  fputc('\n', ofp);
  fputc(operator, ofp);
  fputc('\n', ofp);
  // printf("\n%c\n", operator);
  c = fgetc(ifp); // read in first character of first number
  // read numbers until we reach the end of the file
  while (file_end != 1) {
    c = fgetc(ifp);
    if (!feof(ifp)) {
      arr2_size++;
      arr2 = realloc(arr2, arr2_size * sizeof(int));
      if (arr2 == NULL) {
        fprintf(stderr, "Array not reallocated");
      }
      arr2[arr2_size - 1] = (int)(c)-48;
    } else {
      file_end = 1;
    }
  }

  // write out second number
  for (i = 0; i < arr2_size; i++) {
    fputc((arr2[i]) + '0', ofp);
  }
  // write out '=' sign
  fputc('\n', ofp);
  fputc('=', ofp);
  fputc('\n', ofp);

  // get the result based on the operator
  if (operator== '+') {
    result = sum(arr1, arr2, arr1_size, arr2_size);
  } else if (operator== '-') {
    result = subtract(arr1, arr2, arr1_size, arr2_size);
  } else if (operator== '*') {
    result = multiply(arr1, arr2, arr1_size, arr2_size);
  } else if (operator== '/') {
    result = divide(arr1, arr2, arr1_size, arr2_size);
  }

  // write out result
  for (i = 0; i < result.res_arr_size; i++) {
    fputc((result.res_arr[i]) + '0', ofp);
  }

  // clode files, free memory
  fclose(ifp);
  fclose(ofp);
  free(arr1);
  free(arr2);

  return 0;
}