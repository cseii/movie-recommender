CXX      = g++
CXXFLAGS = -std=c++17 -Wall -g -Iinclude
TARGET   = recommend
SRCDIR   = src
OBJDIR   = obj

OBJS = $(OBJDIR)/main.o \
       $(OBJDIR)/Rating.o \
       $(OBJDIR)/RatingManager.o \
       $(OBJDIR)/SimilarityCalculator.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm -rf $(OBJDIR) $(TARGET)

.PHONY: all clean