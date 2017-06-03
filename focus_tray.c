#include "focus_tray.h"
#include "focus_config.h"


void (*onclick_callback) (int);
char * notif_title;

GtkWidget *menu;
GtkWidget *quit_item, *about_item, *clickme_item, *pause_item;
u_int8_t is_pause = 0;

static void on_item_clicked(GtkWidget *item,
			    gpointer user_data)
{
    if(item == about_item)
    {
	GStrv authors[] = {AUTHOR_NAME " " AUTHOR_EMAIL,}; 
	gtk_show_about_dialog (NULL,
			       "program-name", APP_NAME,
			       "logo-icon-name",APP_LOGO,
			       "license-type",GTK_LICENSE_GPL_2_0,
			       "authors",authors,
			       "copyright",COPYRIGHT,
			       "comments",COMMENTS,
			       "website" , WEBSITE,
			       "website-label","Github",
			       NULL);
    }
    else if(item == quit_item)
	onclick_callback(TRAY_QUIT);
    else if(item == clickme_item)
	onclick_callback(TRAY_CLICKED);
    else if(item == pause_item)
    {
	is_pause = !is_pause;
	if(is_pause)
	{
	    gtk_menu_item_set_label(pause_item,"Unpause");
	    onclick_callback(TRAY_PAUSE);

	}else
	{
	    gtk_menu_item_set_label(pause_item,"Pause");
	    onclick_callback(TRAY_UNPAUSE);
	}
    }
}


void create_menu(){
   
    menu = gtk_menu_new();

    char * title = malloc(sizeof(char) * (strlen("title ")+ strlen(notif_title)));
    strcpy(title,"Title: ");
    //adding title of the notifcation to distigush between multi-run of this app
    gtk_menu_shell_append (GTK_MENU_SHELL (menu), gtk_menu_item_new_with_label (strcat(title,notif_title)));
    
    pause_item = gtk_menu_item_new_with_label ("Pause");
    gtk_menu_shell_append (GTK_MENU_SHELL (menu), pause_item);
    g_signal_connect(pause_item, "activate", G_CALLBACK(on_item_clicked), NULL);

    clickme_item = gtk_menu_item_new_with_label ("Click me!");
    gtk_menu_shell_append (GTK_MENU_SHELL (menu), clickme_item);
    g_signal_connect(clickme_item, "activate", G_CALLBACK(on_item_clicked), NULL);
    
    about_item = gtk_menu_item_new_with_label ("About");
    gtk_menu_shell_append (GTK_MENU_SHELL (menu), about_item);
    g_signal_connect(about_item, "activate", G_CALLBACK(on_item_clicked), NULL);
    
    quit_item = gtk_menu_item_new_with_label ("Quit");
    gtk_menu_shell_append (GTK_MENU_SHELL (menu), quit_item);
    g_signal_connect(quit_item, "activate", G_CALLBACK(on_item_clicked), NULL);
    
    gtk_widget_show_all(menu);
    free(title);
}


static void create_tray_icon() {

    AppIndicator *indicator;
    
    indicator = app_indicator_new (APP_NAME,
				   APP_LOGO,
                                   APP_INDICATOR_CATEGORY_APPLICATION_STATUS);
    app_indicator_set_status (indicator, APP_INDICATOR_STATUS_ACTIVE);
    create_menu();
    app_indicator_set_attention_icon (indicator, APP_NAME);
    app_indicator_set_menu (indicator, GTK_MENU (menu));
}




void intiate_tray_icon(char* title,void(*click_callback)(int))
{
    notif_title = title;
    onclick_callback = click_callback;
    create_tray_icon();
}

