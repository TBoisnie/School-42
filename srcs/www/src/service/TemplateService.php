<?php

namespace Service;


class TemplateService
{

	// Constants
	private const VIEW_DIR = "view";
	// Properties
	private static array $page_vars = [];

	//
	// Public
	//
	public static function get(array|string $path_or_parts, array $variables = []) : string
	{
		static::$page_vars = $variables;
		return static::_get($path_or_parts, $variables);
	}

	public static function getPartial(array|string $path_or_parts, array $variables = []) : string
	{
		return static::_get($path_or_parts, [ ...static::$page_vars, ...$variables ]);
	}

	//
	// Private
	//
	private static function _get(array|string $path_or_parts, array $variables) : string
	{
		$path_parts = \is_string($path_or_parts) ? \explode('/', $path_or_parts) : $path_or_parts;

		$level = \ob_get_level();

		\ob_start();

		try
		{
			\extract($variables, \EXTR_SKIP);
			include FileService::toSrcPath([ self::VIEW_DIR, ...$path_parts ]);
		}
		catch (\Throwable $e)
		{
			while (\ob_get_level() > $level)
			{
				\ob_end_clean();
			}
			throw $e;
		}

		return \ob_get_clean();
	}

}
