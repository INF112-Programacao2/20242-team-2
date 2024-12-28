#include <iostream>
#include <string>
class semente{

    //atributos:

    int _id_lote; //identificador unico do lote de sementes
    int _id_tipo; //identificador de tipo de semente
    std::string _nome_cientifico; //nome cientifico da semente
    std::string _geneIntroduzido;
    std::string _metodo_producao; 
    std::string _data_producao;  //formato DD/MM/AAAA
    std::string _pais_origem;
    int _quantidade_disponivel;  //kg de sementes disponiveis no lote
    float _preco_estimado;
    std::string _statusDisponibilidade;  //em estoque,vendido ou plantado

    //metodos:

 semente();   //construtor (em teoria, todos os atributos serao definidos aqui)
    ~semente();  //destrutor

    void exibirDetalhes();   // Exibe todas as informações da semente
    
    //de inicio, nao faz sentido ter seteres dos atributos dessa classe

    static int _contador_tipo; //controla a quantidade de tipos

    //gets:
    int get_tempo_colheita();
    std::string get_clima_ideal();
    std::string get_solo_ideal();
    std::string get_expectativaResistenciaPragas();
    int get_expectativaCrescimento();
    float get_expectativaTaxaDeGerminacao();
    float get_expectativaTaxaDeSobrevivencia();
    float get_expectativaIncidenciaPragasDoencas(); 

};
