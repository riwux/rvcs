# See LICENSE file for copyright and license details.
.POSIX:
.SUFFIXES:

include config.mak

SCCS_SRC_DIR = sccs
LIBUTIL_DIR  = lib/libutil

HDR =\
     util.h
LIBUTIL_SRC =\
             $(LIBUTIL_DIR)/util.c

SCCS_SRC  =\
           $(SCCS_SRC_DIR)/sccs.c\
           $(SCCS_SRC_DIR)/what.c
SCCS_BIN = $(SCCS_SRC_DIR)/sccs

all: $(SCCS_BIN)

$(SCCS_BIN): $(SCCS_SRC) $(LIBUTIL_SRC)
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ $(SCCS_SRC) $(LIBUTIL_SRC) $(LDFLAGS)

clean:
	rm -f $(SCCS_BIN)

.PHONY: all lib clean
