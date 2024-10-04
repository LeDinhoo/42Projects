FROM debian:buster

RUN apt-get update -y && apt-get -y upgrade && \
    apt-get install -y openssl nginx && \
    mkdir -p /etc/nginx/ssl && \
    chmod 777 /etc/nginx/ssl && \
    openssl req -newkey rsa:4096 -x509 -sha256 -days 365 -nodes \
       -out /etc/nginx/ssl/server.crt \
       -keyout /etc/nginx/ssl/server.key \
       -subj "/C=FR/ST=Rhone/L=Lyon/O=42_School/OU=42_Lyon/CN=hdupuy.42.fr"

COPY nginx.conf /etc/nginx/conf.d/default.conf

EXPOSE 443

CMD [ "nginx", "-g", "daemon off;" ]