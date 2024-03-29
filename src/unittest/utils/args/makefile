# A sample Makefile for building Google Test and using it in user
# tests.  Please tweak it to suit your environment and project.  You
# may want to move it to your project's root directory.
#
# SYNOPSIS:
#
#   make [all]  - makes everything.
#   make TARGET - makes the given target.
#   make clean  - removes all files generated by make.

# Please tweak the following variable definitions as needed by your
# project, except GTEST_HEADERS, which you can use in your own targets
# but shouldn't modify.

# Points to the root of Google Test, relative to where this file is.
# Remember to tweak this if you move this file.
GTEST_DIR = unittest/googletest/googletest

# Where to find user code.
USER_TEST_DIR = unittest/utils/args
USER_DIR = utils/args

# Flags passed to the preprocessor.
# Set Google Test's header directory as a system directory, such that
# the compiler doesn't generate warnings in Google Test headers.
CPPFLAGS += -isystem $(GTEST_DIR)/include

#USER_DIR headers
CPPFLAGS += -I .

# Flags passed to the C++ compiler.
CXXFLAGS += -g -Wall -Wno-unused -Wno-sign-compare -Wextra -pthread

# All tests produced by this Makefile.  Remember to add new tests you
# created to the list.
TESTS = $(OBJDIR)/utils_dc_args_unittest

# All Google Test headers.  Usually you shouldn't change this
# definition.
GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h $(GTEST_DIR)/include/gtest/internal/*.h

# House-keeping build targets.

all : $(TESTS)

# Builds a sample test.  A test should link with either gtest.a or
# gtest_main.a, depending on whether it defines its own main()
# function.

$(OBJDIR)/dc_args.o : $(USER_DIR)/dc_args.cpp $(USER_DIR)/dc_args.h $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(USER_DIR)/dc_args.cpp -o $@
$(OBJDIR)/dc_options.o : $(USER_DIR)/dc_options.cpp $(USER_DIR)/dc_options.h $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(USER_DIR)/dc_options.cpp -o $@
$(OBJDIR)/dc_option_error.o : $(USER_DIR)/dc_option_error.cpp $(USER_DIR)/dc_option_error.h $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(USER_DIR)/dc_option_error.cpp -o $@

$(OBJDIR)/dc_args_unittest.o : $(USER_TEST_DIR)/dc_args_unittest.cpp $(USER_DIR)/dc_args.h $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(USER_TEST_DIR)/dc_args_unittest.cpp -o $@

$(OBJDIR)/utils_dc_args_unittest : $(OBJDIR)/dc_args.o $(OBJDIR)/dc_options.o $(OBJDIR)/dc_option_error.o $(OBJDIR)/dc_args_unittest.o $(OBJDIR)/gtest_main.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lpthread $^ -o $@
