
<?= Service\TemplateService::getPartial('layout/start') ?>

<div class="container">

	<h2>Auth/Register</h2>

	<form method="post" class="form">
		<div class="form__row">
			<label for="lb-username">Username</label>
			<input type="text" name="username" id="lb-username" minlength="3" maxlength="21" required>
			<ul class="list form__info">
				<li>Username must be between 3 and 21 characters long.</li>
				<li>Username can contains letters (a-z, A-Z), digits (0-9), underscore (_), and hyphen (-).</li>
			</ul>
		</div>

		<div class="form__row">
			<label for="lb-password">Password</label>
			<input type="password" name="password" id="lb-password" minlength="8" required>
			<ul class="list form__info">
				<li>Password must be at least 8 characters long.</li>
			</ul>
		</div>

		<div class="form__row">
			<label for="lb-confirm-password">Password confirmation</label>
			<input type="password" name="password-confirm" id="lb-confirm-password" minlength="8" required>
			<ul class="list form__info">
				<li>Password confirmation must match previously provided password.</li>
			</ul>
		</div>

		<div class="form__row">
			<label for="lb-email">Email</label>
			<input type="email" name="email" id="lb-email" required>
			<ul class="list form__info">
				<li>An email will be sent to validate your registration.</li>
			</ul>
		</div>

		<div class="form__row">
			<input type="hidden" name="_csrf" value="<?= $_csrf_token ?>">

			<button type="submit" name="auth-register-form" class="btn btn--primary rounded">
				Register
			</button>
		</div>
	</form>

</div>

<?= Service\TemplateService::getPartial('layout/end') ?>
