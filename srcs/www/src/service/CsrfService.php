<?php

namespace Service;


class CsrfService
{
	// Constants
	private const KEY = 'csrf';


	//
	// Utilities
	//
	public static function isTokenValid(string $token) : bool
	{
		return static::getToken() === $token;
	}

	//
	// Getters
	//
	public static function getToken() : string
	{
		if (empty($_SESSION[static::KEY]))
		{
			static::generateToken();
		}

		return $_SESSION[static::KEY];
	}

	//
	// Setters
	//
	private static function generateToken() : void
	{
		$_SESSION[static::KEY] = md5(uniqid(mt_rand(), true));
	}

}
