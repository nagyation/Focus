#include "focus_tray.h"
#include "focus_config.h"


void (*onclick_callback) (int);

GtkWidget *menu;
GtkWidget *quit_item, *about_item, *clickme_item;

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
			       "website-label","GITHUB",
			       NULL);
    }
    else if(item == quit_item)
	onclick_callback(QUIT);
    else if(item == clickme_item)
	onclick_callback(CLICKED);
}


void create_menu(){
   
    menu = gtk_menu_new();

    about_item = gtk_menu_item_new_with_label ("About");
    gtk_menu_shell_append (GTK_MENU_SHELL (menu), about_item);
    g_signal_connect(about_item, "activate", G_CALLBACK(on_item_clicked), NULL);

    clickme_item = gtk_menu_item_new_with_label ("Click me!");
    gtk_menu_shell_append (GTK_MENU_SHELL (menu), clickme_item);
    g_signal_connect(clickme_item, "activate", G_CALLBACK(on_item_clicked), NULL);
    
    quit_item = gtk_menu_item_new_with_label ("Quit");
    gtk_menu_shell_append (GTK_MENU_SHELL (menu), quit_item);
    g_signal_connect(quit_item, "activate", G_CALLBACK(on_item_clicked), NULL);
    
     gtk_widget_show_all(menu);
}


static void intiate_tray_icon() {

    AppIndicator *indicator;
    
    indicator = app_indicator_new (APP_NAME,
				   APP_LOGO,
                                   APP_INDICATOR_CATEGORY_APPLICATION_STATUS);
    app_indicator_set_status (indicator, APP_INDICATOR_STATUS_ACTIVE);
    create_menu();
    app_indicator_set_attention_icon (indicator, APP_NAME);
    app_indicator_set_menu (indicator, GTK_MENU (menu));
}




void create_tray_icon(void(*click_callback)(int))
{
    onclick_callback = click_callback;
    intiate_tray_icon();
}

