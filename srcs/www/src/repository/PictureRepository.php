<?php

namespace Repository;

use Model\Picture;
use Model\User;
use Service\PaginationService;


class PictureRepository
	extends AbstractRepository
{

	// Constants
	public const TABLE = 'pictures';

	//
	// Get count
	//
	public function getCount(?User $user = null) : int
	{
		$sql = "SELECT COUNT(id) FROM ".self::TABLE;

		if ($user !== null)
		{
			$sql .= " WHERE id_author = :id_author ";
		}

		$st = $this->getConnection()->prepare($sql);

		if ($user !== null)
		{
			$st->bindValue(':id_author', $user->getId(), \PDO::PARAM_INT);
		}

		$st->execute();
		$count = $st->fetchColumn();
		$st->closeCursor();

		return $count;
	}

	public function create(Picture $picture) : void
	{
		$sql = "INSERT INTO ".self::TABLE."
					(id_author, path)
				VALUES
					(:id_author, :path)
		";

		$st = $this->getConnection()->prepare($sql);
		$st->bindValue(':id_author', $picture->getAuthor()->getId(), \PDO::PARAM_INT);
		$st->bindValue(':path', $picture->getPath(), \PDO::PARAM_STR);
		$st->execute();
		$st->closeCursor();
	}

	//
	// Delete
	//
	public function delete(Picture $picture) : void
	{
		$sql = "DELETE FROM ".self::TABLE." WHERE id = :id";

		$st = $this->getConnection()->prepare($sql);
		$st->bindValue(':id', $picture->getId(), \PDO::PARAM_INT);
		$st->execute();
		$st->closeCursor();
	}

	//
	// Get
	//
	public function get(int $id) : ?Picture
	{
		$sql = "SELECT p.id AS p_id, p.path, u.id AS u_id, u.username, u.email, u.notify
				FROM ".self::TABLE." AS p
				INNER JOIN ".UserRepository::TABLE." AS u
					ON p.id_author = u.id
				WHERE p.id = :id
		";

		$st = $this->getConnection()->prepare($sql);
		$st->bindValue(':id', $id, \PDO::PARAM_INT);
		$st->execute();
		$row = $st->fetch(\PDO::FETCH_ASSOC);
		$st->closeCursor();

		$picture = null;
		if (!empty($row))
		{
			$picture = (new Picture())
				->setId($row['p_id'])
				->setPath($row['path'])
				->setAuthor((new User())
					->setId($row['u_id'])
					->setUsername($row['username'])
					->setEmail($row['email'])
					->setNotify($row['notify'])
				)
			;
		}

		return $picture;
	}

	public function getPage(PaginationService $page) : array
	{
		$sql = "SELECT p.id AS p_id, p.path, u.id AS u_id, u.username
				FROM ".self::TABLE." AS p
				INNER JOIN ".UserRepository::TABLE." AS u
					ON p.id_author = u.id
				ORDER BY p.id DESC
				LIMIT :limit
					OFFSET :offset
		";

		$st = $this->getConnection()->prepare($sql);
		$st->bindValue(':limit', $page->getSize(), \PDO::PARAM_INT);
		$st->bindValue(':offset', $page->getSize() * $page->getCurrent(), \PDO::PARAM_INT);
		$st->execute();
		$rows = $st->fetchAll(\PDO::FETCH_ASSOC);
		$st->closeCursor();

		$pictures = [];
		foreach ($rows as $row)
		{
			$pictures[] = (new Picture())
				->setId($row['p_id'])
				->setPath($row['path'])
				->setAuthor((new User())
					->setId($row['u_id'])
					->setUsername($row['username'])
				)
			;
		}

		return $pictures;
	}

	public function getPageFor(User $user, PaginationService $page) : array
	{
		$sql = "SELECT id, path
				FROM ".self::TABLE."
				WHERE id_author = :id_author
				ORDER BY id DESC
				LIMIT :limit
					OFFSET :offset
		";

		$st = $this->getConnection()->prepare($sql);
		$st->bindValue(':id_author', $user->getId(), \PDO::PARAM_INT);
		$st->bindValue(':limit', $page->getSize(), \PDO::PARAM_INT);
		$st->bindValue(':offset', $page->getSize() * $page->getCurrent(), \PDO::PARAM_INT);
		$st->execute();
		$rows = $st->fetchAll(\PDO::FETCH_ASSOC);
		$st->closeCursor();

		$pictures = [];
		foreach ($rows as $row)
		{
			$pictures[] = (new Picture())
				->setId($row['id'])
				->setPath($row['path'])
				->setAuthor($user)
			;
		}

		return $pictures;
	}

}
