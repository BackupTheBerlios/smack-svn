/* Generated by GOB (v2.0.8)   (do not edit directly) */

#include <glib.h>
#include <glib-object.h>
#ifndef __GUI_DRUM_H__
#define __GUI_DRUM_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */



#include <gtk/gtkvbox.h>
#include "lo/lo.h"


/*
 * Type checking and casting macros
 */
#define GUI_TYPE_DRUM	(gui_drum_get_type())
#define GUI_DRUM(obj)	G_TYPE_CHECK_INSTANCE_CAST((obj), gui_drum_get_type(), guiDrum)
#define GUI_DRUM_CONST(obj)	G_TYPE_CHECK_INSTANCE_CAST((obj), gui_drum_get_type(), guiDrum const)
#define GUI_DRUM_CLASS(klass)	G_TYPE_CHECK_CLASS_CAST((klass), gui_drum_get_type(), guiDrumClass)
#define GUI_IS_DRUM(obj)	G_TYPE_CHECK_INSTANCE_TYPE((obj), gui_drum_get_type ())

#define GUI_DRUM_GET_CLASS(obj)	G_TYPE_INSTANCE_GET_CLASS((obj), gui_drum_get_type(), guiDrumClass)

/*
 * Main object structure
 */
#ifndef __TYPEDEF_GUI_DRUM__
#define __TYPEDEF_GUI_DRUM__
typedef struct _guiDrum guiDrum;
#endif
struct _guiDrum {
	GtkVBox __parent__;
};

/*
 * Class definition
 */
typedef struct _guiDrumClass guiDrumClass;
struct _guiDrumClass {
	GtkVBoxClass __parent__;
};


/*
 * Public methods
 */
GType	gui_drum_get_type	(void);
GtkWidget * 	gui_drum_new	(void);
GtkWidget * 	gui_drum_new_drum	(const char * title,
					char * drumname,
					int note,
					lo_address address,
					...);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
