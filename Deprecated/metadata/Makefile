# the compiler: g++ for C++
CXX = g++

# compiler flags:
#  -Wall turns on most, but not all, compiler warnings
CXXFLAGS  = -Wall

# Dynamic linking 
LDFLAGS = "-Wl,-rpath,." -L. -lLexActivator

# Uncomment following line for static linking on Linux
#LDFLAGS += -Wl,-Bstatic -L. -lLexActivator -Wl,-Bdynamic -lpthread -lssl3 -lnss3 -lnspr4

# Uncomment following line for static linking on MacOS
#LDFLAGS += -L. -lLexActivator -framework CoreFoundation -framework SystemConfiguration -framework Security

# the build target executable:
TARGET = node-locked-license

all: $(TARGET)

$(TARGET): $(TARGET).cpp
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(TARGET).cpp $(LDFLAGS)

clean:
	$(RM) $(TARGET)