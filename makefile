# Nome do arquivo executável
TARGET = programa

# Definindo o compilador e as flags
CXX = g++
CXXFLAGS = -std=c++14 -Wall -g  # Adicionada a flag -g para depuração

# Lista de arquivos .cpp
SOURCES = Usuario.cpp Gestor.cpp Vendedor.cpp Analista.cpp classeSemente.cpp classeLote.cpp classeArea_Plantio.cpp classeNegociacao.cpp Relatorio.cpp main.cpp

# Gerando os arquivos objetos a partir dos fontes
OBJECTS = $(SOURCES:.cpp=.o)
EXEC = programa

# Regra padrão
all: $(EXEC)

# Regra principal para compilar o projeto
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET)

# Como compilar os arquivos .cpp para .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regra para compilar e rodar
makerun: all
	./$(EXEC)

# Regra para rodar o Valgrind
valgrind: $(TARGET)
	valgrind --leak-check=full --show-leak-kinds=all ./$(TARGET)

#Regra para conferir instalação do eSpeak
eSpeak: $(TARGET)
	espeak --version

# Limpar os arquivos gerados (como .o e o executável)
clean:
	rm -f $(OBJECTS) $(TARGET)
