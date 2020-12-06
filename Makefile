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


#SRCS = ./sources/lecteurcarte.c ./sources/borne.c ./sources/baseclient.c ./sources/boutons.c ./sources/generateur.c ./sources/log.c ./sources/prise.c ./sources/timer.c ./sources/voyants.c

#ce SRCS est pareil que là haut : on ajoute de manieire immediate ":=" à SCRCS
#shell escape pour passer la commande find de shell
#et on trouve grace à find tout les fichiers dont le nom est '*.c'

SRCS := $(shell find $(SRC_DIR) -name '*.c')		 
OBJS = ${SRCS:$(SRC_DIR)%.c=$(OBJ_DIR)%.o}

move =

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

all :
	@echo "1 - compilation des librairies/objets"
	$(CC) $(CFLAGS) $(INCLDIRS) -c ${SRCS}
	@echo "2 - deplacer les fichiers objets dans le bon repertoire "
	mv -f -i *.o ./objets	
	@echo "3 - Liee les librairies a l'executable"
	$(CC) $(CFLAGS) $(INCLDIRS) -o $(TARGET) $(OBJS) $(LIBS64)

depend:
	@echo "creer les dependance entre les fichiers automatiquement"
	$(CC) -MM $(SRCS) $(INCLDIRS) > Makefile.dep
	
clean:
	rm -f -i $(OBJS)

veryclean: clean
	rm -f -i $(TARGET) a.out *.*~
	
test:
	@echo "$(OBJS)   ---   $(SRCS)"
	
run: clean depend all
	./$(TARGET)

include Makefile.dep




