/* Generated by GOB (v2.0.11) on Thu May 12 23:48:17 2005
   (do not edit directly) */

/* End world hunger, donate to the World Food Programme, http://www.wfp.org */

#define GOB_VERSION_MAJOR 2
#define GOB_VERSION_MINOR 0
#define GOB_VERSION_PATCHLEVEL 11

#define selfp (self->_priv)

#include <string.h> /* memset() */

#ifdef G_LIKELY
#define ___GOB_LIKELY(expr) G_LIKELY(expr)
#define ___GOB_UNLIKELY(expr) G_UNLIKELY(expr)
#else /* ! G_LIKELY */
#define ___GOB_LIKELY(expr) (expr)
#define ___GOB_UNLIKELY(expr) (expr)
#endif /* G_LIKELY */

#line 13 "drum.gob"

#ifndef HAVE_GETOPT_LONG
#       include "getopt.h"
#else
#       include <getopt.h>
#endif

#include "gui-drum.h"
#include "gui.h"
#include "phat-fan-slider-pix.h"
#include <stdio.h>
#include <glib.h>
#include <stdlib.h>
#include <stdarg.h>

lo_address addr;

#line 41 "gui-drum.c"
/* self casting macros */
#define SELF(x) GUI_DRUM(x)
#define SELF_CONST(x) GUI_DRUM_CONST(x)
#define IS_SELF(x) GUI_IS_DRUM(x)
#define TYPE_SELF GUI_TYPE_DRUM
#define SELF_CLASS(x) GUI_DRUM_CLASS(x)

#define SELF_GET_CLASS(x) GUI_DRUM_GET_CLASS(x)

/* self typedefs */
typedef guiDrum Self;
typedef guiDrumClass SelfClass;

/* here are local prototypes */
static void gui_drum_class_init (guiDrumClass * c) G_GNUC_UNUSED;
static void gui_drum_init (guiDrum * self) G_GNUC_UNUSED;
static gint gui_drum_osc_cb (GtkWidget * widget, gpointer data) G_GNUC_UNUSED;
static gint gui_drum_load_cb (GtkWidget * widget, gpointer data) G_GNUC_UNUSED;

/* pointer to the class of our parent */
static GtkVBoxClass *parent_class = NULL;

/* Short form macros */
#define self_new gui_drum_new
#define self_new_drum gui_drum_new_drum
#define self_osc_cb gui_drum_osc_cb
#define self_load_cb gui_drum_load_cb
GType
gui_drum_get_type (void)
{
	static GType type = 0;

	if ___GOB_UNLIKELY(type == 0) {
		static const GTypeInfo info = {
			sizeof (guiDrumClass),
			(GBaseInitFunc) NULL,
			(GBaseFinalizeFunc) NULL,
			(GClassInitFunc) gui_drum_class_init,
			(GClassFinalizeFunc) NULL,
			NULL /* class_data */,
			sizeof (guiDrum),
			0 /* n_preallocs */,
			(GInstanceInitFunc) gui_drum_init,
			NULL
		};

		type = g_type_register_static (GTK_TYPE_VBOX, "guiDrum", &info, (GTypeFlags)0);
	}

	return type;
}

/* a macro for creating a new object of our type */
#define GET_NEW ((guiDrum *)g_object_new(gui_drum_get_type(), NULL))

/* a function for creating a new object of our type */
#include <stdarg.h>
static guiDrum * GET_NEW_VARG (const char *first, ...) G_GNUC_UNUSED;
static guiDrum *
GET_NEW_VARG (const char *first, ...)
{
	guiDrum *ret;
	va_list ap;
	va_start (ap, first);
	ret = (guiDrum *)g_object_new_valist (gui_drum_get_type (), first, ap);
	va_end (ap);
	return ret;
}

static void 
gui_drum_class_init (guiDrumClass * c G_GNUC_UNUSED)
{
#define __GOB_FUNCTION__ "gui:Drum::class_init"

	parent_class = g_type_class_ref (GTK_TYPE_VBOX);

}
#undef __GOB_FUNCTION__
#line 34 "drum.gob"
static void 
gui_drum_init (guiDrum * self G_GNUC_UNUSED)
#line 123 "gui-drum.c"
{
#define __GOB_FUNCTION__ "gui:Drum::init"
}
#undef __GOB_FUNCTION__



#line 40 "drum.gob"
GtkWidget * 
gui_drum_new (void)
#line 134 "gui-drum.c"
{
#define __GOB_FUNCTION__ "gui:Drum::new"
{
#line 41 "drum.gob"
	
	return (GtkWidget *)GET_NEW;
    }}
#line 142 "gui-drum.c"
#undef __GOB_FUNCTION__

#line 45 "drum.gob"
GtkWidget * 
gui_drum_new_drum (const char * title, char * filename, char * drumname, int note, GHashTable * sliders, lo_address address, ...)
#line 148 "gui-drum.c"
{
#define __GOB_FUNCTION__ "gui:Drum::new_drum"
{
#line 48 "drum.gob"
	
	va_list ap;
	va_start(ap, address);
	addr = address;
	GtkWidget* widget = (GtkWidget *)GET_NEW;
	GtkWidget* hbox;
	GtkWidget* slider;
	GtkWidget* label;
	GtkWidget* check;
	int i = 0;
	double lower, upper;
	char* name;
	char* key;
	
	gtk_box_set_spacing(GTK_BOX(widget), 0);
	hbox = gtk_hbox_new(FALSE, GUI_SPACING);
	gtk_widget_show(hbox);	
	/* the name of this drum, goes at the top */
	label = gtk_label_new(title);
        gtk_label_set_markup(GTK_LABEL(label), g_strconcat("<b>", title, "</b>", NULL));	
	gtk_box_pack_start(GTK_BOX(hbox), label, FALSE, FALSE, 0);
	gtk_widget_show(label);
	check = gtk_check_button_new();
	gtk_box_pack_start(GTK_BOX(hbox), check, FALSE, FALSE, 0);
	gtk_widget_show(check);
	gtk_object_set_data(GTK_OBJECT(check), "drum_name", drumname);
	gtk_object_set_data(GTK_OBJECT(check), "file_name", filename);
	gtk_box_pack_start(GTK_BOX(widget), hbox, FALSE, FALSE, 10);

	/* midi note selector 
	label = gtk_label_new("Note");
        gtk_box_pack_start(GTK_BOX(widget), label, FALSE, FALSE, 0);
	gtk_widget_show(label);

	button = phat_slider_button_new_with_range(note, 0, 127, 1, "%.0f");
	phat_slider_button_set_threshold(PHAT_SLIDER_BUTTON(button), GUI_THRESHOLD);
	gtk_box_pack_start(GTK_BOX(widget), button, FALSE, FALSE, 0);
	gtk_widget_show(button); */

	/* velocity sensitivity, right now just volume */ 
	label = gtk_label_new("Velocity");  
	gtk_box_pack_start(GTK_BOX(widget), label, FALSE, FALSE, 0);
	gtk_misc_set_alignment(GTK_MISC(label), 0, 0.5);
	gtk_widget_show(label);
	slider = phat_fan_slider_pix_new_with_range(1, 0, 3, 0.1);
	gtk_box_pack_start(GTK_BOX(widget), slider, FALSE, FALSE, 0); 
	gtk_widget_show(slider);
	key=g_strconcat("/", drumname, "/amp_mono_0/Gain", NULL);
	gtk_object_set_data(GTK_OBJECT(slider), "key", key);
	g_hash_table_insert (sliders, key, slider); 
	/* connect change parm to osc */
	g_signal_connect (slider, "value-changed", G_CALLBACK (gui_drum_osc_cb), NULL);

	
	    
	while((name = va_arg(ap, char*)) != NULL)
	{
	    
	    label = gtk_label_new(name);  
	    gtk_box_pack_start(GTK_BOX(widget), label, FALSE, FALSE, 0);
	    gtk_misc_set_alignment(GTK_MISC(label), 0, 0.5);
	    gtk_widget_show(label);
	    lower = va_arg(ap, double);
	    upper = va_arg(ap, double);
	    

	    
	    /* loop over each param creating a slider for it */  
	    slider = phat_fan_slider_pix_new_with_range(0, lower, upper, 0.1);
	    gtk_box_pack_start(GTK_BOX(widget), slider, FALSE, FALSE, 0); 
	    gtk_widget_show(slider);

	    	    
	    gtk_object_set_data(GTK_OBJECT(slider), "drum_name", drumname);
	    gtk_object_set_data(GTK_OBJECT(slider), "node_name", va_arg(ap, char*));
	    gtk_object_set_data(GTK_OBJECT(slider), "param_name", va_arg(ap, char*));
	   	    
	    key=g_strconcat("/", drumname, "/", gtk_object_get_data(GTK_OBJECT(slider), "node_name"), "/", gtk_object_get_data(GTK_OBJECT(slider), "param_name"), NULL);
	    gtk_object_set_data(GTK_OBJECT(slider), "key", key);
	    //fprintf(stderr, "add the keys is %s \n", key);  
	    g_hash_table_insert (sliders, key, slider); 
	    /* connect change parm to osc */
	    g_signal_connect (slider, "value-changed", G_CALLBACK (gui_drum_osc_cb), NULL);
	    i++;
	}
	
	gtk_object_set_data(GTK_OBJECT(check), "param_num", GINT_TO_POINTER(i));
	g_signal_connect (G_OBJECT (check), "toggled", G_CALLBACK (gui_drum_load_cb), filename);

 
	gtk_widget_set_size_request(widget, 85, -1);

	return widget;
    }}
#line 247 "gui-drum.c"
#undef __GOB_FUNCTION__

#line 143 "drum.gob"
static gint 
gui_drum_osc_cb (GtkWidget * widget, gpointer data)
#line 253 "gui-drum.c"
{
#define __GOB_FUNCTION__ "gui:Drum::osc_cb"
{
#line 145 "drum.gob"
	
	if (lo_send(addr, "/om/synth/set_port_value", "isf", 42, (gchar*) gtk_object_get_data(GTK_OBJECT(widget), "key"), phat_fan_slider_get_value(PHAT_FAN_SLIDER (widget))) == -1) {
	    printf("OSC error %d: %s\n", lo_address_errno(addr), lo_address_errstr(addr));
	}
	return TRUE;
    }}
#line 264 "gui-drum.c"
#undef __GOB_FUNCTION__

#line 153 "drum.gob"
static gint 
gui_drum_load_cb (GtkWidget * widget, gpointer data)
#line 270 "gui-drum.c"
{
#define __GOB_FUNCTION__ "gui:Drum::load_cb"
{
#line 155 "drum.gob"
	
	
	GError   *error = NULL;
	gchar   *command;
	     	    
	if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget))) /* load patch */
	{
	    command = g_strconcat("om_patch_loader -p16180 ", PKGDATADIR, "/", (gchar*) gtk_object_get_data(GTK_OBJECT(widget), "file_name"), NULL);

	    if (!g_spawn_command_line_async(command, &error)){
		g_warning("g_spawn_async_with_pipes() failed: %s\n", error->message);
		g_error_free(error);
		error = NULL;
		return 0;
	    }
	   	    
	} 
	 else
	{
	    command = g_strconcat("/", (gchar*) gtk_object_get_data(GTK_OBJECT(widget), "drum_name"), NULL);
	    if (lo_send(addr, "/om/synth/destroy_patch", "is", 42, command)
		        == -1){
		printf("OSC error %d: %s\n", lo_address_errno(addr), lo_address_errstr(addr));
	    }
	}    
	
	g_free(command);	 
	return TRUE;
    }}
#line 304 "gui-drum.c"
#undef __GOB_FUNCTION__
