<?php

namespace Enum;


enum OverlayType : string
{
	case ANONYMOUS = "anonymous.png";
	case BIRTHDAY = "birthday.png";
	case CAT = "cat.png";
	case UNICORN = "unicorn.png";

	public static function fromString(string $overlay) : ?static
	{
		return static::tryFrom(strtolower($overlay));
	}
};
