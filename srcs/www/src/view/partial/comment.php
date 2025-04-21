
<?php
	$author = $comment->getAuthor()->getUsername();
?>

<div class="comment rounded">
	<header class="comment__header">
		<address>
			By
			<a rel="author" href="?p=profile&u=<?= urlencode($author) ?>">
				<?= htmlspecialchars($author) ?>
			</a>
		</address>
	</header>
	<div class="comment__content">
		<p><?= nl2br(htmlspecialchars($comment->getContent())) ?></p>
	</div>
</div>
