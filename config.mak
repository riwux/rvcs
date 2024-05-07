# See LICENSE file for copyright and license details.
PREFIX = /usr/local
BINDIR = $(PREFIX)/bin
MANDIR = $(PREFIX)/share/man/man1

CC       = cc
CPPFLAGS = -Iinclude
CFLAGS   = -std=c99 -pedantic -Wall -Wextra
LDFLAGS  = -s
