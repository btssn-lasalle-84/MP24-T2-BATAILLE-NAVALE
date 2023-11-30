TARGET = batailleNavale.out # Nom de l'exécutable
OBJETS = main.o BatailleNavale.o Joueur.o Grille.o Flotte.o IHM.o Navire.o
CXX = g++ # Compilateur
LD = g++ -o
CXXFLAGS = -Wall # Options de compilation
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

