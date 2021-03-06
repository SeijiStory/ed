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

/* HEADERS */
#include <stdio.h> /* for file operations */
#include <stdlib.h>
#include <string.h>
#include <unistd.h> /* for getopt() */
#include "parse.h" /* list of ed commands */

/* PROGRAM CONSTANTS */
#define VERSION "0.1a" /* program version */
#define OPTIONS "hVlp:sv" /* valid launch arguments */
#define CMDBUFLEN 256 /* max length of command; based off of z/OS UNIX System 
                       * Services Command Reference */

/* PROGRAM FLAGS */
volatile char loose = 0; /* always return zero? */
volatile char silent = 0; /* suppress messages? */
volatile char verbose = 0; /* verbose enabled? */

/* STATE VARIABLES */
char running = 1; /* program currently running? */
size_t address = 0; /* current line address to work with */
char *defaultfname = NULL; /* the default file name */
char *prompt = NULL; /* prompt message */
int exitcode = 0;

/* BUFFERS */
char *yankbuf = NULL; /* yank buffer */
char *filebuf; /* store open file */
char commandbuf[CMDBUFLEN];

/* FUNCTIONS */

int main(int argc, char **argv)
{
        int opt; /* getting arguments */
        while ((opt = getopt(argc, argv, OPTIONS)) > -1) {
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
                        exitcode = 0;
                        goto exit;
                        break;
                case 'V':
                        printf( "ed " VERSION "\n"
                                "Copyright (C) 2017 Seiji Story.\nLicense "
                                "GPLv3+: GNU GPL version 3 or later "
                                "<http://gnu.org/licenses/gpl.html>\nThis is "
                                "free software: you are free to change and "
                                "redistribute it.\nThere is NO WARRANTY, to "
                                "the extent permitted by law.\n" );
                        exitcode = 0;
                        goto exit;
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
                        exitcode = 1;
                        goto exit;
                } /* TODO: add -r and -G flag support */
        }
        while (running) {
                if (!prompt) { /* prompt not set */
                        prompt = malloc(1);
                        prompt = "";
                }
                printf(prompt);
                fgets(commandbuf, CMDBUFLEN, stdin);
                ed_parse(commandbuf);
        }
exit:
        /* Clean up */
        free(defaultfname);
        defaultfname = NULL;
        free(prompt);
        prompt = NULL;
        free(yankbuf);
        yankbuf = NULL;
        free(filebuf);
        filebuf = NULL;
        return exitcode;
}
