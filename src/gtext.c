#include <errno.h>
#include <string.h>
#include "gtext-app.h"
#include "gtext-css.h"

int main(int argc, char* argv[]) {
    GTextApp* app;
    int status;

    gtk_init(&argc, &argv);
    gtext_css_init();

    app = gtext_app_new();
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}
