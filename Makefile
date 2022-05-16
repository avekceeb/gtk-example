# sudo apt install libgtkmm-3.0-dev

all: table

table:
	g++ table-example.cpp -o table `pkg-config gtkmm-3.0 --cflags --libs`

clean:
	rm -rf *.o *.exe ./table
