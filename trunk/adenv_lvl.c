/*
    adenv.c - A LADSPA plugin to generate percussive (i.e no sustain time), linear AD envelopes.
    This one takes in levels to make  filter sweeps/etc easier. 
                 
    Copyright (C) 2005 Loki Davison 
    based of DADSR by Mike Rawes

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#include <stdlib.h>
#include <ladspa.h>
#include <stdio.h>
#include <math.h>
//#include "gettext.h"

#ifdef ENABLE_NLS
#include <locale.h>
#define G_(s) gettext(s)
#else
#define G_(s) (s)
#endif
#define G_NOP(s) s

/* 
#define DAHDSR_BASE_ID                   43
 */
#define DAHDSR_VARIANT_COUNT             1

#define DAHDSR_GATE                      0
#define DAHDSR_TRIGGER                   1
#define DAHDSR_START_LEVEL		 2
#define DAHDSR_ATTACK_LEVEL		 3
#define DAHDSR_DECAY_LEVEL               4
#define DAHDSR_ATTACK                    5
#define DAHDSR_DECAY                     6
#define DAHDSR_OUTPUT                    7

LADSPA_Descriptor ** dahdsr_descriptors = 0;

typedef enum
{
	IDLE,
	ATTACK,
	DECAY,
} DAHDSRState;

typedef struct
{
	LADSPA_Data * gate;
	LADSPA_Data * trigger;
	LADSPA_Data * attack;
	LADSPA_Data * decay;
	LADSPA_Data * start_level;
	LADSPA_Data * attack_level;
	LADSPA_Data * decay_level;
	LADSPA_Data * output;
	LADSPA_Data   srate;
	LADSPA_Data   inv_srate;
	LADSPA_Data   last_gate;
	LADSPA_Data   last_trigger;
	LADSPA_Data   from_level;
	LADSPA_Data   level;
	DAHDSRState   state;
	unsigned long samples;
} Dahdsr;

const LADSPA_Descriptor *
ladspa_descriptor (unsigned long index)
{
	if (index < DAHDSR_VARIANT_COUNT)
		return dahdsr_descriptors[index];

	return 0;
}

void
cleanupDahdsr (LADSPA_Handle instance)
{
	free (instance);
}

void
connectPortDahdsr (LADSPA_Handle instance,
                   unsigned long port,
                   LADSPA_Data * data)
{
	Dahdsr * plugin = (Dahdsr *)instance;

	switch (port)
	{
	case DAHDSR_GATE:
		plugin->gate = data;
		break;
	case DAHDSR_TRIGGER:
		plugin->trigger = data;
		break;
	case DAHDSR_START_LEVEL:
		plugin->start_level = data;
		break;
	case DAHDSR_ATTACK_LEVEL:
		plugin->attack_level = data;
		break;
	case DAHDSR_DECAY_LEVEL:
		plugin->decay_level = data;
		break;
	case DAHDSR_ATTACK:
		plugin->attack = data;
		break;
	case DAHDSR_DECAY:
		plugin->decay = data;
		break;
	case DAHDSR_OUTPUT:
		plugin->output = data;
		break;
	}
}

LADSPA_Handle
instantiateDahdsr (const LADSPA_Descriptor * descriptor,
                   unsigned long sample_rate)
{
	Dahdsr * plugin = (Dahdsr *) malloc (sizeof (Dahdsr));

	plugin->srate = (LADSPA_Data) sample_rate;
	plugin->inv_srate = 1.0f / plugin->srate;

	return (LADSPA_Handle) plugin;
}

void
activateDahdsr (LADSPA_Handle instance)
{
	Dahdsr * plugin = (Dahdsr *) instance;

	plugin->last_gate = 0.0f;
	plugin->last_trigger = 0.0f;
	plugin->from_level = 0.0f;
	plugin->level = 0.0f;
	plugin->state = IDLE;
	plugin->samples = 0;
}


void
runDahdsr_Control (LADSPA_Handle instance,
                   unsigned long sample_count)
{
	Dahdsr * plugin = (Dahdsr *) instance;

/* Gate */
	LADSPA_Data * gate = plugin->gate;

/* Trigger */
	LADSPA_Data * trigger = plugin->trigger;
/* start level */
	LADSPA_Data start_level = * (plugin->start_level);
/* attack level */
	LADSPA_Data attack_level = * (plugin->attack_level);
/* decay level */
	LADSPA_Data decay_level = * (plugin->decay_level);

/* Attack Time (s) */
	LADSPA_Data attack = * (plugin->attack);

/* Decay Time (s) */
	LADSPA_Data decay = * (plugin->decay);

/* Envelope Out */
	LADSPA_Data * output = plugin->output;

/* Instance Data */
	LADSPA_Data srate = plugin->srate;
	LADSPA_Data inv_srate = plugin->inv_srate;
	LADSPA_Data last_gate = plugin->last_gate;
	LADSPA_Data last_trigger = plugin->last_trigger;
	LADSPA_Data from_level = plugin->from_level;
	LADSPA_Data level = plugin->level;
	DAHDSRState state = plugin->state;
	unsigned long samples = plugin->samples;

	LADSPA_Data gat, trg, att, dec;
	LADSPA_Data elapsed;
	unsigned long s;

/* Convert times into rates */
	att = attack > 0.0f ? inv_srate / attack : srate;
	dec = decay > 0.0f ? inv_srate / decay : srate;
	/* cuse's formula ...
	 * ReleaseCoeff = (ln(EndLevel) - ln(StartLevel)) / (EnvelopeDuration * SampleRate)
	 *
	 *  while (currentSample < endSample) Level += Level * ReleaseCoeff;
	 */
	/* check params don't cause div by zero */
	if(start_level == 0){
	    start_level=0.001;
	}
	if(attack_level == 0){
	    attack_level=0.001;
	}	
	if(decay_level == 0){
	    decay_level=0.001;
	}		
	LADSPA_Data ReleaseCoeff_att = (log(attack_level) - log(start_level)) / (attack * srate);
	LADSPA_Data ReleaseCoeff_dec = (log(decay_level) - log(attack_level)) / (decay * srate);
	
	for (s = 0; s < sample_count; s++)
	{
		gat = gate[s];
		trg = trigger[s];

	/* Initialise delay phase if gate is opened and was closed, or
	   we received a trigger */
		if ((trg > 0.0f && !(last_trigger > 0.0f)) ||
		    (gat > 0.0f && !(last_gate > 0.0f)))
		{
		     //fprintf(stderr, "triggered in control \n");
			if (att < srate)
			{
				state = ATTACK;
			}
			samples = 0;
		}

		if (samples == 0)
			from_level = level;

	/* Calculate level of envelope from current state */
		switch (state)
		{
		case IDLE:
			/* might need to fix this... */
			level = start_level;
			//level = 0.0f;
			break;
		case ATTACK:
			/* fix level adding prob */
			if(samples == 0)
			{
			    level = start_level;
			}			    
			samples++;
			elapsed = (LADSPA_Data) samples * att;
			if (elapsed > 1.0f)
			{
				state = DECAY;
				samples = 0;
				fprintf(stderr, "finished attack, RC %f, level %f attack_level %f start %f\n", ReleaseCoeff_att, level, attack_level, start_level);
			} else {
				level += level * ReleaseCoeff_att;
			}
			break;
		case DECAY:
			samples++;
			elapsed = (LADSPA_Data) samples * dec;
			if (elapsed > 1.0f)
			{
				fprintf(stderr, "finished decay, RC %f , level %f decay_level %f start %f\n", ReleaseCoeff_dec, level, decay_level, start_level);
				state = IDLE;
				samples = 0;
			}
			else
			{
				level += level * ReleaseCoeff_dec;
		    	}
			break;
		default:
		/* Should never happen */
			fprintf(stderr, "bugger!!!");
			level = 0.0f;
		}

		output[s] = level;
		last_gate = gat;
		last_trigger = trg;
	}

	plugin->last_gate = last_gate;
	plugin->last_trigger = last_trigger;
	plugin->from_level = from_level;
	plugin->level = level;
	plugin->state = state;
	plugin->samples = samples;
}


void
_init (void)
{
	static const unsigned long ids[] = {2662};
	static const char * labels[] = {"adenv_lvl"};
	static const char * names[] = {G_NOP("Percussive AD Envelope with levels")};
	char ** port_names;
	LADSPA_PortDescriptor * port_descriptors;
	LADSPA_PortRangeHint * port_range_hints;
	LADSPA_Descriptor * descriptor;
	int i;

	LADSPA_PortDescriptor gate_port_descriptors[] = {LADSPA_PORT_INPUT | LADSPA_PORT_AUDIO};
	LADSPA_PortDescriptor trigger_port_descriptors[] = {LADSPA_PORT_INPUT | LADSPA_PORT_AUDIO};
	LADSPA_PortDescriptor start_level_port_descriptors[] = {LADSPA_PORT_INPUT | LADSPA_PORT_CONTROL};
	LADSPA_PortDescriptor attack_level_port_descriptors[] = {LADSPA_PORT_INPUT | LADSPA_PORT_CONTROL};
	LADSPA_PortDescriptor decay_level_port_descriptors[] = {LADSPA_PORT_INPUT | LADSPA_PORT_CONTROL};
	LADSPA_PortDescriptor attack_port_descriptors[] = {LADSPA_PORT_INPUT | LADSPA_PORT_CONTROL};
	LADSPA_PortDescriptor decay_port_descriptors[] = {LADSPA_PORT_INPUT | LADSPA_PORT_CONTROL};
	LADSPA_PortDescriptor output_port_descriptors[] = {LADSPA_PORT_OUTPUT | LADSPA_PORT_AUDIO};

	void (*run_functions[]) (LADSPA_Handle,
	                         unsigned long) = {runDahdsr_Control};

#ifdef ENABLE_NLS
	setlocale (LC_ALL, "");
	bindtextdomain (PACKAGE, LOCALEDIR);
	textdomain (PACKAGE);
#endif

	dahdsr_descriptors = (LADSPA_Descriptor **) calloc (DAHDSR_VARIANT_COUNT, sizeof (LADSPA_Descriptor));

	if (dahdsr_descriptors)
	{
			int i = 0;
		        dahdsr_descriptors[i] = (LADSPA_Descriptor *) malloc (sizeof (LADSPA_Descriptor));
			descriptor = dahdsr_descriptors[i];
			if (descriptor)
			{
				descriptor->UniqueID = ids[i];
				descriptor->Label = labels[i];
				descriptor->Properties = LADSPA_PROPERTY_HARD_RT_CAPABLE;
				descriptor->Name = G_(names[i]);
				descriptor->Maker = "Loki Davison <ltdav1[at]student.monash.edu.au>";
				descriptor->Copyright = "GPL";

				descriptor->PortCount = 8;

				port_descriptors = (LADSPA_PortDescriptor *) calloc (8, sizeof (LADSPA_PortDescriptor));
				descriptor->PortDescriptors = (const LADSPA_PortDescriptor *)port_descriptors;

				port_range_hints = (LADSPA_PortRangeHint *) calloc (8, sizeof (LADSPA_PortRangeHint));
				descriptor->PortRangeHints = (const LADSPA_PortRangeHint *) port_range_hints;

				port_names = (char **) calloc (8, sizeof (char*));
				descriptor->PortNames = (const char **) port_names;

			/* Parameters for Gate */
				port_descriptors[DAHDSR_GATE] = gate_port_descriptors[i];
				port_names[DAHDSR_GATE] = G_("Gate");
				port_range_hints[DAHDSR_GATE].HintDescriptor = LADSPA_HINT_TOGGLED;

			/* Parameters for Trigger */
				port_descriptors[DAHDSR_TRIGGER] = trigger_port_descriptors[i];
				port_names[DAHDSR_TRIGGER] = G_("Trigger");
				port_range_hints[DAHDSR_TRIGGER].HintDescriptor = LADSPA_HINT_TOGGLED;

			/* Parameters for Attack Time (s) */
				port_descriptors[DAHDSR_ATTACK] = attack_port_descriptors[i];
				port_names[DAHDSR_ATTACK] = G_("Attack Time (s)");
				port_range_hints[DAHDSR_ATTACK].HintDescriptor = LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_DEFAULT_MINIMUM;
				port_range_hints[DAHDSR_ATTACK].LowerBound = 0.0f;

			/* Parameters for Start Level */
				port_descriptors[DAHDSR_START_LEVEL] = start_level_port_descriptors[i];
				port_names[DAHDSR_START_LEVEL] = G_("Initial Level");
				port_range_hints[DAHDSR_START_LEVEL].HintDescriptor = LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_DEFAULT_MINIMUM;
				port_range_hints[DAHDSR_START_LEVEL].LowerBound = 0.0f;

			/* Parameters for Attack to level (s) */
				port_descriptors[DAHDSR_ATTACK_LEVEL] = attack_level_port_descriptors[i];
				port_names[DAHDSR_ATTACK_LEVEL] = G_("Attack to Level");
				port_range_hints[DAHDSR_ATTACK_LEVEL].HintDescriptor = LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_DEFAULT_1;
				port_range_hints[DAHDSR_ATTACK_LEVEL].LowerBound = 0.0f;

			/* Parameters for Decay to level (s) */
				port_descriptors[DAHDSR_DECAY_LEVEL] = decay_level_port_descriptors[i];
				port_names[DAHDSR_DECAY_LEVEL] = G_("Decay to Level");
				port_range_hints[DAHDSR_DECAY_LEVEL].HintDescriptor = LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_DEFAULT_MINIMUM;
				port_range_hints[DAHDSR_DECAY_LEVEL].LowerBound = 0.0f;

			/* Parameters for Decay Time (s) */
				port_descriptors[DAHDSR_DECAY] = decay_port_descriptors[i];
				port_names[DAHDSR_DECAY] = G_("Decay Time (s)");
				port_range_hints[DAHDSR_DECAY].HintDescriptor = LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_DEFAULT_MINIMUM;
				port_range_hints[DAHDSR_DECAY].LowerBound = 0.0f;

			/* Parameters for Envelope Out */
				port_descriptors[DAHDSR_OUTPUT] = output_port_descriptors[i];
				port_names[DAHDSR_OUTPUT] = G_("Envelope Out");
				port_range_hints[DAHDSR_OUTPUT].HintDescriptor = 0;

				descriptor->activate = activateDahdsr;
				descriptor->cleanup = cleanupDahdsr;
				descriptor->connect_port = connectPortDahdsr;
				descriptor->deactivate = NULL;
				descriptor->instantiate = instantiateDahdsr;
				descriptor->run = run_functions[i];
				descriptor->run_adding = NULL;
				descriptor->set_run_adding_gain = NULL;
			}
	}	
	
}

void
_fini (void)
{
	LADSPA_Descriptor * descriptor;
	if (dahdsr_descriptors)
	{
		descriptor = dahdsr_descriptors[0];
		if (descriptor)
		{
			free ((LADSPA_PortDescriptor *) descriptor->PortDescriptors);
		    	free ((char **) descriptor->PortNames);
			free ((LADSPA_PortRangeHint *) descriptor->PortRangeHints);
			free (descriptor);
		}
		free (dahdsr_descriptors);
	}
}
