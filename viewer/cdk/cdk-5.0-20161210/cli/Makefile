# $Id: Makefile.in,v 1.7 2013/07/19 23:55:03 tom Exp $
#
# Makefile for the cli directory.
#
SHELL		= /bin/sh

prefix		= /usr/local
exec_prefix	= ${prefix}

srcdir		= .


CC		= gcc
RM		= rm -f
CTAGS		= ctags
ETAGS		= etags
LINT		= 
LINT_OPTS	= 

LIBS		= -lcdk -lncurses 

LIBTOOL		=  
LIBTOOL_CLEAN	= 
LIBTOOL_LINK	= ${CC}
LINK		= $(LIBTOOL_LINK)

x		= 
o		= .o
LOCAL_LIBDIR	= .

CFLAGS		= -g -O2 
CPPFLAGS	= -DHAVE_CONFIG_H -I../include -I$(srcdir)/../include -I.   -D_DARWIN_C_SOURCE -D_XOPEN_SOURCE_EXTENDED
LDFLAGS		= -L..  

BINS	= \
	cdkalphalist$x \
	cdkcalendar$x \
	cdkdialog$x \
	cdkentry$x \
	cdkfselect$x \
	cdkitemlist$x \
	cdklabel$x \
	cdkmatrix$x \
	cdkmentry$x \
	cdkradio$x \
	cdkscale$x \
	cdkscroll$x \
	cdkselection$x \
	cdkslider$x \
	cdktemplate$x \
	cdkviewer$x

CDKSRC	= \
	cdkalphalist.c \
	cdkcalendar.c \
	cdkdialog.c \
	cdkentry.c \
	cdkfselect.c \
	cdkitemlist.c \
	cdklabel.c \
	cdkmatrix.c \
	cdkmentry.c \
	cdkradio.c \
	cdkscale.c \
	cdkscroll.c \
	cdkselection.c \
	cdkslider.c \
	cdktemplate.c \
	cdkviewer.c

LINKIT	= $(LINK) $(CFLAGS) $(CPPFLAGS) $? -o $@ $(LDFLAGS) $(LIBS)

all : $(BINS)

cdkalphalist$x :	cdkalphalist.c	; $(LINKIT)
cdkcalendar$x :		cdkcalendar.c	; $(LINKIT)
cdkdialog$x :		cdkdialog.c	; $(LINKIT)
cdkentry$x :		cdkentry.c	; $(LINKIT)
cdkfselect$x :		cdkfselect.c	; $(LINKIT)
cdkitemlist$x :		cdkitemlist.c	; $(LINKIT)
cdklabel$x :		cdklabel.c	; $(LINKIT)
cdkmatrix$x :		cdkmatrix.c	; $(LINKIT)
cdkmentry$x :		cdkmentry.c	; $(LINKIT)
cdkradio$x :		cdkradio.c	; $(LINKIT)
cdkscale$x :		cdkscale.c	; $(LINKIT)
cdkscroll$x :		cdkscroll.c	; $(LINKIT)
cdkselection$x :	cdkselection.c	; $(LINKIT)
cdkslider$x :		cdkslider.c	; $(LINKIT)
cdktemplate$x :		cdktemplate.c	; $(LINKIT)
cdkviewer$x :		cdkviewer.c	; $(LINKIT)
#
# Standard clean directives.
#
clean::
	- $(LIBTOOL_CLEAN) $(RM) *.o core $(BINS)

distclean:: clean
	$(RM) Makefile

tags :
	$(CTAGS) *.[ch] */*.[ch]

TAGS :
	$(ETAGS) *.[ch] */*.[ch]

lint: $(CDKSRC)
	$(LINT) $(LINT_OPTS) $(CPPFLAGS) $(CDKSRC)
