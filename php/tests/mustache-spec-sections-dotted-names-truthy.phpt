--TEST--
Dotted Names - Truthy
--DESCRIPTION--
Dotted names should be valid for Section tags.
--SKIPIF--
<?php if(!extension_loaded('mustache')) die('skip '); ?>
--FILE--
<?php
$test = array (
  'name' => 'Dotted Names - Truthy',
  'data' => 
  array (
    'a' => 
    array (
      'b' => 
      array (
        'c' => true,
      ),
    ),
  ),
  'expected' => '"Here" == "Here"',
  'template' => '"{{#a.b.c}}Here{{/a.b.c}}" == "Here"',
  'desc' => 'Dotted names should be valid for Section tags.',
);
$mustache = new Mustache();
echo $mustache->render($test["template"], $test["data"]);
?>
--EXPECTREGEX--
"Here"\s+\=\=\s+"Here"