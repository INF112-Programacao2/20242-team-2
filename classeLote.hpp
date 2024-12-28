#ifndef CLASSE_LOTE_HPP
#define CLASSE_LOTE_HPP


#include <iostream>
#include <string>
#include "classeSemente.hpp"
#include "classeLote.hpp"
#include <fstream>

class lote{

    private:


    //atributos:

    int _id_lote; //identificador unico do lote de sementes
    semente* _ptr_semente;  //apontador para o objeto semente correspondente
    
    //int _id_tipo; identificador de tipo de semente (ainda nao visualizei como vai funcionar)
    std::string _nome_cientifico; //nome cientifico da semente
    std::string _geneIntroduzido;
    std::string _metodo_producao; 
    std::string _data_producao;  //formato DD/MM/AAAA
    std::string _pais_origem;
    int _quantidade_disponivel;  //kg de sementes disponiveis no lote
    float _preco_estimado;
    std::string _statusDisponibilidade;  //em estoque,vendido ou plantado

    static int _contador_lote; //controla a quantidade de lotes
    static int _contador_tipo; //controla a quantidade de tipos

    public: //sujeito a mudanca

    //metodos:

    lote();  //construtor
    ~lote(); //destrutor

    void exibirDetalhes();
    void set_statusDisponibilidade();  //ou set_statusDisponibilidade
    void set_preco_estimado();  //ou set_preco
    float verificarCompatibilidade(); //% devemos atribuir pesos
    void consumirSementes(); //diminuir ou zerar a quantidade disponivel no lote
    void adicionarSementes(); //aumentar o num de lotes ou num de sementes no lote
    void gerarRelatorioSementes();  //polimorfismo?

};

#endif