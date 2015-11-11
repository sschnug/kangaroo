
include /home/swakkhar/kangaroo/template.mk

EXEC=kangaroo

LOBJS= frames/*.o funcs/*.o selcs/*.o selcs/sfs/*.o selcs/sps/*.o tabus/*.o tabus/dvtabus/*.o tabus/svtabus/*.o vars/*.o vars/flipvars/*.o vars/rangevars/*.o

all: subdirs $(EXEC)

$(EXEC): subdirs
	$(AR) lib$@.a $(LOBJS)

.PHONY: subdirs
subdirs:
	@${MAKE} -w -C frames
	@${MAKE} -w -C funcs
	@${MAKE} -w -C selcs
	@${MAKE} -w -C selcs/sfs
	@${MAKE} -w -C selcs/sps
	@${MAKE} -w -C tabus
	@${MAKE} -w -C tabus/dvtabus
	@${MAKE} -w -C tabus/svtabus
	@${MAKE} -w -C vars
	@${MAKE} -w -C vars/flipvars
	@${MAKE} -w -C vars/rangevars

.PHONY: clean
clean:
	@${MAKE} -w -C frames clean
	@${MAKE} -w -C funcs clean
	@${MAKE} -w -C selcs clean
	@${MAKE} -w -C selcs/sfs clean
	@${MAKE} -w -C selcs/sps clean
	@${MAKE} -w -C tabus clean
	@${MAKE} -w -C tabus/dvtabus clean
	@${MAKE} -w -C tabus/svtabus clean
	@${MAKE} -w -C vars clean
	@${MAKE} -w -C vars/flipvars clean
	@${MAKE} -w -C vars/rangevars clean
	rm -f lib${EXEC}.a *~

