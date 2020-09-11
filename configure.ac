AC_PREREQ([2.69])
AC_INIT([git-extra], [0.0.0])

# Store build files not in main directory
AC_CONFIG_AUX_DIR([build-aux])

AM_INIT_AUTOMAKE([foreign subdir-objects nostdinc -Wall -Werror])

AC_CONFIG_SRCDIR([src/main.c])
AC_CONFIG_HEADERS([include/config.h])

AC_ARG_ENABLE([memcheck],
  [AS_HELP_STRING([--disable-memcheck],
  [disable valgrind (enabled by default)])],
  [enable_memcheck=$enableval],
  [enable_memcheck=yes])

AC_PATH_PROG([GIT], [git])
AM_CONDITIONAL([HAVE_GIT], [test -n "$GIT"])
AM_COND_IF([HAVE_GIT],,[AC_MSG_ERROR([Please install git before trying to build git-extra])])

AC_PATH_PROG([DOCKER], [docker])
AM_CONDITIONAL([HAVE_DOCKER], [test -n "$DOCKER"])

AC_PATH_PROG([NODE], [node])
AM_CONDITIONAL([HAVE_NODE], [test -n "$NODE"])

AC_PATH_PROG([VALGRIND], [valgrind])
AM_CONDITIONAL([HAVE_VALGRIND], [test -n "$VALGRIND"])

dnl disable memcheck if valgrind not found
if test "x$enable_memcheck" = "xyes"; then
  if test -z "$VALGRIND"; then
    enable_memcheck=no
  fi
fi

AC_MSG_CHECKING([if memcheck should be enabled])
if test x$enable_memcheck != xno; then
  AC_MSG_RESULT(yes)
else
  AC_MSG_RESULT(no)
fi

AM_CONDITIONAL([ENABLE_MEMCHECK],[test x$enable_memcheck = xyes])

# Checks for programs.
AC_PROG_CC
AC_PROG_INSTALL

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([stddef.h stdlib.h string.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_OFF_T
AC_TYPE_PID_T
AC_TYPE_SIZE_T
AC_TYPE_SSIZE_T

# Checks for library functions.
AC_FUNC_FORK
AC_FUNC_MALLOC
AC_CHECK_FUNCS([dup2 getcwd memset setenv])

AC_CONFIG_FILES([
	Makefile
  test/integration/Makefile
	test/unit/Makefile
])
AC_OUTPUT
