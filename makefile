
ifneq ($(KERNELRELEASE),)
include Kbuild
else
# normal makefile
KDIR ?= $$HOME/repos/linux-stable

default:
	$(MAKE) -C $(KDIR) M=$$PWD

clean:
	$(MAKE) -C $(KDIR) M=$$PWD clean
endif