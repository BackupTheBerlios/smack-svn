/* Generated by GOB (v2.0.8) on Sat Dec  4 16:06:30 2004
   (do not edit directly) */

/* End world hunger, donate to the World Food Programme, http://www.wfp.org */

#define GOB_VERSION_MAJOR 2
#define GOB_VERSION_MINOR 0
#define GOB_VERSION_PATCHLEVEL 8

#define selfp (self->_priv)

#ifdef G_LIKELY
#define ___GOB_LIKELY(expr) G_LIKELY(expr)
#define ___GOB_UNLIKELY(expr) G_UNLIKELY(expr)
#else /* ! G_LIKELY */
#define ___GOB_LIKELY(expr) (expr)
#define ___GOB_UNLIKELY(expr) (expr)
#endif /* G_LIKELY */

#line 12 "drum.gob"

#include "gui-drum.h"
#include "gui.h"
#include "phat-fan-slider-pix.h"
#include <stdio.h>
#include <glib.h>
#include <stdarg.h>

lo_address addr;

#line 32 "gui-drum.c"
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

/* pointer to the class of our parent */
static GtkVBoxClass *parent_class = NULL;

/* Short form macros */
#if defined(__GNUC__) && !defined(__STRICT_ANSI__)
#define self_new() gui_drum_new()
#define self_new_drum(args...) gui_drum_new_drum(args)
#define self_osc_cb(args...) gui_drum_osc_cb(args)
#endif /* __GNUC__ && !__STRICT_ANSI__ */

/* Short form pointers */
static GtkWidget * (* const self_new) (void) = gui_drum_new;
static GtkWidget * (* const self_new_drum) (const char * title, int note, lo_address address, ...) = gui_drum_new_drum;
static gint (* const self_osc_cb) (GtkWidget * widget, gpointer data) = gui_drum_osc_cb;

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
gui_drum_class_init (guiDrumClass * c)
{
#define __GOB_FUNCTION__ "gui:Drum::class_init"

	parent_class = g_type_class_ref (GTK_TYPE_VBOX);

	return;
	c = NULL;
}
#undef __GOB_FUNCTION__
#line 26 "drum.gob"
static void 
gui_drum_init (guiDrum * self)
#line 121 "gui-drum.c"
{
#define __GOB_FUNCTION__ "gui:Drum::init"
	return;
	self = NULL;
}
#undef __GOB_FUNCTION__



#line 32 "drum.gob"
GtkWidget * 
gui_drum_new (void)
#line 134 "gui-drum.c"
{
#define __GOB_FUNCTION__ "gui:Drum::new"
{
#line 33 "drum.gob"
	
	return (GtkWidget *)GET_NEW;
    }}
#line 142 "gui-drum.c"
#undef __GOB_FUNCTION__

#line 37 "drum.gob"
GtkWidget * 
gui_drum_new_drum (const char * title, int note, lo_address address, ...)
#line 148 "gui-drum.c"
{
#define __GOB_FUNCTION__ "gui:Drum::new_drum"
{
#line 40 "drum.gob"
	
	va_list ap;
	va_start(ap, address);
	addr = address;	  
	GtkWidget* widget = (GtkWidget *)GET_NEW;
	GtkWidget* slider;
	GtkWidget* label;
	/*GtkWidget* button;*/
	char* name;

	gtk_box_set_spacing(GTK_BOX(widget), 2);  
	/* the name of this drum, goes at the top */
	label = gtk_label_new(title);
        gtk_label_set_markup(GTK_LABEL(label), g_strconcat("<b>", title, "</b>", NULL));	
	gtk_box_pack_start(GTK_BOX(widget), label, FALSE, FALSE, 10);
	gtk_widget_show(label);

	/* midi note selector 
	label = gtk_label_new("Note");
        gtk_box_pack_start(GTK_BOX(widget), label, FALSE, FALSE, 0);
	gtk_widget_show(label);

	button = phat_slider_button_new_with_range(note, 0, 127, 1, "%.0f");
	phat_slider_button_set_threshold(PHAT_SLIDER_BUTTON(button), GUI_THRESHOLD);
	gtk_box_pack_start(GTK_BOX(widget), button, FALSE, FALSE, 0);
	gtk_widget_show(button); */

	/* velocity sensitivity */
	label = gtk_label_new("Vel. Sens.");  
	gtk_box_pack_start(GTK_BOX(widget), label, FALSE, FALSE, 0);
	gtk_widget_show(label);
	    
	slider = phat_fan_slider_pix_new_with_range(1, 0.0, 1.0, .1);
	gtk_box_pack_start(GTK_BOX(widget), slider, FALSE, FALSE, 0); 
	gtk_widget_show(slider);

   
	while((name = va_arg(ap, char*)) != NULL)
	{
	    	
	    /* loop over each param creating a slider for it */
	    label = gtk_label_new(name);  
	    gtk_box_pack_start(GTK_BOX(widget), label, FALSE, FALSE, 0);
	    gtk_widget_show(label);
	    
	    slider = phat_fan_slider_pix_new_with_range(.5, 0.0, 1.0, .1);
	    gtk_box_pack_start(GTK_BOX(widget), slider, FALSE, FALSE, 0); 
	    gtk_widget_show(slider);
	    
	    /* connect change parm to osc */
	    g_signal_connect (G_OBJECT (slider), "value-changed", G_CALLBACK (gui_drum_osc_cb), va_arg(ap, char*));
	    
	}
	
	  
	  gtk_widget_set_size_request(widget, 65, -1);

	return widget;
    }}
#line 212 "gui-drum.c"
#undef __GOB_FUNCTION__

#line 100 "drum.gob"
static gint 
gui_drum_osc_cb (GtkWidget * widget, gpointer data)
#line 218 "gui-drum.c"
{
#define __GOB_FUNCTION__ "gui:Drum::osc_cb"
{
#line 102 "drum.gob"
	
	if (lo_send(addr, "/patch/set_control", "ssif", "808cowbell", data, 0, phat_fan_slider_get_value(PHAT_FAN_SLIDER (widget))) == -1) {
	    printf("OSC error %d: %s\n", lo_address_errno(addr), lo_address_errstr(addr));
	} 
	fprintf(stderr, "frobing the knobs %s\n", (char*)data);
	return TRUE;
    }}
#line 230 "gui-drum.c"
#undef __GOB_FUNCTION__


#if (!defined __GNUC__) || (defined __GNUC__ && defined __STRICT_ANSI__)
/*REALLY BAD HACK
  This is to avoid unused warnings if you don't call
  some method.  I need to find a better way to do
  this, not needed in GCC since we use some gcc
  extentions to make saner, faster code */
static void
___gui_drum_really_bad_hack_to_avoid_warnings(void)
{
	((void (*)(void))GET_NEW_VARG)();
	((void (*)(void))self_new)();
	((void (*)(void))self_new_drum)();
	((void (*)(void))self_osc_cb)();
	___gui_drum_really_bad_hack_to_avoid_warnings();
}
#endif /* !__GNUC__ || (__GNUC__ && __STRICT_ANSI__) */

