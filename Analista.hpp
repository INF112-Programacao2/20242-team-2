#ifndef ANALISTA_HPP
#define ANALISTA_HPP

#include "Usuario.hpp"
#include "classeNegociacao.hpp"
#include "Relatorio.hpp"

class Analista: public Usuario{
    public:

        Analista();
        ~Analista() override;

        void atualizarStatusDoLote();
        void visualizarRelatorio();
        virtual void acessarInterface();

    private:
        void elaborarRelatorio();
        void registrarRelatorio(Relatorio &relatorio);
        virtual void gerarRelatorio(); 

    };
#endif
