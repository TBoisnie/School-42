<?php

namespace Form\Comment;

use Form\AbstractForm;


class CommentForm
	extends AbstractForm
{

	protected function validate() : void
	{
		if (!isset($this->_post['content']) || mb_strlen($this->_post['content']) < 8 || mb_strlen($this->_post['content']) > 250)
		{
			$this->_errors['content'] = "Comment's content must be between 8 and 250 characters long.";
		}
	}

	protected function getName(): string
	{
		return "comment-form";
	}

}
