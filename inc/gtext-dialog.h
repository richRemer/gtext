#ifndef GTEXT_DIALOG_H
#define GTEXT_DIALOG_H

#include <gtk/gtk.h>

GFile* gtext_dialog_open();
GFile* gtext_dialog_save_as(GtkWindow*);

#endif
