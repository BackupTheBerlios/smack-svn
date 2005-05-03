/* Generated by GOB (v2.0.11)   (do not edit directly) */

#include <glib.h>
#include <glib-object.h>
#ifndef __PHAT_FAN_SLIDER_PIX_H__
#define __PHAT_FAN_SLIDER_PIX_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */



#include <phat/phatfanslider.h>


/*
 * Type checking and casting macros
 */
#define PHAT_TYPE_FAN_SLIDER_PIX	(phat_fan_slider_pix_get_type())
#define PHAT_FAN_SLIDER_PIX(obj)	G_TYPE_CHECK_INSTANCE_CAST((obj), phat_fan_slider_pix_get_type(), PhatFanSliderPix)
#define PHAT_FAN_SLIDER_PIX_CONST(obj)	G_TYPE_CHECK_INSTANCE_CAST((obj), phat_fan_slider_pix_get_type(), PhatFanSliderPix const)
#define PHAT_FAN_SLIDER_PIX_CLASS(klass)	G_TYPE_CHECK_CLASS_CAST((klass), phat_fan_slider_pix_get_type(), PhatFanSliderPixClass)
#define PHAT_IS_FAN_SLIDER_PIX(obj)	G_TYPE_CHECK_INSTANCE_TYPE((obj), phat_fan_slider_pix_get_type ())

#define PHAT_FAN_SLIDER_PIX_GET_CLASS(obj)	G_TYPE_INSTANCE_GET_CLASS((obj), phat_fan_slider_pix_get_type(), PhatFanSliderPixClass)

/*
 * Main object structure
 */
#ifndef __TYPEDEF_PHAT_FAN_SLIDER_PIX__
#define __TYPEDEF_PHAT_FAN_SLIDER_PIX__
typedef struct _PhatFanSliderPix PhatFanSliderPix;
#endif
struct _PhatFanSliderPix {
	PhatFanSlider __parent__;
	/*< public >*/
	GdkPixbuf * filled;
	GdkPixbuf * empty;
	GdkPixbuf * edge;
};

/*
 * Class definition
 */
typedef struct _PhatFanSliderPixClass PhatFanSliderPixClass;
struct _PhatFanSliderPixClass {
	PhatFanSliderClass __parent__;
};


/*
 * Public methods
 */
GType	phat_fan_slider_pix_get_type	(void);
GtkWidget * 	phat_fan_slider_pix_new	(GtkAdjustment * adjustment);
GtkWidget * 	phat_fan_slider_pix_new_with_range	(double value,
					double lower,
					double upper,
					double step);
gboolean 	phat_fan_slider_pix_expose	(GtkWidget * widget,
					GdkEventExpose * event);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
