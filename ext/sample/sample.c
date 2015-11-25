#include "php_sample.h"
PHP_FUNCTION(sample_hello_world)
{
	zval *arr;
	if( zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,"z",&arr) == FAILURE ){
		RETURN_NULL();
	}
	if(arr->type != IS_ARRAY){
		php_error_docref(NULL TSRMLS_CC, E_ERROR, "not array");
	}
	RETURN_LONG(zend_hash_num_elements(arr->value.ht));
};
PHP_FUNCTION(display_ht)
{
	HashTable *hash;
	Bucket *p = NULL;
	int i;
	if( zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,"H",&hash)==FAILURE ){
		RETURN_NULL();
	}

	for(i=0;i<hash->nTableSize;i++){
		p = hash->arBuckets[i];
		php_printf("arBuckets[%d]",i);
		while(p!=NULL){
			php_printf(" -> %d",p->h);
			p = p->pNext;
		}
		php_printf("\n");
	}
	
}
static inline unsigned int zend_mm_high_bit(size_t _size)
{
#if defined(__GNUC__) && (defined(__native_client__) || defined(i386))
	unsigned int n;

	__asm__("bsrl %1,%0\n\t" : "=r" (n) : "rm"  (_size) : "cc");
	return n;
#elif defined(__GNUC__) && defined(__x86_64__)
	unsigned long n;

        __asm__("bsr %1,%0\n\t" : "=r" (n) : "rm"  (_size) : "cc");
        return (unsigned int)n;
#elif defined(_MSC_VER) && defined(_M_IX86)
	__asm {
		bsr eax, _size
	}
#elif defined(__GNUC__) && (defined(__arm__) ||  defined(__aarch64__))
	return (8 * SIZEOF_SIZE_T - 1) - __builtin_clzl(_size);
#else
	unsigned int n = 0;
	while (_size != 0) {
		_size = _size >> 1;
		n++;
	}
	return n-1;
#endif
}
PHP_FUNCTION(display_mm)
{
	size_t size;
	if( zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,"l",&size)==FAILURE ){
		RETURN_NULL();
	}
	size_t index = zend_mm_high_bit(size);
	php_printf("%ld\n",index);
}
PHP_FUNCTION(function_empty)
{	

}
PHP_FUNCTION(function_emalloc)
{	
	emalloc(32);
}
PHP_FUNCTION(get_ag)
{	
	php_printf("size:%ld\n",AG(mm_heap)->size);
}
static zend_function_entry sample_functions[] = {
	ZEND_FE(sample_hello_world, NULL)
	ZEND_FE(display_ht, NULL)
	ZEND_FE(display_mm, NULL)
	ZEND_FE(function_empty, NULL)
	ZEND_FE(function_emalloc, NULL)
	ZEND_FE(get_ag, NULL)
	{ NULL, NULL, NULL }
};
zend_module_entry sample_module_entry = {
	#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
	#endif
	PHP_SAMPLE_EXTNAME,
	sample_functions, 		/* Functions */
	NULL, 		/* MINIT */
	NULL, 		/* MSHUTDOWN */
	NULL, 		/* RINIT */
	NULL, 		/* RSHUTDOWN */
	NULL, 		/* MINFO */
	#if ZEND_MODULE_API_NO >= 20010901
	PHP_SAMPLE_EXTVER,
	#endif
	STANDARD_MODULE_PROPERTIES
};
#ifdef COMPILE_DL_SAMPLE
	ZEND_GET_MODULE(sample)
#endif
