FROM node:22-alpine

RUN apk update
RUN apk upgrade
RUN apk add --no-cache ffmpeg
