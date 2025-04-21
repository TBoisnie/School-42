<?php

namespace Repository;

use Model\Comment;
use Model\Picture;
use Model\User;
use Service\PaginationService;


class CommentRepository extends AbstractRepository
{

	// Constants
	public const TABLE = 'comments';

	//
	// Create
	//
	public function create(Comment $comment) : void
	{
		$sql = "INSERT INTO ".self::TABLE."
					(id_author, id_picture, content)
				VALUES
					(:id_author, :id_picture, :content)
		";

		$st = $this->getConnection()->prepare($sql);
		$st->bindValue(':id_author', $comment->getAuthor()->getId(), \PDO::PARAM_INT);
		$st->bindValue(':id_picture', $comment->getPicture()->getId(), \PDO::PARAM_INT);
		$st->bindValue(':content', $comment->getContent(), \PDO::PARAM_STR);
		$st->execute();
		$st->closeCursor();
	}

	//
	// Delete
	//
	public function delete(Comment $comment) : void
	{
		$sql = " DELETE FROM ".self::TABLE." WHERE id = :id ";

		$st = $this->getConnection()->prepare($sql);
		$st->bindValue(':id', $comment->getId(), \PDO::PARAM_INT);
		$st->execute();
		$st->closeCursor();
	}

	//
	// Get count for User|Picture|null
	//
	public function getCountFor(User|Picture|null $model = null) : int
	{
		$sql = " SELECT COUNT(id) FROM ".self::TABLE;

		$sql .= $model instanceof User    ? " WHERE id_author  = :id_model" : "";
		$sql .= $model instanceof Picture ? " WHERE id_picture = :id_model" : "";

		$st = $this->getConnection()->prepare($sql);

		if ($model !== null)
		{
			$st->bindValue(':id_model', $model->getId(), \PDO::PARAM_INT);
		}

		$st->execute();
		$count = $st->fetchColumn();
		$st->closeCursor();

		return $count;
	}

	//
	// Get page for User|Picture|null
	//
	public function getPageFor(PaginationService $page, User|Picture|null $model = null) : array
	{
		$sql  = " SELECT c.id AS c_id, c.content, u.id AS u_id, u.username, u.email, p.id AS p_id, p.path ";
		$sql .= " FROM ".self::TABLE." AS c ";
		$sql .= " INNER JOIN ".UserRepository::TABLE."    AS u ON c.id_author  = u.id ";
		$sql .= " INNER JOIN ".PictureRepository::TABLE." AS p ON c.id_picture = p.id ";

		$sql .= $model instanceof User    ? " WHERE c.id_author  = :id_model " : "";
		$sql .= $model instanceof Picture ? " WHERE c.id_picture = :id_model " : "";

		$sql .= " LIMIT :limit OFFSET :offset ";

		$st = $this->getConnection()->prepare($sql);
		$st->bindValue(':limit', $page->getSize(), \PDO::PARAM_INT);
		$st->bindValue(':offset', $page->getSize() * $page->getCurrent(), \PDO::PARAM_INT);

		if ($model !== null)
		{
			$st->bindValue(':id_model', $model->getId(), \PDO::PARAM_INT);
		}

		$st->execute();
		$rows = $st->fetchAll(\PDO::FETCH_ASSOC);
		$st->closeCursor();

		$comments = [];
		foreach ($rows as $row)
		{
			$comments[] = (new Comment())
				->setId($row['c_id'])
				->setContent($row['content'])
				->setAuthor((new User())
					->setId($row['u_id'])
					->setUsername($row['username'])
					->setEmail($row['email'])
				)
				->setPicture((new Picture())
					->setId($row['p_id'])
					->setPath($row['path'])
				)
			;
		}

		return $comments;
	}

}
