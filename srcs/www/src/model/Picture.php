<?php

namespace Model;


class Picture
	extends AbstractModel
{

	// Properties
	protected int $id;
	protected string $path;
	// Relations
	protected ?User $author;
	protected ?array $comments;
	protected ?array $likes;

	public function __construct()
	{
		$this->id = 0;
		$this->path = "";
		$this->author = null;
		$this->comments = null;
		$this->likes = null;
	}

	//
	// Getters
	//
	public function getId() : int
	{
		return $this->id;
	}

	public function getPath() : string
	{
		return $this->path;
	}

	public function getAuthor() : ?User
	{
		return $this->author;
	}

	public function getComments() : ?array
	{
		return $this->comments;
	}

	public function getLikes() : ?array
	{
		return $this->likes;
	}

	//
	// Setters
	//
	public function setId(int $id) : self
	{
		$this->id = $id;
		return $this;
	}

	public function setPath(string $path) : self
	{
		$this->path = $path;
		return $this;
	}

	public function setAuthor(User $author) : self
	{
		$this->author = $author;
		return $this;
	}

	public function setComments(array $comments) : self
	{
		$this->comments = $comments;
		return $this;
	}

	public function setLikes(array $likes) : self
	{
		$this->likes = $likes;
		return $this;
	}

}
