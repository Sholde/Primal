# variable

CC = gcc

OPTI = -Ofast

EXEC = app.exe
ARCHIVE = BOUTON_Nicolas-HADJAB_LYNDA-DEDARALLY_Taariq
TAR = tar.gz

SRCDIR = src
OBJDIR = obj
BINDIR = bin

DEPS = $(wildcard $(SRCDIR)/*.h)
SRC = $(wildcard $(SRCDIR)/*.c)
OBJ = $(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

FLAG = -Wall -g3

GMP = -lgmp

# make

all: config compil

compil: $(OBJ)
	@ $(CC) -o $(BINDIR)/$(EXEC) $(OBJ) $(GMP) $(OPTI)
	@ echo "Linking complete!"

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(DEPS)
	@ $(CC) -c -o $@ $< $(FLAG) $(GMP) $(OPTI)
	@ echo "Compiled "$@" successfully!"

run:
	@ ./$(BINDIR)/$(EXEC)
	

clean:
	@ if [ $(ARCHIVE).$(TAR) ]; then rm -f $(ARCHIVE).$(TAR); echo "Archive removed!"; fi
	@ rm -rf $(OBJDIR)/
	@ echo "Object files removed!"
	@ rm -rf $(BINDIR)/
	@ echo "Executable removed!"
	
package: clean
	@ tar -czvf $(ARCHIVE).$(TAR) *
	@ echo "Archive created!"
	
config:
	@ if [ ! -d "bin/" ]; then mkdir bin; fi
	@ if [ ! -d "obj/" ]; then mkdir obj; fi
