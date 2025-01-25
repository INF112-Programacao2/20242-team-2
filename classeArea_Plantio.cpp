#include "classeArea_Plantio.hpp"
#include <limits>
#include <fstream>
#include <iostream>
#include <sstream>

AreaPlantio::AreaPlantio() {
    _status = "Disponível";
    _sementes_plantadas.clear();

    // Nome correto do arquivo para evitar inconsistências
    const std::string nomeArquivo = "AreaPlantio.txt";

    std::fstream arquivoAreaPlantio(nomeArquivo, std::ios::in | std::ios::out);

    if (!arquivoAreaPlantio.is_open()) {
        std::ofstream novoArquivo(nomeArquivo);
        if (!novoArquivo) {
            std::cerr << "Erro ao criar o arquivo AreaPlantio.txt\n";
            return;
        }
        novoArquivo << "0 0" <<std::endl;
        novoArquivo.close();
        _id_area = 0;
    }
}

AreaPlantio::AreaPlantio(int id_area) {             

    int id_contador;                  
    std::ifstream arquivoAreas("AreaPlantio.txt");
    if (!arquivoAreas)
        std::cerr << "Erro ao abrir o arquivo Areas.txt\n";

    std::string linha;
    for (int i = 0; i < id_area; i++) {
        std::getline(arquivoAreas, linha);
    }

    arquivoAreas >> _id_area >> id_contador; 
    _id_area++;
    arquivoAreas.ignore();
    std::getline(arquivoAreas, _status, '+');
    std::getline(arquivoAreas, _nome_proprietario, '+');
    std::getline(arquivoAreas, _cnpj_proprietario, '+');
    std::getline(arquivoAreas, _localizacao, '+');
    std::getline(arquivoAreas, _tipo_solo, '+');
    std::getline(arquivoAreas, _clima, '+');       
    arquivoAreas >> _tamanho;                            

    arquivoAreas.close();
}

AreaPlantio::~AreaPlantio() {}

bool AreaPlantio::verificarDisponibilidade(int id_area) {
    std::ifstream arquivoAreas("AreaPlantio.txt");
    if (!arquivoAreas) {
        std::cerr << "Erro ao abrir arquivo AreaPlantio.txt\n";
        return false;
    }

    std::string linha;
    int id_lido;
    std::string status;

    // Pula o contador inicial
    std::getline(arquivoAreas, linha);

    while (std::getline(arquivoAreas, linha)) {
        std::stringstream ss(linha);
        
        // Extrai o ID
        ss >> id_lido;
        
        if (id_lido == id_area) {
            // Extrai o status
            std::getline(ss, status, '+');
            
            return (status == "Disponível");
        }
    }

    // Se o ID não foi encontrado
    std::cerr << "Área com ID " << id_area << " não encontrada.\n";
    return false;
}

void AreaPlantio::exibirArea() {
    int id;
    std::string nome_proprietario, cnpj_proprietario, localizacao, tipo_solo, clima, status;
    float tamanho;
    std::vector<int> sementes_plantadas;

    std::cout << "Deseja visualizar os dados de qual área? ID: ";
    std::cin >> id;
    if (id <= 0)
        throw std::invalid_argument("Valor de ID invalido");

    std::fstream arquivoAreaPlantio("AreaPlantio.txt");
    if (!arquivoAreaPlantio)
        std::cerr << "Erro ao abrir o arquivo AreaPlantio.txt\n";

    std::string linha;
    int id_lido = 0;

    while (id_lido != id) {
        std::getline(arquivoAreaPlantio, linha);
        arquivoAreaPlantio >> id_lido;
        if (arquivoAreaPlantio.fail()) {
            throw std::invalid_argument("Nao existe nenhuma area com esse id");
        }
    }
    arquivoAreaPlantio.ignore();

    getline(arquivoAreaPlantio, nome_proprietario, '+');
    getline(arquivoAreaPlantio, cnpj_proprietario, '+');
    arquivoAreaPlantio >> tamanho;
    arquivoAreaPlantio.ignore();
    getline(arquivoAreaPlantio, localizacao, '+');
    getline(arquivoAreaPlantio, tipo_solo, '+');
    getline(arquivoAreaPlantio, clima, '+');
    getline(arquivoAreaPlantio, status);

    arquivoAreaPlantio.close();

    for(int i = 0; i < 50; i++) std::cout << "-";
    std::cout << std::endl;

    std::cout << "Dados da área:\n"
              << "ID: " << id << "\n"
              << "Nome Proprietario: " << nome_proprietario << "\n"
              << "CNPJ Proprietario: " << cnpj_proprietario << "\n"
              << "Tamanho: " << tamanho << " hectares\n"
              << "Localização: " << localizacao << "\n"
              << "Tipo Solo: " << tipo_solo << "\n"
              << "Clima: " << clima << "\n"
              << "Status: " << status << "\n";

    for(int i = 0; i < 50; i++) std::cout << "-";
    std::cout << std::endl;
}

// Implementações dos métodos set
void AreaPlantio::set_id_area(int id){
    _id_area=id;
}

void AreaPlantio::set_nome_proprietario(std::string nome) {
    _nome_proprietario = nome;
}

void AreaPlantio::set_cnpj_proprietario(std::string cnpj) {
    _cnpj_proprietario = cnpj;
}

void AreaPlantio::set_tamanho(float tamanho) {
    _tamanho = tamanho;
}

void AreaPlantio::set_localizacao(std::string localizacao) {
    _localizacao = localizacao;
}

void AreaPlantio::set_tipo_solo(std::string tipo_solo) {
    _tipo_solo = tipo_solo;
}

void AreaPlantio::set_clima(std::string clima) {
    _clima = clima;
}

void AreaPlantio::set_status(std::string status) {
    _status = status;
}

void AreaPlantio::adicionar_semente_plantada(int id_semente) {
    _sementes_plantadas.push_back(id_semente);
}

// Implementações dos métodos get

int AreaPlantio::get_id_area() {
    return _id_area;
}

std::string AreaPlantio::get_nome_proprietario() {
    return _nome_proprietario;
}

std::string AreaPlantio::get_cnpj_proprietario() {
    return _cnpj_proprietario;
}

float AreaPlantio::get_tamanho() {
    return _tamanho;
}

std::string AreaPlantio::get_localizacao() {
    return _localizacao;
}

std::string AreaPlantio::get_tipo_solo() {
    return _tipo_solo;
}

std::string AreaPlantio::get_clima() {
    return _clima;
}

std::string AreaPlantio::get_status() {
    return _status;
}

std::vector<int> AreaPlantio::get_sementes_plantadas(){
    return _sementes_plantadas;
}