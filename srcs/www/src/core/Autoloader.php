<?php

namespace Core;


final class Autoloader
{

	public static function enable() : void
	{
		spl_autoload_register([static::class, 'load']);
	}

	public static function disable() : void
	{
		spl_autoload_unregister([static::class, 'load']);
	}

	private static function load($namespaced_class) : void
	{
		$file = static::toFilePath($namespaced_class);

		if (file_exists($file))
		{
			require $file;
		}
	}

	private static function toFilePath(string $namespaced_class) : string
	{
		$parts = explode('\\', $namespaced_class);

		$class = array_pop($parts);

		// Convert namespace parts to file path parts
		//   ex: ["Core", "DependencyInjection"] => ["core", "dependency-injection"]
		$namespaces = array_map(fn ($part) =>
			strtolower(preg_replace("/([a-z0-9])([A-Z])/", "$1-$2", $part))
		, $parts);

		return static::toSystemPath([...$namespaces, $class]);
	}

	private static function toSystemPath(array $parts) : string
	{
		return join(DIRECTORY_SEPARATOR, [ROOT, ...$parts]) . '.php';
	}

}