#include <iostream>
#include <string>
#include "classeSemente.hpp"

class area_plantio{
private:
    int _id_area;                     //identificador único da área.
    std::string _proprietario_nome;   //nome do proprietário da área.
    std::string _cnpj_proprietario;  //CNPJ do proprietário da área.
    float _tamanho;                  //tamanho da área em hectares.
    std::string _localizacao;        //localização (endereço ou coordenadas).
    std::string _tipo_solo;          //tipo de solo predominante na área.
    std::string _clima;              //clima predominante da região.
    std::string _status;             //status atual da área ("disponível", "em uso", "reservado").
    std::string _sementes_plantadas; //lista de IDs dos lotes de sementes plantadas na área.

public:
    area_plantio();      //construtor
    ~area_plantio();     //destrutor

    void exibirDetalhes();
    void registrarPlantio(int id_lote);               //registra o plantio de um lote de sementes na área.
    bool verificarDisponibilidade();                 //verifica se a área está disponível para plantio.
    float verificarCompatibilidade(Semente& semente); //retorna em porcentagem a compatibilidade de uma area com uma determinada semente.
    void liberarArea();
    void gerar_relatorioArea();
};