#ifndef PHP_HT_H
	#define PHP_HT_H
	#define PHP_HT_EXTNAME "ht"
	#define PHP_HT_EXTVER "1.0"
	#ifdef HAVE_CONFIG_H
		#include "config.h"
	#endif
	#include "php.h"
	extern zend_module_entry ht_module_entry;
	#define phpext_ht_ptr &ht_module_entry
#endif
