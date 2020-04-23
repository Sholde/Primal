# Test de primalité

## Compiler le projet

<pre>make</pre>

## Executer le projet

<pre>make run</pre>

## Voir les sources du projet

<pre>cd src/</pre>

# Explication

Au moment de l'exécution l'application propose 3 choix :
- soit d'entrer le nombre à tester et le nombre d'itéraion sur le terminal
- soit de prendre un nombre à tester contenue dans un fichier et d'écrire le nombre d'itéraion sur le terminal
- soit d'écrire le nombre à tester dans un fichier

Ensuite l'application propose 2 tests de primalité :
- Fermat
- Miller Rabbin

L'application affiche le résultat et demande à l'utilisateur si il veut utiliser les mêmes paramètre (cad le nombre à tester et le nombre d'itéraion), et lui repropose les 2 test si il répond oui.
