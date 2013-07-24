traffic: Time.o trafficLight.o trafficJunction.o trafficLightsMain.cpp
	g++ -g -Wall Time.o trafficLight.o trafficJunction.o trafficLightsMain.cpp -o traffic

tests: TimeTest.o Time.o test/TimeTest.h trafficLight.o trafficLightTest.o test/trafficLightTest.h test/tests.cpp trafficJunctionTest.o trafficJunction.o test/trafficJunctionTest.h
	g++ -g -Wall TimeTest.o Time.o trafficLight.o trafficLightTest.o trafficJunction.o trafficJunctionTest.o test/tests.cpp -o testtraffic

all: tests traffic

afresh: clean all

trafficJunctionTest.o: test/trafficJunctionTest.h test/trafficJunctionTest.cpp
	g++ -g -Wall -c test/trafficJunctionTest.cpp

trafficJunction.o: trafficJunction.cpp trafficJunction.h
	g++ -g -Wall -c trafficJunction.cpp

trafficLightTest.o: test/trafficLightTest.h test/trafficLightTest.cpp
	g++ -g -Wall -c test/trafficLightTest.cpp

trafficLight.o: trafficLight.h trafficLight.cpp
	g++ -g -Wall -c trafficLight.cpp

TimeTest.o: test/TimeTest.h test/TimeTest.cpp
	g++ -g -Wall -c test/TimeTest.cpp

Time.o: Time.h Time.cpp
	g++ -g -Wall -c Time.cpp

clean:
	rm -f *.o testtraffic traffic precleantraffic.tar

archive:
	git archive --format tar --prefix=traffic/ -o precleantraffic.tar master
