#ifndef GTEXT_RES_H
#define GTEXT_RES_H

#include <gtk/gtk.h>

void gtext_load_default_css(int, const char*);
GList* gtext_load_icon_list(const char*);
void gtext_style_widget(GtkWidget*, const char*);

#endif
