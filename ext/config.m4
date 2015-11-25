PHP_ARG_ENABLE(walu,
    [Whether to enable the "walu" extension],
    [  enable-walu        Enable "walu" extension support])

if test $PHP_WALU != "no"; then
    PHP_SUBST(WALU_SHARED_LIBADD)
    PHP_NEW_EXTENSION(walu, walu.c, $ext_shared)
fi
