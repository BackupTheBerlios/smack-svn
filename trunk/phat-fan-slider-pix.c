/* Generated by GOB (v2.0.11) on Tue May  3 17:08:05 2005
   (do not edit directly) */

/* End world hunger, donate to the World Food Programme, http://www.wfp.org */

#define GOB_VERSION_MAJOR 2
#define GOB_VERSION_MINOR 0
#define GOB_VERSION_PATCHLEVEL 11

#define selfp (self->_priv)

#include <string.h> /* memset() */

#include "phat-fan-slider-pix.h"

#ifdef G_LIKELY
#define ___GOB_LIKELY(expr) G_LIKELY(expr)
#define ___GOB_UNLIKELY(expr) G_UNLIKELY(expr)
#else /* ! G_LIKELY */
#define ___GOB_LIKELY(expr) (expr)
#define ___GOB_UNLIKELY(expr) (expr)
#endif /* G_LIKELY */

#line 11 "phatfansliderpix.gob"

#include <stdio.h>
#include <glib.h>

enum
{
     FAN_RISE = 3,
     FAN_RUN = 1,
     SLIDER_WIDTH = 16,
     SLIDER_LENGTH = 32,
     THRESHOLD = 4,
};


#line 40 "phat-fan-slider-pix.c"
/* self casting macros */
#define SELF(x) PHAT_FAN_SLIDER_PIX(x)
#define SELF_CONST(x) PHAT_FAN_SLIDER_PIX_CONST(x)
#define IS_SELF(x) PHAT_IS_FAN_SLIDER_PIX(x)
#define TYPE_SELF PHAT_TYPE_FAN_SLIDER_PIX
#define SELF_CLASS(x) PHAT_FAN_SLIDER_PIX_CLASS(x)

#define SELF_GET_CLASS(x) PHAT_FAN_SLIDER_PIX_GET_CLASS(x)

/* self typedefs */
typedef PhatFanSliderPix Self;
typedef PhatFanSliderPixClass SelfClass;

/* here are local prototypes */
static void phat_fan_slider_pix_class_init (PhatFanSliderPixClass * class) G_GNUC_UNUSED;
static void phat_fan_slider_pix_init (PhatFanSliderPix * self) G_GNUC_UNUSED;
static void phat_fan_slider_pix_calc_layout (PhatFanSlider * slider, int * x, int * y, int * w, int * h) G_GNUC_UNUSED;

/* pointer to the class of our parent */
static PhatFanSliderClass *parent_class = NULL;

/* Short form macros */
#define self_new phat_fan_slider_pix_new
#define self_new_with_range phat_fan_slider_pix_new_with_range
#define self_calc_layout phat_fan_slider_pix_calc_layout
#define self_expose phat_fan_slider_pix_expose
GType
phat_fan_slider_pix_get_type (void)
{
	static GType type = 0;

	if ___GOB_UNLIKELY(type == 0) {
		static const GTypeInfo info = {
			sizeof (PhatFanSliderPixClass),
			(GBaseInitFunc) NULL,
			(GBaseFinalizeFunc) NULL,
			(GClassInitFunc) phat_fan_slider_pix_class_init,
			(GClassFinalizeFunc) NULL,
			NULL /* class_data */,
			sizeof (PhatFanSliderPix),
			0 /* n_preallocs */,
			(GInstanceInitFunc) phat_fan_slider_pix_init,
			NULL
		};

		type = g_type_register_static (PHAT_TYPE_FAN_SLIDER, "PhatFanSliderPix", &info, (GTypeFlags)0);
	}

	return type;
}

/* a macro for creating a new object of our type */
#define GET_NEW ((PhatFanSliderPix *)g_object_new(phat_fan_slider_pix_get_type(), NULL))

/* a function for creating a new object of our type */
#include <stdarg.h>
static PhatFanSliderPix * GET_NEW_VARG (const char *first, ...) G_GNUC_UNUSED;
static PhatFanSliderPix *
GET_NEW_VARG (const char *first, ...)
{
	PhatFanSliderPix *ret;
	va_list ap;
	va_start (ap, first);
	ret = (PhatFanSliderPix *)g_object_new_valist (phat_fan_slider_pix_get_type (), first, ap);
	va_end (ap);
	return ret;
}

#line 32 "phatfansliderpix.gob"
static void 
phat_fan_slider_pix_class_init (PhatFanSliderPixClass * class G_GNUC_UNUSED)
#line 112 "phat-fan-slider-pix.c"
{
#define __GOB_FUNCTION__ "Phat:Fan:Slider:Pix::class_init"

	parent_class = g_type_class_ref (PHAT_TYPE_FAN_SLIDER);

 {
#line 33 "phatfansliderpix.gob"

	GtkWidgetClass* widget_class = (GtkWidgetClass*) class;
	widget_class->expose_event = phat_fan_slider_pix_expose;

    
#line 125 "phat-fan-slider-pix.c"
 }
}
#undef __GOB_FUNCTION__
#line 39 "phatfansliderpix.gob"
static void 
phat_fan_slider_pix_init (PhatFanSliderPix * self G_GNUC_UNUSED)
#line 132 "phat-fan-slider-pix.c"
{
#define __GOB_FUNCTION__ "Phat:Fan:Slider:Pix::init"
 {
#line 40 "phatfansliderpix.gob"

	self->filled = gdk_pixbuf_new_from_file(PKGDATADIR "/pixmaps/slider_full.png", NULL);
	self->empty = gdk_pixbuf_new_from_file(PKGDATADIR "/pixmaps/slider_empty.png", NULL);
	
    
#line 142 "phat-fan-slider-pix.c"
 }
}
#undef __GOB_FUNCTION__



#line 46 "phatfansliderpix.gob"
GtkWidget * 
phat_fan_slider_pix_new (GtkAdjustment * adjustment)
#line 152 "phat-fan-slider-pix.c"
{
#define __GOB_FUNCTION__ "Phat:Fan:Slider:Pix::new"
{
#line 47 "phatfansliderpix.gob"
	
	PhatFanSliderPix* slider;

	g_assert (adjustment->lower < adjustment->upper);
	g_assert ((adjustment->value >= adjustment->lower)
	       && (adjustment->value <= adjustment->upper));

	slider = g_object_new (PHAT_TYPE_FAN_SLIDER_PIX, NULL);

	PHAT_FAN_SLIDER (slider)->orientation = GTK_ORIENTATION_HORIZONTAL;

	phat_fan_slider_set_adjustment (PHAT_FAN_SLIDER (slider), adjustment);

	return (GtkWidget*) slider;

    }}
#line 173 "phat-fan-slider-pix.c"
#undef __GOB_FUNCTION__

#line 64 "phatfansliderpix.gob"
GtkWidget * 
phat_fan_slider_pix_new_with_range (double value, double lower, double upper, double step)
#line 179 "phat-fan-slider-pix.c"
{
#define __GOB_FUNCTION__ "Phat:Fan:Slider:Pix::new_with_range"
{
#line 66 "phatfansliderpix.gob"
	
	GtkAdjustment* adj;

	adj = (GtkAdjustment*) gtk_adjustment_new (value, lower, upper, step, step, 0);
     
	return phat_fan_slider_pix_new (adj);
    }}
#line 191 "phat-fan-slider-pix.c"
#undef __GOB_FUNCTION__

#line 74 "phatfansliderpix.gob"
static void 
phat_fan_slider_pix_calc_layout (PhatFanSlider * slider, int * x, int * y, int * w, int * h)
#line 197 "phat-fan-slider-pix.c"
{
#define __GOB_FUNCTION__ "Phat:Fan:Slider:Pix::calc_layout"
{
#line 76 "phatfansliderpix.gob"
	

	GtkWidget* widget = GTK_WIDGET (slider);
	int focus_width, focus_pad;
	int pad;
	  
        gtk_widget_style_get (widget,
			   "focus-line-width", &focus_width,
			   "focus-padding", &focus_pad,
			   NULL);

	pad = focus_width + focus_pad;

	if (slider->orientation == GTK_ORIENTATION_VERTICAL)
	{
	    *x = widget->allocation.x + (widget->allocation.width - SLIDER_WIDTH) / 2;
	    *y = widget->allocation.y + pad;
	    *w = SLIDER_WIDTH;
	    *h = widget->allocation.height - 2*pad;
	}
	else
	{
	    *x = widget->allocation.x + pad;
	    *y = widget->allocation.y + (widget->allocation.height - SLIDER_WIDTH) / 2;
	    *w = widget->allocation.width - 2*pad;
	    *h = SLIDER_WIDTH;
	}
    }}
#line 230 "phat-fan-slider-pix.c"
#undef __GOB_FUNCTION__

#line 106 "phatfansliderpix.gob"
gboolean 
phat_fan_slider_pix_expose (GtkWidget * widget, GdkEventExpose * event)
#line 236 "phat-fan-slider-pix.c"
{
#define __GOB_FUNCTION__ "Phat:Fan:Slider:Pix::expose"
{
#line 107 "phatfansliderpix.gob"
	
     PhatFanSlider* slider;
     PhatFanSliderPix* pix;
     int x, y;
     int w, h;
     int fx, fy;		/* "filled" coordinates */
     int fw, fh;
     GdkPixbuf* scaled;
     
     
     g_return_val_if_fail (widget != NULL, FALSE);
     g_return_val_if_fail (PHAT_IS_FAN_SLIDER (widget), FALSE);
     g_return_val_if_fail (event != NULL, FALSE);


     //debug ("expose\n");
     if (event->count > 0)
	  return FALSE;

     slider = (PhatFanSlider*) widget;
     pix =  (PhatFanSliderPix*) widget;
     scaled = gdk_pixbuf_copy(pix->empty);
              
     phat_fan_slider_pix_calc_layout (slider, &x, &y, &w, &h);
     
     if (slider->orientation == GTK_ORIENTATION_VERTICAL)
     {
	  if (slider->center_val >= 0)
	  {
	       fw = w;
	       fh = ABS (slider->val - slider->center_val) * h;
	       fx = x;
	       fy = y + h - (slider->center_val * h);

	       if ((slider->val > slider->center_val && !slider->inverted)
		   || (slider->val < slider->center_val && slider->inverted))
	       {
		    fy -= fh;
	       }

	  }
	  else
	  {
	       fw = w;
	       fh = slider->val * h;
	       fx = x;
	       fy = (slider->inverted)? y: y + h - fh;
	  }
     }
     else /* horizontal */
     {
	  if (slider->center_val >= 0)
	  {
	       fw = ABS (slider->val - slider->center_val) * w;
	       fh = h;
	       fx = x + (slider->center_val * w);
	       fy = y;

	       if ((slider->val < slider->center_val && !slider->inverted)
		   || (slider->val > slider->center_val && slider->inverted))
	       {
		    fx -= fw;
	       }
	  }
	  else
	  {
	       fw = slider->val * w;
	       fh = h;
	       fx = (slider->inverted)? x + w - fw: x;
	       fy = y;
	  }
     }
     
     /* Should there just be a different function for pixmaped and non-pixmaped or what? Rc file? param?
      * currently just has non-pixmaped commented out. */

     
     if (!GTK_WIDGET_SENSITIVE (widget))
     {
	 /*
	  gdk_draw_rectangle (widget->window,
			      widget->style->dark_gc[GTK_STATE_INSENSITIVE],
			      TRUE,
			      x, y,
			      w, h);

	  gdk_draw_rectangle (widget->window,
			      widget->style->fg_gc[GTK_STATE_INSENSITIVE],
			      TRUE,
			      fx, fy,
			      fw, fh); */

	  goto skiplines;	/* skip drawing the extra marker lines */
     }
     else
     {
	  //fprintf(stderr, "i think x is %d %d \n", fw, w);
	  //DODGY KLUDGE FIXME for falling of the end of the image
	  if(fw > 66)
	  {
		  gdk_pixbuf_composite(pix->filled, scaled, 0, 0, 66, fh, 0, 0, 1, 1, GDK_INTERP_BILINEAR, 255);
	  
	  } 
	  else
	  {
		  gdk_pixbuf_composite(pix->filled, scaled, 0, 0, fw+1, fh, 0, 0, 1, 1, GDK_INTERP_BILINEAR, 255);
	  }
	  scaled = gdk_pixbuf_scale_simple (scaled, w, h, GDK_INTERP_BILINEAR);
	  gdk_draw_pixbuf(widget->window,NULL, scaled, 0, 0, x, y, -1, -1, GDK_RGB_DITHER_NONE, 0, 0);
	  /*    
	  gdk_draw_rectangle (widget->window,
			      widget->style->dark_gc[GTK_STATE_NORMAL],
			      TRUE,
			      x, y,
			      w, h);

	  gdk_draw_rectangle (widget->window,
			      widget->style->base_gc[GTK_STATE_SELECTED],
			      TRUE,
			      fx, fy,
			      fw, fh);
	  */
	  
     }

     if (slider->orientation == GTK_ORIENTATION_VERTICAL)
     {
	  int line_y;
	  
	  if (slider->center_val >= 0)
	  {
	       line_y = fy;

	       if ((slider->val > slider->center_val && slider->inverted)
		   || (slider->val < slider->center_val && !slider->inverted))
	       {
		    line_y += fh;
	       }
	       
	       line_y = CLAMP (line_y, y, y + h-1);

	       gdk_draw_line (widget->window,
			      widget->style->fg_gc[GTK_STATE_NORMAL],
			      x,
			      line_y,
			      x + w - 1,
			      line_y);

	       line_y = (1 - slider->center_val) * h + y;
	       
	       gdk_draw_line (widget->window,
			      widget->style->base_gc[GTK_STATE_NORMAL],
			      x,
			      line_y,
			      x + w - 1,
			      line_y);
	  }
	  else
	  {
	       line_y = fy;

	       if (slider->inverted)
		    line_y += fh;

	       line_y = CLAMP (line_y, y, y + h-1);
	  
	       gdk_draw_line (widget->window,
			      widget->style->fg_gc[GTK_STATE_NORMAL],
			      x,
			      line_y,
			      x + w - 1,
			      line_y);
	  }
     }
     else
     {
	  int line_x;
	  
	  if (slider->center_val >= 0)
	  {
	       line_x = fx;

	       if ((slider->val < slider->center_val && slider->inverted)
		   || (slider->val > slider->center_val && !slider->inverted))
	       {
		    line_x += fw;
	       }
	       
	       line_x = CLAMP (line_x, x, x + w-1);
	       
	       gdk_draw_line (widget->window,
			      widget->style->fg_gc[GTK_STATE_NORMAL],
			      line_x,
			      y,
			      line_x,
			      y + h - 1);

	       line_x =  slider->center_val * w + x;

	       gdk_draw_line (widget->window,
			      widget->style->base_gc[GTK_STATE_NORMAL],
			      line_x,
			      y,
			      line_x,
			      y + h - 1);
	  }
	  else
	  {
	       line_x = fx;

	       if (!slider->inverted)
		    line_x += fw;
	       
	       line_x = CLAMP (line_x, x, x + w-1);
	
	       /* we can have this when i work out the bitmask thingy */
	       
	       /*gdk_draw_pixbuf(widget->window,widget->style->fg_gc[GTK_STATE_NORMAL], slider->edge, 0, 0, line_x, y, -1, -1, GDK_RGB_DITHER_MAX, 0, 0);*/	       
	  }
     }

skiplines:
     /*
     gtk_paint_shadow (widget->style,
		       widget->window,
		       GTK_STATE_NORMAL,
		       GTK_SHADOW_IN,
		       NULL, widget, NULL,
		       x, y,
		       w, h);*/

     if (GTK_WIDGET_HAS_FOCUS (widget))
     {
	  int focus_width, focus_pad;
	  int pad;
	  
	  gtk_widget_style_get (widget,
				"focus-line-width", &focus_width,
				"focus-padding", &focus_pad,
				NULL);

	  pad = focus_width + focus_pad;

	  x -= pad;
	  y -= pad;
	  w += 2*pad;
	  h += 2*pad;

	  gtk_paint_focus (widget->style, widget->window, GTK_WIDGET_STATE (widget),
			   NULL, widget, NULL,
			   x, y, w, h);
     }

     if (GTK_WIDGET_VISIBLE (slider->fan_window))
	  gtk_widget_queue_draw (slider->fan_window);
     
     return FALSE;
  }}
#line 499 "phat-fan-slider-pix.c"
#undef __GOB_FUNCTION__
