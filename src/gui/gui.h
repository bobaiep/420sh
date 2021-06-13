#include <gtk/gtk.h>
#include "../builtins/builtins.h"
#include "../exec/exec.h"

typedef struct
{
	GtkBuilder *builder;
	gpointer user_data;
} SGlobalData;


void start_voice(GtkButton *button, GtkLabel *text_label);

void InitGUI(int argc, char *argv[]);