SOURCES := $(shell find $(SOURCEDIR) -name '*.dts')
OBJECTS = $(SOURCES:.dts=.dtb)
DTC = dtc

all: $(OBJECTS)

%.dtb: %.dts
	$(DTC) -q -I dts -O dtb $< -o $@

clean:
	-rm -rf $(OBJECTS)

.PHONY: all clean
