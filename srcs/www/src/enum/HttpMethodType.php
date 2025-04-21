<?php

namespace Enum;


enum HttpMethodType : string
{

	// Standard
	case OPTIONS = 'OPTIONS';
	case HEAD    = 'HEAD';
	case GET     = 'GET';
	case POST    = 'POST';
	case PUT     = 'PUT';
	case PATCH   = 'PATCH';
	case DELETE  = 'DELETE';
	case CONNECT = 'CONNECT';
	case TRACE   = 'TRACE';

	public static function fromString(string $method) : ?static
	{
		return static::tryFrom(strtoupper($method));
	}

}
