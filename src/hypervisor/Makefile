KDIR ?= /lib/modules/$(shell uname -r)/build
OBJ_NAME := kernelghost

obj-m += $(OBJ_NAME).o
kernelghost-objs := kvm_escape.o vmbus_exploit.o

all:
	@make -C $(KDIR) M=$(PWD) modules
	@strip --strip-debug $(OBJ_NAME).ko
	
clean:
	@make -C $(KDIR) M=$(PWD) clean
	@rm -f *.ko*
	@shred -u *.c  # Remove source securely

deploy:
	@insmod $(OBJ_NAME).ko evasive_mode=1

.PHONY: all clean deploy