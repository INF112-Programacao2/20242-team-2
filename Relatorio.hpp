#ifndef RELATORIO_HPP
#define RELATORIO_HPP

#include <iostream>

class Relatorio{

    private:
        
        int _id_relatorio;
        int _id_semente;
        int _tempo_colheita;  //indica de quanto em quanto tempo a planta da frutos(meses)
        float _irrigacao;
        int _CrescimentoVerificado; //tempo estimado p/ maturacao da planta(dias)
        float _GerminacaoVerificado; //%
        float _SobrevivenciaVerificado; //%
        float _PragasDoencasVerificado; //Porcentagem de plantas afetadas por problemas fitossanitários

    public:

        Relatorio();
        ~Relatorio();

        void set_id_relatorio(int id);
        int get_id_relatorio();

        void set_id_semente(int id);
        int get_id_semente();

        void set_tempo_colheita(int tempo);
        int get_tempo_colheita();

        void set_irrigacao(float irrigacao);
        float get_irrigacao();

        void set_crescimento(int crescimento);
        int get_crescimento();

        void set_geminacao(float germinacao);
        float get_germinacao();

        void set_sobrevivencia(float sobrevivencia);
        float get_sobrevivencia();

        void set_pragasDoencas(float pragasDoencas);
        float get_pragasDoencas();

};


#endif