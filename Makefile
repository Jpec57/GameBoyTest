LCC=lcc
INCLUDE=includes/
SDIR=src
RDIR=res
TILE_DIR=tiles
SRC=main.c 
NAME=main
TILES=*.c
PATH_ROM='/Users/jpec/Library/Application\ Support/OpenEmu/Game\ Library/roms/Game\ Boy'
SCRIPT=reload.sh

all: $(NAME)

$(NAME):
    $(LCC) -o main.gb $(SDIR)/$(SRC)

#$(NAME):
#	$(LCC) -o main.gb $(SDIR)/$(SRC) $(RDIR)/$(TILE_DIR)/$(TILES)

#launch:
#    sh $(SCRIPT)

clean: 
	rm -rf $(NAME)

re: clean all