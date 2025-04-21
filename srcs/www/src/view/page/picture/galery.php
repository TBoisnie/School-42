
<?= Service\TemplateService::getPartial('layout/start') ?>

<div class="container page-galery">

	<h2>App/Galery</h2>

	<?php if (!empty($pictures)) { ?>
		<ul class="list pictures">
			<?php foreach ($pictures as $picture) { ?>
				<li id="p<?= $picture->getId() ?>">
					<?=
						Service\TemplateService::getPartial('partial/card', [
							'picture' => $picture,
							'clickable' => true,
							'redirect' => $_SERVER["REQUEST_URI"]."#p".$picture->getId(),
						])
					?>
				</li>
			<?php } ?>
		</ul>

		<?=
			Service\TemplateService::getPartial('partial/pagination', [
				'page' => $page,
				'link' => "?p=galery"
			])
		?>
	<?php } else { ?>
		No picture found. Be the first to <a href="?p=studio">post one</a>!
	<?php } ?>

</div>

<?= Service\TemplateService::getPartial('layout/end') ?>