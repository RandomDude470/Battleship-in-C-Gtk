#include <gtk/gtk.h>
#include "openhardgamewindow.h"
int playergamestate1[10][10]={{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0}};
int hor_or_ver1=0;
int ship1[6]={1,2,3,4,5,0};
int compteur_bateau1=0;

gpointer allbuttons1[10][10];
gpointer windowg;

void changeorientation1(GtkButton *button,gpointer *data){
    if (hor_or_ver1)
        hor_or_ver1=0;
    else 
        hor_or_ver1=1;

}
void secondcallback1(GtkButton *button, gpointer *data){
    
    for (int i=0;i<10;i++){
                for (int j=0;j<10;j++){
                    if (playergamestate1[i][j]==1){
                   
                    
                    char butto[12]="button";
                    char iconv[30]="";
                    char jconv[30]="";
                    sprintf(iconv,"%i",i);
                    sprintf(jconv,"%i",j);
                    strcat(butto,iconv);
                    strcat(butto,jconv);
                    
                    
                    GtkButton *nbutton;
                    
                    nbutton = GTK_BUTTON(allbuttons1[j][i]);
                    gtk_widget_add_css_class(GTK_WIDGET(nbutton),"clicked");
                    
                    
                    }
                }
            }
}

void callback_button_click11(GObject *button,gpointer *data){
        int *p;
        p=(int*) data;
        int h_ok=0,v_ok=0;
        int c=0,v=0;
        
        for (int i = 1; i < ship1[compteur_bateau1] ;i++)
        {
            if (playergamestate1[p[1]][p[0]+i]==1 || 9-p[0]+1<ship1[compteur_bateau1] )
            {
                c++;
            }
            
        }
        for (int i = 1; i < ship1[compteur_bateau1] ;i++)
        {
            if (playergamestate1[p[1]+i][p[0]]==1 || 9-p[1]+1<ship1[compteur_bateau1])
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
        
        
        
        

        if (playergamestate1[p[1]][p[0]]==0 && hor_or_ver1==0 && h_ok){
            for (int i=0;i<ship1[compteur_bateau1];i++){
                    playergamestate1[p[1]][p[0]+i]=1;
                }
            if (compteur_bateau1<4)  compteur_bateau1=compteur_bateau1+1;
            else    compteur_bateau1=5;
        
        }else if(playergamestate1[p[1]][p[0]]==0 && hor_or_ver1==1 && v_ok){
            for (int i=0;i<ship1[compteur_bateau1];i++){
                playergamestate1[p[1]+i][p[0]]=1;
            }
            if (compteur_bateau1<4)  compteur_bateau1=compteur_bateau1+1;
            else    compteur_bateau1=5;
        }else{
            
            
        }
        
        
        printf("\nButton clicked! \nrow: %i\ncolumn: %i\n",p[1]+1,p[0]+1);

        for (int i=0;i<10;i++){
            for (int j=0;j<10;j++){
                printf("%i ",playergamestate1[i][j]);
            }
            printf("\n");
        }

        


  
    
}



void hardinputwindow(GtkButton *button,gpointer *app){
    GtkCssProvider *provider;
    GdkDisplay *display;
    display = gdk_display_get_default();
    provider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(provider,"style3.css");
    gtk_style_context_add_provider_for_display(display,GTK_STYLE_PROVIDER(provider),GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    g_object_unref(provider);
    GtkBuilder *builder;
    
    builder = gtk_builder_new();
    gtk_builder_add_from_file(builder,"hardinputgridbuilder.ui",NULL);
    GObject *window;
    window = gtk_builder_get_object(builder,"window");
    gtk_window_set_application(GTK_WINDOW(window),GTK_APPLICATION(app));
    windowg= (gpointer) window;
    
    
 //===============BUttons==========   

    for (int i=0;i<10;i++){
        for (int j=0;j<10;j++){   
            char butto[12]="button";
            char iconv[30]="";
            char jconv[30]="";
            sprintf(iconv,"%i",i);
            sprintf(jconv,"%i",j);
            strcat(butto,iconv);
            strcat(butto,jconv);
            
            GObject *button1;
            button1 = gtk_builder_get_object(builder,butto);
            
            static int tab[10][10][2];
            tab[i][j][0]=i;
            tab[i][j][1]=j;
            
            allbuttons1[i][j]= (gpointer) button1;

           
            g_signal_connect(button1,"clicked",G_CALLBACK(callback_button_click11),(gpointer) tab[i][j]);
            g_signal_connect(button1,"clicked",G_CALLBACK(secondcallback1),NULL);
            
            
            
            
        }
      
    }
    GObject *button2;
    button2 = gtk_builder_get_object(builder,"h_or_v_button");
    g_signal_connect(button2,"clicked",G_CALLBACK(changeorientation1),NULL);
    button2 = gtk_builder_get_object(builder,"start");
    g_signal_connect(button2,"clicked",G_CALLBACK(openhardgamewindow),(gpointer) app);
    g_signal_connect(button2,"clicked",G_CALLBACK(destroywindow1),(gpointer) window);
    
    

    gtk_window_present(GTK_WINDOW(window));
    g_object_unref(builder);
}
