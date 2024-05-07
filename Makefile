# See LICENSE file for copyright and license details.
.POSIX:
.SUFFIXES:

include config.mak

LIBUTIL_DIR = lib/libutil
HDR         = util.h
LIBUTIL_SRC =\
             $(LIBUTIL_DIR)/util.c

SCCS_SRC_DIR = sccs
SCCS_SRC =\
          $(SCCS_SRC_DIR)/sccs.c\
          $(SCCS_SRC_DIR)/what.c
SCCS_BIN = $(SCCS_SRC_DIR)/sccs

all: sccs

sccs: $(SCCS_BIN)

$(SCCS_BIN): $(SCCS_SRC) $(LIBUTIL_SRC)
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ $(SCCS_SRC) $(LIBUTIL_SRC) $(LDFLAGS)

install:
	@mkdir -p $(BINDIR)
	cp -f $(SCCS_BIN) $(BINDIR)

uninstall:
	@printf "Removing $(SCCS_BIN)\n"
	rm -f $(BINDIR)/$(SCCS_BIN)

clean:
	rm -f $(SCCS_BIN)

.PHONY: all sccs lib clean
