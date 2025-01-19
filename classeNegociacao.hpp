#ifndef CLASSE_NEGOCIACAO_HPP
#define CLASSE_NEGOCIACAO_HPP

#include <string>
#include "classeLote.hpp"
#include "classeSemente.hpp"
#include "classeArea_Plantio.hpp"

class negociacao {
private:
    // adicionar atributo como a quantidade de sementes a serem negociadas(kg)
    int _id_negociacao;
    lote* _lote;
    area_plantio* _area;
    std::string _data_negociacao;
    float _valor_negociado;
    std::string _status;

    float _quantidade_semente_negociada;

    std::string getCurrentDate();
    bool validarData(const std::string& data);
    void atualizarStatusArquivo(int id);
    
public:
    negociacao();
    void registrarNegociacao(lote* lote, area_plantio* area, float quantidade_semente_negociada, std::string data);
    void finalizarNegociacao();
    void cancelarNegociacao();
    int get_id_lote_associado();
    float calcularDesconto();
    void gerar_relatorioNegociacao();
};

#endif