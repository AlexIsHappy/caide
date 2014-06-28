# The following variables will likely need to be customized, depending on where
# and how you built LLVM & Clang. They can be overridden by setting them on the
# make command line: "make VARNAME=VALUE", etc.

# LLVM_SRC_PATH is the path to the root of the checked out source code. This
# directory should contain the configure script, the include/ and lib/
# directories of LLVM, Clang in tools/clang/, etc.
# Alternatively, if you're building vs. a binary download of LLVM, then
# LLVM_SRC_PATH can point to the main untarred directory.
LLVM_SRC_PATH := clangbuild/out

# LLVM_BUILD_PATH is the directory in which you built LLVM - where you ran
# configure or cmake.
# For linking vs. a binary build of LLVM, point to the main untarred directory.
# LLVM_BIN_PATH is the directory where binaries are placed by the LLVM build
# process. It should contain the tools like opt, llc and clang.
LLVM_BUILD_PATH := $(LLVM_SRC_PATH)
LLVM_BIN_PATH := $(LLVM_BUILD_PATH)/bin

# It's recommended that CXX matches the compiler you used to build LLVM itself.
CXX := g++
CXXFLAGS := -fno-rtti -O2 -c -static -D__STDC_CONSTANT_MACROS -D__STDC_LIMIT_MACROS
ARCHIVER := ar

LLVM_CXXFLAGS := $($(LLVM_BIN_PATH)/llvm-config --cxxflags)

CLANG_INCLUDES := \
	-I$(LLVM_SRC_PATH)/include \
	-I$(LLVM_BUILD_PATH)/include

BUILDDIR := build

.PHONY: all
all: make_builddir $(BUILDDIR)/libcpphelper.a $(BUILDDIR)/libchelper.a


.PHONY: make_builddir
make_builddir:
	@test -d $(BUILDDIR) || mkdir $(BUILDDIR)

$(BUILDDIR)/libcpphelper.a: $(BUILDDIR)/inliner.o $(BUILDDIR)/optimizer.o $(BUILDDIR)/util.o
	$(ARCHIVER) rcs $(BUILDDIR)/libcpphelper.a $^

$(BUILDDIR)/libchelper.a: $(BUILDDIR)/libcpphelper.a cwrapper.cpp inliner.h optimizer.h
	$(CXX) $(CXXFLAGS) cwrapper.cpp -o $(BUILDDIR)/cwrapper.o -Lbuild -lcpphelper
	$(ARCHIVER) rcs $(BUILDDIR)/libchelper.a $(BUILDDIR)/cwrapper.o

$(BUILDDIR)/inliner.o: inliner.cpp util.h inliner.h
	$(CXX) $(CXXFLAGS) $(LLVM_CXXFLAGS) $(CLANG_INCLUDES) inliner.cpp -o $@

$(BUILDDIR)/optimizer.o: optimizer.cpp util.h optimizer.h
	$(CXX) $(CXXFLAGS) $(LLVM_CXXFLAGS) $(CLANG_INCLUDES) optimizer.cpp -o $@

$(BUILDDIR)/util.o: util.cpp util.h
	$(CXX) $(CXXFLAGS) $(LLVM_CXXFLAGS) $(CLANG_INCLUDES) util.cpp -o $@

.PHONY: clean
clean:
	rm -rf $(BUILDDIR)/* *.dot

######## Test targets
LLVM_LDFLAGS := $($(LLVM_BIN_PATH)/llvm-config --ldflags --libs)

# List of Clang libraries to link. The proper -L will be provided by the
# call to llvm-config
# Note that I'm using -Wl,--{start|end}-group around the Clang libs; this is
# because there are circular dependencies that make the correct order difficult
# to specify and maintain. The linker group options make the linking somewhat
# slower, but IMHO they're still perfectly fine for tools that link with Clang.
CLANG_LIBS := \
	-Wl,--start-group \
	-lclangFrontendTool  \
	-lclangFrontend  \
	-lclangDriver  \
	-lclangSerialization  \
	-lclangCodeGen  \
	-lclangParse  \
	-lclangSema  \
	-lclangStaticAnalyzerFrontend  \
	-lclangStaticAnalyzerCheckers  \
	-lclangStaticAnalyzerCore  \
	-lclangAnalysis  \
	-lclangARCMigrate  \
	-lclangRewriteFrontend  \
	-lclangRewriteCore  \
	-lclangEdit  \
	-lclangAST  \
	-lclangLex  \
	-lclangBasic \
	-Wl,--end-group

test_exe: $(BUILDDIR)/libcpphelper.a $(BUILDDIR)/libchelper.a
	$(CXX) -Lbuild -lchelper -lcpphelper $(CLANG_LIBS) $(LLVM_LDFLAGS) test_c.cpp -o test_c.exe