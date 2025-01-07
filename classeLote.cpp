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
 
    //____________________________________________//
    //todo lote está associado a alguma semente, entao
    char resposta;
    std::cout<<"Esse lote é associado a uma semente ja registrada?  S/N ";
    std::cin>>resposta;
    

    //ainda será alterado! é necessario fazer o construtor da semente ainda
    if(resposta=='S'||resposta=='s'){
        int id;
        std::cout<<"Qual o id da semente associada ao lote? ";
        std::cin>>id;
        _ptr_semente=new semente(id);    //essa semente pode ou nao ja estar registrada
        _id_sementeAssociada=_ptr_semente->get_id_tipo();
    }
    else if(resposta=='N'||resposta=='n'){
        _ptr_semente=new semente();
        _id_sementeAssociada=_ptr_semente->get_id_tipo();
    }
  
    std::cin.ignore();
    
    std::cout<<"Nome cientifico: ";                  std::getline(std::cin,_nome_cientifico);                 
    std::cout<<"Gene introduzido: ";                 std::getline(std::cin,_geneIntroduzido);
    std::cout<<"Metodo de producao: ";               std::getline(std::cin,_metodo_producao);
    std::cout<<"Data de producao:  DD/MM/AA ";       std::getline(std::cin,_data_producao);
    std::cout<<"País de origem: ";                   std::getline(std::cin,_pais_origem);
    std::cout<<"Quantidade disponível no lote: ";    std::cin>>_quantidade_disponivel;
    std::cout<<"Preco estimado:  ";                  std::cin>>_preco_estimado;
    arquivoLotes.seekp(0, std::ios::end);
    arquivoLotes<<_id_sementeAssociada<<"+"<<_id_lote<<"+"<<_statusDisponibilidade<<"+"<<_nome_cientifico<<"+"<<_geneIntroduzido<<"+"<<_metodo_producao<<"+"<<
        _data_producao<<"+"<<_pais_origem<<"+"<<_quantidade_disponivel<<"+"<<_preco_estimado<<"\n";
    
    arquivoLotes.seekg(0,std::ios::beg);        //leva o apontador até a posicao do contador do arquivo
    arquivoLotes<<_id_lote <<std::endl;                    //atualiza o contador
    
    arquivoLotes.close();

    //____________________________________________//
}
lote::~lote(){}

void lote::exibirDetalhesDaSemente(){
    _ptr_semente->exibirDetalhes();

    
}
void lote::exibirDetalhes(){
    for(int i=0;i<50;i++) std::cout<<"-";
    std::cout<<std::endl;

    std::cout<<"Dados do lote:\nID :"<<_id_lote<<"\nNome cientifico: "<<_nome_cientifico<<"\nGene introduzido: "<<
    _geneIntroduzido<<"\nMetodo de producao: "<<_metodo_producao<<"\nData de producao: "<<_data_producao<<"\nPais de origem: "<<
    _pais_origem<<"\nQuantidade disponivel no lote: "<<_quantidade_disponivel<<" kg\nPreco estimado: RS"<<_preco_estimado;
    

    for(int i=0;i<50;i++) std::cout<<"-";
    std::cout<<std::endl;
}



