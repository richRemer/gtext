#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "gtext-app.h"
#include "gtext-res.h"
#include "gtext-window.h"

static const char* const GTEXT_APP_ID = "us.remer.gtext";

static void startup(GApplication* app, gpointer data) {
    const char* css = (const char*)data;
    gtext_load_default_css(strlen(css), css);
    free((void*)css);
}

static void activate(GApplication* app, gpointer data) {
    GtkWidget* window = gtext_window_new(app);
    gtk_widget_show_all(window);
}

static void open(GApplication* app, GFile* files[], gint nfiles, gchar* hint, gpointer data) {
    g_print("open:\n");

    for (int i = 0; i < nfiles; i++) {
        g_print("  %s\n", g_file_get_basename(files[i]));
    }
}

GtkApplication* gtext_app_create() {
    GtkApplication* app;

    app = gtk_application_new(GTEXT_APP_ID, G_APPLICATION_HANDLES_OPEN);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    g_signal_connect(app, "open", G_CALLBACK(open), NULL);

    return app;
}

void gtext_app_load_css(GtkApplication* app, int len, const char* css) {
    char* data = malloc(len + 1);

    // TODO: avoid segfault on ENOMEM above
    memcpy(data, css, len);
    data[len] = '\0';

    // TODO: remove old handler; multiple handlers overwrite CSS data
    g_signal_connect(app, "startup", G_CALLBACK(startup), data);
}

int gtext_app_run(GtkApplication* app, int argc, char* argv[]) {
    return g_application_run(G_APPLICATION(app), argc, argv);
}

void gtext_app_destroy(GtkApplication* app) {
    g_object_unref(app);
}
