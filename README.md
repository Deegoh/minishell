# MiniShell

**This project is currently under construction and shared with [Kenneth Rioja](https://github.com/kennethrioja)**

## Todo list
- [x] Afficher un **prompt** en l’attente d’une nouvelle commande.
- [x] Posséder un **historique** fonctionnel.
- [ ] KR - Chercher et lancer le bon exécutable (en se basant sur la variable d’environnement *PATH*, ou sur un chemin relatif ou absolu).
- [ ] Ne pas utiliser **plus d’une variable globale**. Réfléchissez-y car vous devrez justifier son utilisation.
- [ ] Ne pas interpréter de quotes (guillemets) non fermés ou de caractères spéciaux non demandés dans le sujet, tels que \ (le *backslash*) ou ; (le *point-virgule*).
- [ ] Gérer ’ (*single quote*) qui doit empêcher le shell d’interpréter les méta-caractères présents dans la séquence entre guillemets.
- [ ] Gérer " (*double quote*) qui doit empêcher le shell d’interpréter les méta-caractères présents dans la séquence entre guillemets sauf le $ (signe dollar).
- Implémenter les **redirections** :
	- [ ] < doit rediriger l’entrée.
	- [ ] > doit rediriger la sortie.
	- [ ] << doit recevoir un délimiteur et lire l’input donné jusqu’à rencontrer une ligne
contenant le délimiteur. Cependant, l’historique n’a pas à être mis à jour !
	- [ ] >> doit rediriger la sortie en mode append.
- [ ] Implémenter les **pipes** (caractère |). La sortie de chaque commande de la pipeline est connectée à l’entrée de la commande suivante grâce à un pipe.
- [ ] Gérer les **variables d’environnement** (un $ suivi d’une séquence de caractères) qui doivent être substituées par leur contenu.
- [ ] Gérer $? qui doit être substitué par le statut de sortie de la dernière pipeline exécutée au premier plan.
- [x] Gérer ctrl-C, ctrl-D et ctrl-\ qui doivent fonctionner comme dans bash.
- En mode interactif :
	- [x] ctrl-C affiche un nouveau prompt sur une nouvelle ligne.
	- [x] ctrl-D quitte le shell.
	- [x] ctrl-\ ne fait rien.
	- [ ] ajouter les modif termios
- Votre shell doit implémenter les **builtins** suivantes :
	- [x] echo et l’option -n
	- [x] cd uniquement avec un chemin relatif ou absolu
	- [x] pwd sans aucune option
	- [x] export sans aucune option
	- [x] unset sans aucune option
	- [x] env sans aucune option ni argument
	- [x] exit sans aucune option
	- [ ] a controler avec le nouveau parser

- [ ] Leaks
- [ ] Gestion d'erreurs
- [x] Ajouter ft_printf & Enlever put_str

## Bonus
- [ ] && et || avec des parenthèses pour les priorités.
- [ ] Les wildcards * doivent fonctionner pour le répertoire courant.

## Tiago
- [ ] supprimer getenv pour tous sauf pwd
- [ ] /bin/cat doit fonctionner et ^C doit etre affichier
- [ ] changer opendir pour access afin de rendre le programme plus leger

## Kenneth
- [x] Mettre le Makefile + .h
- [ ] get_redir : stocker toutes les redirections dans t_redir tout en updatant ad.line
- [ ] get_pa : stocker toutes les commandes et les arguments dans t_pa pour pouvoir utiliser execve() qui prend en arguments path et une liste d'arguments
