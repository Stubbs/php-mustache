
#ifndef MUSTACHE_TEMPLATE_HPP
#define MUSTACHE_TEMPLATE_HPP

#include "php_mustache.hpp"


static zend_class_entry * MustacheTemplate_ce_ptr = NULL;


typedef struct _php_obj_MustacheTemplate {
    zend_object obj;
    mustache::Node * node;
} php_obj_MustacheTemplate;


PHP_MINIT_FUNCTION(mustache_template);


PHP_METHOD(MustacheTemplate, render);
ZEND_BEGIN_ARG_INFO_EX(MustacheTemplate__render_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
        ZEND_ARG_INFO(0, vars)
        ZEND_ARG_INFO(0, partials)
ZEND_END_ARG_INFO()


#endif

