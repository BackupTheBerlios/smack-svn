#ifndef __GUI_H__
#define __GUI_H__

/* borrowed the enum from specimen! */

enum
{
    GUI_SPACING = 6, 		/* space between widgets */
    GUI_INDENT = 18,		/* how much to indent sections by */
    GUI_SECSPACE = 18, 		/* space between sections */
    GUI_TITLESPACE = 12,	/* space between a section title and its contents */
    GUI_TEXTSPACE = 12,		/* space between a label and its control */
    GUI_BORDERSPACE = 12,	/* space between a border and its guts */
    GUI_THRESHOLD = 20,         /* threshold used for sliderbuttons */
};

lo_address addr;

void error(int num, const char *msg, const char *path);
int generic_handler(const char *path, const char *types, lo_arg **argv, 
	int argc, void *data, void *user_data);
int param_handler(const char *path, const char *types, lo_arg **argv, 
	int argc, void *data, void *user_data);
void get_slider_vals (gpointer key, gpointer value, gpointer addr);

int node_handler(const char *path, const char *types, lo_arg **argv,
				    int argc, void *data, void *user_data);
#endif /* __GUI_H__ */
