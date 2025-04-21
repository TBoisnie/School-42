<?php

namespace Model;


class Like
	extends AbstractModel
{

	// Relations
	protected ?User $author;
	protected ?Picture $picture;

	public function __construct()
	{
		$this->author = null;
		$this->picture = null;
	}

	//
	// Getters
	//
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
