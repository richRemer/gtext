#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "gtext-app.h"
#include "gtext-res.h"
#include "gtext-window.h"

struct _GTextApp {
    GtkApplication parent;
};

G_DEFINE_TYPE(GTextApp, gtext_app, GTK_TYPE_APPLICATION);

static void gtext_app_init(GTextApp* app) {
    // implements GApplication interface
}

static void gtext_app_activate(GApplication* app) {
    GtkWidget* window = gtext_window_new(app);
    gtk_window_present(GTK_WINDOW(window));
}

static void gtext_app_open(GApplication* app, GFile* files[], gint nfiles, const gchar* hint) {
    g_print("open:\n");

    for (int i = 0; i < nfiles; i++) {
        g_print("  %s\n", g_file_get_basename(files[i]));
    }
}

static void gtext_app_class_init(GTextAppClass* class) {
    G_APPLICATION_CLASS(class)->activate = gtext_app_activate;
    G_APPLICATION_CLASS(class)->open = gtext_app_open;
}

GTextApp* gtext_app_new(void) {
    return g_object_new(GTEXT_APP_TYPE,
                        "application-id", "us.remer.gtext",
                        "flags", G_APPLICATION_HANDLES_OPEN,
                        NULL);
}
