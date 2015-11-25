#ifndef PHP_CLASS_H
	#define PHP_CLASS_H
	#define PHP_CLASS_EXTNAME "class"
	#define PHP_CLASS_EXTVER "1.0"
	#ifdef HAVE_CONFIG_H
		#include "config.h"
	#endif
	#include "php.h"
	extern zend_module_entry class_module_entry;
	#define phpext_class_ptr &class_module_entry
#endif
