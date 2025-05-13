# 🐚 Minishell - Projet 42

Projet de groupe, réalisé avec [Valentin Mondor](https://github.com/vmondor)

## 📌 Description

**Minishell** est un projet réalisé dans le cadre du cursus de l'école **42**.  
L'objectif est de reproduire un shell UNIX minimaliste, capable d'interpréter des commandes et de gérer des fonctionnalités essentielles d'un terminal.  
Ce projet permet de comprendre en profondeur le fonctionnement d’un shell, la gestion des processus, des signaux, des redirections, et l’environnement utilisateur.

---

## 🎯 Objectifs pédagogiques

- Maîtriser les appels systèmes liés aux **processus** (`fork`, `execve`, `waitpid`, etc.)
- Gérer les **signaux** (CTRL+C, CTRL+\ etc.)
- Manipuler l'**environnement** (`env`, `export`, `unset`)
- Implémenter les **redirections** (`>`, `>>`, `<`, `<<`) et les **pipes**
- Construire un **parser robuste** capable de traiter une ligne de commande avec des guillemets, des variables d'environnement, etc.
- Gérer des **builtins** comme `cd`, `echo`, `pwd`, `env`, `exit`, etc.

---

## ⚙️ Fonctionnalités implémentées

- ✅ Exécution de commandes avec ou sans chemin absolu/relatif
- ✅ Builtins : `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`
- ✅ Redirections (`>`, `>>`, `<`, `<<`)
- ✅ Pipe entre plusieurs commandes (`|`)
- ✅ Variables d’environnement (`$HOME`, `$PATH`, etc.)
- ✅ Gestion des guillemets simples et doubles (`'`, `"`)
- ✅ Expansion de variables
- ✅ Gestion des signaux (`SIGINT`, `SIGQUIT`)
- ✅ Gestion des erreurs (commande non trouvée, redirection invalide, etc.)

---

## 🛠️ Technologies utilisées

- **Langage** : C (sans libc interdite)
- **Compilation** : `Makefile`
- **Outils** : `readline`, `valgrind` pour le débogage

---

## 🚀 Lancer le projet

1. Cloner le dépôt :
   ```bash
   git clone https://github.com/vmondor/minishell.git
   cd minishell
   make run