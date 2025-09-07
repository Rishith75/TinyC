int main()
{
    int index = 0, column, limit = 15;
    column = 50;
    int values[10]; // 1D integer array

    int total = 0;
    // Testing while loop
    while (index < limit) 
    {
        index++;
        total += values[index];
    }

    total = 0;
    int grid[6][6]; // 2D integer array
    // Nested for loop
    for (index = 0; index < limit; index++)
    {
        for (column = 0; column < limit; column++)  
            grid[index][column] = total / (index * column + 1); // Avoid division by zero
    }
    
    // Testing do-while loop
    do 
    {
        --column;
        ++index;
        values[index] = (index - column);
    } while (index < 20);

    return 0;
}
