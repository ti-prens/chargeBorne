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

# on fait un peu de menage
SRC_DIR =	./sources
OBJ_DIR =	./objets


SRCS = ./sources/lecteurcarte.c ./sources/borne.c ./sources/baseclient.c ./sources/boutons.c ./sources/generateur.c ./sources/log.c ./sources/prise.c ./sources/timer.c ./sources/voyants.c
		 
OBJS = ${SRCS:./sources/%.c=./objets/%.o}



# Version materielle
INCLDIRS	= -I ./sources/
LIBDIRS		= 

# dependance librairie libsmartcard_borne (voir git)
LIBS64	= -lsmartcard_borne_x64

#linker ?
LINKERFLAG	= -lm

TARGET	=	borne
CC		=	gcc
CFLAGS	=	-Wall -O -g 
MAIN	=	sources/borne.c



$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(INCLDIRS) -o $@ $(OBJS) $(LIBS64)

$(OBJS):
	$(CC) $(CFLAGS) $(INCLDIRS) -c ${SRCS}

depend:
	$(CC) -MM $(SRCS) $(INCLDIRS) > Makefile.dep
	
clean:
	rm -f $(OBJS) core

veryclean: clean
	rm -f $(TARGET) a.out *.*~
	
test:
	@echo "$(OBJS)  ---  $(SRCS)   ---   $(SRCS)"
	
run: clean depend
	./$(TARGET)

include Makefile.dep




