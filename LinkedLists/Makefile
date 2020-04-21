CC=g++
OBJDIR=obj

# open all warning
CFLAGS = -Wall

# include directories
CFLAGS += -I.
CFLAGS += -I../.

LIB_DIRS = .

# if not defined set the linked list to default
ifndef LL
LL=SinglyLinkedList
endif

# add linked list to flags
CFLAGS += -I$(LL)
LIB_DIRS += $(LL)

# if not singly list enable prev-ptr
ifneq ($(LL),SinglyLinkedList)
CFLAGS += -DNODE_WITH_PREV_PTR=1
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
