#!/bin/bash

# Demander le nom du commit à l'utilisateur
#!/bin/bash

# Afficher le texte en couleur
echo -e "\e[1;97m\e[0m \e[1;34mQuel est le nom du commit ?\e[0m \e[1;97m\e[0m"

# Demander le nom du commit à l'utilisateur
read -p " " commit_message

# Le reste du script reste inchangé...


# Nettoyer le projet avec make fclean
make fclean

# Ajouter tous les fichiers modifiés à l'index de Git
git add .

# Commit avec le message spécifié par l'utilisateur
git commit -m "$commit_message"

# Pousser les modifications vers le référentiel distant
git push

echo "Les modifications ont été poussées vers le référentiel distant."
