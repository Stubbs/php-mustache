
#include "php_mustache.hpp"

// Mustache Class Method Entries -----------------------------------------------

static zend_function_entry Mustache_methods[] = {
  PHP_ME(Mustache, __construct, Mustache____construct_args, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
  PHP_ME(Mustache, getEscapeByDefault, Mustache__getEscapeByDefault_args, ZEND_ACC_PUBLIC)
  PHP_ME(Mustache, getStartSequence, Mustache__getStartSequence_args, ZEND_ACC_PUBLIC)
  PHP_ME(Mustache, getStopSequence, Mustache__getStopSequence_args, ZEND_ACC_PUBLIC)
  PHP_ME(Mustache, setEscapeByDefault, Mustache__setEscapeByDefault_args, ZEND_ACC_PUBLIC)
  PHP_ME(Mustache, setStartSequence, Mustache__setStartSequence_args, ZEND_ACC_PUBLIC)
  PHP_ME(Mustache, setStopSequence, Mustache__setStopSequence_args, ZEND_ACC_PUBLIC)
  PHP_ME(Mustache, compile, Mustache__compile_args, ZEND_ACC_PUBLIC)
  PHP_ME(Mustache, tokenize, Mustache__tokenize_args, ZEND_ACC_PUBLIC)
  PHP_ME(Mustache, render, Mustache__render_args, ZEND_ACC_PUBLIC)
  PHP_ME(Mustache, debugDataStructure, Mustache__debugDataStructure_args, ZEND_ACC_PUBLIC)
  { NULL, NULL, NULL }
};

static zend_object_handlers Mustache_obj_handlers;

static void Mustache_obj_free(void *object TSRMLS_DC)
{
  php_obj_Mustache *payload = (php_obj_Mustache *)object;

  mustache::Mustache * mustache = payload->mustache;

  delete mustache;

  efree(object);
}

static zend_object_value Mustache_obj_create(zend_class_entry *class_type TSRMLS_DC)
{
  php_obj_Mustache *payload;
  zval *tmp;
  zend_object_value retval;

  payload = (php_obj_Mustache *)emalloc(sizeof(php_obj_Mustache));
  memset(payload, 0, sizeof(php_obj_Mustache));
  payload->obj.ce = class_type;

  payload->mustache = new mustache::Mustache;

  retval.handle = zend_objects_store_put(payload, NULL, (zend_objects_free_object_storage_t) Mustache_obj_free, NULL TSRMLS_CC);
  retval.handlers = &Mustache_obj_handlers;

  return retval;
}

static void class_init_Mustache(void)
{
  zend_class_entry ce;

  INIT_CLASS_ENTRY(ce, "Mustache", Mustache_methods);
  ce.create_object = Mustache_obj_create;
  Mustache_ce_ptr = zend_register_internal_class(&ce);
  memcpy(&Mustache_obj_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
  Mustache_obj_handlers.clone_obj = NULL;
}

// MustacheTemplate Class Method Entries ---------------------------------------

static zend_function_entry MustacheTemplate_methods[] = {
  //PHP_ME(MustacheTemplate, __construct, MustacheTemplate____construct_args, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
  PHP_ME(MustacheTemplate, render, MustacheTemplate__render_args, ZEND_ACC_PUBLIC)
  { NULL, NULL, NULL }
};

static zend_object_handlers MustacheTemplate_obj_handlers;

void MustacheTemplate_obj_free(void *object TSRMLS_DC)
{
  php_obj_MustacheTemplate *payload = (php_obj_MustacheTemplate *)object;

  mustache::Node * node = payload->node;

  cout << "FREEING" << endl;
  if( node != NULL ) {
  cout << "FREEING NOT NULL" << endl;
    delete node;
  }

  efree(object);
}

zend_object_value MustacheTemplate_obj_create(zend_class_entry *class_type TSRMLS_DC)
{
  return MustacheTemplate_obj_create_ex(class_type, new mustache::Node);
}

zend_object_value MustacheTemplate_obj_create_ex(zend_class_entry *class_type, mustache::Node * node TSRMLS_DC)
{
  php_obj_MustacheTemplate *payload;
  zval *tmp;
  zend_object_value retval;

  payload = (php_obj_MustacheTemplate *)emalloc(sizeof(php_obj_MustacheTemplate));
  memset(payload, 0, sizeof(php_obj_MustacheTemplate));
  payload->obj.ce = class_type;

  payload->node = node;

  retval.handle = zend_objects_store_put(payload, NULL, (zend_objects_free_object_storage_t) MustacheTemplate_obj_free, NULL TSRMLS_CC);
  retval.handlers = &MustacheTemplate_obj_handlers;

  return retval;
}

void class_init_MustacheTemplate(void)
{
  zend_class_entry ce;

  INIT_CLASS_ENTRY(ce, "MustacheTemplate", MustacheTemplate_methods);
  ce.create_object = MustacheTemplate_obj_create;
  MustacheTemplate_ce_ptr = zend_register_internal_class(&ce);
  memcpy(&MustacheTemplate_obj_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
  MustacheTemplate_obj_handlers.clone_obj = NULL;
}

// Module Entry ----------------------------------------------------------------

zend_module_entry mustache_module_entry = {
  STANDARD_MODULE_HEADER,
  PHP_MUSTACHE_NAME,        // Define PHP extension name  
  NULL,        /* Functions */  
  PHP_MINIT(mustache),        /* MINIT */  
  NULL,        /* MSHUTDOWN */  
  NULL,        /* RINIT */  
  NULL,        /* RSHUTDOWN */  
  PHP_MINFO(mustache),        /* MINFO */  
  PHP_MUSTACHE_VERSION,
  STANDARD_MODULE_PROPERTIES  
};  

#ifdef COMPILE_DL_MUSTACHE 
extern "C" {
  ZEND_GET_MODULE(mustache)      // Common for all PHP extensions which are build as shared modules  
}
#endif

// MINIT -----------------------------------------------------------------------
  
PHP_MINIT_FUNCTION(mustache)
{
  class_init_Mustache();
  class_init_MustacheTemplate();
  return SUCCESS;
}

// MINFO -----------------------------------------------------------------------
  
PHP_MINFO_FUNCTION(mustache)
{
  php_info_print_table_start();
  php_info_print_table_row(2, "Version", PHP_MUSTACHE_VERSION);
  php_info_print_table_row(2, "Released", PHP_MUSTACHE_RELEASE);
  php_info_print_table_row(2, "Revision", PHP_MUSTACHE_BUILD);
  php_info_print_table_row(2, "Authors", PHP_MUSTACHE_AUTHORS);
  php_info_print_table_end();
  /* add your stuff here */

}
