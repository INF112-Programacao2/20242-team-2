#include "classeLote.hpp"
#include "classeSemente.hpp"

lote::lote(){

    _statusDisponibilidade="estoque"; 
    int _id_lote=NULL;
    semente* _ptr_semente=nullptr;
    int _id_sementeAssociada=NULL;
    std::string _nome_cientifico="";
    std::string _geneIntroduzido="";
    std::string _metodo_producao="";
    std::string _data_producao="";
    std::string _pais_origem="";
    int _quantidade_disponivel=NULL;
    float _preco_estimado=NULL;
    std::string _statusDisponibilidade="";

    //____________________________________________//
}
lote::lote(int id_lote){                         //aloca um lote que ja esta registrado. Utilizado para negociacao e relatorios        

    std::ifstream arquivoLotes ("Lotes.txt");
    if(!arquivoLotes)
        std::cerr<<"Erro ao abrir o arquivo Lotes.txt\n";

    std::string linha;
    for(int i=0;i<id_lote;i++){
        std::getline(arquivoLotes, linha);  //ignorando as n primeiras linhas do codigo
    }
    //----------------------------------------------
    arquivoLotes>>_id_sementeAssociada;                    arquivoLotes.ignore();
    arquivoLotes>>_id_lote;                                arquivoLotes.ignore();
    std::getline(arquivoLotes,_statusDisponibilidade,'+');
    std::getline(arquivoLotes,_nome_cientifico,'+');
    std::getline(arquivoLotes,_geneIntroduzido,'+');
    std::getline(arquivoLotes,_metodo_producao,'+');
    std::getline(arquivoLotes,_data_producao,'+');
    std::getline(arquivoLotes,_pais_origem,'+');
    arquivoLotes>>_quantidade_disponivel;                  arquivoLotes.ignore();
    arquivoLotes>>_preco_estimado;
    //--------------------------------------------

    arquivoLotes.close();

    _ptr_semente=new semente(_id_sementeAssociada);

}
lote::~lote(){
    delete _ptr_semente;
}

void lote::registrarNovoLote(int id_semente){
         
    std::fstream arquivoLotes ("Lotes.txt");
    if(!arquivoLotes)
        std::cerr<<"Erro ao abrir o arquivo Lotes.txt\n";

    int contadorDeLotes;
    //identificar qual o id do proximo lote:
    arquivoLotes>>_id_lote; _id_lote++;         //le o contador de id e calcula o ID
    arquivoLotes>>contadorDeLotes; contadorDeLotes++;     //le o contador do arquivo e adiciona
 
    //____________________________________________//
    _ptr_semente=new semente(id_semente);
    _id_sementeAssociada=_ptr_semente->get_id_tipo();
    
    std::cin.ignore();
    
    std::cout<<"Nome cientifico: ";                  std::getline(std::cin,_nome_cientifico);                 
    std::cout<<"Gene introduzido: ";                 std::getline(std::cin,_geneIntroduzido);
    std::cout<<"Metodo de producao: ";               std::getline(std::cin,_metodo_producao);
    std::cout<<"Data de producao:  DD/MM/AA ";       std::getline(std::cin,_data_producao);
    std::cout<<"País de origem: ";                   std::getline(std::cin,_pais_origem);
    std::cout<<"Quantidade disponível no lote: ";    std::cin>>_quantidade_disponivel;
    std::cout<<"Preco estimado:  ";                  std::cin>>_preco_estimado;
    
    arquivoLotes.seekp(0, std::ios::end);
    arquivoLotes<<_id_sementeAssociada<<"+"<<_id_lote<<"+"<<_statusDisponibilidade<<"+"<<_nome_cientifico<<
    "+"<<_geneIntroduzido<<"+"<<_metodo_producao<<"+"<<_data_producao<<"+"<<_pais_origem<<"+"<<
    _quantidade_disponivel<<"+"<<_preco_estimado<<"\n";
    
    arquivoLotes.seekg(0,std::ios::beg);        //leva o apontador até a posicao do contador do arquivo
    arquivoLotes<<_id_lote <<" "<<contadorDeLotes<<std::endl;                    //atualiza o contador

    arquivoLotes.close();
}

void lote::exibirDetalhesDaSemente(){
    _ptr_semente->exibirDetalhes();
    
}
void lote::exibirDetalhes(){
    for(int i=0;i<50;i++) std::cout<<"-";
    std::cout<<std::endl;

    std::cout<<"Dados do lote:\nID :"<<_id_lote<<"\nNome cientifico: "<<_nome_cientifico<<"\nGene introduzido: "<<
    _geneIntroduzido<<"\nMetodo de producao: "<<_metodo_producao<<"\nData de producao: "<<_data_producao<<"\nPais de origem: "<<
    _pais_origem<<"\nQuantidade disponivel no lote: "<<_quantidade_disponivel<<" kg\nPreco estimado: RS"<<_preco_estimado<<"\n";
    

    for(int i=0;i<50;i++) std::cout<<"-";
    std::cout<<std::endl;
}

void lote::consumirSementes(int id_lote,int quantidadeConsumida){
   
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
            arquivoLotes>>_id_sementeAssociada;                       arquivoLotes.ignore();
            arquivoLotes>>_id_lote;                                   arquivoLotes.ignore();                  
            getline(arquivoLotes, _statusDisponibilidade, '+');
            getline(arquivoLotes, _nome_cientifico, '+');     
            getline(arquivoLotes, _geneIntroduzido, '+');
            getline(arquivoLotes, _metodo_producao, '+');                                        
            getline(arquivoLotes, _data_producao, '+');
            getline(arquivoLotes, _pais_origem, '+');                                        
            arquivoLotes>>_quantidade_disponivel;                      arquivoLotes.ignore(); 
            arquivoLotes>>_preco_estimado;                            arquivoLotes.ignore();
        } else {
            std::getline(arquivoLotes, linha[i]);
        }
    }             
    
    //alterando o saldo de sementes: 
 
    if(_quantidade_disponivel-quantidadeConsumida<0){
        std::cout<<"Quantidade indisponivel!\n";
        delete[] linha;
        return;
    } 
    else if(_quantidade_disponivel-quantidadeConsumida==0){
        _quantidade_disponivel=0;
        std::cout<<"Quantidade disponível!\n";
        _statusDisponibilidade="vendido";
    }
    else{
        _quantidade_disponivel-=quantidadeConsumida;
    }
    arquivoLotes.close();

    //----------escrevendo o arquivo atualizado------//
    std::ofstream arquivoLotesON("Lotes.txt");
    arquivoLotesON<<controleDeID<<" "<<contador_lotes<<std::endl;
    for(int i=0;i<contador_lotes;i++){
        if(i+1==id_lote){
            arquivoLotesON<<_id_sementeAssociada<<"+"<<id_lote<<"+"<<_statusDisponibilidade<<"+"<<_nome_cientifico
            <<"+"<<_geneIntroduzido<<"+"<<_metodo_producao<<"+"<<_data_producao<<"+"<<_pais_origem<<"+"<<
            _quantidade_disponivel<<"+"<<_preco_estimado<<std::endl;
        }
        else
            arquivoLotesON<<linha[i]<<std::endl;  //escrevendo linhas nao alteradas
    }
    delete[] linha;
    arquivoLotesON.close();
}

float lote::get_preco_estimado(){
    return _preco_estimado;
}

int lote::get_id_lote(){
    return _id_lote;
}


