TARGET = batailleNavale.out # Nom de l'exécutable
OBJETS = main.o BatailleNavale.o Joueur.o Grille.o Flotte.o IHM.o Navire.o
DEBUG = -DDEBUG_BATAILLENAVALE
CXX = g++ # Compilateur
LD = g++ -o
CXXFLAGS = -Wall # Options de compilation
CLANG_TIDY = clang-tidy
CLANG_FLAGS = --quiet -header-filter='.*' -checks=-*,boost-*,bugprone-*,performance-*,readability-*,portability-*,modernize-use-nullptr,clang-analyzer-*,cppcoreguidelines-* --format-style=none -- -std=c++11
RM = rm -f

all: $(TARGET) # Règle par défaut : construire l'exécutable


$(TARGET): $(OBJETS) # Règle pour construire l'exécutable à partir des fichiers objets
	$(LD) $@ $^

main.o: main.cpp
	$(CXX) -c $< $(CXXFLAGS)

%.o: %.cpp %.h
	$(CXX) -c $< $(CXXFLAGS)

clean: # Cible clean : supprimer les fichiers objets
	$(RM) *.o *.*~

cleanall: # Cible cleanall : supprimer les fichiers objets et l'exécutable
	$(RM) *.o *.*~ $(TARGET)

install_clang_tidy:
	@command -v $(CLANG_TIDY) > /dev/null || \
		(sudo apt-get update && sudo apt-get install clang-tidy)

check: install_clang_tidy # Cible check : vérifier la présence de clang-tidy et l'utiliser pour vérifier le code
	@command -v $(CLANG_TIDY) > /dev/null && \
		$(CLANG_TIDY) *.cpp $(CLANG_FLAGS) || \
		(echo "Erreur: clang-tidy n'est pas installé."; exit 1)
