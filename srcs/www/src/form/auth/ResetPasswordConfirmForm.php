<?php

namespace Form\Auth;

use Form\AbstractForm;


class ResetPasswordConfirmForm
	extends AbstractForm
{

	protected function validate() : void
	{
		if (empty($this->_post['password']) || mb_strlen($this->_post['password']) < 8)
		{
			$this->_errors['password'] = "Invalid password.";
		}

		if (empty($this->_post['password-confirm']) || $this->_post['password'] !== $this->_post['password-confirm'])
		{
			$this->_errors['password-confirm'] = "Password confirmation mismatch.";
		}
	}

	protected function getName(): string
	{
		return "auth-reset-password-confirm-form";
	}

}
