/*
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Library General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

/* Temp GUI ideas for Smack. */

#include <gtk/gtk.h>
#include <phat/phat.h>
#include "lo/lo.h"
#include "gui-drum.h"
#include "gui.h"

int main(int argc, char* argv[])
{
    GtkWidget* window;
    GtkWidget* box;
    GtkWidget* vbox;
    GtkWidget* hbox;
    GtkWidget* vbox2;
    GtkWidget* label;
    GtkWidget* button;
    GtkWidget* sep;
    GtkWidget* drum;
        
    gtk_init(&argc, &argv);

    /* setup OSC */
    lo_address addr = lo_address_new(NULL, "19383");
    
    /* main window */
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Smack GUI");
    gtk_container_set_border_width(GTK_CONTAINER(window), GUI_SPACING);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_resizable(GTK_WINDOW(window), TRUE);
    g_signal_connect(G_OBJECT(window), "delete-event",
		     G_CALLBACK(gtk_main_quit), NULL);
    
    /* hold the individual engines */
    vbox = gtk_vbox_new(FALSE, GUI_SPACING);
    gtk_container_add(GTK_CONTAINER(window), vbox);
    gtk_widget_show(vbox);
    
    /* TR 808 */ 
    box = gtk_hbox_new(FALSE, GUI_SPACING);
    gtk_box_pack_start(GTK_BOX(vbox), box, FALSE, FALSE, 0);
    gtk_widget_show(box);
 
    label = gtk_label_new("TR-808");
    gtk_label_set_markup(GTK_LABEL(label), "<big><b> TR-808 </b></big>");   
    gtk_widget_show(label);
    gtk_box_pack_start(GTK_BOX(box), label, FALSE, FALSE, 0);
    
    button = phat_slider_button_new_with_range(10, 0, 16, 1, "%.0f");
    phat_slider_button_set_threshold(PHAT_SLIDER_BUTTON(button), GUI_THRESHOLD);
    gtk_box_pack_end(GTK_BOX(box), button, FALSE, FALSE, 0);
    gtk_widget_show(button);
    label = gtk_label_new("Midi Channel:");
    gtk_box_pack_end(GTK_BOX(box), label, FALSE, FALSE, 0);
    gtk_widget_show(label);

    /* hbox for each drum */
    box = gtk_hbox_new(FALSE, GUI_SPACING);
    gtk_box_pack_start(GTK_BOX(vbox), box, FALSE, FALSE, 0);
    gtk_widget_show(box);

    /* bass drum, each drum is a widget, with a null terminated list of name / param pairs */
    drum = gui_drum_new_drum("Bass", "om/smack808/808bass.om", "808bass", 1, addr, "tune", "/smack/bass/tune", 0, "tone", "/smack/bass/tone", 0, "decay","/smack/bass/decay", 0, NULL);
    gtk_widget_show(drum);
    gtk_box_pack_start(GTK_BOX(box), drum, FALSE, FALSE, 0);

    /*seperator*/
    sep = gtk_vseparator_new();
    gtk_widget_show(sep);
    gtk_box_pack_start(GTK_BOX(box), sep, FALSE, FALSE, 0);
    
    /* snare drum */
    drum = gui_drum_new_drum("Snare", "om/smack808/808snare.om", "808snare", 2, addr, "snappy", "/smack/snare/snappy", 0, "tone", "/smack/snare/tone", 0, "decay","/smack/snare/decay", 0, "hpf", "/smack/snare/hpf", 0, NULL);
    gtk_widget_show(drum);
    gtk_box_pack_start(GTK_BOX(box), drum, FALSE, FALSE, 0);


     /*seperator*/
    sep = gtk_vseparator_new();
    gtk_widget_show(sep);
    gtk_box_pack_start(GTK_BOX(box), sep, FALSE, FALSE, 0);
       
    /* claves */
    drum = gui_drum_new_drum("Claves", "om/smack808/808clave.om", "808claves", 6, addr, "tune", "/s/clave/tune", 0, "BPF", "/s/clave/BPF", 0, NULL);
    gtk_widget_show(drum);
    gtk_box_pack_start(GTK_BOX(box), drum, FALSE, FALSE, 0);

     /*seperator*/
    sep = gtk_vseparator_new();
    gtk_widget_show(sep);
    gtk_box_pack_start(GTK_BOX(box), sep, FALSE, FALSE, 0);
       
    /* cowbell */
    drum = gui_drum_new_drum("Cowbell", "/home/loki/Documents/svn/trunk/om/smack808/808cowbell.om", "808cowbell", 8, addr, "tune1", "triangle_fcsc_oa0", 0, "tune2", "triangle_fcsc_oa1", 0, "decay","/smack/cowbell/decay", 0, NULL);
    gtk_widget_show(drum);
    gtk_box_pack_start(GTK_BOX(box), drum, FALSE, FALSE, 0);

     /*seperator*/
    sep = gtk_vseparator_new();
    gtk_widget_show(sep);
    gtk_box_pack_start(GTK_BOX(box), sep, FALSE, FALSE, 0);

    
    /* hihat */
    drum = gui_drum_new_drum("Hihat", "om/smack808/808hihat.om", "808hihat", 9, addr, "tune", "/s/hh/tune", 0, "CH decay", "/s/hh/chdecay", 0, "OH decay", "/s/hh/ohdecay", 0, NULL);
    gtk_widget_show(drum);
    gtk_box_pack_start(GTK_BOX(box), drum, FALSE, FALSE, 0);

    /* END 808 */

    hbox = gtk_hbox_new(FALSE, GUI_SPACING);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);
    gtk_widget_show(hbox);

     /* TR 909 */ 
    vbox2 = gtk_vbox_new(FALSE, GUI_SPACING);
    gtk_box_pack_start(GTK_BOX(hbox), vbox2, FALSE, FALSE, 0);
    gtk_widget_show(vbox2);
    
    box = gtk_hbox_new(FALSE, GUI_SPACING);
    gtk_box_pack_start(GTK_BOX(vbox2), box, FALSE, FALSE, 0);
    gtk_widget_show(box);
 
    label = gtk_label_new("TR-909");
    gtk_label_set_markup(GTK_LABEL(label), "<big><b> TR-909 </b></big>");   
    gtk_widget_show(label);
    gtk_box_pack_start(GTK_BOX(box), label, FALSE, FALSE, 0);
    
    button = phat_slider_button_new_with_range(10, 0, 16, 1, "%.0f");
    phat_slider_button_set_threshold(PHAT_SLIDER_BUTTON(button), GUI_THRESHOLD);
    gtk_box_pack_end(GTK_BOX(box), button, FALSE, FALSE, 0);
    gtk_widget_show(button);
    label = gtk_label_new("Midi Channel:");
    gtk_box_pack_end(GTK_BOX(box), label, FALSE, FALSE, 0);
    gtk_widget_show(label);

     /* hbox for each drum */
    box = gtk_hbox_new(FALSE, GUI_SPACING);
    gtk_box_pack_start(GTK_BOX(vbox2), box, FALSE, FALSE, 0);
    gtk_widget_show(box); 

    /* bass drum */
    drum = gui_drum_new_drum("Bass", "om/smack909/909bass.om", "909bass", 1, addr, "tune", "/smack/bass/tune", 0, "tone", "/smack/bass/tone", 0, "decay","/smack/bass/decay", 0, NULL);
    gtk_widget_show(drum);
    gtk_box_pack_start(GTK_BOX(box), drum, FALSE, FALSE, 0);

    /*seperator*/
    sep = gtk_vseparator_new();
    gtk_widget_show(sep);
    gtk_box_pack_start(GTK_BOX(box), sep, FALSE, FALSE, 0);
    
    /* snare drum */
    drum = gui_drum_new_drum("Snare", "om/smack909/909snare.om", "909snare", 2, addr, "snappy", "/smack/snare/snappy", 0, "tone", "/smack/snare/tone", 0, "decay","/smack/snare/decay", 0, "hpf", "/smack/snare/hpf", 0, NULL);
    gtk_widget_show(drum);
    gtk_box_pack_start(GTK_BOX(box), drum, FALSE, FALSE, 0); 

     /* END 909 */ 

    vbox2 = gtk_vbox_new(FALSE, GUI_SPACING);
    gtk_box_pack_start(GTK_BOX(hbox), vbox2, FALSE, FALSE, 0);
    gtk_widget_show(vbox2);
    
       /* Smack FM */ 
    box = gtk_hbox_new(FALSE, GUI_SPACING);
    gtk_box_pack_start(GTK_BOX(vbox2), box, FALSE, FALSE, 0);
    gtk_widget_show(box);
 
    label = gtk_label_new("SmackFM");
    gtk_label_set_markup(GTK_LABEL(label), "<big><b> SmackFM </b></big>");   
    gtk_widget_show(label);
    gtk_box_pack_start(GTK_BOX(box), label, FALSE, FALSE, 0);
    
    button = phat_slider_button_new_with_range(10, 0, 16, 1, "%.0f");
    phat_slider_button_set_threshold(PHAT_SLIDER_BUTTON(button), GUI_THRESHOLD);
    gtk_box_pack_end(GTK_BOX(box), button, FALSE, FALSE, 0);
    gtk_widget_show(button);
    label = gtk_label_new("Midi Channel:");
    gtk_box_pack_end(GTK_BOX(box), label, FALSE, FALSE, 0);
    gtk_widget_show(label);

    /* hbox for each drum */
    box = gtk_hbox_new(FALSE, GUI_SPACING);
    gtk_box_pack_start(GTK_BOX(vbox2), box, FALSE, FALSE, 0);
    gtk_widget_show(box); 

    /* hihat low quality*/
    drum = gui_drum_new_drum("Hihat", "om/smackfm/sfmhihat2.om.om", "sfmhihat2", 1, addr, "tune", "/smack/bass/tune", 0, "tone", "/smack/bass/tone", 0, "decay","/smack/bass/decay", 0, NULL);
    gtk_widget_show(drum);
    gtk_box_pack_start(GTK_BOX(box), drum, FALSE, FALSE, 0);

    /*seperator*/
    sep = gtk_vseparator_new();
    gtk_widget_show(sep);
    gtk_box_pack_start(GTK_BOX(box), sep, FALSE, FALSE, 0);
    
    /* hihat hight quality*/
    drum = gui_drum_new_drum("Hihat+", "om/smackfm/sfmhihatbig.om", "sfmhihatbig", 2, addr, "tone", "/smack/snare/tone", 0, "decay","/smack/snare/decay", 0, "hpf", "/smack/snare/hpf", 0, NULL);
    gtk_widget_show(drum);
    gtk_box_pack_start(GTK_BOX(box), drum, FALSE, FALSE, 0); 

     /* END SFM */ 


    gtk_widget_show(window);
    gtk_main();

    return 0;
}
