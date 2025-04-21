
<?= Service\TemplateService::getPartial('layout/start') ?>

<div class="container">

	<h2>Auth/Login</h2>

	<form method="post" class="form">
		<div class="form__row">
			<label for="lb-username">Username</label>
			<input type="text" name="username" id="lb-username">
		</div>

		<div class="form__row">
			<label for="lb-password">Password</label>
			<input type="password" name="password" id="lb-password">
		</div>

		<div class="form__row">
			<input type="hidden" name="_csrf" value="<?= $_csrf_token ?>">

			<button type="submit" name="auth-login-form" class="btn btn--primary rounded">
				Login
			</button>
		</div>
	</form>

	<hr>

	<a href="?p=reset-password">Forgotten password?</a>

</div>

<?= Service\TemplateService::getPartial('layout/end') ?>
