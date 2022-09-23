/*
 * basic program from tutorial on setting up ncurses
 * Will be using this as a prototype to build off of
 *
 * compile with: gcc ncurses_ex.c -lncurses -o main 
 *
 */
#include<ncurses.h>
#include<stdlib.h>

//-----------------------------------------------------------------------------
// FUNCTION PROTOTYPES
//-----------------------------------------------------------------------------
void printing();
void move_sleep();
void display_color();

//-----------------------------------------------------------------------------
// FUNCTION printing
//-----------------------------------------------------------------------------
void printing() {
    int num_int = 17;
    double num_dub = 171.17;

    addstr("Print statement w/ 'addstr'\n\n");
    refresh();

    addstr("Print char w/ 'addch' : ");
    addch('i');
    printw("\n\n");
    refresh();
    
    printw("Print numbers w/ 'printw()' : %d %f \n\n", num_int, num_dub);
}


//-----------------------------------------------------------------------------
// FUNCTION move_sleep
// print the alphabet in both upper/lowercase decrementing
// one space down and across for each iteration
//-----------------------------------------------------------------------------
void move_sleep() {
    // row = 15 for heading
    int row = 15;
    int col = 0;

    // set cursor hide using 0
    curs_set(0);
    // traverse upper case letters
    for (char c = 65; c <= 90; c++){
        // move to current position
        move(row++, col++);
        // print char
        addch(c);
        refresh();
        // NAP FOR MILLISECONDS; pause for .1 seconds
        napms(100);
    }

    row = 15;
    col = 3;
    for (char c = 97; c <= 122; c++){
        mvaddch(row++, col++, c);
        refresh();
        napms(100);
    }
    curs_set(1);
    addch('\n');

}


//-----------------------------------------------------------------------------
// FUNCTION display_color
// display some text with some colors
//-----------------------------------------------------------------------------
void display_color() {
    if (has_colors()) {
        if (start_color() == OK) {
            init_pair(0, COLOR_MAGENTA);
            init_pair(1, COLOR_CYAN);
    
            // to add color to text, enclose in attrset/attroff block
            attrset(COLOR_PAIR(0));
            addstr("Printing some color");
            attroff(COLOR_PAIR(0));


        }
    }
}

//--------------------------------------------------------
// FUNCTION main
//--------------------------------------------------------
int main(void) {
    initscr();

    printw("\n ----------------------------- \n \
            \n |This is our GUI            | \n \
            \n |(Graphical User Interface) | \n \
            \n |                           | \n \
            \n ----------------------------- \n");
    
    refresh();

    printing();

    move_sleep();

    display_color();

    addstr("\npress any key to exit...");
    refresh();

    getch();

    endwin();

    return EXIT_SUCCESS;
}
