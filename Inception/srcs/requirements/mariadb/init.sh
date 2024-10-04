#!/bin/bash
chown -R mysql:mysql /var/lib/mysql
mysql_install_db --datadir=/var/lib/mysql --user=mysql --skip-test-db >> /dev/null

echo "Initialisation de la base de données"
mysqld --user=mysql --bootstrap --silent-startup << _EOF_
FLUSH PRIVILEGES;

CREATE DATABASE IF NOT EXISTS \`${WORDPRESS_DATABASE_NAME}\`;
CREATE USER IF NOT EXISTS \`${WORDPRESS_MYSQL_USER}\`@'%' IDENTIFIED BY '${WORDPRESS_MYSQL_PASSWORD}';
GRANT ALL PRIVILEGES ON \`${WORDPRESS_DATABASE_NAME}\`.* TO \`${WORDPRESS_MYSQL_USER}\`@'%';

ALTER USER \`root\`@\`localhost\` IDENTIFIED BY '${MYSQL_ROOT_PASSWORD}';
GRANT ALL PRIVILEGES ON *.* TO 'root'@'localhost' WITH GRANT OPTION;

FLUSH PRIVILEGES;
_EOF_

echo "Base de données initialisée"
exec mysqld_safe
