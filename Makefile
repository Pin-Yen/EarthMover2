# OBJ = \
# obj/typetree.o\
# obj/typetreefreestyle.o\
# obj/typetreerenjubasic.o\


# OBJ_TEST = \
# obj/testtypetree.o\


# GENERAL_FLAG = -std=c++11

# Test: obj_dir $(OBJ) $(OBJ_TEST)
#     g++ -o test $(OBJ) $(OBJ_NET) $(GENERAL_FLAG) -pthread -O3
# Test : OPT_FLAG = -O0 -g

# obj_dir :
#     if ! [ -d "obj" ]; then mkdir obj; fi

# clean :
#     if [ -d "obj" ]; then rm -r obj; fi
#     if [ -e "EM" ]; then rm EM; fi

# obj/typetree.o: typetree.cpp \
#  typetree.h \
#     g++ -c $(GENERAL_FLAG) $(OPT_FLAG) $< -o $@

# obj/typetreefreestyle: typetreefreestyle.cpp typetreefreestyle.h
#     g++ -c $(GENERAL_FLAG) $(OPT_FLAG) $< -o $@

# obj.typetreerenjubasic: typetreerenjubasic.cpp typetreerenjubasic.h
#     g++ -c $(GENERAL_FLAG) $(OPT_FLAG) $< -o $@

# typetree.h: stonestatus.h typetree.h

# typetreerenjubasic.h: stonestatus.h typetree.h

# typetreefreestyle.h: stonestatus.h typetree.h


SRC_DIR = src
OBJ_DIR = obj

TEST_SRC_DIR = test
TEST_OBJ_DIR = testobj

SELFPLAY_SRC_DIR = selfplay

SRC = $(wildcard $(SRC_DIR)/*.cpp)
OBJ = $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

TEST_SRC = $(wildcard $(TEST_SRC_DIR)/*.cpp)
TEST_OBJ = $(TEST_SRC:$(TEST_SRC_DIR)/%.cpp=$(TEST_OBJ_DIR)/%.o)
CC=g++
CPPFLAGS += -Isrc -Ilib -pthread -g -O0
CFLAGS += -std=c++17
# LDFLAGS += -Llib
# LDLIBS += -lm

.PHONY: clean



$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp obj_dir
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

test_typetree: $(OBJ)
	$(CC) $(TEST_SRC_DIR)/testtypetree.cpp $(CPPFLAGS) $(LDFLAGS) $^ $(LDLIBS) -o $@

test_virtualboard: $(OBJ)
	$(CC) $(TEST_SRC_DIR)/testvirtualboard.cpp $(CPPFLAGS)  $(LDFLAGS) $^ $(LDLIBS) -o $@

test_montecarlo: $(OBJ)
	$(CC) $(TEST_SRC_DIR)/testmontecarlo.cpp $(CPPFLAGS)  $(LDFLAGS) $^ $(LDLIBS) -o $@

selfplay_freestyle: $(OBJ)
	$(CC) $(SELFPLAY_SRC_DIR)/selfplay.cpp $(CPPFLAGS)  $(LDFLAGS) $^ $(LDLIBS) -o $@

$(TESTOBJ_DIR)/%.o: $(TEST_SRC_DIR)/%.cpp testobj_dir
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)

obj_dir :
	if ! [ -d $(OBJ_DIR) ]; then mkdir $(OBJ_DIR); fi

testobj_dir :
	if ! [ -d $(TEST_OBJ_DIR) ]; then mkdir $(TEST_OBJ_DIR); fi