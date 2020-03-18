build: tema1.c
	gcc tema1.c -o tema1 -lm
run: build
	./tema1 ${args}
clean:
	rm -f tema1
