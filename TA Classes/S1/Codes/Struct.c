
#include <string.h>
#include <stdio.h>


// struct detail_id {
//   int Num;
//   char letter;
// };

// int main() {
//   struct detail_id s1;
//   s1.Num = 7992;
//   s1.letter = 'E';
//   printf("number: %d\n", s1.Num);
//   printf("letter: %c\n", s1.letter);

//   return 0;
// }





// error? and how can fix it

struct det2 {
  int myNum;
  char myLetter;
  char myString[30]; 
};

int main() {
  struct det2 s1;

  s1.myString ="Some text";
  s1.myNum=2;
  printf("My string: %s", s1.myString);

  return 0;
}



