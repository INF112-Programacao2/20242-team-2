#ifndef CLASSE_NEGOCIACAO_HPP
#define CLASSE_NEGOCIACAO_HPP

#include <string>
#include "classeLote.hpp"
#include "classeArea_Plantio.hpp"

class Negociacao {
private:
    int _id_negociacao;
    int _id_lote;
    int _id_area;
    std::string _data_negociacao;
    float _valor_negociado;
    std::string _status;
    float _desconto;
    float _quantidade_semente_negociada;

public:
    Negociacao(); // Construtor
    
    // Getters
    int get_id_negociacao();
    int get_id_lote();
    int get_id_area();
    std::string get_data_negociacao();
    float get_valor_negociado();
    std::string get_status();
    float get_desconto();
    float get_quantidade_semente_negociada();

    // Setters
    void set_id_negociacao(int id);
    void set_id_lote(int id);
    void set_id_area(int id);
    void set_data_negociacao(const std::string& data);
    void set_valor_negociado(float valor);
    void set_status(std::string status);
    void set_desconto(float desconto);
    void set_quantidade_semente_negociada(float quantidade);

    // Métodos de exibição e gerenciamento
    void exibir_detalhes();
};

#endif