/*
 * using the gtk lib, we will create a GUI hopefully to interface with
 * our existing python application. This aims to take our application 
 * outside of the CMD line and into something *sort of* prettier!
 */
#include <gtk/gtk.h>

static int counter = 0;

void intro(GtkWidget* widget, gpointer data) {
    // print for gtk
    g_print("RTSP Stream APP");
    g_print("%s clicked %d times\n", (char*)data, ++counter);
}

// destroy windows
void destroy(GtkWidget* widget, gpointer data) {
    gtk_main_quit();
}

int main(int argc, char* argv[]) {
    // declare a ptr to our gtk widget for the window
    GtkWidget *wndw;
    // declare ptr to our widget for a button
    GtkWidget *add_cam_btn;
    GtkWidget *exit_btn;

    // initialize gtk libs w/ cli args
    gtk_init(&argc, &argv);

    // declare our pointers from the top
        // GTK_WINDOW_POPUP = frameless window
        // GTK_WINDOW_TOPLEVEL = standard framed window
    wndw = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    
    // call gtk cnct function
    g_signal_connect(wndw, "DESTROY", G_CALLBACK(destroy), NULL);
    
    /* set border width to 40, this variable can be changed */
    gtk_container_set_border_width(GTK_CONTAINER(window), 40);
    
    // create our buttons
    add_cam_btn = gtk_button_new_with_label("Add camera");
    exit_btn = gtk_button_new_with_label("Exit");

    g_signal_connect(GTK_OBJECT(add_cam_btn, exit_btn), "CLICKED", G_CALLBACK(intro), "BUTTON");

    gtk_container_add(GTK_CONTAINER(wndw), add_cam_btn, exit_btn);

    gtk_widget_show_all(wndw);
    // run out gtk app
    gtk_main();
    return 0;

}

