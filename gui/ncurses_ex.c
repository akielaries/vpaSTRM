/*
 * basic program from tutorial on setting up ncurses
 * Will be using this as a prototype to build off of
 *
 * compile with: gcc ncurses_ex.c -lncurses -o main 
 *
 */
#include<ncurses.h>
#include<stdlib.h>

//--------------------------------------------------------
// FUNCTION PROTOTYPES
//--------------------------------------------------------
void printing();
void moving_and_sleeping();
void colouring();


//--------------------------------------------------------
// FUNCTION printing
//--------------------------------------------------------
void printing() {
    int num_int = 17;
    double num_dub = 171.17;

    addstr("Print statement w/ 'addstr'\n\n");
    refresh();

    addstr("Print char w/ 'addch' : \n\n");
    addch('i');
    refresh();
    
    printw("Print numbers w/ 'printw()' : %d %f \n\n", num_int, num_dub);
}

//--------------------------------------------------------
// FUNCTION main
//--------------------------------------------------------
int main(void) {
    initscr();

    addstr("-----------------\n| This is our GUI        |\n|(Graphical User Interface)|\n-----------------\n\n");
    refresh();

    printing();

    //moving_and_sleeping();

    //colouring();

    addstr("\npress any key to exit...");
    refresh();

    getch();

    endwin();

    return EXIT_SUCCESS;
}
