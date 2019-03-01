#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "gtext-app.h"
#include "gtext-app-win.h"
#include "gtext-res.h"

struct _GTextApp {
    GtkApplication parent;
};

G_DEFINE_TYPE(GTextApp, gtext_app, GTK_TYPE_APPLICATION);

static void gtext_app_init(GTextApp* app) {
    // implements GApplication interface
}

static void gtext_app_startup(GApplication* app) {
    // call parent implementation
    G_APPLICATION_CLASS(gtext_app_parent_class)->startup(app);

    // setup fallback icon for all app windows
    GList* app_icon = gtext_load_icon_list("accessories-text-editor");
    gtk_window_set_default_icon_list(app_icon);
}

static void gtext_app_activate(GApplication* app) {
    GTextAppWin* window = gtext_app_win_new(GTEXT_APP(app));
    gtk_window_present(GTK_WINDOW(window));
}

static void gtext_app_open(GApplication* app, GFile* files[], gint nfiles, const gchar* hint) {
    g_print("open:\n");

    for (int i = 0; i < nfiles; i++) {
        g_print("  %s\n", g_file_get_basename(files[i]));
    }
}

static void gtext_app_class_init(GTextAppClass* class) {
    G_APPLICATION_CLASS(class)->startup = gtext_app_startup;
    G_APPLICATION_CLASS(class)->activate = gtext_app_activate;
    G_APPLICATION_CLASS(class)->open = gtext_app_open;
}

GTextApp* gtext_app_new(void) {
    return g_object_new(GTEXT_APP_TYPE,
                        "application-id", "us.remer.gtext",
                        "flags", G_APPLICATION_HANDLES_OPEN,
                        NULL);
}
