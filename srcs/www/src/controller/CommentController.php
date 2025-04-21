<?php

namespace Controller;

use Form\Comment\CommentForm;
use Model\Comment;
use Repository\CommentRepository;
use Repository\PictureRepository;
use Service\MailService;

class CommentController
	extends AbstractController
{

	public function create()
	{
		$this->unauthorizedUnless($this->getUser());

		$form = new CommentForm();

		if ($form->isSubmitted())
		{
			$form->validateFromGlobals();

			if ($form->isValid())
			{
				$picture = (new PictureRepository)->get($form->getField('picture_id'));

				$this->notFoundUnless($picture);

				(new CommentRepository)->create((new Comment)
					->setPicture($picture)
					->setAuthor($this->getUser())
					->setContent($form->getField('content'))
				);

				if ($picture->getAuthor()->getNotify())
				{
					MailService::send($picture->getAuthor()->getEmail(), "You get a comment!",
						htmlspecialchars($this->getUser()->getUsername()). " commented one of your picture! \n". "https://".$_SERVER['HTTP_HOST']."/?p=picture&i=".$picture->getId()
					);
				}

				$this->getFlashes()->add('success', "Comment has been posted successfully.");
				$this->redirect('/?p=picture&i='.$picture->getId());
			}
			else
			{
				foreach ($form->getErrors() as $message)
				{
					$this->getFlashes()->add('danger', $message);
				}
			}
		}

		$this->redirect($form->getField('redirect') ?? '/');
	}

}
