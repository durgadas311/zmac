#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>
#include <stdarg.h>
#include <errno.h>
#include <ctype.h>
#include "ld80.h"

int warn_extchain, debug;
static char *ofilename, *symfilename;
int fatalerror;

void usage(void);

int main(int argc,char **argv)
{
	unsigned n;
	int c, type, align;
	int suppress_data = 0;
	int oformat = F_IHEX;
	FILE *ofile, *symfile=NULL;
	int symsize = 1024;
	int argc2 = 1;
	char **argv2;
	int abort = 0;
	int lib = 0;
	int symbol_table_required = 0, map_required = 0;
	char *common_name;

	init_section();

	/*
	 * argv is processed in two passes. This ensures that
	 * -o will be consumed before opening any input file.
	 * So ld80 will know what file is to delete in case
	 * of an error.
	 */
	argv2 = calloc_or_die(argc*2+1, sizeof(*argv2));
	argc2=1;

#define	REGULAR_OPTSTRING	"-VlP:D:C:U:O:o:hcs:mS:W:"
#ifdef	DEBUG
#define	OPTSTRING		REGULAR_OPTSTRING "d"
#else
#define	OPTSTRING		REGULAR_OPTSTRING
#endif

	while ((c = getopt (argc, argv, OPTSTRING)) != -1) switch (c) {
	case 1:		/* Input file */
		argv2[argc2++] = optarg;	/* defer processing */
		break;
	case 'P':	/* Program location */
		argv2[argc2++] = "-P";
		argv2[argc2++] = optarg;	/* defer processing */
		break;
	case 'D':	/* Data location */
		argv2[argc2++] = "-D";
		argv2[argc2++] = optarg;	/* defer processing */
		break;
	case 'C':	/* Common location */
		argv2[argc2++] = "-C";
		argv2[argc2++] = optarg;	/* defer processing */
		break;
	case 'l':	/* Library specification */
		argv2[argc2++] = "-l";		/* defer processing */
		break;

	case 'U':	/* "Uncommon" segment */
		if (isspace(*optarg)) *optarg = '\0';	/* blank common */
		{ char *s; for (s=optarg; *s; s++) *s = toupper(*s); }
		mark_uncommon(optarg);
		break;
	case 'S':	/* Set symbol table size */
		n = atoi(optarg);
		if (n<=0) {
			fprintf(stderr,"ld80: symbol table size is invalid\n");
			abort = 1;
			break;
		}
		if (symsize<n) symsize = n;
		break;
	case 'o':	/* Output file */
		ofilename = optarg;
		break;
	case 'O':	/* Output format */
		if (!strcmp(optarg,"ihex")) oformat = F_IHEX;
		else if (!strcmp(optarg,"bin")) oformat = F_BIN00;
		else if (strcmp(optarg,"binff")) oformat = F_BINFF;
		else {
			usage();
			abort = 1;
		}
		break;
	case 'c':	/* Suppress data segments */
		suppress_data++;
		break;
	case 'W':	/* Warnings */
		if (!strcmp(optarg,"extchain")) warn_extchain++;
		else {
			usage();
			abort = 1;
		}
		break;
	case 's':	/* Symbol table */
		symfilename = optarg;
		symbol_table_required++;
		break;
	case 'm':	/* Segment map */
		map_required++;
		break;
#ifdef	DEBUG
	case 'd':	/* Debug level */
		debug++;
		break;
#endif
	case 'V':	/* Version */
		fprintf(stderr,"ld80 v%s\n",VERSION);
		abort = 1;
		break;
	default:
	case 'h':	/* Help */
		usage();
		abort = 1;
		break;
	} /* switch(c) */

	if (symbol_table_required || map_required) {
		if (!symfilename || !strcmp(symfilename,"-")) {
			symfilename = NULL;
			symfile = stdout;
		}
		else {
			symfile = fopen(symfilename,"w");
			if (symfile == NULL) die(E_USAGE,
				"ld80: Cannot open symbol file %s: %s\n",
				symfilename, sys_errlist[errno]);
		}
	}
	if (abort) die(E_USAGE,"");

	/*
	 * Start processing object files.
	 */
	init_symbol(symsize);

	optind = 0;	/* make reinitialize getopt() */
	while ((c = getopt (argc2, argv2, "-lD:P:C:")) != -1) switch (c) {
	case 'l':	/* Library to search in */
		lib = 1;
		break;
	case 'C':	/* Common location */
		common_name = optarg;
		for (/*EMPTY*/; *optarg && *optarg!=','; optarg++)
			*optarg = toupper(*optarg);
		if (*optarg != ',') {
			usage();
			die(E_USAGE,"");
		}
		*optarg++ = '\0';
		if (isspace(*common_name))
			*common_name = '\0';	/* blank common */
		type = T_COMMON;
		/* FALL THROUGH */
	case 'D':	/* Data location */
		if (c == 'D') type = T_DATA;
		/* FALL THROUGH */
	case 'P':	/* Program location */
		if (c == 'P') type = T_CODE;
		if (*optarg == '%') {
			align = 1;
			optarg++;
		}
		else align = 0;
		n = strtoul(optarg, NULL, 16);
		if (0xffff<n)
			die(E_USAGE,"ld80: Address %x is out of range\n", n);
		set_base_address(type, common_name, n, align);
		break;
	case 1:		/* Input file */
		read_object_file(optarg, lib);
		lib = 0;
		break;
	}
	free(argv2);

#ifdef	DEBUG
#define IFDEBUG(x)	if (debug) x
#else
#define	IFDEBUG(x)
#endif
	IFDEBUG( printf("\nRelocating sections\n"); )
	relocate_sections();
	IFDEBUG( dump_sections(); )

	IFDEBUG( printf("\nSetting symbol values\n"); )
	set_symbols();
	IFDEBUG( dump_symbols(); )

	IFDEBUG( printf("\nSetting fixups\n"); )
	set_fixups();
	IFDEBUG( dump_sections(); )

	IFDEBUG( printf("\nResolving externals\n"); )
	resolve_externals();

	IFDEBUG( printf("\nProcessing nodes\n"); )
	process_nodes();
	IFDEBUG( dump_sections(); )

	IFDEBUG( printf("\nJoining sections\n"); )
	join_sections(suppress_data);
	IFDEBUG( dump_sections(); )

	if (map_required) print_map(symfile);
	if (symbol_table_required) print_symbol_table(symfile);

	if (ofilename) {
		if ((ofile=fopen(ofilename,"w")) == NULL) die(E_USAGE,
			"ld80: Cannot open output file %s: %s\n",
			ofilename, sys_errlist[errno]);
	}
	else die(E_USAGE, "ld80: No output file specified\n");

	do_out(ofile, oformat);
	fclose(ofile);

	clear_symbol();
	die(fatalerror ? E_INPUT : E_SUCCESS, "");
}

void *calloc_or_die(size_t nmemb, size_t size)
{
	void *retval = calloc(nmemb, size);
	if (retval==NULL) die(E_RESOURCE,"ld80: not enough memory\n");
	return retval;
}

void usage(void)
{
	fprintf(stderr,
"Usage:\n"
"ld80 [-O oformat] [-cmV] [-W warns] -o ofile [-s symfile] [-U name] ...\n"
"     [-S symsize] input ...\n"
"where oformat: ihex | bin | binff\n"
"        warns: extchain\n"
"        input: [-l] [-P address] [-D address] [-C name,address] ... file\n"
	);
}

void die(int status, const char *format, ...)
{
	va_list arg;

	fflush(stdout);
	va_start(arg, format);
	fprintf(stderr, format, arg);
	va_end(arg);

	if (status && ofilename) unlink(ofilename);
//	if (status && symfilename) unlink(symfilename);
	exit(status);
}
