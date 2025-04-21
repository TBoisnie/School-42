<?php

namespace Repository;

use Model\Like;
use Model\Picture;
use Model\User;


class LikeRepository extends AbstractRepository
{
	// Constants
	public const TABLE = 'likes';

	//
	// Check uniqueness
	//
	public function checkUniqueness(Like $like) : bool
	{
		$sql = "SELECT
					COUNT(*)
				FROM
					".self::TABLE."
				WHERE
					id_author = :id_author
					AND id_picture = :id_picture
		";

		$st = $this->getConnection()->prepare($sql);
		$st->bindValue(':id_author', $like->getAuthor()->getId(), \PDO::PARAM_INT);
		$st->bindValue(':id_picture', $like->getPicture()->getId(), \PDO::PARAM_INT);
		$st->execute();
		$is_unique = !$st->fetchColumn();
		$st->closeCursor();

		return $is_unique;
	}

	//
	// Create
	//
	public function create(Like $like) : void
	{
		if (!$this->checkUniqueness($like))
			return ;

		$sql = "INSERT INTO ".self::TABLE."
				(id_author, id_picture)
			VALUES
				(:id_author, :id_picture)
		";

		$st = $this->getConnection()->prepare($sql);
		$st->bindValue(':id_author', $like->getAuthor()->getId(), \PDO::PARAM_INT);
		$st->bindValue(':id_picture', $like->getPicture()->getId(), \PDO::PARAM_INT);
		$st->execute();
		$st->closeCursor();
	}

	//
	// Delete
	//
	public function delete(Like $like) : void
	{
		$sql = "DELETE FROM
					".self::TABLE."
				WHERE
					id_author = :id_author
					AND id_picture = :id_picture
		";

		$st = $this->getConnection()->prepare($sql);
		$st->bindValue(':id_author', $like->getAuthor()->getId(), \PDO::PARAM_INT);
		$st->bindValue(':id_picture', $like->getPicture()->getId(), \PDO::PARAM_INT);
		$st->execute();
		$st->closeCursor();
	}

	//
	// Get for User|Picture
	//
	public function getIdsFor(User|Picture $model) : array
	{
		$sql = "SELECT
					id_author,
					id_picture
				FROM
					".self::TABLE."
		";
		$sql .= $model instanceof User
			? " WHERE id_author  = :id_model "
			: " WHERE id_picture = :id_model "
		;

		$st = $this->getConnection()->prepare($sql);
		$st->bindValue(':id_model', $model->getId(), \PDO::PARAM_INT);
		$st->execute();
		$rows = $st->fetchAll(\PDO::FETCH_ASSOC);
		$st->closeCursor();

		$ids = array_map( fn ($row) =>
			$row[$model instanceof User ? 'id_picture' : 'id_author']
		, $rows);

		return $ids;
	}


}
