CXX?=g++
CXXFLAGS?=-Wall -O2
LIB?=hidapi
ifeq ($(LIB),libusb)
	CPPFLAGS=-Dlibusb
	LIBS=-lusb-1.0
else
	CPPFLAGS=-Dhidapi
	LIBS=-lhidapi-hidraw
endif
SYSTEMDDIR?=/usr/lib/systemd

PREFIX?=$(DESTDIR)/usr
libdir?=$(PREFIX)/lib
includedir?=$(PREFIX)/include

# Program & versioning information
PROGN=rawwrite
MAJOR=0
MINOR=3
MICRO=9

CXXFLAGS+=-std=gnu++11 -DVERSION=\"$(MAJOR).$(MINOR).$(MICRO)\"
APPSRCS=src/main.cpp
LIBSRCS=src/classes/*.cpp

.PHONY: all bin debug clean

all: bin/$(PROGN)

bin: bin/$(PROGN)

bin/$(PROGN): $(APPSRCS) $(LIBSRCS)
	@mkdir -p bin
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(LDFLAGS) $^ -o $@ $(LIBS)
	
debug: CXXFLAGS += -g -Wextra -pedantic
debug: bin/$(PROGN)

clean:
	@rm -rf bin
