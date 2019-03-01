#include "gtext-res.h"
#include "gtext-window.h"

GtkWidget* gtext_window_new(GtkApplication* app) {
    GtkWidget* window;
    GtkWidget* window_box;
    GtkWidget* scroll_view;
    GtkWidget* text_view;
    GList* window_icon;

    window_icon = gtext_load_icon_list("accessories-text-editor");

    text_view = gtk_text_view_new();
    gtk_text_view_set_monospace(GTK_TEXT_VIEW(text_view), TRUE);
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(text_view), GTK_WRAP_WORD);
    gtext_style_widget(text_view, "gtext-document");

    scroll_view = gtk_scrolled_window_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER(scroll_view), text_view);

    window_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_box_pack_start(GTK_BOX(window_box), scroll_view, TRUE, TRUE, 0);

    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Editor");
    gtk_window_set_default_size(GTK_WINDOW(window), 640, 480);
    gtk_window_set_icon_list(GTK_WINDOW(window), window_icon);
    gtk_container_add(GTK_CONTAINER(window), window_box);
    //g_signal_connect(G_OBJECT(window), "destroy", gtk_main_quit, NULL);

    return window;
}
