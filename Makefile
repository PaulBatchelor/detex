#	Makefile for detex and delatex
#
#	Daniel Trinkle
#	Computer Science Department
#	Purdue University
#
# Detex is a program to remove TeX and LaTeX constructs from text source.

# Installation directory
#
DESTDIR	= /usr/local/bin

# Specify you favorite compiler
#
#CC	= gcc

# Compile time flags, just uncomment the necessary lines
# Some say GNU make does not correctly handle += -- you may have to use :=
#
DEFS	=
#
# Add -traditional for GNU cc on ISC 386/ix system and possibly others
# (reported by pinard@iro.umontreal.ca)
#
# DEFS	+= ${DEFS} -traditional
#
# Add -DHAVE_STRING_H for the SysV string manipulation routines
#
#DEFS	+= ${DEFS} -DHAVE_STRING_H
#
# Add -DMAXPATHLEN=<length> if it is not defined in /usr/include/sys/param.h
#
#DEFS	+= ${DEFS} -DMAXPATHLEN=1024
#
# Add -DNO_MALLOC_DECL if your system does not like the malloc() declaration
# in detex.l (reported by pinard@iro.umontreal.ca)
#
DEFS	+= -DNO_MALLOC_DECL
#
CFLAGS	= -O ${DEFS}

# Use your favorite lexical scanner
#
LEX	= lex
#LEX	= flex

#LFLAGS	= -8 -C

LPR	= lpr -p

# Program names
#
PROGS	= detex

# Header files
#
HDR	= detex.h

# Sources
#
SRC	= detex.l

# Objects for various programs
#
D_OBJ	= detex.o

all:	${PROGS}

detex: ${D_OBJ}
	${CC} ${CFLAGS} -o $@ ${D_OBJ} 

detex.c:
	sed -f states.sed detex.l > xxx.l
	${LEX} ${LFLAGS} xxx.l
	rm -f xxx.l
	mv lex.yy.c detex.c

lexout.c: detex.c
	mv detex.c lexout.c

man-page:
	troff -man detex.1l

# If you want detex available as delatex, uncomment the last two lines of
# this target
install: detex
	rm -f ${DESTDIR}/detex
	install -c -m 775 -o binary -g staff -s detex ${DESTDIR}
#	rm -f ${DESTDIR}/delatex
#	ln ${DESTDIR}/detex ${DESTDIR}/delatex

clean:
	-rm -f a.out core *.s *.o ERRS errs .,* .emacs_[0-9]*
	-rm -f ${PROGS} xxx.l lex.yy.c

print:	${HDR} ${SRC}
	${LPR} Makefile ${HDR} ${SRC}

# Dependencies
#
detex.c: detex.h
detex.c: detex.l
