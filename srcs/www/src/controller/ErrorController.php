<?php

namespace Controller;


class ErrorController extends AbstractController
{

	// Constants
	protected const VIEW_ROOT = 'page/error';

	//
	// Not Found
	//
	public function notFound() : string
	{
		\header('Status: 404 - Not Found');

		return $this->render('not-found');
	}

	//
	// Unauthorized
	//
	public function unauthorized() : string
	{
		\header('Status: 403 - Unauthorized');

		return $this->render('unauthorized');
	}

	//
	// Unexpected
	//
	public function unexpected(\Throwable $error) : string
	{
		\header('Status: 500 - Internal Server Error');

		return $this->render('unexpected', [
			'exception' => $error,
		]);
	}

}
