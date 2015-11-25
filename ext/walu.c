//加载config.h，如果配置了的话
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
 
//加载php头文件
#include "php.h"
 
 
#define phpext_walu_ptr &walu_module_entry

ZEND_FUNCTION(walu_hello)
{
    php_printf("Hello World!\n");
}
 
static zend_function_entry walu_functions[] = {
    ZEND_FE(walu_hello,        NULL)
    { NULL, NULL, NULL }
};
 
//module entry
zend_module_entry walu_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
     STANDARD_MODULE_HEADER,
#endif
    "walu", //这个地方是扩展名称，往往我们会在这个地方使用一个宏。
    NULL, /* Functions */
    NULL, /* MINIT */
    NULL, /* MSHUTDOWN */
    NULL, /* RINIT */
    NULL, /* RSHUTDOWN */
    NULL, /* MINFO */
#if ZEND_MODULE_API_NO >= 20010901
    "2.1", //这个地方是我们扩展的版本
#endif
    STANDARD_MODULE_PROPERTIES
};
 
#ifdef COMPILE_DL_WALU
ZEND_GET_MODULE(walu)
#endif
