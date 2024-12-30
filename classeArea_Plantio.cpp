#include "classeArea_Plantio.hpp"
#include <limits>
#include <fstream>
#include <iostream>

area_plantio::area_plantio() {
    
    // inicializa atributos da classe
    _status = "disponível";
    _sementes_plantadas.clear();

    //____________________________________________//

    // abre ou cria o arquivo para controle de ID
    std::fstream arquivoAreaPlantio("AreaPlantio.txt", std::ios::in | std::ios::out);

    if (!arquivoAreaPlantio.is_open()) {
        // se o arquivo não existir, cria um novo
        std::ofstream novoArquivo("AreaPlantio.txt");
        if (!novoArquivo) {
            std::cerr << "Erro ao criar o arquivo AreaPlantio.txt\n";
            return;
        }
        novoArquivo << "1" << std::endl;
        novoArquivo.close();
        _id_area = 1;
    } else {
        arquivoAreaPlantio >> _id_area;   // lê o último ID e atualiza
        _id_area++;
        arquivoAreaPlantio.seekp(0);      // retorna ao início para sobrescrever o ID
        arquivoAreaPlantio << _id_area << std::endl;
        arquivoAreaPlantio.close();
    }

   //____________________________________________//

    // reabre o arquivo para adicionar novas áreas
    std::ofstream arquivoAreasON("AreaPlantio.txt", std::ios::app);
    if (!arquivoAreasON) {
        std::cerr << "Erro ao abrir o arquivo AreaPlantio.txt para escrita\n";
        return;
    }

    std::cout << "Informações sobre o proprietário:\n";
    std::cout << "Nome do proprietário: ";                                 std::getline(std::cin, _nome_proprietario);
    std::cout << "CNPJ do proprietário: ";                                 std::getline(std::cin, _cnpj_proprietario);

    std::cout << "\nInformações sobre a área:\n";
    std::cout << "Localização: ";                                           std::getline(std::cin, _localizacao);
    std::cout << "Tipo de solo: ";                                          std::getline(std::cin, _tipo_solo);
    std::cout << "Clima: ";                                                 std::getline(std::cin, _clima);
    std::cout << "Tamanho em hectares: ";                                   std::cin >> _tamanho;
   
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');      // limpa o buffer após leitura

    // salva os dados no arquivo
    arquivoAreasON << _id_area << " "<< _nome_proprietario << " " << _cnpj_proprietario << " "<< _localizacao << " " << _tipo_solo << " " << _clima 
                    << " " << _tamanho << "\n";

    arquivoAreasON.close();
}

area_plantio:: ~area_plantio(){}

void area_plantio::exibirDetalhes() {
    std::cout << "\n=== Detalhes da Área de Plantio ===\n";
    std::cout << "ID: " << _id_area << "\n";
    std::cout << "Proprietário: " << _nome_proprietario << "\n";
    std::cout << "CNPJ: " << _cnpj_proprietario << "\n";
    std::cout << "Localização: " << _localizacao << "\n";
    std::cout << "Tipo de Solo: " << _tipo_solo << "\n";
    std::cout << "Clima: " << _clima << "\n";
    std::cout << "Tamanho: " << _tamanho << " hectares\n";
    std::cout << "Status: " << _status << "\n";
    
    if (!_sementes_plantadas.empty()) {
        std::cout << "Sementes plantadas (IDs): ";
        for (int id : _sementes_plantadas) {
            std::cout << id << " ";
        }
        std::cout << "\n";
    }
}

void area_plantio::registrarPlantio(int id_lote) {
    if (_status == "disponível") {
        _sementes_plantadas.push_back(id_lote);
        _status = "em uso";
        std::cout << "Plantio registrado com sucesso!\n";
    } else {
        std::cout << "Área não está disponível para plantio.\n";
    }
}

std::string area_plantio::verificarDisponibilidade() {
    return _status;
}

float area_plantio::verificarCompatibilidade(semente& semente) {
    // implementar lógica de compatibilidade, por enquanto retorna 0.0
    return 0.0;
}

void area_plantio::liberarArea() {
    _status = "disponível";
    _sementes_plantadas.clear();
    std::cout << "Área liberada com sucesso!\n";
}

void area_plantio::gerar_relatorioArea() {
    exibirDetalhes();
    // Aicionar mais informações específicas para o relatório se necessário
}


