<?php

namespace Form\Like;

use Form\AbstractForm;


class LikeForm extends AbstractForm
{

	protected function validate() : void
	{
		if (empty($this->_post['picture_id']) || !\filter_var($this->_post['picture_id'], FILTER_VALIDATE_INT, ["options" => ["min_range" => 0]]))
		{
			$this->_errors['picture_id'] = "Invalid picture ID.";
		}
	}

	public function getName() : string
	{
		return 'like-form';
	}

}
