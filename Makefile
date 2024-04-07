# Makefile for tnycalc.

PACKAGE = tnycalc
VERSION = 0.1.1

# Can be coco or ast09.
TARGET = coco

CMOC = cmoc
TAR = tar

ifeq "$(TARGET)" "ast09"
TARGETFLAG = --void-target
EXEEXT = .srec
else
TARGETFLAG = --$(TARGET)
EXEEXT = .bin
endif

FLOATFLAGS = --mc6839
CFLAGS = $(TARGETFLAG) $(FLOATFLAGS) $(DEFINES)
LDFLAGS = $(TARGETFLAG) $(FLOATFLAGS)

EXE = tnycalc-$(TARGET)$(EXEEXT)

COMMON_SRC = floatstack.c slowmath.c
AST09_SRC = tnycalc-ast09.c ast09.c
COCO_SRC = tnycalc-coco.c cocoio.c

SRC = $(COMMON_SRC)
ifeq "$(TARGET)" "ast09"
SRC += $(AST09_SRC)
else
SRC += $(COCO_SRC)
endif

HEADERS = ast09.h cocoio.h errors.h floatstack.h slowmath.h

OBJ = $(SRC:.c=.o)

DISTFILES = README Makefile $(COMMON_SRC) $(AST09_SRC) $(COCO_SRC) $(HEADERS)

all: $(EXE)

$(EXE): $(OBJ)
	$(CMOC) -o $(EXE) $(LDFLAGS) $(OBJ)


%.o: %.c
	$(CMOC) -c $(CFLAGS) -o $@ $<

clean:
	rm -f $(EXE) $(OBJ)

.PHONY: dist
dist:
	$(TAR) -czf $(PACKAGE)-$(VERSION).tar.gz --transform 's,^,$(PACKAGE)-$(VERSION)/,' $(DISTFILES)

# Automatic prerequisite generation.
%.d: %.c
	$(CMOC) --deps-only $(CFLAGS) $<

.PHONY: cleandeps
cleandeps:
	rm -f $(SRC:.c=.d)

include $(SRC:.c=.d)
