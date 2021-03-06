/**
 * \file parse_events.y
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
#include <stdlib.h>
#include <string.h>

#include "cimunit_platform.h"
#include "cimunit_event_list.h"
#include "cimunit_event_table.h"
#include "cimunit_schedule.h"


// Defines
extern int parse_events_lex_destroy(void); // From parse_events.l
extern int parse_events_parse(struct cimunit_event_table *fired_event_list,
                              const char *action_event,
                              const char *thread,
                              BOOL *parse_result); // From parse_events.y
extern void parse_events__scan_string(char *string); // From parse_events.l
extern int parse_events_lex (void); // From parse_events.l


/// Display errors to the terminal
///
/// \param event_list - event list passed to the parser
/// \param str - error string
void parse_events_error(struct cimunit_event_table *fired_event_list,
                        const char *action_event, const char *thread,
                        BOOL *parse_result, const char *str)
{
	fprintf(stderr,"error: %s\n",str);
}


/// Indicate there is no more input after the EOF.
int parse_events_wrap()
{
	return 1;
}


cimunit_mutex_t *cimunit_parse_event_mutex = NULL;

/// Build a schedule
///
/// \return the completed schedule
BOOL cimunit_schedule_parse_runtime(cimunit_schedule_t *schedule,
                                    const char *action_event,
                                    const char *thread) {
    BOOL result = FALSE;

    /// \todo This is a hack.  There should be an init function that initializes
    ///       this global in a thread safe manner.
    if (!cimunit_parse_event_mutex) {
        cimunit_parse_event_mutex = malloc(sizeof(cimunit_mutex_t));
        cimunit_mutex_init(cimunit_parse_event_mutex, NULL);
    }


    // Parse the schedule string to determine if the action event is unblocked
    cimunit_mutex_lock(cimunit_parse_event_mutex);   
    parse_events_lex_destroy();
    parse_events__scan_string(schedule->schedule_string);
    parse_events_parse(&schedule->fired_event_list, action_event, thread, &result);
    cimunit_mutex_unlock(cimunit_parse_event_mutex);   
    
    return result;
}

%}

%token SYMBOL_COMMA SYMBOL_IMPLIES SYMBOL_EOL SYMBOL_LPAREN SYMBOL_RPAREN SYMBOL_AND
       SYMBOL_OR SYMBOL_LBRACKET SYMBOL_RBRACKET SYMBOL_AT

%union 
{
	int bool_value;
	char *string;
}

%name-prefix "parse_events_"

%parse-param {struct cimunit_event_table *fired_event_list}
%parse-param {const char *action_event}
%parse-param {const char *thread}
%parse-param {BOOL *parse_result}

%token <number> STATE
%token <number> NUMBER
%token <string> NAME

%type <bool_value> basicEvent
%type <bool_value> basicCondition
%type <bool_value> condition


%start schedules

%%

schedules:
    | schedule
    | schedules SYMBOL_COMMA schedule

schedule:
    ordering

ordering:
    condition SYMBOL_IMPLIES NAME
    {
        if (!strcmp($3, action_event)) {
            *parse_result = $1;
        }
        free($3);
    }
    | condition SYMBOL_IMPLIES NAME SYMBOL_AT NAME
    {
        if (!strcmp($3, action_event) &&
            !strcmp($5, thread)) {
            *parse_result = $1;
        }
        free($3);
        free($5);
    }
    ;

basicEvent:
    NAME
    {
        // Lookup event name in the fired event list
        cimunit_event_table_entry_t *event = NULL;
        cimunit_find_event_in_table(fired_event_list, $1, &event);
        free($1);
        $$ = (NULL != event);
    }
    | NAME SYMBOL_AT NAME{
        // Lookup event name in the fired event list
        cimunit_event_table_entry_t *event = NULL;
        cimunit_find_event_in_table_on_thread(
          fired_event_list, $1, $3, &event);
        free($1);
        free($3);
        $$ = (NULL != event);
    }
    ;

blockEvent:
    SYMBOL_LBRACKET basicEvent SYMBOL_RBRACKET
    {
    }
    ;

basicCondition:
    basicEvent
    {
        $$ = $1;
    }
    | blockEvent
    {
        yyerror(fired_event_list, thread, action_event, parse_result,
                "Blocking events are not supported");
        YYERROR;
    }

condition:
    basicCondition
    {
        $$ = $1;
    }
    | condition SYMBOL_OR basicCondition
    {
        $$ = $1 || $3;
    }
    | condition SYMBOL_AND basicCondition
    {
        $$ = $1 && $3;
    }
    | SYMBOL_LPAREN condition SYMBOL_RPAREN
    {
        $$ = $2;
    }
    ;
