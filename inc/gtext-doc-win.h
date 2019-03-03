#ifndef GTEXT_DOC_WIN_H
#define GTEXT_DOC_WIN_H

#include <gtk/gtk.h>
#include "gtext-app.h"

#define GTEXT_DOC_WIN_TYPE (gtext_doc_win_get_type())
G_DECLARE_FINAL_TYPE (GTextDocWin, gtext_doc_win, GTEXT, DOC_WIN, GtkApplicationWindow)

GTextDocWin* gtext_doc_win_new(GTextApp*);
GTextDocWin* gtext_doc_win_new_with_file(GTextApp*, GFile*);
GFile* gtext_doc_win_get_file(GTextDocWin*);
void gtext_doc_win_save(GTextDocWin*);
void gtext_doc_win_save_as(GTextDocWin*);
void gtext_doc_win_set_file(GTextDocWin*, GFile*);

#endif
