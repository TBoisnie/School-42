<?php

namespace Service;


class MailService
{

	public static function send(string $to, string $subject, string $message) : bool
	{
		$message = \wordwrap($message, 70, "\r\n");

		$sent = \mail($to, $subject, $message, [
			'Content-Type' => "text/plain; charset=utf-8",
			'From' => 'kurobayashi.bin@gmail.com',
		]);

		if (!$sent)
		{
			// throw new \Exception("MailService: Error - Mail not sent.");
		}

		return $sent;
	}

}
