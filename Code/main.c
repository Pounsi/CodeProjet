#include "../Headers/InterfaceGraphique.h" 


int main(int argc, char **argv)
{
    gtk_init(&argc, &argv);
    GError **err;
    Fenetre = gtk_window_new(GTK_WINDOW_TOPLEVEL); 
    gtk_rc_parse("Ressources/theme");
    gtk_window_set_title(GTK_WINDOW(Fenetre), "Dcrypt");
    gtk_window_set_default_size(GTK_WINDOW(Fenetre), largeur, hauteur);
    gtk_window_set_icon_from_file(GTK_WINDOW(Fenetre),"Ressources/logo.png", err);

    g_signal_connect(G_OBJECT(Fenetre), "destroy", G_CALLBACK(gtk_main_quit), NULL);
    
    MenuPrincipal(Fenetre);
 
    gtk_main();
    return EXIT_SUCCESS;
}
