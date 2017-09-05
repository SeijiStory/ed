
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
#include <unistd.h> /* For getopt() */

int main(int argc, char **argv)
{
        const char *VERSION = "0.1a";
        const char open = 0;
        const char *options = "hVlpsv";
        char *filebuf;
        int opt; /* Getting arguments */
        while ((opt = getopt(argc, argv, options)) > -1) {
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
                                "\t-p[STR]\t\t\tuse STR as an interactive "
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
                        break;
                case 'p':
                        break;
                case 's':
                        break;
                case 'v':
                        break;
                default:
                        break;
                }
        }
}
