CXX = g++
CXXFLAGS = -Wall -MMD -MP

TARGET = test_panneau
BUILDDIR = .build

SRCS = main.cpp PortSerie.cpp Trame.cpp IHM.cpp
OBJS = $(addprefix $(BUILDDIR)/, $(SRCS:.cpp=.o))
DEPS = $(addprefix $(BUILDDIR)/, $(SRCS:.cpp=.d))

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET)

$(BUILDDIR)/%.o: %.cpp | $(BUILDDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILDDIR):
	mkdir -p $(BUILDDIR)

-include $(DEPS)

clean:
	rm -rf $(BUILDDIR) $(TARGET)

.PHONY: clean