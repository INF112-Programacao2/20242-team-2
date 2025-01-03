#ifndef VENDEDOR_HPP
#define VENDEDOR_HPP

#include "Usuario.hpp"
#include "classeArea_Plantio.hpp"

class Vendedor: public Usuario{
private:
    std::vector<area_plantio> areas;
public:
    void registrarArea();
    void cadastrarNegociacao();
    void atualizarPrecoDaSemente();
    void visualizarRelatorio() override;
};
#endif
