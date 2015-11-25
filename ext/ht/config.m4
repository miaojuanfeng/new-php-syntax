PHP_ARG_ENABLE(
	ht,
	[Whether to enable the "ht" extension],
	[ enable-ht Enable "ht" extension support]
)
if test $PHP_HT != "no"; then
	PHP_SUBST(HT_SHARED_LIBADD)
	PHP_NEW_EXTENSION(ht, ht.c, $ext_shared)
fi
