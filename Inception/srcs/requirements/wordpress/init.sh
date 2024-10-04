#!/bin/bash
if [ ! -d /run/php ]
then
    service php7.3-fpm start
    service php7.3-fpm stop
fi

if [[ ${WORDPRESS_ADMIN_USER,,} == *"admin"* ]]
then
    echo "Erreur : le nom d'utilisateur administrateur ne peut pas contenir le mot 'admin'"
    exit
fi

if [[ ${WORDPRESS_ADMIN_PASSWORD,,} == *${WORDPRESS_ADMIN_USER,,}* ]]
then
    echo "Erreur : le mot de passe administrateur ne peut pas contenir le nom d'utilisateur"
    exit
fi

sleep 12

if [ ! -f /var/www/html/wp-config.php ]
then
    echo "wp-config.php non trouvé : installation de WordPress"
    wp core download --allow-root --path=/var/www/html --locale=fr_FR
    wp config create --allow-root --dbname="${WORDPRESS_DATABASE_NAME}" --dbuser="${WORDPRESS_MYSQL_USER}" --dbpass="${WORDPRESS_MYSQL_PASSWORD}" --dbhost="${WORDPRESS_DATABASE_HOST}"
    wp core install --allow-root --url="${DOMAIN_NAME}" --title="${WORDPRESS_SITE_TITLE}" --admin_name="${WORDPRESS_ADMIN_USER}" --admin_password="${WORDPRESS_ADMIN_PASSWORD}" --admin_email="${WORDPRESS_ADMIN_EMAIL}" --skip-email
    wp user create --allow-root "${WORDPRESS_USER_NAME}" "${WORDPRESS_USER_EMAIL}" --user_pass="${WORDPRESS_USER_PASSWORD}" --role=author
    echo "WordPress installé"
else
    echo "WordPress déjà téléchargé ; installation ignorée"
fi

echo "Lancement de PHP-FPM"
/usr/sbin/php-fpm7.3 -F