#include <iostream>
#include <string>
class semente{

    //atributos:

    int _id_lote; //identificador unico do lote de sementes
    int _id_tipo; //identificador de tipo de semente
    std::string _nome_cientifico; //nome cientifico da semente
    std::string _geneIntroduzido;
    std::string _metodo_producao; 
    std::string _data_producao;  //formato DD/MM/AAAA
    std::string _pais_origem;
    int _quantidade_disponivel;  //kg de sementes disponiveis no lote
    float _preco_estimado;
    std::string _statusDisponibilidade;  //em estoque,vendido ou plantado

    //metodos:

    semente::semente();  //construtor
    semente::~semente(); //destrutor

    void semente::exibirDetalhes();
    void semente::atualizaStatus();  //ou set_statusDisponibilidade
    void semente::atualizaPreco();  //ou set_preco
    float semente::verificarCompatibilidade(); //% devemos atribuir pesos
    void semente::consumirSementes(); //diminuir ou zerar a quantidade disponivel no lote
    void semente::adicionarSementes(); //aumentar o num de lotes ou num de sementes no lote
    void semente::gerarRelatorioSementes();
};