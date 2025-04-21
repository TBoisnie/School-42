<?php

namespace Controller;

use Form\Like\LikeForm;
use Model\Like;
use Repository\LikeRepository;
use Repository\PictureRepository;

class LikeController
	extends AbstractController
{

	public function create() : never
	{
		$this->unauthorizedUnless($this->getUser());

		$form = new LikeForm();

		if ($form->isSubmitted())
		{
			$form->validateFromGlobals();

			if ($form->isValid())
			{
				$picture = (new PictureRepository)->get($form->getField('picture_id'));

				$this->notFoundUnless($picture !== null);

				try {
					(new LikeRepository)->create(
						(new Like())
							->setPicture($picture)
							->setAuthor($this->getUser())
					);

					$_user = $this->getUser()->setLikes([ ...$this->getUser()->getLikes(), $picture->getId() ]);
					$this->setUser($_user);

					$this->getFlashes()->add('success', "Picture has been liked.");
				}
				catch (\Throwable $th)
				{
					// Already liked, do nothing
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

		$this->redirect($form->getField('redirect') ?? '/');
	}

	public function delete() : never
	{
		$this->unauthorizedUnless($this->getUser());

		$form = new LikeForm();

		if ($form->isSubmitted())
		{
			$form->validateFromGlobals();

			if ($form->isValid())
			{
				$picture = (new PictureRepository)->get($form->getField('picture_id'));

				$this->notFoundUnless($picture !== null);

				(new LikeRepository)->delete(
					(new Like())
					->setPicture($picture)
					->setAuthor($this->getUser())
				);

				$_user = $this->getUser()->setLikes(
					\array_filter($this->getUser()->getLikes(), fn($like) =>
						$like !== $picture->getId()
					)
				);
				$this->setUser($_user);

				$this->getFlashes()->add('info', "Picture like has been removed.");
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
