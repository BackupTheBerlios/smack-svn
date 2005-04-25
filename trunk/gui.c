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

/* Smack, A Drum Synth. Written by Loki Davison. */

#ifdef HAVE_CONFIG_H
#       include "config.h"
#endif
/* Check for configure's getopt check result.  */
#ifndef HAVE_GETOPT_LONG
#       include "getopt.h"
#else
#       include <getopt.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <phat/phat.h>
#include "lo/lo.h"
#include "gui-drum.h"
#include "gui.h"
#include "cmdline.h"

int main(int argc, char* argv[])
{
    GtkWidget* window;
    GtkWidget* box;
    GtkWidget* vbox;
    GtkWidget* hbox;
    GtkWidget* vbox2;
    GtkWidget* label;
    //GtkWidget* button;
    GtkWidget* sep;
    GtkWidget* drum;
    GHashTable* sliders;
    struct gengetopt_args_info args_info;
        
    gtk_init(&argc, &argv);

    /* let's call our cmdline parser */
    if (cmdline_parser (argc, argv, &args_info) != 0)
	    exit(1) ;
   
    if (args_info.help_given)
    {
      	printf ("\n");
      	cmdline_parser_print_help ();
    }

    if (args_info.version_given)
    {
    	cmdline_parser_print_version ();
    }


    if (args_info.port_given)
    {
	/* setup OSC */
	addr = lo_address_new(NULL, args_info.port_arg);
    }
    else
    {
	fprintf(stderr, "should specify port, using default 16180...might not work \n");
	addr = lo_address_new(NULL, "16180");
    }
	
    sliders = g_hash_table_new(g_str_hash, g_str_equal); 
    /* setup server thread to handle responses */
    lo_server_thread st = lo_server_thread_new("16188", error);
    // debug method
    //lo_server_thread_add_method(st, NULL, NULL, generic_handler, NULL);
    
    lo_server_thread_add_method(st, "/om/control_change", "sf", param_handler, sliders);
    //lo_server_thread_add_method(st, "/om/new_port", "ssssfff", node_handler, sliders);
    lo_server_thread_start(st);

    if (lo_send(addr, "/om/engine/register_client", "i", 42) == -1) {
	    printf("OSC error %d: %s\n", lo_address_errno(addr), lo_address_errstr(addr));
    }

    
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
    
    /*
    button = phat_slider_button_new_with_range(10, 0, 16, 1, "%.0f");
    phat_slider_button_set_threshold(PHAT_SLIDER_BUTTON(button), GUI_THRESHOLD);
    gtk_box_pack_end(GTK_BOX(box), button, FALSE, FALSE, 0);
    gtk_widget_show(button);
    label = gtk_label_new("Midi Channel:");
    gtk_box_pack_end(GTK_BOX(box), label, FALSE, FALSE, 0);
    gtk_widget_show(label);*/

    /* hbox for each drum */
    box = gtk_hbox_new(FALSE, GUI_SPACING);
    gtk_box_pack_start(GTK_BOX(vbox), box, FALSE, FALSE, 0);
    gtk_widget_show(box);

    /* bass drum, each drum is a widget, see drum.gob */
    drum = gui_drum_new_drum("Bass", "om/smack808/808bass.om", "808bass", 35, sliders, addr, "Tune", 30.0, 400.0, "sine_fcac0", "Frequency", "Tone", 30.0, 400.0, "lowpass_iir0", "Cutoff Frequency", "Decay", 0.0, 4.0, "adenv_0", "Decay Time (s)", NULL);
    gtk_widget_show(drum);
    gtk_box_pack_start(GTK_BOX(box), drum, FALSE, FALSE, 0);

    /*seperator*/
    sep = gtk_vseparator_new();
    gtk_widget_show(sep);
    gtk_box_pack_start(GTK_BOX(box), sep, FALSE, FALSE, 0);
    
    /* snare drum */
    drum = gui_drum_new_drum("Snare", "om/smack808/808snare.om", "808snare", 38, sliders, addr, "Snappy", 0.0, 1.0, "noise_source_white0", "Amplitude", "Tone",  30.0, 800.0, "sine_fcac1", "Frequency", "Decay",  0.0, 4.0, "adenv_0", "Decay Time (s)", "HPF", 30.0, 800.0, "highpass_iir0", "Cutoff Frequency", NULL);
    gtk_widget_show(drum);
    gtk_box_pack_start(GTK_BOX(box), drum, FALSE, FALSE, 0);


     /*seperator*/
    sep = gtk_vseparator_new();
    gtk_widget_show(sep);
    gtk_box_pack_start(GTK_BOX(box), sep, FALSE, FALSE, 0);
       
    /* claves */
    drum = gui_drum_new_drum("Claves", "om/smack808/808clave.om", "808clave", 75, sliders, addr, "Tune", 50.0, 5000.0, "triangle_fcsc_oa0", "Frequency", "BPF", 50.0, 5000.0, "bandpass_a_iir0", "Center Frequency (Hz)", NULL);
    gtk_widget_show(drum);
    gtk_box_pack_start(GTK_BOX(box), drum, FALSE, FALSE, 0);

     /*seperator*/
    sep = gtk_vseparator_new();
    gtk_widget_show(sep);
    gtk_box_pack_start(GTK_BOX(box), sep, FALSE, FALSE, 0);
       
    /* cowbell */
    drum = gui_drum_new_drum("Cowbell", "om/smack808/808cowbell.om", "808cowbell", 56, sliders, addr, "Tune1", 50.0, 5000.0, "triangle_fcsc_oa0", "Frequency", "Tune2", 50.0, 5000.0, "triangle_fcsc_oa1", "Frequency", "Decay", 0.0, 4.0, "adenv_0", "Decay Time (s)", NULL);
    gtk_widget_show(drum);
    gtk_box_pack_start(GTK_BOX(box), drum, FALSE, FALSE, 0);

     /*seperator*/
    sep = gtk_vseparator_new();
    gtk_widget_show(sep);
    gtk_box_pack_start(GTK_BOX(box), sep, FALSE, FALSE, 0);

    
    /* hihat */
    drum = gui_drum_new_drum("Hihat", "om/smack808/808hihat.om", "808hihat", 42, sliders, addr, "Tune",  600.0, 20000.0, "bandpass_a_iir0", "Center Frequency (Hz)", "CH decay", 0.0, 4.0, "adenv_0", "Decay Time (s)", "OH decay", 0.0, 4.0, "adenv_1", "Decay Time (s)", NULL);
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
    
    /*
    button = phat_slider_button_new_with_range(10, 0, 16, 1, "%.0f");
    phat_slider_button_set_threshold(PHAT_SLIDER_BUTTON(button), GUI_THRESHOLD);
    gtk_box_pack_end(GTK_BOX(box), button, FALSE, FALSE, 0);
    gtk_widget_show(button);
    label = gtk_label_new("Midi Channel:");
    gtk_box_pack_end(GTK_BOX(box), label, FALSE, FALSE, 0);
    gtk_widget_show(label);
     */

     /* hbox for each drum */
    box = gtk_hbox_new(FALSE, GUI_SPACING);
    gtk_box_pack_start(GTK_BOX(vbox2), box, FALSE, FALSE, 0);
    gtk_widget_show(box); 

    /* bass drum */
    drum = gui_drum_new_drum("Bass", "om/smack909/909bass.om", "909bass", 36, sliders, addr, "Tune",  30.0, 600.0, "sine_faac0", "Frequency", "Tone", 30.0, 600.0, "lowpass_iir0", "Cutoff Frequency", "Decay", 0.0, 4.0, "adenv_lvl_0", "Decay Time (s)", NULL);
    gtk_widget_show(drum);
    gtk_box_pack_start(GTK_BOX(box), drum, FALSE, FALSE, 0);

    /*seperator*/
    sep = gtk_vseparator_new();
    gtk_widget_show(sep);
    gtk_box_pack_start(GTK_BOX(box), sep, FALSE, FALSE, 0);
    
    /* snare drum */
    drum = gui_drum_new_drum("Snare", "om/smack909/909snare.om", "909snare", 40, sliders, addr, "Snappy", 0.0, 1.0, "/smack/snare/snappy", 0, "Tone", 30.0, 800.0, "/smack/snare/tone", 0, "Decay", 0.0, 4.0, "/smack/snare/decay", 0, "HPF", 30.0, 800.0, "/smack/snare/hpf", 0, NULL);
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
    
    /*
    button = phat_slider_button_new_with_range(10, 0, 16, 1, "%.0f");
    phat_slider_button_set_threshold(PHAT_SLIDER_BUTTON(button), GUI_THRESHOLD);
    gtk_box_pack_end(GTK_BOX(box), button, FALSE, FALSE, 0);
    gtk_widget_show(button);
    label = gtk_label_new("Midi Channel:");
    gtk_box_pack_end(GTK_BOX(box), label, FALSE, FALSE, 0);
    gtk_widget_show(label);
    */
    
    /* hbox for each drum */
    box = gtk_hbox_new(FALSE, GUI_SPACING);
    gtk_box_pack_start(GTK_BOX(vbox2), box, FALSE, FALSE, 0);
    gtk_widget_show(box); 

    /* hihat low quality*/
    drum = gui_drum_new_drum("Hihat", "om/smackfm/sfmhihat2.om.om", "sfmhihat2", 49, sliders, addr, "Tune", 2000.0, 20000.0, "/smack/bass/tune", 0, "Tone", 2000.0, 20000.0, "/smack/bass/tone", 0, "Decay", 0.0, 4.0, "/smack/bass/decay", 0, NULL);
    gtk_widget_show(drum);
    gtk_box_pack_start(GTK_BOX(box), drum, FALSE, FALSE, 0);

    /*seperator*/
    sep = gtk_vseparator_new();
    gtk_widget_show(sep);
    gtk_box_pack_start(GTK_BOX(box), sep, FALSE, FALSE, 0);
    
    /* hihat high quality*/
    drum = gui_drum_new_drum("Hihat+", "om/smackfm/sfmhihatbig.om", "sfmhihatbig", 51, sliders, addr, "Tone",  2000.0, 20000.0, "/smack/snare/tone", 0, "Decay", 0.0, 4.0, "/smack/snare/decay", 0, "HPF",  2000.0, 20000.0, "/smack/snare/hpf", 0, NULL);
    gtk_widget_show(drum);
    gtk_box_pack_start(GTK_BOX(box), drum, FALSE, FALSE, 0); 

     /* END SFM */ 

    /* get value for all sliders by foreaching over the hashtable. */
    //g_hash_table_foreach (sliders, get_slider_vals, addr);

    gtk_widget_show(window);
    gtk_main();

    lo_server_thread_free(st);
    
    return 0;
}

void error(int num, const char *msg, const char *path)
{
    printf("liblo server error %d in path %s: %s\n", num, path, msg);
}

/* the keys are the full paths and the values are the pointer to the sliders */
void get_slider_vals (gpointer key, gpointer value, gpointer addr)
{
    if (lo_send(addr, "/om/request/port_value", "is", 4200, key) == -1)
    {
	printf("OSC error %d: %s\n", lo_address_errno(addr), lo_address_errstr(addr));
    }
}

int generic_handler(const char *path, const char *types, lo_arg **argv,
		    int argc, void *data, void *user_data)
{
    
    int i;

    printf("path: <%s>\n", path);
    for (i=0; i<argc; i++) {
	printf("arg %d '%c' ", i, types[i]);
	lo_arg_pp(types[i], argv[i]);
	printf("\n");
    }
    printf("\n");

    return 1;
}

int param_handler(const char *path, const char *types, lo_arg **argv,
		    int argc, void *data, void *user_data)
{
    gchar* key;
    GtkWidget* slider;
    //fprintf(stderr, "IN HERE!!! \n");
    //key = g_strconcat(&argv[0]->s, &argv[1]->s, NULL);
    key = &argv[0]->s;
    //fprintf(stderr, "key is %s \n", key);
    if((slider = g_hash_table_lookup((GHashTable*) user_data, key)) != NULL)
    {
	if(phat_fan_slider_get_value((PhatFanSlider *)slider) != 0)
	{
	    phat_fan_slider_set_value((PhatFanSlider *)slider, argv[1]->f);
	    //fprintf(stderr, "\n \n #### \n got value for slider %s %f\n ### \n", key, argv[1]->f);
	}
    }
    return 0;
}

int node_handler(const char *path, const char *types, lo_arg **argv,
		    int argc, void *data, void *user_data)
{
    fprintf(stderr, "\n \n #### \n found new port, checking it \n");
    if(g_hash_table_lookup((GHashTable*) user_data, &argv[0]->s))
    {
	 if (lo_send(addr, "/om/request/port_value", "is", 4200, &argv[0]->s) == -1)
	{
	    printf("OSC error %d: %s\n", lo_address_errno(addr), lo_address_errstr(addr));
	}

    }
    return 0;
}


