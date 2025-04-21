FROM php:8.1-fpm-alpine

# Install requirements
RUN apk add --update --no-cache \
    zlib \
    libpq \
    libpng \
    libxpm \
    libwebp \
    freetype \
    libjpeg-turbo \
    msmtp

# Enable php-extensions
RUN apk add --no-cache --virtual build-essentials \
        zlib-dev \
        libpq-dev \
        libpng-dev \
        libxpm-dev \
        libwebp-dev \
        freetype-dev \
        libjpeg-turbo-dev \
    && docker-php-ext-configure gd \
        --enable-gd \
        --with-xpm \
        --with-jpeg \
        --with-webp \
        --with-freetype \
    && docker-php-ext-install -j$(nproc) \
        gd \
        exif \
        pdo_pgsql \
    && apk del build-essentials \
    && rm -rf /usr/src/php*

# Set 'www-data' UID to allow PHP to write file in 'public/img'
RUN apk --no-cache add shadow && \
    usermod -u 1000 www-data

COPY ./generate_ssl.sh  /tmp/generate_ssl.sh
RUN  chmod +x           /tmp/generate_ssl.sh

ENTRYPOINT [ "/tmp/generate_ssl.sh" ]
CMD [ "php-fpm" ]
