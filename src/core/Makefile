# Delete the default suffixes, since they insist on adding circular
# dependencies where I don't want them.
.SUFFIXES:

SRC_GEN := parser.leg.c
SRC := $(filter-out $(SRC_GEN),$(wildcard *.c))
OBJ := $(SRC:.c=.o)
DEPS := $(OBJ:.o=.d)
OUTPUT := malachite

CFLAGS := -Wall -Wextra -pedantic -ansi
LDFLAGS :=

# ----------------------------------------------------------------------

.PHONY: all rebuild
all: $(OUTPUT)

rebuild: clean all

# Our final output
$(OUTPUT): $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $(OBJ)

# ----------------------------------------------------------------------

# Pattern rule for generating dependencies
%.d: %.c
	./depend.sh `dirname $<` $(CC) $(CFLAGS) $< > $@

# Pattern rule for peg/leg
%.leg.c: %.leg
	leg -o $@ $<

# Pattern rule for regular compilation
%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

-include $(DEPS)

# ----------------------------------------------------------------------

.PHONY: clean
clean:
	$(RM) $(DEPS) $(OBJ) $(SRC_GEN) $(OUTPUT)
