CC=g++
OBJDIR=obj

# open all warning
CFLAGS = -Wall

# include directories
CFLAGS += -I.
CFLAGS += -I../.
# for to_string function
CFLAGS += -std=c++0x

LIB_DIRS = .

# if not defined the technique set to default
ifndef TECH
TECH=LinearProbing
endif

# add technique to flags
CFLAGS += -I$(TECH)
LIB_DIRS += $(TECH)

# Seperate Chaining needs the linked list
ifeq ($(TECH),SeparateChaining)
CFLAGS += -I../LinkedLists/DoublyLinkedList
LIB_DIRS += ../LinkedLists/DoublyLinkedList
endif

# set source files and object files under LIB_DIRS
SOURCE_FILES = ${foreach d, $(LIB_DIRS), ${subst ${d}/,,${wildcard $(d)/*.cpp}}}
OBJ_FILES := $(SOURCE_FILES:%.cpp=$(OBJDIR)/%.o)

#TODO: detect header file changes

# add src directories to path for building object files
vpath %.cpp $(LIB_DIRS)

# for tracing compilation
TRACE_CC = @echo "  CC       " $<
Q=@

# rules
build: $(OBJDIR) $(OBJ_FILES)
	$(Q)echo "Linking.."
	$(CC) -o Test.out $(OBJ_FILES)
$(OBJDIR)/%.o: %.cpp
	$(TRACE_CC)
	$(Q)$(CC) $(CFLAGS) -c $< -o $@
$(OBJDIR):
	mkdir $(OBJDIR)
run:
	$(Q)./Test.out
clean:
	rm -rf $(OBJDIR)
	rm -f *.out
