#include "Vendedor.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
#include <ctime>
#include <limits>
#include <algorithm>

//_________________________________________Métodos para Area de Plantio_________________________________________________________________

void Vendedor::registrarArea() {
    AreaPlantio novaArea;
    int id = 0;
    std::string nome, cnpj, localizacao, tipo_solo, clima, status;
    float tamanho;

    // Lê o último ID do arquivo
    std::ifstream arquivoAreas("AreaPlantio.txt");
    if (arquivoAreas.is_open()) {
        arquivoAreas >> id; // Lê o ID atual
        arquivoAreas.close();
    }

    id++; // Incrementa o ID para a nova área

    // Coleta os dados da nova área
    std::cout << "Insira os detalhes da área:\n";
    std::cin.ignore();
    std::cout << "Nome do Proprietário: ";
    std::getline(std::cin, nome);
    std::cout << "CNPJ do Proprietário: ";
    std::getline(std::cin, cnpj);
    std::cout << "Tamanho da Área (hectares): ";
    std::cin >> tamanho;
    std::cin.ignore();
    std::cout << "Localização: ";
    std::getline(std::cin, localizacao);
    std::cout << "Tipo de Solo: ";
    std::getline(std::cin, tipo_solo);
    std::cout << "Clima: ";
    std::getline(std::cin, clima);
    status = "Disponível";

    // Validação dos inputs
    if (nome.empty() || cnpj.empty() || tamanho <= 0 ||
        localizacao.empty() || tipo_solo.empty() || clima.empty()) {
        throw std::invalid_argument("Dados inválidos para registro de área.");
    }

    // Configura os dados da nova área
    novaArea.set_id_area(id);
    novaArea.set_nome_proprietario(nome);
    novaArea.set_cnpj_proprietario(cnpj);
    novaArea.set_tamanho(tamanho);
    novaArea.set_localizacao(localizacao);
    novaArea.set_tipo_solo(tipo_solo);
    novaArea.set_clima(clima);
    novaArea.set_status(status);

    // Registra a nova área na memória e no arquivo
    areasRegistradas.push_back(novaArea);
    salvarArea(novaArea);
}

void Vendedor::salvarArea(AreaPlantio area) {
    int cont_id = 0, cont_registros = 0;
    std::vector<std::string> linhas;

    try {
        // Abrir arquivo em modo leitura
        std::ifstream arquivoEntrada("AreaPlantio.txt");
        if (arquivoEntrada.is_open()) {
            std::string linha;

            // Ler o primeiro ID e o número de registros
            if (std::getline(arquivoEntrada, linha)) {
                std::stringstream ss(linha);
                ss >> cont_id >> cont_registros;
            }

            // Carregar as demais linhas
            while (std::getline(arquivoEntrada, linha)) {
                linhas.push_back(linha);
            }

            arquivoEntrada.close();
        }

        // Incrementar contadores
        cont_id++;
        cont_registros++;

        // Adicionar a nova área no vetor de linhas
        std::ostringstream novaLinha;
        novaLinha << area.get_id_area() << " "
                  << area.get_status() << "+"
                  << area.get_nome_proprietario() << "+"
                  << area.get_cnpj_proprietario() << "+"
                  << area.get_localizacao() << "+"
                  << area.get_tipo_solo() << "+"
                  << area.get_clima() << "+"
                  << std::fixed << std::setprecision(2) << area.get_tamanho();

        // Adicionar sementes, se houver
        std::vector<int> sementes = area.get_sementes_plantadas();
        if (!sementes.empty()) {
            novaLinha << "+";
            for (size_t i = 0; i < sementes.size(); ++i) {
                novaLinha << sementes[i];
                if (i < sementes.size() - 1) novaLinha << ",";
            }
        }

        linhas.push_back(novaLinha.str());

        // Reescrever o arquivo com os novos dados
        std::ofstream arquivoSaida("AreaPlantio.txt", std::ios::trunc);
        if (!arquivoSaida.is_open()) {
            throw std::ios_base::failure("Erro ao abrir o arquivo para escrita.");
        }

        // Escrever contadores atualizados
        arquivoSaida << cont_id << " " << cont_registros << "\n";

        // Escrever as linhas restantes
        for (const auto& linha : linhas) {
            arquivoSaida << linha << "\n";
        }

        arquivoSaida.close();

        std::cout << "Área registrada com sucesso!\n";

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
    std::ifstream arquivoEntrada("AreaPlantio.txt");
    if (!arquivoEntrada) {
        throw std::runtime_error("Erro ao abrir o arquivo AreaPlantio.txt");
    }

    int ultimo_id, total_areas;
    arquivoEntrada >> ultimo_id >> total_areas;
    arquivoEntrada.ignore();

    std::vector<std::string> todas_areas;
    std::vector<int> areas_disponiveis;
    std::string linha;

    todas_areas.push_back(std::to_string(ultimo_id) + " " + std::to_string(total_areas));

    std::cout << "\n=== Áreas Disponíveis ===\n";

    // Listar e validar áreas disponíveis
    while (std::getline(arquivoEntrada, linha)) {
        std::stringstream ss(linha);
        int id_area;
        std::string status_completo;

        ss >> id_area;
        std::getline(ss, status_completo, '+');

        if (status_completo.find("Disponível") != std::string::npos) {
            areas_disponiveis.push_back(id_area);
            std::cout << "ID: " << id_area << "\n";
        }

        todas_areas.push_back(linha);
    }
    arquivoEntrada.close();

    if (areas_disponiveis.empty()) {
        std::cout << "Não há áreas disponíveis para plantio.\n";
        return;
    }

    int id_area;
    std::cout << "\nDigite o ID da área para plantio: ";
    std::cin >> id_area;

    auto it = std::find(areas_disponiveis.begin(), areas_disponiveis.end(), id_area);
    if (it == areas_disponiveis.end()) {
        std::cout << "Área inválida ou não disponível.\n";
        return;
    }

    // Atualizar status da área
    for (size_t i = 1; i < todas_areas.size(); ++i) {
        std::stringstream ss(todas_areas[i]);
        int id_lido;
        std::string resto;

        ss >> id_lido;
        std::getline(ss, resto);

        if (id_lido == id_area) {
            // Replace first status with "Em uso"
            size_t pos_primeiro_mais = resto.find('+');
            if (pos_primeiro_mais != std::string::npos) {
                todas_areas[i] = std::to_string(id_lido) + " Em uso" + resto.substr(pos_primeiro_mais);
            }
            break;
        }
    }

    // Reescrever arquivo
    std::ofstream arquivoSaida("AreaPlantio.txt", std::ios::trunc);
    if (!arquivoSaida) {
        throw std::runtime_error("Erro ao abrir arquivo para escrita");
    }

    for (const auto& linha : todas_areas) {
        arquivoSaida << linha << "\n";
    }
    arquivoSaida.close();

    std::cout << "Área " << id_area << " registrada para plantio.\n";
}


void Vendedor::liberarArea() {
    std::ifstream arquivoEntrada("AreaPlantio.txt");
    if (!arquivoEntrada) {
        throw std::runtime_error("Erro ao abrir o arquivo AreaPlantio.txt");
    }

    int ultimo_id, total_areas;
    arquivoEntrada >> ultimo_id >> total_areas;
    arquivoEntrada.ignore();

    std::vector<std::string> todas_areas;
    std::vector<int> areas_em_uso;
    std::string linha;

    todas_areas.push_back(std::to_string(ultimo_id) + " " + std::to_string(total_areas));

    std::cout << "\n=== Áreas em Uso ===\n";

    // Listar e validar áreas em uso
    while (std::getline(arquivoEntrada, linha)) {
        std::stringstream ss(linha);
        int id_area;
        std::string status_completo;

        ss >> id_area;
        std::getline(ss, status_completo, '+');

        // Verificar se não está disponível
        if (status_completo.find("Disponível") == std::string::npos) {
            areas_em_uso.push_back(id_area);
            std::cout << "ID: " << id_area << " - Status: " << status_completo << "\n";
        }

        todas_areas.push_back(linha);
    }
    arquivoEntrada.close();

    if (areas_em_uso.empty()) {
        std::cout << "Não há áreas em uso para liberar.\n";
        return;
    }

    int id_area;
    std::cout << "\nDigite o ID da área para liberar: ";
    std::cin >> id_area;

    // Validar área selecionada
    auto it = std::find(areas_em_uso.begin(), areas_em_uso.end(), id_area);
    if (it == areas_em_uso.end()) {
        std::cout << "Área inválida ou já disponível.\n";
        return;
    }

    // Atualizar status da área (pulando a primeira linha)
    for (size_t i = 1; i < todas_areas.size(); ++i) {
        std::stringstream ss(todas_areas[i]);
        int id_lido;
        std::string resto;

        ss >> id_lido;
        std::getline(ss, resto);

        if (id_lido == id_area) {
            // Reescreve o status "Disponível"
            size_t pos_primeiro_mais = resto.find('+');
            if (pos_primeiro_mais != std::string::npos) {
                todas_areas[i] = std::to_string(id_lido) + " Disponível" + resto.substr(pos_primeiro_mais);
            }
            break;
        }
    }

    // Reescrever arquivo
    std::ofstream arquivoSaida("AreaPlantio.txt", std::ios::trunc);
    if (!arquivoSaida) {
        throw std::runtime_error("Erro ao abrir arquivo para escrita");
    }

    for (const auto& linha : todas_areas) {
        arquivoSaida << linha << "\n";
    }
    arquivoSaida.close();

     std::cout << "Área " << id_area << " liberada com sucesso.\n";
}

void Vendedor::buscar_lotes_dessa_semente(int id_semente_busca) {
    std::ifstream arquivoLotes("Lotes.txt");
    if (!arquivoLotes)
        throw std::ios_base::failure("Erro ao abrir arquivo Lotes.txt");

    int quant_lotes;
    arquivoLotes >> quant_lotes; 
    arquivoLotes.ignore(); 
    arquivoLotes >> quant_lotes; 

    int id_lote;
    int id_semente_lido;
    std::string linha;

    int idSementeAssociada,id;
    float quantidadeDisponivel,precoEstimado;
    std::string statusDisponibilidade,nomeCientifico,geneIntroduzido,metodoProducao,dataProducao,paisOrigem;

    for (int i = 0; i < quant_lotes; i++) {
        arquivoLotes >> id_semente_lido;
        if(arquivoLotes.fail())
            throw std::ios_base::failure("Erro ao ler ID da semente associada ao lote!");

        if (id_semente_lido == id_semente_busca) {
            arquivoLotes.ignore();
            arquivoLotes >> id_lote;
            arquivoLotes.ignore();
        std::getline(arquivoLotes,statusDisponibilidade,'+');
        std::getline(arquivoLotes,nomeCientifico,'+');
        std::getline(arquivoLotes,geneIntroduzido,'+');
        std::getline(arquivoLotes,metodoProducao,'+');
        std::getline(arquivoLotes,dataProducao,'+');
        std::getline(arquivoLotes,paisOrigem,'+');
        arquivoLotes>>quantidadeDisponivel;                  arquivoLotes.ignore();
        arquivoLotes>>precoEstimado;
        if(arquivoLotes.fail())
            throw std::ios_base::failure("Erro ao ler ID da semente associada ao lote!");


        //imprimir
        std::cout<<"Dados do lote:\nID :"<<id_lote<<"\nNome cientifico: "<<nomeCientifico<<"\nGene introduzido: "<<
        geneIntroduzido<<"\nMetodo de producao: "<<metodoProducao<<"\nData de producao: "<<dataProducao<<"\nPais de origem: "<<
        paisOrigem<<"\nQuantidade disponivel no lote: "<<quantidadeDisponivel<<" kg\nPreco estimado: RS"<<precoEstimado<<"/kg de semente\n\n\n\n";
        }  
        std::getline(arquivoLotes, linha);

    }
    arquivoLotes.close();
}


void Vendedor::compatibilidade_semente() {
    int id_buscado;

    std::cout<<"Deseja verificar a compatibilidade de qual Área de plantio? ID: ";
    std::cin>>id_buscado;
    while(id_buscado<=0){
        std::cout<<"Entrada de ID inválida. Digite novamente o id da Area de plantio: ";
        std::cin>>id_buscado;
    }

    //----buscando dados sobre a Area de plantio--//
    std::ifstream arquivoArea("AreaPlantio.txt");
    if (!arquivoArea) {
        throw std::ios_base::failure("Erro ao abrir arquivo AreaPlantio.txt");
    }

    int id;
    std::string solo,clima;
    std::string buffer;

    while(std::getline(arquivoArea,buffer)){

        //guardadno clima e solo da area de plantio

        arquivoArea>>id;        arquivoArea.ignore();
        std::getline(arquivoArea, buffer, '+');
        std::getline(arquivoArea, buffer, '+');
        std::getline(arquivoArea, buffer, '+');
        std::getline(arquivoArea, buffer, '+');
        std::getline(arquivoArea, solo, '+');
        std::getline(arquivoArea, clima, '+');
    }
    arquivoArea.close();

    std::ifstream arquivoSementes("Sementes.txt");
    if (!arquivoSementes) {
        throw std::ios_base::failure("Erro ao abrir arquivo Sementes.txt");
    }
    int quant_sementes;
    arquivoSementes >> quant_sementes; 
    arquivoSementes.ignore();
    arquivoSementes >> quant_sementes;

    int id_semente;
    std::string solo_semente;
    std::string clima_semente;

    for (int i = 0; i < quant_sementes; i++) {
        arquivoSementes >> id_semente;
        if(arquivoSementes.fail())
            throw std::ios_base:: failure("Erro ao ler ID da semente.\n");
        arquivoSementes.ignore();
        std::getline(arquivoSementes, solo_semente, '+');
        std::getline(arquivoSementes, clima_semente, '+');

        if (solo_semente == solo && clima_semente == clima) {
            buscar_lotes_dessa_semente(id_semente);
        }   
        std::getline(arquivoSementes, buffer);
    }

    arquivoSementes.close();
}

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

void Vendedor::consumirSementes(int id_lote,int quantidadeConsumida){

    int id_sementeAssociada;
    int quantidade_disponivel;
    double preco_estimado;
    std::string statusDisponibilidade, nome_cientifico, geneIntroduzido, metodo_producao, data_producao, pais_origem;
   
    std::fstream arquivoLotes ("Lotes.txt");   //o arquivo sera lido e escrito  
    if(!arquivoLotes)
        std::cerr<<"Erro ao abrir o arquivo Lotes.txt\n";
    int contador_lotes;  //quantos lotes possui o arquivo
    int controleDeID;    //usado nessa funcao apenas pra ser reescrito no arquivo
    arquivoLotes>>controleDeID;
    arquivoLotes>>contador_lotes;
    arquivoLotes.ignore();
    
    std::string *linha=new std::string[contador_lotes];   //aloca as linhas que nao serao alteradas
      // Lê todas as linhas exceto a que será modificada
    for(int i=0;i<contador_lotes;i++){
        if(i+1 == id_lote){
            // Lê o lote que será consumido
            arquivoLotes>>id_sementeAssociada;                       arquivoLotes.ignore();
            arquivoLotes>>id_lote;                                   arquivoLotes.ignore();                  
            getline(arquivoLotes, statusDisponibilidade, '+');
            getline(arquivoLotes, nome_cientifico, '+');     
            getline(arquivoLotes, geneIntroduzido, '+');
            getline(arquivoLotes, metodo_producao, '+');                                        
            getline(arquivoLotes, data_producao, '+');
            getline(arquivoLotes, pais_origem, '+');                                        
            arquivoLotes>> quantidade_disponivel;                      arquivoLotes.ignore(); 
            arquivoLotes>> preco_estimado;                            arquivoLotes.ignore();
        } else {
            std::getline(arquivoLotes, linha[i]);
        }
    }             
    
    //alterando o saldo de sementes: 
 
    if(quantidade_disponivel-quantidadeConsumida<0){
        std::cout<<"Quantidade indisponivel!\n";
        delete[] linha;
        return;
    } 
    else if(quantidade_disponivel-quantidadeConsumida==0){
        quantidade_disponivel=0;
        std::cout<<"Quantidade disponível!\n";
        statusDisponibilidade="Vendido";
    }
    else{
        quantidade_disponivel-=quantidadeConsumida;
    }
    arquivoLotes.close();
    //----------escrevendo o arquivo atualizado------//
    std::ofstream arquivoLotesON("Lotes.txt");
    arquivoLotesON<<controleDeID<<" "<<contador_lotes<<std::endl;
    for(int i=0;i<contador_lotes;i++){
        if(i+1==id_lote){
            arquivoLotesON<<id_sementeAssociada<<"+"<<id_lote<<"+"<<statusDisponibilidade<<"+"<<nome_cientifico
            <<"+"<<geneIntroduzido<<"+"<<metodo_producao<<"+"<<data_producao<<"+"<<pais_origem<<"+"<<
            quantidade_disponivel<<"+"<<preco_estimado<<std::endl;
        }
        else
            arquivoLotesON<<linha[i]<<std::endl;  //escrevendo linhas nao alteradas
    }
    delete[] linha;
    arquivoLotesON.close();
}

void Vendedor::registrarNegociacao() {
    Negociacao novaNegociacao;
    int lote_id, area_id;
    std::string data;
    float quantidade_semente, desconto;

    // Melhorias na entrada de dados
    std::cout << "Insira os detalhes da Negociação:\n";

    while (true) {
        std::cout << "ID do Lote: ";
        if (std::cin >> lote_id && lote_id > 0) break;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cerr << "Entrada inválida. Por favor, insira um valor numérico válido.\n";
    }
    std::cin.ignore();

    while (true) {
        std::cout << "ID da Área: ";
        if (std::cin >> area_id && area_id > 0) break;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cerr << "Entrada inválida. Por favor, insira um valor numérico válido.\n";
    }
    std::cin.ignore();

    while (true) {
        std::cout << "Quantidade de Sementes Negociadas(kg): ";
        if (std::cin >> quantidade_semente && quantidade_semente > 0) break;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cerr << "Entrada inválida. Insira uma quantidade positiva.\n";
    }
    std::cin.ignore();

    std::cout << "Data da Negociação (DD/MM/AAAA, deixe em branco para data atual): ";
    std::getline(std::cin, data);
    if (data.empty()) {
        data = getCurrentDate();
    } else if (!validarData(data)) {
        throw std::invalid_argument("Data inválida.");
    }

    while (true) {
        std::cout << "Desconto (%): ";
        if (std::cin >> desconto && desconto >= 0) break;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cerr << "Entrada inválida. Insira um valor de desconto válido (>= 0).\n";
    }
    std::cin.ignore();

    // Calcular valor negociado
    Lote lote(lote_id);
    float valor_estimado = lote.getPrecoEstimado();
    if (valor_estimado <= 0) {
        throw std::runtime_error("Erro: preço estimado inválido para o lote informado.");
    }

    // Definição do ID automaticamente em salvarNegociacao()
    novaNegociacao.set_id_lote(lote_id);
    novaNegociacao.set_id_area(area_id);
    novaNegociacao.set_quantidade_semente_negociada(quantidade_semente);
    novaNegociacao.set_data_negociacao(data);
    novaNegociacao.set_desconto(desconto);
    novaNegociacao.set_valor_negociado((valor_estimado * quantidade_semente) * (1 - desconto / 100));
    novaNegociacao.set_status("Pendente");

    // Registra negociação
    salvarNegociacao(novaNegociacao);
}

void Vendedor::salvarNegociacao(Negociacao& neg) {
    int cont_id, cont_registros;
    try {
        std::fstream arquivo("Negociacao.txt", std::ios::in | std::ios::out);
        if (!arquivo.is_open()) {
            throw std::ios_base::failure("Erro ao abrir o arquivo para registro.");
        }

        // Le os contadores
        arquivo >> cont_id >> cont_registros;
        cont_id++;
        cont_registros++;

        arquivo.seekp(0, std::ios::end);
        
        // Escreve os detalhes da negociação
        arquivo << cont_id << " " 
                << neg.get_id_lote() << "+"
                << neg.get_id_area() << "+"
                << neg.get_status() << "+"
                << neg.get_data_negociacao() << "+"
                << std::fixed << std::setprecision(2) << neg.get_valor_negociado() << "+"
                << neg.get_quantidade_semente_negociada() << "\n";

        // Atualiza contadores
        arquivo.seekp(0, std::ios::beg);
        arquivo << cont_id << " " << cont_registros << std::endl;

        //Consome as sementes do lote
        consumirSementes(neg.get_id_lote(), neg.get_quantidade_semente_negociada());

        std::cout << "Negociação registrada com sucesso! ID: " << cont_id << std::endl;
        arquivo.close();

    } catch (const std::ios_base::failure& e) {
        std::cerr << "Exceção de I/O: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Exceção geral: " << e.what() << std::endl;
    }
}

void Vendedor::finalizarNegociacao() {

    std::ifstream arquivoEntrada("Negociacao.txt");
    if (!arquivoEntrada) {
        throw std::runtime_error("Erro ao abrir o arquivo Negociacao.txt");
    }

    std::vector<std::string> todas_negociacoes;
    std::vector<int> negociacoes_pendentes;
    std::string linha;

    // Lê todo o conteúdo do arquivo
    while (std::getline(arquivoEntrada, linha)) {
        todas_negociacoes.push_back(linha);
    }
    arquivoEntrada.close();

    std::cout << "\n=== Negociações Pendentes ===\n";

    // Listar e validar negociações pendentes
    for (const auto& linha : todas_negociacoes) {
        std::stringstream ss(linha);
        int id_negociacao;
        std::string id_lote, id_area, status, data_negociacao, valor_negociado, quantidade;

        // Extrai os valores da linha
        ss >> id_negociacao;
        ss.ignore(); // Ignora o espaço após o ID
        std::getline(ss, id_lote, '+');
        std::getline(ss, id_area, '+');
        std::getline(ss, status, '+');
        std::getline(ss, data_negociacao, '+');
        std::getline(ss, valor_negociado, '+');
        std::getline(ss, quantidade);

        if (status == "Pendente") {
            negociacoes_pendentes.push_back(id_negociacao);
            std::cout << "ID: " << id_negociacao << "\n";
        }
    }

    if (negociacoes_pendentes.empty()) {
        std::cout << "Não há negociações pendentes.\n";
        return;
    }

    //alterando status no arquivo txt

    int id_buscado = 0;
    std::cout << "Deseja finalizar qual negociacao? ID da negociacao: ";
    std::cin >> id_buscado;
    while (id_buscado <= 0) {
        std::cout << "ID inválido. Digite novamente o ID da negociacao: ";
        std::cin >> id_buscado;
    }
     // Verifica se o ID inserido está na lista de pendentes
    auto it = std::find(negociacoes_pendentes.begin(), negociacoes_pendentes.end(), id_buscado);
    if (it == negociacoes_pendentes.end()) {
        std::cout << "Negociação inválida ou já finalizada.\n";
        return;
    }

    std::fstream arquivoNeg("Negociacao.txt");
    if (!arquivoNeg)
        throw std::runtime_error("Erro na abertura do arquivo Negociacao.txt");

    std::string linhasModificadas;

    // Ler todo o arquivo e modificar a linha desejada
    while (std::getline(arquivoNeg, linha)) {
        std::istringstream iss(linha);
        int id;
        iss >> id;

        if (id == id_buscado && linha.find("Pendente") != std::string::npos) {
            size_t pos = linha.find("Pendente");
            linha.replace(pos, 8, "Finalizada");
        }
        linhasModificadas += linha + "\n";
    }

    // Reabrir o arquivo para escrita
    arquivoNeg.close();
    arquivoNeg.open("Negociacao.txt", std::ios::out | std::ios::trunc);
    if (!arquivoNeg)
        throw std::runtime_error("Erro na abertura do arquivo Negociacao.txt");

    arquivoNeg << linhasModificadas;
    arquivoNeg.close();

    std::cout <<"Negociacao finalizada com sucesso!\n" ;

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
        std::cout << "Quantidade de Sementes Negociadas: " << quantidade_semente_negociada << "kgs\n";
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
void Vendedor::gerarRelatorio(){

        std::cout<<"Gerando relatorio:\n";
        //montando dados das areas de plantio
        
        std::ifstream arquivoArea("AreaPlantio.txt");
        if (!arquivoArea) 
            throw std::runtime_error("Erro ao abrir arquivo Negociacao.txt para escrita.");
        
        int inteiro,contArea,contNeg;
        float decimal;
        std::string texto;

        arquivoArea>>contArea>>contArea;         arquivoArea.ignore();

        std::ofstream relatorioGerado("RelatorioVendedor.txt");
        if(!relatorioGerado)
            throw std::runtime_error("Erro ao gerar/abrir arquivo RelatorioVendedor.txt\n");

        for (int i=0;i<contArea;i++){
            if(arquivoArea.eof())
                break;
            AreaPlantio area;
            arquivoArea>>inteiro;                      area.set_id_area(inteiro);     arquivoArea.ignore();
            std::getline(arquivoArea,texto,'+');       area.set_status(texto);
            std::getline(arquivoArea,texto,'+');       area.set_nome_proprietario(texto);
            std::getline(arquivoArea,texto,'+');       area.set_cnpj_proprietario(texto);
            std::getline(arquivoArea,texto,'+');       area.set_localizacao(texto);
            std::getline(arquivoArea,texto,'+');       area.set_tipo_solo(texto);
            std::getline(arquivoArea,texto,'+');       area.set_clima(texto);
            arquivoArea>>decimal;                      area.set_tamanho(decimal);     

            relatorioGerado<<"Área de plantio de ID: "<<area.get_id_area()<<"\nStatus da propriedade: "<<area.get_status()<<
                            "\nNome do proprietário: "<<area.get_nome_proprietario()<<"\nCNPJ do proprietário: "<<area.get_cnpj_proprietario()<<
                            "\nLocalização: "<<area.get_localizacao()<<"\nSolo da área: "<<area.get_tipo_solo()<<"\nClima da região: "<<
                            area.get_clima()<<"\nTamanho da área: "<<area.get_tamanho()<<" hec\n\n\n";
        }
        arquivoArea.close();

        std::ifstream arquivoNeg("Negociacao.txt");
        if (!arquivoNeg) 
            throw std::runtime_error("Erro ao abrir arquivo Negociacao.txt para escrita.\n");
        arquivoNeg>>contNeg>>contNeg;             


        for(int i=0;i<contNeg;i++){
            Negociacao neg;
            arquivoNeg>>inteiro;                       neg.set_id_negociacao(inteiro);                      arquivoNeg.ignore();
            arquivoNeg>>inteiro;                       neg.set_id_lote(inteiro);                            arquivoNeg.ignore();
            arquivoNeg>>inteiro;                       neg.set_id_area(inteiro);                            arquivoNeg.ignore();
            std::getline(arquivoNeg,texto,'+');        neg.set_status(texto);               
            std::getline(arquivoNeg,texto,'+');        neg.set_data_negociacao(texto);      
            arquivoNeg>>decimal;                       neg.set_valor_negociado(decimal);                    arquivoNeg.ignore();
            arquivoNeg>>decimal;                       neg.set_quantidade_semente_negociada(decimal);       

            relatorioGerado<<"Negociação de ID: "<<neg.get_id_negociacao()<<"\nID do lote da negociação: "<<neg.get_id_lote()<<
                        "\nID da Área de plantio: "<<neg.get_id_area()<<"\nStatus da negociação: "<<neg.get_status()<<"\nData da negociação: "<<
                        neg.get_data_negociacao()<<"\nValor negociado: RS"<<neg.get_valor_negociado()<<"\nQuantidade de sementes negociada: "<<
                        neg.get_quantidade_semente_negociada()<<" KG\n\n\n";
    
        }
        arquivoNeg.close();
        relatorioGerado.close();
        std::cout<<"Relatorio gerado com sucesso!\n";
}

    //_____________________________________________________________________________________________________

void Vendedor::atualizarPrecoDaSemente(){
    std::cout<<"Dejesa atualizar o preco de qual lote de sementes? ID do lote: ";
    int id_lote=0;
    std::cin>>id_lote;

    while(id_lote<=0){
        std::cout<<"ID inválido. Digite novamente o ID do lote: ";
        std::cin>>id_lote;
    }

    std::fstream arquivoLotes("Lotes.txt");
    if(!arquivoLotes)
        throw std::runtime_error("Erro ao abrir arquivo Lotes.txt");
    
    int cont_registros,id;
    std::string linha;
    float preco;

    arquivoLotes>>cont_registros>>cont_registros;       arquivoLotes.ignore();  //ignorando controle de id
    for(int i=0;i<cont_registros;i++){
        arquivoLotes>>id;
        if(id_lote==id){
            for(int i=0;i<9;i++)  //9 parametros entre id e preco
                std::getline(arquivoLotes,linha,'+');
            int pos=arquivoLotes.tellg();
            arquivoLotes>>preco;
            std::cout<<"O preco por kg atual do lote é de RS "<<preco<<"\nInsira o novo valor: ";
            std::cin>>preco;
            if(preco<=0){
                throw std::invalid_argument("Nao é possivel por um preco menor ou igual a 0!\n");
            }
            arquivoLotes.seekp(pos);
            arquivoLotes<<std::fixed<<std::setprecision(2)<<preco<<std::endl;
            break;
        }
    }
    arquivoLotes.close();
    if(arquivoLotes.fail()){
        throw std::runtime_error("Erro ao atualizar preco!\n");
    std::cout<<"Preco atualizado com sucesso!\n";
    }

}

void Vendedor::acessarInterface() {

    int opcao_selecionada;

    while (true) {
        std::cout << "|-----------------------MENU DO VENDEDOR------------------------|\n";
        std::cout << "|01|- Registrar uma nova área\n";
        std::cout << "|02|- Listar áreas registradas\n";
        std::cout << "|03|- Liberar uma área\n";
        std::cout << "|04|- Excluir uma área\n";
        std::cout << "|05|- Registrar plantio\n";
        std::cout << "|06|- Registrar uma nova negociação\n";
        std::cout << "|07|- Listar negociações registradas\n";
        std::cout << "|08|- Finalizar uma negociação\n";
        std::cout << "|09|- Excluir uma negociação\n";
        std::cout << "|10|- Atualizar preço da semente\n";
        std::cout << "|11|- Verificar compatibilidade\n";
        std::cout << "|12|- Visualizar Relatórios\n";
        std::cout << "|13|- Sair\n";
        std::cout << "|---------------------------------------------------------------|\n";
        std::cout << "|Escolha uma opção: ";
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
                atualizarPrecoDaSemente();
                break;
            case 11:
                compatibilidade_semente();
                break;  // Corrigido para evitar queda em outros cases
            case 12:
                gerarRelatorio();
                break;  // Corrigido para evitar queda em outros cases
            case 13:
                std::cout << "Saindo do menu do vendedor.\n";
                return;  // Sai da função corretamente (eu acho, tem que testar)
            default:
                std::cout << "Opção inválida, tente novamente.\n";
                break;
        }
    }
}

