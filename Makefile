
BINDIR  = bin
OBJDIR  = obj
SRCDIR  = src

CFLAGS   = -Wall -Wextra -ansi -g -pedantic
LDFLAGS  =
DEPFLAGS = -MT $@ -MMD -MP -MF $$TMPFILE
DEPSDIR = deps


SRCS = $(wildcard $(SRCDIR)/*.c)


all: $(BINDIR)/tp4
.PHONY: all


dist: tp4.zip
.PHONY: dist


tp4.zip: Makefile README.md rapport.pdf $(wildcard $(SRCDIR)/*.c) $(wildcard $(SRCDIR)/*.h)
	-rm -f $@
	zip $@ $^


$(BINDIR)/tp4: $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCS))
	$(CC) $(LDFLAGS) -o $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.c
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	set -e; \
	TMPFILE=`mktemp`;\
	$(CC) -c $(DEPFLAGS) $(CFLAGS) -o $@ $<; \
	sed 's,\($*\)\.o[ :]*,\1.o $(DEPSDIR)/\1.d: ,g' < $$TMPFILE > $(DEPSDIR)/$*.d; \
	rm $$TMPFILE


$(shell mkdir -p $(BINDIR) > /dev/null)
$(shell mkdir -p $(OBJDIR) > /dev/null)
$(shell mkdir -p $(SRCDIR) > /dev/null)
$(shell mkdir -p $(DEPSDIR) > /dev/null)

$(DEPSDIR)/%.d: ;
.PRECIOUS: $(DEPSDIR)/%.d


clean:
	-rm -rf $(BINDIR)
	-rm -rf $(OBJDIR)
	-rm -rf $(DEPSDIR)
.PHONY: clean


include $(patsubst $(SRCDIR)/%.c,$(DEPSDIR)/%.d,$(SRCS))

