/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison interface for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2011 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     FZ_INT_CONST = 258,
     FZ_BOOL_CONST = 259,
     FZ_FLOAT_CONST = 260,
     FZ_STRING_CONST = 261,
     FZ_ID = 262,
     FZ_U_ID = 263,
     FZ_ANNOTATION = 264,
     FZ_ANY = 265,
     FZ_ARRAY = 266,
     FZ_BOOL = 267,
     FZ_CASE = 268,
     FZ_COLONCOLON = 269,
     FZ_CONSTRAINT = 270,
     FZ_DIFF = 271,
     FZ_DIV = 272,
     FZ_DOTDOT = 273,
     FZ_ELSE = 274,
     FZ_ELSEIF = 275,
     FZ_ENDIF = 276,
     FZ_ENUM = 277,
     FZ_FLOAT = 278,
     FZ_FUNCTION = 279,
     FZ_IF = 280,
     FZ_IN = 281,
     FZ_INCLUDE = 282,
     FZ_INT = 283,
     FZ_INTERSECT = 284,
     FZ_LET = 285,
     FZ_LIST = 286,
     FZ_MAXIMIZE = 287,
     FZ_MINIMIZE = 288,
     FZ_MOD = 289,
     FZ_NOT = 290,
     FZ_OF = 291,
     FZ_SATISFY = 292,
     FZ_SUBSET = 293,
     FZ_SUPERSET = 294,
     FZ_OUTPUT = 295,
     FZ_PAR = 296,
     FZ_PREDICATE = 297,
     FZ_RECORD = 298,
     FZ_SEMICOLON = 299,
     FZ_SET = 300,
     FZ_SHOW = 301,
     FZ_SHOWCOND = 302,
     FZ_SOLVE = 303,
     FZ_STRING = 304,
     FZ_SYMDIFF = 305,
     FZ_TEST = 306,
     FZ_THEN = 307,
     FZ_TUPLE = 308,
     FZ_TYPE = 309,
     FZ_UNION = 310,
     FZ_VARIANT_RECORD = 311,
     FZ_VAR = 312,
     FZ_WHERE = 313,
     FZ_XOR = 314
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 2068 of yacc.c  */
#line 156 "parser.yxx"
 bool bValue; double dValue; int iValue; char* sValue;
	std::string*                              stValue;
	emu::b1<kangaroo::Int,xmm>*          		iPair;
	emu::b1<kangaroo::Flt,xmm>*          		fPair;
	emu::b1<kangaroo::Int,xmm>*          		iList;
	FlatZinc::ExprSpec*                       exprSpec;
	FlatZinc::TypeSpec*                       typeSpec;
	FlatZinc::AnnSpec*                        annSpec;
	FlatZinc::Annotations*                    anns;



/* Line 2068 of yacc.c  */
#line 122 "parser.tab.hpp"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif




