/**
 * \file parse_events.l
 *
 * Copyright 2011 Dale Frampton and Kurtis Nusbaum
 * 
 * This file is part of cimunit.
 * 
 * cimunit is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 * 
 * cimunit is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with cimunit.  If not, see <http://www.gnu.org/licenses/>.
 */

%{
#include <stdio.h>
#include <string.h>
#include "parse_events_grammar.h"
%}

%option prefix="parse_events_"

%%
[ \t]+                  /* ignore whitespace */;

\n              return SYMBOL_EOL;
,               return SYMBOL_COMMA;
->              return SYMBOL_IMPLIES;
\(              return SYMBOL_LPAREN;
\)              return SYMBOL_RPAREN;
&&              return SYMBOL_AND;
\|\|            return SYMBOL_OR;
\[              return SYMBOL_LBRACKET;
\]              return SYMBOL_RBRACKET;
@               return SYMBOL_AT;

[a-zA-Z0-9_:/]+		{char *temp_str=malloc(strlen(yytext)+1);strcpy(temp_str, yytext);parse_events_lval.string=temp_str;return NAME;}

%%
