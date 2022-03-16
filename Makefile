SRCS := \
  src/main.cpp \
	$(wildcard vendor/boost/program_options/*.cpp) \
	vendor/tinyxml2.cpp

CPPFLAGS += \
  -std=c++17 \
  -pthread \
  -Ivendor \
  -lstdc++

OBJS := $(SRCS:.cpp=.o)

DEPDIR := .d
$(shell mkdir -p $(DEPDIR)/src >/dev/null)
$(shell mkdir -p $(DEPDIR)/vendor/boost/program_options >/dev/null)
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.Td

COMPILE.c = $(CC) $(DEPFLAGS) $(CFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -c
COMPILE.cc = $(CXX) $(DEPFLAGS) $(CXXFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -c
POSTCOMPILE = @mv -f $(DEPDIR)/$*.Td $(DEPDIR)/$*.d && touch $@

%.o : %.c $(DEPDIR)/%.d
	$(COMPILE.c) $(OUTPUT_OPTION) $<
	        $(POSTCOMPILE)

%.o : %.cc $(DEPDIR)/%.d
	$(COMPILE.cc) $(OUTPUT_OPTION) $<
	$(POSTCOMPILE)

%.o : %.cpp $(DEPDIR)/%.d
	$(COMPILE.cc) $(OUTPUT_OPTION) $<
	$(POSTCOMPILE)

$(DEPDIR)/%.d: ;
	.PRECIOUS: $(DEPDIR)/%.d

all: svg2cpp

svg2cpp: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(CPPFLAGS) $(TARGET_ARCH) -o $@

include $(wildcard $(patsubst %,$(DEPDIR)/%.d,$(basename $(SRCS))))

