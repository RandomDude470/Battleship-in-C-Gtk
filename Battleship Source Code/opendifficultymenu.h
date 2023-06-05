#include <gtk/gtk.h>
#include "inputwindow.h"
#include "hardinputwindow.h"
void diffwindow(GtkButton *,gpointer *);
void diffwindow(GtkButton *button,gpointer *app){
    GtkCssProvider *provider;
    GdkDisplay *display;
    display = gdk_display_get_default();
    provider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(provider,"style2.css");
    gtk_style_context_add_provider_for_display(display,GTK_STYLE_PROVIDER(provider),GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    g_object_unref(provider);
    GtkBuilder *builder;
    
    builder = gtk_builder_new();
    gtk_builder_add_from_file(builder,"builderex.ui",NULL);
    GObject *window;
    window = gtk_builder_get_object(builder,"window");
    gtk_window_set_application(GTK_WINDOW(window),GTK_APPLICATION(app));
    
    //----------------------buttons-----------------------
    GObject *buttonx;
    buttonx = gtk_builder_get_object(builder,"easybutton");
    g_signal_connect(buttonx,"clicked",G_CALLBACK(inputwindow),(gpointer) app);
    g_signal_connect(buttonx,"clicked",G_CALLBACK(destroywindow),(gpointer) window);
    buttonx = gtk_builder_get_object(builder,"hardbutton");
    g_signal_connect(buttonx,"clicked",G_CALLBACK(hardinputwindow),(gpointer) app);
    g_signal_connect(buttonx,"clicked",G_CALLBACK(destroywindow),(gpointer) window);
    gtk_window_present(GTK_WINDOW(window));
    g_object_unref(builder);

}