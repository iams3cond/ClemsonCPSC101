//Lab 2
//Andrew Hunter
//01/20/15
//Program assigns and prints variables e1, e2, e3 and e4
#include <stdio.h>

int main()
{

int v1, v2;
int e1, e2, e3, e4;
int howmany;

printf("Please enter two integers, separated by a space");
scanf("%d %d", &v1, &v2);

e1=(v1+2*v2/3*v1);
e2=(v1+((2*v2)/(3*v1)));
e3=(v1+(2*(v2/3))*v1);
e4=((v2%v1)%(v2/v1));

howmany=printf("v1=%d and v2=%d \n", v1, v2);
howmany=printf("Expression values are \n");
howmany=printf("e1=%d, e2=%d, e3=%d, e4=%d \n", e1, e2, e3, e4);

}
