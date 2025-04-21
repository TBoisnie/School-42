<?php

namespace Controller;

use Enum\OverlayType;
use Form\Picture\DeleteForm;
use Form\Picture\StudioForm;
use Model\Picture;
use Repository\PictureRepository;
use Repository\CommentRepository;
use Service\FileService;
use Service\PaginationService;


class PictureController extends AbstractController
{
	// Constants
	protected const VIEW_ROOT = 'page/picture';


	//
	// Galery
	//
	public function galery() : string
	{
		$count = (new PictureRepository)->getCount();
		$page = new PaginationService($count);
		$pictures = (new PictureRepository)->getPage($page);

		// page != 0 and no pictures (page does not exist)
		$this->notFoundUnless($page->getCurrent() === 0 || !empty($pictures));

		return $this->render('galery', [
			'pictures' => $pictures,
			'page' => $page,
		]);
	}

	//
	// Studio
	//
	public function studio() : string
	{
		$this->unauthorizedUnless($this->getUser());

		$form = new StudioForm();

		if ($form->isSubmitted())
		{
			$form->validateFromGlobals();

			if ($form->isValid())
			{
				// Base
				$photo = $form->getPhoto();
				$overlay = $form->getOverlay();

				// Montage
				$picture_width = 1280;
				$picture_height = 720;

				$dx = ($picture_width  - \imagesx($overlay)) / 2;
				$dy = ($picture_height - \imagesy($overlay)) / 2;

				\imagecopy($photo, $overlay, (int)$dx, (int)$dy, 0, 0, \imagesx($overlay), \imagesy($overlay));
				\imagealphablending($photo, false);
				\imagesavealpha($photo, true);

				// Output
				$picture_path = $this->getUser()->getId() . "_" . \microtime(true) . ".png";
				\imagepng($photo, FileService::toPublicPath(['img/picture', $picture_path]));

				// Save
				$picture = (new Picture)
					->setAuthor($this->getUser())
					->setPath($picture_path)
				;

				(new PictureRepository)->create($picture);

				$this->getFlashes()->add('success', "Picture has been saved succesfully.");
			}
			else
			{
				foreach ($form->getErrors() as $message)
				{
					$this->getFlashes()->add('danger', $message);
				}
			}
		}

		// History
		$count = (new PictureRepository)->getCount($this->getUser());
		$page = new PaginationService($count, 3);
		$pictures = (new PictureRepository)->getPageFor($this->getUser(), $page);

		// Prevent submit on refresh
		if ($form->isSubmitted() && $form->isValid() && isset($pictures[0]))
		{
			$this->redirect('/?p=picture&i='.$pictures[0]->getId());
		}

		return $this->render('studio', [
			'overlays' => \array_map(fn($c)=> $c->value, OverlayType::cases()),
			'pictures' => $pictures,
			'page'    => $page
		]);
	}

	//
	// Picture
	//
	public function picture() : string
	{
		$id = (int)($_GET['i'] ?? -1);
		$picture = (new PictureRepository)->get($id);

		$this->notFoundUnless($picture !== null);

		$count = (new CommentRepository)->getCountFor($picture);
		$page = new PaginationService($count);
		$comments = (new CommentRepository)->getPageFor($page, $picture);

		return $this->render('picture', [
			'picture' => $picture,
			'comments' => $comments,
			'page' => $page,
		]);
	}

	public function delete() : void
	{
		$this->unauthorizedUnless($this->getUser());

		$form = new DeleteForm();

		if ($form->isSubmitted())
		{
			$form->validateFromGlobals();

			if ($form->isValid())
			{
				$picture = (new PictureRepository)->get($form->getField('picture_id'));

				$this->notFoundUnless($picture !== null);
				$this->unauthorizedUnless($picture->getAuthor()->getId() === $this->getUser()->getId());

				(new PictureRepository)->delete($picture);

				$path = FileService::toPublicPath(["img", "picture", $picture->getPath()]);
				if (\file_exists($path))
				{
					\unlink($path);
				}

				// Remove associated like from user session
				$_user = $this->getUser()->setLikes(
					\array_filter($this->getUser()->getLikes(), fn($like) =>
						$like !== $picture->getId()
					)
				);
				$this->setUser($_user);

				$this->getFlashes()->add('info', "Picture has been deleted.");
			}
			else
			{
				foreach ($form->getErrors() as $message)
				{
					$this->getFlashes()->add('danger', $message);
				}
			}
		}

		$this->redirect('/');
	}
}
