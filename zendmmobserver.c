#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "php.h"
#include "ext/standard/info.h"
#include "php_zendmmobserver.h"
#include "zend_portability.h"
#include "Zend/zend_alloc.h"

void malloc_observer(size_t size, void * ptr ZEND_FILE_LINE_DC ZEND_FILE_LINE_ORIG_DC)
{
	printf("Malloc of size %zu at %p\n", size, ptr);
}

void free_observer(void * ptr ZEND_FILE_LINE_DC ZEND_FILE_LINE_ORIG_DC)
{
	printf("Free of %p\n", ptr);
}

void realloc_observer(void *ptr, size_t size, void * new_ptr ZEND_FILE_LINE_DC ZEND_FILE_LINE_ORIG_DC)
{
	printf("Realloc of size %zu at %p (formerly %p)\n", size, new_ptr, ptr);
}

void gc_observer(size_t size)
{
	printf("Garbage collection freed %zu bytes\n", size);
}

void shutdown_observer(bool full, bool silent)
{
	printf("Shutdown happened: full(%d), silent(%d)\n", full, silent);
}

PHP_RINIT_FUNCTION(zendmmobserver)
{
	zend_mm_observer_register(
		NULL,
		malloc_observer,
		free_observer,
		realloc_observer,
		gc_observer,
		shutdown_observer
	);
	return SUCCESS;
}

zend_module_entry zendmmobserver_module_entry = {
	STANDARD_MODULE_HEADER,
	"zendmmobserver",					/* Extension name */
	NULL,					/* zend_function_entry */
	NULL,							/* PHP_MINIT - Module initialization */
	NULL,							/* PHP_MSHUTDOWN - Module shutdown */
	PHP_RINIT(zendmmobserver),			/* PHP_RINIT - Request initialization */
	NULL,							/* PHP_RSHUTDOWN - Request shutdown */
	NULL,			/* PHP_MINFO - Module info */
	PHP_ZENDMMOBSERVER_VERSION,		/* Version */
	STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_ZENDMMOBSERVER
# ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
# endif
ZEND_GET_MODULE(zendmmobserver)
#endif
