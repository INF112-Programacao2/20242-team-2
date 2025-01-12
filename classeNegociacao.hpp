#ifndef CLASSE_NEGOCIACAO_HPP
#define CLASSE_NEGOCIACAO_HPP

#include <string>
#include "classeLote.hpp"
#include "classeSemente.hpp"
#include "classeArea_Plantio.hpp"

class negociacao {
private:
    int _id_negociacao;
    lote* _lote;
    area_plantio* _area;
    std::string _data_negociacao;
    float _valor_negociado;
    std::string _status;

    std::string getCurrentDate();
    bool validarData(const std::string& data);
    void atualizarStatusArquivo();
    
public:
    negociacao();
    void registrarNegociacao(lote* lote, area_plantio* area, float valor, std::string data);
    void finalizarNegociacao();
    void cancelarNegociacao();
    int get_id_lote_associado();
    float calcularDesconto();
    void gerar_relatorioNegociacoes();
};

#endif