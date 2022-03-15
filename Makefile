SRCDIR		= src
OBJDIR		= obj
BINDIR		= bin
#TSTDIR		= test
EXE 		= MainEvent
#TEST		= CaloImplementationTests
SRCFILES	= $(wildcard $(SRCDIR)/*.cxx)
#TSTFILES	= $(wildcard $(TSTDIR)/*.cxx)
OBJFILES	= $(subst $(SRCDIR),$(OBJDIR),$(SRCFILES:.cxx=.o))

# ROOT
ROOTCFLAGS 	= $(shell root-config --cflags)
ROOTLIBS   	= $(shell root-config --libs)
ROOTGLIBS  	= $(shell root-config --glibs)
ROOTLDFLAGS	= $(shell root-config --ldflags)

# C++ compiler
CXX        	= g++ -std=c++11 -g -O2
CXXFLAGS   	= -W -Wall -Wextra -pedantic $(ROOTCFLAGS)
LDFLAGS    	= $(ROOTLDFLAGS) $(ROOTLIBS) $(ROOTGLIBS) -lMinuit

INCLUDES   	= -I$(SRCDIR) $(ROOTCFLAGS)
CXXFLAGS   += $(INCLUDES)

$(info Beginning of compilation)
$(info )
$(info Compiler: $(CXX) $(CXXFLAGS))
$(info )
$(info Linker: $(CXX) $(LDFLAGS))
$(info )
$(info Sources directory: $(SRCDIR))
$(info Sources files: $(SRCFILES))
#$(info Tests directory: $(TSTDIR))
#$(info Tests files: $(TSTFILES))
$(info Objects directory: $(OBJDIR))
$(info Object files: $(OBJFILES))
$(info Binary directory: $(BINDIR))
$(info Executables: $(EXE)) #$(TEST))
$(info -------------------------------------)

default: build $(EXE)
	@echo "In default rule."

# Build the main executables
$(EXE): $(OBJDIR)/$(EXE).o $(OBJFILES)
	@echo ""
	@echo "Linking $@ from $^"
	$(CXX) $(OBJFILES) -o $(BINDIR)/$@ $(LDFLAGS)

# Build the objects from the source files.
$(OBJDIR)/%.o: $(SRCDIR)/%.cxx
	@echo ""
	@echo "Compiling $< to $@"
	@$(CXX) $(CXXFLAGS) -c $< -o $@

#test: build $(TEST)
#	@echo "In test rule."

#$(TEST): $(OBJDIR)/$(TEST).o $(OBJFILES)
#	@echo ""
#	@echo "Linking $@ from $^"
#	$(CXX) $(OBJFILES) -o $(BINDIR)/$@ $(LDFLAGS)

#$(OBJDIR)/%.o: $(SRCDIR)/%.cxx $(TSTDIR)/%.cxx
#	@echo ""
#	@echo "Compiling $< to $@"
#	@$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: build
build:
	@mkdir -p $(OBJDIR)
	@mkdir -p $(BINDIR)

.PHONY: clean
clean:
	@echo "Cleaning..."
	rm -f $(OBJDIR)/*.o
	rm -f $(BINDIR)/$(EXE)
#	rm -f $(BINDIR)/$(TEST)
