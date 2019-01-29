export CPMDrive_B = $(PWD)
export CPMDrive_C = $(PWD)/driout
export CPMDefault = B:

RELS = exmpl10.rel exmpl13.rel
HEXS = exmpl11.hex exmpl12.hex exmpl14.hex exmpl15.hex \
	exmpl1.hex exmpl2.hex exmpl3.hex exmpl4.hex \
	exmpl5.hex exmpl6.hex exmpl7.hex exmpl8.hex \
	exmpl9.hex

ZMAC = $(addprefix zout/,$(HEXS) $(RELS))
DRI = $(addprefix driout/,$(HEXS) $(RELS))

zout/%.hex:	%.asm
	-zmac --dri -i -8 -c -s -n $?

zout/%.rel:	%.asm
	-zmac --dri -i -8 -c -s -n --rel $?

driout/%.hex:	%.asm
	-vcpm mac $? '$$SZPCHC'

driout/%.rel:	%.asm
	-vcpm rmac $? '$$SZPCRC'

all:

zmac:	$(ZMAC)

dri:	driout $(DRI)

driout:
	mkdir driout

clean:
	rm -rf zout driout
