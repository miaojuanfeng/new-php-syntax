PHP_ARG_ENABLE(
	class,
	[Whether to enable the "class" extension],
	[ enable-class Enable "class" extension support]
)
if test $PHP_CLASS != "no"; then
	PHP_SUBST(CLASS_SHARED_LIBADD)
	PHP_NEW_EXTENSION(class, class.c, $ext_shared)
fi
