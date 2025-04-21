<?php

namespace Form;

use Enum\FormMethodType;
use Service\CsrfService;

abstract class AbstractForm
{
	// Properties
	protected array $_get;
	protected array $_post;
	protected array $_files;
	protected array $_errors;

	//
	// Constructor
	//
	public function __construct()
	{
		$this->_get = $_GET;
		$this->_post = $_POST;
		$this->_files = $_FILES;
		$this->_errors = [];
	}

	//
	// Public
	//
	public function isSubmitted() : bool
	{
		return !empty($this->getName()) ? isset($this->_post[$this->getName()]) : false;
	}

	public function isValid() : bool
	{
		return empty($this->_errors);
	}

	public function getErrors() : array
	{
		return $this->_errors;
	}

	public function getField(string $name, FormMethodType $type = FormMethodType::POST) : mixed
	{
		return $this->getFields($type)[$name] ?? null;
	}

	public function getFields(?FormMethodType $type = null) : array
	{
		return match ($type)
		{
			FormMethodType::GET => $this->_get,
			FormMethodType::POST => $this->_post,
			FormMethodType::FILES => $this->_files,

			default => [
				'get' => $this->_get,
				'post' => $this->_post,
				'files' => $this->_files,
			]
		};
	}

	public function validateFromGlobals() : void
	{
		if ($this->checkCsrf())
		{
			$this->validate();
		}
	}

	//
	// Private
	//
	private function isProtectedMethod() : bool
	{
		$method = $_SERVER['REQUEST_METHOD'] ?? "POST";
		return \in_array(\strtoupper($method), ['POST', 'PUT', 'PATCH', 'DELETE'], true);
	}

	private function checkCsrf() : bool
	{
		if ($this->isProtectedMethod() && !CsrfService::isTokenValid($this->getField('_csrf') ?? ""))
		{
			$this->_errors['csrf'] = "Invalid CSRF token.";
		}

		return $this->isValid();
	}

	//
	// Abstract
	//
	abstract protected function validate() : void;
	abstract protected function getName() : string;

}
