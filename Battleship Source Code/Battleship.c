#include<gtk/gtk.h>
#include<stdio.h>
#include <stdlib.h>


#include "opendifficultymenu.h"
gpointer appc;
G_MODULE_EXPORT  void whoclickedme(GObject *button,gpointer data){
    int *number;
    number =(int*) data;
    int p=*number;
    printf("Number: %i\n", p);
   
}
void rulebook(GtkButton*butt,gpointer *da){
    GtkWidget *wiii;
    wiii = gtk_application_window_new(GTK_APPLICATION(appc));
    gtk_window_set_application(GTK_WINDOW(wiii),GTK_APPLICATION(appc));
    gtk_window_set_title(GTK_WINDOW(wiii),"RULES");
    gtk_window_set_default_size(GTK_WINDOW(wiii),1300,848);
    gtk_widget_add_css_class(GTK_WIDGET(wiii),"rules");
    gtk_window_set_resizable(GTK_WINDOW(wiii),false);
    gtk_window_present(GTK_WINDOW(wiii));

}




static void css1(){
    GtkCssProvider *provider;
    GdkDisplay *display;
    display = gdk_display_get_default();
    provider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(provider,"style1.css");
    gtk_style_context_add_provider_for_display(display,GTK_STYLE_PROVIDER(provider),GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    g_object_unref(provider);

}


static void activate(GtkApplication *app,gpointer user_data){
    css1();
    GtkWidget *window;
    GtkBuilder *builder1;
    builder1 = gtk_builder_new();
    gtk_builder_add_from_file(builder1,"builder1.ui",NULL);
    window = GTK_WIDGET(gtk_builder_get_object(builder1,"window"));
    gtk_window_set_application(GTK_WINDOW(window),app);
    gtk_window_set_title(GTK_WINDOW(window),"Menu");
    gtk_window_set_default_size(GTK_WINDOW(window),490*1.3,710*1.3);
    gtk_window_set_resizable(GTK_WINDOW(window),false);
    //----------button------------------------------------------
    GObject *startbutton;
    startbutton = gtk_builder_get_object(builder1,"startbutton");
     GObject *quitbutton;
    quitbutton = gtk_builder_get_object(builder1,"quitbutton");
    g_signal_connect(startbutton,"clicked",G_CALLBACK(diffwindow),(gpointer) app);
    g_signal_connect(startbutton,"clicked",G_CALLBACK(destroywindow),(gpointer) window);
    g_signal_connect(quitbutton,"clicked",G_CALLBACK(destroywindow),(gpointer) window);
    quitbutton = gtk_builder_get_object(builder1,"rulesbutton");
    g_signal_connect(quitbutton,"clicked",G_CALLBACK(rulebook),NULL);

   
    
    

    //----------------------------------------------------------
    gtk_window_present(GTK_WINDOW(window));
    
    g_object_unref(builder1);
    
    
}
int main(int argc,char **argv){
    int status;
    
    GtkApplication *app9;
    appc= (gpointer) app9;
    app9 =gtk_application_new("org.example.new",G_MARKUP_DEFAULT_FLAGS);
     appc= (gpointer) app9;
    g_signal_connect(app9,"activate",G_CALLBACK(activate),NULL);
    status=g_application_run(G_APPLICATION(app9),argc,argv);
    g_object_unref(app9);
    return status;
}