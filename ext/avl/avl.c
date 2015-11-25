#include "php_avl.h"
PHP_FUNCTION(class_data){
	zend_class_entry **ce = NULL;
	zend_hash_find(EG(class_table),"person",strlen("person")+1,(void**)&ce);
	if(ce == NULL) php_printf("class null\n");
	php_printf("----------class:%s----------\n",(*ce)->name);
	Bucket *p = (*ce)->properties_info.pListHead;
	zend_property_info *pro;
	php_printf("properties:\n");
	while(p!=NULL){
		pro = p->pData;
		php_printf("(%d)",pro->flags);
		PHPWRITE(pro->name,pro->name_length);
		php_printf(":");
		switch(Z_TYPE_P((*ce)->default_properties_table[pro->offset])){
			case IS_STRING:
				php_printf("%s",Z_STRVAL_P((*ce)->default_properties_table[pro->offset]));
				break;
			case IS_LONG:
				php_printf("%ld",Z_LVAL_P((*ce)->default_properties_table[pro->offset]));
				break;
			default:break;
		}
		php_printf("\n");
		p = p->pListNext;
	}
}
PHP_FUNCTION(execute_data)
{
	zend_op_array *op_array = EG(current_execute_data)->op_array;
	zend_op *op;
	int i;
	for(i=0,op=op_array->opcodes;i<op_array->last;i++){
		printf("opcode:%d\top1_type:%d\top2_type:%d\tresult_type:%d\n",op->opcode,op->op1_type,op->op2_type,op->result_type);
		php_printf("aaa\n");
		php_printf("result:%ld\n",op->result.var);
		op++;
	}
}
PHP_FUNCTION(avl)
{
	HashTable *h;
	Bucket *p;
	int i;
	if( zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,"H",&h) == FAILURE ){
		RETURN_NULL();
	}
	php_printf("----------------\n");
	php_printf("nNumOfElements:%d\n",h->nNumOfElements);
	php_printf("nTableSize:%d\n",h->nTableSize);
	php_printf("h:%ld\n",h->pListHead->h);
	php_printf("----------------\n");
	for(i=0;i<h->nTableSize;i++){
		p = h->arBuckets[i];
		if(p==NULL){
			php_printf("null\n");
		}else{
			while(p!=NULL){
				php_printf("%ld -> ",p->h);
				p = p->pNext;
			}
			php_printf("null\n");
		}
	}
}
PHP_FUNCTION(arg)
{
	zend_function *f = EG(current_execute_data)->prev_execute_data->function_state.function;
	void **p = EG(current_execute_data)->prev_execute_data->function_state.arguments;
	php_printf("%d\n",(int) **p);
	php_printf("%s\n",f->common.function_name);
	
}
static zend_function_entry avl_functions[] = {
	ZEND_FE(avl,NULL)
	ZEND_FE(execute_data,NULL)
	ZEND_FE(class_data,NULL)
	ZEND_FE(arg,NULL)
	{ NULL, NULL, NULL }
};
zend_module_entry avl_module_entry = {
	#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
	#endif
	PHP_AVL_EXTNAME,
	avl_functions, 		/* Functions */
	NULL, 		/* MINIT */
	NULL, 		/* MSHUTDOWN */
	NULL, 		/* RINIT */
	NULL, 		/* RSHUTDOWN */
	NULL, 		/* MINFO */
	#if ZEND_MODULE_API_NO >= 20010901
	PHP_AVL_EXTVER,
	#endif
	STANDARD_MODULE_PROPERTIES
};
#ifdef COMPILE_DL_AVL
	ZEND_GET_MODULE(avl)
#endif
