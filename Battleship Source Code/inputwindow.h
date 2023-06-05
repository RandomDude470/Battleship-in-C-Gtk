#include <gtk/gtk.h>
#include "openmediumgamewindow.h"
int playergamestate[7][7]={{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0}};
int hor_or_ver=0;
int ship[6]={1,2,3,4,5,0};
int compteur_bateau=0;
gulong handler_id;

gpointer allbuttons[7][7];
gpointer windowg;
gpointer appg;
gpointer startbutton;
void printh(void){
    g_print("hello");
}
void changeorientation(GtkButton *button,gpointer *data){
    if (hor_or_ver)
        hor_or_ver=0;
    else 
        hor_or_ver=1;

}
void secondcallback(GtkButton *button, gpointer *data){
    
    for (int i=0;i<7;i++){
                for (int j=0;j<7;j++){
                    if (playergamestate[i][j]==1){
                   
                    
                    char butto[12]="button";
                    char iconv[30]="";
                    char jconv[30]="";
                    sprintf(iconv,"%i",i);
                    sprintf(jconv,"%i",j);
                    strcat(butto,iconv);
                    strcat(butto,jconv);
                    
                    
                    GtkButton *nbutton;
                    
                    nbutton = GTK_BUTTON(allbuttons[j][i]);
                    gtk_widget_add_css_class(GTK_WIDGET(nbutton),"clicked");
                    
                    
                    }
                }
            }
}

void callback_button_click1(GObject *button,gpointer *data){
        int *p;
        p=(int*) data;
        int h_ok=0,v_ok=0;
        int c=0,v=0;
        
        for (int i = 1; i < ship[compteur_bateau] ;i++)
        {
            if (playergamestate[p[1]][p[0]+i]==1 || 6-p[0]+1<ship[compteur_bateau] )
            {
                c++;
            }
            
        }
        for (int i = 1; i < ship[compteur_bateau] ;i++)
        {
            if (playergamestate[p[1]+i][p[0]]==1 || 6-p[1]+1<ship[compteur_bateau])
            {
                v++;
            }
            
        }
        if (c==0)
        {
            h_ok=1;
        }
        if (v==0)
        {
            v_ok=1;
        }
        
        
        
        

        if (playergamestate[p[1]][p[0]]==0 && hor_or_ver==0 && h_ok){
            for (int i=0;i<ship[compteur_bateau];i++){
                    playergamestate[p[1]][p[0]+i]=1;
                }
            if (compteur_bateau<4)  compteur_bateau=compteur_bateau+1;
            else    {
                compteur_bateau=5;
                g_signal_handler_block(startbutton,handler_id);
                g_signal_connect(startbutton,"clicked",G_CALLBACK(openmediumgamewindow), appg);
                g_signal_connect(startbutton,"clicked",G_CALLBACK(destroywindow), windowg);

                }
        
        }else if(playergamestate[p[1]][p[0]]==0 && hor_or_ver==1 && v_ok){
            for (int i=0;i<ship[compteur_bateau];i++){
                playergamestate[p[1]+i][p[0]]=1;
            }
            if (compteur_bateau<4)  compteur_bateau=compteur_bateau+1;
            else    {
                compteur_bateau=5;
                g_signal_handler_block(startbutton,handler_id);
                g_signal_connect(startbutton,"clicked",G_CALLBACK(openmediumgamewindow), appg);
                g_signal_connect(startbutton,"clicked",G_CALLBACK(destroywindow), windowg);
            }
        }else{
            
            
        }
        
        
        printf("\nButton clicked! \nrow: %i\ncolumn: %i\n",p[1]+1,p[0]+1);

        for (int i=0;i<7;i++){
            for (int j=0;j<7;j++){
                printf("%i ",playergamestate[i][j]);
            }
            printf("\n");
        }

        


  
    
}
void alert(GtkWindow *parent, gpointer *ata)
{
 GtkWidget *dialog, *label, *content_area;
 GtkDialogFlags flags;
  char *message="\n   You have to place all the ships   \n";
 // Create the widgets
 flags = GTK_DIALOG_DESTROY_WITH_PARENT;
 dialog = gtk_dialog_new_with_buttons ("Message",parent,flags,("_OK"),GTK_RESPONSE_NONE,NULL);
 content_area = gtk_dialog_get_content_area (GTK_DIALOG (dialog));
 label = gtk_label_new (message);
 gtk_label_set_markup(GTK_LABEL(label), "<b>\n   You have to place all the ships   \n</b>");

 // Ensure that the dialog box is destroyed when the user responds

 g_signal_connect_swapped (dialog,"response",G_CALLBACK (gtk_window_destroy),dialog);

 // Add the label, and show everything we’ve added

 gtk_box_append (GTK_BOX (content_area), label);
 gtk_window_set_resizable(GTK_WINDOW(dialog),FALSE);
 gtk_window_set_default_size(GTK_WINDOW(dialog),300,100);
 gtk_window_set_modal(GTK_WINDOW(dialog),true);
 gtk_widget_add_css_class(dialog,"alert");
 gtk_widget_show (dialog);
}


void inputwindow(GtkButton *button,gpointer *app){
    appg=app;
    GtkCssProvider *provider;
    GdkDisplay *display;
    display = gdk_display_get_default();
    provider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(provider,"style3.css");
    gtk_style_context_add_provider_for_display(display,GTK_STYLE_PROVIDER(provider),GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    g_object_unref(provider);
    GtkBuilder *builder;
    
    builder = gtk_builder_new();
    gtk_builder_add_from_file(builder,"inputgrillbuilder.ui",NULL);
    GObject *window;
    window = gtk_builder_get_object(builder,"window");
    gtk_window_set_application(GTK_WINDOW(window),GTK_APPLICATION(app));
    windowg=  window;
    
    
 //===============BUttons==========   

    for (int i=0;i<7;i++){
        for (int j=0;j<7;j++){   
            char butto[12]="button";
            char iconv[30]="";
            char jconv[30]="";
            sprintf(iconv,"%i",i);
            sprintf(jconv,"%i",j);
            strcat(butto,iconv);
            strcat(butto,jconv);
            
            GObject *button1;
            button1 = gtk_builder_get_object(builder,butto);
            
            static int tab[7][7][2];
            tab[i][j][0]=i;
            tab[i][j][1]=j;
            
            allbuttons[i][j]= (gpointer) button1;

           
            g_signal_connect(button1,"clicked",G_CALLBACK(callback_button_click1),(gpointer) tab[i][j]);
            g_signal_connect(button1,"clicked",G_CALLBACK(secondcallback),NULL);
            
            
            
            
        }
      
    }
    GObject *button2;
    button2 = gtk_builder_get_object(builder,"h_or_v_button");
    g_signal_connect(button2,"clicked",G_CALLBACK(changeorientation),NULL);
    button2 = gtk_builder_get_object(builder,"start");
    startbutton =(gpointer) button2;
    handler_id = g_signal_connect(button2,"clicked",G_CALLBACK(alert),NULL);
    
    
    

    gtk_window_present(GTK_WINDOW(window));
    g_object_unref(builder);
}
