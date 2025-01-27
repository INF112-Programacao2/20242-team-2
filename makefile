# Nome do arquivo executável (padrão a.out)
TARGET = a.out

# Definindo o compilador e as flags
CXX = g++
CXXFLAGS = -std=c++14 -Wall -g  # Adicionada a flag -g para depuração

# Lista de arquivos .cpp
SOURCES = Usuario.cpp Gestor.cpp Analista.cpp Vendedor.cpp classeSemente.cpp classeLote.cpp classeArea_Plantio.cpp classeNegociacao.cpp Relatorio.cpp main.cpp

# Gerando os arquivos objetos a partir dos fontes
OBJECTS = $(SOURCES:.cpp=.o)

# Regra principal para compilar o projeto
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET)

# Como compilar os arquivos .cpp para .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regra para rodar o Valgrind
valgrind: $(TARGET)
	valgrind --leak-check=full --show-leak-kinds=all ./$(TARGET)

# Limpar os arquivos gerados (como .o e o executável)
clean:
	rm -f $(OBJECTS) $(TARGET)
