#ifndef PHP_SAMPLE_H
	#define PHP_SAMPLE_H
	#define PHP_SAMPLE_EXTNAME "sample"
	#define PHP_SAMPLE_EXTVER "1.0"
	#ifdef HAVE_CONFIG_H
		#include "config.h"
	#endif
	#include "php.h"
	extern zend_module_entry sample_module_entry;
	#define phpext_sample_ptr &sample_module_entry
#endif
