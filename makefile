.DEFAULT_GOAL := todolist.cpp

todolist.cpp: 
	g++ -g todolist.cpp func.cpp -o todolist 

run: todolist.cpp
	./todolist

.PHONY: todolist.cpp