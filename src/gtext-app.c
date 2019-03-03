#include "gtext-app.h"
#include "gtext-doc-win.h"
#include "gtext-dialog.h"
#include "gtext-help.h"
#include "gtext-res.h"

struct _GTextApp {
    GtkApplication parent;
    GtkWidget* help_window;
};

G_DEFINE_TYPE(GTextApp, gtext_app, GTK_TYPE_APPLICATION);

GTextApp* gtext_app_new(void) {
    return g_object_new(GTEXT_APP_TYPE,
                        "application-id", "us.remer.gtext",
                        "flags", G_APPLICATION_HANDLES_OPEN,
                        NULL);
}

GtkWidget* gtext_app_new_document(GTextApp* app) {
    GTextDocWin* window = gtext_doc_win_new(app);
    gtk_window_present(GTK_WINDOW(window));
    return GTK_WIDGET(window);
}

GtkWidget* gtext_app_open_document(GTextApp* app) {
    GFile* file;

    if (NULL != (file = gtext_dialog_open())) {
        return gtext_app_open_file(app, file);
    }
}

GtkWidget* gtext_app_open_file(GTextApp* app, GFile* file) {
    GTextDocWin* window = gtext_doc_win_new_with_file(app, file);
    gtk_window_present(GTK_WINDOW(window));
    return GTK_WIDGET(window);
}

GtkWidget* gtext_app_show_help_window(GTextApp* app) {
    if (NULL == app->help_window) {
        app->help_window = gtext_help_create_window();

        // present after 'realize' event or window might be part off-screen
        g_signal_connect(app->help_window, "realize",
            G_CALLBACK(gtk_window_present), NULL);

        gtk_widget_show_all(app->help_window);
    } else {
        // subsequent times, can just present directly
        gtk_window_present(GTK_WINDOW(app->help_window));
    }

    return app->help_window;
}

static void gtext_app_action_help(GSimpleAction* action, GVariant* param, gpointer app) {
    gtext_app_show_help_window(GTEXT_APP(app));
}

static void gtext_app_action_new(GSimpleAction* action, GVariant* param, gpointer app) {
    gtext_app_new_document(GTEXT_APP(app));
}

static void gtext_app_action_open(GSimpleAction* action, GVariant* param, gpointer app) {
    gtext_app_open_document(GTEXT_APP(app));
}

static GActionEntry actions[] = {
    {"help", gtext_app_action_help, NULL, NULL, NULL},
    {"new", gtext_app_action_new, NULL, NULL, NULL},
    {"open", gtext_app_action_open, NULL, NULL, NULL},
    {"save", NULL, NULL, NULL, NULL},
    {"save_as", NULL, NULL, NULL, NULL},
};

static const gchar* help_accels[2] = {"F1", NULL};
static const gchar* new_accels[2] = {"<Ctrl>N", NULL};
static const gchar* open_accels[2] = {"<Ctrl>O", NULL};
static const gchar* save_accels[2] = {"<Ctrl>S", NULL};
static const gchar* save_as_accels[2] = {"<Ctrl><Shift>S", NULL};

static void gtext_app_startup(GApplication* app) {
    GMenu* menu;

    // call parent implementation
    G_APPLICATION_CLASS(gtext_app_parent_class)->startup(app);

    g_set_application_name("GText");

    g_action_map_add_action_entries(G_ACTION_MAP(app),
        actions, G_N_ELEMENTS(actions), app);

    gtk_application_set_accels_for_action(GTK_APPLICATION(app), "app.help", help_accels);
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
    gtext_app_action_new(NULL, NULL, app);
}

static void gtext_app_open(GApplication* app, GFile* files[], gint nfiles, const gchar* hint) {
    for (int i = 0; i < nfiles; i++) {
        gtext_app_open_file(GTEXT_APP(app), files[i]);
    }
}

static void gtext_app_init(GTextApp* app) {
    // implements GApplication interface
}

static void gtext_app_class_init(GTextAppClass* class) {
    G_APPLICATION_CLASS(class)->startup = gtext_app_startup;
    G_APPLICATION_CLASS(class)->activate = gtext_app_activate;
    G_APPLICATION_CLASS(class)->open = gtext_app_open;
}
