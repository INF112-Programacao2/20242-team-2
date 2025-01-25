#include "Vendedor.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
#include <ctime>
#include <limits>

//_________________________________________Métodos para Area de Plantio_________________________________________________________________

void Vendedor::registrarArea() {
    AreaPlantio novaArea;
    int id;
    std::string nome, cnpj, localizacao, tipo_solo, clima, status;
    float tamanho;

    std::ifstream arquivoAreas("AreaPlantio.txt");
    if (!arquivoAreas.is_open()) {
        throw std::ios_base::failure("Erro ao abrir o arquivo AreaPlantio.txt para leitura");
    }
    arquivoAreas >> id;
    id++;
    arquivoAreas.close();

    std::cout << "Insira os detalhes da área:\n";           std::cin.ignore();  
    std::cout << "Nome do Proprietário: ";                  std::getline(std::cin, nome);
    std::cout << "CNPJ do Proprietário: ";                  std::getline(std::cin, cnpj);
    std::cout << "Tamanho da Área (hectares): ";            std::cin >> tamanho;  std::cin.ignore();        
    std::cout << "Localização: ";                           std::getline(std::cin, localizacao);
    std::cout << "Tipo de Solo: ";                          std::getline(std::cin, tipo_solo);
    std::cout << "Clima: ";                                 std::getline(std::cin, clima);
    status="Disponível";

    // Valida os inputs
    if (nome.empty() || cnpj.empty() || tamanho <= 0 || 
        localizacao.empty() || tipo_solo.empty() || clima.empty()){
        throw std::invalid_argument("Dados inválidos para registro de área");
    }

    // Set informações da area
    novaArea.set_id_area(id);
    novaArea.set_nome_proprietario(nome);
    novaArea.set_cnpj_proprietario(cnpj);
    novaArea.set_tamanho(tamanho);
    novaArea.set_localizacao(localizacao);
    novaArea.set_tipo_solo(tipo_solo);
    novaArea.set_clima(clima);
    novaArea.set_status(status);

    // Registra area
    areasRegistradas.push_back(novaArea);
    salvarArea(novaArea);
}

void Vendedor:: atualizarArquivo( std::vector<std::string>& linhas) {
        std::ofstream arquivoSaida("AreaPlantio.txt");
        if (!arquivoSaida) {
            throw std::runtime_error("Erro ao abrir o arquivo AreaPlantio.txt para escrita.");
        }

        for (const auto& linha : linhas) {
            arquivoSaida << linha << "\n";
        }
        arquivoSaida.close();
}

void Vendedor::salvarArea(AreaPlantio area) {
    int cont_id, cont_registros;
    try {
        std::fstream arquivo("AreaPlantio.txt", std::ios::in | std::ios::out);
        if (!arquivo.is_open()) {
            throw std::ios_base::failure("Erro ao abrir o arquivo para registro.");
        }

        // Le os contadores
        arquivo >> cont_id >> cont_registros;
        cont_id++;
        cont_registros++;

        arquivo.seekp(0, std::ios::end);
        
        // Write area details
        arquivo << area.get_id_area() << " " 
                << area.get_status()  << "+"
                << area.get_nome_proprietario() << "+" 
                << area.get_cnpj_proprietario() << "+" 
                << area.get_localizacao() << "+" 
                << area.get_tipo_solo() << "+" 
                << area.get_clima() << "+"
                << area.get_tamanho(); 


        std::vector<int> sementes = area.get_sementes_plantadas();
        if (!sementes.empty()) {
            arquivo << "+";
            for (size_t i = 0; i < sementes.size(); ++i) {
                arquivo << sementes[i];
                if (i < sementes.size() - 1) arquivo << ",";
            }
        }
        arquivo << "\n";

        //Atualiza contadores
        arquivo.seekp(0, std::ios::beg);
        arquivo << cont_id << " " << cont_registros << std::endl;

        std::cout << "Área registrada com sucesso!" << std::endl;
        arquivo.close();

    } catch (const std::ios_base::failure& e) {
        std::cerr << "Exceção de I/O: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Exceção geral: " << e.what() << std::endl;
    }
}

void Vendedor::listarAreasRegistradas() {
    std::ifstream arquivoAreas("AreaPlantio.txt");
    if (!arquivoAreas) {
        std::cerr << "Erro ao abrir o arquivo AreaPlantio.txt\n";
        return;
    }

    int contador_id, contador_areas;
    arquivoAreas >> contador_id >> contador_areas;
    arquivoAreas.ignore();

    std::string linha;
    std::cout << "=== Áreas de Plantio Registradas ===\n";

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

void Vendedor::registrarPlantio() {
    // Abre o arquivo para leitura
    std::ifstream arquivoEntrada("AreaPlantio.txt");
    if (!arquivoEntrada) {
        throw std::runtime_error("Erro ao abrir o arquivo AreaPlantio.txt");
    }

    int ultimo_id, total_areas;
    arquivoEntrada >> ultimo_id >> total_areas;
    arquivoEntrada.ignore(); // Ignora a quebra de linha após a leitura de inteiros

    std::vector<std::string> todas_areas;
    std::vector<int> areas_em_uso;  // Lista para áreas em uso
    std::string linha;

    todas_areas.push_back(std::to_string(ultimo_id) + " " + std::to_string(total_areas));

    std::cout << "\n=== Áreas Disponíveis ===\n";

    // Lê o arquivo e lista apenas áreas disponíveis
    while (std::getline(arquivoEntrada, linha)) {
        std::stringstream ss(linha);
        int id_area;
        std::string status;

        ss >> id_area; 
        std::getline(ss, status, '+'); // Leitura do status após o ID da área

        // Verifica se o status da área é 'Disponível'
        if (status == " Disponível") {
            areas_em_uso.push_back(id_area);
            std::cout << "ID: " << id_area << " - Status: " << status << "\n";
        }

        todas_areas.push_back(linha);  // Armazena todas as linhas
    }
    arquivoEntrada.close();

    if (areas_em_uso.empty()) {
        std::cout << "Não há áreas disponíveis para liberar.\n";
        return;
    }

    // Solicita o ID da área a ser liberada
    int id_area;
    std::cout << "\nDigite o ID da área que deseja registrar: ";
    std::cin >> id_area;

    AreaPlantio area(id_area);

    // Verifica se o ID existe na lista de áreas em uso
    bool found = false;
    for (int area_id : areas_em_uso) {
        if (area_id == id_area) {
            found = true;
            break;
        }
    }

    if (!found) {
        std::cout << "Área com ID " << id_area << " não encontrada ou já está disponível.\n";
        return;
    }

    area.set_status("Em uso");

    // Atualiza o status da área no vetor de linhas
    for (auto& linha : todas_areas) {
        std::stringstream ss(linha);
        std::string status, nome, id_lote, estado, tipo_plantio, clima, tamanho;
        int id_lido;

        // Lê todos os campos da linha
        ss >> id_lido;
        std::getline(ss, status, '+');
        std::getline(ss, nome, '+');
        std::getline(ss, id_lote, '+');
        std::getline(ss, estado, '+');
        std::getline(ss, tipo_plantio, '+');
        std::getline(ss, clima, '+');
        std::getline(ss, tamanho, '+');

        // Verifica e atualiza o status da área
        if (id_lido == id_area) {
            linha = std::to_string(id_lido) + " Em uso+" + nome + "+" + id_lote + "+" + estado + "+" + tipo_plantio + "+" + clima + "+" + tamanho;
            break;
        }
    }

    // Reescreve o arquivo com as atualizações
    std::ofstream arquivoSaida("AreaPlantio.txt", std::ios::trunc);
    if (!arquivoSaida) {
        throw std::runtime_error("Erro ao abrir o arquivo AreaPlantio.txt para escrita.");
    }

    for (const auto& linha : todas_areas) {
        arquivoSaida << linha << "\n";
    }
    arquivoSaida.close();

    std::cout << "Área " << id_area << " foi liberada com sucesso. Status atualizado para 'Em uso'.\n";
}


void Vendedor::liberarArea() {
    // Abre o arquivo para leitura
    std::ifstream arquivoEntrada("AreaPlantio.txt");
    if (!arquivoEntrada) {
        throw std::runtime_error("Erro ao abrir o arquivo AreaPlantio.txt");
    }

    int ultimo_id, total_areas;
    arquivoEntrada >> ultimo_id >> total_areas;
    arquivoEntrada.ignore();  // Ignora o '\n' após a leitura de inteiros

    std::vector<std::string> todas_areas;
    std::vector<int> areas_em_uso;  // Lista para áreas em uso
    std::string linha;

    todas_areas.push_back(std::to_string(ultimo_id) + " " + std::to_string(total_areas));

    std::cout << "\n=== Áreas em Uso ===\n";

    // Lê o arquivo e lista apenas áreas em uso
    while (std::getline(arquivoEntrada, linha)) {
        std::stringstream ss(linha);
        int id_area;
        std::string status;

        ss >> id_area; 
        std::getline(ss, status, '+');

        // Exibe áreas que não estão disponíveis
        if (status != " Disponível") {
            areas_em_uso.push_back(id_area);
            std::cout << "ID: " << id_area << " - Status: " << status << "\n";
        }

        todas_areas.push_back(linha);  // Armazena todas as linhas
    }
    arquivoEntrada.close();

    if (areas_em_uso.empty()) {
        std::cout << "Não há áreas em uso para liberar.\n";
        return;
    }

    // Solicita o ID da área a ser liberada
    int id_area;
    std::cout << "\nDigite o ID da área que deseja liberar: ";
    std::cin >> id_area;

    // Verifica se o ID existe na lista de áreas em uso
    bool found = false;
    for (int area_id : areas_em_uso) {
        if (area_id == id_area) {
            found = true;
            break;
        }
    }

    if (!found) {
        std::cout << "Área com ID " << id_area << " não encontrada ou já está disponível.\n";
        return;
    }

    // Atualiza o status da área no vetor de linhas
    for (auto& linha : todas_areas) {
        std::stringstream ss(linha);
        std::string status, nome, id_lote, estado, tipo_plantio, clima, tamanho;
        int id_lido;

        // Lê todos os campos da linha
        ss >> id_lido;
        std::getline(ss, status, '+');
        std::getline(ss, nome, '+');
        std::getline(ss, id_lote, '+');
        std::getline(ss, estado, '+');
        std::getline(ss, tipo_plantio, '+');
        std::getline(ss, clima, '+');
        std::getline(ss, tamanho);

        // Verifica e atualiza o status da área
        if (id_lido == id_area) {
            linha = std::to_string(id_lido) + " Disponível+" + nome + "+" + id_lote + "+" + estado + "+" + tipo_plantio + "+" + clima + "+" + tamanho;
            break;
        }
    }

    // Reescreve o arquivo com as atualizações
    std::ofstream arquivoSaida("AreaPlantio.txt", std::ios::trunc);
    if (!arquivoSaida) {
        throw std::runtime_error("Erro ao abrir o arquivo AreaPlantio.txt para escrita.");
    }

    for (const auto& linha : todas_areas) {
        arquivoSaida << linha << "\n";
    }
    arquivoSaida.close();

    std::cout << "Área " << id_area << " foi liberada com sucesso. Status atualizado para 'Disponível'.\n";
}

/*void Vendedor::buscar_lotes_dessa_semente(int id_semente_busca) {
    std::ifstream arquivoLotes("Lotes.txt");
    if (!arquivoLotes)
        std::cerr << "Erro ao abrir arquivo Lotes.txt";

    int quant_lotes;
    arquivoLotes >> quant_lotes; 
    arquivoLotes.ignore(); 
    arquivoLotes >> quant_lotes; 

    int id_lote;
    int id_semente_lido;
    std::string linha;
    Lote *lote_teste;

    for (int i = 0; i < quant_lotes; i++) {
        arquivoLotes >> id_semente_lido;

        if (id_semente_lido == id_semente_busca) {
            arquivoLotes.ignore();
            arquivoLotes >> id_lote;
            lote_teste = new Lote(id_lote);
            delete lote_teste;
        }   
        std::getline(arquivoLotes, linha);
    }
    arquivoLotes.close();
}

void Vendedor::compatibilidade_semente() {
    std::ifstream arquivoSementes("Sementes.txt");
    if (!arquivoSementes) {
        std::cerr << "Erro ao abrir arquivo Sementes.txt";
    }
    int quant_sementes;
    arquivoSementes >> quant_sementes; 
    arquivoSementes.ignore();
    arquivoSementes >> quant_sementes;

    int id_semente;
    std::string linha;
    std::string solo_semente;
    std::string clima_semente;

    for (int i = 0; i < quant_sementes; i++) {
        arquivoSementes >> id_semente;
        arquivoSementes.ignore();
        std::getline(arquivoSementes, solo_semente, '+');
        std::getline(arquivoSementes, clima_semente, '+');

        if (solo_semente == get_tipo_solo() && clima_semente == _clima) {
            buscar_lotes_dessa_semente(id_semente);
        }   
        std::getline(arquivoSementes, linha);
    }

    arquivoSementes.close();
} */

void Vendedor::excluirArea() {
    std::fstream arquivoArea("AreaPlantio.txt", std::ios::in | std::ios::out);
    if (!arquivoArea) {
        throw std::runtime_error("Erro ao abrir arquivo AreaPlantio.txt");
    }

    int cont_id, cont_registros;
    arquivoArea >> cont_id >> cont_registros; 
    arquivoArea.ignore();  // Ignora o caractere de nova linha após os contadores

    std::vector<std::string> todas_areas;
    std::string linha;

    // Lê todas as áreas para memória
    while (std::getline(arquivoArea, linha)) {
        todas_areas.push_back(linha);
    }

    bool id_existe = false;

    // Exibe as áreas registradas
    listarAreasRegistradas();
    
    int id_excluir;
    std::cout << "\nDigite o ID da área que deseja excluir: ";
    std::cin >> id_excluir;

    // Verifica se o ID existe
    for (const auto& area : todas_areas) {
        std::stringstream ss(area);
        int id_atual;
        ss >> id_atual;

        if (id_atual == id_excluir) {
            id_existe = true;
            break;
        }
    }

    if (!id_existe) {
        std::cout << "ID inválido.\n";
        return;
    }

    char confirmacao;
    std::cout << "Tem certeza que deseja excluir a área " << id_excluir << "? (S/N): ";
    std::cin >> confirmacao;

    if (toupper(confirmacao) != 'S') {
        std::cout << "Operação cancelada.\n";
        return;
    }

    // Reabre o arquivo para reescrever o conteúdo, sobrescrevendo o arquivo
    std::ofstream arquivoSaida("AreaPlantio.txt", std::ios::trunc);
    if (!arquivoSaida) {
        throw std::runtime_error("Erro ao abrir arquivo AreaPlantio.txt para escrita.");
    }

    // Escreve os contadores atualizados
    arquivoSaida << cont_id << " " << (cont_registros - 1) << std::endl;

    // Reescreve as áreas, ignorando a área a ser excluída
    for (const auto& area : todas_areas) {
        std::stringstream ss(area);
        int id_atual;
        ss >> id_atual;

        if (id_atual != id_excluir) {
            arquivoSaida << area << std::endl;
        }
    }

    std::cout << "Área " << id_excluir << " excluída com sucesso!\n";
}

//_________________________________________Métodos para negociacao_________________________________________________________________

std::string Vendedor::getCurrentDate() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    
    std::ostringstream oss;
    oss << std::setfill('0') 
        << std::setw(2) << ltm->tm_mday << "/" 
        << std::setw(2) << (ltm->tm_mon + 1) << "/" 
        << (ltm->tm_year + 1900);
    
    return oss.str();
}

bool Vendedor::validarData(std::string& data) {
    if (data.length() != 10) return false;
    if (data[2] != '/' || data[5] != '/') return false;
    
    try {
        int dia = std::stoi(data.substr(0, 2));
        int mes = std::stoi(data.substr(3, 2));
        int ano = std::stoi(data.substr(6, 4));

        if (mes < 1 || mes > 12) return false;
        if (ano < 1900) return false;

        int diasPorMes[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

        if ((ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0)) {
            diasPorMes[1] = 29;
        }

        if (dia < 1 || dia > diasPorMes[mes - 1]) return false;

        return true;
    } catch (...) {
        return false;
    }
}

void Vendedor::registrarNegociacao() {
    Negociacao novaNegociacao;
    int id, lote_id, area_id;
    std::string data;
    float quantidade_semente, desconto;

    // Read current ID from file
    std::ifstream arquivoNegociacoes("Negociacao.txt");
    if (!arquivoNegociacoes.is_open()) {
        throw std::ios_base::failure("Erro ao abrir o arquivo Negociacao.txt para leitura");
    }
    arquivoNegociacoes >> id;
    id++;
    arquivoNegociacoes.close();

    std::cout << "Insira os detalhes da Negociação:\n";
    
    std::cout << "ID do Lote: ";
    std::cin >> lote_id;
    std::cin.ignore();

    std::cout << "ID da Área: ";
    std::cin >> area_id;
    std::cin.ignore();

    std::cout << "Quantidade de Sementes Negociadas: ";
    std::cin >> quantidade_semente;
    std::cin.ignore();

    std::cout << "Data da Negociação (DD/MM/AAAA, deixe em branco para data atual): ";
    std::getline(std::cin, data);

    std::cout << "Desconto (%): ";
    std::cin >> desconto;
    std::cin.ignore();

    // Valida os inputs
    if (quantidade_semente <= 0 || 
        (!data.empty() && !validarData(data)) || 
        desconto < 0) {
        throw std::invalid_argument("Dados inválidos para registro de negociação");
    }

    // Calcular valor negociado
    Lote lote(lote_id);
    float valor_estimado = lote.getPrecoEstimado(); // Substitua pela lógica correta de obtenção do preço

    // Set informações da negociação
    novaNegociacao.set_id_negociacao(id);
    novaNegociacao.set_id_lote(lote_id);
    novaNegociacao.set_id_area(area_id);
    novaNegociacao.set_quantidade_semente_negociada(quantidade_semente);
    novaNegociacao.set_data_negociacao(data.empty() ? getCurrentDate() : data);
    novaNegociacao.set_desconto(desconto);
    novaNegociacao.set_valor_negociado((valor_estimado * quantidade_semente) * (1 - desconto/100));
    novaNegociacao.set_status("Pendente");

    // Registra negociação
    salvarNegociacao(novaNegociacao);
}

void Vendedor::salvarNegociacao(Negociacao& neg) {
    int cont_id, cont_registros;

    try {
        // Abre o arquivo Negociacao.txt para leitura e escrita
        std::fstream arquivo("Negociacao.txt", std::ios::in | std::ios::out);
        if (!arquivo.is_open()) {
            throw std::ios_base::failure("Erro ao abrir o arquivo Negociacao.txt para registro.");
        }

        // Lê os contadores no início do arquivo
        arquivo >> cont_id >> cont_registros;
        cont_id++;
        cont_registros++;

        // Move o ponteiro para o final do arquivo para registrar a negociação
        arquivo.seekp(0, std::ios::end);

        // Escreve os dados da negociação no arquivo
        arquivo << neg.get_id_negociacao() << " " 
                << neg.get_id_lote() << "+" 
                << neg.get_id_area() << "+"
                << neg.get_status() << "+"
                << neg.get_data_negociacao() << "+" 
                << std::fixed << std::setprecision(2) << neg.get_valor_negociado() << "+"
                << neg.get_quantidade_semente_negociada() 
                << "\n";

        // Atualiza os contadores no início do arquivo
        arquivo.seekp(0, std::ios::beg);
        arquivo << cont_id << " " << cont_registros << std::endl;

        std::cout << "Negociação registrada com sucesso!" << std::endl;

        arquivo.close();
    } catch (const std::ios_base::failure& e) {
        std::cerr << "Exceção de I/O: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Exceção geral: " << e.what() << std::endl;
    }
}

void Vendedor::finalizarNegociacao() {
    // Abre o arquivo para leitura
    std::ifstream arquivoEntrada("Negociacao.txt");
    if (!arquivoEntrada) {
        throw std::runtime_error("Erro ao abrir o arquivo Negociacao.txt");
    }

    int ultimo_id, total_negociacoes;
    arquivoEntrada >> ultimo_id >> total_negociacoes;
    arquivoEntrada.ignore(); // Ignora a quebra de linha após a leitura de inteiros

    std::vector<std::string> todas_negociacoes;
    std::vector<int> negociacoes_pendentes;  // Lista para negociações pendentes
    std::string linha;

    todas_negociacoes.push_back(std::to_string(ultimo_id) + " " + std::to_string(total_negociacoes));

    std::cout << "\n=== Negociações Pendentes ===\n";

    // Lê o arquivo e lista apenas negociações com status "Pendente"
    while (std::getline(arquivoEntrada, linha)) {
        std::stringstream ss(linha);
        int id_negociacao;
        std::string status, id_lote, id_area;

        ss >> id_negociacao;
        std::getline(ss,  id_lote, '+');
        std::getline(ss, id_area, '+');
        std::getline(ss, status, '+');  // Lê o status após o ID da negociação

        // Verifica se o status da negociação é "Pendente"
        if (status == "Pendente") {
            negociacoes_pendentes.push_back(id_negociacao);
            std::cout << "ID: " << id_negociacao << " - Status: " << status << "\n";
        }

        todas_negociacoes.push_back(linha);  // Armazena todas as linhas
    }
    arquivoEntrada.close();

    if (negociacoes_pendentes.empty()) {
        std::cout << "Não há negociações pendentes para finalizar.\n";
        return;
    }

    // Solicita o ID da negociação a ser finalizada
    int id_negociacao;
    std::cout << "\nDigite o ID da negociação que deseja finalizar: ";
    std::cin >> id_negociacao;

    // Verifica se o ID existe na lista de negociações pendentes
    bool found = false;
    for (int neg : negociacoes_pendentes) {
        if (neg == id_negociacao) {
            found = true;
            break;
        }
    }

    if (!found) {
        std::cout << "Negociação com ID " << id_negociacao << " não encontrada ou já foi finalizada.\n";
        return;
    }

    // Atualiza o status da negociação para "Finalizada"
    for (auto& linha : todas_negociacoes) {
        std::stringstream ss(linha);
        int id_lido;
        std::string status, id_lote, id_area, data_negociacao, valor_negociado, quantidade_semente_negociada;

        // Lê todos os campos da linha
        ss >> id_lido;
        std::getline(ss,  id_lote, '+');
        std::getline(ss, id_area, '+');
        std::getline(ss, status, '+');
        std::getline(ss, data_negociacao, '+');
        std::getline(ss, valor_negociado, '+');
        std::getline(ss, quantidade_semente_negociada);

        // Verifica e atualiza o status da negociação
        if (id_lido == id_negociacao) {
            // Atualiza a linha com o status "Finalizada"
            linha = std::to_string(id_lido) + id_lote + "+" + id_area + "+" + "Finalizada" + "+" + data_negociacao + "+" + valor_negociado + "+" + quantidade_semente_negociada;
            break;
        }
    }

    // Reescreve o arquivo com as negociações atualizadas
    std::ofstream arquivoSaida("Negociacao.txt", std::ios::trunc);
    if (!arquivoSaida) {
        throw std::runtime_error("Erro ao abrir o arquivo Negociacao.txt para escrita.");
    }

    for (const auto& linha : todas_negociacoes) {
        arquivoSaida << linha << "\n";
    }
    arquivoSaida.close();

    std::cout << "Negociação " << id_negociacao << " foi finalizada com sucesso. Status atualizado para 'Finalizada'.\n";
}


void Vendedor::listarNegociacoesRegistradas() {
    std::ifstream arquivoNegociacao("Negociacao.txt");
    if (!arquivoNegociacao) {
        std::cerr << "Erro ao abrir o arquivo Negociacao.txt\n";
        return;
    }

    int contador_id, contador_negociacoes;
    arquivoNegociacao >> contador_id >> contador_negociacoes;
    arquivoNegociacao.ignore(); // Ignora o restante da linha

    std::string linha;
    std::cout << "=== Negociações Registradas ===\n";

    for (int i = 0; i < contador_negociacoes; ++i) {
        std::getline(arquivoNegociacao, linha);
        std::stringstream ss(linha);
        int id_negociacao, id_lote, id_area;
        std::string status, data_negociacao;
        float valor_negociado;
        int quantidade_semente_negociada;

        // Lê os dados da linha
        ss >> id_negociacao;
        ss.ignore(); // Ignora o espaço após o ID da negociação
        ss >> id_lote;
        ss.ignore();
        ss >> id_area;
        ss.ignore();
        std::getline(ss, status, '+');
        std::getline(ss, data_negociacao, '+');
        ss >> valor_negociado;
        ss.ignore();
        ss >> quantidade_semente_negociada;

        // Exibe os dados
        std::cout << "ID da Negociação: " << id_negociacao << "\n";
        std::cout << "ID do Lote: " << id_lote << "\n";
        std::cout << "ID da Área: " << id_area << "\n";
        std::cout << "Status: " << status << "\n";
        std::cout << "Data da Negociação: " << data_negociacao << "\n";
        std::cout << "Valor Negociado: R$" << std::fixed << std::setprecision(2) << valor_negociado << "\n";
        std::cout << "Quantidade de Sementes Negociadas: " << quantidade_semente_negociada << "\n";
        std::cout << "-----------------------------\n";
    }

    arquivoNegociacao.close();
}


void Vendedor::excluirNegociacao() {
    std::ifstream arquivoNegociacao("Negociacao.txt");
    if (!arquivoNegociacao) {
        throw std::runtime_error("Erro ao abrir o arquivo Negociacao.txt");
    }

    int ultimo_id, total_negociacoes;
    arquivoNegociacao >> ultimo_id >> total_negociacoes;
    arquivoNegociacao.ignore(); // Ignora o restante da linha

    std::vector<std::string> todas_negociacoes;
    std::string linha;

    todas_negociacoes.push_back(std::to_string(ultimo_id) + " " + std::to_string(total_negociacoes));  

    // Lê todas as negociações do arquivo
    while (std::getline(arquivoNegociacao, linha)) {
        todas_negociacoes.push_back(linha);
    }

    bool id_existe = false;

    // Exibe as negociações registradas
    listarNegociacoesRegistradas();
    
    arquivoNegociacao.close();

    int id_excluir;
    std::cout << "\nDigite o ID da negociação que deseja excluir: ";
    std::cin >> id_excluir;

    // Verifica se o ID existe
    for (size_t i = 1; i < todas_negociacoes.size(); i++) {
        std::stringstream ss(todas_negociacoes[i]);
        int id_atual;
        ss >> id_atual;
        
        if (id_atual == id_excluir) {
            id_existe = true;
            break;
        }
    }

    if (!id_existe) {
        std::cout << "ID inválido.\n";
        return;
    }

    char confirmacao;
    std::cout << "Tem certeza que deseja excluir a negociação " << id_excluir << "? (S/N): ";
    std::cin >> confirmacao;

    if (toupper(confirmacao) != 'S') {
        std::cout << "Operação cancelada.\n";
        return;
    }

    // Reabre o arquivo para reescrever o conteúdo, sobrescrevendo o arquivo
    std::ofstream arquivoSaida("Negociacao.txt", std::ios::trunc);
    if (!arquivoSaida) {
        throw std::runtime_error("Erro ao abrir arquivo Negociacao.txt para escrita.");
    }

    // Decrementa negociações totais
    arquivoSaida << ultimo_id << " " << (total_negociacoes - 1) << std::endl;

    // Reescreve as negociações, ignorando a negociação a ser excluída
    for (size_t i = 1; i < todas_negociacoes.size(); i++) {
        std::stringstream ss(todas_negociacoes[i]);
        int id_atual;
        ss >> id_atual;

        if (id_atual != id_excluir) {
            arquivoSaida << todas_negociacoes[i] << std::endl;
        }
    }

    arquivoSaida.close();
    std::cout << "Negociação " << id_excluir << " excluída com sucesso!\n";
}

int Vendedor::acessarInterface() {

    int opcao_selecionada;

        while (true) {
            std::cout << "-----------------------MENU DO VENDEDOR------------------------\n";
            std::cout << "1- Registrar uma nova área\n";
            std::cout << "2- Listar áreas registradas\n";
            std::cout << "3- Liberar uma área\n";
            std::cout << "4- Excluir uma área\n";
            std::cout << "5- Registrar plantio\n";
            std::cout << "6- Registrar uma nova negociação\n";
            std::cout << "7- Listar negociações registradas\n";
            std::cout << "8- Finalizar uma negociação\n";
            std::cout << "9- Excluir uma negociação\n";
            std::cout << "10- Atualizar preço da semente\n";
            std::cout << "11- Sair\n";
            std::cout << "---------------------------------------------------------------\n";
            std::cout << "Escolha uma opção: ";
            std::cin >> opcao_selecionada;

            switch (opcao_selecionada) {
                case 1:
                    registrarArea();
                    break;
                case 2:
                    listarAreasRegistradas();
                    break;
                case 3:
                    liberarArea();
                    break;
                case 4:
                    excluirArea();
                    break;
                case 5:
                    registrarPlantio();
                    break;
                case 6:
                    registrarNegociacao();
                    break;
                case 7:
                    listarNegociacoesRegistradas();
                    break;
                case 8:
                    finalizarNegociacao();
                    break;
                case 9:
                    excluirNegociacao();
                    break;
                case 10:
                    //atualizarPrecoDaSemente();
                    break;
                case 11:
                    std::cout << "Saindo do menu do vendedor.\n";
                    return 0; // Encerra o menu
                default:
                    std::cout << "Opção inválida, tente novamente.\n";
            }
        }
}