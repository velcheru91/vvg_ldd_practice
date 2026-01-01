MYPROC=ldd1_rw
obj-m += $(MYPROC).o

export KROOT=/lib/modules/$(shell uname -r)/build

all: modules

modules: clean
	make -C $(KROOT) M=$(PWD) modules

modules_install:
	make -C $(KROOT) M=$(PWD) modules_install

kernel_clean:
	make -C $(KROOT) M=$(PWD) clean

clean: kernel_clean
	rm -rf Module.symvers modules.order

insert: modules
	sudo dmesg -C
	sudo insmod $(MYPROC).ko

remove: clean
	sudo rmmod $(MYPROC)
