#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "Gestor.hpp"
#include "Vendedor.hpp"
#include "Analista.hpp"

void Gestor::cadastrarUsuario() {
    std::string nome, email, tipo, senha;

    // Solicita as informações do usuário
    std::cout << "Insira o nome do usuario: ";
    std::getline(std::cin, nome);
    std::cout << "Insira o email do usuario: ";
    std::getline(std::cin, email);

    // Valida o email
    if (email.find('@') == std::string::npos) {
        std::cerr << "Erro: O email deve conter o caractere '@'!" << std::endl;
        return;
    }

    // Verifica se o email já existe no arquivo
    std::ifstream fin("usuarios.txt");
    if(!fin.is_open()){
        throw std::ios_base::failure("Erro ao abrir o arquivo usuarios.txt");
    }

    std::string linha, emailExistente;
    while (std::getline(fin, linha)) {
        std::getline(fin, linha); // Pula nome
        std::getline(fin, emailExistente); // Lê email
        if (emailExistente == email) {
            std::cerr << "Erro: Este email já está cadastrado!" << std::endl;
            fin.close();
            return;
        }
        std::getline(fin, linha); // Pula tipo de usuário
        std::getline(fin, linha); // Pula senha
    }
    fin.close();

    // Solicita o tipo e senha
    std::cout << "Insira o tipo de usuario: ";
    std::getline(std::cin, tipo);
    std::cout << "Insira a nova senha do usuario: ";
    std::getline(std::cin, senha);

    // Valida a senha
    if (senha.length() < 5) {
        std::cerr << "Erro: A senha deve conter pelo menos 5 caracteres!" << std::endl;
        return;
    }

    // Atualiza ID e grava os dados no arquivo
    int id = ++totalUsuarios;
    std::ofstream fout("usuarios.txt", std::ios::app); // Modo de adição
    if (!fout.is_open()) {
        throw std::ios_base::failure("Erro ao abrir o arquivo usuarios.txt");
    }

    fout << id << std::endl
         << nome << std::endl
         << email << std::endl
         << tipo << std::endl
         << senha << std::endl;
    fout.close();

    std::cout << "Usuario cadastrado com sucesso!" << std::endl;
}

void Gestor::listarUsuarios() {
    std::ifstream fin("usuarios.txt");
    if (!fin.is_open()) {
        throw std::ios_base::failure("Erro ao abrir o arquivo usuarios.txt");
    }

    std::string linha;
    std::cout << "Lista de usuarios cadastrados:" << std::endl;
    while (std::getline(fin, linha)) {
        int id = std::stoi(linha); // Primeiro, lê o ID
        std::getline(fin, linha);
        std::string nome = linha; // Depois, lê o nome
        std::getline(fin, linha);
        std::string tipo = linha; // Depois, lê o tipo
        std::getline(fin, linha);
        std::string senha = linha; // Depois, lê a senha

        // Exibe os dados de forma organizada
        std::cout << "ID: " << id 
                  << ", Nome: " << nome 
                  << ", Tipo: " << tipo     
                  << std::endl;
    }
    fin.close();
}

void Gestor::excluirUsuario() {
    listarUsuarios();

    int idParaExcluir;
    std::cout << std::endl << "Insira o ID do usuario que deseja excluir: ";
    std::cin >> idParaExcluir;
    std::cin.ignore(); // Limpa o buffer para evitar problemas ao ler strings depois

    std::ifstream fin("usuarios.txt");
    if (!fin.is_open()) {
        throw std::ios_base::failure("Erro ao abrir o arquivo usuarios.txt");
    }

    std::vector<std::string> usuariosRestantes;
    std::string linha;
    bool usuarioEncontrado = false;

    // Lê os usuários e armazena aqueles que não devem ser excluídos
    while (std::getline(fin, linha)) {
        std::stringstream ss(linha);
        int idAtual;
        ss >> idAtual;

        // Verifica se este é o ID a ser excluído
        if (idAtual == idParaExcluir) {
            usuarioEncontrado = true;
            // Ignora as próximas 3 linhas (nome, tipo, senha)
            std::getline(fin, linha); // Nome
            std::getline(fin, linha); // Tipo
            std::getline(fin, linha); // Senha
        } else {
            // Mantém os dados do usuário atual
            usuariosRestantes.push_back(std::to_string(idAtual));
            std::getline(fin, linha); usuariosRestantes.push_back(linha); // Nome
            std::getline(fin, linha); usuariosRestantes.push_back(linha); // Tipo
            std::getline(fin, linha); usuariosRestantes.push_back(linha); // Senha
        }
    }
    fin.close();

    if (!usuarioEncontrado) {
        std::cout << "Usuario com ID " << idParaExcluir << " nao encontrado." << std::endl;
        return;
    }

    // Reescreve o arquivo com os usuários restantes
    std::ofstream fout("usuarios.txt");
    if (!fout.is_open()) {
        throw std::ios_base::failure("Erro ao abrir o arquivo usuarios.txt para escrita");
    }

    for (size_t i = 0; i < usuariosRestantes.size(); i++) {
        fout << usuariosRestantes[i] << std::endl;
    }
    fout.close();

    std::cout << "Usuario com ID " << idParaExcluir << " excluido com sucesso." << std::endl;
}

void Gestor::salvarSemente(const Semente& semente) {
    try {
        std::ofstream arquivo("Sementes.txt", std::ios::app);
        if (!arquivo.is_open()) {
            throw std::ios_base::failure("Erro ao abrir o arquivo para registro.");
        }

        // Verifica se algum valor está vazio ou inválido
        if (semente.getId() == 0 || semente.getSoloIdeal().empty() || semente.getClimaIdeal().empty() ||
            semente.getTempoColheita() <= 0 || semente.getIrrigacaoIdeal() <= 0 || 
            semente.getExpectativaResistenciaPraga() < 0 || semente.getExpectativaCrescimento() < 0 ||
            semente.getExpectativaTaxaDeGerminacao() < 0 || semente.getExpectativaTaxaDeSobrevivencia() < 0) {
            throw std::invalid_argument("Nao foi possivel registrar a semente pois um dos valores esta vazio ou invalido.");
        }

        // Caso todos os valores estejam válidos, escreve no arquivo
        arquivo << semente.getId() << "+" << semente.getSoloIdeal() << "+"
                << semente.getClimaIdeal() << "+" << semente.getTempoColheita() << "+"
                << semente.getIrrigacaoIdeal() << "+" << semente.getExpectativaResistenciaPraga() << "+"
                << semente.getExpectativaCrescimento() << "+" << semente.getExpectativaTaxaDeGerminacao() << "+"
                << semente.getExpectativaTaxaDeSobrevivencia() << "+" << semente.getProduzFrutos() << "\n";
                
        std::cout << "Semente registrada com sucesso!" << std::endl;
        arquivo.close();

    } catch (const std::ios_base::failure& e) {
        std::cerr << "Excecao de I/O: " << e.what() << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cerr << "Excecao de argumento invalido: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Excecao geral: " << e.what() << std::endl;
    }
}

void Gestor::registrarSemente() {
        Semente novaSemente;

        std::string clima, solo;
        float tempoColheita, irrigacaoIdeal, expectativaResistencia, expectativaCrescimento;
        bool produzFrutos;
        float expectativaTaxaGerminacao, expectativaTaxaSobrevivencia;

        std::cout << "Insira os detalhes da semente:\n";
        std::cout << "Clima ideal: ";
        std::getline(std::cin, clima);
        std::cout << "Solo ideal: ";
        std::getline(std::cin, solo);
        std::cout << "Tempo de colheita (em dias): ";
        std::cin >> tempoColheita;
        std::cout << "Irrigacao ideal (em mm/dia): ";
        std::cin >> irrigacaoIdeal;
        std::cout << "Expectativa de resistência a pragas (%): ";
        std::cin >> expectativaResistencia;
        std::cout << "Expectativa de crescimento (%): ";
        std::cin >> expectativaCrescimento;
        std::cout << "Expectativa de taxa de germinação (%): ";
        std::cin >> expectativaTaxaGerminacao;
        std::cout << "Expectativa de taxa de sobrevivência (%): ";
        std::cin >> expectativaTaxaSobrevivencia;
        std::cout << "A semente produz frutos (1 - sim, 0 - não): ";
        std::cin >> produzFrutos;

        // Preenche os dados no objeto
        novaSemente.setClimaIdeal(clima);
        novaSemente.setSoloIdeal(solo);
        novaSemente.setTempoColheita(tempoColheita);
        novaSemente.setIrrigacaoIdeal(irrigacaoIdeal);
        novaSemente.setExpectativaResistenciaPraga(expectativaResistencia);
        novaSemente.setExpectativaCrescimento(expectativaCrescimento);
        novaSemente.setExpectativaTaxaDeGerminacao(expectativaTaxaGerminacao);
        novaSemente.setExpectativaTaxaDeSobrevivencia(expectativaTaxaSobrevivencia);
        novaSemente.setProduzFrutos(produzFrutos);

        // Registra a nova semente no contêiner
        sementesRegistradas.push_back(novaSemente);

        salvarSemente(novaSemente);
}

void Gestor::excluirSemente() {
    int idParaExcluir;
    std::cout << "Insira o ID da semente que deseja excluir: ";
    std::cin >> idParaExcluir;
    std::cin.ignore(); // Limpa o buffer de entrada

    std::ifstream arquivoEntrada("Sementes.txt");
    if (!arquivoEntrada.is_open()) {
        throw std::ios_base::failure("Erro ao abrir o arquivo Sementes.txt");
    }

    std::vector<std::string> sementesRestantes;
    std::string linha;
    bool sementeEncontrada = false;

    while (std::getline(arquivoEntrada, linha)) {
        std::stringstream ss(linha);
        int idAtual;
        char separador;
        ss >> idAtual >> separador;

        if (idAtual == idParaExcluir) {
            sementeEncontrada = true;
            continue; // Ignora essa linha (não adiciona ao vetor)
        }
        sementesRestantes.push_back(linha);
    }
    arquivoEntrada.close();

    if (!sementeEncontrada) {
        std::cout << "Semente com ID " << idParaExcluir << " nao encontrada." << std::endl;
        return;
    }

    std::ofstream arquivoSaida("Sementes.txt");
    if (!arquivoSaida.is_open()) {
        throw std::ios_base::failure("Erro ao abrir o arquivo Sementes.txt para escrita");
    }

    for (const auto &semente : sementesRestantes) {
        arquivoSaida << semente << std::endl;
    }
    arquivoSaida.close();

    std::cout << "Semente com ID " << idParaExcluir << " excluida com sucesso." << std::endl;
}

void Gestor::salvarLote(const Lote& lote) {
    try {
        std::ofstream arquivoLotes("Lotes.txt", std::ios::app);
        if (!arquivoLotes.is_open()) {
            throw std::ios_base::failure("Erro ao abrir o arquivo para escrita.");
        }

        arquivoLotes << lote.getIdSementeAssociada() << "+" << lote.getIdLote() << "+" << lote.getStatusDisponibilidade() << "+"
                     << lote.getNomeCientifico() << "+" << lote.getGeneIntroduzido() << "+" << lote.getMetodoProducao() << "+"
                     << lote.getDataProducao() << "+" << lote.getPaisOrigem() << "+" << lote.getQuantidadeDisponivel() << "+" << lote.getPrecoEstimado() << "\n";

        arquivoLotes.close();

        std::ofstream arquivoLotesWrite("Lotes.txt", std::ios::in | std::ios::out);
        if (!arquivoLotesWrite.is_open()) {
            throw std::ios_base::failure("Erro ao abrir o arquivo para leitura e escrita.");
        }

        arquivoLotesWrite.seekp(0, std::ios::beg);
        arquivoLotesWrite << lote.getIdLote() << std::endl;
        arquivoLotesWrite.close();

        std::cout << "Lote registrado com sucesso!\n";
    } catch (const std::ios_base::failure& e) {
        std::cerr << "Excecao de I/O: " << e.what() << "\n";
    } catch (const std::exception& e) {
        std::cerr << "Excecao: " << e.what() << "\n";
    }
}

void Gestor::registrarLote() {
        Lote novoLote;

        int idSementeAssociada;
        std::string statusDisponibilidade, nomeCientifico, geneIntroduzido, metodoProducao, dataProducao, paisOrigem;
        float quantidadeDisponivel, precoEstimado;

        std::cout << "ID da semente associada: "; 
        std::cin >> idSementeAssociada;
        std::cout << "Status de disponibilidade (Estoque/Vendido/Plantado): "; 
        std::getline(std::cin, statusDisponibilidade);
        std::cout << "Nome cientifico: "; 
        std::getline(std::cin, nomeCientifico);
        std::cout << "Gene introduzido: "; 
        std::getline(std::cin, geneIntroduzido);
        std::cout << "Metodo de producao: "; 
        std::getline(std::cin, metodoProducao);
        std::cout << "Data de producao (DD/MM/AA): "; 
        std::getline(std::cin, dataProducao);
        std::cout << "Pais de origem: "; 
        std::getline(std::cin, paisOrigem);
        std::cout << "Quantidade disponivel (kg): "; 
        std::cin >> quantidadeDisponivel;
        std::cout << "Preco estimado: "; 
        std::cin >> precoEstimado;

        novoLote.setIdSementeAssociada(idSementeAssociada);
        novoLote.setStatusDisponibilidade(statusDisponibilidade);
        novoLote.setNomeCientifico(nomeCientifico);
        novoLote.setGeneIntroduzido(geneIntroduzido);
        novoLote.setMetodoProducao(metodoProducao);
        novoLote.setDataProducao(dataProducao);
        novoLote.setPaisOrigem(paisOrigem);
        novoLote.setQuantidadeDisponivel(quantidadeDisponivel);
        novoLote.setPrecoEstimado(precoEstimado);

        salvarLote(novoLote);
}

