#include <bits/stdc++.h>
using namespace std;

#define ltsit list<symbolEntry>::iterator
#define ltiit list<int>::iterator
#define ltstit list<symboltable*>::iterator
#define qdit vector<quad>::iterator
#define ltsym list<symbolEntry>
#define ltst list<symboltable*>
class symbolEntry;					
class symboltype;				
class symboltable;			
class quad;						
class quadArray;

// CLASSES

//class to store symbol table entries
class symbolEntry {                                    
	
	public:
	// symbolEntry class contains
		// 1. name of the symbol
		string name;
		// 2. type of the symbol				
		symboltype *type;
		// 3. size of the symbol	
		int size;
		// 4. offset of the symbol			
		int offset;
		// 5. nested symbol table		
		symboltable* nested;
		// 6. value of the symbol 
		string val;

		// Constructor
		symbolEntry (string , string t="int", symboltype* ptr = NULL, int width = 0);
		// A method to update different fields of an existing entry.
		symbolEntry* update(symboltype*); 	
};

//class to store type of symbol
class symboltype {
    public:
	//symboltype class contains
		// 1. type of the symbol
		string type; 
		// 2. width of the symbol
		int width;
		// 3. pointer to the array type
		symboltype* arraytype;
		// Constructor
		symboltype(string , symboltype* ptr = NULL, int width = 1);
};

//class to store symbol table
class symboltable {
    public: 
	// symboltable class contains
		// 1. name of the symbol table
		string name;
		// 2. count of temporary variables		
		int tempcount;
		// 3. list of symbol entries
		ltsym table;
		// 4. pointer to the parent symbol table
		symboltable* parent;
		// Constructor
		symboltable (string name="NULL");
		//  A method to lookup an id (given its name or lexeme) in the Symbol Table. If the id exists, the entry is returned, otherwise a new entry is created.
		symbolEntry* lookup (string);
		//A static method to generate a new temporary, insert it to the Symbol Table, and return a pointer to the entry.		
		static symbolEntry* gentemp (symboltype* , string init = "");	  
		//  A method to update different fields of an existing entry.    			
		void update();	
		//A method to print the Symbol Table in a suitable format.				
		void print();	

					        			
};

//class to store quadruple
class quad {                   
			
	public:
	// quad class contains
		// 1. result of the operation
		string res;
		// 2. operation to be performed
		string op;
		// 3. first argument
		string arg1;
		// 4. second argument
		string arg2;

		// Functions to print the quad
		void print();
		// function to output the result of the quad operation	
		void print1();
		// function to printing if statments
		void print2();

		// Constructors based on type of arguments
		quad (string , string , string op = "=", string arg2 = "");			
		quad (string , int , string op = "=", string arg2 = "");				
		quad (string , float , string op = "=", string arg2 = "");			
};

//class to store array of quads
class quadArray                
{ 		
	public:
		vector <quad> Array;
		//  A method to print the quadarray in a suitable format.
		void print();								
};

// Denotes basic variable types (not user defined)
class basicType {                                
	
    public:
		// type name (e.g. float)
		vector <string> type;			
		// type size (in bytes)
		vector <int> size;			
		// add a new basic type
		void addType(string ,int );
};

// STRUCTS

// Statement
struct Statement {
	// nextlist for statements
	list<int> nextList;		
};

// Array (to handle 1D and multi D arrays) 
struct Array {
	// Used for type of Array: may be ptr or arr
	string atype;				
	// Location used to compute address of Array
	symbolEntry* location;			
	// pointer to the symbol table entry	
	symbolEntry* Array;				
	// type of the subarray generated (needed for multidim arrays)
	symboltype* type;		
};

// Expression
struct Expression {
	// pointer to the symbol table entry
	symbolEntry* location;			
	// to store type of expression out of int, char, float, bool
	string type; 				
	// truelist for boolean expressions
	list<int> trueList;		
	// falselist for boolean expressions
	list<int> falseList;	
	// for statement expressions
	list<int> nextList;		
};


// typedefs
typedef Expression* expr;
typedef symboltype symtyp;

// extern (include external variables)
extern char* yytext;

extern int yyparse();
extern symboltable* ST;			// denotes the current Symbol Table
extern symboltable* globalST;		// global symbol table
extern symbolEntry* currSymbolPtr;		// pointer to current symbol
extern quadArray Q;				// quad array (for TAC)
extern basicType bt;            // basic types
extern long long int instr_count;// denotes count of instr
void outputSpace(int);

// Emit Functions
void emit(string , string , int, string arg = "");		  
void emit(string , string , float , string arg = "");   
void emit(string , string , string arg1="", string arg2 = "");
// Purpose: Insert i as the target label for each of the quads on the list pointed to by p.
// Input: A list of integers representing quad indices, and an integer i representing the target label.
// Output: None. The function modifies the quads in place.
void backpatch (list <int> , int );
// Purpose: Create a new list containing only i, an index into the array of quads, and return the newly created list.
// Input: An integer i representing an index into the array of quads.
// Output: A list containing the single integer i.
list<int> makelist (int );
// Purpose: Concatenate two lists pointed to by l1 and l2 and return the concatenated list.
// Input: Two lists of integers l1 and l2.
// Output: A list containing all elements from l1 followed by all elements from l2.				
list<int> merge (list<int> &l1, list <int> &l2);
// Purpose: Return the next instruction number.
// Input: None.
// Output: An integer representing the next instruction number.
int nextinstr();
// Purpose: Update the count of instructions.
// Input: None.
// Output: None. The function updates the instruction count.
void updateNextInstr();		
// Purpose: Convert a symbol to the desired type (target_type).
// Input: A pointer to a symbolEntry and a string representing the target type.
// Output: A pointer to a new symbolEntry of the target type.								
symbolEntry* convertType(symbolEntry*, string);
// Purpose: Check if E1 and E2 have the same types. If not, check if they have compatible types and use an appropriate conversion function.
// Input: References to two symbolEntry pointers s1 and s2.
// Output: A boolean value indicating whether the types are the same or compatible.				
bool compareSymbolType(symbolEntry* &s1, symbolEntry* &s2);
// Purpose: Recursively check if the symbol types are the same.
// Input: Two pointers to symboltype objects.
// Output: A boolean value indicating whether the symbol types are the same.
bool compareSymbolType(symtyp*, symtyp*);	
// Purpose: Get the size of the symbol type.
// Input: A pointer to a symboltype object.
// Output: An integer representing the size of the symbol type.
int computeSize(symtyp*);						
// Purpose: Print the type name of a symbol.
// Input: A pointer to a symboltype object.
// Output: A string representing the type name of the symbol.
string printType(symtyp*);	
// Purpose: Change the current symbol table to a new symbol table.
// Input: A pointer to a symboltable object.
// Output: None. The function updates the current symbol table.					
void changeTable(symboltable*);	
// Purpose: Convert an integer to a string.
// Input: An integer num.
// Output: A string representing the integer.
string convertInt2String(int num);

// Purpose: Convert a float to a string.
// Input: A float num.
// Output: A string representing the float.
string convertFloat2String(float num);

// Purpose: Convert an integer expression to a boolean expression.
// Input: An expr object representing an integer expression.
// Output: An expr object representing a boolean expression.
expr convertInt2Bool(expr expression);

// Purpose: Convert a boolean expression to an integer expression.
// Input: An expr object representing a boolean expression.
// Output: An expr object representing an integer expression.
expr convertBool2Int(expr expression);