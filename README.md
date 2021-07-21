# socket-cpp

POSIX compliant multiclient-server network infrastructure that can operate autonomously in any application.

# run

In server folder:
`g++ -pthread *.cpp ../*.cpp -o sv; ./sv`

In client folder:
`g++ -pthread *.cpp ../*.cpp -o cli; ./cli`
