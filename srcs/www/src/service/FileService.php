<?php

namespace Service;


class FileService
{

	static public function toPublicPath(string|array $path_or_parts) : string
	{
		return static::toRootPath(['public', $path_or_parts]);
	}

	static public function toSrcPath(string|array $path_or_parts, string $suffix = '.php') : string
	{
		return static::toRootPath(['src', $path_or_parts]). $suffix;
	}

	static private function toRootPath(string|array $path_or_parts) : string
	{
		return join(DIRECTORY_SEPARATOR, [ dirname(__DIR__, 2), ...static::flatten($path_or_parts) ]);
	}

	static private function flatten(string|array $path_or_parts) : array
	{
		if (!\is_array($path_or_parts))
		{
			return [ $path_or_parts ];
		}

		$flatten = [];
		\array_walk_recursive($path_or_parts, function($value) use (&$flatten) {
			$flatten[] = $value;
		});

		return $flatten;
	}

}
