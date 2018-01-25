AC_PREREQ([2.65])
AC_INIT([libmpsse],[1.3],[https://github.com/l29ah/libmpsse])

AC_ARG_ENABLE([python],AS_HELP_STRING([--disable-python], [Do not build Python wrappers]))
AS_IF([test "x$enable_python" != "xno"], [BUILD="swig"], [BUILD=""])

AC_CONFIG_SRCDIR([mpsse.c])

AC_PROG_CC
AC_LANG(C)

AC_TYPE_SIZE_T
AC_FUNC_MALLOC

CFLAGS="-Wall -fPIC -fno-strict-aliasing $CFLAGS"

dnl Check to see if the libftdi1 headers have been installed
AC_CHECK_HEADERS([libftdi1/ftdi.h], [LIBFTDI1=1], [LIBFTDI1=""])

dnl If libftdi1 headers were not detected, check for libftdi headers/library
if ! test $LIBFTDI1
then
	AC_CHECK_HEADERS([ftdi.h],[LIBFTDI1=0],[echo "error: missing libftdi header files" && exit 1])
	AC_CHECK_LIB([ftdi],[ftdi_init],[],[echo "error: missing libftdi library" && exit 1],[])
	LDFLAGS="-lftdi $LDFLAGS"
dnl Else check for the libftdi1 library
else
	AC_CHECK_LIB([ftdi1],[ftdi_init],[],[echo "error: missing libftdi1 library" && exit 1],[])
	LDFLAGS="-lftdi1 $LDFLAGS"
fi

if test $BUILD
then
	AM_PATH_PYTHON()
	AC_ARG_VAR([PYTHON_INC], [Include flags for python, bypassing python-config])
	AC_ARG_VAR([PYTHON_LIBS], [Library flags for python, bypassing python-config])

	AC_ARG_VAR([PYTHON_CONFIG], [Path to python-config])
	AS_IF([(test -z "$PYTHON_INC" || test -z "$PYTHON_LIBS") && test -z "$PYTHON_CONFIG"], [
		AC_PATH_PROGS([PYTHON_CONFIG],
			[python$PYTHON_VERSION-config python-config],
			[no])
		AS_IF([test "$PYTHON_CONFIG" = no], [AC_MSG_ERROR([cannot find python-config for $PYTHON.])])
	])

	AC_ARG_VAR([SWIG], [Path to swig])
	AS_IF([test -z "$SWIG"], [
		AC_PATH_PROGS([SWIG],
			[swig],
			[no])
		AS_IF([test "$SWIG" = no], [AC_MSG_ERROR([cannot find swig.])])
	])

	AS_IF([test -z "$PYTHON_INC"], [
		AC_MSG_CHECKING([python include flags])
		PYTHON_INC=`$PYTHON_CONFIG --includes`
		AC_MSG_RESULT([$PYTHON_INC])
	])
	AS_IF([test -z "$PYTHON_LIBS"], [
		AC_MSG_CHECKING([python lib flags])
		PYTHON_LIBS=`$PYTHON_CONFIG --libs`
		AC_MSG_RESULT([$PYTHON_LIBS])
	])

fi

dnl OSX specific compiler flags
if test "$(uname)" == "Darwin"
then
	SONAME="-install_name"
	FRAMEWORK="-framework Python"
else
	SONAME="-soname"
	FRAMEWORK=""
fi

cp confdefs.h config.h

AC_SUBST(BUILD, $BUILD)
AC_SUBST(SWIG, $SWIG)
AC_SUBST(PYDEV, $PYTHON_INC)
AC_SUBST(PYLIB, $PYTHON_LIBS)
AC_SUBST(SONAME, $SONAME)
AC_SUBST(FRAMEWORK, $FRAMEWORK)
AC_SUBST(LIBFTDI1, $LIBFTDI1)
AC_CONFIG_FILES([Makefile])
AC_OUTPUT
