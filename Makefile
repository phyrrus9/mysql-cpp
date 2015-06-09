OBJS=mySQLCon.o mySQLResult.o
TARGET=libmySQL.a

all: $(OBJS)
	ar rvs $(TARGET) $(OBJS)

mySQLCon.o:
	g++ -fPIC -c mySQLCon.cpp -o mySQLCon.o

mySQLResult.o:
	g++ -fPIC -c mySQLResult.cpp -o mySQLResult.o

clean:
	rm -rf $(TARGET) $(OBJS)
