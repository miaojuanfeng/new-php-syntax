#include "php_class.h"
PHP_FUNCTION(get_class_info)
{
	zend_class_entry **c = NULL;
	zend_hash_find(EG(class_table),"person",strlen("person")+1,(void**)&c);
	if(c==NULL){
		php_printf("c is null\n");
		return;	
	}
	php_printf("------------Class Info-------------\n");
	php_printf("ZEND_INTERNAL_CLASS:%d\n",ZEND_INTERNAL_CLASS);
	php_printf("ZEND_USER_CLASS:%d\n",ZEND_USER_CLASS);
	php_printf("ZEND_ACC_IMPLICIT_ABSTRACT_CLASS:%d\n",ZEND_ACC_IMPLICIT_ABSTRACT_CLASS);
    	php_printf("ZEND_ACC_EXPLICIT_ABSTRACT_CLASS:%d\n",ZEND_ACC_EXPLICIT_ABSTRACT_CLASS);
    	php_printf("ZEND_ACC_FINAL_CLASS:%d\n",ZEND_ACC_FINAL_CLASS);
    	php_printf("ZEND_ACC_INTERFACE:%d\n",ZEND_ACC_INTERFACE);
	php_printf("------------Class Info-------------\n");
	php_printf("type:%d\n",(*c)->type);
	php_printf("name:");PHPWRITE((*c)->name,(*c)->name_length);php_printf("\n");
	php_printf("ce_flags:%d\n",(*c)->ce_flags);
	//function
	Bucket *p = (*c)->function_table.pListHead;
	zend_function *f = NULL;
	while(p!=NULL){
		f = p->pData;
		php_printf("function:%s\n",(f)->op_array.function_name);
		p = p->pListNext;
	}
	//constant
	p = (*c)->constants_table.pListHead;
	while(p!=NULL){
		php_printf("constant:%s\n",(p)->arKey);
		p = p->pListNext;
	}
	//default_properties_table
	zval **properties = (*c)->default_properties_table;
	int i;
	for(i=0;i<(*c)->default_properties_count;i++){
		switch(Z_TYPE_PP(properties)){
			case IS_LONG:
				php_printf("properties:%d\n",Z_LVAL_PP(properties));
				break;
			case IS_STRING:
				php_printf("properties:");
				PHPWRITE(Z_STRVAL_PP(properties),Z_STRLEN_PP(properties));
				php_printf("\n");
				break;
		}
		
		properties++;
	}
	//static_members_table
	zval **static_members = (*c)->static_members_table;
	for(i=0;i<(*c)->default_static_members_count;i++){
		switch(Z_TYPE_PP(static_members)){
			case IS_LONG:
				php_printf("static_members:%d\n",Z_LVAL_PP(static_members));
				break;
			case IS_STRING:
				php_printf("static_members:");
				PHPWRITE(Z_STRVAL_PP(static_members),Z_STRLEN_PP(static_members));
				php_printf("\n");
				break;
		}
		static_members++;
	}
}
static zend_function_entry class_functions[] = {
	ZEND_FE(get_class_info,NULL)
	{ NULL, NULL, NULL }
};
zend_module_entry class_module_entry = {
	#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
	#endif
	PHP_CLASS_EXTNAME,
	class_functions, 		/* Functions */
	NULL, 		/* MINIT */
	NULL, 		/* MSHUTDOWN */
	NULL, 		/* RINIT */
	NULL, 		/* RSHUTDOWN */
	NULL, 		/* MINFO */
	#if ZEND_MODULE_API_NO >= 20010901
	PHP_CLASS_EXTVER,
	#endif
	STANDARD_MODULE_PROPERTIES
};
#ifdef COMPILE_DL_CLASS
	ZEND_GET_MODULE(class)
#endif
