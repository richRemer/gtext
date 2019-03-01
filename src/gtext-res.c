#include <stdbool.h>
#include <gtk/gtk.h>
#include "gtext-res.h"

GList* gtext_load_icon_list(const char* icon_name) {
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
