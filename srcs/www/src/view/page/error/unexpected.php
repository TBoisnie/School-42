
<?= Service\TemplateService::getPartial('layout/start') ?>

<div class="container">

	<h2>Error/Unexpected</h2>

	<p>
		500 - Oups... Something went wrong!
	</p>

	<!-- <pre> -->
		<?php //var_dump(get_defined_vars()); ?>
	<!-- </pre> -->

</div>

<?= Service\TemplateService::getPartial('layout/end') ?>
