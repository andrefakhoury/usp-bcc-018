def genMSG(txt):
	msg = 0
	for i in txt:
		msg = msg + int(i)


def main():
	genMSG("hello")

main()