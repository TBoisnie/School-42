<?php

namespace Form\Auth;

use Form\AbstractForm;


class RegisterForm
	extends AbstractForm
{

	protected function validate() : void
	{
		if (empty($this->_post['username']) || !preg_match("/^[\w-]{3,21}$/", $this->_post['username']))
		{
			$this->_errors['username'] = "Invalid username.";
		}

		if (empty($this->_post['password']) || mb_strlen($this->_post['password']) < 8)
		{
			$this->_errors['password'] = "Invalid password.";
		}

		if (empty($this->_post['password-confirm']) || $this->_post['password'] !== $this->_post['password-confirm'])
		{
			$this->_errors['password-confirm'] = "Password confirmation mismatch.";
		}

		if (empty($this->_post['email']) || !filter_var($this->_post['email'], FILTER_VALIDATE_EMAIL))
		{
			$this->_errors['email'] = "Invalid email.";
		}
	}

	protected function getName(): string
	{
		return "auth-register-form";
	}

}
