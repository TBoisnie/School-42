
<?php
	$anchor ??= '';

	// Number of items to show at start/end, and around active page.
	$range_ = 2;
	$boundaries_ = [
		[
			'low' => 0,
			'high' => \min($range_, $page->getCurrent() - $range_)
		],
		/* 'gap' => */ !!($page->getCurrent() > 2 * $range_),
		[
			'low' => \max(0, $page->getCurrent() - $range_),
			'high' => \min($page->getCurrent() + $range_ + 1, $page->getMax())
		],
		/* 'gap' => */ !!($page->getCurrent() < $page->getMax() - 2 * $range_),
		[
			'low' => \max($page->getCurrent() + $range_ + 1, $page->getMax() - $range_),
			'high' => $page->getMax()
		]
	];
?>

<ul class="list list--row pagination rounded">
	<?php
	foreach ($boundaries_ as $gap_or_boundary_)
	{
		if (\is_array($gap_or_boundary_))
		{
			$boundary_ = $gap_or_boundary_;

			for ($i = $boundary_['low']; $i < $boundary_['high']; ++$i)
			{
				?>
				<a href="<?= $link ?>&o=<?= $i ?><?= $anchor ?>" class="pagination__item rounded <?= $i === $page->getCurrent() ? 'active' : '' ?>">
					<?= $i + 1 ?>
				</a>
				<?php
			}
		}
		else if ($gap_or_boundary_ === true)
		{
			?>
			<span class="pagination__item">...</span>
			<?php
		}
	}
	?>
</ul>
