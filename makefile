#Makefile by CDJ - based on
# http://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/ 
# https://www.cs.swarthmore.edu/~newhall/unixhelp/howto_makefiles.html
# https://blog.melski.net/2010/11/30/makefile-hacks-print-the-value-of-any-variable/
# https://stackoverflow.com/questions/7004702/how-can-i-create-a-makefile-for-c-projects-with-src-obj-and-bin-subdirectories

# define the C compiler to use
CC = gcc

# define any compile-time flags
CFLAGS = -Wall -g

# define any directories containing header files other than /usr/include
INCLUDES = -I./include

# define library paths in addition to /usr/lib
#   if I wanted to include libraries not in /usr/lib I'd specify
#   their path using -Lpath, something like:
LFLAGS = -L./lib

# define any libraries to link into executable:
#   if I want to link in libraries (libx.so or libx.a) I use the -llibname 
#   option, something like (this will link in libmylib.so and libm.so:
LIBS = -lm -lreadline

#Define folders for sources, executeables and objects
SRCDIR = ./src
OBJDIR = ./obj
BINDIR = ./bin

# define the C source files
#SRCS = weathercollect.c weatherfunc.c
SRCS = $(wildcard $(SRCDIR)/*.c)
#SRCS = $(SRCDIR)/%.c

# define the C object files 
OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

# define the executable file 
MAIN = weathercollect

#
# The following part of the makefile is generic; it can be used to 
# build any executable just by changing the definitions above and by
# deleting dependencies appended to the file from 'make depend'
#

.PHONY: depend clean

all:	$(MAIN)
	@echo  Compilation Completed

$(MAIN):	$(OBJS) 
	$(CC) $(CFLAGS) $(INCLUDES) -o $(BINDIR)/$(MAIN) $(OBJS) $(LFLAGS) $(LIBS)

# this is a suffix replacement rule for building .o's from .c's
# it uses automatic variables $<: the name of the prerequisite of
# the rule(a .c file) and $@: the name of the target of the rule (a .o file) 
# (see the gnu make manual section about automatic variables)
#.c.o:
$(OBJS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@
	@echo "Compiled "$<" successfully!"

clean:
	$(RM) $(OBJDIR)/*.o $(BINDIR)/$(MAIN)
	@echo "o-file and executeable deleted."

depend: $(SRCS)
	makedepend $(INCLUDES) $^
	@echo "Dependencies created successfully!"

#Print the value of a var
print-%:
	@echo '$*=$($*)'
