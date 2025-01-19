#include "classeArea_Plantio.hpp"
#include <limits>
#include <fstream>
#include <iostream>
#include <sstream>

area_plantio::area_plantio() {
    
    // inicializa atributos da classe
    _status = "Disponível";
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
    std::cin.ignore();
    std::cout << "Nome do proprietário: ";                                 std::getline(std::cin, _nome_proprietario);
    std::cout << "CNPJ do proprietário: ";                                 std::getline(std::cin, _cnpj_proprietario);

    std::cout << "\nInformações sobre a área:\n";
    std::cout << "Localização: ";                                           std::getline(std::cin, _localizacao);
    std::cout << "Tipo de solo: ";                                          std::getline(std::cin, _tipo_solo);
    std::cout << "Clima: ";                                                 std::getline(std::cin, _clima);
    std::cout << "Tamanho em hectares: ";                                   std::cin >> _tamanho;
   
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');      // limpa o buffer após leitura

    // salva os dados no arquivo
    arquivoAreasON << _id_area << " " <<_status<< "+"<< _nome_proprietario << "+" << _cnpj_proprietario << "+"<< _localizacao << "+" << _tipo_solo << "+" << _clima 
                    << "+" << _tamanho <<"\n";

    arquivoAreasON.close();
}

area_plantio:: area_plantio(int id_area){                               

    std::ifstream arquivoAreas ("AreaPlantio.txt");
    if(!arquivoAreas)
        std::cerr<<"Erro ao abrir o arquivo Areas.txt\n";

    std::string linha;
    for(int i=0;i<id_area;i++){
        std::getline(arquivoAreas, linha);  //ignorando as n primeiras linhas do codigo
    }
    //----------------------------------------------


    arquivoAreas >>_id_area;                                arquivoAreas.ignore();
    std::getline(arquivoAreas, _status, '+');
    std::getline(arquivoAreas, _nome_proprietario,'+');
    std::getline(arquivoAreas, _cnpj_proprietario,'+');
    std::getline(arquivoAreas,_localizacao,'+');
    std::getline(arquivoAreas,_tipo_solo,'+');
    std::getline(arquivoAreas,_clima,'+');       
    arquivoAreas >> _tamanho;                            
    //--------------------------------------------

    arquivoAreas.close();
}

area_plantio:: ~area_plantio(){}

int area_plantio:: get_id_area(){
    return _id_area;
}

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
    if (_status != "Disponível") {
        throw std::runtime_error("Área não está disponível para plantio.");
    }

    // Atualiza o estado do objeto
    _sementes_plantadas.push_back(id_lote);
    _status = "Em uso";

    // Abre o arquivo para leitura e escrita
    std::fstream arquivoArea("AreaPlantio.txt", std::ios::in | std::ios::out);
    if (!arquivoArea) {
        throw std::runtime_error("Erro ao abrir o arquivo AreaPlantio.txt");
    }

    int contador_areas;
    arquivoArea >> contador_areas;
    arquivoArea.ignore();

    // Aloca memória para armazenar todas as linhas
    std::string* linhas = new std::string[contador_areas];

    // Lê todas as linhas do arquivo
    for (int i = 0; i < contador_areas; i++) {
        if (i + 1 == _id_area) {
            // Pula a linha atual que será atualizada
            std::string linha_antiga;
            std::getline(arquivoArea, linha_antiga);

            // Cria a nova linha com os dados atualizados
            std::stringstream nova_linha;
            nova_linha << _id_area << " "  << _status << "+" << _nome_proprietario << "+"  << _cnpj_proprietario << "+" << _localizacao << "+" 
                        << _tipo_solo << "+" << _clima << "+"  << _tamanho;

            linhas[i] = nova_linha.str();
        } else {
            std::getline(arquivoArea, linhas[i]);
        }
    }

    // Fecha o arquivo e reabre para reescrita
    arquivoArea.close();
    std::ofstream arquivoSaida("AreaPlantio.txt", std::ios::trunc);
    
    if (!arquivoSaida) {
        delete[] linhas;
        throw std::runtime_error("Erro ao reescrever o arquivo AreaPlantio.txt");
    }

    // Escreve o número de áreas e todas as linhas atualizadas
    arquivoSaida << contador_areas << std::endl;
    for (int i = 0; i < contador_areas; i++) {
        arquivoSaida << linhas[i] << std::endl;
    }

    delete[] linhas;
    arquivoSaida.close();
    
    std::cout << "Plantio registrado com sucesso!\n";
}

bool area_plantio::verificarDisponibilidade() {
    if(_status=="Disponível"){
        return true;
    }else{
        return false;
    }
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


