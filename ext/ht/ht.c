#include "php_ht.h"

#define HASH_INDEX(ht,key) _ht_hash_index(key) % ht->size
typedef struct _HT_Bucket
{
	char *key;
	void *value;
	Bucket *next;
}HT_Bucket;
typedef struct _HT_HashTable
{
	int size;
	HT_Bucket *buckets;
}HT_HashTable;
static int _ht_hash_index(char *key){
	int sum = 0;
	char *cur = key;	
	while(*cur != '\0') sum += *cur++;
	return sum;
}
void parse_va_args(int n,...)
{
	va_list ap;
	int p;
	int i;
	va_start(ap,n);
	for(i=0;i<n;i++)
	{
		p = va_arg(ap,int);
		php_printf("%c\n",p);
	}
	va_end(ap);
}
PHP_FUNCTION(va_test)
{
	parse_va_args(3,'c','a','b');
}
PHP_FUNCTION(ht)
{
	/*char *s;
	long s_l;
	int sum = 0;
	if( zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,"s",&s,&s_l) == FAILURE ){
		RETURN_NULL();
	}
	HT_HashTable *ht_ht;
	ht_ht->size = 5;
	ht_ht->buckets = (HT_Bucket*)calloc(ht_ht->size,sizeof(HT_Bucket));
	php_printf("%d\n",HASH_INDEX(ht_ht,s));*/

	zval *arr;
	Bucket *p;
	zval **pData;
	if( zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,"a",&arr) == FAILURE ){
		RETURN_NULL();
	}
	if( arr->type == IS_ARRAY ){
		/*printf("%d\n",arr->value.ht->nNumOfElements);
		zend_hash_move_forward(arr->value.ht);
		data = arr->value.ht->pInternalPointer;
		printf("%d\n",data->h);*/
		p = arr->value.ht->pInternalPointer;
		while(p){
			if( p->nKeyLength == 0 )
				php_printf("%ld",p->h);
			else
				php_printf("%s",p->arKey);
			pData = (zval**)p->pData;
			php_printf("=>");
			if( (*pData)->type == IS_STRING )
				PHPWRITE(Z_STRVAL_P(*pData),Z_STRLEN_P(*pData));
			else if( (*pData)->type == IS_LONG )
				php_printf("%ld",Z_LVAL_P(*pData));			
			php_printf("\n");
			p = p->pListNext;
		}
	}
}
PHP_FUNCTION(strtolong)
{
	char *str;
	long len;
	if( zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,"s",&str,&len) == FAILURE ){
		RETURN_NULL();
	}
	RETURN_LONG(strtol(str,NULL,10));
}
PHP_FUNCTION(longtostr)
{
	/*long l;
	char s[100];
	long sl;
	if( zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,"l",&l) == FAILURE ){
		RETURN_NULL();
	}
	sl = sprintf(s,"%d",(long)l);
	RETURN_STRING(s,strlen(s));*/
}
PHP_FUNCTION(hash_index)
{
	HashTable *Ht;
	long lh = 0;
	if( zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,"H",&Ht) == FAILURE ){
		RETURN_NULL();
	}
	Bucket *p = Ht->pListHead;
	while(p!=NULL){
		lh = zend_inline_hash_func(p->arKey,p->nKeyLength);
		php_printf("hash=>%ld --- %s=>%ld\n",lh,p->arKey,p->h);
		p = p->pListNext;
	}
}
PHP_FUNCTION(refcount){
	zval **z;
	if( _zend_get_parameters_array_ex(ZEND_NUM_ARGS(), &z TSRMLS_CC) == FAILURE ){
		RETURN_NULL();
	}
	php_printf("refcount__gc:%d\nis_ref__gc:%d\n",(*z)->refcount__gc,(*z)->is_ref__gc);
}
PHP_FUNCTION(GetAllFunc){
	/*Bucket *p;
	p = EG(function_table)->pListHead;
	while(p!=NULL){
		php_printf("%s == ",p->arKey);
		p = p->pListNext;
	}
	php_printf("total = %d\n",EG(function_table)->nNumOfElements);
RETURN_NULL();*/
	zend_function *f = NULL;
	zend_hash_find(EG(function_table),"GetName",strlen("GetName")+1,(void**)&f);
	php_printf("%s\n",(f)->op_array.function_name);
RETURN_NULL();
	/*
	//
	p = EG(symbol_table).pListHead;
	while(p!=NULL){
		php_printf("%s == ",p->arKey);
		p = p->pListNext;
	}
	php_printf("total = %d\n",EG(symbol_table).nNumOfElements);
	//
	p = EG(active_symbol_table)->pListHead;
	while(p!=NULL){
		php_printf("%s == ",p->arKey);
		p = p->pListNext;
	}
	php_printf("total = %d\n",EG(active_symbol_table)->nNumOfElements);
	//
	p = EG(zend_constants)->pListHead;
	while(p!=NULL){
		php_printf("%s == ",p->arKey);
		p = p->pListNext;
	}
	php_printf("total = %d\n",EG(zend_constants)->nNumOfElements);*/
	/*if(EG(active_op_array)->static_variables == NULL) php_printf("NULL");
	p = EG(active_op_array)->static_variables->pListHead;
	while(p!=NULL){
		php_printf("%s == ",p->arKey);
		p = p->pListNext;
	}
	php_printf("total = %d\n",EG(active_op_array)->static_variables->nNumOfElements);
	/*zend_function *f = NULL;
	zend_hash_find(EG(function_table),"aa",strlen("aa")+1,(void**)&f);
	if(f==NULL) php_printf("NULL");
	printf("%d\n",f->internal_function.type);
printf("%d\n",ZEND_USER_FUNCTION);
	PHPWRITE(f->internal_function.function_name,strlen("aa")+1);
	/*zval *val;
	val = (zval*)emalloc(sizeof(zval));
	val->type = IS_LONG;
	val->value.lval = 100;
	val->refcount__gc = 1;
	val->is_ref__gc = 0;
	zend_hash_add(&EG(symbol_table),"miaojuanfeng",strlen("miaojuanfeng")+1, &val, sizeof(zval *), NULL);
	zval **z = NULL;
	zend_hash_find(&EG(symbol_table),"miaojuanfeng",strlen("miaojuanfeng")+1,(void**)&z);
	if(z==NULL) php_printf("null\n");
	php_printf("%ld\n",(*z)->value.lval);*/
	zend_op *op = EG(active_op_array)->opcodes;
	//printf("%d\n",EG(active_op_array)->last);
	//printf("%d\n",(*op)->opcode);
	//(*op)++;
	int i;
printf("IS_BOOL:%d\n",IS_BOOL);
printf("IS_LONG:%d\n",IS_LONG);
printf("IS_DOUBLE:%d\n",IS_DOUBLE);
printf("IS_NULL:%d\n",IS_NULL);
printf("IS_STRING:%d\n",IS_STRING);
printf("IS_ARRAY:%d\n",IS_ARRAY);
printf("IS_OBJECT:%d\n",IS_OBJECT);
	for(i=0;i<EG(active_op_array)->last;i++)
	{	
		php_printf("opcode:%d - ",op->opcode);
		php_printf("op1_type:%d - ",op->op1_type);
php_printf("op1.var:%d - ",op->op1.var);
php_printf("op1.constant:%d - ",op->op1.constant);
php_printf("op1.num:%d - ",op->op1.num);
php_printf("op1.hash:%d - ",op->op1.hash);
		php_printf("op1->zv:");
		if(op->op1_type!=16&&op->op1_type!=8){
			switch(op->op1.zv->type){
			case IS_BOOL:
			case IS_LONG:
				php_printf("%ld",op->op1.zv->value.lval);
				break;
			case IS_DOUBLE:
			case IS_STRING:
				PHPWRITE(op->op1.zv->value.str.val,op->op1.zv->value.str.len);
				break;
			case IS_NULL:
			default:
				php_printf("unknow");
			}
		}
		php_printf(" - ");
		php_printf("op2_type:%d - ",op->op2_type);
php_printf("op2.var:%d - ",op->op2.var);
php_printf("op2.constant:%d - ",op->op2.constant);
php_printf("op2.num:%d - ",op->op2.num);
php_printf("op2.hash:%d - ",op->op2.hash);
		php_printf("op2->zv:");
		if(op->op2_type!=16&&op->op2_type!=8){
			switch(op->op2.zv->type){
			case IS_BOOL:
			case IS_LONG:
				php_printf("%ld",op->op2.zv->value.lval);
				break;
			case IS_DOUBLE:
			case IS_STRING:
				PHPWRITE(op->op2.zv->value.str.val,op->op2.zv->value.str.len);
				break;
			case IS_NULL:
			default:
				php_printf("unknow");
			}
		}
		php_printf(" - ");
		php_printf("result_type:%d",op->result_type);
		php_printf("\n");
		op++;
	}
}
PHP_FUNCTION(echo_globals){
	Bucket *p;
	p = EG(active_symbol_table)->pListHead;
	while(p!=NULL){
		php_printf("%s == ",p->arKey);
		p = p->pListNext;
	}
	php_printf("total = %d\n",EG(active_symbol_table)->nNumOfElements);
}
static zend_function_entry ht_functions[] = {
	ZEND_FE(ht,NULL)
	ZEND_FE(va_test,NULL)
	ZEND_FE(strtolong,NULL)
	ZEND_FE(longtostr,NULL)
	ZEND_FE(hash_index,NULL)
	ZEND_FE(refcount,NULL)
	ZEND_FE(GetAllFunc,NULL)
	ZEND_FE(echo_globals,NULL)
	{ NULL, NULL, NULL }
};
zend_module_entry ht_module_entry = {
	#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
	#endif
	PHP_HT_EXTNAME,
	ht_functions, 		/* Functions */
	NULL, 		/* MINIT */
	NULL, 		/* MSHUTDOWN */
	NULL, 		/* RINIT */
	NULL, 		/* RSHUTDOWN */
	NULL, 		/* MINFO */
	#if ZEND_MODULE_API_NO >= 20010901
	PHP_HT_EXTVER,
	#endif
	STANDARD_MODULE_PROPERTIES
};
#ifdef COMPILE_DL_HT
	ZEND_GET_MODULE(ht)
#endif
