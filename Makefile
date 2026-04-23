CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11
TARGET = movie_app
OBJS = main.o Movie.o user.o rating.o MovieManager.o UserManager.o RatingManager.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

main.o: main.cpp MovieManager.h UserManager.h RatingManager.h
	$(CXX) $(CXXFLAGS) -c main.cpp

Movie.o: Movie.cpp Movie.h
	$(CXX) $(CXXFLAGS) -c Movie.cpp

user.o: user.cpp user.h
	$(CXX) $(CXXFLAGS) -c user.cpp

rating.o: rating.cpp rating.h
	$(CXX) $(CXXFLAGS) -c rating.cpp

MovieManager.o: MovieManager.cpp MovieManager.h Movie.h
	$(CXX) $(CXXFLAGS) -c MovieManager.cpp

UserManager.o: UserManager.cpp UserManager.h user.h
	$(CXX) $(CXXFLAGS) -c UserManager.cpp

RatingManager.o: RatingManager.cpp RatingManager.h rating.h MovieManager.h
	$(CXX) $(CXXFLAGS) -c RatingManager.cpp

clean:
	rm -f $(TARGET) $(OBJS)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean