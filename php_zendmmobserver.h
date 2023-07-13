/* zendmmobserver extension for PHP */

#ifndef PHP_ZENDMMOBSERVER_H
# define PHP_ZENDMMOBSERVER_H

extern zend_module_entry zendmmobserver_module_entry;
# define phpext_zendmmobserver_ptr &zendmmobserver_module_entry

# define PHP_ZENDMMOBSERVER_VERSION "0.1.0"

# if defined(ZTS) && defined(COMPILE_DL_ZENDMMOBSERVER)
ZEND_TSRMLS_CACHE_EXTERN()
# endif

#endif	/* PHP_ZENDMMOBSERVER_H */
