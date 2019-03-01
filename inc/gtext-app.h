#ifndef GTEXT_APP_H
#define GTEXT_APP_H

#include <gtk/gtk.h>

GtkApplication* gtext_app_create();
void gtext_app_load_css(GtkApplication*, int, const char*);
int gtext_app_run(GtkApplication*, int, char*[]);
void gtext_app_destroy(GtkApplication*);

#endif
