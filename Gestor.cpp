#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "Gestor.hpp"
#include "Vendedor.hpp"
#include "Analista.hpp"

Gestor::Gestor(){};

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

void Gestor::salvarSemente(Semente& semente) {

    int cont_id,cont_registros;
    try {
        std::fstream arquivo("Sementes.txt");
        if (!arquivo.is_open()) {
            throw std::ios_base::failure("Erro ao abrir o arquivo para registro.");
        }

        //lendo contadores do arquivo
        arquivo>>cont_id;         cont_id++;
        arquivo>>cont_registros;  cont_registros++;

        // Verifica se algum valor está vazio ou inválido
        if (semente.get_id_tipo() == 0 || semente.get_solo_ideal().empty() || semente.get_clima_ideal().empty() ||
            semente.get_tempo_colheita() < 0 || semente.get_irrigacao_ideal() <= 0 || 
            semente.get_expectativaIncidenciaPragasDoencas() < 0 || semente.get_expectativaCrescimento() < 0 ||
            semente.get_expectativaTaxaDeGerminacao() < 0 || semente.get_expectativaTaxaDeSobrevivencia() < 0) {
            throw std::invalid_argument("Nao foi possivel registrar a semente pois um dos valores esta vazio ou invalido.");
        }

        arquivo.seekp(0,std::ios::end);
        // Caso todos os valores estejam válidos, escreve no arquivo
        arquivo << semente.get_id_tipo() << "+" << semente.get_solo_ideal() << "+"
                << semente.get_clima_ideal() << "+" << semente.get_tempo_colheita() << "+"
                << semente.get_irrigacao_ideal() << "+" << semente.get_expectativaIncidenciaPragasDoencas() << "+"
                << semente.get_expectativaCrescimento() << "+" << semente.get_expectativaTaxaDeGerminacao() << "+"
                << semente.get_expectativaTaxaDeSobrevivencia() << "+" << semente.get_produz_frutos() << "\n";

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

        std::string clima, solo;
        float tempoColheita, irrigacaoIdeal, expectativaIncidenciaPragasDoencas, expectativaCrescimento;
        bool produzFrutos;
        float expectativaTaxaGerminacao, expectativaTaxaSobrevivencia;
        int id;

        std::ifstream arquivoSementes("Sementes.txt");
        if (!arquivoSementes.is_open()) {
            throw std::ios_base::failure("Erro ao abrir o arquivo Sementes.txt para escrita");
        }
        arquivoSementes>>id; id++;         //le o contador de tipos e calcula o ID
        arquivoSementes.close();


        std::cout << "Insira os detalhes da semente:\n";
        std::cout << "Clima ideal: ";                               std::getline(std::cin, clima); 
        std::cout << "Solo ideal: ";                                std::getline(std::cin, solo);
        std::cout << "Irrigacao ideal (em mm/dia): ";               std::cin >> irrigacaoIdeal;
        std::cout << "Expectativa de resistência a pragas (%): ";   std::cin >> expectativaIncidenciaPragasDoencas;
        std::cout << "Expectativa de crescimento (%): ";            std::cin >> expectativaCrescimento;
        std::cout << "Expectativa de taxa de germinação (%): ";     std::cin >> expectativaTaxaGerminacao;
        std::cout << "Expectativa de taxa de sobrevivência (%): ";   std::cin >> expectativaTaxaSobrevivencia;

        //se produz frutos? e se sim de quanto em quanto tempo?
        char resp;
        std::cout<<"Produz frutos? (S/N) ";   std::cin>>resp;
        if(resp=='s'||resp=='s'){
            novaSemente.set_produz_frutos(true);
            std::cout<<"Tempo de colheita (meses): ";     
            std::cin>>tempoColheita;
            novaSemente.set_tempo_colheita(tempoColheita); 

            if (std::cin.fail()) {
                throw std::invalid_argument("Entrada inválida para o tempo de colheita.");
            }
        std::cin.ignore();          
        }

        else if(resp=='n'||resp=='N'){
            novaSemente.set_produz_frutos(false);
            novaSemente.set_tempo_colheita(0);
        }
        //tratando respostas diferentes de sim ou nao
        else
            throw std::invalid_argument("Resposta inválida para 'Produz frutos?'");
        
        novaSemente.set_id_tipo(id);
        novaSemente.set_clima_ideal(clima);
        novaSemente.set_solo_ideal(solo);
        novaSemente.set_tempo_colheita(tempoColheita);
        novaSemente.set_irrigacao_ideal(irrigacaoIdeal);
        novaSemente.set_expectativaIncidenciaPragasDoencas(expectativaIncidenciaPragasDoencas);
        novaSemente.set_expectativaCrescimento(expectativaCrescimento);
        novaSemente.set_expectativaTaxaDeGerminacao(expectativaTaxaGerminacao);
        novaSemente.set_expectativaTaxaDeSobrevivencia(expectativaTaxaSobrevivencia);
        novaSemente.set_produz_frutos(produzFrutos);

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
    } catch (const std::exception& e) {
        std::cerr << "Excecao: " << e.what() << "\n";
    }catch (const std::invalid_argument& e) {
        std::cerr << "Excecao de argumento invalido: " << e.what() << std::endl;
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

        int idSementeAssociada,quantidadeDisponivel,precoEstimado;
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
    getline(arquivoSementes, linha, '+');                       semente_vizualizada.set_clima_ideal(linha);
    getline(arquivoSementes, linha, '+');                       semente_vizualizada.set_solo_ideal(linha);                                      
    arquivoSementes >> valor_lido;                              semente_vizualizada.set_expectativaIncidenciaPragasDoencas(valor_lido);
    arquivoSementes >> valor_lido;                              semente_vizualizada.set_irrigacao_ideal(valor_lido);           
    arquivoSementes >> valor_lido;                              semente_vizualizada.set_expectativaTaxaDeSobrevivencia(valor_lido);          
    arquivoSementes >> valor_lido;                              semente_vizualizada.set_expectativaTaxaDeGerminacao(valor_lido);
    arquivoSementes >> valor_lido;                              semente_vizualizada.set_expectativaCrescimento(valor_lido);
    arquivoSementes >>valor_lido;                            
    if(valor_lido==1){
        semente_vizualizada.set_produz_frutos(true);
        arquivoSementes>>valor_lido;              semente_vizualizada.set_tempo_colheita(valor_lido);
    }


    arquivoSementes.close();
    //------------------------------------------------
    for(int i=0;i<50;i++) std::cout<<"-";
    std::cout<<std::endl;

    std::cout<<"Dados da semente:\nID :"<<semente_vizualizada.get_id_tipo()<<"\nSolo ideal: "<<semente_vizualizada.get_solo_ideal()<<"\nClima ideal: "<<
    semente_vizualizada.get_clima_ideal()<<"\nIrrigacao ideal: "<<semente_vizualizada.get_irrigacao_ideal()<<" cmˆ3 agua/cmˆ3 solo\nTaxa de germinacao: "<<
    semente_vizualizada.get_expectativaTaxaDeGerminacao()<<" %\nTaxa de sobrevivencia: "<<semente_vizualizada.get_expectativaTaxaDeSobrevivencia()<<" %\nTaxa de crescimento: "<<
    semente_vizualizada.get_expectativaTaxaDeSobrevivencia()<<" %\nTaxa de incidencia de Pragas e doencas: "<<semente_vizualizada.get_expectativaIncidenciaPragasDoencas()<<" %\n";
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

int Gestor::acessarInterface() {
   int opcao_selecionada;

   std::cout<<"-------------------------MENU DO GESTOR--------------------------\n";
   std::cout<<"1- Registrar uma nova semente\n2- Visualizar dados de uma semente\n";
   std::cout<<"3- Excluir uma semente\n4- Registrar um novo lote\n";
   std::cout<<"5-Visualizar dados de um lote\n6- Excluir um lote\n";
   std::cout<<"7-Visualizar relatórios\n8- Sair do programa\n";
   std::cout<<"------------------------------------------------------------------\n";

   std::cin>>opcao_selecionada;
   if(opcao_selecionada!=1&&opcao_selecionada!=2&&opcao_selecionada!=3
       &&opcao_selecionada!=4&&opcao_selecionada!=5&&opcao_selecionada!=6
       &&opcao_selecionada!=7&&opcao_selecionada!=8){
       throw std::invalid_argument("Opção inválida! Por favor, selecione uma opção válida.");
   }
    if(opcao_selecionada==1){
        //registrar uma nova semente
        try {
            registrarSemente();
        
        }catch (const std::bad_alloc& e) {
            std::cerr << "Erro de alocação de memória. " << e.what() << std::endl;
        }catch (const std::exception& e) {
            std::cerr << "Erro: " << e.what() << std::endl;
        }catch (...) {
            std::cerr << "Erro desconhecido!" << std::endl;
        }
    }
    else if(opcao_selecionada==2){
        //visualizar dados de uma semente especifica
        try{
        visualizar_semente_especifica();
        }catch(const std::exception& e){
            std::cerr<<"Erro: "<<e.what()<<std::endl;
        }catch(...){
            std::cerr<<"Erro desconhecido!"<<std::endl;
        }
    }
   else if(opcao_selecionada==3){
        //excluir uma semente
        try{
            excluirSemente();
        }catch(const std::exception& e){
            std::cerr<<"Erro: "<<e.what()<<std::endl;
        }catch(...){
            std::cerr<<"Erro desconhecido!"<<std::endl;
        }
   }
    else if(opcao_selecionada==4){
        //registrar um novo lote
        try{
            registrarLote();
        }catch(const std::exception& e){
            std::cerr<<"Erro: "<<e.what()<<std::endl;
        }catch(...){
            std::cerr<<"Erro desconhecido!"<<std::endl;
        }
    }
    else if(opcao_selecionada==5){
        //visualizar dados de um lote em especifico
        try{
            visualizar_lote_especifico();
        }catch(const std::exception& e){
            std::cerr<<"Erro: "<<e.what()<<std::endl;
        }catch(...){
            std::cerr<<"Erro desconhecido!"<<std::endl;
        }
    }
    else if(opcao_selecionada==6){
        try{
            excluirLote();
        }catch(const std::exception& e){
            std::cerr<<"Erro: "<<e.what()<<std::endl;
        }catch(...){
            std::cerr<<"Erro desconhecido!"<<std::endl;
        }
    }
    else if(opcao_selecionada==7){
        // funcao pra visualizar relatorio;
         // funcao pra visualizar relatorio;
        try{
            gerarRelatorio();
        }catch(const std::exception& e){
            std::cerr<<"Erro: "<<e.what()<<std::endl;
        }catch(...){
            std::cerr<<"Erro desconhecido!"<<std::endl;
        }
    }
    else if(opcao_selecionada==8){
        return 0;
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
