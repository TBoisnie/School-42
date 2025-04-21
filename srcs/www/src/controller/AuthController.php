<?php

namespace Controller;

use Form\Auth\LoginForm;
use Form\Auth\RegisterForm;
use Form\Auth\ResetPasswordConfirmForm;
use Form\Auth\ResetPasswordForm;
use Model\User;
use Repository\LikeRepository;
use Repository\UserRepository;
use Service\MailService;

class AuthController extends AbstractController
{

	// Constants
	protected const VIEW_ROOT = 'page/auth';

	//
	// Register
	//
	public function register()
	{
		$this->unauthorizedUnless(!$this->getUser());

		$form = new RegisterForm();

		if ($form->isSubmitted())
		{
			$form->validateFromGlobals();

			if ($form->isValid())
			{
				$user = (new User())
					->setUsername($form->getField('username'))
					->setPassword($form->getField('password'))
					->setEmail($form->getField('email'))
				;

				$repository = new UserRepository();
				$uniqueness = $repository->isUnique($user);

				if ($uniqueness === true)
				{
					$secret = $repository->create($user);
					$link = "https://".$_SERVER['HTTP_HOST']."/index.php?p=email-confirm&u=".\htmlspecialchars(urlencode($user->getUsername()))."&s=".\urlencode($secret);

					MailService::send($user->getEmail(), "Account Registration",
						"Thanks for your registration ! To confirm your account, go to: \r\n".$link
					);

					$this->getFlashes()
						->add('success', "
							An email has been sent to ".htmlspecialchars($form->getField('email')).".
							Click on the link inside to validate your registration.
						");
				}
				else
				{
					foreach($uniqueness as $conflict)
					{
						$this->getFlashes()->add('danger', \ucfirst($conflict)." is already used.");
					}
				}
			}
			else
			{
				foreach ($form->getErrors() as $message)
				{
					$this->getFlashes()->add('danger', $message);
				}
			}
		}

		return $this->render('register');
	}

	//
	// Register confirm
	//
	public function emailConfirm()
	{
		if (!empty($_GET['u']) || !empty($_GET['s']))
		{
			$verified = (new UserRepository)->verify($_GET['u'], $_GET['s']);

			if ($verified)
			{
				$this->getFlashes()->add('success', "Congratulation! Email verified. You can now login.");
				$this->redirect($this->getUser() ? "/?p=logout" : "/?p=login");
			}
			else
			{
				$this->getFlashes()->add('danger', "Invalid confirmation token.");
			}
		}

		$this->redirect("/?p=register");
	}

	//
	// Login
	//
	public function login()
	{
		$this->unauthorizedUnless(!$this->getUser());

		$form = new LoginForm();

		if ($form->isSubmitted())
		{
			$form->validateFromGlobals();

			if ($form->isValid())
			{
				$user = (new UserRepository)->getByCredentials(
					$form->getField('username'),
					$form->getField('password')
				);

				if ($user === null)
				{
					$this->getFlashes()->add('danger', "Invalid credentials.");
				}
				else
				{
					$user->setLikes((new LikeRepository)->getIdsFor($user));

					$_SESSION['user'] = \serialize($user);
					$this->getFlashes()->add('success', "Connection successful.");
					$this->redirect("/");
				}
			}
			else
			{
				foreach ($form->getErrors() as $message)
				{
					$this->getFlashes()->add('danger', $message);
				}
			}
		}

		return $this->render('login');
	}

	//
	// Logout
	//
	public function logout()
	{
		unset($_SESSION['user']);
		$this->getFlashes()->add('info', "Disconnection complete.");
		$this->redirect("/");
	}

	//
	// Reset password
	//
	public function resetPassword()
	{
		$this->unauthorizedUnless(!$this->getUser());

		$form = new ResetPasswordForm();

		if ($form->isSubmitted())
		{
			$form->validateFromGlobals();

			if ($form->isValid())
			{
				$secret = (new UserRepository)->setForgotPasswordSecret(
					$form->getField('username'),
					$form->getField('email')
				);

				if ($secret !== null)
				{
					$link = "https://".$_SERVER['HTTP_HOST']."/index.php?p=reset-password-confirm&u=".\urlencode($form->getField('username'))."&s=".\urlencode($secret);

					MailService::send($form->getField('email'), "Account Reset Password",
						"To reset your password, go to: \r\n".$link
					);
				}

				$this->getFlashes()->add('success', "
					An email has been sent to ".htmlspecialchars($form->getField('email')).".<br>
					Click on the link inside to reset your password.
				");
			}
			else
			{
				foreach ($form->getErrors() as $message)
				{
					$this->getFlashes()->add('danger', $message);
				}
			}
		}

		return $this->render('reset-password');
	}

	//
	// Reset Password confirm
	//
	public function resetPasswordConfirm()
	{
		$this->unauthorizedUnless(!$this->getUser());

		if (empty($_GET['u']) || empty($_GET['s']) || !(new UserRepository)->checkSecret($_GET['u'], $_GET['s']))
		{
			$this->getFlashes()->add('danger', "Invalid confirmation token.");
			$this->redirect("/?p=register");
		}

		$form = new ResetPasswordConfirmForm();

		if ($form->isSubmitted())
		{
			$form->validateFromGlobals();

			if ($form->isValid())
			{
				(new UserRepository)->updateForgotPassword(
					$_GET['u'],
					$form->getField('password')
				);

				$this->getFlashes()->add('success', "Your password has been successfully updated.");
				$this->redirect("/?p=login");
			}
			else
			{
				foreach ($form->getErrors() as $message)
				{
					$this->getFlashes()->add('danger', $message);
				}
			}
		}

		return $this->render('reset-password-confirm');
	}
}
