#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "gtext-app.h"
#include "gtext-app-win.h"
#include "gtext-dialog.h"
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

static GActionEntry actions[] = {
    {"new", gtext_app_action_new, NULL, NULL, NULL},
    {"open", gtext_app_action_open, NULL, NULL, NULL},
    {"save", NULL, NULL, NULL, NULL},
    {"save_as", NULL, NULL, NULL, NULL},
};

static const gchar* new_accels[2] = {"<Ctrl>N", NULL};
static const gchar* open_accels[2] = {"<Ctrl>O", NULL};
static const gchar* save_accels[2] = {"<Ctrl>S", NULL};
static const gchar* save_as_accels[2] = {"<Ctrl><Shift>S", NULL};

GTextApp* gtext_app_new(void) {
    return g_object_new(GTEXT_APP_TYPE,
                        "application-id", "us.remer.gtext",
                        "flags", G_APPLICATION_HANDLES_OPEN,
                        NULL);
}

void gtext_app_action_new(GSimpleAction* action, GVariant* param, gpointer app) {
    gtext_app_activate(G_APPLICATION(app));
}

void gtext_app_action_open(GSimpleAction* action, GVariant* param, gpointer app) {
    GFile* file = gtext_dialog_open();
    if (file) gtext_app_open(G_APPLICATION(app), &file, 1, NULL);
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
    GMenu* menu;

    // call parent implementation
    G_APPLICATION_CLASS(gtext_app_parent_class)->startup(app);

    g_set_application_name("GText");

    g_action_map_add_action_entries(G_ACTION_MAP(app),
        actions, G_N_ELEMENTS(actions), app);

    gtk_application_set_accels_for_action(GTK_APPLICATION(app), "app.new", new_accels);
    gtk_application_set_accels_for_action(GTK_APPLICATION(app), "app.open", open_accels);
    gtk_application_set_accels_for_action(GTK_APPLICATION(app), "win.save", save_accels);
    gtk_application_set_accels_for_action(GTK_APPLICATION(app), "win.save_as", save_as_accels);

    menu = gtext_res_create_menu();
    gtk_application_set_app_menu(GTK_APPLICATION(app), G_MENU_MODEL(menu));
    g_object_unref(menu);

    // setup fallback icon for all app windows
    GList* app_icon = gtext_res_load_icon_list("accessories-text-editor");
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
