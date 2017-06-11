#include <stdio.h>
# define U(x) x
# define NLSTATE yyprevious=YYNEWLINE
# define BEGIN yybgin = yysvec + 1 +
# define INITIAL 0
# define YYLERR yysvec
# define YYSTATE (yyestate-yysvec-1)
# define YYOPTIM 1
# define YYLMAX BUFSIZ
#ifndef __cplusplus
# define output(c) (void)putc(c,yyout)
#else
# define lex_output(c) (void)putc(c,yyout)
#endif

#if defined(__cplusplus) || defined(__STDC__)

#if defined(__cplusplus) && defined(__EXTERN_C__)
extern "C" {
#endif
	int yyback(int *, int);
	int yyinput(void);
	int yylook(void);
	void yyoutput(int);
	int yyracc(int);
	int yyreject(void);
	void yyunput(int);
	int yylex(void);
#ifdef YYLEX_E
	void yywoutput(wchar_t);
	wchar_t yywinput(void);
#endif
#ifndef yyless
	int yyless(int);
#endif
#ifndef yywrap
	int yywrap(void);
#endif
#ifdef LEXDEBUG
	void allprint(char);
	void sprint(char *);
#endif
#if defined(__cplusplus) && defined(__EXTERN_C__)
}
#endif

#ifdef __cplusplus
extern "C" {
#endif
	void exit(int);
#ifdef __cplusplus
}
#endif

#endif
# define unput(c) {yytchar= (c);if(yytchar=='\n')yylineno--;*yysptr++=yytchar;}
# define yymore() (yymorfg=1)
#ifndef __cplusplus
# define input() (((yytchar=yysptr>yysbuf?U(*--yysptr):getc(yyin))==10?(yylineno++,yytchar):yytchar)==EOF?0:yytchar)
#else
# define lex_input() (((yytchar=yysptr>yysbuf?U(*--yysptr):getc(yyin))==10?(yylineno++,yytchar):yytchar)==EOF?0:yytchar)
#endif
#define ECHO fprintf(yyout, "%s",yytext)
# define REJECT { nstr = yyreject(); goto yyfussy;}
int yyleng;
char yytext[YYLMAX];
int yymorfg;
extern char *yysptr, yysbuf[];
int yytchar;
FILE *yyin = {stdin}, *yyout = {stdout};
extern int yylineno;
struct yysvf { 
	struct yywork *yystoff;
	struct yysvf *yyother;
	int *yystops;};
struct yysvf *yyestate;
extern struct yysvf yysvec[], *yybgin;
#ifndef lint
static char	rcsid[] = "$Header: /p/src/local/bin/detex/RCS/detex.l,v 2.19 1997/09/10 18:12:37 trinkle Exp $";
#endif


# line 7 "xxx.l"
/*
 * detex [-e environment-list] [-c] [-l] [-n] [-s] [-t] [-w] [file[.tex]]
 *
 *	This program is used to remove TeX or LaTeX constructs from a text
 *	file.
 *
 * Written by:
 *	Daniel Trinkle
 *	Department of Computer Science
 *	Purdue University
 *
 */

#include "detex.h"
#ifdef HAVE_STRING_H
#include <string.h>
#define	index	strchr
#define	rindex	strrchr
#else
#include <strings.h>
#endif
#ifndef MAXPATHLEN
#include <sys/param.h>
#endif
#ifdef OS2
#include <stdlib.h>
#endif

#define	LaBEGIN		if (fLatex) BEGIN
#define	CITEBEGIN	if (fLatex && !fCite) BEGIN
#define	IGNORE		if (fSpace && !fWord) putchar(' ')
#define	SPACE		if (!fWord) putchar(' ')
#define	NEWLINE		if (!fWord) putchar('\n')

char	*SafeMalloc();
#ifndef NO_MALLOC_DECL
char	*malloc();
#endif
#ifdef OS2
void	yyless(int);
#endif

char	*rgsbEnvIgnore[MAXENVS];	/* list of environments ignored */
char	*rgsbIncList[MAXINCLIST];	/* list of includeonly files */
char	*rgsbInputPaths[MAXINPUTPATHS];	/* list of input paths in order */
char	sbCurrentEnv[CCHMAXENV];	/* current environment being ignored */
char	*sbProgName;			/* name we were invoked with */
FILE	*rgfp[NOFILE+1];		/* stack of input/include files */
int	cfp = 0;			/* count of files in stack */
int	cOpenBrace = 0;			/* count of `{' in <SG> */
int	csbEnvIgnore;			/* count of environments ignored */
int	csbIncList = 0;			/* count of includeonly files */
int	csbInputPaths;			/* count of input paths */
int	fLatex = 0;			/* flag to indicated delatex */
int	fWord = 0;			/* flag for -w option */
int	fFollow = 1;			/* flag to follow input/include */
int	fCite = 0;			/* flag to echo \cite and \ref args */
int	fSpace = 0;			/* flag to replace \cs with space */
int	fForcetex = 0;			/* flag to inhibit latex mode */
# define SJ 2
# define SK 4
# define SL 6
# define SM 8
# define SN 10
# define SO 12
# define SP 14
# define SA 16
# define SB 18
# define SC 20
# define SD 22
# define SE 24
# define SF 26
# define SH 28
# define SG 30
# define SI 32
# define YYNEWLINE 10
yylex(){
int nstr; extern int yyprevious;
#ifdef __cplusplus
/* to avoid CC and lint complaining yyfussy not being used ...*/
static int __lex_hack = 0;
if (__lex_hack) goto yyfussy;
#endif
while((nstr = yylook()) >= 0)
yyfussy: switch(nstr){
case 0:
if(yywrap()) return(0); break;
case 1:

# line 75 "xxx.l"
	/* ignore comments */	;
break;
case 2:

# line 77 "xxx.l"
{fLatex = !fForcetex; IGNORE;}
break;
case 3:

# line 79 "xxx.l"
    /* environment start */	{LaBEGIN SA; IGNORE;}
break;
case 4:

# line 81 "xxx.l"
	{   if (BeginEnv("verbatim"))
							BEGIN SD;
						    else
							BEGIN SI;
						    IGNORE;
						}
break;
case 5:

# line 88 "xxx.l"
/* verbatim mode */	{BEGIN SO; IGNORE;}
break;
case 6:

# line 89 "xxx.l"
				ECHO;
break;
case 7:

# line 91 "xxx.l"
				{   if (BeginEnv(yytext))
							BEGIN SD;
						    else
							BEGIN SH;
						    IGNORE;
						}
break;
case 8:

# line 97 "xxx.l"
				NEWLINE;
break;
case 9:

# line 98 "xxx.l"
				;
break;
case 10:

# line 100 "xxx.l"
 /* absorb some environments */	{LaBEGIN SC; IGNORE;}
break;
case 11:

# line 101 "xxx.l"
				NEWLINE;
break;
case 12:

# line 102 "xxx.l"
				;
break;
case 13:

# line 104 "xxx.l"
	 /* end environment */	{   if (EndEnv(yytext))
							BEGIN SO;
						    IGNORE;
						}
break;
case 14:

# line 108 "xxx.l"
				{BEGIN SD; IGNORE;}
break;
case 15:

# line 109 "xxx.l"
				NEWLINE;
break;
case 16:

# line 110 "xxx.l"
				;
break;
case 17:

# line 112 "xxx.l"
    /* ignore args  */	{LaBEGIN SG; IGNORE;}
break;
case 18:

# line 113 "xxx.l"
   /* of these \cs */	{LaBEGIN SH; IGNORE;}
break;
case 19:

# line 114 "xxx.l"
			{LaBEGIN SH; IGNORE;}
break;
case 20:

# line 115 "xxx.l"
			{CITEBEGIN SG; IGNORE;}
break;
case 21:

# line 116 "xxx.l"
		{LaBEGIN SH; IGNORE;}
break;
case 22:

# line 117 "xxx.l"
				{LaBEGIN SH; IGNORE;}
break;
case 23:

# line 118 "xxx.l"
			{SPACE;}
break;
case 24:

# line 119 "xxx.l"
			{LaBEGIN SG; SPACE;}
break;
case 25:

# line 120 "xxx.l"
			{LaBEGIN SH; IGNORE;}
break;
case 26:

# line 121 "xxx.l"
			{CITEBEGIN SH; IGNORE;}
break;
case 27:

# line 122 "xxx.l"
			{LaBEGIN SH; IGNORE;}
break;
case 28:

# line 123 "xxx.l"
				{CITEBEGIN SH; IGNORE;}
break;
case 29:

# line 124 "xxx.l"
			{LaBEGIN SH; IGNORE;}
break;
case 30:

# line 125 "xxx.l"
/* ignore \verb<ch>...<ch> */	{   if (fLatex) {
						 	char verbchar, c;
						 	verbchar = input();
						 	while ((c = input()) != verbchar)
							    if (c == '\n')
								NEWLINE;
						    }
						    IGNORE;
						}
break;
case 31:

# line 134 "xxx.l"
				BEGIN SO;
break;
case 32:

# line 135 "xxx.l"
				NEWLINE;
break;
case 33:

# line 136 "xxx.l"
				;
break;
case 34:

# line 137 "xxx.l"
				{   cOpenBrace++; }
break;
case 35:

# line 138 "xxx.l"
				{   cOpenBrace--;
						    if (cOpenBrace == 0)
							BEGIN SO;
						}
break;
case 36:

# line 142 "xxx.l"
				NEWLINE;
break;
case 37:

# line 143 "xxx.l"
				;
break;
case 38:

# line 145 "xxx.l"
	/* ignore def begin */	{BEGIN SJ; IGNORE;}
break;
case 39:

# line 146 "xxx.l"
				BEGIN SO;
break;
case 40:

# line 147 "xxx.l"
				NEWLINE;
break;
case 41:

# line 148 "xxx.l"
				;
break;
case 42:

# line 150 "xxx.l"
	/* formula mode */	{LaBEGIN SE; IGNORE;}
break;
case 43:

# line 151 "xxx.l"
			BEGIN SO;
break;
case 44:

# line 152 "xxx.l"
				NEWLINE;
break;
case 45:

# line 153 "xxx.l"
				;
break;
case 46:

# line 155 "xxx.l"
	/* display mode */	{LaBEGIN SB; IGNORE;}
break;
case 47:

# line 156 "xxx.l"
			BEGIN SO;
break;
case 48:

# line 157 "xxx.l"
				NEWLINE;
break;
case 49:

# line 158 "xxx.l"
				;
break;
case 50:

# line 160 "xxx.l"
	/* display mode */	{BEGIN SK; IGNORE;}
break;
case 51:

# line 161 "xxx.l"
				BEGIN SO;
break;
case 52:

# line 162 "xxx.l"
				NEWLINE;
break;
case 53:

# line 163 "xxx.l"
				;
break;
case 54:

# line 165 "xxx.l"
	/* math mode */		{BEGIN SN; IGNORE;}
break;
case 55:

# line 166 "xxx.l"
				BEGIN SO;
break;
case 56:

# line 167 "xxx.l"
				NEWLINE;
break;
case 57:

# line 168 "xxx.l"
				;
break;
case 58:

# line 169 "xxx.l"
					;
break;
case 59:

# line 171 "xxx.l"
/* process files */	{LaBEGIN SF; IGNORE;}
break;
case 60:

# line 172 "xxx.l"
			{   IncludeFile(yytext);
						    BEGIN SO;
						}
break;
case 61:

# line 175 "xxx.l"
				NEWLINE;
break;
case 62:

# line 176 "xxx.l"
				;
break;
case 63:

# line 178 "xxx.l"
			{BEGIN SL; IGNORE;}
break;
case 64:

# line 179 "xxx.l"
		AddInclude(yytext);
break;
case 65:

# line 180 "xxx.l"
			{   if (csbIncList == 0)
							rgsbIncList[csbIncList++] = '\0';
						    BEGIN SO;
						}
break;
case 66:

# line 184 "xxx.l"
			NEWLINE;
break;
case 67:

# line 185 "xxx.l"
				;
break;
case 68:

# line 187 "xxx.l"
			{BEGIN SM; IGNORE;}
break;
case 69:

# line 188 "xxx.l"
			{   InputFile(yytext);
						    BEGIN SO;
						}
break;
case 70:

# line 191 "xxx.l"
				NEWLINE;
break;
case 71:

# line 192 "xxx.l"
				;
break;
case 72:

# line 194 "xxx.l"
/* handle ligatures */	{(void)printf("%.2s", yytext+1);}
break;
case 73:

# line 195 "xxx.l"
	{(void)printf("%.1s", yytext+1);}
break;
case 74:

# line 197 "xxx.l"
/* ignore other \cs */	{BEGIN SP; IGNORE;}
break;
case 75:

# line 198 "xxx.l"
				SPACE;
break;
case 76:

# line 199 "xxx.l"
				IGNORE;
break;
case 77:

# line 200 "xxx.l"
			IGNORE;
break;
case 78:

# line 201 "xxx.l"
	IGNORE;
break;
case 79:

# line 202 "xxx.l"
				{BEGIN SO; NEWLINE;}
break;
case 80:

# line 203 "xxx.l"
			{BEGIN SO; IGNORE;}
break;
case 81:

# line 204 "xxx.l"
				{yyless(0);BEGIN SO;}
break;
case 82:

# line 206 "xxx.l"
/* special characters */	IGNORE;
break;
case 83:

# line 207 "xxx.l"
				IGNORE;
break;
case 84:

# line 208 "xxx.l"
				SPACE;
break;
case 85:

# line 210 "xxx.l"
			{   if (fWord)
							(void)printf("%s\n", yytext);
						    else
							ECHO;
						}
break;
case 86:

# line 215 "xxx.l"
				if (!fWord) ECHO;
break;
case 87:

# line 216 "xxx.l"
				if (!fWord) ECHO;
break;
case -1:
break;
default:
(void)fprintf(yyout,"bad switch yylook %d",nstr);
} return(0); }
/* end of yylex */
/******
** main --
**	Set sbProgName to the base of arg 0.
**	Set the input paths.
**	Check for options
**		-c		echo LaTeX \cite, \ref, and \pageref values
**		-e <env-list>	list of LaTeX environments to ignore
**		-l		force latex mode
**		-n		do not follow \input and \include
**		-s		replace control sequences with space
**		-t		force tex mode
**		-w		word only output
**	Set the list of LaTeX environments to ignore.
**	Process each input file.
**	If no input files are specified on the command line, process stdin.
******/

main(cArgs,rgsbArgs)
int	cArgs;
char	*rgsbArgs[];
{
	char	*pch, *sbEnvList = DEFAULTENV, sbBadOpt[2];
	FILE	*TexOpen();
	int	fSawFile = 0, iArgs = 1;

	/* get base name and decide what we are doing, detex or delatex */
#ifdef OS2
	char drive[_MAX_DRIVE], dir[_MAX_DIR];
	char fname[_MAX_FNAME], ext[_MAX_EXT];
#ifdef __EMX__
	_wildcard(&cArgs, &rgsbArgs);
	_response(&cArgs, &rgsbArgs);
#endif
	_splitpath (rgsbArgs[0], drive, dir, fname, ext);
	sbProgName = strlwr(fname);
#else
	if ((sbProgName = rindex(rgsbArgs[0], '/')) != NULL)
	    sbProgName++;
	else
	    sbProgName = rgsbArgs[0];
#endif
	if (strcmp("delatex",sbProgName) == 0)
	    fLatex = 1;

	/* set rgsbInputPaths for use with TexOpen() */
	SetInputPaths();

	/* process command line options */
	while (iArgs < cArgs && *(pch = rgsbArgs[iArgs]) == CHOPT) {
		while (*++pch)
		    switch (*pch) {
		    case CHCITEOPT:
			fCite = 1;
			break;
		    case CHENVOPT:
			sbEnvList = rgsbArgs[++iArgs];
			break;
		    case CHLATEXOPT:
			fLatex = 1;
			break;
		    case CHNOFOLLOWOPT:
			fFollow = 0;
			break;
		    case CHSPACEOPT:
			fSpace = 1;
			break;
		    case CHTEXOPT:
			fForcetex = 1;
			break;
		    case CHWORDOPT:
			fWord = 1;
			break;
		    default:
#ifdef OS2
			OS2UsageExit();
#else
			sbBadOpt[0] = *pch;
			sbBadOpt[1] = '\0';
			Warning("unknown option ignored -", sbBadOpt);
#endif
		    }
		iArgs++;
	}
	SetEnvIgnore(sbEnvList);

	/* process input files */
	for (; iArgs < cArgs; iArgs++) {
	    fSawFile++;
	    if ((yyin = TexOpen(rgsbArgs[iArgs])) == NULL) {
		Warning("can't open file", rgsbArgs[iArgs]);
		continue;;
	    }
	    BEGIN SO;
	    (void)yylex();
	}

	/* if there were no input files, assume stdin */
	if (!fSawFile) {
	    yyin = stdin;
#ifdef OS2
	    if (isatty(fileno(stdin)))
		OS2UsageExit();
#endif
	    BEGIN SO;
	    (void)yylex();
	}
#ifndef FLEX_SCANNER
	if (YYSTATE != SO)
	    ErrorExit("input contains an unterminated mode or environment");
#endif
	return(0);
}

#ifdef FLEX_SCANNER
#undef yywrap
#endif

/******
** yywrap -- handles EOF for lex.  Check to see if the stack of open files
**	has anything on it.  If it does, set yyin to the to value.  If not
**	return the termination signal for lex.
******/

yywrap()
{
	(void)fclose(yyin);
	if (cfp > 0) {
	    yyin = rgfp[--cfp];
	    return(0);
	}
	return(1);
}

#ifdef OS2

/******
** yyless -- return characters to the input stream.  Some systems don't have
**	a yyless routine
******/

void yyless(n)
int n;
{
	int 	i = strlen(yytext);

	while (i > n) unput(yytext[--i]);
	yytext[yyleng = n] = '\0';
}
#endif

/******
** SetEnvIgnore -- sets rgsbEnvIgnore to the values indicated by the
**	sbEnvList.
******/

SetEnvIgnore(sbEnvList)
char	*sbEnvList;
{
	char *sb;

	sb = SafeMalloc(strlen(sbEnvList) + 1, "malloc for SetEnvIgnore failed");
	(void) strcpy(sb, sbEnvList);
	csbEnvIgnore = SeparateList(sb, rgsbEnvIgnore, CHENVSEP, MAXENVS);
	if (csbEnvIgnore == ERROR)
	    ErrorExit("The environtment list contains too many environments");
}

/******
** BeginEnv -- checks to see if sbEnv is in the list rgsbEnvIgnore.  If it
**	is, sbCurrentEnv is set to sbEnv.
******/

BeginEnv(sbEnv)
char	*sbEnv;
{
	int	i;

	if (!fLatex) return(0);
	for (i = 0; i < csbEnvIgnore; i++)
	    if (strcmp(sbEnv, rgsbEnvIgnore[i]) == 0) {
		(void)strcpy(sbCurrentEnv, sbEnv);
		return(1);
	    }
	return(0);
}

/******
** EndEnv -- checks to see if sbEnv is the current environment being ignored.
******/

EndEnv(sbEnv)
char	*sbEnv;
{
	if (!fLatex) return(0);
	if (strcmp(sbEnv, sbCurrentEnv) == 0)
	    return(1);
	return(0);
}

/******
** InputFile -- push the current yyin and open sbFile.  If the open fails,
**	the sbFile is ignored.
******/

InputFile(sbFile)
char	*sbFile;
{
	FILE	*TexOpen();

	if (!fFollow)
	    return;
	rgfp[cfp++] = yyin;
	if ((yyin = TexOpen(sbFile)) == NULL) {
	    Warning("can't open \\input file", sbFile);
	    yyin = rgfp[--cfp];
	}
}

/******
** IncludeFile -- if sbFile is not in the rgsbIncList, push current yyin
**	and open sbFile.  If the open fails, the sbFile is ignored.
******/

IncludeFile(sbFile)
char	*sbFile;
{
	FILE	*TexOpen();

	if (!fFollow)
	    return;
	if (!InList(sbFile))
	    return;
	rgfp[cfp++] = yyin;
	if ((yyin = TexOpen(sbFile)) == NULL) {
	    Warning("can't open \\include file", sbFile);
	    yyin = rgfp[--cfp];
	}
}

/******
** AddInclude -- adds sbFile to the rgsbIncList and increments csbIncList.
**	If the include list is too long, sbFile is ignored.
******/

AddInclude(sbFile)
char	*sbFile;
{
	if (!fFollow)
	    return;
	if (csbIncList >= MAXINCLIST)
	    Warning("\\includeonly list is too long, ignoring", sbFile);
	rgsbIncList[csbIncList] = SafeMalloc(strlen(sbFile) + 1, "malloc for AddInclude failed");
	(void)strcpy(rgsbIncList[csbIncList++], sbFile);
}

/******
** InList -- checks to see if sbFile is in the rgsbIncList.  If there is
**	no list, all files are assumed to be "in the list".
******/

InList(sbFile)
char	*sbFile;
{
	char	*pch, sbBase[MAXPATHLEN];
	int	i;

	if (csbIncList == 0)	/* no list */
	    return(1);
	(void)strcpy(sbBase, sbFile);
	if ((pch = rindex(sbBase, '.')) != NULL)
	    *pch = '\0';
	i = 0;
	while ((i < csbIncList) && rgsbIncList[i])
	    if (strcmp(rgsbIncList[i++], sbBase) == 0)
	        return(1);
	return(0);
}

/******
** SetInputPaths -- sets rgsbInputPaths to the values indicated by the
**	TEXINPUTS environment variable if set or else DEFAULTINPUTS.  If
**	the user's TEXINPUTS has a leading ':' prepend the DEFAULTINPUTS
**	to the path, if there is a trailing ':' append the DEFAULTINPUTS.
**	This is consistent with the most recent TeX.  However, this
**	routine does not honor the '//' construct (expand subdirs).
******/

SetInputPaths()
{
	char *sb, *sbPaths, *getenv();
	int cchDefaults, cchPaths;

	cchDefaults = strlen(DEFAULTINPUTS);
#ifdef OS2
	if ((sb = getenv("TEXINPUT")) == NULL)
#endif
	    if ((sb = getenv("TEXINPUTS")) == NULL)
		sb = DEFAULTINPUTS;
	cchPaths = strlen(sb);
	if (sb[0] == CHPATHSEP)
	    cchPaths += cchDefaults;
	if (sb[strlen(sb) - 1] == CHPATHSEP)
	    cchPaths += cchDefaults;
	sbPaths = SafeMalloc(cchPaths + 1, "malloc for SetInputPaths failed");
	sbPaths[0] = '\0';
	if (sb[0] == CHPATHSEP)
	    (void)strcat(sbPaths, DEFAULTINPUTS);
	(void)strcat(sbPaths, sb);
	if (sb[strlen(sb) - 1] == CHPATHSEP)
	    (void)strcat(sbPaths, DEFAULTINPUTS);

	csbInputPaths = SeparateList(sbPaths, rgsbInputPaths, CHPATHSEP, MAXINPUTPATHS);
	if (csbInputPaths == ERROR)
#ifdef OS2
	    ErrorExit("TEXINPUT(S) environment variable has too many paths");
#else
	    ErrorExit("TEXINPUTS environment variable has too many paths");
#endif
}

/******
** SeparateList -- takes a chSep separated list sbList, replaces the
**	chSep's with NULLs and sets rgsbList[i] to the beginning of
**	the ith word in sbList.  The number of words is returned.  A
**	ERROR is returned if there are more than csbMax words.
******/

SeparateList(sbList, rgsbList, chSep, csbMax)
char	*sbList, *rgsbList[], chSep;
int	csbMax;
{
	int	csbList = 0;

	while (sbList && *sbList && csbList < csbMax) {
	    rgsbList[csbList++] = sbList;
	    if (sbList = index(sbList, chSep))
		*sbList++ = '\0';
	}
	return(sbList && *sbList ? ERROR : csbList);
}

/******
** TexOpen -- tries to open sbFile in each of the rgsbInputPaths in turn.
**	For each input path the following order is used:
**		file.tex - must be as named, if not there go to the next path
**		file.ext - random extension, try it
**		file     - base name, add .tex and try it
**		file     - try it as is
**	Notice that if file exists in the first path and file.tex exists in
**	one of the other paths, file in the first path is what is opened.
**	If the sbFile begins with a '/', no paths are searched.
******/

FILE *
TexOpen(sbFile)
char	*sbFile;
{
	char	*pch, *sbNew;
	FILE	*fp;
	int	iPath;
	static char	sbFullPath[MAXPATHLEN];

	for (iPath = 0; iPath < csbInputPaths; iPath++) {
#ifdef OS2
	    if (*sbFile == '/' || *sbFile == '\\' || strchr(sbFile, ':')) {	/* absolute path */
#else
	    if (*sbFile == '/') {	/* absolute path */
#endif
		(void)sprintf(sbFullPath, "%s", sbFile);
		iPath = csbInputPaths;	/* only check once */
	    } else
		(void)sprintf(sbFullPath, "%s/%s", rgsbInputPaths[iPath], sbFile);
#ifdef OS2
	    pch = sbFullPath;
	    while (pch = strchr(pch, '\\'))
		*pch = '/';
#endif

	    /* If sbFile ends in .tex then it must be there */
	    if ((pch = rindex(sbFullPath, '.')) != NULL
			&& (strcmp(pch, ".tex") == 0))
		if ((fp = fopen(sbFullPath, "r")) != NULL)
		    return(fp);
		else
		    continue;

	    /* if .<ext> then try to open it.  the '.' represents   */
	    /* the beginning of an extension if it is not the first */
	    /* character and it does not follow a '.' or a '/'      */
	    if (pch != NULL && pch > &(sbFullPath[0])
                    && *(pch - 1) != '.' && *(pch - 1) != '/'
		    && (fp = fopen(sbFullPath, "r")) != NULL)
		return(fp);

	    /* just base name, add .tex to the name */
	    sbNew = SafeMalloc(strlen(sbFullPath) + 5, "malloc for TexOpen failed");
	    (void)strcpy(sbNew, sbFullPath);
	    (void)strcat(sbNew, ".tex");
	    if ((fp = fopen(sbNew, "r")) != NULL)
		return(fp);

	    /* try sbFile regardless */
	    if ((fp = fopen(sbFullPath, "r")) != NULL)
		return(fp);
	}
	return((FILE *)NULL);
}

/******
** SafeMalloc -- wrapper around malloc() to check for failure.
******/

char *
SafeMalloc(cch, sbMessage)
int cch;
char *sbMessage;
{
	char *sb;

	if ((sb = (char *)malloc((unsigned)cch)) == NULL)
	    ErrorExit(sbMessage);
	return(sb);
}

/******
** Warning -- print a warning message preceded by the program name.
******/

Warning(sb1, sb2)
char	*sb1, *sb2;
{
	(void)fprintf(stderr, "%s: warning: %s %s\n", sbProgName, sb1, sb2);
}

/******
** ErrorExit -- print an error message preceded by the program name.
**	Stdout is flushed and detex exits.
******/

ErrorExit(sb1)
char	*sb1;
{
	(void)fflush(stdout);
	(void)fprintf(stderr, "%s: error: %s\n", sbProgName, sb1);
	exit(1);
}
#ifdef OS2

/******
** OS2UsageExit -- print OS/2 usage message and exit.
******/

OS2UsageExit()
{
	(void)printf("\n%s [ -clnstw ] [ -e environment-list ] [ filename[.tex] ... ]\n",
		sbProgName);
	puts("  -c  echo LaTeX \\cite, \\ref, and \\pageref values\n  \
-e  <env-list> list of LaTeX environments to ignore\n  \
-l  force latex mode\n  \
-n  do not follow \\input and \\include\n  \
-s  replace control sequences with space\n  \
-t  force tex mode\n  \
-w  word only output");
	exit(0);
}
#endif
int yyvstop[] = {
0,

80,
0,

80,
0,

80,
0,

80,
0,

80,
0,

80,
0,

80,
0,

80,
0,

80,
0,

80,
0,

80,
0,

80,
0,

80,
0,

80,
0,

80,
0,

80,
0,

80,
0,

80,
0,

80,
0,

80,
0,

80,
0,

80,
0,

80,
0,

80,
0,

80,
0,

80,
0,

80,
0,

80,
0,

80,
0,

80,
0,

80,
0,

80,
0,

80,
0,

80,
0,

41,
0,

40,
0,

39,
41,
0,

53,
0,

52,
0,

53,
0,

64,
67,
0,

67,
0,

66,
0,

65,
67,
0,

69,
71,
0,

71,
0,

70,
0,

58,
0,

56,
0,

55,
58,
0,

58,
0,

87,
0,

87,
0,

54,
87,
0,

1,
87,
0,

86,
87,
0,

87,
0,

82,
87,
0,

82,
87,
0,

84,
87,
0,

81,
0,

80,
81,
0,

79,
0,

78,
81,
0,

81,
0,

81,
0,

80,
81,
0,

9,
0,

9,
0,

8,
0,

7,
9,
0,

9,
0,

49,
0,

48,
0,

49,
0,

16,
0,

15,
0,

13,
16,
0,

14,
16,
0,

12,
0,

11,
0,

12,
0,

45,
0,

44,
0,

45,
0,

60,
62,
0,

62,
0,

61,
0,

33,
0,

32,
0,

31,
33,
0,

37,
0,

36,
0,

34,
37,
0,

35,
37,
0,

6,
0,

6,
0,

51,
0,

64,
0,

69,
0,

57,
0,

83,
0,

50,
0,

1,
0,

86,
0,

85,
0,

76,
0,

75,
76,
0,

42,
76,
0,

74,
76,
0,

74,
76,
0,

74,
76,
0,

74,
76,
0,

46,
76,
0,

74,
76,
0,

74,
76,
0,

74,
76,
0,

74,
76,
0,

74,
76,
0,

74,
76,
0,

74,
76,
0,

74,
76,
0,

74,
76,
0,

74,
76,
0,

74,
76,
0,

74,
76,
0,

74,
76,
0,

80,
0,

80,
0,

78,
0,

77,
0,

7,
0,

47,
0,

13,
0,

43,
0,

60,
0,

85,
0,

74,
0,

74,
0,

73,
0,

73,
0,

74,
0,

74,
0,

74,
0,

74,
0,

74,
0,

74,
0,

74,
0,

74,
0,

74,
0,

74,
0,

74,
0,

74,
0,

74,
0,

72,
0,

72,
0,

74,
0,

74,
0,

74,
0,

38,
74,
0,

74,
0,

22,
74,
0,

74,
0,

74,
0,

74,
0,

74,
0,

74,
0,

74,
0,

28,
74,
0,

74,
0,

74,
0,

10,
0,

74,
0,

74,
0,

74,
0,

74,
0,

20,
74,
0,

74,
0,

74,
0,

74,
0,

74,
0,

74,
0,

74,
0,

74,
0,

74,
0,

30,
74,
0,

3,
74,
0,

74,
0,

74,
0,

74,
0,

74,
0,

74,
0,

74,
0,

24,
74,
0,

68,
74,
0,

25,
74,
0,

74,
0,

74,
0,

74,
0,

74,
0,

74,
0,

74,
0,

74,
0,

74,
0,

74,
0,

74,
0,

74,
0,

74,
0,

17,
74,
0,

74,
0,

74,
0,

74,
0,

74,
0,

59,
74,
0,

26,
74,
0,

74,
0,

74,
0,

74,
0,

19,
74,
0,

74,
0,

23,
74,
0,

74,
0,

74,
0,

74,
0,

74,
0,

74,
0,

74,
0,

27,
74,
0,

74,
0,

4,
0,

74,
0,

74,
0,

74,
0,

29,
74,
0,

74,
0,

74,
0,

63,
74,
0,

18,
74,
0,

74,
0,

21,
74,
0,

5,
0,

2,
0,
0};
# define YYTYPE int
struct yywork { YYTYPE verify, advance; } yycrank[] = {
0,0,	0,0,	3,35,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	5,38,	3,35,	3,36,	
104,0,	0,0,	0,0,	0,0,	
7,41,	5,38,	5,39,	0,0,	
0,0,	0,0,	34,0,	0,0,	
7,42,	7,43,	0,0,	0,0,	
113,147,	113,148,	0,0,	0,0,	
62,129,	0,0,	3,35,	0,0,	
0,0,	6,40,	40,98,	51,101,	
3,35,	5,38,	12,50,	54,103,	
5,40,	3,35,	3,35,	5,38,	
7,41,	3,35,	85,141,	113,147,	
5,38,	5,38,	7,41,	62,129,	
5,38,	14,54,	14,55,	7,42,	
7,41,	0,0,	0,0,	7,41,	
0,0,	3,35,	3,35,	72,135,	
72,135,	122,147,	122,148,	0,0,	
5,38,	5,38,	69,134,	69,134,	
0,0,	3,35,	9,45,	7,41,	
7,41,	112,146,	99,0,	99,0,	
5,38,	112,146,	9,46,	9,47,	
114,147,	114,148,	72,135,	7,41,	
122,147,	3,35,	0,0,	75,138,	
0,0,	69,134,	53,102,	125,158,	
5,38,	150,168,	116,146,	82,140,	
97,143,	99,0,	116,146,	7,41,	
117,149,	118,151,	9,45,	114,147,	
117,150,	119,152,	120,154,	121,155,	
9,45,	99,0,	126,159,	11,48,	
128,161,	9,45,	9,45,	119,153,	
3,37,	9,45,	3,35,	11,48,	
11,49,	16,61,	12,48,	5,38,	
20,73,	5,38,	24,80,	26,83,	
34,96,	67,130,	7,42,	137,162,	
7,44,	9,45,	9,45,	140,163,	
113,148,	14,59,	62,130,	14,60,	
114,146,	143,164,	149,167,	11,48,	
151,169,	9,45,	11,50,	124,147,	
124,148,	11,48,	127,160,	152,170,	
153,171,	154,172,	11,48,	11,48,	
100,0,	100,0,	11,48,	155,173,	
157,177,	9,45,	122,156,	13,52,	
127,146,	158,178,	131,0,	131,0,	
72,137,	159,179,	124,147,	13,52,	
13,52,	15,61,	11,48,	11,48,	
160,180,	122,148,	161,181,	100,0,	
69,135,	15,62,	15,63,	162,182,	
156,174,	156,175,	11,48,	163,183,	
99,0,	131,0,	99,0,	164,184,	
9,46,	167,185,	9,46,	13,53,	
114,148,	156,176,	13,54,	13,55,	
169,189,	13,52,	11,51,	171,190,	
173,191,	15,61,	13,52,	13,52,	
174,192,	175,193,	13,56,	15,64,	
176,194,	177,195,	17,68,	178,196,	
15,61,	15,64,	123,147,	123,148,	
15,65,	168,186,	17,69,	17,70,	
168,187,	180,197,	13,52,	13,57,	
142,0,	142,0,	181,198,	168,188,	
182,199,	11,48,	11,48,	11,48,	
15,65,	15,65,	13,57,	124,146,	
185,201,	123,147,	146,165,	146,166,	
186,202,	187,203,	17,68,	188,204,	
15,65,	190,205,	191,206,	142,0,	
17,68,	192,207,	13,58,	193,208,	
194,209,	17,68,	17,68,	195,210,	
19,73,	17,68,	197,213,	124,148,	
15,66,	146,165,	196,211,	196,212,	
19,73,	19,74,	100,0,	199,214,	
100,0,	202,218,	203,219,	204,220,	
205,221,	17,68,	17,71,	206,222,	
131,0,	207,223,	21,76,	211,224,	
212,225,	13,59,	13,59,	13,59,	
13,60,	17,71,	21,76,	21,77,	
19,73,	147,147,	147,148,	15,67,	
15,61,	15,61,	19,73,	213,226,	
214,227,	215,228,	218,230,	19,73,	
19,73,	17,68,	123,157,	19,73,	
219,231,	220,232,	184,184,	184,184,	
221,233,	222,234,	21,76,	223,235,	
147,147,	224,236,	225,237,	226,238,	
21,76,	227,239,	23,80,	19,73,	
19,73,	21,76,	21,76,	200,200,	
200,200,	21,76,	23,80,	23,81,	
25,83,	184,184,	123,148,	19,73,	
17,72,	228,240,	17,68,	229,241,	
25,83,	25,84,	142,0,	231,242,	
142,0,	21,76,	21,78,	232,243,	
165,165,	165,166,	200,200,	19,75,	
233,244,	234,245,	23,80,	235,246,	
237,247,	21,78,	146,166,	238,248,	
23,80,	239,249,	240,250,	241,251,	
25,83,	23,80,	23,80,	242,252,	
244,253,	23,80,	25,83,	165,165,	
246,254,	21,76,	247,255,	25,83,	
25,83,	201,216,	201,216,	25,83,	
248,256,	250,258,	19,73,	19,73,	
19,73,	23,80,	23,80,	251,259,	
252,260,	217,217,	217,217,	253,261,	
254,262,	256,263,	27,86,	25,83,	
25,83,	23,80,	216,216,	216,216,	
201,216,	258,264,	27,87,	27,88,	
21,76,	259,265,	21,79,	25,83,	
260,266,	147,148,	261,267,	262,268,	
217,217,	23,82,	264,269,	265,270,	
249,249,	249,249,	266,271,	267,272,	
269,273,	216,216,	270,274,	25,85,	
184,200,	272,275,	27,86,	274,277,	
273,273,	273,273,	277,277,	277,277,	
27,86,	0,0,	29,89,	0,0,	
200,215,	27,86,	27,86,	249,249,	
0,0,	27,86,	29,89,	29,90,	
23,80,	23,80,	23,80,	0,0,	
0,0,	0,0,	0,0,	273,273,	
0,0,	277,277,	25,83,	25,83,	
25,83,	27,86,	27,86,	0,0,	
0,0,	0,0,	0,0,	0,0,	
165,166,	0,0,	29,89,	0,0,	
0,0,	27,86,	0,0,	0,0,	
29,89,	0,0,	0,0,	0,0,	
0,0,	29,89,	29,89,	31,92,	
217,229,	29,89,	0,0,	0,0,	
0,0,	27,86,	0,0,	31,92,	
31,93,	0,0,	0,0,	201,217,	
0,0,	0,0,	0,0,	0,0,	
0,0,	29,89,	29,89,	56,105,	
56,105,	56,105,	56,105,	56,105,	
56,105,	56,105,	56,105,	56,105,	
56,105,	29,89,	0,0,	31,92,	
216,217,	0,0,	0,0,	0,0,	
27,87,	31,92,	27,87,	33,96,	
0,0,	0,0,	31,92,	31,92,	
0,0,	29,89,	31,92,	33,96,	
33,0,	41,99,	0,0,	0,0,	
249,257,	0,0,	0,0,	0,0,	
0,0,	41,0,	41,0,	0,0,	
0,0,	0,0,	31,92,	31,92,	
273,276,	0,0,	277,278,	0,0,	
0,0,	0,0,	0,0,	33,96,	
0,0,	0,0,	31,92,	0,0,	
29,89,	33,96,	29,91,	0,0,	
41,0,	41,99,	33,96,	33,96,	
0,0,	0,0,	33,96,	41,99,	
0,0,	0,0,	31,92,	0,0,	
41,0,	41,99,	0,0,	0,0,	
41,99,	0,0,	0,0,	0,0,	
0,0,	45,100,	33,96,	33,96,	
0,0,	0,0,	0,0,	0,0,	
0,0,	45,0,	45,0,	55,104,	
41,99,	41,99,	33,96,	0,0,	
0,0,	0,0,	0,0,	55,104,	
55,0,	31,94,	0,0,	31,95,	
41,99,	0,0,	0,0,	0,0,	
0,0,	0,0,	33,97,	0,0,	
45,0,	45,100,	0,0,	0,0,	
0,0,	0,0,	0,0,	45,100,	
41,99,	0,0,	0,0,	55,104,	
45,100,	45,100,	0,0,	0,0,	
45,100,	55,104,	0,0,	0,0,	
0,0,	0,0,	55,104,	55,104,	
0,0,	0,0,	55,104,	0,0,	
0,0,	33,96,	33,96,	33,96,	
45,100,	45,100,	0,0,	0,0,	
0,0,	0,0,	0,0,	41,0,	
0,0,	41,0,	55,104,	55,104,	
45,100,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	55,104,	0,0,	
0,0,	0,0,	0,0,	0,0,	
45,100,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	55,104,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	57,106,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	45,0,	
0,0,	45,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	55,104,	0,0,	55,104,	
57,107,	57,107,	57,107,	57,107,	
57,107,	57,107,	57,107,	57,107,	
57,107,	57,107,	57,107,	57,107,	
57,107,	57,107,	57,107,	57,107,	
57,107,	57,107,	57,107,	57,107,	
57,107,	57,107,	57,107,	57,107,	
57,107,	57,107,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
57,107,	57,107,	57,107,	57,107,	
57,107,	57,107,	57,107,	57,107,	
57,107,	57,107,	57,107,	57,107,	
57,107,	57,107,	57,107,	57,107,	
57,107,	57,107,	57,107,	57,107,	
57,107,	57,107,	57,107,	57,107,	
57,107,	57,107,	58,108,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	58,108,	58,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	58,109,	58,108,	0,0,	
0,0,	0,0,	0,0,	0,0,	
58,108,	58,110,	0,0,	0,0,	
0,0,	58,108,	58,108,	0,0,	
0,0,	58,108,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	58,111,	58,112,	58,111,	
58,111,	58,111,	58,111,	58,111,	
58,111,	58,111,	58,111,	58,111,	
58,111,	58,113,	58,111,	58,111,	
58,114,	58,111,	58,111,	58,111,	
58,111,	58,111,	58,111,	58,111,	
58,111,	58,111,	58,111,	58,111,	
58,115,	58,108,	0,0,	0,0,	
0,0,	0,0,	58,116,	58,117,	
58,118,	58,119,	58,120,	58,121,	
58,111,	58,111,	58,122,	0,0,	
58,111,	58,123,	58,111,	58,111,	
58,124,	58,125,	58,111,	58,126,	
58,127,	58,111,	58,111,	58,128,	
58,111,	58,111,	58,111,	58,111,	
58,108,	64,131,	58,108,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	64,0,	64,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
64,0,	64,131,	0,0,	0,0,	
0,0,	0,0,	0,0,	64,131,	
0,0,	0,0,	0,0,	0,0,	
64,131,	64,131,	0,0,	0,0,	
64,131,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
64,131,	64,131,	0,0,	0,0,	
0,0,	65,131,	0,0,	0,0,	
0,0,	0,0,	0,0,	65,131,	
64,131,	0,0,	65,132,	65,132,	
65,132,	65,132,	65,132,	65,132,	
65,132,	65,132,	65,132,	65,132,	
0,0,	0,0,	0,0,	65,131,	
64,131,	0,0,	65,132,	65,132,	
65,132,	65,132,	65,132,	65,132,	
65,132,	65,132,	65,132,	65,132,	
65,132,	65,132,	65,132,	65,132,	
65,132,	65,132,	65,132,	65,132,	
65,132,	65,132,	65,132,	65,132,	
65,132,	65,132,	65,132,	65,132,	
65,132,	0,0,	0,0,	64,0,	
0,0,	64,131,	65,131,	65,132,	
65,132,	65,132,	65,132,	65,132,	
65,132,	65,132,	65,132,	65,132,	
65,132,	65,132,	65,132,	65,132,	
65,132,	65,132,	65,132,	65,132,	
65,132,	65,132,	65,132,	65,132,	
65,132,	65,132,	65,132,	65,132,	
65,132,	66,133,	66,133,	66,133,	
66,133,	66,133,	66,133,	66,133,	
66,133,	66,133,	66,133,	66,133,	
66,133,	66,133,	66,133,	66,133,	
66,133,	66,133,	66,133,	66,133,	
66,133,	66,133,	66,133,	66,133,	
66,133,	66,133,	66,133,	66,133,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	66,133,	66,133,	
66,133,	66,133,	66,133,	66,133,	
66,133,	66,133,	66,133,	66,133,	
66,133,	66,133,	66,133,	66,133,	
66,133,	66,133,	66,133,	66,133,	
66,133,	66,133,	66,133,	66,133,	
66,133,	66,133,	66,133,	66,133,	
71,136,	71,136,	71,136,	71,136,	
71,136,	71,136,	71,136,	71,136,	
71,136,	71,136,	71,136,	71,136,	
71,136,	71,136,	71,136,	71,136,	
71,136,	71,136,	71,136,	71,136,	
71,136,	71,136,	71,136,	71,136,	
71,136,	71,136,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
71,136,	71,136,	71,136,	71,136,	
71,136,	71,136,	71,136,	71,136,	
71,136,	71,136,	71,136,	71,136,	
71,136,	71,136,	71,136,	71,136,	
71,136,	71,136,	71,136,	71,136,	
71,136,	71,136,	71,136,	71,136,	
71,136,	71,136,	78,139,	78,139,	
78,139,	78,139,	78,139,	78,139,	
78,139,	78,139,	78,139,	78,139,	
78,139,	78,139,	78,139,	78,139,	
78,139,	78,139,	78,139,	78,139,	
78,139,	78,139,	78,139,	78,139,	
78,139,	78,139,	78,139,	78,139,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	78,139,	78,139,	
78,139,	78,139,	78,139,	78,139,	
78,139,	78,139,	78,139,	78,139,	
78,139,	78,139,	78,139,	78,139,	
78,139,	78,139,	78,139,	78,139,	
78,139,	78,139,	78,139,	78,139,	
78,139,	78,139,	78,139,	78,139,	
86,142,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
86,0,	86,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	86,0,	
86,142,	0,0,	0,0,	0,0,	
0,0,	0,0,	86,142,	0,0,	
0,0,	0,0,	0,0,	86,142,	
86,142,	0,0,	0,0,	86,142,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	86,142,	
86,142,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	86,142,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	86,142,	
0,0,	106,144,	106,144,	106,144,	
106,144,	106,144,	106,144,	106,144,	
106,144,	106,144,	106,144,	106,144,	
106,144,	106,144,	106,144,	106,144,	
106,144,	106,144,	106,144,	106,144,	
106,144,	106,144,	106,144,	106,144,	
106,144,	106,144,	106,144,	0,0,	
0,0,	0,0,	86,0,	0,0,	
86,0,	106,144,	106,144,	106,144,	
106,144,	106,144,	106,144,	106,144,	
106,144,	106,144,	106,144,	106,144,	
106,144,	106,144,	106,144,	106,144,	
106,144,	106,144,	106,144,	106,144,	
106,144,	106,144,	106,144,	106,144,	
106,144,	106,144,	106,144,	111,145,	
111,145,	111,145,	111,145,	111,145,	
111,145,	111,145,	111,145,	111,145,	
111,145,	111,145,	111,145,	111,145,	
111,145,	111,145,	111,145,	111,145,	
111,145,	111,145,	111,145,	111,145,	
111,145,	111,145,	111,145,	111,145,	
111,145,	111,145,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
111,145,	111,145,	111,145,	111,145,	
111,145,	111,145,	111,145,	111,145,	
111,145,	111,145,	111,145,	111,145,	
111,145,	111,145,	111,145,	111,145,	
111,145,	111,145,	111,145,	111,145,	
111,145,	111,145,	111,145,	111,145,	
111,145,	111,145,	144,144,	144,144,	
144,144,	144,144,	144,144,	144,144,	
144,144,	144,144,	144,144,	144,144,	
144,144,	144,144,	144,144,	144,144,	
144,144,	144,144,	144,144,	144,144,	
144,144,	144,144,	144,144,	144,144,	
144,144,	144,144,	144,144,	144,144,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	144,144,	144,144,	
144,144,	144,144,	144,144,	144,144,	
144,144,	144,144,	144,144,	144,144,	
144,144,	144,144,	144,144,	144,144,	
144,144,	144,144,	144,144,	144,144,	
144,144,	144,144,	144,144,	144,144,	
144,144,	144,144,	144,144,	144,144,	
0,0};
struct yysvf yysvec[] = {
0,	0,	0,
yycrank+0,	0,		yyvstop+1,
yycrank+0,	0,		yyvstop+3,
yycrank+-1,	0,		yyvstop+5,
yycrank+0,	yysvec+3,	yyvstop+7,
yycrank+-8,	0,		yyvstop+9,
yycrank+-1,	yysvec+5,	yyvstop+11,
yycrank+-15,	0,		yyvstop+13,
yycrank+0,	yysvec+7,	yyvstop+15,
yycrank+-77,	0,		yyvstop+17,
yycrank+0,	yysvec+9,	yyvstop+19,
yycrank+-118,	0,		yyvstop+21,
yycrank+-6,	yysvec+11,	yyvstop+23,
yycrank+-170,	0,		yyvstop+25,
yycrank+-21,	yysvec+13,	yyvstop+27,
yycrank+-180,	0,		yyvstop+29,
yycrank+-5,	yysvec+15,	yyvstop+31,
yycrank+-221,	0,		yyvstop+33,
yycrank+0,	yysvec+17,	yyvstop+35,
yycrank+-267,	0,		yyvstop+37,
yycrank+-8,	yysvec+19,	yyvstop+39,
yycrank+-289,	0,		yyvstop+41,
yycrank+0,	yysvec+21,	yyvstop+43,
yycrank+-329,	0,		yyvstop+45,
yycrank+-10,	yysvec+23,	yyvstop+47,
yycrank+-339,	0,		yyvstop+49,
yycrank+-11,	yysvec+25,	yyvstop+51,
yycrank+-401,	0,		yyvstop+53,
yycrank+0,	yysvec+27,	yyvstop+55,
yycrank+-441,	0,		yyvstop+57,
yycrank+0,	yysvec+29,	yyvstop+59,
yycrank+-486,	0,		yyvstop+61,
yycrank+0,	yysvec+31,	yyvstop+63,
yycrank+-526,	0,		yyvstop+65,
yycrank+-12,	yysvec+33,	yyvstop+67,
yycrank+0,	0,		yyvstop+69,
yycrank+0,	0,		yyvstop+71,
yycrank+0,	0,		yyvstop+73,
yycrank+0,	0,		yyvstop+76,
yycrank+0,	0,		yyvstop+78,
yycrank+2,	0,		yyvstop+80,
yycrank+-536,	0,		yyvstop+82,
yycrank+0,	0,		yyvstop+85,
yycrank+0,	0,		yyvstop+87,
yycrank+0,	0,		yyvstop+89,
yycrank+-588,	0,		yyvstop+92,
yycrank+0,	0,		yyvstop+95,
yycrank+0,	0,		yyvstop+97,
yycrank+0,	0,		yyvstop+99,
yycrank+0,	0,		yyvstop+101,
yycrank+0,	0,		yyvstop+103,
yycrank+3,	0,		yyvstop+106,
yycrank+0,	0,		yyvstop+108,
yycrank+2,	0,		yyvstop+110,
yycrank+7,	0,		yyvstop+112,
yycrank+-598,	0,		yyvstop+115,
yycrank+459,	0,		yyvstop+118,
yycrank+659,	0,		yyvstop+121,
yycrank+-781,	0,		yyvstop+123,
yycrank+0,	0,		yyvstop+126,
yycrank+0,	0,		yyvstop+129,
yycrank+0,	0,		yyvstop+132,
yycrank+23,	0,		yyvstop+134,
yycrank+0,	0,		yyvstop+137,
yycrank+-904,	0,		yyvstop+139,
yycrank+934,	0,		yyvstop+142,
yycrank+993,	0,		yyvstop+144,
yycrank+14,	0,		yyvstop+146,
yycrank+0,	0,		yyvstop+149,
yycrank+65,	0,		yyvstop+151,
yycrank+0,	yysvec+69,	yyvstop+153,
yycrank+1051,	0,		yyvstop+155,
yycrank+58,	0,		yyvstop+158,
yycrank+0,	0,		yyvstop+160,
yycrank+0,	0,		yyvstop+162,
yycrank+2,	0,		yyvstop+164,
yycrank+0,	0,		yyvstop+166,
yycrank+0,	0,		yyvstop+168,
yycrank+1109,	0,		yyvstop+170,
yycrank+0,	0,		yyvstop+173,
yycrank+0,	0,		yyvstop+176,
yycrank+0,	0,		yyvstop+178,
yycrank+2,	0,		yyvstop+180,
yycrank+0,	0,		yyvstop+182,
yycrank+0,	0,		yyvstop+184,
yycrank+9,	0,		yyvstop+186,
yycrank+-1231,	0,		yyvstop+188,
yycrank+0,	0,		yyvstop+191,
yycrank+0,	0,		yyvstop+193,
yycrank+0,	0,		yyvstop+195,
yycrank+0,	0,		yyvstop+197,
yycrank+0,	0,		yyvstop+199,
yycrank+0,	0,		yyvstop+202,
yycrank+0,	0,		yyvstop+204,
yycrank+0,	0,		yyvstop+206,
yycrank+0,	0,		yyvstop+209,
yycrank+0,	0,		yyvstop+212,
yycrank+3,	0,		yyvstop+214,
yycrank+0,	0,		yyvstop+216,
yycrank+-73,	yysvec+41,	yyvstop+218,
yycrank+-155,	yysvec+45,	yyvstop+220,
yycrank+0,	0,		yyvstop+222,
yycrank+0,	0,		yyvstop+224,
yycrank+0,	0,		yyvstop+226,
yycrank+-2,	yysvec+55,	yyvstop+228,
yycrank+0,	yysvec+56,	yyvstop+230,
yycrank+1260,	yysvec+57,	0,	
yycrank+0,	yysvec+57,	yyvstop+232,
yycrank+0,	0,		yyvstop+234,
yycrank+0,	0,		yyvstop+236,
yycrank+0,	0,		yyvstop+239,
yycrank+1319,	0,		yyvstop+242,
yycrank+16,	yysvec+111,	yyvstop+245,
yycrank+19,	yysvec+111,	yyvstop+248,
yycrank+79,	yysvec+111,	yyvstop+251,
yycrank+0,	0,		yyvstop+254,
yycrank+5,	yysvec+111,	yyvstop+257,
yycrank+7,	yysvec+111,	yyvstop+260,
yycrank+4,	yysvec+111,	yyvstop+263,
yycrank+12,	yysvec+111,	yyvstop+266,
yycrank+4,	yysvec+111,	yyvstop+269,
yycrank+4,	yysvec+111,	yyvstop+272,
yycrank+60,	yysvec+111,	yyvstop+275,
yycrank+217,	yysvec+111,	yyvstop+278,
yycrank+146,	yysvec+111,	yyvstop+281,
yycrank+2,	yysvec+111,	yyvstop+284,
yycrank+17,	yysvec+111,	yyvstop+287,
yycrank+57,	yysvec+111,	yyvstop+290,
yycrank+19,	yysvec+111,	yyvstop+293,
yycrank+0,	yysvec+62,	yyvstop+296,
yycrank+0,	yysvec+67,	yyvstop+298,
yycrank+-165,	yysvec+64,	yyvstop+300,
yycrank+0,	yysvec+65,	0,	
yycrank+0,	yysvec+66,	yyvstop+302,
yycrank+0,	yysvec+69,	0,	
yycrank+0,	yysvec+72,	0,	
yycrank+0,	yysvec+71,	yyvstop+304,
yycrank+38,	0,		0,	
yycrank+0,	0,		yyvstop+306,
yycrank+0,	yysvec+78,	yyvstop+308,
yycrank+33,	0,		0,	
yycrank+0,	0,		yyvstop+310,
yycrank+-227,	yysvec+86,	yyvstop+312,
yycrank+39,	0,		0,	
yycrank+1377,	0,		yyvstop+314,
yycrank+0,	yysvec+111,	yyvstop+316,
yycrank+241,	yysvec+111,	yyvstop+318,
yycrank+292,	0,		yyvstop+320,
yycrank+0,	0,		yyvstop+322,
yycrank+47,	yysvec+111,	yyvstop+324,
yycrank+3,	yysvec+111,	yyvstop+326,
yycrank+36,	yysvec+111,	yyvstop+328,
yycrank+57,	yysvec+111,	yyvstop+330,
yycrank+61,	yysvec+111,	yyvstop+332,
yycrank+61,	yysvec+111,	yyvstop+334,
yycrank+56,	yysvec+111,	yyvstop+336,
yycrank+93,	yysvec+111,	yyvstop+338,
yycrank+70,	yysvec+111,	yyvstop+340,
yycrank+70,	yysvec+111,	yyvstop+342,
yycrank+75,	yysvec+111,	yyvstop+344,
yycrank+68,	yysvec+111,	yyvstop+346,
yycrank+72,	yysvec+111,	yyvstop+348,
yycrank+77,	0,		0,	
yycrank+95,	0,		0,	
yycrank+99,	0,		0,	
yycrank+347,	0,		yyvstop+350,
yycrank+0,	0,		yyvstop+352,
yycrank+96,	yysvec+111,	yyvstop+354,
yycrank+124,	yysvec+111,	yyvstop+356,
yycrank+107,	yysvec+111,	yyvstop+358,
yycrank+0,	yysvec+111,	yyvstop+360,
yycrank+94,	yysvec+111,	yyvstop+363,
yycrank+0,	yysvec+111,	yyvstop+365,
yycrank+96,	yysvec+111,	yyvstop+368,
yycrank+108,	yysvec+111,	yyvstop+370,
yycrank+116,	yysvec+111,	yyvstop+372,
yycrank+103,	yysvec+111,	yyvstop+374,
yycrank+120,	yysvec+111,	yyvstop+376,
yycrank+122,	yysvec+111,	yyvstop+378,
yycrank+0,	yysvec+111,	yyvstop+380,
yycrank+134,	yysvec+111,	yyvstop+383,
yycrank+140,	yysvec+111,	yyvstop+385,
yycrank+142,	0,		0,	
yycrank+0,	0,		yyvstop+387,
yycrank+309,	0,		0,	
yycrank+138,	yysvec+111,	yyvstop+389,
yycrank+136,	yysvec+111,	yyvstop+391,
yycrank+148,	yysvec+111,	yyvstop+393,
yycrank+139,	yysvec+111,	yyvstop+395,
yycrank+0,	yysvec+111,	yyvstop+397,
yycrank+148,	yysvec+111,	yyvstop+400,
yycrank+148,	yysvec+111,	yyvstop+402,
yycrank+144,	yysvec+111,	yyvstop+404,
yycrank+143,	yysvec+111,	yyvstop+406,
yycrank+148,	yysvec+111,	yyvstop+408,
yycrank+159,	yysvec+111,	yyvstop+410,
yycrank+160,	yysvec+111,	yyvstop+412,
yycrank+159,	yysvec+111,	yyvstop+414,
yycrank+0,	yysvec+111,	yyvstop+416,
yycrank+182,	0,		0,	
yycrank+326,	0,		0,	
yycrank+376,	yysvec+111,	yyvstop+419,
yycrank+180,	yysvec+111,	yyvstop+422,
yycrank+171,	yysvec+111,	yyvstop+424,
yycrank+162,	yysvec+111,	yyvstop+426,
yycrank+183,	yysvec+111,	yyvstop+428,
yycrank+176,	yysvec+111,	yyvstop+430,
yycrank+189,	yysvec+111,	yyvstop+432,
yycrank+0,	yysvec+111,	yyvstop+434,
yycrank+0,	yysvec+111,	yyvstop+437,
yycrank+0,	yysvec+111,	yyvstop+440,
yycrank+190,	yysvec+111,	yyvstop+443,
yycrank+176,	yysvec+111,	yyvstop+445,
yycrank+190,	yysvec+111,	yyvstop+447,
yycrank+192,	0,		0,	
yycrank+208,	0,		0,	
yycrank+397,	0,		0,	
yycrank+388,	0,		0,	
yycrank+201,	yysvec+111,	yyvstop+449,
yycrank+213,	yysvec+111,	yyvstop+451,
yycrank+209,	yysvec+111,	yyvstop+453,
yycrank+210,	yysvec+111,	yyvstop+455,
yycrank+205,	yysvec+111,	yyvstop+457,
yycrank+222,	yysvec+111,	yyvstop+459,
yycrank+223,	yysvec+111,	yyvstop+461,
yycrank+205,	yysvec+111,	yyvstop+463,
yycrank+217,	yysvec+111,	yyvstop+465,
yycrank+224,	0,		0,	
yycrank+231,	0,		0,	
yycrank+236,	0,		0,	
yycrank+0,	yysvec+111,	yyvstop+467,
yycrank+237,	yysvec+111,	yyvstop+470,
yycrank+254,	yysvec+111,	yyvstop+472,
yycrank+244,	yysvec+111,	yyvstop+474,
yycrank+260,	yysvec+111,	yyvstop+476,
yycrank+252,	yysvec+111,	yyvstop+478,
yycrank+0,	yysvec+111,	yyvstop+481,
yycrank+256,	yysvec+111,	yyvstop+484,
yycrank+251,	yysvec+111,	yyvstop+486,
yycrank+260,	0,		0,	
yycrank+272,	0,		0,	
yycrank+272,	0,		0,	
yycrank+278,	yysvec+111,	yyvstop+488,
yycrank+0,	yysvec+111,	yyvstop+490,
yycrank+261,	yysvec+111,	yyvstop+493,
yycrank+0,	yysvec+111,	yyvstop+495,
yycrank+270,	yysvec+111,	yyvstop+498,
yycrank+281,	yysvec+111,	yyvstop+500,
yycrank+287,	yysvec+111,	yyvstop+502,
yycrank+415,	0,		0,	
yycrank+292,	0,		0,	
yycrank+278,	0,		0,	
yycrank+284,	yysvec+111,	yyvstop+504,
yycrank+283,	yysvec+111,	yyvstop+506,
yycrank+292,	yysvec+111,	yyvstop+508,
yycrank+0,	yysvec+111,	yyvstop+510,
yycrank+287,	yysvec+111,	yyvstop+513,
yycrank+0,	0,		yyvstop+515,
yycrank+293,	0,		0,	
yycrank+304,	0,		0,	
yycrank+312,	yysvec+111,	yyvstop+517,
yycrank+297,	yysvec+111,	yyvstop+519,
yycrank+298,	yysvec+111,	yyvstop+521,
yycrank+0,	yysvec+111,	yyvstop+523,
yycrank+317,	0,		0,	
yycrank+322,	0,		0,	
yycrank+305,	yysvec+111,	yyvstop+526,
yycrank+319,	yysvec+111,	yyvstop+528,
yycrank+0,	yysvec+111,	yyvstop+530,
yycrank+319,	0,		0,	
yycrank+320,	0,		0,	
yycrank+0,	yysvec+111,	yyvstop+533,
yycrank+332,	yysvec+111,	yyvstop+536,
yycrank+427,	0,		0,	
yycrank+319,	0,		0,	
yycrank+0,	yysvec+111,	yyvstop+538,
yycrank+0,	0,		yyvstop+541,
yycrank+429,	0,		0,	
yycrank+0,	0,		yyvstop+543,
0,	0,	0};
struct yywork *yytop = yycrank+1499;
struct yysvf *yybgin = yysvec+1;
char yymatch[] = {
  0,   1,   1,   1,   1,   1,   1,   1, 
  1,   9,  10,   1,   1,   1,   1,   1, 
  1,   1,   1,   1,   1,   1,   1,   1, 
  1,   1,   1,   1,   1,   1,   1,   1, 
  9,  33,   1,   1,   1,   1,   1,  39, 
  1,   1,   1,   1,  44,  45,   1,   1, 
 48,  48,  48,  48,  48,  48,  48,  48, 
 48,  48,   1,   1,   1,  45,   1,  33, 
 64,  65,  65,  65,  65,  65,  65,  65, 
 65,  65,  65,  65,  76,  65,  65,  76, 
 65,  65,  65,  65,  65,  65,  65,  65, 
 65,  65,  65,   1,  92,   1,   1,   1, 
 45,  65,  65,  65,  65,  65,  65,  65, 
 65,  76,  76,  65,  76,  65,  65,  76, 
 65,  65,  65,  65,  65,  65,  65,  65, 
 65,  65,  65, 123,  92, 125,   1,   1, 
  1,   1,   1,   1,   1,   1,   1,   1, 
  1,   1,   1,   1,   1,   1,   1,   1, 
  1,   1,   1,   1,   1,   1,   1,   1, 
  1,   1,   1,   1,   1,   1,   1,   1, 
  1,   1,   1,   1,   1,   1,   1,   1, 
  1,   1,   1,   1,   1,   1,   1,   1, 
  1,   1,   1,   1,   1,   1,   1,   1, 
  1,   1,   1,   1,   1,   1,   1,   1, 
  1,   1,   1,   1,   1,   1,   1,   1, 
  1,   1,   1,   1,   1,   1,   1,   1, 
  1,   1,   1,   1,   1,   1,   1,   1, 
  1,   1,   1,   1,   1,   1,   1,   1, 
  1,   1,   1,   1,   1,   1,   1,   1, 
  1,   1,   1,   1,   1,   1,   1,   1, 
  1,   1,   1,   1,   1,   1,   1,   1, 
  1,   1,   1,   1,   1,   1,   1,   1, 
0};
char yyextra[] = {
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0};
/*	Copyright (c) 1989 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

#pragma ident	"@(#)ncform	6.8	95/02/11 SMI"

int yylineno =1;
# define YYU(x) x
# define NLSTATE yyprevious=YYNEWLINE
struct yysvf *yylstate [YYLMAX], **yylsp, **yyolsp;
char yysbuf[YYLMAX];
char *yysptr = yysbuf;
int *yyfnd;
extern struct yysvf *yyestate;
int yyprevious = YYNEWLINE;
#if defined(__cplusplus) || defined(__STDC__)
int yylook(void)
#else
yylook()
#endif
{
	register struct yysvf *yystate, **lsp;
	register struct yywork *yyt;
	struct yysvf *yyz;
	int yych, yyfirst;
	struct yywork *yyr;
# ifdef LEXDEBUG
	int debug;
# endif
	char *yylastch;
	/* start off machines */
# ifdef LEXDEBUG
	debug = 0;
# endif
	yyfirst=1;
	if (!yymorfg)
		yylastch = yytext;
	else {
		yymorfg=0;
		yylastch = yytext+yyleng;
		}
	for(;;){
		lsp = yylstate;
		yyestate = yystate = yybgin;
		if (yyprevious==YYNEWLINE) yystate++;
		for (;;){
# ifdef LEXDEBUG
			if(debug)fprintf(yyout,"state %d\n",yystate-yysvec-1);
# endif
			yyt = yystate->yystoff;
			if(yyt == yycrank && !yyfirst){  /* may not be any transitions */
				yyz = yystate->yyother;
				if(yyz == 0)break;
				if(yyz->yystoff == yycrank)break;
				}
#ifndef __cplusplus
			*yylastch++ = yych = input();
#else
			*yylastch++ = yych = lex_input();
#endif
			if(yylastch > &yytext[YYLMAX]) {
				fprintf(yyout,"Input string too long, limit %d\n",YYLMAX);
				exit(1);
			}
			yyfirst=0;
		tryagain:
# ifdef LEXDEBUG
			if(debug){
				fprintf(yyout,"char ");
				allprint(yych);
				putchar('\n');
				}
# endif
			yyr = yyt;
			if ( (int)yyt > (int)yycrank){
				yyt = yyr + yych;
				if (yyt <= yytop && yyt->verify+yysvec == yystate){
					if(yyt->advance+yysvec == YYLERR)	/* error transitions */
						{unput(*--yylastch);break;}
					*lsp++ = yystate = yyt->advance+yysvec;
					if(lsp > &yylstate[YYLMAX]) {
						fprintf(yyout,"Input string too long, limit %d\n",YYLMAX);
						exit(1);
					}
					goto contin;
					}
				}
# ifdef YYOPTIM
			else if((int)yyt < (int)yycrank) {		/* r < yycrank */
				yyt = yyr = yycrank+(yycrank-yyt);
# ifdef LEXDEBUG
				if(debug)fprintf(yyout,"compressed state\n");
# endif
				yyt = yyt + yych;
				if(yyt <= yytop && yyt->verify+yysvec == yystate){
					if(yyt->advance+yysvec == YYLERR)	/* error transitions */
						{unput(*--yylastch);break;}
					*lsp++ = yystate = yyt->advance+yysvec;
					if(lsp > &yylstate[YYLMAX]) {
						fprintf(yyout,"Input string too long, limit %d\n",YYLMAX);
						exit(1);
					}
					goto contin;
					}
				yyt = yyr + YYU(yymatch[yych]);
# ifdef LEXDEBUG
				if(debug){
					fprintf(yyout,"try fall back character ");
					allprint(YYU(yymatch[yych]));
					putchar('\n');
					}
# endif
				if(yyt <= yytop && yyt->verify+yysvec == yystate){
					if(yyt->advance+yysvec == YYLERR)	/* error transition */
						{unput(*--yylastch);break;}
					*lsp++ = yystate = yyt->advance+yysvec;
					if(lsp > &yylstate[YYLMAX]) {
						fprintf(yyout,"Input string too long, limit %d\n",YYLMAX);
						exit(1);
					}
					goto contin;
					}
				}
			if ((yystate = yystate->yyother) && (yyt= yystate->yystoff) != yycrank){
# ifdef LEXDEBUG
				if(debug)fprintf(yyout,"fall back to state %d\n",yystate-yysvec-1);
# endif
				goto tryagain;
				}
# endif
			else
				{unput(*--yylastch);break;}
		contin:
# ifdef LEXDEBUG
			if(debug){
				fprintf(yyout,"state %d char ",yystate-yysvec-1);
				allprint(yych);
				putchar('\n');
				}
# endif
			;
			}
# ifdef LEXDEBUG
		if(debug){
			fprintf(yyout,"stopped at %d with ",*(lsp-1)-yysvec-1);
			allprint(yych);
			putchar('\n');
			}
# endif
		while (lsp-- > yylstate){
			*yylastch-- = 0;
			if (*lsp != 0 && (yyfnd= (*lsp)->yystops) && *yyfnd > 0){
				yyolsp = lsp;
				if(yyextra[*yyfnd]){		/* must backup */
					while(yyback((*lsp)->yystops,-*yyfnd) != 1 && lsp > yylstate){
						lsp--;
						unput(*yylastch--);
						}
					}
				yyprevious = YYU(*yylastch);
				yylsp = lsp;
				yyleng = yylastch-yytext+1;
				yytext[yyleng] = 0;
# ifdef LEXDEBUG
				if(debug){
					fprintf(yyout,"\nmatch ");
					sprint(yytext);
					fprintf(yyout," action %d\n",*yyfnd);
					}
# endif
				return(*yyfnd++);
				}
			unput(*yylastch);
			}
		if (yytext[0] == 0  /* && feof(yyin) */)
			{
			yysptr=yysbuf;
			return(0);
			}
#ifndef __cplusplus
		yyprevious = yytext[0] = input();
		if (yyprevious>0)
			output(yyprevious);
#else
		yyprevious = yytext[0] = lex_input();
		if (yyprevious>0)
			lex_output(yyprevious);
#endif
		yylastch=yytext;
# ifdef LEXDEBUG
		if(debug)putchar('\n');
# endif
		}
	}
#if defined(__cplusplus) || defined(__STDC__)
int yyback(int *p, int m)
#else
yyback(p, m)
	int *p;
#endif
{
	if (p==0) return(0);
	while (*p) {
		if (*p++ == m)
			return(1);
	}
	return(0);
}
	/* the following are only used in the lex library */
#if defined(__cplusplus) || defined(__STDC__)
int yyinput(void)
#else
yyinput()
#endif
{
#ifndef __cplusplus
	return(input());
#else
	return(lex_input());
#endif
	}
#if defined(__cplusplus) || defined(__STDC__)
void yyoutput(int c)
#else
yyoutput(c)
  int c; 
#endif
{
#ifndef __cplusplus
	output(c);
#else
	lex_output(c);
#endif
	}
#if defined(__cplusplus) || defined(__STDC__)
void yyunput(int c)
#else
yyunput(c)
   int c; 
#endif
{
	unput(c);
	}
