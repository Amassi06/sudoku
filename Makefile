
# Nom de l'exécutable
EXEC = programme

# Fichiers source
SRC = ./src/main.c ./src/grille.c

# Argument
ARG = 42

# Régle principale pour compiler le programme

build: $(EXEC)
       
$(EXEC): clean $(SRC)
	@echo "Compilation du programme..."
	gcc $(SRC) -o ./out/$(EXEC) -L./lib -lsudoku

# Règle pour exécuter le programme avec un paramètre compris entre 40 et 50
run:
	@echo "Exécution du programme avec 45 cases non vide"
		LD_LIBRARY_PATH=./lib ./out/$(EXEC) $(ARG)

# Règle pour compiler avec des options de dèbogage
debug: clean $(SRC)
	@echo  "Compilation du programme en mode debug..."
	gcc -g $(SRC) -o ./out/$(EXEC) -L./lib -lsudoku
	
# Règle pour nettoyer les fichiers générés lors de la compilation
clean:
	@echo "Nettoyage des fichiers exècutable..."
	rm -f ./out/$(EXEC)
