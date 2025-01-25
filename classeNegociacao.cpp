#include "classeNegociacao.hpp"
#include <iostream>
#include <iomanip>

// Construtor
#include <iostream>
#include <fstream>
#include <string>

Negociacao::Negociacao() 
    : _id_negociacao(0), _id_lote(0), _id_area(0), _data_negociacao(""), 
      _valor_negociado(0.0), _status("Pendente"), _desconto(0.0), 
      _quantidade_semente_negociada(0.0) 
{
    // Nome correto do arquivo para evitar inconsistências
    const std::string nomeArquivo = "Negociacao.txt";

    // Tentar abrir o arquivo para leitura e escrita
    std::fstream arquivoAreaPlantio(nomeArquivo, std::ios::in | std::ios::out);

    if (!arquivoAreaPlantio.is_open()) {
        // Se o arquivo não existir, criar um novo
        std::ofstream novoArquivo(nomeArquivo);
        if (!novoArquivo) {
            std::cerr << "Erro ao criar o arquivo " << nomeArquivo << "\n";
            return;
        }

        // Escrevendo valores iniciais no novo arquivo
        novoArquivo << "0 0" << std::endl;
        novoArquivo.close();

        // Inicializando _id_negociacao como 0
        _id_negociacao = 0;
    }
}

// Getters
int Negociacao::get_id_negociacao(){
    return _id_negociacao;
}

int Negociacao::get_id_lote(){
    return _id_lote;
}

int Negociacao::get_id_area(){
    return _id_area;
}
std::string Negociacao::get_data_negociacao(){
    return _data_negociacao;
}

float Negociacao::get_valor_negociado() {
    return _valor_negociado;
}

std::string Negociacao::get_status() {
    return _status;
}

float Negociacao::get_desconto() {
    return _desconto;
}

float Negociacao::get_quantidade_semente_negociada(){
    return _quantidade_semente_negociada;
}

// Setters
void Negociacao::set_id_negociacao(int id) {
    _id_negociacao = id;
}

void Negociacao::set_id_lote(int id) {
    _id_lote = id;
}

void Negociacao::set_id_area(int id) {
    _id_area = id;
}

void Negociacao::set_data_negociacao(const std::string& data) {
    _data_negociacao = data;
}

void Negociacao::set_valor_negociado(float valor) {
    _valor_negociado = valor;

}

void Negociacao::set_status(std::string status) {
    _status = status;
}

void Negociacao::set_desconto(float desconto) {
    _desconto = desconto;
}

void Negociacao::set_quantidade_semente_negociada(float quantidade) {
    _quantidade_semente_negociada = quantidade;
}

// Método de exibição de detalhes
void Negociacao::exibir_detalhes() {
    std::cout << "=== Detalhes da Negociação ===\n"
              << "ID: " << _id_negociacao << "\n"
              << "Data: " << _data_negociacao << "\n"
              << "Valor Negociado: R$ " << std::fixed << std::setprecision(2) << _valor_negociado << "\n"
              << "Status: " << _status << "\n"
              << "Desconto: " << _desconto << "%\n"
              << "Quantidade de Sementes: " << _quantidade_semente_negociada << "\n";
    
    if (_id_lote!=0) {
        std::cout << "ID do Lote: " << _id_lote << "\n";
    }
    
    if (_id_area!=0) {
        std::cout << "ID da Área: " << _id_area << "\n";
    }
}