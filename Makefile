PROGRAM	= lda
CC	= gcc
CFLAGS	= -O3
SRCS	= lda.c learn.c likelihood.c writer.c feature.c imatrix.c dmatrix.c util.c
OBJS	= $(SRCS:.c=.o)
HEADERS	= $(SRCS:.c=.h)
LDFLAGS	= -lm
VERSION	= 0.1
PKGNAME	= ldacgs-$(VERSION)
DISTDIR	= ../dist
DISTFILES	= $(SRCS) $(HEADERS) Makefile

all: depend $(PROGRAM)

$(PROGRAM): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LDFLAGS)
.c.o:
	$(CC) $(CFLAGS) -c $<

depend:
	@$(CC) -MM $(SRCS) > .depend
clean:
	@rm -f .depend $(OBJS)
pkg:
	@[ -d $(PKGNAME) ] || mkdir $(PKGNAME)
	@cp -p $(DISTFILES) $(PKGNAME)
	@tar czvf $(DISTDIR)/$(PKGNAME).tar.gz $(PKGNAME)
	@rm -r $(PKGNAME)

-include .depend
