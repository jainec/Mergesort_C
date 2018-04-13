# Mergesort_C

Esta é uma implementação do algoritmo do Mergesort para resolver o seguinte problema:

> A empresa de automação portuária Poxim Tech está desenvolvendo um sistema para movimentação automatizada dos contêineres de carga de origem internacional no Porto de Sergipe para maximizar a eficiência da fiscalização aduaneira.

> Todos os contêineres possuem um cadastro eletrônico contendo informações sobre o código do contêiner,o CNPJ da empresa importadora e o peso líquido em quilos da carga.

> A inspeção dos contêineres é realizada sempre que existe alguma divergência entre as informações cadastradas, como o CNPJ informado ou a diferença percentual maior do que 10% no peso líquido.

> Na triagem dos contêineres são fiscalizados os contêineres com a seguinte ordem de prioridade:

1. Divergência de CNPJ

2. Maior diferença percentual de peso líquido

# Formato de arquivo de entrada

      [#n cont êineres cadastrados]
      [C ódigo 1] [CNPJ 1] [Peso 1]
      ···
      [C ódigo n] [CNPJ n] [Peso n]
      [#m cont êineres selecionados]
      [C ódigo 1] [CNPJ 1] [Peso 1]
      ···
      [C ódigo m] [CNPJ m] [Peso m]
      
**Exemplo:**

    6
    QOZJ7913219 34.699.211/9365-11 13822
    FCCU4584578 50.503.434/5731-28 16022
    KTAJ0603546 20.500.522/6013-58 25279
    ZYHU3978783 43.172.263/4442-14 24543
    IKQZ7582839 51.743.446/1183-18 12160
    HAAZ0273059 25.699.428/4746-79 16644
    5
    ZYHU3978783 43.172.263/4442-14 29765
    IKQZ7582839 51.743.446/1113-18 18501
    KTAJ0603546 20.500.522/6113-58 17842
    QOZJ7913219 34.699.211/9365-11 16722
    FCCU4584578 50.503.434/5731-28 16398

# Formato de arquivo de saída

> Sequência de fiscalização dos contêineres do navio, com a causa da triagem e seguindo a ordem de cadastramento dos contêineres

**Exemplo:**

    KTAJ0603546: 20.500.522/6013-58<->20.500.522/6113-58
    IKQZ7582839: 51.743.446/1183-18<->51.743.446/1113-18
    QOZJ7913219: 2900kg (21%)
    ZYHU3978783: 5222kg (21%)
