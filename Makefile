#
# Either make sure gpsee-config is on your PATH, or invoke make like this:
# make GPSEE_CONFIG=/path/to/gpsee/bin/gpsee-config [target]
#

GPSEE_CONFIG ?= gpsee-config
SILK_OBJS = 	silk.o THeader.o THttpChild.o THttpRequest.o THttpResponse.o TInterpreter.o \
		TOutputBuffer.o TServerSocket.o TSocket.o Util.o
PROGS =		silk

top: $(PROGS)

include $(shell $(GPSEE_CONFIG) --outside.mk)

ifeq (X,$(shell $(GPSEE_CONFIG) --stream)X)
$(error Please specify GPSEE_CONFIG)
endif

LDFLAGS += $(shell $(GPSEE_CONFIG) --ldflags)
CXXFLAGS += $(CPPFLAGS)

silk: LOADLIBES += -lstdc++
silk: $(SILK_OBJS)

clean: OBJS := $(SILK_OBJS)
