.PHONY: all, apple, java

all:
	cd src && make

apple:
	cd src && make apple
	
java:
	javac -target 1.2 -source 1.2 java/*.java