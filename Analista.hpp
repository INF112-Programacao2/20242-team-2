#ifndef ANALISTA_HPP
#define ANALISTA_HPP

#include "Usuario.hpp"
#include "classeNegociacao.hpp"

class Analista: public Usuario{
public:
    void registrarRelatorio();
    void atualizarStatusDaSemente();
    void visualizarRelatorio();
};
#endif
