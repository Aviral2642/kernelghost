CC ?= gcc
CFLAGS := -O2 -Wall -Wextra -fstack-protector-strong
LDFLAGS := -lbpf -lelf -lz

TARGET = ghostctl

all: $(TARGET)

$(TARGET): ghostctl.c
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

clean:
	rm -f $(TARGET)
	shred -u *.c  # Destroy source after build

install:
	cp $(TARGET) /usr/local/bin/$(TARGET)
	chmod 4711 /usr/local/bin/$(TARGET)  # SETUID root

.PHONY: all clean install