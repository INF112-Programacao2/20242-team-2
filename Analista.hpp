#ifndef ANALISTA_HPP
#define ANALISTA_HPP

#include "Usuario.hpp"

class Analista: public Usuario{
private:    
    void registrarRelatorio();
    void atualizarStatusDaSemente();
    void visualizarRelatorio();
};
#endif
