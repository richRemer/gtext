#include <gtk/gtk.h>
#include "gtext-res.h"

void gtext_load_default_css(int len, const char* css) {
    GtkCssProvider* styles;
    GdkScreen* screen;
    GdkDisplay* display;

    display = gdk_display_get_default();
    screen = gdk_display_get_default_screen(display);
    styles = gtk_css_provider_new();

    gtk_css_provider_load_from_data(styles, css, len, NULL);
    gtk_style_context_add_provider_for_screen(
        screen,
        GTK_STYLE_PROVIDER(styles),
        GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    g_object_unref(styles);
}

GList* gtext_load_icon_list(const char* icon_name) {
    GList* icon_list = NULL;
    GdkPixbuf* icon;
    GtkIconTheme* theme;
    gint* sizes;

    theme = gtk_icon_theme_get_default();
    sizes = gtk_icon_theme_get_icon_sizes(theme, icon_name);

    for (gint* size = sizes; *size; ++size) {
      icon = gtk_icon_theme_load_icon(theme, icon_name, *size, 0, NULL);
      icon_list = g_list_prepend(icon_list, icon);
    }

    g_free(sizes);

    return icon_list;
}

void gtext_style_widget(GtkWidget* widget, const char* css_class) {
    GtkStyleContext* style;
    style = gtk_widget_get_style_context(widget);
    gtk_style_context_add_class(style, css_class);
}
