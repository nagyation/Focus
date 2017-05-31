#include "focustray.h"


void (*onclick_callback) (int);
GtkWidget *menu;


static void tray_icon_on_click(GtkStatusIcon *status_icon, 
			       gpointer user_data)
{
    onclick_callback(CLICKED);
}

static void on_item_clicked(GtkWidget *item,
			    gpointer user_data)
{
    onclick_callback(QUIT);
}


void create_menu(){
    GtkWidget *quit_item;
    menu = gtk_menu_new();
    quit_item = gtk_menu_item_new_with_label ("Quit");
    gtk_menu_shell_append (GTK_MENU_SHELL (menu), quit_item);
   g_signal_connect(quit_item, "activate", G_CALLBACK(on_item_clicked), NULL);

     gtk_widget_show_all(menu);
}


void tray_icon_on_menu(GtkStatusIcon *status_icon, guint button, 
                       guint activate_time, gpointer user_data)
{
        gtk_menu_popup(GTK_MENU(menu), NULL, NULL, NULL, NULL,
		       0, gtk_get_current_event_time());
}


static GtkStatusIcon *intiate_tray_icon() {
    GtkStatusIcon *tray_icon;
    
    tray_icon = gtk_status_icon_new_from_file( "/usr/local/share/focus/focus_icon.png");
    gtk_status_icon_set_from_icon_name(tray_icon, 
				   GTK_STOCK_MEDIA_STOP);
//    gtk_status_icon_set_tooltip(tray_icon, 
//                                    "Focus!");
    gtk_status_icon_set_visible(tray_icon, TRUE);

    g_signal_connect(G_OBJECT(tray_icon), "activate", 
                         G_CALLBACK(tray_icon_on_click), NULL);
    g_signal_connect(G_OBJECT(tray_icon), 
		     "popup-menu",
		     G_CALLBACK(tray_icon_on_menu), NULL);
    create_menu();
    return tray_icon;
}




GtkStatusIcon *create_tray_icon(void(*click_callback)(int))
{
    onclick_callback = click_callback;
    return intiate_tray_icon();
}

