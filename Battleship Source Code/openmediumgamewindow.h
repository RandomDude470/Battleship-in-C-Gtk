#include "var.h"
#include<stdio.h>
#include <stdlib.h>
#include<time.h>
#include <windows.h>
#include <gtk/gtk.h>
int turn=0;
int haswon;
int ships[5]={1,2,3,4,5};
int counter=0;
gpointer buttons_right[7][7];
gpointer buttons_left[7][7];
gpointer win;
gpointer winwin;
gpointer losewin;
int pcgamestate[7][7]={{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0}};
void updategameboard(){
  for (int i = 0; i < 7; i++)
  {
    for (int j = 0; j < 7; j++)
    {
      switch (playergamestate[j][i])
      {
      case 1:
        gtk_widget_add_css_class(GTK_WIDGET(buttons_left[i][j]),"intactboat");
        break;
      case -1:
        gtk_widget_remove_css_class(GTK_WIDGET(buttons_left[i][j]),"intactboat");
        gtk_widget_add_css_class(GTK_WIDGET(buttons_left[i][j]),"destroyedboat");
      break;
      case 2:
         gtk_widget_add_css_class(GTK_WIDGET(buttons_left[i][j]),"sea");
      default:
        break;
      }
    }
    
  }
  
}
void boom(){
  int x,y;
  x=rand()%7;
  y=rand()%7;
  while (playergamestate[x][y]==2 || playergamestate[x][y]==-1)
  {
    x=rand()%7;
    y=rand()%7;

  }
  

  if (playergamestate[x][y]==0)
  {
    playergamestate[x][y]=2;
    }else if (playergamestate[x][y]==1)
    {
      playergamestate[x][y]=-1;
    }
    
  
  
  
}
void isfinished(){
  int cpc=0,cpl=0;
  GtkWindow *wind,*winorlose;
  wind = GTK_WINDOW(win);
  for (int i = 0; i < 7; i++)
  {
    for (int j = 0; j < 7; j++)
    {
      if (pcgamestate[i][j]==1)
      {
        cpc++;
      }
      
    }
    
  }
  for (int i = 0; i < 7; i++)
  {
    for (int j = 0; j < 7; j++)
    {
      if (playergamestate[i][j]==1)
      {
        cpl++;
      }
      
    }
    
  }
  
  if (cpc==0)
  {
    printf("You Win");
    haswon=1;
    winorlose =GTK_WINDOW(losewin);
    gtk_window_destroy(GTK_WINDOW(winorlose));
    winorlose =GTK_WINDOW(winwin);
    gtk_window_present(winorlose);
    gtk_window_destroy(GTK_WINDOW(win));
    
    //gtk_window_close(GTK_WINDOW(winorlose));
    
    
  }
  if (cpl==0)
  {
    printf("you lose");
    haswon=0;
    winorlose =GTK_WINDOW(winwin);
    gtk_window_destroy(GTK_WINDOW(winorlose));
    winorlose =GTK_WINDOW(losewin);
    gtk_window_present(winorlose);
    gtk_window_destroy(GTK_WINDOW(win));
    
    // gtk_window_destroy(GTK_WINDOW(winorlose));
    


  }
  
  
  
}


void callbackrightgridbuttons(GtkButton *button,gpointer *data){
  int *p=(int*) data;
  switch (pcgamestate[p[1]][p[0]])
  {
  case -1:
    //do nothing
    break;
  case 2:
    // do nothing
  break;
  case 0:
    pcgamestate[p[1]][p[0]]=2;
    gtk_widget_add_css_class(GTK_WIDGET(button),"sea");
    turn++;
    updategameboard();
    
    boom();
    
    updategameboard();
    isfinished();

    break;
  case 1:
    pcgamestate[p[1]][p[0]]=-1;
    gtk_widget_add_css_class(GTK_WIDGET(button),"sunkenship");
    updategameboard();
    
    boom();
    updategameboard();
    isfinished();
    break;
  default:
    break;
  }
  printf("\n\n");
  for (int i = 0; i < 7; i++)
  {
    for (int j = 0; j < 7; j++)
    {
      printf("%i ",playergamestate[i][j]);
    }
     printf("\n");
 
  }
  
  
}
void destroywindow(GtkButton *button,gpointer *window){
    
    gtk_window_close(GTK_WINDOW(window));
   
}
static void css(){
    GtkCssProvider *provider;
    GdkDisplay *display;
    display = gdk_display_get_default();
    provider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(provider,"style.css");
    gtk_style_context_add_provider_for_display(display,GTK_STYLE_PROVIDER(provider),GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    g_object_unref(provider);

}
static void callback_button_click(GObject *button,gpointer *data){
  int *p;
  p=(int*) data;
  
  
  printf("\nButton clicked! \nrow: %i\ncolumn: %i",p[1]+1,p[0]+1);
  gtk_widget_add_css_class(GTK_WIDGET(button),"clicked");

}

int *validcoordinates(int counter,int hv){
    if (hv==0)
    {
        int sizeb=0;
        int blacklist[49][2];
        for (int i = 0; i < 7; i++)
        {
           for (int j = 0; j < 7; j++)
           {
                if (pcgamestate[i][j]==1)
                {
                    blacklist[sizeb][0]=i;
                    blacklist[sizeb][1]=j;
                    
                    sizeb++;
                    
                }
                                
           }
           
        }
        int goodlist[49][2];
        int sizeg=0;
        for (int i = 0; i < 7; i++)
        {
            for (int j = 0; j < 7; j++)
            {
                int c=0;
                for (int f = 0; f < sizeb; f++)
                {
                    if (((i==blacklist[f][0] && j<=blacklist[f][1] && j>=blacklist[f][1]-counter+1)||(j<0 || j>=6-counter+1)) || (i==blacklist[f][0]&&j==blacklist[f][1]))
                    {
                        c++;
                    }
                    
                }
                if (c==0){
                   goodlist[sizeg][0]=i;
                   goodlist[sizeg][1]=j;
                   sizeg++; 
                }
                
                
            }
            
        }
        
    static int luckycoo[2];
    int l=rand()%sizeg;
    luckycoo[0]=goodlist[l][0];
    luckycoo[1]=goodlist[l][1];
    return luckycoo;

        
    }
    else
    {
        int sizeb=0;
        int blacklist[49][2];
        for (int i = 0; i < 7; i++)
        {
           for (int j = 0; j < 7; j++)
           {
                if (pcgamestate[i][j]==1)
                {
                    blacklist[sizeb][0]=i;
                    blacklist[sizeb][1]=j;
                    
                    sizeb++;
                    
                }
                                
           }
           
        }
        int goodlist[49][2];
        int sizeg=0;
        for (int i = 0; i < 7; i++)
        {
            for (int j = 0; j < 7; j++)
            {
                int c=0;
                for (int f = 0; f < sizeb; f++)
                {
                    if (((j==blacklist[f][1] && i<=blacklist[f][0] && i>=blacklist[f][0]-counter+1)||(i<0 || i>=6-counter+1)) || (i==blacklist[f][0]&&j==blacklist[f][1]))
                    {
                        c++;
                    }
                    
                }
                if (c==0){
                   goodlist[sizeg][0]=i;
                   goodlist[sizeg][1]=j;
                   sizeg++; 
                }
                
                
            }
            
        }
        
    static int luckycoo[2];
    int l=rand()%sizeg;
    luckycoo[0]=goodlist[l][0];
    luckycoo[1]=goodlist[l][1];
    return luckycoo;

    }
    
}

G_MODULE_EXPORT void openmediumgamewindow(GtkButton *button,gpointer *app){

  //======================================INISIALIZING SHIPS IN MACHINE GRID==============================================
    srand(time(NULL));   // Initialization, should only be called once.
            
    for (counter=1;counter<6;counter++){
        int h_v=rand()%2;
        int *valid=validcoordinates(counter,h_v);
        printf("%i %i \"%i\" ",*valid,*(valid+1),h_v);
        for (int i=0;i<counter;i++){
            if(h_v==0){
                pcgamestate[*valid][*(valid+1)+i]=1;
                
            }else{
                pcgamestate[*(valid)+i][*(valid+1)]=1;
            }
        }

    }printf("\n\n\n");

    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            printf("%i ",pcgamestate[i][j]);
        }
        printf("\n");
    }
  //======================================INITIALIZING SHIPS IN MACHINE GRID==============================================


  css();
  // Builder setup
  GtkBuilder *builder;
  builder = gtk_builder_new();
  gtk_builder_add_from_file(builder,"builder.ui",NULL);
  GtkBuilder *builderwin;
  builderwin=gtk_builder_new();
  gtk_builder_add_from_file(builderwin,"builderwin.ui",NULL);
  GObject *winwin1;
  winwin1 =gtk_builder_get_object(builderwin, "windowwin");
  gtk_window_set_application(GTK_WINDOW(winwin1),GTK_APPLICATION(app));
  winwin=(gpointer) winwin1;
  GtkBuilder *builderlose;
  builderlose=gtk_builder_new();
  gtk_builder_add_from_file(builderlose,"builderlose.ui",NULL);
  GObject *losewin1;
  losewin1 =gtk_builder_get_object(builderlose, "windowlose");
  gtk_window_set_application(GTK_WINDOW(losewin1),GTK_APPLICATION(app));
  losewin=(gpointer) losewin1;
   
   // Importing the window from the builder+setting size an title
  GObject *window;
  window = gtk_builder_get_object(builder, "window");
  gtk_window_set_application(GTK_WINDOW(window),GTK_APPLICATION(app));
  gtk_window_set_default_size(GTK_WINDOW(window),800,600);
  gtk_window_set_resizable(GTK_WINDOW(window),false);
  win= (gpointer) window;
  
  // making a gtkbox pointer  variable that will contain our grid ---------Box1---------------
  GObject *box;
  box = gtk_builder_get_object(builder,"box");
  
 // ----------------------------------------------------------------------Grid----------------
  GObject *grid;
  grid=gtk_builder_get_object(builder,"grid");
  
  gtk_widget_set_valign(GTK_WIDGET(grid),GTK_ALIGN_CENTER);
  gtk_widget_set_halign(GTK_WIDGET(grid),GTK_ALIGN_CENTER);
   gtk_widget_set_opacity(GTK_WIDGET(grid),0.7);
//----------------------------------------------------------------------box2--------------------------
  //  GObject *box2;
  // box2=gtk_builder_get_object(builder,"box2");
  // gtk_box_set_homogeneous(GTK_BOX(box),TRUE);
  // gtk_widget_set_size_request(GTK_WIDGET(window),800,600);

//----------------------------------------------------------Grid2-------------------------------------
  grid=gtk_builder_get_object(builder,"grid2");
  
  gtk_widget_set_valign(GTK_WIDGET(grid),GTK_ALIGN_CENTER);
  gtk_widget_set_halign(GTK_WIDGET(grid),GTK_ALIGN_CENTER);
   gtk_widget_set_opacity(GTK_WIDGET(grid),0.7);

//-----------------------------------------------------------buttons------------------------------
for (int i=0;i<7;i++){
        for (int j=0;j<7;j++){   
            char butto[12]="button";
            char iconv[30]="";
            char jconv[30]="";
            sprintf(iconv,"%i",i+7);
            sprintf(jconv,"%i",j+7);
            strcat(butto,iconv);
            strcat(butto,jconv);
            
            GObject *button;
            button = gtk_builder_get_object(builder,butto);
            
            static int tab[7][7][2];
            tab[i][j][0]=i;
            tab[i][j][1]=j;
            buttons_right[i][j]=(gpointer) button;
            
            g_signal_connect(button,"clicked",G_CALLBACK(callbackrightgridbuttons),(gpointer) tab[i][j]);

            char butto1[12]="button";
            char iconv1[30]="";
            char jconv1[30]="";
            sprintf(iconv1,"%i",i);
            sprintf(jconv1,"%i",j);
            strcat(butto1,iconv1);
            strcat(butto1,jconv1);
            button = gtk_builder_get_object(builder,butto1);
            buttons_left[i][j]=(gpointer) button;
            
            
            
        }
       
    }
 
//--------------------------------------------------------Window Present----------------------------  
  gtk_window_present (GTK_WINDOW(window));
  g_object_unref(builder);
  g_object_unref(builderwin);
  g_object_unref(builderlose);
    
}
