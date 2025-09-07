all:
	yacc -d -Wnone TinyC3.y
	lex TinyC3.l
	g++ -w TinyC3_translator.cxx
	./a.out < Test_Inputs/TinyC3_test1.c > Test_Outputs/TinyC3_quads1.txt
	./a.out < Test_Inputs/TinyC3_test2.c > Test_Outputs/TinyC3_quads2.txt
	./a.out < Test_Inputs/TinyC3_test3.c > Test_Outputs/TinyC3_quads3.txt
	./a.out < Test_Inputs/TinyC3_test4.c > Test_Outputs/TinyC3_quads4.txt
	./a.out < Test_Inputs/TinyC3_test5.c > Test_Outputs/TinyC3_quads5.txt

clean: 
	rm -f y.tab.c y.tab.h lex.yy.c a.out Test_Outputs/TinyC3_quads1.txt Test_Outputs/TinyC3_quads2.txt Test_Outputs/TinyC3_quads3.txt Test_Outputs/TinyC3_quads4.txt Test_Outputs/TinyC3_quads5.txt