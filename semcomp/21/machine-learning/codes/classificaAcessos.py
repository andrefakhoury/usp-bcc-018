from sklearn.naive_bayes import MultinomialNB
from dados import carregarAcessos

def main():
	X, Y = carregarAcessos()

	dadosTreino = X[:90]
	marksTreino = Y[:90]

	dadosTeste = X[-9:]
	marksTeste = Y[-9:]

	modelo = MultinomialNB()
	modelo.fit(dadosTreino, marksTreino)

	resultado = modelo.predict(dadosTeste)
	diferencas = resultado - marksTeste
	acertos = [d for d in diferencas if d == 0]
	porcentagem = len(acertos)/len(dadosTeste)*100
	print(porcentagem)

main()