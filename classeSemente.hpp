#ifndef CLASSE_SEMENTE_HPP
#define CLASSE_SEMENTE_HPP


#include <iostream>
#include <string>

class semente{

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

    semente();   //construtor (em teoria, todos os atributos serao definidos aqui)
    semente(int id);  //sobrecarga do construtor
    ~semente();  //destrutor

    void exibirDetalhes();   // Exibe todas as informações da semente
    
    //de inicio, nao faz sentido ter seteres dos atributos dessa classe

    //gets:
    int get_id_tipo();
    int get_tempo_colheita();
    std::string get_clima_ideal();
    std::string get_solo_ideal();
    int get_expectativaCrescimento();
    float get_expectativaTaxaDeGerminacao();
    float get_expectativaTaxaDeSobrevivencia();
    float get_expectativaIncidenciaPragasDoencas(); 


};

#endif
