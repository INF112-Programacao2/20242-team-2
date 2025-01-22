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

void Semente::registrarNovaSemente(){
     //____________________________________________//
         
    std::fstream arquivoSementes ("Sementes.txt");
    if(!arquivoSementes)
        std::cerr<<"Erro ao abrir o arquivo Lotes.txt\n";

        //identificar qual o id do proximo lote:
    arquivoSementes>>_id_tipo; _id_tipo++;         //le o contador de tipos e calcula o ID

    //____________________________________________//  
    
    char resp;
    std::cout<<"Produz frutos? (S/N) ";   std::cin>>resp;
    if(resp=='s'||resp=='s'){
        _produz_frutos=true;
        std::cout<<"Tempo de colheita (meses): ";     
        std::cin>>_tempo_colheita; 

        if (std::cin.fail()) {
            throw std::invalid_argument("Entrada inválida para o tempo de colheita.");
        }
        std::cin.ignore();          
    }
    else if(resp=='n'||resp=='N'){
        _produz_frutos=false;
        _tempo_colheita=0;   //nulo ou 0?
    }
    else{
        throw std::invalid_argument("Resposta inválida para 'Produz frutos?'");
    }

    std::cout << "Clima ideal: ";                                             std::getline(std::cin, _clima_ideal);  
    std::cout << "Solo ideal: ";                                              std::getline(std::cin, _solo_ideal);     
    std::cout << "Irrigacao ideal: (cmˆ3 agua/cmˆ3 solo)";                    std::cin >> _irrigacao_ideal;
    if (std::cin.fail()||_irrigacao_ideal<0) 
        throw std::invalid_argument("Entrada inválida para irrigação ideal.");
    
    std::cin.ignore();
    std::cout << "Taxa de germinacao (%): ";                                  std::cin >> _expectativaTaxaDeGerminacao;
    if (std::cin.fail()||_expectativaTaxaDeGerminacao>100||_expectativaTaxaDeGerminacao<0) 
        throw std::invalid_argument("Entrada inválida para Taxa de germinacao.");
    
    std::cin.ignore();
    std::cout << "Taxa de sobrevivencia (%): ";                               std::cin >> _expectativaTaxaDeSobrevivencia;
    if (std::cin.fail()||_expectativaTaxaDeSobrevivencia>100||_expectativaTaxaDeSobrevivencia<0) 
        throw std::invalid_argument("Entrada inválida para Taca de sobrevivencia.");
    
    std::cin.ignore();
    std::cout << "Incidencia de pragas/doencas (%): ";                        std::cin >> _expectativaIncidenciaPragasDoencas;
    if (std::cin.fail()||_expectativaIncidenciaPragasDoencas>100||_expectativaIncidenciaPragasDoencas<0) 
        throw std::invalid_argument("Entrada inválida para indicidencia de pragas/doencas.");

    std::cin.ignore();                          
    std::cout << "Tempo estimado de maturacao (dias): ";                       std::cin >> _expectativaCrescimento;
    if (std::cin.fail()||_expectativaCrescimento<0) 
        throw std::invalid_argument("Entrada inválida para tempo estimado de maturacao");

    arquivoSementes.seekp(0,std::ios::end);
    arquivoSementes<<_id_tipo<<"+"<<_solo_ideal<<"+"<<_clima_ideal<<"+"<<_irrigacao_ideal<<"+"<<_expectativaIncidenciaPragasDoencas<<"+"<<
        _expectativaTaxaDeSobrevivencia<<"+"<<_expectativaTaxaDeGerminacao<<"+"<<_expectativaCrescimento<<"+";
    if(_produz_frutos){
        arquivoSementes<<1<<"+"<<_tempo_colheita<<std::endl;
    }
    else{
        arquivoSementes<<0<<"+"<<0<<std::endl;
    }
    
    arquivoSementes.seekg(0,std::ios::beg);        //leva o apontador até a posicao do contador do arquivo
    arquivoSementes<<_id_tipo <<std::endl;                    //atualiza o contador
    
    arquivoSementes.close();

}

void Semente::exibirDetalhes(){
    //____________________________________________//
         
    std::fstream arquivoSementes ("Sementes.txt");
    if(!arquivoSementes)
        std::cerr<<"Erro ao abrir o arquivo Lotes.txt\n";

    std::string linha;
    for(int i=0;i<_id_tipo;i++){
        std::getline(arquivoSementes, linha);  //ignorando as n primeiras linhas do codigo
        if (arquivoSementes.fail()) {
            throw std::ios_base::failure("Erro ao ler o arquivo.");
        }
    }

    //----------------------------------------------
    arquivoSementes>>_id_tipo;
    if (arquivoSementes.fail()) 
            throw std::ios_base::failure("Erro ao ler o ID da semente.");
                                                        
    arquivoSementes.ignore();                                           
    getline(arquivoSementes, _clima_ideal, '+');
    if (arquivoSementes.fail()) {
            throw std::ios_base::failure("Erro ao ler o clima ideal");
        }
    getline(arquivoSementes, _solo_ideal, '+'); 
    if (arquivoSementes.fail()) {
            throw std::ios_base::failure("Erro ao ler o solo ideal.");
        }                                      
    arquivoSementes >> _irrigacao_ideal; 
    if (arquivoSementes.fail()) {
            throw std::ios_base::failure("Erro ao ler a irrigacao ideal.");
        }                                    
    arquivoSementes >> _expectativaIncidenciaPragasDoencas;
    if (arquivoSementes.fail()) {
            throw std::ios_base::failure("Erro ao ler a expectativa de incidencia de pragas ou doencas.");
        }                 
    arquivoSementes >> _expectativaTaxaDeSobrevivencia;  
    if (arquivoSementes.fail()) {
            throw std::ios_base::failure("Erro ao ler a expectativa de taxa de sobrevivencia.");
        }                   
    arquivoSementes >> _expectativaTaxaDeGerminacao; 
    if (arquivoSementes.fail()) {
            throw std::ios_base::failure("Erro ao ler a expectativa de taxa de germinacao");
        }                       
    arquivoSementes >> _expectativaCrescimento;  
    if (arquivoSementes.fail()) {
            throw std::ios_base::failure("Erro ao ler a expectativa de crescimento.");
        }                  
    int check;
    arquivoSementes>>check;
    if(check==1)
        _produz_frutos=true;
    else
        _produz_frutos=false;
    arquivoSementes.ignore(1);
    arquivoSementes>>_tempo_colheita;

    arquivoSementes.close();
    //------------------------------------------------
    for(int i=0;i<50;i++) std::cout<<"-";
    std::cout<<std::endl;

    std::cout<<"Dados da semente:\nID :"<<_id_tipo<<"\nSolo ideal: "<<_solo_ideal<<"\nClima ideal: "<<
    _clima_ideal<<"\nIrrigacao ideal: "<<_irrigacao_ideal<<" cmˆ3 agua/cmˆ3 solo\nTaxa de germinacao: "<<
    _expectativaTaxaDeGerminacao<<" %\nTaxa de sobrevivencia: "<<_expectativaTaxaDeSobrevivencia<<" %\nTaxa de crescimento: "<<
    _expectativaCrescimento<<" %\nTaxa de incidencia de Pragas e doencas: "<<_expectativaIncidenciaPragasDoencas<<" %\n";
    if(_produz_frutos)
        std::cout<<"Produz frutos com um tempo de colheita de: "<<_tempo_colheita<<" meses\n";

    for(int i=0;i<50;i++) std::cout<<"-";
    std::cout<<std::endl;
}



int Semente::get_id_tipo(){   //ate entao, o unico get que esta sendo usado é esse
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