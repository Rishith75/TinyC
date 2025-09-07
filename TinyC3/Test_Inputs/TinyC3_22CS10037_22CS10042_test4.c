// Testing pointers (swapping) and typecasting

int calculate_quotient(float numerator, float denominator)
{
    int result;
    // Convert float to int
    result = numerator / denominator; 
    return result;
}

// Nested function call
int calculate_remainder(int dividend, int divisor) {
    // Returns (dividend % divisor)
    int q = calculate_quotient(dividend, divisor);
    int remainder_value = dividend - divisor * q;
    return remainder_value;
}

void exchange(int* first, int* second) // Pointers use case 
{
    int temp = *first;
    *first = *second;
    *second = temp;
}

int main()
{
    int quotient_result = 0, remainder_result = 0;
    float number1 = 3.5;
    quotient_result = calculate_quotient(number1, 1.5);
    remainder_result = 15;
    exchange(&quotient_result, &remainder_result);
    remainder_result = calculate_remainder(25, 6);
    return 0;
}
