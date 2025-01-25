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
    void atualizarArquivo(std::vector<std::string>& linhas);
    void salvarArea(AreaPlantio area);  //ok
    std::string getCurrentDate();
    bool validarData(std::string& data);
    void salvarNegociacao(Negociacao& neg);
    void buscar_lotes_dessa_semente(int id_semente_busca);


public:
    //metodos para area de plantio
    void registrarArea();                                   //ok
    void listarAreasRegistradas();                          //ok
    void liberarArea();                                     //ok
    void excluirArea();                                     //ok
    
    void registrarPlantio();                               //registra o plantio de um lote de sementes na área.
    bool verificarDisponibilidade(int id_area);            //verifica se a área está disponível para plantio.
    void compatibilidade_semente();                

    //metodos para negociacao
    void registrarNegociacao();                             //em andamento
    void listarNegociacoesRegistradas();                    //ok
    void finalizarNegociacao();                             //ok
    void excluirNegociacao();                               //ok
    void atualizarPrecoDaSemente();   

    virtual int acessarInterface()override;                 //abre o menu dos vendedores
    virtual void gerarRelatorio(){};
    
};
#endif
