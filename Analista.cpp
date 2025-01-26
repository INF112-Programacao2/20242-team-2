#include "Analista.hpp"
#include <iostream>

Analista::Analista(){};
Analista::~Analista(){};

void Analista::elaborarRelatorio(){
    std::cout<<"Elaboração do relatório de analise das sementes"<<
    "\n\nDeseja realizar o relatorio de qual semente? ID: ";

    int id_semente;
    std::cin>>id_semente;
    while(id_semente<=0){
        std::cout<<"ID inválido. Digite novamente o ID da semente: ";
        std::cin>>id_semente;
    }


    Relatorio relatorio;
    relatorio.set_id_semente(id_semente);
    float texto;

    std::cout << "Insira os detalhes da observados no plantio:\n";
    std::cout << "Irrigacao ideal (em mm/dia): ";                   std::cin >> texto;          relatorio.set_irrigacao(texto);     
    std::cout << "Taxa desistência a pragas (%): ";                 std::cin >> texto;          relatorio.set_pragasDoencas(texto);
    std::cout << "Taxa de crescimento (%): ";                       std::cin >> texto;          relatorio.set_crescimento(texto);
    std::cout << "Taxa de germinação (%): ";                        std::cin >> texto;          relatorio.set_geminacao(texto);
    std::cout << "Taxa de sobrevivência (%): ";                     std::cin >> texto;          relatorio.set_sobrevivencia(texto);
    std::cout << "Tempo de colheira em dias: ";                     std::cin >> texto;          relatorio.set_tempo_colheita(texto);
    
    registrarRelatorio(relatorio);

}

void Analista::registrarRelatorio(Relatorio &relatorio){


    std::fstream arquivoRelatorio("Relatorio.txt");
    if(!arquivoRelatorio)
        throw std::ios_base::failure("Erro ao abrir o arquivo Relatorio.txt");

    int cont_id,cont_registros;
    arquivoRelatorio>>cont_id>>cont_registros; 
    cont_id++; cont_registros++;
    relatorio.set_id_relatorio(cont_id);

    arquivoRelatorio.seekp(0,std::ios::end);

    arquivoRelatorio<<relatorio.get_id_semente()<<"+"<<relatorio.get_id_relatorio()<<"+"<<relatorio.get_irrigacao()<<"+"
    <<relatorio.get_pragasDoencas()<<"+"<<relatorio.get_crescimento()<<"+"<<relatorio.get_germinacao()<<"+"
    <<relatorio.get_sobrevivencia()<<"+"<<relatorio.get_tempo_colheita()<<std::endl;

    arquivoRelatorio.seekp(0,std::ios::beg);
    arquivoRelatorio<<cont_id<<" "<<cont_registros;

    arquivoRelatorio.close();

}

int Analista::acessarInterface(){

int opcao_menu;

std::cout<<"-------------------------MENU DO ANALISTA--------------------------\n";
   std::cout<<"1- Registrar um novo relatorio\n2- Gerar relatório\n";
   std::cout<<"3- Atualizar status de um lote\n""4- Sair do programa\n";
   std::cout<<"------------------------------------------------------------------\n";

   std::cin>>opcao_menu;
   if(opcao_menu==1){
        elaborarRelatorio();
   }
   else if(opcao_menu==2){
        gerarRelatorio();
   }
       else if(opcao_menu==3){
           return 0;
       }
   else{
    throw std::invalid_argument("Opcao de menu inválido!\n");
   }

}


void Analista::gerarRelatorio(){

    try {
        std::cout << "O relatorio está sendo gerado!\n";

        // Abrir o arquivo de sementes
        std::ifstream arquivoRelatorio("Relatorio.txt");
        if (!arquivoRelatorio) {
            throw std::runtime_error("Erro: Não foi possível abrir o arquivo 'Relatorio.txt'");
        }

         // gerando o relatorio do analista
        std::ofstream relatorioGerado("RelatorioAnalista.txt");
        if (!relatorioGerado) {
            throw std::runtime_error("Erro: Não foi possível abrir o arquivo 'Sementes.txt'");
        }
        relatorioGerado << "------------------------------------------------DADOS DAS ANALISES DE PLANTIO--------------------------------------------------\n";
    

        std::string linha;
        Relatorio relatorio;

        // Percorrendo cada linha do arquivo de sementes
        std::string texto;
        int inteiro;
        float decimal;
        while (std::getline(arquivoRelatorio, texto)) {
            arquivoRelatorio>>inteiro;          arquivoRelatorio.ignore();    relatorio.set_id_semente(inteiro);
            arquivoRelatorio>>inteiro;          arquivoRelatorio.ignore();    relatorio.set_id_relatorio(inteiro);
            arquivoRelatorio>>decimal;          arquivoRelatorio.ignore();    relatorio.set_irrigacao(decimal);
            arquivoRelatorio>>decimal;          arquivoRelatorio.ignore();    relatorio.set_pragasDoencas(decimal);
            arquivoRelatorio>>decimal;          arquivoRelatorio.ignore();    relatorio.set_crescimento(decimal);
            arquivoRelatorio>>decimal;          arquivoRelatorio.ignore();    relatorio.set_geminacao(decimal);
            arquivoRelatorio>>decimal;          arquivoRelatorio.ignore();    relatorio.set_sobrevivencia(decimal);
            arquivoRelatorio>>inteiro;                                        relatorio.set_tempo_colheita(inteiro);  

            if(arquivoRelatorio.fail())
                throw std::ios_base::failure("Erro na leitura do arquivo Relatorio.txt\n");
            
            relatorioGerado << "\n\nID: "<<relatorio.get_id_relatorio()
                            <<"\nReferente a semente de ID: "<<relatorio.get_id_semente()
                            <<"\nIrrigação ideal observada: (%) "<< relatorio.get_irrigacao()
                            <<"\nTaxa de germinação observada: (%) "<<relatorio.get_germinacao()
                            <<"\nTaxa de sobrevivência observada: (%) "<<relatorio.get_sobrevivencia()
                            <<"\nTaxa de crescimento observada: (%) "<<relatorio.get_crescimento()
                            <<"\nTaxa de incidência de pragas e doenças: (%) "<<relatorio.get_pragasDoencas();

            if(relatorio.get_tempo_colheita()!=0){
                relatorioGerado<<"Observou-se um tempo de colheira médio, em dias, de: "<<relatorio.get_tempo_colheita();
            }
                            
        } 
        arquivoRelatorio.close();
        relatorioGerado.close();

    }catch (const std::exception& e) {
            std::cerr << "Erro: " << e.what() << std::endl;
    }
        std::cout<<"Relatorio completo em: RelatorioGestor.txt\n";

}

void Analista::atualizarStatusDoLote(){
    int id_lote=0;
    std::cout<<"Atualizar como 'Plantado' status da semente de ID: ";
    std::cin>>id_lote;

    while(id_lote<=0){
        std::cout<<"ID de lote inválido. Digite novamente: ";
        std::cin>>id_lote;
    }

    std::fstream arquivoLote("Lotes.txt");
    if(!arquivoLote)
        throw std::runtime_error("Erro: Não foi possível abrir o arquivo 'Sementes.txt'");

    std::string linha;
    std::getline(arquivoLote,linha); //ignorando primeira linha do txt
    int id_lido;
    
    while(true){
        arquivoLote>>id_lido; arquivoLote.ignore();      //ignorando id semente e caracter +
        arquivoLote>>id_lido;

        if(id_lido==id_lote)
            break;
        else{
            std::getline(arquivoLote,linha);
            if(arquivoLote.fail())
                throw std::ios_base::failure("ID nao encontrado!");
        }
    }
    Lote lote_alterado(id_lote);
    arquivoLote.seekp(arquivoLote.tellg());
    arquivoLote<<"+Plantado";

    arquivoLote.close();

}
