FROM nginx:alpine

COPY ./generate_ssl.sh  /tmp/generate_ssl.sh
RUN  chmod +x           /tmp/generate_ssl.sh

ENTRYPOINT [ "/tmp/generate_ssl.sh" ]
CMD ["nginx", "-g", "daemon off;"]
