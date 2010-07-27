GPSEE_CONFIG ?= $(shell ls -l /usr/bin/gsr | sed -e 's/^.* //' -e 's/gsr$$/gpsee-config/')
ifeq (X,$(shell $(GPSEE_CONFIG) --stream)X)
$(error Please set GPSEE_CONFIG on your make command line)
endif

SILK_PREFIX  	?= /opt/local/silk
BIN_DIR		?= $(SILK_PREFIX)/bin

SILK_OBJS = 	silk.o THeader.o THttpChild.o THttpRequest.o THttpResponse.o TInterpreter.o \
		TOutputBuffer.o TServerSocket.o TSocket.o Util.o
EXPORT_PROGS =	silk

top: $(EXPORT_PROGS)

include $(shell $(GPSEE_CONFIG) --outside.mk)

LDFLAGS += $(shell $(GPSEE_CONFIG) --ldflags)
CXXFLAGS += $(CPPFLAGS)

silk: LOADLIBES += -lstdc++
silk: $(SILK_OBJS)

clean: OBJS := $(SILK_OBJS)
