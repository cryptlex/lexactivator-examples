# the compiler: g++ for C++
CXX = g++

# compiler flags:
#  -Wall turns on most, but not all, compiler warnings
CXXFLAGS  = -Wall

# Dynamic linking 
# LDFLAGS = "-Wl,-rpath,." -L../lib/dynamic/ -lLexActivator

# Uncomment following line for static linking on Linux
#LDFLAGS += -Wl,-Bstatic -L../lib/static/ -lLexActivator -Wl,-Bdynamic -lpthread -lssl3 -lnss3 -lnspr4

# Uncomment following line for static linking on MacOS
LDFLAGS += -L../lib/static/ -lLexActivator -framework CoreFoundation -framework SystemConfiguration -framework Security

# the build target executable:
TARGET = trial-activation

all: $(TARGET)

$(TARGET): $(TARGET).cpp
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(TARGET).cpp $(LDFLAGS)

clean:
	$(RM) $(TARGET)