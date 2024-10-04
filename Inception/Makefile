VOLUME_DIR = /home/$(USER)/data
WP_DIR = $(VOLUME_DIR)/wordpress
DB_DIR = $(VOLUME_DIR)/mariadb

DOCKER_FILE = ./srcs/docker-compose.yml

.PHONY: all up down re clean fclean

all: up

$(VOLUME_DIR) $(WP_DIR) $(DB_DIR):
	mkdir -p $@

up: $(WP_DIR) $(DB_DIR)
	docker-compose -f $(DOCKER_FILE) up -d --build

down:
	docker-compose -f $(DOCKER_FILE) down

re: down up

clean: down
	docker system prune -af --volumes
	sudo rm -rf $(WP_DIR) $(DB_DIR) $(VOLUME_DIR)

fclean: clean
	docker builder prune --all -f
