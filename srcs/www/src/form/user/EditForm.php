<?php

namespace Form\User;

use Form\AbstractForm;


class EditForm
	extends AbstractForm
{

	protected function validate() : void
	{
		if (empty($this->_post['username']) || !preg_match("/^[\w-]{3,21}$/", $this->_post['username']))
		{
			$this->_errors['username'] = "Invalid username.";
		}

		if (empty($this->_post['email']) || !filter_var($this->_post['email'], FILTER_VALIDATE_EMAIL))
		{
			$this->_errors['email'] = "Invalid email.";
		}

		$this->_post['notify'] = filter_var($this->_post['notify'] ?? "off", FILTER_VALIDATE_BOOL);

		if (!empty($this->_post['new-password']) && mb_strlen($this->_post['new-password']) < 8)
		{
			$this->_errors['new-password'] = "Invalid new password.";
		}

		if (!empty($this->_post['new-password']) && $this->_post['new-password'] !== $this->_post['new-password-confirm'])
		{
			$this->_errors['new-password-confirm'] = "New password confirmation mismatch.";
		}
	}

	protected function getName(): string
	{
		return "user-edit-form";
	}

}
