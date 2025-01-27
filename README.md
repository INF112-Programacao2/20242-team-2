# 🌱 Sistema de Gerenciamento Agrícola

## 🚀 Recursos
- **Gerenciamento de áreas de plantio**: Controle completo das suas áreas cultivadas
- **Controle de lotes de sementes**: Acompanhamento detalhado do seu estoque
- **Sistema de negociações**: Plataforma integrada para compra e venda
- **Interface com saída de voz**: Maior acessibilidade através de texto para fala
- **Relatórios detalhados**: Análise completa das operações

## 📦 Pré-requisitos
- Compilador C++ com suporte a C++11 ou superior
- Make
- eSpeak (para funcionalidade de texto para fala)

### 🛠️ Instalação do eSpeak

#### Linux (Ubuntu/Debian):
```bash
sudo apt-get install espeak
```

#### Windows:
1. Faça o download do instalador no site oficial do espeak
2. Siga o assistente de instalação

## 🔧 Instalação

1. Clone o repositório:
```bash
git clone https://github.com/seu-usuario/20242-team-2.git
cd 20242-team-2
```
2. Verifique a instalação do espeak:
```bash
make eSpeak
```
3. Compile o projeto:
```bash
make
```

## 🎮 Como usar
1. Execute o programa
 ```bash
  make makerun
```
3. Siga as instruções no terminal para acessar os recursos

## 🔄 Comandos úteis

Limpar arquivos de compilação:
```bash
make clean
```

## ⚠️ Resolução de Problemas

### Problemas comuns:

#### eSpeak não encontrado:
- Verifique se o eSpeak está instalado corretamente

#### Erro de compilação:
- Certifique-se de ter o g++ instalado
- Verifique se todas as dependências estão satisfeitas
