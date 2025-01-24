#include "classeArea_Plantio.hpp"
#include <limits>
#include <fstream>
#include <iostream>
#include <sstream>

area_plantio::area_plantio() {
    // inicializa os atributos
    _status = "Disponível";
    _sementes_plantadas.clear();

    // abre o arquivo e registra o controle de id
    std::fstream arquivoAreaPlantio("AreaPlantio.txt", std::ios::in | std::ios::out);

    if (!arquivoAreaPlantio.is_open()) {
        // se o arquivo não existe, cria um novo
        std::ofstream novoArquivo("AreaPlantio.txt");
        if (!novoArquivo) {
            std::cerr << "Erro ao criar o arquivo AreaPlantio.txt\n";
            return;
        }
        novoArquivo << "0" << std::endl;
        novoArquivo.close();
        _id_area = 0;
    } else {
        arquivoAreaPlantio >> _id_area;   //Lê o ultimo id para alterações
        _id_area++;
        arquivoAreaPlantio.seekp(0);      // Rvolta no inicio para atualizar o contador de id
        arquivoAreaPlantio << _id_area << std::endl;
        arquivoAreaPlantio.close();
    }
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


    arquivoAreas >>_id_area; _id_area++;         //le o contador de tipos e calcula o ID                                arquivoAreas.ignore();
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


void area_plantio:: registrarArea(){

    std::ofstream arquivoAreasON("AreaPlantio.txt", std::ios::app);
    if (!arquivoAreasON) {
        std::cerr << "Erro ao abrir o arquivo AreaPlantio.txt para escrita\n";
        return;
    }

    std::cout << "Informações sobre o proprietário:\n";
    std::cout << "Nome do proprietário: ";    std::getline(std::cin, _nome_proprietario);
    std::cout << "CNPJ do proprietário: ";    std::getline(std::cin, _cnpj_proprietario);

    std::cout << "\nInformações sobre a área:\n";
    std::cout << "Localização: ";             std::getline(std::cin, _localizacao);
    std::cout << "Tipo de solo: ";            std::getline(std::cin, _tipo_solo);
    std::cout << "Clima: ";                   std::getline(std::cin, _clima);
    std::cout << "Tamanho em hectares: ";     std::cin >> _tamanho;
   
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Limpa o buffer
    arquivoAreasON.close();
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

void area_plantio:: atualizarStatusArquivo(){
    // Atualiza o arquivo que armazena as informações da área
    std::fstream arquivoArea("AreaPlantio.txt", std::ios::in | std::ios::out);
    if (!arquivoArea) {
        throw std::runtime_error("Erro ao abrir o arquivo AreaPlantio.txt");
    }

    int contador_areas;
    arquivoArea >> contador_areas;
    arquivoArea.ignore();

    std::string* linhas = new std::string[contador_areas];

    // Lê todas as linhas do arquivo
    for (int i = 0; i < contador_areas; i++) {
        std::string linha_atual;
        std::getline(arquivoArea, linha_atual);

        // Identifica a área correspondente
        std::stringstream ss(linha_atual);
        int id_area;
        ss >> id_area;

        if (id_area == _id_area) {
            // Atualiza o status da área correspondente
            std::stringstream nova_linha;
            nova_linha << _id_area << " "  << _status << "+" << _nome_proprietario << "+"  << _cnpj_proprietario << "+" << _localizacao << "+" 
                        << _tipo_solo << "+" << _clima << "+"  << _tamanho;
            linhas[i] = nova_linha.str();
        } else {
            linhas[i] = linha_atual;
        }
    }

    arquivoArea.seekg(0,std::ios::beg);                    //leva o apontador até a posicao do contador do arquivo
    arquivoArea<<_id_area <<std::endl;                    //atualiza o contador

    // Fecha o arquivo de leitura
    arquivoArea.close();

    // Reescreve o arquivo com os dados atualizados
    std::ofstream arquivoSaida("AreaPlantio.txt", std::ios::trunc);
    if (!arquivoSaida) {
        delete[] linhas;
        throw std::runtime_error("Erro ao reescrever o arquivo AreaPlantio.txt");
    }

    arquivoSaida << contador_areas << std::endl;
    for (int i = 0; i < contador_areas; i++) {
        arquivoSaida << linhas[i] << std::endl;
    }

    delete[] linhas;
    arquivoSaida.close();
}

void area_plantio::registrarPlantio(int id_lote) {
    if (_status != "Disponível") {
        throw std::runtime_error("Área não está disponível para plantio.");
    }

    // Atualiza o estado do objeto
    _sementes_plantadas.push_back(id_lote);
    _status = "Em uso";

    atualizarStatusArquivo();
    
    std::cout << "Plantio registrado com sucesso!\n";
}

bool area_plantio::verificarDisponibilidade() {
    if(_status=="Disponível"){
        return true;
    }else{
        return false;
    }
}

void area_plantio::liberarArea() {
    // Atualiza o status da área para "Disponível"
    _status = "Disponível";

    // Limpa as sementes plantadas
    _sementes_plantadas.clear();
    atualizarStatusArquivo();
}


void area_plantio::gerar_relatorioArea() {
    exibirDetalhes();
    // Aicionar mais informações específicas para o relatório se necessário
}


void area_plantio::buscar_lotes_dessa_semente(int id_semente_busca){
    std::ifstream arquivoLotes("Lotes.txt");
    if(!arquivoLotes)
        std::cerr<<"Erro ao abrir arquivo Lotes.txt";

    int quant_lotes;      arquivoLotes>>quant_lotes; 
    arquivoLotes.ignore(); arquivoLotes>>quant_lotes; 

    int id_lote;
    int id_semente_lido;
    std::string linha;
    Lote *lote_teste;

    for(int i=0;i<quant_lotes;i++){
        arquivoLotes>>id_semente_lido;

        if(id_semente_lido==id_semente_busca){
            arquivoLotes.ignore();    arquivoLotes>>id_lote;
            lote_teste=new Lote(id_lote);

            //nesse caso aqui ele ja vai imprimir os lotes apenas por saber que o clima
            //e o solo batem
            //aqui deve ser estipulado os pesos, de modo que so sera imprimido na tela
            //se o x% for atingido
            lote_teste->exibirDetalhes();
            delete lote_teste;
        }   
        std::getline(arquivoLotes,linha);
    }
    arquivoLotes.close();
}


void area_plantio::compatibilidade_semente(){
    
    std::ifstream arquivoSementes("Sementes.txt");
    if(!arquivoSementes){
        std::cerr<<"Erro ao abrir arquivo Sementes.txt";
    }
    int quant_sementes;            arquivoSementes>>quant_sementes; 
    arquivoSementes.ignore();      arquivoSementes>>quant_sementes;

    int id_semente;
    std::string linha;
    std::string solo_semente;
    std::string clima_semente;

    //so serao oferecidas sementes com compatibilidade de solo e clima, necessariamente

    for(int i=0;i<quant_sementes;i++){
        arquivoSementes>>id_semente;     arquivoSementes.ignore();
        std::getline(arquivoSementes,solo_semente,'+');
        std::getline(arquivoSementes,clima_semente,'+');

        if(solo_semente==_tipo_solo&&clima_semente==_clima){
            buscar_lotes_dessa_semente(id_semente);
        }   
        std::getline(arquivoSementes,linha);
    }

    arquivoSementes.close();
}

int area_plantio::get_id_area() {
    return _id_area;
}

std::string area_plantio::get_nome_proprietario() {
    return _nome_proprietario;
}

std::string area_plantio::get_cnpj_proprietario(){
    return _cnpj_proprietario;
}

float area_plantio::get_tamanho(){
    return _tamanho;
}

std::string area_plantio::get_localizacao(){
    return _localizacao;
}

std::string area_plantio::get_tipo_solo(){
    return _tipo_solo;
}

std::string area_plantio::get_clima(){
    return _clima;
}

std::string area_plantio::get_status(){
    return _status;
}
