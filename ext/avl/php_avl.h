#ifndef PHP_AVL_H
	#define PHP_AVL_H
	#define PHP_AVL_EXTNAME "avl"
	#define PHP_AVL_EXTVER "1.0"
	#ifdef HAVE_CONFIG_H
		#include "config.h"
	#endif
	#include "php.h"
	extern zend_module_entry avl_module_entry;
	#define phpext_avl_ptr &avl_module_entry
#endif
