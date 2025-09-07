// ternary operators, if-else conditions, function calls (simple and nested)
int custom_func(int a, int b, int c) 
{
    int result = c;
    if (a > b)  // if-else
        result += a;
    else
    {
        result *= b;
    }
    return result;
}

int find_min(int a, int b) 
{
    int min_value;
    // ternary operator
    min_value = a > b ? b : a; 
    return min_value;
}

// a random function to test nested function calls
int nested_func(int a, int b)
{
    int result = 1;
    if (a < 3) 
    {
        result = custom_func(a, b, 5);
    }
    return result;
}

int main() 
{
    int difference, num1, num2;
    int constant = 5;
    difference = nested_func(10, constant);
    num1 = 2;
    num2 = 3;
    constant = custom_func(find_min(num1, 3), find_min(5, num2), 2);
    return 0;
}