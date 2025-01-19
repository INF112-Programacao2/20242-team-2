#include "classeNegociacao.hpp"
#include <limits>
#include <fstream>
#include <iostream>
#include <ctime>
#include <iomanip>
#include <sstream>


// função para capturar a data atual no formato DD/MM/AAAA.
std::string negociacao:: getCurrentDate() {
    time_t now = time(0); // obtém o tempo atual em segundos desde o Epoch.
    tm* ltm = localtime(&now); // converte o tempo para uma estrutura tm.
    
    std::ostringstream oss;
    oss << std::setfill('0') 
        << std::setw(2) << ltm->tm_mday << "/" // dia com 2 dígitos.
        << std::setw(2) << (ltm->tm_mon + 1) << "/" // mês com 2 dígitos (0-based).
        << (ltm->tm_year + 1900); // ano completo.
    
    return oss.str();
}

// método para validar uma data no formato DD/MM/AAAA.
bool negociacao::validarData(const std::string& data) {
    // verifica se o comprimento e o formato básico estão corretos.
    if (data.length() != 10) return false;
    if (data[2] != '/' || data[5] != '/') return false;
    
    try {
        // extrai dia, mês e ano como inteiros.
        int dia = std::stoi(data.substr(0, 2));
        int mes = std::stoi(data.substr(3, 2));
        int ano = std::stoi(data.substr(6, 4));

        // verifica os valores básicos de mês e ano.
        if (mes < 1 || mes > 12) return false;
        if (ano < 1900) return false;

        // define os dias máximos de cada mês.
        int diasPorMes[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

        // ajusta fevereiro para anos bissextos.
        if ((ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0)) {
            diasPorMes[1] = 29;
        }

        // verifica o valor do dia.
        if (dia < 1 || dia > diasPorMes[mes - 1]) return false;

        return true;
    } catch (...) {
        // captura qualquer erro durante a conversão.
        return false;
    }
}

// Método para calcular descontos. Deve ser implementado posteriormente.
float negociacao::calcularDesconto() {
    float desconto = 0.0;
    return desconto;
}

// construtor da classe negociacao.
negociacao::negociacao() {
    // inicializa todos os membros com valores padrão
    _id_negociacao = 0;
    _lote = nullptr;
    _area = nullptr;
    _data_negociacao = "";
    _valor_negociado = 0.0;
    _status = "Pendente";

    _quantidade_semente_negociada=0;

    // Verifica se o arquivo existe
    std::ifstream verificaArquivo("Negociacao.txt");
    if (!verificaArquivo.is_open()) {
        // Cria um novo arquivo apenas se ele não existir
        std::ofstream novoArquivo("Negociacao.txt");
        if (!novoArquivo.is_open()) {
            throw std::runtime_error("Erro ao criar arquivo Negociacao.txt");
        }
        novoArquivo << "0" << std::endl; // Inicializa o contador de IDs
        novoArquivo.close();
    } else {
        verificaArquivo.close();
    }
}

void negociacao::registrarNegociacao(lote* lote, area_plantio* area, float quantidade_semente_negociada, std::string data) {
    if (lote == nullptr || area == nullptr) {
        throw std::invalid_argument("Lote ou área inválidos");
    }
    
    if (area->verificarDisponibilidade() == false) {
        throw std::runtime_error("Área já está ocupada");
    }
    
    if (!data.empty() && !validarData(data)) {
        throw std::invalid_argument("Formato de data inválido (deve ser DD/MM/AAAA)");
    }

    // Lê e incrementa o ID da negociação
    std::fstream arquivo("Negociacao.txt", std::ios::in | std::ios::out);
    if (!arquivo) {
        throw std::runtime_error("Erro ao abrir arquivo para leitura do ID");
    }
    
    std::string linha;
    std::getline(arquivo, linha);
    _id_negociacao = std::stoi(linha) + 1;
    
    // Volta ao início do arquivo e escreve o novo ID
    arquivo.seekp(0);
    arquivo << _id_negociacao << std::endl;
    arquivo.close();

    _lote = lote;
    _area = area;
    _valor_negociado = lote->get_preco_estimado()*quantidade_semente_negociada;
    _quantidade_semente_negociada=quantidade_semente_negociada;
    _data_negociacao = data.empty() ? getCurrentDate() : data;
    
    std::ofstream arquivoAppend("Negociacao.txt", std::ios::app);
    if (!arquivoAppend) {
        throw std::runtime_error("Erro ao abrir arquivo para salvar negociação");
    }
    
    arquivoAppend << _id_negociacao << " " << _lote->get_id_lote() << "+" << _area->get_id_area() << "+"
                  << _data_negociacao << "+" << std::fixed << std::setprecision(2) << _valor_negociado << "+" << _status << "\n";

    lote->consumirSementes(lote->get_id_lote(), quantidade_semente_negociada);
}

void negociacao::atualizarStatusArquivo(int id_negociacao) {
    std::fstream arquivoNegociacao("Negociacao.txt", std::ios::in | std::ios::out);
    if (!arquivoNegociacao) {
        throw std::runtime_error("Erro ao abrir o arquivo Negociacao.txt");
    }

    int contador_negociacoes;
    arquivoNegociacao >> contador_negociacoes;
    arquivoNegociacao.ignore();

    if (id_negociacao <= 0 || id_negociacao > contador_negociacoes) {
        throw std::runtime_error("ID de negociação inválido");
    }

    std::string* linhas = new std::string[contador_negociacoes];

    // Lê todas as linhas do arquivo
    for (int i = 0; i < contador_negociacoes; i++) {
        if (i + 1 == id_negociacao) {
            // Lê a negociação que será atualizada
            std::string linha_atual;
            std::getline(arquivoNegociacao, linha_atual);
            
            // Cria nova linha com status atualizado
            std::stringstream nova_linha;
            nova_linha << _id_negociacao << " "<< _lote->get_id_lote() << "+" << _area->get_id_area() << "+" << _data_negociacao << "+"
                        << _valor_negociado << "+" << _status;
            
            linhas[i] = nova_linha.str();
        } else {
            std::getline(arquivoNegociacao, linhas[i]);
        }
    }

    // Reescreve o arquivo com o conteúdo atualizado
    arquivoNegociacao.close();
    std::ofstream arquivoSaida("Negociacao.txt", std::ios::trunc);
    
    if (!arquivoSaida) {
        delete[] linhas;
        throw std::runtime_error("Erro ao reescrever o arquivo Negociacao.txt");
    }

    arquivoSaida << contador_negociacoes << std::endl;
    for (int i = 0; i < contador_negociacoes; i++) {
        arquivoSaida << linhas[i] << std::endl;
    }

    delete[] linhas;
    arquivoSaida.close();
}

void negociacao::finalizarNegociacao() {
    if (_lote == nullptr || _area == nullptr) {
        throw std::runtime_error("Negociação não inicializada corretamente");
    }

    if (_status == "Pendente") {
        try {
            // Remove a chamada duplicada de registrarPlantio
            _area->registrarPlantio(_lote->get_id_lote());
            _status = "Concluída";
            atualizarStatusArquivo(_id_negociacao);
            std::cout << "Negociação finalizada com sucesso!\n";
        } catch (const std::exception& e) {
            _status = "Pendente"; // Reverte o status em caso de erro
            throw std::runtime_error(std::string("Erro ao finalizar negociação: ") + e.what());
        }
    } else {
        throw std::runtime_error("Negociação não pode ser finalizada. Status atual: " + _status);
    }
}

// Método para cancelar uma negociação.
void negociacao::cancelarNegociacao() {
    if (_lote == nullptr || _area == nullptr) {
        throw std::runtime_error("Negociação não inicializada corretamente");
    }

    if (_status == "Pendente") {
        _status = "Cancelada";
        
        try {
            atualizarStatusArquivo(_id_negociacao);
            std::cout << "Negociação cancelada com sucesso!\n";
        } catch (const std::exception& e) {
            _status = "Pendente"; // Reverte o status em caso de erro
            throw std::runtime_error(std::string("Erro ao cancelar negociação: ") + e.what());
        }
    } else {
        throw std::runtime_error("Negociação não pode ser cancelada. Status atual: " + _status);
    }
}

// método para gerar um relatório da negociação atual.
void negociacao::gerar_relatorioNegociacao() {
    std::cout << "\n=== Relatório da Negociação ===\n"
              << "ID: " << _id_negociacao << "\n"
              << "Data: " << _data_negociacao << "\n"
              << "Valor: R$ " << std::fixed << std::setprecision(2) << _valor_negociado << "\n"
              << "Status: " << _status << "\n"
              << "Desconto aplicável: R$ " << calcularDesconto() << "\n"; // ,ostra o desconto, se aplicável.

    // exibe detalhes do lote, se associado.
    if (_lote != nullptr) {
        _lote->exibirDetalhes(); // método fictício para exibir detalhes do lote.
        std::cout << "\n";
    } else {
        std::cout << "\nLote não associado\n";
    }

    // exibe detalhes da área, se associada.
    if (_area != nullptr) {
        std::cout << "\nInformações da Área:\n";
        _area->exibirDetalhes(); // método fictício para exibir detalhes da área.
    } else {
        std::cout << "\nÁrea não associada\n";
    }
}
