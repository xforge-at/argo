/*
 * @APPLE_APACHE_LICENSE_HEADER_START@
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * 
 * @APPLE_APACHE_LICENSE_HEADER_END@
 */


#ifndef __DISPATCH_TESTS_SHIMS_FGETLN__
#define __DISPATCH_TESTS_SHIMS_FGETLN__

#if !HAVE_FGETLN
#include <stdio.h>

char *fgetln(FILE *stream, size_t *len);
#endif

#endif /* __DISPATCH_TESTS_SHIMS_FGETLN__ */
