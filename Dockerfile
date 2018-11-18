FROM gcc:8.2.0
RUN apt-get -qq update && apt-get -y install git scons bzr lib32z1 lib32ncurses5

RUN apt-get install -y libgtest-dev
RUN apt-get install -y cmake
RUN cmake /usr/src/gtest/CMAKELists.txt
RUN cd /usr/src/gtest/ && make
RUN cd /usr/src/gtest/ && cp *.a /usr/lib

WORKDIR /usr/src/BlackJack
