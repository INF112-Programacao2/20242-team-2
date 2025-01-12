#include "classeNegociacao.hpp"
#include <limits>
#include <fstream>
#include <iostream>
#include <ctime>
#include <iomanip>
#include <sstream>


//capturar a data atual
std::string getCurrentDate() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    
    std::ostringstream oss;
    oss << std::setfill('0') 
        << std::setw(2) << ltm->tm_mday << "/"
        << std::setw(2) << (ltm->tm_mon + 1) << "/"
        << (ltm->tm_year + 1900);
    
    return oss.str();
}

bool negociacao::validarData(const std::string& data) {
    if (data.length() != 10) return false;
    if (data[2] != '/' || data[5] != '/') return false;
    
    try {
        int dia = std::stoi(data.substr(0, 2));
        int mes = std::stoi(data.substr(3, 2));
        int ano = std::stoi(data.substr(6, 4));

        // verificar valores básicos
        if (mes < 1 || mes > 12) return false;
        if (ano < 1900) return false;

        // dias máximos para cada mês
        int diasPorMes[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

        // ajustar fevereiro para anos bissextos
        if ((ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0)) {
            diasPorMes[1] = 29;
        }

        // verificar o dia
        if (dia < 1 || dia > diasPorMes[mes - 1]) return false;

        return true;
    } catch (...) {
        return false;
    }
}


float negociacao::calcularDesconto() {
    float desconto = 0.0;
    //implementar a lógica de desconto para parceiros
    return desconto;
}

negociacao::negociacao() {
    _status = "Pendente";

    std::fstream arquivoNegociacao("Negociacao.txt", std::ios::in | std::ios::out);

    if (!arquivoNegociacao.is_open()) {
        std::ofstream novoArquivo("Negociacao.txt");
        if (!novoArquivo) {
            std::cerr << "Erro ao criar o arquivo Negociacao.txt\n";
            return;
        }
        novoArquivo << "1" << std::endl;
        novoArquivo.close();
        _id_negociacao = 1;
    } else {
        arquivoNegociacao >> _id_negociacao;
        _id_negociacao++;
        arquivoNegociacao.seekp(0);
        arquivoNegociacao << _id_negociacao << std::endl;
        arquivoNegociacao.close();
    }
}

void negociacao::registrarNegociacao(lote* lote, area_plantio* area, float valor, std::string data) {
    if (lote == nullptr || area == nullptr) {
        throw std::invalid_argument("Lote ou área inválidos");
    }
    
    if (area->verificarDisponibilidade()==false) {
        throw std::runtime_error("Área já está ocupada");
    }
    
    if (!data.empty() && !validarData(data)) {
        throw std::invalid_argument("Formato de data inválido (deve ser DD/MM/AAAA)");
    }

    _lote = lote;
    _area = area;
    _valor_negociado = valor;
    _data_negociacao = data.empty() ? getCurrentDate() : data;
    
    std::ofstream arquivo("Negociacao.txt", std::ios::app);
    if (!arquivo) {
        throw std::runtime_error("Erro ao abrir arquivo para salvar negociação");
    }
    
    arquivo << _id_negociacao << " " << _lote->get_id() << " " << _area->get_id() << " "<< _data_negociacao << " " << std::fixed << std::setprecision(2) << _valor_negociado << " " << _status << "\n";
}

void negociacao::atualizarStatusArquivo() {
    std::string arquivo_temp = "Negociacao_temp.txt";
    std::ifstream arquivo_entrada("Negociacao.txt");
    std::ofstream arquivo_saida(arquivo_temp);
    
    if (!arquivo_entrada || !arquivo_saida) {
        throw std::runtime_error("Erro ao abrir arquivos para atualização de status");
    }

    std::string linha;
    int id_atual;

    // pula a primeira linha que contém o contador de IDs
    std::getline(arquivo_entrada, linha);
    arquivo_saida << linha << std::endl;

    // lê cada linha do arquivo
    while (std::getline(arquivo_entrada, linha)) {
        std::istringstream iss(linha);
        std::string data, status;
        float valor;
        int id_lote, id_area;
        
        // lê os campos da linha
        iss >> id_atual;
        
        if (id_atual == _id_negociacao) {
            // se encontrou a negociação, escreve a linha atualizada
            arquivo_saida << _id_negociacao << " "
                         << _lote->get_id() << " "
                         << _area->get_id() << " "
                         << _data_negociacao << " "
                         << std::fixed << std::setprecision(2) << _valor_negociado << " "
                         << _status << "\n";
        } else {
            // se não é a negociação que queremos atualizar, mantém a linha original
            arquivo_saida << linha << "\n";
        }
    }

    arquivo_entrada.close();
    arquivo_saida.close();

    // remove o arquivo original e renomeia o temporário
    if (std::remove("Negociacao.txt") != 0) {
        throw std::runtime_error("Erro ao remover arquivo original");
    }
    
    if (std::rename(arquivo_temp.c_str(), "Negociacao.txt") != 0) {
        throw std::runtime_error("Erro ao renomear arquivo temporário");
    }
}

void negociacao::finalizarNegociacao() {
    if (_lote == nullptr || _area == nullptr) {
        throw std::runtime_error("Negociação não inicializada corretamente");
    }

    if (_status == "Pendente") {
        _status = "Concluída";
        _area->registrarPlantio(_lote->get_id());
        atualizarStatusArquivo();
        std::cout << "Negociação finalizada com sucesso!\n";
    } else {
        throw std::runtime_error("Negociação não pode ser finalizada. Status atual: " + _status);
    }
}

void negociacao::cancelarNegociacao() {
    if (_lote == nullptr || _area == nullptr) {
        throw std::runtime_error("Negociação não inicializada corretamente");
    }

    if (_status != "Cancelada") {
        _status = "Cancelada";
        _area->liberarArea();
        atualizarStatusArquivo();
        std::cout << "Negociação cancelada com sucesso!\n";
    } else {
        throw std::runtime_error("A negociação já está cancelada");
    }
}

void negociacao::gerar_relatorioNegociacoes(){
    std::cout << "\n=== Relatório da Negociação ===\n"
              << "ID: " << _id_negociacao << "\n"
              << "Data: " << _data_negociacao << "\n"
              << "Valor: R$ " << std::fixed << std::setprecision(2) << _valor_negociado << "\n"
              << "Status: " << _status << "\n"
              << "Desconto aplicável: R$ " << calcularDesconto() << "\n";
    
    if (_lote != nullptr) {
        std::cout << "\nInformações do Lote:\n";
        _lote->exibirDetalhes();
    } else {
        std::cout << "\nLote não associado\n";
    }
    
    if (_area != nullptr) {
        std::cout << "\nInformações da Área:\n";
        _area->exibirDetalhes();
    } else {
        std::cout << "\nÁrea não associada\n";
    }
}