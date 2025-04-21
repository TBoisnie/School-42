<?php

namespace Model;


class Comment
	extends AbstractModel
{

	// Properties
	protected int $id;
	protected string $content;
	// Relations
	protected ?User $author;
	protected ?Picture $picture;

	public function __construct()
	{
		$this->id = 0;
		$this->content = "";
		$this->author = null;
		$this->picture = null;
	}

	//
	// Getters
	//
	public function getId() : int
	{
		return $this->id;
	}

	public function getContent() : string
	{
		return $this->content;
	}

	public function getAuthor() : ?User
	{
		return $this->author;
	}

	public function getPicture() : ?Picture
	{
		return $this->picture;
	}


	//
	// Setters
	//
	public function setId(int $id) : self
	{
		$this->id = $id;
		return $this;
	}

	public function setContent(string $content) : self
	{
		$this->content = $content;
		return $this;
	}

	public function setAuthor(User $author) : self
	{
		$this->author = $author;
		return $this;
	}

	public function setPicture(Picture $picture) : self
	{
		$this->picture = $picture;
		return $this;
	}

}
