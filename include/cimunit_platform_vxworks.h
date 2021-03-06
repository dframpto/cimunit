/**
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

// Adds #define for BOOL
#include <vxWorks.h>

#ifdef __cplusplus
extern "C" {
#endif
  
#define RESTRICT 

#define CIMUNIT_DEFAULT_THREAD_NAME ""
#define CIMUNIT_MAX_THREAD_NAME_LENGTH 16

#ifdef __cplusplus
}
#endif
