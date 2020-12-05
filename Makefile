#
# Makefile.c++
#
# Instructions:
#
# 1. Edit Makefile using vi or emacs:
#    a. rename target, if desired
#    b. add list of source files at SRCS = ...
# 2. % touch Makefile.dep
# 3. % make depend
# 4. % make
#

TARGET = borne
CC = gcc
CFLAGS = -Wall -O -g 

#Version materielle
INCLDIRS = -I .
LIBDIRS = 

#dependance librairie libsmartcard_borne (voir git)
LIBS64 = -lsmartcard_borne_x64

#on fait un peu de menage
SRC_DIR := sources
OBJ_DIR := objets
BIN_DIR := bins 


SRCS := $(wildcard $(SRC_DIR)/*.c)

OBJS := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
#SRCS = borne.c lecteurcarte.c  baseclient.c voyants.c boutons.c timer.c prise.c generateur.c log.c
#OBJS = ${SRCS:.c=.o} 

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(INCLDIRS) -o $@ $(OBJS) $(LIBS64)

$(OBJS):
	$(CC) $(CFLAGS) $(INCLDIRS) -c $*.c

depend:
	$(CC) -MM $(SRCS) $(INCLDIRS) > Makefile.dep

clean:
	rm -f $(OBJS) core

veryclean: clean
	rm -f $(TARGET) a.out *.*~

include Makefile.dep

