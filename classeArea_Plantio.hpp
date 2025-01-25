#ifndef CLASSE_AREA_PLANTIO_HPP
#define CLASSE_AREA_PLANTIO_HPP

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "classeSemente.hpp"
#include "classeLote.hpp"

class AreaPlantio{
private:
    int _id_area;                     //identificador único da área.
    std::string _nome_proprietario;   //nome do proprietário da área.
    std::string _cnpj_proprietario;  //CNPJ do proprietário da área.
    float _tamanho;                  //tamanho da área em hectares.
    std::string _localizacao;        //localização (endereço ou coordenadas).
    std::string _tipo_solo;          //tipo de solo predominante na área.
    std::string _clima;              //clima predominante da região.
    std::string _status;             //status atual da área ("disponível", "em uso", "reservado").
    std::vector <int> _sementes_plantadas; //lista de IDs dos lotes de sementes plantadas na área.

public:
    AreaPlantio();      //construtor
    AreaPlantio(int id);
    ~AreaPlantio();     //destrutor

    void exibirArea();
    bool verificarDisponibilidade(int id_area);

    void set_id_area(int id);
    void set_nome_proprietario(std::string nome);
    void set_cnpj_proprietario(std::string cnpj);
    void set_tamanho(float tamanho);
    void set_localizacao(std::string localizacao);
    void set_tipo_solo(std::string tipo_solo);
    void set_clima(std::string clima);
    void set_status(std::string status);
    void adicionar_semente_plantada(int id_semente);

    int get_id_area();
    std::string get_nome_proprietario();
    std::string get_cnpj_proprietario();
    float get_tamanho();
    std::string get_localizacao();
    std::string get_tipo_solo();
    std::string get_clima();
    std::string get_status();
    std::vector<int> get_sementes_plantadas();
};

#endif