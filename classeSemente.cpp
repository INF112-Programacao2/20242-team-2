#include "classeSemente.hpp"
#include <fstream>

Semente::Semente(){
    int _id_tipo=0;
    bool _produz_frutos=false;
    int _tempo_colheita=0;
    std::string _clima_ideal="";
    std::string _solo_ideal="";
    float _irrigacao_ideal=0;
    int _expectativaCrescimento=0; 
    float _expectativaTaxaDeGerminacao=0; 
    float _expectativaTaxaDeSobrevivencia=0; 
    float _expectativaIncidenciaPragasDoencas=0; 
}

Semente::Semente(int id){
    //____________________________________________//
         
    std::ifstream arquivoSementes ("Sementes.txt");
    if(!arquivoSementes)
        std::cerr<<"Erro ao abrir o arquivo Lotes.txt\n";

    std::string linha;
    for(int i=0;i<id;i++){
        std::getline(arquivoSementes, linha);  //ignorando as n primeiras linhas do codigo
    }

    //----------------------------------------------
    arquivoSementes>>_id_tipo;                              arquivoSementes.ignore();                                           
    getline(arquivoSementes, _clima_ideal, '+');
    getline(arquivoSementes, _solo_ideal, '+');                                        
    arquivoSementes >> _irrigacao_ideal;                                     
    arquivoSementes >> _expectativaIncidenciaPragasDoencas;                 
    arquivoSementes >> _expectativaTaxaDeSobrevivencia;                     
    arquivoSementes >> _expectativaTaxaDeGerminacao;                        
    arquivoSementes >> _expectativaCrescimento;  

    int check;
    arquivoSementes>>check;                                            
    if(check==0){
        _produz_frutos=false;
        _tempo_colheita=0;
    }
    if(check==1){
        _produz_frutos=true;
        arquivoSementes>>_tempo_colheita;
    }
    arquivoSementes.close();
}

Semente::~Semente(){}  //ainda sera desenvolvido

//--------------gets------------------//

int Semente::get_id_tipo(){   
    return _id_tipo;
}

int Semente::get_tempo_colheita(){
    return _tempo_colheita;
}
std::string Semente::get_clima_ideal(){
    return _clima_ideal;
}
std::string Semente::get_solo_ideal(){
    return _solo_ideal;
}
int Semente::get_expectativaCrescimento(){
    return _expectativaCrescimento;
}
float Semente::get_expectativaTaxaDeGerminacao(){
    return _expectativaTaxaDeGerminacao;
}
float Semente::get_expectativaTaxaDeSobrevivencia(){
    return _expectativaTaxaDeSobrevivencia;
}
float Semente::get_expectativaIncidenciaPragasDoencas(){
    return _expectativaIncidenciaPragasDoencas;
} 
float Semente::get_irrigacao_ideal(){
    return _irrigacao_ideal;
}
bool Semente::get_produz_frutos(){
    return _produz_frutos;
}

//-----------------------sets-----------------------//
void Semente::set_id_tipo(int id){   
    _id_tipo=id;
}
void Semente::set_tempo_colheita(int tempo){
    _tempo_colheita=tempo;
}
void Semente::set_clima_ideal(std::string clima){
    _clima_ideal=clima;
}
void Semente::set_solo_ideal(std::string solo){
    _solo_ideal=solo;
}
void Semente::set_expectativaCrescimento(float expectativa){
    _expectativaCrescimento=expectativa;
}
void Semente::set_expectativaTaxaDeGerminacao(float expectativa){
    _expectativaTaxaDeGerminacao=expectativa;
}
void Semente::set_expectativaTaxaDeSobrevivencia(float expectativa){
    _expectativaTaxaDeSobrevivencia=expectativa;
}
void Semente::set_expectativaIncidenciaPragasDoencas(float expectativa){
    _expectativaIncidenciaPragasDoencas=expectativa;
} 
void Semente::set_irrigacao_ideal(float irrigacao){
    _irrigacao_ideal=irrigacao;
}
void Semente::set_produz_frutos(bool produz_frutos){
    _produz_frutos=produz_frutos;
}
