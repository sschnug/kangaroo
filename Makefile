
all: kangaroo

.PHONY: kangaroo
kangaroo:
	@${MAKE} -w -C cbls
	mv cbls/libkangaroo.a .

.PHONY: flatzinc
flatzinc:
	@${MAKE} -w -C flatzinc

.PHONY: clean
clean:
	@${MAKE} -w -C cbls clean

.PHONY: flatzinc-clean
flatzinc-clean:
	@${MAKE} -w -C flatzinc clean

