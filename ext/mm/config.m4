dnl $Id$
dnl config.m4 for extension mm

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(mm, for mm support,
dnl Make sure that the comment is aligned:
dnl [  --with-mm             Include mm support])

dnl Otherwise use enable:

PHP_ARG_ENABLE(mm, whether to enable mm support,
Make sure that the comment is aligned:
[  --enable-mm           Enable mm support])

if test "$PHP_MM" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-mm -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/mm.h"  # you most likely want to change this
  dnl if test -r $PHP_MM/$SEARCH_FOR; then # path given as parameter
  dnl   MM_DIR=$PHP_MM
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for mm files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       MM_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$MM_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the mm distribution])
  dnl fi

  dnl # --with-mm -> add include path
  dnl PHP_ADD_INCLUDE($MM_DIR/include)

  dnl # --with-mm -> check for lib and symbol presence
  dnl LIBNAME=mm # you may want to change this
  dnl LIBSYMBOL=mm # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $MM_DIR/$PHP_LIBDIR, MM_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_MMLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong mm lib version or lib not found])
  dnl ],[
  dnl   -L$MM_DIR/$PHP_LIBDIR -lm
  dnl ])
  dnl
  dnl PHP_SUBST(MM_SHARED_LIBADD)

  PHP_NEW_EXTENSION(mm, mm.c, $ext_shared)
fi
