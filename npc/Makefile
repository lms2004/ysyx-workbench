# Verilog and C++ file paths
VERILOG_FILE ?= vsrc/example.v
TESTBENCH_FILE ?= csrc/main.cpp

# Top module name (no file extension)
TOP_MODULE ?= example

# Build directory
BUILD_DIR ?= obj_dir

# Targets
all: $(BUILD_DIR)/V$(TOP_MODULE)

# Verilate: Compile Verilog to C++
verilate:
	verilator --cc $(VERILOG_FILE) --exe $(TESTBENCH_FILE) --trace

# Build the simulation executable
$(BUILD_DIR)/V$(TOP_MODULE): verilate
	make -j -C $(BUILD_DIR) -f V$(TOP_MODULE).mk V$(TOP_MODULE)

# Simulation target
sim: $(BUILD_DIR)/V$(TOP_MODULE) .git_commit
	@./$<

# Clean generated files
clean:
	rm -rf $(BUILD_DIR) waveform.vcd

.PHONY: .git_commit
.git_commit:
	@echo "Skipping git commit placeholder"

include ../Makefile
