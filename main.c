#include<math.h>
#include<string.h>
#include"main.h"
/* hi 
   prathima
   how 
   are
   you
   sum of 
   a + b is
 */ 


int main()
{
    int a,b;
    int result,choice;
    printf("Enter two numbers : ");
    scanf("%d%d",&a,&b);   //read the inputs from the user

    printf("1. Addition\n2. Subtraction\n3. Multiplication\n4. Division\n5. Modulus\n");
    printf("Enter the choice : ");
    scanf("%d",&choice);    //read the input from the user to find the operation which we need
    
    result = calc(a,b,choice);   //function call

    printf("Result is %d\n",result);    //print the result
    return SUCCESS;
}

int calc(int a,int b,int choice)
{
    switch(choice)
    {
	case 1:
	    return add(a,b);  //call the add function if the choice is 1
	case 2:
	    return sub(a,b);  //call the sub function if the choice is 2
	case 3:
	    return mul(a,b);  //call the mul function if the choice is 3
	case 4:
		return division(a,b);  //call the div function if the choice is 4
	case 5:
	    return mod(a,b);  //call the mod function if the choice is 5
	default:
	    printf("Invalid choice\n");   //else print default msg and exit
	    exit(0);
    }
}



int add(int a,int b)
{
    return SUCCESS;
//    return a+b;   //adding a and b and returning it to the function call
}


int sub(int a,int b)
{
    return SUCCESS;
    return a-b;   //difference of a and b
}

int mul(int a,int b)
{
return SUCCESS;
    return a*b;   //multiplying a and b 
}

int division(int a,int b)
{
return SUCCESS;
    return a/b;   //dividing a by b 
}

int mod(int a,int b)
{
    return a%b;   //modulus a and b and returning it to the function call
}


