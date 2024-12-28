#ifndef GESTOR_HPP
#define GESTOR_HPP

#include "Usuario.hpp"

class Gestor: public Usuario{
private:    
    void registrarSemente();
    void registrarLote();
};
#endif