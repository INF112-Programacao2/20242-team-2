#include "Vendedor.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

void Vendedor::registrarArea() {
    area_plantio novaArea; // Cria uma nova instância de area_plantio, que já gera um novo ID automaticamente

    if (!novaArea.verificarDisponibilidade()) {
        std::cout << "Erro: A area com ID " << novaArea.get_id_area() << " nao esta disponivel para plantio.\n";
        return;
    }

    areas.push_back(novaArea);

    std::cout << "Area de plantio registrada com sucesso com ID " << novaArea.get_id_area() << "!\n";
}


void Vendedor::listarAreasRegistradas() {
    std::ifstream arquivoAreas("AreaPlantio.txt");
    if (!arquivoAreas) {
        std::cerr << "Erro ao abrir o arquivo AreaPlantio.txt\n";
        return;
    }

    int contador_areas;
    arquivoAreas >> contador_areas;
    arquivoAreas.ignore();

    std::string linha;
    std::cout << "=== Areas de Plantio Registradas ===\n";

    for (int i = 0; i < contador_areas; ++i) {
        std::getline(arquivoAreas, linha);
        std::stringstream ss(linha);
        int id;
        std::string status, nome, cnpj, localizacao, solo, clima;
        float tamanho;

        ss >> id;
        ss.ignore();
        std::getline(ss, status, '+');
        std::getline(ss, nome, '+');
        std::getline(ss, cnpj, '+');
        std::getline(ss, localizacao, '+');
        std::getline(ss, solo, '+');
        std::getline(ss, clima, '+');
        ss >> tamanho;

        std::cout << "ID: " << id << "\n";
        std::cout << "Proprietario: " << nome << "\n";
        std::cout << "CNPJ: " << cnpj << "\n";
        std::cout << "Localizacao: " << localizacao << "\n";
        std::cout << "Tipo de Solo: " << solo << "\n";
        std::cout << "Clima: " << clima << "\n";
        std::cout << "Tamanho: " << tamanho << " hectares\n";
        std::cout << "Status: " << status << "\n";
        std::cout << "-----------------------------\n";
    }

    arquivoAreas.close();
}


void Vendedor::liberarAreaRegistrada() {
    // Lista todas as áreas disponíveis
    std::ifstream arquivoArea("AreaPlantio.txt");
    if (!arquivoArea) {
        throw std::runtime_error("Erro ao abrir arquivo AreaPlantio.txt");
    }

    // Lê o contador de áreas
    int total_areas;
    arquivoArea >> total_areas;
    arquivoArea.ignore();

    std::cout << "\n=== Áreas Registradas ===\n";
    
    // Vetor para armazenar as áreas em uso
    std::vector<area_plantio> areas_em_uso;
    
    // Lista apenas áreas em uso
    for (int i = 1; i <= total_areas; i++) {
        area_plantio area(i);
        if (area.verificarDisponibilidade() == false) {
            areas_em_uso.push_back(area);
            area.exibirDetalhes();
        }
    }

    if (areas_em_uso.empty()) {
        std::cout << "Não há áreas em uso para liberar.\n";
        return;
    }

    // Solicita o ID da área a ser liberada
    int id_area;
    std::cout << "\nDigite o ID da área que deseja liberar: ";
    std::cin >> id_area;
    
    // Verifica se o ID é válido
    bool found = false;
    for (auto& area : areas_em_uso) {
        if (area.get_id_area() == id_area) {
            try {
                area.liberarArea();
                found = true;
                std::cout << "Área " << id_area << " foi liberada com sucesso.\n";
                break;
            } catch (const std::exception& e) {
                std::cerr << "Erro ao liberar área: " << e.what() << std::endl;
                return;
            }
        }
    }

    if (!found) {
        std::cout << "Área com ID " << id_area << " não encontrada ou já está disponível.\n";
    }
}

void Vendedor::excluirArea() {
    // Abre o arquivo para leitura
    std::ifstream arquivoArea("AreaPlantio.txt");
    if (!arquivoArea) {
        throw std::runtime_error("Erro ao abrir arquivo AreaPlantio.txt");
    }

    // Lê o contador de áreas
    int total_areas;
    arquivoArea >> total_areas;
    arquivoArea.ignore();

    // Lista todas as áreas para o usuário escolher
    std::cout << "\n=== Áreas Disponíveis para Exclusão ===\n";
    std::vector<std::string> todas_areas;
    std::string linha;

    // Guarda a primeira linha (contador)
    todas_areas.push_back(std::to_string(total_areas));

    // Lê e armazena todas as linhas do arquivo
    while (std::getline(arquivoArea, linha)) {
        if (!linha.empty()) {
            std::stringstream ss(linha);
            int id;
            ss >> id;
            area_plantio area(id);
            area.exibirDetalhes();
            todas_areas.push_back(linha);
        }
    }
    arquivoArea.close();

    // Solicita o ID da área a ser excluída
    int id_excluir;
    std::cout << "\nDigite o ID da área que deseja excluir: ";
    std::cin >> id_excluir;

    // Verifica se o ID é válido
    if (id_excluir <= 0 || id_excluir > total_areas) {
        std::cout << "ID inválido.\n";
        return;
    }

    // Confirma a exclusão
    char confirmacao;
    std::cout << "Tem certeza que deseja excluir a área " << id_excluir << "? (S/N): ";
    std::cin >> confirmacao;
    
    if (toupper(confirmacao) != 'S') {
        std::cout << "Operação cancelada.\n";
        return;
    }

    // Abre o arquivo para escrita
    std::ofstream arquivoSaida("AreaPlantio.txt", std::ios::trunc);
    if (!arquivoSaida) {
        throw std::runtime_error("Erro ao abrir arquivo para escrita");
    }

    // Atualiza o contador de áreas
    arquivoSaida << (total_areas - 1) << std::endl;

    // Reescreve todas as áreas, exceto a que será excluída
    for (size_t i = 1; i < todas_areas.size(); i++) {
        std::stringstream ss(todas_areas[i]);
        int id_atual;
        ss >> id_atual;
        
        if (id_atual != id_excluir) {
            arquivoSaida << todas_areas[i] << std::endl;
        }
    }

    arquivoSaida.close();
    std::cout << "Área " << id_excluir << " excluída com sucesso!\n";
}

void Vendedor::cadastrarNegociacao() {
    negociacao* nova_negociacao = nullptr;
    lote* lote_selecionado = nullptr;
    
    try {
        // 1. Lista áreas disponíveis
        std::ifstream arquivoArea("AreaPlantio.txt");
        if (!arquivoArea) {
            throw std::runtime_error("Erro ao abrir arquivo de áreas");
        }

        int total_areas;
        arquivoArea >> total_areas;
        
        std::cout << "\n=== Áreas Disponíveis ===\n";
        std::vector<area_plantio> areas_disponiveis;
        
        for (int i = 1; i <= total_areas; i++) {
            area_plantio area(i);
            if (area.verificarDisponibilidade()) {
                areas_disponiveis.push_back(area);
                area.exibirDetalhes();
            }
        }
        
        if (areas_disponiveis.empty()) {
            std::cout << "Não há áreas disponíveis para negociação.\n";
            return;
        }

        // 2. Seleciona área
        int id_area;
        std::cout << "\nDigite o ID da área desejada: ";
        std::cin >> id_area;
        
        area_plantio* area_selecionada = nullptr;
        for (auto& area : areas_disponiveis) {
            if (area.get_id_area() == id_area) {
                area_selecionada = &area;
                break;
            }
        }
        
        if (!area_selecionada) {
            throw std::runtime_error("Área não encontrada ou não disponível");
        }

        // 3. Lista lotes compatíveis
        std::cout << "\n=== Lotes Compatíveis ===\n";
        area_selecionada->compatibilidade_semente();
        
        // 4. Seleciona lote
        int id_lote;
        std::cout << "\nDigite o ID do lote desejado: ";
        std::cin >> id_lote;
        
        lote_selecionado = new lote(id_lote);

        // 5. Quantidade de sementes
        float quantidade;
        std::cout << "Digite a quantidade de sementes desejada: ";
        std::cin >> quantidade;
        
        if (quantidade <= 0) {
            throw std::invalid_argument("Quantidade inválida");
        }

        // 6. Data da negociação
        std::string data;
        std::cin.ignore();
        std::cout << "Digite a data da negociação (DD/MM/AAAA) ou deixe em branco para data atual: ";
        std::getline(std::cin, data);

        // 7. Registra negociação
        nova_negociacao = new negociacao();
        nova_negociacao->registrarNegociacao(lote_selecionado, area_selecionada, quantidade, data);

        // 8. Pergunta se deseja finalizar agora
        char finalizar;
        std::cout << "Deseja finalizar a negociação agora? (S/N): ";
        std::cin >> finalizar;

        if (toupper(finalizar) == 'S') {
            nova_negociacao->finalizarNegociacao();
        }

    } catch (const std::exception& e) {
        std::cerr << "Erro ao cadastrar negociação: " << e.what() << std::endl;
        
        // Tenta cancelar a negociação se ela foi criada
        if (nova_negociacao != nullptr) {
            try {
                nova_negociacao->cancelarNegociacao();
                std::cout << "Negociação foi cancelada devido ao erro.\n";
            } catch (const std::exception& cancel_e) {
                std::cerr << "Erro ao cancelar negociação: " << cancel_e.what() << std::endl;
            }
        }
    }

    // Limpeza de memória
    if (lote_selecionado != nullptr) {
        delete lote_selecionado;
    }
    if (nova_negociacao != nullptr) {
        delete nova_negociacao;
    }
}
