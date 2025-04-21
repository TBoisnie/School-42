<?php

namespace Service;


class PaginationService
{

	// Constants
	private const PAGE_SIZE = 10;
	// Attributes
	protected int $size;
	protected int $current;
	protected int $max;

	//
	// Constructor
	//
	public function __construct(
		int $count,
		int $size = self::PAGE_SIZE,
	)
	{
		$this->size = \abs($size);
		$this->__updateCurrent();
		$this->__updateMax($count);
	}

	//
	// Getters
	//
	public function getCurrent() : int
	{
		return $this->current;
	}

	public function getSize() : int
	{
		return $this->size;
	}

	public function getMax() : int
	{
		return $this->max;
	}

	//
	// Utilities
	//
	private function __updateCurrent() : void
	{
		$offset = (int)($_GET['o'] ?? 0);
		$this->current = $offset >= 0 ? $offset : 0;
	}

	private function __updateMax($count) : void
	{
		$this->max = \ceil($count / $this->size);
	}

}