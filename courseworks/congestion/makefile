default: vehicle

all: vehicle test_runner

afresh: clean all

vehicle: vehicleMain.o date.o vehicle.o helper_functions.o
	g++ -g -Wall vehicleMain.o date.o vehicle.o helper_functions.o -o vehicle

test_runner: test_runner.o date_test.o date.o vehicle_test.o vehicle.o helper_functions.o
	g++ -g -Wall test_runner.o date_test.o date.o vehicle_test.o vehicle.o helper_functions.o -o test_runner

vehicleMain.o: vehicleMain.cpp date.h vehicle.h
	g++ -g -Wall -c vehicleMain.cpp

test_runner.o: test_runner.cpp date_test.h vehicle_test.h
	g++ -g -Wall -c test_runner.cpp

vehicle.o: vehicle.h vehicle.cpp
	g++ -g -Wall -c vehicle.cpp

vehicle_test.o: vehicle_test.h vehicle_test.cpp vehicle.h
	g++ -g -Wall -c vehicle_test.cpp

date.o: date.h date.cpp
	g++ -g -Wall -c date.cpp

date_test.o: date_test.h date_test.cpp date.h
	g++ -g -Wall -c date_test.cpp

helper_functions.o: helper_functions.cpp helper_functions.h
	g++ -g -Wall -c helper_functions.cpp

clean:
	rm -f *.o test_runner vehicle

archive: clean_archive
	mkdir -p archive && (git archive --format=tar --prefix vehicle/ -o archive/precleanvehicle.tar master) && cd archive && tar -xvf precleanvehicle.tar && cd vehicle && make clean && rm -rf submission && rm -f .gitignore && rm -f desiredoutput.txt && cd .. && tar -cvf vehicle.tar -C vehicle .  && rm -rf vehicle && mkdir -p test_vehicle_tar && mv vehicle.tar test_vehicle_tar/ && cd test_vehicle_tar && tar -xvf vehicle.tar

clean_archive:
	rm -rf archive