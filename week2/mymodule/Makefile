KDIR= /lib/modules/$(shell uname -r)/build

obj-m := mymodule.o

all:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules

install:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules_install
	depmod -a

clean:
	rm -f *~
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) clean
