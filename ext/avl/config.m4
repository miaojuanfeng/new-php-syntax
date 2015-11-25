PHP_ARG_ENABLE(
	avl,
	[Whether to enable the "avl" extension],
	[ enable-avl Enable "avl" extension support]
)
if test $PHP_AVL != "no"; then
	PHP_SUBST(AVL_SHARED_LIBADD)
	PHP_NEW_EXTENSION(avl, avl.c, $ext_shared)
fi
