#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <stdexcept>
#include <limits>
#include "Gestor.hpp"
#include "Vendedor.hpp"
#include "Analista.hpp"

Gestor::Gestor(){};
Gestor::~Gestor(){};

void Gestor::cadastrarUsuario() {
    std::string nome, email, tipo, senha;

    // Solicita as informações do usuário
    std::cout << "Insira o nome do usuario: ";
    std::cin.ignore();
    std::getline(std::cin, nome);

    while(true){
        std::cout << "Insira o email do usuario: ";
        std::getline(std::cin, email);

    // Valida o email
        if (email.find('@') == std::string::npos) {
            std::cerr << "Erro: O email deve conter o caractere '@'!" << std::endl;
        } else break;
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

    while(true){
        std::cout << "Insira a nova senha do usuario: ";
        std::getline(std::cin, senha);

        // Valida a senha
        if (senha.length() < 5) {
            std::cerr << "Erro: A senha deve conter pelo menos 5 caracteres!" << std::endl;
        } else break;
    }

    // Atualiza ID e grava os dados no arquivo
    int id = ++totalUsuarios;
    std::ofstream fout("usuarios.txt", std::ios::app); // Modo de adição
    if (!fout.is_open()) {
        throw std::ios_base::failure("Erro ao abrir o arquivo usuarios.txt");
    }

    fout << nome << std::endl
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
        std::string nome = linha; // Lê o nome
        std:: getline(fin, linha);
        std::string email=linha;  //Depois, lê o email
        std::getline(fin, linha);
        std::string tipo = linha; // Depois, lê o tipo
        std::getline(fin, linha); //lê a senha

        // Exibe os dados de forma organizada
        std::cout << " Nome: " << nome 
                  << ", Tipo: " << tipo 
                  << ", Email: " << email << std::endl;
    }
    fin.close();
}

void Gestor::excluirUsuario() {
    listarUsuarios();

std::string emailParaExcluir;
    std::cout << "\nInsira o email do usuário que deseja excluir: ";
    std::cin >> emailParaExcluir;
    std::cin.ignore(); // Limpa o buffer para evitar problemas ao ler strings depois.

    std::ifstream fin("usuarios.txt");
    if (!fin.is_open()) {
        throw std::ios_base::failure("Erro ao abrir o arquivo usuarios.txt");
    }

    std::vector<std::string> usuariosRestantes;
    std::string linha;
    bool usuarioEncontrado = false;

    // Lê os usuários e armazena aqueles que não devem ser excluídos
    while (std::getline(fin, linha)) {
        std::string nome = linha; // Lê o nome

        if (!std::getline(fin, linha)) break;
        std::string email = linha; // Lê o email

        if (!std::getline(fin, linha)) break;
        std::string tipo = linha; // Lê o tipo

        if (!std::getline(fin, linha)) break;
        std::string senha = linha; // Lê a senha

        // Verifica se este é o email a ser excluído
        if (email == emailParaExcluir) {
            usuarioEncontrado = true;
            // Usuário encontrado, então não o adiciona à lista de usuários restantes
            continue;
        }

        // Mantém os dados do usuário atual
        usuariosRestantes.push_back(nome);
        usuariosRestantes.push_back(email);
        usuariosRestantes.push_back(tipo);
        usuariosRestantes.push_back(senha);
    }

    fin.close();

    if (!usuarioEncontrado) {
        std::cerr << "Erro: Usuário com email " << emailParaExcluir << " não encontrado.\n";
        return;
    }

    char confirmacao;
    std::cout << "Tem certeza que deseja excluir o usuario " << emailParaExcluir << "? (S/N): ";
    std::cin >> confirmacao;

    if (toupper(confirmacao) != 'S') {
        std::cout << "Operação cancelada.\n";
        return;
    }

    // Salva os usuários restantes de volta no arquivo
    std::ofstream fout("usuarios.txt", std::ios::trunc); // Sobrescreve o arquivo
    if (!fout.is_open()) {
        throw std::ios_base::failure("Erro ao abrir o arquivo usuarios.txt para escrita");
    }

    for (const auto& usuario : usuariosRestantes) {
        fout << usuario << "\n";
    }

    fout.close();

    std::cout << "Usuário com email " << emailParaExcluir << " excluído com sucesso.\n";

}

void Gestor::salvarSemente(Semente& semente) {

    int cont_id=0;
    int cont_registros=0;
    try {
        std::fstream arquivo("Sementes.txt");
        if (!arquivo.is_open()) {
            throw std::ios_base::failure("Erro ao abrir o arquivo para registro.");
        }

        //lendo contadores do arquivo
         if (arquivo.peek() != std::ifstream::traits_type::eof()) {
            arquivo >> cont_id >> cont_registros;
        }
        cont_id++;
        cont_registros++;

        // Verifica se algum valor está vazio ou inválido
        if (semente.get_id_tipo() == 0 || semente.get_solo_ideal().empty() || semente.get_clima_ideal().empty() ||
            semente.get_tempo_colheita() < 0 || semente.get_irrigacao_ideal() <= 0 || 
            semente.get_expectativaIncidenciaPragasDoencas() < 0 || semente.get_expectativaCrescimento() < 0 ||
            semente.get_expectativaTaxaDeGerminacao() < 0 || semente.get_expectativaTaxaDeSobrevivencia() < 0) {
            throw std::invalid_argument("Nao foi possivel registrar a semente pois um dos valores esta vazio ou invalido.");
        }

        arquivo.seekp(0,std::ios::end);
        // Caso todos os valores estejam válidos, escreve no arquivo
        arquivo <<"\n"<< semente.get_id_tipo() << "+" << semente.get_solo_ideal() << "+"
                << semente.get_clima_ideal() << "+"
                << semente.get_expectativaIncidenciaPragasDoencas()<<"+"<<semente.get_irrigacao_ideal()  << "+"
                << semente.get_expectativaCrescimento() << "+" << semente.get_expectativaTaxaDeGerminacao() << "+"
                << semente.get_expectativaTaxaDeSobrevivencia() << "+" << semente.get_produz_frutos() <<"+"
                << semente.get_tempo_colheita();

        //atualizando contador de id e de sementes registradas
        arquivo.seekg(0,std::ios::beg);        //leva o apontador até a posicao do contador do arquivo
        arquivo<<cont_id <<" "<<cont_registros<<std::endl;                    //atualiza o contador

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
    float tempoColheita = 0, irrigacaoIdeal = 0, expectativaIncidenciaPragasDoencas = 0, expectativaCrescimento = 0;
    bool produzFrutos = false;
    float expectativaTaxaGerminacao = 0, expectativaTaxaSobrevivencia = 0;
    int id = 0;

    std::string clima, solo;

    // Lê o ID da semente a partir do arquivo
    std::ifstream arquivoSementes("Sementes.txt");
    if (!arquivoSementes.is_open()) {
        throw std::ios_base::failure("Erro ao abrir o arquivo Sementes.txt para leitura");
    }
    arquivoSementes >> id;  // Lê o ID atual de sementes e incrementa
    id++;
    arquivoSementes.close();

    // Coleta informações da semente
    std::cout << "Insira os detalhes da semente:\n";
    
    // Menu para selecionar clima
    std::cout << "Escolha o clima ideal da semente:\n";
    std::cout << "1. Tropical\n";
    std::cout << "2. Temperado\n";
    std::cout << "3. Equatorial\n";
    std::cout << "4. Semiarido\n";
    std::cout << "5. Litoraneo\n";
    std::cout << "Digite o número correspondente ao clima: ";
    int opcaoClima;
    std::cin >> opcaoClima;
    std::cin.ignore();  // Limpa o buffer de entrada
    switch (opcaoClima) {
        case 1:
            clima = "Tropical";
            break;
        case 2:
            clima = "Temperado";
            break;
        case 3:
            clima = "Equatorial";
            break;
        case 4:
            clima="Semiarido";
            break;
        case 5:
            clima="Litoraneo";
            break;
        default:
            throw std::invalid_argument("Opção de clima inválida.");
    }

    // Menu para selecionar solo
    std::cout << "Escolha o tipo de solo ideal da semente:\n";
    std::cout << "1. Arenoso\n";
    std::cout << "2. Argiloso\n";
    std::cout << "3. Franco\n";
    std::cout << "4. Siltoso\n";
    std::cout << "Digite o número correspondente ao solo: ";
    int opcaoSolo;
    std::cin >> opcaoSolo;
    std::cin.ignore();  // Limpa o buffer de entrada
    switch (opcaoSolo) {
        case 1:
            solo = "Arenoso";
            break;
        case 2:
            solo = "Argiloso";
            break;
        case 3:
            solo = "Franco";
            break;
        case 4:
            solo="Siltoso";
            break;
        default:
            throw std::invalid_argument("Opção de solo inválida.");
    }

    // Coleta de outros dados
    std::cout << "Irrigacao ideal (em mm/dia): ";
    std::cin >> irrigacaoIdeal;

    std::cout << "Expectativa de resistência a pragas (%): ";
    std::cin >> expectativaIncidenciaPragasDoencas;

    std::cout << "Expectativa de crescimento (%): ";
    std::cin >> expectativaCrescimento;

    std::cout << "Expectativa de taxa de germinação (%): ";
    std::cin >> expectativaTaxaGerminacao;

    std::cout << "Expectativa de taxa de sobrevivência (%): ";
    std::cin >> expectativaTaxaSobrevivencia;

    // Pergunta sobre produção de frutos
    char resp;
    std::cin.ignore();  // Limpar o buffer de entrada após os floats
    std::cout << "Produz frutos? (S/N): ";
    std::cin >> resp;

    if (resp == 's' || resp == 'S') {
        novaSemente.set_produz_frutos(true);

        // Pergunta sobre o tempo de colheita
        std::cout << "Tempo de colheita (meses): ";
        std::cin >> tempoColheita;

        // Validando a entrada de tempo de colheita
        if (std::cin.fail()) {
            throw std::invalid_argument("Entrada inválida para o tempo de colheita.");
        }
        novaSemente.set_tempo_colheita(tempoColheita);
    } else if (resp == 'n' || resp == 'N') {
        novaSemente.set_produz_frutos(false);
        novaSemente.set_tempo_colheita(0);  // Semente não produz frutos, então o tempo de colheita é 0
    } else {
        throw std::invalid_argument("Resposta inválida para 'Produz frutos?'");
    }

    // Setando os outros atributos da nova semente
    novaSemente.set_id_tipo(id);
    novaSemente.set_clima_ideal(clima);
    novaSemente.set_solo_ideal(solo);
    novaSemente.set_irrigacao_ideal(irrigacaoIdeal);
    novaSemente.set_expectativaIncidenciaPragasDoencas(expectativaIncidenciaPragasDoencas);
    novaSemente.set_expectativaCrescimento(expectativaCrescimento);
    novaSemente.set_expectativaTaxaDeGerminacao(expectativaTaxaGerminacao);
    novaSemente.set_expectativaTaxaDeSobrevivencia(expectativaTaxaSobrevivencia);

    // Registrando a nova semente no contêiner
    std::vector<Semente> sementesRegistradas;
    sementesRegistradas.push_back(novaSemente);

    // Salvando a semente no arquivo (ou qualquer outro local de armazenamento)
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

    int cont_id, cont_registros;
    arquivoEntrada>>cont_id>>cont_registros;

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

    cont_registros--;   //diminui um no contador de sementes registradas
    arquivoSaida<<cont_id<<" "<<cont_registros;

    for (const auto &semente : sementesRestantes) {
        arquivoSaida << semente << std::endl;
    }
    arquivoSaida.close();

    std::cout << "Semente com ID " << idParaExcluir << " excluida com sucesso." << std::endl;
}


void Gestor::salvarLote(const Lote& lote) {
    
    int cont_id,cont_registros;
    try {

        std::fstream arquivoLotes("Lotes.txt");
        if (!arquivoLotes.is_open()) {
            throw std::ios_base::failure("Erro ao abrir o arquivo para salvar dados.");
        }
        //lendo contadores do arquivo
        arquivoLotes>>cont_id;         cont_id++;
        arquivoLotes>>cont_registros;  cont_registros++;


        // Verifica se algum valor está vazio ou inválido
        if (lote.getDataProducao().empty() || lote.getGeneIntroduzido().empty() || lote.getMetodoProducao().empty() ||
            lote.getIdLote() <= 0 || lote.getIdSementeAssociada() <= 0 || 
            lote.getNomeCientifico().empty() || lote.getPaisOrigem().empty()||
            lote.getPrecoEstimado() <= 0 || lote.getQuantidadeDisponivel() < 0||
            lote.getStatusDisponibilidade().empty()) {
            throw std::invalid_argument("Nao foi possivel registrar o lote pois um dos valores esta vazio ou invalido.");
        }

        arquivoLotes.seekp(0,std::ios::end);
        // Caso todos os valores estejam válidos, escreve no arquivo
        arquivoLotes << lote.getIdSementeAssociada() << "+" << lote.getIdLote() << "+" << lote.getStatusDisponibilidade() << "+"
                     << lote.getNomeCientifico() << "+" << lote.getGeneIntroduzido() << "+" << lote.getMetodoProducao() << "+"
                     << lote.getDataProducao() << "+" << lote.getPaisOrigem() << "+" << lote.getQuantidadeDisponivel() << "+" << lote.getPrecoEstimado() << "\n";

        //atualizando contador de id e de lotes registradas
        arquivoLotes.seekg(0,std::ios::beg);        //leva o apontador até a posicao do contador do arquivo
        arquivoLotes<<cont_id <<" "<<cont_registros<<std::endl;  

        arquivoLotes.close();
        std::cout << "Lote registrado com sucesso!\n";
    } catch (const std::ios_base::failure& e) {
        std::cerr << "Excecao de I/O: " << e.what() << "\n";
    }catch (const std::invalid_argument& e) {
        std::cerr << "Excecao de argumento invalido: " << e.what() << std::endl;
    }catch (const std::exception& e) {
        std::cerr << "Excecao: " << e.what() << "\n";
    }
}

void Gestor::registrarLote() {   

    Lote novoLote;
    int id = 0;
    
    std::ifstream arquivoLotes("Lotes.txt");
    if (arquivoLotes.is_open()) {
        arquivoLotes >> id;
        arquivoLotes.close();
    }
    id++; // Increment ID
    //---------------------------------------//

        int idSementeAssociada;
        float quantidadeDisponivel,precoEstimado;
        std::string statusDisponibilidade,nomeCientifico,geneIntroduzido,metodoProducao,dataProducao,paisOrigem;
        

        std::cout << "ID da semente associada: ";                                std::cin >> idSementeAssociada;
        std::cin.ignore();
        std::cout << "Status de disponibilidade (Estoque/Vendido/Plantado): ";   std::getline(std::cin, statusDisponibilidade);
        std::cout << "Nome cientifico: ";                                        std::getline(std::cin, nomeCientifico);
        std::cout << "Gene introduzido: ";                                       std::getline(std::cin, geneIntroduzido);
        std::cout << "Metodo de producao: ";                                     std::getline(std::cin, metodoProducao);
        std::cout << "Data de producao (DD/MM/AA): ";                            std::getline(std::cin, dataProducao);
        std::cout << "Pais de origem: ";                                         std::getline(std::cin, paisOrigem);
        std::cout << "Quantidade disponivel (kg): ";                             std::cin >> quantidadeDisponivel;
        std::cout << "Preco estimado por kg de semente: ";                       std::cin >> precoEstimado;

        novoLote.setIdSementeAssociada(idSementeAssociada);
        novoLote.setIdLote(id);
        novoLote.setStatusDisponibilidade(statusDisponibilidade);
        novoLote.setNomeCientifico(nomeCientifico);
        novoLote.setGeneIntroduzido(geneIntroduzido);
        novoLote.setMetodoProducao(metodoProducao);
        novoLote.setDataProducao(dataProducao);
        novoLote.setPaisOrigem(paisOrigem);
        novoLote.setQuantidadeDisponivel(quantidadeDisponivel);
        novoLote.setPrecoEstimado(precoEstimado);

        lotesRegistrados.push_back(novoLote);

        salvarLote(novoLote);
}

void Gestor::excluirLote() {
    int idParaExcluir;
    std::cout << "Insira o ID do lote que deseja excluir: ";
    std::cin >> idParaExcluir;
    std::cin.ignore();

    std::ifstream arquivoEntrada("Lotes.txt");
    if (!arquivoEntrada.is_open()) {
        throw std::ios_base::failure("Erro ao abrir o arquivo Lotes.txt");
    }

    std::vector<std::string> lotesRestantes;
    std::string linha;
    bool loteEncontrado = false;

    int cont_id, cont_registros;
    arquivoEntrada>>cont_id>>cont_registros;

    while (std::getline(arquivoEntrada, linha)) {
        std::stringstream ss(linha);
        int idSementeAssociada, idLote;
        char separador;
        ss >> idSementeAssociada >> separador >> idLote >> separador;

        if (idLote == idParaExcluir) {
            loteEncontrado = true;
            continue; 
        }
        lotesRestantes.push_back(linha);
    }
    arquivoEntrada.close();

    if (!loteEncontrado) {
        std::cout << "Lote com ID " << idParaExcluir << " nao encontrado." << std::endl;
        return;
    }
    std::ofstream arquivoSaida("Lotes.txt");
    if (!arquivoSaida.is_open()) {
        throw std::ios_base::failure("Erro ao abrir o arquivo Lotes.txt para escrita");
    }
    cont_registros--;   //diminui um no contador de lotes registradas
    arquivoSaida<<cont_id<<" "<<cont_registros;

    for (const auto &lote : lotesRestantes) {
        arquivoSaida << lote << std::endl;
    }
    arquivoSaida.close();

    std::cout << "Lote com ID " << idParaExcluir << " excluido com sucesso." << std::endl;
}

void Gestor::visualizar_semente_especifica(){

    Semente semente_vizualizada;
    int id;

    std::cout<<"Deseja visualizar os dados de qual semente? ID: ";
    std::cin>>id;
    if(id<=0)
        throw std::invalid_argument("Valor de id invalido");
    semente_vizualizada.set_id_tipo(id);
    //____________________________________________//
    std::fstream arquivoSementes ("Sementes.txt");
    if(!arquivoSementes)
        std::cerr<<"Erro ao abrir o arquivo Semente.txt\n";

    std::string linha;
    float valor_lido;
    int id_lido=0;

    while(id_lido!=id){
        std::getline(arquivoSementes, linha);  //ignorando
        arquivoSementes>>id_lido;
        if (arquivoSementes.fail()) {
            throw std::invalid_argument("Nao existe nenhuma semente com esse id");
        }
    }
    arquivoSementes.ignore();                                           
    getline(arquivoSementes, linha, '+');                       semente_vizualizada.set_solo_ideal(linha);
    getline(arquivoSementes, linha, '+');                       semente_vizualizada.set_clima_ideal(linha);                                      
    arquivoSementes >> valor_lido;                              semente_vizualizada.set_expectativaIncidenciaPragasDoencas(valor_lido);
    arquivoSementes >> valor_lido;                              semente_vizualizada.set_irrigacao_ideal(valor_lido);           
    arquivoSementes >> valor_lido;                              semente_vizualizada.set_expectativaCrescimento(valor_lido);          
    arquivoSementes >> valor_lido;                              semente_vizualizada.set_expectativaTaxaDeGerminacao(valor_lido);
    arquivoSementes >> valor_lido;                              semente_vizualizada.set_expectativaTaxaDeSobrevivencia(valor_lido);
    arquivoSementes >>valor_lido;                            
    if(valor_lido==1){
        semente_vizualizada.set_produz_frutos(true);
        arquivoSementes>>valor_lido;              semente_vizualizada.set_tempo_colheita(valor_lido);
    }
    else{
        semente_vizualizada.set_produz_frutos(false);
        arquivoSementes>>valor_lido;              semente_vizualizada.set_tempo_colheita(valor_lido);
    }

    arquivoSementes.close();
    //------------------------------------------------
    for(int i=0;i<50;i++) std::cout<<"-";
    std::cout<<std::endl;

    std::cout<<"Dados da semente:\nID :"<<semente_vizualizada.get_id_tipo()<<"\nSolo ideal: "<<semente_vizualizada.get_solo_ideal()<<"\nClima ideal: "<<
    semente_vizualizada.get_clima_ideal()<<"\nIrrigacao ideal: "<<semente_vizualizada.get_irrigacao_ideal()<<" cmˆ3 agua/cmˆ3 solo\nTaxa de germinacao: "<<
    semente_vizualizada.get_expectativaTaxaDeGerminacao()<<" %\nTaxa de sobrevivencia: "<<semente_vizualizada.get_expectativaTaxaDeSobrevivencia()<<" %\nTaxa de crescimento: "<<
    semente_vizualizada.get_expectativaCrescimento()<<" %\nTaxa de incidencia de Pragas e doencas: "<<semente_vizualizada.get_expectativaIncidenciaPragasDoencas()<<" %\n";
    if(semente_vizualizada.get_produz_frutos())
        std::cout<<"Produz frutos com um tempo de colheita de: "<<semente_vizualizada.get_tempo_colheita()<<" meses\n";

    for(int i=0;i<50;i++) std::cout<<"-";
    std::cout<<std::endl;
}

void Gestor::visualizar_lote_especifico(){

    int idSementeAssociada,id;
    float quantidadeDisponivel,precoEstimado;
    std::string statusDisponibilidade,nomeCientifico,geneIntroduzido,metodoProducao,dataProducao,paisOrigem;

    std::cout<<"Deseja visualizar os dados de qual lote? ID: ";
    std::cin>>id;
    if(id<=0)
        throw std::invalid_argument("Valor de id invalido");
    //____________________________________________//
    std::ifstream arquivoLotes ("Lotes.txt");
    if(!arquivoLotes)
        std::cerr<<"Erro ao abrir o arquivo Lotes.txt\n";

    std::string linha;     //buffer
    int id_lido=0;

    //lendo cada linha do arquivo até encontrar o id do lote solicitado
    while(id_lido!=id){
        std::getline(arquivoLotes, linha);  //ignorando
        arquivoLotes>>idSementeAssociada;    arquivoLotes.ignore();  arquivoLotes>>id_lido;
        if (arquivoLotes.fail()) {
            throw std::invalid_argument("Nao existe nenhuma semente com esse id");
        }
    }
    //----------------------------------------------
    try{
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
            throw std::ios_base::failure("Erro na leitura do arquivoLotes.txt");
        
    
    }catch(const std::exception& e){
        throw std::runtime_error("Erro ao processar dados do lote.");
    }
    arquivoLotes.close();
    //--------------------------------------------
    try{
        for(int i=0;i<50;i++) std::cout<<"-";
        std::cout<<std::endl;

        std::cout<<"Dados do lote:\nID :"<<id<<"\nNome cientifico: "<<nomeCientifico<<"\nGene introduzido: "<<
        geneIntroduzido<<"\nMetodo de producao: "<<metodoProducao<<"\nData de producao: "<<dataProducao<<"\nPais de origem: "<<
        paisOrigem<<"\nQuantidade disponivel no lote: "<<quantidadeDisponivel<<" kg\nPreco estimado: RS"<<precoEstimado<<"/kg de semente\n";
        

        for(int i=0;i<50;i++) std::cout<<"-";
            std::cout<<std::endl;
    }catch(const std::exception& e){
        throw std::runtime_error("Erro ao exibir detalhes sobre o lote.");
    }
}

void Gestor::acessarInterface() {
    int opcao_selecionada;

    while (true) {
        int opcao_selecionada;
        std::cout << "|-------------------------MENU DO GESTOR--------------------------|\n";
        std::cout << "|1|- Registrar uma nova semente\n";
        std::cout << "|2|- Visualizar dados de uma semente\n";
        std::cout << "|3|- Excluir uma semente\n";
        std::cout << "|4|- Registrar um novo lote\n";
        std::cout << "|5|- Visualizar dados de um lote\n";
        std::cout << "|6|- Excluir um lote\n";
        std::cout << "|7|- Cadastrar um novo usuário\n";
        std::cout << "|8|- Listar usuários cadastrados\n";
        std::cout << "|9|- Excluir um usuário\n";
        std::cout << "|10|- Visualizar relatórios\n";
        std::cout << "|11|- Sair do programa\n";
        std::cout << "|------------------------------------------------------------------|\n";
        std::cout << "|Escolha uma opção: ";
        
        std::cin >> opcao_selecionada;
                // Verifica se a entrada é inválida (ex.: usuário digitou uma string ou caractere inválido)
        if (std::cin.fail()) {
            std::cin.clear(); // Limpa o estado de erro do cin
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignora o restante da entrada inválida
            std::cerr << "Entrada inválida! Por favor, insira um número correspondente a uma opção do menu.\n";
            continue;
        }

        switch (opcao_selecionada) {
            case 1:
                try {
                    registrarSemente();
                } catch (const std::bad_alloc& e) {
                    std::cerr << "Erro de alocação de memória. " << e.what() << std::endl;
                } catch (const std::exception& e) {
                    std::cerr << "Erro: " << e.what() << std::endl;
                } catch (...) {
                    std::cerr << "Erro desconhecido!" << std::endl;
                }
                break;
            
            case 2:
                try {
                    visualizar_semente_especifica();
                } catch (const std::exception& e) {
                    std::cerr << "Erro: " << e.what() << std::endl;
                } catch (...) {
                    std::cerr << "Erro desconhecido!" << std::endl;
                }
                break;
            
            case 3:
                try {
                    excluirSemente();
                } catch (const std::exception& e) {
                    std::cerr << "Erro: " << e.what() << std::endl;
                } catch (...) {
                    std::cerr << "Erro desconhecido!" << std::endl;
                }
                break;
            
            case 4:
                try {
                    registrarLote();
                } catch (const std::exception& e) {
                    std::cerr << "Erro: " << e.what() << std::endl;
                } catch (...) {
                    std::cerr << "Erro desconhecido!" << std::endl;
                }
                break;
            
            case 5:
                try {
                    visualizar_lote_especifico();
                } catch (const std::exception& e) {
                    std::cerr << "Erro: " << e.what() << std::endl;
                } catch (...) {
                    std::cerr << "Erro desconhecido!" << std::endl;
                }
                break;
            
            case 6:
                try {
                    excluirLote();
                } catch (const std::exception& e) {
                    std::cerr << "Erro: " << e.what() << std::endl;
                } catch (...) {
                    std::cerr << "Erro desconhecido!" << std::endl;
                }
                break;
            
                        case 7:
                try {
                    cadastrarUsuario();
                } catch (const std::exception& e) {
                    std::cerr << "Erro: " << e.what() << std::endl;
                } catch (...) {
                    std::cerr << "Erro desconhecido!" << std::endl;
                }
                break;

            case 8:
                try {
                    listarUsuarios();
                } catch (const std::exception& e) {
                    std::cerr << "Erro: " << e.what() << std::endl;
                } catch (...) {
                    std::cerr << "Erro desconhecido!" << std::endl;
                }
                break;

            case 9:
                try {
                    excluirUsuario();
                } catch (const std::exception& e) {
                    std::cerr << "Erro: " << e.what() << std::endl;
                } catch (...) {
                    std::cerr << "Erro desconhecido!" << std::endl;
                }
                break;

            case 10:
                try {
                    gerarRelatorio();
                } catch (const std::exception& e) {
                    std::cerr << "Erro: " << e.what() << std::endl;
                }
                break;

            case 11:
                std::cout << "Encerrando o programa...\n";
                return;

            default:
                std::cerr << "Opção inválida! Tente novamente.\n";
                break;
        }
    }
}


void Gestor::gerarRelatorio() {
    try {
        std::cout << "O relatorio sobre as sementes e os lotes está sendo gerado!\n";

        // Abre ou cria o arquivo de relatório
        std::ofstream relatorioGerado("RelatorioGestor.txt");
        if (!relatorioGerado) {
            throw std::runtime_error("Erro: Não foi possível abrir o arquivo 'RelatorioGestor.txt'");
        }

        // Abrir o arquivo de sementes
        std::ifstream arquivoSementes("Sementes.txt");
        if (!arquivoSementes) {
            throw std::runtime_error("Erro: Não foi possível abrir o arquivo 'Sementes.txt'");
        }

        relatorioGerado << "------------------------------------------------DADOS DAS SEMENTES------------------------------------------------------\n";
        std::string linha;
        
        // Percorrendo cada linha do arquivo de sementes
        while (std::getline(arquivoSementes, linha)) {
            std::string clima, solo;
            float tempoColheita, irrigacaoIdeal, expectativaIncidenciaPragasDoencas, expectativaCrescimento;
            int produzFrutos;
            float expectativaTaxaGerminacao, expectativaTaxaSobrevivencia;
            int id_lido;

            arquivoSementes >> id_lido; arquivoSementes.ignore(); 
            std::getline(arquivoSementes, clima, '+');
            std::getline(arquivoSementes, solo, '+');
            arquivoSementes >> irrigacaoIdeal;
            arquivoSementes >> expectativaIncidenciaPragasDoencas;
            arquivoSementes >> expectativaTaxaSobrevivencia;
            arquivoSementes >> expectativaTaxaGerminacao;
            arquivoSementes >> expectativaCrescimento;
            arquivoSementes >> produzFrutos;
            arquivoSementes >> tempoColheita;

            // Construir a string com os dados da semente
            relatorioGerado << "ID: " << id_lido << 
                                "\n\nSolo ideal: " + solo +
                                "\nClima ideal: " + clima +
                                "\nIrrigação ideal: " << irrigacaoIdeal << " cm3/água/cm3 solo" <<
                                "\nTaxa de germinação: " << expectativaTaxaGerminacao << "%" <<
                                "\nTaxa de sobrevivência: " << expectativaTaxaSobrevivencia << "%" <<
                                "\nTaxa de crescimento: " << expectativaCrescimento << "%" <<
                                "\nTaxa de incidência de Pragas e Doenças: " << expectativaIncidenciaPragasDoencas << "%\n";

            if (produzFrutos == 1) {
                relatorioGerado << "Produz frutos a cada " << tempoColheita << " meses, em média.\n\n\n";
            } else {
                relatorioGerado << "Não produz frutos.\n\n\n";
            }
        }

        arquivoSementes.close();

        // Abrir o arquivo dos lotes
        std::ifstream arquivoLotes("Lotes.txt");
        if (!arquivoLotes) {
            throw std::runtime_error("Erro: Não foi possível abrir o arquivo 'Lotes.txt'");
        }

        // Parte dos lotes do relatório
        relatorioGerado << "\n\n--------------------------------------------------DADOS DOS LOTES------------------------------------------------------\n";

        int cont;
        arquivoLotes >> cont >> cont;

        // Percorrendo cada linha do arquivo de lotes
        for (int i = 0; i < cont; i++) {
            int idSementeAssociada, id;
            float quantidadeDisponivel, precoEstimado;
            std::string statusDisponibilidade, nomeCientifico, geneIntroduzido, metodoProducao, dataProducao, paisOrigem;

            arquivoLotes >> idSementeAssociada; arquivoLotes.ignore();
            arquivoLotes >> id; arquivoLotes.ignore();
            std::getline(arquivoLotes, statusDisponibilidade, '+');
            std::getline(arquivoLotes, nomeCientifico, '+');
            std::getline(arquivoLotes, geneIntroduzido, '+');
            std::getline(arquivoLotes, metodoProducao, '+');
            std::getline(arquivoLotes, dataProducao, '+');
            std::getline(arquivoLotes, paisOrigem, '+');
            arquivoLotes >> quantidadeDisponivel; arquivoLotes.ignore();
            arquivoLotes >> precoEstimado;

            // Construir a string com os dados do lote
            relatorioGerado << "ID: " << id << "\n\nID da semente associada: " << idSementeAssociada <<
                                "\nNome científico: " << nomeCientifico <<
                                "\nGene introduzido: " << geneIntroduzido <<
                                "\nMétodo de produção: " << metodoProducao <<
                                "\nData de produção: " << dataProducao <<
                                "\nPaís de origem: " << paisOrigem <<
                                "\nStatus de disponibilidade: " << statusDisponibilidade <<
                                "\nQuantidade disponível: " << std::fixed << std::setprecision(2) << quantidadeDisponivel << "KG" <<
                                "\nPreço por kg: RS" << std::fixed << std::setprecision(2) << precoEstimado << "\n\n\n";
        }

        arquivoLotes.close();
        relatorioGerado.close();
    }
    catch (const std::exception& e) {
        std::cerr << "Erro: " << e.what() << std::endl;
    }
    std::cout<<"Relatorio completo em: RelatorioGestor.txt\n";
}
