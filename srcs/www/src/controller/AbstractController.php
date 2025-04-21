<?php

namespace Controller;

use Exception\PageNotFoundException;
use Exception\UnauthorizedException;
use Model\User;
use Service\CsrfService;
use Service\FlashService;
use Service\TemplateService;


abstract class AbstractController
{

	// Constants
	protected const VIEW_ROOT = '';
	// Properties
	private ?FlashService $flashes = null;


	//
	// User
	//
	protected function getUser() : ?User
	{
		return isset($_SESSION['user']) ? \unserialize($_SESSION['user']) : null;
	}

	protected function setUser(User $user) : self
	{
		$_SESSION['user'] = \serialize($user);
		return $this;
	}

	//
	// Flashes
	//
	protected function getFlashes() : FlashService
	{
		$this->flashes = $this->flashes ?? new FlashService();
		return $this->flashes;
	}

	//
	// Exception thrower
	//
	protected function unauthorizedUnless(mixed $condition) : void
	{
		if (!$condition)
			throw new UnauthorizedException();
	}

	protected function notFoundUnless(mixed $condition) : void
	{
		if (!$condition)
			throw new PageNotFoundException();
	}

	//
	// Redirection
	//
	protected function redirect(string $location) : void
	{
		\header("Location: https://".$_SERVER['HTTP_HOST'].$location);
		exit();
	}

	//
	// Render
	//
	protected function render(string $file, array $variables = []) : string
	{
		return TemplateService::get([ static::VIEW_ROOT, ...\explode('/', $file) ], [
			'_user' => $this->getUser(),
			'_flashes' => $this->getFlashes(),
			'_csrf_token' => CsrfService::getToken(),
			...$variables
		]);
	}

}
