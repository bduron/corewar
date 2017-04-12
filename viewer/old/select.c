#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <time.h>
#include <sys/select.h>
#include <ncurses.h>

/*  struct to store curses info for cleanup  */

struct curinfo {
    WINDOW * main_window;
    int old_cursor;
};

/*  curses helper functions  */

void start_curses(struct curinfo * info);
void stop_curses(struct curinfo * info);

/*  main function  */

int main(int argc, char * argv[])
{
    /*  Set default timeout  */

    int secs = 0;
    int usecs = 500000;

    /*  Set timeout based on command line args, if provided  */

    if ( argc > 1 ) {
        if ( !strcmp(argv[1], "veryshort") ) {
            secs = 0;
            usecs = 200000;
        }
        else if ( !strcmp(argv[1], "short") ) {
            secs = 1;
            usecs = 0;
        }
        else if ( !strcmp(argv[1], "medium") ) {
            secs = 2;
            usecs = 0;
        }
        else if ( !strcmp(argv[1], "long") ) {
            secs = 5;
            usecs = 0;
        }
    }

    struct curinfo cinfo;
    start_curses(&cinfo);

    int input = '0';        /*  Set to something printable  */
    int num_sel = 0;        /*  Number of times select() has returned  */

    while ( input != 'q' && input != 'Q' ) {

        /*  Output messages  */

        mvprintw(3, 3, "select() has returned %d times", num_sel);
        mvprintw(4, 3, "Last character input was %c", input);
        mvprintw(5, 3, "Press 'q' to quit");
        refresh();

        /*  select() modifies the fd_sets passed to it,
         *  so zero and set them prior to each call.     */

        fd_set fds;
        FD_ZERO(&fds);
        FD_SET(STDIN_FILENO, &fds);

        /*  Same deal for the struct timeval, select() may
         *  modify it, it may not, so recreate to be portable.  */

        struct timeval tv;
        tv.tv_sec = secs;
        tv.tv_usec = usecs;

        /*  Store the return so we can check it  */

        int status = select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv);

        /*  Check for error  */

        if ( status == -1 ) {

            /*  select() returned with an error.  */

            if ( errno != EINTR ) {

                /*  If interrupted by a signal, no problem,
                 *  keep going. Otherwise, let's just quit.  */

                stop_curses(&cinfo);
                perror("error calling select()");
                return EXIT_FAILURE;
            }
        }
        else if ( FD_ISSET(STDIN_FILENO, &fds) ) {

            /*  Only call getch() if input is ready.
             *  getch() will not block when we do it this way.  */

            if ( (input = getch()) == ERR ) {
                stop_curses(&cinfo);
                fprintf(stderr, "ERR returned from getch()\n");
                return EXIT_FAILURE;
            }
        }

        /*  Increment number of times select() has returned  */

        ++num_sel;
    }

    stop_curses(&cinfo);

    return 0;
}

/*  Starts curses and populates the passed struct  */

void start_curses(struct curinfo * info)
{
    if ( (info->main_window = initscr()) == NULL ) {
        fprintf(stderr, "Error calling initscr()\n");
        exit(EXIT_FAILURE);
    }

    keypad(stdscr, TRUE);
    timeout(0);
    raw();
    nonl();
    noecho();
    info->old_cursor = curs_set(0);
    refresh();
}

/*  Stops curses and cleans up  */

void stop_curses(struct curinfo * info)
{
    delwin(info->main_window);
    curs_set(info->old_cursor);
    endwin();
    refresh();
}
