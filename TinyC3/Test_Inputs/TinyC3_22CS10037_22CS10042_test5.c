// Recursive functions and nesting of conditional statements  
int compute_factorial(int num) {
    if (num == 1 || num == 0)
        return 1;
    return num * compute_factorial(num - 1);
}

int compute_gcd(int x, int y) 
{ 
    if (x == 0) 
        return y; 
    return compute_gcd(y % x, x); 
}

int main()  
{  
    int first_num, second_num, gcd_result;
    int factorial_result = 1;
    int condition_flag = 0;
    
    if (condition_flag == 0) {
        first_num = 15;
        if (condition_flag == 1)   
            second_num = 6;
        else
            second_num = 3;
    }
    // Nested if-else statement
    else {
        first_num = 50;
        second_num = 10;
    }
    
    // Calling recursive function
    gcd_result = compute_gcd(first_num, second_num);
    factorial_result = compute_factorial(first_num * second_num);   
    return 0;  
}  
