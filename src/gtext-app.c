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

static void gtext_app_class_init(GTextAppClass*);
static void gtext_app_init(GTextApp*);
static void gtext_app_startup(GApplication*);
static void gtext_app_activate(GApplication*);
static void gtext_app_open(GApplication*, GFile*[], gint, const gchar*);
static void new_activated(GSimpleAction*, GVariant*, gpointer);
static void open_activated(GSimpleAction*, GVariant*, gpointer);

static GActionEntry actions[] = {
    {"new", new_activated, NULL, NULL, NULL},
    {"open", open_activated, NULL, NULL, NULL}
};

static const gchar* new_accels[2] = {"<Ctrl>N", NULL};
static const gchar* open_accels[2] = {"<Ctrl>O", NULL};

GTextApp* gtext_app_new(void) {
    return g_object_new(GTEXT_APP_TYPE,
                        "application-id", "us.remer.gtext",
                        "flags", G_APPLICATION_HANDLES_OPEN,
                        NULL);
}

static void open_activated(GSimpleAction* action, GVariant* param, gpointer app) {
    GtkWidget* dialog;
    gint result;
    GFile* file;

    dialog = gtk_file_chooser_dialog_new(NULL, NULL, GTK_FILE_CHOOSER_ACTION_OPEN,
        "_Cancel", GTK_RESPONSE_CANCEL,
        "_Open", GTK_RESPONSE_ACCEPT,
        NULL);

    if (GTK_RESPONSE_ACCEPT == gtk_dialog_run(GTK_DIALOG(dialog))) {
        file = gtk_file_chooser_get_file(GTK_FILE_CHOOSER(dialog));
        gtext_app_open(G_APPLICATION(app), &file, 1, NULL);
    }

    gtk_widget_destroy(dialog);
}

static void new_activated(GSimpleAction* action, GVariant* param, gpointer app) {
    gtext_app_activate(G_APPLICATION(app));
}

static void gtext_app_class_init(GTextAppClass* class) {
    G_APPLICATION_CLASS(class)->startup = gtext_app_startup;
    G_APPLICATION_CLASS(class)->activate = gtext_app_activate;
    G_APPLICATION_CLASS(class)->open = gtext_app_open;
}

static void gtext_app_init(GTextApp* app) {
    // implements GApplication interface
}

static void gtext_app_startup(GApplication* app) {
    GMenu* app_menu;

    // call parent implementation
    G_APPLICATION_CLASS(gtext_app_parent_class)->startup(app);

    g_set_application_name("GText");

    g_action_map_add_action_entries(G_ACTION_MAP(app),
        actions, G_N_ELEMENTS(actions), app);

    gtk_application_set_accels_for_action(GTK_APPLICATION(app), "app.new", new_accels);
    gtk_application_set_accels_for_action(GTK_APPLICATION(app), "app.open", open_accels);

    app_menu = g_menu_new();
    g_menu_append(app_menu, "New", "app.new");
    g_menu_append(app_menu, "Open", "app.open");
    gtk_application_set_app_menu(GTK_APPLICATION(app), G_MENU_MODEL(app_menu));
    g_object_unref(app_menu);

    // setup fallback icon for all app windows
    GList* app_icon = gtext_load_icon_list("accessories-text-editor");
    gtk_window_set_default_icon_list(app_icon);
}

static void gtext_app_activate(GApplication* app) {
    GTextAppWin* window = gtext_app_win_new(GTEXT_APP(app));
    gtk_window_present(GTK_WINDOW(window));
}

static void gtext_app_open(GApplication* app, GFile* files[], gint nfiles, const gchar* hint) {
    GTextAppWin* window;

    for (int i = 0; i < nfiles; i++) {
        window = gtext_app_win_new_with_file(GTEXT_APP(app), files[i]);
        gtk_window_present(GTK_WINDOW(window));
    }
}
