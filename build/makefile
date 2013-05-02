# edit

CXX ?= g++
CC ?= gcc

SRCDIR = ..
OBJDIR = obj
DEPDIR = $(OBJDIR)

# common configuration
SRCS = api/*.cpp system/*.cpp system/pawn/*.cpp system/SDK/*.cpp util/*.cpp modules/*.cpp
OUTFILE = niceamx.so

INCLUDES = $(SRCDIR) $(SRCDIR)/system
DEFINES =

CPPFLAGS = -std=c++0x
CXXFLAGS = -Wall -pipe -m32
LDFLAGS = -Wall -pipe -m32
LIBS =
BOOST_LIBS = 

PREFIX = ../server/plugins

# custom configurations

config ?= release
configurations := release debug test

# flags for making plugin (should not be used)
CXXFLAGS_plugin := $(CXXFLAGS) -fPIC
LDFLAGS_plugin := $(LDFLAGS) -fPIC -shared -Wl,--no-undefined

# maximum optimization
CXXFLAGS_release = $(CXXFLAGS_plugin) -O3 -fvisibility=hidden -fvisibility-inlines-hidden -ffunction-sections -fdata-sections -fstrict-aliasing -fmerge-all-constants -fomit-frame-pointer -pedantic -flto -fno-ident -mfpmath=sse -msse3 -march=nocona -fgraphite-identity -floop-interchange -floop-block
LDFLAGS_release = $(LDFLAGS_plugin) -O3 -s -Wl,--gc-sections -flto
# add NDEBUG definition when final version is out
DEFINES_release = $(DEFINES) OVERTIMER_DISABLE

# minimum optimization
CXXFLAGS_debug = $(CXXFLAGS_plugin) -O0 -ggdb3 -Wextra -Wno-unused-parameter -fstack-protector-all
LDFLAGS_debug = $(LDFLAGS_plugin) -ggdb3 -rdynamic
DEFINES_debug = $(DEFINES) _DEBUG PRINT_OUTCOMING_NATIVES PRINT_INCOMING_CALLBACKS OVERTIMER_DISABLE
OUTFILE_debug = niceamx-debug.so
postfix_debug = .debug

# test build (for valgrind & co)
OUTFILE_test = niceamx-test
CXXFLAGS_test = $(CXXFLAGS) -ggdb3 -pedantic -Wextra -Wconversion -pg
LDFLAGS_test = $(LDFLAGS) -ggdb3 -pg -rdynamic
DEFINES_test = $(DEFINES) _DEBUG OVERTIMER_ENABLE PRINT_OUTCOMING_NATIVES TEST_MODE
SRCS_test = api/*.cpp system/*.cpp util/*.cpp modules/*.cpp tests/*.cpp
PREFIX_test = ../server
postfix_test = .test

ifdef export
# make config=debug export=1
LDFLAGS_$(config) += -static-libstdc++ -static-libgcc
export: all
	elfedit --output-osabi=none $(OUTFILE) || brandelf -f 0 $(OUTFILE) || freebsd-brandelf -f 0 $(OUTFILE)
endif

ifdef BOOST_ROOT
endif

# do not edit --->


.PHONY: $(configurations) all clean install uninstall

MKDIR ?= mkdir -p --
RM ?= rm -f --
CP ?= cp -f --

postfix ?=


define configuration_template
$(strip $(1))_$(config) ?= $$($(strip $(1)))
$(strip $(1)) := $$($(strip $(1))_$(config))
endef
$(foreach var, CPPFLAGS CXXFLAGS CFLAGS LDFLAGS OUTFILE LIBS INCLUDES DEFINES SRCS PREFIX postfix, $(eval $(call configuration_template, $(strip $(var)))))

all: $(OUTFILE)

$(configurations):
	$(MAKE) 'config=$@'

install: $(PREFIX)/$(OUTFILE)

$(PREFIX)/$(OUTFILE): $(OUTFILE)
	$(CP) '$<' '$@'

uninstall:
	-$(RM) $(PREFIX)/$(OUTFILE)

clean:
	-$(RM) $(OBJS) $(OUTFILE) $(DEPS)

CPPFLAGS += $(addprefix -I, $(INCLUDES)) $(addprefix -D, $(DEFINES))

#PCH = $(SRCDIR)/system/samp.h.gch
REALSRCS := $(wildcard $(addprefix $(SRCDIR)/, $(SRCS)))
OBJS := $(REALSRCS:$(SRCDIR)/%.cpp=$(OBJDIR)/%$(postfix).o)
DEPS := $(REALSRCS:$(SRCDIR)/%.cpp=$(DEPDIR)/%$(postfix).d)
#$(PCH:$(SRCDIR)/%.gch=$(DEPDIR)/%$(postfix).d)

DIRS := $(OBJDIR) $(sort $(dir $(OBJS)) $(dir $(DEPS)))


$(DIRS):
	-$(MKDIR) '$@'

$(OBJDIR)/%$(postfix).o: $(SRCDIR)/%.cpp
	$(CXX) -c -MMD -MP $(CPPFLAGS) $(CXXFLAGS) -o '$@' '$<'
$(OBJDIR)/%$(postfix).o: $(SRCDIR)/%.c
	$(CC) -c -MMD -MP $(CPPFLAGS) $(CFLAGS) -o '$@' '$<'

$(OUTFILE): $(DIRS) $(OBJS)
	$(CXX) $(LDFLAGS) -o '$@' $(OBJS) $(LIBS)

# pre compiled headers (GCC)
$(SRCDIR)/%.gch: $(SRCDIR)/%
	$(CXX) -c -MMD -MP -MF '$(*:%=$(DEPDIR)/%$(postfix).d)' $(CPPFLAGS) $(CXXFLAGS) '$<'

-include $(DEPS)


