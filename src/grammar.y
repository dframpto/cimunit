%{
#include <stdio.h>
#include <string.h>

#include "cimunit_event_list.h"

void yyerror(const char *str)
{
	fprintf(stderr,"error: %s\n",str);
}

int yywrap()
{
	return 1;
}

cimunit_event_list_t *g_grammar_event_list = NULL;
cimunit_event_list_t *g_grammar_condition_list = NULL;

void printConditionsForActionEvent(cimunit_event_t *event) {
    printf("%s has the following actions that wait on it\n", event->event_name);
    
    cimunit_event_list_t *action_list = event->action_events;
    if (!action_list) {
        printf("\tnone\n");
    } else {
        while(action_list) {
            printf("\t%s\n", action_list->event->event_name);
            action_list = action_list->next;
        }
    }
}


main()
{
    cimunit_event_list_init(&g_grammar_event_list);
    cimunit_event_list_init(&g_grammar_condition_list);
	yyparse();
	
	printf("Print the schedule\n");
	cimunit_event_list_t *condition_list = g_grammar_event_list;
	while(condition_list != NULL) {
	    printConditionsForActionEvent(condition_list->event);
	    condition_list = condition_list->next;
	}
}

char *heater="default";

%}

%token SYMBOL_COMMA SYMBOL_IMPLIES SYMBOL_EOL SYMBOL_LPAREN SYMBOL_RPAREN SYMBOL_AND
       SYMBOL_OR SYMBOL_LBRACKET SYMBOL_RBRACKET

%union 
{
	int number;
	char *string;
	struct cimunit_event_list *conditionList;
	struct cimunit_event *event;
}

/* %define api.pure */

%token <number> STATE
%token <number> NUMBER
%token <string> EVENT_NAME

%type <string> basicEvent blockEvent
%type <conditionList> condition basicCondition
// %type <event> basicEvent

%start schedules

%%

schedules:
    | schedules schedule SYMBOL_EOL
    | schedules schedule SYMBOL_COMMA

schedule:
    ordering

ordering:
    condition SYMBOL_IMPLIES basicEvent
    {
        cimunit_event_list_t *condition = $1;
        cimunit_event_t *action_event =
          cimunit_event_list_find(g_grammar_event_list, $3);
        if (!action_event) {
            yyerror("Unable to find action event");
            YYERROR;
        }
        
        
        while(condition != NULL) {
            cimunit_event_add_action(condition->event, action_event);
            condition = condition->next;
        }
        
        cimunit_event_list_destroy(&$1);
    }
    ;

basicEvent:
    EVENT_NAME
    {
        $$ = $1;
        
        if (!cimunit_event_list_find(g_grammar_event_list, $1)) {
            cimunit_event_t *new_event = cimunit_event_init($1);
            cimunit_event_list_add(&g_grammar_event_list, new_event);
        }
    }
    ;

blockEvent:
    SYMBOL_LBRACKET basicEvent SYMBOL_RBRACKET
    {
        $$ = $2;
    }
    ;

basicCondition:
    basicEvent
    {
        cimunit_event_t *condition_event =
          cimunit_event_list_find(g_grammar_event_list, $1);

        if (condition_event) {
            cimunit_event_list_t *new_condition = cimunit_event_list_init();
            cimunit_event_list_add(&new_condition, condition_event);
            $$ = new_condition;
        }
    }
    | blockEvent
    {
        $$ = NULL;
        yyerror("Blocking events are not supported");
        YYERROR;
    }

condition:
    basicCondition
    {
        $$ = $1;
    }
    | condition SYMBOL_OR basicCondition
    {
        cimunit_event_list_t *lhs = $1;
        cimunit_event_list_t *rhs = $3;
        cimunit_event_list_union(&lhs, rhs);
        cimunit_event_list_destroy(&rhs);
        $$ = lhs;
    }
    | condition SYMBOL_AND basicCondition
    {
        cimunit_event_list_t *lhs = $1;
        cimunit_event_list_t *rhs = $3;
        cimunit_event_list_union(&lhs, rhs);
        cimunit_event_list_destroy(&rhs);
        $$ = lhs;
    }
    | SYMBOL_LPAREN condition SYMBOL_RPAREN
    {
        $$ = $2;
    }
    ;
