.SILENT: all clean

TGT = `ls -IMakefile -Ilib`

all:
	@for i in $(TGT); do \
		echo Day $$i; \
		make -s -C $$i; \
	done

clean:
	@for i in $(TGT); do \
		make -s -C $$i clean; \
	done