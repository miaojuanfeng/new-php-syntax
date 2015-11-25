/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2015 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:                                                              |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_mm.h"

/* If you declare any globals in php_mm.h uncomment this:*/
ZEND_DECLARE_MODULE_GLOBALS(mm)


/* True global resources - no need for thread safety here */
static int le_mm;
zend_class_entry *mm_ce;

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("mm.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_mm_globals, mm_globals)
    STD_PHP_INI_ENTRY("mm.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_mm_globals, mm_globals)
PHP_INI_END()
*/
/* }}} */

/* Remove the following function when you have successfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string confirm_mm_compiled(string arg)
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(confirm_mm_compiled)
{
	char *arg = NULL;
	int arg_len, len;
	char *strg;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &arg, &arg_len) == FAILURE) {
		return;
	}

	len = spprintf(&strg, 0, "Congratulations! You have successfully modified ext/%.78s/config.m4. Module %.78s is now compiled into PHP.", "mm", arg);
	RETURN_STRINGL(strg, len, 0);
}
//
PHP_FUNCTION(mm_info)
{
	/*Bucket *p = EG(zend_constants)->pListHead;
	while(p){
		php_printf("%s\n",p->arKey);
		p = p->pListNext;
	}*/
	
	php_printf("name:%s\n",MM_G(name));
	php_printf("age:%ld\n",MM_G(age));
	php_printf("w:%ld\n",MM_G(w));
	php_printf("h:%ld\n",MM_G(h));	


}
/* }}} */
/* The previous line is meant for vim and emacs, so it can correctly fold and 
   unfold functions in source code. See the corresponding marks just before 
   function definition, where the functions purpose is also documented. Please 
   follow this convention for the convenience of others editing your code.
*/


/* {{{ php_mm_init_globals
 */
/* Uncomment this function if you have INI entries*/
static void php_mm_init_globals(zend_mm_globals *mm_globals TSRMLS_DC)
{
	mm_globals->name = estrndup("miaojuanfeng",sizeof("miaojuanfeng"));
	mm_globals->age = 23;
	mm_globals->w = 65;
	mm_globals->h = 175;
}

/* }}} */
PHP_METHOD(mm,__construct){
	php_printf("__construct!!!\n");
}
PHP_METHOD(mm,__destruct){
	php_printf("__destruct!!!\n");
}
PHP_METHOD(mm,index){
	php_printf("index!!!\n");
	/*zend_class_entry **ce;
	if(zend_hash_find(EG(class_table),"ci",sizeof("ci"),(void**)&ce)==FAILURE){
		RETURN_NULL();
	}
	Bucket *p = (*ce)->function_table.pListHead;
	while(p){
		php_printf("%s\t",p->arKey);
		php_printf("__construct:%p\n",p->pData);
		p = p->pListNext;
	}
	php_printf("index!!!\n");
	php_printf("__construct:%p\n",(*ce)->constructor);*/
    	zend_class_entry *ce;
	ce = Z_OBJCE_P(getThis());
	zend_update_property_long(mm_ce, getThis(), ZEND_STRL("mmobject"), 100 TSRMLS_CC);
	//
	zend_class_entry **td;
	if(zend_hash_find(EG(class_table),"stdclass",sizeof("stdclass"),(void**)&td) == FAILURE){
		php_printf("none!\n");
	}
	zval *ob;
	MAKE_STD_ZVAL(ob);
	object_init_ex(ob,*td);
	zend_update_property(mm_ce, getThis(), ZEND_STRL("mmobject"), ob TSRMLS_CC);
	
	compile_file(NULL,0 TSRMLS_CC);
}
const zend_function_entry mm_method_functions[] = {
	PHP_ME(mm,__construct,NULL,ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
	PHP_ME(mm,__destruct,NULL,ZEND_ACC_PUBLIC | ZEND_ACC_DTOR)
	PHP_ME(mm,index,NULL,ZEND_ACC_PUBLIC)
	PHP_FE_END
};

/* {{{ PHP_MINIT_FUNCTION
 */

PHP_MINIT_FUNCTION(mm)
{
	/* If you have INI entries, uncomment these lines 
	REGISTER_INI_ENTRIES();
	*/
	ZEND_INIT_MODULE_GLOBALS(mm,(ts_allocate_ctor)php_mm_init_globals,NULL);

	zend_class_entry ce;
	INIT_CLASS_ENTRY(ce,"CI",mm_method_functions);
	mm_ce = zend_register_internal_class(&ce TSRMLS_CC);

	zend_declare_property_bool(mm_ce,ZEND_STRL("running"),1,ZEND_ACC_PUBLIC TSRMLS_CC);

	zend_declare_property_null(mm_ce,ZEND_STRL("mmobject"),ZEND_ACC_PUBLIC TSRMLS_CC);
		
	//REGISTER_STRINGL_CONSTANT("JEFF","miaojuanfeng",sizeof("miaojuanfeng")-1,CONST_PERSISTENT | CONST_CS);	
	

	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(mm)
{
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(mm)
{
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(mm)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(mm)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "mm support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */

/* {{{ mm_functions[]
 *
 * Every user visible function must have an entry in mm_functions[].
 */
const zend_function_entry mm_functions[] = {
	PHP_FE(confirm_mm_compiled,	NULL)		/* For testing, remove later. */
	PHP_FE(mm_info,	NULL)
	PHP_FE_END	/* Must be the last line in mm_functions[] */
};
/* }}} */

/* {{{ mm_module_entry
 */
zend_module_entry mm_module_entry = {
	STANDARD_MODULE_HEADER,
	"mm",
	mm_functions,
	PHP_MINIT(mm),
	PHP_MSHUTDOWN(mm),
	PHP_RINIT(mm),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(mm),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(mm),
	PHP_MM_VERSION,
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_MM
ZEND_GET_MODULE(mm)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
