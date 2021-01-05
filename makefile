CC  = gcc
CXX = g++

TARGET = shogitui
LDFLAGS = -lm -lpthread -lncursesw

INCLUDE =
DEFINE  = -D NDEBUG

CFLAGS    = -std=c99   $(INCLUDE) -Wall -O2 -g3 $(DEFINE)
CXXFLAGS  = -std=c++11 $(INCLUDE) -Wall -O2 -g3 $(DEFINE)

SRC = src
OBJ = obj
BIN = bin

CSRCS = ${wildcard $(SRC)/*.c}
COBJS := $(CSRCS:$(SRC)%.c=$(OBJ)%.o)

CXXSRCS = ${wildcard $(SRC)/*.cpp}
CXXOBJS := $(CXXSRCS:$(SRC)%.cpp=$(OBJ)%.o)

all: $(TARGET);

$(TARGET): $(COBJS) $(CXXOBJS)
	$(CXX) $(CFLAGS) $(CXXFLAGS) $(COBJS) $(CXXOBJS) -o $(BIN)/$@ $(LDFLAGS)

$(COBJS) : $(@:$(OBJ)%.o=$(SRC)%.c)
	$(CC) -c $(CFLAGS) $(@:$(OBJ)%.o=$(SRC)%.c) -o $@ $(LDFLAGS)

$(CXXOBJS) : $(@:$(OBJ)%.o=$(SRC)%.cpp)
	$(CXX) -c $(CXXFLAGS) $(@:$(OBJ)%.o=$(SRC)%.cpp) -o $@ $(LDFLAGS)

echo:
	@echo $(CC) -c $(CFLAGS) $(CSRCS) -o $@ $(LDFLAGS)
	@echo $(CXX) -c $(CFLAGS) $(COBJS) $(CXXOBJS) -o $@ $(LDFLAGS)
	@echo $(CXX) $(CFLAGS) $(COBJS) $(CXXOBJS) -o $@ $(LDFLAGS)

clean:
	$(RM) $(TARGET) $(COBJS) $(CXXOBJS)

remake: clean $(TARGET);
