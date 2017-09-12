/**     parse.h: This file handles command parsing
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

#ifndef ED_PARSING
#define ED_PARSING

#include <stddef.h>

enum ed_commands {
        ED_APPEND,                      /* (.)a */
        ED_CHANGE,                      /* (.,.)c */
        ED_DELETE,                      /* (.,.)d */
        ED_EDIT,                        /* e file */
        ED_FORCE_EDIT,                  /* E file */
        ED_FILENAME,                    /* f file */
        ED_GLOBAL,                      /* (1,$)g/re/command-list */
        ED_INTERACTIVE_GLOBAL,          /* (1,$)G/re/ */
        ED_LAST_ERROR,                  /* h */
        ED_ERROR_TOGGLE,                /* H */
        ED_INSERT,                      /* (.)i */
        ED_JOIN,                        /* (.,.+1)j */
        ED_MARK,                        /* (.)kx */
        ED_LIST,                        /* (.,.)l */
        ED_MOVE,                        /* (.,.)m(.) */
        ED_NUMBER,                      /* (.,.)n */
        ED_PRINT,                       /* (.,.)p */
        ED_PROMPT_TOGGLE,               /* P */
        ED_QUIT,                        /* q */
        ED_FORCE_QUIT,                  /* Q */
        ED_READ,                        /* ($)r file */
        ED_SUBSTITUTE,                  /* (.,.)s/re/replacement/ */
        ED_COPY,                        /* (.,.)t(.) */
        ED_UNDO,                        /* u */
        ED_NOTGLOBAL,                   /* (1,$)v/re/command-list */
        ED_INTERACTIVE_NOTGLOBAL,       /* (1,$)v/re/ */
        ED_WRITE,                       /* (1,$)w file */
        ED_WRITE_QUIT,                  /* (1,$)wq file */
        ED_WRITE_APPEND,                /* (1,$)W file */
        ED_PASTE,                       /* (.)x */
        ED_YANK,                        /* (.,.)y */
        ED_SCROLL,                      /* (.+1)zn */
        ED_SHELL,                       /* !command */
        ED_COMMENT,                     /* (.,.)# */
        ED_LINE,                        /* ($)= */
        ED_NONE                         /* (.+1)<newline> */
};

struct command {
        size_t address1; /* first address */
        size_t address2; /* second address */
        enum ed_commands command; /* command */
        size_t target; /* target address */
        char *regex; /* regex */
        char *other; /* command-list for global and notglobal, replacement 
                      * for substitution, or command for shell invocation */
}; /* struct for parsed command */

struct command ed_parse(char *);

#endif
