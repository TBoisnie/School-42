
<?= Service\TemplateService::getPartial('layout/start') ?>

<div class="container">

	<h2>Auth/ResetPasswordConfirm</h2>

	<form method="post" class="form">
		<div class="form__row">
			<label for="lb-password">Password</label>
			<input type="password" name="password" id="lb-password">
			<ul class="list form__info">
				<li>Password must be at least 8 characters long.</li>
			</ul>
		</div>

		<div class="form__row">
			<label for="lb-password-confirm">Password confirmation</label>
			<input type="password" name="password-confirm" id="lb-password-confirm">
			<ul class="list form__info">
				<li>Password confirmation must match previously provided password.</li>
			</ul>
		</div>

		<div class="form__row">
			<input type="hidden" name="_csrf" value="<?= $_csrf_token ?>">

			<button type="submit" name="auth-reset-password-confirm-form" class="btn btn--primary">
				Update Password
			</button>
		</div>
	</form>

</div>

<?= Service\TemplateService::getPartial('layout/end') ?>
