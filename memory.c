#include "shell.h"
#include "vars.h"
#include "main.h"
#include "lists.h"
#include "lists1.h"
#include "parser.h"
#include "realloc.h"
#include "shell_loop.h"
#include "string.h"
#include "string1.h"
#include "tokenizer.h"
#include "builtin.h"
#include "builtin1.h"
#include "environ.h"
#include "errors.h"
#include "errors1.h"
#include "exits.h"
#include "getLine.h"
#include "getenv.h"
#include "getinfo.h"
#include "history.h"
#include "_atoi.h"

/*
#include "reaf.h"
#include "shlf.h"
#include "strf.h"
#include "strf1.h"
#include "tof.h"
#include "vaf.h"
#include "buf.h"
#include "buf1.h"
#include "enf.h"
#include "erf.h"
#include "erf1.h"
#include "exf.h"
#include "glf.h"
#include "gvf.h"
#include "gif.h"
#include "hif.h"
#include "atf.h"
#include "mf.h"
#include "lif1.h"
#include "paf.h"
#include "lif.h"
*/

/**
 * bfree - free ptr
 * @ptr: ptr address
 * Return: 1 or 0
 */

int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
