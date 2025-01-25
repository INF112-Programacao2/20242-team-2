#ifndef GESTOR_HPP
#define GESTOR_HPP

#include <vector>
#include "Usuario.hpp"
#include "classeSemente.hpp"
#include "classeLote.hpp"

class Gestor: public Usuario{
    private:
        std::vector<Semente> sementesRegistradas;       //vetor de semente registradas
        std::vector<Lote> lotesRegistrados;             //vetor de lotes registrados
    
       //metodos para sementes
        void registrarSemente();                        //atualizado
        void salvarSemente(Semente &semente);           //atualizado
        void excluirSemente();                          //atualizado
        void visualizar_semente_especifica();           //atualizado
    
        //metodos para lote
        void registrarLote();                           //atualizado
        void salvarLote(const Lote &lote);              //atualizado
        void excluirLote();                             //atualizado
        void visualizar_lote_especifico();              //atualizado
       
        // metodos para cadastro de usuarios
        void cadastrarUsuario();                        //ok
        void listarUsuarios();                          //ok
        void excluirUsuario();                          //ok

    public:
        virtual int acessarInterface()override;   //abre o menu dos gestores - falta funcao de ver relatorios

};
#endif
