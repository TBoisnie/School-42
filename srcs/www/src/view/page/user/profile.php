
<?= Service\TemplateService::getPartial('layout/start') ?>

<div class="container">

	<h2>User/Profile</h2>

	ID: <?= $target->getId() ?><br>
	Username: <?= htmlspecialchars($target->getUsername()) ?><br>
	Email: <?= htmlspecialchars($target->getEmail()) ?><br>
	Notification: <?= $target->getNotify() ? "Yes" : "No" ?>

	<?php if (isset($_user) && $_user->getId() === $target->getId()) { ?>
		<hr>

		<a href="/?p=edit">Edit my profile</a>
	<?php } ?>
</div>

<?= Service\TemplateService::getPartial('layout/end') ?>
