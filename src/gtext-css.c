#include "gtext-css.h"

void gtext_css_init() {
    GtkCssProvider* styles;
    GdkScreen* screen;
    GdkDisplay* display;

    display = gdk_display_get_default();
    screen = gdk_display_get_default_screen(display);
    styles = gtk_css_provider_new();

    gtk_css_provider_load_from_data(styles, gtext_css, gtext_css_len, NULL);
    gtk_style_context_add_provider_for_screen(
        screen,
        GTK_STYLE_PROVIDER(styles),
        GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    g_object_unref(styles);
}

void gtext_css_style_widget(GtkWidget* widget, const char* css_class) {
    GtkStyleContext* style;
    style = gtk_widget_get_style_context(widget);
    gtk_style_context_add_class(style, css_class);
}
