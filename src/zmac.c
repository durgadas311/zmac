#define STRING 257
#define NOOPERAND 258
#define ARITHC 259
#define ADD 260
#define LOGICAL 261
#define AND 262
#define OR 263
#define XOR 264
#define ANDAND 265
#define OROR 266
#define BIT 267
#define CALL 268
#define INCDEC 269
#define DJNZ 270
#define EX 271
#define IM 272
#define PHASE 273
#define DEPHASE 274
#define TK_IN 275
#define JR 276
#define LD 277
#define TK_OUT 278
#define PUSHPOP 279
#define RET 280
#define SHIFT 281
#define RST 282
#define REGNAME 283
#define IXYLH 284
#define ACC 285
#define TK_C 286
#define RP 287
#define HL 288
#define INDEX 289
#define AF 290
#define AFp 291
#define SP 292
#define MISCREG 293
#define COND 294
#define SPCOND 295
#define NUMBER 296
#define UNDECLARED 297
#define END 298
#define ORG 299
#define ASSERT 300
#define TSTATE 301
#define T 302
#define TILO 303
#define TIHI 304
#define SETOCF 305
#define OCF 306
#define LOW 307
#define HIGH 308
#define DC 309
#define DEFB 310
#define DEFD 311
#define DEFS 312
#define DEFW 313
#define EQU 314
#define DEFL 315
#define LABEL 316
#define EQUATED 317
#define WASEQUATED 318
#define DEFLED 319
#define MULTDEF 320
#define SHL 321
#define SHR 322
#define LT 323
#define EQ 324
#define LE 325
#define GE 326
#define NE 327
#define NOT 328
#define MROP_ADD 329
#define MROP_SUB 330
#define MROP_MUL 331
#define MROP_DIV 332
#define MROP_MOD 333
#define MROP_AND 334
#define MROP_OR 335
#define MROP_XOR 336
#define MROP_NE 337
#define MROP_EQ 338
#define MROP_LT 339
#define MROP_GT 340
#define MROP_LE 341
#define MROP_GE 342
#define MROP_SHIFT 343
#define MROP_SHL 344
#define MROP_SHR 345
#define MROP_NOT 346
#define MROP_LOW 347
#define MROP_HIGH 348
#define IF_TK 349
#define IF_DEF_TK 350
#define ELSE_TK 351
#define ENDIF_TK 352
#define ARGPSEUDO 353
#define INCBIN 354
#define LIST 355
#define MINMAX 356
#define MACRO 357
#define MNAME 358
#define ARG 359
#define ENDM 360
#define ONECHAR 361
#define TWOCHAR 362
#define JRPROMOTE 363
#define JPERROR 364
#define PUBLIC 365
#define EXTRN 366
#define MRAS_MOD 367
#define SETSEG 368
#define INSTSET 369
#define LXI 370
#define DAD 371
#define STAX 372
#define STA 373
#define SHLD 374
#define LDAX 375
#define LHLD 376
#define LDA 377
#define MVI 378
#define MOV 379
#define INXDCX 380
#define INRDCR 381
#define PSW 382
#define JUMP8 383
#define JP 384
#define CALL8 385
#define ALUI8 386
#define SPECIAL 387
#define RAWTOKEN 388
#define LOCAL 389
#define LD_XY 390
#define ST_XY 391
#define MV_XY 392
#define ALU_XY 393
#define BIT_XY 394
#define SHIFT_XY 395
#define INP 396
#define OUTP 397
#define JR_COND 398
#define LDST16 399
#define ARITH16 400
#define REPT 401
#define IRPC 402
#define IRP 403
#define EXITM 404
#define NUL 405
#define MPARM 406
#define GT 407
#define UNARY 408
#ifdef YYSTYPE
#undef  YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#endif
#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
typedef union	{
	struct expr *exprptr;
	struct item *itemptr;
	int ival;
	char *cval;
	} YYSTYPE;
#endif /* !YYSTYPE_IS_DECLARED */
extern YYSTYPE yylval;
/* original parser id follows */
/* yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93" */
/* (use YYMAJOR/YYMINOR for ifdefs dependent on parser version) */

#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define YYPATCH 20140715

#define YYEMPTY        (-1)
#define yyclearin      (yychar = YYEMPTY)
#define yyerrok        (yyerrflag = 0)
#define YYRECOVERING() (yyerrflag != 0)
#define YYENOMEM       (-2)
#define YYEOF          0
#define YYPREFIX "yy"

#define YYPURE 0

#line 1 "zmac.y"

/* GWP - keep track of version via hand-maintained date stamp.*/
#define VERSION "5nov2016"

/*
 *  zmac -- macro cross-assembler for the Zilog Z80 microprocessor
 *
 *  Bruce Norskog	4/78
 *
 *  Last modification  1-18-87 by cdk
 *  This assembler is modeled after the Intel 8080 macro cross-assembler
 *  for the Intel 8080 by Ken Borgendale.  The major features are:
 *	1.  Full macro capabilities
 *	2.  Conditional assembly
 *	3.  A very flexible set of listing options and pseudo-ops
 *	4.  Symbol table output
 *	5.  Error report
 *	6.  Elimination of sequential searching
 *	7.  Commenting of source
 *	8.  Facilities for system definiton files
 *
 * Revision History:
 *
 * jrp	3-8-82	Converted to run on Vax, updated syntax to conform better
 *		to the Zilog standard.
 *
 * jrp	3-15-82	Added underscore as a character type in the lex table
 *		'numpart' (0x5F).
 *
 *		Changed maximum number of characters in a label to 15
 *		from 7. Note that 'putsymtab' uses this value inside
 *		of a quoted string, so we use 15.
 *
 * jrp	2-15-83	Fixed 'getlocal' to return better local labels. It used
 *		to crash after 6 invocations.
 *
 * jrp	6-7-83	Fixed bug in the ADD IX,... instruction.
 *
 * jrp	5-11-84	Added code to print unused labels out with the symbol table
 *		Also sped up the macro processor by using stdio.
 *
 * jrp 5-22-84	Added include files ala ormac
 *
 * jrp 8-27-84	Added PHASE/DEPHASE commands
 *
 * cdk 9-20-86	Converted to run on a Pyramid.  This meant changing yylval
 *		to be a %union, and then putting in the appropriate
 *		typecasts where ints are pointers are used interchangeably.
 *		The current version still probably won't run on machines where
 *		sizeof(int) != sizeof(char *).
 *		Also changed emit() to use varargs, and got rid of the
 *		old style = in front of yacc action code.
 *			-Colin Kelley  vu-vlsi!colin
 *
 * cdk 10-2-86	Added some more typecasts to keep lint a little happier.
 *		Removed several unused variables.  Changed most vars
 *		declared as char to int, since many of them were being
 *		compared with -1!  I still don't know what's going on with
 *		est[][] being malloc'd and free'd everywhere...it looks pretty
 *		fishy...
 *
 * cdk 1-18-87  Added MIO code to emulate 'mfile' using malloc()'d memory.
 *		This was needed to get the code to work when compiled under
 *		MSC 4.0 on a PC, and it's probably faster anyway.
 *
 * cdk 2-5-87	Added 'cmp' as a synonym for 'cp', 'jmp' as a synonym for
 *		'jp', and added tolerance of accumulator specification for arithmetic
 *		and logical instructions.  (For example, 'or a,12' is now accepted,
 *		same as 'or 12'.)
 *
 * gwp 12-29-08	Changes to allow compilation with modern C compiler and using bison
 *		as the .y to .c converter.  assert, tstate pseudo-ops.
 *		t(), tilo(), tihi() functions.  ==, <=, >=, !=, !, <, > operators.
 *		-c to turn cycle counts off in listing.  Usage, -h and version.
 *
 * gwp 9-26-10	Add ocf() and setocf to track and set op code fetch counts.
 *		Add sett as an alias for tstate
 *
 * gwp 12-30-11	Add undocumented instructions sl1, pfix, pfiy, in (c), out (c),0
 *		bit/set/res (ixy+d),reg and ld/inc/dec ixylh.
 *
 * gwp 2-8-12   Increase MAXIFS massively due to massive lowt macro
 *
 * gwp 2-11-12  Support 32 bit constants.  '%' alias for MOD.  Add defd, dword.
 *		lo(x) and hi(x) for easy low and high byte extraction.  Allow
 *		filenames longer than 15 characters.  All output to "zout" subdirectory
 *		of source file.
 *
 * gwp 2-15-12	Perform multiple passes while equates are changing.  Support
 *		.label for temporary label definitions and _label for file
 *		scoped labels.  Allow '.' within labels.  Assert listing bugfix.
 *
 * gwp 4-27-12	Implement $ prefixed hex constants and double-quoted strings.
 *
 * gwp 6-30-12	Minor changes to allow compilation with gcc.
 *
 * gwp 9-05-12	incbin added.
 *
 * gwp 11-24-12	Fix macro expansion bug when symbol larger than MAXSYMBOLSIZE
 *		due to file name prepending when symbol starts with '_'.
 *
 * gwp 12-04-12	Optional JR promotion and JP demotion errors.  Output a warning
 *		if no execute address given.  Output ".bds" file to enable easy
 *		simple source level debugging.
 *
 * gwp 4-14-13	Parens in expressions, else, .pseudo, full set of C operators
 *		with conventional precedence and various aliases and code
 *		changes to make source similar to zmac 1.3 on internet.
 *
 * gwp 5-5-13	.cmd,.cas,.lcas,.bin output.  dc (both MACRO-80 and EDAS types).
 *		lo, hi renamed to low, high and make unary operators.  Allow
 *		label::, placeholder public, extern declarations.  Bug fixes
 *		in defs, t, ocf, tihi, tilo in phase mode.  Initial support
 *		for -I include directories. 0x hex constants. --mras flag for
 *		limited MRAS compatibility (allows $ in labels, $? to start
 *		labels).
 *
 * gwp 4-6-13	--rel for .rel (Microsoft linker) output and extern, public,
 *		aseg, cseg, dseg in support (big emit + expression revamp).
 *		-I follows C preprocessor convention, output relative to
 *		current directory.  8080 mnemonics, .z80, .8080, -z, -8.
 *		Change .bin to .cim.  Warn on labels not in first column.
 *
 * gwp 8-11-13	Allow $ to start identifiers and do '$' dropping when macro
 *              parsed so we no longer need to drop '$' in identifiers. 
 *              Even $FCB allowed, with warning.  Add --zmac for backwards
 *		compatibility with zmac.  ` now used for joining in macros.
 *		Most reserved words can be used as labels or variables.
 *		Free-form title, name, comment, subttl parsing.  Allow #arg
 *		for macro arguments (in --mras mode).  Support <CR> delimited
 *		files.  Add .ams output.  Integrate documentation (--doc).
 *
 * gwp 3-12-14	Emit jr even if out of range.  z80.lib support.
 *		Warning and bug fixes from Mark Galanger.
 *		Macros can override built-ins and are no longer listed
 *		in symbol table.  A, B, C, D, E, H, L, M, PSW, SP are
 *		pre-defined values which can be used in data statements
 *		(db, dw, dd).  Reserved words can be equated but are only
 *		accessbile in data.  SET can be used in place of DEFL
 *		(MAC and MACRO-80 agree on this).  '=' can be used in place
 *		of EQU. 'maclib file' includes 'file.lib'.  Bug fix in "dw 0,$".
 *		Removed error flagging in expressions which could cause parse
 *		to fail from that point onwards.
 *		expression(ix) equivalent to (ix + expression).
 *		Macro expanded lines didn't go through the line analyzer.
 *		Empty macro arguments (e.g., mac 1,,2)
 *		Implemented rept, irp, irpc, exitm.  Add more detail on phase
 *		errors. '' is an empty string in db/ascii/etc, 0 otherwise.
 *		Almost any name can be used as a macro parameter name.
 *		Allow 'if' in first column.
 *		Fix .rel mode bug in dc, incbin.
 *		Emit .bds output for dc, incbin.
 *		Allow assembly to wrap past end of memory.
 *		"pragma bds" for raw output to .bds file.  Also output equates
 *		to .bds file.
 *		Macro bug fix from Sergey Erokhin.
 *
 * gwp 9-5-16	Allow ' on identifiers for manual prime register tracking.
 *		Improve MRAS support with *LIST, *INCLUDE and Pk=n parameters.
 *
 * gwp 20-9-16	Big MRAS compatibility fixes.  Can do MRAS operator precedence,
 *		proper .operator. tokenization and agressive macro parameter
 *		substituion.  Change Pk=n to -Pk=n.  Add ++, += and variants
 *		for more compact variable adjustment than defl.  First crack
 *		at .tap output for ZX Spectrum support.
 */

#define MIO		/* use emulation routines from mio.c */

#pragma GCC diagnostic error "-Wreturn-type"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>
#include <sys/stat.h>

#ifdef WIN32
#include <windows.h>	/* just for colouring the output*/
#include <direct.h>		/* _mkdir*/
#endif

#include "zi80dis.h"

#ifdef vax11c
#define unlink(filename) delete(filename)
#endif

#ifdef MIO
#include "mio.h"

FILE *mfopen();
#else
#define mfopen(filename,mode) fopen(filename,mode)
#define mfclose(filename,mode) fclose(filename,mode) 
#define mfputc(c,f) putc(c,f)
#define mfgetc(f) getc(f)
#define mfseek(f,loc,origin) fseek(f,loc,origin)
#define mfread(ptr,size,nitems,f) fread(ptr,size,nitems,f)
#define mfwrite(ptr,size,nitems,f) fread(ptr,size,nitems,f)
#endif /* MIO */

/*
 * DEBUG turns on pass reporting.
 * DBUG enables -d to allow yacc/bison yydebug increment (but must be passed
 *	on the command line)
 * Macro debug and Token debug enables.
#define	DEBUG
#define	M_DEBUG	
#define	T_DEBUG
 */

#ifdef DBUG
#define YYDEBUG 1
#endif

#define ITEMTABLESIZE	100000
#define TEMPBUFSIZE	(1000+MAXSYMBOLSIZE)
#define LINEBUFFERSIZE	1000
#define EMITBUFFERSIZE	200
#define MAXSYMBOLSIZE	40
#define IFSTACKSIZE	20
/* GWP - I use lots of if's with my lowt macro*/
#define MAXIFS		65536
#define TITLELEN	50
#define BINPERLINE	16
#define	PARMMAX		25
#define MAXEXP		25
#define SYMMAJIC	07203
#define	NEST_IN		32
#define MAXPASS		32
#define MAXINCPATH	32

int iflist();
int yylex();
int phaseaddr(int addr);
int nextchar();
int getcol();
int skipline(int ac);
int tokenofitem(int deftoken, int keyexclude, int keyinclude);
int getm();
int counterr();
int countwarn();
int convert(char *buf, char *bufend, int *overflow);

void yyerror(char *err)
{}		/* we will do our own error printing */

struct argparse {
	char *arg;	/* output buffer for argument*/
	int argsize;	/* size of output buffer*/
	int (*getch)(struct argparse *); /* get next character*/
	int *peek;	/* pointer single item pushback buffer*/
	int macarg;	/* working on macro arguments*/

	char *user_ptr;	/* state for getch*/
	int user_int;	/* state for getch*/
	int user_peek;	/* state for getch*/

	int didarg;	/* internal parsing state*/
	int numarg;	/* internal parsing state*/
};

int getarg(struct argparse *ap);

struct	item	{
	char	*i_string;
	int	i_value;
	int	i_token;
	int	i_uses;
	int	i_scope;
	int	i_chain;
	int	i_pass;
};

void itemcpy(struct item *dst, struct item *src);
struct item *keyword(char *name);

#define SCOPE_NONE	(0)
#define SCOPE_PROGRAM	(1)
#define SCOPE_DATA	(2)
#define SCOPE_PUBLIC	(4)
#define SCOPE_EXTERNAL	(8)
#define SCOPE_NORELOC	(16)
#define SCOPE_BUILTIN	(32)	/* abuse */

#define SCOPE_SEGMASK	(3)
#define SCOPE_SEG(s)	((s) & SCOPE_SEGMASK)

struct expr {
	int e_value;
	int e_scope;
	int e_token;
	struct item *e_item;
	struct expr *e_left;
	struct expr *e_right;
};

#define EXPR_SEG(e)	SCOPE_SEG(e->e_scope)

FILE	*fout,
	*fbuf,
	*fbds,
	*fcmd,
	*fcas,
	*flcas,
	*fcim,
	*fams,
	*frel,
	*ftap,
	*fin[NEST_IN],
	*now_file ;

int	pass2;	/*set when pass one completed*/
int	outpass; 	/* set when we decide to stop doing passes * /*/
int	passfail;	/* set when an error means passes should not continue*/
int	passretry;	/* set when an inconsistency will require another pass*/
int	dollarsign ;	/* location counter */
int	olddollar ;	/* kept to put out binary */
int	oldothdollar;	/* output address of next .cmd/.cas/.lcas block*/
int	emit_addr;	/* were code and data are being placed in memory*/
int	tstates;	/* cumulative T-states*/
int	ocf;		/* cumulative op code fetches*/
int	llseq;		/* local label sequence number*/
int	mras;		/* MRAS semi-compatibility mode*/
int	trueval = 1;	/* Value returned for boolean true*/
int	zcompat;	/* Original zmac compatibility mode*/
char	modstr[8];	/* Replacement string for '?' in labels when MRAS compatible*/
int	relopt;		/* Only output .rel files and length of external symbols*/
char	progname[8];	/* Program name for .rel output*/
int	note_depend;	/* Print names of files included*/
int	firstcol;
int	logcol;
int	coloncnt;
int	full_exprs;	/* expression parsing mode allowing almost any identifier*/
struct item *label, pristine_label; /* */
int	list_dollarsign;/* flag used to change list output for some operations*/
int	list_addr;	/* address to display for operation if !list_dollarsign*/

/* Include file search path*/
char	*incpath[MAXINCPATH];
int	incpath_cnt;

/* program counter save for PHASE/DEPHASE */
int	phdollar, phbegin, phaseflag ;

char	*src_name[NEST_IN] ;
int	linein[NEST_IN] ;
int linepeek[NEST_IN];
int	now_in ;


/* These first 5 errors are singled out in lsterr1() for reasons I don't*/
/* quite understand.*/
#define bflag	0	/* balance error */
#define eflag	1	/* expression error */
#define fflag	2	/* syntax error */
#define iflag	3	/* bad digits */
#define mflag	4	/* multiply defined */

#define pflag	5	/* phase error */
#define uflag	6	/* undeclared used */
#define vflag	7	/* value out of range */
#define oflag	8	/* phase/dephase error */
#define aflag	9	/* assert failed */
#define jflag	10	/* JP could be JR */
#define rflag	11	/* expression not relocatable */
#define gflag	12	/* incorrect register */
#define zflag	13	/* Z-80 instruction */

#define FIRSTWARN	warn_hex
#define	warn_hex	14
#define warn_notimpl	15
#define warn_general	16

#define FLAGS	17	/* number of errors and warnings */

char	err[FLAGS];
int	keeperr[FLAGS];
char	errlet[FLAGS]="BEFIMPUVOAJRGZHNW";
char	*errname[FLAGS]={
	"Balance",
	"Expression",
	"Syntax",
	"Digit",
	"Mult. def.",
	"Phase",
	"Undeclared",
	"Value",
	"Phase/Dephase",
	"Assertion failure",
	"Use JR",
	"Not relocatable",
	"Register usage",
	"Z-80 instruction in 8080 mode",
	"$hex constant interpreted as symbol",
	"Not implemented",
	"General"
};
char	errdetail[FLAGS][1024];
char	detail[1024];


unsigned char inpbuf[LINEBUFFERSIZE];
unsigned char inpbuf_insert[LINEBUFFERSIZE];
unsigned char *inpptr;

char	linebuf[LINEBUFFERSIZE];
char	*lineptr;
char	*linemax = linebuf+LINEBUFFERSIZE;

char	outbin[BINPERLINE];
char	*outbinp = outbin;
char	*outbinm = outbin+BINPERLINE;

char	outoth[256];
int	outoth_cnt = 0;

unsigned char	emitbuf[EMITBUFFERSIZE];
unsigned char	*emitptr;

char	ifstack[IFSTACKSIZE];
char	*ifptr;
char	*ifstmax = ifstack+IFSTACKSIZE-1;


char	hexadec[] = "0123456789ABCDEF" ;


int	nitems;
int	linecnt;
int	nbytes;
int	invented;
int	npass;
int	njrpromo;


char	tempbuf[TEMPBUFSIZE];
char	*tempmax = tempbuf+TEMPBUFSIZE-1;

char	arg_flag;
struct argparse arg_state;
void	arg_start();
void	arg_reset();
int	str_getch(struct argparse *ap);

int	mras_undecl_ok;
int	mras_param[10];

char	inmlex;
char	mlex_list_on;
int	parm_number;
int	exp_number;
char	symlong[] = "Symbol/number too long";
int	raw;

int	disp;

int	param_parse;
#define PARAMTABSIZE (PARMMAX * 2)
struct item paramtab[PARAMTABSIZE];

#define FLOC	PARMMAX
#define TEMPNUM	PARMMAX+1
#define REPNUM	PARMMAX+2
#define MSTART	PARMMAX+3
#define MSTR	PARMMAX+4
#define MARGP	PARMMAX+5
#define MIF	PARMMAX+6

#define PAREXT	7

union exprec {
	char *param;
	int value;
	struct argparse *ap;
};
union exprec	*est;
union exprec	*est2;
union exprec	*expstack[MAXEXP];
int	expptr;

int	floc;
int	mfptr;
FILE	*mfile;

char	*writesyms;


char	*title;
char	titlespace[TITLELEN];
char	*timp;
char	*sourcef;
/* changed to cope with filenames longer than 14 chars -rjm 1998-12-15 */
char	src[1024];
char	bin[1024];
char	mtmp[1024];
char	listf[1024];
char	bds[1024];
char	oth[1024];

char	bopt = 1,
	copt = 1,	/* cycle counts in listings by default */
	edef = 1,
	eopt = 1,
	fdef = 0,
	fopt = 0,
	gdef = 1,
	gopt = 1,
	iopt = 0 ,	/* list include files */
	jopt = 0,
	JPopt = 0,
	lstoff = 0,
	lston = 0,	/* flag to force listing on */
	lopt = 0,
	mdef = 0,
	mopt = 0,
	nopt = 1 ,	/* line numbers on as default */
	oopt = 0,
	popt = 1,	/* form feed as default page eject */
	sopt = 0,	/* turn on symbol table listing */
	topt = 1,	/* terse, only error count to terminal */
	printer_output = 0, /* GWP - printer style output*/
	z80,
	saveopt;

char default_jopt, default_JPopt, default_z80 = 1;

char	xeq_flag = 0;
int	xeq;

time_t	now;
int	line;
int	page = 1;

struct stab {
	char	t_name[MAXSYMBOLSIZE+1];
	int	t_value;
	int	t_token;
};

/* GWP - support for cycle count tracking (and opens door for efficient .cmd, etc. output)*/

unsigned char memory[1 << 16];
char memflag[1 << 16];
enum {
	MEM_DATA = 1,
	MEM_INST = 2,
	MEM_T_SET = 4
};
int tstatesum[1 << 16];
int ocfsum[1 << 16];

/* GWP - expression handling extensions for .rel output.*/
void advance_segment(int step);
void expr_reloc_check(struct expr *ex);
void expr_number_check(struct expr *ex);
void expr_scope_same(struct expr *ex1, struct expr *ex2);
void expr_word_check(struct expr *ex);
int is_number(struct expr *ex);
int is_external(struct expr *ex);
struct expr *expr_num(int value);
struct expr *expr_alloc(void);
struct expr *expr_var(struct item *var);
struct expr *expr_mk(struct expr *left, int token, struct expr *right);
struct expr *expr_op(struct expr *left, int token, struct expr *right, int value);
struct expr *expr_op_sc(struct expr *left, int token, struct expr *right, int value);
void expr_free(struct expr *ex);
int can_extend_link(struct expr *ex);
void extend_link(struct expr *ex);
void putrelop(int op);
#define RELOP_BYTE	(1)
#define RELOP_WORD	(2)
#define RELOP_HIGH	(3)
#define RELOP_LOW	(4)
#define RELOP_NOT	(5)
#define RELOP_NEG	(6)
#define RELOP_SUB	(7)
#define RELOP_ADD	(8)
#define RELOP_MUL	(9)
#define RELOP_DIV	(10)
#define RELOP_MOD	(11)
struct item *item_lookup(char *name, struct item *table, int table_size);
struct item *item_substr_lookup(char *name, int token, struct item *table, int table_size);
struct item *locate(char *name);
/* Data descriptions for emit()*/
#define E_CODE		(0)
#define E_DATA		(1)
#define E_CODE8		(2)
#define E_CODE16	(3)
int segment;
#define SEGCHAR(s) " '\"!"[s]
#define SEG_ABS		(0)
#define SEG_CODE	(1)
#define SEG_DATA	(2)
int seg_pos[4]; /* may eventually support SEG_COMMON*/
int seg_size[4];
int rel_main;
int segchange;
void putout(int value);
int outrec;
int outlen;
unsigned char outbuf[1024 * 1024];


/*
 *  push back character
 */
#define NOPEEK (EOF - 1)
int	peekc;
int	nextline_peek;

/* function prototypes */
void error(char *as);
void usage(char *msg, char *param);
void help();
void list_out(int optarg, char *line_str, char type);
void erreport();
void errorprt(int errnum);
void errwarn(int errnum, char *message);
void mlex(char *look);
void popsi();
void suffix(char *str, char *suff);
char *basename(char *filename);
char *getsuffix(char *str);
void outpath(char *out, char *src, char *suff);
void casname(char *out, char *src, int maxlen);
void putm(int c);
void insymtab(char *name);
void outsymtab(char *name);
void compactsymtab();
void putsymtab();
void clear();
void setmem(int addr, int value, int type);
void setvars();
void flushbin();
void flushoth();
void lineout();
void puthex(int byte, FILE *buf);
void putcas(int byte);
void putrelbits(int count, int bits);
void putrel(int byte);
void putrelname(char *str);
void putrelextaddr(int extaddr);
void putrelcmd(int cmd);
void putrelsegref(int scope, int addr);
void flushrel(void);
void lsterr1();
void lsterr2(int lst);
void copyname(char *st1, char *st2);
void next_source(char *sp);
void incbin(char *filename);
void dc(int count, int value);
char *getmraslocal();
void write_tap(int len, int org, unsigned char *data);

#define RELCMD_PUBLIC	(0)
#define RELCMD_COMMON	(1)
#define RELCMD_PROGNAME	(2)
#define RELCMD_LIBLOOK	(3)
#define RELCMD_EXTLINK	(4)
#define RELCMD_COMSIZE	(5)
#define RELCMD_EXTCHAIN	(6)
#define RELCMD_PUBVALUE	(7)
#define RELCMD_EXTMINUS	(8)
#define RELCMD_EXTPLUS	(9)
#define RELCMD_DATASIZE	(10)
#define RELCMD_SETLOC	(11)
#define RELCMD_CODESIZE	(13)
#define RELCMD_ENDMOD	(14)
#define RELCMD_ENDPROG	(15)

/*
 *  add a character to the output line buffer
 */
void addtoline(int ac)
{
	/* check for EOF from stdio */
	if (ac == -1)
		ac = 0 ;
	if (lineptr >= linemax)
		error("line buffer overflow");
	*lineptr++ = ac;
}

int get_tstates(unsigned char *inst, int *low, int *high, int *fetch)
{
	int len;

	if (z80)
		len = zi_tstates(inst, low, high, fetch, 0, 0);
	else
		len = zi_tstates(inst, 0, 0, fetch, low, high);

	return len;
}

/*
 *  put values in buffer for outputing
 */

void emit(int bytes, int desc, struct expr *data, ...)
{
	int type, i, args, dsize;
	va_list ap;

	if (relopt && segchange) {
		segchange = 0;
		putrelcmd(RELCMD_SETLOC);
		putrelsegref(segment, seg_pos[segment]);
	}

	/* External references only supported in .rel output.*/
	if (!relopt && data && (data->e_scope & SCOPE_EXTERNAL)) {
		sprintf(detail, "External references only allowed in .rel output\n");
		errwarn(uflag, detail);
	}

	va_start(ap, data);

	type = desc == E_DATA ? MEM_DATA : MEM_INST;

	/* Check emit is not adding instructions to the buffer.*/
	if (desc != E_DATA && emitptr != emitbuf)
		fprintf(stderr, "internal inconsistency in t-state counting\n");

	dsize = 0;
	args = bytes;
	if (desc == E_DATA) {
		args = 0;
		dsize = bytes;
	}
	else if (desc == E_CODE16)
		dsize = 2;
	else if (desc == E_CODE8)
		dsize = 1;

	for (i = 0; i < args; i++)
	{
		if (emitptr >= &emitbuf[EMITBUFFERSIZE])
			error("emit buffer overflow");
		else {
			int addr = (emit_addr + (emitptr - emitbuf)) & 0xffff;
			*emitptr = va_arg(ap, int);
			if (segment == SEG_CODE) 
				setmem(addr, *emitptr, type);
			putrel(*emitptr);
			putout(*emitptr);
			emitptr++;
		}
	}

	va_end(ap);

	for (i = 0; i < dsize; i++) {
		int addr = (emit_addr + (emitptr - emitbuf)) & 0xffff;
		*emitptr = data->e_value >> (i * 8);
		if (segment == SEG_CODE)
			setmem(addr, *emitptr, type);
		putout(*emitptr);
		emitptr++;
	}

	if (desc != E_DATA)
	{
		int eaddr = emit_addr, low, fetch, addr_after;

		/* emitbuf is OK since this only happens with single emits*/

		if (!z80) {
			/* Check for invalid 8080 instructions.*/
			int op = emitbuf[0] & 0xff;
			if (op == 0x08 || op == 0x10 || op == 0x18 ||
			    op == 0x20 || op == 0x28 || op == 0x30 ||
			    op == 0x38 || op == 0xCB || op == 0xD9 ||
			    op == 0xDD || op == 0xED || op == 0xFD)
			{
				err[zflag]++;
			}
		}

		get_tstates(emitbuf, &low, 0, &fetch);

		/* Sanity check*/
		if (low <= 0)
		{
			fprintf(stderr, "undefined instruction on %02x %02x (assembler or diassembler broken)\n",
				emitbuf[0], emitbuf[1]);
		}

		/* Special case to catch promotion of djnz to DEC B JP NZ*/
		/* Even update the tstatesum[] counter though that seems to*/
		/* me to be above and beyond.*/
		if (emitbuf[0] == 5 && args == 2) {
			tstatesum[eaddr] = tstates;
			ocfsum[eaddr] = ocf;
			memflag[eaddr] |= MEM_T_SET;
			eaddr++;
			tstates += low;
			ocf += fetch;
			low = 10;
			/* still 1 fetch*/
		}

		/* Double setting of both sides of tstatesum[] seems like too*/
		/* much, but must be done in the isolated instruction case:*/
		/* org x ; inc a ; org y*/

		tstatesum[eaddr] = tstates;
		ocfsum[eaddr] = ocf;
		memflag[eaddr] |= MEM_T_SET;

		/* Well, OK, should we default to high or low???*/
		/* Guess it should be whatever makes sense for you*/
		/* to get here which, generally, is the low.*/

		/* low it is.*/

		tstates += low;
		ocf += fetch;

		addr_after = (emit_addr + (emitptr - emitbuf)) & 0xffff;

		tstatesum[addr_after] = tstates;
		ocfsum[addr_after] = ocf;
		memflag[addr_after] |= MEM_T_SET;
	}

	if (relopt && outpass && dsize > 0) {
		if (dsize == 1) {
			if (is_number(data))
				putrel(data->e_value);
			else if (can_extend_link(data)) {
				extend_link(data);
				putrelop(RELOP_BYTE);
				putrel(0);
			}
			else {
				err[rflag]++;

				putrel(0);
			}
		}
		else if (dsize == 2) {
			int handled = 0;
			if (data->e_scope & SCOPE_EXTERNAL) {
				struct item *var = 0;
				int offset = 0;
				/* Simple external reference.*/
				if (is_external(data))
					var = data->e_item;
				else if (is_external(data->e_left) &&
					data->e_token == '+' &&
					is_number(data->e_right))
				{
					var = data->e_left->e_item;
					offset = data->e_right->e_value;
				}
				else if (is_number(data->e_left) &&
					data->e_token == '+' &&
					is_external(data->e_right))
				{
					offset = data->e_left->e_value;
					var = data->e_right->e_item;
				}
				else if (is_external(data->e_left) &&
					data->e_token == '-' &&
					is_number(data->e_right))
				{
					var = data->e_left->e_item;
					offset = data->e_right->e_value;
				}

				if (var && offset) {
					putrelcmd(data->e_token == '-' ?
						RELCMD_EXTMINUS : RELCMD_EXTPLUS);
					/* Theoretically we could put a*/
					/* program or data relative value here...*/
					putrelsegref(SEG_ABS, offset);
				}

				if (var) {
					if (var->i_chain == 0) {
						putrel(0);
						putrel(0);
					}
					else {
						putrelbits(1, 1);
						putrelextaddr(var->i_chain);
					}
					var->i_chain = (segment << 16) |
						((dollarsign + args) & 0xffff);
					handled = 1;
				}
			}
			else if ((data->e_scope & ~SCOPE_PUBLIC) == 0) {
				/* nice constant value*/
				putrel(data->e_value);
				putrel(data->e_value >> 8);
				handled = 1;
			}
			else if (!(data->e_scope & SCOPE_NORELOC)) {
				/* relocatable value*/
				putrelbits(1, 1);
				putrelbits(2, data->e_scope);
				putrelbits(8, data->e_value);
				putrelbits(8, data->e_value >> 8);
				handled = 1;
			}

			if (!handled) {
				if (can_extend_link(data)) {
					extend_link(data);
					putrelop(RELOP_WORD);
					putrel(0);
					putrel(0);
				}
				else {
					err[rflag]++;
					putrel(data->e_value);
					putrel(data->e_value >> 8);
				}
			}
		}
		else if (dsize == 4) {
			/* Only numbers are allowed.*/
			if (data->e_scope != 0) {
				err[vflag]++;
				if (data->e_scope & SCOPE_NORELOC)
					err[rflag]++;
			}
			for (i = 0; i < dsize; i++)
				putrel(data->e_value >> (i * 8));
		}
		else
			error("internal dsize error");
	}
}

#define ET_NOARG_DISP	(0)
#define ET_NOARG	(1)
#define ET_BYTE		(2)
#define ET_WORD		(5)

void emit1(int opcode, int regvalh, struct expr *data, int type)
{
	if (type == ET_BYTE && (data->e_value < -128 || data->e_value > 255))
		err[vflag]++;

	if (regvalh & 0x10000) {
		switch (type) {
		case ET_NOARG_DISP:
			emit(2, E_CODE, 0, regvalh >> 8, opcode);
			break;
		case ET_BYTE:
			emit(2, E_CODE8, data, regvalh >> 8, opcode);
			break;
		}
	}
	else if (regvalh & 0x8000) {
		switch (type) {
		case ET_NOARG_DISP:
			if (opcode & 0x8000)
				emit(4, E_CODE, 0, regvalh >> 8, opcode >> 8, disp, opcode);
			else
				emit(3, E_CODE, 0, regvalh >> 8, opcode, disp);
			break;
		case ET_NOARG:
			emit(2, E_CODE, 0, regvalh >> 8, opcode);
			break;
		case ET_BYTE:
			emit(3, E_CODE8, data, regvalh >> 8, opcode, disp);
			break;
		case ET_WORD:
			emit(2, E_CODE16, data, regvalh >> 8, opcode);
		}
	} else
		switch(type) {
		case ET_NOARG_DISP:
		case ET_NOARG:
			if (opcode & 0100000)
				emit(2, E_CODE, 0, opcode >> 8, opcode);
			else
				emit(1, E_CODE, 0, opcode);
			break;
		case ET_BYTE:
			emit(1, E_CODE8, data, opcode);
			break;
		case ET_WORD:
			if (opcode & 0100000)
				emit(2, E_CODE16, data, opcode >> 8, opcode);
			else
				emit(1, E_CODE16, data, opcode);
		}
}




void emitdad(int rp1,int rp2)
{
	if (rp1 & 0x8000)
		emit(2, E_CODE, 0, rp1 >> 8, rp2 + 9);
	else
		emit(1, E_CODE, 0, rp2 + 9);
}


void emitjr(int opcode, struct expr *dest)
{
	int disp = dest->e_value - dollarsign - 2;

	if (dest->e_scope & SCOPE_NORELOC)
		err[rflag]++;

	/* Can't relative jump to other segments or an external*/
	/* However, without .rel output we default to the code segment*/
	/* for various reasons thus we let "jr 0" (and such) be acceptable*/
	/* in those cases.*/
	if (((relopt && (dest->e_scope & SCOPE_SEGMASK) != segment) ||
		(dest->e_scope & SCOPE_EXTERNAL) ||
		disp > 127 || disp < -128) && z80)
	{
		if (jopt) {
			njrpromo++;
			switch (opcode) {
			case 0x10: /* DJNZ*/
				emit(2, E_CODE16, dest, 0x05, 0xC2); /* DEC B, JP NZ*/
				break;
			case 0x18: /* JR*/
				emit(1, E_CODE16, dest, 0xC3); /* JP*/
				break;
			case 0x20: /* JR NZ*/
				emit(1, E_CODE16, dest, 0xC2); /* JP NZ*/
				break;
			case 0x28: /* JR Z*/
				emit(1, E_CODE16, dest, 0xCA); /* JP Z*/
				break;
			case 0x30: /* JR NC*/
				emit(1, E_CODE16, dest, 0xD2); /* JP NC*/
				break;
			case 0x38: /* JR C*/
				emit(1, E_CODE16, dest, 0xDA); /* JP C*/
				break;
			default:
				err[vflag]++;	/* shouldn't happen!*/
				expr_free(dest);
				break;
			}
		}
		else {
			emit(2, E_CODE, 0, opcode, -2);  /* branch to itself*/
			err[vflag]++;
			expr_free(dest);
		}
	}
	else {
		emit(2, E_CODE, 0, opcode, disp);
		expr_free(dest);
	}
}

void checkjp(int op, struct expr *dest)
{
	op &= 0x030;
	/* Only applies to Z-80 output and if JP optimization checking is on.*/
	/* JR only has z, nz, nc, c*/
	/* A jump to the current segment might have been optimizable*/
	if (z80 && JPopt && (op == 0 || op == 010 || op == 020 || op == 030) &&
		(dest->e_scope & (SCOPE_SEGMASK | SCOPE_EXTERNAL)) == segment)
	{
		int disp = dest->e_value - dollarsign - 2;
		if (disp >= -128 && disp <= 127)
			err[jflag]++;
	}
}

/*
 *  put out a byte of binary 
 */
void putbin(int v)
{
	if(!outpass || !bopt) return;
	*outbinp++ = v;
	if (outbinp >= outbinm) flushbin();

	outoth[outoth_cnt++] = v;
	if (outoth_cnt == 256) flushoth();
}



/*
 *  output one line of binary in INTEL standard form
 */
void flushbin()
{
	char *p;
	int check=outbinp-outbin;

	if (!outpass || !bopt)
		return;
	nbytes += check;
	if (check) {
		putc(':', fbuf);
		puthex(check, fbuf);
		puthex(olddollar>>8, fbuf);
		puthex(olddollar, fbuf);
		puthex(0, fbuf);
		check += (olddollar >> 8) + olddollar;
		olddollar += (outbinp-outbin);
		for (p=outbin; p<outbinp; p++) {
			puthex(*p, fbuf);
			check += *p;
		}
		puthex(256-check, fbuf);
		putc('\n', fbuf);
		outbinp = outbin;
	}
}



/*
 *  put out one byte of hex
 */
void puthex(int byte, FILE *buf)
{
	putc(hexadec[(byte >> 4) & 017], buf);
	putc(hexadec[byte & 017], buf);
}

/* Case-independent string comparisons.*/

int ci_strcompare(char *s1, char *s2, int len)
{
	int c1, c2;
	do {
		if (len == 0)
			return 0;

		c1 = *s1++;
		if (c1 >= 'A' && c1 <= 'Z') c1 += 'a' - 'A';
		c2 = *s2++;
		if (c2 >= 'A' && c2 <= 'Z') c2 += 'a' - 'A';
		if (c1 != c2)
			return c1 - c2;

		if (len > 0)
			if (--len == 0)
				return 0;

	} while (c1 && c2);

	return 0;
}

int ci_strcmp(char *s1, char *s2)
{
	return ci_strcompare(s1, s2, -1);
}

void flushoth()
{
	int i, checksum;

	if (!outpass || !bopt || outoth_cnt == 0)
		return;

	fprintf(fcmd, "%c%c%c%c", 1, outoth_cnt + 2, oldothdollar, oldothdollar >> 8);
	fwrite(outoth, outoth_cnt, 1, fcmd);

	putcas(0x3c);
	putcas(outoth_cnt);
	putcas(oldothdollar);
	putcas(oldothdollar >> 8);
	checksum = oldothdollar + (oldothdollar >> 8);
	for (i = 0; i < outoth_cnt; i++) {
		putcas(outoth[i]);
		checksum += outoth[i];
	}
	putcas(checksum);

	oldothdollar += outoth_cnt;
	outoth_cnt = 0;
}

int casbit, casbitcnt = 0;

void putcas(int byte)
{
	fputc(byte, flcas);

	/* Buffer 0 stop bit and the 8 data bits.*/
	casbit = (casbit << 9) | (byte & 0xff);
	casbitcnt += 9;
	while (casbitcnt >= 8) {
		casbitcnt -= 8;
		fputc(casbit >> casbitcnt, fcas);
	}
}

void casname(char *out, char *src, int maxlen)
{
	char *base = basename(src);
	int i;

	out[0] = 'N';
	for (i = 1; i < maxlen; i++)
		out[i] = ' ';

	for (i = 0; *base && i < maxlen; base++) {
		if (ci_strcmp(base, ".z") == 0 || ci_strcmp(base, ".asm") == 0)
			break;

		if (*base >= 'a' && *base <= 'z') {
			*out++ = *base - ('a' - 'A');
			i++;
		}
		else if (*base >= 'A' && *base <= 'Z') {
			*out++ = *base;
			i++;
		}
	}
}

int relbit, relbitcnt = 0;

void putrelbits(int count, int bits)
{
	if (!outpass || !relopt)
		return;

	relbit <<= count;
	relbit |= bits & ((1 << count) - 1);
	relbitcnt += count;

	while (relbitcnt >= 8) {
		relbitcnt -= 8;
		fputc(relbit >> relbitcnt, frel);
	}
}

void putrel(int byte)
{
	/* Add 0 bit indicating byte to load at next counter*/
	putrelbits(1, 0);
	/* Add byte to load*/
	putrelbits(8, byte);
}

void putrelname(char *str)
{
	int len = strlen(str);
	int maxlen = mras ? 7 : relopt;

	/* .rel file format can do strings 7 long but for compatibility*/
	/* we restrict them to 6.  I believe this is important because*/
	/* extended link functions require a character when they wish to*/
	/* operate on an external symbol.*/
	if (len > maxlen)
		len = maxlen;
	putrelbits(3, len);
	while (len-- > 0) {
		int ch = *str++;
		if (ch >= 'a' && ch <= 'z')
			ch -= 'a' - 'A';
		putrelbits(8, ch);
	}
}

void putrelsegref(int scope, int addr)
{
	putrelbits(2, scope);
	putrelbits(8, addr);
	putrelbits(8, addr >> 8);
}

void putrelextaddr(int extaddr)
{
	putrelsegref(extaddr >> 16, extaddr);
}


void putrelcmd(int relcmd)
{
	putrelbits(1, 1);
	putrelbits(2, 0);
	putrelbits(4, relcmd);
}

void flushrel(void)
{
	if (relbitcnt > 0)
		putrelbits(8 - relbitcnt, 0);

	if (relopt)
		fflush(frel);
}

/*
 *  put out a line of output -- also put out binary
 */
void list(int optarg)
{

	if (!expptr)
		linecnt++;
	addtoline('\0');

	list_out(optarg, linebuf, ' ');

	lineptr = linebuf;
}

void list_out(int optarg, char *line_str, char type)
{
	unsigned char *	p;
	int	i;
	int  lst;
	char seg = ' ';

	if (outpass) {
		lst = iflist();
		if (lst) {
			lineout();
			if (nopt)
				fprintf(fout, "%4d:", linein[now_in]);

			if (copt)
			{
			    if (emitptr > emitbuf && (memflag[emit_addr] & MEM_INST))
			    {
			        int low, high, fetch;
			        get_tstates(memory + emit_addr, &low, &high, &fetch);

				/* Special case to catch promotion of djnz to DEC B JP NZ*/
				if (memory[emit_addr] == 5 && emitptr - emitbuf == 4) {
					low += 10;
					high += 10;
				}

			    	fprintf(fout, nopt ? "%5d" : "%4d", tstatesum[emit_addr]);

				fprintf(fout, "+%d", low);
				if (low != high)
				    fprintf(fout, "+%d", high - low);
			    }
			    else
			    {
			        fprintf(fout, nopt ? "%5s-" : "%4s-", "");
			    }
			}

			if (nopt || copt)
				fprintf(fout, "\t");

			puthex(optarg >> 8, fout);
			puthex(optarg, fout);
			if (relopt)
				seg = SEGCHAR(segment);
			fputc(seg, fout);
			fputc(type, fout);
			for (p = emitbuf; (p < emitptr) && (p - emitbuf < 4); p++) {
				puthex(*p, fout);
			}
			for (i = 4 - (p-emitbuf); i > 0; i--)
				fputs("  ", fout);

			putc('\t', fout);
			fputs(line_str, fout);
		}

		if (bopt) {
			if (emitptr > emitbuf) {
				fprintf(fbds, "%04x %04x d ", dollarsign, emit_addr);
				for (p = emitbuf; p < emitptr; p++)
					fprintf(fbds, "%02x", *p & 0xff);
				fprintf(fbds, "\n");
			}
			fprintf(fbds, "%04x %04x s %s", dollarsign, emit_addr, line_str);

			for (p = emitbuf; p < emitptr; p++)
				putbin(*p);
		}


		p = emitbuf+4;
		while (lst && gopt && p < emitptr) {
			lineout();
			if (nopt) putc('\t', fout);
			fputs("      ", fout);
			for (i = 0; (i < 4) && (p < emitptr);i++) {
				puthex(*p, fout);
				p++;
			}
			putc('\n', fout);
		}

		lsterr2(lst);
	} else
		lsterr1();

	dollarsign += emitptr - emitbuf;
	emit_addr += emitptr - emitbuf;
	dollarsign &= 0xffff;
	emit_addr &= 0xffff;
	emitptr = emitbuf;
}



/*
 *  keep track of line numbers and put out headers as necessary
 */
void lineout()
{
	if (!printer_output)
		return;

	if (line == 60) {
		if (popt)
			putc('\014', fout);	/* send the form feed */
		else
			fputs("\n\n\n\n\n", fout);
		line = 0;
	}
	if (line == 0) {
		fprintf(fout, "\n\n%s %s\t%s\t Page %d\n\n\n",
			&timp[4], &timp[20], title, page++);
		line = 4;
	}
	line++;
}


/*
 *  cause a page eject
 */
void eject()
{
	if (printer_output)
		return;

	if (outpass && iflist()) {
		if (popt) {
			putc('\014', fout);	/* send the form feed */
		} else {
			while (line < 65) {
				line++;
				putc('\n', fout);
			}
		}
	}
	line = 0;
}


/*
 *  space n lines on the list file
 */
void space(int n)
{
	int	i ;
	if (outpass && iflist())
		for (i = 0; i<n; i++) {
			lineout();
			putc('\n', fout);
		}
}

/*
 *  Error handling - pass 1
 */
void lsterr1()
{
	int i;
	for (i = 0; i <= mflag; i++)
		if (err[i]) {
			if (topt)
				errorprt(i);
			passfail = 1;
			err[i] = 0;
		}
}


/*
 *  Error handling - pass 2.
 */
void lsterr2(int lst)
{
	int i;
	for (i=0; i<FLAGS; i++)
		if (err[i]) {
			if (i < FIRSTWARN)
				passfail = 1;
			if (lst) {
				char *desc = errname[i];
				char *type = i < FIRSTWARN ? " error" : " warning";
				if (errdetail[i][0]) {
					desc = errdetail[i];
					type = "";
				}
				lineout();
				fprintf(fout, "%c %s%s\n",
					errlet[i], desc, type);
			}
			err[i] = 0;
			keeperr[i]++;
			if (i > mflag && topt)
				errorprt(i);
		}

	fflush(fout);	/*to avoid putc(har) mix bug*/
}

/*
 *  print diagnostic to error terminal
 */
void errorprt(int errnum)
{
	char *desc = errname[errnum];
	char *type = errnum < FIRSTWARN ? " error" : " warning";
	if (errdetail[errnum][0]) {
		desc = errdetail[errnum];
		type = "";
	}
	fprintf(stderr, "%s(%d) : %s%s",
		src_name[now_in], linein[now_in], desc, type);

	errdetail[errnum][0] = '\0';

	fprintf(stderr, "\n");
	fprintf(stderr, "%s\n", linebuf);
	fflush(stderr) ;
}

void errwarn(int errnum, char *message)
{
	if (errnum == uflag && mras_undecl_ok)
		return;

	err[errnum]++;
	strcpy(errdetail[errnum], message);
}


/*
 *  list without address -- for comments and if skipped lines
 */
void list1()
{
	int lst;

	addtoline('\0');
	lineptr = linebuf;
	if (!expptr) linecnt++;
	if (outpass) {
		if ((lst = iflist())) {
			lineout();
			if (nopt)
				fprintf(fout, "%4d:\t", linein[now_in]);
			if (copt)
				fprintf(fout, "\t");
			fprintf(fout, "\t\t%s", linebuf);
			lsterr2(lst);
		}
		if (bopt)
			fprintf(fbds, "%04x %04x s %s", dollarsign, emit_addr, linebuf);
	}
	else
		lsterr1();
}


/*
 *  see if listing is desired
 */
int iflist()
{
	int i, j;

	if (inmlex)
		return mlex_list_on;

	if (lston)
		return(1) ;
	if (lopt)
		return(0);
	if (*ifptr && !fopt)
		return(0);
	if (!lstoff && !expptr)
		return(1);
	j = 0;
	for (i=0; i<FLAGS; i++)
		if (err[i])
			j++;
	if (expptr)
		return(mopt || j);
	if (eopt && j)
		return(1);
	return(0);
}

void do_equ(struct item *sym, struct expr *val, int call_list);
void do_defl(struct item *sym, struct expr *val, int call_list);

/* GWP - This avoids an apparent bug in bison as it tries to start out the*/
/* Not needed under gcc which defines __STDC__ so I guard it to prevent*/
/* warnings.*/
/* yyparse() function with yyparse() ; { }.*/
#ifndef __STDC__
#define __STDC__
#endif

#define PSTITL	(0)	/* title */
#define PSRSYM	(1)	/* rsym */
#define PSWSYM	(2)	/* wsym */
#define PSINC	(3)	/* include file */
#define PSMACLIB (4)	/* maclib (similar to include) */

#define SPTITL	(0)	/* title */
#define SPSBTL	(1)	/* sub title */
#define SPNAME	(2)	/* name */
#define SPCOM	(3)	/* comment */
#define SPPRAGMA (4)	/* pragma */

#line 1632 "zmac.y"
#ifdef YYSTYPE
#undef  YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#endif
#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
typedef union	{
	struct expr *exprptr;
	struct item *itemptr;
	int ival;
	char *cval;
	} YYSTYPE;
#endif /* !YYSTYPE_IS_DECLARED */
#line 1773 "zmac.y"

char  *cp;
int  i;

void do_equ(struct item *sym, struct expr *val, int call_list)
{
	expr_reloc_check(val);
	switch(sym->i_token) {
	case UNDECLARED: case WASEQUATED:
		if (sym->i_token == WASEQUATED &&
			(sym->i_value != val->e_value ||
			 ((sym->i_scope ^ val->e_scope) & SCOPE_SEGMASK)))
		{
			if (outpass) {
				if (sym->i_value != val->e_value)
					sprintf(detail, "%s error - %s went from $%04x to $%04x",
						errname[pflag], sym->i_string, sym->i_value, val->e_value);
				else
					sprintf(detail, "%s error - %s changed scope",
						errname[pflag], sym->i_string);
				errwarn(pflag, detail);
			}
			else
				passretry = 1;
		}

		sym->i_token = EQUATED;
		sym->i_pass = npass;
		sym->i_value = val->e_value;
		sym->i_scope |= val->e_scope;
		break;
	default:
		/* m80 allows multiple equates as long as the value*/
		/* does not change.  So does newer zmac.*/
		if (sym->i_value != val->e_value ||
			((sym->i_scope ^ val->e_scope) & SCOPE_SEGMASK))
		{
			err[mflag]++;
			sym->i_token = MULTDEF;
			sym->i_pass = npass;
		}
	}
	sym->i_scope &= ~SCOPE_BUILTIN;
	if (call_list)
		list(val->e_value);
	expr_free(val);
}

void do_defl(struct item *sym, struct expr *val, int call_list)
{
	expr_reloc_check(val);
	switch(sym->i_token) {
	case UNDECLARED: case DEFLED:
		sym->i_token = DEFLED;
		sym->i_pass = npass;
		sym->i_value = val->e_value;
		sym->i_scope = (sym->i_scope & SCOPE_SEGMASK) | val->e_scope;
		break;
	default:
		err[mflag]++;
		sym->i_token = MULTDEF;
		sym->i_pass = npass;
		break;
	}
	if (call_list)
		list(val->e_value);
	expr_free(val);
}

void do_end(struct expr *entry)
{
	if (entry) {
		expr_reloc_check(entry);
		xeq_flag++;
		xeq = entry->e_value & 0xffff;
		rel_main = ((entry->e_scope & SCOPE_SEGMASK) << 16) | xeq;
		expr_free(entry);
	}

/* TODO - no reason no to treat END as a simple mras or not.*/
/* At least, give this a try and see how it goes.*/
/*	if (mras) {*/
		while (expptr)
			popsi();

		peekc = NOPEEK;
		nextline_peek = EOF;
/*	}*/
/*	else*/
/*		peekc = 0;*/

}

#line 1759 "y.tab.c"

/* compatibility with bison */
#ifdef YYPARSE_PARAM
/* compatibility with FreeBSD */
# ifdef YYPARSE_PARAM_TYPE
#  define YYPARSE_DECL() yyparse(YYPARSE_PARAM_TYPE YYPARSE_PARAM)
# else
#  define YYPARSE_DECL() yyparse(void *YYPARSE_PARAM)
# endif
#else
# define YYPARSE_DECL() yyparse(void)
#endif

/* Parameters sent to lex. */
#ifdef YYLEX_PARAM
# define YYLEX_DECL() yylex(void *YYLEX_PARAM)
# define YYLEX yylex(YYLEX_PARAM)
#else
# define YYLEX_DECL() yylex(void)
# define YYLEX yylex()
#endif

/* Parameters sent to yyerror. */
#ifndef YYERROR_DECL
#define YYERROR_DECL() yyerror(const char *s)
#endif
#ifndef YYERROR_CALL
#define YYERROR_CALL(msg) yyerror(msg)
#endif

extern int YYPARSE_DECL();

#define STRING 257
#define NOOPERAND 258
#define ARITHC 259
#define ADD 260
#define LOGICAL 261
#define AND 262
#define OR 263
#define XOR 264
#define ANDAND 265
#define OROR 266
#define BIT 267
#define CALL 268
#define INCDEC 269
#define DJNZ 270
#define EX 271
#define IM 272
#define PHASE 273
#define DEPHASE 274
#define TK_IN 275
#define JR 276
#define LD 277
#define TK_OUT 278
#define PUSHPOP 279
#define RET 280
#define SHIFT 281
#define RST 282
#define REGNAME 283
#define IXYLH 284
#define ACC 285
#define TK_C 286
#define RP 287
#define HL 288
#define INDEX 289
#define AF 290
#define AFp 291
#define SP 292
#define MISCREG 293
#define COND 294
#define SPCOND 295
#define NUMBER 296
#define UNDECLARED 297
#define END 298
#define ORG 299
#define ASSERT 300
#define TSTATE 301
#define T 302
#define TILO 303
#define TIHI 304
#define SETOCF 305
#define OCF 306
#define LOW 307
#define HIGH 308
#define DC 309
#define DEFB 310
#define DEFD 311
#define DEFS 312
#define DEFW 313
#define EQU 314
#define DEFL 315
#define LABEL 316
#define EQUATED 317
#define WASEQUATED 318
#define DEFLED 319
#define MULTDEF 320
#define SHL 321
#define SHR 322
#define LT 323
#define EQ 324
#define LE 325
#define GE 326
#define NE 327
#define NOT 328
#define MROP_ADD 329
#define MROP_SUB 330
#define MROP_MUL 331
#define MROP_DIV 332
#define MROP_MOD 333
#define MROP_AND 334
#define MROP_OR 335
#define MROP_XOR 336
#define MROP_NE 337
#define MROP_EQ 338
#define MROP_LT 339
#define MROP_GT 340
#define MROP_LE 341
#define MROP_GE 342
#define MROP_SHIFT 343
#define MROP_SHL 344
#define MROP_SHR 345
#define MROP_NOT 346
#define MROP_LOW 347
#define MROP_HIGH 348
#define IF_TK 349
#define IF_DEF_TK 350
#define ELSE_TK 351
#define ENDIF_TK 352
#define ARGPSEUDO 353
#define INCBIN 354
#define LIST 355
#define MINMAX 356
#define MACRO 357
#define MNAME 358
#define ARG 359
#define ENDM 360
#define ONECHAR 361
#define TWOCHAR 362
#define JRPROMOTE 363
#define JPERROR 364
#define PUBLIC 365
#define EXTRN 366
#define MRAS_MOD 367
#define SETSEG 368
#define INSTSET 369
#define LXI 370
#define DAD 371
#define STAX 372
#define STA 373
#define SHLD 374
#define LDAX 375
#define LHLD 376
#define LDA 377
#define MVI 378
#define MOV 379
#define INXDCX 380
#define INRDCR 381
#define PSW 382
#define JUMP8 383
#define JP 384
#define CALL8 385
#define ALUI8 386
#define SPECIAL 387
#define RAWTOKEN 388
#define LOCAL 389
#define LD_XY 390
#define ST_XY 391
#define MV_XY 392
#define ALU_XY 393
#define BIT_XY 394
#define SHIFT_XY 395
#define INP 396
#define OUTP 397
#define JR_COND 398
#define LDST16 399
#define ARITH16 400
#define REPT 401
#define IRPC 402
#define IRP 403
#define EXITM 404
#define NUL 405
#define MPARM 406
#define GT 407
#define UNARY 408
#define YYERRCODE 256
typedef short YYINT;
static const YYINT yylhs[] = {                           -1,
    0,    0,   28,   30,   28,   28,   28,   28,   28,   28,
   28,   28,   28,   28,   28,   28,   28,   28,   28,   28,
   28,   28,   28,   28,   28,   28,   28,   33,   28,   28,
   28,   28,   28,   28,   28,   28,   28,   28,   39,   40,
   28,   43,   28,   44,   28,   46,   48,   28,   49,   50,
   28,   28,   28,   20,   20,   20,    1,    1,   36,   36,
   51,   37,   37,   52,   27,   27,   27,   27,   27,   27,
   27,   27,   27,   27,   27,   27,   27,   27,   27,   27,
   27,   27,   27,   27,   27,   27,   27,   29,   29,   29,
   29,   29,   29,   29,   29,   29,   29,   29,   29,   29,
   29,   29,   29,   29,   29,   29,   29,   29,   29,   29,
   29,   29,   29,   29,   29,   29,   29,   29,   29,   29,
   29,   29,   29,   29,   29,   29,   29,   29,   29,   29,
   29,   29,   29,   29,   29,   29,   29,   29,   29,   29,
   29,   29,   29,   29,   29,   29,   29,   29,   29,   29,
   29,   29,   29,   29,   29,   29,   29,   29,   29,   29,
   29,   29,   29,   29,   29,   29,   29,   29,   29,   29,
   29,   29,   29,   29,   29,   29,   29,   29,   29,   29,
   29,   29,   29,   29,   29,   29,   29,   29,   29,   29,
   29,   29,   29,   29,   29,   29,   29,   29,   55,   29,
   57,   29,   59,   29,   29,   38,   38,   38,   61,   45,
   21,   21,   60,   26,   62,   64,   62,   63,   63,   63,
   65,   42,   42,   42,   47,   66,   47,    3,    3,    4,
    4,    6,   23,   23,   24,    7,    7,    7,    8,    8,
    9,    9,    9,   53,    5,    5,   22,   22,   10,   10,
   10,   25,   25,   11,   11,   12,   12,   13,   13,   14,
   14,   15,   15,   54,   54,   67,   67,   67,   56,   56,
   68,   58,   58,   69,   19,   19,   18,   18,   17,   16,
   16,   16,   16,   16,   16,   16,   16,   16,   70,   16,
   16,   16,   16,   16,   16,   16,   16,   16,   16,   16,
   16,   16,   16,   16,   16,   16,   16,   16,   16,   16,
   16,   16,   16,   16,   16,   16,   16,   16,   16,   16,
   16,   16,   16,   16,   16,   16,   16,   16,   16,   16,
   16,   16,   16,   16,   16,   16,   16,   16,   16,   16,
   16,   16,   16,   16,   16,   16,   16,   16,    2,    2,
    2,    2,    2,    2,   41,   31,   32,   34,   35,
};
static const YYINT yylen[] = {                            2,
    0,    2,    2,    0,    4,    5,    5,    4,    5,    4,
    4,    6,    3,    5,    2,    2,    3,    4,    4,    6,
    4,    4,    4,    6,    5,    4,    6,    0,    3,    2,
    5,    3,    3,    3,    3,    2,    2,    2,    0,    0,
    7,    0,    6,    0,    7,    0,    0,   11,    0,    0,
   11,    3,    1,    0,    1,    2,    0,    2,    1,    3,
    1,    1,    3,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    2,    1,
    2,    2,    2,    2,    2,    2,    4,    2,    4,    2,
    2,    2,    2,    4,    4,    4,    4,    2,    4,    2,
    2,    4,    2,    2,    2,    2,    2,    2,    4,    4,
    4,    4,    2,    2,    4,    2,    2,    4,    4,    4,
    2,    2,    2,    2,    2,    2,    2,    2,    4,    4,
    6,    4,    2,    4,    4,    2,    2,    4,    2,    2,
    1,    2,    4,    4,    4,    4,    4,    4,    4,    6,
    2,    4,    2,    6,    2,    4,    2,    4,    4,    4,
    4,    4,    2,    4,    2,    4,    2,    4,    4,    6,
    4,    2,    6,    2,    6,    4,    4,    2,    6,    2,
    6,    2,    2,    1,    2,    2,    2,    2,    0,    3,
    0,    3,    0,    3,    1,    0,    1,    3,    0,    2,
    0,    1,    2,    1,    0,    0,    5,    0,    1,    3,
    1,    0,    1,    3,    1,    0,    3,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    3,    1,
    4,    3,    4,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    3,    1,    1,    1,    1,    3,
    1,    1,    3,    1,    1,    1,    1,    1,    3,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    0,    3,
    3,    3,    3,    3,    3,    3,    3,    3,    3,    3,
    3,    3,    3,    3,    3,    3,    3,    3,    3,    3,
    3,    3,    3,    3,    3,    3,    3,    3,    3,    3,
    3,    3,    3,    3,    3,    3,    3,    3,    3,    3,
    3,    5,    3,    2,    2,    2,    2,    2,    2,    2,
    2,    2,    2,    2,    2,    2,    2,    2,    1,    1,
    1,    1,    1,    1,    0,    0,    0,    0,    0,
};
static const YYINT yydefred[] = {                         1,
    0,   53,    0,  350,  352,  353,  354,  351,    0,  356,
    0,    0,  356,    0,    0,    0,    0,    0,    0,    0,
    0,   28,    0,    0,    2,   39,  281,  287,    0,    0,
    0,    0,    0,    0,  280,  283,  284,  285,  288,    0,
    0,    0,    0,    0,  282,  289,    0,    0,    0,    0,
    0,  286,    0,  278,  277,    0,    0,   15,   16,    0,
   30,    0,    0,    0,  349,   61,    0,   59,   64,    0,
   62,   36,   37,   38,    0,    0,    0,    0,  356,  355,
    0,  209,  209,    0,    3,    0,   73,   74,    0,   75,
   76,   77,   78,   79,   80,   81,   82,   83,   84,   87,
   85,   86,    0,    0,   71,   72,   70,    0,    0,   67,
   68,   69,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  338,  340,  335,  346,  348,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,   13,  357,  357,    0,    0,
   32,   33,   34,    0,   35,    0,   29,   17,    0,    0,
    0,    0,    0,    0,    0,   42,    0,    0,    0,    0,
   52,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  194,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  199,  203,
  201,  205,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,   56,    0,    0,    0,    0,    0,  212,    0,
    0,  207,  290,  279,  333,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  315,  316,  318,
  317,  319,  320,  321,  322,  329,  326,  325,  327,  328,
  330,  331,  323,  324,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   26,
    0,   60,   63,   18,   23,   21,   22,    0,   19,    0,
  357,    0,    0,   46,  210,   49,    0,  236,  232,    0,
  238,    0,  235,    0,  111,  228,  229,  230,  231,  240,
    0,  113,    0,    0,  258,  259,  108,    0,    0,  110,
    0,  114,    0,  115,    0,  116,    0,    0,  117,    0,
    0,  118,    0,    0,  263,  261,  262,    0,  260,    0,
  237,  254,  255,  126,  134,  245,  246,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  249,  250,
  253,  252,  136,  251,  137,  152,  123,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  248,  247,    0,  131,
  165,    0,    0,  161,    0,    0,  233,    0,  234,    0,
  135,  127,    0,    0,    0,    0,    0,    0,    0,    0,
    0,   95,    0,  124,  184,  190,    0,    0,  132,  133,
    5,    8,    0,   10,   11,    0,    0,    0,  213,   40,
    0,    0,   14,   25,   31,    0,    0,    0,  225,  226,
    0,  223,   44,  355,  355,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  267,  266,    0,    0,  264,    0,    0,
  272,    0,    0,  269,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    6,    7,    9,  215,  208,    0,
   24,   20,   27,    0,   43,    0,  215,    0,    0,  112,
    0,  257,  256,  128,  239,  242,    0,    0,  109,    0,
  129,  130,  119,    0,  120,    0,  121,    0,  122,    0,
  139,    0,    0,  178,  179,    0,  186,    0,    0,  181,
    0,  169,    0,  168,    0,  153,    0,    0,  276,  176,
    0,    0,    0,  170,  166,  174,    0,  187,  125,    0,
    0,    0,  171,    0,  156,  144,    0,  154,  155,  158,
  140,   12,   41,    0,    0,  224,   45,  357,  357,  241,
  243,    0,    0,    0,    0,    0,    0,    0,  265,  273,
  270,  216,    0,    0,  141,  180,  185,  183,  164,  160,
  189,    0,    0,   47,   50,  221,    0,  219,  215,  215,
  217,    0,   48,   51,  220,
};
static const YYINT yydgoto[] = {                          1,
   23,   66,  345,  346,  385,  347,  348,  349,  350,  413,
  386,  554,  387,  378,  379,   54,   55,  388,  594,  113,
  270,  429,  438,  439,  415,  613,  114,   25,  260,   86,
   57,  179,   75,   62,  321,   67,   70,  271,  115,  538,
  196,  481,  332,  547,  198,  484,  482,  649,  485,  650,
   68,   71,  353,  517,  424,  523,  426,  520,  425,  272,
  199,  614,  647,  643,  648,  544,  518,  524,  521,  127,
};
static const YYINT yysindex[] = {                         0,
 1416,    0, -302,    0,    0,    0,    0,    0, 7223,    0,
   50,   66,    0,   88, 7223, 7223,   26,   26,  106,  107,
  114,    0,   -2, 6703,    0,    0,    0,    0, 7223, 7223,
 7223, 7223, 7223, 7223,    0,    0,    0,    0,    0, 7223,
 7223, 7223, 7223, 7223,    0,    0, 7223, 7223, 7223, 7223,
 7223,    0, 7223,    0,    0,  803, -192,    0,    0, -186,
    0, 7223, 1112, 1141,    0,    0,   20,    0,    0,   27,
    0,    0,    0,    0, -217, 3944, 6486, 7223,    0,    0,
 7223,    0,    0,  165,    0, 8848,    0,    0, 7223,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0, 7223,  126,    0,    0,    0,  190,  205,    0,
    0,    0,  -45,  174,  216,  543,  543,  543,  543,  543,
  543,    0,    0,    0,    0,    0, -132,  543,  543,  543,
  543, 7451, 7618, 7223, 7223, 7223, 7223, 7223, 7223, 7223,
 7223, 7223, 7223, 7223, 7223, 7223, 7223, 7223, 7223, 7223,
 7223, 7223, 7223, 7223, 7223, 7223, 7223, 7223, 7223, 7223,
 7223, 7223, 7223, 7223, 7223, 7223, 7223, 7223, 7223, 7223,
 7223, 7223, 7223, 7223, 7223,    0,    0,    0,  250, 8584,
    0,    0,    0,   26,    0,   26,    0,    0, 1229,  251,
  257,  260, 7706,  657,  -88,    0, 8584,  228,  216,  237,
    0, 7223, 5201, 5145, 5270, 5433, 5489, 5562, 7223, 5897,
 5063, 7223,  -13, 7223, 7223,    0, 5781, 6565, 4036, 7293,
 -180,    4, 5964, 7223, 7223, 7223, 7223, 7223,    0,    0,
    0,    0, -107, -107,   64, 7223, 7223,   64, 7223, 7223,
 -171, -171, -107, -171, 7223, 6011, 7223, 7223,   64,   64,
 7223, 7223, 7223, 7223,   64,   64, 7223, 7223,   92,  276,
 1258, 7794,    0,  278,  283, 7223, 7223, 7223,    0, -112,
   33,    0,    0,    0,    0,  464, 4871, 6070, 8760, 8672,
  887,  887,  433,  570,  433,  433,  570,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0, 7940, 4871, 6070,  464,  570,  433,
  433,  433,  916,  916,  543,  543,  543,  293,  294,    0,
  295,    0,    0,    0,    0,    0,    0, 7223,    0, 7223,
    0,  -34,  303,    0,    0,    0, 8584,    0,    0,  270,
    0,  272,    0, 6626,    0,    0,    0,    0,    0,    0,
 8584,    0,  280,  274,    0,    0,    0,  286, 8584,    0,
  289,    0, 8584,    0,  296,    0, 8584,  297,    0, 8584,
  304,    0, 8584, 8028,    0,    0,    0,  324,    0, 8584,
    0,    0,    0,    0,    0,    0,    0, 8584, 8584,  325,
  326,   84, 8584, 8584, 6810,  338,  339, 8584,  341, 8584,
  343, 6195,  344,  345,  346, 6914,  350, 8584,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  351, 8584, 8584,
 8584, 8584, 8584, 6682, 7223, 7223,    0,    0,  352,    0,
    0, 8584, 8584,    0, 8584, 8584,    0,  359,    0,  360,
    0,    0, 8584, 6774,  361, 8584, 8584, 8584,  362,  365,
 8116,    0, 8262,    0,    0,    0, 8584, 8584,    0,    0,
    0,    0, 7223,    0,    0, 1567, 1596, 1684,    0,    0,
  216, 7223,    0,    0,    0, 1713, 2022,  400,    0,    0,
   42,    0,    0,    0,    0, 5850,   40,  370, 6974,  123,
 5850,   92, 5850, 5850, 5850, 5850, 5964, 7223,  125,  127,
  373,  378,  383,  384, 7223,  141,  386, 5354, 6256,   86,
  387,  144,   64,    0,    0, 8584,  388,    0, 8584,  389,
    0, 8584,  390,    0, 7098, 7223, -171,  395, 7223, 7223,
 7223, 7223, 7223, 2051,    0,    0,    0,    0,    0, 8584,
    0,    0,    0, 7223,    0,  -34,    0,  -34,  -34,    0,
 8584,    0,    0,    0,    0,    0,  396,  399,    0, 8584,
    0,    0,    0, 8584,    0, 8584,    0, 8584,    0, 8584,
    0,  397, 8584,    0,    0,  398,    0,  145, 7161,    0,
 8584,    0,  401,    0, 6334,    0,    0,    0,    0,    0,
    0,    0, 8584,    0,    0,    0,  402,    0,    0, 6682,
 7223, 7223,    0, 8584,    0,    0, 8584,    0,    0,    0,
    0,    0,    0,   41, 8584,    0,    0,    0,    0,    0,
    0,   64, -187,  408,  409,  158,  410, 6390,    0,    0,
    0,    0,  442,  443,    0,    0,    0,    0,    0,    0,
    0, 8584,   51,    0,    0,    0,   48,    0,    0,    0,
    0,   51,    0,    0,    0,
};
static const YYINT yyrindex[] = {                         0,
 4625,    0, 4184,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0, 7329,    0,    0,    0,    0,    0,    0,
    0,    0, 8991, 4331,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  448,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0, 4478,    0,    0,    0,  403,  404,    0,
    0,    0, 4772,    0,   -8, 2516, 2583, 2612, 2624, 2653,
 2944,    0,    0,    0,    0,    0,    0, 2983, 3012, 3051,
 3080,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  449,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
 8350,    0,    0,    0,    0,    0,  450,    0,   61,    0,
    0,  451,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  456,  459,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0, 1268,  381,  268,  182,  224,
 3466, 3533, 3541, 3971, 3643, 3776, 4047,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0, 1151,  314, 1606, 5912, 3852,
 3881, 3889, 3353, 3454, 3118, 3158, 3428,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,   49,    0,    0,    0,    0,  461,    0,    0,  462,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
   78,    0,    0,  462,    0,    0,    0,    0,  164,    0,
  462,    0,  167,    0,  462,    0,  170,  462,    0,  172,
  462,    0,  173,  463,    0,    0,    0,    0,    0,  469,
    0,    0,    0,    0,    0,    0,    0,   81,  471,    0,
    0,    0,  473,  478,    0,    0,    0,  481,    0,  482,
    0,    0,    0,    0, 8438,    0, 2139,  483,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  484,  485,  487,
  488,  489,  492,    0,    0,    0,    0,    0,    0,    0,
    0,  493,  494,    0,  498,  500,    0,    0,    0,    0,
    0,    0,  502,    0,    0,  503,  504,  505,    0,    0,
    0,    0,    0,    0,    0,    0,  508,  509,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
   61,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,   53,  511,    0,   55,  512,
    0,   56,  513,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  222,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  180,    0,    0,    0,    0,    0,    0,    0,    0,  181,
    0,    0,    0,  214,    0,  215,    0,  233,    0,  236,
    0,  484,  517,    0,    0,    0,    0,    0,    0,    0,
  518,    0,    0,    0,    0,    0,  686,  774,    0,    0,
 2168, 2477,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  519,    0,    0,  520,    0,    0,    0,
    0,    0,    0,  285,   60,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  526,   69,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,
};
static const YYINT yygindex[] = {                         0,
    0,   28, -157, -218, -210,    0, -160,    0, -213,    0,
 -240,    0, -203,    7,  319, -339, -207,   -9,   13,    0,
    0,  -62, -216,  -16,    0, -530,    0,    0,    0,    0,
   32, -163,    0,    0,    0,    0,    0,    0,    0,    0,
 -193,    0,    0,    0,  457,    0, -189,    0,    0,    0,
  355,  356, -167,    0,    0,    0,    0,    0,    0, -188,
    0,    0,    0,    0, -102,    0,  -49,  -33,  -30,    0,
};
#define YYTABLESIZE 9391
static const YYINT yytable[] = {                         56,
  358,  206,  480,  333,  417,   63,   64,   85,  404,  418,
  335,  405,  407,  318,  319,  267,  617,  414,  459,  116,
  117,  118,  119,  120,  121,  440,  392,  442,   24,  183,
  122,  123,  124,  125,  126,  206,  185,  128,  129,  130,
  131,  132,  470,  133,   60,   69,  357,  362,  366,  369,
  372,  545,  180,  384,   26,  460,  397,  651,  222,   58,
  412,  403,  268,  184,  274,  271,  189,  193,  194,  227,
  186,  197,  428,  428,  431,   59,  471,  434,  218,  261,
  437,  437,  428,  437,  452,  546,  454,   98,  449,  450,
  244,  652,  222,  262,  455,  456,  268,   61,  274,  271,
  355,  356,  338,  227,  381,  341,  409,  355,  356,  410,
  195,  338,  218,  381,  341,   72,   73,  244,  653,  654,
  244,  244,  343,   74,  276,  277,  278,  279,  280,  281,
  282,  283,  284,  285,  286,  287,  288,  289,  290,  291,
  292,  293,  294,  295,  296,  297,  298,  299,  300,  301,
  302,  303,  304,  305,  306,  307,  308,  309,  310,  311,
  312,  313,  314,  315,  316,  317,  177,  478,  587,  591,
  187,  430,  178,   96,  201,  338,  100,  381,  341,  101,
  441,  102,  103,  263,  427,  591,  352,  360,  364,   99,
   97,  313,  337,  351,  359,  363,  367,  370,  373,  374,
  380,  411,  389,  244,  393,  394,  244,  398,  400,  244,
  408,  244,  244,   69,  419,  420,  421,  422,  423,  244,
  244,  313,  313,  104,  105,  313,  432,  433,  416,  435,
  436,  332,  264,  314,  268,  443,  446,  447,  448,  313,
  528,  451,  106,  453,  313,  107,  553,  457,  458,  265,
  269,  561,  445,  244,  244,  273,  466,  467,  468,  320,
  325,  332,  332,  314,  314,  332,  326,  314,  266,  327,
  331,  334,  244,  390,  313,  244,  391,  301,  571,  332,
  336,  314,  539,  572,  214,  461,  314,  464,  562,  375,
  548,  549,  465,  469,  214,   76,  580,  376,  377,  596,
  588,  592,  473,  474,  475,  590,   77,  301,  301,   78,
  605,  301,  483,  486,  332,  487,  314,  491,  476,  490,
  477,  557,   65,  300,  479,  301,  382,  552,  550,  492,
  301,  383,  493,  559,  132,  563,  565,  567,  569,  494,
  495,    4,    5,    6,    7,    8,  338,  496,  381,  341,
  586,   79,  599,  300,  300,   80,  616,  300,  618,  619,
  301,  301,  608,  609,  610,  611,  437,  498,  499,  500,
  595,  300,  382,  355,  356,  501,  300,  383,  382,  355,
  356,  503,  504,  383,  505,  132,  506,  508,  509,  510,
  299,  301,  132,  512,  513,  525,  132,  211,   81,   82,
   83,   84,  526,  527,  529,  530,  300,  300,  531,  543,
  555,  558,  574,  576,  516,  519,  522,  575,  577,  636,
  299,  299,  578,  579,  299,  582,  583,  597,  598,  632,
  624,  600,  601,  602,  132,  606,  620,  300,  299,  621,
  622,  623,  639,  299,  626,  628,  313,  313,  637,  638,
  640,  644,  645,  534,  633,  634,  646,  357,  359,  355,
   88,  635,  540,   65,   66,  151,  211,  641,   90,  175,
   89,  237,  138,  299,  173,  171,  551,  172,   92,  174,
  150,  560,  192,  564,  566,  568,  570,  193,  573,  314,
  182,  147,  188,  240,   93,  581,  195,  196,  197,  593,
  175,  198,  167,  175,  299,  173,  171,  173,  172,  163,
  174,  143,   91,  146,   94,  593,  604,  149,  177,  607,
  200,  204,  202,  168,  167,  169,  145,  148,  159,  142,
  301,  301,  301,  301,  615,  191,  399,  603,  322,  200,
  214,  323,  214,  214,  214,  214,  214,  214,  214,  655,
  629,  214,  214,  214,  214,  214,  214,  214,  214,  214,
  214,  214,  214,  214,  214,  214,  214,    0,  631,  132,
  630,    0,    0,    0,    0,  132,  300,  300,  300,  300,
    0,  214,  214,  214,  214,  214,    0,    0,    0,  214,
  516,  519,  522,  214,  214,  214,  214,  214,    0,    0,
  214,  214,  214,  214,  214,    0,  175,    0,    0,    0,
    0,  173,  171,    0,  172,    0,  174,    0,  642,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  168,
    0,  169,    0,  214,  214,  214,  214,  214,  214,  214,
    0,    0,  214,  299,  214,  299,  299,  214,  214,  214,
  214,  214,  214,  214,  214,  214,  214,  214,  214,  214,
  214,  214,  214,  214,  214,  214,  329,  214,  214,  214,
  214,  214,    0,    0,  214,  214,  214,  214,  214,  214,
  214,  214,  214,  214,  214,  214,  214,  214,  214,    0,
    0,    0,    0,  175,  166,  157,    0,    0,  173,  171,
  330,  172,    0,  174,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  168,  167,  169,  163,
    0,    0,  278,  278,    0,  278,    0,  278,  278,    0,
  278,    0,  278,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  278,  278,  278,  278,    0,
  165,    0,    0,  139,  140,    0,    0,    0,    0,    0,
    0,  146,  147,  148,  149,  150,  151,  152,  153,  154,
  155,  156,  157,  158,  159,  160,  161,  162,    0,  278,
  164,    0,    0,  162,  139,  140,  141,  142,  143,  144,
  145,    0,  146,  147,  148,  149,  150,  151,  152,  153,
  154,  155,  156,  157,  158,  159,  160,  161,  162,  278,
  277,  277,  176,  277,    0,  277,  277,    0,  277,    0,
  277,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  277,  277,  277,  277,    0,    0,  175,
  166,    0,    0,    0,  173,  171,    0,  172,    0,  174,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  168,  167,  169,  163,    0,  277,    0,    0,
  170,  146,  147,  148,  149,  150,  151,  152,  153,  154,
  155,  156,  157,  158,  159,  160,  161,  162,    0,    0,
  139,  140,  141,    0,  143,  144,  165,  277,  146,  147,
  148,  149,  150,  151,  152,  153,  154,  155,  156,  157,
  158,  159,  160,  161,  162,    0,    0,    0,  134,  135,
  136,  137,  138,  175,    0,    0,  164,    0,  173,  171,
    0,  172,    0,  174,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  278,  278,  278,
  278,  278,  175,    0,    0,    0,    0,  173,    0,    0,
    0,    0,  174,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  170,  139,  140,  141,
  142,  143,  144,  145,    0,  146,  147,  148,  149,  150,
  151,  152,  153,  154,  155,  156,  157,  158,  159,  160,
  161,  162,    0,    0,    0,    0,  278,  278,  278,  278,
  278,  278,  278,    0,  278,  278,  278,  278,  278,  278,
  278,  278,  278,  278,  278,  278,  278,  278,  278,  278,
  278,    0,    0,    0,    0,  277,  277,  277,  277,  277,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  170,  134,  135,  136,  137,  138,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  278,    0,  277,  277,  277,  277,  277,  277,
  277,    0,  277,  277,  277,  277,  277,  277,  277,  277,
  277,  277,  277,  277,  277,  277,  277,  277,  277,    0,
    0,  181,    0,  139,  140,  141,  142,  143,  144,  145,
    0,  146,  147,  148,  149,  150,  151,  152,  153,  154,
  155,  156,  157,  158,  159,  160,  161,  162,  175,  166,
  182,    0,    0,  173,  171,    0,  172,    0,  174,    0,
  298,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  168,  167,  169,  163,    0,    0,  175,  166,    0,
  277,    0,  173,  171,    0,  172,    0,  174,    0,    0,
  298,  298,    0,    0,  298,    0,    0,    0,    0,    0,
  168,  167,  169,  163,    0,  165,    0,    0,  298,  170,
    0,    0,    0,  298,    0,  146,  147,  148,  149,  150,
  151,  152,  153,  154,  155,  156,  157,  158,  159,  160,
  161,  162,    0,    0,  165,  164,    0,    0,  324,    0,
    0,    0,    0,  298,  146,  147,  148,  149,  150,  151,
  152,  153,  154,  155,  156,  157,  158,  159,  160,  161,
  162,    0,    0,    0,  164,  175,  166,  462,    0,    0,
  173,  171,    0,  172,  298,  174,    0,  297,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  168,  167,
  169,  163,    0,    0,  175,  166,    0,    0,    0,  173,
  171,    0,  172,    0,  174,  297,    0,  297,  297,    0,
    0,  297,    0,    0,    0,    0,    0,  168,  167,  169,
  163,    0,  165,    0,    0,  297,    0,    0,    0,    0,
  297,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  165,  164,    0,    0,    0,    0,    0,    0,    0,
  297,  297,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  134,  135,  136,  137,  138,    0,    0,
    0,  164,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  297,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  134,  135,  136,  137,  138,    0,    0,    0,
    0,    0,    0,  298,    0,  298,  298,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  139,  140,  141,  142,  143,  144,  145,    0,
  146,  147,  148,  149,  150,  151,  152,  153,  154,  155,
  156,  157,  158,  159,  160,  161,  162,    0,    0,    0,
    0,  139,  140,  141,  142,  143,  144,  145,    0,  146,
  147,  148,  149,  150,  151,  152,  153,  154,  155,  156,
  157,  158,  159,  160,  161,  162,    0,    0,    0,    0,
  134,  135,  136,  137,  138,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  170,  134,
  135,  136,  137,  138,    0,    0,    0,    0,    0,  297,
  297,  297,  297,  297,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  170,    0,  139,
  140,  141,  142,  143,  144,  145,    0,  146,  147,  148,
  149,  150,  151,  152,  153,  154,  155,  156,  157,  158,
  159,  160,  161,  162,    0,    0,  535,    0,  139,  140,
  141,  142,  143,  144,  145,    0,  146,  147,  148,  149,
  150,  151,  152,  153,  154,  155,  156,  157,  158,  159,
  160,  161,  162,  175,  166,  536,    0,    0,  173,  171,
    0,  172,    0,  174,    0,  296,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  168,  167,  169,  163,
    0,    0,  175,  166,    0,  170,    0,  173,  171,    0,
  172,    0,  174,  296,    0,  296,  296,    0,    0,  296,
    0,    0,    0,    0,    0,  168,  167,  169,  163,    0,
  165,    0,    0,  296,  170,    0,    0,    0,  296,    0,
    0,    2,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  165,
  164,    0,    0,  537,    0,    0,    0,    0,  296,  296,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    3,    0,    0,    0,    0,    0,    0,  164,
  175,  166,  541,    0,    0,  173,  171,    0,  172,  296,
  174,    4,    5,    6,    7,    8,    0,    0,    0,    0,
    0,    0,    0,  168,  167,  169,  163,    0,    0,  175,
  166,    0,    0,    0,  173,  171,    0,  172,    0,  174,
    0,    0,    0,    0,    9,   10,   11,   12,   13,    0,
   14,    0,  168,  167,  169,  163,    0,  165,   15,   16,
   17,   18,   19,   20,   21,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,   22,    0,    0,    0,  165,  164,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  134,  135,
  136,  137,  138,    0,    0,    0,  164,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  134,  135,  136,
  137,  138,    0,    0,    0,    0,    0,  296,  296,  296,
  296,  296,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  139,  140,  141,
  142,  143,  144,  145,    0,  146,  147,  148,  149,  150,
  151,  152,  153,  154,  155,  156,  157,  158,  159,  160,
  161,  162,    0,    0,    0,    0,  139,  140,  141,  142,
  143,  144,  145,    0,  146,  147,  148,  149,  150,  151,
  152,  153,  154,  155,  156,  157,  158,  159,  160,  161,
  162,    0,    0,    0,    0,  134,  135,  136,  137,  138,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  170,  134,  135,  136,  137,  138,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  170,    0,  139,  140,  141,  142,  143,  144,
  145,    0,  146,  147,  148,  149,  150,  151,  152,  153,
  154,  155,  156,  157,  158,  159,  160,  161,  162,    0,
    0,  542,    0,  139,  140,  141,  142,  143,  144,  145,
    0,  146,  147,  148,  149,  150,  151,  152,  153,  154,
  155,  156,  157,  158,  159,  160,  161,  162,  175,  166,
  612,    0,    0,  173,  171,    0,  172,    0,  174,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  168,  167,  169,  163,    0,    0,  175,  166,    0,
  170,    0,  173,  171,    0,  172,    0,  174,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  168,  167,  169,  163,    0,  165,    0,    0,    0,  170,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  165,  164,    0,    0,  277,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  164,  277,  277,  275,    0,    0,
  277,  277,    0,  277,    0,  277,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  277,  277,
  277,  277,    0,    0,  278,  278,    0,    0,    0,  278,
  278,    0,  278,    0,  278,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  278,  278,  278,
  278,    0,  277,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  278,  277,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  134,  135,  136,  137,  138,    0,    0,
    0,  278,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  134,  135,  136,  137,  138,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  139,  140,  141,  142,  143,  144,  145,    0,
  146,  147,  148,  149,  150,  151,  152,  153,  154,  155,
  156,  157,  158,  159,  160,  161,  162,    0,    0,    0,
    0,  139,  140,  141,  142,  143,  144,  145,    0,  146,
  147,  148,  149,  150,  151,  152,  153,  154,  155,  156,
  157,  158,  159,  160,  161,  162,    0,    0,    0,    0,
  277,  277,  277,  277,  277,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  170,  278,
  278,  278,  278,  278,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  170,    0,  277,
  277,  277,  277,  277,  277,  277,    0,  277,  277,  277,
  277,  277,  277,  277,  277,  277,  277,  277,  277,  277,
  277,  277,  277,  277,    0,    0,  172,    0,  278,  278,
  278,  278,  278,  278,  278,    0,  278,  278,  278,  278,
  278,  278,  278,  278,  278,  278,  278,  278,  278,  278,
  278,  278,  278,  277,  277,    0,    0,    0,  277,  277,
    0,  277,    0,  277,    0,  341,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  277,  277,  277,  277,
    0,    0,    0,    0,    0,  277,    0,    0,    0,    0,
    0,    0,  341,  341,    0,  341,  341,  341,  341,  341,
  341,    0,  341,    0,    0,    0,    0,    0,    0,    0,
  277,    0,    0,  341,  278,  341,  341,  341,  341,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  342,    0,    0,    0,    0,    0,    0,    0,
  277,    0,    0,    0,    0,    0,    0,    0,  341,  341,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  342,
  342,  343,  342,  342,  342,  342,  342,  342,    0,  342,
    0,    0,    0,  344,    0,    0,    0,    0,    0,  341,
  342,    0,  342,  342,  342,  342,    0,    0,  343,  343,
    0,  343,  343,  343,  343,  343,  343,    0,  343,    0,
  344,  344,  345,  344,  344,  344,  344,  344,  344,  343,
  344,  343,  343,  343,  343,  342,  342,    0,    0,    0,
    0,  344,    0,  344,  344,  344,  344,    0,    0,  345,
  345,    0,  345,  345,  345,  345,  345,  345,    0,  345,
    0,    0,    0,    0,  343,  343,  342,    0,    0,    0,
  345,    0,  345,  345,  345,  345,  344,  344,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  343,    0,    0,  277,  277,
  277,  277,  277,    0,    0,  345,  345,  344,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  345,  341,  341,  341,
  341,  341,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  277,  277,  277,
  277,  277,  277,  277,    0,  277,  277,  277,  277,  277,
  277,  277,  277,  277,  277,  277,  277,  277,  277,  277,
  277,  277,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  341,  341,  341,  341,
  341,  341,  341,    0,  342,  342,  342,  342,  342,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  343,  343,  343,  343,  343,    0,    0,
    0,    0,    0,  277,    0,  344,  344,  344,  344,  344,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  342,  342,  342,  342,  342,  342,  342,
    0,    0,    0,    0,  345,  345,  345,  345,  345,    0,
    0,    0,  341,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  343,  343,  343,  343,  343,  343,  343,    0,
    0,    0,    0,    0,  344,  344,  344,  344,  344,  344,
  344,    0,    0,  347,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  345,  345,  345,  345,  345,  345,  345,
  347,  347,    0,  347,  347,  347,  347,  347,  347,  342,
  347,    0,  337,    0,    0,    0,    0,    0,    0,    0,
    0,  347,    0,  347,  347,  347,  347,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  343,  337,
  337,  339,  337,  337,  337,  337,  337,  337,    0,  337,
  344,    0,    0,    0,    0,    0,  347,  347,    0,    0,
  337,    0,  337,  337,  337,  337,    0,    0,  339,  339,
    0,  339,  339,  339,  339,  339,  339,    0,  339,  345,
  336,    0,    0,    0,    0,    0,    0,  347,    0,  339,
    0,  339,  339,  339,  339,  337,  337,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  336,  336,  334,
  336,  336,  336,  336,  336,  336,    0,  336,    0,    0,
    0,    0,    0,    0,  339,  339,  337,    0,  336,    0,
  336,  336,  336,  336,    0,    0,  334,  334,    0,  334,
  334,  334,  334,  334,  334,    0,  334,  294,    0,    0,
    0,    0,    0,    0,    0,  339,    0,  334,    0,  334,
  334,  334,  334,  336,  336,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  294,  294,    0,  294,  294,  294,
  294,  294,  294,    0,  294,    0,    0,  293,    0,    0,
    0,    0,  334,  334,  336,  294,    0,  294,  294,  294,
  294,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  293,  293,    0,  293,  293,  293,
  293,  293,  293,  334,  293,  347,  347,  347,  347,  347,
  294,  294,    0,    0,    0,  293,    0,  293,  293,  293,
  293,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  294,    0,    0,  337,  337,  337,  337,  337,    0,
  293,  293,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  347,  347,  347,  347,  347,  347,
  347,    0,    0,  339,  339,  339,  339,  339,    0,    0,
    0,  293,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  337,  337,  337,  337,  337,  337,  337,
    0,    0,  336,  336,  336,  336,  336,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  339,  339,  339,  339,  339,  339,  339,    0,
    0,  334,  334,  334,  334,  334,    0,    0,    0,    0,
  347,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  291,    0,    0,    0,    0,    0,    0,    0,
    0,  336,  336,  336,  336,  336,  336,  336,    0,  294,
  294,  294,  294,  294,    0,    0,    0,    0,    0,  337,
  291,    0,  291,  291,    0,  291,  291,  291,    0,    0,
  334,  334,  334,  334,  334,  334,  334,    0,    0,    0,
  291,    0,  291,  291,  291,  291,    0,    0,  339,  293,
  293,  293,  293,  293,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  295,  294,  294,
  294,  294,  294,  294,  294,  291,  291,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  336,    0,    0,
    0,    0,    0,  292,  295,  295,    0,  295,  295,  295,
  295,  295,  295,    0,  295,  302,  291,    0,  293,  293,
  293,  293,  293,  293,  293,  295,  334,  295,  295,  295,
  295,  292,    0,  292,  292,    0,  292,  292,  292,    0,
    0,    0,    0,  302,    0,  302,  302,    0,    0,  302,
    0,  292,    0,  292,  292,  292,  292,    0,    0,    0,
  295,  295,    0,  302,  294,  302,  302,  302,  302,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  303,    0,    0,    0,  292,  292,    0,    0,
  305,  295,    0,    0,    0,    0,    0,    0,  302,  302,
    0,    0,    0,    0,  293,    0,    0,    0,    0,    0,
  303,    0,  303,  303,    0,    0,  303,  292,  305,    0,
  305,  305,    0,    0,  305,    0,    0,    0,    0,  302,
  303,    0,  303,  303,  303,  303,    0,    0,  305,    0,
  305,  305,  305,  305,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  291,  291,  291,  291,  291,    0,
    0,    0,    0,    0,    0,  303,  303,    0,    0,    0,
    0,    0,    0,  305,  305,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  310,    0,    0,    0,  303,    0,    0,    0,
    0,    0,    0,    0,  305,    0,    0,    0,    0,    0,
    0,    0,    0,  291,  291,  291,  291,  291,  291,  291,
  310,    0,  310,  310,    0,    0,  310,    0,    0,  295,
  295,  295,  295,  295,    0,    0,    0,    0,    0,    0,
  310,    0,  310,  310,  310,  310,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  292,  292,  292,  292,  292,
    0,    0,    0,    0,    0,    0,    0,  302,  302,  302,
  302,  302,    0,    0,    0,  310,  310,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  295,  295,
  295,  295,  295,  295,  295,    0,    0,    0,    0,  291,
    0,    0,    0,    0,    0,    0,  310,    0,    0,    0,
    0,    0,    0,    0,  292,  292,  292,  292,  292,  292,
  292,    0,    0,    0,    0,  312,  302,  302,  302,  302,
  302,  302,  302,    0,  303,  303,  303,  303,  303,    0,
    0,    0,  305,  305,  305,  305,  305,    0,    0,    0,
    0,    0,    0,  312,    0,  312,  312,    0,    0,  312,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  312,  295,  312,  312,  312,  312,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  303,  303,  303,  303,  303,  303,  303,
  292,  304,    0,  305,  305,  305,  305,  305,  312,  312,
    0,    0,  302,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  304,
  308,  304,  304,    0,    0,  304,    0,    0,  309,  312,
    0,    0,    0,    0,  310,  310,  310,  310,  310,  304,
    0,  304,  304,  304,  304,    0,    0,    0,  308,    0,
  308,  308,    0,    0,  308,    0,  309,    0,  309,  309,
    0,    0,  309,    0,    0,    0,    0,    0,  308,  303,
  308,  308,  308,  308,  304,  304,  309,  305,  309,  309,
  309,  309,    0,  188,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  310,  310,  310,  310,  310,
    0,    0,    0,  308,  308,  304,   49,    0,    0,   52,
  307,  309,  309,   51,    0,    0,   47,    0,   48,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  308,    0,    0,    0,  307,    0,
  307,  307,  309,    0,  307,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  307,    0,
    0,  307,    0,  307,   53,    0,    0,  312,  312,  312,
  312,  312,    0,    0,    0,    0,    0,    0,    0,  310,
    0,    0,    0,    0,    0,    0,  311,    0,    0,    0,
    0,    0,    0,  307,  307,    0,    0,    0,   49,   50,
    0,   52,    0,    0,    0,  402,    0,    0,   47,    0,
   48,    0,    0,    0,  311,    0,  311,  311,    0,    0,
  311,    0,    0,    0,  307,    0,    0,    0,  312,  312,
  312,  312,  312,    0,  311,    0,    0,  311,    0,  311,
    0,    0,    0,  304,  304,  304,  304,  304,    0,    0,
    0,    0,    0,    0,    0,    0,   53,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  311,
  311,    0,  308,  308,  308,  308,  308,    0,    0,    0,
  309,  309,  309,  309,  309,    0,    0,    0,    0,    0,
    0,   50,    0,    0,    0,    0,    0,    0,    0,    0,
  311,    0,    0,    0,  304,  304,  304,  304,  304,    0,
    0,    0,  312,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  349,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  308,  308,  308,  308,  308,    0,    0,
    0,  309,  309,  309,  309,  309,    0,    0,    0,    0,
  349,  349,    0,    0,    0,  349,  349,    0,  349,    0,
  349,    0,  307,  307,  307,  307,  307,    0,    0,   27,
   28,  349,    0,    0,  349,   29,   30,   31,    0,   32,
   33,   34,    0,    0,    0,    0,    0,    0,  304,   35,
   36,   37,   38,   39,    0,    0,    0,    0,    0,    0,
    0,    0,   40,   41,    0,    0,    0,  349,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  308,    0,   42,
   43,   44,    0,    0,  307,  309,    0,  307,    0,    0,
    0,    0,    0,    0,   45,    0,    0,  349,  311,  311,
  311,  311,  311,    0,    0,    0,    0,    0,  338,  339,
  381,  341,  382,  355,  356,    0,    0,  383,  401,    0,
    0,   27,   28,    0,    0,    0,    0,   29,   30,   31,
   54,   32,   33,   34,    0,    0,    0,    0,   46,    0,
    0,   35,   36,   37,   38,   39,    0,    0,    0,    0,
    0,    0,    0,    0,   40,   41,    0,    0,    0,    0,
  311,    0,    0,  311,    0,    0,    0,    0,    0,    0,
    0,   42,   43,   44,    0,    0,    0,    0,    0,    0,
    0,   54,    0,    0,    0,    0,   45,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
   46,  349,  349,  349,  349,  349,  349,  349,  349,  349,
  349,  349,  349,  349,  349,  349,  349,  349,  349,  349,
  349,  349,  349,  349,  349,  349,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  349,  349,  349,  349,    0,    0,   55,  349,    0,
    0,    0,  349,  349,  349,  349,  349,  349,  349,    0,
    0,    0,    0,    0,  349,  349,    0,    0,    0,    0,
    0,    0,  349,  349,  349,  349,  349,  349,  349,  349,
    0,    0,    0,    0,    0,    0,  349,  349,  349,    0,
    0,    0,    0,    0,    0,    0,    0,  349,   55,  349,
    0,  349,    0,  349,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  349,  349,  349,  349,  349,  349,  349,
  349,  349,  349,  349,  349,    0,  349,  349,  349,  349,
    0,    0,    0,  349,  349,  349,  349,  349,  349,  349,
  349,  349,  349,  349,  349,  349,  349,  349,   54,   54,
   54,   54,   54,   54,   54,    0,    0,   54,   54,   54,
   54,   54,   54,   54,   54,   54,   54,   54,   54,   54,
   54,   54,   54,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,   54,   54,
   54,   54,    0,    0,   57,   54,    0,    0,    0,   54,
   54,   54,   54,   54,   54,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,   54,    0,    0,    0,   54,    0,
   54,    0,    0,    0,    0,    0,    0,    0,    0,    0,
   54,   54,   54,   54,   54,   54,   54,   54,   54,   54,
   54,   54,    0,   54,   54,   54,   54,    0,    0,    0,
   54,   54,   54,   54,   54,   54,   54,   54,   54,   54,
   54,   54,   54,   54,   54,   55,   55,   55,   55,   55,
   55,   55,    0,    0,   55,   55,   55,   55,   55,   55,
   55,   55,   55,   55,   55,   55,   55,   55,   55,   55,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,   55,   55,   55,   55,    0,
    0,   58,   55,    0,    0,    0,   55,   55,   55,   55,
   55,   55,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,   55,    0,    0,    0,   55,    0,   55,    0,    0,
    0,    0,    0,    0,    0,    0,    0,   55,   55,   55,
   55,   55,   55,   55,   55,   55,   55,   55,   55,    0,
   55,   55,   55,   55,    0,    0,    0,   55,   55,   55,
   55,   55,   55,   55,   55,   55,   55,   55,   55,   55,
   55,   55,   57,   57,   57,   57,   57,   57,   57,    0,
    0,   57,   57,   57,   57,   57,   57,   57,   57,   57,
   57,   57,   57,   57,   57,   57,   57,  175,  166,    0,
    0,    0,  173,  171,    0,  172,    0,  174,    0,    0,
    0,    0,   57,   57,   57,   57,    0,    0,    0,   57,
  168,  167,  169,   57,   57,   57,   57,   57,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  165,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,   57,    0,
    0,    0,   57,    0,   57,    0,    0,    0,    0,    0,
    0,    0,    0,    0,   57,   57,   57,   57,   57,   57,
   57,   57,   57,   57,   57,   57,    0,   57,   57,   57,
   57,    0,    0,    0,   57,   57,   57,   57,   57,   57,
   57,   57,   57,   57,   57,   57,   57,   57,   57,   58,
   58,   58,   58,   58,   58,   58,    0,    0,   58,   58,
   58,   58,   58,   58,   58,   58,   58,   58,   58,   58,
   58,   58,   58,   58,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   58,
   58,   58,   58,    0,    0,    0,   58,    0,    0,    0,
   58,   58,   58,   58,   58,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,   49,    0,    0,   52,    0,
    0,    0,  344,    0,    0,   47,    0,   48,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,   58,    0,    0,    0,   58,
    0,   58,  134,    0,  136,    0,    0,    0,    0,    0,
    0,   58,   58,   58,   58,   58,   58,   58,   58,   58,
   58,   58,   58,   53,   58,   58,   58,   58,    0,    0,
    0,   58,   58,   58,   58,   58,   58,   58,   58,   58,
   58,   58,   58,   58,   58,   58,    0,   49,    0,    0,
   52,    0,    0,    0,  344,    0,    0,   47,   50,   48,
    0,  139,  140,  141,  142,  143,  144,  145,    0,  146,
  147,  148,  149,  150,  151,  152,  153,  154,  155,  156,
  157,  158,  159,  160,  161,  162,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,   49,    0,   53,   52,    0,    0,    0,
  344,    0,    0,   47,    0,   48,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
   50,    0,    0,    0,    0,    0,    0,  170,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,   53,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,   49,    0,    0,   52,    0,    0,    0,  344,
    0,    0,   47,    0,   48,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   50,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  338,  339,  381,  341,  382,
  355,  356,    0,    0,  383,    0,    0,    0,   27,   28,
   53,    0,    0,    0,   29,   30,   31,    0,   32,   33,
   34,    0,    0,    0,    0,    0,    0,    0,   35,   36,
   37,   38,   39,    0,    0,    0,   49,    0,    0,   52,
    0,   40,   41,  585,    0,   50,   47,    0,   48,    0,
    0,    0,    0,    0,    0,    0,    0,    0,   42,   43,
   44,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,   45,    0,    0,    0,  338,  339,  354,
  341,    0,  355,  356,    0,    0,    0,    0,  343,    0,
   27,   28,    0,    0,   53,    0,   29,   30,   31,    0,
   32,   33,   34,    0,    0,    0,    0,    0,    0,    0,
   35,   36,   37,   38,   39,   49,    0,   46,   52,    0,
    0,    0,  344,   40,   41,   47,    0,   48,    0,   50,
    0,    0,    0,  338,  339,  340,  341,    0,  342,    0,
   42,   43,   44,    0,  343,    0,   27,   28,    0,    0,
    0,    0,   29,   30,   31,   45,   32,   33,   34,    0,
    0,    0,    0,    0,    0,    0,   35,   36,   37,   38,
   39,   49,    0,   53,   52,    0,    0,    0,  344,   40,
   41,   47,    0,   48,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   42,   43,   44,   46,
    0,    0,  338,  339,  361,  341,    0,    0,   50,    0,
    0,   45,    0,  343,    0,   27,   28,    0,    0,    0,
    0,   29,   30,   31,    0,   32,   33,   34,    0,   53,
    0,    0,    0,    0,    0,   35,   36,   37,   38,   39,
    0,    0,    0,    0,   49,    0,    0,   52,   40,   41,
    0,  344,    0,    0,   47,   46,   48,    0,    0,    0,
    0,    0,    0,    0,   50,   42,   43,   44,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
   45,    0,    0,    0,    0,    0,  338,  339,  381,  341,
    0,    0,    0,    0,    0,    0,  584,    0,    0,   27,
   28,    0,   53,    0,    0,   29,   30,   31,    0,   32,
   33,   34,    0,    0,    0,    0,    0,    0,    0,   35,
   36,   37,   38,   39,   46,    0,    0,    0,    0,    0,
    0,    0,   40,   41,    0,    0,    0,   50,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   42,
   43,   44,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,   45,  338,  339,  365,  341,    0,
    0,    0,    0,    0,    0,    0,    0,    0,   27,   28,
    0,    0,    0,    0,   29,   30,   31,    0,   32,   33,
   34,    0,    0,    0,    0,    0,    0,    0,   35,   36,
   37,   38,   39,    0,    0,    0,    0,    0,   46,    0,
    0,   40,   41,    0,    0,    0,    0,    0,    0,    0,
    0,  338,  339,  368,  341,    0,    0,    0,   42,   43,
   44,    0,    0,    0,   27,   28,    0,    0,    0,    0,
   29,   30,   31,   45,   32,   33,   34,    0,    0,    0,
    0,    0,    0,    0,   35,   36,   37,   38,   39,    0,
    0,    0,    0,   49,    0,    0,   52,   40,   41,    0,
  395,    0,    0,   47,    0,   48,    0,    0,    0,    0,
    0,    0,    0,    0,   42,   43,   44,   46,    0,    0,
    0,    0,    0,    0,  338,  339,  371,  341,    0,   45,
  396,    0,    0,    0,    0,    0,    0,   27,   28,    0,
    0,    0,    0,   29,   30,   31,    0,   32,   33,   34,
    0,   53,    0,    0,    0,    0,    0,   35,   36,   37,
   38,   39,   49,    0,    0,   52,    0,    0,    0,  344,
   40,   41,   47,   46,   48,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   50,   42,   43,   44,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  306,   45,    0,    0,    0,    0,    0,    0,   49,
    0,    0,   52,    0,    0,    0,   51,    0,    0,   47,
   53,   48,    0,    0,    0,    0,    0,    0,    0,  306,
    0,  306,  306,    0,    0,  306,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   46,    0,    0,  306,
    0,    0,  306,    0,  306,   50,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,   53,    0,    0,
    0,    0,    0,    0,    0,    0,   49,    0,    0,   52,
    0,    0,    0,  344,  306,  306,   47,    0,   48,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,   50,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  306,    0,    0,    0,    0,
    0,    0,    0,   49,    0,    0,   52,    0,    0,    0,
  444,    0,    0,   47,   53,   48,    0,    0,    0,    0,
    0,    0,    0,  338,    0,  381,  341,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   27,   28,    0,    0,
    0,    0,   29,   30,   31,    0,   32,   33,   34,   50,
    0,    0,    0,    0,    0,    0,   35,   36,   37,   38,
   39,   53,    0,    0,    0,    0,  175,  166,    0,   40,
   41,  173,  171,    0,  172,    0,  174,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   42,   43,   44,  168,
  167,  169,  338,  339,  381,  341,   50,    0,    0,    0,
    0,   45,    0,    0,    0,   27,   28,    0,    0,    0,
    0,   29,   30,   31,    0,   32,   33,   34,    0,    0,
    0,    0,    0,    0,    0,   35,   36,   37,   38,   39,
    0,    0,    0,  306,  306,  306,  306,  306,   40,   41,
    0,    0,  375,    0,    0,   46,    0,    0,    0,    0,
  376,  377,   27,   28,    0,   42,   43,   44,   29,   30,
   31,    0,   32,   33,   34,    0,    0,    0,    0,    0,
   45,    0,   35,   36,   37,   38,   39,    0,    0,    0,
    0,    0,    0,    0,    0,   40,   41,   49,    0,    0,
   52,    0,    0,    0,   51,  306,    0,   47,  306,   48,
    0,    0,   42,   43,   44,    0,  338,    0,  381,  341,
    0,    0,    0,    0,   46,    0,    0,   45,    0,   27,
   28,    0,    0,    0,    0,   29,   30,   31,    0,   32,
   33,   34,    0,    0,    0,    0,    0,    0,    0,   35,
   36,   37,   38,   39,    0,   53,    0,    0,   49,    0,
    0,   52,   40,   41,    0,   51,  375,    0,   47,    0,
   48,   46,    0,    0,  376,  377,   27,   28,    0,   42,
   43,   44,   29,   30,   31,    0,   32,   33,   34,    0,
   50,    0,    0,    0,   45,    0,   35,   36,   37,   38,
   39,  134,    0,    0,    0,    0,    0,    0,    0,   40,
   41,    0,    0,    0,    0,    0,   53,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   42,   43,   44,    0,
    0,    0,    0,    0,    0,    0,   49,    0,   46,   52,
    0,   45,    0,   51,    0,    0,   47,    0,   48,    0,
    0,   50,    0,    0,    0,    0,    0,    0,    0,    0,
  139,  140,  141,  142,  143,  144,  145,    0,  146,  147,
  148,  149,  150,  151,  152,  153,  154,  155,  156,  157,
  158,  159,  160,  161,  162,   46,    0,    0,    0,    0,
    0,    0,   49,    0,   53,   52,    0,    0,    0,   51,
    0,    0,   47,    0,   48,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   50,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  170,    0,    0,    0,
   53,  507,  488,  489,    0,    0,    0,    0,    0,    0,
   27,   28,    0,    0,    0,    0,   29,   30,   31,    0,
   32,   33,   34,    0,    0,    0,    0,    0,    0,    0,
   35,   36,   37,   38,   39,   50,    0,    0,   49,    0,
    0,   52,    0,   40,   41,   51,    0,    0,   47,    0,
   48,    0,    0,    0,    0,    0,    0,    0,    0,    0,
   42,   43,   44,  355,  356,    0,    0,    0,    0,    0,
    0,   27,   28,    0,    0,   45,    0,   29,   30,   31,
    0,   32,   33,   34,    0,    0,    0,    0,    0,    0,
    0,   35,   36,   37,   38,   39,   53,    0,    0,    0,
    0,    0,    0,    0,   40,   41,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,   49,    0,   46,
   52,   42,   43,   44,   51,    0,    0,   47,    0,   48,
    0,   50,    0,    0,    0,    0,   45,  589,    0,    0,
  627,  488,  489,    0,    0,    0,    0,    0,    0,   27,
   28,    0,    0,    0,    0,   29,   30,   31,    0,   32,
   33,   34,    0,    0,    0,    0,    0,    0,    0,   35,
   36,   37,   38,   39,    0,   53,    0,    0,   49,    0,
   46,   52,   40,   41,    0,   51,    0,    0,   47,    0,
   48,    0,  338,    0,  381,  341,    0,    0,    0,   42,
   43,   44,    0,    0,    0,   27,   28,    0,    0,    0,
   50,   29,   30,   31,   45,   32,   33,   34,    0,    0,
    0,    0,    0,    0,    0,   35,   36,   37,   38,   39,
    0,    0,    0,    0,   49,    0,   53,   52,   40,   41,
    0,   51,    0,    0,   47,    0,   48,    0,    0,    0,
    0,    0,    0,    0,    0,   42,   43,   44,   46,  112,
  107,    0,  190,    0,  110,  108,    0,  109,    0,  111,
   45,   50,    0,    0,    0,    0,    0,    0,    0,    0,
  104,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,   53,    0,    0,    0,    0,    0,    0,    0,
    0,   27,   28,    0,    0,    0,    0,   29,   30,   31,
    0,   32,   33,   34,   46,    0,  106,    0,    0,    0,
    0,   35,   36,   37,   38,   39,   49,   50,    0,   52,
    0,    0,    0,   51,   40,   41,   47,    0,   48,    0,
    0,    0,    0,    0,    0,    0,  105,    0,    0,    0,
    0,   42,   43,   44,    0,    0,    0,    0,    0,    0,
    0,    0,   49,    0,    0,   52,  191,  192,    0,   51,
  375,    0,   47,    0,   48,    0,    0,    0,    0,  377,
   27,   28,    0,    0,   53,    0,   29,   30,   31,    0,
   32,   33,   34,    0,    0,    0,    0,    0,    0,    0,
   35,   36,   37,   38,   39,    0,    0,    0,    0,    0,
   46,    0,    0,   40,   41,    0,    0,    0,    0,   50,
   53,    0,    0,    0,    0,    0,    0,    0,    0,    0,
   42,   43,   44,  488,  489,    0,    0,    0,    0,    0,
    0,   27,   28,    0,    0,   45,    0,   29,   30,   31,
    0,   32,   33,   34,    0,   50,    0,    0,  514,    0,
    0,   35,   36,   37,   38,   39,   49,    0,    0,   52,
    0,    0,    0,   51,   40,   41,   47,    0,   48,    0,
    0,    0,    0,    0,    0,    0,    0,   87,   88,   46,
    0,   42,   43,   44,    0,    0,    0,   27,   28,    0,
    0,    0,    0,   29,   30,   31,   45,   32,   33,   34,
    0,    0,    0,    0,    0,    0,    0,   35,   36,   37,
   38,   39,    0,    0,   53,    0,   49,    0,    0,   52,
   40,   41,    0,   51,  556,    0,   47,   89,   48,    0,
    0,    0,    0,   90,   91,    0,    0,   42,   43,   44,
   46,   92,   93,   94,   95,   96,   97,   98,   99,   50,
    0,    0,   45,  515,    0,  100,  101,  102,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  103,    0,
    0,  355,  356,    0,   53,    0,    0,    0,    0,   27,
   28,    0,    0,    0,    0,   29,   30,   31,    0,   32,
   33,   34,    0,    0,    0,    0,   46,    0,    0,   35,
   36,   37,   38,   39,    0,  502,    0,    0,    0,   50,
    0,    0,   40,   41,    0,   27,   28,    0,    0,    0,
    0,   29,   30,   31,    0,   32,   33,   34,    0,   42,
   43,   44,    0,    0,    0,   35,   36,   37,   38,   39,
   49,    0,    0,   52,   45,    0,    0,   51,   40,   41,
   47,    0,   48,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,   42,   43,   44,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
   45,    0,    0,    0,    0,    0,    0,    0,   46,    0,
    0,    0,    0,    0,    0,    0,    0,    0,   53,    0,
    0,    0,    0,   49,    0,    0,   52,    0,    0,  511,
   51,    0,    0,   47,    0,   48,    0,    0,    0,   27,
   28,    0,    0,    0,   46,   29,   30,   31,    0,   32,
   33,   34,    0,   50,    0,    0,    0,    0,    0,   35,
   36,   37,   38,   39,    0,    0,    0,    0,    0,    0,
    0,    0,   40,   41,    0,    0,    0,    0,    0,    0,
    0,   53,    0,    0,    0,   49,    0,    0,   52,   42,
   43,   44,   51,    0,    0,   47,    0,   48,    0,   27,
   28,    0,    0,    0,   45,   29,   30,   31,    0,   32,
   33,   34,    0,    0,    0,    0,   50,    0,    0,   35,
   36,   37,   38,   39,    0,    0,    0,    0,    0,    0,
    0,    0,   40,   41,    0,    0,    0,    0,    0,    0,
    0,    0,    0,   53,    0,    0,    0,    0,   46,   42,
   43,   44,    0,    0,    0,   49,    0,    0,   52,    0,
    0,    0,  406,    0,   45,   47,    0,   48,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,   50,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  358,    0,    0,  358,    0,    0,    0,  358,    0,
    0,  358,    0,  358,    0,    0,    0,    0,   46,    0,
    0,    0,    0,   53,    0,    0,    0,    0,    0,    0,
    0,    0,    0,   27,   28,    0,    0,    0,    0,   29,
   30,   31,    0,   32,   33,   34,    0,    0,    0,    0,
    0,    0,    0,   35,   36,   37,   38,   39,   50,  358,
    0,    0,    0,    0,    0,    0,   40,   41,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,   42,   43,   44,  625,    0,    0,    0,
    0,    0,    0,    0,  358,    0,   27,   28,   45,  589,
    0,    0,   29,   30,   31,    0,   32,   33,   34,    0,
    0,    0,    0,    0,    0,    0,   35,   36,   37,   38,
   39,    0,    0,    0,    0,    0,    0,  175,  166,   40,
   41,  274,  173,  171,    0,  172,    0,  174,    0,    0,
    0,    0,   46,    0,    0,    0,   42,   43,   44,    0,
  168,  167,  169,  163,    0,    0,    0,    0,   27,   28,
    0,   45,    0,    0,   29,   30,   31,    0,   32,   33,
   34,    0,    0,    0,    0,    0,    0,    0,   35,   36,
   37,   38,   39,    0,  165,    0,    0,    0,    0,    0,
    0,   40,   41,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,   46,    0,    0,   42,   43,
   44,    0,    0,    0,  164,    0,    0,    0,    0,    0,
    0,    0,    0,   45,    0,    0,    0,    0,   27,   28,
    0,    0,    0,    0,   29,   30,   31,    0,   32,   33,
   34,    0,    0,    0,    0,    0,    0,    0,   35,   36,
   37,   38,   39,    0,    0,    0,    0,    0,    0,    0,
    0,   40,   41,    0,  358,  358,    0,   46,    0,    0,
  358,  358,  358,    0,  358,  358,  358,    0,   42,   43,
   44,    0,    0,    0,  358,  358,  358,  358,  358,    0,
    0,    0,    0,   45,  175,  166,    0,  358,  358,  173,
  171,    0,  172,    0,  174,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  358,  358,  358,  168,  167,  169,
  163,    0,    0,    0,    0,    0,    0,    0,    0,  358,
    0,    0,    0,    0,    0,    0,    0,   46,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  275,  165,  134,  135,  136,  137,  138,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  358,    0,    0,    0,    0,    0,    0,
    0,  164,  175,  166,    0,    0,    0,  173,  171,  328,
  172,    0,  174,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  168,  167,  169,  163,    0,
    0,  139,  140,  141,  142,  143,  144,  145,    0,  146,
  147,  148,  149,  150,  151,  152,  153,  154,  155,  156,
  157,  158,  159,  160,  161,  162,    0,    0,    0,  165,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  164,
  175,  166,    0,    0,    0,  173,  171,  463,  172,    0,
  174,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  168,  167,  169,  163,  170,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  134,
  135,  136,  137,  138,    0,    0,    0,  165,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  164,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  139,  140,
  141,  142,  143,  144,  145,    0,  146,  147,  148,  149,
  150,  151,  152,  153,  154,  155,  156,  157,  158,  159,
  160,  161,  162,    0,    0,    0,    0,  134,  135,  136,
  137,  138,    0,    0,    0,    0,  175,  166,    0,    0,
    0,  173,  171,    0,  172,    0,  174,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  472,    0,  168,
  167,  169,  163,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  170,    0,  139,  140,  141,  142,
  143,  144,  145,  165,  146,  147,  148,  149,  150,  151,
  152,  153,  154,  155,  156,  157,  158,  159,  160,  161,
  162,    0,    0,    0,    0,  134,  135,  136,  137,  138,
    0,    0,    0,  164,  175,  166,    0,    0,    0,  173,
  171,  497,  172,    0,  174,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  168,  167,  169,
  163,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  170,    0,  139,  140,  141,  142,  143,  144,
  145,  165,  146,  147,  148,  149,  150,  151,  152,  153,
  154,  155,  156,  157,  158,  159,  160,  161,  162,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  164,  175,  166,    0,    0,    0,  173,  171,  532,
  172,    0,  174,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  168,  167,  169,  163,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  170,  134,  135,  136,  137,  138,    0,    0,    0,  165,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  164,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  139,  140,  141,  142,  143,  144,  145,    0,  146,  147,
  148,  149,  150,  151,  152,  153,  154,  155,  156,  157,
  158,  159,  160,  161,  162,    0,    0,    0,    0,  134,
  135,  136,  137,  138,    0,    0,    0,    0,  175,  166,
    0,    0,    0,  173,  171,  533,  172,    0,  174,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  168,  167,  169,  163,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  170,    0,  139,  140,
  141,  142,  143,  144,  145,  165,  146,  147,  148,  149,
  150,  151,  152,  153,  154,  155,  156,  157,  158,  159,
  160,  161,  162,    0,    0,    0,    0,  134,  135,  136,
  137,  138,    0,    0,    0,  164,  282,  282,    0,    0,
    0,  282,  282,  282,  282,    0,  282,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  282,
  282,  282,  282,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  170,    0,  139,  140,  141,  142,
  143,  144,  145,  282,  146,  147,  148,  149,  150,  151,
  152,  153,  154,  155,  156,  157,  158,  159,  160,  161,
  162,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  282,  277,  277,    0,  277,    0,  277,
  277,    0,  277,    0,  277,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  277,  277,  277,
  277,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  170,  134,  135,  136,  137,  138,    0,    0,
    0,  277,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  277,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  139,  140,  141,  142,  143,  144,  145,    0,
  146,  147,  148,  149,  150,  151,  152,  153,  154,  155,
  156,  157,  158,  159,  160,  161,  162,    0,    0,    0,
    0,  282,  282,  282,  282,  282,    0,    0,    0,    0,
  175,  166,    0,    0,    0,  173,  171,    0,  172,    0,
  174,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  168,  167,  169,  163,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  170,    0,
  282,  282,  282,  282,  282,  282,  282,  165,  282,  282,
  282,  282,  282,  282,  282,  282,  282,  282,  282,  282,
  282,  282,  282,  282,  282,    0,    0,    0,    0,  277,
  277,  277,  277,  277,    0,    0,    0,  164,  175,  166,
    0,    0,    0,  173,  171,    0,  172,    0,  174,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  168,  167,  169,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  282,    0,  277,  277,
  277,  277,  277,  277,  277,  165,  277,  277,  277,  277,
  277,  277,  277,  277,  277,  277,  277,  277,  277,  277,
  277,  277,  277,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  164,  175,  166,    0,    0,
    0,  173,  171,    0,  172,    0,  174,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  168,
  167,  169,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  277,  134,  135,  136,  137,  138,
    0,    0,    0,  165,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  164,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  139,  140,  141,  142,  143,  144,
  145,    0,  146,  147,  148,  149,  150,  151,  152,  153,
  154,  155,  156,  157,  158,  159,  160,  161,  162,    0,
    0,    0,    0,  134,  135,  136,  137,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  170,    0,  139,  140,  141,  142,  143,  144,  145,    0,
  146,  147,  148,  149,  150,  151,  152,  153,  154,  155,
  156,  157,  158,  159,  160,  161,  162,    0,    0,    0,
    0,  134,  135,  136,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  170,    0,
  139,  140,  141,  142,  143,  144,  145,    0,  146,  147,
  148,  149,  150,  151,  152,  153,  154,  155,  156,  157,
  158,  159,  160,  161,  162,  202,  203,  204,  205,  206,
  207,  208,    0,    0,  209,  210,  211,  212,  213,  214,
  215,  216,  217,  218,  219,  220,  221,  222,  223,  224,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  225,  226,  227,    0,
    0,    0,  228,    0,    0,    0,    0,  229,  230,    0,
  231,    0,    0,    0,    0,    0,  170,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  232,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  233,  234,  235,
  236,  237,  238,  239,  240,  241,  242,  243,  244,    0,
  245,  246,  247,  248,    0,    0,    0,  249,  250,  251,
  252,  253,  254,  255,  256,  257,  258,  259,    4,    4,
    4,    4,    4,    4,    4,    0,    0,    4,    4,    4,
    4,    4,    4,    4,    4,    4,    4,    4,    4,    4,
    4,    4,    4,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    4,
    4,    4,    0,    0,    0,    4,    0,    0,    0,    0,
    4,    4,    0,    4,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    4,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    4,    4,    4,    4,    4,    4,    4,    4,    4,    4,
    4,    4,    0,    4,    4,    4,    4,    0,    0,    0,
    4,    4,    4,    4,    4,    4,    4,    4,    4,    4,
    4,
};
static const YYINT yycheck[] = {                          9,
  204,   10,   37,  197,  223,   15,   16,   10,  219,  223,
  199,  219,  220,  177,  178,   61,  547,  221,  259,   29,
   30,   31,   32,   33,   34,  242,   40,  244,    1,   10,
   40,   41,   42,   43,   44,   44,   10,   47,   48,   49,
   50,   51,   10,   53,   13,   18,  204,  205,  206,  207,
  208,   10,   62,  211,  357,  259,  217,   10,   10,   10,
  221,  219,   10,   44,   10,   10,   76,   77,   78,   10,
   44,   81,  233,  234,  235,   10,   44,  238,   10,   89,
  241,  242,  243,  244,  252,   44,  254,   10,  249,  250,
   10,   44,   44,  103,  255,  256,   44,   10,   44,   44,
  288,  289,  283,   44,  285,  286,  287,  288,  289,  290,
   79,  283,   44,  285,  286,   10,   10,   40,  649,  650,
   40,   41,  294,   10,  134,  135,  136,  137,  138,  139,
  140,  141,  142,  143,  144,  145,  146,  147,  148,  149,
  150,  151,  152,  153,  154,  155,  156,  157,  158,  159,
  160,  161,  162,  163,  164,  165,  166,  167,  168,  169,
  170,  171,  172,  173,  174,  175,  359,  331,  508,  509,
  388,  234,  359,   10,   10,  283,   10,  285,  286,   10,
  243,   10,   10,   58,  292,  525,  203,  204,  205,   10,
   10,   10,  202,  203,  204,  205,  206,  207,  208,  209,
  210,  382,  212,   40,  214,  215,   40,  217,  218,   40,
  220,   40,   40,  186,  224,  225,  226,  227,  228,   40,
   40,   40,   41,   10,   10,   44,  236,  237,  222,  239,
  240,   10,   43,   10,   61,  245,  246,  247,  248,   58,
  444,  251,   10,  253,   63,   10,  487,  257,  258,   45,
   35,  492,  246,   40,   40,  388,  266,  267,  268,   10,
   10,   40,   41,   40,   41,   44,   10,   44,  314,   10,
  359,   44,   40,  287,   93,   40,  290,   10,  497,   58,
   44,   58,  471,  497,    0,   10,   63,   10,  492,  286,
  484,  485,   10,  406,   10,  298,  504,  294,  295,  510,
  508,  509,   10,   10,   10,  509,  309,   40,   41,  312,
  527,   44,   10,   44,   93,   44,   93,   44,  328,   40,
  330,  489,  297,   10,  359,   58,  287,  288,  486,   44,
   63,  292,   44,  491,  344,  493,  494,  495,  496,   44,
   44,  316,  317,  318,  319,  320,  283,   44,  285,  286,
  508,  354,  513,   40,   41,  358,  546,   44,  548,  549,
   93,   94,  530,  531,  532,  533,  527,   44,   44,   44,
  285,   58,  287,  288,  289,  292,   63,  292,  287,  288,
  289,   44,   44,  292,   44,  395,   44,   44,   44,   44,
   10,  124,  402,   44,   44,   44,  406,  406,  401,  402,
  403,  404,   44,   44,   44,   44,   93,   94,   44,   10,
   41,  289,  288,   41,  424,  425,  426,  291,   41,  623,
   40,   41,   40,   40,   44,  285,   41,   41,  285,  389,
  286,   44,   44,   44,  444,   41,   41,  124,   58,   41,
   44,   44,  285,   63,   44,   44,  265,  266,   41,   41,
   41,   10,   10,  463,  618,  619,  406,   10,   10,   10,
   10,  622,  472,   61,   61,   10,  406,  628,   10,   37,
   10,   10,   10,   93,   42,   43,  486,   45,   10,   47,
   10,  491,   10,  493,  494,  495,  496,   10,  498,  266,
   10,   10,   10,   10,   10,  505,   10,   10,   10,  509,
   37,   10,   10,   10,  124,   42,   43,   10,   45,   10,
   47,   10,   10,   10,   10,  525,  526,   10,   10,  529,
   10,   10,   10,   60,   61,   62,   10,   10,   10,   10,
  263,  264,  265,  266,  544,   10,  218,  525,  184,   83,
  256,  186,  258,  259,  260,  261,  262,  263,  264,  652,
  600,  267,  268,  269,  270,  271,  272,  273,  274,  275,
  276,  277,  278,  279,  280,  281,  282,   -1,  602,  579,
  601,   -1,   -1,   -1,   -1,  585,  263,  264,  265,  266,
   -1,  297,  298,  299,  300,  301,   -1,   -1,   -1,  305,
  600,  601,  602,  309,  310,  311,  312,  313,   -1,   -1,
  316,  317,  318,  319,  320,   -1,   37,   -1,   -1,   -1,
   -1,   42,   43,   -1,   45,   -1,   47,   -1,  628,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   60,
   -1,   62,   -1,  349,  350,  351,  352,  353,  354,  355,
   -1,   -1,  358,  263,  360,  265,  266,  363,  364,  365,
  366,  367,  368,  369,  370,  371,  372,  373,  374,  375,
  376,  377,  378,  379,  380,  381,   10,  383,  384,  385,
  386,  387,   -1,   -1,  390,  391,  392,  393,  394,  395,
  396,  397,  398,  399,  400,  401,  402,  403,  404,   -1,
   -1,   -1,   -1,   37,   38,   10,   -1,   -1,   42,   43,
   44,   45,   -1,   47,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   60,   61,   62,   63,
   -1,   -1,   37,   38,   -1,   40,   -1,   42,   43,   -1,
   45,   -1,   47,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   60,   61,   62,   63,   -1,
   94,   -1,   -1,  321,  322,   -1,   -1,   -1,   -1,   -1,
   -1,  329,  330,  331,  332,  333,  334,  335,  336,  337,
  338,  339,  340,  341,  342,  343,  344,  345,   -1,   94,
  124,   -1,   -1,   10,  321,  322,  323,  324,  325,  326,
  327,   -1,  329,  330,  331,  332,  333,  334,  335,  336,
  337,  338,  339,  340,  341,  342,  343,  344,  345,  124,
   37,   38,   10,   40,   -1,   42,   43,   -1,   45,   -1,
   47,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   60,   61,   62,   63,   -1,   -1,   37,
   38,   -1,   -1,   -1,   42,   43,   -1,   45,   -1,   47,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   60,   61,   62,   63,   -1,   94,   -1,   -1,
  407,  329,  330,  331,  332,  333,  334,  335,  336,  337,
  338,  339,  340,  341,  342,  343,  344,  345,   -1,   -1,
  321,  322,  323,   -1,  325,  326,   94,  124,  329,  330,
  331,  332,  333,  334,  335,  336,  337,  338,  339,  340,
  341,  342,  343,  344,  345,   -1,   -1,   -1,  262,  263,
  264,  265,  266,   37,   -1,   -1,  124,   -1,   42,   43,
   -1,   45,   -1,   47,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  262,  263,  264,
  265,  266,   37,   -1,   -1,   -1,   -1,   42,   -1,   -1,
   -1,   -1,   47,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  407,  321,  322,  323,
  324,  325,  326,  327,   -1,  329,  330,  331,  332,  333,
  334,  335,  336,  337,  338,  339,  340,  341,  342,  343,
  344,  345,   -1,   -1,   -1,   -1,  321,  322,  323,  324,
  325,  326,  327,   -1,  329,  330,  331,  332,  333,  334,
  335,  336,  337,  338,  339,  340,  341,  342,  343,  344,
  345,   -1,   -1,   -1,   -1,  262,  263,  264,  265,  266,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  407,  262,  263,  264,  265,  266,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  407,   -1,  321,  322,  323,  324,  325,  326,
  327,   -1,  329,  330,  331,  332,  333,  334,  335,  336,
  337,  338,  339,  340,  341,  342,  343,  344,  345,   -1,
   -1,   10,   -1,  321,  322,  323,  324,  325,  326,  327,
   -1,  329,  330,  331,  332,  333,  334,  335,  336,  337,
  338,  339,  340,  341,  342,  343,  344,  345,   37,   38,
   10,   -1,   -1,   42,   43,   -1,   45,   -1,   47,   -1,
   10,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   60,   61,   62,   63,   -1,   -1,   37,   38,   -1,
  407,   -1,   42,   43,   -1,   45,   -1,   47,   -1,   -1,
   40,   41,   -1,   -1,   44,   -1,   -1,   -1,   -1,   -1,
   60,   61,   62,   63,   -1,   94,   -1,   -1,   58,  407,
   -1,   -1,   -1,   63,   -1,  329,  330,  331,  332,  333,
  334,  335,  336,  337,  338,  339,  340,  341,  342,  343,
  344,  345,   -1,   -1,   94,  124,   -1,   -1,   10,   -1,
   -1,   -1,   -1,   93,  329,  330,  331,  332,  333,  334,
  335,  336,  337,  338,  339,  340,  341,  342,  343,  344,
  345,   -1,   -1,   -1,  124,   37,   38,   10,   -1,   -1,
   42,   43,   -1,   45,  124,   47,   -1,   10,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   60,   61,
   62,   63,   -1,   -1,   37,   38,   -1,   -1,   -1,   42,
   43,   -1,   45,   -1,   47,   38,   -1,   40,   41,   -1,
   -1,   44,   -1,   -1,   -1,   -1,   -1,   60,   61,   62,
   63,   -1,   94,   -1,   -1,   58,   -1,   -1,   -1,   -1,
   63,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   94,  124,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   93,   94,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  262,  263,  264,  265,  266,   -1,   -1,
   -1,  124,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  124,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  262,  263,  264,  265,  266,   -1,   -1,   -1,
   -1,   -1,   -1,  263,   -1,  265,  266,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  321,  322,  323,  324,  325,  326,  327,   -1,
  329,  330,  331,  332,  333,  334,  335,  336,  337,  338,
  339,  340,  341,  342,  343,  344,  345,   -1,   -1,   -1,
   -1,  321,  322,  323,  324,  325,  326,  327,   -1,  329,
  330,  331,  332,  333,  334,  335,  336,  337,  338,  339,
  340,  341,  342,  343,  344,  345,   -1,   -1,   -1,   -1,
  262,  263,  264,  265,  266,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  407,  262,
  263,  264,  265,  266,   -1,   -1,   -1,   -1,   -1,  262,
  263,  264,  265,  266,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  407,   -1,  321,
  322,  323,  324,  325,  326,  327,   -1,  329,  330,  331,
  332,  333,  334,  335,  336,  337,  338,  339,  340,  341,
  342,  343,  344,  345,   -1,   -1,   10,   -1,  321,  322,
  323,  324,  325,  326,  327,   -1,  329,  330,  331,  332,
  333,  334,  335,  336,  337,  338,  339,  340,  341,  342,
  343,  344,  345,   37,   38,   10,   -1,   -1,   42,   43,
   -1,   45,   -1,   47,   -1,   10,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   60,   61,   62,   63,
   -1,   -1,   37,   38,   -1,  407,   -1,   42,   43,   -1,
   45,   -1,   47,   38,   -1,   40,   41,   -1,   -1,   44,
   -1,   -1,   -1,   -1,   -1,   60,   61,   62,   63,   -1,
   94,   -1,   -1,   58,  407,   -1,   -1,   -1,   63,   -1,
   -1,  256,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   94,
  124,   -1,   -1,   10,   -1,   -1,   -1,   -1,   93,   94,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  297,   -1,   -1,   -1,   -1,   -1,   -1,  124,
   37,   38,   10,   -1,   -1,   42,   43,   -1,   45,  124,
   47,  316,  317,  318,  319,  320,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   60,   61,   62,   63,   -1,   -1,   37,
   38,   -1,   -1,   -1,   42,   43,   -1,   45,   -1,   47,
   -1,   -1,   -1,   -1,  349,  350,  351,  352,  353,   -1,
  355,   -1,   60,   61,   62,   63,   -1,   94,  363,  364,
  365,  366,  367,  368,  369,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  387,   -1,   -1,   -1,   94,  124,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  262,  263,
  264,  265,  266,   -1,   -1,   -1,  124,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  262,  263,  264,
  265,  266,   -1,   -1,   -1,   -1,   -1,  262,  263,  264,
  265,  266,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  321,  322,  323,
  324,  325,  326,  327,   -1,  329,  330,  331,  332,  333,
  334,  335,  336,  337,  338,  339,  340,  341,  342,  343,
  344,  345,   -1,   -1,   -1,   -1,  321,  322,  323,  324,
  325,  326,  327,   -1,  329,  330,  331,  332,  333,  334,
  335,  336,  337,  338,  339,  340,  341,  342,  343,  344,
  345,   -1,   -1,   -1,   -1,  262,  263,  264,  265,  266,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  407,  262,  263,  264,  265,  266,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  407,   -1,  321,  322,  323,  324,  325,  326,
  327,   -1,  329,  330,  331,  332,  333,  334,  335,  336,
  337,  338,  339,  340,  341,  342,  343,  344,  345,   -1,
   -1,   10,   -1,  321,  322,  323,  324,  325,  326,  327,
   -1,  329,  330,  331,  332,  333,  334,  335,  336,  337,
  338,  339,  340,  341,  342,  343,  344,  345,   37,   38,
   10,   -1,   -1,   42,   43,   -1,   45,   -1,   47,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   60,   61,   62,   63,   -1,   -1,   37,   38,   -1,
  407,   -1,   42,   43,   -1,   45,   -1,   47,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   60,   61,   62,   63,   -1,   94,   -1,   -1,   -1,  407,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   94,  124,   -1,   -1,   10,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  124,   37,   38,   10,   -1,   -1,
   42,   43,   -1,   45,   -1,   47,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   60,   61,
   62,   63,   -1,   -1,   37,   38,   -1,   -1,   -1,   42,
   43,   -1,   45,   -1,   47,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   60,   61,   62,
   63,   -1,   94,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   94,  124,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  262,  263,  264,  265,  266,   -1,   -1,
   -1,  124,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  262,  263,  264,  265,  266,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  321,  322,  323,  324,  325,  326,  327,   -1,
  329,  330,  331,  332,  333,  334,  335,  336,  337,  338,
  339,  340,  341,  342,  343,  344,  345,   -1,   -1,   -1,
   -1,  321,  322,  323,  324,  325,  326,  327,   -1,  329,
  330,  331,  332,  333,  334,  335,  336,  337,  338,  339,
  340,  341,  342,  343,  344,  345,   -1,   -1,   -1,   -1,
  262,  263,  264,  265,  266,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  407,  262,
  263,  264,  265,  266,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  407,   -1,  321,
  322,  323,  324,  325,  326,  327,   -1,  329,  330,  331,
  332,  333,  334,  335,  336,  337,  338,  339,  340,  341,
  342,  343,  344,  345,   -1,   -1,   10,   -1,  321,  322,
  323,  324,  325,  326,  327,   -1,  329,  330,  331,  332,
  333,  334,  335,  336,  337,  338,  339,  340,  341,  342,
  343,  344,  345,   37,   38,   -1,   -1,   -1,   42,   43,
   -1,   45,   -1,   47,   -1,   10,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   60,   61,   62,   63,
   -1,   -1,   -1,   -1,   -1,  407,   -1,   -1,   -1,   -1,
   -1,   -1,   37,   38,   -1,   40,   41,   42,   43,   44,
   45,   -1,   47,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   94,   -1,   -1,   58,  407,   60,   61,   62,   63,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   10,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  124,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   93,   94,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   37,
   38,   10,   40,   41,   42,   43,   44,   45,   -1,   47,
   -1,   -1,   -1,   10,   -1,   -1,   -1,   -1,   -1,  124,
   58,   -1,   60,   61,   62,   63,   -1,   -1,   37,   38,
   -1,   40,   41,   42,   43,   44,   45,   -1,   47,   -1,
   37,   38,   10,   40,   41,   42,   43,   44,   45,   58,
   47,   60,   61,   62,   63,   93,   94,   -1,   -1,   -1,
   -1,   58,   -1,   60,   61,   62,   63,   -1,   -1,   37,
   38,   -1,   40,   41,   42,   43,   44,   45,   -1,   47,
   -1,   -1,   -1,   -1,   93,   94,  124,   -1,   -1,   -1,
   58,   -1,   60,   61,   62,   63,   93,   94,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  124,   -1,   -1,  262,  263,
  264,  265,  266,   -1,   -1,   93,   94,  124,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  124,  262,  263,  264,
  265,  266,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  321,  322,  323,
  324,  325,  326,  327,   -1,  329,  330,  331,  332,  333,
  334,  335,  336,  337,  338,  339,  340,  341,  342,  343,
  344,  345,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  321,  322,  323,  324,
  325,  326,  327,   -1,  262,  263,  264,  265,  266,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  262,  263,  264,  265,  266,   -1,   -1,
   -1,   -1,   -1,  407,   -1,  262,  263,  264,  265,  266,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  321,  322,  323,  324,  325,  326,  327,
   -1,   -1,   -1,   -1,  262,  263,  264,  265,  266,   -1,
   -1,   -1,  407,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  321,  322,  323,  324,  325,  326,  327,   -1,
   -1,   -1,   -1,   -1,  321,  322,  323,  324,  325,  326,
  327,   -1,   -1,   10,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  321,  322,  323,  324,  325,  326,  327,
   37,   38,   -1,   40,   41,   42,   43,   44,   45,  407,
   47,   -1,   10,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   58,   -1,   60,   61,   62,   63,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  407,   37,
   38,   10,   40,   41,   42,   43,   44,   45,   -1,   47,
  407,   -1,   -1,   -1,   -1,   -1,   93,   94,   -1,   -1,
   58,   -1,   60,   61,   62,   63,   -1,   -1,   37,   38,
   -1,   40,   41,   42,   43,   44,   45,   -1,   47,  407,
   10,   -1,   -1,   -1,   -1,   -1,   -1,  124,   -1,   58,
   -1,   60,   61,   62,   63,   93,   94,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   37,   38,   10,
   40,   41,   42,   43,   44,   45,   -1,   47,   -1,   -1,
   -1,   -1,   -1,   -1,   93,   94,  124,   -1,   58,   -1,
   60,   61,   62,   63,   -1,   -1,   37,   38,   -1,   40,
   41,   42,   43,   44,   45,   -1,   47,   10,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  124,   -1,   58,   -1,   60,
   61,   62,   63,   93,   94,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   37,   38,   -1,   40,   41,   42,
   43,   44,   45,   -1,   47,   -1,   -1,   10,   -1,   -1,
   -1,   -1,   93,   94,  124,   58,   -1,   60,   61,   62,
   63,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   37,   38,   -1,   40,   41,   42,
   43,   44,   45,  124,   47,  262,  263,  264,  265,  266,
   93,   94,   -1,   -1,   -1,   58,   -1,   60,   61,   62,
   63,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  124,   -1,   -1,  262,  263,  264,  265,  266,   -1,
   93,   94,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  321,  322,  323,  324,  325,  326,
  327,   -1,   -1,  262,  263,  264,  265,  266,   -1,   -1,
   -1,  124,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  321,  322,  323,  324,  325,  326,  327,
   -1,   -1,  262,  263,  264,  265,  266,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  321,  322,  323,  324,  325,  326,  327,   -1,
   -1,  262,  263,  264,  265,  266,   -1,   -1,   -1,   -1,
  407,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   10,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  321,  322,  323,  324,  325,  326,  327,   -1,  262,
  263,  264,  265,  266,   -1,   -1,   -1,   -1,   -1,  407,
   38,   -1,   40,   41,   -1,   43,   44,   45,   -1,   -1,
  321,  322,  323,  324,  325,  326,  327,   -1,   -1,   -1,
   58,   -1,   60,   61,   62,   63,   -1,   -1,  407,  262,
  263,  264,  265,  266,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   10,  321,  322,
  323,  324,  325,  326,  327,   93,   94,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  407,   -1,   -1,
   -1,   -1,   -1,   10,   37,   38,   -1,   40,   41,   42,
   43,   44,   45,   -1,   47,   10,  124,   -1,  321,  322,
  323,  324,  325,  326,  327,   58,  407,   60,   61,   62,
   63,   38,   -1,   40,   41,   -1,   43,   44,   45,   -1,
   -1,   -1,   -1,   38,   -1,   40,   41,   -1,   -1,   44,
   -1,   58,   -1,   60,   61,   62,   63,   -1,   -1,   -1,
   93,   94,   -1,   58,  407,   60,   61,   62,   63,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   10,   -1,   -1,   -1,   93,   94,   -1,   -1,
   10,  124,   -1,   -1,   -1,   -1,   -1,   -1,   93,   94,
   -1,   -1,   -1,   -1,  407,   -1,   -1,   -1,   -1,   -1,
   38,   -1,   40,   41,   -1,   -1,   44,  124,   38,   -1,
   40,   41,   -1,   -1,   44,   -1,   -1,   -1,   -1,  124,
   58,   -1,   60,   61,   62,   63,   -1,   -1,   58,   -1,
   60,   61,   62,   63,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  262,  263,  264,  265,  266,   -1,
   -1,   -1,   -1,   -1,   -1,   93,   94,   -1,   -1,   -1,
   -1,   -1,   -1,   93,   94,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   10,   -1,   -1,   -1,  124,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  124,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  321,  322,  323,  324,  325,  326,  327,
   38,   -1,   40,   41,   -1,   -1,   44,   -1,   -1,  262,
  263,  264,  265,  266,   -1,   -1,   -1,   -1,   -1,   -1,
   58,   -1,   60,   61,   62,   63,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  262,  263,  264,  265,  266,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  262,  263,  264,
  265,  266,   -1,   -1,   -1,   93,   94,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  321,  322,
  323,  324,  325,  326,  327,   -1,   -1,   -1,   -1,  407,
   -1,   -1,   -1,   -1,   -1,   -1,  124,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  321,  322,  323,  324,  325,  326,
  327,   -1,   -1,   -1,   -1,   10,  321,  322,  323,  324,
  325,  326,  327,   -1,  262,  263,  264,  265,  266,   -1,
   -1,   -1,  262,  263,  264,  265,  266,   -1,   -1,   -1,
   -1,   -1,   -1,   38,   -1,   40,   41,   -1,   -1,   44,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   58,  407,   60,   61,   62,   63,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  321,  322,  323,  324,  325,  326,  327,
  407,   10,   -1,  323,  324,  325,  326,  327,   93,   94,
   -1,   -1,  407,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   38,
   10,   40,   41,   -1,   -1,   44,   -1,   -1,   10,  124,
   -1,   -1,   -1,   -1,  262,  263,  264,  265,  266,   58,
   -1,   60,   61,   62,   63,   -1,   -1,   -1,   38,   -1,
   40,   41,   -1,   -1,   44,   -1,   38,   -1,   40,   41,
   -1,   -1,   44,   -1,   -1,   -1,   -1,   -1,   58,  407,
   60,   61,   62,   63,   93,   94,   58,  407,   60,   61,
   62,   63,   -1,   10,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  323,  324,  325,  326,  327,
   -1,   -1,   -1,   93,   94,  124,   33,   -1,   -1,   36,
   10,   93,   94,   40,   -1,   -1,   43,   -1,   45,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  124,   -1,   -1,   -1,   38,   -1,
   40,   41,  124,   -1,   44,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   58,   -1,
   -1,   61,   -1,   63,   91,   -1,   -1,  262,  263,  264,
  265,  266,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  407,
   -1,   -1,   -1,   -1,   -1,   -1,   10,   -1,   -1,   -1,
   -1,   -1,   -1,   93,   94,   -1,   -1,   -1,   33,  126,
   -1,   36,   -1,   -1,   -1,   40,   -1,   -1,   43,   -1,
   45,   -1,   -1,   -1,   38,   -1,   40,   41,   -1,   -1,
   44,   -1,   -1,   -1,  124,   -1,   -1,   -1,  323,  324,
  325,  326,  327,   -1,   58,   -1,   -1,   61,   -1,   63,
   -1,   -1,   -1,  262,  263,  264,  265,  266,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   91,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   93,
   94,   -1,  262,  263,  264,  265,  266,   -1,   -1,   -1,
  262,  263,  264,  265,  266,   -1,   -1,   -1,   -1,   -1,
   -1,  126,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  124,   -1,   -1,   -1,  323,  324,  325,  326,  327,   -1,
   -1,   -1,  407,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   10,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  323,  324,  325,  326,  327,   -1,   -1,
   -1,  323,  324,  325,  326,  327,   -1,   -1,   -1,   -1,
   37,   38,   -1,   -1,   -1,   42,   43,   -1,   45,   -1,
   47,   -1,  262,  263,  264,  265,  266,   -1,   -1,  296,
  297,   58,   -1,   -1,   61,  302,  303,  304,   -1,  306,
  307,  308,   -1,   -1,   -1,   -1,   -1,   -1,  407,  316,
  317,  318,  319,  320,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  329,  330,   -1,   -1,   -1,   94,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  407,   -1,  346,
  347,  348,   -1,   -1,  324,  407,   -1,  327,   -1,   -1,
   -1,   -1,   -1,   -1,  361,   -1,   -1,  124,  262,  263,
  264,  265,  266,   -1,   -1,   -1,   -1,   -1,  283,  284,
  285,  286,  287,  288,  289,   -1,   -1,  292,  293,   -1,
   -1,  296,  297,   -1,   -1,   -1,   -1,  302,  303,  304,
   10,  306,  307,  308,   -1,   -1,   -1,   -1,  405,   -1,
   -1,  316,  317,  318,  319,  320,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  329,  330,   -1,   -1,   -1,   -1,
  324,   -1,   -1,  327,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  346,  347,  348,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   61,   -1,   -1,   -1,   -1,  361,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  405,  258,  259,  260,  261,  262,  263,  264,  265,  266,
  267,  268,  269,  270,  271,  272,  273,  274,  275,  276,
  277,  278,  279,  280,  281,  282,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  298,  299,  300,  301,   -1,   -1,   10,  305,   -1,
   -1,   -1,  309,  310,  311,  312,  313,  314,  315,   -1,
   -1,   -1,   -1,   -1,  321,  322,   -1,   -1,   -1,   -1,
   -1,   -1,  329,  330,  331,  332,  333,  334,  335,  336,
   -1,   -1,   -1,   -1,   -1,   -1,  343,  344,  345,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  354,   61,  356,
   -1,  358,   -1,  360,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  370,  371,  372,  373,  374,  375,  376,
  377,  378,  379,  380,  381,   -1,  383,  384,  385,  386,
   -1,   -1,   -1,  390,  391,  392,  393,  394,  395,  396,
  397,  398,  399,  400,  401,  402,  403,  404,  258,  259,
  260,  261,  262,  263,  264,   -1,   -1,  267,  268,  269,
  270,  271,  272,  273,  274,  275,  276,  277,  278,  279,
  280,  281,  282,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  298,  299,
  300,  301,   -1,   -1,   10,  305,   -1,   -1,   -1,  309,
  310,  311,  312,  313,  314,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  354,   -1,   -1,   -1,  358,   -1,
  360,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  370,  371,  372,  373,  374,  375,  376,  377,  378,  379,
  380,  381,   -1,  383,  384,  385,  386,   -1,   -1,   -1,
  390,  391,  392,  393,  394,  395,  396,  397,  398,  399,
  400,  401,  402,  403,  404,  258,  259,  260,  261,  262,
  263,  264,   -1,   -1,  267,  268,  269,  270,  271,  272,
  273,  274,  275,  276,  277,  278,  279,  280,  281,  282,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  298,  299,  300,  301,   -1,
   -1,   10,  305,   -1,   -1,   -1,  309,  310,  311,  312,
  313,  314,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  354,   -1,   -1,   -1,  358,   -1,  360,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  370,  371,  372,
  373,  374,  375,  376,  377,  378,  379,  380,  381,   -1,
  383,  384,  385,  386,   -1,   -1,   -1,  390,  391,  392,
  393,  394,  395,  396,  397,  398,  399,  400,  401,  402,
  403,  404,  258,  259,  260,  261,  262,  263,  264,   -1,
   -1,  267,  268,  269,  270,  271,  272,  273,  274,  275,
  276,  277,  278,  279,  280,  281,  282,   37,   38,   -1,
   -1,   -1,   42,   43,   -1,   45,   -1,   47,   -1,   -1,
   -1,   -1,  298,  299,  300,  301,   -1,   -1,   -1,  305,
   60,   61,   62,  309,  310,  311,  312,  313,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   94,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  354,   -1,
   -1,   -1,  358,   -1,  360,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  370,  371,  372,  373,  374,  375,
  376,  377,  378,  379,  380,  381,   -1,  383,  384,  385,
  386,   -1,   -1,   -1,  390,  391,  392,  393,  394,  395,
  396,  397,  398,  399,  400,  401,  402,  403,  404,  258,
  259,  260,  261,  262,  263,  264,   -1,   -1,  267,  268,
  269,  270,  271,  272,  273,  274,  275,  276,  277,  278,
  279,  280,  281,  282,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  298,
  299,  300,  301,   -1,   -1,   -1,  305,   -1,   -1,   -1,
  309,  310,  311,  312,  313,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   33,   -1,   -1,   36,   -1,
   -1,   -1,   40,   -1,   -1,   43,   -1,   45,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  354,   -1,   -1,   -1,  358,
   -1,  360,  262,   -1,  264,   -1,   -1,   -1,   -1,   -1,
   -1,  370,  371,  372,  373,  374,  375,  376,  377,  378,
  379,  380,  381,   91,  383,  384,  385,  386,   -1,   -1,
   -1,  390,  391,  392,  393,  394,  395,  396,  397,  398,
  399,  400,  401,  402,  403,  404,   -1,   33,   -1,   -1,
   36,   -1,   -1,   -1,   40,   -1,   -1,   43,  126,   45,
   -1,  321,  322,  323,  324,  325,  326,  327,   -1,  329,
  330,  331,  332,  333,  334,  335,  336,  337,  338,  339,
  340,  341,  342,  343,  344,  345,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   33,   -1,   91,   36,   -1,   -1,   -1,
   40,   -1,   -1,   43,   -1,   45,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  126,   -1,   -1,   -1,   -1,   -1,   -1,  407,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   91,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   33,   -1,   -1,   36,   -1,   -1,   -1,   40,
   -1,   -1,   43,   -1,   45,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  126,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  283,  284,  285,  286,  287,
  288,  289,   -1,   -1,  292,   -1,   -1,   -1,  296,  297,
   91,   -1,   -1,   -1,  302,  303,  304,   -1,  306,  307,
  308,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  316,  317,
  318,  319,  320,   -1,   -1,   -1,   33,   -1,   -1,   36,
   -1,  329,  330,   40,   -1,  126,   43,   -1,   45,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  346,  347,
  348,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  361,   -1,   -1,   -1,  283,  284,  285,
  286,   -1,  288,  289,   -1,   -1,   -1,   -1,  294,   -1,
  296,  297,   -1,   -1,   91,   -1,  302,  303,  304,   -1,
  306,  307,  308,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  316,  317,  318,  319,  320,   33,   -1,  405,   36,   -1,
   -1,   -1,   40,  329,  330,   43,   -1,   45,   -1,  126,
   -1,   -1,   -1,  283,  284,  285,  286,   -1,  288,   -1,
  346,  347,  348,   -1,  294,   -1,  296,  297,   -1,   -1,
   -1,   -1,  302,  303,  304,  361,  306,  307,  308,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  316,  317,  318,  319,
  320,   33,   -1,   91,   36,   -1,   -1,   -1,   40,  329,
  330,   43,   -1,   45,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  346,  347,  348,  405,
   -1,   -1,  283,  284,  285,  286,   -1,   -1,  126,   -1,
   -1,  361,   -1,  294,   -1,  296,  297,   -1,   -1,   -1,
   -1,  302,  303,  304,   -1,  306,  307,  308,   -1,   91,
   -1,   -1,   -1,   -1,   -1,  316,  317,  318,  319,  320,
   -1,   -1,   -1,   -1,   33,   -1,   -1,   36,  329,  330,
   -1,   40,   -1,   -1,   43,  405,   45,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  126,  346,  347,  348,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  361,   -1,   -1,   -1,   -1,   -1,  283,  284,  285,  286,
   -1,   -1,   -1,   -1,   -1,   -1,  293,   -1,   -1,  296,
  297,   -1,   91,   -1,   -1,  302,  303,  304,   -1,  306,
  307,  308,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  316,
  317,  318,  319,  320,  405,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  329,  330,   -1,   -1,   -1,  126,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  346,
  347,  348,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  361,  283,  284,  285,  286,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  296,  297,
   -1,   -1,   -1,   -1,  302,  303,  304,   -1,  306,  307,
  308,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  316,  317,
  318,  319,  320,   -1,   -1,   -1,   -1,   -1,  405,   -1,
   -1,  329,  330,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  283,  284,  285,  286,   -1,   -1,   -1,  346,  347,
  348,   -1,   -1,   -1,  296,  297,   -1,   -1,   -1,   -1,
  302,  303,  304,  361,  306,  307,  308,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  316,  317,  318,  319,  320,   -1,
   -1,   -1,   -1,   33,   -1,   -1,   36,  329,  330,   -1,
   40,   -1,   -1,   43,   -1,   45,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  346,  347,  348,  405,   -1,   -1,
   -1,   -1,   -1,   -1,  283,  284,  285,  286,   -1,  361,
   70,   -1,   -1,   -1,   -1,   -1,   -1,  296,  297,   -1,
   -1,   -1,   -1,  302,  303,  304,   -1,  306,  307,  308,
   -1,   91,   -1,   -1,   -1,   -1,   -1,  316,  317,  318,
  319,  320,   33,   -1,   -1,   36,   -1,   -1,   -1,   40,
  329,  330,   43,  405,   45,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  126,  346,  347,  348,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   10,  361,   -1,   -1,   -1,   -1,   -1,   -1,   33,
   -1,   -1,   36,   -1,   -1,   -1,   40,   -1,   -1,   43,
   91,   45,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   38,
   -1,   40,   41,   -1,   -1,   44,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  405,   -1,   -1,   58,
   -1,   -1,   61,   -1,   63,  126,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   91,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   33,   -1,   -1,   36,
   -1,   -1,   -1,   40,   93,   94,   43,   -1,   45,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  126,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  124,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   33,   -1,   -1,   36,   -1,   -1,   -1,
   40,   -1,   -1,   43,   91,   45,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  283,   -1,  285,  286,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  296,  297,   -1,   -1,
   -1,   -1,  302,  303,  304,   -1,  306,  307,  308,  126,
   -1,   -1,   -1,   -1,   -1,   -1,  316,  317,  318,  319,
  320,   91,   -1,   -1,   -1,   -1,   37,   38,   -1,  329,
  330,   42,   43,   -1,   45,   -1,   47,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  346,  347,  348,   60,
   61,   62,  283,  284,  285,  286,  126,   -1,   -1,   -1,
   -1,  361,   -1,   -1,   -1,  296,  297,   -1,   -1,   -1,
   -1,  302,  303,  304,   -1,  306,  307,  308,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  316,  317,  318,  319,  320,
   -1,   -1,   -1,  262,  263,  264,  265,  266,  329,  330,
   -1,   -1,  286,   -1,   -1,  405,   -1,   -1,   -1,   -1,
  294,  295,  296,  297,   -1,  346,  347,  348,  302,  303,
  304,   -1,  306,  307,  308,   -1,   -1,   -1,   -1,   -1,
  361,   -1,  316,  317,  318,  319,  320,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  329,  330,   33,   -1,   -1,
   36,   -1,   -1,   -1,   40,  324,   -1,   43,  327,   45,
   -1,   -1,  346,  347,  348,   -1,  283,   -1,  285,  286,
   -1,   -1,   -1,   -1,  405,   -1,   -1,  361,   -1,  296,
  297,   -1,   -1,   -1,   -1,  302,  303,  304,   -1,  306,
  307,  308,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  316,
  317,  318,  319,  320,   -1,   91,   -1,   -1,   33,   -1,
   -1,   36,  329,  330,   -1,   40,  286,   -1,   43,   -1,
   45,  405,   -1,   -1,  294,  295,  296,  297,   -1,  346,
  347,  348,  302,  303,  304,   -1,  306,  307,  308,   -1,
  126,   -1,   -1,   -1,  361,   -1,  316,  317,  318,  319,
  320,  262,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  329,
  330,   -1,   -1,   -1,   -1,   -1,   91,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  346,  347,  348,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   33,   -1,  405,   36,
   -1,  361,   -1,   40,   -1,   -1,   43,   -1,   45,   -1,
   -1,  126,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  321,  322,  323,  324,  325,  326,  327,   -1,  329,  330,
  331,  332,  333,  334,  335,  336,  337,  338,  339,  340,
  341,  342,  343,  344,  345,  405,   -1,   -1,   -1,   -1,
   -1,   -1,   33,   -1,   91,   36,   -1,   -1,   -1,   40,
   -1,   -1,   43,   -1,   45,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  126,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  407,   -1,   -1,   -1,
   91,  287,  288,  289,   -1,   -1,   -1,   -1,   -1,   -1,
  296,  297,   -1,   -1,   -1,   -1,  302,  303,  304,   -1,
  306,  307,  308,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  316,  317,  318,  319,  320,  126,   -1,   -1,   33,   -1,
   -1,   36,   -1,  329,  330,   40,   -1,   -1,   43,   -1,
   45,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  346,  347,  348,  288,  289,   -1,   -1,   -1,   -1,   -1,
   -1,  296,  297,   -1,   -1,  361,   -1,  302,  303,  304,
   -1,  306,  307,  308,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  316,  317,  318,  319,  320,   91,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  329,  330,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   33,   -1,  405,
   36,  346,  347,  348,   40,   -1,   -1,   43,   -1,   45,
   -1,  126,   -1,   -1,   -1,   -1,  361,  362,   -1,   -1,
  287,  288,  289,   -1,   -1,   -1,   -1,   -1,   -1,  296,
  297,   -1,   -1,   -1,   -1,  302,  303,  304,   -1,  306,
  307,  308,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  316,
  317,  318,  319,  320,   -1,   91,   -1,   -1,   33,   -1,
  405,   36,  329,  330,   -1,   40,   -1,   -1,   43,   -1,
   45,   -1,  283,   -1,  285,  286,   -1,   -1,   -1,  346,
  347,  348,   -1,   -1,   -1,  296,  297,   -1,   -1,   -1,
  126,  302,  303,  304,  361,  306,  307,  308,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  316,  317,  318,  319,  320,
   -1,   -1,   -1,   -1,   33,   -1,   91,   36,  329,  330,
   -1,   40,   -1,   -1,   43,   -1,   45,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  346,  347,  348,  405,   37,
   38,   -1,  257,   -1,   42,   43,   -1,   45,   -1,   47,
  361,  126,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   58,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   91,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  296,  297,   -1,   -1,   -1,   -1,  302,  303,  304,
   -1,  306,  307,  308,  405,   -1,   94,   -1,   -1,   -1,
   -1,  316,  317,  318,  319,  320,   33,  126,   -1,   36,
   -1,   -1,   -1,   40,  329,  330,   43,   -1,   45,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  124,   -1,   -1,   -1,
   -1,  346,  347,  348,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   33,   -1,   -1,   36,  361,  362,   -1,   40,
  286,   -1,   43,   -1,   45,   -1,   -1,   -1,   -1,  295,
  296,  297,   -1,   -1,   91,   -1,  302,  303,  304,   -1,
  306,  307,  308,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  316,  317,  318,  319,  320,   -1,   -1,   -1,   -1,   -1,
  405,   -1,   -1,  329,  330,   -1,   -1,   -1,   -1,  126,
   91,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  346,  347,  348,  288,  289,   -1,   -1,   -1,   -1,   -1,
   -1,  296,  297,   -1,   -1,  361,   -1,  302,  303,  304,
   -1,  306,  307,  308,   -1,  126,   -1,   -1,  257,   -1,
   -1,  316,  317,  318,  319,  320,   33,   -1,   -1,   36,
   -1,   -1,   -1,   40,  329,  330,   43,   -1,   45,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  265,  266,  405,
   -1,  346,  347,  348,   -1,   -1,   -1,  296,  297,   -1,
   -1,   -1,   -1,  302,  303,  304,  361,  306,  307,  308,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  316,  317,  318,
  319,  320,   -1,   -1,   91,   -1,   33,   -1,   -1,   36,
  329,  330,   -1,   40,   41,   -1,   43,  315,   45,   -1,
   -1,   -1,   -1,  321,  322,   -1,   -1,  346,  347,  348,
  405,  329,  330,  331,  332,  333,  334,  335,  336,  126,
   -1,   -1,  361,  362,   -1,  343,  344,  345,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  356,   -1,
   -1,  288,  289,   -1,   91,   -1,   -1,   -1,   -1,  296,
  297,   -1,   -1,   -1,   -1,  302,  303,  304,   -1,  306,
  307,  308,   -1,   -1,   -1,   -1,  405,   -1,   -1,  316,
  317,  318,  319,  320,   -1,  286,   -1,   -1,   -1,  126,
   -1,   -1,  329,  330,   -1,  296,  297,   -1,   -1,   -1,
   -1,  302,  303,  304,   -1,  306,  307,  308,   -1,  346,
  347,  348,   -1,   -1,   -1,  316,  317,  318,  319,  320,
   33,   -1,   -1,   36,  361,   -1,   -1,   40,  329,  330,
   43,   -1,   45,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  346,  347,  348,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  361,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  405,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   91,   -1,
   -1,   -1,   -1,   33,   -1,   -1,   36,   -1,   -1,  286,
   40,   -1,   -1,   43,   -1,   45,   -1,   -1,   -1,  296,
  297,   -1,   -1,   -1,  405,  302,  303,  304,   -1,  306,
  307,  308,   -1,  126,   -1,   -1,   -1,   -1,   -1,  316,
  317,  318,  319,  320,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  329,  330,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   91,   -1,   -1,   -1,   33,   -1,   -1,   36,  346,
  347,  348,   40,   -1,   -1,   43,   -1,   45,   -1,  296,
  297,   -1,   -1,   -1,  361,  302,  303,  304,   -1,  306,
  307,  308,   -1,   -1,   -1,   -1,  126,   -1,   -1,  316,
  317,  318,  319,  320,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  329,  330,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   91,   -1,   -1,   -1,   -1,  405,  346,
  347,  348,   -1,   -1,   -1,   33,   -1,   -1,   36,   -1,
   -1,   -1,   40,   -1,  361,   43,   -1,   45,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  126,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   33,   -1,   -1,   36,   -1,   -1,   -1,   40,   -1,
   -1,   43,   -1,   45,   -1,   -1,   -1,   -1,  405,   -1,
   -1,   -1,   -1,   91,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  296,  297,   -1,   -1,   -1,   -1,  302,
  303,  304,   -1,  306,  307,  308,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  316,  317,  318,  319,  320,  126,   91,
   -1,   -1,   -1,   -1,   -1,   -1,  329,  330,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  346,  347,  348,  286,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  126,   -1,  296,  297,  361,  362,
   -1,   -1,  302,  303,  304,   -1,  306,  307,  308,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  316,  317,  318,  319,
  320,   -1,   -1,   -1,   -1,   -1,   -1,   37,   38,  329,
  330,   41,   42,   43,   -1,   45,   -1,   47,   -1,   -1,
   -1,   -1,  405,   -1,   -1,   -1,  346,  347,  348,   -1,
   60,   61,   62,   63,   -1,   -1,   -1,   -1,  296,  297,
   -1,  361,   -1,   -1,  302,  303,  304,   -1,  306,  307,
  308,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  316,  317,
  318,  319,  320,   -1,   94,   -1,   -1,   -1,   -1,   -1,
   -1,  329,  330,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  405,   -1,   -1,  346,  347,
  348,   -1,   -1,   -1,  124,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  361,   -1,   -1,   -1,   -1,  296,  297,
   -1,   -1,   -1,   -1,  302,  303,  304,   -1,  306,  307,
  308,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  316,  317,
  318,  319,  320,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  329,  330,   -1,  296,  297,   -1,  405,   -1,   -1,
  302,  303,  304,   -1,  306,  307,  308,   -1,  346,  347,
  348,   -1,   -1,   -1,  316,  317,  318,  319,  320,   -1,
   -1,   -1,   -1,  361,   37,   38,   -1,  329,  330,   42,
   43,   -1,   45,   -1,   47,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  346,  347,  348,   60,   61,   62,
   63,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  361,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  405,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   93,   94,  262,  263,  264,  265,  266,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  405,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  124,   37,   38,   -1,   -1,   -1,   42,   43,   44,
   45,   -1,   47,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   60,   61,   62,   63,   -1,
   -1,  321,  322,  323,  324,  325,  326,  327,   -1,  329,
  330,  331,  332,  333,  334,  335,  336,  337,  338,  339,
  340,  341,  342,  343,  344,  345,   -1,   -1,   -1,   94,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  124,
   37,   38,   -1,   -1,   -1,   42,   43,   44,   45,   -1,
   47,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   60,   61,   62,   63,  407,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  262,
  263,  264,  265,  266,   -1,   -1,   -1,   94,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  124,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  321,  322,
  323,  324,  325,  326,  327,   -1,  329,  330,  331,  332,
  333,  334,  335,  336,  337,  338,  339,  340,  341,  342,
  343,  344,  345,   -1,   -1,   -1,   -1,  262,  263,  264,
  265,  266,   -1,   -1,   -1,   -1,   37,   38,   -1,   -1,
   -1,   42,   43,   -1,   45,   -1,   47,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   58,   -1,   60,
   61,   62,   63,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  407,   -1,  321,  322,  323,  324,
  325,  326,  327,   94,  329,  330,  331,  332,  333,  334,
  335,  336,  337,  338,  339,  340,  341,  342,  343,  344,
  345,   -1,   -1,   -1,   -1,  262,  263,  264,  265,  266,
   -1,   -1,   -1,  124,   37,   38,   -1,   -1,   -1,   42,
   43,   44,   45,   -1,   47,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   60,   61,   62,
   63,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  407,   -1,  321,  322,  323,  324,  325,  326,
  327,   94,  329,  330,  331,  332,  333,  334,  335,  336,
  337,  338,  339,  340,  341,  342,  343,  344,  345,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  124,   37,   38,   -1,   -1,   -1,   42,   43,   44,
   45,   -1,   47,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   60,   61,   62,   63,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  407,  262,  263,  264,  265,  266,   -1,   -1,   -1,   94,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  124,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  321,  322,  323,  324,  325,  326,  327,   -1,  329,  330,
  331,  332,  333,  334,  335,  336,  337,  338,  339,  340,
  341,  342,  343,  344,  345,   -1,   -1,   -1,   -1,  262,
  263,  264,  265,  266,   -1,   -1,   -1,   -1,   37,   38,
   -1,   -1,   -1,   42,   43,   44,   45,   -1,   47,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   60,   61,   62,   63,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  407,   -1,  321,  322,
  323,  324,  325,  326,  327,   94,  329,  330,  331,  332,
  333,  334,  335,  336,  337,  338,  339,  340,  341,  342,
  343,  344,  345,   -1,   -1,   -1,   -1,  262,  263,  264,
  265,  266,   -1,   -1,   -1,  124,   37,   38,   -1,   -1,
   -1,   42,   43,   44,   45,   -1,   47,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   60,
   61,   62,   63,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  407,   -1,  321,  322,  323,  324,
  325,  326,  327,   94,  329,  330,  331,  332,  333,  334,
  335,  336,  337,  338,  339,  340,  341,  342,  343,  344,
  345,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  124,   37,   38,   -1,   40,   -1,   42,
   43,   -1,   45,   -1,   47,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   60,   61,   62,
   63,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  407,  262,  263,  264,  265,  266,   -1,   -1,
   -1,   94,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  124,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  321,  322,  323,  324,  325,  326,  327,   -1,
  329,  330,  331,  332,  333,  334,  335,  336,  337,  338,
  339,  340,  341,  342,  343,  344,  345,   -1,   -1,   -1,
   -1,  262,  263,  264,  265,  266,   -1,   -1,   -1,   -1,
   37,   38,   -1,   -1,   -1,   42,   43,   -1,   45,   -1,
   47,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   60,   61,   62,   63,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  407,   -1,
  321,  322,  323,  324,  325,  326,  327,   94,  329,  330,
  331,  332,  333,  334,  335,  336,  337,  338,  339,  340,
  341,  342,  343,  344,  345,   -1,   -1,   -1,   -1,  262,
  263,  264,  265,  266,   -1,   -1,   -1,  124,   37,   38,
   -1,   -1,   -1,   42,   43,   -1,   45,   -1,   47,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   60,   61,   62,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  407,   -1,  321,  322,
  323,  324,  325,  326,  327,   94,  329,  330,  331,  332,
  333,  334,  335,  336,  337,  338,  339,  340,  341,  342,
  343,  344,  345,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  124,   37,   38,   -1,   -1,
   -1,   42,   43,   -1,   45,   -1,   47,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   60,
   61,   62,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  407,  262,  263,  264,  265,  266,
   -1,   -1,   -1,   94,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  124,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  321,  322,  323,  324,  325,  326,
  327,   -1,  329,  330,  331,  332,  333,  334,  335,  336,
  337,  338,  339,  340,  341,  342,  343,  344,  345,   -1,
   -1,   -1,   -1,  262,  263,  264,  265,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  407,   -1,  321,  322,  323,  324,  325,  326,  327,   -1,
  329,  330,  331,  332,  333,  334,  335,  336,  337,  338,
  339,  340,  341,  342,  343,  344,  345,   -1,   -1,   -1,
   -1,  262,  263,  264,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  407,   -1,
  321,  322,  323,  324,  325,  326,  327,   -1,  329,  330,
  331,  332,  333,  334,  335,  336,  337,  338,  339,  340,
  341,  342,  343,  344,  345,  258,  259,  260,  261,  262,
  263,  264,   -1,   -1,  267,  268,  269,  270,  271,  272,
  273,  274,  275,  276,  277,  278,  279,  280,  281,  282,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  299,  300,  301,   -1,
   -1,   -1,  305,   -1,   -1,   -1,   -1,  310,  311,   -1,
  313,   -1,   -1,   -1,   -1,   -1,  407,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  360,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  370,  371,  372,
  373,  374,  375,  376,  377,  378,  379,  380,  381,   -1,
  383,  384,  385,  386,   -1,   -1,   -1,  390,  391,  392,
  393,  394,  395,  396,  397,  398,  399,  400,  258,  259,
  260,  261,  262,  263,  264,   -1,   -1,  267,  268,  269,
  270,  271,  272,  273,  274,  275,  276,  277,  278,  279,
  280,  281,  282,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  299,
  300,  301,   -1,   -1,   -1,  305,   -1,   -1,   -1,   -1,
  310,  311,   -1,  313,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  360,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  370,  371,  372,  373,  374,  375,  376,  377,  378,  379,
  380,  381,   -1,  383,  384,  385,  386,   -1,   -1,   -1,
  390,  391,  392,  393,  394,  395,  396,  397,  398,  399,
  400,
};
#define YYFINAL 1
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 408
#define YYUNDFTOKEN 481
#define YYTRANSLATE(a) ((a) > YYMAXTOKEN ? YYUNDFTOKEN : (a))
#if YYDEBUG
static const char *const yyname[] = {

"end-of-file",0,0,0,0,0,0,0,0,0,"'\\n'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,"'!'",0,"'#'","'$'","'%'","'&'",0,"'('","')'","'*'","'+'","','","'-'",0,
"'/'",0,0,0,0,0,0,0,0,0,0,"':'",0,"'<'","'='","'>'","'?'",0,0,0,0,0,0,"'F'",0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"'['",0,"']'","'^'",0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"'|'",0,"'~'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"STRING",
"NOOPERAND","ARITHC","ADD","LOGICAL","AND","OR","XOR","ANDAND","OROR","BIT",
"CALL","INCDEC","DJNZ","EX","IM","PHASE","DEPHASE","TK_IN","JR","LD","TK_OUT",
"PUSHPOP","RET","SHIFT","RST","REGNAME","IXYLH","ACC","TK_C","RP","HL","INDEX",
"AF","AFp","SP","MISCREG","COND","SPCOND","NUMBER","UNDECLARED","END","ORG",
"ASSERT","TSTATE","T","TILO","TIHI","SETOCF","OCF","LOW","HIGH","DC","DEFB",
"DEFD","DEFS","DEFW","EQU","DEFL","LABEL","EQUATED","WASEQUATED","DEFLED",
"MULTDEF","SHL","SHR","LT","EQ","LE","GE","NE","NOT","MROP_ADD","MROP_SUB",
"MROP_MUL","MROP_DIV","MROP_MOD","MROP_AND","MROP_OR","MROP_XOR","MROP_NE",
"MROP_EQ","MROP_LT","MROP_GT","MROP_LE","MROP_GE","MROP_SHIFT","MROP_SHL",
"MROP_SHR","MROP_NOT","MROP_LOW","MROP_HIGH","IF_TK","IF_DEF_TK","ELSE_TK",
"ENDIF_TK","ARGPSEUDO","INCBIN","LIST","MINMAX","MACRO","MNAME","ARG","ENDM",
"ONECHAR","TWOCHAR","JRPROMOTE","JPERROR","PUBLIC","EXTRN","MRAS_MOD","SETSEG",
"INSTSET","LXI","DAD","STAX","STA","SHLD","LDAX","LHLD","LDA","MVI","MOV",
"INXDCX","INRDCR","PSW","JUMP8","JP","CALL8","ALUI8","SPECIAL","RAWTOKEN",
"LOCAL","LD_XY","ST_XY","MV_XY","ALU_XY","BIT_XY","SHIFT_XY","INP","OUTP",
"JR_COND","LDST16","ARITH16","REPT","IRPC","IRP","EXITM","NUL","MPARM","GT",
"UNARY",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
"illegal-symbol",
};
static const char *const yyrule[] = {
"$accept : statements",
"statements :",
"statements : statements statement",
"statement : label.part '\\n'",
"$$1 :",
"statement : label.part $$1 operation '\\n'",
"statement : symbol maybecolon EQU expression '\\n'",
"statement : symbol maybecolon '=' expression '\\n'",
"statement : symbol DEFL expression '\\n'",
"statement : symbol varop '=' expression '\\n'",
"statement : symbol '+' '+' '\\n'",
"statement : symbol '-' '-' '\\n'",
"statement : symbol MINMAX expression ',' expression '\\n'",
"statement : IF_TK expression '\\n'",
"statement : IF_DEF_TK arg_on ARG arg_off '\\n'",
"statement : ELSE_TK '\\n'",
"statement : ENDIF_TK '\\n'",
"statement : label.part END '\\n'",
"statement : label.part END expression '\\n'",
"statement : label.part DEFS expression '\\n'",
"statement : label.part DEFS expression ',' expression '\\n'",
"statement : label.part DC ONECHAR '\\n'",
"statement : label.part DC TWOCHAR '\\n'",
"statement : label.part DC STRING '\\n'",
"statement : label.part DC expression ',' expression '\\n'",
"statement : ARGPSEUDO arg_on ARG arg_off '\\n'",
"statement : ARGPSEUDO arg_on arg_off '\\n'",
"statement : label.part INCBIN arg_on ARG arg_off '\\n'",
"$$2 :",
"statement : SPECIAL $$2 RAWTOKEN",
"statement : LIST '\\n'",
"statement : LIST mras_undecl_on expression mras_undecl_off '\\n'",
"statement : JRPROMOTE expression '\\n'",
"statement : JPERROR expression '\\n'",
"statement : PUBLIC public.list '\\n'",
"statement : EXTRN extrn.list '\\n'",
"statement : MRAS_MOD '\\n'",
"statement : SETSEG '\\n'",
"statement : INSTSET '\\n'",
"$$3 :",
"$$4 :",
"statement : UNDECLARED MACRO $$3 parm.list '\\n' $$4 locals",
"$$5 :",
"statement : label.part MNAME al $$5 arg.list '\\n'",
"$$6 :",
"statement : label.part REPT expression al '\\n' $$6 locals",
"$$7 :",
"$$8 :",
"statement : label.part IRPC parm.single ',' $$7 al arg.element arg_off '\\n' $$8 locals",
"$$9 :",
"$$10 :",
"statement : label.part IRP parm.single ',' $$9 al arg.element arg_off '\\n' $$10 locals",
"statement : label.part EXITM '\\n'",
"statement : error",
"maybecolon :",
"maybecolon : ':'",
"maybecolon : ':' ':'",
"label.part :",
"label.part : symbol maybecolon",
"public.list : public.part",
"public.list : public.list ',' public.part",
"public.part : symbol",
"extrn.list : extrn.part",
"extrn.list : extrn.list ',' extrn.part",
"extrn.part : symbol",
"varop : '+'",
"varop : '-'",
"varop : '*'",
"varop : '/'",
"varop : '%'",
"varop : '&'",
"varop : '|'",
"varop : '^'",
"varop : ANDAND",
"varop : OROR",
"varop : SHL",
"varop : SHR",
"varop : MROP_ADD",
"varop : MROP_SUB",
"varop : MROP_MUL",
"varop : MROP_DIV",
"varop : MROP_MOD",
"varop : MROP_AND",
"varop : MROP_OR",
"varop : MROP_XOR",
"varop : MROP_SHL",
"varop : MROP_SHR",
"varop : MROP_SHIFT",
"operation : NOOPERAND",
"operation : NOOPERAND expression",
"operation : SHIFT",
"operation : JP expression",
"operation : CALL expression",
"operation : RST expression",
"operation : ALUI8 expression",
"operation : ALU_XY dxy",
"operation : ADD expression",
"operation : ADD ACC ',' expression",
"operation : ARITHC expression",
"operation : ARITHC ACC ',' expression",
"operation : LOGICAL expression",
"operation : AND expression",
"operation : OR expression",
"operation : XOR expression",
"operation : LOGICAL ACC ',' expression",
"operation : AND ACC ',' expression",
"operation : OR ACC ',' expression",
"operation : XOR ACC ',' expression",
"operation : ADD allreg",
"operation : ADD ACC ',' allreg",
"operation : ADD m",
"operation : ARITHC allreg",
"operation : ARITHC ACC ',' allreg",
"operation : ARITHC m",
"operation : LOGICAL allreg",
"operation : LOGICAL m",
"operation : AND allreg",
"operation : OR allreg",
"operation : XOR allreg",
"operation : LOGICAL ACC ',' allreg",
"operation : AND ACC ',' allreg",
"operation : OR ACC ',' allreg",
"operation : XOR ACC ',' allreg",
"operation : SHIFT reg",
"operation : SHIFT_XY dxy",
"operation : SHIFT memxy ',' realreg",
"operation : INCDEC allreg",
"operation : INRDCR reg8",
"operation : ARITHC HL ',' bcdehlsp",
"operation : ADD mar ',' bcdesp",
"operation : ADD mar ',' mar",
"operation : DAD evenreg8",
"operation : ARITH16 bcdesp",
"operation : ARITH16 mar",
"operation : INCDEC evenreg",
"operation : INXDCX evenreg8",
"operation : PUSHPOP pushable",
"operation : PUSHPOP pushable8",
"operation : BIT expression",
"operation : BIT expression ',' reg",
"operation : BIT_XY expression ',' dxy",
"operation : BIT expression ',' memxy ',' realreg",
"operation : JP condition ',' expression",
"operation : JUMP8 expression",
"operation : JP '(' mar ')'",
"operation : CALL condition ',' expression",
"operation : CALL8 expression",
"operation : JR expression",
"operation : JR spcondition ',' expression",
"operation : JR_COND expression",
"operation : DJNZ expression",
"operation : RET",
"operation : RET condition",
"operation : LD allreg ',' allreg",
"operation : LD_XY realreg ',' dxy",
"operation : ST_XY realreg ',' dxy",
"operation : MOV reg8 ',' reg8",
"operation : LD allreg ',' noparenexpr",
"operation : MV_XY expression ',' dxy",
"operation : MVI reg8 ',' expression",
"operation : LD allreg ',' '(' RP ')'",
"operation : LDAX realreg",
"operation : LD allreg ',' parenexpr",
"operation : LDA expression",
"operation : LD '(' RP ')' ',' ACC",
"operation : STAX realreg",
"operation : LD parenexpr ',' ACC",
"operation : STA expression",
"operation : LD allreg ',' MISCREG",
"operation : LD MISCREG ',' ACC",
"operation : LD evenreg ',' lxexpression",
"operation : LXI evenreg8 ',' lxexpression",
"operation : LD evenreg ',' parenexpr",
"operation : LHLD expression",
"operation : LD parenexpr ',' evenreg",
"operation : SHLD expression",
"operation : LD evenreg ',' mar",
"operation : LDST16 expression",
"operation : EX RP ',' HL",
"operation : EX AF ',' AFp",
"operation : EX '(' SP ')' ',' mar",
"operation : TK_IN realreg ',' parenexpr",
"operation : TK_IN expression",
"operation : TK_IN realreg ',' '(' TK_C ')'",
"operation : INP realreg",
"operation : TK_IN 'F' ',' '(' TK_C ')'",
"operation : TK_IN '(' TK_C ')'",
"operation : TK_OUT parenexpr ',' ACC",
"operation : TK_OUT expression",
"operation : TK_OUT '(' TK_C ')' ',' realreg",
"operation : OUTP realreg",
"operation : TK_OUT '(' TK_C ')' ',' expression",
"operation : IM expression",
"operation : PHASE expression",
"operation : DEPHASE",
"operation : ORG expression",
"operation : ASSERT expression",
"operation : TSTATE expression",
"operation : SETOCF expression",
"$$11 :",
"operation : DEFB $$11 db.list",
"$$12 :",
"operation : DEFW $$12 dw.list",
"$$13 :",
"operation : DEFD $$13 dd.list",
"operation : ENDM",
"parm.list :",
"parm.list : parm.element",
"parm.list : parm.list ',' parm.element",
"$$14 :",
"parm.single : $$14 parm.element",
"maybeocto :",
"maybeocto : '#'",
"parm.element : maybeocto MPARM",
"locals : local_decls",
"local_decls :",
"$$15 :",
"local_decls : local_decls LOCAL $$15 local.list '\\n'",
"local.list :",
"local.list : local.element",
"local.list : local.list ',' local.element",
"local.element : MPARM",
"arg.list :",
"arg.list : arg.element",
"arg.list : arg.list ',' arg.element",
"arg.element : ARG",
"$$16 :",
"arg.element : '%' $$16 expression",
"allreg : reg",
"allreg : ixylhreg",
"reg : realreg",
"reg : mem",
"ixylhreg : IXYLH",
"reg8 : realreg",
"reg8 : m",
"m : COND",
"realreg : REGNAME",
"realreg : ACC",
"realreg : TK_C",
"mem : '(' HL ')'",
"mem : memxy",
"memxy : '(' INDEX dxy ')'",
"memxy : '(' INDEX ')'",
"memxy : dxy '(' INDEX ')'",
"dxy : expression",
"evenreg : bcdesp",
"evenreg : mar",
"evenreg8 : realreg",
"evenreg8 : SP",
"pushable : RP",
"pushable : AF",
"pushable : mar",
"pushable8 : realreg",
"pushable8 : PSW",
"bcdesp : RP",
"bcdesp : SP",
"bcdehlsp : bcdesp",
"bcdehlsp : HL",
"mar : HL",
"mar : INDEX",
"condition : spcondition",
"condition : COND",
"spcondition : SPCOND",
"spcondition : TK_C",
"db.list : db.list.element",
"db.list : db.list ',' db.list.element",
"db.list.element : TWOCHAR",
"db.list.element : STRING",
"db.list.element : expression",
"dw.list : dw.list.element",
"dw.list : dw.list ',' dw.list.element",
"dw.list.element : expression",
"dd.list : dd.list.element",
"dd.list : dd.list ',' dd.list.element",
"dd.list.element : expression",
"lxexpression : noparenexpr",
"lxexpression : TWOCHAR",
"expression : parenexpr",
"expression : noparenexpr",
"parenexpr : '(' expression ')'",
"noparenexpr : LABEL",
"noparenexpr : NUMBER",
"noparenexpr : ONECHAR",
"noparenexpr : EQUATED",
"noparenexpr : WASEQUATED",
"noparenexpr : DEFLED",
"noparenexpr : '$'",
"noparenexpr : UNDECLARED",
"noparenexpr : MULTDEF",
"$$17 :",
"noparenexpr : NUL $$17 RAWTOKEN",
"noparenexpr : expression '+' expression",
"noparenexpr : expression '-' expression",
"noparenexpr : expression '/' expression",
"noparenexpr : expression '*' expression",
"noparenexpr : expression '%' expression",
"noparenexpr : expression '&' expression",
"noparenexpr : expression AND expression",
"noparenexpr : expression '|' expression",
"noparenexpr : expression OR expression",
"noparenexpr : expression '^' expression",
"noparenexpr : expression XOR expression",
"noparenexpr : expression SHL expression",
"noparenexpr : expression SHR expression",
"noparenexpr : expression '<' expression",
"noparenexpr : expression LT expression",
"noparenexpr : expression '=' expression",
"noparenexpr : expression EQ expression",
"noparenexpr : expression '>' expression",
"noparenexpr : expression GT expression",
"noparenexpr : expression LE expression",
"noparenexpr : expression NE expression",
"noparenexpr : expression GE expression",
"noparenexpr : expression ANDAND expression",
"noparenexpr : expression OROR expression",
"noparenexpr : expression MROP_ADD expression",
"noparenexpr : expression MROP_SUB expression",
"noparenexpr : expression MROP_DIV expression",
"noparenexpr : expression MROP_MUL expression",
"noparenexpr : expression MROP_MOD expression",
"noparenexpr : expression MROP_AND expression",
"noparenexpr : expression MROP_OR expression",
"noparenexpr : expression MROP_XOR expression",
"noparenexpr : expression MROP_SHL expression",
"noparenexpr : expression MROP_SHR expression",
"noparenexpr : expression MROP_LT expression",
"noparenexpr : expression MROP_EQ expression",
"noparenexpr : expression MROP_GT expression",
"noparenexpr : expression MROP_LE expression",
"noparenexpr : expression MROP_NE expression",
"noparenexpr : expression MROP_GE expression",
"noparenexpr : expression MROP_SHIFT expression",
"noparenexpr : expression '?' expression ':' expression",
"noparenexpr : '[' expression ']'",
"noparenexpr : '~' expression",
"noparenexpr : MROP_NOT expression",
"noparenexpr : '!' expression",
"noparenexpr : '+' expression",
"noparenexpr : MROP_ADD expression",
"noparenexpr : '-' expression",
"noparenexpr : MROP_SUB expression",
"noparenexpr : T expression",
"noparenexpr : TILO expression",
"noparenexpr : TIHI expression",
"noparenexpr : OCF expression",
"noparenexpr : LOW expression",
"noparenexpr : MROP_LOW expression",
"noparenexpr : HIGH expression",
"noparenexpr : MROP_HIGH expression",
"symbol : UNDECLARED",
"symbol : LABEL",
"symbol : MULTDEF",
"symbol : EQUATED",
"symbol : WASEQUATED",
"symbol : DEFLED",
"al :",
"arg_on :",
"arg_off :",
"mras_undecl_on :",
"mras_undecl_off :",

};
#endif

int      yydebug;
int      yynerrs;

int      yyerrflag;
int      yychar;
YYSTYPE  yyval;
YYSTYPE  yylval;

/* define the initial stack-sizes */
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH  YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 10000
#define YYMAXDEPTH  10000
#endif
#endif

#define YYINITSTACKSIZE 200

typedef struct {
    unsigned stacksize;
    YYINT    *s_base;
    YYINT    *s_mark;
    YYINT    *s_last;
    YYSTYPE  *l_base;
    YYSTYPE  *l_mark;
} YYSTACKDATA;
/* variables for the parser stack */
static YYSTACKDATA yystack;
#line 3862 "zmac.y"

/*extern int	yylval;*/

#define F_END	0
#define OTHER	1
#define SPACE	2
#define DIGIT	3
#define LETTER	4
#define STARTER 5
#define DOLLAR	6


/*
 *  This is the table of character classes.  It is used by the lexical
 *  analyser. (yylex())
 */
char	charclass[] = {
	F_END,	OTHER,	OTHER,	OTHER,	OTHER,	OTHER,	OTHER,	OTHER,
	OTHER,	SPACE,	OTHER,	OTHER,	OTHER,	SPACE,	OTHER,	OTHER,
	OTHER,	OTHER,	OTHER,	OTHER,	OTHER,	OTHER,	OTHER,	OTHER,
	OTHER,	OTHER,	OTHER,	OTHER,	OTHER,	OTHER,	OTHER,	OTHER,
	SPACE,	OTHER,	OTHER,	OTHER,	DOLLAR,	OTHER,	OTHER,	OTHER,	//  !"#$%&'
	OTHER,	OTHER,	OTHER,	OTHER,	OTHER,	OTHER,	STARTER,OTHER,	// ()*+,-./
	DIGIT,	DIGIT,	DIGIT,	DIGIT,	DIGIT,	DIGIT,	DIGIT,	DIGIT,	// 01234567
	DIGIT,	DIGIT,	OTHER,	OTHER,	OTHER,	OTHER,	OTHER,	STARTER,// 89:;<=>?
	STARTER,LETTER, LETTER, LETTER, LETTER, LETTER, LETTER, LETTER,	// @ABCDEFG
	LETTER, LETTER, LETTER, LETTER, LETTER, LETTER, LETTER, LETTER,	// HIJKLMNO
	LETTER, LETTER, LETTER, LETTER, LETTER, LETTER, LETTER, LETTER,	// PQRSTUVW
	LETTER, LETTER, LETTER, OTHER,	OTHER,	OTHER,	OTHER,	LETTER,	// XYZ[\]^_
	OTHER,	LETTER, LETTER, LETTER, LETTER, LETTER, LETTER, LETTER,	// `abcdefg
	LETTER, LETTER, LETTER, LETTER, LETTER, LETTER, LETTER, LETTER,	// hijklmno
	LETTER, LETTER, LETTER, LETTER, LETTER, LETTER, LETTER, LETTER,	// pqrstuvw
	LETTER, LETTER, LETTER, OTHER,	OTHER,	OTHER,	OTHER,	OTHER,	// xyz{|}~
};
#define CHARCLASS(x) charclass[(x) & 0xff]


/*
 *  the following table tells which characters are parts of numbers.
 *  The entry is non-zero for characters which can be parts of numbers.
 */
char	numpart[] = {
	0,	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,	0,
	'0',	'1',	'2',	'3',	'4',	'5',	'6',	'7',
	'8',	'9',	0,	0,	0,	0,	0,	0,
	0,	'A',	'B',	'C',	'D',	'E',	'F',	0,
	'H',	0,	0,	0,	0,	0,	0,	'O',
	0,	'Q',	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,	0,
	0,	'a',	'b',	'c',	'd',	'e',	'f',	0,
	'h',	0,	0,	0,	0,	0,	0,	'o',
	0,	'q',	0,	0,	0,	0,	0,	0,
	'x',	0,	0,	0,	0,	0,	0,	0,
	0};




/*
 *  the following table is a list of assembler mnemonics;
 *  for each mnemonic the associated machine-code bit pattern
 *  and symbol type are given.
 *
 *  The i_uses field is overloaded to indicate the possible uses for
 *  a token.
 */

#define VERB	(1)	/* opcode or psuedo-op */
#define I8080	(2)	/* used in 8080 instructions */
#define Z80	(4)	/* used in Z80 instructions */
#define UNDOC	(8)	/* used only in undocumented instructions */
#define TERM	(16)	/* can appear in expressions (not all marked) */
#define ZNONSTD	(32)	/* non-standard Z-80 mnemonic (probably TDL or DRI) */
#define COL0	(64)	/* will always be recognized in logical column 0 */
#define MRASOP	(128)	/* dig operator out of identifiers */

struct	item	keytab[] = {
	{"*include",	PSINC,	ARGPSEUDO,	VERB | COL0 },
	{"*list",	0,	LIST,		VERB | COL0 },
	{"*mod",	0,	MRAS_MOD,	VERB },
	{".8080",	0,	INSTSET,	VERB },
	{"a",		7,	ACC,		I8080 | Z80 },
	{"aci",		0316,	ALUI8,		VERB | I8080 },
	{"adc",		1,	ARITHC,		VERB | I8080 | Z80  },
	{"adcx",	0xdd8e,	ALU_XY,		VERB | Z80 | ZNONSTD },
	{"adcy",	0xfd8e,	ALU_XY,		VERB | Z80 | ZNONSTD },
	{"add",		0,	ADD,		VERB | I8080 | Z80  },
	{"addx",	0xdd86,	ALU_XY,		VERB | Z80 | ZNONSTD },
	{"addy",	0xfd86,	ALU_XY,		VERB | Z80 | ZNONSTD },
	{"adi",		0306,	ALUI8,		VERB | I8080 },
	{"af",		060,	AF,		Z80 },
	{"ana",		4,	ARITHC,		VERB | I8080},
	{"and",		4,	AND,		VERB | Z80 | TERM },
	{".and.",	0,	MROP_AND,	TERM | MRASOP },
	{"andx",	0xdda6,	ALU_XY,		VERB | Z80 | ZNONSTD },
	{"andy",	0xfda6,	ALU_XY,		VERB | Z80 | ZNONSTD },
	{"ani",		0346,	ALUI8,		VERB | I8080 },
	{".ascii",	0,	DEFB,		VERB },
	{".aseg",	SEG_ABS,SETSEG,		VERB },
	{".aset",	0,	DEFL,		VERB },
	{".assert",	0,	ASSERT,		VERB },
	{"b",		0,	REGNAME,	I8080 | Z80 },
	{"bc",		0,	RP,		Z80 },
	{"bit",		0145500,BIT,		VERB | Z80 },
	{"bitx",	0xdd46,	BIT_XY,		VERB | Z80 | ZNONSTD },
	{"bity",	0xfd46,	BIT_XY,		VERB | Z80 | ZNONSTD },
	{".block",	0,	DEFS,		VERB },
	{".byte",	0,	DEFB,		VERB },
	{"c",		1,	TK_C,		I8080 | Z80 },
	{"call",	0315,	CALL,		VERB | I8080 | Z80 },
	{"cc",		0334,	CALL8,		VERB | I8080 },
	{"ccd",		0xeda9,	NOOPERAND,	VERB | Z80 | ZNONSTD },
	{"ccdr",	0xedb9,	NOOPERAND,	VERB | Z80 | ZNONSTD },
	{"ccf",		077,	NOOPERAND,	VERB | Z80 },
	{"cci",		0xeda1,	NOOPERAND,	VERB | Z80 | ZNONSTD },
	{"ccir",	0xedb1,	NOOPERAND,	VERB | Z80 | ZNONSTD },
	{"cm",		0374,	CALL8,		VERB | I8080 },
	{"cma",		057,	NOOPERAND,	VERB | I8080 },
	{"cmc",		077,	NOOPERAND,	VERB | I8080 },
	{"cmp",		7,	LOGICAL,	VERB | I8080 },
	{"cmpx",	0xddbe,	ALU_XY,		VERB | Z80 | ZNONSTD },
	{"cmpy",	0xfdbe,	ALU_XY,		VERB | Z80 | ZNONSTD },
	{"cnc",		0324,	CALL8,		VERB | I8080 },
	{"cnz",		0304,	CALL8,		VERB | I8080 },
	{".comment",	SPCOM,	SPECIAL,	VERB },
	{".cond",	0,	IF_TK,		VERB },
	{"cp",		7,	LOGICAL,	VERB | I8080 | Z80 },
	{"cpd",		0166651,NOOPERAND,	VERB | Z80 },
	{"cpdr",	0166671,NOOPERAND,	VERB | Z80 },
	{"cpe",		0354,	CALL8,		VERB | I8080 },
	{"cpi",		0166641,NOOPERAND,	VERB | I8080 | Z80 },
	{"cpir",	0166661,NOOPERAND,	VERB | Z80 },
	{"cpl",		057,	NOOPERAND,	VERB | Z80 },
	{"cpo",		0344,	CALL8,		VERB | I8080 },
	{".cseg",	SEG_CODE,SETSEG,	VERB },
	{"cz",		0314,	CALL8,		VERB | I8080 },
	{"d",		2,	REGNAME,	I8080 | Z80 },
	{"daa",		0047,	NOOPERAND,	VERB | I8080 | Z80 },
	{"dad",		0,	DAD,		VERB | I8080 },
	{"dadc",	0xed4a,	ARITH16,	VERB | Z80 | ZNONSTD },
	{"dadx",	0xdd09,	ARITH16,	VERB | Z80 | ZNONSTD },
	{"dady",	0xfd09,	ARITH16,	VERB | Z80 | ZNONSTD },
	{".db",		0,	DEFB,		VERB },
	{".dc",		0,	DC,		VERB },
	{"dcr",		1,	INRDCR,		VERB | I8080 },
	{"dcrx",	0xdd35,	ALU_XY,		VERB | Z80 | ZNONSTD },
	{"dcry",	0xfd35,	ALU_XY,		VERB | Z80 | ZNONSTD },
	{"dcx",		1,	INXDCX,		VERB | I8080 },
	{"dcxix",	0xdd2b,	NOOPERAND,	VERB | Z80 | ZNONSTD },
	{"dcxiy",	0xfd2b,	NOOPERAND,	VERB | Z80 | ZNONSTD },
	{"de",		020,	RP,		Z80 },
	{"dec",		1,	INCDEC,		VERB | I8080 | Z80 },
	{".defb",	0,	DEFB,		VERB },
	{".defd",	0,	DEFD,		VERB },
	{".defl",	0,	DEFL,		VERB },
	{".defm",	0,	DEFB,		VERB },
	{".defs",	0,	DEFS,		VERB },
	{".defw",	0,	DEFW,		VERB },
	{".dephase",	0,	DEPHASE,	VERB },
	{"di",		0363,	NOOPERAND,	VERB | I8080 | Z80 },
	{"djnz",	020,	DJNZ,		VERB | Z80 },
	{".ds",		0,	DEFS,		VERB },
	{"dsbc",	0xed42,	ARITH16,	VERB | Z80 | ZNONSTD },
	{".dseg",	SEG_DATA,SETSEG,	VERB },
	{".dw",		0,	DEFW,		VERB },
	{".dword",	0,	DEFD,		VERB },
	{"e",		3,	REGNAME,	I8080 | Z80 },
	{"ei",		0373,	NOOPERAND,	VERB | I8080 | Z80 },
	{".eject",	1,	LIST,		VERB },
	{".elist",	3,	LIST,		VERB },
	{".else",	0,	ELSE_TK,	VERB },
	{".end",	0,	END,		VERB },
	{".endc",	0,	ENDIF_TK,	VERB },
	{".endif",	0,	ENDIF_TK,	VERB },
	{".endm", 	0,	ENDM,		VERB },
	{".entry",	0,	PUBLIC,		VERB },
	{"eq",		0,	EQ,		0 },
	{".eq.",	0,	MROP_EQ,	TERM | MRASOP },
	{".equ",	0,	EQU,		VERB },
	{"ex",		0,	EX,		VERB | Z80 },
	{"exaf",	0x08,	NOOPERAND,	VERB | Z80 | ZNONSTD },
	{".exitm", 	0,	EXITM,		VERB },
	{".ext",	0,	EXTRN,		VERB },
	{".extern",	0,	EXTRN,		VERB },
	{".extrn",	0,	EXTRN,		VERB },
	{"exx",		0331,	NOOPERAND,	VERB | Z80 },
	{".flist",	4,	LIST,		VERB },
	{"ge",		0,	GE,		0 },
	{".ge.",	0,	MROP_GE,	TERM | MRASOP },
	{".glist",	5,	LIST,		VERB },
	{".global",	0,	PUBLIC,		VERB },
	{"gt",		0,	GT,		0 },
	{".gt.",	0,	MROP_GT,	TERM | MRASOP },
	{"h",		4,	REGNAME,	I8080 | Z80 },
	{"halt",	0166,	NOOPERAND,	VERB | Z80 },
	{"high",	0,	HIGH,		0 },
	{".high.",	0,	MROP_HIGH,	TERM | MRASOP },
	{"hl",		040,	HL,		Z80 },
	{"hlt",		0166,	NOOPERAND,	VERB | I8080 },
	{"i",		0,	MISCREG,	Z80 },
	{".if",		0,	IF_TK,		VERB | COL0 },
	{".ifdef",	1,	IF_DEF_TK,	VERB | COL0 },
	{".ifndef",	0,	IF_DEF_TK,	VERB | COL0 },
	{"im",		0166506,IM,		VERB | Z80 },
	{"im0",		0xed46,	NOOPERAND,	VERB | Z80 | ZNONSTD },
	{"im1",		0xed56,	NOOPERAND,	VERB | Z80 | ZNONSTD },
	{"im2",		0xed5e,	NOOPERAND,	VERB | Z80 | ZNONSTD },
	{"in",		0333,	TK_IN,		VERB | I8080 | Z80 },
	{"inc",		0,	INCDEC,		VERB | Z80 },
	{".incbin", 	0, 	INCBIN,		VERB },
	{".include",	PSINC,	ARGPSEUDO,	VERB | COL0 },	// COL0 only needed for MRAS mode
	{"ind",		0166652,NOOPERAND,	VERB | Z80 },
	{"indr",	0166672,NOOPERAND,	VERB | Z80 },
	{"ini",		0166642,NOOPERAND,	VERB | Z80 },
	{"inir",	0166662,NOOPERAND,	VERB | Z80 },
	{"inp",		0,	INP,		VERB | Z80 | ZNONSTD },
	{"inr",		0,	INRDCR,		VERB | I8080 },
	{"inrx",	0xdd34,	ALU_XY,		VERB | Z80 | ZNONSTD },
	{"inry",	0xfd34,	ALU_XY,		VERB | Z80 | ZNONSTD },
	{"inx",		0,	INXDCX,		VERB | I8080 },
	{"inxix",	0xdd23,	NOOPERAND,	VERB | Z80 | ZNONSTD },
	{"inxiy",	0xfd23,	NOOPERAND,	VERB | Z80 | ZNONSTD },
	{"irp",		0,	IRP,		VERB },
	{"irpc",	0,	IRPC,		VERB },
	{"ix",		0156440,INDEX,		Z80 },
	{"ixh",		0x1DD04,IXYLH,		Z80 | UNDOC },
	{"ixl",		0x1DD05,IXYLH,		Z80 | UNDOC },
	{"iy",		0176440,INDEX,		Z80 },
	{"iyh",		0x1FD04,IXYLH,		Z80 | UNDOC },
	{"iyl",		0x1FD05,IXYLH,		Z80 | UNDOC },
	{"jc",		0332,	JUMP8,		VERB | I8080 },
	{"jm",		0372,	JUMP8,		VERB | I8080 },
	{"jmp",		0303,	JP,		VERB | I8080 },
	{"jnc",		0322,	JUMP8,		VERB | I8080 },
	{"jnz",		0302,	JUMP8,		VERB | I8080 },
	{"jp",		0,	JP,		VERB | I8080 | Z80 },
	{"jpe",		0352,	JUMP8,		VERB | I8080 },
	{".jperror",	0,	JPERROR,	VERB },
	{"jpo",		0342,	JUMP8,		VERB | I8080 },
	{"jr",		040,	JR,		VERB | Z80 },
	{"jrc",		0x38,	JR_COND,	VERB | Z80 | ZNONSTD },
	{"jrnc",	0x30,	JR_COND,	VERB | Z80 | ZNONSTD },
	{"jrnz",	0x20,	JR_COND,	VERB | Z80 | ZNONSTD },
	{".jrpromote",	0,	JRPROMOTE,	VERB },
	{"jrz",		0x28,	JR_COND,	VERB | Z80 | ZNONSTD },
	{"jz",		0312,	JUMP8,		VERB | I8080 },
	{"l",		5,	REGNAME,	I8080 | Z80 },
	{"lbcd",	0xed4b,	LDST16,		VERB | Z80 | ZNONSTD },
	{"ld",		0,	LD,		VERB | Z80 },
	{"lda",		0,	LDA,		VERB | I8080 },
	{"ldai",	0xed57,	NOOPERAND,	VERB | Z80 | ZNONSTD },
	{"ldar",	0xed5f,	NOOPERAND,	VERB | Z80 | ZNONSTD },
	{"ldax",	0,	LDAX,		VERB | I8080 },
	{"ldd",		0166650,NOOPERAND,	VERB | Z80 },
	{"lddr",	0166670,NOOPERAND,	VERB | Z80 },
	{"lded",	0xed5b,	LDST16,		VERB | Z80 | ZNONSTD },
	{"ldi",		0166640,NOOPERAND,	VERB | Z80 },
	{"ldir",	0166660,NOOPERAND,	VERB | Z80 },
	{"ldx",		0xdd46,	LD_XY,		VERB | Z80 | ZNONSTD},
	{"ldy",		0xfd46,	LD_XY,		VERB | Z80 | ZNONSTD},
	{"le",		0,	LE,		0 },
	{".le.",	0,	MROP_LE,	TERM | MRASOP },
	{"lhld",	0,	LHLD,		VERB | I8080 },
	{".list",	0,	LIST,		VERB | COL0 }, // COL0 only needed for MRAS
	{"lixd",	0xdd2a,	LDST16,		VERB | Z80 | ZNONSTD },
	{"liyd",	0xfd2a,	LDST16,		VERB | Z80 | ZNONSTD },
	{".local",	0,	LOCAL,		VERB },
	{"low",		0,	LOW,		0 },
	{".low.",	0,	MROP_LOW,	TERM | MRASOP },
	{"lspd",	0xed7b,	LDST16,		VERB | Z80 | ZNONSTD },
	{"lt",		0,	LT,		0 },
	{".lt.",	0,	MROP_LT,	TERM | MRASOP },
	{"lxi",		0,	LXI,		VERB | I8080 },
	{"lxix",	0xdd21,	LDST16,		VERB | Z80 | ZNONSTD },
	{"lxiy",	0xfd21,	LDST16,		VERB | Z80 | ZNONSTD },
	{"m",		070,	COND,		I8080 | Z80 },
	{".maclib",	PSMACLIB,ARGPSEUDO,	VERB },
	{".macro",	0,	MACRO,		VERB },
	{".max",	1,	MINMAX,		VERB },
	{".min",	0,	MINMAX,		VERB },
	{".mlist",	6,	LIST,		VERB },
	{"mod",		0,	'%',		0 },
	{".mod.",	0,	MROP_MOD,	TERM | MRASOP },
	{"mov",		0,	MOV,		VERB | I8080 },
	{"mvi",		0,	MVI,		VERB | I8080 },
	{"mvix",	0xdd36,	MV_XY,		VERB | Z80 | ZNONSTD },
	{"mviy",	0xfd36,	MV_XY,		VERB | Z80 | ZNONSTD },
	{".name",	SPNAME,	SPECIAL,	VERB },
	{"nc",		020,	SPCOND,		0 },
	{"ne",		0,	NE,		0 },
	{".ne.",	0,	MROP_NE,	TERM | MRASOP },
	{"neg",		0166504,NOOPERAND,	VERB | Z80 },
	{".nolist",	-1,	LIST,		VERB },
	{"nop",		0,	NOOPERAND,	VERB | I8080 | Z80 },
	{"not",		0,	'~',		0 },
	{".not.",	0,	MROP_NOT,	TERM | MRASOP },
	{"nul",		0,	NUL,		0 },
	{"nv",		040,	COND,		Z80 },
	{"nz",		0,	SPCOND,		Z80 },
	{"ocf",		0,	OCF,		0 },
	{"or",		6,	OR,		VERB | Z80 | TERM },
	{".or.",	6,	MROP_OR,	TERM | MRASOP },
	{"ora",		6,	LOGICAL,	VERB | I8080 },
	{".org",	0,	ORG,		VERB },
	{"ori",		0366,	ALUI8,		VERB | I8080 },
	{"orx",		0xddb6,	ALU_XY,		VERB | Z80 | ZNONSTD },
	{"ory",		0xfdb6,	ALU_XY,		VERB | Z80 | ZNONSTD },
	{"otdr",	0166673,NOOPERAND,	VERB | Z80 },
	{"otir",	0166663,NOOPERAND,	VERB | Z80 },
	{"out",		0323,	TK_OUT,		VERB | I8080 | Z80 },
	{"outd",	0166653,NOOPERAND,	VERB | Z80 },
	{"outdr",	0166673,NOOPERAND,	VERB | Z80 | ZNONSTD },
	{"outi",	0166643,NOOPERAND,	VERB | Z80 },
	{"outir",	0166663,NOOPERAND,	VERB | Z80 | ZNONSTD },
	{"outp",	0,	OUTP,		VERB | Z80 | ZNONSTD },
	{"p",		060,	COND,		Z80 },
	{".page",	1,	LIST,		VERB },
	{"pchl",	0351,	NOOPERAND,	VERB | I8080 },
	{"pcix",	0xdde9,	NOOPERAND,	VERB | Z80 | ZNONSTD },
	{"pciy",	0xfde9,	NOOPERAND,	VERB | Z80 | ZNONSTD },
	{"pe",		050,	COND,		Z80 },
	{"pfix",	0xdd,	NOOPERAND,	VERB | Z80 | UNDOC },
	{"pfiy",	0xfd,	NOOPERAND,	VERB | Z80 | UNDOC },
	{".phase",	0,	PHASE,		VERB },
	{"po",		040,	COND,		Z80 },
	{"pop",		0301,	PUSHPOP,	VERB | I8080 | Z80 },
	{"popix",	0xdde1,	NOOPERAND,	VERB | Z80 | ZNONSTD },
	{"popiy",	0xfde1,	NOOPERAND,	VERB | Z80 | ZNONSTD },
	{"pragma",	SPPRAGMA,SPECIAL,	VERB },
	{"psw", 	060,	PSW,		I8080 },
	{".public",	0,	PUBLIC,		VERB },
	{"push",	0305,	PUSHPOP,	VERB | I8080 | Z80 },
	{"pushix",	0xdde5,	NOOPERAND,	VERB | Z80 | ZNONSTD },
	{"pushiy",	0xfde5,	NOOPERAND,	VERB | Z80 | ZNONSTD },
	{"r",		010,	MISCREG,	Z80 },
	{"ral",		027,	NOOPERAND,	VERB | I8080 },
	{"ralr",	2,	SHIFT,		VERB | Z80 | ZNONSTD },
	{"ralx",	0xdd16,	SHIFT_XY,	VERB | Z80 | ZNONSTD },
	{"raly",	0xfd16,	SHIFT_XY,	VERB | Z80 | ZNONSTD },
	{"rar",		037,	NOOPERAND,	VERB | I8080 },
	{"rarr",	3,	SHIFT,		VERB | Z80 | ZNONSTD },
	{"rarx",	0xdd1e,	SHIFT_XY,	VERB | Z80 | ZNONSTD },
	{"rary",	0xfd1e,	SHIFT_XY,	VERB | Z80 | ZNONSTD },
	{"rc",		0330,	NOOPERAND,	VERB | I8080 },
	{".read",	PSINC,	ARGPSEUDO,	VERB },
	{"rept",	0,	REPT,		VERB },
	{"res",		0145600,BIT,		VERB | Z80 },
	{"resx",	0xdd86,	BIT_XY,		VERB | Z80 | ZNONSTD },
	{"resy",	0xfd86,	BIT_XY,		VERB | Z80 | ZNONSTD },
	{"ret",		0311,	RET,		VERB | I8080 | Z80 },
	{"reti",	0166515,NOOPERAND,	VERB | Z80 },
	{"retn",	0166505,NOOPERAND,	VERB | Z80 },
	{"rl",		2,	SHIFT,		VERB | Z80 },
	{"rla",		027,	NOOPERAND,	VERB | Z80 },
	{"rlc",		0,	SHIFT,		VERB | I8080 | Z80 },
	{"rlca",	07,	NOOPERAND,	VERB | Z80 },
	{"rlcr",	0,	SHIFT,		VERB | I8080 | Z80 | ZNONSTD },
	{"rlcx",	0xdd06,	SHIFT_XY,	VERB | Z80 | ZNONSTD },
	{"rlcy",	0xfd06,	SHIFT_XY,	VERB | Z80 | ZNONSTD },
	{"rld",		0166557,NOOPERAND,	VERB | Z80 },
	{"rm",		0370,	NOOPERAND,	VERB | I8080 },
	{".rmem",	0,	DEFS,		VERB },
	{"rnc",		0320,	NOOPERAND,	VERB | I8080 },
	{"rnz",		0300,	NOOPERAND,	VERB | I8080 },
	{"rp",		0360,	NOOPERAND,	VERB | I8080 },
	{"rpe",		0350,	NOOPERAND,	VERB | I8080 },
	{"rpo",		0340,	NOOPERAND,	VERB | I8080 },
	{"rr",		3,	SHIFT,		VERB | Z80 },
	{"rra",		037,	NOOPERAND,	VERB | Z80 },
	{"rrc",		1,	SHIFT,		VERB | I8080 | Z80 },
	{"rrca",	017,	NOOPERAND,	VERB | Z80 },
	{"rrcr",	1,	SHIFT,		VERB | Z80 | ZNONSTD },
	{"rrcx",	0xdd0e,	SHIFT_XY,	VERB | Z80 | ZNONSTD },
	{"rrcy",	0xfd0e,	SHIFT_XY,	VERB | Z80 | ZNONSTD },
	{"rrd",		0166547,NOOPERAND,	VERB | Z80 },
	{"rst",		0307,	RST,		VERB | I8080 | Z80 },
	{".rsym",	PSRSYM,	ARGPSEUDO,	VERB },
	{"rz",		0310,	NOOPERAND,	VERB | I8080 },
	{"sbb",		3,	ARITHC,		VERB | I8080 },
	{"sbc",		3,	ARITHC,		VERB | Z80 },
	{"sbcd",	0xed43,	LDST16,		VERB | Z80 | ZNONSTD },
	{"sbcx",	0xdd9e,	ALU_XY,		VERB | Z80 | ZNONSTD },
	{"sbcy",	0xfd9e,	ALU_XY,		VERB | Z80 | ZNONSTD },
	{"sbi",		0336,	ALUI8,		VERB | I8080 },
	{"scf",		067,	NOOPERAND,	VERB | Z80 },
	{"sded",	0xed53,	LDST16,		VERB | Z80 | ZNONSTD },
	{"set",		0145700,BIT,		VERB | Z80 },
	{"setb",	0145700,BIT,		VERB | Z80 | ZNONSTD },
	{".setocf",	0,	SETOCF,		VERB },
	{".sett",	0,	TSTATE,		VERB },
	{"setx",	0xddc6,	BIT_XY,		VERB | Z80 | ZNONSTD },
	{"sety",	0xfdc6,	BIT_XY,		VERB | Z80 | ZNONSTD },
	{"shl",		0,	SHL,		TERM },
	{".shl.",	0,	MROP_SHL,	TERM | MRASOP },
	{"shld",	0,	SHLD,		VERB | I8080 },
	{"shr",		0,	SHR,		TERM },
	{".shr.",	0,	MROP_SHR,	TERM | MRASOP },
	{"sixd",	0xdd22,	LDST16,		VERB | Z80 | ZNONSTD },
	{"siyd",	0xfd22,	LDST16,		VERB | Z80 | ZNONSTD },
	{"sl1",		6,	SHIFT,		VERB | Z80 | UNDOC },
	{"sla",		4,	SHIFT,		VERB | Z80 },
	{"slar",	4,	SHIFT,		VERB | Z80 | ZNONSTD },
	{"slax",	0xdd26,	SHIFT_XY,	VERB | Z80 | ZNONSTD },
	{"slay",	0xfd26,	SHIFT_XY,	VERB | Z80 | ZNONSTD },
	{"sll",		6,	SHIFT,		VERB | Z80 },
	{"sp",		060,	SP,		I8080 | Z80 },
	{".space",	2,	LIST,		VERB },
	{"sphl",	0371,	NOOPERAND,	VERB | I8080 },
	{"spix",	0xddf9,	NOOPERAND,	VERB | Z80 | ZNONSTD },
	{"spiy",	0xfdf9,	NOOPERAND,	VERB | Z80 | ZNONSTD },
	{"sra",		5,	SHIFT,		VERB | Z80 },
	{"srar",	5,	SHIFT,		VERB | Z80 | ZNONSTD },
	{"srax",	0xdd2e,	SHIFT_XY,	VERB | Z80 | ZNONSTD },
	{"sray",	0xfd2e,	SHIFT_XY,	VERB | Z80 | ZNONSTD },
	{"srl",		7,	SHIFT,		VERB | Z80 },
	{"srlr",	7,	SHIFT,		VERB | Z80 | ZNONSTD },
	{"srlx",	0xdd3e,	SHIFT_XY,	VERB | Z80 | ZNONSTD },
	{"srly",	0xfd3e,	SHIFT_XY,	VERB | Z80 | ZNONSTD },
	{"sspd",	0xed73,	LDST16,		VERB | Z80 | ZNONSTD },
	{"sta",		0,	STA,		VERB | I8080 },
	{"stai",	0xed47,	NOOPERAND,	VERB | Z80 | ZNONSTD },
	{"star",	0xed4f,	NOOPERAND,	VERB | Z80 | ZNONSTD },
	{"stax",	0,	STAX,		VERB | I8080 },
	{"stc",		067,	NOOPERAND,	VERB | I8080 },
	{"stx",		0xdd70,	ST_XY,		VERB | Z80 | ZNONSTD},
	{"sty",		0xfd70,	ST_XY,		VERB | Z80 | ZNONSTD},
	{"sub",		2,	LOGICAL,	VERB | I8080 | Z80 },
	{".subttl",	SPSBTL,	SPECIAL,	VERB },
	{"subx",	0xdd96,	ALU_XY,		VERB | Z80 | ZNONSTD },
	{"suby",	0xfd96,	ALU_XY,		VERB | Z80 | ZNONSTD },
	{"sui",		0326,	ALUI8,		VERB | I8080 },
	{"t",		0,	T,		0 },
	{".text",	0,	DEFB,		VERB },
	{"tihi",	0,	TIHI,		0 },
	{"tilo",	0,	TILO,		0 },
	{".title",	SPTITL,	SPECIAL,	VERB },
	{".tstate",	0,	TSTATE,		VERB },
	{"v",		050,	COND,		Z80 },
	{".word",	0,	DEFW,		VERB },
	{".wsym",	PSWSYM,	ARGPSEUDO,	VERB },
	{"xchg",	0353,	NOOPERAND,	VERB | I8080 },
	{"xor",		5,	XOR,		VERB | Z80 | TERM },
	{".xor.",	5,	MROP_XOR,	TERM | MRASOP },
	{"xorx",	0xddae,	ALU_XY,		VERB | Z80 | ZNONSTD },
	{"xory",	0xfdae,	ALU_XY,		VERB | Z80 | ZNONSTD },
	{"xra",		5,	LOGICAL,	VERB | I8080 },
	{"xri",		0356,	ALUI8,		VERB | I8080 },
	{"xthl",	0343,	NOOPERAND,	VERB | I8080 },
	{"xtix",	0xdde3,	NOOPERAND,	VERB | Z80 | ZNONSTD },
	{"xtiy",	0xfde3,	NOOPERAND,	VERB | Z80 | ZNONSTD },
	{"z",		010,	SPCOND,		Z80 },
	{".z80",	1,	INSTSET,	VERB },
};

/*
 *  user-defined items are tabulated in the following table.
 */

struct item	itemtab[ITEMTABLESIZE];
struct item	*itemmax = itemtab+ITEMTABLESIZE;



/*
 *  lexical analyser, called by yyparse.
 */
int yylex()
{
	int lex();
	int token = lex();

	if (mras) {
		switch (token)
		{
		// Operator translations because of different precedence
		case '+': token = MROP_ADD; break;
		case '-': token = MROP_SUB; break;
		case '*': token = MROP_MUL; break;
		case '/': token = MROP_DIV; break;
		case '%': token = MROP_MOD; break;
		case '&': token = MROP_AND; break;
		case '|': token = MROP_OR; break;
		case '^': token = MROP_XOR; break;
		case SHL: token = MROP_SHL; break;
		case SHR: token = MROP_SHR; break;
		case LT:  token = MROP_LT; break;
		case EQ:  token = MROP_EQ; break;
		case '>': token = MROP_GT; break;
		case GE:  token = MROP_GE; break;
		case NE:  token = MROP_NE; break;
		case LE:  token = MROP_LE; break;
		case NOT: token = MROP_NOT; break;
		case HIGH: token = MROP_HIGH; break;
		case LOW: token = MROP_LOW; break;
		// Operator translations to completely different operator.
		case '<': token = MROP_SHIFT; break;
		case '!': token = MROP_OR; break;
		default: break;
		// Sadly, AND, OR, XOR and '=' can't be translated unilaterally
		// because they are also opcodes or psuedo-ops.
		}
	}

	return token;
}

int lex()
{
	int c;
	char *p;
	int radix;
	int sep;
	int exclude, include, overflow, token, endc;

	if (arg_flag) {
		yylval.cval = arg_state.arg;
		c = getarg(&arg_state);
		if (c == '\0' || c == '\n' || c == ';')
			c = skipline(c);

		return c;
	}

	if (raw == 2) {
		while (charclass[c = nextchar()] == SPACE)
			;

		*tempbuf = c == '\n' || c == '\0';

		peekc = skipline(c);

		raw = 0;

		return RAWTOKEN;
	}
	else if (raw) {
		int skip = 1;
		p = tempbuf;
		while ((c = nextchar()) != '\n' && c) {
			if (p >= tempmax) {
				*p = '\0';
				printf("was parsing '%s'\n", tempbuf);
				error(symlong);
			}
			if (!skip || charclass[c] != SPACE) {
				*p++ = c;
				skip = 0;
			}
		}
		if (c == 0)
			peekc = c;

		*p-- = '\0';

		while (p >= tempbuf && CHARCLASS(*p) == SPACE)
			*p-- = '\0';

		raw = 0;

		return RAWTOKEN;
	}

	for (;;) switch(charclass[c = nextchar()]) {
	case F_END:
		if (!expptr)
			return 0;

		if (est[MSTR].param) {
			int ch;
			est[REPNUM].value++;
			ch = est[MSTR].param[est[REPNUM].value];
			if (ch) {
				est[0].param[0] = ch;
				floc = est[MSTART].value;
				mfseek(mfile, (long)floc, 0);
				est[TEMPNUM].value = exp_number++;
			}
			else {
				free(est[MSTR].param);
				est[MSTR].param = 0;
				popsi();
			}
		}
		else if (est[REPNUM].value < 0) {
			int arg;
			do {
				switch (getarg(est[MARGP].ap)) {
				case ARG:
					arg = 1;
					break;
				case ',':
					arg = 0;
					break;
				default:
					arg = 2;
					break;
				}
			} while (!arg);

			if (arg == 1) {
				floc = est[MSTART].value;
				mfseek(mfile, (long)floc, 0);
				est[TEMPNUM].value = exp_number++;
			}
			else {
				// XXX - memory leak
				est[0].param = NULL;
				free(est[MARGP].ap);
				popsi();
			}
		}
		else if (est[REPNUM].value-- > 0) {
			floc = est[MSTART].value;
			mfseek(mfile, (long)floc, 0);
			est[TEMPNUM].value = exp_number++;
		}
		else
			popsi();

		continue;

	case SPACE:
		while (charclass[c = nextchar()] == SPACE)
			;
		peekc = c;
		logcol++;
		break;
	case LETTER:
	case STARTER:
	case DIGIT:
	case DOLLAR:
	spectok:
		firstcol = getcol() == 1;

		radix = -1; // might be a number
		p = tempbuf;
		do {
			if (p >= tempmax) {
				*tempmax = '\0';
				printf("was parsing '%s'\n", tempbuf);
				error(symlong);
			}
			*p = (c >= 'A' && c <= 'Z') ? c + 'a' - 'A' : c;
			if (mras && *p == '?') {
				char *q;

				radix = 0; // can't be a number even if it looks like it

				if (expptr)
					q = getmraslocal();
				else
					for (q = modstr; *q == '@'; q++)
						;

				if (*q) {
					strcpy(p, q);
					p = strchr(p, '\0') - 1;
				}
				else
					*p = '?';
			}
			p++;
			c = nextchar();
		} while	(charclass[c]==LETTER || charclass[c]==DIGIT ||
			charclass[c]==STARTER || charclass[c]==DOLLAR);

		*p = '\0';

		// When parsing macro parameters we use a custom symbol table.
		// And, heck, almost anything goes.
		if (param_parse) {
			struct item *param = item_lookup(tempbuf, paramtab, PARAMTABSIZE);
			peekc = c;
			if (param->i_token) {
				sprintf(detail, "%s error.  Macro parameter '%s' repeated",
					errname[fflag], tempbuf);
				errwarn(fflag, detail);
			}

			param->i_token = MPARM;
			param->i_string = malloc(strlen(tempbuf) + 1);
			strcpy(param->i_string, tempbuf);

			yylval.itemptr = param;
			return param->i_token;
		}

		// Special case for AF'
		if (c == '\'' && strcmp(tempbuf, "af") == 0)
			return AFp;

		endc = c;
		peekc = c;

		// Pass off '?' (XXX but, technically, should only be done in expression context)
		if (strcmp(tempbuf, "?") == 0)
			return '?';

		// Pass off '$'
		if (strcmp(tempbuf, "$") == 0)
			return '$';

		// Look ahead at what we have.
		while (charclass[c] == SPACE)
			c = nextchar();

		peekc = c;

		//printf("%d %s\n", logcol, tempbuf);
		// If logcol == 0 then if c == ':' we're a label for sure.
		// If logcol == 1 if c == ':' we're a label, change logcol
		//    otherwise we're op or pseudo
		// If logcol == 0 and c == '\n' or ';' then we're alone so
		//	we give tokenization a chance otherwise label
		// If logcol >= 2 we're in the arguments
		//
		// There is quite a lot of unrealized scope for error
		// detection and helpful warnings.

		 // Default to any tokenization.
		exclude = 0;
		include = 0;

		if (logcol >= 2) {
			// Arguments allow mnemonics and psuedo-ops
			exclude = VERB;
			include = TERM;
		}
		else if (logcol == 0 && c != ';' && c != '\n') {
			exclude = ~TERM;
			include = COL0;
		}
		else if (logcol == 1 && c == ':') {
			exclude = ~TERM;
			logcol = 0;
		}

		logcol++;

		// Look for possible numbers.
		// 0x<hex> $<hex> <hex>h <octal>o <octal>q <binary>b
		// <decimal> <decimal>d
		// Suffix formats must start with 0-9.

		if (radix)
			radix = convert(tempbuf, p, &overflow);

		// If we're in the first logical column and the token starts with
		// '$' then we'll force it to be a label even though it could be
		// a $hex constant. This will allow $FCB as a label.
		// Thus we must also allow symbol lookup a chance to override number
		// parsing if we start with a '$'.

		if (tempbuf[0] == '$') {
			if (logcol == 1 || locate(tempbuf)->i_token) {
				if (radix > 0) {
					sprintf(detail, "warning: $hex constant '%s' interpreted as symbol", tempbuf);
					errwarn(warn_hex, detail);
				}
				radix = 0;
			}
		}

		if (radix > 0) {
			// Might be line skipping time, though.
			if (*ifptr)
				return skipline(c);

			if (overflow) {
				err[iflag]++;
				yylval.ival = 0;
			}
			return NUMBER;
		}

		// Too late to do '$' concatenation of numbers.  But zmac
		// didn't allow for that previously at any rate.
		if (zcompat) {
			char *q = tempbuf;
			// Normal zmac operation requires we ignore $ in identifiers
			for (p = q; *p; p++)
				if (*p != '$')
					*q++ = *p;

			*q = '\0';
			p = q;
		}

		// GWP - boy, this should be a warning or error
		if (p - tempbuf > MAXSYMBOLSIZE) {
			p = tempbuf + MAXSYMBOLSIZE;
			*p = '\0';
		}

		token = tokenofitem(UNDECLARED, exclude, include);

		// Initial "priming" hack

		if (endc == '\'')
		{
			//printf("allowing <<%s%c>> at %d, endc=%c\n", tempbuf, peekc, logcol, endc);
			peekc = NOPEEK;
// A step towards emitting the instructions
#if 0
			// Only if auto-exx on on...
			if (tempbuf[0] == 'a') {
				emit1(8, 0, 0, ET_NOARG);
				list_out(dollarsign, "\tex\taf,af'\n", '*');
			}
			else {
				emit1(0xd9, 0, 0, ET_NOARG);
				list_out(dollarsign, "\texx\n", '*');
			}
#endif
		}

		return token;

	default:
		if (*ifptr)
			return(skipline(c));

		if (mras && getcol() == 1 && c == '*')
			goto spectok;

		switch(c) {
		int corig;
		case ':':
			if (logcol == 1) {
				// Make sure "label:ret", "label: ret",
				// "label: :ret", "label: : ret" work out OK.
				// But stop fooling around once we've done the VERB
				peekc = nextchar();
				if (charclass[peekc] == SPACE)
					logcol--;
			}
			return c;
		case ';':
			return(skipline(c));
		case '\'':
		case '"':
			sep = c;
			p = tempbuf;
			p[1] = 0;
			do	switch(c = nextchar())	{
			case '\0':
			case '\n':
				err[bflag]++;
				goto retstring;
			default:
				if (c == sep && (c = nextchar()) != sep) {
				retstring:
					peekc = c;
					*p = '\0';
					switch (p - tempbuf) {
					case 2:
						p = tempbuf;
						yylval.ival = *p++ & 255;
						yylval.ival |= (*p & 255) << 8;
						return TWOCHAR;
					case 1:
						p = tempbuf;
						yylval.ival = *p++;
						return ONECHAR;
					case 0:
						if (!full_exprs) {
							yylval.ival = 0;
							return NUMBER;
						}
						// fall through
					default:
						yylval.cval = tempbuf;
						return STRING;
					}
				}
				*p++ = c;
			} while (p < tempmax);
			/*
			 *  if we break out here, our string is longer than
			 *  our input line
			 */
			error("string buffer overflow");
		case '<':
			corig = c;
			switch (c = nextchar ()) {
			case '=':
				return LE;
			case '<':
				return SHL;
			case '>':
				return NE;
			default:
				peekc = c;
				return corig;
			}
			/* break; suppress "unreachable" warning for tcc */
		case '>':
			corig = c;
			switch (c = nextchar ()) {
			case '=':
				return GE;
			case '>':
				return SHR;
			default:
				peekc = c;
				return corig;
			}
			/* break; suppress "unreachable" warning for tcc */
		case '!':
			corig = c;
			switch (c = nextchar ()) {
			case '=':
				return NE;
			default:
				peekc = c;
				return corig;
			}
			/* break; suppress "unreachable" warning for tcc */
		case '=':
			corig = c;
			switch (c = nextchar ()) {
			case '=':
				return '=';
			default:
				peekc = c;
				return corig;
			}
			/* break; suppress "unreachable" warning for tcc */

		case '&':
			corig = c;
			if ((c = nextchar()) == '&')
				return ANDAND;
			else {
				peekc = c;
				return corig;
			}
			/* break; suppress "unreachable" warning for tcc */
		case '|':
			corig = c;
			if ((c = nextchar()) == '|')
				return OROR;
			else {
				peekc = c;
				return corig;
			}
			/* break; suppress "unreachable" warning for tcc */
		default:
			return(c);
		}
	}
}

// Convert string to number
// 0x<hex> $<hex> <hex>h <octal>o <octal>q <binary>b
// <decimal> <decimal>d
// Suffix formats must start with 0-9.
//
// Returns:
//	-1	not numeric
//	0	numeric but digit out of range
//	>0	radix of number,  yylval.ival holds value

int convert(char *buf, char *bufend, int *overflow)
{
	int radix = -1, dummy;
	char *d0, *dn;

	if (!bufend)
		bufend = strchr(buf, '\0');

	if (!overflow)
		overflow = &dummy;

	if (buf[0] == '0' && buf[1] == 'x' && buf[2]) {
		radix = 16;
		d0 = buf + 2;
		dn = bufend;
	} else if (buf[0] == '$') {
		radix = 16;
		d0 = buf + 1;
		dn = bufend;
	}
	else if (buf[0] >= '0' && buf[0] <= '9') {
		d0 = buf;
		dn = bufend - 1;
		switch (*dn) {
		case 'o':
		case 'q':
			radix = 8;
			break;
		case 'd':
			radix = 10;
			break;
		case 'h':
			radix = 16;
			break;
		case 'b':
			radix = 2;
			break;
		default:
			radix = 10;
			dn++;
		}
	}

	// We may have a number on our hands.
	if (radix > 0) {
		*overflow = 0;
		yylval.ival = 0;

		for (; d0 < dn; d0++) {
			unsigned int ovchk = (unsigned int)yylval.ival;
			int c = *d0 - (*d0 > '9' ? ('a' - 10) : '0');
			if (c < 0 || c >= radix) {
				radix = 0;
				break;
			}
			if (ovchk * radix / radix != ovchk)
				*overflow = 1;

			yylval.ival *= radix;
			yylval.ival += c;
		}
	}

	return radix;
}

// Verify keytab is in alphabetical order.
// And that all MRASOP keywords start with '.'

int check_keytab()
{
	int i;
	char *prev;

	for (i = 0; i < sizeof(keytab) / sizeof(keytab[0]); i++) {
		char *next = keytab[i].i_string;
		next += *next == '.';
		if (i != 0) {
			if (strcmp(prev, next) >= 0) {
				printf("keytab error: %s >= %s\n", prev, next);
				return 0;
			}
		}
		prev = next;

		if ((keytab[i].i_uses & MRASOP) && keytab[i].i_string[0] != '.') {
			printf("keytab error: %s does not start with '.'\n",
				keytab[i].i_string);
			return 0;
		}
	}

	printf("keytab OK\n");

	return 1;
}


struct item *keyword(char *name)
{
	int  r, l, u;
	struct item *ip;

	/*
	 *  binary search
	 */
	l = 0;
	u = (sizeof keytab/sizeof keytab[0])-1;
	while (l <= u) {
		char *key;
		i = (l+u)/2;
		ip = &keytab[i];
		key = ip->i_string;
		r = strcmp(name + (name[0] == '.'), key + (key[0] == '.'));
		if (r == 0) {
			// Do not allow ".foo" to match "foo"
			if (name[0] == '.' && key[0] != '.')
				break;

			return ip;
		}
		if (r < 0)
			u = i-1;
		else
			l = i+1;
	}

	return 0;
}

// Find 'name' in an item table.  Returns an empty slot if not found.
// Uses case-independent comparisions which are largely wasted as
// there is only 1 case where 'name' has not already been lowercased.

struct item *item_lookup(char *name, struct item *table, int table_size)
{
	struct item *ip;
	/*
	 *  hash into item table
	 */
	int hash = 0;
	char *p = name;
	while (*p) {
		char ch = *p++;
		if (ch >= 'A' && ch <= 'Z') ch += 'a' - 'A';
		hash += ch;
	}
	hash %= table_size;
	ip = &table[hash];

	for (;;) {
		if (ip->i_token == 0)
			break;
		if (ci_strcmp(name, ip->i_string) == 0)
			break;
		if (++ip >= table + table_size)
			ip = table;
	}

	return ip;
}

struct item *locate(char *name)
{
	return item_lookup(name, itemtab, ITEMTABLESIZE);
}

// Return the longest token that matches the start of the given name.
// Currently used for MRAS which will substitute macro parameters inside
// identifiers.
struct item *item_substr_lookup(char *name, int token, struct item *table, int table_size)
{
	struct item *ip = 0;
	int i;

	for (i = 0; i < table_size; i++) {
		int len;

		if (table[i].i_token != token)
			continue;

		len = strlen(table[i].i_string);
		if (ci_strcompare(name, table[i].i_string, len) == 0) {
			if (!ip || len > strlen(ip->i_string)) {
				ip = table + i;
			}
		}
	}

	return ip;
}

/*
 *  return the token associated with the string pointed to by
 *  tempbuf.  if no token is associated with the string, associate
 *  deftoken with the string and return deftoken.
 *  in either case, cause yylval to point to the relevant
 *  symbol table entry.
 *
 *  Only keys not matching the keyexclude will be returned allowing
 *  context-dependent tokenization.  Unless they match keyinclude.
 */

int tokenofitem(int deftoken, int keyexclude, int keyinclude)
{
	struct item *ip;
	int  i;

#ifdef T_DEBUG
	fputs("'tokenofitem entry'	", stderr) ;
	fputs(tempbuf, stderr) ;
#endif

	// Allow macros to override built-ins
	// Maybe shouldn't be done for identifiers that will undergo
	// '.' and '_' expansion.
	ip = locate(tempbuf);
	if (ip->i_token == MNAME)
		goto found;

	if (full_exprs)
		keyexclude = ~TERM;

	ip = keyword(tempbuf);
	if (ip) {
		if (ip->i_uses & keyinclude)
			goto found;

		if (!(ip->i_uses & keyexclude))
			goto found;
	}

	// This is really my own thing rather than old zmac, but zmac
	// didn't support it and it does depend on '$' crushing a bit.
	if (zcompat) {
	    // '_' prefixed labels are local to the file
	    if (tempbuf[0] == '_') {
		    strcat(tempbuf, "$");
		    strcat(tempbuf, basename(src_name[now_in]));
	    }

	    // '.' prefixed labels are local between labels
	    if (tempbuf[0] == '.') {
		    char *p = tempbuf;
		    while (*p) p++;
		    sprintf(p, "$%d", llseq);
	    }
	}

	ip = locate(tempbuf);

	if (ip->i_token)
		goto found;

	if (!deftoken) {
		i = 0 ;
		goto token_done ;
	}
	if (++nitems > ITEMTABLESIZE-20)
		error("item table overflow");
	ip->i_string = malloc(strlen(tempbuf)+1);
	ip->i_token = deftoken;
	ip->i_uses = 0;
	strcpy(ip->i_string, tempbuf);

found:
	if (*ifptr) {
		if (ip->i_token == ENDIF_TK) {
			i = ENDIF_TK;
			goto token_done ;
		}
		if (ip->i_token == ELSE_TK) {
			/* We must only honour the ELSE if it is not
			   in a nested failed IF/ELSE */
			char forbid = 0;
			char *ifstackptr;
			for (ifstackptr = ifstack; ifstackptr != ifptr; ++ifstackptr) {
				if (*ifstackptr) {
					forbid = 1;
					break;
				}
			}
			if (!forbid) {
				i = ELSE_TK;
				goto token_done;
			}
		}
		if (ip->i_token == IF_TK || ip->i_token == IF_DEF_TK) {
			if (ifptr >= ifstmax)
				error("Too many ifs");
			else *++ifptr = 1;
		}
		i = skipline(' ');
		goto token_done ;
	}
	yylval.itemptr = ip;
	i = ip->i_token;
token_done:
#ifdef T_DEBUG
	fputs("\t'tokenofitem exit'\n", stderr) ;
#endif
	return(i) ;
}

void itemcpy(struct item *dst, struct item *src)
{
	if (dst && src && dst != src) {
		dst->i_string = src->i_string;
		dst->i_value = src->i_value;
		dst->i_token = src->i_token;
		dst->i_uses = src->i_uses;
		dst->i_scope = src->i_scope;
		dst->i_chain = src->i_chain;
		dst->i_pass = src->i_pass;
	}
}

/*
 *  interchange two entries in the item table -- used by custom_qsort
 */
void interchange(int i, int j)
{
	struct item temp;

	itemcpy(&temp, itemtab + i);
	itemcpy(itemtab + i, itemtab + j);
	itemcpy(itemtab + j, &temp);
}



/*
 *  quick sort -- used by compactsymtab to sort the symbol table
 */
void custom_qsort(int m, int n)
{
	int  i, j;

	if (m < n) {
		i = m;
		j = n+1;
		for (;;) {
			do i++; while(strcmp(itemtab[i].i_string,
					itemtab[m].i_string) < 0);
			do j--; while(strcmp(itemtab[j].i_string,
					itemtab[m].i_string) > 0);
			if (i < j) interchange(i, j); else break;
		}
		interchange(m, j);
		custom_qsort(m, j-1);
		custom_qsort(j+1, n);
	}
}

int getcol()
{
	return inpptr - inpbuf;
}

/*
 *  get the next character
 */
int nextchar()
{
	int c, ch;
	unsigned char *p;
	char *getlocal();

	if (peekc != NOPEEK) {
		c = peekc;
		peekc = NOPEEK;
		return c;
	}

	if (inpptr) {
		int col = getcol();

		// Double nul indicates EOF for macros
		if (expptr && inpptr[0] == '\0' && inpptr[1] == '\0') {
			inpptr = 0;
			return 0;
		}

		if (col == 0) {
			void analyze_inpbuf(void);
			void mras_operator_separate(void);

			if (!expptr)
				linein[now_in]++;

			analyze_inpbuf();

			if (mras)
				mras_operator_separate();
		}

		if (inpbuf_insert[col]) {
			c = inpbuf_insert[col];
			inpbuf_insert[col] = '\0';
		}
		else {
			c = *inpptr++;
			addtoline(c);
		}

		if (*inpptr == '\0')
			inpptr = 0;

		return c;
	}

	inpptr = inpbuf;
	logcol = 0;
	p = inpbuf;

	// XXX - should check for input line overflow!

	// If invoking a macro then pull the next line from it.
	if (expptr) {
		for (;;) {
			ch = getm();

			if (ch == '\1') { /* expand argument */
				ch = getm() - 'A';
				if (ch >= 0 && ch < PARMMAX && est[ch].param) {
					strcpy((char *)p, est[ch].param);
					p = (unsigned char *)strchr((char *)p, '\0');
				}
			}
			else if (ch == '\2') {	/*  local symbol  */
				ch = getm() - 'A';
				if (ch >= 0 && ch < PARMMAX && est[ch].param)
					strcpy((char *)p, est[ch].param);
				else
					strcpy((char *)p, getlocal(ch, est[TEMPNUM].value));

				p = (unsigned char *)strchr((char *)p, '\0');
			}
			else {
				if (ch == 0)
					break;

				*p++ = ch;

				if (ch == '\n')
					break;
			}
		}
		*p = '\0';
		p[1] = ch;
	}
	else {
		for (;;) {
			ch = nextline_peek != NOPEEK ? nextline_peek : getc(now_file);
			nextline_peek = NOPEEK;

			if (ch == '\r') {
				nextline_peek = getc(now_file);
				if (nextline_peek == '\n')
					nextline_peek = NOPEEK;

				ch = '\n';
			}

			if (ch == EOF)
				break;

			*p++ = ch;

			if (ch == '\n') 
				break;
		}

		*p = '\0';

		/* if EOF, check for include file */
		if (ch == EOF) {
			if (now_in) {
				fclose(fin[now_in]) ;
				free(src_name[now_in]);
				now_file = fin[--now_in];
				nextline_peek = linepeek[now_in];
			}
			else if (p == inpbuf)
				return 0;
	
			if (linein[now_in] < 0) {
				lstoff = 1;
				linein[now_in] = -linein[now_in];
			} else {
				lstoff = 0 ;
			}

			if (outpass) {
				if (iflist()) {
					lineout();
					fprintf(fout, "**** %s ****\n", src_name[now_in]) ;
				}
				if (bopt)
					fprintf(fbds, "%04x %04x f %s\n", dollarsign, emit_addr, src_name[now_in]);
			}

			if (p != inpbuf) {
				*p++='\n';
				*p = '\0';
			}
			else
				inpptr = 0;
		}
	}

	return nextchar();
}

char *skipspace(char *p)
{
	while (CHARCLASS(*p) == SPACE)
		p++;

	return p;
}

// Look at inpbuf and try to determine what logical column we are starting
// at.  We could put all of the work in here and keep yylex simple but for
// now we share the load.

void analyze_inpbuf(void)
{
	int cc;
	char *p, *q, save;
	char *word1, *word2;
	struct item *ip, *word1item;
	int triplecase = 1;

	// No need to do this when pulling in data for a macro.  In fact,
	// in can be harmful to undef a macro.
	if (inmlex)
		return;

	// Default if we find nothing to override
	logcol = 0;

	// One case to check is when you start with whitespace yet there are
	// 3 columns.  If so then we change logcol to -1 to compensate.
	// If the 2nd column is a VERB.

	// If we start with whitespace then we can give up on triple word case.
	p = (char *)inpbuf;
	if (CHARCLASS(*p) != SPACE)
		triplecase = 0;

	p = skipspace(p);
	word1 = p;

	// Now skip over a token or abort if we don't find one

	cc = CHARCLASS(*p);
	if (cc != LETTER && cc != STARTER && cc != DIGIT && cc != DOLLAR)
		return;

	for (;;) {
		cc = CHARCLASS(*p);
		if (cc == LETTER || cc == STARTER || cc == DIGIT || cc == DOLLAR)
			p++;
		else
			break;
	}

	// We could skip space-separated colons now, but if we see a colon
	// both issues have been decided to do that because it is easier.
	if (*p == ':')
		return;

	save = *p;
	*p = '\0';
	word1item = locate(word1);
	*p = save;

	p = skipspace(p);

	// Another token to skip past.
	// But we need to examine it to see if it is a verb.

	cc = CHARCLASS(*p);
	if (cc != LETTER && cc != STARTER && cc != DIGIT && cc != DOLLAR)
		return;

	q = p;
	word2 = p;
	for (;;) {
		cc = CHARCLASS(*p);
		if (cc == LETTER || cc == STARTER || cc == DIGIT || cc == DOLLAR)
			p++;
		else
			break;
	}

	// Now we have a second word we can check for the "name macro" case.
	// Unless we're skipping.
	save = *p;
	*p = '\0';
	if (ci_strcmp(word2, "macro") == 0 && word1item->i_token && !*ifptr)
		word1item->i_token = UNDECLARED;

	*p = save;

	if (!triplecase)
		return;

	// Must have space to skip over
	if (CHARCLASS(*p) != SPACE)
		return;

	// This 2nd token must be a verb.
	cc = *p;
	*p = '\0';
	ip = keyword(q);
	*p = cc;
	if (!ip || !(ip->i_uses & VERB))
		return;

	// Now skip over space.  If there's anything but a comment or end
	// of the line then we've may have 3 logical columns.
	// "ld a, 5" can throw that off, but we've done the verb check.

	p = skipspace(p);

	if (*p != ';' && *p != '\n' && *p != '\0')
		logcol--;
}

void mras_operator_separate(void)
{
	int i, sep;

	// Only do operator separation after macro expansion.
	if (inmlex)
		return;

	// Apply operator separation across the entire line.
	// We could limit this to logical columns if need be,
	// but I imagine MRAS didn't allow "x.mod.y" as a label
	// or macro name.

	// Strings are handled in a simple but largly compatible way.
	// AF' is a problem which can be safely ignored since its appearance
	// will mean no expression is present.
	// My allowed salting of ' after identifiers is another matter.
	// But, again, original MRAS code won't do that.

	memset(inpbuf_insert, 0, strlen((char *)inpbuf));

	sep = '\0';
	for (i = 0; inpbuf[i]; i++) {
		int j;

		if (inpbuf[i] == sep) {
			sep = '\0';
			continue;
		}

		if (inpbuf[i] == '\'' || inpbuf[i] == '"')
			sep = inpbuf[i];

		// Don't do anthing if inside a string constant.
		if (sep)
			continue;

		if (inpbuf[i] == ';')
			break;

		// Slight nod to efficiency.  Assumption is tested in
		// check_keytab().

		if (inpbuf[i] != '.')
			continue;

		for (j = 0; j < sizeof(keytab) / sizeof(keytab[0]); j++) {
			char *p = keytab[j].i_string;
			int len = strlen(p);

			if (!(keytab[j].i_uses & MRASOP))
				continue;

			if (ci_strcompare((char *)inpbuf + i, p, len) == 0) {
				// Only need to add spaces if we're possibly
				// in an identifier.  But no harm if we're not.
				inpbuf_insert[i] = ' ';
				inpbuf_insert[i + len] = ' ';
				i += len - 1;
				break;
			}
		}
	}
}


/*
 *  skip to rest of the line -- comments and if skipped lines
 */
int skipline(int ac)
{
	int  c;

	c = ac;
	while (c != '\n' && c != '\0')
		c = nextchar();
	return('\n');
}

void add_incpath(char *dir)
{
	char *p;

	if (incpath_cnt >= MAXINCPATH) {
		fprintf(stderr, "Sorry, can only handle %d include paths\n", MAXINCPATH);
		exit(1);
	}

	p = malloc(strlen(dir) + 1);
	strcpy(p, dir);

	incpath[incpath_cnt++] = dir;
}

FILE *open_incpath(char *filename, char *mode)
{
	char quote;
	int i;
	char path[1024];
	FILE *fp;

	// Due to the way parsing works the string can be specified
	// without quotes or will allow quotes but include them.  Instead
	// of fooling with the parsing I just strip the quotes.  I think
	// you can still include a file that starts with a single or double
	// quote by quoting it, but that's an awful thing to do to yourself.

	quote = *filename;
	if (quote == '"' || quote == '\'') {
		strcpy(filename, filename + 1);
		if (strrchr(filename, quote))
			*strrchr(filename, quote) = '\0';
	}

	// First look for included file in same directory as source file.

	strcpy(path, src_name[now_in]);
	*basename(path) = '\0';
	strcat(path, filename);
	fp = fopen(path, mode);
	if (fp) {
		if (note_depend && outpass)
			printf("%s\n", path);
		return fp;
	}

	for (i = 0; i < incpath_cnt; i++) {
		sprintf(path, "%s/%s", incpath[i], filename);
		fp = fopen(path, mode);
		if (fp) {
			if (note_depend && outpass)
				printf("%s\n", path);
			return fp;
		}
	}

	if (note_depend && outpass)
		printf("%s\n", filename);

	return fopen(filename, mode);
}

void version()
{
	fprintf(stderr, "zmac version " VERSION "\n");
}

//
// Print out a usage message and exit.
//
void usage(char *msg, char *param)
{
	fprintf(stderr, msg, param);
	fprintf(stderr, "\n");
	version();
	fprintf(stderr, "usage: zmac [-8bcefghijJlLmnopstz] [-I dir] [-Pk=n] file[.z]\n");
	fprintf(stderr, "other opts: --rel[7] --mras --zmac --dep --help --doc --version\n");
	fprintf(stderr, "  zmac -h for more detail about options.\n");
	exit(1);
}

void help()
{
	version();

	fprintf(stderr, "\t--version show version number\n");
	fprintf(stderr, "\t--help\tshow this help message\n");
	fprintf(stderr, "\t-8\tuse 8080 interpretation of mnemonics\n");
	fprintf(stderr, "\t-b\tno binary (.hex,.cmd,.cas, etc.) output\n");
	fprintf(stderr, "\t-c\tno cycle counts in listing\n");
	fprintf(stderr, "\t-e\terror list only\n");
	fprintf(stderr, "\t-f\tprint if skipped lines\n");
	fprintf(stderr, "\t-g\tdo not list extra code\n");
	fprintf(stderr, "\t-h\tshow this information about options and quit\n");
	fprintf(stderr, "\t-i\tdo not list include files\n");
	fprintf(stderr, "\t-I dir\tadd 'dir' to include file search path\n");
	fprintf(stderr, "\t-j\tpromote relative jumps to absolute as needed\n");
	fprintf(stderr, "\t-J\twarn when a jump could be relative\n");
	fprintf(stderr, "\t-l\tno list\n");
	fprintf(stderr, "\t-L\tforce listing of everything\n");
	fprintf(stderr, "\t-m\tprint macro expansions\n");
	fprintf(stderr, "\t-n\tput line numbers off\n");
	fprintf(stderr, "\t-o\tlist to standard output\n");
	fprintf(stderr, "\t-p\tput out four \\n's for eject\n");
	fprintf(stderr, "\t-s\tdon't produce a symbol list\n");
	fprintf(stderr, "\t-t\toutput error count instead of list of errors\n");
	fprintf(stderr, "\t-z\tuse Z-80 interpretation of mnemonics\n");
	fprintf(stderr, "\t-Pk=num\tset @@k to num before assembly (e.g., -P4=10)\n");
	fprintf(stderr, "\t--dep\tlist files included\n");
	fprintf(stderr, "\t--mras\tlimited MRAS/EDAS compatibility\n");
	fprintf(stderr, "\t--rel\toutput .rel file only (--rel7 for 7 character symbol names)\n");
	fprintf(stderr, "\t--zmac\tcompatibility with original zmac\n");
	fprintf(stderr, "\t--doc\toutput documentation as HTML file\n");

	exit(0);
}

int main(int argc, char *argv[])
{
	struct item *ip;
	int  i;
	int  files;
#ifdef DBUG
	extern  yydebug;
#endif

	fout = stdout ;
	fin[0] = stdin ;
	now_file = stdin ;
	files = 0;

	// Special flag for unit testing.
	if (argc > 1 && strcmp(argv[1], "--test") == 0)
		exit(!check_keytab());

	for (i=1; i<argc; i++) {
		int skip = 0;
		if (strcmp(argv[i], "--mras") == 0) {
			mras = 1;
			trueval = -1;
			continue;
		}

		if (strcmp(argv[i], "--rel") == 0) {
			relopt = 6;
			bopt = 0;
			continue;
		}

		if (strcmp(argv[i], "--rel7") == 0) {
			relopt = 7;
			bopt = 0;
			continue;
		}

		if (strcmp(argv[i], "--zmac") == 0) {
			zcompat = 1;
			continue;
		}

		if (strcmp(argv[i], "--dep") == 0) {
			note_depend = 1;
			continue;
		}

		if (strcmp(argv[i], "--help") == 0) {
			help();
			continue;
		}

		if (strcmp(argv[i], "--doc") == 0) {
			extern void doc(void);
			doc();
			exit(0);
			continue; // not reached
		}

		if (strcmp(argv[i], "--version") == 0) {
			version();
			exit(0);
			continue; // not reached
		}

		if (argv[i][0] == '-' && argv[i][1] == 'P' &&
			argv[i][2] >= '0' && argv[i][2] <= '9')
		{
			if (argv[i][3] == '=') {
				int overflow;
				int radix;
				int sign = 1;
				char *str = argv[i] + 4;
				if (*str == '-') {
					sign = -1;
					str++;
				}

				radix = convert(str, NULL, &overflow);
				if (radix <= 0 || overflow)
					usage("bad -Pn= parameter value", 0);

				mras_param[argv[i][2] - '0'] = sign * yylval.ival;
			}
			else if (argv[i][3] == '\0')
				mras_param[argv[i][2] - '0'] = -1;
			else
				usage("-Pn syntax error", 0);

			continue;
		}

		if (*argv[i] == '-') while (*++argv[i]) {
			switch(*argv[i]) {

			case '8':	/* Equivalent to .8080 */
				default_z80 = 0;
				continue;

			case 'b':	/*  no binary  */
				bopt = 0;
				continue;

			case 'c':	/*  no cycle counts in listing */
				copt-- ;
				continue;

#ifdef DBUG
			case 'd':	/*  debug  */
				yydebug++;
				continue;
#endif

			case 'e':	/*  error list only  */
				eopt = 0;
				edef = 0;
				continue;

			case 'f':	/*  print if skipped lines  */
				fopt++;
				fdef++;
				continue;

			case 'g':	/*  do not list extra code  */
				gopt = 0;
				gdef = 0;
				continue;

			case 'h':
				help();
				continue;

			case 'i':	/* do not list include files */
				iopt = 1 ;
				continue ;

			case 'I':
				if (argv[i][1])
					add_incpath(argv[i] + 1);
				else {
					i++;
					if (i < argc)
						add_incpath(argv[i]);
					else
						usage("missing argument to -I option", 0);
				}
				skip = 1;
				break;

			case 'l':	/*  no list  */
				lopt++;
				continue;

			case 'L':	/*  force listing of everything */
				lston++;
				continue;

			case 'j':	// promote relative jumps to absolute as needed
				default_jopt = 1;
				continue;

			case 'J':	// error when JR instructions could replace JP
				default_JPopt = 1;
				continue;

			case 'm':	/*  print macro expansions  */
				mdef++;
				mopt++;
				continue;

			case 'n':	/*  put line numbers off */
				nopt-- ;
				continue;

			case 'o':	/*  list to standard output  */
				oopt++;
				continue;

			case 'p':	/*  put out four \n's for eject */
				popt-- ;
				continue;

			case 'P':	// GWP - printer style output (headers, page separation, etc.)
				printer_output = 1;
				continue;

			case 's':	/*  don't produce a symbol list  */
				sopt++;
				continue;

			case 't':	/*  output only number of errors */
				topt = 0;
				continue;

			case 'z':	/* Equivalent to .z80 */
				default_z80 = 1;
				continue;

			default:	/*  error  */
				usage("Unknown option", 0);

			}
			if (skip)
				break;
		}
		else if (files++ == 0) {
			sourcef = argv[i];
			strcpy(src, sourcef);
			if ((now_file = fopen(src, "r")) == NULL) {
				if (!*getsuffix(src))
					suffix(src, ".z");
				if ((now_file = fopen(src, "r")) == NULL)
					usage("Cannot open source file '%s'", src);
			}
			now_in = 0;
			fin[now_in] = now_file ;
			src_name[now_in] = src ;
		} else if (files)
			usage("Too many arguments", 0);
	}


	if (files == 0)
		usage("No source file", 0);

	{
		char outdir[1025];
		outpath(outdir, sourcef, 0);
#ifdef WIN32
		_mkdir(outdir);
#else
		mkdir(outdir, 0777);
#endif
	}

	if (bopt) {
		outpath(bds, sourcef, ".bds");
		fbds = fopen(bds, "w");
		if (fbds == NULL)
			error("Cannot create .bds file");

		fprintf(fbds, "binary-debuggable-source\n");

		fprintf(fbds, "%04x %04x f %s\n", dollarsign, emit_addr, src_name[now_in]);

		outpath(oth, sourcef, ".cmd");
		fcmd = fopen(oth, "wb");
		if (fcmd == NULL)
			error("Cannot create .cmd file");

		outpath(oth, sourcef, ".cas");
		fcas = fopen(oth, "wb");
		if (fcas == NULL)
			error("Cannot create .cas file");

		outpath(oth, sourcef, ".lcas");
		flcas = fopen(oth, "wb");
		if (flcas == NULL)
			error("Cannot create .lcas file");

		// Tape header
		for (i = 0; i < 255; i++) {
			fputc(0, flcas);
			fputc(0x55, fcas);
		}
		fputc(0xA5, flcas);
		fputc(0x7F, fcas);
		casname(oth, sourcef, 6);
		putcas(0x55);
		for (i = 0; i < 6; i++)
			putcas(oth[i]);

		outpath(oth, sourcef, ".cim");
		fcim = fopen(oth, "wb");
		if (fcim == NULL)
			error("Cannot create .cim file");

		outpath(oth, sourcef, ".ams");
		fams = fopen(oth, "wb");
		if (fams == NULL)
			error("Cannot create .ams file");

		outpath(oth, sourcef, ".tap");
		ftap = fopen(oth, "wb");
		if (ftap == NULL)
			error("Cannot create .tap file");

		outpath(bin, sourcef, ".hex");
#ifdef MSDOS
		if (( fbuf = fopen(bin, "wb")) == NULL)
#else
		if (( fbuf = fopen(bin, "w")) == NULL)
#endif
			error("Cannot create .hex file");
	}
	else if (relopt) {
		outpath(oth, sourcef, ".rel");
		frel = fopen(oth, "wb");
		if (frel == NULL)
			error("Cannot create .rel file");

		strncpy(progname, basename(sourcef), sizeof progname);
		progname[sizeof progname - 1] = '\0';
	}
	if (!lopt && !oopt) {
		outpath(listf, sourcef, ".lst");
		if ((fout = fopen(listf, "w")) == NULL)
			error("Cannot create list file");
	} else
		fout = stdout ;
	outpath(mtmp, sourcef, ".tmp");
#ifdef MSDOS
	mfile = mfopen(mtmp,"w+b") ;
#else
	mfile = mfopen(mtmp,"w+") ;
#endif
	if (mfile == NULL) {
		error("Cannot create temp file");
	}
	/*unlink(mtmp);*/

	/*
	 *  get the time
	 */
	time(&now);
	timp = ctime(&now);
	timp[16] = 0;
	timp[24] = 0;

	title = sourcef;
	/*
	 * pass 1
	 */
#ifdef DEBUG
	fputs("DEBUG-pass 1\n", stderr) ;
#endif
	clear();
	setvars();
	npass = 1;
	outpass = 0;
	yyparse();

	// GWP - errors should stop us, but the listing is very useful.

	pass2++;

	for (npass = 2; npass < MAXPASS; npass++) {
		if (passfail || npass == MAXPASS - 1)
			outpass = 1;

		if (outpass) {
			putrelcmd(RELCMD_PROGNAME);
			putrelname(progname);
		}

		ip = itemtab;
		ip--;
		while (++ip < itemmax) {
			// Output list of public labels.  m80 will let
			// equates and aseg values be public so we do, too.
			if (outpass && ip->i_token && (ip->i_scope & SCOPE_PUBLIC)) {
				putrelcmd(RELCMD_PUBLIC);
				putrelname(ip->i_string);
			}

			/* reset use count */
			ip->i_uses = 0 ;

			/* set macro names, equated and defined names */
			switch	(ip->i_token) {
			case MNAME:
				ip->i_token = UNDECLARED;
				break;

			case EQUATED:
				ip->i_token = WASEQUATED;
				break;

			case DEFLED:
				if (zcompat)
					ip->i_token = UNDECLARED;
				break;
			}
		}

		if (outpass) {
			// m80 outputs data size as an absolute value, but
			// code size as code segment relative.  Odd, but
			// I'll follow suit.
			putrelcmd(RELCMD_DATASIZE);
			putrelsegref(SEG_ABS, seg_size[SEG_DATA]);

			putrelcmd(RELCMD_CODESIZE);
			putrelsegref(SEG_CODE, seg_size[SEG_CODE]);
		}

		// In case we hit 'end' inside an included file
		while (now_in > 0) {
			fclose(fin[now_in]);
			free(src_name[now_in]);
			now_file = fin[--now_in];
			nextline_peek = linepeek[now_in];
		}
		setvars();
		fseek(now_file, (long)0, 0);

	#ifdef DEBUG
		fprintf(stderr, "DEBUG- pass %d\n", npass) ;
	#endif

		yyparse();

		if (outpass || passfail)
			break;

		if (!passretry)
			outpass = 1;
	}

	if (bopt) {
		flushbin();
		flushoth();
		putc(':', fbuf);
		if (xeq_flag) {
			puthex(0, fbuf);
			puthex(xeq >> 8, fbuf);
			puthex(xeq, fbuf);
			puthex(1, fbuf);
			puthex(255-(xeq >> 8)-xeq, fbuf);
			fprintf(fcmd, "%c%c%c%c", 2, 2, xeq, xeq >> 8);
			fflush(fcmd);
			putcas(0x78);
			putcas(xeq);
			putcas(xeq >> 8);
		} else
			for	(i = 0; i < 10; i++)
				putc('0', fbuf);
		putc('\n', fbuf);
		fflush(fbuf);
		// "Play Cas" seems to require trailing zeros to work
		// properly.  And we need to output at least one zero byte
		// to flush out the final high speed bits.
		for (i = 0; i < 6; i++)
			putcas(0);
	}

	if (relopt) {
		struct item *ip;
		// Output external symbols and value of public symbols
		for (ip = itemtab; ip < itemmax; ip++) {
			if (ip->i_token == UNDECLARED && (ip->i_scope & SCOPE_EXTERNAL)) {
				putrelcmd(RELCMD_EXTCHAIN);
				// Chain value will have top two bits set appropriately
				putrelextaddr(ip->i_chain);
				putrelname(ip->i_string);
			}
			if (ip->i_scope & SCOPE_PUBLIC)
			{
				putrelcmd(RELCMD_PUBVALUE);
				putrelsegref(ip->i_scope, ip->i_value);
				putrelname(ip->i_string);
			}
		}

		// End module, entry address if any
		putrelcmd(RELCMD_ENDMOD);
		putrelextaddr(rel_main);
		flushrel(); // byte alignment expected after end module

		// End .rel file
		putrelcmd(RELCMD_ENDPROG);
		flushrel();
	}

	if (xeq_flag == 0) {
#if WIN32
		char *username = getenv("USERNAME");
		if (username && strcmp(username, "George") == 0 && !relopt) {
			CONSOLE_SCREEN_BUFFER_INFO inf;
			HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
			GetConsoleScreenBufferInfo(hOut, &inf);
			SetConsoleTextAttribute(hOut, FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_INTENSITY);
			fprintf(stderr, "Warning: no entry address (forgot \"end label\")\n");
			fflush(stderr);
			SetConsoleTextAttribute(hOut, inf.wAttributes);
		}
#endif
	}
	else if (bopt) {
		fprintf(fbds, "%04x e\n", xeq);
	}

	if (bopt) {
		int low = 0;
		int high = sizeof(memory) - 1;
		int chk;
		int filelen;
		char leafname[] = "FILENAMEBIN";

		while (low < sizeof(memory) && (memflag[low] & (MEM_INST | MEM_DATA)) == 0)
			low++;

		while (high >= 0 && (memflag[high] & (MEM_INST | MEM_DATA)) == 0)
			high--;

		if (high >= low)
			fwrite(memory + low, high + 1 - low, 1, fcim);

		// AMSDOS binary file output (A for Amstrad, code from zmac 1.3)
		filelen = (high + 1) - low;

		chk = 0;
		putc(0, fams);
		for (i = 0; i < 11; i++) {
			putc(leafname[i], fams);
			chk += leafname[i];
		}
		for (i = 0; i < 6; i++)
			putc(0, fams);

		putc(2, fams); // Unprotected binary
		chk += 2;
		putc(0, fams);
		putc(0, fams);
		putc(low & 0xff, fams);
		chk += low & 0xff;
		putc(low >> 8, fams);
		chk += low >> 8;
		putc(0, fams);
		putc(filelen & 0xff, fams);
		chk += filelen & 0xff;
		putc(filelen >> 8, fams);
		chk += filelen >> 8;
		putc(xeq & 0xff, fams);
		chk += xeq & 0xff;
		putc(xeq >> 8, fams);
		chk += xeq >> 8;
		for (i = 28; i < 64; i++)
			putc(0, fams);

		putc(filelen & 0xff, fams);
		chk += filelen & 0xff;
		putc(filelen >> 8, fams);
		chk += filelen >> 8;
		putc(0, fams); // this would be used if filelen > 64K
		putc(chk & 0xff, fams);
		putc(chk >> 8, fams);

		for (i = 69; i < 128; i++)
			putc(0, fams);

		if (filelen > 0)
			fwrite(memory + low, filelen, 1, fams);

		if (filelen & 0x7f)
			putc(0x1a, fams); // CP/M EOF character

		write_tap(filelen, low, memory + low);
	}

	if (bopt) {
		struct item *tp;

		for (tp = itemtab; tp < itemmax; tp++) {
			if (tp->i_token == LABEL)
				fprintf(fbds, "%04x a %s\n", tp->i_value, tp->i_string);
			else if (tp->i_token == EQUATED)
				fprintf(fbds, "%04x v %s\n", tp->i_value, tp->i_string);
		}
	}

	if (!lopt)
		fflush(fout);
	if (writesyms)
		outsymtab(writesyms);
	compactsymtab();
	if (eopt)
		erreport();
	if (!lopt && !sopt)
		putsymtab();
	if (!lopt) {
		eject();
		fflush(fout);
	}
	// GWP - some things (like balance errors in macro definitions) do
	// not show up until you use them.  So just in case we print an error
	// count here as not to confuse the programmer who is unlikely to check
	// the listing for errors if none are shown in the command window.
	if (counterr() > 0)
		fprintf(stderr, "%d errors (see listing if no diagnostics appeared here)\n", counterr());
	if (countwarn() > 0)
		fprintf(stderr, "%d warnings (see listing if no diagnostics appeared here)\n", countwarn());
	exit(counterr() > 0);
}

void equate(char *id, int value)
{
	struct item *it;

	it = locate(id);
	if (!it->i_token) {
		nitems++;
		it->i_value = value;
		it->i_token = EQUATED;
		it->i_pass = npass;
		it->i_scope = SCOPE_BUILTIN;
		it->i_uses = 0;
		it->i_string = malloc(strlen(id)+1);
		strcpy(it->i_string, id);
	}
}

/*
 *  set some data values before each pass
 */
void setvars()
{
	int  i;

	peekc = NOPEEK;
	inpptr = 0;
	nextline_peek = NOPEEK;
	raw = 0;
	linein[now_in] = linecnt = 0;
	exp_number = 0;
	emitptr = emitbuf;
	lineptr = linebuf;
	ifptr = ifstack;
	*ifptr = 0;
	dollarsign = 0;
	emit_addr = 0;
	olddollar = 0;
	oldothdollar = 0;
	phaseflag = 0;
	for (i=0; i<FLAGS; i++) err[i] = 0;
	tstates = 0;
	ocf = 0;
	llseq = 0;
	passfail = 0;
	passretry = 0;
	njrpromo = 0;
	jopt = default_jopt;
	JPopt = default_JPopt;
	strcpy(modstr, "@@@@");
	segment = SEG_CODE;
	memset(seg_pos, 0, sizeof(seg_pos));
	memset(seg_size, 0, sizeof(seg_size));
	segchange = 0;
	z80 = default_z80;
	outrec = 0;

	param_parse = 0;
	arg_reset();

	mfptr = 0;
	mfseek(mfile, mfptr, 0);

	// These are slighly harmful, but not too bad.  Only
	// absolutely necessary for MAC compatibility.  But there's
	// some use in having them available always.

	equate("b", 0);
	equate("c", 1);
	equate("d", 2);
	equate("e", 3);
	equate("h", 4);
	equate("l", 5);
	equate("m", 6);
	equate("a", 7);

	equate("sp", 6);
	equate("psw", 6);

	// There are a large number of symbols to add to support
	// "LXI H,MOV" and the like.

	// Technically only MRAS has these, but I'll wait and see if
	// anyone actually uses @@0 through @@9.  If so, then we can
	// DEFL them instead of EQU.
	for (i = 0; i < 10; i++) {
		char var[4];
		var[0] = '@';
		var[1] = '@';
		var[2] = '0' + i;
		var[3] = '\0';
		equate(var, mras_param[i]);
	}
}

//
// Clear out cycle counts and memory.
//

void clear()
{
	int i;

	for (i = 0; i < sizeof(memory) / sizeof(memory[0]); i++)
	{
		memory[i] = 0;
		memflag[i] = 0;
		tstatesum[i] = 0;
	}
}

void setmem(int addr, int value, int type)
{
	value &= 0xff;
	memory[addr] = value;
	memflag[addr] |= type;
}

/*
 *  print out an error message and die
 */
void error(char *as)
{
	*linemax = 0;
	fprintf(fout, "%s\n", linebuf);
	fflush(fout);
	fprintf(stderr, "%s\n", as) ;
	exit(1);
}


/*
 * Compact the symbol table, removing unused, UNDECLARED entries,
 * macros and built-in identifiers.
 */
void compactsymtab()
{
	struct item *tp, *fp;

	if (!nitems)
		return;

	tp = itemtab;
	tp--;
	for (fp = itemtab; fp<itemmax; fp++) {
		if (fp->i_token == UNDECLARED && !(fp->i_scope & SCOPE_EXTERNAL)) {
			nitems--;
			continue;
		}
		if (fp->i_token == 0)
			continue;

		// Don't list macros or internally defined symbols
		if (fp->i_token == MNAME || (fp->i_scope & SCOPE_BUILTIN)) {
			nitems--;
			continue;
		}

		tp++;
		itemcpy(tp, fp);
	}

	tp++;
	tp->i_string = "{";	/* } */

	/*  sort the table */
	custom_qsort(0, nitems-1);
}

/*
 *  output the symbol table
 */
void putsymtab()
{
	int  i, j, k, t, rows;
	char c, c1, seg = ' ';
	int numcol = printer_output ? 4 : 1;
	struct item *tp;

	if (!nitems)
		return;

	title = "**  Symbol Table  **";

	rows = (nitems+numcol-1) / numcol;
	if (rows+5+line > 60)
		eject();
	lineout();
	fprintf(fout,"\n\n\nSymbol Table:\n\n") ;
	line += 4;

	for (i=0; i<rows; i++) {
		for(j=0; j<numcol; j++) {
			k = rows*j+i;
			if (k < nitems) {
				tp = &itemtab[k];
				t = tp->i_token;
				c = ' ' ;
				if (t == EQUATED || t == DEFLED)
					c = '=' ;
				if (tp->i_uses == 0)
					c1 = '+' ;
				else
					c1 = ' ' ;

				// GWP - decided I don't care about uses
				// even if it were accurate.
				// TODO: Should use maxsymbol size in there,
				// but makes output harder to read.

				fprintf(fout, "%-15s%c", tp->i_string, c);

				if (relopt)
					seg = SEGCHAR(tp->i_scope & SCOPE_SEGMASK);

				if (tp->i_value >> 16)
					fprintf(fout, "%8x%c", tp->i_value, seg);
				else
					fprintf(fout, "%4x%c    ", tp->i_value & 0xffff, seg);

				if (tp->i_scope & SCOPE_EXTERNAL)
					fprintf(fout, " (extern)");

				if (tp->i_scope & SCOPE_PUBLIC)
					fprintf(fout, " (public)");
			}
		}
		lineout();
		putc('\n', fout);
	}
}




/*
 *  put out error report
 */
void erreport()
{
	int i, numerr, numwarn;

	if (line > 49) eject();
	lineout();
	numerr = 0;
	for (i=0; i<FIRSTWARN; i++) numerr += keeperr[i];
	numwarn = 0;
	for (i = FIRSTWARN; i < FLAGS; i++) numwarn += keeperr[i];
	if (numerr || numwarn) {
		fputs("\n\n\nError + Warning report:\n\n", fout);
		fprintf(fout, "%6d errors\n", numerr);
		fprintf(fout, "%6d warnings\n", numwarn);
		line += 6;
	} else {
		fputs("\n\n\nStatistics:\n", fout);
		line += 3;
	}

	for (i=0; i<FLAGS; i++)
		if (keeperr[i]) {
			lineout();
			fprintf(fout, "%6d %c -- %s %s\n",
				keeperr[i], errlet[i], errname[i],
				i < FIRSTWARN ? "error" : "warnings");
		}

	if (line > 52) eject();
	lineout();
	fprintf(fout, "\n%6d\tpasses\n", npass);
	fprintf(fout, "%6d\tjr promotions\n", njrpromo);
	fprintf(fout, "%6d\tsymbols\n", nitems);
	fprintf(fout, "%6d\tbytes\n", nbytes);
	line += 4;
	if (mfptr) {
		if (line > 53) eject();
		lineout();
		fprintf(fout, "\n%6d\tmacro calls\n", exp_number);
		fprintf(fout, "%6d\tmacro bytes\n", mfptr);
		fprintf(fout, "%6d\tinvented symbols\n", invented/2);
		line += 3;
	}
}

/*
 * count errors (GWP - added to set exit code)
 */
int counterr()
{
	int i, numerr = 0;
	for (i=0; i<FIRSTWARN; i++) numerr += keeperr[i];
	return numerr;
}

// Count warnings
int countwarn()
{
	int i, numwarn = 0;
	for (i = FIRSTWARN; i < FLAGS; i++)
		numwarn += keeperr[i];
	return numwarn;
}

char *mlook;

int nextmac()
{
	int ch;

	if (mlook) {
		if (*mlook) {
			ch = *mlook++;
			addtoline(ch);
		}
		else
			mlook = 0;
	}

	if (!mlook)
		ch = nextchar();

	return ch;
}

void putm_param_ref(struct item *param);
void putm_str(char *str, int look_for_param);

/*
 *  lexical analyser for macro definition
 */
void mlex(char *look)
{
	char  *p;
	int  c;
	int  t;
	int quote = 0, ampdrop = 0;
	struct item *param, *key;
	char symbuf[TEMPBUFSIZE];
	char *symbufmax = symbuf+TEMPBUFSIZE-1;

	/*
	 *  move text onto macro file, changing formal parameters
	 */
#ifdef	M_DEBUG
	fprintf(stderr,"enter 'mlex' at %d\n", mfptr) ;
#endif
	inmlex++;

	mlook = look;

	c = nextmac();
	for (;;) {
		int octo = 0, amp = 0, caret = 0;

		if (c == '#' || c == '&' || c == '^') {
			int esc = c;
			c = nextmac();
			if (charclass[c] != STARTER && charclass[c] != LETTER) {
				if (esc != '&' || !ampdrop)
					putm(esc);
				ampdrop = 0;
				continue;
			}
			if (esc == '#')
				octo = 1;
			else if (esc == '&')
				amp = 1;
			else
				caret = 1;
		}

		switch(charclass[c]) {

		case DIGIT:
			while (numpart[c]) {
				putm(c);
				c = nextmac();
			}
			continue;

		case STARTER:
		case LETTER:
			t = 0;
			p = symbuf;
			do {
				if (p >= symbufmax) {
					*symbufmax = '\0';
					printf("was parsing '%s' in macro definition\n", tempbuf);
					error(symlong);
				}
				*p++ = c;
				if (t < MAXSYMBOLSIZE)
					tempbuf[t++] = (c >= 'A' && c <= 'Z')  ?
						c+'a'-'A' : c;
				c = nextmac();
			} while	(charclass[c]==LETTER || charclass[c]==DIGIT || charclass[c]==STARTER);

			tempbuf[t] = 0;
			*p++ = '\0';
			p = symbuf;

			key = keyword(tempbuf);
			t = key ? key->i_token : 0;

			// Hmmm, that "item_lookup" is putting crap in the table, yes?
			if (mras)
				param = item_substr_lookup(tempbuf, MPARM, paramtab, PARAMTABSIZE);
			else
				param = item_lookup(tempbuf, paramtab, PARAMTABSIZE);

			// Accept almost anything as a parameter.  But a few
			// keywords will just screw things up royally.
			if (param && t != ENDM && t != REPT && t != IRPC && t != IRP && t != MACRO)
				t = param->i_token;

			// Caret escaping kills all expansion
			// And interpretation of ENDM, etc.  For better or worse.
			if (caret)
				t = 0;

			if (t == MPARM) {
				int pfx = octo || amp || c == '&';
				// # prefix only allowed if declared that way
				if (octo != param->i_scope)
					t = 0;
				else
					octo = 0;

				// Expansion in quoted strings only with prefix character.
				if (quote && !pfx && !zcompat)
					t = 0;

				amp = 0; // parameter substitution, eat '&'
			}
			else if (t && quote)
				t = 0;

			if (ampdrop)
				amp = 0;

			ampdrop = c == '&' && t == MPARM;

			if (octo) putm('#');
			if (amp) putm('&');

			if (t != MPARM) {
				putm(symbuf[0]);
				putm_str(symbuf + 1, mras && !quote);
			}
			else {
				putm_param_ref(param);
				// Only in MRAS will we have a remainder string
				putm_str(symbuf + strlen(param->i_string), mras && !quote);
			}

			if (t == ENDM) {
				if (--inmlex == 0)
					goto done;
			}
			else if (t == REPT || t == IRPC || t == IRP || t == MACRO) {
				inmlex++;
			}

			continue;

		case F_END:
			errwarn(warn_general, "macro definition went until end of file");
			if (expptr) {
				popsi();
				c = nextmac();
				continue;
			}

			goto done;

		default:
			switch (c) {
			case '\n':
				quote = 0;
				list1();
				break;
			case ';':
				if (!quote) {
					while (c != '\n' && c != 0) {
						putm(c);
						c = nextmac();
					}
					continue;
				}
				break;
			case '\'':
			case '"':
				if (c == quote)
					quote = 0;
				else
					quote = c;
				break;
			default:
				break;
			}
			if (c != '\1' && c != '`') putm(c);
			c = nextmac();
		}
	}

	/*
	 *  finish off the file entry
	 */
done:
	while(c != EOF && c != '\n' && c != '\0') c = nextmac();
	inmlex++;
	list1();
	inmlex--;
	// WHY two newlines??
//	putm('\n');
	putm('\n');
	putm(0);

	// TODO - here's where we could save parameter names for MRAS
	for (c = 0; c < PARAMTABSIZE; c++) {
		if (paramtab[c].i_token == MPARM) {
			free(paramtab[c].i_string);
			paramtab[c].i_string = NULL;
			paramtab[c].i_token = 0;
		}
	}
	inmlex = 0;
#ifdef	M_DEBUG
	fprintf(stderr,"exit 'mlex' at %d\n", mfptr) ;
#endif
}

void putm_param_ref(struct item *param)
{
	if (*(param->i_string) == '?' || param->i_chain)
		putm('\2');
	else
		putm('\1');

	putm(param->i_value + 'A');
}

void putm_str(char *str, int look_for_param)
{
	for (; *str; str++) {
		if (look_for_param) {
			struct item *param = item_substr_lookup(str, MPARM, paramtab, PARAMTABSIZE);
			if (param) {
				putm_param_ref(param);
				str += strlen(param->i_string) - 1;
				continue;
			}
		}
		putm(*str);
	}
}

int str_getch(struct argparse *ap)
{
	int ch = ap->user_peek;
	if (ch >= 0) {
		ap->user_peek = -1;
		return ch;
	}
	if (!ap->user_ptr || ap->user_ptr[ap->user_int] == '\0')
		return '\0';

	return ap->user_ptr[ap->user_int++];
}

int arg_getch(struct argparse *ap)
{
	(void)ap; // suppress warning
	return nextchar();
}

void arg_start()
{
	arg_reset();
	arg_flag = 1;
}

void arg_reset()
{
	arg_flag = 0;

	arg_state.arg = tempbuf;
	arg_state.argsize = sizeof tempbuf;
	arg_state.peek = &peekc;
	arg_state.getch = arg_getch;
	arg_state.macarg = 0;
	arg_state.user_ptr = 0;
	arg_state.user_int = 0;
	arg_state.didarg = 0;
	arg_state.numarg = 0;
}

/*
 *  lexical analyser for the arguments of a macro call
 */
int getarg(struct argparse *ap)
{
	int c;
	char *p;
	int quote;
	int depth;

	*ap->arg = 0;
	while (charclass[c = ap->getch(ap)] == SPACE);

	switch(c) {

	case '\0':
		if (!ap->user_ptr)
			popsi(); // a seemingly unlikely case?
	case '\n':
	case ';':
		if (!ap->didarg && ap->numarg) {
			*ap->peek = c;
			ap->didarg = 1;
			ap->numarg++;
			return ARG;
		}
		ap->didarg = 0;
		ap->numarg = 0;
		return c;

	case ',':
		if (!ap->didarg) {
			ap->didarg = 1;
			*ap->peek = c;
			ap->numarg++;
			return ARG;
		}
		ap->didarg = 0;
		return c;

	case '\'':
	case '\"':
		quote = c;
		p = ap->arg;
		if (!zcompat)
			*p++ = c;

		do {
			c = ap->getch(ap);
			if (c == '\0' || c == '\n') {
				*ap->peek = c;
				*p = 0;
				err[bflag]++;
				ap->didarg = 1;
				ap->numarg++;
				return ARG;
			}
			else if (c == quote) {
				if ((c = ap->getch(ap)) != quote) {
					if (!zcompat)
						*p++ = quote;
					*ap->peek = c;
					*p = '\0';
					ap->didarg = 1;
					ap->numarg++;
					return ARG;
				}
			}
			else
				*p++ = c;
		} while (p < ap->arg + ap->argsize - 1);
		ap->arg[ap->argsize - 1] = '\0';
		printf("was parsing macro argument '%s'\n", ap->arg);
		error(symlong);
		return 0; // not reached

	case '<':
		depth = 1;
		p = ap->arg;
		do {
			c = ap->getch(ap);
			if (c == '\0' || c == '\n') {
				*ap->peek = c;
				*p = 0;
				err[bflag]++;
				ap->didarg = 1;
				ap->numarg++;
				return ARG;
			}
			if (c == '>') {
				depth--;
				if (depth == 0) {
					*p = '\0';
					ap->didarg = 1;
					ap->numarg++;
					return ARG;
				}
			}
			else if (c == '<')
				depth++;

			*p++ = c;
		} while (p < ap->arg + ap->argsize - 1);
		ap->arg[ap->argsize - 1] = '\0';
		printf("was parsing macro argument '%s'\n", ap->arg);
		error(symlong);
		return 0; // not reached

	default:  /* unquoted string */
		if (c == '%' && ap->macarg) {
			ap->didarg = 1;
			ap->numarg++;
			return c;
		}

		p = ap->arg;
		*ap->peek = c;

		do {
			c = ap->getch(ap);
			switch(c) {
			case '\0':
			case '\n':
			case '\t':
			case ' ':
			case ',':
				*ap->peek = c;
				*p = '\0';
				ap->didarg = 1;
				ap->numarg++;
				return ARG;
			case '^':
				c = ap->getch(ap);
				switch (c) {
				case ',':
				case '^':
				case ' ':
				case '\t':
					*p++ = c;
					break;
				default:
					*p++ = '^';
					*ap->peek = c;
					break;
				}
				break;
			default:
				*p++ = c;
			}
		} while (p < ap->arg + ap->argsize - 1);
		ap->arg[ap->argsize - 1] = '\0';
		printf("was parsing macro argument '%s'\n", ap->arg);
		error("macro argument too long");
		return 0; // not reached
	}
}


/*
 *  add a suffix to a string
 */
void suffix(char *str, char *suff)
{
	strcpy(getsuffix(str), suff);
}

char *basename(char *filename)
{
	char *base, *p;

	base = filename;
	for (p = filename; *p; p++) {
		if (*p == '/' || *p == '\\') {
			base = p + 1;
		}
	}

	return base;
}

char *getsuffix(char *str)
{
	char *suffix = 0;
	str = basename(str);
	for (; *str; str++) {
		if (*str == '.')
			suffix = str;
	}
	return suffix ? suffix : str;
}

// Construct output file given input path.
// Essentially files for "file.z" are sent to "zout/file.suffix".
// And for "dir/file.z" they are "zout/file.suffix"

void outpath(char *out, char *src, char *suff)
{
	strcpy(out, "zout");
	if (!suff)
		return;

	strcat(out, "/");
	strcat(out, basename(src));
	suffix(out, suff);
}


/*
 *  put out a byte to the macro file, keeping the offset
 */
void putm(int c)
{
	mfseek(mfile, mfptr, 0);
	mfptr++;
	mfputc(c, mfile);
}



/*
 *  get a byte from the macro file
 */
int getm()
{
	int ch;

	mfseek(mfile, floc, 0);
	floc++;
	ch = mfgetc(mfile);
	if (ch == EOF) {
		ch = 0;
		fprintf(stderr, "bad macro read\n");
	}
	return ch;
}



/*
 *  pop standard input
 */
void popsi()
{
	int  i;

	for (i=0; i<PARMMAX; i++) {
		if (est[i].param) free(est[i].param);
	}
	floc = est[FLOC].value;
	ifptr = est[MIF].param;
	free(est);
	expptr--;
	est = expptr ? expstack[expptr-1] : 0;
	mfseek(mfile, (long)floc, 0);
	if (lineptr > linebuf) lineptr--;
}



/*
 *  return a unique name for a local symbol
 *  c is the parameter number, n is the macro number.
 */

char *getlocal(int c, int n)
{
	static char local_label[10];

	invented++;
	if (c >= 26)
		c += 'a' - '0';
	sprintf(local_label, "?%c%04d", c+'a', n) ;
	return(local_label);
}

char *getmraslocal()
{
	static char mras_local[32];
	char *p = mras_local + sizeof mras_local - 1;
	int n = est[TEMPNUM].value;

	*p = '\0';
	for (; n > 0; n /= 26)
		*--p = 'A' + n % 26;


	return p;
}


/*
 *  read in a symbol table
 */
void insymtab(char *name)
{
	struct stab *t;
	int  s, i;
	FILE *sfile;

	t = (struct stab *) tempbuf;
	if (!(sfile = fopen(name, "rb")))
		return;
	fread((char *)t, 1, sizeof *t, sfile);
	if (t->t_value != SYMMAJIC)
		return;

	
	s = t->t_token;
	for (i=0; i<s; i++) {
		fread((char *)t, 1, sizeof *t, sfile);
		if (tokenofitem(UNDECLARED, 0, 0) != UNDECLARED)
			continue;
		yylval.itemptr->i_token = t->t_token;
		yylval.itemptr->i_value = t->t_value;
		if (t->t_token == MACRO)
			yylval.itemptr->i_value += mfptr;
	}

	while ((s = fread(tempbuf, 1, TEMPBUFSIZE, sfile)) > 0) {
		mfptr += s;
		mfwrite(tempbuf, 1, s, mfile) ;
	}
	fclose(sfile);
}



/*
 *  write out symbol table
 */
void outsymtab(char *name)
{
	struct stab *t;
	struct item *ip;
	int  i;
	FILE *sfile;

	t = (struct stab *) tempbuf;
	if (!(sfile = fopen(name, "wb")))
		return;
	for (ip=itemtab; ip<itemmax; ip++) {
		if (ip->i_token == UNDECLARED) {
			ip->i_token = 0;
			nitems--;
		}
	}

	copyname(title, (char *)t);
	t->t_value = SYMMAJIC;
	t->t_token = nitems;
	fwrite((char *)t, 1, sizeof *t, sfile);

	for (ip=itemtab; ip<itemmax; ip++) {
		if (ip->i_token != 0) {
			t->t_token = ip->i_token;
			t->t_value = ip->i_value;
			copyname(ip->i_string, (char *)t);
			fwrite((char *)t, 1, sizeof *t, sfile);
		}
	}

	mfseek(mfile, (long)0, 0);
	while((i = mfread(tempbuf, 1, TEMPBUFSIZE, mfile) ) > 0)
		fwrite(tempbuf, 1, i, sfile);

	fclose(sfile);
}



/*
 *  copy a name into the symbol file
 */
void copyname(char *st1, char *st2)
{
	char  *s1, *s2;
	int  i;

	i = (MAXSYMBOLSIZE+2) & ~01;
	s1 = st1;
	s2 = st2;

	while((*s2++ = *s1++)) i--;		/* -Wall-ishness :-) -RJM */
	while(--i > 0) *s2++ = '\0';
}

/* get the next source file */
void next_source(char *sp)
{

	if(now_in == NEST_IN -1)
		error("Too many nested includes") ;
	if ((now_file = open_incpath(sp, "r")) == NULL) {
		char ebuf[1024] ;
		sprintf(ebuf,"Can't open include file: %s", sp) ;
		error(ebuf) ;
	}
	if (outpass && iflist()) {
		lineout() ;
		fprintf(fout, "**** %s ****\n",sp) ;
	}

	if (outpass && bopt)
		fprintf(fbds, "%04x %04x f %s\n", dollarsign, emit_addr, sp);

	/* save the list control flag with the current line number */
	if (lstoff)
		linein[now_in] = - linein[now_in] ;

	/* no list if include files are turned off */
	lstoff |= iopt ;

	linepeek[now_in] = nextline_peek;
	nextline_peek = NOPEEK;
	/* save the new file descriptor. */
	fin[++now_in] = now_file ;
	/* start with line 0 */
	linein[now_in] = 0 ;
	/* save away the file name */
	src_name[now_in] = malloc(strlen(sp)+1) ;
	strcpy(src_name[now_in],sp) ;
}

int phaseaddr(int addr)
{
	if (!phaseflag)
		return addr;

	if (addr < phbegin || addr > dollarsign) {
		err[vflag]++;
		if (pass2)
			fprintf(stderr, "$%04x outside current phase area\n", addr);
		return 0;
	}

	return phdollar + (addr - phbegin);
}

// Include contents of named file as binary data.
void incbin(char *filename)
{
	FILE *fp = open_incpath(filename, "rb");
	int ch;
	int start = dollarsign;
	int last = start;
	int bds_count;

	if (!fp) {
		char ebuf[1024];
		sprintf(ebuf, "Can't binary include file: %s", filename);
		error(ebuf);
		return;
	}

	addtoline('\0');
	if (outpass && bopt)
		fprintf(fbds, "%04x %04x s %s", dollarsign, emit_addr, linebuf);

	// Avoid emit() because it has a small buffer and it'll spam the listing.
	bds_count = 0;
	while ((ch = fgetc(fp)) != EOF) {
		if (outpass && bopt) {
			if (bds_count == 0)
				fprintf(fbds, "%04x %04x d ", dollarsign, emit_addr);
			fprintf(fbds, "%02x", ch);
			bds_count++;
			if (bds_count == 16) {
				fprintf(fbds, "\n");
				bds_count = 0;
			}
		}

		if (segment == SEG_CODE)
			setmem(emit_addr, ch, MEM_DATA);
		emit_addr++;
		emit_addr &= 0xffff;
		last = dollarsign;
		dollarsign++;
		dollarsign &= 0xffff;

		putbin(ch);
		putrel(ch);
		putout(ch);
	}
	if (outpass && bopt && bds_count)
		fprintf(fbds, "\n");

	fclose(fp);

	// Do our own list() work as we emit bytes manually.

	if (outpass && iflist()) {
		lineout();

		if (nopt)
			fprintf(fout, "%4d:", linein[now_in]);

		if (copt)
		        fprintf(fout, nopt ? "%5s-" : "%4s-", "");

		if (nopt || copt)
			fprintf(fout, "\t");

		puthex(start >> 8, fout);
		puthex(start, fout);
		if (relopt)
			fputc(SEGCHAR(segment), fout);
		fprintf(fout, " .. ");
		puthex(last >> 8, fout);
		puthex(last, fout);
		if (relopt)
			fputc(SEGCHAR(segment), fout);

		putc('\t', fout);

		fputs(linebuf, fout);

		lineptr = linebuf;
	}
}

void dc(int count, int value)
{
	int start = dollarsign;
	int bds_count;

	addtoline('\0');
	if (outpass && bopt)
		fprintf(fbds, "%04x %04x s %s", dollarsign, emit_addr, linebuf);

	// Avoid emit() because it has a small buffer and it'll spam the listing.
	bds_count = 0;
	while (count-- > 0) {
		if (outpass && bopt) {
			if (bds_count == 0)
				fprintf(fbds, "%04x %04x d ", dollarsign, emit_addr);
			fprintf(fbds, "%02x", value);
			bds_count++;
			if (bds_count == 16) {
				fprintf(fbds, "\n");
				bds_count = 0;
			}
		}

		if (segment == SEG_CODE)
			setmem(emit_addr, value, MEM_DATA);
		emit_addr++;
		emit_addr &= 0xffff;
		dollarsign++;
		dollarsign &= 0xffff;

		putbin(value);
		putrel(value);
		putout(value);
	}
	if (outpass && bopt && bds_count)
		fprintf(fbds, "\n");

	// Do our own list() work as we emit bytes manually.

	if (outpass && iflist()) {
		lineout();

		if (nopt)
			fprintf(fout, "%4d:", linein[now_in]);

		if (copt)
		        fprintf(fout, nopt ? "%5s-" : "%4s-", "");

		if (nopt || copt)
			fprintf(fout, "\t");

		puthex(start >> 8, fout);
		puthex(start, fout);
		if (relopt) {
			fputc(SEGCHAR(segment), fout);
			fprintf(fout, "..");
		}
		else
			fprintf(fout, " .. ");

		puthex((dollarsign - 1) >> 8, fout);
		puthex((dollarsign - 1), fout);
		if (relopt)
			fputc(SEGCHAR(segment), fout);
		putc(' ', fout);
		puthex(value, fout);
		putc('\t', fout);
		fputs(linebuf, fout);
		lsterr2(1);

		lineptr = linebuf;
	}
	else
		lsterr1();
}

#define OUTREC_SEG	outbuf[outrec]
#define OUTREC_ADDR	((outbuf[outrec + 1] << 8) | outbuf[outrec + 2])
#define OUTREC_LEN	outbuf[outrec + 3]
#define OUTREC_DATA	outbuf[outrec + 4 + outlen]
#define OUTREC_SIZEOF	5

void new_outrec(void)
{
	OUTREC_LEN = outlen;
	outrec += OUTREC_SIZEOF + outlen;

	outlen = 0;
	OUTREC_SEG = segment;
	outbuf[outrec + 1] = seg_pos[segment] >> 8;
	outbuf[outrec + 2] = seg_pos[segment];
}

void putout(int value)
{
	int addr = (OUTREC_ADDR + outlen) & 0xffff;
	if (OUTREC_SEG != segment || addr != seg_pos[segment])
		new_outrec();

	if (pass2 && OUTREC_DATA != value && !passfail) {
		char segname[2];
		if (relopt)
			sprintf(segname, "%c", SEGCHAR(segment));
		else
			segname[0] = '\0';

		sprintf(detail, "%s error - $%04x%s changed from $%02x to $%02x",
			errname[pflag], addr, segname, OUTREC_DATA, value);
		errwarn(pflag, detail);

		if (!outpass)
			passretry = 1;
	}
	OUTREC_DATA = value;
	outlen++;

	if (outlen >= 256)
		new_outrec();

	advance_segment(1);
}

void advance_segment(int step)
{
	int top = seg_pos[segment] += step;
	seg_pos[segment] &= 0xffff;
	if (top >= 0x10000)
		top = 0xffff;

	if (top > seg_size[segment])
		seg_size[segment] = top;
}

void expr_reloc_check(struct expr *ex)
{
	if (!relopt) return;
	if (ex->e_scope & (SCOPE_EXTERNAL | SCOPE_NORELOC))
		err[rflag]++;
}

void expr_number_check(struct expr *ex)
{
	if (!relopt) return;
	expr_reloc_check(ex);
	if (ex->e_scope & SCOPE_SEGMASK)
		err[rflag]++;
}

void expr_scope_same(struct expr *ex1, struct expr *ex2)
{
	if (!relopt) return;
	if ((ex1->e_scope & SCOPE_SEGMASK) != (ex2->e_scope & SCOPE_SEGMASK))
		err[rflag]++;
}

void expr_word_check(struct expr *ex)
{
	if (ex->e_value < -32768 || ex->e_value > 65535) {
		err[vflag]++;
	}
}

int is_number(struct expr *ex)
{
	return ex && (ex->e_scope & ~SCOPE_PUBLIC) == 0;
}

int is_external(struct expr *ex)
{
	return ex && (ex->e_scope & SCOPE_EXTERNAL) && !ex->e_left && !ex->e_right &&
		ex->e_item;
}

struct expr *expr_alloc(void)
{
	struct expr *ex = malloc(sizeof *ex);

	ex->e_value = 0;
	ex->e_scope = 0;
	ex->e_token = 0;
	ex->e_item = 0;
	ex->e_left = 0;
	ex->e_right = 0;

	return ex;
}

struct expr *expr_var(struct item *it)
{
	struct expr *ex = expr_alloc();

	ex->e_token = 'v';
	ex->e_item = it;
	ex->e_scope = it->i_scope;
	ex->e_value = it->i_value;

	return ex;
}

struct expr *expr_num(int value)
{
	struct expr *ex = expr_alloc();
	ex->e_value = value;
	ex->e_token = '0';

	return ex;
}

// Build expression and update value based on the operator.
// Could be done inline in the grammar but there is a fair bit of
// repetition and MRAS operators have only made that worse.

struct expr *expr_mk(struct expr *left, int op, struct expr *right)
{
	struct expr *ex;
	int val = 0;
	int sc = 0;

	switch (op) {
	case '+':
		ex = expr_op(left, '+', right, left->e_value + right->e_value);

		// Can't operate on external labels.
		// But we can add constants to any scope.
		if (!((left->e_scope | right->e_scope) & SCOPE_EXTERNAL) &&
			((left->e_scope & SCOPE_SEGMASK) == 0 ||
			(right->e_scope & SCOPE_SEGMASK) == 0))
		{
			ex->e_scope &= ~(SCOPE_NORELOC | SCOPE_SEGMASK);
			ex->e_scope |= (left->e_scope | right->e_scope) & SCOPE_SEGMASK;
		}
		return ex;
	case '-':
		ex = expr_op_sc(left, '-', right, left->e_value - right->e_value);

		// But we can subtract a constant.
		if (!((left->e_scope | right->e_scope) & SCOPE_EXTERNAL) &&
			((right->e_scope & SCOPE_SEGMASK) == 0))
		{
			ex->e_scope &= ~(SCOPE_NORELOC | SCOPE_SEGMASK);
			ex->e_scope |= (left->e_scope & SCOPE_SEGMASK);
		}
		return ex;
	case '/':
		if (right->e_value == 0)
			err[eflag]++;
		else
			val = left->e_value / right->e_value;

		break;
	case '*':
		val = left->e_value * right->e_value;
		break;
	case '%':
		if (right->e_value == 0)
			err[eflag]++;
		else
			val = left->e_value % right->e_value;

		break;
	case '&':
		val = left->e_value & right->e_value;
		break;
	case '|':
		val = left->e_value | right->e_value;
		break;
	case '^':
		val = left->e_value ^ right->e_value;
		break;
	case SHL:
		val = left->e_value << right->e_value;
		break;
	case SHR:
		val = right->e_value == 0 ? left->e_value : ((left->e_value >> 1) & ((0x7fff << 16) | 0xffff)) >> (right->e_value - 1);
		break;
	case '<':
		val = (left->e_value < right->e_value) * trueval;
		sc = 1;
		break;
	case '=':
		val = (left->e_value == right->e_value) * trueval;
		sc = 1;
		break;
	case '>':
		val = (left->e_value > right->e_value) * trueval;
		sc = 1;
		break;
	case LE:
		val = (left->e_value <= right->e_value) * trueval;
		sc = 1;
		break;
	case NE:
		val = (left->e_value != right->e_value) * trueval;
		sc = 1;
		break;
	case GE:
		val = (left->e_value >= right->e_value) * trueval;
		sc = 1;
		break;
	case ANDAND:
		val = (left->e_value && right->e_value) * trueval;
		break;
	case OROR:
		val = (left->e_value || right->e_value) * trueval;
		break;
	default:
		fprintf(stderr, "internal expression evaluation error!\n");
		exit(-1);
		break;
	}

	if (sc)
		return expr_op_sc(left, op, right, val);

	return expr_op(left, op, right, val);
}


// Expression consruction for operators that subtract/compare.
// They produce a valid result if operating on numbers in the same segment.
struct expr *expr_op_sc(struct expr *left, int token, struct expr *right, int value)
{
	struct expr *ex = expr_op(left, token, right, value);

	if (!(ex->e_scope & SCOPE_EXTERNAL) &&
		((left->e_scope ^ right->e_scope) & SCOPE_SEGMASK) == 0)
	{
		// Result relocatable and a simple number
		ex->e_scope &= ~(SCOPE_NORELOC | SCOPE_SEGMASK);
	}

	return ex;
}

struct expr *expr_op(struct expr *left, int token, struct expr *right, int value)
{
	struct expr *ex = expr_alloc();

	ex->e_value = value;
	ex->e_token = token;
	ex->e_left = left;
	ex->e_right = right;

	// Combining two numbers will be fine as long as they're not
	// flagged as external or already not relocatable.  In which case
	// it is up to the particular operator to allow the value
	// to become valid.

	ex->e_scope = left->e_scope;
	if (left->e_scope & SCOPE_SEGMASK)
		ex->e_scope |= SCOPE_NORELOC;
	if (right) {
		ex->e_scope |= right->e_scope;
		if (right->e_scope & SCOPE_SEGMASK)
			ex->e_scope |= SCOPE_NORELOC;
	}

	return ex;
}

void expr_free(struct expr *ex)
{
	if (!ex)
		return;

	expr_free(ex->e_left);
	expr_free(ex->e_right);
	free(ex);
}

int synth_op(struct expr *ex, int gen)
{
	if (ex->e_token == '&' && is_number(ex->e_right) &&
		ex->e_right->e_value == 255)
	{
		if (gen) {
			extend_link(ex->e_left);
			putrelop(RELOP_LOW);
			return 1;
		}
		return can_extend_link(ex->e_left);
	}

	return 0;
}

int link_op(struct expr *ex)
{
	if (!ex)
		return 0;

	switch (ex->e_token) {
	case HIGH: return RELOP_HIGH;
	case LOW: return RELOP_LOW;
	case '~': return RELOP_NOT;
	case '-': return !ex->e_right ? RELOP_NEG : RELOP_SUB;
	case '+': return RELOP_ADD;
	case '*': return RELOP_MUL;
	case '/': return RELOP_DIV;
	case '%': return RELOP_MOD;
	default: return 0;
	}
}

int can_extend_link(struct expr *ex)
{
	if (!ex)
		return 1;

	// If we have a value available then we're good.
	if (!(ex->e_scope & SCOPE_NORELOC))
		return 1;

	// Might be able to synthesize the operation.
	if (synth_op(ex, 0))
		return 1;

	// Otherwise, the operator must be supported and the children
	// must be linkable.

	return link_op(ex) && can_extend_link(ex->e_left) && can_extend_link(ex->e_right);
}

void extend_link(struct expr *ex)
{
	int op;

	if (!ex)
		return;

	if (synth_op(ex, 1))
		return;

	extend_link(ex->e_left);
	extend_link(ex->e_right);

	op = link_op(ex);
	if (op) {
		putrelop(op);
		return;
	}

	putrelcmd(RELCMD_EXTLINK);

	if (is_external(ex)) {
		char *str = ex->e_item->i_string;
		int len = strlen(str);

		if (len > 6)
			len = 6;

		putrelbits(3, 1 + len);
		putrelbits(8, 'B');
		while (len-- > 0) {
			int ch = *str++;
			if (ch >= 'a' && ch <= 'z')
				ch -= 'a' - 'A';
			putrelbits(8, ch);
		}
	}
	else {
		putrelbits(3, 4);
		putrelbits(8, 'C');
		putrelbits(8, ex->e_scope & SCOPE_SEGMASK);
		putrelbits(8, ex->e_value);
		putrelbits(8, ex->e_value >> 8);
	}
}

void putrelop(int op)
{
	putrelcmd(RELCMD_EXTLINK);

	putrelbits(3, 2);
	putrelbits(8, 'A');
	putrelbits(8, op);
}

void write_tap_block(int type, int len, unsigned char *data)
{
	int i, parity;

	fputc((len + 2) & 0xff, ftap);
	fputc((len + 2) >> 8, ftap);

	fputc(type, ftap);
	parity = type;
	for (i = 0; i < len; i++) {
		fputc(data[i], ftap);
		parity ^= data[i];
	}
	fputc(parity, ftap);
}

// One supposes .tap files could load multiple blocks into memory.
// However, doesn't seem to be a lot of point and we'd have to write
// extra loader code to make it happen.  For now we just load the
// assembled data as one contiguous block with the holes getting
// filled with zeros.

void write_tap(int len, int org, unsigned char *data)
{
	unsigned char block[32], *p, orglo, orghi;
	unsigned char basic_loader[] = {
		239, 34, 34, 175, 58, 249, 192, 176, // LOAD ""CODE:RANDOMIZE USR VAL
		'"', '2', '3', '2', '9', '6', '"', 13 // aka 0x5b00 - start of RAM
	};
	int entry = org;

	if (xeq_flag)
		entry = xeq;

	// .tap file output borrowed heavily from skoolkit's bin2tap.py
	// It loads a short basic program which auto-executes and loads
	// a short machine-language loader that reads the block of code
	// and jumps to it.
	// Constrast this with pasmo which doesn't have the short machine
	// code loader but uses a native code block.  I think that means
	// it can only execute at the beginning of the loaded data.

	p = block;

	*p++ = 0; // Program block
	casname((char *)p, sourcef, 10);
	p += 10;
	*p++ = 4 + sizeof basic_loader; *p++ = 0; // length of BASIC program
	*p++ = 10; *p++ = 0; // run line 10 after loading
	*p++ = 4 + sizeof basic_loader; *p++ = 0; // length of BASIC program

	write_tap_block(0, p - block, block);

	p = block;
	*p++ = 0; *p++ = 10; // line 10
	*p++ = sizeof(basic_loader); *p++ = 0;
	memcpy(p, basic_loader, sizeof basic_loader);
	p += sizeof basic_loader;
	write_tap_block(0xff, p - block, block);

	p = block;

	*p++ = 3; // Code block
	casname((char *)p, sourcef, 10);
	p += 10;
	*p++ = 19; *p++ = 0; // length of loader program
	*p++ = 0; *p++ = 0x5b; // 0x5b00 == 23296 - start of RAM
	*p++ = 0; *p++ = 0; // ?

	write_tap_block(0, p - block, block);

	p = block;

	orglo = org & 0xff;
	orghi = org >> 8;
	/* LD IX,org   */ *p++ = 0xdd; *p++ = 0x21; *p++ = orglo; *p++ = orghi;
	/* LD DE,len   */ *p++ = 0x11; *p++ = len & 0xff; *p++ = len >> 8;
	/* SCF         */ *p++ = 0x37;
	/* SBC A,A     */ *p++ = 0x9f;
	/* LD SP,org   */ *p++ = 0x31; *p++ = orglo; *p++ = orghi;
	/* LD BC,entry */ *p++ = 0x01; *p++ = entry & 0xff; *p++ = entry >> 8;
	/* PUSH BC     */ *p++ = 0xc5;
	/* JP $556     */ *p++ = 0xc3; *p++ = 0x56; *p++ = 0x05;

	write_tap_block(0xff, p - block, block);

	write_tap_block(0xff, len, data);
}
#line 8640 "y.tab.c"

#if YYDEBUG
#include <stdio.h>		/* needed for printf */
#endif

#include <stdlib.h>	/* needed for malloc, etc */
#include <string.h>	/* needed for memset */

/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack(YYSTACKDATA *data)
{
    int i;
    unsigned newsize;
    YYINT *newss;
    YYSTYPE *newvs;

    if ((newsize = data->stacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return YYENOMEM;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;

    i = (int) (data->s_mark - data->s_base);
    newss = (YYINT *)realloc(data->s_base, newsize * sizeof(*newss));
    if (newss == 0)
        return YYENOMEM;

    data->s_base = newss;
    data->s_mark = newss + i;

    newvs = (YYSTYPE *)realloc(data->l_base, newsize * sizeof(*newvs));
    if (newvs == 0)
        return YYENOMEM;

    data->l_base = newvs;
    data->l_mark = newvs + i;

    data->stacksize = newsize;
    data->s_last = data->s_base + newsize - 1;
    return 0;
}

#if YYPURE || defined(YY_NO_LEAKS)
static void yyfreestack(YYSTACKDATA *data)
{
    free(data->s_base);
    free(data->l_base);
    memset(data, 0, sizeof(*data));
}
#else
#define yyfreestack(data) /* nothing */
#endif

#define YYABORT  goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR  goto yyerrlab

int
YYPARSE_DECL()
{
    int yym, yyn, yystate;
#if YYDEBUG
    const char *yys;

    if ((yys = getenv("YYDEBUG")) != 0)
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = YYEMPTY;
    yystate = 0;

#if YYPURE
    memset(&yystack, 0, sizeof(yystack));
#endif

    if (yystack.s_base == NULL && yygrowstack(&yystack) == YYENOMEM) goto yyoverflow;
    yystack.s_mark = yystack.s_base;
    yystack.l_mark = yystack.l_base;
    yystate = 0;
    *yystack.s_mark = 0;

yyloop:
    if ((yyn = yydefred[yystate]) != 0) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = YYLEX) < 0) yychar = YYEOF;
#if YYDEBUG
        if (yydebug)
        {
            yys = yyname[YYTRANSLATE(yychar)];
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM)
        {
            goto yyoverflow;
        }
        yystate = yytable[yyn];
        *++yystack.s_mark = yytable[yyn];
        *++yystack.l_mark = yylval;
        yychar = YYEMPTY;
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;

    YYERROR_CALL("syntax error");

    goto yyerrlab;

yyerrlab:
    ++yynerrs;

yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yystack.s_mark]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yystack.s_mark, yytable[yyn]);
#endif
                if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM)
                {
                    goto yyoverflow;
                }
                yystate = yytable[yyn];
                *++yystack.s_mark = yytable[yyn];
                *++yystack.l_mark = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yystack.s_mark);
#endif
                if (yystack.s_mark <= yystack.s_base) goto yyabort;
                --yystack.s_mark;
                --yystack.l_mark;
            }
        }
    }
    else
    {
        if (yychar == YYEOF) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = yyname[YYTRANSLATE(yychar)];
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = YYEMPTY;
        goto yyloop;
    }

yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    if (yym)
        yyval = yystack.l_mark[1-yym];
    else
        memset(&yyval, 0, sizeof yyval);
    switch (yyn)
    {
case 3:
#line 1878 "zmac.y"
	{ 
		/* An identfier without a colon all by itself on a line*/
		/* will be interpreted as a label.  But there's a very*/
		/* good chance it is a misspelling of an instruction or*/
		/* pseudo-op name creating silent errors.  Since the condition*/
		/* is unusual we print a warning.  Unless it is followed by*/
		/* a colon in which case there's no ambiguity.*/
		if (yystack.l_mark[-1].itemptr && !firstcol && coloncnt == 0 && outpass) {
			fprintf(stderr, "%s(%d): warning: '%s' treated as label (instruction typo?)\n",
				src_name[now_in], linein[now_in], yystack.l_mark[-1].itemptr->i_string);
			fprintf(stderr, "\tAdd a colon or move to first column to stop this warning.\n");
		}

		if (yystack.l_mark[-1].itemptr) list(dollarsign);
		else  list1();
	}
break;
case 4:
#line 1895 "zmac.y"
	{ list_dollarsign = 1; }
break;
case 5:
#line 1895 "zmac.y"
	{
		list(list_dollarsign ? dollarsign : list_addr);
	}
break;
case 6:
#line 1899 "zmac.y"
	{
		do_equ(yystack.l_mark[-4].itemptr, yystack.l_mark[-1].exprptr, 1);
		if (yystack.l_mark[-3].ival == 2)
			yystack.l_mark[-4].itemptr->i_scope |= SCOPE_PUBLIC;
	}
break;
case 7:
#line 1905 "zmac.y"
	{
		do_defl(yystack.l_mark[-4].itemptr, yystack.l_mark[-1].exprptr, 1); /* TODO: is '=' equate or defl?*/
		/* I don't even recall what assembler I saw that allows '='*/
		/* Not MACR0-80.  Not MRAS.  Not MAC.*/
		/* I choose "defl" since it works so nicely with +=, etc.*/
		if (yystack.l_mark[-3].ival == 2)
			yystack.l_mark[-4].itemptr->i_scope |= SCOPE_PUBLIC;
	}
break;
case 8:
#line 1914 "zmac.y"
	{
		do_defl(yystack.l_mark[-3].itemptr, yystack.l_mark[-1].exprptr, 1);
	}
break;
case 9:
#line 1918 "zmac.y"
	{
		do_defl(yystack.l_mark[-4].itemptr, expr_mk(expr_var(yystack.l_mark[-4].itemptr), yystack.l_mark[-3].ival, yystack.l_mark[-1].exprptr), 1);
	}
break;
case 10:
#line 1922 "zmac.y"
	{
		do_defl(yystack.l_mark[-3].itemptr, expr_mk(expr_var(yystack.l_mark[-3].itemptr), '+', expr_num(1)), 1);
	}
break;
case 11:
#line 1926 "zmac.y"
	{
		do_defl(yystack.l_mark[-3].itemptr, expr_mk(expr_var(yystack.l_mark[-3].itemptr), '-', expr_num(1)), 1);
	}
break;
case 12:
#line 1930 "zmac.y"
	{
		int val3 = yystack.l_mark[-3].exprptr->e_value;
		int val5 = yystack.l_mark[-1].exprptr->e_value;
		expr_reloc_check(yystack.l_mark[-3].exprptr);
		expr_reloc_check(yystack.l_mark[-1].exprptr);
		expr_scope_same(yystack.l_mark[-3].exprptr, yystack.l_mark[-1].exprptr);
		switch (yystack.l_mark[-5].itemptr->i_token) {
		case UNDECLARED: case DEFLED:
			yystack.l_mark[-5].itemptr->i_token = DEFLED;
			yystack.l_mark[-5].itemptr->i_pass = npass;
			yystack.l_mark[-5].itemptr->i_scope |= yystack.l_mark[-3].exprptr->e_scope;
			if (yystack.l_mark[-4].itemptr->i_value)	/* max */
				list(yystack.l_mark[-5].itemptr->i_value = (val3 > val5? val3:val5));
			else list(yystack.l_mark[-5].itemptr->i_value = (val3 < val5? val3:val5));
			break;
		default:
			err[mflag]++;
			yystack.l_mark[-5].itemptr->i_token = MULTDEF;
			yystack.l_mark[-5].itemptr->i_pass = npass;
			list(yystack.l_mark[-5].itemptr->i_value);
		}
		expr_free(yystack.l_mark[-3].exprptr);
		expr_free(yystack.l_mark[-1].exprptr);
	}
break;
case 13:
#line 1955 "zmac.y"
	{
		expr_number_check(yystack.l_mark[-1].exprptr);
		if (ifptr >= ifstmax)
			error("Too many ifs");
		else
			*++ifptr = !(yystack.l_mark[-1].exprptr->e_value);

		saveopt = fopt;
		fopt = 1;
		list(yystack.l_mark[-1].exprptr->e_value);
		fopt = saveopt;
		expr_free(yystack.l_mark[-1].exprptr);
	}
break;
case 14:
#line 1970 "zmac.y"
	{
		struct item *ip = locate(tempbuf);
		int declared = ip && ip->i_pass == npass;
		int value = declared == yystack.l_mark[-4].itemptr->i_value;

		if (ifptr >= ifstmax)
			error("Too many ifs");
		else
			*++ifptr = !value;

		saveopt = fopt;
		fopt = 1;
		list(value);
		fopt = saveopt;
	}
break;
case 15:
#line 1986 "zmac.y"
	{
		/* FIXME: it would be nice to spot repeated ELSEs, but how? */
		*ifptr = !*ifptr;
		saveopt = fopt;
		fopt = 1;
		list1();
		fopt = saveopt;
	}
break;
case 16:
#line 1995 "zmac.y"
	{
		if (ifptr == ifstack) err[bflag]++;
		else --ifptr;
		list1();
	}
break;
case 17:
#line 2001 "zmac.y"
	{
		list(dollarsign);
		do_end(NULL);
	}
break;
case 18:
#line 2006 "zmac.y"
	{
		list(yystack.l_mark[-1].exprptr->e_value);
		do_end(yystack.l_mark[-1].exprptr);
	}
break;
case 19:
#line 2011 "zmac.y"
	{
		expr_number_check(yystack.l_mark[-1].exprptr);
		if (yystack.l_mark[-1].exprptr->e_value < 0) err[vflag]++;
		if (yystack.l_mark[-1].exprptr->e_value > 0) {
			if (!phaseflag) {
				list(dollarsign);
				flushbin();
				flushoth();
				dollarsign += yystack.l_mark[-1].exprptr->e_value;
				olddollar += yystack.l_mark[-1].exprptr->e_value;
				oldothdollar += yystack.l_mark[-1].exprptr->e_value;
				emit_addr += yystack.l_mark[-1].exprptr->e_value;
				advance_segment(yystack.l_mark[-1].exprptr->e_value);
				putrelcmd(RELCMD_SETLOC);
				putrelsegref(segment, seg_pos[segment]);
			}
			else
				dc(yystack.l_mark[-1].exprptr->e_value, 0);
		}
		else
			list1();

		expr_free(yystack.l_mark[-1].exprptr);
	}
break;
case 20:
#line 2036 "zmac.y"
	{
		expr_number_check(yystack.l_mark[-3].exprptr);
		expr_number_check(yystack.l_mark[-1].exprptr);
		if (yystack.l_mark[-3].exprptr->e_value < 0) err[vflag]++;
		if (yystack.l_mark[-1].exprptr->e_value < -128 || yystack.l_mark[-1].exprptr->e_value > 127) err[vflag]++;
		if (yystack.l_mark[-3].exprptr->e_value > 0) {
			dc(yystack.l_mark[-3].exprptr->e_value, yystack.l_mark[-1].exprptr->e_value);
		}
		else
			list1();

		expr_free(yystack.l_mark[-3].exprptr);
		expr_free(yystack.l_mark[-1].exprptr);
	}
break;
case 21:
#line 2051 "zmac.y"
	{ emit(1, E_DATA, expr_num(yystack.l_mark[-1].ival | 0x80)); list(dollarsign); }
break;
case 22:
#line 2053 "zmac.y"
	{ emit(1, E_DATA, expr_num(yystack.l_mark[-1].ival)); emit(1, E_DATA, expr_num((yystack.l_mark[-1].ival >> 8) | 0x80)); list(dollarsign); }
break;
case 23:
#line 2056 "zmac.y"
	{
			for (cp = yystack.l_mark[-1].cval; *cp != '\0'; cp++)
				if (!cp[1])
					emit(1, E_DATA, expr_num(*cp | 0x80));
				else
					emit(1, E_DATA, expr_num(*cp));

			list(dollarsign);
		}
break;
case 24:
#line 2067 "zmac.y"
	{
			expr_number_check(yystack.l_mark[-3].exprptr);
			expr_number_check(yystack.l_mark[-1].exprptr);
			dc(yystack.l_mark[-3].exprptr->e_value, yystack.l_mark[-1].exprptr->e_value);
			expr_free(yystack.l_mark[-3].exprptr);
			expr_free(yystack.l_mark[-1].exprptr);
		}
break;
case 25:
#line 2075 "zmac.y"
	{
		list1();
		switch (yystack.l_mark[-4].itemptr->i_value) {

		case PSTITL:	/* title */
			lineptr = linebuf;
			cp = tempbuf;
			title = titlespace;
			while ((*title++ = *cp++) && (title < &titlespace[TITLELEN]));
			*title = 0;
			title = titlespace;
			break;

		case PSRSYM:	/* rsym */
			if (pass2) break;
			insymtab(tempbuf);
			break;

		case PSWSYM:	/* wsym */
			writesyms = malloc(strlen(tempbuf)+1);
			strcpy(writesyms, tempbuf);
			break;
		case PSINC:	/* include file */
			if (mras && !strchr(tempbuf, '.')) {
				strcat(tempbuf, ".asm");
			}
			next_source(tempbuf);
			break ;
		case PSMACLIB:
			strcat(tempbuf, ".lib");
			next_source(tempbuf);
			break;
		}
	}
break;
case 26:
#line 2110 "zmac.y"
	{
		fprintf(stderr, "Missing argument of '%s'\n", yystack.l_mark[-3].itemptr->i_string);
		err[fflag]++;
		list(dollarsign);
	}
break;
case 27:
#line 2116 "zmac.y"
	{
		incbin(tempbuf);
	}
break;
case 28:
#line 2120 "zmac.y"
	{ raw = 1; }
break;
case 29:
#line 2120 "zmac.y"
	{
		int quote = 0;
		char *p, *q;
		switch (yystack.l_mark[-2].itemptr->i_value) {
		case SPTITL:
			cp = tempbuf;
			title = titlespace;
			if (*cp == '\'' || *cp == '"')
				quote = *cp++;
			while ((*title++ = *cp++) && (title < &titlespace[TITLELEN]));
			if (quote && title > titlespace + 1 && title[-2] == quote)
				title[-2] = '\0';
			title = titlespace;
			list1();
			break;
		case SPSBTL:
			err[warn_notimpl]++;
			list1();
			break;
		case SPNAME:
			/* Drop surrounding ('') if present*/
			p = tempbuf;
			q = strchr(tempbuf, '\0') - 1;
			if (*p == '(' && *q == ')' && q > p) p++, q--;
			if (*p == '\'' && *q == '\'' && q > p) p++, q--;
			q[1] = '\0';
			strncpy(progname, p, sizeof progname);
			progname[sizeof progname - 1] = '\0';
			list1();
			break;
		case SPCOM:
			quote = *tempbuf;
			list1();
			for (;;) {
				raw = 1;
				yychar = yylex();
				list1();
				if (yychar == 0)
					break;
				if (*tempbuf == quote) {
					yychar = yylex();
					break;
				}
			}
			break;

		case SPPRAGMA:
			if (strncmp(tempbuf, "bds", 3) == 0 && bopt && outpass) {
				fprintf(fbds, "%s\n", tempbuf + 4);
			}
			list1();
			break;
		}
	}
break;
case 30:
#line 2175 "zmac.y"
	{
		goto dolopt; }
break;
case 31:
#line 2178 "zmac.y"
	{
		int enable = yystack.l_mark[-2].exprptr->e_value;

		enable = yystack.l_mark[-2].exprptr->e_value;

		if (mras) {
			if (ci_strcmp(tempbuf, "on") == 0)
				enable = 1;
			else if (ci_strcmp(tempbuf, "off") == 0)
				enable = -1;
			else {
				fprintf(stderr, "LIST not given 'on' or 'off'\n");
				err[fflag]++;
				list(dollarsign);
				goto dolopt_done;
			}
		}
		else {
			expr_number_check(yystack.l_mark[-2].exprptr);
			expr_free(yystack.l_mark[-2].exprptr);
		}
		goto doloptA;
	dolopt:
		enable = 1;
	doloptA:
		linecnt++;
		if (outpass) {
			lineptr = linebuf;
			switch (yystack.l_mark[-4].itemptr->i_value) {
			case 0:	/* list */
				if (enable < 0) lstoff = 1;
				if (enable > 0) lstoff = 0;
				break;

			case 1:	/* eject */
				if (enable) eject();
				break;

			case 2:	/* space */
				if ((line + enable) > 60) eject();
				else space(enable);
				break;

			case 3:	/* elist */
				eopt = edef;
				if (enable < 0) eopt = 0;
				if (enable > 0) eopt = 1;
				break;

			case 4:	/* fopt */
				fopt = fdef;
				if (enable < 0) fopt = 0;
				if (enable > 0) fopt = 1;
				break;

			case 5:	/* gopt */
				gopt = gdef;
				if (enable < 0) gopt = 1;
				if (enable > 0) gopt = 0;
				break;

			case 6: /* mopt */
				mopt = mdef;
				if (enable < 0) mopt = 0;
				if (enable > 0) mopt = 1;
			}
		}
	dolopt_done: ;
	}
break;
case 32:
#line 2248 "zmac.y"
	{
		expr_number_check(yystack.l_mark[-1].exprptr);
		jopt = !!yystack.l_mark[-1].exprptr->e_value;
		list1();
		expr_free(yystack.l_mark[-1].exprptr);
	}
break;
case 33:
#line 2255 "zmac.y"
	{
		expr_number_check(yystack.l_mark[-1].exprptr);
		JPopt = !!yystack.l_mark[-1].exprptr->e_value;
		list1();
		expr_free(yystack.l_mark[-1].exprptr);
	}
break;
case 34:
#line 2262 "zmac.y"
	{
		list1();
	}
break;
case 35:
#line 2266 "zmac.y"
	{
		list1();
	}
break;
case 36:
#line 2270 "zmac.y"
	{
		char *p = strchr(modstr, '\0') - 1;
		for (; p >= modstr; p--) {
			(*p)++;
			if (*p < 'Z')
				break;
			*p = 'A';
		}
		list1();
	}
break;
case 37:
#line 2281 "zmac.y"
	{
		if (relopt && segment != yystack.l_mark[-1].itemptr->i_value) {
			segment = yystack.l_mark[-1].itemptr->i_value;
			segchange = 1;
			dollarsign = seg_pos[yystack.l_mark[-1].itemptr->i_value];
		}
		list1();
	}
break;
case 38:
#line 2290 "zmac.y"
	{
		z80 = yystack.l_mark[-1].itemptr->i_value;
		list1();
	}
break;
case 39:
#line 2295 "zmac.y"
	{ param_parse = 1; }
break;
case 40:
#line 2295 "zmac.y"
	{
		param_parse = 0;
		yystack.l_mark[-4].itemptr->i_token = MNAME;
		yystack.l_mark[-4].itemptr->i_pass = npass;
		yystack.l_mark[-4].itemptr->i_value = mfptr;
		if (keyword(yystack.l_mark[-4].itemptr->i_string)) {
			sprintf(detail, "Macro '%s' will override the built-in '%s'",
				yystack.l_mark[-4].itemptr->i_string, yystack.l_mark[-4].itemptr->i_string);
			errwarn(warn_general, detail);
		}
#ifdef M_DEBUG
		fprintf (stderr, "%s(%d) [UNDECLARED MACRO %s]\n",
			src_name[now_in], linein[now_in], yystack.l_mark[-4].itemptr->i_string);
#endif
		list1();
	}
break;
case 41:
#line 2311 "zmac.y"
	{
		mlex_list_on++;
		mfseek(mfile, (long)mfptr, 0);
		mlex(yystack.l_mark[0].cval);
		mlex_list_on--;
		parm_number = 0;
	}
break;
case 42:
#line 2319 "zmac.y"
	{ arg_state.macarg = 1; }
break;
case 43:
#line 2319 "zmac.y"
	{
#ifdef M_DEBUG
		fprintf (stderr, "%s(%d) [MNAME %s]\n",
			src_name[now_in], linein[now_in], yystack.l_mark[-4].itemptr->i_string);
#endif
		yystack.l_mark[-4].itemptr->i_uses++ ;
		arg_reset();
		parm_number = 0;
		list(dollarsign);
		expptr++;
		est = est2;
		est2 = NULL; /* GWP - this may leak, but it avoids double-free crashes*/
		est[FLOC].value = floc;
		est[TEMPNUM].value = exp_number++;
		est[MIF].param = ifptr;
		est[REPNUM].value = 0;
		est[MSTR].param = NULL;
		floc = yystack.l_mark[-4].itemptr->i_value;
		mfseek(mfile, (long)floc, 0);
	}
break;
case 44:
#line 2340 "zmac.y"
	{
		expr_reloc_check(yystack.l_mark[-2].exprptr);
		list1();
		arg_reset();
	}
break;
case 45:
#line 2345 "zmac.y"
	{
		int pos = mfptr;
		mfseek(mfile, (long)mfptr, 0);
		mlex(yystack.l_mark[0].cval);
		parm_number = 0;

		/* MRAS compat would require treating the repeat count*/
		/* as a byte value with 0 == 256.*/
		if (yystack.l_mark[-4].exprptr->e_value > 0) {
			expptr++;
			est = est2;
			est2 = NULL;
			est[FLOC].value = floc;
			est[TEMPNUM].value = exp_number++;
			est[MIF].param = ifptr;
			est[REPNUM].value = yystack.l_mark[-4].exprptr->e_value - 1;
			est[MSTART].value = pos;
			est[MSTR].param = NULL;
			floc = pos;
			mfseek(mfile, (long)floc, 0);
		}
	}
break;
case 46:
#line 2368 "zmac.y"
	{ parm_number = 0; }
break;
case 47:
#line 2369 "zmac.y"
	{
		list1();
	}
break;
case 48:
#line 2372 "zmac.y"
	{
		int pos = mfptr;

		mfseek(mfile, (long)mfptr, 0);
		mlex(yystack.l_mark[0].cval);

		parm_number = 0;

		if (est2[0].param[0]) {
			expptr++;
			est = est2;
			est2 = NULL;
			est[FLOC].value = floc;
			est[TEMPNUM].value = exp_number++;
			est[MIF].param = ifptr;
			est[REPNUM].value = 0;
			est[MSTART].value = pos;
			est[MSTR].param = est[0].param;
			est[0].param = malloc(2);
			est[0].param[0] = est[MSTR].param[0];
			est[0].param[1] = '\0';
			floc = pos;
			mfseek(mfile, (long)floc, 0);
		}
	}
break;
case 49:
#line 2398 "zmac.y"
	{ parm_number = 0; }
break;
case 50:
#line 2399 "zmac.y"
	{
		list1();
	}
break;
case 51:
#line 2402 "zmac.y"
	{
		int pos = mfptr;
		mfseek(mfile, (long)mfptr, 0);
		mlex(yystack.l_mark[0].cval);

		parm_number = 0;
		/* if the sub list is not empty*/
		if (est2[0].param[0] && est2[0].param[0] != ';'
			&& est2[0].param[0] != '\n')
		{
			expptr++;
			est = est2;
			est2 = NULL;
			est[FLOC].value = floc;
			est[TEMPNUM].value = exp_number++;
			est[MIF].param = ifptr;
			est[REPNUM].value = -1;
			est[MSTART].value = pos;
			est[MSTR].param = NULL;

			est[MARGP].ap = malloc(sizeof *est[MARGP].ap);
			est[MARGP].ap->arg = malloc(TEMPBUFSIZE);
			est[MARGP].ap->argsize = TEMPBUFSIZE;
			est[MARGP].ap->getch = str_getch;
			est[MARGP].ap->user_ptr = est[0].param;
			est[MARGP].ap->user_int = 0;
			est[MARGP].ap->user_peek = -1;
			est[MARGP].ap->peek = &est[MARGP].ap->user_peek;
			est[MARGP].ap->macarg = 0;
			est[MARGP].ap->didarg = 0;
			est[MARGP].ap->numarg = 0;

			est[0].param = est[MARGP].ap->arg;
			getarg(est[MARGP].ap);

			floc = pos;
			mfseek(mfile, (long)floc, 0);
		}
	}
break;
case 52:
#line 2442 "zmac.y"
	{
		/* XXX - popsi() is not safe, There is type-specific cleanup.*/
		/*  But for now...*/
		/* popsi() must be made safe as others use it.*/
		list1();
		popsi();
	}
break;
case 53:
#line 2450 "zmac.y"
	{
		err[fflag]++;
		arg_reset();
		parm_number = 0;
		param_parse = 0;

		if (est2)
		{
			int i;
			for (i=0; i<PARMMAX; i++) {
				if (est2[i].param) {
#ifdef M_DEBUG
	fprintf (stderr, "[Freeing2 arg%u(%p)]\n", i, est2[i].param),
#endif
					free(est2[i].param);
				}
			}
			free(est2);
			est2 = NULL;
		}

		while(yychar != '\n' && yychar != '\0') yychar = yylex();
		list(dollarsign);
		yyclearin;yyerrok;
	}
break;
case 54:
#line 2478 "zmac.y"
	{ yyval.ival = 0; }
break;
case 55:
#line 2480 "zmac.y"
	{ yyval.ival = 1; }
break;
case 56:
#line 2482 "zmac.y"
	{ yyval.ival = 2; }
break;
case 57:
#line 2487 "zmac.y"
	{	label = yyval.itemptr = NULL;	}
break;
case 58:
#line 2489 "zmac.y"
	{
		coloncnt = yystack.l_mark[0].ival;
		itemcpy(&pristine_label, yystack.l_mark[-1].itemptr);
		label = coloncnt == 0 ? yystack.l_mark[-1].itemptr : NULL;
		yystack.l_mark[-1].itemptr->i_scope |= segment;
		if (yystack.l_mark[0].ival == 2)
			yystack.l_mark[-1].itemptr->i_scope |= SCOPE_PUBLIC;

		if (yystack.l_mark[-1].itemptr->i_string[0] != '.')
			llseq++;

		switch(yystack.l_mark[-1].itemptr->i_token) {
		case UNDECLARED:
			if (pass2) {
				sprintf(detail, "%s error - label '%s' not declared",
					errname[pflag], yystack.l_mark[-1].itemptr->i_string);
				errwarn(pflag, detail);
			}
			else {
				yystack.l_mark[-1].itemptr->i_token = LABEL;
				yystack.l_mark[-1].itemptr->i_pass = npass;
				yystack.l_mark[-1].itemptr->i_value = dollarsign;
			}
			break;
		case LABEL:
			if (!pass2) {
				yystack.l_mark[-1].itemptr->i_token = MULTDEF;
				yystack.l_mark[-1].itemptr->i_pass = npass;
				err[mflag]++;
			} else if (yystack.l_mark[-1].itemptr->i_value != dollarsign) {
				/* XXX - perhaps only allow retrys if JR promotions are in play?*/
				if (outpass) {
					if (!passfail) {
						sprintf(detail, "%s error - label '%s' changed from $%04x to $%04x",
							errname[pflag], yystack.l_mark[-1].itemptr->i_string, yystack.l_mark[-1].itemptr->i_value, dollarsign);
						errwarn(pflag, detail);
					}
				}
				else {
					yystack.l_mark[-1].itemptr->i_value = dollarsign;
					passretry = 1;
				}
			}
			break;
		default:
			err[mflag]++;
			yystack.l_mark[-1].itemptr->i_token = MULTDEF;
			yystack.l_mark[-1].itemptr->i_pass = npass;
		}
	}
break;
case 61:
#line 2548 "zmac.y"
	{
		yystack.l_mark[0].itemptr->i_scope |= SCOPE_PUBLIC;
		/* Just being "public" does not #ifdef define a symbol.*/
		if (pass2) {
			if (yystack.l_mark[0].itemptr->i_token == UNDECLARED) {
				sprintf(detail, "'%s' %s", yystack.l_mark[0].itemptr->i_string, errname[uflag]);
				errwarn(uflag, detail);
			}
		}
	}
break;
case 64:
#line 2567 "zmac.y"
	{
		if (pass2 && yystack.l_mark[0].itemptr->i_scope != SCOPE_NONE && !(yystack.l_mark[0].itemptr->i_scope & SCOPE_EXTERNAL)) {
			fprintf(stderr, "Label scope change\n");
			err[fflag]++;
		}
		yystack.l_mark[0].itemptr->i_pass = npass; /* external labels seen as defined for #ifdef*/
		yystack.l_mark[0].itemptr->i_scope |= SCOPE_EXTERNAL;
		if (pass2) {
			if (yystack.l_mark[0].itemptr->i_token != UNDECLARED) {
				fprintf(stderr, "External label defined locally.\n");
				err[fflag]++;
			}
		}
	}
break;
case 65:
#line 2584 "zmac.y"
	{ yyval.ival = '+'; }
break;
case 66:
#line 2585 "zmac.y"
	{ yyval.ival = '-'; }
break;
case 67:
#line 2586 "zmac.y"
	{ yyval.ival = '*'; }
break;
case 68:
#line 2587 "zmac.y"
	{ yyval.ival = '/'; }
break;
case 69:
#line 2588 "zmac.y"
	{ yyval.ival = '%'; }
break;
case 70:
#line 2589 "zmac.y"
	{ yyval.ival = '&'; }
break;
case 71:
#line 2590 "zmac.y"
	{ yyval.ival = '|'; }
break;
case 72:
#line 2591 "zmac.y"
	{ yyval.ival = '^'; }
break;
case 73:
#line 2592 "zmac.y"
	{ yyval.ival = ANDAND; }
break;
case 74:
#line 2593 "zmac.y"
	{ yyval.ival = OROR; }
break;
case 75:
#line 2594 "zmac.y"
	{ yyval.ival = SHL; }
break;
case 76:
#line 2595 "zmac.y"
	{ yyval.ival = SHR; }
break;
case 77:
#line 2597 "zmac.y"
	{ yyval.ival = '+'; }
break;
case 78:
#line 2598 "zmac.y"
	{ yyval.ival = '-'; }
break;
case 79:
#line 2599 "zmac.y"
	{ yyval.ival = '*'; }
break;
case 80:
#line 2600 "zmac.y"
	{ yyval.ival = '/'; }
break;
case 81:
#line 2601 "zmac.y"
	{ yyval.ival = '%'; }
break;
case 82:
#line 2602 "zmac.y"
	{ yyval.ival = '&'; }
break;
case 83:
#line 2603 "zmac.y"
	{ yyval.ival = '|'; }
break;
case 84:
#line 2604 "zmac.y"
	{ yyval.ival = '^'; }
break;
case 85:
#line 2605 "zmac.y"
	{ yyval.ival = MROP_SHL; }
break;
case 86:
#line 2606 "zmac.y"
	{ yyval.ival = MROP_SHR; }
break;
case 87:
#line 2607 "zmac.y"
	{ yyval.ival = MROP_SHIFT; }
break;
case 88:
#line 2612 "zmac.y"
	{ emit1(yystack.l_mark[0].itemptr->i_value, 0, 0, ET_NOARG); }
break;
case 89:
#line 2615 "zmac.y"
	{
			/* XXX - maybe splitting out CPI is better?*/
			if (!z80 && yystack.l_mark[-1].itemptr->i_value == 0166641)
				emit1(0376, 0, yystack.l_mark[0].exprptr, ET_BYTE);
			else
				err[fflag]++;
		}
break;
case 90:
#line 2624 "zmac.y"
	{
			if (!z80 && yystack.l_mark[0].itemptr->i_value < 2)
				emit(1, E_CODE, 0, 007 | (yystack.l_mark[0].itemptr->i_value << 3));
			else
				err[fflag]++;
		}
break;
case 91:
#line 2632 "zmac.y"
	{
		if (z80 || yystack.l_mark[-1].itemptr->i_value == 0303) {
			checkjp(0, yystack.l_mark[0].exprptr);
			emit(1, E_CODE16, yystack.l_mark[0].exprptr, 0303);
		}
		else
			/* can't optimize jump on plus*/
			emit(1, E_CODE16, yystack.l_mark[0].exprptr, 0362);
	}
break;
case 92:
#line 2643 "zmac.y"
	{	emit(1, E_CODE16, yystack.l_mark[0].exprptr, 0315);	}
break;
case 93:
#line 2646 "zmac.y"
	{
		/* accepts rst 0-7 or rst 0,8,16,...,56*/
		int vec = yystack.l_mark[0].exprptr->e_value;
		expr_number_check(yystack.l_mark[0].exprptr);
		if ((vec > 7 || vec < 0) && (vec & ~(7 << 3)))
			err[vflag]++;
		if (vec > 7) vec >>= 3;
		emit(1, E_CODE, 0, yystack.l_mark[-1].itemptr->i_value + ((vec & 7) << 3));
		expr_free(yystack.l_mark[0].exprptr);
	}
break;
case 94:
#line 2658 "zmac.y"
	{ emit1(yystack.l_mark[-1].itemptr->i_value, 0, yystack.l_mark[0].exprptr, ET_BYTE); }
break;
case 95:
#line 2661 "zmac.y"
	{
			emit(3, E_CODE, 0, yystack.l_mark[-1].itemptr->i_value >> 8, yystack.l_mark[-1].itemptr->i_value, disp);
		}
break;
case 96:
#line 2666 "zmac.y"
	{ emit1(0306, 0, yystack.l_mark[0].exprptr, ET_BYTE); }
break;
case 97:
#line 2669 "zmac.y"
	{ emit1(0306, 0, yystack.l_mark[0].exprptr, ET_BYTE); }
break;
case 98:
#line 2672 "zmac.y"
	{ emit1(0306 + (yystack.l_mark[-1].itemptr->i_value << 3), 0, yystack.l_mark[0].exprptr, ET_BYTE); }
break;
case 99:
#line 2675 "zmac.y"
	{ emit1(0306 + (yystack.l_mark[-3].itemptr->i_value << 3), 0, yystack.l_mark[0].exprptr, ET_BYTE); }
break;
case 100:
#line 2678 "zmac.y"
	{
			if (!z80 && yystack.l_mark[-1].itemptr->i_value == 7)
				emit(1, E_CODE16, yystack.l_mark[0].exprptr, 0364);
			else
				emit1(0306 | (yystack.l_mark[-1].itemptr->i_value << 3), 0, yystack.l_mark[0].exprptr, ET_BYTE);
		}
break;
case 101:
#line 2686 "zmac.y"
	{ emit1(0306 | (yystack.l_mark[-1].itemptr->i_value << 3), 0, yystack.l_mark[0].exprptr, ET_BYTE); }
break;
case 102:
#line 2689 "zmac.y"
	{ emit1(0306 | (yystack.l_mark[-1].itemptr->i_value << 3), 0, yystack.l_mark[0].exprptr, ET_BYTE); }
break;
case 103:
#line 2692 "zmac.y"
	{ emit1(0306 | (yystack.l_mark[-1].itemptr->i_value << 3), 0, yystack.l_mark[0].exprptr, ET_BYTE); }
break;
case 104:
#line 2695 "zmac.y"
	{ emit1(0306 | (yystack.l_mark[-3].itemptr->i_value << 3), 0, yystack.l_mark[0].exprptr, ET_BYTE); }
break;
case 105:
#line 2698 "zmac.y"
	{ emit1(0306 | (yystack.l_mark[-3].itemptr->i_value << 3), 0, yystack.l_mark[0].exprptr, ET_BYTE); }
break;
case 106:
#line 2701 "zmac.y"
	{ emit1(0306 | (yystack.l_mark[-3].itemptr->i_value << 3), 0, yystack.l_mark[0].exprptr, ET_BYTE); }
break;
case 107:
#line 2704 "zmac.y"
	{ emit1(0306 | (yystack.l_mark[-3].itemptr->i_value << 3), 0, yystack.l_mark[0].exprptr, ET_BYTE); }
break;
case 108:
#line 2707 "zmac.y"
	{ emit1(0200 + (yystack.l_mark[0].ival & 0377), yystack.l_mark[0].ival, 0, ET_NOARG_DISP); }
break;
case 109:
#line 2710 "zmac.y"
	{ emit1(0200 + (yystack.l_mark[0].ival & 0377), yystack.l_mark[0].ival, 0, ET_NOARG_DISP); }
break;
case 110:
#line 2713 "zmac.y"
	{ emit(1, E_CODE, 0, 0206); }
break;
case 111:
#line 2716 "zmac.y"
	{ emit1(0200 + (yystack.l_mark[-1].itemptr->i_value << 3) + (yystack.l_mark[0].ival & 0377), yystack.l_mark[0].ival, 0, ET_NOARG_DISP); }
break;
case 112:
#line 2719 "zmac.y"
	{ emit1(0200 + (yystack.l_mark[-3].itemptr->i_value << 3) + (yystack.l_mark[0].ival & 0377), yystack.l_mark[0].ival, 0, ET_NOARG_DISP); }
break;
case 113:
#line 2722 "zmac.y"
	{ emit1(0200 + (yystack.l_mark[-1].itemptr->i_value << 3) + (yystack.l_mark[0].ival & 0377), yystack.l_mark[0].ival, 0, ET_NOARG_DISP); }
break;
case 114:
#line 2725 "zmac.y"
	{ emit1(0200 + (yystack.l_mark[-1].itemptr->i_value << 3) + (yystack.l_mark[0].ival & 0377), yystack.l_mark[0].ival, 0, ET_NOARG_DISP); }
break;
case 115:
#line 2728 "zmac.y"
	{ emit1(0200 + (yystack.l_mark[-1].itemptr->i_value << 3) + (yystack.l_mark[0].ival & 0377), yystack.l_mark[0].ival, 0, ET_NOARG_DISP); }
break;
case 116:
#line 2731 "zmac.y"
	{ emit1(0200 + (yystack.l_mark[-1].itemptr->i_value << 3) + (yystack.l_mark[0].ival & 0377), yystack.l_mark[0].ival, 0, ET_NOARG_DISP); }
break;
case 117:
#line 2734 "zmac.y"
	{ emit1(0200 + (yystack.l_mark[-1].itemptr->i_value << 3) + (yystack.l_mark[0].ival & 0377), yystack.l_mark[0].ival, 0, ET_NOARG_DISP); }
break;
case 118:
#line 2737 "zmac.y"
	{ emit1(0200 + (yystack.l_mark[-1].itemptr->i_value << 3) + (yystack.l_mark[0].ival & 0377), yystack.l_mark[0].ival, 0, ET_NOARG_DISP); }
break;
case 119:
#line 2740 "zmac.y"
	{ emit1(0200 + (yystack.l_mark[-3].itemptr->i_value << 3) + (yystack.l_mark[0].ival & 0377), yystack.l_mark[0].ival, 0, ET_NOARG_DISP); }
break;
case 120:
#line 2743 "zmac.y"
	{ emit1(0200 + (yystack.l_mark[-3].itemptr->i_value << 3) + (yystack.l_mark[0].ival & 0377), yystack.l_mark[0].ival, 0, ET_NOARG_DISP); }
break;
case 121:
#line 2746 "zmac.y"
	{ emit1(0200 + (yystack.l_mark[-3].itemptr->i_value << 3) + (yystack.l_mark[0].ival & 0377), yystack.l_mark[0].ival, 0, ET_NOARG_DISP); }
break;
case 122:
#line 2749 "zmac.y"
	{ emit1(0200 + (yystack.l_mark[-3].itemptr->i_value << 3) + (yystack.l_mark[0].ival & 0377), yystack.l_mark[0].ival, 0, ET_NOARG_DISP); }
break;
case 123:
#line 2752 "zmac.y"
	{ emit1(0145400 + (yystack.l_mark[-1].itemptr->i_value << 3) + (yystack.l_mark[0].ival & 0377), yystack.l_mark[0].ival, 0, ET_NOARG_DISP); }
break;
case 124:
#line 2755 "zmac.y"
	{
			emit(4, E_CODE, 0, yystack.l_mark[-1].itemptr->i_value >> 8, 0xcb, disp, yystack.l_mark[-1].itemptr->i_value);
		}
break;
case 125:
#line 2760 "zmac.y"
	{ emit1(0xCB00 + (yystack.l_mark[-3].itemptr->i_value << 3) + (yystack.l_mark[0].ival & 0377), yystack.l_mark[-2].ival, 0, ET_NOARG_DISP); }
break;
case 126:
#line 2763 "zmac.y"
	{ emit1(yystack.l_mark[-1].itemptr->i_value + ((yystack.l_mark[0].ival & 0377) << 3) + 4, yystack.l_mark[0].ival, 0, ET_NOARG_DISP); }
break;
case 127:
#line 2766 "zmac.y"
	{ emit1(yystack.l_mark[-1].itemptr->i_value + ((yystack.l_mark[0].ival & 0377) << 3) + 4, yystack.l_mark[0].ival, 0, ET_NOARG_DISP); }
break;
case 128:
#line 2769 "zmac.y"
	{ if (yystack.l_mark[-3].itemptr->i_value == 1)
				emit(2,E_CODE,0,0355,0112+yystack.l_mark[0].ival);
			else
				emit(2,E_CODE,0,0355,0102+yystack.l_mark[0].ival);
		}
break;
case 129:
#line 2776 "zmac.y"
	{ emitdad(yystack.l_mark[-2].ival,yystack.l_mark[0].ival); }
break;
case 130:
#line 2779 "zmac.y"
	{
			if (yystack.l_mark[-2].ival != yystack.l_mark[0].ival) {
				fprintf(stderr,"ADD mar, mar error\n");
				err[gflag]++;
			}
			emitdad(yystack.l_mark[-2].ival,yystack.l_mark[0].ival);
		}
break;
case 131:
#line 2787 "zmac.y"
	{ emitdad(040, yystack.l_mark[0].ival); }
break;
case 132:
#line 2790 "zmac.y"
	{
			emit(2, E_CODE, 0, yystack.l_mark[-1].itemptr->i_value >> 8, yystack.l_mark[-1].itemptr->i_value | yystack.l_mark[0].ival);
		}
break;
case 133:
#line 2795 "zmac.y"
	{
			int dst = yystack.l_mark[-1].itemptr->i_value >> 8;
			int reg = yystack.l_mark[0].ival >> 8;
			if (!reg) reg = 0xed;

			if (dst != reg) {
				if (dst == 0xed)
					fprintf(stderr, "dadc/dsbc cannot take ix or iy\n");
				else if (dst == 0xdd)
					fprintf(stderr, "dadx cannot take hl or iy\n");
				else
					fprintf(stderr, "dady cannot take hl or ix\n");
				err[gflag]++;
			}
			emit(2, E_CODE, 0, yystack.l_mark[-1].itemptr->i_value >> 8, yystack.l_mark[-1].itemptr->i_value | yystack.l_mark[0].ival);
		}
break;
case 134:
#line 2813 "zmac.y"
	{ emit1((yystack.l_mark[-1].itemptr->i_value << 3) + (yystack.l_mark[0].ival & 0377) + 3, yystack.l_mark[0].ival, 0, ET_NOARG); }
break;
case 135:
#line 2816 "zmac.y"
	{ emit1((yystack.l_mark[-1].itemptr->i_value << 3) + (yystack.l_mark[0].ival & 0377) + 3, yystack.l_mark[0].ival, 0, ET_NOARG); }
break;
case 136:
#line 2819 "zmac.y"
	{ emit1(yystack.l_mark[-1].itemptr->i_value + (yystack.l_mark[0].ival & 0377), yystack.l_mark[0].ival, 0, ET_NOARG); }
break;
case 137:
#line 2822 "zmac.y"
	{ emit1(yystack.l_mark[-1].itemptr->i_value + (yystack.l_mark[0].ival & 0377), yystack.l_mark[0].ival, 0, ET_NOARG); }
break;
case 138:
#line 2825 "zmac.y"
	{
			if (strcmp(yystack.l_mark[-1].itemptr->i_string, "set") == 0 && label) {
				/* Clear error that label definition will have been set*/
				err[mflag] = 0;
				itemcpy(label, &pristine_label);
				do_defl(label, yystack.l_mark[0].exprptr, 0);
				list_dollarsign = 0;
				list_addr = label->i_value;
			}
			else {
				err[fflag]++;
			}
		}
break;
case 139:
#line 2840 "zmac.y"
	{
			int bit = yystack.l_mark[-2].exprptr->e_value;
			expr_number_check(yystack.l_mark[-2].exprptr);
			expr_free(yystack.l_mark[-2].exprptr);
			if (bit < 0 || bit > 7)
				err[vflag]++;
			emit1(yystack.l_mark[-3].itemptr->i_value + ((bit & 7) << 3) + (yystack.l_mark[0].ival & 0377), yystack.l_mark[0].ival, 0, ET_NOARG_DISP);
		}
break;
case 140:
#line 2850 "zmac.y"
	{
			int bit = yystack.l_mark[-2].exprptr->e_value;
			expr_number_check(yystack.l_mark[-2].exprptr);
			expr_free(yystack.l_mark[-2].exprptr);
			if (bit < 0 || bit > 7)
				err[vflag]++;
			emit(4, E_CODE, 0, yystack.l_mark[-3].itemptr->i_value >> 8, 0xcb, disp,
				yystack.l_mark[-3].itemptr->i_value | (bit << 3));
		}
break;
case 141:
#line 2861 "zmac.y"
	{
			int bit = yystack.l_mark[-4].exprptr->e_value;
			expr_number_check(yystack.l_mark[-4].exprptr);
			expr_free(yystack.l_mark[-4].exprptr);
			if (bit < 0 || bit > 7)
				err[vflag]++;
			emit1(yystack.l_mark[-5].itemptr->i_value + ((bit & 7) << 3) + (yystack.l_mark[0].ival & 0377), yystack.l_mark[-2].ival, 0, ET_NOARG_DISP);
		}
break;
case 142:
#line 2871 "zmac.y"
	{
		checkjp(yystack.l_mark[-2].ival, yystack.l_mark[0].exprptr);
		emit(1, E_CODE16, yystack.l_mark[0].exprptr, 0302 + yystack.l_mark[-2].ival);
	}
break;
case 143:
#line 2877 "zmac.y"
	{
		checkjp(yystack.l_mark[-1].itemptr->i_value, yystack.l_mark[0].exprptr);
		emit(1, E_CODE16, yystack.l_mark[0].exprptr, yystack.l_mark[-1].itemptr->i_value);
	}
break;
case 144:
#line 2883 "zmac.y"
	{ emit1(0351, yystack.l_mark[-1].ival, 0, ET_NOARG); }
break;
case 145:
#line 2886 "zmac.y"
	{ emit(1, E_CODE16, yystack.l_mark[0].exprptr, 0304 + yystack.l_mark[-2].ival); }
break;
case 146:
#line 2889 "zmac.y"
	{ emit(1, E_CODE16, yystack.l_mark[0].exprptr, yystack.l_mark[-1].itemptr->i_value); }
break;
case 147:
#line 2892 "zmac.y"
	{ emitjr(030,yystack.l_mark[0].exprptr); }
break;
case 148:
#line 2895 "zmac.y"
	{ emitjr(yystack.l_mark[-3].itemptr->i_value + yystack.l_mark[-2].ival, yystack.l_mark[0].exprptr); }
break;
case 149:
#line 2898 "zmac.y"
	{ emitjr(yystack.l_mark[-1].itemptr->i_value, yystack.l_mark[0].exprptr); }
break;
case 150:
#line 2901 "zmac.y"
	{ emitjr(yystack.l_mark[-1].itemptr->i_value, yystack.l_mark[0].exprptr); }
break;
case 151:
#line 2904 "zmac.y"
	{ emit(1, E_CODE, 0, yystack.l_mark[0].itemptr->i_value); }
break;
case 152:
#line 2907 "zmac.y"
	{ emit(1, E_CODE, 0, 0300 + yystack.l_mark[0].ival); }
break;
case 153:
#line 2910 "zmac.y"
	{
			/* Many constraints on byte access to IX/IY registers.*/
			if ((yystack.l_mark[-2].ival | yystack.l_mark[0].ival) >> 16) {
				int a = yystack.l_mark[-2].ival;
				int b = yystack.l_mark[0].ival;

				/* Only ixh,ixh; ixh,ixl; ixl,ixh; ixl,ixl allowed.*/
				if (a >> 16 && b >> 16) {
					if (a >> 8 != b >> 8) {
						fprintf(stderr, "LD cannot move between ix and iy\n");
						err[gflag]++;
					}
				}
				else {
					int c = b >> 16 ? a : b;
					/* No access to h, l, (hl), (ix), (iy)*/
					if (c == 4 || c == 5 || (c & 0xff) == 6) {
						fprintf(stderr, "LD cannot combine i/xy/lh and h,l,(hl),(ix) or (iy).\n");
						err[gflag]++;
					}
				}
			}

			if ((yystack.l_mark[-2].ival & 0377) == 6 && (yystack.l_mark[0].ival & 0377) == 6) {
				fprintf(stderr,"LD reg, reg error: can't do memory to memory\n");
				err[gflag]++;
			}
			emit1(0100 + ((yystack.l_mark[-2].ival & 7) << 3) + (yystack.l_mark[0].ival & 7),yystack.l_mark[-2].ival | yystack.l_mark[0].ival, 0, ET_NOARG_DISP);
		}
break;
case 154:
#line 2941 "zmac.y"
	{
			emit(3, E_CODE, 0, yystack.l_mark[-3].itemptr->i_value >> 8, yystack.l_mark[-3].itemptr->i_value | (yystack.l_mark[-2].ival << 3), disp);
		}
break;
case 155:
#line 2946 "zmac.y"
	{
			emit(3, E_CODE, 0, yystack.l_mark[-3].itemptr->i_value >> 8, yystack.l_mark[-3].itemptr->i_value | yystack.l_mark[-2].ival, disp);
		}
break;
case 156:
#line 2951 "zmac.y"
	{
			if (yystack.l_mark[-2].ival == 6 && yystack.l_mark[0].ival == 6) err[gflag]++;
			emit1(0100 + ((yystack.l_mark[-2].ival & 7) << 3) + (yystack.l_mark[0].ival & 7),yystack.l_mark[-2].ival | yystack.l_mark[0].ival, 0, ET_NOARG_DISP);
		}
break;
case 157:
#line 2957 "zmac.y"
	{ emit1(6 + ((yystack.l_mark[-2].ival & 0377) << 3), yystack.l_mark[-2].ival, yystack.l_mark[0].exprptr, ET_BYTE); }
break;
case 158:
#line 2960 "zmac.y"
	{
			emit(3, E_CODE8, yystack.l_mark[-2].exprptr, yystack.l_mark[-3].itemptr->i_value >> 8, yystack.l_mark[-3].itemptr->i_value, disp);
		}
break;
case 159:
#line 2965 "zmac.y"
	{ emit1(6 + ((yystack.l_mark[-2].ival & 0377) << 3), yystack.l_mark[-2].ival, yystack.l_mark[0].exprptr, ET_BYTE); }
break;
case 160:
#line 2968 "zmac.y"
	{	if (yystack.l_mark[-4].ival != 7) {
				fprintf(stderr,"LD reg, (RP) error\n");
				err[gflag]++;
			}
			else emit(1, E_CODE, 0, 012 + yystack.l_mark[-1].itemptr->i_value);
		}
break;
case 161:
#line 2976 "zmac.y"
	{
			if (yystack.l_mark[0].ival != 0 && yystack.l_mark[0].ival != 2) err[gflag]++;
			emit(1, E_CODE, 0, 012 + (yystack.l_mark[0].ival << 3));
		}
break;
case 162:
#line 2982 "zmac.y"
	{
			if (yystack.l_mark[-2].ival != 7) {
				fprintf(stderr,"LD reg, (expr) error: A only valid destination\n");
				err[gflag]++;
			}
			else {
				expr_word_check(yystack.l_mark[0].exprptr);
				emit(1, E_CODE16, yystack.l_mark[0].exprptr, 072);
			}
		}
break;
case 163:
#line 2994 "zmac.y"
	{
			expr_word_check(yystack.l_mark[0].exprptr);
			emit(1, E_CODE16, yystack.l_mark[0].exprptr, 072);
		}
break;
case 164:
#line 3000 "zmac.y"
	{ emit(1, E_CODE, 0, 2 + yystack.l_mark[-3].itemptr->i_value); }
break;
case 165:
#line 3003 "zmac.y"
	{
			if (yystack.l_mark[0].ival != 0 && yystack.l_mark[0].ival != 2) err[gflag]++;
			emit(1, E_CODE, 0, 2 + (yystack.l_mark[0].ival << 3));
		}
break;
case 166:
#line 3009 "zmac.y"
	{
			expr_word_check(yystack.l_mark[-2].exprptr);
			emit(1, E_CODE16, yystack.l_mark[-2].exprptr, 062);
		}
break;
case 167:
#line 3015 "zmac.y"
	{
			expr_word_check(yystack.l_mark[0].exprptr);
			emit(1, E_CODE16, yystack.l_mark[0].exprptr, 062);
		}
break;
case 168:
#line 3021 "zmac.y"
	{
			if (yystack.l_mark[-2].ival != 7) {
				fprintf(stderr,"LD reg, MISCREG error: A only valid destination\n");
				err[gflag]++;
			}
			else emit(2, E_CODE, 0, 0355, 0127 + yystack.l_mark[0].itemptr->i_value);
		}
break;
case 169:
#line 3030 "zmac.y"
	{ emit(2, E_CODE, 0, 0355, 0107 + yystack.l_mark[-2].itemptr->i_value); }
break;
case 170:
#line 3033 "zmac.y"
	{
			expr_word_check(yystack.l_mark[0].exprptr);
			emit1(1 + (yystack.l_mark[-2].ival & 060), yystack.l_mark[-2].ival, yystack.l_mark[0].exprptr, ET_WORD);
		}
break;
case 171:
#line 3039 "zmac.y"
	{
			expr_word_check(yystack.l_mark[0].exprptr);
			emit1(1 + (yystack.l_mark[-2].ival & 060), yystack.l_mark[-2].ival, yystack.l_mark[0].exprptr, ET_WORD);
		}
break;
case 172:
#line 3045 "zmac.y"
	{
			expr_word_check(yystack.l_mark[0].exprptr);
			if ((yystack.l_mark[-2].ival & 060) == 040)
				emit1(052, yystack.l_mark[-2].ival, yystack.l_mark[0].exprptr, ET_WORD);
			else
				emit(2, E_CODE16, yystack.l_mark[0].exprptr, 0355, 0113 + yystack.l_mark[-2].ival);
		}
break;
case 173:
#line 3054 "zmac.y"
	{
			expr_word_check(yystack.l_mark[0].exprptr);
			emit1(052, 040, yystack.l_mark[0].exprptr, ET_WORD);
		}
break;
case 174:
#line 3060 "zmac.y"
	{
			expr_word_check(yystack.l_mark[-2].exprptr);
			if ((yystack.l_mark[0].ival & 060) == 040)
				emit1(042, yystack.l_mark[0].ival, yystack.l_mark[-2].exprptr, ET_WORD);
			else
				emit(2, E_CODE16, yystack.l_mark[-2].exprptr, 0355, 0103 + yystack.l_mark[0].ival);
		}
break;
case 175:
#line 3069 "zmac.y"
	{
			expr_word_check(yystack.l_mark[0].exprptr);
			emit1(042, 040, yystack.l_mark[0].exprptr, ET_WORD);
		}
break;
case 176:
#line 3075 "zmac.y"
	{
			if (yystack.l_mark[-2].ival != 060) {
				fprintf(stderr,"LD evenreg error\n");
				err[gflag]++;
			}
			else
				emit1(0371, yystack.l_mark[0].ival, 0, ET_NOARG);
		}
break;
case 177:
#line 3085 "zmac.y"
	{
			expr_word_check(yystack.l_mark[0].exprptr);
			emit(2, E_CODE16, yystack.l_mark[0].exprptr, yystack.l_mark[-1].itemptr->i_value >> 8, yystack.l_mark[-1].itemptr->i_value);
		}
break;
case 178:
#line 3091 "zmac.y"
	{
			if (yystack.l_mark[-2].itemptr->i_value != 020) {
				fprintf(stderr,"EX RP, HL error\n");
				err[gflag]++;
			}
			else
				emit(1, E_CODE, 0, 0353);
		}
break;
case 179:
#line 3101 "zmac.y"
	{ emit(1, E_CODE, 0, 010); }
break;
case 180:
#line 3104 "zmac.y"
	{ emit1(0343, yystack.l_mark[0].ival, 0, ET_NOARG); }
break;
case 181:
#line 3107 "zmac.y"
	{
			if (yystack.l_mark[-2].ival != 7) {
				fprintf(stderr,"IN reg, (expr) error\n");
				err[gflag]++;
			}
			else	{
				if (yystack.l_mark[0].exprptr->e_value < 0 || yystack.l_mark[0].exprptr->e_value > 255)
					err[vflag]++;
				emit(1, E_CODE8, yystack.l_mark[0].exprptr, yystack.l_mark[-3].itemptr->i_value);
			}
		}
break;
case 182:
#line 3120 "zmac.y"
	{
			if (yystack.l_mark[0].exprptr->e_value < 0 || yystack.l_mark[0].exprptr->e_value > 255)
				err[vflag]++;
			emit(1, E_CODE8, yystack.l_mark[0].exprptr, yystack.l_mark[-1].itemptr->i_value);
		}
break;
case 183:
#line 3127 "zmac.y"
	{ emit(2, E_CODE, 0, 0355, 0100 + (yystack.l_mark[-4].ival << 3)); }
break;
case 184:
#line 3130 "zmac.y"
	{ emit(2, E_CODE, 0, 0355, 0101 + (yystack.l_mark[0].ival << 3)); }
break;
case 185:
#line 3133 "zmac.y"
	{ emit(2, E_CODE, 0, 0355, 0160); }
break;
case 186:
#line 3136 "zmac.y"
	{ emit(2, E_CODE, 0, 0355, 0160); }
break;
case 187:
#line 3139 "zmac.y"
	{
			if (yystack.l_mark[-2].exprptr->e_value < 0 || yystack.l_mark[-2].exprptr->e_value > 255)
				err[vflag]++;
			emit(1, E_CODE8, yystack.l_mark[-2].exprptr, yystack.l_mark[-3].itemptr->i_value);
		}
break;
case 188:
#line 3146 "zmac.y"
	{
			if (yystack.l_mark[0].exprptr->e_value < 0 || yystack.l_mark[0].exprptr->e_value > 255)
				err[vflag]++;
			emit(1, E_CODE8, yystack.l_mark[0].exprptr, yystack.l_mark[-1].itemptr->i_value);
		}
break;
case 189:
#line 3153 "zmac.y"
	{ emit(2, E_CODE, 0, 0355, 0101 + (yystack.l_mark[0].ival << 3)); }
break;
case 190:
#line 3156 "zmac.y"
	{ emit(2, E_CODE, 0, 0355, 0101 + (yystack.l_mark[0].ival << 3)); }
break;
case 191:
#line 3159 "zmac.y"
	{
			expr_number_check(yystack.l_mark[0].exprptr);
			if (yystack.l_mark[0].exprptr->e_value != 0) {
				fprintf(stderr, "Can only output 0 to port C with OUT\n");
				err[vflag]++;
			}
			expr_free(yystack.l_mark[0].exprptr);

			emit(2, E_CODE8, 0, 0355, 0101 + (6 << 3));
		}
break;
case 192:
#line 3171 "zmac.y"
	{
			int im = yystack.l_mark[0].exprptr->e_value;
			expr_number_check(yystack.l_mark[0].exprptr);
			expr_free(yystack.l_mark[0].exprptr);
			if (im > 2 || im < 0)
				err[vflag]++;
			else
				emit(2, E_CODE, 0, yystack.l_mark[-1].itemptr->i_value >> 8, yystack.l_mark[-1].itemptr->i_value + ((im + (im > 0)) << 3));
		}
break;
case 193:
#line 3182 "zmac.y"
	{
			expr_number_check(yystack.l_mark[0].exprptr);
			if (phaseflag) {
				err[oflag]++;
			} else {
				phaseflag = 1;
				phdollar = dollarsign;
				dollarsign = yystack.l_mark[0].exprptr->e_value;
				phbegin = dollarsign;
			}
			expr_free(yystack.l_mark[0].exprptr);
		}
break;
case 194:
#line 3196 "zmac.y"
	{
			if (!phaseflag) {
				err[oflag]++;
			} else {
				phaseflag = 0;
				dollarsign = phdollar + dollarsign - phbegin;
			}
		}
break;
case 195:
#line 3206 "zmac.y"
	{
			expr_reloc_check(yystack.l_mark[0].exprptr);
			/* Cannot org to the other segment (but absolute values are OK)*/
			if (relopt && segment && (yystack.l_mark[0].exprptr->e_scope & SCOPE_SEGMASK) != segment)
				err[rflag]++;
			if (phaseflag) {
				err[oflag]++;
				dollarsign = phdollar + dollarsign - phbegin;
				phaseflag = 0;
			}
			if (yystack.l_mark[0].exprptr->e_value-dollarsign) {
				flushbin();
				flushoth();
				olddollar = yystack.l_mark[0].exprptr->e_value;
				oldothdollar = yystack.l_mark[0].exprptr->e_value;
				dollarsign = yystack.l_mark[0].exprptr->e_value;
				emit_addr = yystack.l_mark[0].exprptr->e_value;
				seg_pos[segment] = dollarsign;
				if (seg_pos[segment] > seg_size[segment])
					seg_size[segment] = seg_pos[segment];
				putrelcmd(RELCMD_SETLOC);
				putrelsegref(segment, seg_pos[segment]);
				segchange = 0;
			}
			expr_free(yystack.l_mark[0].exprptr);
		}
break;
case 196:
#line 3234 "zmac.y"
	{
			list_dollarsign = 0;
			list_addr = yystack.l_mark[0].exprptr->e_value;
			expr_number_check(yystack.l_mark[0].exprptr);
			if (outpass && !yystack.l_mark[0].exprptr->e_value)
			{
				err[aflag]++;
			}
			expr_free(yystack.l_mark[0].exprptr);
		}
break;
case 197:
#line 3246 "zmac.y"
	{
			list_dollarsign = 0;
			list_addr = yystack.l_mark[0].exprptr->e_value;
			expr_number_check(yystack.l_mark[0].exprptr);
			tstates = yystack.l_mark[0].exprptr->e_value;
			tstatesum[emit_addr] = tstates;
			expr_free(yystack.l_mark[0].exprptr);
		}
break;
case 198:
#line 3256 "zmac.y"
	{
			list_dollarsign = 0;
			list_addr = yystack.l_mark[0].exprptr->e_value;
			expr_number_check(yystack.l_mark[0].exprptr);
			ocf = yystack.l_mark[0].exprptr->e_value;
			ocfsum[emit_addr] = ocf;
			expr_free(yystack.l_mark[0].exprptr);
		}
break;
case 199:
#line 3265 "zmac.y"
	{ full_exprs = 1; }
break;
case 200:
#line 3265 "zmac.y"
	{ full_exprs = 0; }
break;
case 201:
#line 3267 "zmac.y"
	{ full_exprs = 1; }
break;
case 202:
#line 3267 "zmac.y"
	{ full_exprs = 0; }
break;
case 203:
#line 3269 "zmac.y"
	{ full_exprs = 1; }
break;
case 204:
#line 3269 "zmac.y"
	{ full_exprs = 0; }
break;
case 209:
#line 3281 "zmac.y"
	{ param_parse = 1; }
break;
case 210:
#line 3281 "zmac.y"
	{ param_parse = 0; }
break;
case 211:
#line 3283 "zmac.y"
	{ yyval.ival = 0; }
break;
case 212:
#line 3283 "zmac.y"
	{ yyval.ival = 1; }
break;
case 213:
#line 3287 "zmac.y"
	{
			if (parm_number >= PARMMAX)
				error("Too many parameters");
			yystack.l_mark[0].itemptr->i_value = parm_number++;
			yystack.l_mark[0].itemptr->i_scope = yystack.l_mark[-1].ival;
			yystack.l_mark[0].itemptr->i_chain = 0;
		}
break;
case 214:
#line 3296 "zmac.y"
	{
		static char macpush[LINEBUFFERSIZE];
		/* Because of locals the parser has to look ahead.*/
		/* We'll have buffered that as we usually do so just a*/
		/* matter of picking that up and cancelling any look-ahead.*/
		*lineptr = '\0';
		strcpy(macpush, linebuf);
		lineptr = linebuf;
		peekc = NOPEEK;
		yychar = YYEMPTY;
		yyval.cval = macpush;
	}
break;
case 216:
#line 3312 "zmac.y"
	{ param_parse = 1; }
break;
case 217:
#line 3312 "zmac.y"
	{ param_parse = 0; list1(); }
break;
case 221:
#line 3324 "zmac.y"
	{
			if (parm_number >= PARMMAX)
				error("Too many parameters");
			yystack.l_mark[0].itemptr->i_value = parm_number++;
			yystack.l_mark[0].itemptr->i_scope = 0;
			yystack.l_mark[0].itemptr->i_chain = 1;
		}
break;
case 225:
#line 3344 "zmac.y"
	{
			cp = malloc(strlen(tempbuf)+1);
#ifdef M_DEBUG
			fprintf (stderr, "[Arg%u(%p): %s]\n", parm_number, cp, tempbuf);
#endif
			est2[parm_number++].param = cp;
			strcpy(cp, tempbuf);
		}
break;
case 226:
#line 3353 "zmac.y"
	{ arg_flag = 0; }
break;
case 227:
#line 3354 "zmac.y"
	{
			arg_flag = 1;
			expr_reloc_check(yystack.l_mark[0].exprptr);
			sprintf(tempbuf, "%d", yystack.l_mark[0].exprptr->e_value);
			est2[parm_number++].param = strdup(tempbuf);
			expr_free(yystack.l_mark[0].exprptr);
		}
break;
case 232:
#line 3375 "zmac.y"
	{
			yyval.ival = yystack.l_mark[0].itemptr->i_value;
		}
break;
case 235:
#line 3385 "zmac.y"
	{ if (yystack.l_mark[0].itemptr->i_value != 070) err[gflag]++; yyval.ival = 6; }
break;
case 236:
#line 3389 "zmac.y"
	{
			yyval.ival = yystack.l_mark[0].itemptr->i_value;
		}
break;
case 237:
#line 3394 "zmac.y"
	{
			yyval.ival = yystack.l_mark[0].itemptr->i_value;
		}
break;
case 238:
#line 3399 "zmac.y"
	{
			yyval.ival = yystack.l_mark[0].itemptr->i_value;
		}
break;
case 239:
#line 3405 "zmac.y"
	{
			yyval.ival = 6;
		}
break;
case 241:
#line 3413 "zmac.y"
	{
			yyval.ival = (yystack.l_mark[-2].itemptr->i_value & 0177400) | 6;
		}
break;
case 242:
#line 3418 "zmac.y"
	{
			disp = 0;
			yyval.ival = (yystack.l_mark[-1].itemptr->i_value & 0177400) | 6;
		}
break;
case 243:
#line 3424 "zmac.y"
	{
			yyval.ival = (yystack.l_mark[-1].itemptr->i_value & 0177400) | 6;
		}
break;
case 244:
#line 3429 "zmac.y"
	{
			expr_number_check(yystack.l_mark[0].exprptr);
			disp = yystack.l_mark[0].exprptr->e_value;
			expr_free(yystack.l_mark[0].exprptr);
			if (disp > 127 || disp < -128)
				err[vflag]++;
		}
break;
case 247:
#line 3443 "zmac.y"
	{ if (yystack.l_mark[0].ival & 1) err[gflag]++; yyval.ival = yystack.l_mark[0].ival << 3; }
break;
case 248:
#line 3445 "zmac.y"
	{ yyval.ival = yystack.l_mark[0].itemptr->i_value; }
break;
case 249:
#line 3449 "zmac.y"
	{
			yyval.ival = yystack.l_mark[0].itemptr->i_value;
		}
break;
case 250:
#line 3454 "zmac.y"
	{
			yyval.ival = yystack.l_mark[0].itemptr->i_value;
		}
break;
case 252:
#line 3461 "zmac.y"
	{ if (yystack.l_mark[0].ival & 1) err[gflag]++; yyval.ival = yystack.l_mark[0].ival << 3; }
break;
case 253:
#line 3463 "zmac.y"
	{ yyval.ival = yystack.l_mark[0].itemptr->i_value; }
break;
case 254:
#line 3467 "zmac.y"
	{
			yyval.ival = yystack.l_mark[0].itemptr->i_value;
		}
break;
case 255:
#line 3472 "zmac.y"
	{
			yyval.ival = yystack.l_mark[0].itemptr->i_value;
		}
break;
case 257:
#line 3480 "zmac.y"
	{
			yyval.ival = yystack.l_mark[0].itemptr->i_value;
		}
break;
case 258:
#line 3486 "zmac.y"
	{
			yyval.ival = yystack.l_mark[0].itemptr->i_value;
		}
break;
case 259:
#line 3491 "zmac.y"
	{
			yyval.ival = yystack.l_mark[0].itemptr->i_value;
		}
break;
case 261:
#line 3499 "zmac.y"
	{
			yyval.ival = yystack.l_mark[0].itemptr->i_value;
		}
break;
case 262:
#line 3505 "zmac.y"
	{
			yyval.ival = yystack.l_mark[0].itemptr->i_value;
		}
break;
case 263:
#line 3510 "zmac.y"
	{	yyval.ival = 030;	}
break;
case 266:
#line 3519 "zmac.y"
	{
			emit(1, E_DATA, expr_num(yystack.l_mark[0].ival));
			emit(1, E_DATA, expr_num(yystack.l_mark[0].ival>>8));
		}
break;
case 267:
#line 3525 "zmac.y"
	{
			cp = yystack.l_mark[0].cval;
			while (*cp != '\0')
				emit(1,E_DATA,expr_num(*cp++));
		}
break;
case 268:
#line 3532 "zmac.y"
	{
			if (is_number(yystack.l_mark[0].exprptr) && (yystack.l_mark[0].exprptr->e_value < -128 || yystack.l_mark[0].exprptr->e_value > 255))
				err[vflag]++;
			emit(1, E_DATA, yystack.l_mark[0].exprptr);
		}
break;
case 271:
#line 3549 "zmac.y"
	{
			if (yystack.l_mark[0].exprptr->e_value < -32768 || yystack.l_mark[0].exprptr->e_value > 65535) {
				err[vflag]++;
			}
			emit(2, E_DATA, yystack.l_mark[0].exprptr);
		}
break;
case 274:
#line 3566 "zmac.y"
	{
			/* Can't check overflow as I only have 32 bit ints.*/
			emit(4, E_DATA, yystack.l_mark[0].exprptr);
		}
break;
case 276:
#line 3578 "zmac.y"
	{
			yyval.exprptr = expr_num(yystack.l_mark[0].ival);
		}
break;
case 279:
#line 3591 "zmac.y"
	{	yyval.exprptr = yystack.l_mark[-1].exprptr;	}
break;
case 280:
#line 3608 "zmac.y"
	{
			yyval.exprptr = expr_var(yystack.l_mark[0].itemptr);
			yystack.l_mark[0].itemptr->i_uses++;
		}
break;
case 281:
#line 3614 "zmac.y"
	{
			yyval.exprptr = expr_num(yystack.l_mark[0].ival);
		}
break;
case 282:
#line 3619 "zmac.y"
	{
			yyval.exprptr = expr_num(yystack.l_mark[0].ival);
		}
break;
case 283:
#line 3624 "zmac.y"
	{
			yyval.exprptr = expr_var(yystack.l_mark[0].itemptr);
		}
break;
case 284:
#line 3629 "zmac.y"
	{
			yyval.exprptr = expr_var(yystack.l_mark[0].itemptr);
		}
break;
case 285:
#line 3634 "zmac.y"
	{
			yyval.exprptr = expr_var(yystack.l_mark[0].itemptr);
		}
break;
case 286:
#line 3639 "zmac.y"
	{
			yyval.exprptr = expr_num(dollarsign + emitptr - emitbuf);
			yyval.exprptr->e_scope = segment;
		}
break;
case 287:
#line 3645 "zmac.y"
	{
			yyval.exprptr = expr_alloc();
			yyval.exprptr->e_token = 'u';
			yyval.exprptr->e_item = yystack.l_mark[0].itemptr;
			yyval.exprptr->e_scope = yystack.l_mark[0].itemptr->i_scope;
			yyval.exprptr->e_value = 0;

			if (!(yystack.l_mark[0].itemptr->i_scope & SCOPE_EXTERNAL)) {
				sprintf(detail, "'%s' %s", yystack.l_mark[0].itemptr->i_string, errname[uflag]);
				/* Would be nice to add to list of undeclared errors*/
				errwarn(uflag, detail);
			}
		}
break;
case 288:
#line 3660 "zmac.y"
	{
			yyval.exprptr = expr_alloc();
			yyval.exprptr->e_token = 'm';
			yyval.exprptr->e_item = yystack.l_mark[0].itemptr;
			yyval.exprptr->e_scope = yystack.l_mark[0].itemptr->i_scope;
			/* Use the current value.  Harmless enough as this*/
			/* will normally error out yet vital to allow*/
			/* "var set var+1" to function.*/
			yyval.exprptr->e_value = yystack.l_mark[0].itemptr->i_value;
		}
break;
case 289:
#line 3671 "zmac.y"
	{ raw = 2; }
break;
case 290:
#line 3672 "zmac.y"
	{
			yyval.exprptr = expr_num(tempbuf[0] ? -1 : 0);
		}
break;
case 291:
#line 3675 "zmac.y"
	{ yyval.exprptr = expr_mk(yystack.l_mark[-2].exprptr, '+', yystack.l_mark[0].exprptr); }
break;
case 292:
#line 3676 "zmac.y"
	{ yyval.exprptr = expr_mk(yystack.l_mark[-2].exprptr, '-', yystack.l_mark[0].exprptr); }
break;
case 293:
#line 3677 "zmac.y"
	{ yyval.exprptr = expr_mk(yystack.l_mark[-2].exprptr, '/', yystack.l_mark[0].exprptr); }
break;
case 294:
#line 3678 "zmac.y"
	{ yyval.exprptr = expr_mk(yystack.l_mark[-2].exprptr, '*', yystack.l_mark[0].exprptr); }
break;
case 295:
#line 3679 "zmac.y"
	{ yyval.exprptr = expr_mk(yystack.l_mark[-2].exprptr, '%', yystack.l_mark[0].exprptr); }
break;
case 296:
#line 3680 "zmac.y"
	{ yyval.exprptr = expr_mk(yystack.l_mark[-2].exprptr, '&', yystack.l_mark[0].exprptr); }
break;
case 297:
#line 3681 "zmac.y"
	{ yyval.exprptr = expr_mk(yystack.l_mark[-2].exprptr, '&', yystack.l_mark[0].exprptr); }
break;
case 298:
#line 3682 "zmac.y"
	{ yyval.exprptr = expr_mk(yystack.l_mark[-2].exprptr, '|', yystack.l_mark[0].exprptr); }
break;
case 299:
#line 3683 "zmac.y"
	{ yyval.exprptr = expr_mk(yystack.l_mark[-2].exprptr, '|', yystack.l_mark[0].exprptr); }
break;
case 300:
#line 3684 "zmac.y"
	{ yyval.exprptr = expr_mk(yystack.l_mark[-2].exprptr, '^', yystack.l_mark[0].exprptr); }
break;
case 301:
#line 3685 "zmac.y"
	{ yyval.exprptr = expr_mk(yystack.l_mark[-2].exprptr, '^', yystack.l_mark[0].exprptr); }
break;
case 302:
#line 3686 "zmac.y"
	{ yyval.exprptr = expr_mk(yystack.l_mark[-2].exprptr, SHL, yystack.l_mark[0].exprptr); }
break;
case 303:
#line 3687 "zmac.y"
	{ yyval.exprptr = expr_mk(yystack.l_mark[-2].exprptr, SHR, yystack.l_mark[0].exprptr); }
break;
case 304:
#line 3688 "zmac.y"
	{ yyval.exprptr = expr_mk(yystack.l_mark[-2].exprptr, '<', yystack.l_mark[0].exprptr); }
break;
case 305:
#line 3689 "zmac.y"
	{ yyval.exprptr = expr_mk(yystack.l_mark[-2].exprptr, '<', yystack.l_mark[0].exprptr); }
break;
case 306:
#line 3690 "zmac.y"
	{ yyval.exprptr = expr_mk(yystack.l_mark[-2].exprptr, '=', yystack.l_mark[0].exprptr); }
break;
case 307:
#line 3691 "zmac.y"
	{ yyval.exprptr = expr_mk(yystack.l_mark[-2].exprptr, '=', yystack.l_mark[0].exprptr); }
break;
case 308:
#line 3692 "zmac.y"
	{ yyval.exprptr = expr_mk(yystack.l_mark[-2].exprptr, '>', yystack.l_mark[0].exprptr); }
break;
case 309:
#line 3693 "zmac.y"
	{ yyval.exprptr = expr_mk(yystack.l_mark[-2].exprptr, '>', yystack.l_mark[0].exprptr); }
break;
case 310:
#line 3694 "zmac.y"
	{ yyval.exprptr = expr_mk(yystack.l_mark[-2].exprptr, LE, yystack.l_mark[0].exprptr); }
break;
case 311:
#line 3695 "zmac.y"
	{ yyval.exprptr = expr_mk(yystack.l_mark[-2].exprptr, NE, yystack.l_mark[0].exprptr); }
break;
case 312:
#line 3696 "zmac.y"
	{ yyval.exprptr = expr_mk(yystack.l_mark[-2].exprptr, GE, yystack.l_mark[0].exprptr); }
break;
case 313:
#line 3697 "zmac.y"
	{ yyval.exprptr = expr_mk(yystack.l_mark[-2].exprptr, ANDAND, yystack.l_mark[0].exprptr); }
break;
case 314:
#line 3698 "zmac.y"
	{ yyval.exprptr = expr_mk(yystack.l_mark[-2].exprptr, OROR, yystack.l_mark[0].exprptr); }
break;
case 315:
#line 3700 "zmac.y"
	{ yyval.exprptr = expr_mk(yystack.l_mark[-2].exprptr, '+', yystack.l_mark[0].exprptr); }
break;
case 316:
#line 3701 "zmac.y"
	{ yyval.exprptr = expr_mk(yystack.l_mark[-2].exprptr, '-', yystack.l_mark[0].exprptr); }
break;
case 317:
#line 3702 "zmac.y"
	{ yyval.exprptr = expr_mk(yystack.l_mark[-2].exprptr, '/', yystack.l_mark[0].exprptr); }
break;
case 318:
#line 3703 "zmac.y"
	{ yyval.exprptr = expr_mk(yystack.l_mark[-2].exprptr, '*', yystack.l_mark[0].exprptr); }
break;
case 319:
#line 3704 "zmac.y"
	{ yyval.exprptr = expr_mk(yystack.l_mark[-2].exprptr, '%', yystack.l_mark[0].exprptr); }
break;
case 320:
#line 3705 "zmac.y"
	{ yyval.exprptr = expr_mk(yystack.l_mark[-2].exprptr, '&', yystack.l_mark[0].exprptr); }
break;
case 321:
#line 3706 "zmac.y"
	{ yyval.exprptr = expr_mk(yystack.l_mark[-2].exprptr, '|', yystack.l_mark[0].exprptr); }
break;
case 322:
#line 3707 "zmac.y"
	{ yyval.exprptr = expr_mk(yystack.l_mark[-2].exprptr, '^', yystack.l_mark[0].exprptr); }
break;
case 323:
#line 3708 "zmac.y"
	{ yyval.exprptr = expr_mk(yystack.l_mark[-2].exprptr, SHL, yystack.l_mark[0].exprptr); }
break;
case 324:
#line 3709 "zmac.y"
	{ yyval.exprptr = expr_mk(yystack.l_mark[-2].exprptr, SHR, yystack.l_mark[0].exprptr); }
break;
case 325:
#line 3710 "zmac.y"
	{ yyval.exprptr = expr_mk(yystack.l_mark[-2].exprptr, '<', yystack.l_mark[0].exprptr); }
break;
case 326:
#line 3711 "zmac.y"
	{ yyval.exprptr = expr_mk(yystack.l_mark[-2].exprptr, '=', yystack.l_mark[0].exprptr); }
break;
case 327:
#line 3712 "zmac.y"
	{ yyval.exprptr = expr_mk(yystack.l_mark[-2].exprptr, '>', yystack.l_mark[0].exprptr); }
break;
case 328:
#line 3713 "zmac.y"
	{ yyval.exprptr = expr_mk(yystack.l_mark[-2].exprptr, LE, yystack.l_mark[0].exprptr); }
break;
case 329:
#line 3714 "zmac.y"
	{ yyval.exprptr = expr_mk(yystack.l_mark[-2].exprptr, NE, yystack.l_mark[0].exprptr); }
break;
case 330:
#line 3715 "zmac.y"
	{ yyval.exprptr = expr_mk(yystack.l_mark[-2].exprptr, GE, yystack.l_mark[0].exprptr); }
break;
case 331:
#line 3718 "zmac.y"
	{
			if (yystack.l_mark[0].exprptr->e_value < 0) {
				yystack.l_mark[0].exprptr->e_value = -yystack.l_mark[0].exprptr->e_value;
				yyval.exprptr = expr_mk(yystack.l_mark[-2].exprptr, SHR, yystack.l_mark[0].exprptr);
			}
			else
				yyval.exprptr = expr_mk(yystack.l_mark[-2].exprptr, SHL, yystack.l_mark[0].exprptr);
		}
break;
case 332:
#line 3728 "zmac.y"
	{
			expr_number_check(yystack.l_mark[-4].exprptr);
			if (yystack.l_mark[-4].exprptr->e_value) {
				yyval.exprptr = yystack.l_mark[-2].exprptr;
				expr_free(yystack.l_mark[0].exprptr);
			}
			else {
				yyval.exprptr = yystack.l_mark[0].exprptr;
				expr_free(yystack.l_mark[-2].exprptr);
			}
			expr_free(yystack.l_mark[-4].exprptr);
		}
break;
case 333:
#line 3742 "zmac.y"
	{	yyval.exprptr = yystack.l_mark[-1].exprptr;	}
break;
case 334:
#line 3745 "zmac.y"
	{	yyval.exprptr = expr_op(yystack.l_mark[0].exprptr, '~', 0, ~yystack.l_mark[0].exprptr->e_value);	}
break;
case 335:
#line 3748 "zmac.y"
	{	yyval.exprptr = expr_op(yystack.l_mark[0].exprptr, '~', 0, ~yystack.l_mark[0].exprptr->e_value);	}
break;
case 336:
#line 3751 "zmac.y"
	{	yyval.exprptr = expr_op(yystack.l_mark[0].exprptr, '!', 0, !yystack.l_mark[0].exprptr->e_value * trueval);	}
break;
case 337:
#line 3754 "zmac.y"
	{	yyval.exprptr = yystack.l_mark[0].exprptr; /* no effect */	}
break;
case 338:
#line 3757 "zmac.y"
	{	yyval.exprptr = yystack.l_mark[0].exprptr; /* no effect */	}
break;
case 339:
#line 3760 "zmac.y"
	{	yyval.exprptr = expr_op(yystack.l_mark[0].exprptr, '-', 0, -yystack.l_mark[0].exprptr->e_value);	}
break;
case 340:
#line 3763 "zmac.y"
	{	yyval.exprptr = expr_op(yystack.l_mark[0].exprptr, '-', 0, -yystack.l_mark[0].exprptr->e_value);	}
break;
case 341:
#line 3766 "zmac.y"
	{
			expr_reloc_check(yystack.l_mark[0].exprptr);
			yyval.exprptr = expr_num(tstatesum[phaseaddr(yystack.l_mark[0].exprptr->e_value)]);
			expr_free(yystack.l_mark[0].exprptr);
		}
break;
case 342:
#line 3773 "zmac.y"
	{
			int low;
			expr_reloc_check(yystack.l_mark[0].exprptr);
			get_tstates(memory + phaseaddr(yystack.l_mark[0].exprptr->e_value), &low, 0, 0);
			yyval.exprptr = expr_num(low);
			expr_free(yystack.l_mark[0].exprptr);
		}
break;
case 343:
#line 3782 "zmac.y"
	{
			int high;
			expr_reloc_check(yystack.l_mark[0].exprptr);
			get_tstates(memory + phaseaddr(yystack.l_mark[0].exprptr->e_value), 0, &high, 0);
			yyval.exprptr = expr_num(high);
			expr_free(yystack.l_mark[0].exprptr);
		}
break;
case 344:
#line 3791 "zmac.y"
	{
			expr_reloc_check(yystack.l_mark[0].exprptr);
			yyval.exprptr = expr_num(ocfsum[phaseaddr(yystack.l_mark[0].exprptr->e_value)]);
			expr_free(yystack.l_mark[0].exprptr);
		}
break;
case 345:
#line 3798 "zmac.y"
	{
			yyval.exprptr = expr_op(yystack.l_mark[0].exprptr, yystack.l_mark[-1].ival, 0, yystack.l_mark[0].exprptr->e_value & 0xff);
		}
break;
case 346:
#line 3803 "zmac.y"
	{
			yyval.exprptr = expr_op(yystack.l_mark[0].exprptr, yystack.l_mark[-1].ival, 0, yystack.l_mark[0].exprptr->e_value & 0xff);
		}
break;
case 347:
#line 3808 "zmac.y"
	{
			yyval.exprptr = expr_op(yystack.l_mark[0].exprptr, yystack.l_mark[-1].ival, 0, (yystack.l_mark[0].exprptr->e_value >> 8) & 0xff);
		}
break;
case 348:
#line 3813 "zmac.y"
	{
			yyval.exprptr = expr_op(yystack.l_mark[0].exprptr, yystack.l_mark[-1].ival, 0, (yystack.l_mark[0].exprptr->e_value >> 8) & 0xff);
		}
break;
case 355:
#line 3834 "zmac.y"
	{ int i;
		if (expptr >= MAXEXP)
			error("Macro expansion level too deep");
		est2 = (union exprec *) malloc((PARMMAX + PAREXT) * sizeof *est2);
		expstack[expptr] = est2;
		for (i=0; i<PARMMAX; i++)
			est2[i].param = 0;
		arg_start();
	}
break;
case 356:
#line 3847 "zmac.y"
	{	arg_start();	}
break;
case 357:
#line 3851 "zmac.y"
	{	arg_reset();	}
break;
case 358:
#line 3855 "zmac.y"
	{	if (mras) mras_undecl_ok = 1; }
break;
case 359:
#line 3859 "zmac.y"
	{	if (mras) mras_undecl_ok = 0; }
break;
#line 11193 "y.tab.c"
    }
    yystack.s_mark -= yym;
    yystate = *yystack.s_mark;
    yystack.l_mark -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yystack.s_mark = YYFINAL;
        *++yystack.l_mark = yyval;
        if (yychar < 0)
        {
            if ((yychar = YYLEX) < 0) yychar = YYEOF;
#if YYDEBUG
            if (yydebug)
            {
                yys = yyname[YYTRANSLATE(yychar)];
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == YYEOF) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yystack.s_mark, yystate);
#endif
    if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM)
    {
        goto yyoverflow;
    }
    *++yystack.s_mark = (YYINT) yystate;
    *++yystack.l_mark = yyval;
    goto yyloop;

yyoverflow:
    YYERROR_CALL("yacc stack overflow");

yyabort:
    yyfreestack(&yystack);
    return (1);

yyaccept:
    yyfreestack(&yystack);
    return (0);
}
