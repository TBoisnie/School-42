
<?= Service\TemplateService::getPartial('layout/start') ?>

<div class="container">

	<h2>App/Picture</h2>

	<?= Service\TemplateService::getPartial('partial/card', [
		'redirect' => $_SERVER["REQUEST_URI"],
	]) ?>

	<?php if (isset($_user)) { ?>
		<h3>Post a comment</h3>

		<form method="post" action="?p=comment" class="form">
			<div class="form__row">
				<label for="lb-content" style="display: none">Content:</label>
				<textarea name="content" id="lb-content" class="form__field" rows="4" minlength="8" maxlength="250" required placeholder="Write your comment here..."></textarea>
				<ul class="list form__info">
					<li>Can contains between 8 and 250 characters.</li>
				</ul>
			</div>

			<div class="form__row">
				<input type="hidden" name="picture_id" value="<?= $picture->getId() ?>">
				<input type="hidden" name="_csrf" value="<?= $_csrf_token ?>">
				<input type="hidden" name="redirect" value="<?= htmlspecialchars($_SERVER["REQUEST_URI"]) ?>">

				<button type="submit" name="comment-form" class="btn btn--primary rounded">Publish</button>
			</div>
		</form>
	<?php } ?>

	<h3 id="comments">Comments</h3>

	<?php if (!empty($comments)) { ?>
		<ul class="list">
			<?php foreach ($comments as $comment) { ?>
				<li>
					<?= Service\TemplateService::getPartial('partial/comment', [
						'comment' => $comment
					]) ?>
				</li>
			<?php } ?>
		</ul>
	<?php } else { ?>
		No comments found.
	<?php } ?>

	<?=
		Service\TemplateService::getPartial('partial/pagination', [
			'page' => $page,
			'link' => "?p=picture&i={$picture->getId()}",
			'anchor' => "#comments"
		])
	?>
</div>

<?= Service\TemplateService::getPartial('layout/end') ?>
