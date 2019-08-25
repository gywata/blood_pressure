lib: blood_pressure.cpp
	g++ -std=c++11 -fPIC -shared blood_pressure.cpp -o libpressure.so

test: lib test.cpp
	g++ -Wall -L/Users/ywata/Projects/philips test.cpp -lpressure -o test	
