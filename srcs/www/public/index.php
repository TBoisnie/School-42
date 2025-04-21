<?php

// Session
$session_cookie_params = session_get_cookie_params();
$session_cookie_params['samesite'] = "Lax";
session_set_cookie_params($session_cookie_params);

session_start();

// Globally define root folder of the application
define('ROOT', dirname(__DIR__).DIRECTORY_SEPARATOR.'src');

// Autoloading
require join(DIRECTORY_SEPARATOR, [ ROOT, 'core', 'Autoloader.php' ]);
\Core\Autoloader::enable();

// Page
echo \Core\Router::getPage();
