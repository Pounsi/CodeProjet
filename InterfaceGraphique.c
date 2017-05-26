#include "InterfaceGraphique.h"




void MenuResultatDecryptagePartielVig(GtkWidget *Fenetre)
{
    
    Fenetre = gtk_widget_get_toplevel (Fenetre);
    ViderContenaire(GTK_CONTAINER(Fenetre));
    GtkWidget *Box,*Box2, *Label,*Label2,*Label_retour,*Bouton1, *Bouton2;
    gchar *Text;
    gchar Text_crypt[TAILLETEXTE];
    
    FILE *fichier=NULL;
    fichier=fopen("text.txt","r");

            if (fichier != NULL)
            {
                fgets(Text_crypt,TAILLETEXTE,fichier);
                 fclose(fichier);
                
            }
    
    

    DOUBLEC *Donnees;
    Donnees=(DOUBLEC *)malloc(sizeof(DOUBLEC));

    DecryptageVigenere(Donnees->texte,Text_crypt,Donnees->cle);
    
    gchar text_affichage[TAILLETEXTE]; 
    RetourALaLigne(text_affichage,Donnees->texte);
    
    

    Box = gtk_vbox_new(FALSE, 0);
    gtk_container_add(GTK_CONTAINER(Fenetre), Box);

    Label=gtk_label_new(NULL);
    Text = g_locale_to_utf8("<span font_desc=\"Times New Roman italic 12\" foreground=\"#1d1d1d\">Menu Dechiffrement partiel de Vigenere</span>\n",
    -1, NULL, NULL, NULL);
    gtk_label_set_markup(GTK_LABEL(Label), Text);
    g_free(Text);
    gtk_label_set_justify(GTK_LABEL(Label), GTK_JUSTIFY_CENTER);

    gtk_box_pack_start(GTK_BOX(Box), Label, TRUE, TRUE, 0);
    
    Label2=gtk_label_new(text_affichage);
    gtk_label_set_justify(GTK_LABEL(Label2), GTK_JUSTIFY_CENTER);
    gtk_box_pack_start(GTK_BOX(Box), Label2, TRUE, TRUE, 0);
    
    Label2=gtk_label_new(Donnees->cle);
    gtk_label_set_justify(GTK_LABEL(Label2), GTK_JUSTIFY_CENTER);
    gtk_box_pack_start(GTK_BOX(Box), Label2, TRUE, TRUE, 0);
    
    
    Box2 = gtk_hbox_new(TRUE, 0);
    gtk_container_add(GTK_CONTAINER(Box), Box2);
    
    Bouton1 = gtk_button_new_with_label("Redechiffrer");
    g_signal_connect(G_OBJECT(Bouton1), "clicked", G_CALLBACK(MenuResultatDecryptagePartielVig), NULL);
    gtk_box_pack_start(GTK_BOX(Box2), Bouton1, TRUE, TRUE, 0);
    
    
    Bouton2 = gtk_button_new_with_label("Terminer");
    g_signal_connect(G_OBJECT(Bouton2), "clicked", G_CALLBACK(MenuResultatDecryptageVigenere), Donnees);
    gtk_box_pack_start(GTK_BOX(Box2), Bouton2, TRUE, TRUE, 0);
    
    gtk_widget_show_all(Fenetre);
}

void MenuResultatDecryptagePartiel(GtkWidget *Fenetre,DOUBLEC *Donnees)
{
    
    Fenetre = gtk_widget_get_toplevel (Fenetre);
    ViderContenaire(GTK_CONTAINER(Fenetre));
    GtkWidget *Box,*Box2, *Label,*Label2,*Label_retour,*Bouton2, *Bouton3;
    int taille=TAILLETEXTE;
    gchar *Text;
    gchar *tmp[TAILLETEXTE];
    ConvertisseurTableau(tmp,&taille,Donnees->texte);
    
    DechiffreSubstitution(tmp,Donnees->cle);

    gchar text_affichage[TAILLETEXTE]; 
    RetourALaLigne(text_affichage,tmp);

    Box = gtk_vbox_new(FALSE, 0);
    gtk_container_add(GTK_CONTAINER(Fenetre), Box);

    Label=gtk_label_new(NULL);
    Text = g_locale_to_utf8("<span font_desc=\"Times New Roman italic 12\" foreground=\"#1d1d1d\">Menu Dechiffrement partiel</span>\n",
    -1, NULL, NULL, NULL);
    gtk_label_set_markup(GTK_LABEL(Label), Text);
    g_free(Text);
    gtk_label_set_justify(GTK_LABEL(Label), GTK_JUSTIFY_CENTER);

    gtk_box_pack_start(GTK_BOX(Box), Label, TRUE, TRUE, 0);
    
    Label2=gtk_label_new(text_affichage);
    gtk_label_set_justify(GTK_LABEL(Label2), GTK_JUSTIFY_CENTER);
    gtk_box_pack_start(GTK_BOX(Box), Label2, TRUE, TRUE, 0);
    
    Label2=gtk_label_new(Donnees->cle);
    gtk_label_set_justify(GTK_LABEL(Label2), GTK_JUSTIFY_CENTER);
    gtk_box_pack_start(GTK_BOX(Box), Label2, TRUE, TRUE, 0);
    
    Label2=gtk_label_new("Legende");
    gtk_label_set_justify(GTK_LABEL(Label2), GTK_JUSTIFY_CENTER);
    gtk_box_pack_start(GTK_BOX(Box), Label2, TRUE, TRUE, 0);
    
    Box2 = gtk_hbox_new(TRUE, 0);
    gtk_container_add(GTK_CONTAINER(Box), Box2);
    
    
    Bouton2 = gtk_button_new_with_label("Changer la cle");
    g_signal_connect(G_OBJECT(Bouton2), "clicked", G_CALLBACK(BoiteDialogueChangerLaCleSubstitution), Donnees);
    gtk_box_pack_start(GTK_BOX(Box2), Bouton2, TRUE, TRUE, 0);
    
    Bouton3 = gtk_button_new_with_label("Terminer");
    g_signal_connect(G_OBJECT(Bouton3), "clicked", G_CALLBACK(MenuResultatDecryptageSubstitution), Donnees);
    gtk_box_pack_start(GTK_BOX(Box2), Bouton3, TRUE, TRUE, 0);
    
    gtk_widget_show_all(Fenetre);
}

void BoiteDialogueChangerLaCleSubstitution(GtkWidget *Fenetre,DOUBLEC *Donnees)
{

        GtkWidget *Boite,*Entrer,*Entrer_cle,*Label_text,*Label_cle;
        gchar *C1,*C2,*msg,*indication_cle;
        GtkTextBuffer* Buffer;
        GtkTextIter debut;
        GtkTextIter fin;
        Fenetre = gtk_widget_get_toplevel (Fenetre);//on passe a la fenetre du bouton 
        Boite = gtk_dialog_new_with_buttons("Sasie du texte",GTK_WINDOW(Fenetre),GTK_DIALOG_MODAL,GTK_STOCK_OK,GTK_RESPONSE_OK,GTK_STOCK_CANCEL,GTK_RESPONSE_CANCEL,NULL);

        Label_text=gtk_label_new(NULL);
        Label_cle=gtk_label_new(NULL);
        
            msg= g_locale_to_utf8("<span font_desc=\"Times New Roman italic 12\" foreground=\"#1d1d1d\">Votre caractere à changer : </span>\n",
               -1, NULL, NULL, NULL);
       

        indication_cle = g_locale_to_utf8("<span font_desc=\"Times New Roman italic 12\" foreground=\"#1d1d1d\">Par ce caractere :\n(EN MAJUSCULE)    </span>\n",
               -1, NULL, NULL, NULL);
        
       
            
            Entrer= gtk_text_view_new();

            gtk_label_set_markup(GTK_LABEL(Label_text), msg);

            gtk_label_set_justify(GTK_LABEL(Label_text), GTK_JUSTIFY_CENTER);

            gtk_box_pack_start(GTK_BOX(GTK_DIALOG(Boite)->vbox), Label_text, TRUE, FALSE,0);

            gtk_box_pack_start(GTK_BOX(GTK_DIALOG(Boite)->vbox), Entrer, TRUE, TRUE,10);

        Entrer_cle=gtk_text_view_new();

        gtk_label_set_markup(GTK_LABEL(Label_cle), indication_cle);

        gtk_label_set_justify(GTK_LABEL(Label_cle), GTK_JUSTIFY_CENTER);

        gtk_box_pack_start(GTK_BOX(GTK_DIALOG(Boite)->vbox), Label_cle, TRUE, FALSE,0);
        
        gtk_box_pack_start(GTK_BOX(GTK_DIALOG(Boite)->vbox), Entrer_cle, TRUE, TRUE,10);
        
        gtk_widget_show_all(GTK_DIALOG(Boite)->vbox);

        switch(gtk_dialog_run(GTK_DIALOG(Boite)))
            {
                case GTK_RESPONSE_OK:
                    Buffer= gtk_text_view_get_buffer(GTK_TEXT_VIEW(Entrer));
                    gtk_text_buffer_get_start_iter(Buffer,&debut);
                    gtk_text_buffer_get_end_iter(Buffer,&fin);
                    C1 = gtk_text_buffer_get_text(Buffer,&debut,&fin,FALSE);
              
                    
                   
                    Buffer= gtk_text_view_get_buffer(GTK_TEXT_VIEW(Entrer_cle));
                    gtk_text_buffer_get_start_iter(Buffer,&debut);
                    gtk_text_buffer_get_end_iter(Buffer,&fin);
                    C2 = gtk_text_buffer_get_text(Buffer,&debut,&fin,FALSE);

                    RemplacerCleSubstitution(Donnees,C1[0],C2[0]);
                    MenuResultatDecryptagePartiel(Fenetre,Donnees);
                    
                    break;
                case GTK_RESPONSE_CANCEL:
                case GTK_RESPONSE_NONE:
                default:
                    break;
            }
            
        gtk_widget_destroy(Boite);
    
}

void modifieLangue(GtkWidget *Fenetre, int lang)
{
    if (lang==0)
    {
        langue=0;
    }
    else
    {
        langue=1;
    }
    MenuDecryptage(Fenetre);
}

void ChoisirLangue()
{
    GtkWidget *Boite,*bouton1,*bouton2, *Label_text;
    gchar* msg;
    int i=0;
    int j=1;
    Fenetre = gtk_widget_get_toplevel (Fenetre);//je crée la seconde fenetre

    ViderContenaire(GTK_CONTAINER(Fenetre));

    Label_text=gtk_label_new(NULL);
    Boite = gtk_vbox_new(FALSE, 0);
    gtk_container_add(GTK_CONTAINER(Fenetre), Boite);

    msg= g_locale_to_utf8("<span font_desc=\"Times New Roman italic 12\" foreground=\"#1d1d1d\">Quelle est la langue utilisée</span>\n",
    -1, NULL, NULL, NULL);

    bouton1= gtk_button_new_with_label("Français");
    gtk_label_set_markup(GTK_LABEL(Label_text), msg);
    gtk_label_set_justify(GTK_LABEL(Label_text), GTK_JUSTIFY_CENTER);
    g_signal_connect(G_OBJECT(bouton1), "clicked", G_CALLBACK(modifieLangue), (gpointer) i );
    gtk_box_pack_start(GTK_BOX(Boite), Label_text, TRUE, FALSE,0);
    gtk_box_pack_start(GTK_BOX(Boite), bouton1, TRUE, TRUE,10);
    bouton2=gtk_button_new_with_label("Anglais");
    g_signal_connect(G_OBJECT(bouton2), "clicked", G_CALLBACK(modifieLangue), (gpointer) j);
    gtk_box_pack_start(GTK_BOX(Boite), bouton2, TRUE, TRUE,10);
   
    gtk_widget_show_all(Fenetre);
}

void MenuAttente(GtkWidget *Fenetre)
{
   GtkWidget* pWindow;
   GtkWidget* Label;
   gchar* Text;
 
   pWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
   gtk_window_set_title(GTK_WINDOW(pWindow), "fenetre d'attente");
   gtk_window_set_default_size(GTK_WINDOW(pWindow), 320, 200);
   gtk_container_set_border_width(GTK_CONTAINER(pWindow), 4);

    Label=gtk_label_new(NULL);
    Text = g_locale_to_utf8("<span font_desc=\"Times New Roman italic 12\" foreground=\"#1d1d1d\">Patientez...</span>\n",
           -1, NULL, NULL, NULL);
    gtk_label_set_markup(GTK_LABEL(Label), Text);
    g_free(Text);  
    gtk_container_add(GTK_CONTAINER(pWindow), Label);
    

   gtk_widget_show_all(pWindow);  
   gtk_widget_show_all(pWindow);
   gtk_main_iteration(); 
   gtk_main_iteration();

   sleep(3);      
   gtk_widget_destroy(pWindow);
   gtk_main();

}

void Enregistrer (GtkWidget *p_widget, GtkWidget *text )
{
      /* Le fichier n'a pas encore ete enregistre */
        gchar *chemin;
        GtkWidget *p_dialog = NULL;

        p_dialog = gtk_file_chooser_dialog_new ("Sauvegarder le fichier", NULL,
                                                GTK_FILE_CHOOSER_ACTION_SAVE,
                                                GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
                                                GTK_STOCK_SAVE, GTK_RESPONSE_ACCEPT,
                                                NULL);
        if (gtk_dialog_run (GTK_DIALOG (p_dialog)) == GTK_RESPONSE_ACCEPT)
        {
          chemin = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (p_dialog));
        }
        gtk_widget_destroy (p_dialog);
      /* l'utilisateur vient de nous fournir son nouvel emplacement, on peut donc l'enregistrer */
        FILE *fichier = NULL;

        fichier = fopen (chemin, "w");
        if (fichier)
        {
          gchar *contents = NULL;
          gchar *locale = NULL;

          contents = gtk_label_get_text(GTK_LABEL(text));
          locale = g_locale_from_utf8 (contents, -1, NULL, NULL, NULL);
          g_free (contents), contents = NULL;
          fprintf (fichier, "%s", locale);
          g_free (locale), locale = NULL;
          fclose (fichier), fichier = NULL;
        }
  /* Parametres inutilises */
  (void)p_widget;
}

void RecupererChemin(GtkWidget *bouton, GtkWidget *selection)
{
    
    ANALYSE a;
    const gchar* chemin;
    gchar Text_crypt[TAILLETEXTE];
    gchar contenu[TAILLEFICHIER];
    gchar cle[TAILLECLE];
    GtkWidget *dialog;
    gchar *Resultat;
    Resultat=(gchar *)malloc(TAILLETEXTE*sizeof(gchar));
   
    chemin = gtk_file_selection_get_filename(GTK_FILE_SELECTION (selection) );
    dialog = gtk_message_dialog_new(GTK_WINDOW(selection),GTK_DIALOG_MODAL,
    GTK_MESSAGE_INFO,GTK_BUTTONS_OK,"Vous avez choisi :\n%s", chemin);
     //ce chemin doit etre utiliser pour remplir une chaine/tableau ensuite on supprime la "dialog"

    LireFichier(contenu,TAILLEFICHIER,chemin);
    
        DOUBLEC *Donnees;
        Donnees = (DOUBLEC *)malloc(sizeof(DOUBLEC));
        FILE* fichier =NULL;
        if (choix==4)
        {
            remove("text.txt");
            fichier=fopen("text.txt","w");

            if (fichier != NULL)
            {
                fputs(contenu,fichier);
                fclose(fichier);
            }
            MenuResultatDecryptagePartielVig(Fenetre);
        }
   switch (choix)
    {
    case 1:
        CryptageSubstitution(Donnees->texte,contenu,Donnees->cle);
        MenuResultatSubstitution(Fenetre,Donnees);
        break;
    case 2:
    
        

        fichier=fopen("cle.txt","r");

        if (fichier != NULL)
        {
            fgets(cle,TAILLECLE,fichier);
            fclose(fichier);
            remove("cle.txt");
        }

        CryptageVigenere(Text_crypt,contenu,cle);

        MenuResultatVigenere(Fenetre,Text_crypt,cle);
        
        break;
    case 3:
        strcpy(Donnees->texte,contenu);
        char* cle="abcdefghijklmnopqrstuvwxyz";
        strcpy(Donnees->cle,cle);
        strcpy(Donnees->texte,contenu);
        DecryptageSubstitution(Resultat,contenu,Donnees->cle);
        
        MenuResultatDecryptagePartiel(Fenetre, Donnees);
        break;
    case 5:
        a=AnalyseFrequentielle(contenu);
        MenuResultatAnalyse(Fenetre,a);
        break;

    }
    
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
    gtk_widget_destroy(selection);
}

void ChoisirFichier()
{
    GtkWidget *selection;
    
    selection = gtk_file_selection_new( g_locale_to_utf8( "Sélectionnez un fichier", -1, NULL, NULL, NULL) );
    gtk_widget_show(selection);
    //On interdit l'utilisation des autres fenêtres.
    gtk_window_set_modal(GTK_WINDOW(selection), TRUE);
     
    g_signal_connect(G_OBJECT(GTK_FILE_SELECTION(selection)->ok_button), "clicked", G_CALLBACK(RecupererChemin), selection );
    g_signal_connect_swapped(G_OBJECT(GTK_FILE_SELECTION(selection)->cancel_button), "clicked", G_CALLBACK(gtk_widget_destroy), selection);
}
 
void ViderContenaire(GtkContainer * container)
{
    GList * children = gtk_container_get_children(container);
    while(children)
    {
        gtk_widget_destroy(children->data);
        children = g_list_next(children);
    }
    g_list_free(children);
}

void MenuResultatSubstitution(GtkWidget *Fenetre, DOUBLEC *Donnees)
{
    Fenetre = gtk_widget_get_toplevel (Fenetre);
    ViderContenaire(GTK_CONTAINER(Fenetre));

    GtkWidget *Box, *Box_2,*Label, *Label_msg,*Label_cle,*Bouton1,*Bouton2,*Bouton3;
    gchar* Text;
    gchar text_affichage[TAILLETEXTE]; 
    RetourALaLigne(text_affichage,Donnees->texte);
    
    Box = gtk_vbox_new(FALSE, 0);
    gtk_container_add(GTK_CONTAINER(Fenetre), Box);
    Box_2= gtk_hbox_new(FALSE, 0);
    Label=gtk_label_new(NULL);
    Label_msg=gtk_label_new(NULL);
    Label_cle=gtk_label_new(NULL);

    Text = g_locale_to_utf8("<span font_desc=\"Times New Roman italic 12\" foreground=\"#1d1d1d\">Resultat du chiffrement</span>\n<span font_desc=\"Times New Roman italic 12\" foreground=\"#1d1d1d\">Substitution</span>\n",
    -1, NULL, NULL, NULL);
    gtk_label_set_markup(GTK_LABEL(Label), Text);
    g_free(Text);
    gtk_label_set_justify(GTK_LABEL(Label), GTK_JUSTIFY_CENTER);

    gtk_box_pack_start(GTK_BOX(Box), Box_2, TRUE, TRUE, 0);

    Bouton3 = gtk_button_new_with_label("R");
    g_signal_connect(G_OBJECT(Bouton3), "clicked", G_CALLBACK(MenuCryptageSubstitution), NULL);
    gtk_box_pack_start(GTK_BOX(Box_2), Bouton3, FALSE, TRUE, 0);

    gtk_box_pack_start(GTK_BOX(Box_2), Label, TRUE, TRUE, 0);

    gtk_label_set_markup(GTK_LABEL(Label_msg), text_affichage);
    gtk_label_set_justify(GTK_LABEL(Label_msg), GTK_JUSTIFY_CENTER);
    gtk_box_pack_start(GTK_BOX(Box), Label_msg, TRUE, TRUE, 0);
    
    Bouton1 = gtk_button_new_with_label("Enregistrer le msg");
    g_signal_connect(G_OBJECT(Bouton1), "clicked", G_CALLBACK(Enregistrer), Label_msg);
    gtk_box_pack_start(GTK_BOX(Box), Bouton1, TRUE, TRUE, 0);

    gtk_label_set_markup(GTK_LABEL(Label_cle),Donnees->cle);
    gtk_label_set_justify(GTK_LABEL(Label_cle), GTK_JUSTIFY_CENTER);
    gtk_box_pack_start(GTK_BOX(Box), Label_cle, TRUE, TRUE, 0);
    
    Bouton2 = gtk_button_new_with_label("Enregistrer la cle");
    g_signal_connect(G_OBJECT(Bouton2), "clicked", G_CALLBACK(Enregistrer), Label_cle);
    gtk_box_pack_start(GTK_BOX(Box), Bouton2, TRUE, TRUE, 0);
    
    gtk_widget_show_all(Fenetre);
}

void MenuResultatVigenere(GtkWidget *Fenetre, gchar* Text_crypt, gchar* cle)
{
    Fenetre = gtk_widget_get_toplevel (Fenetre);
    ViderContenaire(GTK_CONTAINER(Fenetre));

    GtkWidget *Box, *Box_2,*Label, *Label_msg,*Label_cle,*Bouton1,*Bouton2,*Bouton3,*Label_retour;
    gchar* Text;
    gchar text_affichage[TAILLETEXTE]; 
    RetourALaLigne(text_affichage,Text_crypt);
    Box = gtk_vbox_new(FALSE, 0);
    gtk_container_add(GTK_CONTAINER(Fenetre), Box);
    Box_2= gtk_hbox_new(FALSE, 0);
    Label=gtk_label_new(NULL);
    Label_msg=gtk_label_new(NULL);
    Label_cle=gtk_label_new(NULL);
    Label_retour=gtk_label_new(NULL);
    Text = g_locale_to_utf8("<span font_desc=\"Times New Roman italic 12\" foreground=\"#1d1d1d\">Resultat du chiffrement</span>\n<span font_desc=\"Times New Roman italic 12\" foreground=\"#1d1d1d\">Vigenere</span>\n",
           -1, NULL, NULL, NULL);
    gtk_label_set_markup(GTK_LABEL(Label), Text);
    g_free(Text);
 
    gtk_label_set_justify(GTK_LABEL(Label), GTK_JUSTIFY_CENTER);

    gtk_box_pack_start(GTK_BOX(Box), Box_2, TRUE, TRUE, 0);

    Bouton3 = gtk_button_new_with_label("R");
    g_signal_connect(G_OBJECT(Bouton3), "clicked", G_CALLBACK(MenuCryptage), NULL);
    gtk_box_pack_start(GTK_BOX(Box_2), Bouton3, FALSE, TRUE, 0);
    
    gtk_box_pack_start(GTK_BOX(Box_2), Label, TRUE, TRUE, 0);

    ////////////Affichage du resultat//////////////

    gtk_label_set_markup(GTK_LABEL(Label_msg), text_affichage);
    gtk_label_set_justify(GTK_LABEL(Label_msg), GTK_JUSTIFY_CENTER);
    gtk_box_pack_start(GTK_BOX(Box), Label_msg, TRUE, TRUE, 0);
    
    Bouton1 = gtk_button_new_with_label("Enregistrer le msg");
    gtk_label_set_markup(GTK_LABEL(Label_retour), Text_crypt);
    g_signal_connect(G_OBJECT(Bouton1), "clicked", G_CALLBACK(Enregistrer), Label_retour);
    gtk_box_pack_start(GTK_BOX(Box), Bouton1, TRUE, TRUE, 0);

        ////////////Affichage de la cle//////////////

    gtk_label_set_markup(GTK_LABEL(Label_cle), cle);
    gtk_label_set_justify(GTK_LABEL(Label_cle), GTK_JUSTIFY_CENTER);
    gtk_box_pack_start(GTK_BOX(Box), Label_cle, TRUE, TRUE, 0);
    
    Bouton2 = gtk_button_new_with_label("Enregistrer la cle");
    g_signal_connect(G_OBJECT(Bouton2), "clicked", G_CALLBACK(Enregistrer), Label_cle);
    gtk_box_pack_start(GTK_BOX(Box), Bouton2, TRUE, TRUE, 0);
    
    gtk_widget_show_all(Fenetre);
}

void MenuResultatAnalyse(GtkWidget *Fenetre,ANALYSE analyse)
{
    Fenetre = gtk_widget_get_toplevel (Fenetre);//on passe a la fenetre du bouton 
    ViderContenaire(GTK_CONTAINER(Fenetre));//on la vide

    GtkWidget *Box, *Box_2,*Label, *Label_msg,*Label_cle,*Label_cle2,*Bouton2,*Bouton3;
    gchar* Text;
    
    Box = gtk_vbox_new(FALSE, 0);
    gtk_container_add(GTK_CONTAINER(Fenetre), Box);
    Box_2= gtk_hbox_new(FALSE, 0);
    Label=gtk_label_new(NULL);
    Label_msg=gtk_label_new(NULL);
    Label_cle=gtk_label_new(NULL);
    Label_cle2=gtk_label_new(NULL);

    Text = g_locale_to_utf8("<span font_desc=\"Times New Roman italic 12\" foreground=\"#1d1d1d\">Resultat de l'Analyse Frequentielle</span>\n",
    -1, NULL, NULL, NULL);
    gtk_label_set_markup(GTK_LABEL(Label), Text);
    g_free(Text);
    gtk_label_set_justify(GTK_LABEL(Label), GTK_JUSTIFY_CENTER);

    gtk_box_pack_start(GTK_BOX(Box), Box_2, TRUE, TRUE, 0);

    Bouton3 = gtk_button_new_with_label("R");
    g_signal_connect(G_OBJECT(Bouton3), "clicked", G_CALLBACK(MenuAnalyseFrequentielle), NULL);
    gtk_box_pack_start(GTK_BOX(Box_2), Bouton3, FALSE, TRUE, 0);
    
    gtk_box_pack_start(GTK_BOX(Box_2), Label, TRUE, TRUE, 0);

    ////////////Affichage du resultat//////////////
    analyse = tri(analyse);
    gchar save[TAILLETEXTE];
    save[0]= '\0';
    gchar ch[TAILLETEXTE];
    gchar* ch3;
    ch[0]= '\0';
    gchar ch1[1000];
    ch3 = "vous avez ici le nombre d'occurences de chaque caracteres dans votre texte : \n ";
    int i,j;
    gchar x[3] ;
    x[0]= 'A'; x[1]= ':'; x[2]= '\0';
    gchar y[2] ;
    y[0]= '\n'; y[1]= '\0';
    gchar* z="  |  ";
    strcat(ch,ch3);
    for (i = 0; i < 26; i++)
    {
        if (i%13 == 0)
            strcat(ch,y);
        j = (int) analyse.occ[0][i];
        sprintf(ch1,"%d",j);
        strcat(ch,x);
        strcat(ch,ch1);
        strcat(ch,z);
        x[0]= x[0]+1;
    }
	strcat(save,ch);
	strcat(save,y);
	
    gtk_label_set_markup(GTK_LABEL(Label_msg), ch);
    gtk_label_set_justify(GTK_LABEL(Label_msg), GTK_JUSTIFY_CENTER);
    gtk_box_pack_start(GTK_BOX(Box), Label_msg, TRUE, TRUE, 0);

        ////////////Affichage de la cle//////////////
    ch[0]= '\0';
    ch3 = "les digrammes et trigrammes qui se repettent dans votre texte sont : \n ";
    strcat(ch,ch3);
    int f = analyse.nbdi;
    if (f > 91) f = 91;
    for (i = 0; i < analyse.nbdi ; i++)
    {
        if (i%10 == 0)
            strcat(ch,y);
        strcat(ch,analyse.di[i].nom);
        j =  analyse.di[i].frequence;
        sprintf(ch1," : %d",j);
        strcat(ch,ch1);
        strcat(ch,z);
    }
     f = analyse.nbtr;
    if (f > 91) f = 91;
    for (i = 0; i < f ; i++)
    {
        if (i%13 == 0)
            strcat(ch,y);
        strcat(ch,analyse.tr[i].nom);
        j =  analyse.tr[i].frequence;
        sprintf(ch1," : %d",j);
        strcat(ch,ch1);
        strcat(ch,z);
    }
    strcat(save,ch);
    
    gtk_label_set_markup(GTK_LABEL(Label_cle), ch);
    gtk_label_set_justify(GTK_LABEL(Label_cle), GTK_JUSTIFY_CENTER);
    gtk_box_pack_start(GTK_BOX(Box), Label_cle, TRUE, TRUE, 0);
    
    gtk_label_set_markup(GTK_LABEL(Label_cle2), save);//on a besoin dun label
    Bouton2 = gtk_button_new_with_label("Enregistrer le resultat");
    g_signal_connect(G_OBJECT(Bouton2), "clicked", G_CALLBACK(Enregistrer), Label_cle2);//pas label cle
    gtk_box_pack_start(GTK_BOX(Box), Bouton2, TRUE, TRUE, 0);
    
    gtk_widget_show_all(Fenetre);
}

void MenuResultatDecryptageSubstitution(GtkWidget *Fenetre, DOUBLEC *Donnees)//appeler text clair
{
    Fenetre = gtk_widget_get_toplevel (Fenetre);
    ViderContenaire(GTK_CONTAINER(Fenetre));

    GtkWidget *Box, *Box_2,*Label, *Label_msg,*Label_cle,*Label_retour,*Bouton1,*Bouton2,*Bouton3;
    gchar *Text;
    gchar *Text_clair[TAILLETEXTE];
    strcpy(Text_clair,Donnees->texte);
    DechiffreSubstitution(Text_clair,Donnees->cle);


    gchar text_affichage[TAILLETEXTE]; 
    RetourALaLigne(text_affichage,Text_clair);
    
    Box = gtk_vbox_new(FALSE, 0);
    gtk_container_add(GTK_CONTAINER(Fenetre), Box);
    Box_2= gtk_hbox_new(FALSE, 0);
    Label=gtk_label_new(NULL);
    Label_msg=gtk_label_new(NULL);
    Label_cle=gtk_label_new(NULL);
    Label_retour=gtk_label_new(NULL);
    Text = g_locale_to_utf8("<span font_desc=\"Times New Roman italic 12\" foreground=\"#1d1d1d\">resultat du dechiffrement</span>\n<span font_desc=\"Times New Roman italic 12\" foreground=\"#1d1d1d\">Par Substitution</span>\n",
           -1, NULL, NULL, NULL);
    gtk_label_set_markup(GTK_LABEL(Label), Text);
    g_free(Text);
 
    gtk_label_set_justify(GTK_LABEL(Label), GTK_JUSTIFY_CENTER);

    gtk_box_pack_start(GTK_BOX(Box), Box_2, TRUE, TRUE, 0);

    Bouton3 = gtk_button_new_with_label("R");

    g_signal_connect(G_OBJECT(Bouton3), "clicked", G_CALLBACK(MenuDecryptageSubstitution), NULL);

    gtk_box_pack_start(GTK_BOX(Box_2), Bouton3, FALSE, TRUE, 0);
    
    gtk_box_pack_start(GTK_BOX(Box_2), Label, TRUE, TRUE, 0);

    ////////////Affichage du resultat//////////////

    gtk_label_set_markup(GTK_LABEL(Label_msg), text_affichage);

    gtk_label_set_justify(GTK_LABEL(Label_msg), GTK_JUSTIFY_CENTER);

    gtk_box_pack_start(GTK_BOX(Box), Label_msg, TRUE, TRUE, 0);
    
    
    Bouton1 = gtk_button_new_with_label("Enregistrer le msg");
    gtk_label_set_markup(GTK_LABEL(Label_retour), Text_clair);
    g_signal_connect(G_OBJECT(Bouton1), "clicked", G_CALLBACK(Enregistrer), Label_retour);
   
    gtk_box_pack_start(GTK_BOX(Box), Bouton1, TRUE, TRUE, 0);

        ////////////Affichage de la cle//////////////

    gtk_label_set_markup(GTK_LABEL(Label_cle), Donnees->cle);

    gtk_label_set_justify(GTK_LABEL(Label_cle), GTK_JUSTIFY_CENTER);

    gtk_box_pack_start(GTK_BOX(Box), Label_cle, TRUE, TRUE, 0);
    
    Bouton2 = gtk_button_new_with_label("Enregistrer la cle");

    g_signal_connect(G_OBJECT(Bouton2), "clicked", G_CALLBACK(Enregistrer), Label_cle);
   
    gtk_box_pack_start(GTK_BOX(Box), Bouton2, TRUE, TRUE, 0);
    
    gtk_widget_show_all(Fenetre);
}

void MenuResultatDecryptageVigenere(GtkWidget *Fenetre, DOUBLEC *Donnees)//appeler text clair
{
    Fenetre = gtk_widget_get_toplevel (Fenetre);//on passe a la fenetre du bouton 
    ViderContenaire(GTK_CONTAINER(Fenetre));//on la vide

    GtkWidget *Box, *Box_2,*Label,*Label_msg,*Label_cle,*Label_retour,*Bouton1,*Bouton2,*Bouton3;
    gchar* Text;
    gchar text_affichage[TAILLETEXTE]; 
    RetourALaLigne(text_affichage,Donnees->texte);
    Box = gtk_vbox_new(FALSE, 0);
    gtk_container_add(GTK_CONTAINER(Fenetre), Box);
    Box_2= gtk_hbox_new(FALSE, 0);
    Label=gtk_label_new(NULL);
    Label_msg=gtk_label_new(NULL);
    Label_cle=gtk_label_new(NULL);
    Label_retour=gtk_label_new(NULL);
    Text = g_locale_to_utf8("<span font_desc=\"Times New Roman italic 12\" foreground=\"#1d1d1d\">resultat du chiffrement</span>\n<span font_desc=\"Times New Roman italic 12\" foreground=\"#1d1d1d\">Par Vigenere</span>\n",
           -1, NULL, NULL, NULL);
    gtk_label_set_markup(GTK_LABEL(Label), Text);
    g_free(Text);
 
    gtk_label_set_justify(GTK_LABEL(Label), GTK_JUSTIFY_CENTER);

    gtk_box_pack_start(GTK_BOX(Box), Box_2, TRUE, TRUE, 0);

    Bouton3 = gtk_button_new_with_label("R");

    g_signal_connect(G_OBJECT(Bouton3), "clicked", G_CALLBACK(MenuDecryptageVigenere), NULL);

    gtk_box_pack_start(GTK_BOX(Box_2), Bouton3, FALSE, TRUE, 0);
    
    gtk_box_pack_start(GTK_BOX(Box_2), Label, TRUE, TRUE, 0);

    ////////////Affichage du resultat//////////////

    gtk_label_set_markup(GTK_LABEL(Label_msg), text_affichage);

    gtk_label_set_justify(GTK_LABEL(Label_msg), GTK_JUSTIFY_CENTER);

    gtk_box_pack_start(GTK_BOX(Box), Label_msg, TRUE, TRUE, 0);
    
    
    Bouton1 = gtk_button_new_with_label("Enregistrer le msg");
    gtk_label_set_markup(GTK_LABEL(Label_retour), Donnees->texte);
    g_signal_connect(G_OBJECT(Bouton1), "clicked", G_CALLBACK(Enregistrer), Label_retour);
   
    gtk_box_pack_start(GTK_BOX(Box), Bouton1, TRUE, TRUE, 0);

        ////////////Affichage de la cle//////////////

    gtk_label_set_markup(GTK_LABEL(Label_cle), Donnees->cle);

    gtk_label_set_justify(GTK_LABEL(Label_cle), GTK_JUSTIFY_CENTER);

    gtk_box_pack_start(GTK_BOX(Box), Label_cle, TRUE, TRUE, 0);
    
    Bouton2 = gtk_button_new_with_label("Enregistrer la cle");

    g_signal_connect(G_OBJECT(Bouton2), "clicked", G_CALLBACK(Enregistrer), Label_cle);
   
    gtk_box_pack_start(GTK_BOX(Box), Bouton2, TRUE, TRUE, 0);
    
    gtk_widget_show_all(Fenetre);
}

void BoiteDialogueSubstitution(GtkWidget *Fenetre)
{
    GtkWidget *Boite,*Entrer;
    gchar *Text_clair;
    DOUBLEC *Donnees;
    Donnees=(DOUBLEC *)malloc(sizeof(DOUBLEC));
    GtkTextBuffer* Buffer;
    GtkTextIter debut;
    GtkTextIter fin;
	Fenetre = gtk_widget_get_toplevel (Fenetre);//on passe a la fenetre du bouton 
    Boite = gtk_dialog_new_with_buttons("Sasie du texte",GTK_WINDOW(Fenetre),GTK_DIALOG_MODAL,GTK_STOCK_OK,GTK_RESPONSE_OK,GTK_STOCK_CANCEL,GTK_RESPONSE_CANCEL,NULL);

    Entrer= gtk_text_view_new();

    gtk_box_pack_start(GTK_BOX(GTK_DIALOG(Boite)->vbox), Entrer, TRUE, TRUE,10);

    gtk_widget_show_all(GTK_DIALOG(Boite)->vbox);

    switch(gtk_dialog_run(GTK_DIALOG(Boite)))
        {
            case GTK_RESPONSE_OK:
                Buffer= gtk_text_view_get_buffer(GTK_TEXT_VIEW(Entrer));
                gtk_text_buffer_get_start_iter(Buffer,&debut);
                gtk_text_buffer_get_end_iter(Buffer,&fin);
                Text_clair = gtk_text_buffer_get_text(Buffer,&debut,&fin,FALSE);
                CryptageSubstitution(Donnees->texte,Text_clair,Donnees->cle);
                MenuResultatSubstitution(Fenetre, Donnees);
                break;
            case GTK_RESPONSE_CANCEL:
            case GTK_RESPONSE_NONE:
            default:
                break;
        }
        
    gtk_widget_destroy(Boite);
}

void BoiteDialogueVigenereTexte(GtkWidget *Fenetre, DOUBLEC *Donnees)
{
        remove("cle.txt");

        GtkWidget *Boite,*Entrer_cle,*Label_cle;
        gchar *Text_clair,*indication_cle,*Text_crypt;

        GtkTextBuffer* Buffer;
        GtkTextIter debut;
        GtkTextIter fin;
        Fenetre = gtk_widget_get_toplevel (Fenetre);//on passe a la fenetre du bouton 
        Boite = gtk_dialog_new_with_buttons("Sasie du texte",GTK_WINDOW(Fenetre),GTK_DIALOG_MODAL,GTK_STOCK_OK,GTK_RESPONSE_OK,GTK_STOCK_CANCEL,GTK_RESPONSE_CANCEL,NULL);

        Label_cle=gtk_label_new(NULL);
    
        indication_cle = g_locale_to_utf8("<span font_desc=\"Times New Roman italic 12\" foreground=\"#1d1d1d\">Votre texte : </span>\n",
               -1, NULL, NULL, NULL);

        Entrer_cle=gtk_text_view_new();

        gtk_label_set_markup(GTK_LABEL(Label_cle), indication_cle);

        gtk_label_set_justify(GTK_LABEL(Label_cle), GTK_JUSTIFY_CENTER);

        gtk_box_pack_start(GTK_BOX(GTK_DIALOG(Boite)->vbox), Label_cle, TRUE, FALSE,0);
        
        gtk_box_pack_start(GTK_BOX(GTK_DIALOG(Boite)->vbox), Entrer_cle, TRUE, TRUE,10);
        
        gtk_widget_show_all(GTK_DIALOG(Boite)->vbox);

        switch(gtk_dialog_run(GTK_DIALOG(Boite)))
            {
                case GTK_RESPONSE_OK:
              
                    
                   
                    Buffer= gtk_text_view_get_buffer(GTK_TEXT_VIEW(Entrer_cle));
                    gtk_text_buffer_get_start_iter(Buffer,&debut);
                    gtk_text_buffer_get_end_iter(Buffer,&fin);
                    Text_clair= gtk_text_buffer_get_text(Buffer,&debut,&fin,FALSE);
                    Text_crypt=(gchar *)malloc(strlen(Text_clair)*sizeof(gchar));
                    strcpy(Donnees->texte,Text_clair);
                    CryptageVigenere(Text_crypt,Donnees->texte, Donnees->cle);
                    MenuResultatVigenere(Fenetre, Text_crypt,Donnees->cle);
                    break;
                case GTK_RESPONSE_CANCEL:
                case GTK_RESPONSE_NONE:
                default:
                    break;
            }
            
        gtk_widget_destroy(Boite);
    
}

void BoiteDialogueVigenereCle(GtkWidget *Fenetre)
{

	    GtkWidget *Boite,*Entrer_cle,*Label_cle;
	    gchar *cle,*indication_cle;
	    GtkTextBuffer* Buffer;
	    GtkTextIter debut;
	    GtkTextIter fin;
	    Fenetre = gtk_widget_get_toplevel (Fenetre); 
	    Boite = gtk_dialog_new_with_buttons("Sasie du texte",GTK_WINDOW(Fenetre),GTK_DIALOG_MODAL,GTK_STOCK_OK,GTK_RESPONSE_OK,GTK_STOCK_CANCEL,GTK_RESPONSE_CANCEL,NULL);
	    
	    Label_cle=gtk_label_new(NULL);
	    
	    indication_cle = g_locale_to_utf8("<span font_desc=\"Times New Roman italic 12\" foreground=\"#1d1d1d\">Votre cle : </span>\n",
	           -1, NULL, NULL, NULL);

	    Entrer_cle=gtk_text_view_new();

	    gtk_label_set_markup(GTK_LABEL(Label_cle), indication_cle);

	    gtk_label_set_justify(GTK_LABEL(Label_cle), GTK_JUSTIFY_CENTER);

	    gtk_box_pack_start(GTK_BOX(GTK_DIALOG(Boite)->vbox), Label_cle, TRUE, FALSE,0);
	    
	    gtk_box_pack_start(GTK_BOX(GTK_DIALOG(Boite)->vbox), Entrer_cle, TRUE, TRUE,10);
	    
	    gtk_widget_show_all(GTK_DIALOG(Boite)->vbox);

	    switch(gtk_dialog_run(GTK_DIALOG(Boite)))
	        {
	            case GTK_RESPONSE_OK:
		      
		        	
		           
	                Buffer= gtk_text_view_get_buffer(GTK_TEXT_VIEW(Entrer_cle));
	                gtk_text_buffer_get_start_iter(Buffer,&debut);
	                gtk_text_buffer_get_end_iter(Buffer,&fin);
	                cle = gtk_text_buffer_get_text(Buffer,&debut,&fin,FALSE);
	                DOUBLEC *Donnees;
	                Donnees = (DOUBLEC *)malloc(sizeof(DOUBLEC));
                    strcpy(Donnees->cle,cle);
	                MenuCryptageVigenere(Fenetre,Donnees);
	                break;
	            case GTK_RESPONSE_CANCEL:
	            case GTK_RESPONSE_NONE:
	            default:
	                break;
	        }
	        
	    gtk_widget_destroy(Boite);
	
}

void BoiteDialogueAnalyse(GtkWidget *Fenetre)
{
	ANALYSE a;
    GtkWidget *Boite,*Entrer;
    gchar* Text;
    GtkTextBuffer* Buffer;
    GtkTextIter debut;
    GtkTextIter fin;
	Fenetre = gtk_widget_get_toplevel (Fenetre);//on passe a la fenetre du bouton 
    Boite = gtk_dialog_new_with_buttons("Sasie du texte",GTK_WINDOW(Fenetre),GTK_DIALOG_MODAL,GTK_STOCK_OK,GTK_RESPONSE_OK,GTK_STOCK_CANCEL,GTK_RESPONSE_CANCEL,NULL);

    Entrer= gtk_text_view_new();

    gtk_box_pack_start(GTK_BOX(GTK_DIALOG(Boite)->vbox), Entrer, TRUE, TRUE,10);

    gtk_widget_show_all(GTK_DIALOG(Boite)->vbox);

    switch(gtk_dialog_run(GTK_DIALOG(Boite)))
        {
            case GTK_RESPONSE_OK:
                Buffer= gtk_text_view_get_buffer(GTK_TEXT_VIEW(Entrer));
                gtk_text_buffer_get_start_iter(Buffer,&debut);
                gtk_text_buffer_get_end_iter(Buffer,&fin);
                Text = gtk_text_buffer_get_text(Buffer,&debut,&fin,FALSE);
                a = AnalyseFrequentielle(Text);
                MenuResultatAnalyse(Fenetre,a);
                break;
            case GTK_RESPONSE_CANCEL:
            case GTK_RESPONSE_NONE:
            default:
                break;
        }
        
    gtk_widget_destroy(Boite);
}

void BoiteDialogueDecryptageSubstitution(GtkWidget *Fenetre)
{
    GtkWidget *Boite,*Entrer,*Label_text;
    gchar *Text_crypt,*cle,*msg,*Resultat;
    GtkTextBuffer* Buffer;
    GtkTextIter debut;
    GtkTextIter fin;
    DOUBLEC *Donnees;
    Resultat=(gchar *)malloc(TAILLETEXTE*sizeof(gchar));
    Fenetre = gtk_widget_get_toplevel (Fenetre); 
    Boite = gtk_dialog_new_with_buttons("Sasie du texte",GTK_WINDOW(Fenetre),GTK_DIALOG_MODAL,GTK_STOCK_OK,GTK_RESPONSE_OK,GTK_STOCK_CANCEL,GTK_RESPONSE_CANCEL,NULL);

    Label_text=gtk_label_new(NULL);

     msg= g_locale_to_utf8("<span font_desc=\"Times New Roman italic 12\" foreground=\"#1d1d1d\">Votre texte : </span>\n",
           -1, NULL, NULL, NULL);

    Entrer= gtk_text_view_new();

    gtk_label_set_markup(GTK_LABEL(Label_text), msg);

    gtk_label_set_justify(GTK_LABEL(Label_text), GTK_JUSTIFY_CENTER);

    gtk_box_pack_start(GTK_BOX(GTK_DIALOG(Boite)->vbox), Label_text, TRUE, FALSE,0);


    gtk_box_pack_start(GTK_BOX(GTK_DIALOG(Boite)->vbox), Entrer, TRUE, TRUE,10);


    gtk_widget_show_all(GTK_DIALOG(Boite)->vbox);

    switch(gtk_dialog_run(GTK_DIALOG(Boite)))
        {
            case GTK_RESPONSE_OK:
                Buffer= gtk_text_view_get_buffer(GTK_TEXT_VIEW(Entrer));
                gtk_text_buffer_get_start_iter(Buffer,&debut);
                gtk_text_buffer_get_end_iter(Buffer,&fin);
                Text_crypt = gtk_text_buffer_get_text(Buffer,&debut,&fin,FALSE);
                
                Donnees = (DOUBLEC *)malloc(sizeof(DOUBLEC));
				strcpy(Donnees->texte,Text_crypt);
				cle="abcdefghijklmnopqrstuvwxyz";
				strcpy(Donnees->cle,cle);
                strcpy(Donnees->texte,Text_crypt);
                DecryptageSubstitution(Resultat,Text_crypt,Donnees->cle);
                
                MenuResultatDecryptagePartiel(Fenetre, Donnees);
                break;
            case GTK_RESPONSE_CANCEL:
            case GTK_RESPONSE_NONE:
            default:
                break;
        }
        
    gtk_widget_destroy(Boite);
}

void BoiteDialogueDecryptageVigenere(GtkWidget *Fenetre)
{
    GtkWidget *Boite,*Entrer,*Label_text;
    gchar *Text_crypt,*msg;
    gchar Text_clair[TAILLETEXTE];
    gchar cle[TAILLECLE];
    GtkTextBuffer* Buffer;
    GtkTextIter debut;
    GtkTextIter fin;
    FILE *fichier=NULL;
    Fenetre = gtk_widget_get_toplevel (Fenetre);//on passe a la fenetre du bouton 
    Boite = gtk_dialog_new_with_buttons("Sasie du texte",GTK_WINDOW(Fenetre),GTK_DIALOG_MODAL,GTK_STOCK_OK,GTK_RESPONSE_OK,GTK_STOCK_CANCEL,GTK_RESPONSE_CANCEL,NULL);

    Label_text=gtk_label_new(NULL);

     msg= g_locale_to_utf8("<span font_desc=\"Times New Roman italic 12\" foreground=\"#1d1d1d\">Votre texte : </span>\n",
           -1, NULL, NULL, NULL);


    Entrer= gtk_text_view_new();

    gtk_label_set_markup(GTK_LABEL(Label_text), msg);
    gtk_label_set_justify(GTK_LABEL(Label_text), GTK_JUSTIFY_CENTER);
    gtk_box_pack_start(GTK_BOX(GTK_DIALOG(Boite)->vbox), Label_text, TRUE, FALSE,0);

    gtk_box_pack_start(GTK_BOX(GTK_DIALOG(Boite)->vbox), Entrer, TRUE, TRUE,10);


    gtk_widget_show_all(GTK_DIALOG(Boite)->vbox);

    switch(gtk_dialog_run(GTK_DIALOG(Boite)))
        {
            case GTK_RESPONSE_OK:
                Buffer= gtk_text_view_get_buffer(GTK_TEXT_VIEW(Entrer));
                gtk_text_buffer_get_start_iter(Buffer,&debut);
                gtk_text_buffer_get_end_iter(Buffer,&fin);
                Text_crypt = gtk_text_buffer_get_text(Buffer,&debut,&fin,FALSE);
                remove("text.txt");
                fichier=fopen("text.txt","w");

                if (fichier != NULL)
                {
                    fputs(Text_crypt,fichier);
                    fclose(fichier);
                }
                MenuResultatDecryptagePartielVig(Fenetre);
                 
                break;
            case GTK_RESPONSE_CANCEL:
            case GTK_RESPONSE_NONE:
            default:
                break;
        }
        
    gtk_widget_destroy(Boite);
}

void MenuDecryptageVigenere(GtkWidget *Fenetre)
{
    Fenetre = gtk_widget_get_toplevel (Fenetre);
	ViderContenaire(GTK_CONTAINER(Fenetre));
	GtkWidget *Box,*Bouton1, *Bouton2, *Bouton3,*Box_2, *Label;
    gchar* Text;
    choix=4;
    
    Box = gtk_vbox_new(FALSE, 0);
    gtk_container_add(GTK_CONTAINER(Fenetre), Box);
    Box_2 = gtk_hbox_new(FALSE, 0);
    
    Label=gtk_label_new(NULL);
    Text = g_locale_to_utf8("<span font_desc=\"Times New Roman italic 12\" foreground=\"#1d1d1d\">Dechiffrement de Vigenere</span>\n",
    -1, NULL, NULL, NULL);
    gtk_label_set_markup(GTK_LABEL(Label), Text);
    g_free(Text);
    gtk_label_set_justify(GTK_LABEL(Label), GTK_JUSTIFY_CENTER);

    gtk_box_pack_start(GTK_BOX(Box), Box_2, TRUE, TRUE, 0);

    Bouton3 = gtk_button_new_with_label("R");
    g_signal_connect(G_OBJECT(Bouton3), "clicked", G_CALLBACK(MenuDecryptage), NULL);
    gtk_box_pack_start(GTK_BOX(Box_2), Bouton3, FALSE, TRUE, 0);

    gtk_box_pack_start(GTK_BOX(Box_2), Label, TRUE, TRUE, 0);
    
    Bouton1 = gtk_button_new_with_label("Rentrer un texte");
    g_signal_connect(G_OBJECT(Bouton1), "clicked", G_CALLBACK(BoiteDialogueDecryptageVigenere), NULL);
    gtk_box_pack_start(GTK_BOX(Box), Bouton1, TRUE, TRUE, 0);
    
    Bouton2 = gtk_button_new_with_label("Choisir un fichier");
    g_signal_connect(G_OBJECT(Bouton2), "clicked", G_CALLBACK(ChoisirFichier), NULL);
    gtk_box_pack_start(GTK_BOX(Box), Bouton2, TRUE, TRUE, 0);
    
    gtk_widget_show_all(Fenetre);
}

void MenuDecryptageSubstitution(GtkWidget *Fenetre)
{
    Fenetre = gtk_widget_get_toplevel (Fenetre);
	ViderContenaire(GTK_CONTAINER(Fenetre));
	GtkWidget *Box,*Bouton1, *Bouton2, *Bouton3,*Box_2, *Label;
    gchar* Text;
    choix=3;
    
    Box = gtk_vbox_new(FALSE, 0);
    gtk_container_add(GTK_CONTAINER(Fenetre), Box);
    Box_2 = gtk_hbox_new(FALSE, 0);
    
    Label=gtk_label_new(NULL);
    Text = g_locale_to_utf8("<span font_desc=\"Times New Roman italic 12\" foreground=\"#1d1d1d\">Dechiffrement Substitution</span>\n",
    -1, NULL, NULL, NULL);
    gtk_label_set_markup(GTK_LABEL(Label), Text);
    g_free(Text);
    gtk_label_set_justify(GTK_LABEL(Label), GTK_JUSTIFY_CENTER);

    gtk_box_pack_start(GTK_BOX(Box), Box_2, TRUE, TRUE, 0);

    Bouton3 = gtk_button_new_with_label("R");
    g_signal_connect(G_OBJECT(Bouton3), "clicked", G_CALLBACK(MenuDecryptage), NULL);
    gtk_box_pack_start(GTK_BOX(Box_2), Bouton3, FALSE, TRUE, 0);

    gtk_box_pack_start(GTK_BOX(Box_2), Label, TRUE, TRUE, 0);
    
    Bouton1 = gtk_button_new_with_label("Rentrer un texte");
    g_signal_connect(G_OBJECT(Bouton1), "clicked", G_CALLBACK(BoiteDialogueDecryptageSubstitution), NULL);
    gtk_box_pack_start(GTK_BOX(Box), Bouton1, TRUE, TRUE, 0);
    
    Bouton2 = gtk_button_new_with_label("choisir un fichier");
    g_signal_connect(G_OBJECT(Bouton2), "clicked", G_CALLBACK(ChoisirFichier), NULL);
    gtk_box_pack_start(GTK_BOX(Box), Bouton2, TRUE, TRUE, 0);
    
    gtk_widget_show_all(Fenetre);
}

void MenuCryptageVigenere(GtkWidget *Fenetre,DOUBLEC *Donnees)
{
    Fenetre = gtk_widget_get_toplevel (Fenetre);
    ViderContenaire(GTK_CONTAINER(Fenetre));
    GtkWidget *Box,*Bouton1, *Bouton2, *Bouton3,*Box_2, *Label;
    gchar *Text;
    choix=2;
    int taille1,taille2;
    taille1=strlen(Donnees->cle);
    gchar tmp[TAILLETEXTE];
    strcpy(tmp,Donnees->cle);
   ConvertisseurTableau(Donnees->cle,&taille2,tmp);
    taille2=strlen(Donnees->cle);
     if ((taille1 != taille2) || (taille1 == 0))
		{    GtkWidget *pAbout;
 
    pAbout = gtk_message_dialog_new (GTK_WINDOW(Fenetre),
        GTK_DIALOG_MODAL,
        GTK_MESSAGE_INFO,
        GTK_BUTTONS_OK,
        "votre cle %s\n n'est pas utilisable",
        tmp);
    gtk_dialog_run(GTK_DIALOG(pAbout));
    gtk_widget_destroy(pAbout);
		MenuCryptage(Fenetre);
		}
    Box = gtk_vbox_new(FALSE, 0);
    gtk_container_add(GTK_CONTAINER(Fenetre), Box);
    Box_2 = gtk_hbox_new(FALSE, 0);
    ///////////////mettre la cle dans un fichier///////////
    FILE* fichier= NULL;
    remove("cle.txt");
    fichier=fopen("cle.txt","w");

    if (fichier != NULL)
    {
        fputs(Donnees->cle,fichier);
        fclose(fichier);
    }
    /////////////////////////////////
    Label=gtk_label_new(NULL);
    Text = g_locale_to_utf8("<span font_desc=\"Times New Roman italic 12\" foreground=\"#1d1d1d\">Chiffrement Vigenere</span>\n",
    -1, NULL, NULL, NULL);
    gtk_label_set_markup(GTK_LABEL(Label), Text);
    g_free(Text);
    gtk_label_set_justify(GTK_LABEL(Label), GTK_JUSTIFY_CENTER);

    gtk_box_pack_start(GTK_BOX(Box), Box_2, TRUE, TRUE, 0);

    Bouton3 = gtk_button_new_with_label("R");
    g_signal_connect(G_OBJECT(Bouton3), "clicked", G_CALLBACK(MenuPrincipal), NULL);
    gtk_box_pack_start(GTK_BOX(Box_2), Bouton3, FALSE, TRUE, 0);

    gtk_box_pack_start(GTK_BOX(Box_2), Label, TRUE, TRUE, 0);
    
    Bouton1 = gtk_button_new_with_label("Rentrer un texte ");
    g_signal_connect(G_OBJECT(Bouton1), "clicked", G_CALLBACK(BoiteDialogueVigenereTexte), Donnees);
    gtk_box_pack_start(GTK_BOX(Box), Bouton1, TRUE, TRUE, 0);
    
    Bouton2 = gtk_button_new_with_label("choisir un fichier");
    g_signal_connect(G_OBJECT(Bouton2), "clicked", G_CALLBACK(ChoisirFichier),NULL);
    gtk_box_pack_start(GTK_BOX(Box), Bouton2, TRUE, TRUE, 0);
    
    gtk_widget_show_all(Fenetre);
}

void MenuCryptageSubstitution(GtkWidget *Fenetre)
{
    Fenetre = gtk_widget_get_toplevel (Fenetre); 
	ViderContenaire(GTK_CONTAINER(Fenetre));
	GtkWidget *Box,*Bouton1, *Bouton2, *Bouton3,*Box_2, *Label;
    gchar* Text;
    choix=1;
    
    Box = gtk_vbox_new(FALSE, 0);
    gtk_container_add(GTK_CONTAINER(Fenetre), Box);
    Box_2= gtk_hbox_new(FALSE, 0);
    
    Label=gtk_label_new(NULL);
    Text = g_locale_to_utf8("<span font_desc=\"Times New Roman italic 12\" foreground=\"#1d1d1d\">Chiffrement Substitution</span>\n",
    -1, NULL, NULL, NULL);
    gtk_label_set_markup(GTK_LABEL(Label), Text);
    g_free(Text);
    gtk_label_set_justify(GTK_LABEL(Label), GTK_JUSTIFY_CENTER);

    gtk_box_pack_start(GTK_BOX(Box), Box_2, TRUE, TRUE, 0);

    Bouton3 = gtk_button_new_with_label("R");
    g_signal_connect(G_OBJECT(Bouton3), "clicked", G_CALLBACK(MenuCryptage), NULL);
    gtk_box_pack_start(GTK_BOX(Box_2), Bouton3, FALSE, TRUE, 0);

    gtk_box_pack_start(GTK_BOX(Box_2), Label, TRUE, TRUE, 0);
    
    Bouton1 = gtk_button_new_with_label("Rentrer un texte ");
    g_signal_connect(G_OBJECT(Bouton1), "clicked", G_CALLBACK(BoiteDialogueSubstitution), NULL);
    gtk_box_pack_start(GTK_BOX(Box), Bouton1, TRUE, TRUE, 0);
    
    Bouton2 = gtk_button_new_with_label("choisir un fichier");
    g_signal_connect(G_OBJECT(Bouton2), "clicked", G_CALLBACK(ChoisirFichier), NULL);
    gtk_box_pack_start(GTK_BOX(Box), Bouton2, TRUE, TRUE, 0);
    
    gtk_widget_show_all(Fenetre);

}

void MenuAnalyseFrequentielle(GtkWidget *Fenetre)
{
    Fenetre = gtk_widget_get_toplevel (Fenetre);
	ViderContenaire(GTK_CONTAINER(Fenetre));
	GtkWidget *Box,*Bouton1, *Bouton2, *Bouton3,*Box_2, *Label;
    gchar* Text;
    choix=5;
    Box = gtk_vbox_new(FALSE, 0);
    gtk_container_add(GTK_CONTAINER(Fenetre), Box);
    Box_2 = gtk_hbox_new(FALSE, 0);
   
    Label=gtk_label_new(NULL);
    Text = g_locale_to_utf8("<span font_desc=\"Times New Roman italic 12\" foreground=\"#1d1d1d\">Analyse Frequentielle</span>\n",
    -1, NULL, NULL, NULL);
    gtk_label_set_markup(GTK_LABEL(Label), Text);
    g_free(Text);
    gtk_label_set_justify(GTK_LABEL(Label), GTK_JUSTIFY_CENTER);

    gtk_box_pack_start(GTK_BOX(Box), Box_2, TRUE, TRUE, 0);

    Bouton3 = gtk_button_new_with_label("R");
    g_signal_connect(G_OBJECT(Bouton3), "clicked", G_CALLBACK(MenuPrincipal), NULL);
    gtk_box_pack_start(GTK_BOX(Box_2), Bouton3, FALSE, TRUE, 0);

    gtk_box_pack_start(GTK_BOX(Box_2), Label, TRUE, TRUE, 0);
    
    Bouton1 = gtk_button_new_with_label("Rentrer un texte ");
    g_signal_connect(G_OBJECT(Bouton1), "clicked", G_CALLBACK(BoiteDialogueAnalyse), NULL);
    gtk_box_pack_start(GTK_BOX(Box), Bouton1, TRUE, TRUE, 0);
    
    Bouton2 = gtk_button_new_with_label("choisir un fichier");
    g_signal_connect(G_OBJECT(Bouton2), "clicked", G_CALLBACK(ChoisirFichier), NULL);
    gtk_box_pack_start(GTK_BOX(Box), Bouton2, TRUE, TRUE, 0);
    
    gtk_widget_show_all(Fenetre);

}

void MenuDecryptage(GtkWidget *Fenetre)
{
    Fenetre = gtk_widget_get_toplevel (Fenetre); 
	ViderContenaire(GTK_CONTAINER(Fenetre));
	GtkWidget *Box,*Bouton1, *Bouton2, *Bouton3,*Box_2, *Label;
    gchar* Text;
    
    Box = gtk_vbox_new(FALSE, 0);
    gtk_container_add(GTK_CONTAINER(Fenetre), Box);
    Box_2=gtk_hbox_new(FALSE, 0);
    
    Label=gtk_label_new(NULL);
    Text = g_locale_to_utf8("<span font_desc=\"Times New Roman italic 12\" foreground=\"#1d1d1d\">Dechiffrement</span>\n"
    "<span font_desc=\"Times New Roman italic 12\" foreground=\"#1d1d1d\">Choisir le type de dechiffrement</span>\n",
    -1, NULL, NULL, NULL);
    gtk_label_set_markup(GTK_LABEL(Label), Text);
    g_free(Text);
    gtk_label_set_justify(GTK_LABEL(Label), GTK_JUSTIFY_CENTER);

    gtk_box_pack_start(GTK_BOX(Box), Box_2, TRUE, TRUE, 0);

    Bouton3 = gtk_button_new_with_label("R");
    g_signal_connect(G_OBJECT(Bouton3), "clicked", G_CALLBACK(MenuPrincipal), NULL);
    gtk_box_pack_start(GTK_BOX(Box_2), Bouton3, FALSE, TRUE, 0);

    gtk_box_pack_start(GTK_BOX(Box_2), Label, TRUE, TRUE, 0);
    
    Bouton1 = gtk_button_new_with_label("Substitution");
    g_signal_connect(G_OBJECT(Bouton1), "clicked", G_CALLBACK(MenuDecryptageSubstitution), NULL);
    gtk_box_pack_start(GTK_BOX(Box), Bouton1, TRUE, TRUE, 0);
    
    Bouton2 = gtk_button_new_with_label("Vigenere");
    g_signal_connect(G_OBJECT(Bouton2), "clicked", G_CALLBACK(MenuDecryptageVigenere), NULL);
    gtk_box_pack_start(GTK_BOX(Box), Bouton2, TRUE, TRUE, 0);
    
    gtk_widget_show_all(Fenetre);
}

void MenuCryptage(GtkWidget *Fenetre)
{
    Fenetre = gtk_widget_get_toplevel (Fenetre);
	ViderContenaire(GTK_CONTAINER(Fenetre));
	GtkWidget *Box,*Bouton1, *Bouton2, *Bouton3,*Box_2, *Label;
    gchar* Text;
    
    Box = gtk_vbox_new(FALSE, 0);
    gtk_container_add(GTK_CONTAINER(Fenetre), Box);
    Box_2=gtk_hbox_new(FALSE, 0);

    Label=gtk_label_new(NULL);
    Text = g_locale_to_utf8("<span font_desc=\"Times New Roman italic 12\" foreground=\"#1d1d1d\">Chiffrement</span>\n"
    "<span font_desc=\"Times New Roman italic 12\" foreground=\"#1d1d1d\">Choisir le type de chiffrement</span>\n",
    -1, NULL, NULL, NULL);
    gtk_label_set_markup(GTK_LABEL(Label), Text);
    g_free(Text);
    gtk_label_set_justify(GTK_LABEL(Label), GTK_JUSTIFY_CENTER);

    gtk_box_pack_start(GTK_BOX(Box), Box_2, TRUE, TRUE, 0);

    Bouton3 = gtk_button_new_with_label("R");
    g_signal_connect(G_OBJECT(Bouton3), "clicked", G_CALLBACK(MenuPrincipal), NULL);
    gtk_box_pack_start(GTK_BOX(Box_2), Bouton3, FALSE, TRUE, 0);
    
    gtk_box_pack_start(GTK_BOX(Box_2), Label, TRUE, TRUE, 0);

    Bouton1 = gtk_button_new_with_label("Substitution");
    g_signal_connect(G_OBJECT(Bouton1), "clicked", G_CALLBACK(MenuCryptageSubstitution), NULL);
    gtk_box_pack_start(GTK_BOX(Box), Bouton1, TRUE, TRUE, 0);
    
    Bouton2 = gtk_button_new_with_label("Vigenere");
    g_signal_connect(G_OBJECT(Bouton2), "clicked", G_CALLBACK(BoiteDialogueVigenereCle), NULL);
    gtk_box_pack_start(GTK_BOX(Box), Bouton2, TRUE, TRUE, 0);
    
    gtk_widget_show_all(Fenetre);
}

void MenuPrincipal(GtkWidget *Fenetre)
{
    Fenetre = gtk_widget_get_toplevel (Fenetre);
	ViderContenaire(GTK_CONTAINER(Fenetre));
	GtkWidget *Box, *Label,*Bouton1, *Bouton2, *Bouton3;
    gchar* Text;
    
    Box = gtk_vbox_new(FALSE, 0);
    gtk_container_add(GTK_CONTAINER(Fenetre), Box);

    Label=gtk_label_new(NULL);
    Text = g_locale_to_utf8("<span font_desc=\"Times New Roman italic 12\" foreground=\"#1d1d1d\">Dcrypt</span>\n",
    -1, NULL, NULL, NULL);
    gtk_label_set_markup(GTK_LABEL(Label), Text);
    g_free(Text);
    gtk_label_set_justify(GTK_LABEL(Label), GTK_JUSTIFY_CENTER);
    gtk_box_pack_start(GTK_BOX(Box), Label, TRUE, TRUE, 0);
    
    Bouton1 = gtk_button_new_with_label("Chiffrer");
    g_signal_connect(G_OBJECT(Bouton1), "clicked", G_CALLBACK(MenuCryptage), NULL);
    gtk_box_pack_start(GTK_BOX(Box), Bouton1, TRUE, TRUE, 0);
    
    Bouton2 = gtk_button_new_with_label("Dechiffrer");
    g_signal_connect(G_OBJECT(Bouton2), "clicked", G_CALLBACK(ChoisirLangue), NULL);
    gtk_box_pack_start(GTK_BOX(Box), Bouton2, TRUE, TRUE, 0);
    
    Bouton3 = gtk_button_new_with_label("Analyse Frequentielle");
    g_signal_connect(G_OBJECT(Bouton3), "clicked", G_CALLBACK(MenuAnalyseFrequentielle), NULL);
    gtk_box_pack_start(GTK_BOX(Box), Bouton3, TRUE, TRUE, 0);
    
    gtk_widget_show_all(Fenetre);
}



/*
 * le travail a fournir 
recuperer chemin faut mettre les clées 
il faut mettre une barre de progression pour eviter les seg faults (fait 70% )
changer le nom de choisirlangue

* les problemes rencontrés 
il ya des seg fault quand on fait 2 enregistrement du texte
*/
