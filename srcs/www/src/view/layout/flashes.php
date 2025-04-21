
<?php if ($_flashes->hasAny()) { ?>
	<div class="container flashes">
		<?php foreach ($_flashes->getAll() as $type => $messages) { ?>
			<?php foreach ($messages as $message) { ?>
				<div class="flash flash--<?= $type ?>"><?= $message ?></div>
			<?php } ?>
		<?php } ?>
	</div>
<?php } ?>
