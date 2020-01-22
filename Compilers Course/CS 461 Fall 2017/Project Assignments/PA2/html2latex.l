/*
	Samuel Leonard
	sleonar5
	CS461
	Lab 2
*/

%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int list_type;
%}

%option       noyywrap nounput yylineno
%x            COMMENT PARA PRE OL UL LI

%%

"<h1>"[^<]*"</h1>" {
    /**************************************************************************
     * Matched an HTML H1 header so print it out as a LateX section title.
     * The beginning and ending tags need to be stripped off before the
     * title can be formatted in LateX.
     *************************************************************************/
    yytext[yyleng-5] = 0;
    printf( "\\section{%s}", yytext+4 );
}

"<h2>"[^<]*"</h2>" {
    /**************************************************************************
     * Matched an HTML H2 header so print it out as a LateX section title.
     * The beginning and ending tags need to be stripped off before the
     * title can be formatted in LateX.
     *************************************************************************/
    yytext[yyleng-5] = 0;
    printf( "\\subsection{%s}", yytext+4 );
}

"<h3>"[^<]*"</h3>" {
    /**************************************************************************
     * Matched an HTML H3 header so print it out as a LateX section title.
     * The beginning and ending tags need to be stripped off before the
     * title can be formatted in LateX.
     *************************************************************************/
    yytext[yyleng-5] = 0;
    printf( "\\subsubsection{%s}", yytext+4 );
}

"<!--" {
    /**************************************************************************
     * Matched an HTML comment so print it out as a LateX comment. The
     * beginning and ending tags are stripped off before the LateX comment
     * is emitted.
     *************************************************************************/
    printf( "%% " );
    BEGIN COMMENT;
}

[ \t\n\r]+ {
    /**************************************************************************
     * Matched some whitespace that is not inside of an HTML tag. We
     * just ignore the whitespace.
     *************************************************************************/
}

. {
    /**************************************************************************
     * Matched something that we did not expect to see. Issue an error and
     * exit the program with a failure code.
     *************************************************************************/
    fprintf( stderr, "Unexpected input at line %d: '%s'\n", yylineno, yytext );
    exit( 1 );
}

<COMMENT>"-->" {
    /**************************************************************************
     * Matched an HTML end comment while parsing an HTML comment. Print out
     * a new line and resume normal parsing.
     *************************************************************************/
    printf( "\n" );
    BEGIN 0;
}

<COMMENT>[\n](\r)? {
    /**************************************************************************
     * Matched a newline while parsing an HTML comment. Print out a new
     * line making sure to mark the next line as a comment as well.
     *************************************************************************/
    printf( "\n%% " );
}

<COMMENT>[ \t] {
    /**************************************************************************
     * Matched some white space while parsing an HTML comment. Print out
     * the white space as is.
     *************************************************************************/
    printf( "%s", yytext );
}

<COMMENT>. {
    /**************************************************************************
     * Matched any other text while parsing an HTML comment. Print out
     * the text as is.
     *************************************************************************/
    printf( "%s", yytext );
}

"<p>" {
    /**************************************************************************
     * Matched an HTML p tag to print out the string in LaTeX.
     * The beginning and ending tags need to be stripped off before the
     * string can be formatted in LateX. Stripping and printing was already 
		 * defined.
     *************************************************************************/
		BEGIN PARA;
}

<PARA>"</p>" {
		/**************************************************************************
     * Matched an HTML p closing tag. The beginning and ending tags need to 
		 * be stripped off before the string can be formatted in LateX. Stripping 
		 * and printing was already defined.
     *************************************************************************/
		BEGIN 0;
		printf("\n\n");
}

"<pre>"[^<]*"</pre>" {
    /**************************************************************************
     * Matched an HTML pre header and prints the preformatted text.
     * The beginning and ending tags need to be stripped off before the
     * string can be formatted in LateX.
     *************************************************************************/
		BEGIN PRE;
    yytext[yyleng-6] = 0;
    printf( "\\begin{verbatim}%s\\end{verbatim}\n", yytext+5 );
		BEGIN 0;
}

"<ul>" {
    /**************************************************************************
     * Matched an HTML ul header so print it out as a LateX uordered list.
     * The beginning and ending tags need to be stripped off before the
     * title can be formatted in LateX.
     *************************************************************************/
		BEGIN UL;
		list_type = 0;
		printf("\\begin{itemize}");
}

<UL>"</ul>" {
    /**************************************************************************
     * Matched an HTML ul closing header and print the end list statement.
     * The beginning and ending tags need to be stripped off before the
     * title can be formatted in LateX.
     *************************************************************************/
		printf("\\end{itemize}\n");
		BEGIN 0;
}

"<ol>" {
    /**************************************************************************
     * Matched an HTML ol header so print it out as a LateX ordered list.
     * The beginning and ending tags need to be stripped off before the
     * title can be formatted in LateX.
     *************************************************************************/
		BEGIN OL;
		list_type = 1;
		printf("\\begin{enumerate}");
}

<OL>"</ol>" {
    /**************************************************************************
     * Matched an HTML ol closing header and print the end list statement.
     * The beginning and ending tags need to be stripped off before the
     * title can be formatted in LateX.
     *************************************************************************/
    printf("\\end{enumerate}\n");
		BEGIN 0;
}

<UL,OL>"<li>" {
		/**************************************************************************
		 * Matched an HTML li opening tag and print the listed item.
		 * The beginning and ending tags need to be stripped off before the
		 * list string can be formatted in LateX.
		 *************************************************************************/
		BEGIN LI;
		printf("\\item ");
}

<LI>"</li>" {
		/**************************************************************************
		 * Matched an HTML li closing tag and return to the proper list type.
		 * The beginning and ending tags need to be stripped off before the
		 * being formatted in LateX.
		 *************************************************************************/
		if(list_type == 0){
			BEGIN UL;
		}
		else{
			BEGIN OL;
		}
		printf("\n");
}

<PARA,LI>"<big>"[^<]*"</big>" {
		/**************************************************************************
		 * Matched an HTML big style tag so to print in large font.
		 * The beginning and ending tags need to be stripped off before it can be
		 * formatted in LateX.
		 *************************************************************************/
		yytext[yyleng-6] = 0;
		printf("\{\\Large %s}", yytext+5);
}

<PARA,LI>"<small>"[^<]*"</small>" {
		/**************************************************************************
		 * Matched an HTML small style tag so to print in small font.
		 * The beginning and ending tags need to be stripped off before it can be
		 * formatted in LateX.
		 *************************************************************************/
		yytext[yyleng-8] = 0;
		printf("\{\\scriptsize %s}", yytext+7);
}

<PARA,LI>"<b>"[^<]*"</b>" {
		/**************************************************************************
		 * Matched an HTML b style tag so to print in bold font.
		 * The beginning and ending tags need to be stripped off before it can be
		 * formatted in LateX.
		 *************************************************************************/
		yytext[yyleng-4] = 0;
		printf("\\textbf\{%s}", yytext+3);
}

<PARA,LI>"<i>"[^<]*"</i>" {
		/**************************************************************************
		 * Matched an HTML i style tag so to print in italic font.
		 * The beginning and ending tags need to be stripped off before it can be
		 * formatted in LateX.
		 *************************************************************************/
		yytext[yyleng-4] = 0;
		printf("\\textit\{%s}", yytext+3);
}

<PARA,LI>"<strong>"[^<]*"</strong>" {
		/**************************************************************************
		 * Matched an HTML strong style tag so to print in strong font.
		 * The beginning and ending tags need to be stripped off before it can be
		 * formatted in LateX.
		 *************************************************************************/
		yytext[yyleng-9] = 0;
		printf("\\textmd\{%s}", yytext+8);
}

<PARA,LI>"<em>"[^<]*"</em>" {
		/**************************************************************************
		 * Matched an HTML em style tag so to print in emphatic font.
		 * The beginning and ending tags need to be stripped off before it can be
		 * formatted in LateX.
		 *************************************************************************/
		yytext[yyleng-5] = 0;
		printf("\\emph\{%s}", yytext+4);
}

<PARA,LI>"<sup>"[^<]*"</sup>" {
		/**************************************************************************
		 * Matched an HTML sup type tag so to print in superscript text.
		 * The beginning and ending tags need to be stripped off before it can be
		 * formatted in LateX.
		 *************************************************************************/
		yytext[yyleng-6] = 0;
		printf("\\textsuperscript\{%s}", yytext+5);
}

<PARA,LI>"<sub>"[^<]*"</sub>" {
		/**************************************************************************
		 * Matched an HTML sub type tag so to print in subscript text.
		 * The beginning and ending tags need to be stripped off before it can be
		 * formatted in LateX.
		 *************************************************************************/
		yytext[yyleng-6] = 0;
		printf("\\textsubscript\{%s}", yytext+5);
}

%%

/**************************************************************************
 * The main function for the HTML to LateX converter. Here we do three
 * things:
 *  1. Print out the LateX document header.
 *  2. Invoke the lexer to print out the LateX document
 *  3. Print out the LateX footer.
 *************************************************************************/
int main( int argc, const char *argv[] ) {
    printf( "\\documentclass[12pt]{article}\n" );
    printf( "\\usepackage{fixltx2e}\n" );
    printf( "\n" );
    printf( "\\setlength{\\parindent}{0.0in}\n" );
    printf( "\\setlength{\\parskip}{0.125in}\n" );
    printf( "\n\n" );
    printf( "\\begin{document}\n" );
    yylex();
    printf( "\\end{document}\n" );
    return 0;
}
