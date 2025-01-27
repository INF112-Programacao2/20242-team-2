#include "classeLote.hpp"
#include "classeSemente.hpp"

Lote::Lote() : _ptr_semente(nullptr) {
    _statusDisponibilidade = "Estoque"; 
    _id_lote = 0;
    _id_sementeAssociada = 0;
    _nome_cientifico = "";
    _geneIntroduzido = "";
    _metodo_producao = "";
    _data_producao = "";
    _pais_origem = "";
    _quantidade_disponivel = 0;
    _preco_estimado = 0;
}
//KATRINE VAI TER QUE ADAPTAR
Lote::Lote(int id_lote){                         //aloca um lote que ja esta registrado. Utilizado para negociacao e relatorios        

    std::ifstream arquivoLotes ("Lotes.txt");
    if(!arquivoLotes)
        std::cerr<<"Erro ao abrir o arquivo Lotes.txt\n";

    std::string linha;
    for(int i=0;i<id_lote;i++){
        std::getline(arquivoLotes, linha);  //ignorando as n primeiras linhas do codigo
    }
    //----------------------------------------------
    try{
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

    if(arquivoLotes.fail())
        throw std::ios_base::failure("Erro na leitura do arquivoLotes.txt");
    
    //--------------------------------------------
    }catch(const std::exception& e){
        throw std::runtime_error("Erro ao processar dados do lote.");
    }
    arquivoLotes.close();

    try{
    _ptr_semente = new Semente(_id_sementeAssociada);
    }catch(const std::bad_alloc& e){
        throw std::runtime_error("Erro na alocacao de memoria para semente.");
    }

}
Lote::~Lote() {
    delete _ptr_semente;
}

/*  //mantendo para caso precise reutilizar a logica

void Lote::exibirDetalhesDaSemente(){
    if (_ptr_semente != nullptr) {
        _ptr_semente->exibirDetalhes();
    } else {
        throw std::runtime_error("Erro: Ponteiro para semente não alocado.");
    }
}
    
void Lote::exibirDetalhes(){
    try{
    for(int i=0;i<50;i++) std::cout<<"-";
    std::cout<<std::endl;

    std::cout<<"Dados do lote:\nID :"<<_id_lote<<"\nNome cientifico: "<<_nome_cientifico<<"\nGene introduzido: "<<
    _geneIntroduzido<<"\nMetodo de producao: "<<_metodo_producao<<"\nData de producao: "<<_data_producao<<"\nPais de origem: "<<
    _pais_origem<<"\nQuantidade disponivel no lote: "<<_quantidade_disponivel<<" kg\nPreco estimado: RS"<<_preco_estimado<<"\n";
    

    for(int i=0;i<50;i++) std::cout<<"-";
    std::cout<<std::endl;
    }catch(const std::exception& e){
        throw std::runtime_error("Erro ao exibir detalhes sobre o lote.");
    }
}
*/


int Lote::getIdLote() const {
    return _id_lote;
}
void Lote::setIdLote(int idLote) {
    _id_lote = idLote;
}

int Lote::getIdSementeAssociada() const {
    return _id_sementeAssociada;
}
void Lote::setIdSementeAssociada(int idSementeAssociada) {
    _id_sementeAssociada = idSementeAssociada;
}

std::string Lote::getNomeCientifico() const {
    return _nome_cientifico;
}
void Lote::setNomeCientifico(const std::string& nomeCientifico) {
    _nome_cientifico = nomeCientifico;
}

std::string Lote::getGeneIntroduzido() const {
    return _geneIntroduzido;
}
void Lote::setGeneIntroduzido(const std::string& geneIntroduzido) {
    _geneIntroduzido = geneIntroduzido;
}

std::string Lote::getMetodoProducao() const {
    return _metodo_producao;
}
void Lote::setMetodoProducao(const std::string& metodoProducao) {
    _metodo_producao = metodoProducao;
}

std::string Lote::getDataProducao() const {
    return _data_producao;
}
void Lote::setDataProducao(const std::string& dataProducao) {
    _data_producao = dataProducao;
}

std::string Lote::getPaisOrigem() const {
    return _pais_origem;
}
void Lote::setPaisOrigem(const std::string& paisOrigem) {
    _pais_origem = paisOrigem;
}

int Lote::getQuantidadeDisponivel() const {
    return _quantidade_disponivel;
}
void Lote::setQuantidadeDisponivel(int quantidadeDisponivel) {
    _quantidade_disponivel = quantidadeDisponivel;
}

float Lote::getPrecoEstimado() const {
    return _preco_estimado;
}
void Lote::setPrecoEstimado(float precoEstimado) {
    _preco_estimado = precoEstimado;
}

std::string Lote::getStatusDisponibilidade() const {
    return _statusDisponibilidade;
}
void Lote::setStatusDisponibilidade(const std::string& statusDisponibilidade) {
    _statusDisponibilidade = statusDisponibilidade;
}




