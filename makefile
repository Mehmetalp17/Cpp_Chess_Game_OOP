all: clean compile run

compile: mychess.cpp chesslib.cpp
	@echo "-------------------------------------------"
	@echo "Compiling..."
	@g++ -o test mychess.cpp chesslib.cpp -lm -std=c++11

run:
	@echo "-------------------------------------------"
	@echo "Running the tests...."
	@echo "======================================================================="
	@./test
	@echo "======================================================================="
	@echo "Completed tests...."

clean:
	@echo "-------------------------------------------"
	@echo "Cleaning..."
	@rm -f *.o
	@rm -f test