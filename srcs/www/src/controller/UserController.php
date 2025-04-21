<?php

namespace Controller;

use Form\User\EditForm;
use Model\User;
use Repository\UserRepository;
use Service\MailService;

class UserController extends AbstractController
{

	// Constants
	protected const VIEW_ROOT = 'page/user';


	public function profile() : string
	{
		$username = null;

		if (!empty($_GET['u']))
		{
			$username = $_GET['u'];
		}
		else if ($this->getUser())
		{
			$username = $this->getUser()->getUsername();
		}

		$this->notFoundUnless(!empty($username));

		$target = (new UserRepository)->getProfile($username);

		$this->notFoundUnless($target);

		return $this->render('profile', [
			'target' => $target,
		]);
	}

	public function edit() : string
	{
		$this->unauthorizedUnless($this->getUser());

		$form = new EditForm();

		if ($form->isSubmitted())
		{
			$form->validateFromGlobals();

			if ($form->isValid())
			{
				$repository = new UserRepository();

				$user = new User();
				$user->setId($this->getUser()->getId());

				if ($this->getUser()->getUsername() !== $form->getField('username'))
				{
					$user->setUsername($form->getField('username'));
				}

				if ($this->getUser()->getEmail() !== $form->getField('email'))
				{
					$user->setEmail($form->getField('email'));
				}

				if (!empty($form->getField('new-password')))
				{
					$user->setPassword($form->getField('new-password'));

					$repository->updatePassword($user);
				}

				$uniqueness = $repository->isUnique($user);

				if ($uniqueness === true)
				{
					$verified = $this->getUser()->getEmail() === $form->getField('email');

					$user->setEmail($form->getField('email'));
					$user->setUsername($form->getField('username'));
					$user->setNotify($form->getField('notify'));

					$secret = $repository->update($user, $verified);

					if ($user->getEmail() !== $this->getUser()->getEmail())
					{
						$link = "https://".$_SERVER['HTTP_HOST']."/index.php?p=email-confirm&u=".\htmlspecialchars(urlencode($user->getUsername()))."&s=".\urlencode($secret);

						MailService::send($user->getEmail(), "Edit Confirmation",
							"To confirm you profile edit, go to: \r\n".$link
						);

						$this->getFlashes()
						->add('info', "
							An email has been sent to ".htmlspecialchars($form->getField('email')).".
							Click on the link inside to validate your modification.
						");
					}

					$_user = $this->getUser()
						->setEmail($user->getEmail())
						->setUsername($user->getUsername())
						->setNotify($user->getNotify())
					;
					$this->setUser($_user);

					$this->getFlashes()->add('success', "Your profile has been updated successfully.");
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
				foreach($form->getErrors() as $message)
				{
					$this->getFlashes()->add('danger', $message);
				}
			}
		}

		return $this->render('edit');
	}

}
