
<figure class="card rounded">
	<?php if (!empty($clickable)) { ?>
		<a href="?p=picture&i=<?= $picture->getId() ?>">
		<?php } ?>
			<img src="img/picture/<?= $picture->getPath() ?>" alt="Photo Montage by <?= htmlspecialchars($picture->getAuthor()->getUsername()) ?>" class="card__picture">
		<?php if (!empty($clickable)) { ?>
		</a>
	<?php } ?>
	<figcaption class="card__details">
		<address>
			By
			<a rel="author" href="?p=profile&u=<?= urlencode($picture->getAuthor()->getUsername()) ?>">
				<?= htmlspecialchars($picture->getAuthor()->getUsername()) ?>
			</a>
		</address>

		<?php if (!empty($_user)) { ?>
			<div style="display: flex;">
				<?php if ($picture->getAuthor()->getId() === $_user->getId()) { ?>
					<form method="post" action="?p=delete">
						<input type="hidden" name="picture_id" value="<?= $picture->getId() ?>">
						<input type="hidden" name="_csrf" value="<?= $_csrf_token ?>">

						<button type="submit" name="picture-delete-form" class="btn btn--sm btn--secondary">
							<span class="material-icons">delete</span>
						</button>
					</form>
				<?php } ?>

				<?php $type = \in_array($picture->getId(), $_user->getLikes()) ? 'unlike' : 'like'; ?>

				<form method="post" action="?p=<?= $type ?>">
					<input type="hidden" name="picture_id" value="<?= $picture->getId() ?>">
					<input type="hidden" name="redirect" value="<?= htmlspecialchars($redirect) ?>">
					<input type="hidden" name="_csrf" value="<?= $_csrf_token ?>">

					<button type="submit" name="like-form" class="btn btn--sm btn--primary" title="<?= $type === 'unlike' ? 'Unlike' : 'Like' ?>">
						<span class="material-icons"><?= $type === 'unlike' ? 'thumb_down' : 'thumb_up' ?></span>
					</button>
				</form>
			</div>
		<?php } ?>
	</figcaption>
</figure>
