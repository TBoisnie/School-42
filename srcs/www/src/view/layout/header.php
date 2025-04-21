
<header class="main-header">
	<nav class="main-nav">
		<ul class="list list--row">
			<li>
				<a href="/" title="Home">
					<span class="material-icons">home</span>
				</a>
			</li>
			<li>
				<a href="?p=galery" title="Galery">
					<span class="material-icons">collections</span>
				</a>
			</li>
			<?php if (!empty($_user)) { ?>
				<li>
					<a href="?p=studio" title="Studio">
						<span class="material-icons">palette</span>
					</a>
				</li>
			<?php } ?>
		</ul>
	</nav>
	<nav>
		<ul class="list list--row">
			<?php if (isset($_user)) { ?>
				<li>
					<a href="?p=profile" title="Profile">
						<span class="material-icons">account_circle</span>
					</a>
				</li>
				<li>
					<a href="?p=logout" title="Logout">
						<span class="material-icons">logout</span>
					</a>
				</li>
			<?php } else { ?>
				<li>
					<a href="?p=register" title="Register">
						<span class="material-icons">person_add</span>
					</a>
				</li>
				<li>
					<a href="?p=login" title="Login">
						<span class="material-icons">login</span>
					</a>
				</li>
			<?php } ?>
		</ul>
	</nav>
</header>

<?= Service\TemplateService::getPartial('layout/flashes') ?>
