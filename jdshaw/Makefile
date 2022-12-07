.SILENT: all clean

TGT = 01 02 03 04 05

all:
	@for i in $(TGT); do \
		echo Day $$i; \
		make -s -C $$i; \
	done

clean:
	@for i in $(TGT); do \
		make -s -C $$i clean; \
	done