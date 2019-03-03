#include "gtext-dialog.h"

GFile* gtext_dialog_open() {
    GtkWidget* dialog;
    GFile* file;

    dialog = gtk_file_chooser_dialog_new(NULL, NULL,
        GTK_FILE_CHOOSER_ACTION_OPEN,
        "_Cancel", GTK_RESPONSE_CANCEL,
        "_Open", GTK_RESPONSE_ACCEPT,
        NULL);

    if (GTK_RESPONSE_ACCEPT == gtk_dialog_run(GTK_DIALOG(dialog))) {
        file = gtk_file_chooser_get_file(GTK_FILE_CHOOSER(dialog));
        g_object_ref(file);
    }

    gtk_widget_destroy(dialog);

    return file;
}
