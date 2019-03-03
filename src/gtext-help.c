#include "gtext-help.h"

GtkWidget* gtext_help_create_window() {
    GtkWidget* window;
    GtkWidget* section;
    GtkWidget* app_group;
    GtkWidget* doc_group;
    GtkWidget* shortcut_help;
    GtkWidget* shortcut_new;
    GtkWidget* shortcut_open;
    GtkWidget* shortcut_save;
    GtkWidget* shortcut_save_as;

    // HACK: this whole thing is hack-y
    // HACK: for some reason GTK+ is missing constructors for these types

    shortcut_help = g_object_new(GTK_TYPE_SHORTCUTS_SHORTCUT,
        "accelerator", "F1",
        "title", "Shortcuts",
        "subtitle", "Activate to show keyboard shortcuts",
        NULL);

    shortcut_new = g_object_new(GTK_TYPE_SHORTCUTS_SHORTCUT,
        "accelerator", "<Ctrl>N",
        "title", "New document",
        "subtitle", "Activate to create an empty document",
        NULL);

    shortcut_open = g_object_new(GTK_TYPE_SHORTCUTS_SHORTCUT,
        "accelerator", "<Ctrl>O",
        "title", "Open document",
        "subtitle", "Activate to open a document from disk",
        NULL);

    app_group = g_object_new(GTK_TYPE_SHORTCUTS_GROUP,
        "title", "Application shortcuts",
        NULL);
    gtk_container_add(GTK_CONTAINER(app_group), shortcut_help);
    gtk_container_add(GTK_CONTAINER(app_group), shortcut_new);
    gtk_container_add(GTK_CONTAINER(app_group), shortcut_open);

    shortcut_save = g_object_new(GTK_TYPE_SHORTCUTS_SHORTCUT,
        "accelerator", "<Ctrl>S",
        "title", "Save document",
        "subtitle", "Activate to save current document to disk",
        NULL);

    shortcut_save_as = g_object_new(GTK_TYPE_SHORTCUTS_SHORTCUT,
        "accelerator", "<Ctrl><Shift>S",
        "title", "Save copy",
        "subtitle", "Activate to save copy of current document to disk",
        NULL);

    doc_group = g_object_new(GTK_TYPE_SHORTCUTS_GROUP,
        "title", "Document shortcuts",
        NULL);
    gtk_container_add(GTK_CONTAINER(doc_group), shortcut_save);
    gtk_container_add(GTK_CONTAINER(doc_group), shortcut_save_as);

    section = g_object_new(GTK_TYPE_SHORTCUTS_SECTION,
        "section-name", "only-section",
        "title", "GText Shortcuts",
        NULL);
    gtk_container_add(GTK_CONTAINER(section), app_group);
    gtk_container_add(GTK_CONTAINER(section), doc_group);
    gtk_widget_show(section);   // HACK: section must be shown or window breaks

    window = g_object_new(GTK_TYPE_SHORTCUTS_WINDOW,
        "title", "Keyboard shortcuts",
        NULL);
    gtk_container_add(GTK_CONTAINER(window), section);
    gtk_widget_hide(gtk_window_get_titlebar(GTK_WINDOW(window)));
    g_signal_connect(window, "delete-event",
        G_CALLBACK(gtk_widget_hide_on_delete), NULL);

    return window;
}
