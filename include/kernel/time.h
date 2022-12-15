// SPDX-FileCopyrightText: CGL-KFS
// SPDX-License-Identifier: BSD-3-Clause

/* include/kernel/time.h
 *
 * Time relative functions
 *
 * created: 2022/12/14 - xlmod <glafond-@student.42.fr>
 * updated: 2022/12/15 - glafond- <glafond-@student.42.fr>
 */

#ifndef TIME_T
#define TIME_T

#include <stdint.h>

typedef uint32_t time_t;

/*
 * Sleep at least ms millisecond
 */
void sleep(uint32_t ms);

/*
 * Return the time since the kernel start in millisecond
 */
uint32_t gettime();

#endif
