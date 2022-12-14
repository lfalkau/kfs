// SPDX-FileCopyrightText: CGL-KFS
// SPDX-License-Identifier: BSD-3-Clause

/* kernel/nsh/builtins/utils.c
 *
 * Insert file description here
 *
 * created: 2022/12/08 - xlmod <glafond-@student.42.fr>
 * updated: 2022/12/14 - glafond- <glafond-@student.42.fr>
 */

#include <kernel/print.h>
#include <kernel/screenbuf.h>
#include <kernel/nsh.h>
#include <kernel/stdlib.h>

extern struct screenbuf sb[];
extern int sb_index;
extern int sb_nbscreen;

extern struct builtin builtin[];

/*
 * Clear screen.
 */
int clear(__attribute__ ((unused)) int argc, __attribute__ ((unused)) char **argv) {
	sb_clear(sb + sb_index);
	return 0;
}

/*
 * Next screen.
 */
int next(__attribute__ ((unused)) int argc, __attribute__ ((unused)) char **argv) {
	sb_unload(sb + sb_index);
	sb_index = (sb_index + 1) % sb_nbscreen;
	sb_load(sb + sb_index);
	return 0;
}

/*
 * Prev screen.
 */
int prev(__attribute__ ((unused)) int argc, __attribute__ ((unused)) char **argv) {
	sb_unload(sb + sb_index);
	sb_index = abs(sb_index - 1) % sb_nbscreen;
	sb_load(sb + sb_index);
	return 0;
}

/*
 * Prints usage and help message.
 */
int help(__attribute__ ((unused)) int argc, __attribute__ ((unused)) char **argv) {
	kprintf("KFS - available commands:\n");
	for (int i = 0; builtin[i].name != NULL ; i++)
		kprintf("-> %s: %s\n", builtin[i].name, builtin[i].description);
	return 0;
}