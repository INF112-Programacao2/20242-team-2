#include "classeLote.hpp"
#include "classeSemente.hpp"


lote::lote(){

    _statusDisponibilidade="estoque"; 
    //____________________________________________//
         
    std::fstream arquivoLotes ("Lotes.txt");
    if(!arquivoLotes)
        std::cerr<<"Erro ao abrir o arquivo Lotes.txt\n";

    //identificar qual o id do proximo lote:
    arquivoLotes>>_id_lote; _id_lote++;         //le o contador de lotes e calcula o ID
    arquivoLtes.seekg(0,std::ios::beg);        //leva o apontador até a posicao do contador do arquivo
    arquivoLotes<<_id_lote <<std::endl;                    //atualiza o contador
 
    arquivoLotes.close();
    //____________________________________________//

    std::ofstream arquivoLotesON ("Lotes.txt",std::ios::app);  
    
    std::cout<<"Nome cientifico: ";                  std::getline(std::cin,_nome_cientifico);                 
    std::cout<<"Gene introduzido: ";                 std::getline(std::cin,_geneIntroduzido);
    std::cout<<"Metodo de producao: ";               std::getline(std::cin,_metodo_producao);
    std::cout<<"Data de producao:  DD/MM/AA ";       std::getline(std::cin,_data_producao);
    std::cout<<"País de origem: ";                   std::getline(std::cin,_pais_origem);
    std::cout<<"Quantidade disponível no lote: ";    std::cin>>_quantidade_disponivel;
    std::cout<<"Preco estimado:  ";                  std::cin>>_preco_estimado;

    arquivoLotesON<<_id_lote<<" "<<_statusDisponibilidade<<" "<<_nome_cientifico<<" "<<_geneIntroduzido<<" "<<_metodo_producao<<" "<<
        _data_producao<<" "<<_pais_origem<<" "<<_quantidade_disponivel<<" "<<_preco_estimado<<"\n";
    
    arquivoLotesON.close();

    //____________________________________________//
    //todo lote está associado a alguma semente, entao
    char resposta;
    std::cout<<"Esse lote é associado a uma semente ja registrada?  S/N";
    std::cin>>resposta;


    //ainda será alterado! é necessario fazer o construtor da semente ainda
    if(resposta=='S'||resposta=='s'){
        semente *semente_associada=new semente();    //essa semente pode ou nao ja estar registrada
    }
    else if(resposta=='N'||resposta=='n'){
        semente *semente_associada=new semente();
    }
}



