# edit

CXX ?= g++
CC ?= gcc

SRCDIR = ..
OBJDIR = obj
DEPDIR = $(OBJDIR)


SRCS = api/*.cpp system/*.cpp system/pawn/*.cpp system/SDK/*.cpp util/*.cpp modules/*.cpp
OUTFILE := niceamx.so

INCLUDES = $(SRCDIR) $(SRCDIR)/system
DEFINES =

CPPFLAGS = -std=c++0x
CXXFLAGS = -Wall -pipe -m32
LDFLAGS = -Wall -pipe -m32
LIBS =
# configurations

# maximum optimization
release: CXXFLAGS += -O3 -fvisibility=hidden -fvisibility-inlines-hidden -ffunction-sections -fdata-sections -fstrict-aliasing -fmerge-all-constants -fomit-frame-pointer -pedantic
release: LDFLAGS += -s -Wl,--gc-sections
release: DEFINES += NDEBUG

# minimum optimization
debug: CXXFLAGS += -ggdb3 -Wextra -Wno-unused-parameter
debug: LDFLAGS += -ggdb3
debug: OUTFILE = niceamx-debug.so
debug: DEFINES += _DEBUG OVERTIMER_ENABLE PRINT_OUTCOMING_NATIVES
debug: .postfix = .debug

release debug: .plugin

test: OUTFILE = niceamx-test
test: CXXFLAGS += -ggdb3 -pedantic -Wextra -pg
test: LDFLAGS += -ggdb3 -pg
test: DEFINES += _DEBUG OVERTIMER_ENABLE PRINT_OUTCOMING_NATIVES TEST_MODE
test: SRCS = api/*.cpp system/*.cpp util/*.cpp modules/*.cpp tests/*.cpp
test: .postfix = .test
test: TARGET ?= all
test:
	$(MAKE) $(TARGET) 'OUTFILE=$(OUTFILE)' 'SRCS=$(SRCS)' 'LIBS=$(LIBS)' 'LDFLAGS=$(LDFLAGS)' 'CXXFLAGS=$(CXXFLAGS)' 'CPPFLAGS=$(CPPFLAGS)' '.postfix=$(.postfix)'


export: OUTFILE = niceamx-export.so
export: LDFLAGS += -static-libstdc++ -static-libgcc
#export: TARGET ?= release
export: release
	elfedit --output-osabi=none $(OUTFILE) || brandelf -f 0 $(OUTFILE) || freebsd-brandelf -f 0 $(OUTFILE)


# flags to make a plugin
.plugin: CXXFLAGS += -fPIC
.plugin: LDFLAGS += -fPIC -shared -Wl,--no-undefined
.plugin: TARGET ?= all
.plugin:
	$(MAKE) $(TARGET) 'OUTFILE=$(OUTFILE)' 'SRCS=$(SRCS)' 'LIBS=$(LIBS)' 'LDFLAGS=$(LDFLAGS)' 'CXXFLAGS=$(CXXFLAGS)' 'CPPFLAGS=$(CPPFLAGS)' '.postfix=$(.postfix)'

.PHONY: install release debug test export .plugin

install: ../server/plugins/$(OUTFILE)

../server/plugins/$(OUTFILE): $(OUTFILE)
	cp -f '$<' '$@'
# do not edit --->

.PHONY: all clean
all: $(OUTFILE)

CPPFLAGS += $(addprefix -I, $(INCLUDES)) $(addprefix -D, $(DEFINES))

MKDIR ?= mkdir -p --
RM ?= rm -f --
.postfix ?=

REALSRCS := $(wildcard $(addprefix $(SRCDIR)/, $(SRCS)))
OBJS := $(REALSRCS:$(SRCDIR)/%.cpp=$(OBJDIR)/%$(.postfix).o)
DEPS := $(REALSRCS:$(SRCDIR)/%.cpp=$(DEPDIR)/%$(.postfix).d)

DIRS := $(sort $(dir $(OBJS)) $(dir $(DEPS)))


$(DIRS):
	$(MKDIR) '$@'

$(OBJDIR)/%$(.postfix).o: $(SRCDIR)/%.cpp
	$(CXX) -c -MMD -MP $(CPPFLAGS) $(CXXFLAGS) -o '$@' '$<'
$(OBJDIR)/%$(.postfix).o: $(SRCDIR)/%.c
	$(CC) -c -MMD -MP $(CPPFLAGS) $(CXXFLAGS) -o '$@' '$<'

$(OUTFILE): $(DIRS) $(OBJS)
	$(CXX) $(LDFLAGS) -o '$@' $(OBJS) $(LIBS)

clean:
	$(RM) $(OBJS) $(OUTFILE) $(DEPS)

-include $(DEPS)


