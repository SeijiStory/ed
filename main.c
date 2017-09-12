
/**     main.c: This file contains the user interface for the editor
 *      Copyright (C) 2017  Seiji Story
 *
 *      This program is free software: you can redistribute it and/or modify
 *      it under the terms of the GNU General Public License as published by
 *      the Free Software Foundation, either version 3 of the License, or
 *      (at your option) any later version.
 *
 *      This program is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *      GNU General Public License for more details.
 *
 *      You should have received a copy of the GNU General Public License
 *      along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h> /* For file operations */
#include <stdlib.h>
#include <string.h>
#include <unistd.h> /* For getopt() */


int main(int argc, char **argv)
{
        /* PROGRAM CONSTANTS */
        const char *VERSION = "0.1a"; /* program version */
        const char *options = "hVlp:sv"; /* valid program options */

        /* PROGRAM VARIABLES */

        /* Flags */
        volatile char loose = 0; /* always return zero? */
        char *prompt = NULL; /* prompt message */
        volatile char silent = 0; /* suppress messages? */
        volatile char verbose = 0; /* verbose enabled? */

        /* Running Variables */
        size_t address = 0; /* current line address to work with */
        char *defaultfname = NULL; /* the default file name */
        char *yankbuf = NULL; /* yank buffer */

        /* FILE VARIABLES */
        const char open = 0; /* file currently open? */
        char *filebuf; /* store open file */
        int opt; /* getting arguments */


        while ((opt = getopt(argc, argv, options)) > -1) {
                size_t n;
                switch (opt) {
                case 'h':
                        printf( "Ed - The line editor.\n\n"
                                "Usage: ed [options] [file]\n\n"
                                "Options:\n"
                                "\t-h\t\t\tdisplay this help and exit\n"
                                "\t-V\t\t\toutput version information and "
                                "exit\n"
                                "\t-l\t\t\texit with 0 status even if a "
                                "command fails\n"
                                "\t-p [STR]\t\t\tuse STR as an interactive "
                                "prompt\n"
                                "\t-s\t\t\tsuppress diagnostics, byte counts, "
                                "and \'!\' prompt\n"
                                "\t-v\t\t\tbe verbose; equivalent to the \'H\' "
                                "command\n"
                                "Start edit by reading in 'file' if given.\n"
                                "If \'file\' begins with a \'!\', reading "
                                "output of shell command.\n\n"
                                "Exit status:\n"
                                "\t0 for a normal exit\n"
                                "\t1 for environmental problems (file not "
                                "found, invalid flags, I/O/ errors,\n\t  "
                                "etc.)\n"
                                "\t2 to indicate a corrupt of invalid input "
                                "file\n"
                                "\t3 for an internal consistency error (eg: "
                                "bug) which caused ed to panic.\n" );
                        break;
                case 'V':
                        printf( "ed %s\n"
                                "Copyright (C) 2017 Seiji Story.\nLicense "
                                "GPLv3+: GNU GPL version 3 or later "
                                "<http://gnu.org/licenses/gpl.html>\nThis is "
                                "free software: you are free to change and "
                                "redistribute it.\nThere is NO WARRANTY, to "
                                "the extent permitted by law.\n", VERSION );
                        break;
                case 'l':
                        loose = 1;
                        break;
                case 'p':
                        n = strlen(optarg) + 1;
                        prompt = malloc(n);
                        strncpy(prompt, optarg, n);
                        break;
                case 's':
                        silent = 1;
                        break;
                case 'v':
                        verbose = 1;
                        break;
                default:
                        printf( "ed: invalid option -- \'%c\'\n"
                                "Try \'ed -h\' for more information.\n" );
                        exit(1);
                }
        }
}
