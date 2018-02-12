#ifndef _LIBMPSSE_CONTEXT_H_
#define _LIBMPSSE_CONTEXT_H_

#if LIBFTDI1 == 1
#include <libftdi1/ftdi.h>
#else
#include <ftdi.h>
#endif

#include "mpsse.h"

struct mpsse_context
{
	char *description;
	struct ftdi_context ftdi;
	enum modes mode;
	enum low_bits_status status;
	int flush_after_read;
	int vid;
	int pid;
	int clock;
	int xsize;
	int open;
	int endianess;
	uint8_t tris;
	uint8_t pstart;
	uint8_t pstop;
	uint8_t pidle;
	uint8_t gpioh;
	uint8_t trish;
	uint8_t bitbang;
	uint8_t tx;
	uint8_t rx;
	uint8_t txrx;
	uint8_t tack;
	uint8_t rack;
};

#ifdef SWIGPYTHON
typedef struct swig_string_data
{
        int size;
        char *data;
} swig_string_data;

swig_string_data Read(struct mpsse_context *mpsse, int size);
swig_string_data Transfer(struct mpsse_context *mpsse, char *data, int size);
#endif

#endif
