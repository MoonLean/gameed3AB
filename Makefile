#linha de comando a ser iniciada primeiro
#verifica a existencia dos arquivos
run: main.cpp JOGO_ED3.cpp JOGO_ED3.h compilador
	@echo Tudo okay, executando...
	main
compilador:
	@echo Compilando...
	gcc -o main main.cpp JOGO_ED3.cpp
