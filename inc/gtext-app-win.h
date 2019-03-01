#ifndef GTEXT_APP_WIN_H
#define GTEXT_APP_WIN_H

#include <gtk/gtk.h>
#include "gtext-app.h"

#define GTEXT_APP_WIN_TYPE (gtext_app_win_get_type())
G_DECLARE_FINAL_TYPE (GTextAppWin, gtext_app_win, GTEXT, APP_WIN, GtkApplicationWindow)
GTextAppWin* gtext_app_win_new(GTextApp*);

#endif
