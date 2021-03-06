// Copyright (c) Athena Dev Teams - Licensed under GNU GPL
// For more information, see LICENCE in the main folder

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "nullpo.h"

static void
nullpo_info_core (const char *file, int line, const char *func, const char *fmt,
				  va_list ap)
{
	if (file == NULL)
		file = "??";

	func =
		func == NULL    ? "unknown" :
		func[0] == '\0' ? "unknown" :
		func;
	printf ("--- nullpo info --------------------------------------------\n");
	printf ("%s:%d: in func `%s'\n", file, line, func);

	if (fmt != NULL) {
		if (fmt[0] != '\0') {
			vprintf (fmt, ap);

			if (fmt[strlen (fmt) - 1] != '\n')
				printf ("\n");
		}
	}

	printf ("--- end nullpo info ----------------------------------------\n");
}

int
nullpo_chk_f (const char *file, int line, const char *func, const void *target,
			  const char *fmt, ...)
{
	va_list ap;

	if (target != NULL)
		return 0;

	va_start (ap, fmt);
	nullpo_info_core (file, line, func, fmt, ap);
	va_end (ap);
	return 1;
}

int
nullpo_chk (const char *file, int line, const char *func, const void *target)
{
	if (target != NULL)
		return 0;

	nullpo_info_core (file, line, func, NULL, NULL);
	return 1;
}

void
nullpo_info_f (const char *file, int line, const char *func, const char *fmt,
			   ...)
{
	va_list ap;
	va_start (ap, fmt);
	nullpo_info_core (file, line, func, fmt, ap);
	va_end (ap);
}

void
nullpo_info (const char *file, int line, const char *func)
{
	nullpo_info_core (file, line, func, NULL, NULL);
}
