# socket-cpp

POSIX compliant multiclient-server network infrastructure that can operate autonomously in any application.

# run

In server folder:
`g++ -pthread *.cpp ../lib/*.cpp.o -o sv; ./sv.o

In client folder:
`g++ -pthread *.cpp ../lib/*.cpp.o -o cli; ./cli.o`
