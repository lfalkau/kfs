// SPDX-FileCopyrightText: CGL-KFS
// SPDX-License-Identifier: BSD-3-Clause

/* include/kernel/nsh.h
 *
 * Insert file description here
 *
 * created: 2022/12/08 - xlmod <glafond-@student.42.fr>
 * updated: 2022/12/08 - xlmod <glafond-@student.42.fr>
 */


#ifndef NSH_H
#define NSH_H

#define NSH_BUFSIZE 1024

struct builtin {
	char *name;
	int (*exec)(int ,char **);
};

void nsh();

#endif