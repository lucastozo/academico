# Lucas Tozo Monção

''' formato do arquivo automato.txt - Nota: o nome dos estados devem ser NÚMEROS NATURAIS NÃO NULOS (1, 2, 3, ...)
<qtd_estados>
<estado_inicial>
<estado_final_1>,<estado_final_2>,<estado_final_n>
<alfabeto_simbolo_1>,<alfabeto_simbolo_2>,<alfabeto_simbolo_n>
<{estado_comeco},{simbolo},{estado_alvo}_1>
<{estado_comeco},{simbolo},{estado_alvo}_2>
<{estado_comeco},{simbolo},{estado_alvo}_n>
<palavra_1>,<palavra_2>,<palavra_n>
'''

''' automato.txt usado para demonstracao:
4
1
4
a,b
1,a,2
1,b,3
2,a,2
2,b,4
3,a,4
3,b,3
4,a,4
4,b,4
abaa,bba,aaab,bab,abbba,a,b,aa,bb,
'''

from dataclasses import dataclass

@dataclass
class Estado:
    id: str
    inicial: bool = False
    final: bool = False

@dataclass
class Transicao:
    estado_atual: Estado
    simbolo: str
    estado_destino: Estado

@dataclass
class Automato:
    alfabeto: list[str]
    estados: list[Estado]
    transicoes: list[Transicao]

    def verificarPalavra(self, palavra: str) -> bool:
        estado_atual = None
        for estado in self.estados:
            if estado.inicial: estado_atual = estado
        if estado_atual is None: return False

        for simbolo_atual in palavra:
            if simbolo_atual not in self.alfabeto: return False
            
            estado_para_transicionar = None
            for transicao in self.transicoes:
                if transicao.estado_atual == estado_atual and transicao.simbolo == simbolo_atual:
                    estado_para_transicionar = transicao.estado_destino
                    break

            if estado_para_transicionar is None: return False
            estado_atual = estado_para_transicionar

        return estado_atual.final

# construção do automato a partir do arquivo
alfabeto: list[str] = []
estados: list[Estado] = []
transicoes: list[Transicao] = []
f = open("automato.txt")
arquivo_linhas = f.readlines()

# adicionar estados
qtd_estados = int(arquivo_linhas[0])
estado_inicial = int(arquivo_linhas[1])
estados_finais = arquivo_linhas[2].strip().split(',')
for i in range(1, qtd_estados + 1):
    estado = Estado(str(i))
    if i == estado_inicial: estado.inicial = True
    if str(i) in estados_finais: estado.final = True
    estados.append(estado)

# adicionar simbolos
simbolos = arquivo_linhas[3].strip().split(',')
for simbolo in simbolos:
    alfabeto.append(simbolo)

# adicionar transicoes
transicoes_indice = 4 # transiçoes começam na linha 5 do arquivo
transicoes_bruto: list[str] = []
for i in range(transicoes_indice, len(arquivo_linhas)-1):
    transicoes_bruto.append(arquivo_linhas[transicoes_indice])
    transicoes_indice += 1
palavra_indice = transicoes_indice # vai terminar o for com o número da linha da palavra

for transicao_bruto in transicoes_bruto:
    estado_atual = estados[int(transicao_bruto.split(',')[0])-1]
    simbolo = transicao_bruto.split(',')[1]
    estado_destino = estados[int(transicao_bruto.split(',')[2])-1]
    transicoes.append(Transicao(estado_atual, simbolo, estado_destino))

palavras = arquivo_linhas[palavra_indice].strip().split(',')

f.close()

afd = Automato(alfabeto, estados, transicoes)
for palavra in palavras:
    if afd.verificarPalavra(palavra): 
        print(f"{palavra}: aceita")
    else:
        print(f"{palavra}: rejeitada")