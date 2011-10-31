/*
 * \file test_cimunit_event.c
 *
 * Copyright 2011 Dale Frampton
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

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "CUnit.h"

#include "cimunit_event.h"
#include "cimunit_event_list.h"

static void test_cimunit_init_event(void)
{
    char event_name[] = "test";

    cimunit_event_t event;
    cimunit_event_init(&event, event_name);
  
    /// - Verify the event name is initialized
    CU_ASSERT_PTR_NOT_NULL(event.event_name);
    CU_ASSERT_STRING_EQUAL(event.event_name, event_name);
    
    CU_ASSERT_FALSE(event.is_action);
  
    /// - No cross platform tests for mutex configuration
  
    /// - Verify the dependent events list is empty
    CU_ASSERT_PTR_NULL(event.action_events);
  
    cimunit_event_destroy(&event);
}


static void test_cimunit_event_add_action(void)
{
    cimunit_event_t condition;
    cimunit_event_init(&condition, "condition");
    cimunit_event_t action;
    cimunit_event_init(&action, "action");
  
    /// - Run SUT
    cimunit_event_add_action(&condition, &action);
  
    /// - Verify the action is in the list
    CU_ASSERT_PTR_NOT_NULL(condition.action_events);
    CU_ASSERT_PTR_NOT_NULL(cimunit_event_list_find(condition.action_events,
                                                   action.event_name));
                        
    /// - Verify the action event is listed as an action event
    CU_ASSERT_TRUE(action.is_action);

    /// - Clean up
    cimunit_event_destroy(&condition);
    cimunit_event_destroy(&action);
}


static void test_cimunit_event_add_multiple_actions(void)
{
    cimunit_event_t condition;
    cimunit_event_init(&condition, "condition");
    cimunit_event_t action1;
    cimunit_event_init(&action1, "action1");
    cimunit_event_t action2;
    cimunit_event_init(&action2, "action2");
    cimunit_event_add_action(&condition, &action1);
  
    /// - Run SUT
    cimunit_event_add_action(&condition, &action2);

    /// - Verify both items are in the list
    CU_ASSERT_PTR_NOT_NULL(cimunit_event_list_find(condition.action_events,
                                                   action1.event_name));
    CU_ASSERT_PTR_NOT_NULL(cimunit_event_list_find(condition.action_events,
                                                   action2.event_name));

    /// - Clean up
    cimunit_event_destroy(&condition);
    cimunit_event_destroy(&action1);
    cimunit_event_destroy(&action2);
}


static void test_cimunit_event_fire(void)
{
    cimunit_event_t condition;
    cimunit_event_init(&condition, "condition");
    cimunit_event_t action;
    cimunit_event_init(&action, "action");
  
    /// - Run SUT
    cimunit_event_add_action(&condition, &action);

    cimunit_event_fire(&condition);
    cimunit_event_fire(&action);

    cimunit_event_destroy(&condition); 
    cimunit_event_destroy(&action); 
}

static cimunit_event_t event_multiply_before;
static cimunit_event_t event_multiply_after;
static void *op_multiply(void *value)
{
    int *my_value = (int *)value;

    cimunit_event_fire(&event_multiply_before);
    *my_value *= 2;
    cimunit_event_fire(&event_multiply_after);
    
    pthread_exit(NULL);
}

static cimunit_event_t event_add_before;
static cimunit_event_t event_add_after;
static void *op_add(void *value)
{
    int *my_value = (int *)value;
    
    cimunit_event_fire(&event_add_before);
    *my_value += 1;
    cimunit_event_fire(&event_add_after);
    
    pthread_exit(NULL);
}


static void test_cimunit_event_fire_add_before_mult(void)
{
    int value = 0;
    int *value_ptr = &value;
    
    cimunit_event_init(&event_add_before, "add_before");
    cimunit_event_init(&event_add_after, "add_after");
    cimunit_event_init(&event_multiply_before, "multiply_before");
    cimunit_event_init(&event_multiply_after, "multiply_after");  

    pthread_t add_thread;
    pthread_t mult_thread;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);    

    /// - Run SUT
    cimunit_event_add_action(&event_add_after, &event_multiply_before);
    pthread_create(&mult_thread, &attr, op_multiply, value_ptr);
    pthread_create(&add_thread, &attr, op_add, value_ptr);
    pthread_join(mult_thread, NULL);
    pthread_join(add_thread, NULL);

    CU_ASSERT_EQUAL(value, 2);

    cimunit_event_destroy(&event_add_before);
    cimunit_event_destroy(&event_add_after);
    cimunit_event_destroy(&event_multiply_before);
    cimunit_event_destroy(&event_multiply_after);
}


static void test_cimunit_event_fire_mult_before_add(void)
{
    int value = 0;
    int *value_ptr = &value;
    
    cimunit_event_init(&event_add_before, "add_before");
    cimunit_event_init(&event_add_after, "add_after");
    cimunit_event_init(&event_multiply_before, "multiply_before");
    cimunit_event_init(&event_multiply_after, "multiply_after");  

    pthread_t add_thread;
    pthread_t mult_thread;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);    

    /// - Run SUT
    cimunit_event_add_action(&event_multiply_after, &event_add_before);
    pthread_create(&mult_thread, &attr, op_multiply, value_ptr);
    pthread_create(&add_thread, &attr, op_add, value_ptr);
    pthread_join(mult_thread, NULL);
    pthread_join(add_thread, NULL);

    CU_ASSERT_EQUAL(value, 1);

    cimunit_event_destroy(&event_add_before);
    cimunit_event_destroy(&event_add_after);
    cimunit_event_destroy(&event_multiply_before);
    cimunit_event_destroy(&event_multiply_after);

}


static CU_TestInfo tests_cimunit_event[] = {
  {"init", test_cimunit_init_event },
  {"add_action", test_cimunit_event_add_action},
  {"add_multiple_actions", test_cimunit_event_add_multiple_actions},
  {"fire", test_cimunit_event_fire},
  {"fire_add_before_mult", test_cimunit_event_fire_add_before_mult},
  {"fire_mult_before_add", test_cimunit_event_fire_mult_before_add},
  CU_TEST_INFO_NULL,
};


static CU_SuiteInfo suites[] = {
  {"suite_cimunit_event", NULL, NULL, tests_cimunit_event},
  CU_SUITE_INFO_NULL,
};

void AddEventTests(void)
{
  assert(NULL != CU_get_registry());
  assert(!CU_is_test_running());

	/* Register suites. */
	if (CU_register_suites(suites) != CUE_SUCCESS) {
		fprintf(stderr, "suite registration failed - %s\n",
			CU_get_error_msg());
		exit(EXIT_FAILURE);
	}
}

