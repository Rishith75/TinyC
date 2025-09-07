// declaration of variables(int, float, char), 1D array, 2D array, functions, and arithmetic operations

// global declarations
float rate = 3.6; // float declaration
int   count, data[15];  // 1D array declaration
float matrix[3][3];     // 2D array declaration
int m = 8, *pointer, n; // pointer declaration
void calculate(int id, float rate); // function declaration
char symbol;

void main()
{
	// Variable Declaration
	int num1 = 225;
	int num2 = 29, total, diff, product, quotient, remainder, bitwise_and, bitwise_or;
	// Character definitions
	char initial = 'f', symbol = 'e'; 

	// Arithmetic Operations
	total = num1 + num2;
	diff = num1 - num2;
	product = num1 * num2;
	quotient = num1 / num2;
	remainder = num1 % num2;
	bitwise_and = num1 & num2;
	bitwise_or = num1 | num2;
	
	num2 = num2 << 3;
	num1 = num1 >> 2;

	return 0;
}
