#ifndef VENDEDOR_HPP
#define VENDEDOR_HPP

#include "Usuario.hpp"
#include "classeArea_Plantio.hpp"
#include "classeLote.hpp"
#include "classeNegociacao.hpp"
#include <vector>

class Vendedor: public Usuario {
//private:
private:
    std::vector<AreaPlantio> areasRegistradas;
    void salvarArea(AreaPlantio area);                       //ok
    std::string getCurrentDate();                            //ok
    bool validarData(std::string& data);                    //ok
    void salvarNegociacao(Negociacao& neg);                 //ok
    void buscar_lotes_dessa_semente(int id_semente_busca);  //ok
    void registrar_relatorio_area(AreaPlantio area);
    void registrar_relatorio_neg(Negociacao neg);

    //metodos para area de plantio
    void registrarArea();                                   //ok
    void listarAreasRegistradas();                          //ok
    void liberarArea();                                     //ok
    void excluirArea();                                     //ok
    
    void registrarPlantio();                               //ok
    bool verificarDisponibilidade(int id_area);            //ok
    void compatibilidade_semente();                        //ok

    //metodos para negociacao
    void registrarNegociacao();                             //ok
    void listarNegociacoesRegistradas();                    //ok
    void finalizarNegociacao();                             //não esta atualizando o txt corretamente
    void excluirNegociacao();                               //ok
    void atualizarPrecoDaSemente();                         //ainda não implementado
    void consumirSementes(int id_lote,int quantidadeConsumida);  //ok

public:
    virtual void acessarInterface()override;                 //abre o menu dos vendedores
    virtual void gerarRelatorio();                          //julia esta desenvolvendo
    
};
#endif
