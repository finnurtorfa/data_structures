### Toolchain Commands
##############################

CC = gcc

### General variables
##############################

SH	= $(shell echo $$0)
RM	= rm -rf
CP	= cp -r
MK	= mkdir -p

### Important Directories
##############################

OBJ_DIR = obj
BUILD_DIRS = obj output
OUTPUT_DIR = output
C_SRC_DIRS  = .
C_SRC_DIRS += list

### Message strings
################################################

MSG_ERRORS_NONE 				= Errors: none
MSG_BEGIN 							= -------- begin --------
MSG_END 								= ---------  end  ---------
MSG_SIZE_BEFORE 				= Size before: 
MSG_SIZE_AFTER					= Size after:
MSG_COFF 								= Converting to AVR COFF:
MSG_EXTENDED_COFF 			= Converting to AVR Extended COFF:
MSG_FLASH 							= Creating load file for Flash:
MSG_EEPROM 							= Creating load file for EEPROM:
MSG_EXTENDED_LISTING 		= Creating Extended Listing:
MSG_SYMBOL_TABLE 				= Creating Symbol Table:
MSG_LINKING 						= Linking:
MSG_COMPILING 					= Compiling C:
MSG_ASSEMBLING 					= Assembling:
MSG_CLEANING 						= Cleaning project:
MSG_CREATING_LIBRARY		= Creating library:
MSG_CREATING_BUILD_DIRS	= Creating build directory:

### Source files
### List them without directory extensions
################################################

# Lists
C_SRC  = linked_list.c
C_SRC += dynamic_array.c
C_SRC += hashmap.c

# Tests
TEST_SRC = test_linked_list.c
TEST_SRC += test_dynamic_array.c
TEST_SRC += test_hashmap.c

### Set source lookup paths
################################################

vpath %.c $(C_SRC_DIRS)


### Object files
################################################

C_OBJ = $(addprefix $(OBJ_DIR)/, $(C_SRC:.c=.o))
TEST_OBJ = $(addprefix $(OBJ_DIR)/, $(TEST_SRC:.c=.o))
TEST_OUTPUT = $(TEST_SRC:.c=.out)

### Compiler options
################################################

C_FLAGS  = -W
C_FLAGS += -Wall
C_FLAGS += -Wextra
C_FLAGS += -Winit-self
C_FLAGS += -Wstrict-prototypes
C_FLAGS += -Wl,-z,now 
C_FLAGS += -Wformat-security
C_FLAGS += -fno-exceptions
C_FLAGS += -fstack-protector -Wl,-z,relro 
C_FLAGS += -Wno-unused 
C_FLAGS += -Wno-unused-parameter 
C_FLAGS += -Wno-unused-function 
C_FLAGS += -Wno-unused-label 
C_FLAGS += -Wpointer-arith 
C_FLAGS += -Wformat 
C_FLAGS += -Wreturn-type 
C_FLAGS += -Wsign-compare 
C_FLAGS += -Wmultichar 
C_FLAGS += -Wformat-nonliteral 
C_FLAGS += -Wuninitialized 
C_FLAGS += -Wno-deprecated 
C_FLAGS += -Wmissing-noreturn
C_FLAGS += -Wmissing-format-attribute 
C_FLAGS += -Wbad-function-cast 
C_FLAGS += -Wundef
C_FLAGS += $(patsubst %,-I%,$(INCLUDE_DIRS))
C_FLAGS += -I. 
C_FLAGS += --std=gnu99

### Linker options
################################################

LD_FLAGS =  -L.
LD_FLAGS += -Wl,-O1
LD_FLAGS += -Wl,--discard-all
LD_FLAGS += -Wl,--no-undefined
LD_FLAGS += -Wl,--build-id=sha1
LD_FLAGS += -rdynamic

### Rules
###
### Rules are formatted in the following manner,
### all but the target are optional:
### target : dependencies
###		command
###		...
###		...
###	
################################################

# Default rule target
.PHONY: all
.PRECIOUS : $(C_OBJ)
all: begin version $(BUILD_DIRS) $(C_OBJ) end

# Compile: create object files from C source files.
$(OBJ_DIR)/%.o : %.c
	@echo
	@echo $(MSG_COMPILING) $<
	$(CC) -c $(C_FLAGS) $< -o $@ 

# Target: create build directories
$(BUILD_DIRS) : 
	@echo
	@echo $(MSG_CREATING_BUILD_DIRS)
	- $(MK) $@

test: begin version $(BUILD_DIRS) $(C_OBJ) $(TEST_OUTPUT) end

test%.out: $(TEST_OBJ)
	@echo
	@echo $(MSG_LINKING) $@
	$(CC) $(C_FLAGS) $(C_OBJ) $(OBJ_DIR)/$(@:.out=.o) $(LD_FLAGS) -o $(OUTPUT_DIR)/$@

debug: C_FLAGS += -g
debug: test

# Target: clean project.
clean: begin clean_list end

clean_list :
	@echo
	@echo $(MSG_CLEANING)
	$(RM) $(BUILD_DIRS)

begin : 
	@echo
	@echo $(MSG_BEGIN)

version : 
	@echo
	$(CC) --version

end :
	@echo
	@echo $(MSG_END)
