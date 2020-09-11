TEMPLATE_DIR=$(builddir)/

AM_CPPFLAGS = \
	-I$(top_builddir)/include/ \
	-I$(top_builddir)/test/unit/ \
	-I$(top_srcdir)/include/ \
	-I$(top_srcdir)/test/unit/ \
	-DTEMPLATE_DIR='"$(TEMPLATE_DIR)"'

EXTRA_DIST = \
	add.tests.h \
	branch.tests.h \
	cat.tests.h \
	commit.tests.h \
	default.tests.h \
	editor.tests.h \
	edit.tests.h \
	hash.tests.h \
	templ.tests.h \
	test_utils.h

check_PROGRAMS = add.tests branch.tests cat.tests commit.tests default.tests edit.tests editor.tests hash.tests templ.tests
TESTS = $(check_PROGRAMS)

if ENABLE_MEMCHECK
LOG_COMPILER = $(VALGRIND)
AM_LOG_FLAGS = --leak-check=full -v
endif

common_SOURCES = test_utils.c

TEST_SRC_DIR = $(top_srcdir)/src

common_SOURCES += \
	$(TEST_SRC_DIR)/default.c \
	$(TEST_SRC_DIR)/exec.c \
	$(TEST_SRC_DIR)/git.c \
	$(TEST_SRC_DIR)/log.c

add_tests_SOURCES = \
	$(common_SOURCES) \
	add.tests.c \
	$(TEST_SRC_DIR)/add.c \
	$(TEST_SRC_DIR)/branch.c \
	$(TEST_SRC_DIR)/commit.c \
	$(TEST_SRC_DIR)/editor.c \
	$(TEST_SRC_DIR)/hash.c \
	$(TEST_SRC_DIR)/prepend.c \
	$(TEST_SRC_DIR)/templ.c

branch_tests_SOURCES = \
	$(common_SOURCES) \
	branch.tests.c \
	$(TEST_SRC_DIR)/branch.c \
	$(TEST_SRC_DIR)/prepend.c

cat_tests_SOURCES = \
	$(common_SOURCES) \
	cat.tests.c \
	$(TEST_SRC_DIR)/cat.c

commit_tests_SOURCES = \
	$(common_SOURCES) \
	commit.tests.c \
	$(TEST_SRC_DIR)/branch.c \
	$(TEST_SRC_DIR)/commit.c \
	$(TEST_SRC_DIR)/prepend.c

default_tests_SOURCES = \
	$(common_SOURCES) \
	default.tests.c

edit_tests_SOURCES = \
	$(common_SOURCES) \
	edit.tests.c \
	$(TEST_SRC_DIR)/add.c \
	$(TEST_SRC_DIR)/branch.c \
	$(TEST_SRC_DIR)/cat.c \
	$(TEST_SRC_DIR)/commit.c \
	$(TEST_SRC_DIR)/edit.c \
	$(TEST_SRC_DIR)/editor.c \
	$(TEST_SRC_DIR)/hash.c \
	$(TEST_SRC_DIR)/prepend.c \
	$(TEST_SRC_DIR)/templ.c

editor_tests_SOURCES = \
	$(common_SOURCES) \
	editor.tests.c \
	$(TEST_SRC_DIR)/editor.c \
	$(TEST_SRC_DIR)/hash.c

hash_tests_SOURCES = \
	$(common_SOURCES) \
	hash.tests.c \
	$(TEST_SRC_DIR)/hash.c

templ_tests_SOURCES = \
	$(common_SOURCES) \
	templ.tests.c \
	$(TEST_SRC_DIR)/templ.c