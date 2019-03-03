#include "gtext-css.h"
#include "gtext-res.h"
#include "gtext-app-win.h"
#include "gtext-dialog.h"

struct _GTextAppWin {
    GtkApplicationWindow parent;
    GtkWidget* layout;
    GtkWidget* viewport;
    GtkWidget* content;
    GFile* file;
};

G_DEFINE_TYPE (GTextAppWin, gtext_app_win, GTK_TYPE_APPLICATION_WINDOW)

static GActionEntry actions[] = {
    {"save", gtext_app_win_action_save, NULL, NULL, NULL},
    {"save_as", gtext_app_win_action_save_as, NULL, NULL, NULL}
};

GTextAppWin* gtext_app_win_new(GTextApp* app) {
    return g_object_new(GTEXT_APP_WIN_TYPE,
        "application", app,
        "show-menubar", FALSE,
        NULL);
}

GTextAppWin* gtext_app_win_new_with_file(GTextApp* app, GFile* file) {
    GTextAppWin* window = gtext_app_win_new(app);
    GtkTextBuffer* buffer;
    char* contents;
    gsize len;

    if (g_file_load_contents(file, NULL, &contents, &len, NULL, NULL)) {
        buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(window->content));
        gtk_text_buffer_set_text(buffer, contents, len);
        g_object_ref(window->file = file);
        g_free(contents);
    }

    return window;
}

void gtext_app_win_action_save(GSimpleAction* action, GVariant* param, gpointer window) {
    GtkTextBuffer* buffer;
    GtkTextIter start;
    GtkTextIter end;
    GFile* file;
    GFileOutputStream* out;
    gchar* contents;
    int len;

    if (NULL == (file = gtext_app_win_get_file(GTEXT_APP_WIN(window)))) {
        return gtext_app_win_action_save_as(action, param, window);
    }

    if (NULL == (out = g_file_replace(file, NULL, FALSE, 0, NULL, NULL))) {
        g_printerr("could not open file for writing\n");
    }

    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(GTEXT_APP_WIN(window)->content));
    gtk_text_buffer_get_start_iter(buffer, &start);
    gtk_text_buffer_get_end_iter(buffer, &end);

    contents = gtk_text_buffer_get_text(buffer, &start, &end, FALSE);
    len = strlen(contents);
    if (len && contents[len-1] != '\n') contents[len++] = '\n';

    g_output_stream_write(G_OUTPUT_STREAM(out), contents, len, NULL, NULL);
    g_output_stream_close(G_OUTPUT_STREAM(out), NULL, NULL);
    g_free(contents);
}

void gtext_app_win_action_save_as(GSimpleAction* action, GVariant* param, gpointer window) {
    GFile* file = gtext_dialog_save_as(GTK_WINDOW(window));

    if (file) {
        GTEXT_APP_WIN(window)->file = file;
        gtext_app_win_action_save(action, param, window);
    }
}

GFile* gtext_app_win_get_file(GTextAppWin* window) {
    return window->file;
}

static void gtext_app_win_class_init(GTextAppWinClass* class) {

}

static void gtext_app_win_init(GTextAppWin* window) {
    window->content = gtk_text_view_new();
    gtk_text_view_set_monospace(GTK_TEXT_VIEW(window->content), TRUE);
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(window->content), GTK_WRAP_WORD);
    gtext_css_style_widget(window->content, "content");

    window->viewport = gtk_scrolled_window_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER(window->viewport), window->content);

    window->layout = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_box_pack_start(GTK_BOX(window->layout), window->viewport, TRUE, TRUE, 0);

    g_action_map_add_action_entries(G_ACTION_MAP(window), actions,
        G_N_ELEMENTS(actions), window);

    gtk_window_set_title(GTK_WINDOW(window), "Editor");
    gtk_window_set_default_size(GTK_WINDOW(window), 640, 480);
    gtk_container_add(GTK_CONTAINER(window), window->layout);
    gtk_widget_show_all(window->layout);
}
