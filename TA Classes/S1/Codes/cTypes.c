#include <stdio.h>
#include <ctype.h>
#include <string.h>
int main()
{
	char s[]="HIQWEerty";
    char a[]="OstasQWe";
    // size_t  {is undefind integer can store size of things in types}

    for (size_t i = 0; i < strlen(s); i++) {
        s[i] = tolower(s[i]);
    }
    for (size_t i = 0; i < strlen(a); i++) {
        a[i] = toupper(a[i]);
    }
    int temp1=islower(a[0]);
    int temp2=isupper(a[0]);
    int temp3=isdigit(a[0]);
    printf("%s \n",s);
    printf("%s \n",a);
    printf("%d %d %d",temp1,temp2,temp3);

    // int i;
    // for (i = 0; i < 5; i++) {
    //     printf("%d\n", i);
    // }

    // int j;
    // j=0
    // while(j<5)
    // {
    //     j++;
    //     print("%d\n",j)
    // }


	return 0;
}
