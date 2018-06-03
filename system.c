/* Cydia - iPhone UIKit Front-End for Debian APT
 * Copyright (C) 2008-2015  Jay Freeman (saurik)
*/

/* GNU General Public License, Version 3 {{{ */
/*
 * Cydia is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published
 * by the Free Software Foundation, either version 3 of the License,
 * or (at your option) any later version.
 *
 * Cydia is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Cydia.  If not, see <http://www.gnu.org/licenses/>.
**/

/*
 * Copyright (C) 2018 Arthur Chaloin
*/

int __system__(char const* command) {
	pid_t childpid = fork();

	if (childpid < 0) {
		fprintf(stderr, "fork failed during substitued _system() call\n");
		return -1;
	} else if (!childpid) {
		int err;

		printf("bye\n");
		if ((err = execv("/bin/bash", (char* []) {"/bin/sh", "-c", (char*)command, NULL}))) {
			fprintf(stderr, "execv returned an non-zero exit code: %d\n", err);
			exit(err);
		}
	}

	int childProcessStatus = 0;
	waitpid(childpid, &childProcessStatus, 0);
	return WEXITSTATUS(childProcessStatus);
}