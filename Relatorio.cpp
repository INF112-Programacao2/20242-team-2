#include "Relatorio.hpp"

Relatorio::Relatorio() 
    : _id_semente(0), _tempo_colheita(0), _irrigacao(0.0), 
      _CrescimentoVerificado(0), _GerminacaoVerificado(0.0), _SobrevivenciaVerificado(0.0),
       _PragasDoencasVerificado(0.0) {}

// Destruidor
Relatorio::~Relatorio() {
    // Destruidor não faz nada específico aqui (sem alocação dinâmica)
}

// Métodos Setters

void Relatorio::set_id_relatorio(int id){
    _id_relatorio=id;
}
void Relatorio::set_id_semente(int id) {
    _id_semente = id;
}

void Relatorio::set_tempo_colheita(int tempo) {
    _tempo_colheita = tempo;
}

void Relatorio::set_irrigacao(float irrigacao) {
    this->_irrigacao = irrigacao;
}

void Relatorio::set_crescimento(int crescimento) {
    this->_CrescimentoVerificado = crescimento;
}

void Relatorio::set_geminacao(float germinacao) {
    this->_GerminacaoVerificado = germinacao;
}

void Relatorio::set_sobrevivencia(float sobrevivencia) {
    this->_SobrevivenciaVerificado = sobrevivencia;
}

void Relatorio::set_pragasDoencas(float pragasDoencas) {
    this->_PragasDoencasVerificado = pragasDoencas;
}

// Métodos Getters
int Relatorio::get_id_relatorio(){
    return _id_relatorio;
}
int Relatorio::get_id_semente() {
    return _id_semente;
}

int Relatorio::get_tempo_colheita() {
    return _tempo_colheita;
}

float Relatorio::get_irrigacao() {
    return _irrigacao;
}

int Relatorio::get_crescimento() {
    return _CrescimentoVerificado;
}

float Relatorio::get_germinacao() {
    return _GerminacaoVerificado;
}

float Relatorio::get_sobrevivencia() {
    return _SobrevivenciaVerificado;
}

float Relatorio::get_pragasDoencas() {
    return _PragasDoencasVerificado;
}