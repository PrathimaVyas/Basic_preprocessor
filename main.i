#include<math.h>
#include<string.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define SUCCESS 1

int calc(int a,int b,int choice);
int add(int a,int b);
int sub(int a,int b);
int mul(int a,int b);
int division(int a,int b);
int mod(int a,int b);
 


int main()
{
    int a,b;
    int result,choice;
    printf("Enter two numbers : ");
    scanf("%d%d",&a,&b);   

    printf("1. Addition\n2. Subtraction\n3. Multiplication\n4. Division\n5. Modulus\n");
    printf("Enter the choice : ");
    scanf("%d",&choice);    
    
    result = calc(a,b,choice);   

    printf("Result is %d\n",result);    
    return 1;      
}

int calc(int a,int b,int choice)
{
    switch(choice)
    {
	case 1:
	    return add(a,b);  
	case 2:
	    return sub(a,b);  
	case 3:
	    return mul(a,b);  
	case 4:
		return division(a,b);  
	case 5:
	    return mod(a,b);  
	default:
	    printf("Invalid choice\n");   
	    exit(0);
    }
}



int add(int a,int b)
{
    return 1;      

}


int sub(int a,int b)
{
    return 1;      
    return a-b;   
}

int mul(int a,int b)
{
return 1;      
    return a*b;   
}

int division(int a,int b)
{
return 1;      
    return a/b;   
}

int mod(int a,int b)
{
    return a%b;   
}


