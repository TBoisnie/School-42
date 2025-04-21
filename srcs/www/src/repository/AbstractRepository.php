<?php

namespace Repository;


abstract class AbstractRepository
{
	private const TYPE = 'pgsql';
	private const PORT = '5432';
	private const HOST = 'db';
	private const NAME = $_ENV['POSTGRES_DB'];
	private const USER = $_ENV['POSTGRES_USER'];
	private const PASS = $_ENV['POSTGRES_PASSWORD'];

	private static ?\PDO $connection = null;

	protected function getConnection() : \PDO
	{
		if (!static::$connection)
		{
			$dsn  = self::TYPE;
			$dsn .= ":host=".self::HOST;
			$dsn .= ";port=".self::PORT;
			$dsn .= ";dbname=".self::NAME;
			$dsn .= ";options='--client_encoding=UTF8'";

			$options = [
				\PDO::ATTR_ERRMODE => \PDO::ERRMODE_EXCEPTION
			];

			static::$connection = new \PDO($dsn, self::USER, self::PASS, $options);
		}

		return static::$connection;
	}

}
