#include "gtext-css.h"
#include "gtext-res.h"
#include "gtext-app-win.h"

struct _GTextAppWin {
    GtkApplicationWindow parent;
    GtkWidget* layout;
    GtkWidget* viewport;
    GtkWidget* content;
};

G_DEFINE_TYPE (GTextAppWin, gtext_app_win, GTK_TYPE_APPLICATION_WINDOW)

static void gtext_app_win_init(GTextAppWin* window) {
    window->content = gtk_text_view_new();
    gtk_text_view_set_monospace(GTK_TEXT_VIEW(window->content), TRUE);
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(window->content), GTK_WRAP_WORD);
    gtext_css_style_widget(window->content, "content");

    window->viewport = gtk_scrolled_window_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER(window->viewport), window->content);

    window->layout = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_box_pack_start(GTK_BOX(window->layout), window->viewport, TRUE, TRUE, 0);

    gtk_window_set_title(GTK_WINDOW(window), "Editor");
    gtk_window_set_default_size(GTK_WINDOW(window), 640, 480);
    gtk_container_add(GTK_CONTAINER(window), window->layout);
    gtk_widget_show_all(window->layout);
}

static void gtext_app_win_class_init(GTextAppWinClass* class) {

}

GTextAppWin* gtext_app_win_new(GTextApp* app) {
    return g_object_new(GTEXT_APP_WIN_TYPE,
        "application", app,
        "show-menubar", FALSE,
        NULL);
}
