import pandas
LOG = open("log.txt", "w") # arquivo pra log

EPOCAS = 2
TX_APRENDIZAGEM = 0.5
LIMIAR_INICIAL = 0.3
PESO_INICIAL = [3.0,0.0,3.0]

pesos = PESO_INICIAL
limiar = LIMIAR_INICIAL

def carregar_dados(caminho_csv: str) -> list:
    df = pandas.read_csv(caminho_csv)
    dados = []
    for _, linha in df.iterrows():
        atributos = [linha['Atributo1'], linha['Atributo2'], linha['Atributo3']]
        classe = linha['Classe']
        dados.append((atributos, classe))
    return dados

DADOS_TREINAMENTO = carregar_dados("treinamento.csv")
DADOS_TESTE = carregar_dados("teste.csv")

def ativacao(entrada: list, pesos: list) -> int:
    u = entrada[0] * pesos[0] + entrada[1] * pesos[1] + entrada[2] * pesos[2] - limiar
    if u >= 0:
        return 1
    else:
        return 0

def pesos_corrigidos(entrada: list, pesos: list, valor_estimado: int, valor_esperado: int) -> list:
    w1 = pesos[0] + TX_APRENDIZAGEM * entrada[0] * (valor_esperado - valor_estimado)
    w2 = pesos[1] + TX_APRENDIZAGEM * entrada[1] * (valor_esperado - valor_estimado)
    w3 = pesos[2] + TX_APRENDIZAGEM * entrada[2] * (valor_esperado - valor_estimado)
    nv_limiar = limiar + TX_APRENDIZAGEM * (valor_esperado - valor_estimado)
    return [w1,w2,w3,nv_limiar]

for epoca in range(EPOCAS):
    print(f"### ÉPOCA {epoca + 1} ###", file=LOG)
    for entrada, esperado in DADOS_TREINAMENTO:
        estimado = ativacao(entrada, pesos)
        print(f"\nEntrada: {entrada}, Esperado: {esperado}, Estimado: {estimado}", file=LOG)

        if estimado != esperado:
            print("Erro - ajuste de pesos vai acontecer", file=LOG)
            print(f"Pesos antes: {pesos}, Limiar: {limiar}", file=LOG)

            retorno = pesos_corrigidos(entrada, pesos, estimado, esperado)
            pesos[0] = retorno[0]
            pesos[1] = retorno[1]
            pesos[2] = retorno[2]
            limiar = retorno[3]

            print(f"Pesos depois: {pesos}, Limiar: {limiar}", file=LOG)

print("\nResultados no conjunto de teste:", file=LOG)
for entrada, esperado in DADOS_TESTE:
    estimado = ativacao(entrada, pesos)
    print(f"Entrada: {entrada}, Esperado: {esperado}, Estimado: {estimado}", file=LOG)

print(f"\nPesos finais: {pesos}, Limiar final: {limiar}", file=LOG)
LOG.close()