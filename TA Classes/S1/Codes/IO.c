
#include <stdio.h>
#define max 3

int main()
{
	int a;
	scanf("%d ", &a);
    char c;
    c = getchar();
    // getchar(c)
    putchar(c);
    printf("\n%d a\n",a*2);    
    puts("os TAs");
	return 0;
}



// int main()
// {
//     char buf[max];
//     gets(buf);
//     printf("\nstring is: %s", buf);
//     return 0;
// }

// int main()
// {
//     char buf[max];
//     fgets(buf,max,stdin);
    
//     // output have max-1 characters

//     printf("\nstring is: %s", buf);
//     return 0;
// }
