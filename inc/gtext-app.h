#ifndef GTEXT_APP_H
#define GTEXT_APP_H

#include <gtk/gtk.h>

#define GTEXT_APP_TYPE (gtext_app_get_type())
G_DECLARE_FINAL_TYPE (GTextApp, gtext_app, GTEXT, APP, GtkApplication)

GTextApp* gtext_app_new(void);
void gtext_app_action_new(GSimpleAction*, GVariant*, gpointer);
void gtext_app_action_open(GSimpleAction*, GVariant*, gpointer);

#endif
