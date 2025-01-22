#ifndef VENDEDOR_HPP
#define VENDEDOR_HPP

#include "Usuario.hpp"
#include "classeArea_Plantio.hpp"
#include "classeLote.hpp"
#include "classeNegociacao.hpp"
#include <vector>

class Vendedor: public Usuario {
private:
    std::vector<area_plantio> areas;

    //metodos para area de plantio
    void registrarArea();               //ok
    void listarAreasRegistradas();      //ok
    void liberarAreaRegistrada();       //ok
    void excluirArea();                 //ok       

    //metodos para negociacao
    void cadastrarNegociacao();         //ok       
    void atualizarPrecoDaSemente();     
    
};
#endif