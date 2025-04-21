<?php

namespace Model;


class User
	extends AbstractModel
{

	// Properties
	protected int $id;
	protected string $username;
	protected string $password;
	protected string $email;
	protected bool $notification_enabled;
	// Relations
	protected ?array $pictures;
	protected ?array $comments;
	protected ?array $likes;

	//
	// Constructor
	//
	public function __construct()
	{
		// Properties
		$this->id = 0;
		$this->username = "";
		$this->password = "";
		$this->email = "";
		$this->notify = false;
		// Relations
		$this->pictures = null;
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

	public function getUsername() : string
	{
		return $this->username;
	}

	public function getPassword() : string
	{
		return $this->password;
	}

	public function getEmail() : string
	{
		return $this->email;
	}

	public function getNotify() : bool
	{
		return $this->notify;
	}

	public function getPictures() : ?array
	{
		return $this->pictures;
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

	public function setUsername(string $username) : self
	{
		$this->username = $username;
		return $this;
	}

	public function setPassword(string $password) : self
	{
		$this->password = $password;
		return $this;
	}

	public function setEmail(string $email) : self
	{
		$this->email = $email;
		return $this;
	}

	public function setNotify(bool $notify) : self
	{
		$this->notify = $notify;
		return $this;
	}

	public function setPictures(array $pictures) : self
	{
		$this->pictures = $pictures;
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

	//
	// Serialization
	//
	public function __serialize() : array
	{
		return [
			'id' => $this->id,
			'username' => $this->username,
			'email' => $this->email,
			'notify' => $this->notify,
			'likes' => \serialize($this->likes),
		];
	}

	public function __unserialize(array $data) : void
	{
		$this->id = $data['id'];
		$this->username = $data['username'];
		$this->email = $data['email'];
		$this->notify = $data['notify'];
		$this->likes = \unserialize($data['likes']);
	}

}
