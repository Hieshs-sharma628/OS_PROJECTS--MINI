//project on calculator using c 
#include<stdio.h> 
#include<conio.h>
int main()
{
char operater_choice;
int num1,num2,result=0;//declaration of numbers and result storing
printf("Enter the oppreater(+,-,*,/)::");
scanf("%c",&operater_choice);//take the operater as input from user
printf("\nenter the 1st value::");
scanf("%d",&num1);//take 1st number as input from user
printf("\nenter the 2nd value::");
scanf("%d",&num2);//take 2st number as input from user
switch(operater_choice)//select the operater
{
case'+':
result=num1+num2;//perform Addtion 
printf("%d",result);
break;
case'-':
result=num1-num2;//perform substraction 
printf("%d",result);
break;
case'*':
result=num1*num2;//perform multiplication
printf("%d", result);
break;
case'/':
result=num1/num2;//perform devide
printf("%d",result);
break;
default:
printf("%c is not valid",operater_choice);
}
return 0;
}
  