--
-- Schemas
--
CREATE TABLE IF NOT EXISTS "users"
(
	"id"         SERIAL       PRIMARY KEY,
	"username"   VARCHAR(50)  NOT NULL UNIQUE,
	"password"   VARCHAR(255) NOT NULL,
	"email"      VARCHAR(255) NOT NULL UNIQUE,
	"notify"     BOOLEAN      NOT NULL DEFAULT TRUE,
	"verified"   BOOLEAN      NOT NULL DEFAULT FALSE,
	"secret_key" VARCHAR(255) NULL
);

CREATE TABLE IF NOT EXISTS "pictures"
(
	"id"        SERIAL       PRIMARY KEY,
	"id_author" INTEGER      REFERENCES "users" ON DELETE CASCADE,
	"path"      VARCHAR(255) NOT NULL UNIQUE
);

CREATE TABLE IF NOT EXISTS "comments"
(
	"id"         SERIAL  PRIMARY KEY,
	"id_author"  INTEGER REFERENCES "users" ON DELETE CASCADE,
	"id_picture" INTEGER REFERENCES "pictures" ON DELETE CASCADE,
	"content"    TEXT    NOT NULL
);

CREATE TABLE IF NOT EXISTS "likes"
(
	"id_author"  INTEGER REFERENCES "users" ON DELETE CASCADE,
	"id_picture" INTEGER REFERENCES "pictures" ON DELETE CASCADE,
	PRIMARY KEY ("id_author", "id_picture")
);

--
-- Fixtures
--
INSERT INTO "users"
	("username", "password", "email", "notify", "verified")
VALUES
	('qwe',       '$2y$10$AD2//KhVSZ0YAm40Q2hr7OdYuai.0u.If7NoRGAAP8vCWLltc3H4K', 'qwe@qwe.qwe', FALSE, TRUE),
	('Random-42', '$2y$10$AD2//KhVSZ0YAm40Q2hr7OdYuai.0u.If7NoRGAAP8vCWLltc3H4K', 'random42@domain.com', FALSE, FALSE),
	('Azhalya',   '$2y$10$AD2//KhVSZ0YAm40Q2hr7OdYuai.0u.If7NoRGAAP8vCWLltc3H4K', 'azhalya@domain.com', TRUE, TRUE)
; -- Password: qwe

INSERT INTO "pictures"
	("id_author", "path")
VALUES
	(1, 'pokemon.png'),
	(1, 'mewtwo.png'),
	(3, 'bulbizar.png'),
	(3, 'salameche.png'),
	(3, 'carapuce.png'),
	(3, 'evoli.png')
;

INSERT INTO "comments"
	("id_author", "id_picture", "content")
VALUES
	(1, 1, 'First!'),
	(3, 1, '<insert random toxic content here>'),
	(3, 3, '<script>alert("H@ck3R");</script>'),
	(1, 3, 'What a wonderful picture!'),
	(2, 4, 'This is a spam. This is a spam. This is a spam. This is a spam. This is a spam. This is a spam. This is a spam. This is a spam.'),
	(2, 4, 'This is a spam. This is a spam. This is a spam. This is a spam. This is a spam. This is a spam. This is a spam. This is a spam.'),
	(2, 4, 'This is a spam. This is a spam. This is a spam. This is a spam. This is a spam. This is a spam. This is a spam. This is a spam.'),
	(2, 4, 'This is a spam. This is a spam. This is a spam. This is a spam. This is a spam. This is a spam. This is a spam. This is a spam.'),
	(2, 4, 'This is a spam. This is a spam. This is a spam. This is a spam. This is a spam. This is a spam. This is a spam. This is a spam.'),
	(2, 4, 'This is a spam. This is a spam. This is a spam. This is a spam. This is a spam. This is a spam. This is a spam. This is a spam.'),
	(2, 4, 'This is a spam. This is a spam. This is a spam. This is a spam. This is a spam. This is a spam. This is a spam. This is a spam.'),
	(2, 4, 'This is a spam. This is a spam. This is a spam. This is a spam. This is a spam. This is a spam. This is a spam. This is a spam.'),
	(2, 4, 'This is a spam. This is a spam. This is a spam. This is a spam. This is a spam. This is a spam. This is a spam. This is a spam.'),
	(2, 4, 'This is a spam. This is a spam. This is a spam. This is a spam. This is a spam. This is a spam. This is a spam. This is a spam.'),
	(2, 4, 'This is a spam. This is a spam. This is a spam. This is a spam. This is a spam. This is a spam. This is a spam. This is a spam.'),
	(2, 4, 'This is a spam. This is a spam. This is a spam. This is a spam. This is a spam. This is a spam. This is a spam. This is a spam.'),
	(2, 4, 'This is a spam. This is a spam. This is a spam. This is a spam. This is a spam. This is a spam. This is a spam. This is a spam.'),
	(2, 4, 'This is a spam. This is a spam. This is a spam. This is a spam. This is a spam. This is a spam. This is a spam. This is a spam.'),
	(2, 4, 'This is a spam. This is a spam. This is a spam. This is a spam. This is a spam. This is a spam. This is a spam. This is a spam.'),
	(2, 4, 'This is a spam. This is a spam. This is a spam. This is a spam. This is a spam. This is a spam. This is a spam. This is a spam.'),
	(2, 4, 'This is a spam. This is a spam. This is a spam. This is a spam. This is a spam. This is a spam. This is a spam. This is a spam.'),
	(2, 4, 'This is a spam. This is a spam. This is a spam. This is a spam. This is a spam. This is a spam. This is a spam. This is a spam.'),
	(2, 4, 'This is a spam. This is a spam. This is a spam. This is a spam. This is a spam. This is a spam. This is a spam. This is a spam.'),
	(2, 4, 'This is a spam. This is a spam. This is a spam. This is a spam. This is a spam. This is a spam. This is a spam. This is a spam.'),
	(2, 4, 'This is a spam. This is a spam. This is a spam. This is a spam. This is a spam. This is a spam. This is a spam. This is a spam.')
;

INSERT INTO "likes"
	("id_author", "id_picture")
VALUES
	(1, 1),
	(1, 2),
	(1, 4),
	(2, 3),
	(2, 4),
	(3, 1),
	(3, 2),
	(3, 3),
	(3, 4),
	(3, 5),
	(3, 6)
;