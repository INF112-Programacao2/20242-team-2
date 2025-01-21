#ifndef ANALISTA_HPP
#define ANALISTA_HPP

#include "Usuario.hpp"

class Analista: public Usuario{
public:
    void registrarRelatorio();
    void atualizarStatusDaSemente();
};
#endif
