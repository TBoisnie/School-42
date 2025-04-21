<?php

namespace Service;


class FlashService
{
	// Constants
	private const KEY = 'flashes';


	//
	// Utilities
	//
	public function has(string $type) : bool
	{
		return !empty($_SESSION[self::KEY][$type]);
	}

	public function hasAny() : bool
	{
		return !empty($_SESSION[self::KEY]);
	}

	//
	// Getters
	//
	public function get(string $type) : array
	{
		$flashes = $_SESSION[self::KEY][$type];
		unset($_SESSION[self::KEY][$type]);
		return $flashes;
	}

	public function getAll() : array
	{
		$flashes = $_SESSION[self::KEY];
		$_SESSION[self::KEY] = [];
		return $flashes;
	}

	//
	// Setters
	//
	public function add(string $type, string $content) : self
	{
		$_SESSION[self::KEY][$type][] = $content;
		return $this;
	}

}
