# Gestão de Frotas e Manutenção de Fragatas

**Projeto desenvolvido em linguagem C para gerenciamento de uma frota de fragatas espaciais, com cadastro, consulta, relatórios e persistência de dados.**

Atividade acadêmica desenvolvida por **Vitor Reis** e **Miguel Zimmermann**, como parte dos estudos de programação na FATEC.

## Sobre o projeto

O sistema de Gestão de Frotas e Manutenção de Fragatas foi desenvolvido com o objetivo de aplicar conceitos fundamentais da linguagem C na construção de uma aplicação de gerenciamento de dados.

A aplicação permite administrar uma frota de naves espaciais por meio de uma interface de terminal, armazenando informações como código de identificação, modelo, ano de fabricação, distância percorrida e custo de revisão.

O projeto utiliza **estruturas (`struct`), ponteiros, alocação dinâmica de memória, modularização e manipulação de arquivos**, permitindo que os dados sejam preservados entre execuções.

## Funcionalidades

O sistema disponibiliza as seguintes operações:

- **Cadastro de fragatas:** registra novas naves, validando os dados fornecidos e impedindo códigos duplicados.
- **Busca por código:** localiza uma fragata a partir de seu identificador único.
- **Listagem da frota:** apresenta todas as fragatas cadastradas e suas informações.
- **Edição de fragatas:** permite atualizar modelo, ano de fabricação, distância percorrida e valor da revisão, mantendo o código identificador.
- **Exclusão de fragatas:** remove da frota uma fragata localizada por seu código e libera a memória correspondente.
- **Relatório gerencial:** apresenta o total de fragatas, os custos total e médio das revisões, o ano e a idade média da frota, a fragata que percorreu a maior distância e a que possui a revisão mais cara.
- **Persistência de dados:** carrega automaticamente os registros existentes e permite salvá-los em arquivo.
- **Gerenciamento de memória:** utiliza alocação dinâmica e libera a memória utilizada ao encerrar a aplicação.

O sistema suporta até **100 fragatas cadastradas**.

## Tecnologias utilizadas

- **Linguagem C (C11):** implementação das funcionalidades e estruturas de dados.
- **CMake:** configuração e automatização da compilação.
- **Biblioteca padrão de C:** entrada e saída, manipulação de strings, arquivos e memória.
- **CLion:** ambiente de desenvolvimento utilizado no projeto.

## Estrutura do projeto

```text
projeto-vitor-reis-e-miguel-zimmermann/
│
├── main.c           # Menu principal e fluxo da aplicação
├── fragata.c        # Implementação das operações da frota
├── fragata.h        # Estruturas, constantes e protótipos
├── fragatas.txt     # Armazenamento dos registros
├── CMakeLists.txt    # Configuração de compilação
└── README.md         # Documentação do projeto
```

### Organização do código

O projeto foi dividido em módulos para facilitar a leitura, manutenção e reutilização de funções.

**`main.c`**

Responsável pela inicialização do sistema, apresentação do menu interativo, processamento das opções selecionadas e encerramento da aplicação.

**`fragata.h`**

Contém a definição da estrutura `Fragata`, o limite de registros, os tipos de dados e as declarações das funções utilizadas pelo sistema.

**`fragata.c`**

Implementa as operações de cadastro, busca, edição, exclusão, listagem, geração de relatórios, leitura e gravação de arquivos, além do gerenciamento de memória.

## Como executar

### Pré-requisitos

É necessário possuir um compilador C compatível com C11, como o GCC. Opcionalmente, o projeto pode ser compilado utilizando o CMake.

### 1. Clonar o repositório

```bash
git clone https://github.com/znoppa/projeto-vitor-reis-e-miguel-zimmermann.git

cd projeto-vitor-reis-e-miguel-zimmermann
```

### 2. Compilar com GCC

```bash
gcc -std=c11 main.c fragata.c -o frota
```

### 3. Executar

No Linux ou macOS:

```bash
./frota
```

No Windows (PowerShell):

```powershell
.\frota.exe
```

### Alternativa: compilação com CMake

O projeto também disponibiliza um arquivo `CMakeLists.txt`, configurado para CMake 4.3 ou superior.

```bash
cmake -S . -B build
cmake --build build
```

O executável gerado terá o nome `ProjetoFragatas`. Seu caminho dependerá do sistema operacional e do gerador de compilação utilizado.

## Utilização

Ao iniciar o programa, será apresentado o seguinte menu:

```text
--=-=-=-- Gestao de Frota e Manutencao de Fragatas --=-=-=--

1. Cadastrar fragata
2. Buscar fragata por codigo
3. Listar fragatas
4. Exibir relatorio
5. Editar fragata
6. Excluir fragata
7. Salvar e sair

Escolha uma opcao:
```

Para cadastrar uma fragata, selecione a opção `1` e preencha os campos solicitados.

Exemplo de cadastro:

```text
Codigo: FRG-001
Modelo: Exploradora Atlas
Ano de fabricacao: 2480
Distancia percorrida em anos-luz: 12500.5
Valor da revisao em unidades: 3200
```

Após o cadastro, a fragata poderá ser consultada, editada, excluída, listada e considerada nos relatórios. A edição e a exclusão utilizam o código da fragata para localizar o registro.

A opção `7` salva os registros no arquivo `fragatas.txt` e encerra a aplicação quando a gravação é concluída.

## Armazenamento dos dados

Os registros são armazenados localmente em um arquivo de texto denominado `fragatas.txt`.

Cada linha contém os dados de uma fragata, separados por ponto e vírgula (`;`), seguindo o formato:

```text
codigo;modelo;ano_fabricacao;distancia_percorrida;valor_revisao
```

Exemplo:

```text
FRG-001;Exploradora Atlas;2480;12500.5;3200
FRG-002;Nave de Suporte Orion;2482;8700;1800
```

Durante a inicialização, o sistema procura o arquivo no diretório de execução e carrega os registros válidos. Ao salvar, os dados da frota são gravados novamente nesse arquivo.

Não é necessário utilizar um banco de dados externo.

## Conceitos aplicados

Durante o desenvolvimento, foram utilizados conceitos importantes da programação em C:

- **Estruturas de dados:** representação das informações das fragatas por meio de `struct`.
- **Vetores de ponteiros:** armazenamento de referências para as fragatas cadastradas.
- **Alocação dinâmica:** utilização de `malloc()` e `free()` para gerenciar a memória.
- **Modularização:** separação das responsabilidades entre arquivos `.c` e `.h`.
- **Manipulação de arquivos:** leitura e gravação com `fopen()`, `fgets()`, `fprintf()` e `fclose()`.
- **Validação de entradas:** verificação dos dados informados e prevenção de cadastros duplicados.
- **Atualização e exclusão de registros:** alteração de estruturas existentes e liberação individual de memória com `free()`.
- **Estruturas de controle:** utilização de condicionais, laços e menus interativos.

## Limitações

A versão atual possui algumas limitações:

- A frota está limitada a 100 registros.
- O código identificador de uma fragata não pode ser alterado durante a edição.
- O cálculo da idade média considera o ano atual do sistema como 2500.
- O armazenamento é realizado exclusivamente em arquivo de texto.
- A interação com o usuário ocorre por meio do terminal.

## Desenvolvedores

**Vitor Reis** — Desenvolvimento do projeto.

**Miguel Zimmermann Martins Silva** — Desenvolvimento do projeto.

Projeto
