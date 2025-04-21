<?php

namespace Form\Picture;

use Enum\OverlayType;
use Form\AbstractForm;
use Service\FileService;


class StudioForm
	extends AbstractForm
{
	// Constants
	private const PHOTO_MAX_SIZE = 3000000;

	//
	// Public
	//
	public function getPhoto() : \GdImage|false
	{
		return \imagecreatefromstring(\base64_decode($this->_post['photo']));
	}

	public function getOverlay() : \GdImage|false
	{
		return \imagecreatefrompng(FileService::toPublicPath(['img/overlay', $this->_post['overlay']]));
	}

	//
	// Protected
	//
	protected function validate() : void
	{
		$accepted_format = ['image/png'];

		if (empty($this->_post['photo']))
		{
			$this->_errors['photo'] = "You must provide a photo.";
		}
		else
		{
			$info = @\getimagesizefromstring(\base64_decode($this->_post['photo']));

			if (!$info || !\in_array($info['mime'], $accepted_format))
			{
				$this->_errors['photo'] = "Provided file must be an image (PNG).";
			}

			// Get image size as if it was a file
			// Base-64 algorithm increases the image size up to 33%
			if ((int)(strlen(rtrim($this->_post['photo'], '=')) * 0.75) > self::PHOTO_MAX_SIZE)
			{
				$this->_errors['photo'] = "Provided image is to heavy (3mb max).";
			}
		}

		if (!isset($this->_post['overlay']) || OverlayType::fromString($this->_post['overlay']) === null)
		{
			$this->_errors['overlay'] = "Overlay must be one of the defined selection.";
		}
	}

	protected function getName() : string
	{
		return "studio-form";
	}

}
