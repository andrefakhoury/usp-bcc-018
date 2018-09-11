#eh gordinho, tem perna curta, faz miau
from sklearn.naive_bayes import MultinomialNB

def main():
	porco1 = [1, 1, 0]
	porco2 = [1, 1, 0]
	porco3 = [1, 1, 0]

	gato1  = [1, 1, 1]
	gato2  = [0, 1, 1]
	gato3  = [0, 1, 1]

	porcos = [porco1, porco2, porco3]
	gatos  = [gato1,  gato2,  gato3]
	dados  = porcos + gatos

	'''	dizer o que eh cada um desses
		1 porco, -1 gato'''
	marcacoes = [1, 1, 1, -1, -1, -1]

	modelo = MultinomialNB()
	modelo.fit(dados, marcacoes) #treinar

	#a, b, c = input().split()
	#a, b, c = [int(a), int(b), int(c)]

	misterioso1 = [1, 1, 1]
	misterioso2 = [1, 1, 0]
	misterioso3 = [0, 0, 1]
	misterioso4 = [0, 0, 0]

	testes = [misterioso1, misterioso2, misterioso3, misterioso4]
	marcacoes_testes = [-1, 1, -1, 1]
	resultado = modelo.predict(testes)

	diferencas = marcacoes_testes - resultado

	# cont = 0
	# for d in diferencas: if (d != 0): cont = cont+1
	# print(cont)

	acertos = [d for d in diferencas if d == 0]
	totAcertos = len(acertos)
	porcentagem = totAcertos/len(testes)*100

	print("Acertos:", porcentagem)

main()