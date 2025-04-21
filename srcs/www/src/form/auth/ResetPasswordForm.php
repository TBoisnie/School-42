<?php

namespace Form\Auth;

use Form\AbstractForm;


class ResetPasswordForm
	extends AbstractForm
{

	protected function validate() : void
	{
		if (empty($this->_post['username']))
		{
			$this->_errors['username'] = "Username must be provided.";
		}

		if (empty($this->_post['email']))
		{
			$this->_errors['email'] = "Email must be provided.";
		}
	}

	protected function getName(): string
	{
		return "auth-reset-password-form";
	}

}
