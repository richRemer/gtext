#ifndef GTEXT_CSS_H
#define GTEXT_CSS_H

#include <gtk/gtk.h>

extern unsigned char gtext_css[];
extern unsigned int gtext_css_len;

void gtext_css_init();
void gtext_css_style_widget(GtkWidget* widget, const char* css_class);

#endif
