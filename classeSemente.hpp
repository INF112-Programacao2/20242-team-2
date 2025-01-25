#ifndef CLASSE_SEMENTE_HPP
#define CLASSE_SEMENTE_HPP


#include <iostream>
#include <string>

class Semente{

    private:
        //atributos:
        int _id_tipo; 
        bool _produz_frutos;
        int _tempo_colheita;  //indica de quanto em quanto tempo a planta da frutos(meses)
        std::string _clima_ideal;
        std::string _solo_ideal;
        float _irrigacao_ideal;
        int _expectativaCrescimento; //tempo estimado p/ maturacao da planta(dias)
        float _expectativaTaxaDeGerminacao; //%
        float _expectativaTaxaDeSobrevivencia; //%
        float _expectativaIncidenciaPragasDoencas; //Porcentagem de plantas afetadas por problemas fitossanitários

    public:

        //metodos:
    
        Semente();   //construtor (em teoria, todos os atributos serao definidos aqui)
        Semente(int id);  //sobrecarga do construtor
        ~Semente();  //destrutor
        
        //--------------gets------------//
        int get_id_tipo();
        int get_tempo_colheita();
        std::string get_clima_ideal();
        std::string get_solo_ideal();
        int get_expectativaCrescimento();
        float get_expectativaTaxaDeGerminacao();
        float get_expectativaTaxaDeSobrevivencia();
        float get_expectativaIncidenciaPragasDoencas(); 
        float get_irrigacao_ideal();
        bool get_produz_frutos();
    
        //--------sets------//
        void set_id_tipo(int id);  
        void set_tempo_colheita(int tempo); 
        void set_clima_ideal(std::string clima);
        void set_solo_ideal(std::string solo);
        void set_expectativaCrescimento(float expectativa);
        void set_expectativaTaxaDeGerminacao(float expectativa);
        void set_expectativaTaxaDeSobrevivencia(float expectativa);
        void set_expectativaIncidenciaPragasDoencas(float expectativa);
        void set_irrigacao_ideal(float irrigacao);
        void set_produz_frutos(bool produz_frutos);
};

#endif
