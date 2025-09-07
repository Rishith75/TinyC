#include "y.tab.c"
#include "lex.yy.c"
#include<sstream>
#include<string>
#include<iostream>
using namespace std;

// reference to global variables declared in header file 
symboltable* globalST;						// global symbol table
quadArray Q;							// quad array (for TAC)
string var_type;						// store current variable type
symboltable* ST;							// pointer to current symbol table
symbolEntry* currSymbolPtr; 					// pointer to current symbol
basicType bt;							// basic types
long long int instr_count;				// count of instr (used for sanity check)

// to implement switch case for strings in c++
int s2i(string op) {
	// Create a map to associate string operators with integer values
	map<string, int> op_map = {
		{"+", 0}, {"-", 1}, {"*", 2}, {"/", 3}, {"%", 4}, {"|", 5}, {"^", 6}, {"&", 7},
		{"==", 8}, {"!=", 9}, {"<=", 10}, {"<", 11}, {">", 12}, {">=", 13}, {"goto", 14},
		{">>", 15}, {"<<", 16}, {"=", 17}, {"=&", 18}, {"=*", 19}, {"*=", 20}, {"uminus", 21},
		{"~", 22}, {"!", 23}, {"=[]", 24}, {"[]=", 25}, {"return", 26}, {"param", 27},
		{"call", 28}, {"label", 29}
	};

	// Check if the operator exists in the map
	if (op_map.find(op) == op_map.end())
		return -1; // Return -1 if the operator is not found

	// Return the corresponding integer value for the operator
	return op_map[op];
}

// Functions related to symbol table

// Constructor for class symEntry
symbolEntry::symbolEntry(string symbolName, string typeName, symboltype* arrayType, int typeWidth) 
{     
	// Initialize symbol table entry
	(*this).name = symbolName;
	// Create symboltype for the symbol
	type = new symboltype(typeName, arrayType, typeWidth);       
	// Determine size based on type
	size = computeSize(type);                  
	// Initialize offset to 0
	offset = 0;                                   
	// No initial value assigned
	val = "-";                                    
	// Set nested table to NULL initially
	nested = NULL;                                
}

// function to update symbol (modify attributes for typecasting)
symbolEntry* symbolEntry::update(symboltype* newType) 
{
	// Assign the new type to the symbol
	type = newType;										 

	// Recalculate the size based on the new type
	(*this).size = computeSize(newType);                 

	// Return the updated symbol entry
	return this;                                 
}

// Constructor for class symboltype
symboltype::symboltype(string typeName, symboltype* arrayType, int typeWidth)        
{
	// Initialize type
	this->type = typeName;

	// Initialize width
	this->width = typeWidth;

	// Initialize array type
	this->arraytype = arrayType;

	// Refer to translator.h for details on each attribute of the symbol type
}

// Constructor for class symboltable, i.e. a symbol table
symboltable::symboltable(string tableName)            
{
	// Initialize the name of the symbol table
	this->name = tableName;

	// Initialize count to 0 as there are no temporary variables initially
	this->tempcount = 0;                           
}

// lookup function for, looking up id of a symbol
symbolEntry* symboltable::lookup(string symbolName)               
{
	symbolEntry* symbol;
	// Iterator for list<symbolEntry> type
	ltsit it;                      
	it = table.begin();
	// Traverse through all symbols in the table
	while(it != table.end()) 
	{
		// Return the address of the iterator if symbol is found
		if(it->name == symbolName) 
			return &(*it);         
		it++;
	}
	// Create a new symbol if not found in the table
	symbol = new symbolEntry(symbolName);
	// Add the new symbol to the list (at the end)
	table.push_back(*symbol);
	// Return reference to the newly added symbol           
	return &table.back();              
}

//Update the symbol table 
void symboltable::update()                      
{
	// List of nested symbol tables
	ltst nestedTables;                 
	ltsit symbolIter;
	symbolIter = table.begin();
	int currentOffset;
	
	while(symbolIter != table.end()) 
	{
		if(symbolIter == table.begin()) 
		{
			symbolIter->offset = 0;
			currentOffset = symbolIter->size;
		}
		else 
		{
			symbolIter->offset = currentOffset;
			currentOffset = symbolIter->offset + symbolIter->size;
		}
		if(symbolIter->nested != NULL) 
			nestedTables.push_back(symbolIter->nested);
		symbolIter++;
	}
	
	ltstit nestedIter;
	nestedIter = nestedTables.begin();
	while(nestedIter != nestedTables.end()) 
	{
	  (*nestedIter)->update();
	  nestedIter++;
	}
}
// print a symbol table
void symboltable::print()                            
{
    int instruction_index = 0;
    // collection of tables
    ltst table_list;                       
    for(int i = 0; i < 50; i++) 
        cout << "";             
    cout << endl;
    // display table name and its parent's name
    cout << "Table Name: " << this->name << "\t\t\t Parent Name: ";          
    if(this->parent == NULL)
        cout << "NULL" << endl;
    else
        cout << this->parent->name << endl; 
    for(int j = 0; j < 50; j++) 
        cout << "";
    cout << endl;
    
    cout << "Name";              
    outputSpace(11);
    cout << "Type";             
    outputSpace(16);
    cout << "Initial Value";   
    outputSpace(7);
    cout << "Size";              
    outputSpace(11);
    cout << "Offset";            
    outputSpace(9);
    cout << "Nested" << endl;      
    outputSpace(100);
    cout << endl;
    ostringstream stream;
     
    // display all attributes for each entry
    for(ltsit iterator = table.begin(); iterator != table.end(); iterator++) {          
        // display name
        cout << iterator->name;                                    
        outputSpace(15 - iterator->name.length());
        string type_result = printType(iterator->type);               
        // display type	
        cout << type_result;
        outputSpace(20 - type_result.length());
        // display initial value 
        cout << iterator->val;                                    
        
        // display size
        outputSpace(20 - iterator->val.length());
        cout << iterator->size;                                   
        stream << iterator->size;
        
        // display offset
        outputSpace(15 - stream.str().length());
        stream.str("");
        stream.clear();
        cout << iterator->offset;                                 
        stream << iterator->offset;
        
        
        outputSpace(15 - stream.str().length());
        stream.str("");
        stream.clear();

        // display nested table
        if(iterator->nested == NULL) 
        {                             
            cout << "NULL" << endl;	
        }
        else 
        {
            cout << iterator->nested->name << endl;
            table_list.push_back(iterator->nested);
        }
    }
    
    for(int k = 0; k < 100; k++) 
        cout << "-";
    cout << "\n\n";
    for(ltstit iter = table_list.begin(); iter != table_list.end(); ++iter) 
    {
        (*iter)->print();  // display symbol table
    }
}

// make new symbol table
void changeTable(symboltable* newsymboltable) 
{	      
	// Update the current symbol table to the new symbol table
	ST = newsymboltable;
} 

// Check if the symbols have same symbol table entries or not
bool compareSymbolType(symbolEntry*& sym1, symbolEntry*& sym2)
{
	symboltype* type1 = sym1->type; // Retrieve the base types
	symboltype* type2 = sym2->type;
	int isConvertible = 0;

	// Check if one type can be converted to the other
	if (compareSymbolType(type1, type2))
		isConvertible = 1;
	else if (sym1 = convertType(sym1, type2->type))
		isConvertible = 1;
	else if (sym2 = convertType(sym2, type1->type))
		isConvertible = 1;

	// Return true if conversion is possible, otherwise false
	return isConvertible ? true : false;
}

// Check if the symbol types are same or not
bool compareSymbolType(symboltype* type1, symboltype* type2) { 	
	// Flag to indicate if types are comparable
	int isComparable = 0;	

	// Check if both symbol types are NULL
	if(type1 == NULL && type2 == NULL)
		return true;

	// Check if only one of them is NULL or types are different
	else if(type1 == NULL || type2 == NULL || type1->type != type2->type)
		return false;

	// Recursively check their array types
	else 
		return compareSymbolType(type1->arraytype, type2->arraytype);       
}

// Functions related to quads and TAC

// Constructor for quad object
quad::quad(string result, string argument1, string operation, string argument2) 
{
	// Assign the result to the quad's result field
	this->res = result;

	// Assign the first argument to the quad's arg1 field
	this->arg1 = argument1;

	// Assign the operation to the quad's op field
	this->op = operation;

	// Assign the second argument to the quad's arg2 field
	this->arg2 = argument2;
}

quad::quad(string result, int arg1Value, string operation, string arg2Value) 
{
	// Assign the result to the quad's result field
	this->res = result;

	// Assign the second argument to the quad's arg2 field
	this->arg2 = arg2Value;

	// Assign the operation to the quad's op field
	this->op = operation;

	// Convert the integer argument to string and assign to arg1
	this->arg1 = convertInt2String(arg1Value);
}

quad::quad(string result, float arg1Value, string operation, string arg2Value) 
{
	// Assign the result to the quad's result field
	this->res = result;

	// Assign the second argument to the quad's arg2 field
	this->arg2 = arg2Value;

	// Assign the operation to the quad's op field
	this->op = operation;

	// Convert the float argument to string and assign to arg1
	this->arg1 = convertFloat2String(arg1Value);
}

// method to output quads
void quad::print() 
{   
    int instruction_index = 0;	
    switch(s2i(op))
    {
        // Binary operations
        case 0:
            this->print1();
            break;
        
        case 1:
            this->print1();
            break;
    
        case 2:
            this->print1();
            break;

        case 3:
            this->print1();
            break;

        case 4:
            this->print1();
            break;

        case 5:
            this->print1();
            break;

        case 6:
            this->print1();
            break;

        case 7:
            this->print1();
            break;

        case 8:
            this->print2();
            break;

        case 9:
            this->print2();
            break;

        case 10:
            this->print2();
            break;

        case 11:
            this->print2();
            break;

        case 12:
            this->print2();
            break;

        case 13:
            this->print2();
            break;

        case 14:
            cout << "goto " << res;
            break;

        // Shift operations
        case 15:
            this->print1();
            break;

        case 16:
            this->print1();
            break;
    
        case 17:
            cout << res << " = " << arg1;
            break;

        // Unary operations 
        case 18:
            cout << res << " = &" << arg1;
            break;

        case 19:
            cout << res << " = *" << arg1;
            break;

        case 20:
            cout << "*" << res << " = " << arg1;
            break;

        case 21:
            cout << res << " = -" << arg1;
            break;
    
        case 22:
            cout << res << " = ~" << arg1;
            break;

        case 23:
            cout << res << " = !" << arg1;
            break;

        // Other operations
        case 24:
            cout << res << " = " << arg1 << "[" << arg2 << "]";
            break;

        case 25:
            cout << res << "[" << arg1 << "] = " << arg2;
            break;

        case 26:
            cout << "return " << res;
            break;

        case 27:
            cout << "param " << res;
            break;

        case 28:
            cout << res << " = call " << arg1 << ", " << arg2;
            break;

        case 29:
            cout << res << ": ";
            break;

        default:
            cout << "Unknown operation " << op;
            break;
    }  
    cout << endl;         
}

void quad::print1()
{
	// Output the result of the quad operation
	cout << res << " = " << arg1 << " " << op << " " << arg2;
}

// for printing if statments
void quad::print2()
{
	 
	cout<<"if "<<arg1<< " "<<op<<" "<<arg2<<" goto "<<res;
	 
}

// Add a new basic C type to type symbol table
void basicType::addType(string typeName, int typeSize) 
{
	// Add the type name to the type list
	type.push_back(typeName);
	
	// Add the type size to the size list
	size.push_back(typeSize);
}

// method to output the quad array, i.e., the TAC
void quadArray::print()                                   
{
    for(int i = 0; i < 100; i++) 
        cout << "_";
    cout << endl;
    
    // output the Three Address Code
    cout << "Three Address Code:" << endl;           
    for(int i = 0; i < 100; i++) 
        cout << "_";
    cout << endl;
    
    int index = 0;
    qdit iterator = Array.begin();
    while(iterator != Array.end()) 
    {
        if(iterator->op == "label") 
        {           
            // if it is a label, print it
            cout << endl << "L" << index << ": ";
            iterator->print();
        }
        else 
        {                         
            // otherwise, print with indentation
            cout << "L" << index << ": ";
            outputSpace(4);
            iterator->print();
        }
        iterator++;
        index++;
    }
    
    for(int i = 0; i < 100; i++) 
        cout << "_";      
    cout << endl;
}

// helper function, just to format output
void outputSpace(int n)
{
	 
	for(int i = 0; i<n; i++)
	{
		cout<<" ";
	}
	 
}

// function to convert an integer to a string
string convertInt2String(int num)                    
{
    stringstream ss;                      
    ss << num; 
    string temp = ss.str();
    char* charArray = (char*) temp.c_str();
    string result = string(charArray);
    return result;                              
}

// function to convert a float to a string
string convertFloat2String(float num)                       
{
    std::ostringstream stream;
    stream << num;
    return stream.str();
}


// function overloading to handle different instruction types
void emit(string operation, string result, string argument1, string argument2) 
{             
    // Create a new quad and add it to the Array
    quad *newQuad = new quad(result, argument1, operation, argument2);
    Q.Array.push_back(*newQuad);
}

void emit(string operation, string result, int argument1, string argument2) 
{                 
    // Create a new quad and add it to the Array
    quad *newQuad = new quad(result, argument1, operation, argument2);
    Q.Array.push_back(*newQuad);
}

void emit(string operation, string result, float argument1, string argument2) 
{                 
    // Create a new quad and add it to the Array
    quad *newQuad = new quad(result, argument1, operation, argument2);
    Q.Array.push_back(*newQuad);
}

// function to perform type conversions
// symbol is converted to the desired type (target_type)
symbolEntry* convertType(symbolEntry* symbol, string target_type) 
{                            
    symbolEntry* new_symbol = ST->gentemp(new symboltype(target_type));    
    // if symbol is currently float
    if(symbol->type->type == "float")                                      
    {
        // if target type is int
        if(target_type == "int")                                      
        {
            emit("=", new_symbol->name, "float2int(" + symbol->name + ")");
            return new_symbol;
        }
        // if target type is char
        else if(target_type == "char")                             
        {
            emit("=", new_symbol->name, "float2char(" + symbol->name + ")");
            return new_symbol;
        }
        return symbol;
    }

    // if symbol is currently int
    else if(symbol->type->type == "int")                                  
    {
        // if target type is float
        if(target_type == "float")                                     
        {
            emit("=", new_symbol->name, "int2float(" + symbol->name + ")");
            return new_symbol;
        }
        // if target type is char
        else if(target_type == "char")                                
        {
            emit("=", new_symbol->name, "int2char(" + symbol->name + ")");
            return new_symbol;
        }
        return symbol;
    }

    // if symbol is currently char
    else if(symbol->type->type == "char")                                 
    {
        // if target type is int
        if(target_type == "int")                                     
        {
            emit("=", new_symbol->name, "char2int(" + symbol->name + ")");
            return new_symbol;
        }
        // if target type is double
        if(target_type == "double")                                
        {
            emit("=", new_symbol->name, "char2double(" + symbol->name + ")");
            return new_symbol;
        }
        return symbol;
    }
    return symbol;
}

// refer to header file for greater details of these functions
// For backpatching grammar 
void backpatch(list<int> patch_list, int address)                
{
    // get string form of the address
    string address_str = convertInt2String(address);              
    ltiit it = patch_list.begin();
     
    while(it != patch_list.end()) 
    {
        Q.Array[*it].res = address_str;  // perform the backpatching
        it++;
    }
}

// make a new list
list<int> makelist(int init) 
{
	list<int> newlist(1,init);                     
	 
	return newlist;
}

// merge existing lists
list<int> merge(list<int> &a,list<int> &b)
{
	a.merge(b);                                
	 
	return a;
}

// Convert an integer expression to a boolean expression
expr convertInt2Bool(expr expression)        
{   
    // Update the false list and true list, and emit general goto statements if not already boolean
    if(expression->type != "bool")                
    {
        expression->falseList = makelist(nextinstr());    
        emit("==", "", expression->location->name, "0");
        expression->trueList = makelist(nextinstr());
        emit("goto", "");
    }
}

// Convert boolean expression to integer
expr convertBool2Int(expr expression) 
{   
    // Use general goto statements and standard procedure
    if(expression->type == "bool") 
    {
        expression->location = ST->gentemp(new symboltype("int"));         
        
        // Backpatch true list
        backpatch(expression->trueList, nextinstr());
        
        // Emit true assignment
        emit("=", expression->location->name, "true");
        
        // Calculate next instruction
        int next_instr = nextinstr() + 1;
        
        // Convert next instruction to string
        string next_instr_str = convertInt2String(next_instr);
        
        // Emit goto statement
        emit("goto", next_instr_str);
        
        // Backpatch false list
        backpatch(expression->falseList, nextinstr());
        
        // Emit false assignment
        emit("=", expression->location->name, "false");
    }
}

void updateNextInstr()
{
	instr_count++;
}


int nextinstr() 
{
	 
	return Q.Array.size();  // The next instruction index is the size of the quad array
}

symbolEntry* symboltable:: gentemp(symboltype* type, string initial_value) 
{   
    // create a temporary variable
    string temp_name = "t" + convertInt2String(ST->tempcount++);  // generate name for temporary variable
    symbolEntry* temp_symbol = new symbolEntry(temp_name);
    temp_symbol->type = type;
    temp_symbol->size = computeSize(type);  // calculate its size
    temp_symbol->val = initial_value;
    ST->table.push_back(*temp_symbol);  // add it to the symbol table
    return &ST->table.back();
}

// function to calculate size
int computeSize(symboltype* type)                   
{
    if(type->type.compare("void") == 0)    
        return bt.size[1];
    else if(type->type.compare("char") == 0) 
        return bt.size[2];
    else if(type->type.compare("int") == 0) 
        return bt.size[3];
    else if(type->type.compare("float") == 0) 
        return bt.size[4];
    else if(type->type.compare("arr") == 0) 
        return type->width * computeSize(type->arraytype);  // recursive call for arrays and multidimensional arrays
    else if(type->type.compare("ptr") == 0) 
        return bt.size[5];
    else if(type->type.compare("func") == 0) 
        return bt.size[6];
    else 
        return -1;
}

// Display the type of variable (useful for multidimensional arrays)
string printType(symboltype* type)                    
{
    if(type == NULL) return bt.type[0];
    if(type->type.compare("void") == 0) return bt.type[1];
    else if(type->type.compare("char") == 0) return bt.type[2];
    else if(type->type.compare("int") == 0) return bt.type[3];
    else if(type->type.compare("float") == 0) return bt.type[4];
    else if(type->type.compare("ptr") == 0) return bt.type[5] + "(" + printType(type->arraytype) + ")";  // recursive for pointers
    else if(type->type.compare("arr") == 0) 
    {
        string width_str = convertInt2String(type->width);  // recursive for arrays
        return bt.type[6] + "(" + width_str + "," + printType(type->arraytype) + ")";
    }
    else if(type->type.compare("func") == 0) return bt.type[7];
    else return "NA";
}

int main()
{
	// Add all the base types initially
	bt.addType("null",0);                 
	bt.addType("void",0);
	bt.addType("char",1);
	bt.addType("int",4);
	bt.addType("float",8);
	bt.addType("ptr",4);
	bt.addType("arr",0);
	bt.addType("func",0);
	// count of instr 
	instr_count = 0;
	// the global symbol table
	globalST=new symboltable("Global");                        
	ST=globalST;
	// call parser
	yyparse();												 
	// update the Golbal symbo table
	globalST->update();										 
	cout<<"\n";
	//print TAC
	Q.print();	
	//print all STs
	globalST->print();										
	
};