<?php

namespace Repository;

use Model\User;
use Repository\AbstractRepository;


class UserRepository extends AbstractRepository
{

	// Constants
	public const TABLE = 'users';


	//
	// Check uniqueness
	//
	public function isUnique(User $user) : array|bool
	{
		$sql = "
			SELECT username, email
			FROM ".self::TABLE."
			WHERE username = :username
				OR email = :email
		";

		$st = $this->getConnection()->prepare($sql);
		$st->bindValue(':username', $user->getUsername(), \PDO::PARAM_STR);
		$st->bindValue(':email', $user->getEmail(), \PDO::PARAM_STR);
		$st->execute();
		$rows = $st->fetchAll(\PDO::FETCH_ASSOC);
		$st->closeCursor();

		$conflicts = [];
		foreach ($rows as $row)
		{
			$conflicts[] = $row['username'] === $user->getUsername() ? "username" : "email";
		}

		return empty($conflicts) ? true : $conflicts;
	}

	//
	// Create
	//
	public function create(User $user) : ?string
	{
		$secret = $this->generateSecretKey();

		$sql = "
			INSERT INTO ".self::TABLE."
				(username, password, email, secret_key)
			VALUES
				(:username, :password, :email, :secret_key)
		";

		$st = $this->getConnection()->prepare($sql);
		$st->bindValue(':username', $user->getUsername(), \PDO::PARAM_STR);
		$st->bindValue(':password', $this->hashPassword($user->getPassword()), \PDO::PARAM_STR);
		$st->bindValue(':email', $user->getEmail(), \PDO::PARAM_STR);
		$st->bindValue(':secret_key', $secret, \PDO::PARAM_STR);
		$st->execute();
		$st->closeCursor();

		return $secret;
	}

	public function update(User $user, bool $lock = false) : ?string
	{
		$secret = $this->generateSecretKey();

		$sql = "
			UPDATE ".self::TABLE."
			SET username = :username, email = :email, notify = :notify, secret_key = :secret_key, verified = :verified
			WHERE id = :id
		";

		$st = $this->getConnection()->prepare($sql);
		$st->bindValue(':username', $user->getUsername(), \PDO::PARAM_STR);
		$st->bindValue(':email', $user->getEmail(), \PDO::PARAM_STR);
		$st->bindValue(':notify', $user->getNotify(), \PDO::PARAM_BOOL);
		$st->bindValue(':secret_key', $secret, \PDO::PARAM_STR);
		$st->bindValue(':verified', $lock, \PDO::PARAM_BOOL);
		$st->bindValue(':id', $user->getId(), \PDO::PARAM_INT);
		$st->execute();
		$st->closeCursor();

		return $secret;
	}

	public function updatePassword(User $user) : ?bool
	{
		$sql = "
			UPDATE ".self::TABLE."
			SET password = :password
			WHERE id = :id
		";

		$st = $this->getConnection()->prepare($sql);
		$st->bindValue(':password', $this->hashPassword($user->getPassword()), \PDO::PARAM_STR);
		$st->bindValue(':id', $user->getId(), \PDO::PARAM_INT);
		$st->execute();
		$updated = $st->rowCount();
		$st->closeCursor();

		return $updated;
	}

	//
	// Verify
	//
	public function verify(string $username, string $secret) : bool
	{
		$sql = "
			UPDATE ".self::TABLE."
			SET verified = TRUE, secret_key = NULL
			WHERE username = :username
				AND secret_key = :secret_key
		";

		$st = $this->getConnection()->prepare($sql);
		$st->bindValue(':username', $username, \PDO::PARAM_STR);
		$st->bindValue(':secret_key', $secret, \PDO::PARAM_STR);
		$st->execute();
		$updated = !!$st->rowCount();
		$st->closeCursor();

		return $updated;
	}

	//
	// Get By Credentials
	//
	public function getByCredentials(string $username, string $password) : ?User
	{
		$sql = "
			SELECT id, username, password, email, notify
			FROM ".self::TABLE."
			WHERE username = :username
				AND verified = TRUE
		";

		$st = $this->getConnection()->prepare($sql);
		$st->bindValue(':username', $username, \PDO::PARAM_STR);
		$st->execute();
		$row = $st->fetch(\PDO::FETCH_ASSOC);
		$st->closeCursor();

		$user = null;
		if (!empty($row) && $this->verifyPassword($password, $row['password']))
		{
			$user = (new User())
				->setId($row['id'])
				->setUsername($row['username'])
				->setEmail($row['email'])
				->setNotify($row['notify'])
			;
		}

		return $user;
	}

	//
	// Get profile
	//
	public function getProfile(string $username) : ?User
	{
		$sql = "
			SELECT id, username, email, notify
			FROM ".self::TABLE."
			WHERE username = :username
		";

		$st = $this->getConnection()->prepare($sql);
		$st->bindValue(':username', $username, \PDO::PARAM_STR);
		$st->execute();
		$row = $st->fetch(\PDO::FETCH_ASSOC);
		$st->closeCursor();

		$user = null;
		if (!empty($row))
		{
			$user = (new User())
				->setId($row['id'])
				->setUsername($row['username'])
				->setEmail($row['email'])
				->setNotify($row['notify'])
			;
		}

		return $user;
	}

	//
	// Set forgot password secret
	//
	public function setForgotPasswordSecret(string $username, string $email) : ?string
	{
		$secret = $this->generateSecretKey();

		$sql = "
			UPDATE ".self::TABLE."
			SET secret_key = :secret_key
			WHERE username = :username
				AND email = :email
				AND verified = TRUE
		";

		$st = $this->getConnection()->prepare($sql);
		$st->bindValue(':username', $username, \PDO::PARAM_STR);
		$st->bindValue(':email', $email, \PDO::PARAM_STR);
		$st->bindValue(':secret_key', $secret, \PDO::PARAM_STR);
		$st->execute();
		$updated = !!$st->rowCount();
		$st->closeCursor();

		return $updated ? $secret : null;
	}

	//
	// Check Secret
	//
	public function checkSecret(string $username, string $secret) : ?bool
	{
		$sql = "
			SELECT id
			FROM ".self::TABLE."
			WHERE username = :username
				AND secret_key = :secret_key
		";

		$st = $this->getConnection()->prepare($sql);
		$st->bindValue(':username', $username, \PDO::PARAM_STR);
		$st->bindValue(':secret_key', $secret, \PDO::PARAM_STR);
		$st->execute();
		$valid = !!$st->fetch(\PDO::FETCH_ASSOC);
		$st->closeCursor();

		return $valid;
	}

	//
	// Update forgot password
	//
	public function updateForgotPassword(string $username, string $password) : bool
	{
		$sql = "
			UPDATE ".self::TABLE."
			SET password = :password, secret_key = NULL
			WHERE username = :username
		";

		$st = $this->getConnection()->prepare($sql);
		$st->bindValue(':password', $this->hashPassword($password), \PDO::PARAM_STR);
		$st->bindValue(':username', $username, \PDO::PARAM_STR);
		$st->execute();
		$updated = !!$st->rowCount();
		$st->closeCursor();

		return $updated;
	}

	//
	// Utilities
	//
	private function hashPassword(string $password) : string
	{
		return \password_hash($password, PASSWORD_BCRYPT, [ 'cost' => 10 ]);
	}

	private function verifyPassword(string $password, string $hash) : bool
	{
		return \password_verify($password, $hash);
	}

	private function generateSecretKey() : string
	{
		return \hash('sha256', \uniqid());
	}

}
