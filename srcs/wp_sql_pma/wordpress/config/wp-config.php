<?php
/**
 * The base configuration for WordPress
 *
 * The wp-config.php creation script uses this file during the
 * installation. You don't have to use the web site, you can
 * copy this file to "wp-config.php" and fill in the values.
 *
 * This file contains the following configurations:
 *
 * * MySQL settings
 * * Secret keys
 * * Database table prefix
 * * ABSPATH
 *
 * @link https://wordpress.org/support/article/editing-wp-config-php/
 *
 * @package WordPress
 */

// ** MySQL settings - You can get this info from your web host ** //
define('WP_SITEURL', 'http://'.$_SERVER['HTTP_HOST']);
define('WP_HOME',	 'http://'.$_SERVER['HTTP_HOST']);

/** The name of the database for WordPress */
define( 'DB_NAME', "_k8s_wp_db_name_");

/** MySQL database username */
define( 'DB_USER', "_k8s_wp_db_user_");

/** MySQL database password */
define( 'DB_PASSWORD', "_k8s_wp_db_pass_");

/** MySQL hostname */
define( 'DB_HOST', "_k8s_wp_db_host_");


/** Database Charset to use in creating database tables. */
define( 'DB_CHARSET', 'utf8' );

/** The Database Collate type. Don't change this if in doubt. */
define( 'DB_COLLATE', '' );

/**#@+
 * Authentication Unique Keys and Salts.
 *
 * Change these to different unique phrases!
 * You can generate these using the {@link https://api.wordpress.org/secret-key/1.1/salt/ WordPress.org secret-key service}
 * You can change these at any point in time to invalidate all existing cookies. This will force all users to have to log in again.
 *
 * @since 2.6.0
 */
define('AUTH_KEY',         'r#kD/v_TC-`=|^e7F]OQ7*}*CbcE6%]-N&Gfol[w7lx8=OUv|k_-Lgm*2];FAJ_k');
define('SECURE_AUTH_KEY',  'c[OvkdZXNNb@?11_=hMl)n05tFq[`]K;saJVn7ylsaB|L0/?d^foH9`xzUt C-~0');
define('LOGGED_IN_KEY',    'fMBc7k==3lJUc47,CsJBHIz=YpBtx5H`cP~%qHCB44=Ss:p+glMsPdCBg-lM)[+K');
define('NONCE_KEY',        '#`2]4y6}EcR-a++0*B+%b*9Fjmntv*06SR#P.DyzA?@nUJ$-{ay3}|v;pZHzpNZi');
define('AUTH_SALT',        ']dBo>l+4mNMThcx,=E!?W,:f5k(dgnoqpt`gO{[I[kg9cTd{*M|K0>,5{Z^),n}+');
define('SECURE_AUTH_SALT', '(}-j-#;3[,,*}{Kc9lOCq@*La;pEp>rB$MY+F|?2Ha{T=}kxG_-y:6h[D%5v|<y*');
define('LOGGED_IN_SALT',   '|&>bKutvQn[P3,.R&[+>|P+??fQhR|(n8g=.e>O8LymT&?uR2/Q+-O_V>NEgl%U ');
define('NONCE_SALT',       '<MiId;TG rT&+Ul8a~$y4z8_E_dME~Ey-MG=-q/R+z2zBij9k?n`~Zn][Y-,U;x8');

/**#@-*/

/**
 * WordPress Database Table prefix.
 *
 * You can have multiple installations in one database if you give each
 * a unique prefix. Only numbers, letters, and underscores please!
 */
$table_prefix = 'wp_';

/**
 * For developers: WordPress debugging mode.
 *
 * Change this to true to enable the display of notices during development.
 * It is strongly recommended that plugin and theme developers use WP_DEBUG
 * in their development environments.
 *
 * For information on other constants that can be used for debugging,
 * visit the documentation.
 *
 * @link https://wordpress.org/support/article/debugging-in-wordpress/
 */
define( 'WP_DEBUG', false );

/* That's all, stop editing! Happy publishing. */

/** Absolute path to the WordPress directory. */
if ( ! defined( 'ABSPATH' ) ) {
	define( 'ABSPATH', __DIR__ . '/' );
}

/** Sets up WordPress vars and included files. */
require_once ABSPATH . 'wp-settings.php';
