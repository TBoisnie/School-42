
<?= Service\TemplateService::getPartial('layout/start') ?>

<div class="container">

	<h2>Auth/ResetPassword</h2>

	<form method="post" class="form">
		<div class="form__row">
			<label for="lb-username">Username</label>
			<input type="text" name="username" id="lb-username">
		</div>

		<div class="form__row">
			<label for="lb-email">Email</label>
			<input type="email" name="email" id="lb-email">
		</div>

		<div class="form__row">
			<input type="hidden" name="_csrf" value="<?= $_csrf_token ?>">

			<button type="submit" name="auth-reset-password-form" class="btn btn--primary rounded">
				Reset Password
			</button>
		</div>
	</form>

</div>

<?= Service\TemplateService::getPartial('layout/end') ?>
