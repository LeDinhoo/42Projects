# Projet Inception : Déploiement de WordPress avec Docker

## Introduction

Ce projet, nommé "Inception", consiste à déployer une infrastructure WordPress complète utilisant Docker. L'architecture comprend trois services principaux : Nginx (serveur web), WordPress (application PHP), et MariaDB (base de données), chacun fonctionnant dans son propre conteneur Docker.

## Prérequis

- Docker et Docker Compose installés sur votre système
- Make (pour utiliser le Makefile)
- Un système d'exploitation compatible (testé sur Debian Buster)
- Au moins 8 Go d'espace disque disponible

# Sommaire

1. [Makefile](#makefile)
2. [Docker Compose](#docker-compose)
3. [Nginx](#nginx)
   1. [Dockerfile](#nginx-dockerfile)
   2. [Configuration](#nginx-configuration)
4. [MariaDB](#mariadb)
   1. [Dockerfile](#mariadb-dockerfile)
   2. [Script d'initialisation](#mariadb-init-script)
   3. [Configuration](#configuration-mariadb)
5. [WordPress](#wordpress)
   1. [Dockerfile](#wordpress-dockerfile)
   2. [Script d'initialisation](#wordpress-init-script)
   3. [Configuration PHP-FPM](#wordpress-php-fpm-configuration)

# Sommaire - Configuration de la Machine Virtuelle pour Inception

1. [Téléchargement de l'image Debian](#1-téléchargement-de-limage-debian)
2. [Création et configuration de la machine virtuelle](#2-création-et-configuration-de-la-machine-virtuelle)
3. [Démarrage de la VM et sélection de l'image Debian](#3-démarrage-de-la-vm-et-sélection-de-limage-debian)
4. [Installation de Debian](#4-installation-de-debian)
5. [Connexion en tant que root](#5-connexion-en-tant-que-root)
6. [Installation des paquets nécessaires et démarrage de l'environnement graphique](#6-installation-des-paquets-nécessaires-et-démarrage-de-lenvironnement-graphique)
7. [Configuration de SSH pour permettre la connexion root](#7-configuration-de-ssh-pour-permettre-la-connexion-root)
8. [Configuration du pare-feu UFW](#8-configuration-du-pare-feu-ufw)
9. [Configuration de la redirection de ports et connexion SSH à distance](#9-configuration-de-la-redirection-de-ports-et-connexion-ssh-à-distance)
   1. [Configuration de la redirection de ports dans VirtualBox](#91-configuration-de-la-redirection-de-ports-dans-virtualbox)
   2. [Vérification du service SSH et connexion à distance](#92-vérification-du-service-ssh-et-connexion-à-distance)
10. [Configuration de sudo et ajout de l'utilisateur au groupe Docker](#10-configuration-de-sudo-et-ajout-de-lutilisateur-au-groupe-docker)
    1. [Configuration de sudo](#101-configuration-de-sudo)
    2. [Ajout de l'utilisateur au groupe Docker](#102-ajout-de-lutilisateur-au-groupe-docker)
11. [Test de la configuration et clonage du projet Inception](#11-test-de-la-configuration-et-clonage-du-projet-inception)
    1. [Passage à l'utilisateur normal](#111-passage-à-lutilisateur-normal)
    2. [Clonage du projet Inception](#112-clonage-du-projet-inception)
12. [Lancement du projet Inception avec Docker Compose](#12-lancement-du-projet-inception-avec-docker-compose)


## Structure du projet
```
📦inception
 ┣ 📂srcs
 ┃ ┣ 📂requirements
 ┃ ┃ ┣ 📂mariadb
 ┃ ┃ ┃ ┣ 📜50-server.conf
 ┃ ┃ ┃ ┣ 📜Dockerfile
 ┃ ┃ ┃ ┗ 📜init.sh
 ┃ ┃ ┣ 📂nginx
 ┃ ┃ ┃ ┣ 📜Dockerfile
 ┃ ┃ ┃ ┗ 📜nginx.conf
 ┃ ┃ ┗ 📂wordpress
 ┃ ┃ ┃ ┣ 📜Dockerfile
 ┃ ┃ ┃ ┣ 📜init.sh
 ┃ ┃ ┃ ┗ 📜www.conf
 ┃ ┣ 📜.env
 ┃ ┗ 📜docker-compose.yml
 ┗ 📜Makefile
```

# Makefile

## Explication du Makefile

### Variables

```makefile
VOLUME_DIR = /home/$(USER)/data
WP_DIR = $(VOLUME_DIR)/wordpress
DB_DIR = $(VOLUME_DIR)/mariadb
DOCKER_FILE = ./srcs/docker-compose.yml
```

- `VOLUME_DIR` : Chemin du répertoire de données de l'utilisateur.
- `WP_DIR` : Chemin du répertoire WordPress dans le volume.
- `DB_DIR` : Chemin du répertoire MariaDB dans le volume.
- `DOCKER_FILE` : Chemin du fichier docker-compose.yml.

### Cibles factices

```makefile
.PHONY: all up down re clean fclean
```

Déclare que ces cibles ne correspondent pas à des fichiers réels.

### Cible par défaut

```makefile
all: up
```

Exécute la cible 'up' par défaut.

### Création des répertoires

```makefile
$(VOLUME_DIR) $(WP_DIR) $(DB_DIR):
	mkdir -p $@
```

Crée les répertoires nécessaires s'ils n'existent pas.

### Cible 'up'

```makefile
up: $(WP_DIR) $(DB_DIR)
	docker-compose -f $(DOCKER_FILE) up --build
```

- Dépend de la création des répertoires WP_DIR et DB_DIR.
- Lance les conteneurs avec docker-compose en mode détaché et reconstruit les images.

### Cible 'down'

```makefile
down:
	docker-compose -f $(DOCKER_FILE) down
```

Arrête et supprime les conteneurs définis dans le fichier docker-compose.

### Cible 're'

```makefile
re: down up
```

Exécute 'down' puis 'up' pour redémarrer les conteneurs.

### Cible 'clean'

```makefile
clean: down
	docker system prune -af --volumes
	sudo rm -rf $(WP_DIR) $(DB_DIR) $(VOLUME_DIR)
```

- Arrête les conteneurs.
- Supprime tous les conteneurs, réseaux et volumes docker non utilisés.
- Supprime les répertoires de données.

### Cible 'fclean'

```makefile
fclean: clean
	docker builder prune --all -f
```

- Exécute 'clean'.
- Supprime tous les caches de construction Docker.

Ce Makefile est conçu pour gérer un environnement Docker contenant WordPress et MariaDB. Il offre des commandes pour démarrer, arrêter, nettoyer et reconstruire l'environnement facilement.

# Docker Compose

Je vais vous expliquer en détail ce fichier docker-compose.yml que j'ai créé pour notre projet Inception. Ce fichier définit l'architecture de notre application, qui se compose de trois services principaux : nginx, WordPress et MariaDB. Voici une explication approfondie de chaque section :

## Services

### 1. Service nginx

```yaml
nginx:
  restart: always
  container_name: nginx
  build:
    dockerfile: Dockerfile
    context: ./requirements/nginx
  volumes:
    - wordpress:/var/www/html
  networks:
    - inception_network
  env_file:
    - .env
  ports:
    - "443:443"
  depends_on:
    - wordpress
```

- `restart: always` : Cette option assure que le conteneur nginx redémarre automatiquement en cas d'arrêt, même après un redémarrage de l'hôte Docker. C'est crucial pour maintenir la disponibilité de notre serveur web.
- `build` : Spécifie comment construire l'image Docker pour nginx. Le Dockerfile se trouve dans `./requirements/nginx`.
- `volumes` : Monte le volume 'wordpress' dans le conteneur, permettant à nginx d'accéder aux fichiers WordPress.
- `networks` : Connecte le conteneur au réseau 'inception_network'.
- `env_file` : Utilise les variables d'environnement définies dans le fichier .env.
- `ports` : Expose le port 443 (HTTPS) du conteneur vers l'hôte.
- `depends_on` : Indique que nginx dépend du service WordPress, assurant que WordPress démarre avant nginx.

### 2. Service WordPress

```yaml
wordpress:
  restart: always
  container_name: wordpress
  build:
    dockerfile: Dockerfile
    context: ./requirements/wordpress
  volumes:
    - wordpress:/var/www/html
  networks:
    - inception_network
  env_file:
    - .env
  ports:
    - 9000:9000
  depends_on:
    - mariadb
```

La configuration est similaire à celle de nginx, avec quelques différences clés :
- `ports` : Expose le port 9000, utilisé par PHP-FPM pour communiquer avec nginx.
- `depends_on` : WordPress dépend de MariaDB, assurant que la base de données est prête avant le démarrage de WordPress.

### 3. Service MariaDB

```yaml
mariadb:
  restart: always
  container_name: mariadb
  build:
    dockerfile: Dockerfile
    context: ./requirements/mariadb
  volumes:
    - mariadb:/var/lib/mysql
  networks:
    - inception_network
  env_file:
    - .env
  ports:
    - 3306:3306
```

La configuration de MariaDB est similaire aux autres services, avec une différence notable :
- `volumes` : Utilise un volume spécifique 'mariadb' pour stocker les données de la base de données, assurant leur persistance.

## Networks

```yaml
networks:
  inception_network:
    driver: bridge
```

J'ai défini un réseau nommé 'inception_network' utilisant le driver 'bridge'. Ce type de réseau crée un réseau privé interne à l'hôte Docker, permettant aux conteneurs de communiquer entre eux tout en les isolant du réseau de l'hôte. C'est idéal pour notre configuration car cela offre une sécurité accrue et une isolation appropriée.

## Volumes

```yaml
volumes:
  mariadb:
    name: mariadb
    driver: local
    driver_opts:
      o: bind
      type: none
      device: /home/dupuy/data/mariadb

  wordpress:
    name: wordpress
    driver: local
    driver_opts:
      o: bind
      type: none
      device: /home/dupuy/data/wordpress
```

J'ai défini deux volumes pour la persistance des données :

1. `mariadb` : Pour stocker les données de la base de données.
2. `wordpress` : Pour stocker les fichiers WordPress.

Pour chaque volume :
- `driver: local` indique que le volume sera stocké sur le système de fichiers local de l'hôte Docker.
- Les `driver_opts` sont configurées pour monter directement des répertoires de l'hôte dans les conteneurs (bind mount). Cela permet un accès facile aux fichiers depuis l'hôte, ce qui est particulièrement utile pour le développement et le débogage.

Cette configuration assure que les données persistent même si les conteneurs sont arrêtés ou supprimés, et permet une gestion facile des fichiers directement depuis l'hôte.

# Nginx

## Nginx Dockerfile

Je vais vous expliquer en détail le Dockerfile que j'ai créé pour le service Nginx de notre projet Inception. Ce fichier définit comment construire l'image Docker pour notre serveur web Nginx. Voici une explication approfondie de chaque instruction :

```dockerfile
FROM debian:buster
```
J'ai choisi Debian Buster comme image de base pour sa stabilité et son support à long terme. Bien qu'une version plus récente pourrait offrir des packages plus à jour, Buster offre un bon équilibre entre stabilité et actualité des packages.

```dockerfile
RUN apt-get update -y && apt-get -y upgrade
```
Cette commande met à jour la liste des paquets disponibles et effectue une mise à niveau du système. C'est une bonne pratique pour s'assurer que nous travaillons avec les dernières versions des paquets.

```dockerfile
RUN apt-get install -y openssl
```
J'installe OpenSSL pour la gestion des certificats SSL/TLS. OpenSSL est essentiel pour générer et gérer les certificats nécessaires au HTTPS. Bien qu'il existe des alternatives comme LibreSSL ou GnuTLS, OpenSSL reste le choix le plus courant et le mieux supporté.

```dockerfile
RUN apt-get install -y nginx
```
Ici, j'installe le serveur web Nginx. J'ai choisi Nginx pour sa légèreté et ses performances, particulièrement efficace pour servir du contenu statique et comme proxy inverse. Son architecture événementielle non-bloquante lui permet de gérer efficacement de nombreuses connexions simultanées avec une faible empreinte mémoire.

```dockerfile
RUN mkdir -p /etc/nginx/ssl
RUN chmod 777 /etc/nginx/ssl
```
Je crée un répertoire pour stocker les certificats SSL et lui attribue des permissions larges (777). Dans un environnement de production, il serait préférable d'utiliser des permissions plus restrictives (comme 750) et de s'assurer que seuls les utilisateurs nécessaires y ont accès.

```dockerfile
RUN openssl req -newkey rsa:4096 -x509 -sha256 -days 365 -nodes \
       -out /etc/nginx/ssl/server.crt \
       -keyout /etc/nginx/ssl/server.key \
       -subj "/C=FR/ST=Rhone/L=Lyon/O=42_School/OU=42_Lyon/CN=hdupuy.42.fr"
```
Cette commande génère un certificat SSL auto-signé. Bien que pratique pour le développement, un tel certificat n'est pas reconnu par les navigateurs et ne devrait pas être utilisé en production. Dans un environnement de production, il faudrait obtenir un certificat d'une autorité reconnue (comme Let's Encrypt) et le configurer correctement.

```dockerfile
COPY nginx.conf /etc/nginx/conf.d/default.conf
```
Je copie le fichier de configuration Nginx dans le conteneur. Ce fichier définit probablement les paramètres du serveur HTTPS, les chemins des certificats SSL, et d'autres configurations spécifiques à notre application.

```dockerfile
EXPOSE 443
```
J'indique que le conteneur utilisera le port 443 (HTTPS). Si nous voulions gérer aussi le trafic HTTP et le rediriger vers HTTPS, nous pourrions exposer le port 80 et configurer Nginx en conséquence.

```dockerfile
CMD [ "nginx", "-g", "daemon off;" ]
```
Enfin, je démarre Nginx en mode premier plan avec l'option "daemon off". Cette approche est préférable dans un environnement conteneurisé car elle permet à Docker de gérer correctement le cycle de vie du processus, facilite la collecte des logs, et assure que le conteneur s'arrête proprement si Nginx s'arrête.


## Nginx Configuration

Je vais vous expliquer en détail ce fichier de configuration Nginx que j'ai créé pour notre projet Inception. Ce fichier définit comment notre serveur Nginx doit gérer les requêtes entrantes pour notre application WordPress. Voici une explication approfondie de chaque section :

```nginx
server {
    listen 443 ssl;
    listen [::]:443 ssl;
```
Ces lignes configurent le serveur pour écouter les connexions HTTPS sur le port 443, à la fois pour IPv4 et IPv6. C'est essentiel pour assurer que toutes les connexions à notre site sont sécurisées via SSL/TLS.

```nginx
    root /var/www/html;
```
Cette ligne définit le répertoire racine où Nginx cherchera les fichiers à servir. C'est le répertoire standard pour les fichiers web dans de nombreuses configurations, et il correspond probablement au point de montage de notre volume WordPress.

```nginx
    index index.php index.html index.htm;
```
Ceci spécifie l'ordre de priorité des fichiers index. Nginx cherchera d'abord index.php, puis index.html, et enfin index.htm. Cette configuration est optimale pour WordPress, qui utilise principalement des fichiers PHP.

```nginx
    server_name hdupuy.42.fr;
```
Cette ligne définit le nom de domaine du serveur. C'est crucial pour que Nginx sache quel bloc server utiliser pour les requêtes adressées à ce domaine spécifique.

```nginx
    ssl_certificate     /etc/nginx/ssl/server.crt;
    ssl_certificate_key /etc/nginx/ssl/server.key;
```
Ces lignes spécifient l'emplacement du certificat SSL et de sa clé privée. Ces fichiers sont essentiels pour établir des connexions HTTPS sécurisées.

```nginx
    ssl_protocols       TLSv1.2 TLSv1.3;
```
Cette directive définit les protocoles SSL/TLS autorisés. TLSv1.2 et TLSv1.3 sont actuellement les versions les plus sécurisées et recommandées.

```nginx
    location / {
        try_files $uri $uri/ /index.php?$args;
    }
```
Ce bloc gère les requêtes pour la racine du site. La directive `try_files` permet de servir des fichiers statiques directement, ou de passer à WordPress si aucun fichier n'est trouvé.

```nginx
    location ~ \.php$ {
        include snippets/fastcgi-php.conf;
        fastcgi_pass wordpress:9000;
        fastcgi_split_path_info ^(.+\.php)(/.+)$;
    }
```
Ce bloc gère les requêtes pour les fichiers PHP. Il inclut la configuration FastCGI standard pour PHP, puis passe les requêtes PHP au service WordPress sur le port 9000. Cela permet à Nginx de communiquer avec le processus PHP-FPM dans le conteneur WordPress. La directive `fastcgi_split_path_info` est nécessaire pour le bon fonctionnement de certains scripts PHP, notamment dans WordPress.


# MariaDB

## MariaDB Dockerfile

Je vais vous expliquer en détail ce Dockerfile que j'ai créé pour le service MariaDB de notre projet Inception. Ce fichier définit comment construire l'image Docker pour notre serveur de base de données. Voici une explication approfondie de chaque instruction :

```dockerfile
FROM debian:buster
```
J'ai choisi Debian Buster comme image de base pour sa stabilité et sa compatibilité avec MariaDB. Cette version de Debian offre un bon équilibre entre stabilité et actualité des packages.

```dockerfile
RUN apt-get update -y && apt-get -y upgrade
RUN apt-get install -y mariadb-server
```
Ces commandes mettent à jour le système et installent MariaDB Server. J'utilise l'option `-y` pour automatiser les réponses aux prompts d'installation, ce qui est nécessaire dans un environnement Docker non interactif.

```dockerfile
COPY init.sh init.sh
COPY 50-server.conf /etc/mysql/mariadb.conf.d/50-server.cnf
```
Je copie deux fichiers importants dans le conteneur :
1. `init.sh` : un script d'initialisation pour configurer et démarrer MariaDB.
2. `50-server.conf` : un fichier de configuration personnalisé pour MariaDB.

```dockerfile
RUN chmod +x /init.sh
RUN chmod 600 /etc/mysql/mariadb.conf.d/50-server.cnf
```
Je configure les permissions des fichiers copiés. Le script `init.sh` est rendu exécutable, et le fichier de configuration MariaDB reçoit des permissions restrictives (600) pour des raisons de sécurité.

```dockerfile
RUN mkdir -p /var/run/mysqld
RUN chmod 777 /var/run/mysqld
```
Je prépare l'environnement pour l'exécution de MariaDB en créant le répertoire `/var/run/mysqld` et en lui attribuant des permissions permissives. Bien que 777 soit nécessaire pour le fonctionnement de MariaDB dans ce contexte, il faut noter que ces permissions larges pourraient être considérées comme un risque de sécurité dans certains environnements.

```dockerfile
EXPOSE 3306
```
Cette instruction informe Docker que le conteneur écoutera sur le port 3306, qui est le port standard utilisé par MariaDB pour les connexions client.

```dockerfile
ENTRYPOINT [ "/init.sh" ]
```
Je définis le point d'entrée du conteneur comme étant le script `init.sh`. Ce script sera responsable de l'initialisation et du démarrage de MariaDB lorsque le conteneur démarrera.

Quelques points supplémentaires à considérer :

1. Sécurité : L'utilisation de `chmod 600` pour le fichier de configuration est une bonne pratique, mais les permissions 777 sur `/var/run/mysqld` pourraient être affinées.

2. Configuration : Le contenu du fichier `50-server.conf` devrait être examiné pour s'assurer qu'il suit les meilleures pratiques de configuration de MariaDB.

3. Initialisation : Le script `init.sh` joue un rôle crucial. Il devrait configurer la base de données initiale, créer les utilisateurs et les bases de données nécessaires, appliquer les paramètres de sécurité, et démarrer le service MariaDB.

4. Optimisation : Les commandes RUN pourraient être combinées pour réduire le nombre de couches dans l'image Docker, améliorant ainsi légèrement les performances et réduisant la taille de l'image.

5. Mise à jour et maintenance : L'utilisation de Debian:buster implique que les mises à jour de sécurité dépendent de la maintenance de cette image. Une stratégie de mise à jour régulière devrait être envisagée.

6. Environnement de production : Pour un déploiement en production, des considérations supplémentaires seraient nécessaires, comme la gestion des sauvegardes, la journalisation, et l'utilisation de secrets pour les mots de passe.

## MariaDB Init Script

Je vais vous expliquer en détail ce script bash que j'ai créé pour initialiser et configurer notre base de données MariaDB dans le contexte de notre projet Inception. Ce script est crucial pour la mise en place correcte de notre environnement de base de données. Voici une explication approfondie de chaque section :

```bash
#!/bin/bash
```
Cette ligne, appelée "shebang", indique que ce script doit être exécuté par le shell bash.

```bash
chown -R mysql:mysql /var/lib/mysql
mysql_install_db --datadir=/var/lib/mysql --user=mysql --skip-test-db >> /dev/null
```
Ces commandes préparent l'environnement pour MariaDB :
- `chown` change le propriétaire du répertoire de données de MariaDB pour s'assurer que l'utilisateur mysql a les bonnes permissions.
- `mysql_install_db` initialise le répertoire de données de MariaDB. L'option `--skip-test-db` évite la création de bases de données de test inutiles.

```bash
echo "Initiating database"
mysqld --user=mysql --bootstrap --silent-startup << _EOF_
# ... (commandes SQL)
_EOF_
```
Cette section utilise la technique "here document" pour passer un script SQL directement à mysqld en mode bootstrap. Ce mode permet d'exécuter des commandes SQL sans démarrer complètement le serveur MySQL.

Les commandes SQL exécutées sont :

```sql
FLUSH PRIVILEGES;

CREATE DATABASE IF NOT EXISTS `${MYSQL_DTBS_NAME}`;
CREATE USER IF NOT EXISTS `${MYSQL_USER_NAME}`@'%' IDENTIFIED BY '${MYSQL_USER_PSWD}';
GRANT ALL PRIVILEGES ON `${MYSQL_DTBS_NAME}`.* TO `${MYSQL_USER_NAME}`@'%';

ALTER USER `root`@`localhost` IDENTIFIED BY '${MYSQL_ROOT_PSWD}';
GRANT ALL PRIVILEGES ON *.* TO 'root'@'localhost' WITH GRANT OPTION;

FLUSH PRIVILEGES;
```

Ces commandes :
1. Réinitialisent les privilèges.
2. Créent la base de données spécifiée par la variable d'environnement `MYSQL_DTBS_NAME`.
3. Créent un utilisateur avec le nom et le mot de passe spécifiés par les variables d'environnement.
4. Accordent tous les privilèges à cet utilisateur sur la base de données créée.
5. Modifient le mot de passe de l'utilisateur root.
6. Accordent tous les privilèges à root sur toutes les bases de données.
7. Rafraîchissent à nouveau les privilèges pour s'assurer que tous les changements sont pris en compte.

```bash
echo "Database initiated"
exec mysqld_safe
```
Ces lignes finales indiquent que l'initialisation est terminée et lancent le serveur MariaDB en utilisant `mysqld_safe`, qui est un script de démarrage recommandé pour MariaDB en production.

Quelques points importants à noter :
- L'utilisation de variables d'environnement (`${MYSQL_DTBS_NAME}`, etc.) permet une configuration flexible du script.
- Le script gère à la fois la création initiale de la base de données et la configuration des utilisateurs.
- L'utilisation de `IF NOT EXISTS` dans les commandes SQL assure que le script peut être exécuté plusieurs fois sans erreur.
- Le script accorde des privilèges larges, ce qui pourrait nécessiter des ajustements pour un environnement de production plus sécurisé.


## Configuration MariaDB

Je comprends, voici l'explication dans le format que j'utilisais précédemment :

Ce fichier de configuration MariaDB, que j'ai créé pour notre projet Inception, définit les paramètres de base pour notre serveur MariaDB. Voici une explication détaillée de chaque ligne :

```
[mysqld]
```
Cette section définit les paramètres pour le démon MySQL (mysqld), qui est le processus serveur principal de MariaDB.

```
user = mysql
```
Cette ligne définit l'utilisateur système sous lequel le serveur MariaDB s'exécutera. L'utilisation de l'utilisateur 'mysql' est une pratique standard pour des raisons de sécurité.

```
port = 3306
```
Ceci spécifie le port sur lequel MariaDB écoutera les connexions. 3306 est le port standard pour MySQL/MariaDB.

```
datadir = /var/lib/mysql
```
Cette ligne indique le répertoire où MariaDB stockera ses fichiers de données. Ce chemin est standard dans la plupart des installations Linux.

```
socket = /var/run/mysqld/mysqld.sock
```
Ceci définit l'emplacement du fichier socket Unix pour les connexions locales. Ce socket permet une communication efficace entre le serveur et les clients sur la même machine.

```
bind-address=*
```
Cette ligne permet au serveur d'écouter les connexions sur toutes les interfaces réseau. L'astérisque (*) signifie "toutes les adresses IP". C'est nécessaire dans un environnement conteneurisé pour permettre les connexions depuis d'autres conteneurs.

Quelques points supplémentaires à noter :
- Cette configuration est minimaliste et adaptée à un environnement de développement conteneurisé.
- Pour un environnement de production, des paramètres supplémentaires seraient nécessaires, notamment pour la sécurité et les performances.
- L'option `bind-address=*` devrait être utilisée avec précaution dans un environnement de production, car elle ouvre le serveur à des connexions depuis n'importe quelle adresse IP.

Cette configuration établit les bases pour notre serveur MariaDB, le rendant accessible depuis d'autres conteneurs dans notre environnement Docker tout en maintenant une structure de fichiers standard. Elle est conçue pour fonctionner de manière cohérente avec les autres composants de notre projet Inception, notamment le Dockerfile MariaDB et le script d'initialisation que nous avons discutés précédemment.

# WordPress

## Wordpress Dockerfile

Je vais vous expliquer en détail ce Dockerfile que j'ai créé pour le service WordPress de notre projet Inception. Ce fichier définit comment construire l'image Docker pour notre serveur WordPress. Voici une explication approfondie de chaque instruction :

```dockerfile
FROM debian:buster
```
J'ai choisi Debian Buster comme image de base pour sa stabilité et sa compatibilité. Cette version de Debian offre un bon équilibre entre stabilité et actualité des packages.

```dockerfile
ENV DEBIAN_FRONTEND noninteractive
```
Cette ligne configure l'interface utilisateur de Debian en mode non-interactif, ce qui évite les prompts interactifs lors de l'installation des paquets et pourrait bloquer le build.

```dockerfile
RUN apt-get -y update && apt-get -y upgrade
```
Ces commandes mettent à jour la liste des paquets et effectuent une mise à niveau du système, assurant que nous travaillons avec les dernières versions des paquets.

```dockerfile
RUN apt-get -y install \
    wget \
    php-fpm \
    php-mysql \
    mariadb-client
```
Cette instruction installe les paquets nécessaires :
- wget : pour télécharger WP-CLI
- php-fpm : pour exécuter PHP
- php-mysql : pour la connexion PHP à MySQL/MariaDB
- mariadb-client : pour les interactions avec la base de données depuis le conteneur

```dockerfile
COPY www.conf /etc/php/7.3/fpm/pool.d/
```
Je copie un fichier de configuration personnalisé pour PHP-FPM, permettant d'ajuster la configuration selon nos besoins spécifiques.

```dockerfile
RUN wget https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar
RUN chmod +x wp-cli.phar
RUN mv wp-cli.phar /usr/local/bin/wp
```
Ces commandes installent WP-CLI, un outil en ligne de commande pour gérer WordPress. WP-CLI est crucial pour automatiser l'installation, la configuration et la maintenance de WordPress dans un environnement conteneurisé.

### Résumé de WP-CLI

WP-CLI (WordPress Command Line Interface) est un outil en ligne de commande qui permet d'interagir et de gérer une installation WordPress sans passer par l'interface graphique. Il est particulièrement utile pour les développeurs et administrateurs système qui souhaitent automatiser des tâches répétitives, déployer des sites rapidement, et effectuer des opérations de maintenance de manière efficace.

### Fonctionnalités principales

- **Installation et configuration** : Installez et configurez WordPress rapidement.
- **Gestion des plugins et thèmes** : Installez, activez, désactivez et mettez à jour les plugins et thèmes.
- **Gestion des utilisateurs** : Ajoutez, supprimez et mettez à jour les utilisateurs.
- **Mises à jour** : Mettez à jour WordPress core, plugins et thèmes facilement.
- **Base de données** : Effectuez des sauvegardes, des restaurations et des opérations de maintenance sur la base de données.
- **Options du site** : Gérez les options du site WordPress.

### Deux exemples de commande

1. **Installation de WordPress**

   Cette commande télécharge et configure WordPress en spécifiant les informations de base du site et de l'administrateur.

   ```sh
   wp core install --url="http://example.com" --title="Example Site" --admin_user="admin" --admin_password="password" --admin_email="email@example.com" --allow-root
   ```

   - `--url` : L'URL du site WordPress.
   - `--title` : Le titre du site.
   - `--admin_user` : Le nom d'utilisateur de l'administrateur.
   - `--admin_password` : Le mot de passe de l'administrateur.
   - `--admin_email` : L'email de l'administrateur.

2. **Installation et activation d'un plugin**

   Cette commande installe le plugin Akismet et l'active immédiatement.

   ```sh
   wp plugin install akismet --activate --allow-root
   ```

   - `install akismet` : Télécharge et installe le plugin Akismet.
   - `--activate` : Active le plugin immédiatement après l'installation.

### Avantages de WP-CLI

- **Automatisation** : Facilite l'automatisation des tâches courantes, ce qui réduit les erreurs et économise du temps.
- **Efficacité** : Permet des opérations rapides et efficaces, surtout lors de la gestion de multiples sites WordPress.
- **Scriptabilité** : Les commandes peuvent être intégrées dans des scripts pour des déploiements et des maintenances automatisés.
- **Accès direct** : Offre un accès direct à des fonctionnalités avancées de WordPress sans nécessiter d'interface utilisateur graphique.

WP-CLI est un outil puissant pour quiconque travaille avec WordPress, offrant des fonctionnalités complètes pour la gestion, le déploiement, et la maintenance des sites WordPress via la ligne de commande.

```dockerfile
COPY init.sh /init.sh
RUN chmod +x /init.sh
```
Je copie un script d'initialisation et le rends exécutable. Ce script sera probablement utilisé pour configurer WordPress au démarrage du conteneur.

```dockerfile
EXPOSE 9000
```
Cette ligne expose le port 9000, sur lequel PHP-FPM écoute par défaut, permettant la communication avec Nginx.

```dockerfile
WORKDIR /var/www/html/
```
Je définis le répertoire de travail comme étant l'emplacement standard pour les fichiers web.

```dockerfile
ENTRYPOINT [ "/init.sh" ]
```
Enfin, je définis le point d'entrée du conteneur comme étant le script d'initialisation, qui sera exécuté au démarrage du conteneur.

Points importants à noter :
1. L'utilisation de WP-CLI permet une configuration automatisée et reproductible, idéale pour les environnements conteneurisés.
2. La configuration de PHP-FPM est personnalisée pour s'adapter à nos besoins spécifiques.
3. Le script d'initialisation joue un rôle crucial dans la configuration de WordPress au démarrage du conteneur.

Ce Dockerfile crée une image Docker contenant une installation de WordPress prête à l'emploi, configurée pour fonctionner avec PHP-FPM et communiquer avec notre service MariaDB. Il offre une base solide et flexible pour notre service WordPress dans le projet Inception.

## WordPress Init Script

Je vais vous expliquer en détail ce script bash que j'ai créé pour initialiser et configurer WordPress dans notre environnement conteneurisé pour le projet Inception. Voici une explication approfondie de chaque section :

```bash
if [ ! -d /run/php ]
then
    service php7.3-fpm start
    service php7.3-fpm stop
fi
```
Cette section crée le répertoire nécessaire pour PHP-FPM en démarrant puis arrêtant le service. C'est une astuce pour s'assurer que le répertoire `/run/php` existe, car certaines configurations de PHP-FPM s'attendent à ce qu'il soit présent.

```bash
if [[ ${WP_ADMIN_NAME,,} == *"admin"* ]]
then
    echo "Erreur : le nom d'utilisateur administrateur ne peut pas contenir le mot 'admin'"
    exit
fi

if [[ ${WP_ADMIN_PSWD,,} == *${WP_ADMIN_NAME,,}* ]]
then
    echo "Erreur : le mot de passe administrateur ne peut pas contenir le nom d'utilisateur"
    exit
fi
```
Ces vérifications assurent que le nom d'utilisateur administrateur ne contient pas le mot "admin" et que le mot de passe ne contient pas le nom d'utilisateur. C'est une mesure de sécurité simple mais efficace.

```bash
sleep 12
```
Cette pause de 12 secondes permet de s'assurer que d'autres services, comme la base de données, sont prêts avant de continuer.

```bash
if [ ! -f /var/www/html/wp-config.php ]
then
    echo "wp-config.php non trouvé : installation de WordPress"

    wp core download --allow-root --path=/var/www/html --locale=fr_FR
    wp config create --allow-root --dbname="${MYSQL_DTBS_NAME}" --dbuser="${MYSQL_USER_NAME}" --dbpass="${MYSQL_USER_PSWD}" --dbhost="${WP_DTBS_HOST}"
    wp core install --allow-root --url="${DOMAIN_NAME}" --title="${WP_TITLE}" --admin_name="${WP_ADMIN_NAME}" --admin_password="${WP_ADMIN_PSWD}" --admin_email="${WP_ADMIN_EMAIL}" --skip-email
    wp user create --allow-root "${WP_USER_NAME}" "${WP_USER_EMAIL}" --user_pass="${WP_USER_PSWD}" --role=author

    echo "WordPress installé"
else
    echo "WordPress déjà téléchargé ; installation ignorée"
fi
```
Cette section est le cœur du script. Elle vérifie si WordPress est déjà installé en cherchant le fichier wp-config.php. Si ce fichier n'existe pas, le script procède à l'installation de WordPress :
1. Télécharge les fichiers de base de WordPress.
2. Crée le fichier de configuration avec les détails de la base de données.
3. Installe WordPress et crée le compte administrateur.
4. Crée un utilisateur supplémentaire avec le rôle d'auteur.

L'utilisation de WP-CLI (`wp`) permet d'automatiser tout ce processus.

```bash
echo "Lancement de PHP-FPM"
/usr/sbin/php-fpm7.3 -F
```
Enfin, le script lance PHP-FPM en premier plan. L'option `-F` est cruciale dans un environnement Docker car elle garde PHP-FPM en premier plan, ce qui est nécessaire pour que le conteneur reste actif.

Points importants à noter :
1. Le script effectue des vérifications de sécurité sur les noms d'utilisateur et mots de passe.
2. Il utilise WP-CLI pour automatiser l'installation et la configuration de WordPress.
3. Il crée deux types de comptes (administrateur et auteur) pour une meilleure gestion des rôles et des permissions.
4. Le script est idempotent : il ne réinstalle pas WordPress s'il est déjà présent.

Ce script est crucial pour notre projet Inception car il assure une installation et une configuration cohérentes et automatisées de WordPress dans notre environnement conteneurisé.

## WordPress PHP-FPM Configuration

Je vais vous expliquer en détail ce fichier de configuration PHP-FPM que j'ai créé pour notre projet Inception. Ce fichier, généralement nommé `www.conf`, définit les paramètres pour le pool de processus PHP-FPM qui gèrera notre application WordPress. Voici une explication approfondie de chaque directive :

```
[www]
```
Cette ligne définit le début d'un pool de processus nommé "www". C'est le pool qui gèrera les requêtes PHP pour notre application WordPress.
Un **pool** dans le contexte de PHP-FPM est un groupe de processus configuré pour traiter les requêtes PHP. Chaque pool est défini par un ensemble de paramètres spécifiques (comme le nombre de processus, les utilisateurs, les sockets de communication) et peut être configuré indépendamment pour gérer les requêtes d'applications web distinctes. Par exemple, le pool nommé "www" gère les requêtes PHP pour une application WordPress, optimisant les performances et la sécurité.

```
user = www-data
group = www-data
```
Ces lignes spécifient l'utilisateur et le groupe sous lesquels les processus PHP-FPM s'exécuteront. L'utilisation de "www-data" est une pratique standard pour des raisons de sécurité.

```
listen = wordpress:9000
```
Cette directive configure PHP-FPM pour écouter sur l'adresse "wordpress" et le port 9000. Dans notre environnement Docker, "wordpress" fait référence au nom du service WordPress défini dans le fichier docker-compose.yml.

```
listen.owner = www-data
listen.group = www-data
```
Ces lignes définissent le propriétaire et le groupe du socket d'écoute, assurant que le serveur web (Nginx dans notre cas) a les permissions nécessaires pour communiquer avec PHP-FPM.

```
pm = dynamic
```
Cette option configure le gestionnaire de processus en mode "dynamic", permettant à PHP-FPM d'ajuster dynamiquement le nombre de processus enfants en fonction de la charge du serveur.

```
pm.max_children = 16
pm.start_servers = 4
pm.min_spare_servers = 2
pm.max_spare_servers = 8
```
Ces directives définissent les paramètres du gestionnaire de processus :
- `max_children` : nombre maximum de processus enfants
- `start_servers` : nombre de processus à démarrer initialement
- `min_spare_servers` et `max_spare_servers` : limites pour les processus inactifs

```
chdir = /
```
Cette ligne change le répertoire de travail des processus PHP-FPM vers la racine du système de fichiers.

```
clear_env = no
```
Cette directive cruciale empêche PHP-FPM de nettoyer les variables d'environnement, permettant aux scripts PHP d'accéder aux variables d'environnement définies dans le conteneur Docker.

Points importants à noter :
1. Cette configuration est optimisée pour un environnement WordPress conteneurisé, offrant un bon équilibre entre performance et utilisation des ressources.
2. L'utilisation de "wordpress:9000" pour l'écoute montre une intégration étroite avec l'architecture Docker.
3. Le mode dynamic du gestionnaire de processus permet une adaptation à différentes charges de travail.
4. La directive `clear_env = no` est essentielle pour le fonctionnement correct dans un environnement Docker.

Cette configuration fournit une base solide pour exécuter WordPress avec PHP-FPM dans notre conteneur Docker, offrant un bon équilibre entre performance, sécurité et adaptabilité.








## 1. Téléchargement de l'image Debian

Pour commencer la configuration de notre machine virtuelle, nous allons télécharger l'image ISO de Debian :

1. Rendez-vous sur le site officiel de Debian : [https://www.debian.org/](https://www.debian.org/)
2. Naviguez vers la section "Téléchargements" ou "Downloads".
3. Choisissez la version stable la plus récente de Debian (au moment de la rédaction, il s'agit de Debian 11 "Bullseye").
4. Sélectionnez l'image ISO appropriée pour votre architecture (généralement amd64 pour les systèmes 64 bits).
5. Lancez le téléchargement de l'image ISO.

> Note : Assurez-vous de vérifier l'intégrité du fichier téléchargé en utilisant les sommes de contrôle fournies sur le site de Debian.


## 2. Création et configuration de la machine virtuelle

Après avoir téléchargé l'image Debian, nous allons créer et configurer notre machine virtuelle :

1. Ouvrez votre logiciel de virtualisation (par exemple, VirtualBox ou VMware).
2. Cliquez sur "Nouvelle machine virtuelle" ou équivalent.
3. Nommez la machine virtuelle "Debian".
4. Sélectionnez le type "Linux" et la version "Debian 64-bit".
5. Configurez les ressources de la VM :
   - Mémoire RAM : 4096 MB (4 GB)
   - CPU : 2 cœurs
   - Stockage : 8 GB de disque dur virtuel
6. Laissez les autres paramètres par défaut.
7. Finalisez la création de la VM.

> Note : Assurez-vous que votre système hôte dispose de suffisamment de ressources pour allouer ces spécifications à la VM.


## 3. Démarrage de la VM et sélection de l'image Debian

Une fois la VM créée, nous allons la démarrer et sélectionner l'image Debian pour l'installation :

1. Dans votre logiciel de virtualisation, sélectionnez la VM "Debian" que vous venez de créer.
2. Avant de démarrer la VM, allez dans les paramètres de la machine virtuelle.
3. Dans la section "Stockage" ou "Lecteur", sélectionnez le lecteur CD/DVD virtuel.
4. Cliquez sur l'icône de CD/DVD et choisissez "Choisir un fichier de disque optique virtuel".
5. Naviguez jusqu'à l'emplacement où vous avez téléchargé l'image ISO Debian et sélectionnez-la.
6. Appliquez les changements et fermez la fenêtre des paramètres.
7. Démarrez la VM.
8. La VM devrait maintenant démarrer sur l'image Debian, lançant ainsi le processus d'installation.

> Note : Assurez-vous que l'ordre de démarrage dans les paramètres du BIOS virtuel donne la priorité au lecteur CD/DVD pour permettre le boot sur l'image ISO.



## 4. Installation de Debian

Nous allons maintenant procéder à l'installation de Debian en mode normal non graphique. Voici les étapes clés de l'installation :

1. Au menu de démarrage, sélectionnez "Install" (pas l'option graphique).
2. Configurez les paramètres de base :
   - Langue : Choisissez votre préférence
   - Localisation : Sélectionnez votre pays
   - Configuration du clavier : Choisissez la disposition appropriée
3. Configuration réseau :
   - Hostname : `debian`
   - Domain Name : laissez vide
4. Configuration des utilisateurs :
   - Root password : Choisissez un mot de passe simple (pour l'environnement de développement uniquement)
   - Full name for new user : Votre login (ex: `hdupuy`)
   - Username : Confirmez ou modifiez le nom d'utilisateur suggéré
   - User password : Choisissez un mot de passe simple
5. Partitionnement :
   - Méthode : "Guided - use entire disk"
   - Schéma : "All files in one partition"
6. Configuration supplémentaire :
   - Scan extra installation media : Non
   - Miroir HTTPS : Laissez vide
7. Sélection des logiciels :
   - Décochez toutes les options
   - Cochez uniquement "SSH server"
   > Note : Utilisez la touche Espace pour cocher/décocher et Entrée pour valider
8. Installation du chargeur de démarrage GRUB :
   - Installer GRUB sur le disque principal : Oui
   - Sélectionnez le disque pour l'installation de GRUB

Une fois l'installation terminée, la VM va redémarrer. Retirez l'image ISO du lecteur virtuel si nécessaire pour démarrer sur le disque dur.

> Attention : L'utilisation de mots de passe simples est uniquement recommandée pour un environnement de développement isolé. Pour un environnement de production, utilisez toujours des mots de passe forts.



## 5. Connexion en tant que root

Après le redémarrage de la VM, nous allons nous connecter en tant qu'utilisateur root :

1. À l'invite de connexion, tapez `root` comme nom d'utilisateur.
2. Appuyez sur Entrée.
3. Saisissez le mot de passe root que vous avez défini lors de l'installation.
   > Attention : Les caractères du mot de passe ne s'afficheront pas à l'écran pour des raisons de sécurité.
4. Appuyez sur Entrée pour vous connecter.

> Note : La connexion en tant que root vous donne un contrôle total sur le système. Utilisez ce compte avec précaution, car toute erreur peut avoir des conséquences importantes sur le système.

> Conseil de sécurité : Dans un environnement de production, il est généralement recommandé de désactiver la connexion directe en tant que root et d'utiliser sudo pour les tâches administratives. Cependant, pour notre environnement de développement, nous utiliserons root pour simplifier le processus de configuration.


## 6. Installation des paquets nécessaires et démarrage de l'environnement graphique

Après la connexion en tant que root, nous allons installer les paquets nécessaires et démarrer l'environnement graphique :

```bash
# Mise à jour de la liste des paquets disponibles
apt update

# Installation des paquets nécessaires
apt install -y sudo ufw docker docker-compose make openbox xinit kitty firefox-esr

# Démarrage de l'environnement graphique
startx
```

Explications des commandes :

1. `apt update` : 
   - Met à jour la liste des paquets disponibles dans les dépôts Debian.
   - Assure que nous installons les dernières versions des paquets.

2. `apt install -y [paquets]` :
   - Installe les paquets spécifiés.
   - L'option `-y` répond automatiquement "oui" aux demandes de confirmation.
   - Paquets installés :
     - `sudo` : Permet l'exécution de commandes avec des privilèges élevés.
     - `ufw` : Pare-feu facile à configurer.
     - `docker` : Plateforme de conteneurisation.
     - `docker-compose` : Outil pour définir et exécuter des applications Docker multi-conteneurs.
     - `make` : Outil d'automatisation de la compilation.
     - `openbox` : Gestionnaire de fenêtres léger.
     - `xinit` : Initialise le système X Window.
     - `kitty` : Émulateur de terminal moderne.
     - `firefox-esr` : Navigateur web Firefox Extended Support Release.

3. `startx` :
   - Démarre l'environnement graphique X Window System.
   - Lance Openbox comme gestionnaire de fenêtres.

> Note : L'utilisation de `startx` démarre une session graphique basique. Dans un environnement de production, on utiliserait généralement un gestionnaire de connexion graphique.


## 7. Configuration de SSH pour permettre la connexion root

Après avoir quitté l'environnement graphique (clic droit > Exit), nous allons configurer SSH pour permettre la connexion en tant que root :

1. Ouvrez le fichier de configuration SSH :
   ```bash
   nano /etc/ssh/sshd_config
   ```

2. Dans l'éditeur nano, recherchez et décommentez (retirez le # au début) les lignes suivantes :
   ```
   Port 42
   PermitRootLogin yes
   PasswordAuthentication yes
   ```

   > Note : Permettre la connexion root via SSH est généralement déconseillé pour des raisons de sécurité. Cette configuration est utilisée ici pour simplifier le développement, mais ne devrait pas être utilisée en production.

3. Sauvegardez et quittez nano :
   - Appuyez sur `Ctrl + X`
   - Puis `Y` pour confirmer la sauvegarde
   - Enfin `Enter` pour confirmer le nom du fichier

4. Redémarrez le service SSH pour appliquer les changements :
   ```bash
   service ssh restart
   service sshd restart
   ```

5. Vérifiez le statut du service SSH :
   ```bash
   service ssh status
   ```

Explications des commandes :
- `nano /etc/ssh/sshd_config` : Ouvre le fichier de configuration SSH dans l'éditeur de texte nano.
- `service ssh restart` et `service sshd restart` : Redémarrent le service SSH pour appliquer les nouvelles configurations.
- `service ssh status` : Affiche l'état actuel du service SSH, permettant de vérifier qu'il fonctionne correctement après les modifications.

> Attention : Permettre la connexion root via SSH et l'authentification par mot de passe augmente les risques de sécurité. Cette configuration ne doit être utilisée que dans un environnement de développement contrôlé et isolé.




Très bien, voici comment nous pouvons documenter ces étapes de configuration du pare-feu UFW en Markdown :

## 8. Configuration du pare-feu UFW

Après avoir configuré SSH, nous allons maintenant configurer le pare-feu UFW (Uncomplicated Firewall) pour sécuriser notre VM tout en permettant le trafic nécessaire :

```bash
# Vérifier le statut initial d'UFW
ufw status

# Activer UFW
ufw enable

# Autoriser le trafic HTTPS (port 443)
ufw allow 443

# Autoriser le trafic HTTP (port 80)
ufw allow 80

# Autoriser le trafic sur le port 42 (spécifique au projet)
ufw allow 42

# Vérifier le statut final d'UFW
ufw status
```

Explications des commandes :

1. `ufw status` : 
   - Affiche l'état actuel du pare-feu et les règles configurées.
   - Utilisé avant et après la configuration pour voir les changements.

2. `ufw enable` :
   - Active le pare-feu UFW.
   - Vous devrez confirmer cette action, car elle peut potentiellement couper les connexions existantes.

3. `ufw allow [port]` :
   - Autorise le trafic entrant sur le port spécifié.
   - 443 : Pour le trafic HTTPS
   - 80 : Pour le trafic HTTP
   - 42 : Port spécifique au projet (assurez-vous que c'est nécessaire pour votre application)

> Note : N'oubliez pas d'autoriser le port SSH (généralement 22) si ce n'est pas déjà fait, pour maintenir l'accès à distance.

> Attention : La configuration du pare-feu est une étape cruciale pour la sécurité. Assurez-vous de ne pas vous bloquer l'accès à la VM en configurant des règles trop restrictives.





## 9. Configuration de la redirection de ports et connexion SSH à distance

Pour permettre l'accès à notre VM depuis la machine hôte, nous devons configurer la redirection de ports dans VirtualBox et vérifier la connexion SSH.

### 9.1 Configuration de la redirection de ports dans VirtualBox

1. Arrêtez la machine virtuelle si elle est en cours d'exécution.
2. Dans VirtualBox, sélectionnez votre VM Debian.
3. Cliquez sur "Configuration".
4. Allez dans l'onglet "Réseau".
5. Sélectionnez "Avancé" pour développer les options avancées.
6. Cliquez sur "Redirection de ports".
7. Ajoutez les règles suivantes :

   | Nom   | Protocole | Port Hôte | Port Invité |
   |-------|-----------|-----------|-------------|
   | SSH   | TCP       | 42        | 42          |
   | HTTP  | TCP       | 80        | 80          |
   | HTTPS | TCP       | 443       | 443         |

8. Cliquez sur "OK" pour sauvegarder les changements.

### 9.2 Vérification du service SSH et connexion à distance

1. Redémarrez la VM.
2. Connectez-vous en tant que root.
3. Vérifiez que le service SSH est actif :
   ```bash
   service ssh status
   ```

4. Sur votre machine hôte, ouvrez un terminal et connectez-vous à la VM via SSH :
   ```bash
   ssh root@localhost -p 42
   ```
5. Entrez le mot de passe root que vous avez défini lors de l'installation.

> Note : L'utilisation du port 42 pour SSH est non standard et spécifique à ce projet. Normalement, SSH utilise le port 22.

> Attention : La connexion SSH en tant que root avec un mot de passe est généralement déconseillée pour des raisons de sécurité. Dans un environnement de production, utilisez des clés SSH et un utilisateur non-root avec sudo.

Vous avez maintenant le contrôle de la VM directement depuis votre machine hôte, ce qui facilitera la copie et le collage des commandes pour la suite de la configuration.


## 10. Configuration de sudo et ajout de l'utilisateur au groupe Docker

Dans cette étape, nous allons configurer sudo pour notre utilisateur et l'ajouter au groupe Docker pour faciliter l'utilisation de Docker sans privilèges root.

### 10.1 Configuration de sudo

1. Connectez-vous à la VM en tant que root via SSH :
   ```bash
   ssh root@localhost -p 42
   ```

2. Ouvrez le fichier de configuration sudoers :
   ```bash
   nano /etc/sudoers
   ```

3. Ajoutez la ligne suivante sous `root ALL=(ALL:ALL) ALL` :
   ```
   hdupuy ALL=(ALL:ALL) ALL
   ```
   > Remplacez "hdupuy" par votre nom d'utilisateur.

4. Sauvegardez et quittez nano (Ctrl+X, puis Y, puis Enter).

5. Vérifiez que sudo est bien installé :
   ```bash
   apt install sudo
   ```

### 10.2 Ajout de l'utilisateur au groupe Docker

1. Affichez les groupes actuels de votre utilisateur :
   ```bash
   groups hdupuy
   ```

2. Ajoutez votre utilisateur au groupe Docker :
   ```bash
   sudo usermod -aG docker hdupuy
   ```
   > Remplacez "hdupuy" par votre nom d'utilisateur.

3. Vérifiez à nouveau les groupes pour confirmer l'ajout :
   ```bash
   groups hdupuy
   ```

> Note : L'ajout au groupe Docker permet d'utiliser Docker sans préfixer chaque commande avec `sudo`. Cependant, cela donne à l'utilisateur des privilèges équivalents à root pour les opérations Docker.

> Important : Après avoir ajouté l'utilisateur au groupe Docker, vous devrez vous déconnecter et vous reconnecter pour que les changements prennent effet.


## 11. Test de la configuration et clonage du projet Inception

Dans cette étape, nous allons tester notre configuration en passant à notre utilisateur normal et cloner le projet Inception depuis GitHub.

### 11.1 Passage à l'utilisateur normal

1. Passez de l'utilisateur root à votre utilisateur normal :
   ```bash
   su hdupuy
   ```
   > Remplacez "hdupuy" par votre nom d'utilisateur.

2. Naviguez vers le répertoire personnel de l'utilisateur :
   ```bash
   cd ~/
   ```

### 11.2 Clonage du projet Inception

Voici une commande unique qui créera tous les fichiers avec leur contenu respectif :

```bash
mkdir -p inception/srcs/requirements/{mariadb,nginx,wordpress} && \
cat << 'EOF' > inception/Makefile
VOLUME_DIR = /home/$(USER)/data
WP_DIR = $(VOLUME_DIR)/wordpress
DB_DIR = $(VOLUME_DIR)/mariadb

DOCKER_FILE = ./srcs/docker-compose.yml

.PHONY: all up down re clean fclean

all: up

$(VOLUME_DIR) $(WP_DIR) $(DB_DIR):
	mkdir -p $@

up: $(WP_DIR) $(DB_DIR)
	docker-compose -f $(DOCKER_FILE) up --build

down:
	docker-compose -f $(DOCKER_FILE) down

re: down up

clean: down
	docker system prune -af --volumes
	sudo rm -rf $(WP_DIR) $(DB_DIR) $(VOLUME_DIR)

fclean: clean
	docker builder prune --all -f

EOF

cat << 'EOF' > inception/srcs/docker-compose.yml
services:

  nginx:
    restart: always
    container_name: nginx
    build:
      dockerfile: Dockerfile
      context: ./requirements/nginx
    volumes:
      - wordpress:/var/www/html
    networks:
      - inception_network
    env_file:
      - .env
    ports:
      - "443:443"
    depends_on:
      - wordpress

  wordpress:
    restart: always
    container_name: wordpress
    build:
      dockerfile: Dockerfile
      context: ./requirements/wordpress
    volumes:
      - wordpress:/var/www/html
    networks:
      - inception_network
    env_file:
      - .env
    ports:
      - 9000:9000
    depends_on:
      - mariadb

  mariadb:
    restart: always
    container_name: mariadb
    build:
      dockerfile: Dockerfile
      context: ./requirements/mariadb
    volumes:
      - mariadb:/var/lib/mysql
    networks:
      - inception_network
    env_file:
      - .env
    ports:
      - 3306:3306

networks:
  inception_network:
    driver: bridge

volumes:
  mariadb:
    name: mariadb
    driver: local
    driver_opts:
      o: bind
      type: none
      device: /home/${USER}/data/mariadb

  wordpress:
    name: wordpress
    driver: local
    driver_opts:
      o: bind
      type: none
      device: /home/${USER}/data/wordpress
EOF

cat << 'EOF' > inception/srcs/requirements/mariadb/50-server.conf
[mysqld]
user = mysql
port = 3306
datadir = /var/lib/mysql
socket = /var/run/mysqld/mysqld.sock
bind-address=*
EOF

cat << 'EOF' > inception/srcs/requirements/mariadb/Dockerfile
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
EOF

cat << 'EOF' > inception/srcs/requirements/mariadb/init.sh
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
EOF

cat << 'EOF' > inception/srcs/requirements/nginx/Dockerfile
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
EOF

cat << 'EOF' > inception/srcs/requirements/nginx/nginx.conf
server {
    listen 443 ssl;
    listen [::]:443 ssl;

    root /var/www/html;

    index index.php index.html index.htm;

    server_name hdupuy.42.fr;

    ssl_certificate     /etc/nginx/ssl/server.crt;
    ssl_certificate_key /etc/nginx/ssl/server.key;

    ssl_protocols       TLSv1.2 TLSv1.3;

    location / {
        try_files $uri $uri/ /index.php?$args;
    }

    location ~ \.php$ {
        include snippets/fastcgi-php.conf;
        fastcgi_pass wordpress:9000;
        fastcgi_split_path_info ^(.+\.php)(/.+)$;
    }
}
EOF

cat << 'EOF' > inception/srcs/requirements/wordpress/Dockerfile
FROM debian:buster

ENV DEBIAN_FRONTEND noninteractive

RUN apt-get -y update && apt-get -y upgrade
RUN apt-get -y install \
    wget \
    php-fpm \
    php-mysql \
    mariadb-client

COPY www.conf /etc/php/7.3/fpm/pool.d/

RUN wget https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar && \
    chmod +x wp-cli.phar && \
    mv wp-cli.phar /usr/local/bin/wp

COPY init.sh /init.sh
RUN chmod +x /init.sh

EXPOSE 9000

WORKDIR /var/www/html/

ENTRYPOINT [ "/init.sh" ]
EOF

cat << 'EOF' > inception/srcs/requirements/wordpress/init.sh
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
EOF

cat << 'EOF' > inception/srcs/requirements/wordpress/www.conf
[www]
user = www-data
group = www-data
listen = wordpress:9000
listen.owner = www-data
listen.group = www-data
pm = dynamic
pm.max_children = 16
pm.start_servers = 4
pm.min_spare_servers = 2
pm.max_spare_servers = 8
chdir = /
clear_env = no
EOF

chmod +x inception/srcs/requirements/mariadb/init.sh inception/srcs/requirements/wordpress/init.sh
```

Cette commande unique créera tous les dossiers nécessaires et les fichiers avec leur contenu respectif. Elle rendra également les scripts init.sh exécutables.

Notez que cette commande suppose que vous êtes dans le répertoire parent où vous voulez créer le dossier `inception`. Si ce n'est pas le cas, ajustez le chemin en conséquence.

Après avoir exécuté cette commande, vous aurez toute la structure de fichiers nécessaire pour votre projet Inception.

## Script pour la creation du fichier .env

Voici un script Bash qui vous guidera pour remplir les informations nécessaires et créera le fichier .env dans le dossier inception/srcs/ :

```bash
#!/bin/bash

# Définir le chemin du fichier .env
ENV_FILE="inception/srcs/.env"

# Fonction pour demander une valeur à l'utilisateur
ask_value() {
    local prompt="$1"
    local value

    while true; do
        read -p "$prompt : " value
        if [ -n "$value" ]; then
            echo "$value"
            break
        else
            echo "Cette valeur ne peut pas être vide. Veuillez réessayer."
        fi
    done
}

# Créer le dossier si nécessaire
mkdir -p "$(dirname "$ENV_FILE")"

# Demander les valeurs à l'utilisateur
echo "Veuillez fournir les informations suivantes pour le fichier .env :"

DOMAIN_NAME=$(ask_value "Nom de domaine")
WORDPRESS_DATABASE_NAME=$(ask_value "Nom de la base de données WordPress")
WORDPRESS_MYSQL_USER=$(ask_value "Utilisateur MySQL WordPress")
WORDPRESS_MYSQL_PASSWORD=$(ask_value "Mot de passe MySQL WordPress")
MYSQL_ROOT_PASSWORD=$(ask_value "Mot de passe root MySQL")
WORDPRESS_DATABASE_HOST=$(ask_value "Hôte de la base de données WordPress")
WORDPRESS_SITE_TITLE=$(ask_value "Titre du site WordPress")
WORDPRESS_ADMIN_USER=$(ask_value "Utilisateur admin WordPress")
WORDPRESS_ADMIN_EMAIL=$(ask_value "Email admin WordPress")
WORDPRESS_ADMIN_PASSWORD=$(ask_value "Mot de passe admin WordPress")
WORDPRESS_USER_NAME=$(ask_value "Nom d'utilisateur WordPress")
WORDPRESS_USER_EMAIL=$(ask_value "Email utilisateur WordPress")
WORDPRESS_USER_PASSWORD=$(ask_value "Mot de passe utilisateur WordPress")

# Créer le fichier .env
cat << EOF > "$ENV_FILE"
DOMAIN_NAME=$DOMAIN_NAME

WORDPRESS_DATABASE_NAME=$WORDPRESS_DATABASE_NAME
WORDPRESS_MYSQL_USER=$WORDPRESS_MYSQL_USER
WORDPRESS_MYSQL_PASSWORD=$WORDPRESS_MYSQL_PASSWORD
MYSQL_ROOT_PASSWORD=$MYSQL_ROOT_PASSWORD

WORDPRESS_DATABASE_HOST=$WORDPRESS_DATABASE_HOST
WORDPRESS_SITE_TITLE=$WORDPRESS_SITE_TITLE

WORDPRESS_ADMIN_USER=$WORDPRESS_ADMIN_USER
WORDPRESS_ADMIN_EMAIL=$WORDPRESS_ADMIN_EMAIL
WORDPRESS_ADMIN_PASSWORD=$WORDPRESS_ADMIN_PASSWORD

WORDPRESS_USER_NAME=$WORDPRESS_USER_NAME
WORDPRESS_USER_EMAIL=$WORDPRESS_USER_EMAIL
WORDPRESS_USER_PASSWORD=$WORDPRESS_USER_PASSWORD
EOF

echo "Le fichier .env a été créé avec succès dans $ENV_FILE"
```

Pour utiliser ce script :

1. Copiez ce code dans un nouveau fichier, par exemple `create_env.sh`.

2. Rendez le script exécutable :
   ```
   chmod +x create_env.sh
   ```

3. Exécutez le script :
   ```
   ./create_env.sh
   ```

Le script va vous guider en vous demandant de remplir chaque champ. Il proposera des valeurs par défaut (celles que vous avez fournies) entre crochets. Si vous appuyez simplement sur Entrée sans rien taper, la valeur par défaut sera utilisée.

Une fois que vous avez rempli toutes les informations, le script créera le fichier .env dans le dossier inception/srcs/ avec les valeurs que vous avez fournies.

Ce script offre plusieurs avantages :
- Il guide l'utilisateur à travers chaque champ.
- Il crée automatiquement le dossier si nécessaire.
- Il assure que le fichier .env est créé au bon endroit avec le bon contenu.

N'oubliez pas de garder ce fichier .env sécurisé, car il contient des informations sensibles comme des mots de passe.

## Redirection de localhost vers login.42.fr

Pour faire en sorte que hdupuy.42.fr renvoie sur localhost sur Linux, vous pouvez modifier le fichier `/etc/hosts`. Voici les étapes à suivre :

1. Ouvrez un terminal.

2. Utilisez un éditeur de texte avec des privilèges root pour modifier le fichier `/etc/hosts`. Par exemple, avec nano :

   ```
   sudo nano /etc/hosts
   ```

3. Ajoutez la ligne suivante à la fin du fichier :

   ```
   127.0.0.1   hdupuy.42.fr
   ```

4. Sauvegardez le fichier et quittez l'éditeur. Dans nano, vous pouvez faire cela en appuyant sur Ctrl+X, puis Y, et enfin Enter.

5. Pour que les changements soient pris en compte immédiatement, vous pouvez vider le cache DNS de votre système. Sur la plupart des systèmes Linux, vous pouvez le faire en redémarrant le service de résolution de noms :

   ```
   sudo /etc/init.d/networking restart
   ```

Après ces étapes, toutes les requêtes vers hdupuy.42.fr seront redirigées vers votre machine locale (localhost).


## 12. Lancement du projet Inception avec Docker Compose

Cette étape finale consiste à naviguer dans le bon répertoire et à lancer le projet Inception en utilisant Docker Compose.

1. Naviguez vers le répertoire `srcs` à l'intérieur du dossier `inception` :
   ```bash
   cd inception/srcs
   ```

2. Lancez le projet en utilisant Docker Compose :
   ```bash
   docker-compose -f docker-compose.yml up --build
   ```
3. Vous pouvez lancer le projet en utilisant le Makefile fourni :
   ```bash
   make
   ```

Explications de la commande :
- `docker-compose` : Outil pour définir et exécuter des applications Docker multi-conteneurs.
- `-f docker-compose.yml` : Spécifie le fichier de configuration Docker Compose à utiliser.
- `up` : Crée et démarre les conteneurs définis dans le docker-compose.yml.
- `--build` : Force Docker Compose à reconstruire les images avant de démarrer les conteneurs.

> Note : Cette commande va construire les images Docker si nécessaire, puis démarrer tous les services définis dans votre fichier docker-compose.yml. Le processus peut prendre plusieurs minutes, surtout lors de la première exécution.

> Conseil : Gardez un œil sur la sortie de la console pour détecter d'éventuelles erreurs ou messages importants pendant le démarrage des services.

Pour arrêter les conteneurs, vous pouvez utiliser Ctrl+C dans le terminal où Docker Compose est en cours d'exécution.

Si vous voulez exécuter les conteneurs en arrière-plan, vous pouvez ajouter l'option `-d` à la commande :
```bash
docker-compose -f docker-compose.yml up --build -d
```

Pour arrêter et supprimer les conteneurs en arrière-plan, utilisez :
```bash
docker-compose -f docker-compose.yml down
```

Pour vérifier si les deux utilisateurs (l'utilisateur WordPress et l'utilisateur root) ont bien été créés dans la base de données MariaDB, vous pouvez suivre ces étapes :

1. Connectez-vous au conteneur MariaDB :
   ```
   docker exec -it [nom_du_conteneur_mariadb] bash
   ```

2. Connectez-vous à MariaDB en tant que root :
   ```
   mysql -u root -p
   ```
   Entrez le mot de passe root que vous avez défini (${MYSQL_ROOT_PASSWORD}).

3. Une fois connecté, vous pouvez vérifier les utilisateurs avec la commande suivante :
   ```sql
   SELECT User, Host FROM mysql.user;
   ```

4. Pour vérifier les privilèges de l'utilisateur WordPress :
   ```sql
   SHOW GRANTS FOR '[WORDPRESS_MYSQL_USER]'@'%';
   ```
   Remplacez [WORDPRESS_MYSQL_USER] par le nom d'utilisateur que vous avez défini.

5. Vérifiez également que la base de données WordPress a été créée :
   ```sql
   SHOW DATABASES;
   ```

6. Pour vérifier que l'utilisateur WordPress a bien les droits sur la base de données :
   ```sql
   SHOW GRANTS FOR '[WORDPRESS_MYSQL_USER]'@'%';
   ```
