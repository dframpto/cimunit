/**
 * \file cimunit_event_list.h
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

#ifndef CIMUNIT_EVENT_LIST_H
#define CIMUNIT_EVENT_LIST_H

#ifdef __cplusplus
extern "C" {
#endif
  
/// Forward declaration
struct cimunit_event;
 
/// \addtogroup cimunit_event_list cimunit_event_list Module
/// @{

/// Structure which maintains a list of events.
typedef struct cimunit_event_list {
    /// Pointer to event structure
    struct cimunit_event *event;

    /// Next event in the list
    struct cimunit_event_list *next;
} cimunit_event_list_t;


/// Create a new and empty instance of an event list
///
/// \returns - NULL.  It doesn't do much at this point, perhaps never.
cimunit_event_list_t *cimunit_event_list_init();

/// Cleans up the memory associated with the event list
///
/// \param list - event list to be cleaned up
void cimunit_event_list_destroy(cimunit_event_list_t **list);

/// Add a new event into the list
///
/// \param list - event list to be updated
/// \param event - event to be added into the list
void cimunit_event_list_add(cimunit_event_list_t **list,
                            struct cimunit_event *event);

/// Merge an event list into the list
///
/// The list will be the union of both lists.
///
/// \param list - event list to be merged into
/// \param list2 - event list from which data will be pulled
void cimunit_event_list_union(cimunit_event_list_t **list,
                              cimunit_event_list_t *list2);

/// Gets an event from the list by name and thread
///
/// \param list - event list being queried
/// \param name - name of the event being searched for
/// \param thread - name of the thread associated with the event
/// \return NULL if the event wasn't found, else a pointer to the event.
struct cimunit_event *cimunit_event_list_find_with_thread(
  cimunit_event_list_t *list, const char *name, const char *thread);

/// Gets an event from the list by name
///
/// \param list - event list being queried
/// \param name - name of the event being searched for
/// \return NULL if the event wasn't found, else a pointer to the event.
struct cimunit_event *cimunit_event_list_find(cimunit_event_list_t *list,
                                              const char *name);

/// @}

#ifdef __cplusplus
}
#endif

#endif // CIMUNIT_EVENT_LIST_H
