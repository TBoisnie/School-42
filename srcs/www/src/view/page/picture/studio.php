
<?= Service\TemplateService::getPartial('layout/start') ?>

<div class="container page-studio">

	<main>
		<h2>App/Studio</h2>

		<div id="screen" class="screen card rounded">
			<video class="fit-content center" autoplay></video>
			<canvas class="fit-container fit-content center"></canvas>
			<img class="fit-container fit-content center" src="img/overlay/anonymous.png" alt="">
		</div>

		<div id="controls" class="controls">
			<input type="file" accept="image/*;capture=camera" style="display: none;">
			<button class="btn btn--secondary btn--clear rounded">Clear</button>
			<button class="btn btn--primary btn--take">File</button>
			<button class="btn btn--secondary btn--camera rounded">Enable Camera</button>
		</div>

		<form id="form-studio" method="post" enctype="multipart/form-data">
			<fieldset id="overlays" class="overlays">
				<ul class="list list--row">
					<?php foreach ($overlays as $name) { ?>
						<li>
							<label>
								<input type="radio" name="overlay" value="<?= $name ?>" form="form-studio" style="display: none;">
								<img src="img/overlay/<?= $name ?>" class="overlay" alt="<?= $name ?>">
							</label>
						</li>
					<?php } ?>
				</ul>
			</fieldset>
			<input type="hidden" name="photo" value="">
			<input type="hidden" name="_csrf" value="<?= $_csrf_token ?>">
			<button type="submit" name="studio-form" class="btn btn--primary rounded">Save</button>
		</form>
	</main>

	<div class="history">
		<h3>History</h3>

		<?php if (!empty($pictures)) { ?>
			<ul class="list">
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
		<?php } else { ?>
			No picture found in your history.
		<?php } ?>

		<?=
			Service\TemplateService::getPartial('partial/pagination', [
				'page' => $page,
				'link' => "?p=studio"
			])
		?>
	</div>

</div>

<script>
	(async function() {

		const Screen = {
			// Properties
			_video:   document.querySelector("#screen video"),
			_photo:   document.querySelector("#screen canvas"),
			_overlay: document.querySelector("#screen img"),

			// Methods
			init()
			{
				this._photo.width = 1280;
				this._photo.height = 720;
				this._photo.getContext('2d').imageSmoothingEnabled = true;

				return this;
			},

			getVideo()
			{
				return this._video;
			},

			setVideo(stream)
			{
				if (stream)
				{
					this.clear();
				}

				this._video.srcObject = stream;

				return this;
			},

			setPhoto(image_or_video)
			{
				this.clear();

				const max_width = this._photo.width;
				const max_height = this._photo.height;

				let width = image_or_video.videoWidth ?? image_or_video.width;
				let height = image_or_video.videoHeight ?? image_or_video.height;

				const ratio = width / height;

				// Scale width
				width = Math.max(Math.min(width, max_width), max_width);
				height = width / ratio;

				// Scale height
				height = Math.min(height, max_height);
				width = height * ratio;

				// Position center
				const dx = (max_width - width) / 2;
				const dy = (max_height - height) / 2;

				// Draw
				this._photo.getContext('2d').drawImage(image_or_video, dx, dy, width, height);

				// Update form for upload
				Form.setPhoto(this._photo.toDataURL());

				return this;
			},

			setOverlay(overlay)
			{
				this._overlay.src = overlay;
				return this;
			},

			clear()
			{
				this._photo.getContext('2d').clearRect(0, 0, this._photo.width, this._photo.height);
				return this;
			}
		};

		const Camera = {
			// Properties
			_stream: null,

			// Methods
			getStream()
			{
				return this._stream;
			},

			isEnabled()
			{
				return this._stream !== null;
			},

			async enable()
			{
				try
				{
					this._stream = await navigator.mediaDevices.getUserMedia({ audio: false, video: true });
				}
				catch (err)
				{
					// console.log("No camera detected.");
				}

				return this;
			},

			async disable()
			{
				if (this.isEnabled())
				{
					this._stream.getVideoTracks().forEach( (track) => track.stop() );
					this._stream = null;
				}

				return this;
			},

			async toggle()
			{
				if (this.isEnabled())
				{
					await this.disable();
				}
				else
				{
					await this.enable();
				}

				return this;
			},
		};

		const Form = {
			// Properties
			_photo: document.querySelector("#form-studio input[name='photo']"),
			_overlays: document.querySelectorAll("#overlays input[type='radio']"),
			_overlays_ctn: document.querySelector("#overlays"),

			// Methods
			reset()
			{
				this._overlays_ctn.addEventListener('click', this.handleOverlay);

				this._photo.value = "";
				this._overlays[0].click();

				return this;
			},

			setPhoto(url_encoded_photo)
			{
				this._photo.value = url_encoded_photo.replace(/^(data:image\/png;base64,)/, "");
				return this;
			},

			async handleOverlay(ev)
			{
				const target = ev.target;

				if (target.attributes.name?.value === 'overlay')
				{
					Screen.setOverlay(target.parentElement.querySelector("img").src);
				}
			},
		};

		const Controls = {
			// Properties
			_file:   document.querySelector("#controls input[type='file']"),
			_camera: document.querySelector("#controls .btn--camera"),
			_take:   document.querySelector("#controls .btn--take"),
			_clear:  document.querySelector("#controls .btn--clear"),

			// Methods
			init()
			{
				this._file.addEventListener('change', this.handleFile.bind(this));
				this._camera.addEventListener('click', this.handleCamera.bind(this));
				this._take.addEventListener('click', this.handleTake.bind(this));
				this._clear.addEventListener('click', this.handleClear.bind(this));

				return this;
			},

			async handleFile(ev)
			{
				const file = ev.target.files[0];

				if (!file)
				{
					return ;
				}

				if (!file.type.match('image\/[png|jpeg]'))
				{
					this._file.value = null;
					return ;
				}

				const reader = new FileReader();
				const img = new Image();

				reader.readAsDataURL(file);

				reader.onload = (event) =>
				{
					if (event.target.readyState == FileReader.DONE)
					{
						img.src = event.target.result;
						img.onload = () => {
							Screen.setPhoto(img);
						};
					}
				};
			},

			async handleCamera(ev)
			{
				const was_enabled = Camera.isEnabled();

				Screen.setVideo((await Camera.toggle()).getStream());

				const is_enabled = Camera.isEnabled();

				this._camera.innerHTML = is_enabled ? "Disable Camera"
					: (was_enabled !== is_enabled) ? "Enable Camera" : "No Webcam Available";
				this._take.innerHTML = Camera.isEnabled() ? "Snap" : "File";
			},

			async handleTake(ev)
			{
				if (!Camera.isEnabled())
				{
					this._file.click();
					return ;
				}

				Screen.setPhoto(Screen.getVideo());
			},

			async handleClear(ev)
			{
				Form.reset();
				Screen.clear();
			},
		};

		//
		// Run
		//
		Screen.init();
		Form.reset();
		Controls.init();

	})();
</script>

<?= Service\TemplateService::getPartial('layout/end') ?>
