#include "gtext-app.h"
#include "gtext-css.h"

int main(int argc, char* argv[]) {
    GtkApplication* app;
    int status;

    app = gtext_app_create();
    gtext_app_load_css(app, gtext_css_len, gtext_css);
    status = gtext_app_run(app, argc, argv);
    gtext_app_destroy(app);

    return status;
}
