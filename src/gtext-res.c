#include <stdbool.h>
#include <gtk/gtk.h>
#include "gtext-res.h"

GMenu* gtext_res_create_menu() {
    GMenu* full_menu;
    GMenu* app_menu;
    GMenu* doc_menu;
    GMenu* help_menu;

    full_menu = g_menu_new();
    app_menu = g_menu_new();
    doc_menu = g_menu_new();
    help_menu = g_menu_new();

    g_menu_append(app_menu, "New", "app.new");
    g_menu_append(app_menu, "Open...", "app.open");
    g_menu_append(doc_menu, "Save", "win.save");
    g_menu_append(doc_menu, "Save As...", "win.save_as");
    g_menu_append(help_menu, "Keyboard Shortcuts", "app.help");
    g_menu_append_section(full_menu, NULL, G_MENU_MODEL(app_menu));
    g_menu_append_section(full_menu, NULL, G_MENU_MODEL(doc_menu));
    g_menu_append_section(full_menu, NULL, G_MENU_MODEL(help_menu));

    g_object_unref(help_menu);
    g_object_unref(doc_menu);
    g_object_unref(app_menu);

    return full_menu;
}

GList* gtext_res_load_icon_list(const char* icon_name) {
    GList* icon_list = NULL;
    GdkPixbuf* icon;
    GtkIconTheme* theme;
    gint* sizes;

    theme = gtk_icon_theme_get_default();
    sizes = gtk_icon_theme_get_icon_sizes(theme, icon_name);

    for (gint* size = sizes; *size; ++size) {
        if (*size <= 0) continue;
        icon = gtk_icon_theme_load_icon(theme, icon_name, *size, 0, NULL);
        icon_list = g_list_prepend(icon_list, icon);
    }

    g_free(sizes);

    if (NULL == icon_list) {
        icon = gtk_icon_theme_load_icon(theme, icon_name, 48, 0, NULL);
        icon_list = g_list_prepend(icon_list, icon);
    }

    return icon_list;
}
