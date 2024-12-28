#ifndef VENDEDOR_HPP
#define VENDEDOR_HPP

#include "Usuario.hpp"

class Vendedor: public Usuario{
private:    
    void registrarArea();
    void cadastrarNegociacao();
    void atualizarPrecoDaSemente();
};
#endif
