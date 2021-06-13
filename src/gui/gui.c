#include "gui.h"

GtkWidget *parent;

void start_voice(GtkButton *button, GtkLabel *text_label){
    (void)button;
    (void)text_label;

    write(STDOUT_FILENO,"start-voice\n",13);
}

void InitGUI(int argc, char *argv[])
{
	//Init variables
    GtkWidget *main_window;
	SGlobalData data;
	//Init GTK
	gtk_init(&argc, &argv);
	//Build from .glade
    data.builder = gtk_builder_new();
    gtk_builder_add_from_file(data.builder, "src/gui/gui.glade", NULL);
	//Get main_window
	main_window =  GTK_WIDGET(gtk_builder_get_object(data.builder,"main_window"));
    parent = main_window;
	//Connect signals
	gtk_builder_connect_signals(data.builder, &data);
    g_signal_connect(main_window,"destroy",G_CALLBACK(gtk_main_quit),NULL);

    gtk_window_set_title(GTK_WINDOW(main_window), "420-sh - Voice Recognition");
    gtk_widget_show_all(main_window);
    gtk_main();
}
