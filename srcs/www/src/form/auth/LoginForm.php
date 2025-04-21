<?php

namespace Form\Auth;

use Form\AbstractForm;


class LoginForm
	extends AbstractForm
{

	protected function validate() : void
	{
		if (empty($this->_post['username']) || empty($this->_post['password']))
		{
			$this->_errors['credentials'] = "Invalid credentials.";
		}
	}

	protected function getName() : string
	{
		return "auth-login-form";
	}

}
