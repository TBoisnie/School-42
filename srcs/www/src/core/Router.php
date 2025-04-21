<?php

namespace Core;

use Controller\PictureController;
use Controller\AuthController;
use Controller\CommentController;
use Controller\UserController;
use Controller\ErrorController;
use Controller\LikeController;
use Exception\PageNotFoundException;
use Exception\UnauthorizedException;

class Router
{

	//
	// Getters
	//
	static public function getPage() : string
	{
		$route = static::resolve();

		try
		{
			$reflection_method = new \ReflectionMethod(...$route);
			$page = $reflection_method->invoke(new ($route[0])());
		}
		catch (PageNotFoundException $e)
		{
			$page = (new ErrorController)->notFound();
		}
		catch (UnauthorizedException $e)
		{
			$page = (new ErrorController)->unauthorized();
		}
		catch (\Throwable $th)
		{
			$page = (new ErrorController)->unexpected($th);
		}

		return $page;
	}

	//
	// Utilities
	//
	static private function resolve() : array
	{
		$page = $_GET['p'] ?? 'galery';

		return match($page)
		{
			// Picture
			'galery'  => [ PictureController::class, 'galery' ],
			'studio'  => [ PictureController::class, 'studio' ],
			'picture' => [ PictureController::class, 'picture' ],
			'delete'  => [ PictureController::class, 'delete' ],
			// Like
			'like' => [ LikeController::class, 'create' ],
			'unlike' => [ LikeController::class, 'delete' ],
			// Comment
			'comment' => [ CommentController::class, 'create' ],
			// Auth
			'register'               => [ AuthController::class, 'register' ],
			'email-confirm'          => [ AuthController::class, 'emailConfirm' ],
			'login'                  => [ AuthController::class, 'login' ],
			'logout'                 => [ AuthController::class, 'logout' ],
			'reset-password'         => [ AuthController::class, 'resetPassword' ],
			'reset-password-confirm' => [ AuthController::class, 'resetPasswordConfirm' ],
			// User
			'profile' => [ UserController::class, 'profile' ],
			'edit'    => [ UserController::class, 'edit' ],
			// Default
			default => [ ErrorController::class, 'notFound' ]
		};
	}

}
