%{
#include "y.tab.h"
%}

digit               [0-9]
nondigit            [a-zA-Z_]
identifier          {nondigit}({nondigit}|{digit})*

integer_constant    {digit}+

escape_sequence     \\[\'\"\?abfnrtv]
c_char              [^\'\\\n]|{escape_sequence}
c_char_sequence     ({c_char})+

character_constant   \'{c_char}\'

digit_sequence      ({digit}+|\'{c_char_sequence}\'{digit}+)
sign                [+-]
fractional_constant ({digit_sequence}?\.{digit_sequence})|({digit_sequence}\.)
exponent_part       ([eE]{sign}?{digit_sequence})
floating_constant   ({fractional_constant}{exponent_part}?|{digit_sequence}{exponent_part})

s_char              [^\"\\\n]|{escape_sequence}
s_char_sequence     {s_char}+
string_literal      \"({s_char_sequence})*\"

comment             \/\*[^*]*\*+([^/*][^*]*\*+)*\/|\/\/[^\n]*\n

%%


"sizeof" {yylval.char_value=strdup(yytext);return SIZEOF;}

"++" {yylval.char_value=strdup(yytext);return D_PLUS;}

"--" {yylval.char_value=strdup(yytext);return D_MINUS;}

"->" {yylval.char_value = strdup(yytext);return ARR_MINUS;}

"<<" {yylval.char_value=strdup(yytext);return D_LST;}

">>" {yylval.char_value=strdup(yytext);return D_GRT;}

"<=" {yylval.char_value=strdup(yytext);return L_EQT;}

">=" {yylval.char_value=strdup(yytext);return G_EQT;}

"==" {yylval.char_value=strdup(yytext);return D_EQT;}

"!=" {yylval.char_value=strdup(yytext);return N_EQT;}

"&&" {yylval.char_value=strdup(yytext);return D_AND;}

"||" {yylval.char_value=strdup(yytext);return D_OR;}

"*=" {yylval.char_value=strdup(yytext);return MUL_EQT;}

"/=" {yylval.char_value=strdup(yytext);return DIV_EQT;}

"%=" {yylval.char_value=strdup(yytext);return PER_EQT;}

"+=" {yylval.char_value=strdup(yytext);return P_EQT;}

"-=" {yylval.char_value=strdup(yytext);return M_EQT;}

"<<=" {yylval.char_value=strdup(yytext);return DL_EQT;}

">>=" {yylval.char_value=strdup(yytext);return DG_EQT;}

"&=" {yylval.char_value=strdup(yytext);return A_EQT;}

"^=" {yylval.char_value=strdup(yytext);return X_EQT;}

"|=" {yylval.char_value=strdup(yytext);return O_EQT;}


"(" {yylval.char_value=strdup(yytext);return LPAREN;}

")" {yylval.char_value=strdup(yytext);return RPAREN;}

"[" {yylval.char_value=strdup(yytext);return LSQRP;}

"]" {yylval.char_value=strdup(yytext);return RSQRP;}

"{" {yylval.char_value=strdup(yytext);return LFPAREN;}

"}" {yylval.char_value=strdup(yytext);return RFPAREN;}

"." {yylval.char_value=strdup(yytext);return DOT;}

">" {yylval.char_value=strdup(yytext);return GRT;}

"<" {yylval.char_value=strdup(yytext);return LST;}

"=" {yylval.char_value=strdup(yytext);return EQT;}


"+" {yylval.char_value=strdup(yytext);return PLUS;}

"-" {yylval.char_value=strdup(yytext);return MINUS;}

"*" {yylval.char_value=strdup(yytext);return MUL;}

"/" {yylval.char_value=strdup(yytext);return DIV;}

"%" {yylval.char_value=strdup(yytext);return PER;}

"," {yylval.char_value=strdup(yytext);return COMMA;}

"&" {yylval.char_value=strdup(yytext);return AND;}

"~" {yylval.char_value=strdup(yytext);return TILDA;}

"!" {yylval.char_value=strdup(yytext);return NOT;}

"^" {yylval.char_value=strdup(yytext);return XOR;}

"|" {yylval.char_value=strdup(yytext);return OR;}

"?" {yylval.char_value=strdup(yytext);return QUES;}

":" {yylval.char_value=strdup(yytext);return COLON;}

";" {yylval.char_value=strdup(yytext);return SEMI_COL;}

"extern" {yylval.char_value=strdup(yytext);return EXTERN;}

"static" {yylval.char_value=strdup(yytext);return STATIC;}

"void" {yylval.char_value=strdup(yytext);return VOID;}

"char" {yylval.char_value=strdup(yytext);return CHAR;}

"short" {yylval.char_value=strdup(yytext);return SHORT;}

"int" {yylval.char_value=strdup(yytext);return INT;}

"long" {yylval.char_value=strdup(yytext);return LONG;}

"float" {yylval.char_value=strdup(yytext);return FLOAT;}

"double" {yylval.char_value=strdup(yytext);return DOUBLE;}

"const" {yylval.char_value=strdup(yytext);return CONST;}

"restrict" {yylval.char_value=strdup(yytext);return RESTRICT;}

"volatile" {yylval.char_value=strdup(yytext);return VOLATILE;}

"inline" {yylval.char_value=strdup(yytext);return INLINE;}

"case" {yylval.char_value=strdup(yytext);return CASE;}

"default" {yylval.char_value=strdup(yytext);return DEFAULT;}

"if" {yylval.char_value=strdup(yytext);return IF;}

"else" {yylval.char_value=strdup(yytext);return ELSE;}

"switch" {yylval.char_value=strdup(yytext);return SWITCH;}

"while" {yylval.char_value=strdup(yytext);return WHILE;}

"do"  {yylval.char_value=strdup(yytext);return DO;}

"for" {yylval.char_value=strdup(yytext);return FOR;}

"goto" {yylval.char_value=strdup(yytext);return GOTO;}

"continue" {yylval.char_value=strdup(yytext);return CONTINUE;}

"break" {yylval.char_value=strdup(yytext);return BREAK;}

"return" {yylval.char_value=strdup(yytext);return RETURN;}

{identifier} {
    yylval.sym_ptr = ST->lookup(yytext);
    return IDENTIFIER;
}

{floating_constant} {
    yylval.char_value=strdup(yytext);
    return FLOAT_CONSTANT;
}

{integer_constant} {
    yylval.int_value=atoi(yytext);
    return INTEGER_CONSTANT;
}

{character_constant} {
    yylval.char_value=strdup(yytext);
    return CHARACTER_CONSTANT;
}

{string_literal} {
    yylval.char_value=strdup(yytext);
    return STR_LTR;
}

{comment} {}

[ \t\n]+ {}

. {}

%%
int yywrap(void) {
    return 1;
}
