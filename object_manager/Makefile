.PHONY: all clean install

PROJECTS = vfsys

all:
		for dir in $(PROJECTS); do \
				(cd $$dir; ${MAKE}) \
		done
		$(AR) -M <libs.mri

clean:
		for dir in $(PROJECTS); do \
				(cd $$dir; ${MAKE} clean) \
		done;
		rm -f objmgr.a

install:
		for dir in $(PROJECTS); do \
				(cd $$dir; ${MAKE} install) \
		done
		cp objmgr.a ../sysroot/lib/objmgr.a
