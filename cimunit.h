#ifdef CIMUNIT_H
#define CIMUNIT_H
#include "cimunit_mutex.h"
#include "cimunit_tester.h"

/** \name Cimunit Typedefs */
//@{

/** \brief Type indicating an amount of threads */

typedef CIMUNIT_THREAD pthread_t;

typedef struct{
  cimunit_schedule *schedule;
  CIMUNIT_THREAD thread;
} cimunit_test_args;

//@}

/** \name Cimunit Functions */
//@{

int cimunit_run_tests(cimunit_tester *tester);

int cimunit_fire_event(cimunit_schedule *schedule, const char* event);

//@}

/** \name Cimunit Helper Macros */
//@{

#define CIMUNIT_TEST(TEST_GROUP, TEST_NAME) \
##TEST_GROUP##_##TEST_NAME##_Cimunit_Test( \
  void *args) 

#define CIMUNIT_FIRE_EVENT(EVENT) \
  cimunit_fire_event(((*cimunit_test_args)args)->schedule, EVENT);


#define CIMUNIT_ADD_TEST_SCHEDULE(TESTER, TEST_GROUP, TEST_NAME, SCHEDULE) \
  cimunit_add_test(&TESTER,##TEST_GROUP##_##TEST_NAME##_Cimunit_Test, SCHEDULE);

#define CIMUNIT_TNUMBER \
  ((cimunit_test_args*)args)->thread
//@}

#endif //CIMUNIT_H
