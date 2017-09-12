#ifndef ED_COMMANDS
#define ED_COMMANDS

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
