FROM debian:buster

RUN apt-get update -y && apt-get -y upgrade
RUN apt-get install -y mariadb-server

COPY init.sh init.sh
COPY 50-server.conf /etc/mysql/mariadb.conf.d/50-server.cnf

RUN chmod +x /init.sh && \
    chmod 600 /etc/mysql/mariadb.conf.d/50-server.cnf && \
    mkdir -p /var/run/mysqld && \
    chmod 777 /var/run/mysqld

EXPOSE 3306

ENTRYPOINT [ "/init.sh" ]