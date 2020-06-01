.PHONY: all clean install

PROJECTS = terminal serial parallel video

all:
		for dir in $(PROJECTS); do \
				(cd $$dir; ${MAKE}) \
		done
		$(AR) -M <libs.mri

clean:
		for dir in $(PROJECTS); do \
				(cd $$dir; ${MAKE} clean) \
		done;
		rm -f drivers.a

install:
		for dir in $(PROJECTS); do \
				(cd $$dir; ${MAKE} install) \
		done
		cp drivers.a ../sysroot/lib/drivers.a
